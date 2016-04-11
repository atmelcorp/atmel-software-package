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
 * This example indicates how to use the TWI with AT24MAC driver in order to
 * access data on a real AT24MAC device and on an emulated ST24MAC using a
 * TWI slave port.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XULT.
 *
 * Requirements before running this example on SAMA5D2-XULT:
 * Connect SDA1 (J22 pin 8) and SDA0 (J20 pin 10) on the board.
 * Connect SCL1 (J22 pin 7) and SD1 (J20 pin 9) on the board.
 *
 * \section Descriptions
 *
 * This example shows how to configure the TWI in master and slave mode.
 * In master mode, the example can read or write from 2 devices: one real AT24MAC
 * and one emulated AT24MAC.
 * In slave mode, this example implements an emulated AT24MAC EEPROM.
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

#include <stdint.h>

#include "board.h"
#include "chip.h"

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/twid.h"
#include "peripherals/xdmad.h"

#include <cortex-a/mmu.h>
#include <cortex-a/cp15.h>

#include "memories/at24.h"

#include "misc/console.h"

#include "memories/at25.h"

#include "trace.h"
#include "mutex.h"
#include "timer.h"
#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Defines
 *------------------------------------------------------------------------------*/

#define AT24_EMULATOR 1
#define PIT_PERIOD        1000

#define CMD_BUFFER_SIZE  256
#define READ_BUFFER_SIZE  256

/*------------------------------------------------------------------------------
 *         Local Variables
 *------------------------------------------------------------------------------*/

static uint8_t _device = 0; // Used to determine if the master communicate
                            // with the emulator or the real device

typedef void (*_parser)(const uint8_t*, uint32_t);

static const struct _pin at24_pins[] = AT24_PINS;

ALIGNED(L1_CACHE_BYTES) static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
ALIGNED(L1_CACHE_BYTES) static uint8_t read_buffer[READ_BUFFER_SIZE];

static _parser _cmd_parser;
static uint32_t cmd_index = 0;

struct _at24 at24_drv = {
	.desc = AT24_DESC,
	.addr = AT24_EEP_ADDR,
	.sn_addr = AT24_SN_ADDR,
	.sn_offset = AT24_SN_OFFSET,
	.eui_offset = AT24_EUI48_OFFSET,
};
struct _twi_desc at24_twid = {
	.addr = AT24_ADDR,
	.freq = AT24_FREQ,
#ifdef CONFIG_SOC_SAMA5D4
	//.transfert_mode = TWID_MODE_ASYNC
	.transfert_mode = TWID_MODE_POLLING
#else
	.transfert_mode = TWID_MODE_DMA
#endif
};

mutex_t lock = 0;

/*----------------------------------------------------------------------------
 *        Slave definitions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
/* =================== TWI slave device definition ============== */
/* twi_slave examples mimics a serial memory with TWI interface. */
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI0_IOS1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWIHS0)
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
/* =================== TWI slave device definition ============== */
/* twi_slave examples mimics a serial memory with TWI interface. */
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWI1)
#else
#error Unsupported board...
#endif

/** Slave address of the device on TWI bus. */
#define TWI_SLAVE_EEP_ADDR 0x53
/** TWI slave serial memory pages (example AT24C02)*/
#define TWI_SLAVE_EEP_PAGES 16
/** TWI slave serial memory page size (example AT24C02)*/
#define TWI_SLAVE_EEP_PAGE_SIZE 16

/** The slave device instance*/
struct _slave_device_driver
{
	/** Page address of the slave device*/
	uint16_t page_addr;
	/** Offset of the memory access*/
	uint16_t offset;
	/** Read address of the request*/
	uint8_t acquire_addr;
	/** Memory buffer*/
	uint8_t memory[TWI_SLAVE_EEP_PAGE_SIZE * TWI_SLAVE_EEP_PAGES];
};

static const struct _pin twi_slave_pins[] = TWI_SLAVE_PINS;

/** instance of TWI slave device */
static struct _slave_device_driver emulate_driver;

/*----------------------------------------------------------------------------
 *        Local Slave functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for TWI slave interrupt.
 *
 *  Handle process TWI master's requests.
 */
static void twi_slave_handler(void)
{
	uint32_t status;
	Twi *twi = TWI_SLAVE_ADDR;

	status = twi_get_status(twi);

	if ((status & TWI_SR_SVACC) == TWI_SR_SVACC) {
		if (emulate_driver.acquire_addr == 0) {
			twi_disable_it(twi, TWI_IDR_SVACC);
			twi_enable_it(twi, TWI_IER_RXRDY |
					TWI_IER_EOSACC |
					TWI_IER_SCL_WS);
			emulate_driver.acquire_addr++;
			emulate_driver.page_addr = 0;
			emulate_driver.offset = 0;
		}

		if ((status & TWI_SR_GACC) == TWI_SR_GACC) {
			trace_debug("General Call Treatment, not treated\r\n");
		} else if ((status & TWI_SR_SVREAD) == TWI_SR_SVREAD) {
			/*Slave Read */
			if ((status & (TWI_SR_TXRDY | TWI_SR_NACK)) == TWI_SR_TXRDY) {
				if (emulate_driver.acquire_addr == 2) {
					/* Write one byte of data from slave to master device */
					twi_write_byte(twi, emulate_driver.memory[emulate_driver.page_addr + emulate_driver.offset]);
					emulate_driver.offset++;
				}
			}
		} else {
			/*Slave Write*/
			if ((status & TWI_SR_RXRDY) == TWI_SR_RXRDY) {
				if (emulate_driver.acquire_addr == 1) {
					/* Acquire MSB address */
					emulate_driver.page_addr = twi_read_byte(twi);
					emulate_driver.acquire_addr++;
				} else {
					/* Read one byte of data from master to slave device */
					emulate_driver.memory[emulate_driver.page_addr + emulate_driver.offset] = twi_read_byte(twi);
					emulate_driver.offset++;
				}
			}
		}
	} else {
		if ((status & (TWI_SR_EOSACC | TWI_SR_TXCOMP)) ==
				(TWI_SR_EOSACC | TWI_SR_TXCOMP)) {
			/* End of transfer, end of slave access */
			emulate_driver.offset = 0;
			emulate_driver.acquire_addr = 0;
			emulate_driver.page_addr = 0;
			twi_enable_it(twi, TWI_SR_SVACC);
			twi_disable_it(twi, TWI_IDR_RXRDY |
					TWI_IDR_EOSACC |
					TWI_IDR_SCL_WS);
		}
	}
}

static void console_handler(uint8_t key)
{
	static uint32_t index = 0;
	if (mutex_try_lock(&lock))
		return;
	if (index >= CMD_BUFFER_SIZE) {
		printf("\r\nWARNING! command buffer size exceeded, "
		       "reseting\r\n");
		index = 0;
	}
	console_echo(key);
	switch (key) {
	case 0x7E:
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

/*
 *
 */
static void _eeprom_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	uint8_t status;
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
	status = at24_write_eep(&at24_drv, addr, (uint8_t*)end_addr+1, len);
	if(!status) printf("Write done.\r\n");;
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
	at24_read_eep(&at24_drv, addr, read_buffer, length);
	console_dump_frame(read_buffer, length);
}

/*
 *
 */
static void print_menu(void)
{
	printf("\r\n\r\n Twi mode ");
	switch(at24_twid.transfert_mode) {
	case TWID_MODE_POLLING:
		printf("POLLING \r\n");
		break;
	case TWID_MODE_FIFO:
		printf("FIFO \r\n");
		break;
	case TWID_MODE_ASYNC:
		printf("ASYNC \r\n");
		break;
	case TWID_MODE_DMA:
		printf("DMA \r\n");
		break;
	}
	printf("twi eeprom example mini-console:\r\n\r\n"
	       "|===========        Commands        ====================|\r\n"
	       "| a serial                                              |\r\n"
	       "|      Query device serial number                       |\r\n"
	       "| a mac                                                 |\r\n"
	       "|      Query device mac addr                            |\r\n"
	       "| r addr size                                           |\r\n"
	       "|      Read 'size' octets starting from address 'addr'  |\r\n"
	       "| w addr str                                            |\r\n"
	       "|      Write 'str' to address 'addr'                    |\r\n"
	       "| s device (default)                                    |\r\n"
	       "|      Select at24 device                               |\r\n"
	       "| s emulator                                            |\r\n"
	       "|      Select to TWI slave device emulating at24        |\r\n"
	       "| m                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

/*
 *
 */
static void _eeprom_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	const char *serial_lbl = "serial";
	const char *mac_lbl = "mac";
	uint8_t status;
	int i = 0;

	if (_device == AT24_EMULATOR) {
		printf("Serial feature not emulated...\r\n");
		return;
	}
	if (!strncmp((char*)buffer, serial_lbl, 6)) {
		status = at24_get_serial_number(&at24_drv);
		if(status == TWID_SUCCESS) {
			printf("serial number: ");
			for (i = 0; i < sizeof(at24_drv.serial_number); ++i) {
				printf("%u", (unsigned char)at24_drv.serial_number[i]);
			}
		}
		else printf("--E-- Error twi ");
		printf("\r\n");
	} else if (!strncmp((char*)buffer, mac_lbl, 3)) {
		status = at24_get_mac_address(&at24_drv);
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

static void _eeprom_toggle_device_arg_parser(const uint8_t* buffer, uint32_t len)
{
	const char *emulator_lbl = "emulator";
	const char *device_lbl = "device";

	if (!strncmp((char*)buffer, emulator_lbl, 8)) {
		_device = AT24_EMULATOR;
		at24_drv.addr = TWI_SLAVE_EEP_ADDR;
		printf("Use AT24 emulator\r\n");
	} else if (!strncmp((char*)buffer, device_lbl, 8)) {
		_device = 0;
		at24_drv.addr = AT24_EEP_ADDR;
		printf("Use AT24 device\r\n");
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
	case 's':
		_eeprom_toggle_device_arg_parser(buffer+2, len-2);
		break;
	default:
		printf("Command %c unknown\r\n", *buffer);
	}
}

/*------------------------------------------------------------------------------
 *         Main
 *------------------------------------------------------------------------------*/

int main (void)
{
	uint32_t i;
	uint32_t twi_id;

	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console();

#ifndef VARIANT_DDRAM
	mmu_initialize();
	cp15_icache_invalidate();
	cp15_dcache_invalidate();
	cp15_enable_icache();
	cp15_enable_mmu();
	cp15_enable_dcache();
#endif

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	_cmd_parser = _eeprom_cmd_parser;

	xdmad_initialize(false);
	printf("-- Twi EEPROM Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME " --\n\r"
	       "-- Compiled: " __DATE__ " at " __TIME__ " --\n\r");

	/* configure twi flash pins */
	pio_configure(at24_pins, ARRAY_SIZE(at24_pins));
	at24_configure(&at24_drv, &at24_twid);

	/* Configure TWI as slave */
	for (i=0 ; i < sizeof(emulate_driver.memory) ; i++)
		emulate_driver.memory[i] = i;
	emulate_driver.offset = 0;
	emulate_driver.acquire_addr = 0;
	emulate_driver.page_addr = 0;

	pio_configure(twi_slave_pins, ARRAY_SIZE(twi_slave_pins));

	twi_id = get_twi_id_from_addr(TWI_SLAVE_ADDR);
	pmc_enable_peripheral(twi_id);

	/* Configure TWI as slave */
	twi_configure_slave(TWI_SLAVE_ADDR, TWI_SLAVE_EEP_ADDR);
	trace_debug("TWI is in slave mode\n\r");

	/* Clear receipt buffer */
	(void)twi_read_byte(TWI_SLAVE_ADDR);

	aic_set_source_vector(twi_id, twi_slave_handler);
	twi_enable_it(TWI_SLAVE_ADDR, TWI_SR_SVACC);
	aic_enable(twi_id);

	trace_debug("Device act as a serial memory with TWI interface." \
		" (Device address: 0x%02x)\n\r", TWI_SLAVE_EEP_ADDR);

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
