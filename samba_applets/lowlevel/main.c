/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
#include "board.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Initialization mode */

#define INIT_MODE_EK           0
#define INIT_MODE_USER_CRYSTAL 1
#define INIT_MODE_BYPASS       2

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/* Input arguments for the Init command. */

struct input_init
{
	uint32_t comm_type;    /* type of communication link used */
	uint32_t trace_level;  /* trace level */
	uint32_t mode;         /* low initialization mode */
	uint32_t crystal_freq; /* frequency of user-defined crystal */
	uint32_t ext_clock;    /* frequency of external clock in bypass mode */
};

/*----------------------------------------------------------------------------
 *         Private functions
 *----------------------------------------------------------------------------*/

static uint32_t handle_cmd_init(uint32_t cmd, uint32_t *args)
{
	struct input_init *in = (struct input_init *)args;

	assert(cmd == APPLET_CMD_INIT);

	applet_set_init_params(in->comm_type, in->trace_level);

	switch (in->mode) {
	case INIT_MODE_EK:
		low_level_init();
		trace_info_wp("\r\nApplet 'Low-Level' from softpack " SOFTPACK_VERSION ".\r\n");
		trace_info_wp("Low-Level initialization complete.\r\n");
		return APPLET_SUCCESS;

	case INIT_MODE_USER_CRYSTAL:
	case INIT_MODE_BYPASS:
	default:
		// unknown mode or not implemented
		return APPLET_FAIL;
	}
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INIT, handle_cmd_init },
	{ 0, NULL }
};
