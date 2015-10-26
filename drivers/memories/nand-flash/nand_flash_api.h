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

#include "nand_flash_common.h"

/*------------------------------------------------------------------------*/
/*                      Type                                              */
/*------------------------------------------------------------------------*/

/** ECC Type */
enum {
	ECC_NO = 0,   /** No ecc, raw data only */
	ECC_PMECC,    /** Error correction with PMECC BCH algorithm */
	ECC_SOFTWARE, /** Error correction with Hamming algorithm */
	ECC_HSIAO     /** Error correction with HSIAO (sama5d3) algorithm */
};

struct _nand_hsmc_api {
	uint8_t ecc_type;
	uint8_t nfc_enabled;
	uint8_t nfc_sram_enabled;
	uint8_t dma_enabled;
};

/*--------------------------------------------------------------------------
*                        Export functions
*-------------------------------------------------------------------------*/

extern uint8_t nand_api_use_pmecc(void);

extern uint8_t nand_api_use_software_ecc(void);

extern uint8_t nand_api_use_hasio_ecc(void);

extern uint8_t nand_api_no_ecc(void);

extern uint8_t nand_api_nfc_enabed(void);

extern uint8_t nand_api_nfc_sram_enabed(void);

extern uint8_t nand_api_dma_enabed(void);

extern void nand_api_configure(uint8_t ecc_type, uint8_t nfc_enabled,
		uint8_t nfc_sram_enabled, uint8_t dma_enabled);

extern void nand_api_configure_ecc(uint8_t ecc_type);

#endif /* NAND_FLASH_API_H */
