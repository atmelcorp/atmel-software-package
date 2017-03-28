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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>

#include "applet.h"
#include "bootconfig.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'BootConfig' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	if (bootcfg_initialize() < 0) {
		trace_error("Failed to initialize bootconfig applet.\r\n");
		return APPLET_FAIL;
	}

	mbx->out.buf_addr = 0;
	mbx->out.buf_size = 0;
	mbx->out.page_size = 0;
	mbx->out.mem_size = 0;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union read_bootcfg_mailbox *mbx = (union read_bootcfg_mailbox*)mailbox;
	uint32_t index = mbx->in.index;

	assert(cmd == APPLET_CMD_READ_BOOTCFG);

	if (bootcfg_read(index, &mbx->out.value) < 0) {
		trace_error("Invalid parameter for read config: index %u\r\n",
				(unsigned)mbx->in.index);
		return APPLET_FAIL;
	}

	bootcfg_print(index, mbx->out.value);

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union write_bootcfg_mailbox *mbx = (union write_bootcfg_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_WRITE_BOOTCFG);

	if (bootcfg_write(mbx->in.index, mbx->in.value) < 0) {
		trace_error("Invalid parameter for write config: index %u value 0x%08x\r\n",
				(unsigned)mbx->in.index, (unsigned)mbx->in.value);
		return APPLET_FAIL;
	}

	trace_warning_wp("Configuration written: ");
	bootcfg_print(mbx->in.index, mbx->in.value);

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_READ_BOOTCFG, handle_cmd_read_bootcfg },
	{ APPLET_CMD_WRITE_BOOTCFG, handle_cmd_write_bootcfg },
	{ 0, NULL }
};
