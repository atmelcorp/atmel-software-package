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

/*
 * shows how to switch from a clock to another (PLLA,
 * PLLUTMI, SLCK, MCK) or change divider. Shows how
 * to change SLCK (32K OSC or internal RC)
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

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------
 */

struct pck_mck_cfg clock_test_setting[4] = {
	/* PLLA = 996, PCK = 498, MCK = 166 MHz */
	/* PLLA EXT12M EXT32K MULA=83 DIV2ON=1 PRES=0 MDIV=3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 82,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.h32mxdiv2 = true,
	},
	/* PCK = UPLL, MCK = UPLL/3 */
	/* UPLL EXT12M EXT32K MULA=0 DIV2ON=0 PRES=0 MDIV=3 */
	{
		.pck_input = PMC_MCKR_CSS_UPLL_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.h32mxdiv2 = true,
	},
	/* PCK = MCK = 12MHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 32 kHz */
	/* slow clock EXT12M EXT32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
};

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
static void _console_handler(void)
{
	if (!console_is_rx_ready())
		return;
	MenuChoice = console_get_char();
}

static void _restore_console(void)
{
	console_configure(CONSOLE_BAUDRATE);

	/* Initializing console interrupts */
	aic_set_source_vector(CONSOLE_ID, _console_handler);
	aic_enable(CONSOLE_ID);
	console_enable_interrupts(US_IER_RXRDY);
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

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

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
