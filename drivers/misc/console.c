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
* \file
*
* Implements CONSOLE.
*
*/

/*----------------------------------------------------------------------------
*        Headers
*----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/aic.h"
#ifdef CONFIG_HAVE_DBGU
#include "peripherals/dbgu.h"
#endif
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/uart.h"
#include "peripherals/usart.h"

#include "console.h"

#include <assert.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local Types
 *----------------------------------------------------------------------------*/

typedef void (*init_handler_t)(void*, uint32_t, uint32_t);
typedef void (*put_char_handler_t)(void*, uint8_t);
typedef uint8_t (*get_char_handler_t)(void*);
typedef bool (*rx_ready_handler_t)(void*);
typedef void (*enable_it_handler_t)(void*, uint32_t);
typedef void (*disable_it_handler_t)(void*, uint32_t);

struct _console {
	uint32_t             mode;
	uint32_t             rx_int_mask;
	init_handler_t       init;
	put_char_handler_t   put_char;
	get_char_handler_t   get_char;
	rx_ready_handler_t   rx_ready;
	enable_it_handler_t  enable_it;
	disable_it_handler_t disable_it;
};

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

static const struct _console console_usart = {
	.mode = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT,
	.rx_int_mask = US_IER_RXRDY,
	.init = (init_handler_t)usart_configure,
	.put_char = (put_char_handler_t)usart_put_char,
	.get_char = (get_char_handler_t)usart_get_char,
	.rx_ready = (rx_ready_handler_t)usart_is_rx_ready,
	.enable_it = (enable_it_handler_t)usart_enable_it,
	.disable_it = (disable_it_handler_t)usart_disable_it,
};

static const struct _console console_uart = {
	.mode = UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO,
	.rx_int_mask = UART_IER_RXRDY,
	.init = (init_handler_t)uart_configure,
	.put_char = (put_char_handler_t)uart_put_char,
	.get_char = (get_char_handler_t)uart_get_char,
	.rx_ready = (rx_ready_handler_t)uart_is_rx_ready,
	.enable_it = (enable_it_handler_t)uart_enable_it,
	.disable_it = (disable_it_handler_t)uart_disable_it,
};

#ifdef CONFIG_HAVE_DBGU
static const struct _console console_dbgu = {
	.mode = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE,
	.rx_int_mask = DBGU_IER_RXRDY,
	.init = (init_handler_t)dbgu_configure,
	.put_char = (put_char_handler_t)dbgu_put_char,
	.get_char = (get_char_handler_t)dbgu_get_char,
	.rx_ready = (rx_ready_handler_t)dbgu_is_rx_ready,
	.enable_it = (enable_it_handler_t)dbgu_enable_it,
	.disable_it = (disable_it_handler_t)dbgu_disable_it,
};
#endif

static uint32_t console_id = 0;
static void *console_addr = NULL;
static const struct _console *console = NULL;
static bool console_initialized = false;
static console_rx_handler_t console_rx_handler;

/*------------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------------*/

static void console_handler(void)
{
	uint8_t c;

	if (!console_is_rx_ready())
		return;

	c = console_get_char();
	if (console_rx_handler)
		console_rx_handler(c);
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

void console_configure(void* addr, uint32_t baudrate)
{
	uint32_t id;

	id = get_usart_id_from_addr((Usart*)addr);
	if (id != ID_PERIPH_COUNT) {
		console = &console_usart;
	} else {
		id = get_uart_id_from_addr((Uart*)addr);
		if (id != ID_PERIPH_COUNT) {
			console = &console_uart;
		} else {
#ifdef CONFIG_HAVE_DBGU
			if (addr == DBGU) {
				id = ID_DBGU;
				console = &console_dbgu;
			} else
#endif
			{
				/* Unknown console type */
				assert(0);
				return;
			}
		}
	}

	/* Save console peripheral address and ID */
	console_id = id;
	console_addr = addr;

	/* Initialize driver to use */
	pmc_enable_peripheral(id);
	console->init(console_addr, console->mode, baudrate);

	/* Finally */
	console_initialized = true;
}

void console_put_char(uint8_t c)
{
	// if console is not initialized, do nothing
	if (!console_initialized)
		return;

	console->put_char(console_addr, c);
}

uint8_t console_get_char(void)
{
	// if console is not initialized, fail
	if (!console_initialized) {
		assert(0);
		while(1);
	}

	return console->get_char(console_addr);
}

bool console_is_rx_ready(void)
{
	// if console is not initialized, rx not ready
	if (!console_initialized)
		return false;

	return console->rx_ready(console_addr);
}

void console_set_rx_handler(console_rx_handler_t handler)
{
	console_rx_handler = handler;
}

void console_enable_rx_interrupt(void)
{
	aic_set_source_vector(console_id, console_handler);
        aic_enable(console_id);
	console->enable_it(console_addr, console->rx_int_mask);
}

void console_disable_rx_interrupt(void)
{
        aic_disable(console_id);
	console->disable_it(console_addr, console->rx_int_mask);
}

void console_example_info(const char *example_name)
{
	/* Clear screen */
	console_clear_screen();

	/* reset cursor */
	console_reset_cursor();

	/* Output example information */
	printf("-- %s --\r\n", example_name);
#ifndef NDEBUG
	printf("Softpack v%s\r\n", SOFTPACK_VERSION);
	printf("Built for %s\r\n", get_board_name());
	printf("Processor: %s\r\n", get_chip_name());
	printf("Processor clock: %u MHz\r\n", (unsigned)(pmc_get_processor_clock() / 1000000));
	printf("Master clock: %u MHz\r\n", (unsigned)(pmc_get_master_clock() / 1000000));
	printf("MMU is %s\r\n", cp15_mmu_is_enabled() ? "enabled" : "disabled");
	printf("I-Cache is %s\r\n", cp15_icache_is_enabled() ? "enabled" : "disabled");
	printf("D-Cache is %s\r\n", cp15_dcache_is_enabled() ? "enabled" : "disabled");
#endif
	printf("\r\n");
}

void console_dump_frame(uint8_t *frame, uint32_t size)
{
	uint32_t i;
	for (i = 0; i < size; i++) {
		printf("%02x ", frame[i]);
	}
	printf("\n\r");
}

void console_dump_memory(uint8_t *buffer, uint32_t size,
				uint32_t address)
{
	uint32_t i, j;
	uint32_t last_line_start;
	uint8_t *tmp;

	for (i = 0; i < (size / 16); i++) {
		printf("0x%08X: ", (unsigned int)(address + (i * 16)));
		tmp = (uint8_t *) & buffer[i * 16];
		for (j = 0; j < 4; j++) {
			printf("%02X%02X%02X%02X ", tmp[0], tmp[1], tmp[2],
			       tmp[3]);
			tmp += 4;
		}
		tmp = (uint8_t *) & buffer[i * 16];
		for (j = 0; j < 16; j++) {
			console_put_char(*tmp++);
		}
		printf("\n\r");
	}
	if ((size % 16) != 0) {
		last_line_start = size - (size % 16);
		printf("0x%08X: ", (unsigned int)(address + last_line_start));
		for (j = last_line_start; j < last_line_start + 16; j++) {
			if ((j != last_line_start) && (j % 4 == 0)) {
				printf(" ");
			}
			if (j < size)
				printf("%02X", buffer[j]);
			else
				printf("  ");
		}
		printf(" ");
		for (j = last_line_start; j < size; j++) {
			console_put_char(buffer[j]);
		}
		printf("\n\r");
	}
}

uint32_t console_get_integer(uint32_t * pvalue)
{
	uint8_t key;
	uint8_t nb = 0;
	uint32_t value = 0;

	while (1) {
		key = console_get_char();
		console_put_char(key);

		if (key >= '0' && key <= '9') {
			value = (value * 10) + (key - '0');
			nb++;
		} else {
			if (key == 0x0D || key == ' ') {
				if (nb == 0) {
					printf
					    ("\n\rWrite a number and press ENTER or SPACE!\n\r");
					return 0;
				} else {
					printf("\n\r");
					*pvalue = value;
					return 1;
				}
			} else {
				printf("\n\r'%c' not a number!\n\r", key);
				return 0;
			}
		}
	}
}

uint32_t console_get_integer_min_max(uint32_t * pvalue, uint32_t min,
					 uint32_t max)
{
	uint32_t value = 0;

	if (console_get_integer(&value) == 0)
		return 0;
	if (value < min || value > max) {
		printf("\n\rThe number have to be between %u and %u\n\r",
		       (unsigned int)min, (unsigned int)max);
		return 0;
	}
	printf("\n\r");
	*pvalue = value;
	return 1;
}

uint32_t console_get_hexa_32(uint32_t * pvalue)
{
	uint8_t key;
	uint32_t dw = 0;
	uint32_t value = 0;

	for (dw = 0; dw < 8; dw++) {
		key = console_get_char();
		console_put_char(key);

		if (key >= '0' && key <= '9') {
			value = (value * 16) + (key - '0');
		} else {
			if (key >= 'A' && key <= 'F') {
				value = (value * 16) + (key - 'A' + 10);
			} else {
				if (key >= 'a' && key <= 'f') {
					value = (value * 16) + (key - 'a' + 10);
				} else {
					printf
					    ("\n\rIt is not a hexa character!\n\r");
					return 0;
				}
			}
		}
	}
	printf("\n\r");
	*pvalue = value;
	return 1;
}

void console_clear_screen(void)
{
	printf("\033[2J\033[0;0f");
}

void console_reset_cursor(void)
{
	printf("\033[0;0f");
}

void console_echo(uint8_t c)
{
	switch (c) {
	case '\r':
	case '\n':
		printf("\r\n");
		break;
	case 0x7F:
		printf("\033[1D\033[K");
		break;
	case '\b':
		printf("\033[1D\033[K");
		break;
	default:
		console_put_char(c);
	}
}
