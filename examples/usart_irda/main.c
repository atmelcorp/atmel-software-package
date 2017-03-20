/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 *  \page irda IrDA Example
 *
 *  \section Purpose
 *  This application gives an example of how to use USART in IrDA mode.
 *
 *  \section Requirements
 *  To run this example 2 kits are needed, one acts as a transmitter and the
 *  other acts as a receiver. And the infrared modules should keep face to face.
 *  This example can be used on SAMA5D2x Xplained board with a Fieldbus shield.
 *  Setting of jumpers on Fieldbus shield board:
 *  - Keep JP24 and JP25 open
 *  - Short 1&2, 3&4, 5&6 of J11
 *  \section Description
 *
 *  \section Usage
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">SAM-BA User Guide</a>,
 *     the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">GNU-Based Software Development</a>
 *     application note or to the <a href="http://www.iar.com/website1/1.0.1.0/78/1/">IAR EWARM User and reference guides</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application (e.g.
 *     HyperTerminal on Microsoft Windows) with these settings:
 *        - 115200 bauds
 *        - 8 data bits
 *        - No parity
 *        - 1 stop bit
 *        - No flow control
 *  -# Start the application. The following traces shall appear on the terminal:
 *     \code
 *      -- IrDA Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      Menu:
 *        t - transmit data throught IrDA
 *        r - receive data from IrDA
 *     \endcode
 *
 *   \section References
 *  - irda/main.c
 *  - pio.h
 *  - usart.h
 *
 */

/** \file
 *
 *  This file contains all the specific code for the IrDA example.
 *
 */


/*------------------------------------------------------------------------------
 *          Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "timer.h"

#include "irq/irq.h"
#include "gpio/pio.h"
#include "serial/usartd.h"
#include "serial/usart.h"

#include "serial/console.h"


#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Internal definitions
 *------------------------------------------------------------------------------*/

/** define the peripherals and pins used for IrDA */
#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#define IRDA_USART FLEXUSART3
#define IRDA_PINS  PINS_FLEXCOM3_USART_IOS3

#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#define IRDA_USART USART4
#define IRDA_PINS  PINS_USART4

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#define IRDA_USART USART4
#define IRDA_PINS  PINS_USART4

#elif defined(CONFIG_BOARD_SAM9G15_EK)
#define IRDA_USART USART0
#define IRDA_PINS  PINS_USART0

#elif defined(CONFIG_BOARD_SAM9G25_EK)
#define IRDA_USART USART0
#define IRDA_PINS  PINS_USART0

#elif defined(CONFIG_BOARD_SAM9G35_EK)
#define IRDA_USART USART0
#define IRDA_PINS  PINS_USART0

#elif defined(CONFIG_BOARD_SAM9X25_EK)
#define IRDA_USART USART0
#define IRDA_PINS  PINS_USART0

#elif defined(CONFIG_BOARD_SAM9X35_EK)
#define IRDA_USART USART0
#define IRDA_PINS  PINS_USART0

#else
#error Unsupported SoC!
#endif

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** define pins for IrDA TX & RX */
static const struct _pin pins_irda[] = IRDA_PINS;

/** define descriptor for IrDA */
static struct _usart_desc irda_desc = {
	.addr           = IRDA_USART,
	.baudrate       = 57600,
	.mode           = US_MR_USART_MODE_IRDA | US_MR_CHMODE_NORMAL |
	                  US_MR_PAR_NO | US_MR_CHRL_8_BIT |
	                  US_MR_NBSTOP_1_BIT,
	.transfer_mode = USARTD_MODE_POLLING,
};

/** define receive/transmit status for IrDA */
static bool receiving = false;

/** Transmit buffer. */
static char buffer_tx[] =
"\n\r\
**************************************************************************\n\r\
* This application gives an example of how to use USART in IrDA mode.\n\r\
* The USART features an IrDA mode supplying half-duplex point-to-point \n\r\
* wireless communication. It embeds the modulator and demodulator which \n\r\
* allows a glueless connection to the infrared transceivers. The modulator\n\r\
* and demodulator are compliant with the IrDA specification version 1.1 and\n\r\
* support data transfer speeds ranging from 2.4 kbit/s to 115.2 kbit/s. \n\r\
* \n\r\
* Note that the modulator and the demodulator are activated.\n\r\
**************************************************************************\n\r";

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 *  \brief Update receive/transmit status for IrDA.
 */
static void _update_irda_status(bool is_receiving)
{
	if (is_receiving) {
		printf("\n\rData received from IrDA will be printed bellow...\n\r");
		usart_set_receiver_enabled(IRDA_USART, 1u);
		usart_set_transmitter_enabled(IRDA_USART, 0u);
		pio_clear(&pins_irda[0]);
	} else {
		printf("\n\rTransmitting data throuth IrDA...\n\r");
		usart_set_receiver_enabled(IRDA_USART, 0u);
		usart_set_transmitter_enabled(IRDA_USART, 1u);
	}
}

/**
 *  \brief Handler for DBGU input.
 */
static void console_handler(uint8_t key)
{
	if (key == 't' || key == 'T') {
		_update_irda_status(0);
		receiving = false;
	} else if (key == 'r' || key == 'R') {
		_update_irda_status(1);
		receiving = true;
	}
}

/**
 *  \brief Handler for IrDA
 */
static void irda_irq_handler(uint32_t source, void* user_arg)
{
	if (usart_is_rx_ready(IRDA_USART))
		printf("%c", usart_get_char(IRDA_USART));
}

/**
 *  \brief initialize IrDA interface
 */
static void irda_interface_init(void)
{
	uint32_t id = get_usart_id_from_addr(IRDA_USART);
	pio_configure(&pins_irda[0], ARRAY_SIZE(pins_irda));
	usartd_configure(0, &irda_desc);
	irq_add_handler(id, irda_irq_handler, NULL);
	usart_enable_it(IRDA_USART, US_IER_RXRDY);
	usart_set_irda_filter(IRDA_USART, 100);
	irq_enable(id);
}

static int irda_finish_tx_transfer_callback(void* arg, void* arg2)
{
	usartd_finish_tx_transfer(0);
	return 0;
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 *  \brief IrDA Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	/* Output example information */
	console_example_info("IrDA Example");

	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	printf("Initializing IrDA interface\n\r");
	irda_interface_init();
	printf("IrDA interface initialized.\n\r");

	printf("\n\rMenu:\n\r");
	printf("  t - transmit data throught IrDA\n\r");
	printf("  r - receive data from IrDA\n\r");

	_update_irda_status(receiving);

	while(1){
		if (!receiving) {
			struct _buffer tx = {
				.data = (unsigned char*)buffer_tx,
				.size = sizeof(buffer_tx),
				.attr = USARTD_BUF_ATTR_WRITE,
			};
			struct _callback _cb = {
				.method = irda_finish_tx_transfer_callback,
				.arg = 0,
			};
			usartd_transfer(0, &tx, &_cb);
			msleep(200);
		}
	}
}
