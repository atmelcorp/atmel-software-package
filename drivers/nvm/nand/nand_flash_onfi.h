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

#ifndef NAND_FLASH_ONFI_H
#define NAND_FLASH_ONFI_H

/*------------------------------------------------------------------------*/
/*                      Headers                                           */
/*------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------- */
/*         Definitions                                                    */
/*----------------------------------------------------------------------- */

/** NANDFLASH chip status response */
#define NAND_IO_RC_PASS    0
#define NAND_IO_RC_FAIL    1
#define NAND_IO_RC_TIMEOUT 2

/** Describes memory organization block information in ONFI parameter page */
struct _onfi_page_param {
	/** ONFI compatible */
	bool onfi_compatible;

	/** JEDEC manufacturer ID */
	uint8_t manuf_id;

	/** Manufacturer Name */
	char manufacturer[13];

	/** Device model */
	char device_model[21];

	/** Bus width */
	uint8_t bus_width;

	/** Number of data bytes per page. */
	uint32_t page_size;

	/** Number of spare bytes per page. */
	uint16_t spare_size;

	/** Number of pages per block. */
	uint16_t pages_per_block;

	/** Number of blocks per logical unit (LUN). */
	uint16_t blocks_per_lun;

	/** Number of logical units. */
	uint8_t logical_units;

	/** Number of bits of ECC correction */
	uint8_t ecc_correctability;
};

/*--------------------------------------------------------------------- */
/*         Exported functions                                           */
/*--------------------------------------------------------------------- */

extern bool nand_onfi_device_detect(const struct _nand_flash *nand);

extern bool nand_onfi_check_compatibility(const struct _nand_flash *nand);

extern bool nand_onfi_enable_internal_ecc(const struct _nand_flash *nand);

extern bool nand_onfi_disable_internal_ecc(const struct _nand_flash *nand);

extern bool nand_onfi_is_compatible(void);

extern uint8_t nand_onfi_get_manufacturer_id(void);

extern uint8_t nand_onfi_get_bus_width(void);

extern uint32_t nand_onfi_get_page_size(void);

extern uint16_t nand_onfi_get_spare_size(void);

extern uint16_t nand_onfi_get_pages_per_block(void);

extern uint16_t nand_onfi_get_blocks_per_lun(void);

extern uint8_t nand_onfi_get_ecc_correctability(void);

extern bool nand_onfi_get_model(struct _nand_flash_model *model);

#endif /* NAND_FLASH_ONFI_H */
