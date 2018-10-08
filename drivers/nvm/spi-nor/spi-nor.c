/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "errno.h"
#include "intmath.h"
#include "mm/cache.h"
#include "nvm/spi-nor/spi-nor.h"
#include "peripherals/bus.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Debug Constants
 *----------------------------------------------------------------------------*/

//#define SPI_NOR_VERBOSE_DEBUG

/*----------------------------------------------------------------------------
 *        Local Variables
 *----------------------------------------------------------------------------*/

static struct spi_flash_parameters params;

static CACHE_ALIGNED uint8_t _spi_flash_hdr[16];
static struct _buffer _bus_exec_buffer[2];

static const char flash_name[] = "unknown";

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static const struct spi_nor_info *spi_nor_read_id(struct spi_flash *flash)
{
	const struct spi_nor_info *info;
	char id_str[8], *p;
	int i, rc;

#ifdef SPI_NOR_VERBOSE_DEBUG
	trace_debug("spi-nor: cmd: 0x%02x\r\n", SFLASH_INST_READ_ID);
#endif
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_ID, flash->id, sizeof(flash->id));
	if (rc < 0)
		return NULL;

	p = id_str;
	for (i = 0; i < 3; i++) {
		uint8_t lo = (flash->id[i] & 0x0f) >> 0;
		uint8_t hi = (flash->id[i] & 0xf0) >> 4;

		*p++ = (hi < 10) ? ('0' + hi) : ('a' + hi - 10);
		*p++ = (lo < 10) ? ('0' + lo) : ('a' + lo - 10);
	}
	*p = '\0';
	trace_info("SF: Got Manufacturer and Device ID: %s\r\n", id_str);

	for (info = spi_nor_ids; info->name; info++) {
		if (!memcmp(info->id, flash->id, info->id_len))
			return info;
	}

	return NULL;
}

static int spi_nor_init_params(struct spi_flash *flash, const struct spi_nor_info *info, struct spi_flash_parameters *fparams)
{
	struct spi_flash_erase_map *map = &flash->erase_map;
	uint32_t erase_mask = 0;
	uint32_t erase_offset = 0;

	if (info && info->params)
		memcpy(fparams, info->params, sizeof(*fparams));
	else
		memset(fparams, 0, sizeof(*fparams));

	/* Set SPI NOR sizes. */
	if (info) {
		fparams->size = info->sector_size * info->n_sectors;
		fparams->page_size = info->page_size;
	} else {
		flash->page_size = 256;
	}

	/* Set legacy flash parameters as default. */
	if (info && info->params)
		goto set_erase_map;

	/* (Fast) Read settings. */
	fparams->hwcaps.mask |= SFLASH_HWCAPS_READ;
	spi_flash_set_read_settings(&fparams->reads[SFLASH_CMD_READ], 0, 0, SFLASH_INST_READ, SFLASH_PROTO_1_1_1);
	if (!info || !(info->flags & SNOR_NO_FR)) {
		fparams->hwcaps.mask |= SFLASH_HWCAPS_READ_FAST;
		spi_flash_set_read_settings(&fparams->reads[SFLASH_CMD_READ_FAST], 0, 8, SFLASH_INST_FAST_READ, SFLASH_PROTO_1_1_1);
	}

	/* Page Program settings. */
	fparams->hwcaps.mask |= SFLASH_HWCAPS_PP;
	spi_flash_set_pp_settings(&fparams->page_programs[SFLASH_CMD_PP], SFLASH_INST_PAGE_PROGRAM, SFLASH_PROTO_1_1_1);

	/* Sector Erase settings. */
set_erase_map:
	if (info && info->flags & SNOR_SECT_4K_ONLY) {
		erase_mask |= (0x1UL << erase_offset);
		spi_flash_set_erase_command(&map->commands[erase_offset], 4096u, SFLASH_INST_ERASE_4K);
		erase_offset++;
	} else {
		/* 64KB erase is always supported */
		erase_mask |= (0x1UL << erase_offset);
		spi_flash_set_erase_command(&map->commands[erase_offset], info ? info->sector_size : 65536u, SFLASH_INST_ERASE_64K);
		erase_offset++;

		if (info && info->flags & SNOR_SECT_4K) {
			erase_mask |= (0x1UL << erase_offset);
			spi_flash_set_erase_command(&map->commands[erase_offset], 4096u, SFLASH_INST_ERASE_4K);
			erase_offset++;
		}

		if (info && info->flags & SNOR_SECT_32K) {
			erase_mask |= (0x1UL << erase_offset);
			spi_flash_set_erase_command(&map->commands[erase_offset], 32768u, SFLASH_INST_ERASE_32K);
			erase_offset++;
		}
	}
	spi_flash_init_uniform_erase_map(map, erase_mask, fparams->size);

	/* Quad Enable Requirements & 0-4-4 Mode Entry Method. */
	flash->enable_0_4_4 = NULL;
	switch (spi_flash_get_mfr(flash)) {
	case SFLASH_MFR_MICRON:
		fparams->quad_enable = NULL;
		flash->enable_0_4_4 = micron_enable_0_4_4;
		flash->xip_mode = 0x00u;
		break;

	case SFLASH_MFR_MACRONIX:
		fparams->quad_enable = macronix_quad_enable;
		break;

	case SFLASH_MFR_ATMEL:
		flash->set_protection = at25_set_protection;
		break;

	case SFLASH_MFR_SST:
		flash->xip_mode = 0xa0u;
		fparams->hwcaps.mask |= SFLASH_HWCAPS_READ_1_4_4;
		fparams->reads[SFLASH_CMD_READ_1_4_4].num_mode_cycles = 2;
		fparams->reads[SFLASH_CMD_READ_1_4_4].num_wait_states = 4;
		fparams->reads[SFLASH_CMD_READ_1_4_4].inst = SFLASH_INST_FAST_READ_1_4_4;
		fparams->reads[SFLASH_CMD_READ_1_4_4].proto = SFLASH_PROTO_1_4_4;
		fparams->quad_enable = spansion_new_quad_enable;
		break;

	default:
		fparams->quad_enable = spansion_quad_enable;
		break;
	}

	/* Override the parameters with data read from SFDP tables. */
	if (!info || !(info->flags & SNOR_SKIP_SFDP))
		spi_flash_parse_sfdp(flash, fparams);

	return 0;
}

static uint8_t spi_nor_convert_inst(uint8_t inst, const uint8_t table[][2], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (table[i][0] == inst)
			return table[i][1];

	/* No conversion found, keep input op code. */
	return inst;
}

static inline uint8_t spi_nor_convert_3to4_read(uint8_t inst)
{
	static const uint8_t spi_nor_3to4_read[][2] = {
		{ SFLASH_INST_READ,		SFLASH_INST_READ_4B },
		{ SFLASH_INST_FAST_READ,	SFLASH_INST_FAST_READ_4B },
		{ SFLASH_INST_FAST_READ_1_1_2,	SFLASH_INST_FAST_READ_1_1_2_4B },
		{ SFLASH_INST_FAST_READ_1_2_2,	SFLASH_INST_FAST_READ_1_2_2_4B },
		{ SFLASH_INST_FAST_READ_1_1_4,	SFLASH_INST_FAST_READ_1_1_4_4B },
		{ SFLASH_INST_FAST_READ_1_4_4,	SFLASH_INST_FAST_READ_1_4_4_4B },
	};

	return spi_nor_convert_inst(inst, spi_nor_3to4_read,
				    ARRAY_SIZE(spi_nor_3to4_read));
}

static inline uint8_t spi_nor_convert_3to4_write(uint8_t inst)
{
	static const uint8_t spi_nor_3to4_program[][2] = {
		{ SFLASH_INST_PAGE_PROGRAM,		SFLASH_INST_PAGE_PROGRAM_4B },
		{ SFLASH_INST_PAGE_PROGRAM_1_1_4,	SFLASH_INST_PAGE_PROGRAM_1_1_4_4B },
		{ SFLASH_INST_PAGE_PROGRAM_1_4_4,	SFLASH_INST_PAGE_PROGRAM_1_4_4_4B },
	};

	return spi_nor_convert_inst(inst, spi_nor_3to4_program,
				    ARRAY_SIZE(spi_nor_3to4_program));
}

static inline uint8_t spi_nor_convert_3to4_erase(uint8_t inst)
{
	static const uint8_t spi_nor_3to4_erase[][2] = {
		{ SFLASH_INST_ERASE_4K,		SFLASH_INST_ERASE_4K_4B },
		{ SFLASH_INST_ERASE_32K,	SFLASH_INST_ERASE_32K_4B },
		{ SFLASH_INST_ERASE_64K,	SFLASH_INST_ERASE_64K_4B },
	};

	return spi_nor_convert_inst(inst, spi_nor_3to4_erase,
				    ARRAY_SIZE(spi_nor_3to4_erase));
}

static void spi_nor_set_4bais(struct spi_flash *flash)
{
	struct spi_flash_erase_map *map = &flash->erase_map;
	int i;

	flash->read_inst = spi_nor_convert_3to4_read(flash->read_inst);
	flash->write_inst = spi_nor_convert_3to4_write(flash->write_inst);

	for (i = 0; i < SFLASH_CMD_ERASE_MAX; i++) {
		struct spi_flash_erase_command *cmd = &map->commands[i];

		cmd->inst = spi_nor_convert_3to4_erase(cmd->inst);
	}

	flash->addr_len = 4;
}

static int sst26_unlock_block_protection(struct spi_flash *flash)
{
	int rc;

	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_ULBPR, NULL, 0);
	return rc < 0 ? rc : spi_flash_wait_till_ready(flash);
}

static int spi_nor_clear_sr_bp(struct spi_flash *flash)
{
	uint8_t sr = 0;
	int rc;

	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, &sr, 1);
	return rc < 0 ? rc : spi_flash_wait_till_ready(flash);
}

static int spi_nor_probe(struct spi_flash *flash)
{
	const struct spi_nor_info *info;
	int rc;

	/* Check minimum requirement. */
	if (!flash->ops)
		return -EINVAL;

	/*
	 * Reset the SPI flash memory:
	 * exit the 4-byte address and/or the 4-4-4 modes.
	 */
	if (flash->hwcaps.mask & (SFLASH_HWCAPS_READ_4_4_4 | SFLASH_HWCAPS_PP_4_4_4)) {
		flash->reg_proto = SFLASH_PROTO_4_4_4;
		spi_flash_reset(flash);
	}
	flash->reg_proto = SFLASH_PROTO_1_1_1;
	spi_flash_reset(flash);
	usleep(50);

	/* Set default settings. */
	flash->read_proto = SFLASH_PROTO_1_1_1;
	flash->write_proto = SFLASH_PROTO_1_1_1;
	flash->read = spi_nor_read;
	flash->write = spi_nor_write;
	flash->erase = spi_nor_erase;
	flash->flags = 0;
	flash->normal_mode = 0xFFu;
	flash->xip_mode = 0xA5u;

	/* Get the static SPI flash info (might by NULL). */
	info = spi_nor_read_id(flash);
	if (!info) {
		flash->name = flash_name;
		goto init_params;
	}

	if (info->flags & SNOR_HAS_FSR)
		flash->flags |= SFLASH_FLG_HAS_FSR;

	if (info->flags & SNOR_SST_ULBPR)
		if (sst26_unlock_block_protection(flash))
			trace_info("SF: WARNING: SST26 - can't unlock block protection\r\n");

	if (info->flags & SNOR_CLEAR_SR_BP)
		if (spi_nor_clear_sr_bp(flash))
			trace_warning("SF: WARNING: can't clear Block Protection bits in Status Register\r\n");

	flash->name = info->name;

	/* Parse the Serial Flash Discoverable Parameter tables. */
init_params:
	rc = spi_nor_init_params(flash, info, &params);
	if (rc < 0)
		return rc;

	if (params.size == 0)
		return -ENODEV;

	flash->size = params.size;
	if (params.page_size > 0)
		flash->page_size = params.page_size;

	/*
	 * Configure the SPI memory:
	 * - select instructions for (Fast) Read, Page Program and Sector Erase.
	 * - set the number of mode & wait state cycles.
	 * - set the SPI protocols for register and memory accesses.
	 * - set the Quad Enable bit if needed (required by SPI x-y-4 protos).
	 */
	rc = spi_flash_setup(flash, &params);
	if (rc < 0)
		return rc;

	if (info && info->addr_len) {
		flash->addr_len = info->addr_len;
	} else {
		flash->addr_len = 3;
		if (flash->size > 0x01000000u) {
			if (!info || !(info->flags & SNOR_NO_4BAIS))
				spi_nor_set_4bais(flash);
			else
				trace_info("SF: WARNING: can't read above 16MiB\r\n");
		}
	}

	return 0;
}

static int _bus_init(union spi_flash_priv* priv)
{
	return 0;
}

static int _bus_cleanup(union spi_flash_priv* priv)
{
	return 0;
}

static int _bus_set_freq(union spi_flash_priv* priv, uint32_t freq)
{
	priv->spi.spi_dev.bitrate = freq;
	return bus_configure_slave(priv->spi.bus, &priv->spi);
}

static int _bus_set_mode(union spi_flash_priv* priv, uint8_t mode)
{
	priv->spi.spi_dev.spi_mode = mode;
	return bus_configure_slave(priv->spi.bus, &priv->spi);
}

static int _bus_exec(union spi_flash_priv* priv, const struct spi_flash_command *cmd)
{
	int rc;
	uint8_t buffers = 2;
	uint8_t *data = _spi_flash_hdr;


	*data++ = cmd->inst;
	switch (cmd->addr_len) {
	case 4:
		*data++ = (cmd->addr >> 24) & 0xff;
	case 3:
		*data++ = (cmd->addr >> 16) & 0xff;
		*data++ = (cmd->addr >> 8) & 0xff;
		*data++ = (cmd->addr >> 0) & 0xff;
		break;
	case 0:
	default:
		break;
	}
	if (cmd->num_mode_cycles / 8)
		memset(data, cmd->mode, cmd->num_mode_cycles / 8);

	_bus_exec_buffer[0].data = _spi_flash_hdr;
	_bus_exec_buffer[0].attr = BUS_BUF_ATTR_TX;
	_bus_exec_buffer[0].size = 1 + cmd->addr_len + cmd->num_mode_cycles / 8 + cmd->num_wait_states / 8;

	switch (cmd->flags) {
	case SFLASH_TYPE_READ:
	case SFLASH_TYPE_READ_REG:
#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_debug("spi-nor: READ*\r\n");
#endif
		_bus_exec_buffer[1].data = cmd->rx_data;
		_bus_exec_buffer[1].size = cmd->data_len;
		_bus_exec_buffer[1].attr = BUS_BUF_ATTR_RX;
		if (cmd->data_len)
			_bus_exec_buffer[1].attr |= BUS_SPI_BUF_ATTR_RELEASE_CS;
		break;
	case SFLASH_TYPE_WRITE:
	case SFLASH_TYPE_WRITE_REG:
#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_debug("spi-nor: WRITE*\r\n");
#endif
		if (cmd->data_len) {
			_bus_exec_buffer[1].data = (uint8_t*)cmd->tx_data;
			_bus_exec_buffer[1].size = cmd->data_len;
			_bus_exec_buffer[1].attr = BUS_BUF_ATTR_TX | BUS_SPI_BUF_ATTR_RELEASE_CS;
		} else {
			buffers = 1;
			_bus_exec_buffer[0].attr |= BUS_SPI_BUF_ATTR_RELEASE_CS;
		}
		break;
	case SFLASH_TYPE_ERASE:
#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_debug("spi-nor: ERASE\r\n");
#endif
		buffers = 1;
		_bus_exec_buffer[0].attr |= BUS_SPI_BUF_ATTR_RELEASE_CS;
		break;
	default:
		return -EINVAL;
	}

#ifdef SPI_NOR_VERBOSE_DEBUG
	trace_debug("spi-nor: inst: 0x%02x\r\n", cmd->inst);
	if (cmd->addr_len) {
		trace_debug("spi-nor: addr_len: %u\r\n", cmd->addr_len);
		trace_debug("spi-nor: addr: %x\r\n", cmd->addr);
	}
	if (cmd->data_len) {
		trace_debug("spi-nor: len: 0x%x\r\n", cmd->data_len);
		trace_debug("spi-nor: buffer: %p\r\n", _bus_exec_buffer[1].data);
	}
#endif

	bus_start_transaction(priv->spi.bus);
	rc = bus_transfer(priv->spi.bus, priv->spi.spi_dev.chip_select, _bus_exec_buffer, buffers, NULL);
	bus_wait_transfer(priv->spi.bus);
	bus_stop_transaction(priv->spi.bus);

	return rc;
}

static const struct spi_ops _spi_bus_ops = {
	.init		= _bus_init,
	.cleanup	= _bus_cleanup,
	.set_freq	= _bus_set_freq,
	.set_mode	= _bus_set_mode,
	.exec		= _bus_exec,
};

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

int spansion_quad_enable(struct spi_flash *flash)
{
	uint8_t sr[2];
	int rc;

	/* Keep the current value of the Status Register. */
	rc = spi_flash_read_sr(flash, &sr[0]);
	if (rc < 0)
		return rc;

	/* Set the Status and Control/Status 2 Registers. */
	sr[1] = CR_QE_SPAN;
	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, sr, 2);
	return rc < 0 ? rc : spi_flash_wait_till_ready(flash);
}

int spansion_new_quad_enable(struct spi_flash *flash)
{
	uint8_t sr[2];
	int rc;

	/* Check the current Quand Enable bit value. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_CR, &sr[1], 1);
	if (rc < 0)
		return rc;

	if (sr[1] & CR_QE_SPAN)
		return 0;

	/* Keep the current value of the Status Register. */
	rc = spi_flash_read_sr(flash, &sr[0]);
	if (rc < 0)
		return rc;

	/* Set the Status and Control/Status 2 Registers. */
	sr[1] |= CR_QE_SPAN;
	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, sr, 2);
	rc = rc < 0 ? rc : spi_flash_wait_till_ready(flash);
	if (rc < 0)
		return rc;

	/* Read back and check. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_CR, &sr[1], 1);
	if (rc < 0)
		return rc;

	return (sr[1] & CR_QE_SPAN) ? 0 : -1;
}

int macronix_quad_enable(struct spi_flash *flash)
{
	uint8_t sr;
	int rc;

	/* Check the current Quand Enable bit value. */
	rc = spi_flash_read_sr(flash, &sr);
	if (rc < 0)
		return rc;

	if (sr & SR_QE_MX)
		return 0;

	/* Set the Status and Control/Status 2 Registers. */
	sr |= SR_QE_MX;
	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, &sr, 1);
	rc = rc < 0 ? rc : spi_flash_wait_till_ready(flash);
	if (rc < 0)
		return rc;

	/* Read back and check. */
	rc = spi_flash_read_sr(flash, &sr);
	if (rc < 0)
		return rc;

	return (sr & SR_QE_MX) ? 0 : -1;
}

int sr2_bit7_quad_enable(struct spi_flash *flash)
{
	uint8_t sr2;
	int rc;

	/* Check the current Quand Enable bit value. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_SR2, &sr2, 1);
	if (rc < 0)
		return rc;

	if (sr2 & SR2_QE_BIT7)
		return 0;

	/* Set the Status and Control/Status 2 Registers. */
	sr2 |= SR2_QE_BIT7;
	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR2, &sr2, 1);
	rc = rc < 0 ? rc : spi_flash_wait_till_ready(flash);
	if (rc < 0)
		return rc;

	/* Read back and check. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_SR2, &sr2, 1);
	if (rc < 0)
		return rc;

	return (sr2 & SR2_QE_BIT7) ? 0 : -1;
}

int micron_enable_0_4_4(struct spi_flash *flash, bool enable)
{
	uint8_t vcr, mask, value;
	int rc;

	mask = VCR_XIP;
	value = (enable) ? 0 : VCR_XIP;

	/* Check the current XIP bit value. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_VCR, &vcr, 1);
	if (rc < 0)
		return rc;

	if ((vcr & mask) == value)
		return 0;

	/* Update the XIP bit value. */
	vcr = (vcr & ~mask) | value;
	rc = spi_flash_write_enable(flash);
	rc = rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_WRITE_VCR, &vcr, 1);
	rc = rc < 0 ? rc : spi_flash_wait_till_ready(flash);
	if (rc < 0)
		return rc;

	/* Read back and check. */
	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_VCR, &vcr, 1);
	if (rc < 0)
		return rc;

	return ((vcr & mask) == value) ? 0 : -1;
}

int at25_set_protection(struct spi_flash *flash, bool protect)
{
	uint8_t sr;
	int rc;

	rc = spi_flash_read_sr(flash, &sr);
	if (rc < 0)
		return rc;
#ifdef SPI_NOR_VERBOSE_DEBUG
	trace_info("spi-nor: protection: %s\r\n", sr & SR_SWP ? "on" : "off");
#endif

	rc = spi_flash_write_enable(flash);
	if (rc < 0)
		return rc;

	if (protect) {
#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_info("spi-nor: lock all\r\n");
#endif
		/* Perform a global protect command */
		sr |= SR_SWP_PROTECT_ALL;
		rc = spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, &sr, 1);
		if (rc < 0)
			return rc;
	} else {
#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_info("spi-nor: unlock all\r\n");
#endif
		/* Get the status register value to check the current protection */
		if ((sr & SR_SWP) == SR_SWP_PROTECT_NONE)
			return 0;

		/* Perform a global unprotect command */
		sr = 0;
		rc = spi_flash_write_reg(flash, SFLASH_INST_WRITE_SR, &sr, 1);
		if (rc < 0)
			return rc;

		/* Check the new status */
		rc = spi_flash_read_sr(flash, &sr);
		if (rc < 0)
			return rc;
		if (sr & (SR_SPRL_LOCKED | SR_SWP))
			return -EPERM;
	}

#ifdef SPI_NOR_VERBOSE_DEBUG
	trace_info("spi-nor: protection: %s\r\n", sr & SR_SWP ? "on" : "off");
#endif

	return 0;
}

int spi_nor_configure(struct spi_flash *flash, const struct spi_flash_cfg *cfg)
{
	int rc;

	memset(flash, 0, sizeof(struct spi_flash));

	switch (cfg->type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case SPI_FLASH_TYPE_SPI:
		/* SPI bus already initialized in board_cfg_spi_bus() */
		flash->ops = &_spi_bus_ops;
		flash->priv.spi = cfg->spi.bus_cfg;
		flash->hwcaps.mask = (SFLASH_HWCAPS_READ | SFLASH_HWCAPS_READ_FAST | SFLASH_HWCAPS_PP);
		break;
#endif
#ifdef CONFIG_HAVE_QSPI
	case SPI_FLASH_TYPE_QSPI:
		qspi_configure(flash, cfg);
		break;
#endif
	default:
		return -EINVAL;
	}

	/* Init the SPI controller. */
	rc = spi_flash_init(flash);
	if (rc < 0) {
		trace_info("SF: Fail to initialize spi\r\n");
		return rc;
	}

	/* Set the SPI mode. */
	rc = spi_flash_set_mode(flash, cfg->mode);
	if (rc < 0)
		return rc;

	/* Set the new baudrate. */
	rc = spi_flash_set_freq(flash, cfg->baudrate);
	if (rc < 0)
		return rc;

	/* Probe the SPI flash memory. */
	rc = spi_nor_probe(flash);
	if (rc < 0) {
		trace_info("SF: Fail to probe SPI flash\r\n");
		spi_flash_cleanup(flash);
		return rc;
	}

	return 0;
}

int spi_nor_read(struct spi_flash *flash, size_t from, uint8_t* buf, size_t len)
{
	struct spi_flash_command cmd;

	spi_flash_command_init(&cmd, flash->read_inst, flash->addr_len, SFLASH_TYPE_READ);
	cmd.proto = flash->read_proto;
	cmd.addr = from;
	cmd.mode = buf ? flash->normal_mode : flash->xip_mode;
	cmd.num_mode_cycles = flash->num_mode_cycles;
	cmd.num_wait_states = flash->num_wait_states;
	cmd.data_len = len;
	cmd.rx_data = buf;
#ifdef CONFIG_HAVE_AESB
	cmd.use_aesb = flash->use_aesb;
#endif
	return spi_flash_exec(flash, &cmd);
}

int spi_nor_write(struct spi_flash *flash, size_t to, const uint8_t* buf, size_t len)
{
	struct spi_flash_command cmd;
	int rc = 0;

	rc = spi_flash_set_protection(flash, false);
	if (rc < 0)
		return rc;

	spi_flash_command_init(&cmd, flash->write_inst, flash->addr_len, SFLASH_TYPE_WRITE);
	cmd.proto = flash->write_proto;
#ifdef CONFIG_HAVE_AESB
	cmd.use_aesb = flash->use_aesb;
#endif
	while (len) {
		size_t page_offset, page_remain;

		page_offset = to & (flash->page_size - 1);
		page_remain = min_u32(flash->page_size - page_offset, len);

		cmd.addr = to;
		cmd.data_len = page_remain;
		cmd.tx_data = buf;

		rc = spi_flash_write_enable(flash);
		if (rc < 0)
			break;

		rc = spi_flash_exec(flash, &cmd);
		if (rc < 0)
			break;

		rc = spi_flash_wait_till_ready(flash);
		if (rc < 0)
			break;

		buf += page_remain;
		to += page_remain;
		len -= page_remain;
	}

	return rc;
}

int spi_nor_erase(struct spi_flash *flash, size_t offset, size_t len)
{
	const struct spi_flash_erase_map *map = &flash->erase_map;
	struct spi_flash_command cmd;
	int rc = 0;

	rc = spi_flash_set_protection(flash, false);
	if (rc < 0)
		return rc;

	if (!spi_flash_has_uniform_erase(flash)) {
		/* @TODO: add support to non uniform erase map. */
		return -ENOTSUP;
	}

	rc = spi_flash_set_protection(flash, false);
	if (rc < 0)
		return rc;

	spi_flash_command_init(&cmd, 0, flash->addr_len, SFLASH_TYPE_ERASE);
	cmd.proto = flash->reg_proto;
#ifdef CONFIG_HAVE_AESB
	cmd.use_aesb = flash->use_aesb;
#endif
	while (len) {
		const struct spi_flash_erase_command *erase = NULL;
		size_t i;

		for (i = 0; i < SFLASH_CMD_ERASE_MAX; i++) {
			const struct spi_flash_erase_command *e;
			uint32_t rem;

			if ((map->uniform_region.cmd_mask & (0x1UL << i))) {
				e = &map->commands[i];
				spi_flash_div_by_erase_size(e, offset, &rem);
				if (rem)
					continue;

				if (e->size <= len && (!erase || erase->size < e->size))
					erase = e;
			}
		}
		if (!erase)
			return -1;

#ifdef SPI_NOR_VERBOSE_DEBUG
		trace_info("spi-nor: erase params: inst=0x%x\r\n", erase->inst);
		trace_info("spi-nor: erase params: size=%lu\r\n", erase->size);
		trace_info("spi-nor: erase params: size_shift=%ld\r\n", erase->size_shift);
		trace_info("spi-nor: erase params: size_mask=0x%lx\r\n", erase->size_mask);
#endif
		rc = spi_flash_write_enable(flash);
		if (rc < 0)
			break;

		cmd.inst = erase->inst;
		cmd.addr = offset;
		rc = spi_flash_exec(flash, &cmd);
		if (rc < 0)
			break;

		rc = spi_flash_wait_till_ready(flash);
		if (rc < 0)
			break;

		offset += erase->size;
		len -= erase->size;
	}

	return rc;
}
