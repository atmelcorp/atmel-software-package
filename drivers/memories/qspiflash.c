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
#include "compiler.h"
#include "math.h"
#include "timer.h"
#include "trace.h"
#include "memories/qspiflash.h"
#include "peripherals/qspi.h"
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local Definitions
 *----------------------------------------------------------------------------*/

/* Default timeout values (in timer ticks, for 1000 Hz timer) */
#define TIMEOUT_DEFAULT       100 /* 0.1s */
#define TIMEOUT_WRITE         800 /* 0.8s */
#define TIMEOUT_ERASE         800 /* 0.8s */
#define TIMEOUT_ERASE_CHIP 300000 /* 300s */

/** QSPI Status Register bits */
#define SR_WIP                    (1 << 0)  /* Write In Progress */

/** QSPI Commands */
#define CMD_WRITE_STATUS     0x01 /* Write Status Register */
#define CMD_PAGE_PROGRAM     0x02 /* Page Program */
#define CMD_WRITE_DISABLE    0x04 /* Write Disable */
#define CMD_READ_STATUS      0x05 /* Read Status Register */
#define CMD_WRITE_ENABLE     0x06 /* Write Enable */
#define CMD_SECTOR_ERASE     0x20 /* 4KB Sector Erase */
#define CMD_READ_CONFIG      0x35 /* Read Configuration Register */
#define CMD_READ_ID          0x9f /* Read JEDEC ID */
#define CMD_MULTI_IO_READ_ID 0xaf /* Read JEDEC ID (multiple IO) */
#define CMD_BULK_ERASE       0xc7 /* Bulk Chip Erase */
#define CMD_BLOCK_ERASE      0xd8 /* 64KB Block Erase */
#define CMD_READ_QUAD_IO     0xeb /* Read Quad IO (1-4-4) */
#define CMD_ENTER_ADDR4_MODE 0xb7 /* Enter 4-byte address mode */

/** QSPI Commands (Micron) */
#define CMD_MICRON_READ_EVCR  0x65 /* Read Enhanced Volatile Configuration Register */
#define CMD_MICRON_WRITE_EVCR 0x61 /* Write Enhanced Volatile Configuration Register */
#define CMD_MICRON_READ_VCR   0x85 /* Read Volatile Configuration Register */
#define CMD_MICRON_WRITE_VCR  0x81 /* Write Volatile Configuration  Register */

/* QSPI Commands (Macronix) */
#define CMD_MACRONIX_READ_CONFIG 0x15 /* Read Configuration Register */

/* Quad-IO switching method */
#define QUAD_IO_SWITCH_MICRON 0
#define QUAD_IO_SWITCH_SPANSION 1
#define QUAD_IO_SWITCH_MACRONIX 2

/*----------------------------------------------------------------------------
 *        Local Forward Function Declarations
 *----------------------------------------------------------------------------*/

static bool _qspiflash_switch_to_quad_micron(struct _qspiflash *flash);
static bool _qspiflash_switch_to_quad_spansion(struct _qspiflash *flash);
static bool _qspiflash_switch_to_quad_macronix(struct _qspiflash *flash);
static bool _qspiflash_init_spansion_fls(struct _qspiflash *flash);

/*----------------------------------------------------------------------------
 *        Local Constants
 *----------------------------------------------------------------------------*/

static const struct _qspiflash_desc _qspiflash_devices[] = {
	/* Manufacturer: Micron */
	/* mode cycle - bit[0] = 0x0: continuous read, normal read otherwise */
	{ "N25Q128A",   0x0018ba20, 256, 64 * 1024, 256, 1, 9, 0x01, 0x00,
		QSPIFLASH_FEAT_ERASE_4K, NULL, _qspiflash_switch_to_quad_micron },

	/* Manufacturer: Spansion */
	/* mode cycle - bit[4:7] = 0xa: continuous read, normal read otherwise */
	{ "S25FL116K",  0x00154001, 32, 64 * 1024, 256, 2, 4, 0x00, 0xa0,
		QSPIFLASH_FEAT_ERASE_4K, NULL, _qspiflash_switch_to_quad_spansion },
	{ "S25FL132K",  0x00164001, 64, 64 * 1024, 256, 2, 4, 0x00, 0xa0,
		QSPIFLASH_FEAT_ERASE_4K, NULL, _qspiflash_switch_to_quad_spansion },
	{ "S25FL164K",  0x00174001, 128, 64 * 1024, 256, 2, 4, 0x00, 0xa0,
		QSPIFLASH_FEAT_ERASE_4K, NULL, _qspiflash_switch_to_quad_spansion },
	{ "S25FL128S",  0x00182001,  16, 64 * 1024, 256, 2, 4, 0x00, 0xa0,
		0, _qspiflash_init_spansion_fls, _qspiflash_switch_to_quad_spansion },
	{ "S25FL256S",  0x00190201,  32, 64 * 1024, 256, 2, 4, 0x00, 0xa0,
		0, _qspiflash_init_spansion_fls, _qspiflash_switch_to_quad_spansion },
	{ "S25FL512S",  0x00200201,  1024, 256 * 1024, 256, 2, 4, 0x00, 0xa0,
		0, NULL, _qspiflash_switch_to_quad_spansion },

	/* Manufacturer: Macronix */
	/* mode cycles: bit[0:3] = ~bit[4:7]: continuous read, normal read otherwise */
	{ "MX66L1G45G", 0x00201bc2, 2048, 64 * 1024, 256, 2, 4, 0x00, 0xf0,
		QSPIFLASH_FEAT_ERASE_4K, NULL, _qspiflash_switch_to_quad_macronix },
};

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static bool _qspiflash_read_reg(const struct _qspiflash *flash, uint8_t code, void *value, uint32_t length)
{
	struct _qspi_cmd cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_READ;
	cmd.ifr_width = flash->ifr_width;
	cmd.enable.instruction = 1;
	cmd.enable.data = 1;
	cmd.instruction = code;
	cmd.rx_buffer = value;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	return qspi_perform_command(flash->qspi, &cmd);
}

static bool _qspiflash_write_reg(const struct _qspiflash *flash, uint8_t code, const void *value, uint32_t length)
{
	struct _qspi_cmd cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE;
	cmd.ifr_width = flash->ifr_width;
	cmd.enable.instruction = 1;
	cmd.enable.data = (value != NULL);
	cmd.instruction = code;
	cmd.tx_buffer = value;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	return qspi_perform_command(flash->qspi, &cmd);
}

static bool _qspiflash_write_enable(const struct _qspiflash *flash)
{
	return _qspiflash_write_reg(flash, CMD_WRITE_ENABLE, NULL, 0);
}

static bool _qspiflash_enter_addr4_mode(struct _qspiflash *flash)
{
	if (_qspiflash_write_reg(flash, CMD_ENTER_ADDR4_MODE, NULL, 0)) {
		flash->mode_addr4 = true;
		return true;
	}
	return false;
}

static bool _qspiflash_switch_to_quad_micron(struct _qspiflash *flash)
{
	struct _qspiflash_desc *desc = &flash->desc;
	uint8_t evcr, vcr;

	/* Read the Enhanced Volatile Configuration Register (EVCR) */
	if (!_qspiflash_read_reg(flash, CMD_MICRON_READ_EVCR, &evcr, 1))
		return false;

	/* Enable Write */
	if (!_qspiflash_write_enable(flash))
		return false;

	/* Set EVCR, enable quad SPI (4-4-4) */
	evcr &= ~(1 << 7); /* clear bit 7 to enable the Quad SPI protocol 4-4-4 */
	if (!_qspiflash_write_reg(flash, CMD_MICRON_WRITE_EVCR, &evcr, 1))
		return false;

	/* Switch the QSPI controller to Quad CMD protocol (4-4-4) */
	flash->ifr_width = QSPI_IFR_WIDTH_QUAD_CMD;

	/* Wait till ready */
	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	/* Read EVCR to check the protocol update */
	if (!_qspiflash_read_reg(flash, CMD_MICRON_READ_EVCR, &evcr, 1))
		return false;

	if (evcr & (1 << 7))
		return false;

	/* Read the Volatile Configuration Register (VCR) */
	if (!_qspiflash_read_reg(flash, CMD_MICRON_READ_VCR, &vcr, 1))
		return false;

	/* Enable Write */
	if (!_qspiflash_write_enable(flash))
		return false;

	/* Update the VCR to enable XIP */
	vcr &= ~(1 << 3); /* clear bit3 in VCR to enable XIP */
	vcr &= ~(0xf << 4); /* set number of mode/dummy clock cycles for all FAST READ commands */
	vcr |= ((desc->num_mode_cycles + desc->num_dummy_cycles) & 0xf) << 4;
	vcr |= 0x3; /* continuous read */
	if (!_qspiflash_write_reg(flash, CMD_MICRON_WRITE_VCR, &vcr, 1))
		return false;

	/* Wait till ready */
	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	/* Check XIP update */
	if (!_qspiflash_read_reg(flash, CMD_MICRON_READ_VCR, &vcr, 1))
		return false;

	if (vcr & (1 << 3))
		return false;

	return true;
}

static bool _qspiflash_init_spansion_fls(struct _qspiflash *flash)
{
	uint32_t cmd = flash->ifr_width == QSPI_IFR_WIDTH_SINGLE_BIT_SPI ? CMD_READ_ID : CMD_MULTI_IO_READ_ID;
	uint8_t id[6];
	memset(id, 0, 6);
	if (_qspiflash_read_reg(flash, cmd, &id, 6)) {
		/* Verify ID-CFI length */
		if (id[3] == 0x4d) {
			/* Verify family is FL-S */
			if (id[5] == 0x80) {
				struct _qspiflash_desc *desc = &flash->desc;
				uint32_t size = desc->num_blocks * desc->block_size;
				/* Sector Architecture */
				if (id[4] == 0) {
					/* Uniform 256kB sectors */
					desc->block_size = 256 * 1024;
					desc->num_blocks = size / desc->block_size;
					return true;
				} else if (id[4] == 1) {
					/* Uniform 64kB sectors */
					desc->block_size = 64 * 1024;
					desc->num_blocks = size / desc->block_size;
					return true;
				}
			}
		}
	}
	return false;
}

static bool _qspiflash_switch_to_quad_spansion(struct _qspiflash *flash)
{
	uint8_t cr, sr_cr[2];

	/* Set the Status and Control Registers */
	sr_cr[0] = 0x00; /* Status Register */
	sr_cr[1] = 0x02; /* Configuration Register: Set the Quad Data Width bit (non volatile) and Latency Code bits to 00b */
	if (!_qspiflash_write_reg(flash, CMD_WRITE_STATUS, sr_cr, sizeof(sr_cr)))
		return false;

	/* Wait till ready */
	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	/* Check the protocol update: this command still uses SPI 1-1-1 protocol */
	if (!_qspiflash_read_reg(flash, CMD_READ_CONFIG, &cr, 1))
		return false;

	if ((cr & 0xc2) != 0x02)
		return false;

	/* Switch the QSPI host controller in Quad IO (1-4-4) */
	flash->ifr_width = QSPI_IFR_WIDTH_QUAD_IO;
	return true;
}

static bool _qspiflash_switch_to_quad_macronix(struct _qspiflash *flash)
{
	uint8_t sr_cr[2];

	/* Read the Status Register */
	if (!qspiflash_read_status(flash, &sr_cr[0]))
		return false;

	/* Read the Control Register */
	if (!_qspiflash_read_reg(flash, CMD_MACRONIX_READ_CONFIG, &sr_cr[1], 1))
		return false;

	/* Update the Status Register to set the Quad Enable bit (non-volatile) */
	sr_cr[0] |= (1 << 6);

	/* Configure 2 mode + 4 dummy cycles for Read Quad IO (1-4-4) up to 84MHz */
	sr_cr[1] &= ~0xe0; /* clear bit7:bit6:bit5 (all volatile) */

	/* Enable Write */
	if (!_qspiflash_write_enable(flash))
		return false;

	/* Write the Status and Control Registers */
	if (!_qspiflash_write_reg(flash, CMD_WRITE_STATUS, sr_cr, 2))
		return false;

	/* Wait till ready */
	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	/* Assert the Quad Enable bit is set */
	if (!qspiflash_read_status(flash, &sr_cr[0]))
		return false;

	if ((sr_cr[0] & (1 << 6)) == 0)
		return false;

	/* Stay in SPI Mode (as opposed to QPI mode), so switch to QUAD IO (not QUAD CMD) */
	flash->ifr_width = QSPI_IFR_WIDTH_QUAD_IO;
	return true;
}

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

bool qspiflash_configure(struct _qspiflash *flash, Qspi *qspi)
{
	static const uint32_t ifr_widths[] = {
		QSPI_IFR_WIDTH_SINGLE_BIT_SPI,
		QSPI_IFR_WIDTH_QUAD_IO,
		QSPI_IFR_WIDTH_QUAD_CMD,
	};
	int i,j;

	memset(flash, 0, sizeof(*flash));
	flash->qspi = qspi;

	bool found = false;
	for (i = 0; !found && i < ARRAY_SIZE(ifr_widths); i++) {
		/* Switch QSPI protocol */
		flash->ifr_width = ifr_widths[i];

		/* Read JEDEC ID */
		uint32_t jedec_id = 0;
		if (!qspiflash_read_jedec_id(flash, &jedec_id))
			continue;

		/* Look for a supported flash */
		for (j = 0; !found && j < ARRAY_SIZE(_qspiflash_devices); j++) {
			const struct _qspiflash_desc *desc = &_qspiflash_devices[j];
			if (jedec_id == desc->jedec_id) {
				memcpy(&flash->desc, desc, sizeof(*desc));
				found = true;
			}
		}
	}

	/* Not found */
	if (!found)
		return false;

	/* Initialize */
	if (flash->desc.init) {
		if (!flash->desc.init(flash)) {
			return false;
		}
	}

	/* Enter 4-byte addressig mode if size > 16MB */
	if (flash->desc.num_blocks * flash->desc.block_size > 16 * 1024 * 1024) {
		if (!_qspiflash_enter_addr4_mode(flash))
			return false;
	}

	/* Switch to Quad SPI */
	if (flash->desc.switch_to_quad) {
		if (!flash->desc.switch_to_quad(flash)) {
			return false;
		}
	}

	return true;
}


bool qspiflash_read_status(const struct _qspiflash *flash, uint8_t *status)
{
	return _qspiflash_read_reg(flash, CMD_READ_STATUS, status, 1);
}

bool qspiflash_wait_ready(const struct _qspiflash *flash, uint32_t timeout)
{
	struct _timeout to;
	timer_start_timeout(&to, timeout);
	do {
		uint8_t status;

		if (!qspiflash_read_status(flash, &status))
			return false;

		if ((status & SR_WIP) == 0)
			return true;
	} while (!timer_timeout_reached(&to));

	trace_debug("qspiflash_wait_ready timeout reached\r\n");

	/* Timed out */
	return false;
}

bool qspiflash_read_jedec_id(const struct _qspiflash *flash,
		uint32_t *jedec_id)
{
	uint32_t cmd = flash->ifr_width == QSPI_IFR_WIDTH_SINGLE_BIT_SPI ? CMD_READ_ID : CMD_MULTI_IO_READ_ID;
	uint32_t id = 0;
	if (_qspiflash_read_reg(flash, cmd, &id, 3)) {
		*jedec_id = id;
		return true;
	}
	return false;
}

bool qspiflash_read(const struct _qspiflash *flash, uint32_t addr, void *data,
		uint32_t length)
{
	const struct _qspiflash_desc *desc = &flash->desc;
	uint8_t mode = data ? desc->normal_read_mode : desc->continuous_read_mode;
	struct _qspi_cmd cmd;

	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_READ_MEMORY;
	cmd.ifr_width = flash->ifr_width;
	cmd.enable.instruction = 1;
	cmd.enable.address = flash->mode_addr4 ? 4 : 3;
	cmd.enable.mode = (desc->num_mode_cycles > 0);
	cmd.enable.dummy = (desc->num_dummy_cycles > 0);
	cmd.enable.data = 1;
	cmd.instruction = CMD_READ_QUAD_IO;
	cmd.mode = mode;
	cmd.num_mode_cycles = desc->num_mode_cycles;
	cmd.num_dummy_cycles = desc->num_dummy_cycles;
	cmd.address = addr;
	cmd.rx_buffer = data;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	return qspi_perform_command(flash->qspi, &cmd);
}

bool qspiflash_erase_chip(const struct _qspiflash *flash)
{
	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	if (!_qspiflash_write_enable(flash))
		return false;

	if (!_qspiflash_write_reg(flash, CMD_BULK_ERASE, NULL, 0))
		return false;

	if (!qspiflash_wait_ready(flash, TIMEOUT_ERASE_CHIP))
		return false;

	return true;
}

bool qspiflash_erase_block(const struct _qspiflash *flash, uint32_t addr,
		bool erase_4k)
{
	struct _qspi_cmd cmd;
	uint8_t instr;

	if (erase_4k) {
		if (flash->desc.features & QSPIFLASH_FEAT_ERASE_4K) {
			instr = CMD_SECTOR_ERASE;
		} else {
			return false;
		}
	} else {
		instr = CMD_BLOCK_ERASE;
	}

	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	if (!_qspiflash_write_enable(flash))
		return false;

	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE;
	cmd.ifr_width = flash->ifr_width;
	cmd.enable.instruction = 1;
	cmd.enable.address = flash->mode_addr4 ? 4 : 3;
	cmd.instruction = instr;
	cmd.address = addr;
	cmd.timeout = TIMEOUT_DEFAULT;
	if (!qspi_perform_command(flash->qspi, &cmd))
		return false;

	if (!qspiflash_wait_ready(flash, TIMEOUT_ERASE))
		return false;

	return true;
}

bool qspiflash_write(const struct _qspiflash *flash, uint32_t addr,
		const void *data, uint32_t length)
{
	struct _qspi_cmd cmd;
	uint32_t written = 0;
	const uint8_t *ptr = data;

	if (!qspiflash_wait_ready(flash, TIMEOUT_DEFAULT))
		return false;

	while (written < length) {
		/* remaining size in current page */
		uint32_t remaining = flash->desc.page_size
			- (addr % flash->desc.page_size);
		/* number of bytes to write this round */
		uint32_t count = min(length - written, remaining);

		if (!_qspiflash_write_enable(flash))
			return false;

		memset(&cmd, 0, sizeof(cmd));
		cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE_MEMORY;
		cmd.ifr_width = flash->ifr_width;
		cmd.enable.instruction = 1;
		cmd.enable.address = flash->mode_addr4 ? 4 : 3;
		cmd.enable.data = 1;
		cmd.instruction = CMD_PAGE_PROGRAM;
		cmd.address = addr;
		cmd.tx_buffer = ptr;
		cmd.buffer_len = count;
		cmd.timeout = TIMEOUT_DEFAULT;

		if (!qspi_perform_command(flash->qspi, &cmd))
			return false;

		if (!qspiflash_wait_ready(flash, TIMEOUT_WRITE))
			return false;

		written += count;
		addr += count;
		ptr += count;
	}

	return true;
}
