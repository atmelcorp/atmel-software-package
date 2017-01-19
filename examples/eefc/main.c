/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm/mpu_armv7m.h"
#include "board.h"
#include "chip.h"
#include "compiler.h"
#include "cpuidle.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "nvm/flash/eefc.h"
#include "nvm/flash/flashd.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "trace.h"

#define CMD_BUFFER_SIZE   (1024)
#define READ_BUFFER_SIZE  (4 * 1024)

CACHE_ALIGNED static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
CACHE_ALIGNED static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;
static volatile uint32_t cmd_length = 0;
static volatile bool cmd_complete = false;

static struct _flash flash;

static void console_handler(uint8_t key)
{
	/* already processing a command: ignore input */
	if (cmd_complete)
	       return;

	switch (key) {
	case '\r':
	case '\n':
		if (cmd_length > 0) {
			console_echo(key);
			cmd_buffer[cmd_length] = '\0';
			cmd_complete = true;
		}
		break;
	case 0x7F:
	case '\b':
		if (cmd_length > 0) {
			console_echo(key);
			cmd_length--;
			cmd_buffer[cmd_length] = '\0';
		}
		break;
	default:
		if (cmd_length < (ARRAY_SIZE(cmd_buffer) - 1)) {
			console_echo(key);
			cmd_buffer[cmd_length] = key;
			cmd_length++;
		}
		break;
	}
}

static void _flash_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	int rc;
	char* end_addr = NULL;
	char* end_length = NULL;
	uint32_t offset = strtoul((char*)buffer, &end_addr, 0);

	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid offset\r\n", buffer);
		return;
	}

	int length = strtol(end_addr, &end_length, 0);
	if (end_length == end_addr) {
		printf("Args: %s\r\n"
		       "Invalid size\r\n", buffer);
		return;
	}

	rc = flashd_read(&flash, offset, read_buffer, length);
	if (rc == 0) {
		printf("Read complete (%u bytes): ", length);
		console_dump_frame(read_buffer, length);
	} else {
		printf("Read failed (errno=%d)\r\n", rc);
	}
}

static void _flash_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	int rc;
	char* end_addr = NULL;
	uint32_t offset = strtoul((char*)buffer, &end_addr, 0);

	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid offset\r\n", buffer);
		return;
	}

	if (1 + end_addr - (char*)buffer > len) {
		printf("No data given.\r\n");
		return;
	}

	len -= (end_addr + 1) - (char*)buffer;
	rc = flashd_write(&flash, offset, (uint8_t*)end_addr + 1, len);
	if (rc == 0)
		printf("Write complete (%d bytes)\r\n", len);
	else
		printf("Write failed (errno=%d)\r\n", rc);
}

static void _flash_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "uid", 3)) {
		int rc;
		uint8_t unique_id[16];

		rc = flashd_read_unique_id(&flash, unique_id);
		if (rc == 0) {
			printf("Read UID complete: ");
			console_dump_frame(unique_id, 16);
		} else {
			printf("Read UID failed (errno=%d)\r\n", rc);
		}
	}
}

static void _flash_delete_arg_parser(const uint8_t* buffer, uint32_t len)
{
	int rc;
	char* end_addr = NULL;
	unsigned long offset = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		if (!strncmp((char*)buffer, "all", 3)) {
			flashd_erase(&flash);
		} else {
			printf("Args: %s\r\n"
			       "Invalid offset\r\n", buffer);
		}
		return;
	}
	rc = flashd_erase_block(&flash, offset, flash.erase_size);
	if (rc == 0)
		printf("Erase complete (%u bytes)\r\n", flash.erase_size);
	else
		printf("Erase failed (errno=%d)\r\n", rc);
}

static void print_menu(void)
{
	printf("\r\n");

	printf("|================ Embedded Flash Example ===============|\r\n");

	printf("|====================== Commands =======================|\r\n"
	       "| a uid                                                 |\r\n"
	       "|      Query embedded flash unique id                   |\r\n"
	       "| r offset size                                         |\r\n"
	       "|      Read 'size' bytes starting at 'offset'           |\r\n"
	       "| w offset str                                          |\r\n"
	       "|      Write 'str' to 'offset'                          |\r\n"
	       "| d offset                                              |\r\n"
	       "|      Erase page at 'offset'                           |\r\n"
	       "|      'all' to erase entire flash                      |\r\n"
	       "| h                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

static void _flash_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if (*buffer == 'h' || *buffer == 'H') {
		print_menu();
		return;
	}
	if (*(buffer + 1) != ' ') {
		printf("Commands can only be one caracter size\r\n");
		printf("%c%c\r\n", *buffer, *(buffer + 1));
		return;
	}
	switch(*buffer) {
	case 'r':
		_flash_read_arg_parser(buffer + 2, len - 2);
		break;
	case 'w':
		_flash_write_arg_parser(buffer + 2, len - 2);
		break;
	case 'a':
		_flash_query_arg_parser(buffer + 2, len - 2);
		break;
	case 'd':
		_flash_delete_arg_parser(buffer + 2, len - 2);
		break;
	default:
		printf("Command %c unknown\r\n", *buffer);
	}
}

int main (void)
{
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();
	_cmd_parser = _flash_cmd_parser;

	/* Output example information */
	console_example_info("Embedded Flash Example");

	/* Initialize flash driver */
	if (flashd_initialize(&flash, EEFC) < 0)
		trace_fatal("Flash initialization error!\r\n");
	printf("Flash Size: %u bytes\r\n", (unsigned)flash.total_size);
	printf("Flash Page Size: %u bytes\r\n", (unsigned)flash.page_size);
	printf("Flash Erase Size: %u bytes\r\n", (unsigned)flash.erase_size);
	printf("Flash Lock Count: %u bytes\r\n", (unsigned)flash.lock_count);
	printf("Flash GPNVM Count: %u bits\r\n", (unsigned)flash.gpnvm_count);

	print_menu();

	while (1) {
		cpu_idle();

		if (cmd_complete) {
			_cmd_parser(cmd_buffer, cmd_length);
			cmd_length = 0;
			cmd_complete = false;
		}
	}
}
