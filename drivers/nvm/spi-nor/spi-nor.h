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

#ifndef __SPI_NOR_H__
#define __SPI_NOR_H__

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "nvm/spi-nor/spi-flash.h"
#include "nvm/spi-nor/sfdp.h"
#include "peripherals/bus.h"

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define SNOR_SECT_4K		(0x1UL << 0)
#define SNOR_NO_FR		(0x1UL << 1)
#define SNOR_HAS_FSR		(0x1UL << 2)
#define SNOR_NO_4BAIS		(0x1UL << 3)
#define SNOR_SKIP_SFDP		(0x1UL << 4)
#define SNOR_SECT_4K_ONLY	(0x1UL << 5)
#define SNOR_SST_ULBPR		(0x1UL << 6)
#define SNOR_SECT_32K		(0x1UL << 7)

/*----------------------------------------------------------------------------
 *        Exported Types
 *----------------------------------------------------------------------------*/

struct spi_flash_cfg {
	enum {
		SPI_FLASH_TYPE_NONE = 0,
#ifdef CONFIG_HAVE_SPI_BUS
		SPI_FLASH_TYPE_SPI,
#endif
#ifdef CONFIG_HAVE_QSPI
		SPI_FLASH_TYPE_QSPI,
#endif
	} type;
	uint32_t baudrate;
	enum {
		SPI_FLASH_MODE0 = 0,
		SPI_FLASH_MODE1,
		SPI_FLASH_MODE2,
		SPI_FLASH_MODE3,
	} mode;
	union {
		uint32_t dummy; /* ensure that union is never empty to avoid error on IAR */
#ifdef CONFIG_HAVE_QSPI
		struct {
			Qspi* addr;
		} qspi;
#endif
#ifdef CONFIG_HAVE_SPI_BUS
		struct {
			struct _bus_dev_cfg bus_cfg;
		} spi;
#endif
	};
};

struct spi_nor_info {
	const char		*name;

	uint8_t			id[SFLASH_MAX_ID_LEN];
	uint8_t			id_len;

	uint32_t		sector_size;
	uint16_t		n_sectors;
	uint16_t		page_size;
	uint16_t		addr_len;
	uint16_t		flags;

	const struct spi_flash_parameters	*params;
};

/*----------------------------------------------------------------------------
 *        Exported Variables
 *----------------------------------------------------------------------------*/

extern const struct spi_nor_info spi_nor_ids[];

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

int spi_nor_configure(struct spi_flash *flash, const struct spi_flash_cfg *cfg);
int spi_nor_read(struct spi_flash *flash, size_t from, uint8_t* buf, size_t len);
int spi_nor_write(struct spi_flash *flash, size_t to, const uint8_t* buf, size_t len);
int spi_nor_erase(struct spi_flash *flash, size_t offset, size_t len);

int spansion_new_quad_enable(struct spi_flash *flash);
int spansion_quad_enable(struct spi_flash *flash);
int macronix_quad_enable(struct spi_flash *flash);
int sr2_bit7_quad_enable(struct spi_flash *flash);
int micron_enable_0_4_4(struct spi_flash *flash, bool enable);
int at25_set_protection(struct spi_flash *flash, bool protect);

#endif /* __SPI_NOR_H__ */
