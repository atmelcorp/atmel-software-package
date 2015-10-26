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

/** \file */

/*--------------------------------------------------------------------- */
/*         Headers                                                      */
/*--------------------------------------------------------------------- */

#include "peripherals/hsmc.h"

#include "nand_flash_api.h"

/*--------------------------------------------------------------------- */
/*                      Global variables                                */
/*--------------------------------------------------------------------- */

static struct _nand_hsmc_api nand_api;

/*-------------------------------------------------------------------- */
/*                      Global functions                               */
/*---------------------------------------------------------------------*/

/**
 * \brief Configure NAND API parameter.
 */

void nand_api_configure(
						uint8_t ecc_type,
						uint8_t nfc_enabled,
						uint8_t nfc_sram_enabled,
						uint8_t dma_enabled)
{
	nand_api.ecc_type = ecc_type;
	nand_api.nfc_enabled = nfc_enabled;
	nand_api.nfc_sram_enabled = nfc_sram_enabled;
	nand_api.dma_enabled = dma_enabled;
	if (nand_api.nfc_enabled == true)
		hsmc_nfc_enable()
	else
		hsmc_nfc_disable()
}

/**
 * \brief Set API ECC type.
 */
void nand_api_configure_ecc(uint8_t ecc_type)
{
	nand_api.ecc_type = ecc_type;
}

/**
 * \brief Return turn if NAND API work with pmecc enabled.
 */
uint8_t nand_api_use_pmecc(void)
{
	return (nand_api.ecc_type == ECC_PMECC);
}

/**
 * \brief Return turn if NAND API work with software enabled.
 */
uint8_t nand_api_use_software_ecc(void)
{
	return (nand_api.ecc_type == ECC_SOFTWARE);
}

/**
 * \brief Return turn if NAND API work with ECC_HSIAO enabled.
 */
uint8_t nand_api_use_hasio_ecc(void)
{
	return (nand_api.ecc_type == ECC_HSIAO);
}

/**
 * \brief Return turn if NAND API work without ECC enabled.
 */
uint8_t nand_api_no_ecc(void)
{
	return (nand_api.ecc_type == ECC_NO);
}

/**
 * \brief Return turn if NAND API work with NFC enabled.
 */
uint8_t nand_api_nfc_enabed(void)
{
	return (nand_api.nfc_enabled == true);
}

/**
 * \brief Return turn if NAND API work with NFC/SRAM enabled.
 */
uint8_t nand_api_nfc_sram_enabed(void)
{
	return (nand_api.nfc_sram_enabled == true);
}

/**
 * \brief Return turn if NAND API work with DMA enabled.
 */
uint8_t nand_api_dma_enabed(void)
{
	return (nand_api.dma_enabled == true);
}
