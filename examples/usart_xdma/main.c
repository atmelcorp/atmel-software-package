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

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/usartd.h"
#include "peripherals/usart.h"
#include "peripherals/xdmad.h"

#include "misc/console.h"

#include "memories/at25.h"

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
#define USART_ADDR USART4
#define USART_PINS PINS_FLEXCOM4_USART_IOS2

#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#define USART_ADDR USART4
#define USART_PINS PINS_USART4

#else
#error Unsupported SoC!
#endif

static const struct _pin usart_pins[] = USART_PINS;

ALIGNED(32) static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
ALIGNED(32) static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;
static uint32_t cmd_index = 0;

mutex_t lock = 0;

static struct _usart_desc usart_desc = {
	.addr           = USART_ADDR,
	.baudrate       = 115200,
	.mode           = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT,
	.transfert_mode = USARTD_MODE_DMA,
};

static void console_handler(uint8_t key)
{
	static uint32_t index = 0;
	if (mutex_try_lock(&lock))
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
	mutex_free(&lock);
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
		.size = size
	};
	usartd_transfert(&usart_desc, &rx, 0,
			 usartd_finish_transfert_callback, 0);
	usartd_wait_transfert(&usart_desc);
	printf("%s\r\n", read_buffer);
}

static void _usart_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	struct _buffer tx = {
		.data = (unsigned char*)buffer,
		.size = len
	};
	usartd_transfert(&usart_desc, 0, &tx,
			 usartd_finish_transfert_callback, 0);
}

static void print_menu(void)
{
	printf("Usart example mini-console:\r\n\r\n"
	       "|===========        Commands        ====================|\r\n"
	       "| r size                                                |\r\n"
	       "|      Wait to recieve 'size' characters from usart and |\r\n"
	       "|      print the result string (block call)             |\r\n"
	       "| w str                                                 |\r\n"
	       "|      Write 'str' throught usart                       |\r\n"
	       "| m                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

static void _usart_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if (*buffer == 'm') {
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
	default:
		printf("Command %c unknown\r\n", *buffer);
	}

}

int main (void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console(0);

	/* Output example information */
	console_example_info("USART XDMA Example");

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	usartd_configure(&usart_desc);
	_cmd_parser = _usart_cmd_parser;

	/* Initialize XDMA */
	xdmad_initialize(false);

	/* configure spi serial flash pins */
	pio_configure(usart_pins, ARRAY_SIZE(usart_pins));

	print_menu();

	while (1) {
		asm volatile ("cpsie I");
		asm ("wfi");
		if (mutex_try_lock(&lock)) {
			continue;
		}
		if (cmd_index > 0) {
			_cmd_parser(cmd_buffer, cmd_index);
			cmd_index = 0;
		}
		mutex_free(&lock);
	}
}
