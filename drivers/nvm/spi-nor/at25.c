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

#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "intmath.h"
#include "nvm/spi-nor/at25.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "bus/spi-bus.h"
#include <stdio.h>
#include <assert.h>
#include <errno.h>

/*----------------------------------------------------------------------------
 *        Local Constants
 *----------------------------------------------------------------------------*/

/** Read array command code. */
#define CMD_READ_ARRAY             0x0B
/** Read array (low frequency) command code. */
#define CMD_READ_ARRAY_LF          0x03
/** Block erase command code (4K block). */
#define CMD_BLOCK_ERASE_4K         0x20
/** Block erase command code (32K block). */
#define CMD_BLOCK_ERASE_32K        0x52
/** Block erase command code (64K/256K block). */
#define CMD_BLOCK_ERASE_64K_256K   0xD8
/** Chip erase command code 1. */
#define CMD_CHIP_ERASE_1           0x60
/** Chip erase command code 2. */
#define CMD_CHIP_ERASE_2           0xC7
/** Byte/page program command code. */
#define CMD_BYTE_PAGE_PROGRAM      0x02
/** Sequential program mode command code 1. */
#define CMD_SEQUENTIAL_PROGRAM_1   0xAD
/** Sequential program mode command code 2. */
#define CMD_SEQUENTIAL_PROGRAM_2   0xAF
/** Write enable command code. */
#define CMD_WRITE_ENABLE           0x06
/** Write disable command code. */
#define CMD_WRITE_DISABLE          0x04
/** Protect sector command code. */
#define CMD_PROTECT_SECTOR         0x36
/** Unprotect sector command code. */
#define CMD_UNPROTECT_SECTOR       0x39
/** Read sector protection registers command code. */
#define CMD_READ_SECTOR_PROT       0x3C
/** Read status register command code. */
#define CMD_READ_STATUS            0x05
/** Write status register command code. */
#define CMD_WRITE_STATUS           0x01
/** Read manufacturer and device ID command code. */
#define CMD_READ_JEDEC_ID          0x9F
/** Deep power-down command code. */
#define CMD_DEEP_PDOWN             0xB9
/** Resume from deep power-down command code. */
#define CMD_RES_DEEP_PDOWN         0xAB

/* Enter 4-BYTE ADDRESS mode  */
#define CMD_ENTER_4ADDR_MODE       0xB7
/* Exit 4-BYTE ADDRESS mode  */
#define CMD_EXIT_4ADDR_MODE        0xE9

/** Maximum size in 3-byte addressing mode */
#define MODE_3B_MAX_SIZE           (1 << 24)

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static uint32_t _at25_compute_addr(struct _at25* at25, uint8_t* cmd,
				   uint32_t addr)
{
	assert(at25);

	switch (at25->addressing) {
	case AT25_ADDRESS_4_BYTES:
		cmd[0] = (addr & 0xFF000000) >> 24;
		cmd[1] = (addr & 0x00FF0000) >> 16;
		cmd[2] = (addr & 0x0000FF00) >> 8;
		cmd[3] = (addr & 0x000000FF);
		return 4;
	case AT25_ADDRESS_3_BYTES:
	default:
		cmd[0] = (addr & 0x00FF0000) >> 16;
		cmd[1] = (addr & 0x0000FF00) >> 8;
		cmd[2] = (addr & 0x000000FF);
		return 3;
	}
}

static uint8_t _at25_read_status(struct _at25* at25)
{
	assert(at25);
	uint8_t at25_status;
	uint8_t opcode = CMD_READ_STATUS;
	struct _buffer buf[2] = {
		{
			.data = &opcode,
			.size = sizeof(opcode),
			.attr = SPID_BUF_ATTR_WRITE,
		},
		{
			.data = &at25_status,
			.size = sizeof(at25_status),
			.attr = SPID_BUF_ATTR_READ | SPID_BUF_ATTR_RELEASE_CS,
		},
	};

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, buf, 2, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	return at25_status;
}

static void _at25_wait(struct _at25* at25)
{
	if (_at25_read_status(at25) & AT25_STATUS_RDYBSY_BUSY) {
		trace_debug("at25: Device in busy status, Waiting...\r\n");
		while (_at25_read_status(at25) & AT25_STATUS_RDYBSY_BUSY);
		trace_debug("at25: Device ready.\r\n");
	}
}

static int _at25_check_writable(struct _at25* at25)
{
	assert(at25);

	uint8_t status;
	status = _at25_read_status(at25) & (AT25_STATUS_RDYBSY_BUSY | AT25_STATUS_SWP);
	if (status & AT25_STATUS_RDYBSY_BUSY) {
		trace_debug("at25: Device %s is busy\r\n", at25->desc->name);
		return -EBUSY;
	}
	if (status & AT25_STATUS_SWP) {
		trace_error("at25: Device %s is write protected\r\n", at25->desc->name);
		return -EPERM;
	}
	return 0;
}

static void _at25_enable_write(struct _at25* at25)
{
	assert(at25);

	uint8_t opcode = CMD_WRITE_ENABLE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);
}

static void _at25_disable_write(struct _at25* at25)
{
	assert(at25);

	uint8_t opcode = CMD_WRITE_DISABLE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);
}

static void _at25_write_status(struct _at25* at25, uint8_t value)
{
	assert(at25);

	uint8_t cmd[2] = { CMD_WRITE_STATUS, value };
	struct _buffer out = {
		.data = cmd,
		.size = 2,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};

	_at25_enable_write(at25);

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	_at25_disable_write(at25);
}

static void _at25_enter_4addr_mode(struct _at25* at25)
{
	assert(at25);

	_at25_enable_write(at25);

	uint8_t opcode = CMD_ENTER_4ADDR_MODE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};
	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	at25->addressing = AT25_ADDRESS_4_BYTES;
	spi_bus_wait_transfer(at25->dev.bus);
}

static void _at25_exit_4addr_mode(struct _at25* at25)
{
	assert(at25);

	_at25_enable_write(at25);

	uint8_t opcode = CMD_EXIT_4ADDR_MODE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};
	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	at25->addressing = AT25_ADDRESS_3_BYTES;
	spi_bus_wait_transfer(at25->dev.bus);
}

static void _at25_set_addressing(struct _at25* at25)
{
	assert(at25);
	assert(at25->desc);

	if (at25->desc->size > MODE_3B_MAX_SIZE) {
		_at25_enter_4addr_mode(at25);
	} else {
		_at25_exit_4addr_mode(at25);
	}
}

static uint32_t _at25_read_jedec_id(struct _at25* at25)
{
	assert(at25);
	uint8_t opcode = CMD_READ_JEDEC_ID;
	uint8_t _jedec_id[3];
	struct _buffer buf[2] = {
		{
			.data = &opcode,
			.size = 1,
			.attr = SPID_BUF_ATTR_WRITE,
		},
		{
			.data = _jedec_id,
			.size = 3,
			.attr = SPID_BUF_ATTR_READ | SPID_BUF_ATTR_RELEASE_CS,
		},
	};

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, buf, 2, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	return (_jedec_id[2] << 16) | (_jedec_id[1] << 8) | _jedec_id[0];
}

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

void at25_wait(struct _at25* at25)
{
	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	_at25_wait(at25);

	spi_bus_stop_transaction(at25->dev.bus);
}

int at25_configure(struct _at25* at25)
{
	uint32_t jedec_id;

	/* Configure chip select */
	spi_bus_configure_cs(at25->dev.bus, at25->dev.chip_select, at25->dev.bitrate,
	                     at25->dev.delay.bs, at25->dev.delay.bct, at25->dev.spi_mode);

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	jedec_id = _at25_read_jedec_id(at25);
	trace_debug("at25: read JEDEC ID 0x%08x.\r\n", (unsigned)jedec_id);
	at25->desc = spi_nor_find(jedec_id);
	if (!at25->desc) {
		spi_bus_stop_transaction(at25->dev.bus);
		return -ENODEV;
	}

	_at25_set_addressing(at25);

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

int at25_read_jedec_id(struct _at25* at25, uint32_t *jedec_id)
{
	assert(at25);

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	*jedec_id = _at25_read_jedec_id(at25);

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

uint8_t at25_read_status(struct _at25* at25)
{
	assert(at25);
	uint8_t status;
	uint8_t at25_status;
	uint8_t opcode = CMD_READ_STATUS;
	struct _buffer buf[2] = {
		{
			.data = &opcode,
			.size = sizeof(opcode),
			.attr = SPID_BUF_ATTR_WRITE,
		},
		{
			.data = &at25_status,
			.size = sizeof(status),
			.attr = SPID_BUF_ATTR_READ | SPID_BUF_ATTR_RELEASE_CS,
		},
	};

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, buf, 2, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	spi_bus_stop_transaction(at25->dev.bus);

	return at25_status;
}

int at25_set_protection(struct _at25* at25, bool enable)
{
	assert(at25);

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	if (enable) {
		/* Perform a global protect command */
		_at25_write_status(at25, 0x7F);
	} else {
		/* Get the status register value to check the current protection */
		if ((_at25_read_status(at25) & AT25_STATUS_SWP) == AT25_STATUS_SWP_PROTNONE) {
			spi_bus_stop_transaction(at25->dev.bus);
			return 0;
		}

		/* Perform a global unprotect command */
		_at25_write_status(at25, 0x0);
		_at25_disable_write(at25);

		/* Check the new status */
		if (_at25_read_status(at25) & (AT25_STATUS_SPRL | AT25_STATUS_SWP)) {
			spi_bus_stop_transaction(at25->dev.bus);
			return -EPERM;
		}
	}
	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

void at25_print_device_info(struct _at25* at25)
{
	assert(at25);

	if (!at25->desc)
		return;

	printf("Device info:\r\n");
	printf("\t- JEDEC ID:\t\t\t0x%X\r\n",
	       (unsigned)at25->desc->jedec_id);
	printf("\t- Manufacturer ID:\t\t0x%X\r\n",
	       (unsigned)SPINOR_JEDEC_MANUF(at25->desc->jedec_id));
	printf("\t- Device Family Code:\t\t0x%X\r\n",
	       (unsigned)SPINOR_JEDEC_FAMILY(at25->desc->jedec_id));
	printf("\t- Device Density Code:\t\t0x%X\r\n",
	       (unsigned)SPINOR_JEDEC_DENSITY(at25->desc->jedec_id));
	printf("\t- Device Sub Code:\t\t0x%X\r\n",
	       (unsigned)SPINOR_JEDEC_SUBCODE(at25->desc->jedec_id));
	printf("\t- Device Product Version:\t0x%X\r\n",
	       (unsigned)SPINOR_JEDEC_VERSION(at25->desc->jedec_id));
	printf("\t- Device Name:\t\t\t%s\r\n", at25->desc->name);
	printf("\t- Device Size:\t\t\t%lu bytes\r\n", at25->desc->size);
	printf("\t- Device Page Size:\t\t%lu bytes\r\n", at25->desc->page_size);
	printf("\t- Block Erase Supported:\t");
	if (at25->desc->flags & SPINOR_FLAG_ERASE_4K)
		printf("4KB ");
	if (at25->desc->flags & SPINOR_FLAG_ERASE_32K)
		printf("32KB ");
	if (at25->desc->flags & SPINOR_FLAG_ERASE_64K)
		printf("64KB ");
	if (at25->desc->flags & SPINOR_FLAG_ERASE_256K)
		printf("256KB ");
	printf("\r\n");
}

void at25_print_device_status(struct _at25* at25)
{
	uint32_t status = at25_read_status(at25);
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

bool at25_is_busy(struct _at25* at25)
{
	bool busy;

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	busy = (_at25_read_status(at25) & AT25_STATUS_RDYBSY_BUSY) != 0;

	spi_bus_stop_transaction(at25->dev.bus);

	return busy;
}

int at25_read(struct _at25* at25, uint32_t addr, uint8_t* data, uint32_t length)
{
	if (addr > at25->desc->size)
		return -EINVAL;

	trace_debug("at25: Start flash read at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));

	assert(at25);

	uint8_t cmd[6];
	struct _buffer buf[2] = {
		{
			.data = cmd,
			.size = 1,
			.attr = SPID_BUF_ATTR_WRITE,
		},
		{
			.data = data,
			.size = length,
			.attr = SPID_BUF_ATTR_READ | SPID_BUF_ATTR_RELEASE_CS,
		},
	};

	cmd[0] = CMD_READ_ARRAY;
	buf[0].size += _at25_compute_addr(at25, &cmd[1], addr);
	buf[0].size += 1; /* one dummy byte */

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, buf, 2, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

int at25_erase_chip(struct _at25* at25)
{
	trace_debug("at25: Start flash reset all block will be erased\r\n");

	assert(at25);

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	int status = _at25_check_writable(at25);
	if (status < 0) {
		spi_bus_stop_transaction(at25->dev.bus);
		return status;
	}

	uint8_t cmd = CMD_CHIP_ERASE_1;
	struct _buffer out = {
		.data = &cmd,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};

	_at25_enable_write(at25);

	spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	_at25_disable_write(at25);

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

int at25_erase_block(struct _at25* at25, uint32_t addr, uint32_t length)
{
	trace_debug("at25: Start flash erase at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));

	assert(at25);

	if ((addr + length) > at25->desc->size)
		return -EINVAL;

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	int status = _at25_check_writable(at25);
	if (status < 0) {
		spi_bus_stop_transaction(at25->dev.bus);
		return status;
	}

	uint8_t cmd[5];

	struct _buffer out = {
		.data = cmd,
		.size = 1,
		.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
	};

	uint8_t command;
	uint32_t flags = at25->desc->flags;

	switch (length) {
	case 256 * 1024:
		if (flags & SPINOR_FLAG_ERASE_256K) {
			command = CMD_BLOCK_ERASE_64K_256K;
			trace_debug("at25: Will apply 256K erase\r\n");
		} else {
			trace_error("at25: 256K Erase not supported\r\n");
			status = -EINVAL;
		}
		break;
	case 64 * 1024:
		if (flags & SPINOR_FLAG_ERASE_64K) {
			command = CMD_BLOCK_ERASE_64K_256K;
			trace_debug("at25: Will apply 64K erase\r\n");
		} else {
			trace_error("at25: 64K Erase not supported\r\n");
			status = -EINVAL;
		}
		break;
	case 32 * 1024:
		if (flags & SPINOR_FLAG_ERASE_32K) {
			command = CMD_BLOCK_ERASE_32K;
			trace_debug("at25: Will apply 32K erase\r\n");
		} else {
			trace_error("at25: 32K Erase not supported\r\n");
			status = -EINVAL;
		}
		break;
	case 4 * 1024:
		if (flags & SPINOR_FLAG_ERASE_4K) {
			command = CMD_BLOCK_ERASE_4K;
			trace_debug("at25: Will apply 4K erase\r\n");
		} else {
			trace_error("at25: 4K Erase not supported\r\n");
			status = -EINVAL;
		}
		break;
	default:
		status = -EINVAL;
	}

	if (status < 0) {
		spi_bus_stop_transaction(at25->dev.bus);
		return status;
	}

	cmd[0] = command;
	out.size += _at25_compute_addr(at25, &cmd[1], addr);

	trace_debug("at25: Clearing block at addr 0x%x\r\n", (unsigned int)addr);

	_at25_enable_write(at25);

	status = spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, &out, 1, NULL, NULL);
	spi_bus_wait_transfer(at25->dev.bus);

	if (_at25_read_status(at25) & AT25_STATUS_EPE) {
		spi_bus_stop_transaction(at25->dev.bus);
		return -EIO;
	}

	_at25_wait(at25);
	_at25_disable_write(at25);

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}

int at25_write(struct _at25* at25, uint32_t addr, const uint8_t* data, uint32_t length)
{
	uint8_t cmd[6];

	if (addr > at25->desc->size)
		return -EINVAL;

	trace_debug("at25: Start flash write at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));
	assert(at25);
	assert(data);

	while (spi_bus_transaction_pending(at25->dev.bus));
	spi_bus_start_transaction(at25->dev.bus);

	int status = _at25_check_writable(at25);
	if  (status < 0) {
		spi_bus_stop_transaction(at25->dev.bus);
		return status;
	}

	/* Retrieve device page size */
	uint32_t page_size = at25->desc->page_size;

	struct _buffer buf[2] = {
		{
			.data = cmd,
			/* .size, */
			.attr = SPID_BUF_ATTR_WRITE,
		},
		{
			.data = (uint8_t*)data,
			/* .size, */
			.attr = SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_RELEASE_CS,
		}
	};

	while (length > 0) {
		/* Compute number of bytes to program in page */
		uint32_t write_size;
		write_size = min_u32(length, page_size - (addr % page_size));

		_at25_wait(at25);

		_at25_enable_write(at25);

		cmd[0] = CMD_BYTE_PAGE_PROGRAM;
		buf[0].size = 1;
		if (SPINOR_JEDEC_MANUF(at25->desc->jedec_id) == SPINOR_MANUF_SST) {
			cmd[0] = CMD_SEQUENTIAL_PROGRAM_1;
			buf[0].size++;
		}
		buf[0].size += _at25_compute_addr(at25, &cmd[1], addr);
		buf[1].size = write_size;

		spi_bus_transfer(at25->dev.bus, at25->dev.chip_select, buf, 2, NULL, NULL);
		spi_bus_wait_transfer(at25->dev.bus);

		if (_at25_read_status(at25) & AT25_STATUS_EPE) {
			spi_bus_stop_transaction(at25->dev.bus);
			return -EIO;
		}

		length -= write_size;
		buf[1].data += write_size;
		addr += write_size;

		_at25_disable_write(at25);

	}

	spi_bus_stop_transaction(at25->dev.bus);

	return 0;
}
