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
#include "applet.h"
#include "trace.h"
#include "peripherals/pio.h"
#include "peripherals/sfc.h"
#include "misc/console.h"

#include <string.h>

extern int __buffer_start__;
extern int __buffer_end__;

static bool _console_initialized;
static uint32_t _comm_type;
uint8_t *applet_buffer;
uint32_t applet_buffer_size;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_SOC_SAMA5D2)

struct _console_cfg {
	void* addr;
	const struct _pin pins[2];
};

/**
 * \brief Initialize console for SAMA5D2
 * Chooses the UART and IOSET by reading the boot config in Fuses or BSCR.
 * Baudrate is 57600.
 */
static void initialize_console(void)
{
	const struct _console_cfg console_cfg[] = {
		{ UART1, PINS_UART1_IOS1 },
		{ UART0, PINS_UART0_IOS1 },
		{ UART1, PINS_UART1_IOS2 },
		{ UART2, PINS_UART2_IOS1 },
		{ UART2, PINS_UART2_IOS2 },
		{ UART2, PINS_UART2_IOS3 },
		{ UART3, PINS_UART3_IOS1 },
		{ UART3, PINS_UART3_IOS2 },
		{ UART3, PINS_UART3_IOS3 },
		{ UART4, PINS_UART4_IOS1 },
	};
	uint32_t bcw;
	uint32_t baudrate;
	uint32_t console;

	/* read boot config word from fuse */
	bcw = sfc_read(16);

	/* if BSCR is not disabled and BUREG index is valid, use BUREG */
	if ((bcw & BCW_DISABLE_BSCR) == 0) {
		uint32_t bsc_cr = BSC->BSC_CR;
		if (bsc_cr & BSC_CR_BUREG_VALID) {
			uint32_t index = (bsc_cr & BSC_CR_BUREG_INDEX_Msk) >> BSC_CR_BUREG_INDEX_Pos;
			bcw = SECURAM->BUREG_256b[index];
		}
	}

	/* if ROM-code is v1.0, use 57600 baudrate */
	baudrate = 115200;
	if (!memcmp((const char*)0x210000, "v1.0", 5))
		baudrate = 57600;

	/* configure console */
	console = (bcw & BCW_UART_CONSOLE_Msk) >> BCW_UART_CONSOLE_Pos;
	pio_configure(console_cfg[console].pins, 2);
	console_configure(console_cfg[console].addr, baudrate);
}

#elif defined(CONFIG_SOC_SAMA5D4)

/**
 * \brief Initialize console for SAMA5D4
 * Always USART3, baudrate is 115200.
 */
static void initialize_console(void)
{
	const struct _pin console_pins[] = { PIN_USART3_TXD, PIN_USART3_RXD };
	pio_configure(console_pins, 2);
	console_configure(USART3, 115200);
}

#else

#error Unsupported SoC!

#endif

static void init_applet_buffer(void)
{
	applet_buffer = (uint8_t*)&__buffer_start__;
	applet_buffer_size = (uint32_t)&__buffer_end__ - (uint32_t)&__buffer_start__;
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

void applet_set_init_params(uint32_t comm, uint32_t trace)
{
	_comm_type = comm;
	trace_level = trace;
}

/**
 * \brief  Applet main entry. This function decodes received command and
 * executes it.
 * \param mailbox  Applet mailbox
 */
void applet_main(struct applet_mailbox *mailbox)
{
	int i;

	/* set default status */
	mailbox->status = APPLET_FAIL;

	if (!_console_initialized) {
		initialize_console();
		_console_initialized = true;
	}

	if (!applet_buffer) {
		init_applet_buffer();
	}

	/* look for handler and call it */
	for (i = 0; applet_commands[i].handler; i++) {
		if (applet_commands[i].command == mailbox->command)
		{
			mailbox->status = applet_commands[i].handler(
					mailbox->command, mailbox->data);
			break;
		}
	}
	if (!applet_commands[i].handler) {
		trace_error_wp("Unsupported applet command 0x%08x\r\n",
				(unsigned)mailbox->command);
	}

	/* notify the host application of the end of the command processing */
	mailbox->command = ~(mailbox->command);

	/* send ACK character if comm type is DBGU */
	if (_comm_type == COMM_TYPE_DBGU)
		console_put_char(0x06);
}
