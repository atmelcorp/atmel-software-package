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

#include "chip.h"
#include "trace.h"

#include "nvm/nand/nfc.h"
#include "extram/smc.h"

#include "nand_flash.h"

#include <string.h>

/*-------------------------------------------------------------------- */
/*                     Local types                                     */
/*-------------------------------------------------------------------- */

struct _nand_cfg {
	uint8_t ecc_type;
	bool nfc_enabled;
	bool nfc_sram_enabled;
	bool dma_enabled;
};

/*-------------------------------------------------------------------- */
/*                     Local variables                                 */
/*-------------------------------------------------------------------- */

static struct _nand_cfg nand_cfg;

/*-------------------------------------------------------------------- */
/*                     Global functions                                */
/*---------------------------------------------------------------------*/

/**
 * \brief Initializes a _nand_flash instance based on the given physicalinterface.
 * \param nand  Pointer to a _nand_flash instance.
 * \returns 0 if initialization is successful; otherwise returns non-zero
 */
uint8_t nand_initialize(struct _nand_flash *nand)
{
	/* Initialize fields */
	nand->data_addr = get_ebi_addr_from_cs(NAND_EBI_CS);
	if (!nand->data_addr) {
		trace_warning("Cound not determine EBI address for CS%u\r\n",
				NAND_EBI_CS);
		return NAND_ERROR_INVALID_ARG;
	}

	memset(&nand->model, 0, sizeof(nand->model));
	return 0;
}

void nand_write_command(const struct _nand_flash *nand, uint8_t command)
{
	/** address for transferring command bytes to the NANDFLASH, CLE A22 */
	uint32_t command_addr = nand->data_addr | 0x400000;
	*((volatile uint8_t*)command_addr) = (uint8_t)command;
}

void nand_write_command16(const struct _nand_flash *nand,
		uint16_t command)
{
	/** address for transferring command bytes to the NANDFLASH, CLE A22 */
	uint32_t command_addr = nand->data_addr | 0x400000;
	*((volatile uint16_t*)command_addr) = (uint16_t)command;
}

void nand_write_address(const struct _nand_flash *nand, uint8_t address)
{
	/** address for transferring address bytes to the NANDFLASH, ALE A21 */
	uint32_t address_addr = nand->data_addr | 0x200000;
	*((volatile uint8_t*)address_addr) = (uint8_t)address;
}

void nand_write_address16(const struct _nand_flash *nand,
		uint16_t address)
{
	/** address for transferring address bytes to the NANDFLASH, ALE A21 */
	uint32_t address_addr = nand->data_addr | 0x200000;
	*((volatile uint16_t*)address_addr) = (uint16_t)address;
}

void nand_write_data(const struct _nand_flash *nand, uint8_t data)
{
	*((volatile uint8_t*)nand->data_addr) = (uint8_t)data;
}

void nand_write_data16(const struct _nand_flash *nand, uint16_t data)
{
	*((volatile uint16_t*)nand->data_addr) = (uint16_t)data;
}

uint8_t nand_read_data(const struct _nand_flash *nand)
{
	return *((volatile uint8_t*)nand->data_addr);
}

uint16_t nand_read_data16(const struct _nand_flash *nand)
{
	return *((volatile uint16_t*)nand->data_addr);
}

/**
 * \brief Set ECC type.
 */
void nand_set_ecc_type(uint8_t ecc_type)
{
	nand_cfg.ecc_type = ecc_type;
}

/**
 * \brief Return true if NAND work with pmecc enabled.
 */
bool nand_is_using_pmecc(void)
{
	return nand_cfg.ecc_type == ECC_PMECC;
}

/**
 * \brief Return true if NAND work without ECC enabled.
 */
bool nand_is_using_no_ecc(void)
{
	return nand_cfg.ecc_type == ECC_NO;
}

#ifdef CONFIG_HAVE_NFC

/**
 * \brief Enable or Disable use of NFC
 */
void nand_set_nfc_enabled(bool enabled)
{
	nand_cfg.nfc_enabled = enabled;

	if (nand_cfg.nfc_enabled)
		nfc_enable();
	else
		nfc_disable();
}

/**
 * \brief Return true if NAND work with NFC enabled.
 */
bool nand_is_nfc_enabled(void)
{
	return nand_cfg.nfc_enabled;
}

/**
 * \brief Enable or Disable use of NFC SRAM
 */
void nand_set_nfc_sram_enabled(bool enabled)
{
	if (enabled && !nand_cfg.nfc_enabled) {
		trace_warning("Cannot enable NFC SRAM because NFC is disabled\r\n");
		return;
	}

	nand_cfg.nfc_sram_enabled = enabled;
}

/**
 * \brief Return true if NAND work with NFC/SRAM enabled.
 */
bool nand_is_nfc_sram_enabled(void)
{
	return nand_cfg.nfc_sram_enabled;
}

#endif /* CONFIG_HAVE_NFC */

/**
 * \brief Enable or Disable use of DMA
 */
void nand_set_dma_enabled(bool enabled)
{
	nand_cfg.dma_enabled = enabled;
}

/**
 * \brief Return if NAND API work with DMA enabled.
 */
bool nand_is_dma_enabled(void)
{
	return nand_cfg.dma_enabled;
}
