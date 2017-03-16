/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

/**
 *  \page pmc_clock_switching PMC Clock Switching Example
 *
 *  \section Purpose
 * This examples shows how to switch from a clock to another (PLLA,
 * PLLUTMI, SLCK, MCK) or change divider, also shows how
 * to change SLCK (32K OSC or internal RC)
 *
 *  \section Requirements
 *  This package can be used with SAMA5D2-XULT.
 *
 *  \section Note
 *  Using some frequency of peripheral clock would cause unreadable text on the
 *  console. (e.g. when console's target baudrate is 38400 bps and peripheral
 *  clock is 12MHz: the value of UART_BRGR will be 12000000/38400/16 ~= 19.53,
 *  and the actual baudrate of console would be 12000000/20/16 = 37500, that has
 *  a gap of 2.4% to the desired one, so unreadable text may occur)
 *
 *  \section Usage
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear (values depend on
 *     the board and chip used):
 *     \code
 *      -- Clock switching Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      MCK = 166 Mhz
 *      PLLA = 498 Mhz
 *      Processor clock = 498 Mhz
 *      Select an option :
 *      ###############################
 *      1 -> Switch to PLLA
 *      2 -> Switch to UPLL
 *      3 -> Switch to main clock
 *      4 -> Switch to slow clock
 *      -------------------------------
 *      =>
 *     \endcode
 *
 *  \section References
 *  - pmc_clock_switching/main.c
 *  - pio.h
 *  - pio_it.h

 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_console.h"
#include "chip.h"

#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "gpio/pio.h"
#include "serial/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "clk-config.h"

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

volatile uint8_t MenuChoice;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _console_handler(uint8_t c)
{
	MenuChoice = c;
}

static void _configure_console(void)
{
	/* reconfigure console */
	board_cfg_console(38400);

	/* Initialize console interrupts */
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();
}

static void _set_clock_setting(int index)
{
	while (!console_is_tx_empty());
	pmc_set_custom_pck_mck(&clock_test_setting[index]);
	_configure_console();
}

static void _print_clocks(void)
{
	printf("MCK = %d Mhz\r\n", (unsigned)(pmc_get_master_clock() / 1000000));
	printf("PLLA = %d Mhz\r\n", (unsigned)(pmc_get_plla_clock() / 1000000));
	printf("Processor clock = %d Mhz\r\n", (unsigned)(pmc_get_processor_clock() / 1000000));
}

static void _print_menu(void)
{
	printf("Select an option :\n\r"
	       "###############################\n\r"
	       "1 -> Switch to PLLA\n\r"
	       "2 -> Switch to UPLL\n\r"
	       "3 -> Switch to main clock\n\r"
	       "4 -> Switch to slow clock\n\r"
	       "-------------------------------\n\r"
	       "=>");
}

static void _wait_busyloop(int loops)
{
	volatile unsigned int delay;
	for (delay = 0; delay < loops; delay++);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/* override default board_init */
void board_init(void)
{
	/* Configure low-level peripherals */
	board_cfg_lowlevel(true, false, false);

	_configure_console();
}

/**
 *  \brief Application entry point for clock switching.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Output example information */
	console_example_info("Clock Switching Example");

	/* -------- Enable UTMI CLK ---------------------- */
	pmc_enable_upll_clock();
#ifdef CONFIG_HAVE_PMC_UPLL_BIAS
	pmc_enable_upll_bias();
#endif

	_print_clocks();
	_print_menu();
	MenuChoice = 0;
	while (1) {
		switch (MenuChoice) {
		case '1':
			printf(" %c\r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to PLLA\r\n");

			_set_clock_setting(0);
			_print_clocks();
			_print_menu();
			break;
		case '2':
			printf(" %c\r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to UPLL\r\n");

			_set_clock_setting(1);
			_print_clocks();
			_print_menu();
			break;
		case '3':
			printf(" %c\r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to main clock\r\n");

			_set_clock_setting(2);
			_print_clocks();
			_print_menu();
			break;
		case '4':
			printf(" %c\r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to slow clock\r\n");
			printf("It is too slow to output info on serial port\r\n");
			printf("So stay at this speed for a moment only\r\n");

			_set_clock_setting(3);
			_wait_busyloop(1000);
			_set_clock_setting(0);

			printf("Back to PLLA\r\n");
			_print_clocks();
			_print_menu();
			break;
		default:
			break;
		}
	}
}
