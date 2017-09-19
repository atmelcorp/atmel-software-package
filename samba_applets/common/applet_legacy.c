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

#include <string.h>

#include "applet.h"
#include "applet_legacy.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local definitions
 *----------------------------------------------------------------------------*/

/** Mailbox content for the legacy commands. */
union legacy_mailbox {
	struct {
		/** Buffer address */
		uint32_t buf_addr;
		/** Read/Write Length (in bytes) */
		uint32_t length;
		/** Read/Write offset (in bytes) */
		uint32_t offset;
	} in;

	struct {
		/** Bytes read/written */
		uint32_t bytes;
	} out;
};

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_SOC_SAMA5D3
/* ROM Code version string */
static const char* sama5d3_rom_version = (const char*)0x310000;
#endif

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

bool applet_is_legacy_command(uint32_t cmd)
{
	return (cmd == APPLET_CMD_LEGACY_WRITE ||
	        cmd == APPLET_CMD_LEGACY_READ);
}

/* Dummy implementations of the legacy READ/WRITE commands */
uint32_t applet_emulate_legacy_command(uint32_t cmd, uint32_t *args)
{
	union legacy_mailbox *mbx = (union legacy_mailbox*)args;

	if (cmd == APPLET_CMD_LEGACY_READ) {
#ifdef CONFIG_SOC_SAMA5D3
		/* SAMA5D3 ROM-code versions 2.0/2.1 cannot properly support the READ command */
		if (!strncmp(sama5d3_rom_version, "v2.0", 4) ||
		    !strncmp(sama5d3_rom_version, "v2.1", 4)) {
			trace_error_wp("SAMA5D3 ROM-Code 2.0 or 2.1 detected, READ command disabled.\r\n");
			return APPLET_FAIL;
		}
#endif
		/* only move existing data inside the applet buffer */
		if (mbx->in.offset && mbx->in.offset < applet_buffer_size) {
			memmove(applet_buffer,
				applet_buffer + mbx->in.offset,
				applet_buffer_size - mbx->in.offset);
		}

		return APPLET_SUCCESS;
	} else if (cmd == APPLET_CMD_LEGACY_WRITE) {
		/* do nothing */
		return APPLET_SUCCESS;
	}

	return APPLET_FAIL;
}
