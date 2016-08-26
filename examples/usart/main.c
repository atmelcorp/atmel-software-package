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

#include <stdint.h>

#include "board.h"
#include "chip.h"

#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/usartd.h"
#include "peripherals/usart.h"

#include "misc/cache.h"
#include "misc/console.h"

#include "mutex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef VARIANT_DDRAM
#define CMD_BUFFER_SIZE   8*1024*1024
#define READ_BUFFER_SIZE  8*1024*1024
#else
#define CMD_BUFFER_SIZE  256
#define READ_BUFFER_SIZE  256
#endif

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#define USART_ADDR USART0
#define USART_PINS PINS_FLEXCOM0_USART_IOS1

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

#else
#error Unsupported SoC!
#endif

static const struct _pin usart_pins[] = USART_PINS;

CACHE_ALIGNED static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
CACHE_ALIGNED static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;
static uint32_t cmd_index = 0;

mutex_t lock = 0;

static struct _usart_desc usart_desc = {
	.addr           = USART_ADDR,
	.baudrate       = 115200,
	.mode           = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT,
	.transfer_mode  = USARTD_MODE_ASYNC,
};

static void console_handler(uint8_t key)
{
	static uint32_t index = 0;
	if (!mutex_try_lock(&lock))
		return;
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
	mutex_unlock(&lock);
}

static void _usart_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	memset(read_buffer, 0x0, sizeof(read_buffer));
	char* end_addr = NULL;
	unsigned int size = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid address\r\n",
			buffer);
		return;
	}

	struct _buffer rx = {
		.data = (unsigned char*)read_buffer,
		.size = size,
		.attr = USARTD_BUF_ATTR_READ,
	};
	usartd_transfer(&usart_desc, &rx, usartd_finish_transfer_callback, 0);
	usartd_wait_transfer(&usart_desc);
	printf("%s\r\n", read_buffer);
}

static void _usart_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	struct _buffer tx = {
		.data = (unsigned char*)buffer,
		.size = len,
		.attr = USARTD_BUF_ATTR_WRITE,
	};
	usartd_transfer(&usart_desc, &tx, usartd_finish_transfer_callback, 0);
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
	       "| m polling                                             |\r\n"
	       "| m async                                               |\r\n"
	       "| m dma                                                 |\r\n"
	       "|      Select transfer mode                             |\r\n"
#ifdef CONFIG_HAVE_USART_FIFO
	       "| f fifo                                                |\r\n"
	       "|      Toggle FIFO feature                              |\r\n"
#endif /* CONFIG_HAVE_USART_FIFO */
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
			usart_fifo_enable(usart_desc.addr);
			printf("Disable FIFO\r\n");
		}
	}
}
#endif /* CONFIG_HAVE_USART_FIFO */

static void _usart_mode_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "polling", 7)) {
		usart_desc.transfer_mode = USARTD_MODE_POLLING;
		printf("Use POLLING mode\r\n");
	}
	else if (!strncmp((char*)buffer, "async", 5)) {
		usart_desc.transfer_mode = USARTD_MODE_ASYNC;
		printf("Use ASYNC mode\r\n");
	}
	else if (!strncmp((char*)buffer, "dma", 3)) {
		usart_desc.transfer_mode = USARTD_MODE_DMA;
		printf("Use DMA mode\r\n");
	}
}

static void _usart_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if ((*buffer == 'h') || (*buffer == 'H')) {
		print_menu();
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
	console_example_info("USART DMA Example");

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	usartd_configure(&usart_desc);
	_cmd_parser = _usart_cmd_parser;

	/* configure spi serial flash pins */
	pio_configure(usart_pins, ARRAY_SIZE(usart_pins));

	print_menu();

	while (1) {
		irq_wait();
		if (!mutex_try_lock(&lock)) {
			continue;
		}
		if (cmd_index > 0) {
			_cmd_parser(cmd_buffer, cmd_index);
			cmd_index = 0;
		}
		mutex_unlock(&lock);
	}
}
