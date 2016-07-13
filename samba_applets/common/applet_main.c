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

#include "chip.h"
#include "board.h"
#include "applet.h"
#include "applet_legacy.h"
#include "trace.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/sfc.h"
#include "misc/console.h"

#include <string.h>

extern int __buffer_end__;
#if defined(__GNUC__)
extern int __buffer_start__;
#endif

static bool applet_initialized = false;
static uint32_t _comm_type;

uint8_t *applet_buffer;
uint32_t applet_buffer_size;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void init_applet_buffer(void)
{
#if defined(__ICCARM__)
	/* Rely on the fact that CSTACK is the last section in RAM region */
	#pragma section = "CSTACK"
	applet_buffer = __section_end("CSTACK");
#elif defined(__GNUC__)
	applet_buffer = (uint8_t*)&__buffer_start__;
#else
#error Unknown compiler!
#endif
	applet_buffer_size = (uint32_t)&__buffer_end__ - (uint32_t)applet_buffer;
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

void applet_set_init_params(uint32_t comm, uint32_t trace)
{
	_comm_type = comm;

	if (_comm_type  != COMM_TYPE_DBGU) {
		trace_level = trace;
		board_cfg_console(0);
	} else {
		/* We are communicating using the console UART so the applet */
		/* cannot display any trace */
		trace_level = 0;
	}

}

applet_command_handler_t get_applet_command_handler(uint8_t cmd)
{
	int i;
	for (i = 0; applet_commands[i].handler; i++)
		if (applet_commands[i].command == cmd)
			return applet_commands[i].handler;
	return NULL;
}

/**
 * \brief  Applet main entry. This function decodes received command and
 * executes it.
 * \param mailbox  Applet mailbox
 */
void applet_main(struct applet_mailbox *mailbox)
{
	applet_command_handler_t handler;

	if (!applet_buffer) {
		init_applet_buffer();
	}

	pmc_set_oscillators(BOARD_SLOW_CLOCK_EXT_OSC, BOARD_MAIN_CLOCK_EXT_OSC);

	/* set default status */
	mailbox->status = APPLET_FAIL;

	/* look for handler and call it */
	handler = get_applet_command_handler(mailbox->command);
	if (handler) {
		if (applet_initialized) {
			mailbox->status = handler(mailbox->command, mailbox->data);
		} else if (mailbox->command == APPLET_CMD_INITIALIZE) {
			mailbox->status = handler(mailbox->command, mailbox->data);
			applet_initialized = (mailbox->status == APPLET_SUCCESS);
		} else {
			trace_error_wp("Applet not initialized!\r\n");
		}
	} else if (applet_is_legacy_command(mailbox->command)) {
		if (applet_initialized) {
			mailbox->status = applet_emulate_legacy_command(
					mailbox->command, mailbox->data);
		} else {
			trace_error_wp("Applet not initialized!\r\n");
		}
	} else {
		trace_error_wp("Unsupported applet command 0x%08x\r\n",
				(unsigned)mailbox->command);
	}

	/* notify the host application of the end of the command processing */
	mailbox->command = ~(mailbox->command);

	/* send ACK character if comm type is DBGU */
	if (_comm_type == COMM_TYPE_DBGU)
		console_put_char(0x06);
}
