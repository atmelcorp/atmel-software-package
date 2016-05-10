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
 *  Using some frequency of peripheral clock would cause unreadable code on the
 *  console. (e.g. when console's target baudrate is 115200 bps, peripheral clock
 *  is 12MHz: the value of UART_BRGR will be 12000000/115200/16 = 6, and the
 *  actual baudrate of console would be 12000000/6/16 = 125000, that has a gap
 *  of 8.5% to the desired one, so the unreadable code occurs)
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
 *----------------------------------------------------------------------------
 */

#include "board.h"
#include "chip.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "clk-config.h"

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------
 */

#define MENU_STRING_LENGTH   200
#define MENU_NB_OPTIONS      8
char menu_choice_msg[MENU_NB_OPTIONS][MENU_STRING_LENGTH] = {
	"###############################\n\r",
	"1 -> Switch to PLLA\n\r",
	"2 -> Switch to UPLL\n\r",
	"3 -> Switch to main clock\n\r",
	"4 -> Switch to slow clock\n\r",
	"-------------------------------\n\r"};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------
 */

volatile unsigned int MenuChoice;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Handler for DBGU input.
 */
static void _console_handler(uint8_t c)
{
	MenuChoice = c;
}

static void _restore_console(void)
{
	board_cfg_console(0);

	/* Initializing console interrupts */
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();
}

/* ---------------------------------------------------------------------------
 * Function Name       : _print_clocks
 * Object              :
 * ---------------------------------------------------------------------------
 */
static void _print_clocks(void)
{
	printf("MCK = %d Mhz\r\n", (unsigned)(pmc_get_master_clock() / 1000000));
	printf("PLLA = %d Mhz\r\n", (unsigned)(pmc_get_plla_clock() / 1000000));
	printf("Processor clock = %d Mhz\r\n", (unsigned)(pmc_get_processor_clock() / 1000000));
}

/* ---------------------------------------------------------------------------
 * Function Name       : _print_menu
 * Object              :
 * ---------------------------------------------------------------------------
 */
static void _print_menu(void)
{
	int i;

	printf("Select an option :\n\r");

	for (i = 0; i < MENU_NB_OPTIONS; ++i)
		printf(menu_choice_msg[i]);

	printf("=>");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Application entry point for clock switching.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	volatile unsigned int delay;

	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console(0);

	/* To align display */
	printf("\r\n");

	/* Output example information */
	printf("-- Clock switching example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	_restore_console();

	/* -------- Enable UTMI CLK ---------------------- */
	pmc_enable_upll_clock();
	pmc_enable_upll_bias();

	_print_clocks();
	_print_menu();
	MenuChoice = 0;
	while (1) {
		switch (MenuChoice) {
		case '1':
			printf(" %c \r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to PLLA\r\n");
			pmc_set_custom_pck_mck(&clock_test_setting[0]);
			_restore_console();
			_print_clocks();
			_print_menu();
			break;
		case '2':
			printf(" %c \r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to UPLL\r\n");
			pmc_set_custom_pck_mck(&clock_test_setting[1]);
			_restore_console();
			_print_clocks();
			_print_menu();
			break;
		case '3':
			printf(" %c \r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to main clock\r\n");
			pmc_set_custom_pck_mck(&clock_test_setting[2]);
			_restore_console();
			_print_clocks();
			_print_menu();
			break;
		case '4':
			printf(" %c \r\n", MenuChoice);
			MenuChoice = 0;

			printf("Switch to slow clock\r\n");
			printf("It is too slow to output info on serial port\r\n");
			printf("So stay at this speed for a moment only\r\n");
			for (delay = 0; delay < 1000; delay++);
			pmc_set_custom_pck_mck(&clock_test_setting[3]);

			for (delay = 0; delay < 1000; delay++);
			pmc_set_custom_pck_mck(&clock_test_setting[0]);
			_restore_console();
			printf("Go back to fast clock and continue\r\n");
			_print_clocks();
			_print_menu();
			break;
		default:
			break;
		}
	}
}
