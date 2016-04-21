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
 *  \page power_consumption_pll Power Consumption PLL Example
 *
 *  \section Purpose
 *  The demonstration program offers methods to change the settings of Audio PLL,
 *  UPLL and PLLA.
 *  Power consumptions could be measured by ammeters connected between the
 *  jumpers of VDDCORE or VDDBU.
 *
 *  \section Requirements
 *  This package can be used with SAMA5D2-XULT.
 *
 *  \section Note
 *  The default peripheral clock is 12MHz, and there might be some unreadable
 *  code on the console when console's baudrate is 115200 bps, the reason is:
 *  the value of UART_BRGR will be 12000000/115200/16 = 6, and the actual
 *  baudrate of console would be 12000000/6/16 = 125000, that has a gap of 8.5%
 *  to the desired one, so the unreadable code occurs)
 *  User can change the clock by replacing clock_test_setting[1] to
 *  clock_test_setting[0] in the main routine to avoid unreadable code.
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
 *      -- PLL consumption measurement xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      Select main clock as MCK
 *      Select an option :
 *      ############################
 *      1 -> Disable AUDIOPLL
 *      2 -> AUDIOPLL 660 MHz
 *      3 -> AUDIOPLL 696 MHz
 *      4 -> AUDIOPLL 720 MHz
 *      5 -> AUDIOPLL 744 MHz
 *      ############################
 *      6 -> Disable UPLL
 *      7 -> Enable  UPLL
 *      ############################
 *      8 -> Disable PLLA
 *      9 -> PLLA =   408 MHz
 *      0 -> PLLA =   600 MHz
 *      a -> PLLA =   792 MHz
 *      b -> PLLA =   996 MHz
 *      c -> PLLA =  1200 MHz
 *      ############################
 *      =>
 *     \endcode
 *
 *  \section References
 *  - power_consumption_pll/main.c
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
#include "peripherals/twid.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"

#include "misc/led.h"
#include "power/act8945a.h"
#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

struct pck_mck_cfg clock_test_setting[] = {
	/* PLL A = 996, PCK = 498, MCK = 166 MHz */
	/* PLLA RC12M RC32K MULA=83 DIV2ON=1 PRES=0  MDIV=3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 82,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.h32mxdiv2 = true,
	},
	/* PCK = MCK = 12MHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 750 kHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=16 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV16,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 187.5 kHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=64 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 32 kHz */
	/* slow clock RC12M RC32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 512 Hz */
	/* slow clock RC12M RC32K MULA=0 DIV2ON=0 PRES=64 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 12MHz */
	/* MAIN RC12M EXT32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
};

#define MENU_NB_OPTIONS      17
#define MENU_STRING_LENGTH   200
char menu_choice_msg[MENU_NB_OPTIONS][MENU_STRING_LENGTH] = {
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	" ############################\n\r",
	" 1 -> Disable AUDIOPLL\n\r",
	" 2 -> AUDIOPLL 660 MHz\n\r",
	" 3 -> AUDIOPLL 696 MHz\n\r",
	" 4 -> AUDIOPLL 720 MHz\n\r",
	" 5 -> AUDIOPLL 744 MHz\n\r",
#endif
	" ############################\n\r",
	" 6 -> Disable UPLL\n\r",
	" 7 -> Enable  UPLL\n\r",
	" ############################\n\r",
	" 8 -> Disable PLLA\n\r",
	" 9 -> PLLA =   408 MHz\n\r",
	" 0 -> PLLA =   600 MHz\n\r",
	" a -> PLLA =   792 MHz\n\r",
	" b -> PLLA =   996 MHz\n\r",
	" c -> PLLA =  1200 MHz\n\r",
	" ############################\n\r"};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------
 */

unsigned char use_clock_setting = 0;

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
	board_cfg_console();

	/* Initializing console interrupts */
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();
}

/* ---------------------------------------------------------------------------
 * Function Name       : _print_menu
 * Object              :
 * ---------------------------------------------------------------------------
 */
static void _print_menu(void)
{
	int i;

	printf("\r\nSelect an option :\r\n");

	for (i = 0; i < MENU_NB_OPTIONS; ++i)
		printf(menu_choice_msg[i]);

	printf("=>");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Application entry point for PLL consumption measurement.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main(void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console();

	/* Output example information */
	printf("-- PLL consumption measurement %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	printf("Select main clock as MCK\r\n");
	pmc_set_custom_pck_mck(&clock_test_setting[1]);

	/* Initialize console */
	_restore_console();

#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	struct _pmc_audio_cfg audiopll_cfg;
#endif

	_print_menu();
	MenuChoice = 0;
	while (1) {
		switch (MenuChoice) {
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
		case '1':
			printf(" %c \r\n", MenuChoice);
			printf("Disable AUDIOPLL\r\n");

			pmc_disable_audio();

			MenuChoice = 0;
			_print_menu();
			break;
		case '2':
			printf(" %c \r\n", MenuChoice);
			/* f_pmc 24~125MHz f_audio 8~48MHz f_vc0 650_750MHz */
			printf("f_vco = 660 MHz, f_pmc = f_vco/7\r\n");

			/* first disable audio pll */
			pmc_disable_audio();
			/* config audio pll */
			audiopll_cfg.qdpmc = (7 - 1);
			audiopll_cfg.nd = (55 - 1);
			audiopll_cfg.fracr = (0);
			audiopll_cfg.qdaudio = (28);
			audiopll_cfg.div = (0x2);
			pmc_configure_audio(&audiopll_cfg);
			/* Enable audio pll, PMC, but not PADCLK */
			pmc_enable_audio(1, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case '3':
			printf(" %c \r\n", MenuChoice);
			/* f_pmc 24~125MHz f_audio 8~48MHz f_vc0 650_750MHz */
			printf("f_vco = 696 MHz, f_pmc = f_vco/7\r\n");

			/* first disable audio pll */
			pmc_disable_audio();
			/* config audio pll */
			audiopll_cfg.qdpmc = (7 - 1);
			audiopll_cfg.nd = (58 - 1);
			audiopll_cfg.fracr = (0);
			audiopll_cfg.qdaudio = (28);
			audiopll_cfg.div = (0x2);
			pmc_configure_audio(&audiopll_cfg);
			/* Enable audio pll, PMC, but not PADCLK */
			pmc_enable_audio(1, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case '4':
			printf(" %c \r\n", MenuChoice);
			/* f_pmc 24~125MHz f_audio 8~48MHz f_vc0 650_750MHz */
			printf("f_vco = 720 MHz, f_pmc = f_vco/7\r\n");

			/* first disable audio pll */
			pmc_disable_audio();
			/* config audio pll */
			audiopll_cfg.qdpmc = (7 - 1);
			audiopll_cfg.nd = (60 - 1);
			audiopll_cfg.fracr = (0);
			audiopll_cfg.qdaudio = (28);
			audiopll_cfg.div = (0x2);
			pmc_configure_audio(&audiopll_cfg);
			/* Enable audio pll, PMC, but not PADCLK */
			pmc_enable_audio(1, 0);

			MenuChoice = 0;
			_print_menu();
			break;

		case '5':
			printf(" %c \r\n", MenuChoice);
			/* f_pmc 24~125MHz f_audio 8~48MHz f_vc0 650_750MHz */
			printf("f_vco = 744 MHz, f_pmc = f_vco/7\r\n");

			/* first disable audio pll */
			pmc_disable_audio();
			/* config audio pll */
			audiopll_cfg.qdpmc = (7 - 1);
			audiopll_cfg.nd = (62 - 1);
			audiopll_cfg.fracr = (0);
			audiopll_cfg.qdaudio = (28);
			audiopll_cfg.div = (0x2);
			pmc_configure_audio(&audiopll_cfg);
			/* Enable audio pll, PMC, but not PADCLK */
			pmc_enable_audio(1, 0);

			MenuChoice = 0;
			_print_menu();
			break;
#endif

		case '6':
			printf(" %c \r\n", MenuChoice);
			printf("Disable UPLL\r\n");

			/* disable UTMI CLK */
			pmc_disable_upll_clock();
			pmc_disable_upll_bias();

			MenuChoice = 0;
			_print_menu();
			break;
		case '7':
			printf(" %c \r\n", MenuChoice);
			printf("Enable UPLL\r\n");

			/* enable UTMI CLK */
			pmc_enable_upll_clock();
			pmc_enable_upll_bias();

			MenuChoice = 0;
			_print_menu();
			break;
		case '8':
			printf(" %c \r\n", MenuChoice);
			printf("Disable PLLA\r\n");

			pmc_disable_plla();

			MenuChoice = 0;
			_print_menu();
			break;
		case '9':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 408 MHz\r\n");

			pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
				CKGR_PLLAR_OUTA(0x0) |
				CKGR_PLLAR_DIVA(1)   |
				CKGR_PLLAR_MULA(33)  |
				CKGR_PLLAR_DIVA_BYPASS, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case '0':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 600 MHz\r\n");

			pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
				CKGR_PLLAR_OUTA(0x0) |
				CKGR_PLLAR_DIVA(1)   |
				CKGR_PLLAR_MULA(49)  |
				CKGR_PLLAR_DIVA_BYPASS, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'a':
		case 'A':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 792 MHz\r\n");

			pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
				CKGR_PLLAR_OUTA(0x0) |
				CKGR_PLLAR_DIVA(1)   |
				CKGR_PLLAR_MULA(65)  |
				CKGR_PLLAR_DIVA_BYPASS, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'b':
		case 'B':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 996 MHz\r\n");

			pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
				CKGR_PLLAR_OUTA(0x0) |
				CKGR_PLLAR_DIVA(1)   |
				CKGR_PLLAR_MULA(82)  |
				CKGR_PLLAR_DIVA_BYPASS, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'c':
		case 'C':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 1200 MHz\r\n");

			pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
				CKGR_PLLAR_OUTA(0x0) |
				CKGR_PLLAR_DIVA(1)   |
				CKGR_PLLAR_MULA(99)  |
				CKGR_PLLAR_DIVA_BYPASS, 0);

			MenuChoice = 0;
			_print_menu();
			break;
		default:
			break;
		}
	}
}
