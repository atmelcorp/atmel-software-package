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

/*----------------------------------------------------------------------------
*        Headers
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chip.h"
#include "console.h"
#ifdef CONFIG_HAVE_L1CACHE
#include "mm/l1cache.h"
#endif
#ifdef CONFIG_HAVE_L2CACHE
#include "mm/l2cache.h"
#endif
#ifdef CONFIG_HAVE_MMU
#include "mm/mmu.h"
#endif
#include "peripherals/pmc.h"
#include "serial/seriald.h"

static struct _seriald console;

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

void console_configure(const struct _console_cfg* config)
{
	if (config && config->addr && config->baudrate)
	{
		if (config->tx_pin.mask)
			pio_configure(&config->tx_pin, 1);
		if (config->rx_pin.mask)
			pio_configure(&config->rx_pin, 1);
		seriald_configure(&console, config->addr, config->baudrate);
	} else {
		memset(&console, 0, sizeof(console));
	}
}

void console_put_char(char c)
{
	seriald_put_char(&console, *(uint8_t*)&c);
}

void console_put_string(const char* str)
{
	seriald_put_string(&console, (const uint8_t*)str);
}

bool console_is_tx_empty(void)
{
	return seriald_is_tx_empty(&console);
}

char console_get_char(void)
{
	uint8_t c = seriald_get_char(&console);
	return *(char*)&c;
}

bool console_is_rx_ready(void)
{
	return seriald_is_rx_ready(&console);
}

void console_set_rx_handler(console_rx_handler_t handler)
{
	seriald_set_rx_handler(&console, handler);
}

void console_enable_rx_interrupt(void)
{
	seriald_enable_rx_interrupt(&console);
}

void console_disable_rx_interrupt(void)
{
	seriald_disable_rx_interrupt(&console);
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
#ifdef CONFIG_HAVE_MMU
	printf("MMU is %s\r\n", mmu_is_enabled() ? "enabled" : "disabled");
#endif
#ifdef CONFIG_HAVE_L1CACHE
	printf("I-Cache is %s\r\n", icache_is_enabled() ? "enabled" : "disabled");
	printf("D-Cache is %s\r\n", dcache_is_enabled() ? "enabled" : "disabled");
#endif
#ifdef CONFIG_HAVE_L2CACHE
	printf("L2-Cache is %s\r\n", l2cache_is_enabled() ? "enabled" : "disabled");
#endif
#endif
	console_put_string("\r\n");
}

void console_dump_frame(uint8_t *frame, uint32_t size)
{
	uint32_t i;
	for (i = 0; i < size; i++) {
		printf("%02x ", frame[i]);
	}
	console_put_string("\n\r");
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
	console_put_string("\n\r");
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
					console_put_string("\n\rIt is not a hexa character!\n\r");
					return 0;
				}
			}
		}
	}
	console_put_string("\n\r");
	*pvalue = value;
	return 1;
}

void console_clear_screen(void)
{
	console_put_string("\033[2J\033[0;0f");
}

void console_reset_cursor(void)
{
	console_put_string("\033[0;0f");
}

void console_echo(uint8_t c)
{
	switch (c) {
	case '\r':
	case '\n':
		console_put_string("\r\n");
		break;
	case 0x7F:
		console_put_string("\033[1D\033[K");
		break;
	case '\b':
		console_put_string("\033[1D\033[K");
		break;
	default:
		console_put_char(c);
	}
}
