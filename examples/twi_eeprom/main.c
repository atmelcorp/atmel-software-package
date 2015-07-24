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
#include "peripherals/flexcom.h"
#include "peripherals/twid.h"
#include "peripherals/xdmad.h"

#include "memories/at24.h"

#include "misc/console.h"

#include "memories/at25.h"

#include "mutex.h"
#include "timer.h"
#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFFER_SIZE  256
#define READ_BUFFER_SIZE  256

typedef void (*_parser)(const uint8_t*, uint32_t);

static const struct _pin at24_pins[] = AT24_PINS;

ALIGNED(32) static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
ALIGNED(32) static uint8_t read_buffer[READ_BUFFER_SIZE];

static _parser _cmd_parser;
static uint32_t cmd_index = 0;

struct _at24 at24_drv = {
	.desc = AT24_DESC
};
struct _twi_desc at24_twid = {
	.addr = AT24_ADDR,
	.freq = AT24_FREQ,
	.transfert_mode = TWID_MODE_DMA
};

mutex_t lock = 0;

static void console_handler(void)
{
	static uint32_t index = 0;
	uint8_t key;
	if (!console_is_rx_ready())
		return;
	key = console_get_char();
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

static void _eeprom_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	unsigned int addr = strtol((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n"
		       "Invalid address\r\n",
			buffer);
		return;
	}
	if (addr > 0xFF) {
		printf("Address 0x%x out of bound\r\n",
		       (unsigned int)addr);
		return;
	}

	if (1+end_addr - (char*)buffer > len) {
		printf("No data given.\r\n");
		return;
	}

	len -= (end_addr+1) - (char*)buffer;

	at24_write_eep(&at24_drv, addr, (uint8_t*)end_addr+1, len);
}

static void _eeprom_read_arg_parser(const uint8_t* buffer, uint32_t len)
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
	if (addr > 0xFF) {
		printf("Address 0x%x out of bound\r\n",
		       (unsigned int)addr);
		return;
	}

	at24_read_eep(&at24_drv, addr, read_buffer, length);
	console_dump_frame(read_buffer, length);
}

static void print_menu(void)
{
	printf("Spi serial flash example mini-console:\r\n\r\n"
	       "|===========        Commands        ====================|\r\n"
	       "| a serial                                              |\r\n"
	       "|      Query device serial number                       |\r\n"
	       "| a mac                                                 |\r\n"
	       "|      Qeury device mac addr                            |\r\n"
	       "| r addr size                                           |\r\n"
	       "|      Read 'size' octets starting from address 'addr'  |\r\n"
	       "| w addr str                                            |\r\n"
	       "|      Write 'str' to address 'addr'                    |\r\n"
	       "| m                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

static void _eeprom_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	const char *serial_lbl = "serial";
	const char *mac_lbl = "mac";
	int i = 0;

	if (!strncmp((char*)buffer, serial_lbl, 6)) {
		at24_get_serial_number(&at24_drv);
		printf("serial number: ");
		for (i = 0; i < sizeof(at24_drv.serial_number); ++i) {
			printf("%u",
			       (unsigned char)at24_drv.serial_number[i]);
		}
		printf("\r\n");
	} else if (!strncmp((char*)buffer, mac_lbl, 3)) {
		at24_get_mac_address(&at24_drv);
		printf("MAC addr: ");
		for (i = 0; i < sizeof(at24_drv.mac_addr_48); i+=2) {
			printf("%s%02X:%02X",
			       (i != 0 ? ":" : ""),
			       (unsigned int)at24_drv.mac_addr_48[i],
			       (unsigned int)at24_drv.mac_addr_48[i+1]);
		}
		printf("\r\n");
	}
}

static void _eeprom_cmd_parser(const uint8_t* buffer, uint32_t len)
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
	case 'r':
		_eeprom_read_arg_parser(buffer+2, len-2);
		break;
	case 'w':
		_eeprom_write_arg_parser(buffer+2, len-2);
		break;
	case 'a':
		_eeprom_query_arg_parser(buffer+2, len-2);
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
	_cmd_parser = _eeprom_cmd_parser;

	/* Clear console */
	xdmad_initialize(false);
	printf("-- Twi EEPROM Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME " --\n\r"
	       "-- Compiled: " __DATE__ " at " __TIME__ " --\n\r");

	/* configure spi serial flash pins */
	pio_configure(at24_pins, ARRAY_SIZE(at24_pins));

	at24_configure(&at24_drv, &at24_twid);

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
