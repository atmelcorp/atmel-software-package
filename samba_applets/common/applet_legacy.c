/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#include "applet.h"
#include "applet_legacy.h"
#include "trace.h"
#include "intmath.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *         Local definitions
 *----------------------------------------------------------------------------*/

#define APPLET_CMD_LEGACY_WRITE        0x02 /* Write (legacy) */
#define APPLET_CMD_LEGACY_READ         0x03 /* Read (legacy) */
#define APPLET_CMD_LEGACY_BATCH_ERASE  0x14 /* Batch Erase (legacy) */

/** Mailbox content for the legacy commands. */
union legacy_mailbox {
	struct {
		/** Buffer address */
		uint32_t buf_addr;
		/** Buffer size (in bytes) */
		uint32_t buf_size;
		/** Read/Write offset (in bytes) */
		uint32_t offset;
	} rw_in;

	struct {
		/** Erase offset (in bytes) */
		uint32_t offset;
	} erase_in;

	struct {
		/** Bytes read/written/erased */
		uint32_t bytes;
	} out;
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool get_applet_info(uint32_t *buf_addr, uint32_t *buf_size,
		uint32_t *page_size, uint32_t *erase_support)
{
	union initialize_mailbox mbx;
	applet_command_handler_t handler;

	handler = get_applet_command_handler(APPLET_CMD_READ_INFO);
	if (!handler)
		return false;
	if (handler(APPLET_CMD_READ_INFO, (uint32_t*)&mbx) != APPLET_SUCCESS)
		return false;

	*buf_addr = mbx.out.buf_addr;
	*buf_size = mbx.out.buf_size;
	*page_size = mbx.out.page_size;
	*erase_support = mbx.out.erase_support;
	return true;
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

bool applet_is_legacy_command(uint32_t cmd)
{
	return (cmd == APPLET_CMD_LEGACY_WRITE)
		|| (cmd == APPLET_CMD_LEGACY_READ)
		|| (cmd == APPLET_CMD_LEGACY_BATCH_ERASE);
}

uint32_t applet_emulate_legacy_command(uint32_t cmd, uint32_t *args)
{
	uint32_t buf_addr, buf_size, page_size, erase_support;
	uint32_t length, new_cmd, status;
	union legacy_mailbox *mbx = (union legacy_mailbox*)args;
	union read_write_erase_pages_mailbox new_mbx;
	applet_command_handler_t handler;

	if (!applet_is_legacy_command(cmd))
		return APPLET_FAIL;

	if (!get_applet_info(&buf_addr, &buf_size,
				&page_size, &erase_support))
		return APPLET_FAIL;

	if (cmd == APPLET_CMD_LEGACY_WRITE ||
			cmd == APPLET_CMD_LEGACY_READ) {

		if (mbx->rw_in.buf_addr != buf_addr) {
			trace_error("Invalid buffer address\r\n");
			return APPLET_FAIL;
		}

		if (mbx->rw_in.buf_size > buf_size) {
			trace_error("Invalid buffer size\r\n");
			return APPLET_FAIL;
		}

		if (mbx->rw_in.offset & (page_size - 1)) {
			trace_error("Un-aligned offset\r\n");
			return APPLET_FAIL;
		}

		length = ROUND_UP_MULT(mbx->rw_in.buf_size, page_size);
		/* if buffer size was rounded up, fill the padding with 0xFF */
		if (length != mbx->rw_in.buf_size)
			memset((uint8_t*)buf_addr + mbx->rw_in.buf_size, 0xff,
					length - mbx->rw_in.buf_size);

		if (cmd == APPLET_CMD_LEGACY_WRITE)
			new_cmd = APPLET_CMD_WRITE_PAGES;
		else if (cmd == APPLET_CMD_LEGACY_READ)
			new_cmd = APPLET_CMD_READ_PAGES;
		new_mbx.in.offset = mbx->rw_in.offset / page_size;
		new_mbx.in.length = length / page_size;

		length = mbx->rw_in.buf_size;
	} else if (cmd == APPLET_CMD_LEGACY_BATCH_ERASE) {
		if (!erase_support) {
			trace_error("Applet does not support any erase size\r\n");
			return APPLET_FAIL;
		}

		/* get maximum supported erase size */
		length = 1 << (31 - __builtin_clz(erase_support));

		if (mbx->erase_in.offset & (page_size - 1)) {
			trace_error("Un-aligned offset\r\n");
			return APPLET_FAIL;
		}

		new_cmd = APPLET_CMD_ERASE_PAGES;
		new_mbx.in.offset = mbx->erase_in.offset / page_size;
		new_mbx.in.length = length;

		length = new_mbx.in.length * page_size;
	} else {
		return APPLET_FAIL;
	}

	handler = get_applet_command_handler(new_cmd);
	if (!handler) {
		trace_error_wp("Unsupported applet command 0x%08x\r\n",
				(unsigned)cmd);
		return APPLET_FAIL;
	}
	status = handler(new_cmd, (uint32_t*)&new_mbx);
	mbx->out.bytes = min_u32(length, new_mbx.out.pages * page_size);
	return status;
}
