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

#include <string.h>

#include "applet.h"
#include "applet_legacy.h"
#include "board.h"
#include "board_timer.h"
#include "chip.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "nvm/sfc.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "timer.h"
#include "trace.h"

/* define this to enable debug display of mailbox content */
#undef APPLET_MAILBOX_DEBUG

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

static void debug_display_mailbox(struct applet_mailbox *mailbox)
{
#ifdef APPLET_MAILBOX_DEBUG
	int i;
	trace_debug_wp("--------\r\n");
	trace_debug_wp("TICK=0x%08x\r\n", (unsigned)timer_get_tick());
	trace_debug_wp("CMD=0x%08x\r\n", (unsigned)mailbox->command);
	trace_debug_wp("STATUS=0x%08x\r\n", (unsigned)mailbox->status);
	for (i = 0; i < 16; i++)
		trace_debug_wp("[%02d]=0x%08x%s", i, (unsigned)mailbox->data[i], (i & 3) == 3 ? "\r\n" : " ");
#endif
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

void applet_set_init_params(uint32_t comm, uint32_t trace)
{
	_comm_type = comm;

	/* If we are communicating using the console UART, the applet */
	/* cannot display any trace. We still need to configure the */
	/* console subsystem to send the acknowledge byte ater command */
	/* execution. */
	trace_level = _comm_type == COMM_TYPE_DBGU ? 0 : trace;
	board_cfg_console(0);
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
		/* Applet buffer is not set, this is the first call to the applet */
		/* Let's do some setup */
		init_applet_buffer();
		pmc_set_main_oscillator_freq(BOARD_MAIN_CLOCK_EXT_OSC);
		board_cfg_timer();
		dma_initialize(true);
	}

	/* display mailbox content before command processing */
	debug_display_mailbox(mailbox);

	/* set default status */
	mailbox->status = APPLET_FAIL;

	/* look for handler and call it */
	handler = get_applet_command_handler(mailbox->command);
	if (handler) {
		if (mailbox->command == APPLET_CMD_INITIALIZE) {
			mailbox->status = handler(mailbox->command, mailbox->data);
			applet_initialized = (mailbox->status == APPLET_SUCCESS);
		} else if (applet_initialized) {
			mailbox->status = handler(mailbox->command, mailbox->data);
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

	/* display mailbox content after command processing */
	debug_display_mailbox(mailbox);

	/* notify the host application of the end of the command processing */
	mailbox->command = ~(mailbox->command);

	/* send ACK character if comm type is DBGU */
	if (_comm_type == COMM_TYPE_DBGU)
		console_put_char(0x06);
}
