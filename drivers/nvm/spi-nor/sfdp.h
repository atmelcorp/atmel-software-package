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

#ifndef _SFDP_H
#define _SFDP_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "nvm/spi-nor/spi-flash.h"

/*----------------------------------------------------------------------------
 *        Exported Typedefs
 *----------------------------------------------------------------------------*/

struct spi_flash_read_command {
	uint8_t num_mode_cycles;
	uint8_t num_wait_states;
	uint8_t inst;
	enum spi_flash_protocol proto;
};

struct spi_flash_pp_command {
	uint8_t inst;
	enum spi_flash_protocol proto;
};

enum spi_flash_read_command_index {
	SFLASH_CMD_READ,
	SFLASH_CMD_READ_FAST,

	/* Dual SPI */
	SFLASH_CMD_READ_1_1_2,
	SFLASH_CMD_READ_1_2_2,
	SFLASH_CMD_READ_2_2_2,

	/* Quad SPI */
	SFLASH_CMD_READ_1_1_4,
	SFLASH_CMD_READ_1_4_4,
	SFLASH_CMD_READ_4_4_4,

	SFLASH_CMD_READ_MAX
};

enum spi_flash_pp_command_index {
	SFLASH_CMD_PP,

	/* Quad SPI */
	SFLASH_CMD_PP_1_1_4,
	SFLASH_CMD_PP_1_4_4,
	SFLASH_CMD_PP_4_4_4,

	SFLASH_CMD_PP_MAX
};

struct spi_flash_parameters {
	uint32_t size;
	uint32_t page_size;

	struct spi_flash_hwcaps hwcaps;
	struct spi_flash_read_command reads[SFLASH_CMD_READ_MAX];
	struct spi_flash_pp_command page_programs[SFLASH_CMD_PP_MAX];

	int (*quad_enable)(struct spi_flash *flash);
};

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

static inline void
spi_flash_set_read_settings(struct spi_flash_read_command *read,
			    uint8_t num_mode_cycles,
			    uint8_t num_wait_states,
			    uint8_t inst,
			    enum spi_flash_protocol proto)
{
	read->num_mode_cycles = num_mode_cycles;
	read->num_wait_states = num_wait_states;
	read->inst = inst;
	read->proto = proto;
}

static inline void
spi_flash_set_pp_settings(struct spi_flash_pp_command *pp, uint8_t inst, enum spi_flash_protocol proto)
{
	pp->inst = inst;
	pp->proto = proto;
}

int spi_flash_parse_sfdp(struct spi_flash *flash, struct spi_flash_parameters *params);

#endif /* _SFDP_H */
