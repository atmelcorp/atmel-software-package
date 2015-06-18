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
#include "peripherals/spid.h"

#include "misc/console.h"

#include "memories/at25.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFFER_SIZE  128
#define READ_BUFFER_SIZE  256

static const struct _pin at25_pins[] = AT25_PINS;

static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;

static struct _spi_desc spi_at25_desc = {
	.addr           = AT25_ADDR,
	.bitrate        = AT25_FREQ,
	.attributes     = AT25_ATTRS,
	.dlybs          = AT25_DLYBS,
	.dlybct         = AT25_DLYCT,
	.mutex          = 1,
	.chip_select    = AT25_CS,
	.spi_mode       = AT25_SPI_MODE,
	.transfert_mode = SPID_MODE_FIFO,
	.dma = 0
};

static struct _at25 at25drv;

static void console_handler(void)
{
	volatile static uint32_t lock = 0;
	static uint32_t index = 0;
	uint8_t key;
	if (!console_is_rx_ready())
		return;
	key = console_get_char();
	if (lock)
		return;
	lock = 1;
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
		_cmd_parser(cmd_buffer, index);
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
	lock = 0;
}

static void _flash_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	char* end_length = NULL;
	unsigned long addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid address\r\n",
		       buffer);
		return;
	}

	int length = strtol(end_addr, &end_length, 0);
	if (end_length == end_addr) {
		printf("Args: %s\r\n"
		       "Invalid size\r\n",
			buffer);
		return;
	}
	int offset = 0;
	while (length > READ_BUFFER_SIZE) {
		if(at25_read(&at25drv, addr+offset, read_buffer,
			      READ_BUFFER_SIZE)) {
			/* Read failed, no need to dump anything */
			return;
		}
		offset += READ_BUFFER_SIZE;
		length -= READ_BUFFER_SIZE;
		console_dump_frame(read_buffer, READ_BUFFER_SIZE);

	}
	at25_read(&at25drv, addr+offset, read_buffer,
			length);
	console_dump_frame(read_buffer, length);
}

static void _flash_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	unsigned int addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid address\r\n",
			buffer);
		return;
	}

	len -= (end_addr+1) - (char*)buffer;

	at25_write(&at25drv, addr, (uint8_t*)end_addr+1, len);
}

static void _flash_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	const char *dev_lbl = "device";
	const char *status_lbl = "status";
	uint32_t status = 0;
	if (!strncmp((char*)buffer, dev_lbl, 6)) {
		at25_print_device_info(&at25drv);
	} else if (!strncmp((char*)buffer, status_lbl, 6)) {
		status = at25_read_status(&at25drv);
		printf("AT25 chip status:\r\n"
		       "\t- Busy: %s\r\n"
		       "\t- Write Enabled: %s\r\n"
		       "\t- Software protection: %s\r\n"
		       "\t- Write protect pin: %s\r\n"
		       "\t- Erase/Program error: %s\r\n"
		       "\t- Sector Protection Resgister: %s\r\n"
		       "\t- Raw register value: 0x%X\r\n",
		       status & AT25_STATUS_RDYBSY_BUSY ? "yes":"no",
		       status & AT25_STATUS_WEL ? "yes":"no",
		       status & AT25_STATUS_SWP ? "Some/all":"none",
		       status & AT25_STATUS_WPP ? "inactive":"active",
		       status & AT25_STATUS_EPE ? "yes":"no",
		       status & AT25_STATUS_SPRL ? "locked":"unlocked",
		       (unsigned int)status);
	}
}

static void _flash_delete_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	char* erase_type_str = NULL;
	unsigned long addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		if (!strncmp((char*)buffer, "all", 3)) {
			at25_erase_chip(&at25drv);
		} else {
			printf("Args: %s\r\n"
			       "Invalid address\r\n",
			       buffer);
		}
		return;
	}

	uint32_t erase_type = AT25_BLOCK_ERASE_4K;

	erase_type_str = end_addr + 1;
	switch(*erase_type_str) {
	case '4':
		if (*(erase_type_str+1) == 'k' || *(erase_type_str+1) == 'K') {
			erase_type = AT25_BLOCK_ERASE_4K;
		}
		break;
	case '3':
		if (*(erase_type_str+1) == '2' &&
		    (*(erase_type_str+2) == 'k' || *(erase_type_str+2) == 'K')) {
			erase_type = AT25_BLOCK_ERASE_32K;
		}
		break;
	case '6':
		if (*(erase_type_str+1) == '4' &&
		    (*(erase_type_str+2) == 'k' || *(erase_type_str+2) == 'K')) {
			erase_type = AT25_BLOCK_ERASE_64K;
		}
		break;
	default:
		printf("Args: %s\r\n"
		       "Invalid Erase type\r\n",
		       buffer);
		return;
	}
	at25_erase_block(&at25drv, addr, erase_type);
}

static void _flash_cmd_parser(const uint8_t* buffer, uint32_t len)
{

	if (*(buffer+1) != ' ') {
		printf("Commands can only be one caracter size\r\n");
		printf("%c%c\r\n", *buffer, *(buffer+1));
		return;
	}
	switch(*buffer) {
	case 'r':
		_flash_read_arg_parser(buffer+2, len-2);
		break;
	case 'w':
		_flash_write_arg_parser(buffer+2, len-2);
		break;
	case 'a':
		_flash_query_arg_parser(buffer+2, len-2);
		break;
	case 'd':
		_flash_delete_arg_parser(buffer+2, len-2);
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

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Configure console interrupts */
	console_enable_interrupts(US_IER_RXRDY);
	aic_set_source_vector(CONSOLE_ID, console_handler);
	aic_enable(CONSOLE_ID);
	_cmd_parser = _flash_cmd_parser;

	/* Clear console */
	console_clear_screen();
	console_reset_cursor();

	printf("-- Spi flash Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME " --\n\r"
	       "-- Compiled: " __DATE__ " at " __TIME__ " --\n\r");

	/* configure spi serial flash pins */
	pio_configure(at25_pins, ARRAY_SIZE(at25_pins));

	/* Open serial flash device */
	at25_configure(&at25drv, &spi_at25_desc);
	if(at25_unprotect(&at25drv))
		printf("Protection desactivation FAILED!\r\n");

	while (1);
}
