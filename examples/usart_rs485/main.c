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

/** *  \page usart_rs485 USART RS485 Example
 *
 *  \section Purpose
 *
 *  The USART RS485 Example demonstrates how to use USART in RS485 mode.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5Dx/SAME70/SAMV71 board. Before running, make sure to connect
 *  two boards with RS485 lines. The rs485 adapt board(ADM3485ARZ) for this purpose.
 *  Match each paired pins of two boards respectively with A to A,
 *  B to B and FGND to FGND(the central pin of J3).
 *  this part is connect with SAMA5Dx/SAME70/SAMV71 board and ADM3485ARZ
 *   - <b>Board 1                             Board 2</b>
 *   -  TXD1(XPRO_PD17 pin14) <->DI            TXD1(XPRO_PD17 pin14) <->DI
 *   -  RXD1(XPRO_PD16 pin13) <->RO            RXD1(XPRO_PD16 pin13) <->RO
 *   -  RTS1(XPRO_PD15 pin18) <->DE            RTS1(XPRO_PD15 pin18) <->DE
 *   -  3.3v                                   3.3v
 *   -  GND                                    GND
 *  this part is connect with 2 ADM3485ARZ
 *      A              <-------------------->  A
 *      B              <-------------------->  B
 *      PGND           <-------------------->  PGND
 *
 *  \section Description
 *
 *  This example connects two boards through RS485 interface. One board acts
 *  as the transmitter and the other one as the receiver. It is determined by
 *  the sequence the two applications started.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *     IAR EWARM User and reference guides</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application for each board
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start application from two boards in sequence. Make sure the second board
 *     should NOT be started unless the first board had run to wait for the
 *     synchronizing character. The output message in later section would
 *     describe this.
 *
 *  -# In the terminal  window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- USART RS485 Example xxx --
 *      -- xxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - usart_rs485/main.c
 *  - pio.h
 *  - usart.h
 */

/** \file
 *
 *  This file contains all the specific code for the usart_rs485 example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "trace.h"
#include "compiler.h"

#include "mm/cache.h"
#include "serial/console.h"

#include "peripherals/pmc.h"
#include "gpio/pio.h"
#include "serial/usartd.h"
#include "serial/usart.h"


#include "mutex.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Local definition
 *----------------------------------------------------------------------------*/
#define BUFFER_SIZE  1024

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#define USART_ADDR FLEXUSART0
#define USART_PINS PINS_FLEXCOM0_USART_RS485_IOS1

#elif defined(CONFIG_BOARD_SAMA5D3_EK)
#define USART_ADDR USART1
#define USART_PINS PINS_USART1_RS485

#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
#define USART_ADDR USART3
#define USART_PINS PINS_USART3_RS485

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4_RS485

#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4_RS485

#elif defined(CONFIG_BOARD_SAME70_XPLAINED)
#define USART_ADDR USART2
#define USART_PINS PINS_USART2_RS485

#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
#define USART_ADDR USART2
#define USART_PINS PINS_USART2_RS485

#else
#error Unsupported SoC!
#endif

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/
CACHE_ALIGNED static uint8_t read_buffer[BUFFER_SIZE];
CACHE_ALIGNED static uint8_t write_buffer[BUFFER_SIZE];

/** Transmit buffer. */
uint8_t palette[BUFFER_SIZE]=

 "**************************************************************************\n\r\
 *  This application gives an example of how to use USART in RS485 mode.\n\r\
 *  The USART features the RS485 mode to enable line driver control.\n\r\
 *  While operating in RS485 mode, the USART behaves as though in asynchronous \n\r\
 *  or synchronous mode and configuration of all the parameters is possible \n\r\
 *  \n\r\
 *  The difference is that the RTS pin is driven high when the transmitter\n\r\
 *  is operating. The behaviour of the RTS pin is controlled by the TXEMPTY bit.\n\r\
 *  \n\r\
 **************************************************************************\n\r\
 ";


static struct _usart_desc usart_desc = {
	.addr           = USART_ADDR,
	.baudrate       = 115200,
	.mode           = US_MR_USART_MODE_RS485 | US_MR_CHMODE_NORMAL
					| US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHRL_8_BIT,
	.transfer_mode  = USARTD_MODE_DMA,
};

static const struct _pin usart_pins[] = USART_PINS;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static int _usart_finish_tx_transfer_callback(void* arg, void* arg2)
{
	usartd_finish_tx_transfer(0);
	return 0;
}

/**
 *  \brief Send single buffer data through DMA
 */
static void _usart_dma_tx(const uint8_t* buffer, uint32_t len )
{

	struct _buffer tx = {
		.data = (unsigned char*)buffer,
		.size = len,
		.attr = USARTD_BUF_ATTR_WRITE,
	};
	struct _callback _cb = {
		.method = _usart_finish_tx_transfer_callback,
		.arg = 0,
	};
	usartd_transfer(0, &tx, &_cb);
	usartd_wait_tx_transfer(0);

}

static int _usart_finish_rx_transfer_callback(void* arg, void* arg2)
{
	usartd_finish_rx_transfer(0);
	return 0;
}

/**
 *  \brief Receive single buffer data through DMA
 */
static void _usart_dma_rx(const uint8_t* buffer, uint32_t len )
{

	struct _buffer rx = {
		.data = (unsigned char*)buffer,
		.size = len,
		.attr = USARTD_BUF_ATTR_READ,
	};
	struct _callback _cb = {
		.method = _usart_finish_rx_transfer_callback,
		.arg = 0,
	};
	usartd_transfer(0, &rx, &_cb);
	usartd_wait_rx_transfer(0);

}

/**
 * \brief Display main menu.
 */
static void display_menu( void )
{
	printf("Menu :\n\r");
	printf("------\n\r");
	printf(" - t: Transmit pattern to RS485\n\r");
	printf(" - r: Receive data from RS485 \n\r");
	printf(" - m: Display menu \r\n");
}

/**
 * \brief Dump buffer to DBGU
 *
 */
static void _dump_info(uint8_t *buf, uint32_t size)
{
	uint32_t i = 0 ;

	while ((i < size) && (buf[i] != 0)) {
		printf("%c", buf[i++]);
	}
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Application entry point.
 *
 * Configures USART in synchronous master/slave mode start a transmission
 * between two boards.
 * \return Unused.
 */
extern int main( void )
{
	uint8_t c;

	/* Output example information */
	console_example_info("Usart RS485 Example");

	/* display main menu*/
	display_menu();

	/* init transfer buffer */
	memcpy(write_buffer, palette, BUFFER_SIZE);

	/* configure usart pins */
	pio_configure(usart_pins, ARRAY_SIZE(usart_pins));

	/* configure USART1 in RS485 mode*/
	usartd_configure(0, &usart_desc);

	while(1) {

		if(console_is_rx_ready()) {

			c = console_get_char();
			switch(c) {
			case 't':
			case 'T':

				trace_info("RS485 Transmitting ... \r\n");
				_usart_dma_tx(write_buffer, sizeof(write_buffer));
				trace_info("RS485 Transmitting completed \r\n");
				break;

			case 'r':
			case 'R':
				trace_info("RS485 receiving ... \r\n");
				_usart_dma_rx(read_buffer, sizeof(read_buffer));
				/* successfully received and display */
				_dump_info(read_buffer, sizeof(read_buffer));
				trace_info("RS485 Receiving completed \r\n");
				memset(read_buffer, 0, sizeof(read_buffer));
				break;

			case 'm':
			case 'M':
				display_menu();
				break;
			}
		}
	}
}
