/* ----------------------------------------------------------------------------
 *         MICROCHIP Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Microchip Technology
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
#include <string.h>

#include "applet.h"
#include "chip.h"
#include "uniqueid.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t uid[UID_SIZE_MAX];
	uint32_t uid_size = 0;
	uint32_t i = 0;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'ReadUniqueID' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	/* clear uid vector before using it */
	memset(uid, 0, sizeof(uid));

	uid_size = read_unique_id(uid, UID_SIZE_MAX);
	if (!uid_size) {
		trace_error("Failed to initialize readuniqueid applet.\r\n");
		return APPLET_FAIL;
	}

	/* print unique id */
	for (i = 0; i < uid_size; i++)
		trace_warning_wp("UID[%lu] = 0x%08lx\r\n", i, uid[i]);

	mbx->out.buf_addr = (uint32_t)applet_buffer;
	mbx->out.buf_size = uid_size * sizeof(uint32_t);
	mbx->out.page_size = 0;
	mbx->out.mem_size = 0;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	/* copy UID in buffer */
	memcpy(applet_buffer, &uid, uid_size * sizeof(uint32_t));

	return APPLET_SUCCESS;
}


/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ 0, NULL }
};
