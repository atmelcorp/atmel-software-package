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
#include "intmath.h"
#include "timer.h"
#include "trace.h"
#include "nvm/spi-nor/qspiflash.h"
#include "spi/qspi.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*----------------------------------------------------------------------------
 *        Local Definitions
 *----------------------------------------------------------------------------*/

/* Default timeout values (in timer ticks, for 1000 Hz timer) */
#define TIMEOUT_DEFAULT       100 /* 0.1s */
#define TIMEOUT_WRITE         800 /* 0.8s */
#define TIMEOUT_ERASE        3000 /* 3s */
#define TIMEOUT_ERASE_CHIP 500000 /* 500s */

/** QSPI Commands */
#define CMD_WRITE_STATUS     0x01 /* Write Status Register */
#define CMD_PAGE_PROGRAM     0x02 /* Page Program */
#define CMD_READ             0x03 /* Read */
#define CMD_WRITE_DISABLE    0x04 /* Write Disable */
#define CMD_READ_STATUS      0x05 /* Read Status Register */
#define CMD_WRITE_ENABLE     0x06 /* Write Enable */
#define CMD_FAST_READ        0x0b /* Fast Read */
#define CMD_SECTOR_ERASE     0x20 /* 4KB Sector Erase */
#define CMD_READ_CONFIG      0x35 /* Read Configuration Register */
#define CMD_FAST_READ_1_1_2  0x3b /* Fast Read (1-1-2) */
#define CMD_BLOCK_ERASE_32K  0x52 /* 32KB Block Erase */
#define CMD_FAST_READ_1_1_4  0x6b /* Fast Read (1-1-4) */
#define CMD_READ_FLAG_STATUS 0x70 /* Read Flag Status Register */
#define CMD_READ_ID          0x9f /* Read JEDEC ID */
#define CMD_MULTI_IO_READ_ID 0xaf /* Read JEDEC ID (multiple IO) */
#define CMD_FAST_READ_1_2_2  0xbb /* Fast Read (1-2-2) */
#define CMD_BULK_ERASE       0xc7 /* Bulk Chip Erase */
#define CMD_BLOCK_ERASE      0xd8 /* 64/256KB Block Erase */
#define CMD_FAST_READ_1_4_4  0xeb /* Fast Read (1-4-4) */
#define CMD_ENTER_ADDR4_MODE 0xb7 /* Enter 4-byte address mode */

#define CMD_QUAD_PAGE_PROGRAM 0x32

/** QSPI Commands (Micron) */
#define CMD_MICRON_READ_EVCR  0x65 /* Read Enhanced Volatile Configuration Register */
#define CMD_MICRON_WRITE_EVCR 0x61 /* Write Enhanced Volatile Configuration Register */
#define CMD_MICRON_READ_VCR   0x85 /* Read Volatile Configuration Register */
#define CMD_MICRON_WRITE_VCR  0x81 /* Write Volatile Configuration  Register */

/* FLAG STATUS REGISTER BITS */
#define FSR_NBUSY 0x80

/* QSPI Commands (Macronix) */
#define CMD_MACRONIX_READ_CONFIG 0x15 /* Read Configuration Register */
#define CMD_QUAD_PAGE_PROGRAM_MX 0x38
#define CMD_QUAD_PAGE_PROGRAM_MX_4B 0x3e

/* QSPI Commands (Spansion) */
#define CMD_SPANSION_QPP 0x32 /* Quad Page Programming */

/* QSPI Commands (SST) */
#define CMD_SST_ULBPR 0x98 /* Unlock Block Protection */

/** QSPI Status Register bits */
#define SR_WIP              (1 << 0) /* Write In Progress */
#define SR_MACRONIX_QUAD_EN (1 << 6) /* Quad-IO Enable */
#define SR_SPANSION_BP0     (1 << 2) /* Block Protect */
#define SR_SPANSION_BP1     (1 << 3) /* Block Protect */
#define SR_SPANSION_BP2     (1 << 4) /* Block Protect */

/* QSPI Configuration Register bits */
#define CR_SPANSION_QUAD (1 << 1) /* Puts the device into Quad I/O mode */
#define CR_SPANSION_BPNV (1 << 3) /* Configures BP2-0 bits in the Status Register */

/* Micron Enhanced Volatile Configuration Register  */
#define EVCR_DUAL_ENABLE (1 << 6)
#define EVCR_QUAD_ENABLE (1 << 7)

/*
 * 4byte address commands:
 * MUST be named as the associated 3byte address command with the _4B suffix.
 */
#define CMD_READ_4B                 0x13
#define CMD_FAST_READ_4B            0x0c
#define CMD_FAST_READ_1_1_2_4B      0x3c
#define CMD_FAST_READ_1_1_4_4B      0x6c
#define CMD_FAST_READ_1_2_2_4B      0xbc
#define CMD_FAST_READ_1_4_4_4B      0xec

#define CMD_PAGE_PROGRAM_4B         0x12
#define CMD_QUAD_PAGE_PROGRAM_4B    0x34
#define CMD_SECTOR_ERASE_4B         0x21
#define CMD_BLOCK_ERASE_32K_4B      0x5c
#define CMD_BLOCK_ERASE_4B          0xdc

/*----------------------------------------------------------------------------
 *        Local Types
 *----------------------------------------------------------------------------*/

struct _read_id_config {
	uint32_t ifr_width;
	uint8_t  opcode;
};

struct _flash_init {
	uint8_t manuf_id;
	int (*init)(struct _qspiflash *);
};

/*----------------------------------------------------------------------------
 *        Local Forward Function Declarations
 *----------------------------------------------------------------------------*/

static int _qspiflash_init_micron(struct _qspiflash *flash);
static int _qspiflash_init_macronix(struct _qspiflash *flash);
static int _qspiflash_init_spansion(struct _qspiflash *flash);
static int _qspiflash_init_sst(struct _qspiflash *flash);

/*----------------------------------------------------------------------------
 *        Local Constants
 *----------------------------------------------------------------------------*/

static const struct _read_id_config configs[] = {
	/* Regular protocol and command */
	{ QSPI_IFR_WIDTH_SINGLE_BIT_SPI, CMD_READ_ID },
	/* Micron Quad mode & Macronix QPI mode */
	{ QSPI_IFR_WIDTH_QUAD_CMD, CMD_MULTI_IO_READ_ID },
	/* Micron Dual mode */
	{ QSPI_IFR_WIDTH_DUAL_CMD, CMD_MULTI_IO_READ_ID },
	/* Winbond QPI mode */
	{ QSPI_IFR_WIDTH_QUAD_CMD, CMD_READ_ID },
};

static const struct _flash_init flash_inits[] = {
	{ SPINOR_MANUF_MICRON, _qspiflash_init_micron },
	{ SPINOR_MANUF_MACRONIX, _qspiflash_init_macronix },
	{ SPINOR_MANUF_SPANSION, _qspiflash_init_spansion },
	{ SPINOR_MANUF_SST, _qspiflash_init_sst },
};

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static int _qspiflash_read_reg(const struct _qspiflash *flash, uint8_t code, void *value, uint32_t length)
{
	struct _qspi_cmd cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_READ;
	cmd.ifr_width = flash->ifr_width_reg;
	cmd.enable.instruction = 1;
	cmd.enable.data = 1;
	cmd.instruction = code;
	cmd.rx_buffer = value;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	if (!qspi_perform_command(flash->qspi, &cmd))
		return -EIO;
	return 0;
}

static int _qspiflash_write_reg(const struct _qspiflash *flash, uint8_t code, const void *value, uint32_t length)
{
	struct _qspi_cmd cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE;
	cmd.ifr_width = flash->ifr_width_reg;
	cmd.enable.instruction = 1;
	cmd.enable.data = (value != NULL);
	cmd.instruction = code;
	cmd.tx_buffer = value;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	if (!qspi_perform_command(flash->qspi, &cmd))
		return -EIO;
	return 0;
}

static int _qspiflash_write_enable(const struct _qspiflash *flash)
{
	return _qspiflash_write_reg(flash, CMD_WRITE_ENABLE, NULL, 0);
}

static int _qspiflash_enter_addr4_mode(struct _qspiflash *flash)
{
	int ret;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	ret = _qspiflash_write_reg(flash, CMD_ENTER_ADDR4_MODE, NULL, 0);
	if (ret < 0)
		return ret;

	flash->mode_addr4 = true;
	return 0;
}

static int _qspiflash_read_flag_status(const struct _qspiflash *flash, uint8_t *status)
{
	if (flash->desc->flags & SPINOR_FLAG_FSR)
		return _qspiflash_read_reg(flash, CMD_READ_FLAG_STATUS, status, 1);
	else {
		*status = FSR_NBUSY; /* Not busy */
		return 0;
	}
}

/*----------------------------------------------------------------------------
 *        Local Functions (convert opcode to its 4-byte address version)
 *----------------------------------------------------------------------------*/

struct address_entry {
	unsigned char	src_opcode;
	unsigned char	dst_opcode;
};

static unsigned char qspi_flash_convert_opcode(unsigned char opcode,
			const struct address_entry *entries,
			int num_entries)
{
	int b, e;

	b = 0;
	e = num_entries - 1;
	while (b <= e) {
		int m = (b + e) >> 1;
		const struct address_entry *entry = &entries[m];

		if (opcode == entry->src_opcode)
			return entry->dst_opcode;

		if (opcode < entry->src_opcode)
			e = m - 1;
		else
			b = m + 1;
	}

	/* No convertion found */
	return opcode;
}

static unsigned char qspi_flash_3to4_opcode(unsigned char opcode)
{
	/* MUST be sorted by 3byte opcode */
#define ENTRY_3TO4(_opcode) { _opcode, _opcode##_4B }
	static const struct address_entry qspi_flash_3to4_table[] = {
		ENTRY_3TO4(CMD_PAGE_PROGRAM),         /* 0x02 */
		ENTRY_3TO4(CMD_READ),                 /* 0x03 */
		ENTRY_3TO4(CMD_FAST_READ),            /* 0x0b */
		ENTRY_3TO4(CMD_SECTOR_ERASE),         /* 0x20 */
		ENTRY_3TO4(CMD_QUAD_PAGE_PROGRAM),    /* 0x32 */
		ENTRY_3TO4(CMD_QUAD_PAGE_PROGRAM_MX), /* 0x38 */
		ENTRY_3TO4(CMD_FAST_READ_1_1_2),      /* 0x3b */
		ENTRY_3TO4(CMD_BLOCK_ERASE_32K),      /* 0x52 */
		ENTRY_3TO4(CMD_FAST_READ_1_1_4),      /* 0x6b */
		ENTRY_3TO4(CMD_FAST_READ_1_2_2),      /* 0xbb */
		ENTRY_3TO4(CMD_BLOCK_ERASE),          /* 0xd8 */
		ENTRY_3TO4(CMD_FAST_READ_1_4_4),      /* 0xeb */
	};
#undef ENTRY_3TO4

	return qspi_flash_convert_opcode(opcode,
					qspi_flash_3to4_table,
					ARRAY_SIZE(qspi_flash_3to4_table));
}

/*----------------------------------------------------------------------------
 *        Local Functions (Micron support)
 *----------------------------------------------------------------------------*/

static int _micron_set_protocol(struct _qspiflash *flash,
		uint8_t mask, uint8_t val, uint32_t ifr_width)
{
	int ret;
	uint8_t evcr;

	/* Read the Enhanced Volatile Configuration Register (EVCR). */
	ret = _qspiflash_read_reg(flash, CMD_MICRON_READ_EVCR, &evcr, 1);
	if (ret < 0)
		return ret;

	/* Check whether we need to update the protocol bits. */
	if ((evcr & mask) == val) {
		trace_debug("QSPI Flash: Micron Quad mode already enabled\r\n");
		return 0;
	}

	trace_debug("QSPI Flash: Micron Quad mode disabled, will enable it\r\n");

	/* Set EVCR protocol bits. */
	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;
	evcr = (evcr & ~mask) | val;
	ret = _qspiflash_write_reg(flash, CMD_MICRON_WRITE_EVCR, &evcr, 1);
	if (ret < 0)
		return ret;

	/* Switch reg protocol now before accessing any other registers. */
	flash->ifr_width_reg = ifr_width;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	/* Read EVCR and check it. */
	ret = _qspiflash_read_reg(flash, CMD_MICRON_READ_EVCR, &evcr, 1);
	if (ret < 0)
		return ret;
	if ((evcr & mask) != val)
		return -EIO;

	return 0;
}

static int _micron_set_quad_spi_protocol(struct _qspiflash *flash)
{
	int ret;

	/* Set Quad/Dual bits to 0_ to select the Quad SPI mode. */
	ret = _micron_set_protocol(flash, EVCR_QUAD_ENABLE, 0,
				QSPI_IFR_WIDTH_QUAD_CMD);
	if (ret < 0)
		return ret;

	flash->ifr_width_read = QSPI_IFR_WIDTH_QUAD_CMD;
	flash->ifr_width_program = QSPI_IFR_WIDTH_QUAD_CMD;
	flash->ifr_width_erase = QSPI_IFR_WIDTH_QUAD_CMD;

	return 0;
}

static int _micron_set_dummy_cycles(struct _qspiflash *flash,
		uint8_t num_dummy_cycles)
{
	int ret;
	uint8_t vcr, val, mask;

	/* Clear bit3 (XIP) to enable the Continuoues Read mode. */
	mask = 0xf8;
	val = (num_dummy_cycles << 4) & mask;

	/* Read the Volatile Configuration Register (VCR). */
	ret = _qspiflash_read_reg(flash, CMD_MICRON_READ_VCR, &vcr, 1);
	if (ret < 0)
		return ret;

	/* Check whether we need to update the number of dummy cycles. */
	if ((vcr & mask) == val)
		goto updated;

	/* Update the number of dummy into the VCR. */
	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;
	vcr = (vcr & ~mask) | val;
	ret = _qspiflash_write_reg(flash, CMD_MICRON_WRITE_VCR, &vcr, 1);
	if (ret < 0)
		return ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	/* Read VCR and check it. */
	ret = _qspiflash_read_reg(flash, CMD_MICRON_READ_VCR, &vcr, 1);
	if (ret < 0)
		return ret;
	if ((vcr & mask) != val)
		return -EIO;

updated:
	/* Save the number of mode/dummy cycles to use with Fast Read commands. */
	if (num_dummy_cycles) {
		flash->num_mode_cycles = 1;
		flash->num_dummy_cycles = num_dummy_cycles - 1;
	} else {
		flash->num_mode_cycles = 0;
		flash->num_dummy_cycles = 0;
	}

	/* mode cycle - bit[0] = 0x0: continuous read, normal read otherwise */
	flash->normal_read_mode = 0x01;
	flash->continuous_read_mode = 0x00;

	return 0;
}

static int _qspiflash_init_micron(struct _qspiflash *flash)
{
	int ret;

	if (flash->desc->flags & SPINOR_FLAG_QUAD) {
		ret = _micron_set_quad_spi_protocol(flash);
		if (ret < 0)
			return ret;

		flash->opcode_read = CMD_FAST_READ_1_4_4;
	}

	ret = _micron_set_dummy_cycles(flash, 8);
	if (ret < 0)
		return ret;

	return 0;
}

/*----------------------------------------------------------------------------
 *        Local Functions (Macronix support)
 *----------------------------------------------------------------------------*/

static int _macronix_quad_enable(struct _qspiflash *flash)
{
	int ret;
	uint8_t status;

	ret = qspiflash_read_status(flash, &status);
	if (ret < 0)
		return ret;

	if (status & SR_MACRONIX_QUAD_EN) {
		trace_debug("QSPI Flash: Macronix Quad mode already enabled\r\n");
		return 0;
	}

	trace_debug("QSPI Flash: Macronix Quad mode disabled, will enable it\r\n");

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	status |= SR_MACRONIX_QUAD_EN;
	ret = _qspiflash_write_reg(flash, CMD_WRITE_STATUS, &status, 1);
	if (ret < 0)
		return ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	ret = qspiflash_read_status(flash, &status);
	if (ret < 0)
		return ret;

	if ((status & SR_MACRONIX_QUAD_EN) == 0)
		return -EIO;

	return 0;
}

static int _macronix_dummy2code(uint8_t read_opcode,
		uint8_t num_dummy_cycles, uint8_t *dc)
{
	switch (read_opcode) {
	case CMD_READ:
		*dc = 0;
		break;

	case CMD_FAST_READ:
	case CMD_FAST_READ_1_1_4:
		switch (num_dummy_cycles) {
		case 6:
			*dc = 1;
			break;
		case 8:
			*dc = 0;
			break;
		case 10:
			*dc = 3;
			break;
		default:
			return -EINVAL;
		}
		break;

	case CMD_FAST_READ_1_4_4:
		switch (num_dummy_cycles) {
		case 4:
			*dc = 1;
			break;
		case 6:
			*dc = 0;
			break;
		case 8:
			*dc = 2;
			break;
		case 10:
			*dc = 3;
		default:
			return -EINVAL;
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int _macronix_set_dummy_cycles(struct _qspiflash *flash,
		uint8_t num_dummy_cycles)
{
	int ret;
	uint8_t mask, val, dc;
	uint8_t cr, sr, sr_cr[2];

	/* Convert the number of dummy cycles into Macronix DC volatile bits. */
	ret = _macronix_dummy2code(flash->opcode_read, num_dummy_cycles, &dc);
	if (ret < 0)
		return ret;

	mask = 0xc0;
	val = (dc << 6) & mask;

	ret = _qspiflash_read_reg(flash, CMD_MACRONIX_READ_CONFIG, &cr, 1);
	if (ret < 0)
		return ret;

	if ((cr & mask) == val)
		goto updated;

	ret = qspiflash_read_status(flash, &sr);
	if (ret < 0)
		return ret;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	cr = (cr & ~mask) | val;
	sr_cr[0] = sr & 0xff;
	sr_cr[1] = cr & 0xff;
	ret = _qspiflash_write_reg(flash, CMD_WRITE_STATUS, sr_cr, 2);
	if (ret < 0)
		return ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	ret = _qspiflash_read_reg(flash, CMD_MACRONIX_READ_CONFIG, &cr, 1);
	if (ret < 0)
		return ret;

	if ((cr & mask) != val)
		return -EIO;

updated:
	if (num_dummy_cycles) {
		flash->num_mode_cycles = 2;
		flash->num_dummy_cycles = num_dummy_cycles - 2;
	} else {
		flash->num_mode_cycles = 0;
		flash->num_dummy_cycles = 0;
	}

	/* mode cycles: bit[0:3] = ~bit[4:7]: continuous read, normal read otherwise */
	flash->normal_read_mode = 0x00;
	flash->continuous_read_mode = 0xf0;

	return 0;
}

static int _qspiflash_init_macronix(struct _qspiflash *flash)
{
	if (flash->desc->flags & SPINOR_FLAG_QUAD) {
		/*
		 * In QPI mode, only the Fast Read 1-4-4 (0xeb) op code is supported.
		 * In SPI mode, both the Fast Read 1-1-4 (0x6b) and Fast Read 1-4-4
		 * (0xeb) op codes are supported but we'd rather use the Fast Read 1-4-4
		 * command as it is the only one which allows us to enter/leave the
		 * peformance enhance (continuous read) mode required by XIP operations.
		 */
		flash->opcode_read = CMD_FAST_READ_1_4_4;

		/*
		 * Check whether the QPI mode is enabled: if it is then we know that
		 * the Quad Enabled (QE) non-volatile bit is already set. Otherwise,
		 * we MUST set the QE bit before using any Quad SPI command.
		 */
		if (flash->ifr_width_read != QSPI_IFR_WIDTH_QUAD_CMD) {
			int ret = _macronix_quad_enable(flash);
			if (ret < 0)
				return ret;

			flash->ifr_width_read = QSPI_IFR_WIDTH_QUAD_IO;
		}
	}

	return _macronix_set_dummy_cycles(flash, 8);
}

/*----------------------------------------------------------------------------
 *        Local Functions (Spansion support)
 *----------------------------------------------------------------------------*/

static int _spansion_set_protocol(struct _qspiflash *flash,
		uint8_t mask, uint8_t val)
{
	int ret;
	bool need_update = false;
	uint8_t wrr_val[2];

	/* Read the Status Register. */
	ret = qspiflash_read_status(flash, &wrr_val[0]);
	if (ret < 0)
		return ret;

	/* Read the Configuration Register. */
	ret = _qspiflash_read_reg(flash, CMD_READ_CONFIG, &wrr_val[1], 1);
	if (ret < 0)
		return ret;

	/* Check whether block protect is enabled and disable it */
	if (wrr_val[0] & (SR_SPANSION_BP0 | SR_SPANSION_BP1 | SR_SPANSION_BP2)) {
		trace_debug("QSPI Flash: Chip protected from program/erase, will un-protect\r\n");
		wrr_val[0] = 0;
		wrr_val[1] |= CR_SPANSION_BPNV;
		need_update = true;
	}

	/* Check whether we need to update the protocol bits. */
	if ((wrr_val[1] & mask) != val) {
		trace_debug("QSPI Flash: Spansion Quad mode disabled, will enable it\r\n");
		/* Set Quad protocol bit. */
		wrr_val[1] = (wrr_val[1] & ~mask) | val;
		need_update = true;
	} else {
		trace_debug("QSPI Flash: Spansion Quad mode already enabled\r\n");
	}

	if (!need_update)
		return 0;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	/* Write the Status and Config Registers. */
	ret = _qspiflash_write_reg(flash, CMD_WRITE_STATUS, wrr_val, sizeof(wrr_val));
	if (ret < 0)
		return ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	/* Read the Configuration Register and check it. */
	ret = _qspiflash_read_reg(flash, CMD_READ_CONFIG, &wrr_val[1], 1);
	if (ret < 0)
		return ret;

	if ((wrr_val[1] & mask) != val)
		return -EIO;

	return 0;
}

static int _spansion_set_dummy_cycles(struct _qspiflash *flash,
		uint8_t num_dummy_cycles)
{
	/* Save the number of mode/dummy cycles to use with Fast Read commands. */
	if (num_dummy_cycles) {
		flash->num_mode_cycles = 2;
		flash->num_dummy_cycles = num_dummy_cycles - 2;
	} else {
		flash->num_mode_cycles = 0;
		flash->num_dummy_cycles = 0;
	}

	/* The upper nibble (bits 7-4) of the Mode bits control the length of the
	   next Quad I/O High Performance instruction through the inclusion or
	   exclusion of the first byte instruction code. The lower nibble (bits 3-0)
	   of the Mode bits are DON'T CARE ("x"). If the Mode bits equal Axh, then
	   the device remains in Quad I/O High Performance Read Mode and the next
	   address can be entered (after CS# is raised high and then asserted low)
	   without requiring the EBh instruction opcode. */
	flash->normal_read_mode = 0x00;
	flash->continuous_read_mode = 0xA0;

	return 0;
}

static int _qspiflash_init_spansion(struct _qspiflash *flash)
{
	int ret;

	if (flash->desc->flags & SPINOR_FLAG_QUAD) {
		/* Puts the device into Quad I/O mode */
		ret = _spansion_set_protocol(flash, CR_SPANSION_QUAD, CR_SPANSION_QUAD);
		if (ret < 0)
			return ret;

		flash->opcode_read = CMD_FAST_READ_1_4_4;
		flash->ifr_width_read = QSPI_IFR_WIDTH_QUAD_IO;

		if (flash->desc->flags & SPINOR_FLAG_QPP) {
			flash->opcode_page_program = CMD_SPANSION_QPP;
			flash->ifr_width_program = QSPI_IFR_WIDTH_QUAD_OUTPUT;
		}
	}

	ret = _spansion_set_dummy_cycles(flash, 6);
	if (ret < 0)
		return ret;

	return 0;
}

/*----------------------------------------------------------------------------
 *        Local Functions (SST/Microchip support)
 *----------------------------------------------------------------------------*/

static int _qspiflash_init_sst(struct _qspiflash *flash)
{
	int ret;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	return _qspiflash_write_reg(flash, CMD_SST_ULBPR, NULL, 0);
}


/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

int qspiflash_configure(struct _qspiflash *flash, Qspi *qspi)
{
	int i, ret;

	memset(flash, 0, sizeof(*flash));
	flash->qspi = qspi;

	uint32_t jedec_id = 0;
	for (i = 0; !flash->desc && i < ARRAY_SIZE(configs); i++) {
		trace_debug("Trying protocol %u opcode 0x%02x\r\n",
				(unsigned)configs[i].ifr_width,
				configs[i].opcode);

		/* Switch QSPI protocol */
		flash->ifr_width_reg = configs[i].ifr_width;
		flash->ifr_width_read = configs[i].ifr_width;
		flash->ifr_width_program = configs[i].ifr_width;
		flash->ifr_width_erase = configs[i].ifr_width;

		/* Read JEDEC ID */
		jedec_id = 0;
		if (_qspiflash_read_reg(flash, configs[i].opcode, &jedec_id, 3) < 0)
			continue;

		if (jedec_id != 0xffffff) {
			trace_debug("Found memory with JEDEC ID 0x%08x.\r\n",
					(unsigned)jedec_id);

			/* Look for a supported flash */
			flash->desc = spi_nor_find(jedec_id);
			if (!flash->desc)
				trace_warning("Memory with JEDEC ID 0x%08x is not supported\r\n",
						(unsigned)jedec_id);
		}
	}

	/* Not found */
	if (!flash->desc) {
		trace_debug("No supported memory found.\r\n");
		return -ENODEV;
	} else {
		trace_debug("Found supported memory with JEDEC ID 0x%08x (%s).\r\n",
				(unsigned)jedec_id, flash->desc->name);
	}

	/* Set default settings */
	flash->opcode_read = CMD_FAST_READ;
	flash->opcode_page_program = CMD_PAGE_PROGRAM;
	flash->opcode_sector_erase = CMD_SECTOR_ERASE;
	flash->opcode_block_erase = CMD_BLOCK_ERASE;
	flash->opcode_block_erase_32k = CMD_BLOCK_ERASE_32K;
	flash->mode_addr4 = false;
#ifdef CONFIG_HAVE_AESB
	flash->use_aesb = false;
#endif
	flash->num_mode_cycles = 0;
	flash->num_dummy_cycles = 8;

	/* Initialize */
	for (i = 0;  i < ARRAY_SIZE(flash_inits); i++) {
		if ((jedec_id & 0xff) == flash_inits[i].manuf_id) {
			ret = flash_inits[i].init(flash);
			if (ret < 0) {
				trace_warning("Could not initialize QSPI memory\r\n");
				return ret;
			}
		}
	}

	/* Convert opcodes to their 4byte address version for >16MB memories */
	if (flash->desc->size > 16 * 1024 * 1024) {
		if (flash->desc->flags & SPINOR_FLAG_ENTER_4B_MODE) {
			ret = !_qspiflash_enter_addr4_mode(flash);
			if (ret < 0) {
				trace_warning("Could not switch QSPI memory to 4-byte address mode\r\n");
				return ret;
			}
		} else {
			flash->mode_addr4 = true;
			flash->opcode_read = qspi_flash_3to4_opcode(flash->opcode_read);
			flash->opcode_page_program = qspi_flash_3to4_opcode(flash->opcode_page_program);
			flash->opcode_sector_erase = qspi_flash_3to4_opcode(flash->opcode_sector_erase);
			flash->opcode_block_erase = qspi_flash_3to4_opcode(flash->opcode_block_erase);
			flash->opcode_block_erase_32k = qspi_flash_3to4_opcode(flash->opcode_block_erase_32k);
		}
	}

	return 0;
}

#ifdef CONFIG_HAVE_AESB
void qspiflash_use_aesb(struct _qspiflash *flash, bool enable)
{
	flash->use_aesb = enable;
}
#endif

int qspiflash_read_status(const struct _qspiflash *flash, uint8_t *status)
{
	return _qspiflash_read_reg(flash, CMD_READ_STATUS, status, 1);
}

int qspiflash_wait_ready(const struct _qspiflash *flash, uint32_t timeout)
{
	struct _timeout to;
	timer_start_timeout(&to, timeout);
	do {
		int ret;
		uint8_t status, flag_status;

		ret = _qspiflash_read_flag_status(flash, &flag_status);
		if (ret < 0)
			return ret;
		ret = qspiflash_read_status(flash, &status);
		if (ret < 0)
			return ret;

		if (((status & SR_WIP) == 0) && ((flag_status & FSR_NBUSY) != 0))
			return 0;
	} while (!timer_timeout_reached(&to));

	trace_debug("qspiflash_wait_ready timeout reached\r\n");

	/* Timed out */
	return -EBUSY;
}

int qspiflash_read_jedec_id(const struct _qspiflash *flash,
		uint32_t *jedec_id)
{
	int ret;
	uint32_t cmd = flash->ifr_width_reg == QSPI_IFR_WIDTH_SINGLE_BIT_SPI ? CMD_READ_ID : CMD_MULTI_IO_READ_ID;
	uint32_t id = 0;
	ret = _qspiflash_read_reg(flash, cmd, &id, 3);
	if (ret < 0)
		return ret;
	*jedec_id = id;
	return 0;
}

int qspiflash_read(const struct _qspiflash *flash, uint32_t addr, void *data,
		uint32_t length)
{
	int ret;
	uint8_t mode = data ? flash->normal_read_mode : flash->continuous_read_mode;
	struct _qspi_cmd cmd;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_READ_MEMORY;
	cmd.ifr_width = flash->ifr_width_read;
	cmd.enable.instruction = 1;
	cmd.enable.address = flash->mode_addr4 ? 4 : 3;
	cmd.enable.mode = (flash->num_mode_cycles > 0);
	cmd.enable.dummy = (flash->num_dummy_cycles > 0);
	cmd.enable.data = 1;
	cmd.instruction = flash->opcode_read;
#ifdef CONFIG_HAVE_AESB
	cmd.use_aesb = flash->use_aesb;
#endif
	cmd.mode = mode;
	cmd.num_mode_cycles = flash->num_mode_cycles;
	cmd.num_dummy_cycles = flash->num_dummy_cycles;
	cmd.address = addr;
	cmd.rx_buffer = data;
	cmd.buffer_len = length;
	cmd.timeout = TIMEOUT_DEFAULT;
	if (!qspi_perform_command(flash->qspi, &cmd))
	       return -EIO;
	return 0;
}

int qspiflash_erase_chip(const struct _qspiflash *flash)
{
	int ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	ret = _qspiflash_write_reg(flash, CMD_BULK_ERASE, NULL, 0);
	if (ret < 0)
		return ret;

	ret = qspiflash_wait_ready(flash, TIMEOUT_ERASE_CHIP);
	if (ret < 0)
		return ret;

	return 0;
}

int qspiflash_erase_block(const struct _qspiflash *flash,
		uint32_t addr, uint32_t length)
{
	int ret;
	uint32_t flags = flash->desc->flags;
	struct _qspi_cmd cmd;
	uint8_t instr;

	switch (length) {
	case 256 * 1024:
		if (flags & SPINOR_FLAG_ERASE_256K) {
			instr = flash->opcode_block_erase;
		} else {
			trace_error("qspiflash: 256K Erase not supported\r\n");
			return -EINVAL;
		}
		break;
	case 64 * 1024:
		if (flags & SPINOR_FLAG_ERASE_64K) {
			instr = flash->opcode_block_erase;
		} else {
			trace_error("qspiflash: 64K Erase not supported\r\n");
			return -EINVAL;
		}
		break;
	case 32 * 1024:
		if (flags & SPINOR_FLAG_ERASE_32K) {
			instr = flash->opcode_block_erase_32k;
		} else {
			trace_error("qspiflash: 32K Erase not supported\r\n");
			return -EINVAL;
		}
		break;
	case 4 * 1024:
		if (flags & SPINOR_FLAG_ERASE_4K) {
			instr = flash->opcode_sector_erase;
		} else {
			trace_error("qspiflash: 4K Erase not supported\r\n");
			return -EINVAL;
		}
		break;
	default:
		trace_error("qspiflash: unsupported erase length (%u)\r\n",
				(unsigned)length);
		return -EINVAL;
	}

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	ret = _qspiflash_write_enable(flash);
	if (ret < 0)
		return ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE;
	cmd.ifr_width = flash->ifr_width_erase;
	cmd.enable.instruction = 1;
#ifdef CONFIG_HAVE_AESB
	cmd.use_aesb = flash->use_aesb;
#endif
	cmd.enable.address = flash->mode_addr4 ? 4 : 3;
	cmd.instruction = instr;
	cmd.address = addr;
	cmd.timeout = TIMEOUT_DEFAULT;
	if (!qspi_perform_command(flash->qspi, &cmd))
		return -EIO;

	ret = qspiflash_wait_ready(flash, TIMEOUT_ERASE);
	if (ret < 0)
		return ret;

	return 0;
}

int qspiflash_write(const struct _qspiflash *flash, uint32_t addr,
		const void *data, uint32_t length)
{
	int ret;
	struct _qspi_cmd cmd;
	uint32_t written = 0;
	const uint8_t *ptr = data;

	ret = qspiflash_wait_ready(flash, TIMEOUT_DEFAULT);
	if (ret < 0)
		return ret;

	while (written < length) {
		/* remaining size in current page */
		uint32_t remaining = flash->desc->page_size
			- (addr % flash->desc->page_size);
		/* number of bytes to write this round */
		uint32_t count = min_u32(length - written, remaining);

		ret = _qspiflash_write_enable(flash);
		if (ret < 0)
			return ret;

		memset(&cmd, 0, sizeof(cmd));
		cmd.ifr_type = QSPI_IFR_TFRTYP_TRSFR_WRITE_MEMORY;
		cmd.ifr_width = flash->ifr_width_program;
		cmd.enable.instruction = 1;
		cmd.enable.address = flash->mode_addr4 ? 4 : 3;
#ifdef CONFIG_HAVE_AESB
		cmd.use_aesb = flash->use_aesb;
#endif
		cmd.enable.data = 1;
		cmd.instruction = flash->opcode_page_program;
		cmd.address = addr;
		cmd.tx_buffer = ptr;
		cmd.buffer_len = count;
		cmd.timeout = TIMEOUT_DEFAULT;

		if (!qspi_perform_command(flash->qspi, &cmd))
			return -EIO;

		ret = qspiflash_wait_ready(flash, TIMEOUT_WRITE);
		if (ret < 0)
			return ret;

		written += count;
		addr += count;
		ptr += count;
	}

	return 0;
}
