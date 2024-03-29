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
 *  \page usart USART Example
 *
 *  \section Purpose
 *  This application gives an example of how to use USART.
 *
 *  \section Requirements
 *  To run this example 2 kits are needed, one acts as a transmitter and the
 *  other acts as a receiver. And the infrared modules should keep face to face.
 *  This example can be used on SAMA5D2x Xplained board with a Fieldbus shield.
 *
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
 *      -- Usart Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      Menu:
 *      r size
 *            Wait to recieve 'size' characters from usart and
 *            print the result string (block call)
 *      w str
 *            Write 'str' throught usart
 *      m
 *            Print this menu
 *     \endcode
 *
 *   \section References
 *  - usart/main.c
 *  - pio.h
 *  - usart.h
 *
 */

/** \file
 *
 *  This file contains all the specific code for the usart example.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "cpuidle.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "mutex.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "serial/usart.h"
#include "serial/usartd.h"


#ifdef VARIANT_DDRAM
#define CMD_BUFFER_SIZE   256*1024
#define READ_BUFFER_SIZE  256*1024
#else
#define CMD_BUFFER_SIZE  256
#define READ_BUFFER_SIZE  256
#endif
#define TEST_BUFFER_SIZE 36

#if defined(CONFIG_BOARD_SAMA5D2_PTC_EK)
#define USART_ADDR FLEXUSART4
#define USART_PINS PINS_FLEXCOM4_USART_HS_IOS3

#elif defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#define USART_ADDR FLEXUSART0
#define USART_PINS PINS_FLEXCOM0_USART_HS_IOS1

#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
#define USART_ADDR FLEXUSART3
#define USART_PINS PINS_FLEXCOM3_USART_HS_IOS2

#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4

#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
#define USART_ADDR USART3
#define USART_PINS PINS_USART3

#elif defined(CONFIG_BOARD_SAMA5D3_EK)
#define USART_ADDR USART1
#define USART_PINS PINS_USART1

#elif defined(CONFIG_BOARD_SAM9G15_EK)
#define USART_ADDR USART0
#define USART_PINS PINS_USART0

#elif defined(CONFIG_BOARD_SAM9G25_EK)
#define USART_ADDR USART0
#define USART_PINS PINS_USART0

#elif defined(CONFIG_BOARD_SAM9G35_EK)
#define USART_ADDR USART0
#define USART_PINS PINS_USART0

#elif defined(CONFIG_BOARD_SAM9X25_EK)
#define USART_ADDR USART0
#define USART_PINS PINS_USART0

#elif defined(CONFIG_BOARD_SAM9X35_EK)
#define USART_ADDR USART0
#define USART_PINS PINS_USART0

#elif defined(CONFIG_BOARD_SAM9X60_EK) || defined(CONFIG_BOARD_SAM9X60_CURIOSITY)
#define USART_ADDR FLEXUSART4
#define USART_PINS PINS_FLEXCOM4_USART_HS_IOS1

#elif defined(CONFIG_BOARD_SAME70_XPLAINED)
#define USART_ADDR USART2
#define USART_PINS PINS_USART2

#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
#define USART_ADDR USART2
#define USART_PINS PINS_USART2

#else
#error Unsupported SoC!
#endif

static const struct _pin usart_pins[] = USART_PINS;

CACHE_ALIGNED static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
CACHE_ALIGNED static uint8_t read_buffer[READ_BUFFER_SIZE];
static const uint8_t test_patten[TEST_BUFFER_SIZE] = "abcdefghijklmnopqrstuvwxyz0123456789";

typedef void (*_parser)(const uint8_t*, uint32_t);
static bool is_loopback = false;
static _parser _cmd_parser;
static volatile uint32_t cmd_index = 0;

static struct _usart_desc usart_desc = {
	.addr           = USART_ADDR,
	.baudrate       = 115200,
	.mode           = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT,
	.transfer_mode  = USARTD_MODE_POLLING,
	.timeout        = 0, // unit: ms
};

static void console_handler(uint8_t key)
{
	static uint32_t index = 0;
	if (index >= CMD_BUFFER_SIZE) {
		printf("\r\nWARNING! command buffer size exeeded, "
		       "reseting\r\n");
		index = 0;
	}
	console_echo(key);
	switch (key) {
	case '\r':
	case '\n':
		cmd_buffer[index]='\0';
		cmd_index = index;
		index = 0;
		break;
	case 0x7F:
	case '\b':
		cmd_buffer[--index]='\0';
		break;
	default:
		cmd_buffer[index++]=key;
		break;
	}
}

static int _usart_finish_rx_transfer_callback(void* arg, void* arg2)
{
	uint32_t received = (uint32_t)arg2;
	if (!is_loopback) printf("R:%lu bytes ", received);
	for (uint32_t i = 0; i < received; i++)
		printf("%c", read_buffer[i]);
	printf("\r\n");
	return 0;
}

static void _usart_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	memset(read_buffer, 0x0, sizeof(read_buffer));
	char* end_addr = NULL;
	uint32_t size = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid address\r\n",
			buffer);
		return;
	}

	memset(read_buffer, 0, ARRAY_SIZE(read_buffer));
	cache_clean_region(read_buffer, ARRAY_SIZE(read_buffer));
	
	struct _buffer rx = {
		.data = (unsigned char*)read_buffer,
		.size = size,
		.attr = USARTD_BUF_ATTR_READ,
	};
	struct _callback _cb = {
		.method = _usart_finish_rx_transfer_callback,
		.arg = 0,
	};
	usartd_transfer(0, &rx, &_cb);
	usartd_wait_rx_transfer(0);
}

static int _usart_finish_tx_transfer_callback(void* arg, void* arg2)
{
	return 0;
}

static void _usart_write_arg_parser(const uint8_t* buffer, uint32_t len)
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

static void print_menu(void)
{
	printf("\r\n\r\nUSART transfer mode: ");
	switch (usart_desc.transfer_mode) {
	case USARTD_MODE_POLLING:
		printf("POLLING\r\n");
		break;
	case USARTD_MODE_ASYNC:
		printf("ASYNC\r\n");
		break;
	case USARTD_MODE_DMA:
		printf("DMA\r\n");
		break;
	}
	printf("Usart example mini-console:\r\n\r\n"
	       "|===========        Commands        ====================|\r\n"
	       "| r size                                                |\r\n"
	       "|      Wait to recieve 'size' characters from usart and |\r\n"
	       "|      print the result string (block call)             |\r\n"
	       "| w str                                                 |\r\n"
	       "|      Write 'str' throught usart                       |\r\n"
#ifdef US_CSR_CMP
	       "| c                                                     |\r\n"
	       "|      Demo Comparision Function                        |\r\n"
#endif /* US_CSR_CMP */
	       "| p                                                     |\r\n"
	       "|      receive with DMA (ping/pong buffer used)         |\r\n"
	       "| m polling                                             |\r\n"
	       "| m async                                               |\r\n"
	       "| m dma                                                 |\r\n"
	       "|      Select transfer mode                             |\r\n"
#ifdef CONFIG_HAVE_USART_FIFO
	       "| f fifo                                                |\r\n"
	       "|      Toggle FIFO feature                              |\r\n"
	       "| f handshaking                                         |\r\n"
	       "|      Toggle Handshaking and normal mode               |\r\n"
#endif /* CONFIG_HAVE_USART_FIFO */
	       "| l                                                     |\r\n"
	       "|      Local Loopback test                              |\r\n"
	       "| h                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

#ifdef CONFIG_HAVE_USART_FIFO
static void _usart_feature_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "fifo", 4)) {
		if (!usart_desc.use_fifo) {
			usart_desc.use_fifo = true;
			usart_fifo_enable(usart_desc.addr);
			printf("Enable FIFO\r\n");
		} else {
			usart_desc.use_fifo = false;
			usart_fifo_disable(usart_desc.addr);
			printf("Disable FIFO\r\n");
		}
	}
	if (!strncmp((char*)buffer, "handshaking", 11)) {
		if ((usart_desc.mode & US_MR_USART_MODE_HW_HANDSHAKING) != US_MR_USART_MODE_HW_HANDSHAKING) {
			if (!usart_desc.use_fifo) {
				usart_desc.use_fifo = true;
				usart_fifo_enable(usart_desc.addr);
			}
			usart_desc.mode = US_MR_USART_MODE_HW_HANDSHAKING | US_MR_PAR_NO | US_MR_CHRL_8_BIT;
			usart_desc.fifo.tx.threshold = 8;
			usart_desc.fifo.rx.threshold = 8;
			usart_desc.fifo.rx.threshold2 = 4;
			printf(" Switch to handshaking mode with FIFO enabled\r\n");
			printf(" RTS pin will be controlled by Receive FIFO thresholds\r\n");
		} else {
			usart_desc.mode = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT;
			printf(" Switch to usart normal mode\r\n");
		}
		usartd_configure(0, &usart_desc);
	}
}
#endif /* US_CSR_CMP */

static int usart_dma_pingpong_callback(void* arg, void* arg2)
{
	uint8_t iface = (uint32_t)arg2;
	uint8_t buf[8];
	uint32_t read, remain, i;

	printf("\r\nmessage received: ");
	do {
		remain = usartd_dma_pingpong_read(iface, buf, sizeof(buf), &read);
		for (i = 0; i < read; i++)
			printf("%c", buf[i]);
	} while(remain);
	return 0;
}

static void _usart_mode_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "polling", 7)) {
		usart_desc.transfer_mode = USARTD_MODE_POLLING;
		usart_desc.timeout = 0;
		printf("Use POLLING mode\r\n");
	}
	else if (!strncmp((char*)buffer, "async", 5)) {
		usart_desc.transfer_mode = USARTD_MODE_ASYNC;
		usart_desc.timeout = 500; //ms
		printf("Use ASYNC mode\r\n");
	}
	else if (!strncmp((char*)buffer, "dma", 3)) {
		usart_desc.transfer_mode = USARTD_MODE_DMA;
		usart_desc.timeout = 0;
		printf("Use DMA mode\r\n");
	}
	usart_set_rx_timeout(usart_desc.addr, usart_desc.baudrate, usart_desc.timeout);
	printf("Timeout %lums\r\n",usart_desc.timeout );
}

static void _usart_loopback_autotest(void)
{
	uint32_t size;
	printf("Start local loopback test\r\n");
	for (uint8_t mode = USARTD_MODE_ASYNC; mode <= USARTD_MODE_DMA; mode++) {
		usart_desc.transfer_mode  = mode;
		printf("Mode:%s\r\n", mode == USARTD_MODE_ASYNC? "ASYNC": "DMA");
#ifdef CONFIG_HAVE_USART_FIFO
		for (uint8_t fifo = 0; fifo <= (mode == USARTD_MODE_DMA? 0 : 1); fifo++) {
			if (!fifo) {
				printf("FIFO disabled\r\n");
				usart_desc.use_fifo = false;
				usart_fifo_disable(usart_desc.addr);
			} else {
				printf("FIFO enabled\r\n");
				usart_desc.use_fifo = true;
				usart_fifo_enable(usart_desc.addr);
			}
#endif
			for (size = 1; size <= TEST_BUFFER_SIZE; size++) {
				struct _buffer tx = {
					.data = (unsigned char*)test_patten,
					.size = size,
					.attr = USARTD_BUF_ATTR_WRITE,
				};
				struct _callback _cb_tx = {
					.method = _usart_finish_tx_transfer_callback,
					.arg = 0,
				};
				memset(read_buffer, 0x0, sizeof(read_buffer));
				cache_clean_region(read_buffer, ARRAY_SIZE(read_buffer));
				struct _buffer rx = {
					.data = (unsigned char*)read_buffer,
					.size = size,
					.attr = USARTD_BUF_ATTR_READ,
				};
				struct _callback _cb_rx = {
					.method = _usart_finish_rx_transfer_callback,
					.arg = 0,
				};
				usartd_transfer(0, &rx, &_cb_rx);
				usartd_transfer(0, &tx, &_cb_tx);
				usartd_wait_tx_transfer(0);
				usartd_wait_rx_transfer(0);
				printf("%s\r\n", read_buffer);
			}
#ifdef CONFIG_HAVE_USART_FIFO
		}
#endif
	}
}
static void _usart_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if ((*buffer == 'h') || (*buffer == 'H')) {
		print_menu();
		return;
	}
#ifdef US_CSR_CMP
	if ((*buffer == 'c') || (*buffer == 'C')) {
		printf("\r\nUSART Comparison function (ping/pong buffer used): ");
		printf("\r\n  callback would be called once \"5\" is received.");
		usart_desc.cmp.enable = 1;
		usart_desc.cmp.val1 = '5';
		usart_desc.cmp.val2 = '5';
		usart_desc.timeout = 0;
		struct _buffer rx = {
			.data = (unsigned char*)read_buffer,
			.size = 64,
			.attr = USARTD_BUF_ATTR_READ | USARTD_BUF_ATTR_PINGPONG,
		};
		struct _callback _cb = {
			.method = usart_dma_pingpong_callback,
			.arg = 0,
		};
		usartd_transfer(0, &rx, &_cb);
		return;
	}
#endif /* US_CSR_CMP */
	if ((*buffer == 'p') || (*buffer == 'P')) {
		printf("\r\nUSART receive with DMA (ping/pong buffer used): ");
		printf("\r\n  Note: the max length of one message should not execeed the size of buffer");
		printf("\r\n  callback would be called after data received and timeout occurs.");

		usart_desc.timeout = 500;
		struct _buffer rx = {
			.data = (unsigned char*)read_buffer,
			.size = 64,
			.attr = USARTD_BUF_ATTR_READ | USARTD_BUF_ATTR_PINGPONG,
		};
		struct _callback _cb = {
			.method = usart_dma_pingpong_callback,
			.arg = 0,
		};
		usartd_transfer(0, &rx, &_cb);
		return;
	}
	if ((*buffer == 'l') || (*buffer == 'L')) {
		usart_loopback_enable(usart_desc.addr);
		is_loopback = true;
		printf("Enable Loopback test\r\n");
		_usart_loopback_autotest();
		usart_loopback_disable(usart_desc.addr);
		is_loopback = false;
		return;
	}
	if (*(buffer+1) != ' ') {
		printf("Commands can only be one caracter size\r\n");
		printf("%c%c\r\n", *buffer, *(buffer+1));
		return;
	}
	switch(*buffer) {
	case 'w':
		_usart_write_arg_parser(buffer+2, len-2);
		break;
	case 'r':
		_usart_read_arg_parser(buffer+2, len-2);
		break;
	case 'm':
		_usart_mode_arg_parser(buffer+2, len-2);
		break;
#ifdef CONFIG_HAVE_USART_FIFO
	case 'f':
		_usart_feature_arg_parser(buffer+2, len-2);
		break;
#endif
	default:
		printf("Command %c unknown\r\n", *buffer);
	}

}

int main (void)
{
	/* Output example information */
	console_example_info("USART Example");

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	usartd_configure(0, &usart_desc);
	_cmd_parser = _usart_cmd_parser;

	/* configure spi serial flash pins */
	pio_configure(usart_pins, ARRAY_SIZE(usart_pins));

	print_menu();

	while (1) {
		cpu_idle();
		if (cmd_index > 0) {
			_cmd_parser(cmd_buffer, cmd_index);
			cmd_index = 0;
		}
	}
}
