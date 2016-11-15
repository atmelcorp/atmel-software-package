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

/*
 * Tip: on evaluation boards such as SAMA5D2-XULT mind the Boot_Disable jumper,
 * as proper execution of this example requires the chip select signal from SoC
 * to memory to be effectively connected (Boot_Disable jumper removed).
 */

#include <stdint.h>

#include "board.h"
#include "board_spi.h"
#include "chip.h"

#include "bus/spi-bus.h"

#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/spid.h"

#include "misc/console.h"
#include "misc/cache.h"

#include "memories/at25.h"

#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFFER_SIZE   (1024)
#define READ_BUFFER_SIZE  (4 * 1024)

CACHE_ALIGNED static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
CACHE_ALIGNED static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;
static volatile uint32_t cmd_length = 0;
static volatile bool cmd_complete = false;

static struct _at25* at25drv;

static void console_handler(uint8_t key)
{
	/* already processing a command: ignore input */
	if (cmd_complete)
	       return;

	switch (key) {
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
	while (length > 0) {
		int chunk_size = length < READ_BUFFER_SIZE ? length : READ_BUFFER_SIZE;

		if(at25_read(at25drv, addr+offset, read_buffer, chunk_size)) {
			/* Read failed, no need to dump anything */
			return;
		}
		offset += chunk_size;
		length -= chunk_size;
		console_dump_frame(read_buffer, chunk_size);
	}
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

	if (1+end_addr - (char*)buffer > len) {
		printf("No data given.\r\n");
		return;
	}

	len -= (end_addr+1) - (char*)buffer;

	at25_write(at25drv, addr, (uint8_t*)end_addr+1, len);
}

static void _flash_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "device", 6)) {
		if (at25drv->desc) {
			at25_print_device_info(at25drv);
		} else {
			printf("No device detected!\r\n");
		}
	} else if (!strncmp((char*)buffer, "status", 6)) {
		uint32_t status = at25_read_status(at25drv);
		printf("AT25 chip status:\r\n"
		       "\t- Busy: %s\r\n"
		       "\t- Write Enabled: %s\r\n"
		       "\t- Software protection: %s\r\n"
		       "\t- Write protect pin: %s\r\n"
		       "\t- Erase/Program error: %s\r\n"
		       "\t- Sector Protection Register: %s\r\n"
		       "\t- Raw register value: 0x%X\r\n",
		       status & AT25_STATUS_RDYBSY_BUSY ? "yes":"no",
		       status & AT25_STATUS_WEL ? "yes":"no",
		       status & AT25_STATUS_SWP ? "Some/all":"none",
		       status & AT25_STATUS_WPP ? "inactive":"active",
		       status & AT25_STATUS_EPE ? "yes":"no",
		       status & AT25_STATUS_SPRL ? "locked":"unlocked",
		       (unsigned)status);
	}
}

static void _flash_delete_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	char* erase_type_str = NULL;
	unsigned long addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		if (!strncmp((char*)buffer, "all", 3)) {
			at25_erase_chip(at25drv);
		} else {
			printf("Args: %s\r\n"
			       "Invalid address\r\n",
			       buffer);
		}
		return;
	}

	uint32_t erase_length = 4096;

	erase_type_str = end_addr + 1;
	if (!strcmp("4k", erase_type_str) ||
	    !strcmp("4K", erase_type_str)) {
		erase_length = 4 * 1024;
	} else if (!strcmp("32k", erase_type_str) ||
	           !strcmp("32K", erase_type_str)) {
		erase_length = 32 * 1024;
	} else if (!strcmp("64k", erase_type_str) ||
	           !strcmp("64K", erase_type_str)) {
		erase_length = 64 * 1024;
	} else if (!strcmp("256k", erase_type_str) ||
	           !strcmp("256K", erase_type_str)) {
		erase_length = 256 * 1024;
	} else {
		printf("Args: %s\r\n"
		       "Invalid Erase type\r\n",
		       buffer);
		return;
	}
	at25_erase_block(at25drv, addr, erase_length);
}

static void _flash_mode_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "polling", 7)) {
		spi_bus_set_transfer_mode(at25drv->dev.bus, SPID_MODE_POLLING);
		printf("Use POLLING mode\r\n");
	} else if (!strncmp((char*)buffer, "async", 5)) {
		spi_bus_set_transfer_mode(at25drv->dev.bus, SPID_MODE_ASYNC);
		printf("Use ASYNC mode\r\n");
	} else if (!strncmp((char*)buffer, "dma", 3)) {
		spi_bus_set_transfer_mode(at25drv->dev.bus, SPID_MODE_DMA);
		printf("Use DMA mode\r\n");
	} else {
		printf("Args: %s\r\n"
			   "Invalid mode (polling, async, dma)\r\n", buffer);
	}
}

#ifdef CONFIG_HAVE_SPI_FIFO
static void _flash_feature_arg_parser(const uint8_t* buffer, uint32_t len)
{
	if (!strncmp((char*)buffer, "fifo", 4)) {
		if (!spi_bus_fifo_is_enabled(at25drv->dev.bus)) {
			spi_bus_fifo_enable(at25drv->dev.bus);
			printf("Enable FIFO\r\n");
		} else {
			spi_bus_fifo_disable(at25drv->dev.bus);
			printf("Disable FIFO\r\n");
		}
	}
}
#endif /* CONFIG_HAVE_SPI_FIFO */

static void print_menu(void)
{
	const char* mode_str;

	printf("\r\n");

	printf("|=============== SPI SerialFlash Example ===============|\r\n");

	printf("| Device: %-46s|\r\n", at25drv->desc ? at25drv->desc->name : "N/A");
	switch (spi_bus_get_transfer_mode(at25drv->dev.bus)) {
	case SPID_MODE_POLLING:
		mode_str = "polling";
		break;
	case SPID_MODE_ASYNC:
		mode_str = "async";
		break;
	case SPID_MODE_DMA:
		mode_str = "DMA";
		break;
	default:
		mode_str = "unknown";
		break;
	}
	printf("| Mode: %-48s|\r\n", mode_str);
#ifdef CONFIG_HAVE_SPI_FIFO
	printf("| FIFO: %-48s|\r\n", spi_bus_fifo_is_enabled(at25drv->dev.bus) ? "enabled" : "disabled");
#endif

	printf("|====================== Commands =======================|\r\n"
	       "| m polling                                             |\r\n"
	       "| m async                                               |\r\n"
	       "| m dma                                                 |\r\n"
	       "|      Select transfer mode                             |\r\n"
#ifdef CONFIG_HAVE_SPI_FIFO
	       "| f fifo                                                |\r\n"
	       "|      Enable/disable FIFO                              |\r\n"
#endif
	       "| a status                                              |\r\n"
	       "|      Query device status                              |\r\n"
	       "| a device                                              |\r\n"
	       "|      Query serial flash JEDEC info                    |\r\n"
	       "| r addr size                                           |\r\n"
	       "|      Read 'size' bytes starting at address 'addr'     |\r\n"
	       "| w addr str                                            |\r\n"
	       "|      Write 'str' to address 'addr'                    |\r\n"
	       "| d addr [4k|32k|64k|256k]                              |\r\n"
	       "|      Erase block containing the address 'addr'        |\r\n"
	       "|      The erase can be 4k, 32k, 64k or 256k            |\r\n"
	       "| h                                                     |\r\n"
	       "|      Print this menu                                  |\r\n"
	       "|=======================================================|\r\n");
}

static void _flash_cmd_parser(const uint8_t* buffer, uint32_t len)
{
	if (*buffer == 'h'||*buffer=='H') {
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
	case 'm':
		_flash_mode_arg_parser(buffer+2, len-2);
		break;
#ifdef CONFIG_HAVE_SPI_FIFO
	case 'f':
		_flash_feature_arg_parser(buffer+2, len-2);
		break;
#endif
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
	console_example_info("SPI Flash Example");

	/* retrieve pointer to AT25 device structure */
	at25drv = board_get_at25();

	print_menu();

	while (1) {
		irq_wait();

		if (cmd_complete && cmd_length > 0) {
			_cmd_parser(cmd_buffer, cmd_length);
			cmd_length = 0;
			cmd_complete = false;
		}
	}
}
