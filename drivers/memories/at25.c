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
#include "memories/at25.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/spid.h"
#include "peripherals/spi.h"
#include <stdio.h>
#include <assert.h>

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

static void _at25_send_write_cmd(struct _at25* at25, uint32_t addr)
{
	uint8_t cmd[6];
	uint8_t dummy_byte = 0;

	struct _buffer out = {
		.data = cmd,
		.size = 1
	};

	if (SPINOR_JEDEC_MANUF(at25->desc->jedec_id) == SPINOR_MANUF_SST)
	{
		cmd[0] = CMD_SEQUENTIAL_PROGRAM_1;
		dummy_byte = 1;
	} else {
		cmd[0] = CMD_BYTE_PAGE_PROGRAM;
	}
	out.size += _at25_compute_addr(at25, &cmd[1], addr);
	out.size += dummy_byte ? 1 : 0;
	spid_transfert(at25->spid, 0, &out, NULL, 0);
}

static uint32_t _at25_check_writable(struct _at25* at25)
{
	uint32_t status;
	status = at25_check_status(at25,
				   AT25_STATUS_RDYBSY_BUSY | AT25_STATUS_SWP);
	if (status & AT25_STATUS_RDYBSY_BUSY) {
		trace_debug("at25: Device %s is busy\r\n", at25->desc->name);
		return AT25_ERROR_BUSY;
	}
	if (status & AT25_STATUS_SWP) {
		trace_error("at25: Device %s is write protected\r\n", at25->desc->name);
		return AT25_ERROR_PROTECTED;
	}
	return AT25_SUCCESS;
}

static void _at25_enable_write(struct _at25* at25)
{
	spid_begin_transfert(at25->spid);
	uint8_t opcode = CMD_WRITE_ENABLE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1
	};
	spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
}

static void _at25_disable_write(struct _at25* at25)
{
	spid_begin_transfert(at25->spid);
	uint8_t opcode = CMD_WRITE_DISABLE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1
	};
	spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
}

static uint32_t _at25_write_status(struct _at25* at25, uint8_t value)
{
	uint32_t status = 0;
	uint8_t cmd[2] = { CMD_WRITE_STATUS, value };
	struct _buffer out = {
		.data = cmd,
		.size = 2
	};

	_at25_enable_write(at25);

	spid_begin_transfert(at25->spid);
	status = spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
	_at25_disable_write(at25);
	if (status) {
		return AT25_ERROR_SPI;
	}
	return AT25_SUCCESS;
}

static void _at25_enter_4addr_mode(struct _at25* at25)
{
	_at25_enable_write(at25);

	spid_begin_transfert(at25->spid);
	uint8_t opcode = CMD_ENTER_4ADDR_MODE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1
	};
	spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
	at25->addressing = AT25_ADDRESS_4_BYTES;
}

static void _at25_exit_4addr_mode(struct _at25* at25)
{
	_at25_enable_write(at25);

	spid_begin_transfert(at25->spid);
	uint8_t opcode = CMD_EXIT_4ADDR_MODE;
	struct _buffer out = {
		.data = &opcode,
		.size = 1
	};
	spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
	at25->addressing = AT25_ADDRESS_3_BYTES;
}

static void _at25_set_addressing(struct _at25* at25)
{
	assert(at25->desc);

	if (at25->desc->size > MODE_3B_MAX_SIZE) {
		_at25_enter_4addr_mode(at25);
	} else {
		_at25_exit_4addr_mode(at25);
	}
}

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

uint32_t at25_check_status(struct _at25* at25, uint32_t mask)
{
	uint32_t status = at25_read_status(at25);
	if (status & mask)
		return status & mask;

	return AT25_SUCCESS;
}

void at25_wait(struct _at25* at25)
{
	if (at25_check_status(at25, AT25_STATUS_RDYBSY_BUSY))
	    trace_debug("at25: Device in busy status, Waiting...\r\n");
	while (at25_check_status(at25, AT25_STATUS_RDYBSY_BUSY));
	trace_debug("at25: Device ready.\r\n");
}

uint32_t at25_configure(struct _at25* at25, struct _spi_desc* spid)
{
	at25->spid = spid;
	spid_configure(spid);
	uint32_t jedec_id = at25_read_jedec_id(at25);
	trace_debug("at25: read JEDEC ID 0x%08x.\r\n", (unsigned)jedec_id);
	at25->desc = spi_nor_find(jedec_id);
	if (!at25->desc)
		return AT25_DEVICE_NOT_SUPPORTED;

	_at25_set_addressing(at25);
	return AT25_SUCCESS;
}

uint32_t at25_read_jedec_id(struct _at25* at25)
{
	assert(at25);
	assert(at25->spid);
	uint8_t jedec[3];
	uint8_t opcode = CMD_READ_JEDEC_ID;
	struct _buffer in = {
		.data = jedec,
		.size = 3
	};
	struct _buffer out = {
		.data = &opcode,
		.size = sizeof(opcode)
	};

	spid_begin_transfert(at25->spid);
	spid_transfert(at25->spid, &in, &out, spid_finish_transfert_callback, 0);
	spid_wait_transfert(at25->spid);

	return (jedec[2] << 16) | (jedec[1] << 8) | jedec[0];
}

uint32_t at25_read_status(struct _at25* at25)
{
	assert(at25);
	assert(at25->spid);
	uint8_t status;
	uint8_t opcode = CMD_READ_STATUS;
		struct _buffer in = {
		.data = &status,
		.size = sizeof(status)
	};
	struct _buffer out = {
		.data = &opcode,
		.size = sizeof(opcode)
	};

	spid_begin_transfert(at25->spid);
	spid_transfert(at25->spid, &in, &out, spid_finish_transfert_callback, 0);
	spid_wait_transfert(at25->spid);

	return status;
}

uint32_t at25_protect(struct _at25* at25)
{
	assert(at25);
	assert(at25->spid);

	/* Perform a global protect command */
	_at25_write_status(at25, 0x7F);
	return AT25_SUCCESS;
}

uint32_t at25_unprotect(struct _at25* at25)
{
	assert(at25);
	assert(at25->spid);

	/* Get the status register value to check the current protection */
	uint32_t status = at25_read_status(at25);
	if ((status & AT25_STATUS_SWP) == AT25_STATUS_SWP_PROTNONE)
		return 0;

	/* Perform a global unprotect command */
	_at25_write_status(at25, 0x0);

	_at25_disable_write(at25);
	/* Check the new status */
	if (at25_check_status(at25, AT25_STATUS_SPRL | AT25_STATUS_SWP))
		return AT25_ERROR_PROTECTED;
	else
		return AT25_SUCCESS;
}

void at25_print_device_info(struct _at25* at25)
{
	assert(at25);
	assert(at25->spid);

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

uint32_t at25_is_busy(struct _at25* at25)
{
	return at25_check_status(at25, AT25_STATUS_RDYBSY_BUSY);
}

uint32_t at25_read(struct _at25* at25, uint32_t addr, uint8_t* data, uint32_t length)
{
	if (addr > at25->desc->size)
		return AT25_ADDR_OOB;

	trace_debug("at25: Start flash read at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));

	assert(at25);
	assert(at25->spid);

	uint32_t status = 0;

	if (at25_is_busy(at25))
		return AT25_ERROR_BUSY;

	uint8_t cmd[6];
	struct _buffer out = {
		.data = cmd,
		.size = 1
	};
	struct _buffer in = {
		.data = data,
		.size = length
	};

	cmd[0] = CMD_READ_ARRAY;
	out.size += _at25_compute_addr(at25, &cmd[1], addr);
	out.size += 1; /* one dummy byte */

	spid_begin_transfert(at25->spid);
	status = spid_transfert(at25->spid, &in, &out, spid_finish_transfert_callback, 0);
	spid_wait_transfert(at25->spid);
	if (status)
		return AT25_ERROR_SPI;

	return AT25_SUCCESS;
}

uint32_t at25_erase_chip(struct _at25* at25)
{
	trace_debug("at25: Start flash reset all block will be erased\r\n");

	assert(at25);
	assert(at25->spid);

	uint32_t status = _at25_check_writable(at25);
	if (status)
		return status;


	uint8_t cmd = CMD_CHIP_ERASE_1;
	struct _buffer out = {
		.data = &cmd,
		.size = 1
	};

	_at25_enable_write(at25);
	spid_begin_transfert(at25->spid);
	status = spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
	spid_wait_transfert(at25->spid);
	if (status)
		return AT25_ERROR_SPI;

	_at25_disable_write(at25);
	return AT25_SUCCESS;
}

uint32_t at25_erase_block(struct _at25* at25, uint32_t addr, uint32_t length)
{
	trace_debug("at25: Start flash erase at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));

	assert(at25);
	assert(at25->spid);

	if ((addr + length) > at25->desc->size)
		return AT25_ADDR_OOB;

	uint32_t status = _at25_check_writable(at25);
	if (status)
		return status;

	uint8_t cmd[5];

	struct _buffer out = {
		.data = cmd,
		.size = 1
	};

	uint8_t command;
	uint32_t flags = at25->desc->flags;

	switch(length) {
	case 256 * 1024:
		if (flags & SPINOR_FLAG_ERASE_256K) {
			command = CMD_BLOCK_ERASE_64K_256K;
			trace_debug("at25: Will apply 256K erase\r\n");
		} else {
			trace_error("at25: 256K Erase not supported\r\n");
			return AT25_ERROR_PROGRAM;
		}
		break;
	case 64 * 1024:
		if (flags & SPINOR_FLAG_ERASE_64K) {
			command = CMD_BLOCK_ERASE_64K_256K;
			trace_debug("at25: Will apply 64K erase\r\n");
		} else {
			trace_error("at25: 64K Erase not supported\r\n");
			return AT25_ERROR_PROGRAM;
		}
		break;
	case 32 * 1024:
		if (flags & SPINOR_FLAG_ERASE_32K) {
			command = CMD_BLOCK_ERASE_32K;
			trace_debug("at25: Will apply 32K erase\r\n");
		} else {
			trace_error("at25: 32K Erase not supported\r\n");
			return AT25_ERROR_PROGRAM;
		}
		break;
	case 4 * 1024:
		if (flags & SPINOR_FLAG_ERASE_4K) {
			command = CMD_BLOCK_ERASE_4K;
			trace_debug("at25: Will apply 4K erase\r\n");
		} else {
			trace_error("at25: 4K Erase not supported\r\n");
			return AT25_ERROR_PROGRAM;
		}
		break;
	default:
		return AT25_ERROR_PROGRAM;
	}

	cmd[0] = command;
	out.size += _at25_compute_addr(at25, &cmd[1], addr);

	trace_debug("at25: Clearing block at addr 0x%x\r\n", (unsigned int)addr);

	_at25_enable_write(at25);
	spid_begin_transfert(at25->spid);
	spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
	spid_wait_transfert(at25->spid);
	if (at25_check_status(at25, AT25_STATUS_EPE))
		return AT25_ERROR_PROGRAM;

	at25_wait(at25);
	_at25_disable_write(at25);
	return AT25_SUCCESS;
}

uint32_t at25_write(struct _at25* at25, uint32_t addr, const uint8_t* data, uint32_t length)
{
	if (addr > at25->desc->size)
		return AT25_ADDR_OOB;

	trace_debug("at25: Start flash write at address: 0x%08X\r\n",
		    (unsigned int)(addr & (at25->desc->size - 1)));
	assert(at25);
	assert(at25->spid);
	assert(data);

	uint32_t status = _at25_check_writable(at25);
	if (status)
		return status;

	/* Retrieve device page size */
	uint32_t page_size = at25->desc->page_size;

	struct _buffer out = {
		.data = (uint8_t*)data,
		.size = length
	};

	while(length > 0) {
		/* Compute number of bytes to program in page */
		uint32_t write_size;
		write_size = min_u32(length, page_size - (addr % page_size));

		at25_wait(at25);

		_at25_enable_write(at25);

		spid_begin_transfert(at25->spid);
		_at25_send_write_cmd(at25, addr);
		out.size = write_size;
		status = spid_transfert(at25->spid, 0, &out, spid_finish_transfert_callback, 0);
		if (status)
			return AT25_ERROR_SPI;

		spid_wait_transfert(at25->spid);
		if (at25_check_status(at25, AT25_STATUS_EPE))
			return AT25_ERROR_PROGRAM;

		length -= write_size;
		out.data += write_size;
		addr += write_size;
	}

	_at25_disable_write(at25);

	return AT25_SUCCESS;
}
