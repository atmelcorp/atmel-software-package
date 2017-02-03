/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
#include "gpio/pio.h"
#include "intmath.h"
#include "nvm/spi-nor/qspiflash.h"
#include "peripherals/pmc.h"
#include "pin_defs.h"
#include "spi/qspi.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define MAX_BUFFER_SIZE (64 * 1024)

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _qspiflash flash;

static uint8_t *buffer;
static uint32_t buffer_size;
static uint32_t erase_support;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t instance, uint32_t ioset, Qspi** addr)
{
	int i;
	for (i = 0; i < num_qspiflash_pin_defs; i++) {
		const struct qspiflash_pin_definition* def =
			&qspiflash_pin_defs[i];
		if (def->instance == instance && def->ioset == ioset) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}

	trace_error("Invalid configuration: QSPI%u IOSet%u\r\n",
		(unsigned)instance, (unsigned)ioset);
	return false;
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t instance = mbx->in.parameters[0];
	uint32_t ioset = mbx->in.parameters[1];
	uint32_t freq = mbx->in.parameters[2];

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_warning_wp("\r\nApplet 'QSPI Flash' from softpack " SOFTPACK_VERSION ".\r\n");

	uint32_t max_freq = pmc_get_peripheral_clock(ID_QSPI0);
	if (freq == 0 || freq > max_freq) {
		trace_error("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)freq);
		return APPLET_FAIL;
	}

	Qspi* addr;
	if (!configure_instance_pio(instance, ioset, &addr))
		return APPLET_FAIL;

	trace_warning_wp("Initializing QSPI%u IOSet%u at %uHz\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)freq);

	/* initialize the QSPI */
	qspi_initialize(addr);
	qspi_set_baudrate(addr, freq);

	/* initialize the QSPI flash */
	if (qspiflash_configure(&flash, addr) < 0) {
		trace_error("Error while detecting QSPI flash chip\r\n");
		return APPLET_DEV_UNKNOWN;
	}

	if (!flash.desc->jedec_id) {
		trace_error("Device Unknown\r\n");
		return APPLET_DEV_UNKNOWN;
	}
	else {
		uint32_t page_size = flash.desc->page_size;
		uint32_t mem_size = flash.desc->size;

		trace_warning_wp("Found Device %s\r\n", flash.desc->name);
		trace_warning_wp("Size: %u bytes\r\n", (unsigned)mem_size);
		trace_warning_wp("Page Size: %u bytes\r\n", (unsigned)page_size);

		erase_support = 0;
		if (flash.desc->flags & SPINOR_FLAG_ERASE_4K) {
			trace_warning_wp("Supports 4K block erase\r\n");
			erase_support |= (4 * 1024) / page_size;
		}
		if (flash.desc->flags & SPINOR_FLAG_ERASE_32K) {
			trace_warning_wp("Supports 32K block erase\r\n");
			erase_support |= (32 * 1024) / page_size;
		}
		if (flash.desc->flags & SPINOR_FLAG_ERASE_64K) {
			trace_warning_wp("Supports 64K block erase\r\n");
			erase_support |= (64 * 1024) / page_size;
		}
		if (flash.desc->flags & SPINOR_FLAG_ERASE_256K) {
			trace_warning_wp("Supports 256K block erase\r\n");
			erase_support |= (256 * 1024) / page_size;
		}

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
		mbx->out.mem_size = mem_size / page_size;
		mbx->out.erase_support = erase_support;
		mbx->out.nand_header = 0;

		trace_warning_wp("QSPI applet initialized successfully.\r\n");

		return APPLET_SUCCESS;
	}
}

static uint32_t handle_cmd_read_info(uint32_t cmd, uint32_t *mailbox)
{
	/* 'read info' uses the same mailbox output as 'initialize' */
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_INFO);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = flash.desc->page_size;
	mbx->out.mem_size = flash.desc->size / flash.desc->page_size;
	mbx->out.erase_support = erase_support;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;

	uint32_t offset = mbx->in.offset * flash.desc->page_size;
	uint32_t length = mbx->in.length * flash.desc->page_size;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	/* check that requested size does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the write operation */
	if (qspiflash_write(&flash, offset, buffer, length) < 0) {
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

	uint32_t offset = mbx->in.offset * flash.desc->page_size;
	uint32_t length = mbx->in.length * flash.desc->page_size;

	assert(cmd == APPLET_CMD_READ_PAGES);

	/* check that requested size does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the read operation */
	if (qspiflash_read(&flash, offset, buffer, length) < 0) {
		trace_error("Read error\r\n");
		mbx->out.pages = 0;
		return APPLET_READ_FAIL;
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

	uint32_t offset = mbx->in.offset * flash.desc->page_size;
	uint32_t length = mbx->in.length * flash.desc->page_size;

	assert(cmd == APPLET_CMD_ERASE_PAGES);

	if ((flash.desc->flags & SPINOR_FLAG_ERASE_4K)
			&& length == 4 * 1024) {
	} else if ((flash.desc->flags & SPINOR_FLAG_ERASE_32K)
			&& length == 32 * 1024) {
	} else if ((flash.desc->flags & SPINOR_FLAG_ERASE_64K)
			&& length == 64 * 1024) {
	} else if ((flash.desc->flags & SPINOR_FLAG_ERASE_256K)
			&& length == 256 * 1024) {
	} else {
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

	if (qspiflash_erase_block(&flash, offset, length) < 0) {
		trace_error("Erase failed at offset 0x%lx\r\n", offset);
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
