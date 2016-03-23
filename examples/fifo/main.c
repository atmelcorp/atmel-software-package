/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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
 * \page Usart FIFO Example
 *
 * \section Purpose
 *
 * The Usart FIFO example will help new users get familiar with Atmel's
 * SAMA5D2X family of microcontrollers. This basic application shows the
 * usage of Usart FIFO mode.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XPLAINED.
 *
 * \section Description
 *
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 57600 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *      -- Usart FIFO Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Connect the F3_TXD and F3_RXD pins of board to the serial of PC first;
 * -# Press the key listed in the menu to perform the corresponding action.
 * \section References
 * - fifo/main.c
 * - usart.h
 * - usart.c
 */

/** \file
 *
 *  This file contains all the specific code for the Usart FIFO example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"
#include "chip.h"
#include "compiler.h"

#include "peripherals/flexcom.h"
#include "peripherals/usart.h"
#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"

#include "misc/console.h"

#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *      Internal variables
----------------------------------------------------------------------------*/
Flexcom* flexcom = FLEXCOM3;
static const struct _pin usart_pins[] = PINS_FLEXCOM3_USART_IOS3;

ALIGNED(L1_CACHE_BYTES)
static const char test_data [] = "-- Write FIFO test PADDING PADDING PADDING \
PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING -- \r\n";

/** Usart Echo back ON/OFF */
static volatile uint8_t is_usart_echo_on = 0;

/**
 * console help dump
 */
static void _print_help(void)
{
	printf("-- ESC to Enable/Disable ECHO on Usart --\n\r");
	printf("-- Press 't' to send test data to Usart --\n\r");
}

/*----------------------------------------------------------------------------
 *  Interrupt handlers
 *----------------------------------------------------------------------------*/

/**
 * USART interrupt handler
 */
static void usart_handler(void)
{
	char read_buffer[33];
	uint32_t read = 0;
	*read_buffer = '\0';

	if (usart_is_rx_ready(&flexcom->usart)) {
		uint32_t size = usart_fifo_rx_size(&flexcom->usart);
		read = usart_read_stream(&flexcom->usart, read_buffer, size);
		read_buffer[read] = '\0';
	}
	flexcom->usart.US_CR = US_CR_RSTSTA;

	if(is_usart_echo_on) {
		usart_write_stream(&flexcom->usart, read_buffer, read);
	}
}

/**
 * Configure USART to work @ 115200 FIFO mode
 */
static void _configure_usart(void)
{
	pio_configure(usart_pins, ARRAY_SIZE(usart_pins));
	pmc_enable_peripheral(ID_USART3);

	aic_set_source_vector(ID_USART3, usart_handler);

	uint32_t mode = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT;

	flexcom_select(flexcom, FLEX_MR_OPMODE_USART);

	usart_configure(&flexcom->usart, mode, 115200);

	usart_fifo_configure(&flexcom->usart, 16u, 7u, 4u,
				US_FMR_RXRDYM_ONE_DATA | US_FMR_TXRDYM_FOUR_DATA);

	usart_enable_it(&flexcom->usart, US_IER_RXRDY);
	aic_enable(ID_USART3);
}


/**
 * Test Usart write
 */
static void _send_test_data(void)
{
	usart_write_stream(&flexcom->usart, test_data, sizeof(test_data));
}

/*----------------------------------------------------------------------------
 *          Main
 *----------------------------------------------------------------------------*/

/**
 * \brief Usart FIFO Application entry point.
 *
 * Initializes drivers and start the Usart Serial .
 */
int main (void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	board_cfg_console();

	/* Enable DDRAM */
#ifndef VARIANT_DDRAM
	board_cfg_ddram();
#endif

	printf("-- Usart FIFO Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	_configure_usart();

	/* Help informaiton */
	_print_help();

	while (1) {
		if (console_is_rx_ready()) {

			uint8_t key = console_get_char();
			/* ESC: Usart Echo ON/OFF */
			if (key == 27) {
				printf("** USART Echo %s\n\r",
						is_usart_echo_on ? "OFF" : "ON");
				is_usart_echo_on = !is_usart_echo_on;

			} else if (key == 't') {
				/* 't': Test Usart writing  */
				_send_test_data();

			} else {
				printf("Alive\n\r");
				usart_write_stream(&flexcom->usart, (char*)"Alive\n\r", 8);
			}
		}
	}
}
