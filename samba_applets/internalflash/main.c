/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "applet.h"
#include "board.h"
#include "chip.h"
#include "intmath.h"
#include "nvm/flash/flashd.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _flash flash;

static uint8_t *buffer;
static uint32_t buffer_size;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'Internal Flash' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	/* initialize the SPI and serial flash */
	if (flashd_initialize(&flash, EEFC) < 0) {
		trace_error("Error while initializing internal flash.\r\n");
		return APPLET_DEV_UNKNOWN;
	}

	trace_warning_wp("Internal flash driver initialized\r\n");

	/* Get device parameters */
	uint32_t size = flash.total_size;
	uint32_t page_size = flash.page_size;

	trace_warning_wp("Size: %u bytes\r\n", (unsigned)size);
	trace_warning_wp("Page Size: %u bytes\r\n", (unsigned)page_size);
	trace_warning_wp("Erase Size: %u bytes\r\n", (unsigned)flash.erase_size);

	/* round buffer size to a multiple of page size and check if
	 * it's big enough for at least one page */
	buffer = applet_buffer;
	buffer_size = applet_buffer_size & ~(page_size - 1);
	if (buffer_size == 0) {
		trace_error("Not enough memory for buffer\r\n");
		return APPLET_FAIL;
	}
	trace_warning_wp("Buffer Address: 0x%08x\r\n", (unsigned)buffer);
	trace_warning_wp("Buffer Size: %u bytes\r\n", (unsigned)buffer_size);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = page_size;
	mbx->out.mem_size = size / page_size;
	mbx->out.erase_support = flash.erase_size / page_size;
	mbx->out.nand_header = 0;

	trace_warning_wp("Internal flash applet initialized successfully.\r\n");
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_info(uint32_t cmd, uint32_t *mailbox)
{
	/* 'read info' uses the same mailbox output as 'initialize' */
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_INFO);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = flash.page_size;
	mbx->out.mem_size = flash.total_size / flash.page_size;
	mbx->out.erase_support = flash.erase_size / flash.page_size;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * flash.page_size;
	uint32_t length = mbx->in.length * flash.page_size;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	/* check that requested size does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that we won't write past end of flash */
	if (offset + length > flash.total_size) {
		trace_error("Trying to write past end of flash\r\n");
		return APPLET_FAIL;
	}

	/* perform the write operation */
	if (flashd_write(&flash, offset, buffer, length) < 0) {
		trace_error("Write error\r\n");
		mbx->out.pages = 0;
		return APPLET_WRITE_FAIL;
	}

	trace_info_wp("Wrote %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * flash.page_size;
	uint32_t length = mbx->in.length * flash.page_size;

	assert(cmd == APPLET_CMD_READ_PAGES);

	/* check that request does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that we won't read past end of flash */
	if (offset + length > flash.total_size) {
		trace_error("Trying to read past end of flash\r\n");
		return APPLET_FAIL;
	}

	/* get flash read address */
	if (flashd_read(&flash, offset, buffer, length) < 0) {
		trace_error("Read error\r\n");
		mbx->out.pages = 0;
		return APPLET_FAIL;
	}

	trace_info_wp("Read %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_erase_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * flash.page_size;
	uint32_t length = mbx->in.length * flash.page_size;

	assert(cmd == APPLET_CMD_ERASE_PAGES);

	if (flash.erase_size != length) {
		trace_error("Memory does not support requested erase size "
				"%u bytes\r\n", (unsigned)length);
		return APPLET_FAIL;
	}

	if (offset & (length - 1)) {
		trace_error("Unaligned erase offset: 0x%08x (erase size "
				"%u bytes)\r\n", (unsigned)offset,
				(unsigned)length);
		return APPLET_FAIL;
	}

	if (flashd_erase_block(&flash, offset, length) < 0) {
		trace_error("Erase failed at offset 0x%08x\r\n",
				(unsigned)offset);
		return APPLET_ERASE_FAIL;
	}

	trace_info_wp("Erased %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_READ_INFO, handle_cmd_read_info },
	{ APPLET_CMD_ERASE_PAGES, handle_cmd_erase_pages },
	{ APPLET_CMD_READ_PAGES, handle_cmd_read_pages },
	{ APPLET_CMD_WRITE_PAGES, handle_cmd_write_pages },
	{ 0, NULL }
};
