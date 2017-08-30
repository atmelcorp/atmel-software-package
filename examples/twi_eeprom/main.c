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
 * \page twi_eeprom TWI EEPROM Example
 *
 * \section Purpose
 *
 * This example indicates how to use the TWI with AT24 driver in order to
 * access data on a real AT24 device and on an emulated AT24 using a TWI slave
 * port.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XPLAINED, SAMA5D27-SOM1-EK, SAMA5D3-EK,
 * SAMA5D3-XPLAINED, SAMA5D4-EK, SAMA5D4-XPLAINED and SAM9xx5-EK.
 *
 * \section Descriptions
 *
 * This example shows how to configure the TWI in master and slave mode.
 * In master mode, the example can read or write from 2 devices: one real AT24
 * and one emulated AT24.
 * In slave mode, this example implements an emulated AT24C02 EEPROM.
 *
 * \section Usage
 *
 * -# Compile the application and connect the DBGU port of the evaluation board
 *    to the computer.
 * -# Open and configure a terminal application on PC
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Download the program inside the evaluation board and run it. Please refer to
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# Upon startup, the application will output the following line on the DBGU:
 *    \code
 *     -- Twi EEPROM Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Choose an item in the menu to test.
 *
 * \section References
 * - twi_eeprom/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for twi_eeprom example.
 */


/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "board_twi.h"
#include "trace.h"
#include "cpuidle.h"

#include "gpio/pio.h"
#include "i2c/twid.h"
#include "nvm/i2c/at24.h"

#include "mm/cache.h"
#include "serial/console.h"

#include "at24_emulator.h"
#include "peripherals/bus.h"
#include "config.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Defines
 *------------------------------------------------------------------------------*/

#ifdef BOARD_AT24_TWI_BUS
#define HAVE_AT24_DEVICE
#endif

/*------------------------------------------------------------------------------
 *         Local Types
 *------------------------------------------------------------------------------*/

typedef void (*_parser)(const uint8_t*, uint32_t);

/*------------------------------------------------------------------------------
 *         Local Constants
 *------------------------------------------------------------------------------*/

static const struct _at24_config at24_emulator_cfg = {
	.bus = AT24_EMU_MASTER_BUS,
	.addr = AT24_EMU_ADDR,
	.model = AT24_EMULATED_MODEL,
};

static struct _twi_slave_desc _slaved = {
	.twi = AT24_EMU_DEV,
	.addr = AT24_EMU_ADDR,
};

/*------------------------------------------------------------------------------
 *         Local Variables
 *------------------------------------------------------------------------------*/

static _parser _cmd_parser;
static volatile uint32_t cmd_length = 0;
static volatile bool cmd_complete = false;
CACHE_ALIGNED static uint8_t cmd_buffer[256];

#ifdef HAVE_AT24_DEVICE
static struct _at24* at24_device;
#endif
static struct _at24 at24_emulator;
static struct _at24* at24;

/*------------------------------------------------------------------------------
 *         Local Functions
 *------------------------------------------------------------------------------*/

/*
 *
 */
static void print_menu(void)
{
	const char* mode_str;
	enum _bus_transfer_mode mode;

	printf("\r\n");

	printf("|================= TWI EEPROM Example ==================|\r\n");

	printf("| I2C Address: 0x%02x                                     |\r\n",
	       at24->addr);
	printf("| Device: %-46s|\r\n", at24->desc->name);

	bus_ioctl(at24->bus, BUS_IOCTL_GET_TRANSFER_MODE, &mode);
	switch (mode) {
	case BUS_TRANSFER_MODE_POLLING:
		mode_str = "polling";
		break;
	case BUS_TRANSFER_MODE_ASYNC:
		mode_str = "async";
		break;
	case BUS_TRANSFER_MODE_DMA:
		mode_str = "DMA";
		break;
	default:
		mode_str = "unknown";
		break;
	}
	printf("| Emulated: %-44s|\r\n", at24 == &at24_emulator ? "yes" : "no");
	printf("| Mode: %-48s|\r\n", mode_str);
#ifdef CONFIG_HAVE_TWI_FIFO
	{
		bool _enabled;

		bus_ioctl(at24->bus, BUS_IOCTL_GET_FIFO_STATUS, &_enabled);
		printf("| FIFO: %-48s|\r\n", _enabled ? "enabled" : "disabled");
	}
#endif

	printf("|====================== Commands =======================|\r\n"
	       "| m polling                                             |\r\n"
	       "| m async                                               |\r\n"
	       "| m dma                                                 |\r\n"
	       "|      Select mode                                      |\r\n"
#ifdef CONFIG_HAVE_TWI_FIFO
	       "| f fifo                                                |\r\n"
	       "|      Toggle feature                                   |\r\n"
#endif
#ifdef HAVE_AT24_DEVICE
	       "| d device                                              |\r\n"
	       "|      Select real AT24 device                          |\r\n"
	       "| d emulator                                            |\r\n"
	       "|      Select emulated AT24 device on TWI slave         |\r\n"
#endif
	       "| r addr size                                           |\r\n"
	       "|      Read 'size' bytes starting at address 'addr'     |\r\n"
	       "| w addr str                                            |\r\n"
	       "|      Write 'str' to address 'addr'                    |\r\n");

	if (at24_has_serial(at24))
		printf("| a serial                                              |\r\n"
		       "|      Query device serial number                       |\r\n");

	if (at24_has_eui48(at24))
		printf("| a eui48                                               |\r\n"
		       "|      Query device EUI48                               |\r\n");

	if (at24_has_eui64(at24))
		printf("| a eui64                                               |\r\n"
		       "|      Query device EUI64                               |\r\n");

	printf("| h                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

static void console_handler(uint8_t key)
{
	switch (key) {
	case 0x7E:
	case '\r':
	case '\n':
		console_echo(key);
		cmd_buffer[cmd_length] = '\0';
		cmd_complete = true;
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

/*
 *
 */
static void _eeprom_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	unsigned int addr = strtol((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n Invalid address\r\n", buffer);
		return;
	}
	if (addr > 0xFF) {
		printf("Address 0x%x out of bound\r\n", (unsigned int)addr);
		return;
	}

	if (1+end_addr - (char*)buffer > len) {
		printf("No data given.\r\n");
		return;
	}
	len -= (end_addr+1) - (char*)buffer;
	memmove(cmd_buffer, (uint8_t*)end_addr+1, len);
	if (at24_write(at24, addr, cmd_buffer, len) == 0)
		printf("Write done.\r\n");
	else
		printf("Write failed!\r\n");
}

/*
 *
 */
static void _eeprom_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	char* end_length = NULL;
	unsigned long addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s\r\n Invalid address\r\n", buffer);
		return;
	}

	int length = strtol(end_addr, &end_length, 0);
	if (end_length == end_addr) {
		printf("Args: %s\r\n Invalid size\r\n",	buffer);
		return;
	}
	if (addr > 0xFF) {
		printf("Address 0x%x out of bound\r\n",
		       (unsigned int)addr);
		return;
	}
	if (at24_read(at24, addr, cmd_buffer, length) == 0)
		console_dump_frame(cmd_buffer, length);
	else
		printf("Read failed!\r\n");
}

/*
 *
 */
static void _eeprom_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	int i = 0;

	if (!strncmp((char*)buffer, "serial", 6)) {
		uint8_t serial[AT24_SERIAL_LENGTH];
		if (at24_read_serial(at24, serial)) {
			printf("serial: ");
			for (i = 0; i < AT24_SERIAL_LENGTH; i++)
				printf("%02x", (unsigned)serial[i]);
			printf("\r\n");
		} else {
			printf("Error while reading serial\r\n");
		}
		return;
	}

	if (!strncmp((char*)buffer, "eui48", 5)) {
		uint8_t eui48[EUI48_LENGTH];
		if (at24_read_eui48(at24, eui48)) {
			printf("EUI48: ");
			for (i = 0; i < EUI48_LENGTH; i++) {
				if (i > 0)
					printf(":");
				printf("%02x", (unsigned)eui48[i]);
			}
			printf("\r\n");
		} else {
			printf("Error while reading EUI48\r\n");
		}
		return;
	}

	if (!strncmp((char*)buffer, "eui64", 5)) {
		uint8_t eui64[EUI64_LENGTH];
		if (at24_read_eui64(at24, eui64)) {
			printf("EUI64: ");
			for (i = 0; i < EUI64_LENGTH; i++) {
				if (i > 0)
					printf(":");
				printf("%02x", (unsigned)eui64[i]);
			}
			printf("\r\n");
		} else {
			printf("Error while reading EUI64\r\n");
		}
		return;
	}

	printf("Invalid advanced command!\r\n");
}

static void _eeprom_select_emulator(void)
{
	enum _bus_transfer_mode mode;

	printf("Using AT24 emulator\r\n");
	at24 = &at24_emulator;

	/* In TWI slave mode, only polling mode is supported */
	printf("Using polling mode.\r\n");
	mode = BUS_TRANSFER_MODE_POLLING;
	bus_ioctl(at24->bus, BUS_IOCTL_SET_TRANSFER_MODE, &mode);
}

#ifdef HAVE_AT24_DEVICE
static void _eeprom_select_real_device(void)
{
	printf("Using AT24 device\r\n");
	at24 = at24_device;
}

static void _eeprom_toggle_device_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "emulator", 8)) {
		_eeprom_select_emulator();
		print_menu();
		return;
	}

	if (!strncmp((char*)buffer, "device", 8)) {
		_eeprom_select_real_device();
		print_menu();
		return;
	}

	printf("Invalid switch command!\r\n");
}
#endif

static void _eeprom_toggle_mode_arg_parser(const uint8_t* buffer, uint32_t len)
{
	enum _bus_transfer_mode mode;

	if (!strncmp((char*)buffer, "polling", 7)) {
		mode = BUS_TRANSFER_MODE_POLLING;
		printf("Using polling mode.\r\n");
	} else if (!strncmp((char*)buffer, "async", 5)) {
		mode = BUS_TRANSFER_MODE_ASYNC;
		printf("Using async mode.\r\n");
	} else if (!strncmp((char*)buffer, "dma", 3)) {
		mode = BUS_TRANSFER_MODE_DMA;
		printf("Using DMA mode.\r\n");
	} else {
		printf("Invalid mode command!\r\n");
	}

	bus_ioctl(at24->bus, BUS_IOCTL_SET_TRANSFER_MODE, &mode);
}

static void _eeprom_toggle_feature_arg_parser(const uint8_t* buffer, uint32_t len)
{
#ifdef CONFIG_HAVE_TWI_FIFO
	if (!strncmp((char*)buffer, "fifo", 4)) {
		bool _enabled;

		bus_ioctl(at24->bus, BUS_IOCTL_GET_FIFO_STATUS, &_enabled);
		if (!_enabled) {
			bus_ioctl(at24->bus, BUS_IOCTL_ENABLE_FIFO, NULL);
			printf("Enable FIFO use.\r\n");
		} else {
			bus_ioctl(at24->bus, BUS_IOCTL_DISABLE_FIFO, NULL);
			printf("Disable FIFO use.\r\n");
		}
		return;
	}
#endif

	printf("Invalid feature command!\r\n");
}

static void _eeprom_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if (*buffer == 'h' || *buffer == 'H' || *buffer == '?') {
		print_menu();
		return;
	}
	if (*(buffer+1) != ' ') {
		printf("Commands can only be one caracter size\r\n");
		return;
	}

	switch(*buffer) {
	case 'r':
	case 'R':
		_eeprom_read_arg_parser(buffer+2, len-2);
		break;
	case 'w':
	case 'W':
		_eeprom_write_arg_parser(buffer+2, len-2);
		break;
	case 'a':
	case 'A':
		_eeprom_query_arg_parser(buffer+2, len-2);
		break;
#ifdef HAVE_AT24_DEVICE
	case 'd':
	case 'D':
		_eeprom_toggle_device_arg_parser(buffer+2, len-2);
		break;
#endif /* HAVE_AT24_DEVICE */
	case 'm':
	case 'M':
		_eeprom_toggle_mode_arg_parser(buffer+2, len-2);
		break;
	case 'f':
	case 'F':
		_eeprom_toggle_feature_arg_parser(buffer+2, len-2);
		break;
	default:
		printf("Command '%c' unknown\r\n", *buffer);
	}
}

static void _configure_emulator(void)
{
	static struct _pin pins[] = AT24_EMU_PINS;

	pio_configure(pins, ARRAY_SIZE(pins));
	at24_emulator_initialize(&_slaved);
}

/*------------------------------------------------------------------------------
 *         Main
 *------------------------------------------------------------------------------*/

int main (void)
{
	/* Output example information */
	console_example_info("TWI EEPROM Example");

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	_cmd_parser = _eeprom_cmd_parser;

	/* configure AT24 master for emulator */
	at24_configure(&at24_emulator, &at24_emulator_cfg);

	/* Configure AT24 slave for emulator */
	_configure_emulator();

#ifdef HAVE_AT24_DEVICE
	at24_device = board_get_at24();
	_eeprom_select_real_device();
#else
	_eeprom_select_emulator();
#endif

	print_menu();
	while (1) {
		cpu_idle();
		if (cmd_complete && cmd_length > 0) {
			_cmd_parser(cmd_buffer, cmd_length);
			cmd_length = 0;
			cmd_complete = false;
		}
	}
}
