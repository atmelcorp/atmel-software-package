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

/**
*  \file
*
*  Definitions and function prototype for nand API module
*/

#ifndef NAND_FLASH_API_H
#define NAND_FLASH_API_H

/*------------------------------------------------------------------------*/
/*                      Headers                                           */
/*------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

#include "nand_flash_common.h"
#include "nand_flash_model.h"

#include "gpio/pio.h"

/*------------------------------------------------------------------------*/
/*                      Type                                              */
/*------------------------------------------------------------------------*/

/** ECC Type */
enum {
	ECC_NO = 0,   /** No ecc, raw data only */
	ECC_PMECC,    /** Error correction with PMECC BCH algorithm */
};

/** Describes a physical NandFlash chip connected to the SAM micro-controller. */
struct _nand_flash {
	/** Model describing this NandFlash characteristics. */
	struct _nand_flash_model model;

	/** Bad block marker position */
	uint16_t badblock_marker_pos;

	/** Address for sending data to the NandFlash. */
	uint32_t data_addr;
};

/*--------------------------------------------------------------------------
*                        Export functions
*-------------------------------------------------------------------------*/

extern uint8_t nand_initialize(struct _nand_flash *nand);

extern void nand_write_command(const struct _nand_flash *nand,
		uint8_t command);

extern void nand_write_command16(const struct _nand_flash *nand,
		uint16_t command);

extern void nand_write_address(const struct _nand_flash *nand,
		uint8_t address);

extern void nand_write_address16(const struct _nand_flash *nand,
		uint16_t address);

extern void nand_write_data(const struct _nand_flash *nand,
		uint8_t data);

extern void nand_write_data16(const struct _nand_flash *nand,
		uint16_t data);

extern uint8_t nand_read_data(const struct _nand_flash *nand);

extern uint16_t nand_read_data16(const struct _nand_flash *nand);

extern void nand_set_ecc_type(uint8_t ecc_type);

extern bool nand_is_using_pmecc(void);

extern bool nand_is_using_no_ecc(void);

#ifdef CONFIG_HAVE_NFC

extern void nand_set_nfc_enabled(bool enabled);

extern bool nand_is_nfc_enabled(void);

extern void nand_set_nfc_sram_enabled(bool enabled);

extern bool nand_is_nfc_sram_enabled(void);

#endif /* CONFIG_HAVE_NFC */

extern void nand_set_dma_enabled(bool enabled);

extern bool nand_is_dma_enabled(void);

#endif /* NAND_FLASH_API_H */
