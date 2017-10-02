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

#include "board.h"
#include "errno.h"
#include "gpio/pio.h"
#include "intmath.h"
#include "nvm/spi-nor/spi-flash.h"
#include "nvm/spi-nor/sfdp.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local Definitions
 *----------------------------------------------------------------------------*/

/* Default timeout values (in timer ticks, for 1000 Hz timer) */
#define TIMEOUT_DEFAULT       100 /* 0.1s */
#define TIMEOUT_WRITE         800 /* 0.8s */
#define TIMEOUT_ERASE        3000 /* 3s */
#define TIMEOUT_ERASE_CHIP 500000 /* 500s */

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

int spi_flash_read_reg(struct spi_flash *flash, uint8_t inst, uint8_t *buf, size_t len)
{
	struct spi_flash_command cmd;

	spi_flash_command_init(&cmd, inst, 0, SFLASH_TYPE_READ_REG);
	cmd.proto = flash->reg_proto;
	cmd.data_len = len;
	cmd.rx_data = buf;
	cmd.timeout = TIMEOUT_DEFAULT;
	return spi_flash_exec(flash, &cmd);
}

int spi_flash_write_reg(struct spi_flash *flash, uint8_t inst, const uint8_t *buf, size_t len)
{
	struct spi_flash_command cmd;

	spi_flash_command_init(&cmd, inst, 0, SFLASH_TYPE_WRITE_REG);
	cmd.proto = flash->reg_proto;
	cmd.data_len = len;
	cmd.tx_data = buf;
	cmd.timeout = TIMEOUT_DEFAULT;
	return spi_flash_exec(flash, &cmd);
}

static int spi_flash_is_ready(struct spi_flash *flash)
{
	uint8_t sr, fsr;
	int rc;

	rc = spi_flash_read_sr(flash, &sr);
	if (rc < 0)
		return rc;

	if (sr & SR_WIP)
		return 0;

	if (!(flash->flags & SFLASH_FLG_HAS_FSR))
		return 1;

	rc = spi_flash_read_reg(flash, SFLASH_INST_READ_FSR, &fsr, 1);
	if (rc < 0)
		return rc;

	return (fsr & FSR_READY) != 0;
}

int spi_flash_wait_till_ready_timeout(struct spi_flash *flash, unsigned long timeout)
{
	unsigned long delay = 1L; /* 1ms */
	unsigned long loop = (timeout + delay - 1) / (delay);
	int rc;

	if (!loop)
		loop = 1;
	while (loop-- > 0) {
		rc = spi_flash_is_ready(flash);
		if (rc < 0)
			return rc;
		if (rc)
			return 0;

		msleep(delay);
	}

	return -ETIMEDOUT;
}

int spi_flash_hwcaps2cmd(uint32_t hwcaps)
{
	switch (hwcaps) {
	case SFLASH_HWCAPS_READ:
		return SFLASH_CMD_READ;
	case SFLASH_HWCAPS_READ_FAST:
		return SFLASH_CMD_READ_FAST;
	case SFLASH_HWCAPS_READ_1_1_2:
		return SFLASH_CMD_READ_1_1_2;
	case SFLASH_HWCAPS_READ_1_2_2:
		return SFLASH_CMD_READ_1_2_2;
	case SFLASH_HWCAPS_READ_2_2_2:
		return SFLASH_CMD_READ_2_2_2;
	case SFLASH_HWCAPS_READ_1_1_4:
		return SFLASH_CMD_READ_1_1_4;
	case SFLASH_HWCAPS_READ_1_4_4:
		return SFLASH_CMD_READ_1_4_4;
	case SFLASH_HWCAPS_READ_4_4_4:
		return SFLASH_CMD_READ_4_4_4;

	case SFLASH_HWCAPS_PP:
		return SFLASH_CMD_PP;
	case SFLASH_HWCAPS_PP_1_1_4:
		return SFLASH_CMD_PP_1_1_4;
	case SFLASH_HWCAPS_PP_1_4_4:
		return SFLASH_CMD_PP_1_4_4;
	case SFLASH_HWCAPS_PP_4_4_4:
		return SFLASH_CMD_PP_4_4_4;
	}

	return -EINVAL;
}

static int spi_flash_select_read(struct spi_flash *flash, const struct spi_flash_parameters *params, uint32_t shared_hwcaps)
{
	int cmd, best_match = fls(shared_hwcaps & SFLASH_HWCAPS_READ_MASK) - 1;
	const struct spi_flash_read_command *read;

	if (best_match < 0)
		return -EINVAL;

	cmd = spi_flash_hwcaps2cmd((0x1UL << best_match));
	if (cmd < 0)
		return cmd;

	read = &params->reads[cmd];
	flash->num_mode_cycles = read->num_mode_cycles;
	flash->num_wait_states = read->num_wait_states;
	flash->read_inst = read->inst;
	flash->read_proto = read->proto;
	return 0;
}

static int spi_flash_select_pp(struct spi_flash *flash, const struct spi_flash_parameters *params, uint32_t shared_hwcaps)
{
	int cmd, best_match = fls(shared_hwcaps & SFLASH_HWCAPS_PP_MASK) - 1;
	const struct spi_flash_pp_command *pp;

	if (best_match < 0)
		return -EINVAL;

	cmd = spi_flash_hwcaps2cmd((0x1UL << best_match));
	if (cmd < 0)
		return cmd;

	pp = &params->page_programs[cmd];
	flash->write_inst = pp->inst;
	flash->write_proto = pp->proto;
	return 0;
}

int spi_flash_setup(struct spi_flash *flash, const struct spi_flash_parameters *params)
{
	uint32_t ignored_mask, shared_mask;
	int rc;

	/*
	 * Keep only the hardware capabilities supported by both the SPI
	 * controller and the SPI flash memory.
	 */
	shared_mask = flash->hwcaps.mask & params->hwcaps.mask;

	/* SPI n-n-n protocols are not supported yet. */
	ignored_mask = (SFLASH_HWCAPS_READ_2_2_2 |
			SFLASH_HWCAPS_READ_4_4_4 |
			SFLASH_HWCAPS_PP_4_4_4);
	if (shared_mask & ignored_mask)
		shared_mask &= ~ignored_mask;

	/* Select the (Fast) Read command. */
	rc = spi_flash_select_read(flash, params, shared_mask);
	if (rc < 0) {
		trace_info("SF: can't select read settings supported by both the SPI controller and memory.\n");
		return rc;
	}

	/* Select the Page Program command. */
	rc = spi_flash_select_pp(flash, params, shared_mask);
	if (rc < 0) {
		trace_info("SF: can't select write settings supported by both the SPI controller and memory.\n");
		return rc;
	}

	/* Enable Quad I/O if needed. */
	if ((spi_flash_protocol_get_data_nbits(flash->read_proto) == 4 ||
	     spi_flash_protocol_get_data_nbits(flash->write_proto) == 4) &&
	    params->quad_enable)
		rc = params->quad_enable(flash);

	return rc;
}

int spi_flash_read_sr(struct spi_flash *flash, uint8_t *sr)
{
	return spi_flash_read_reg(flash, SFLASH_INST_READ_SR, sr, 1);
}

int spi_flash_write_enable(struct spi_flash *flash)
{
	return spi_flash_write_reg(flash, SFLASH_INST_WRITE_ENABLE, NULL, 0);
}

int spi_flash_write_disable(struct spi_flash *flash)
{
	return spi_flash_write_reg(flash, SFLASH_INST_WRITE_DISABLE, NULL, 0);
}

int spi_flash_reset(struct spi_flash *flash)
{
	int rc;

	rc = spi_flash_write_reg(flash, SFLASH_INST_RESET_ENABLE, NULL, 0);
	return rc < 0 ? rc : spi_flash_write_reg(flash, SFLASH_INST_RESET, NULL, 0);
}

int spi_flash_wait_till_ready(struct spi_flash *flash)
{
	return spi_flash_wait_till_ready_timeout(flash, SFLASH_DEFAULT_TIMEOUT);
}

void spi_flash_set_erase_command(struct spi_flash_erase_command *cmd, size_t size, uint8_t inst)
{
	cmd->size = size;
	cmd->inst = inst;

	if (IS_POWER_OF_TWO(cmd->size))
		cmd->size_shift = fls(cmd->size) - 1;
	else
		cmd->size_shift = 0;

	cmd->size_mask = (1U << cmd->size_shift) - 1;
}

uint32_t spi_flash_div_by_erase_size(const struct spi_flash_erase_command *cmd, uint32_t dividend, uint32_t *remainder)
{
	div_t q;

	if (cmd->size_shift) {
		*remainder = dividend & cmd->size_mask;
		return dividend >> cmd->size_shift;
	}

	q = div(dividend, cmd->size);
	*remainder = q.rem;
	return q.quot;
}

void spi_flash_init_uniform_erase_map(struct spi_flash_erase_map *map, uint32_t cmd_mask, uint64_t flash_size)
{
	map->num_regions = 1;
	map->regions = &map->uniform_region;
	map->uniform_region.cmd_mask = cmd_mask;
	map->uniform_region.offset = 0;
	map->uniform_region.size = flash_size;
}

int spi_flash_exec(struct spi_flash *flash, const struct spi_flash_command *cmd)
{
	return flash->ops->exec(&flash->priv, cmd);
}

uint8_t spi_flash_protocol_get_inst_nbits(enum spi_flash_protocol proto)
{
	return ((unsigned long)(proto & SFLASH_PROTO_INST_MASK)) >>
		SFLASH_PROTO_INST_SHIFT;
}

uint8_t spi_flash_protocol_get_addr_nbits(enum spi_flash_protocol proto)
{
	return ((unsigned long)(proto & SFLASH_PROTO_ADDR_MASK)) >>
		SFLASH_PROTO_ADDR_SHIFT;
}

uint8_t spi_flash_protocol_get_data_nbits(enum spi_flash_protocol proto)
{
	return ((unsigned long)(proto & SFLASH_PROTO_DATA_MASK)) >>
		SFLASH_PROTO_DATA_SHIFT;
}

uint8_t spi_flash_get_mfr(const struct spi_flash *flash)
{
	return flash->id[0];
}

int spi_flash_init(struct spi_flash *flash)
{
	return flash->ops->init(&flash->priv);
}

int spi_flash_cleanup(struct spi_flash *flash)
{
	return flash->ops->cleanup(&flash->priv);
}

int spi_flash_set_mode(struct spi_flash *flash, uint8_t mode)
{
	return flash->ops->set_mode(&flash->priv, mode);
}

int spi_flash_set_freq(struct spi_flash *flash, uint32_t freq)
{
	return flash->ops->set_freq(&flash->priv, freq);
}

int spi_flash_read(struct spi_flash *flash, size_t from, void *buf, size_t len)
{
	return flash->read(flash, from, buf, len);
}

int spi_flash_write(struct spi_flash *flash, size_t to, const void *buf, size_t len)
{
	return flash->write(flash, to, buf, len);
}

int spi_flash_erase(struct spi_flash *flash, size_t offset, size_t len)
{
	return flash->erase(flash, offset, len);
}

bool spi_flash_has_uniform_erase(const struct spi_flash *flash)
{
	return flash->erase_map.regions == &flash->erase_map.uniform_region;
}

uint32_t spi_flash_get_uniform_erase_map(const struct spi_flash *flash)
{
	uint32_t erase_map = 0;

	if (spi_flash_has_uniform_erase(flash)) {
		int i;
		for (i = 0; i < SFLASH_CMD_ERASE_MAX; i++) {
			if (flash->erase_map.uniform_region.cmd_mask & (1u << i)) {
				erase_map |= flash->erase_map.commands[i].size / flash->page_size;
			}
		}
	}

	return erase_map;
}

void spi_flash_command_init(struct spi_flash_command *cmd, uint8_t inst, uint8_t addr_len, uint8_t flags)
{
	memset(cmd, 0, sizeof(*cmd));
	cmd->proto = SFLASH_PROTO_1_1_1;
	cmd->inst = inst;
	cmd->addr_len = addr_len;
	cmd->flags = flags;
}

#ifdef CONFIG_HAVE_AESB
void spi_flash_use_aesb(struct spi_flash* flash, bool enable)
{
	flash->use_aesb = enable;
}
#endif

int spi_flash_set_protection(struct spi_flash *flash, bool protect)
{
	if (flash->set_protection)
		return flash->set_protection(flash, protect);

	return 0;
}
