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
 *  text on the console when console's baudrate is 38400 bps, the reason is:
 *  the value of UART_BRGR will be 12000000/38400/16 ~= 19.53, and the actual
 *  baudrate of console would be 12000000/20/16 = 37500, that has a gap of 2.4%
 *  to the desired one, so unreadable text may occur)
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
#include "board_console.h"
#include "chip.h"

#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "gpio/pio.h"

#include "led/led.h"
#include "serial/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_SOC_SAMA5D3
#define _PMC_PLLICPR_IPLL_PLLA PMC_PLLICPR_IPLL_PLLA(3)
#else
#define _PMC_PLLICPR_IPLL_PLLA 0
#endif

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct pck_mck_cfg clock_test_setting[] = {
	/* PCK = MCK = 12MHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = false,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#ifdef CONFIG_HAVE_PMC_PLLADIV2
		.plla_div2 = false,
#endif
#ifdef CONFIG_HAVE_PMC_UPLLDIV2
		.upll_div2 = false,
#endif
#ifdef CONFIG_HAVE_PMC_H32MXDIV
		.h32mx_div2 = false,
#endif
	},
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static volatile unsigned int MenuChoice;

static struct _pmc_plla_cfg plla_config = {
	.mul = 99,
	.div = 1,
	.count = 0x3f,
#ifdef CONFIG_DOC_SAMA5D3
	.icp = 3,
#endif
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for DBGU input.
 */
static void _console_handler(uint8_t c)
{
	MenuChoice = c;
}

static void _configure_console(void)
{
	board_cfg_console(38400);

	/* Initializing console interrupts */
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();
}

static void _print_menu(void)
{
	printf("\r\nSelect an option:\r\n"
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	       " ############################\n\r"
	       " 1 -> Disable AUDIOPLL\n\r"
	       " 2 -> AUDIOPLL 660 MHz\n\r"
	       " 3 -> AUDIOPLL 696 MHz\n\r"
	       " 4 -> AUDIOPLL 720 MHz\n\r"
	       " 5 -> AUDIOPLL 744 MHz\n\r"
#endif
	       " ############################\n\r"
	       " 6 -> Disable UPLL\n\r"
	       " 7 -> Enable  UPLL\n\r"
	       " ############################\n\r"
	       " 8 -> Disable PLLA\n\r"
	       " 9 -> PLLA =   408 MHz\n\r"
	       " 0 -> PLLA =   600 MHz\n\r"
	       " a -> PLLA =   792 MHz\n\r"
	       " b -> PLLA =   996 MHz\n\r"
	       " c -> PLLA =  1200 MHz\n\r"
	       " ############################\n\r"
	       "=>");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/* override default board_init */
void board_init(void)
{
	/* Configure low-level peripherals */
	board_cfg_lowlevel(true, false, false);

	/* Configure console */
	_configure_console();
}

/**
 *  \brief Application entry point for PLL consumption measurement.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	struct _pmc_audio_cfg audiopll_cfg;
#endif

	/* Output example information */
	console_example_info("PLL Consumption Measurement Example");

	/* Switch to main clock and reconfigure console */
	printf("Select main clock as MCK\r\n");
	while (!console_is_tx_empty());
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	_configure_console();

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
#ifdef CONFIG_HAVE_PMC_UPLL_BIAS
			pmc_disable_upll_bias();
#endif

			MenuChoice = 0;
			_print_menu();
			break;
		case '7':
			printf(" %c \r\n", MenuChoice);
			printf("Enable UPLL\r\n");

			/* enable UTMI CLK */
			pmc_enable_upll_clock();
#ifdef CONFIG_HAVE_PMC_UPLL_BIAS
			pmc_enable_upll_bias();
#endif

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

			plla_config.div = 1;
			plla_config.mul = (408 * 1000000 / BOARD_MAIN_CLOCK_EXT_OSC) - 1;
			pmc_configure_plla(&plla_config);

			MenuChoice = 0;
			_print_menu();
			break;
		case '0':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 600 MHz\r\n");

			plla_config.div = 1;
			plla_config.mul = (600 * 1000000 / BOARD_MAIN_CLOCK_EXT_OSC) - 1;
			pmc_configure_plla(&plla_config);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'a':
		case 'A':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 792 MHz\r\n");

			plla_config.div = 1;
			plla_config.mul = (792 * 1000000 / BOARD_MAIN_CLOCK_EXT_OSC) - 1;
			pmc_configure_plla(&plla_config);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'b':
		case 'B':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 996 MHz\r\n");

			plla_config.div = 1;
			plla_config.mul = (996 * 1000000 / BOARD_MAIN_CLOCK_EXT_OSC) - 1;
			pmc_configure_plla(&plla_config);

			MenuChoice = 0;
			_print_menu();
			break;
		case 'c':
		case 'C':
			printf(" %c \r\n", MenuChoice);
			printf("PLLA = 1200 MHz\r\n");

			plla_config.div = 1;
			plla_config.mul = (1200 * 1000000 / BOARD_MAIN_CLOCK_EXT_OSC) - 1;
			pmc_configure_plla(&plla_config);

			MenuChoice = 0;
			_print_menu();
			break;
		default:
			break;
		}
	}
}
