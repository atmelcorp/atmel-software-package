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
 * \page smc_nandflash_slc SMC NAND Flash SLC Example
 *
 * \section Purpose
 *
 * This basic nandflash example shall show how to read and write data from/to
 * a nandflash connected to the SMC, taking ECC and Bad Block marking into account.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2.
 *
 * \section Description
 *
 * The required steps are:
 * <ul>
 * <li> Configure the SMC to interface with the NAND Flash. </li>
 * <li> Measure throughtput for RAW data write/read with or without DMA
 * enabled </li>
 * <li> Measure throughtput for write/read with or without DMA enabled
 * using PMECC </li>
 * </ul>
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- SMC NandFlash SLC Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     =========================================================
 *     Menu: press a key to select test mode.
 *     ---------------------------------------------------------
 *     - r: Raw data
 *     - p: PMECC
 *     - c: Display current configuration
 *     - m: Display this menu
 *    \endcode
 *
 * \section References
 * - smc_nandflash/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for smc_nand_slc example.
 */

/*-------------------------------------------------------------------------
 *        Headers
 *------------------------------------------------------------------------*/

#include <board.h>

#include "board.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"

#include "nvm/nand/pmecc.h"
#include "nvm/nand/nand_flash.h"
#include "nvm/nand/nand_flash_skip_block.h"
#include "nvm/nand/nand_flash_model_list.h"
#include "nvm/nand/nand_flash_model.h"
#include "nvm/nand/nand_flash_ecc.h"
#include "nvm/nand/nand_flash_onfi.h"
#include "nvm/nand/nand_flash_dma.h"
#include "nvm/nand/nand_flash_raw.h"

#include "serial/console.h"
#include "mm/cache.h"
#include "led/led.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*-------------------------------------------------------------------------
 *         Definition
 *------------------------------------------------------------------------*/

#define PATTERN_SIZE        32

enum {
	CONF_DMA,
#ifdef CONFIG_HAVE_NFC
	CONF_NFC,
	CONF_NFC_SRAM,
#endif /* CONFIG_HAVE_NFC */
};

/*-------------------------------------------------------------------------
 *         Local variables
 *------------------------------------------------------------------------*/

/** Size of the data area of in the nandflash, in bytes.*/
static uint32_t page_size;

/** Size of the spare area of in the nandflash, in bytes.*/
static uint32_t spare_size;

/** Nandflash device structure.*/
static struct _nand_flash nand;

/** Nandflash device structure. */
static struct _nand_flash_model model_from_onfi;

static uint8_t ecc_type = ECC_PMECC;
static bool dma_enabled = false;
#ifdef CONFIG_HAVE_NFC
static bool nfc_enabled = false;
static bool nfc_sram_enabled = false;
#endif /* CONFIG_HAVE_NFC */

/** Number of bits of ECC correction */
static uint8_t onfi_ecc_correctability = 0xFF;

static uint8_t sector_idx = 0;
static uint32_t sector_size = 512;
static uint8_t correctability;
static uint16_t block;
static uint16_t page;

/** pattern buffer */
static uint8_t pattern_buffer[NAND_MAX_PAGE_DATA_SIZE];

/** page buffer */
CACHE_ALIGNED_DDR static uint8_t page_buffer[NAND_MAX_PAGE_DATA_SIZE + NAND_MAX_PAGE_SPARE_SIZE];

/** spare buffer */
CACHE_ALIGNED_DDR static uint8_t spare_buffer[NAND_MAX_PAGE_SPARE_SIZE];

/** pattern buffer */
const uint8_t pattern[PATTERN_SIZE] = {
	0x01, 0x2c, 0x00, 0xed, 0xfc, 0xdb, 0x00, 0x43,
	0xa0, 0x22, 0x4e, 0x02, 0x33, 0x01, 0x05, 0x08,
	0xb4, 0xce, 0x0c, 0x91, 0xd7, 0x84, 0xbb, 0x71,
	0x93, 0x18, 0x06, 0x06, 0x07, 0x06, 0x53, 0x5d
};

/*-------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------*/

/**
 * \brief Dump current software configuration for SMC.
 */
static void _dump_smc_configuration(void)
{
	printf("SMC software configuration :\n\r");
	printf("------\n\r");

	if (ecc_type == ECC_NO)
		printf("-I- ECC is disabled.\n\r");
	else if (ecc_type == ECC_PMECC)
		printf("-I- PMECC is enabled.\n\r");

	if (dma_enabled)
		printf("-I- DMA is enabled,the DATA phase of the " \
				"transfer can be DMA-assisted.\n\r");
	else
		printf("-I- DMA is disabled.\n\r");

#ifdef CONFIG_HAVE_NFC
	if (nfc_enabled)
		printf("-I- SMC NFC is enabled, NFC handles cmd, " \
				"address and data sequences.\n\r");
	else
		printf("-I- SMC NFC is disabled, EBI handles cmd, " \
				"address and data sequences.\n\r");

	if (nfc_sram_enabled)
		printf("-I SMC NFC Host SRAM is enabled, An SRAM is " \
				"used as an internal read/write buffer "
				"when data is transferred.\n\r");
	else
		printf("-I- SMC NFC Host SRAM is disabled.\n\r");
#endif /* CONFIG_HAVE_NFC */
}

/**
 * \brief SMC software configuration.
 * \prarm mode Mode to be configured.
 */
static void _smc_configure(uint8_t mode)
{
	switch (mode) {
	case CONF_DMA:
		if (dma_enabled == true)
			dma_enabled = false;
		else
			dma_enabled = true;
#ifdef CONFIG_SOC_SAMA5D3
		if (dma_enabled) {
			printf("-W- DMA cannot be used with NFC SRAM on SAMA5D3, disabling NFC SRAM.\r\n");
			nfc_sram_enabled = false;
		}
#endif
		break;

#ifdef CONFIG_HAVE_NFC
	case CONF_NFC:
		if (nfc_enabled == true) {
			nfc_enabled = false;
			nfc_sram_enabled = false;
		} else {
			nfc_enabled = true;
		}
		break;

	case CONF_NFC_SRAM:
		if (nfc_enabled == true) {
			if (nfc_sram_enabled == true)
				nfc_sram_enabled = false;
			else
				nfc_sram_enabled = true;
		}
#ifdef CONFIG_SOC_SAMA5D3
		if (nfc_sram_enabled) {
			printf("-W- NFC SRAM cannot be used with DMA on SAMA5D3, disabling DMA.\r\n");
			dma_enabled = false;
		}
#endif
		break;
#endif /* CONFIG_HAVE_NFC */
	}

	nand_set_ecc_type(ecc_type);
	nand_set_dma_enabled(dma_enabled);
#ifdef CONFIG_HAVE_NFC
	nand_set_nfc_enabled(nfc_enabled);
	nand_set_nfc_sram_enabled(nfc_sram_enabled);
#endif /* CONFIG_HAVE_NFC */
}

/**
 * \brief Access Nand flash page.
 */
static void _page_access(void)
{
	if (ecc_type == ECC_PMECC) {
		pmecc_initialize(sector_idx, correctability,
				page_size, spare_size, 0, 0);
	}

	printf("-I- Erase block\n\r");
	nand_skipblock_erase_block(&nand, block, SCRUB_ERASE);

	printf("-I- Write block\n\r");
	memcpy(page_buffer, pattern_buffer, page_size);
	nand_skipblock_write_page(&nand, block, page, page_buffer, 0);

	printf("-I- Read block\n\r");
	memset(page_buffer, 0, page_size);
	nand_skipblock_read_page(&nand, block, page, page_buffer, 0);

	/* Test if the read contains expected data */
	if (memcmp(pattern_buffer, page_buffer, page_size)) {
		printf("-I- Read data is different from buffer, test failed\n\r");
	} else {
		printf("-I- Read data matches buffer.\n\r");
	}
}

/**
 * \brief Generate some error bit for error correction.
 */
static void _simulate_error_bits(uint8_t *buffer)
{
	uint32_t sectors, byte_pos, i, j;
	uint8_t tmp, bit_pos;

	sectors = page_size / sector_size;

	for (i = 0; i < sectors; i++) {
		for (j = 0; j < correctability; j++) {
			byte_pos = i * sector_size + j * (sector_size / correctability);
			bit_pos = (i * 32 + j) % 8;
			tmp = buffer[byte_pos];

			/* Inverse Bit  */
			buffer[byte_pos] = tmp ^ ((uint8_t)(1 << bit_pos));
			printf("Generate error  <%x,%x > %u, @[#Sector %u,#Byte %u,Bit# %u]\n\r",
				  (unsigned)tmp, buffer[byte_pos],
				  (unsigned)byte_pos, (unsigned)i,
				  (unsigned)(byte_pos % sector_size),
				  (unsigned)bit_pos);
		}
	}
}

/**
 * \brief Write Nand flash page with simulated error bits.
 */
static void _write_page_with_simulated_error_bits(void)
{
	nand_set_ecc_type(ECC_PMECC);
	pmecc_initialize(sector_idx, correctability,
			page_size, spare_size, 0, 0);

	printf("-I- Erase block %d\n\r", block);
	nand_skipblock_erase_block(&nand, block, SCRUB_ERASE);

	printf("-I- Write a page of data, ECC values will be generated\n\r");
	memcpy(page_buffer, pattern_buffer, page_size);
	nand_skipblock_write_page(&nand, block,
			page, page_buffer, 0);

	printf("-I- Read spare area which contains ECC values\n\r");
	pmecc_disable();
	nand_set_ecc_type(ECC_NO);
	nand_raw_read_page(&nand, block, page, 0, spare_buffer);

	printf("-I- Erase page\n\r");
	nand_skipblock_erase_block(&nand, block, SCRUB_ERASE);

	printf("-I- Write a page of data with injected errors and previously computed ECC values\n\r");
	_simulate_error_bits(page_buffer);
	nand_raw_write_page(&nand, block, page, page_buffer, spare_buffer);
}

/**
 * \brief Read Nand flash page to correct simulated error bits.
 */
static void _read_page_with_simulated_error_bits(void)
{
	nand_set_ecc_type(ECC_PMECC);
	pmecc_initialize(sector_idx, correctability,
			page_size, spare_size, 0, 0);

	printf("-I- Read page of data with ECC enabled\n\r");
	memset(page_buffer, 0, page_size);
	nand_skipblock_read_page(&nand, block,
			page, page_buffer, 0);

	/* Test if the read contains expected data */
	if (memcmp(pattern_buffer, page_buffer, page_size)) {
		printf("-I- Read data is different from buffer, test failed.\n\r");
	} else {
		printf("-I- Read data matches buffer.\n\r");
	}
}

/**
 * \brief Check is the pmecc parameter header is valid
  \return true if the pmecc parameter header is valid; otherwise returns false
 */
static bool is_valid_pmecc_param(void)
{
	uint32_t mm, ecc_size_bytes, sector_size_per_page;

	if (correctability < onfi_ecc_correctability
			&& onfi_ecc_correctability != 0xff) {
		printf("-W- Number of bits of ECC correction <%d> " \
				"do not satisfy ONFI ECC correctability <%d>",
				correctability, onfi_ecc_correctability);
		printf("This leads to an unpredictable behavior of the " \
				"ECC correction\n\r");
	}

	sector_size_per_page = page_size / sector_size;
	if (sector_size_per_page > 8)
		return false;

	mm = sector_idx == 0 ? 13 : 14;
	if (((mm * correctability) % 8) == 0) {
		ecc_size_bytes = ((mm * correctability) / 8) * sector_size_per_page;
	} else {
		ecc_size_bytes = (((mm * correctability) / 8) + 1) * sector_size_per_page;
	}

	if (ecc_size_bytes > (spare_size - 2))
		return false;

	return true;
}

/**
 * \brief Configure pmecc parameter
  \param mode 0-9 mode
 */
static uint32_t _configure_correction(uint8_t mode)
{
	if (mode < 5) {
		sector_idx = 0;
		sector_size = 512;
	} else {
		sector_idx = 1;
		sector_size = 1024;
	}

	switch (mode) {
	case 0:
		correctability = 2;
		printf("-I- 512 bytes per sector, 2 errors per sector\n\r");
		break;
	case 1:
		correctability = 4;
		printf("-I- 512 bytes per sector, 4 errors per sector\n\r");
		break;
	case 2:
		correctability = 8;
		printf("-I- 512 bytes per sector, 8 errors per sector\n\r");
		break;
	case 3:
		correctability = 12;
		printf("-I- 512 bytes per sector, 12 errors per sector\n\r");
		break;
	case 4:
		correctability = 24;
		printf("-I- 512 bytes per sector, 24 errors per sector\n\r");
		break;
	case 5:
		correctability = 2;
		printf("-I- 1024 bytes per sector, 2 errors per sector\n\r");
		break;
	case 6:
		correctability = 4;
		printf("-I- 1024 bytes per sector, 4 errors per sector\n\r");
		break;
	case 7:
		correctability = 8;
		printf("-I- 1024 bytes per sector, 8 errors per sector\n\r");
		break;
	case 8:
		correctability = 12;
		printf("-I- 1024 bytes per sector, 12 errors per sector\n\r");
		break;
	case 9:
		correctability = 24;
		printf("-I- 1024 bytes per sector, 24 errors per sector\n\r");
		break;
	case 10:
		correctability = 32;
		printf("-I- 1024 bytes per sector, 32 errors per sector\n\r");
		break;
	}

	if (!is_valid_pmecc_param()) {
		printf ("-E- Invalid configuration for pagesize %u, sparesize %u\n\r",
				(unsigned)page_size, (unsigned)spare_size);
		return 0;
	}

	return 1;
}

/**
 * \brief Display menu.
 */
static void _display_menu(uint8_t menu_idx)
{
	uint8_t x;

	if (menu_idx == 0) {
		printf("\n\r");
		printf("=========================================================\n\r");
		printf("Menu: press a key to select test mode.\n\r");
		printf("---------------------------------------------------------\n\r");
		printf(" r: Raw data \n\r");
		printf(" p: PMECC\n\r");
		printf(" c: Display current configuration\n\r");
		printf(" m: Display menu\n\r");
		printf("=========================================================\n\r\n\r");
		return;
	}

	printf(" --- NAND Configuration\n\r");

	x = dma_enabled ? 'X' : ' ';
	printf("[%c] d: DMA\n\r", x);

#ifdef CONFIG_HAVE_NFC
	x = nfc_enabled ? 'X' : ' ';
	printf("[%c] n: NFC \n\r", x);

	x = nfc_sram_enabled ? 'X' : ' ';
	printf("[%c] h: NFC host sram\n\r", x);
#endif /* CONFIG_HAVE_NFC */

	printf("\n\r");
	if (menu_idx == 1) {
		printf("Access NAND flash with raw data only:\n\r");
		printf("------\n\r");
	} else if (menu_idx == 2) {
		printf("PMECC Menu:\n\r");
		printf("------\n\r");
		printf(" 0-9: Configure correction parameter\n\r");
		printf("    0:  512 bytes per sector,    2 errors per sector\n\r");
		printf("    1:  512 bytes per sector,    4 errors per sector\n\r");
		printf("    2:  512 bytes per sector,    8 errors per sector\n\r");
		printf("    3:  512 bytes per sector,   12 errors per sector\n\r");
		printf("    4:  512 bytes per sector,   24 errors per sector\n\r");
		printf("    -------------------------------------------------\n\r");
		printf("    5: 1024 bytes per sector,    2 errors per sector\n\r");
		printf("    6: 1024 bytes per sector,    4 errors per sector\n\r");
		printf("    7: 1024 bytes per sector,    8 errors per sector\n\r");
		printf("    8: 1024 bytes per sector,   12 errors per sector\n\r");
		printf("    9: 1024 bytes per sector,   24 errors per sector\n\r");
		printf("    a: 1024 bytes per sector,   32 errors per sector\n\r");
	}


	printf(" p: Erase/Write/Read\n\r");

	if (menu_idx == 2) {
		printf(" w: Write page with simulated error bit(s)\n\r");
		printf(" r: Read page to correct simulated error bit(s)\n\r");
	}

	printf(" c: Display current configuration\n\r");
	printf(" m: Display menu\n\r");
	printf(" b: Back to main menu\n\r");
}

/**
 * \brief Test Pmecc.
 */
static void _loop_pmecc(void)
{
	uint8_t key;

	ecc_type = ECC_PMECC;
	nand_set_ecc_type(ecc_type);
	_configure_correction(1);

	for (;;) {
		key = console_get_char();
		switch (key) {
		case 'd':
		case 'D':
			_smc_configure(CONF_DMA);
			_display_menu(3);
			break;
#ifdef CONFIG_HAVE_NFC
		case 'n':
		case 'N':
			_smc_configure(CONF_NFC);
			_display_menu(3);
			break;
		case 'h':
		case 'H':
			_smc_configure(CONF_NFC_SRAM);
			_display_menu(3);
			break;
#endif /* CONFIG_HAVE_NFC */
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			/* Config correction parameter. */
			if (_configure_correction((key - '0')))
				printf("-I- Press 'w' to write page with simulated %d error bits per sector\n\r",
						correctability);
			break;
		case 'a':
		case 'A':
			if (_configure_correction(10))
				printf("-I- Press 'w' to write page with simulated %d error bits per sector\n\r",
						correctability);
			break;
		case 'p':
		case 'P':
			_page_access();
			printf("\n\r");
			break;
		case 'w':
		case 'W':
			_write_page_with_simulated_error_bits();
			printf("\n\r-I- Press 'r' to read page to correct simulated error bit(s)\n\r");
			break;
		case 'r':
		case 'R':
			_read_page_with_simulated_error_bits();
			break;
		case 'c':
		case 'C':
			_dump_smc_configuration();
			break;
		case 'm':
		case 'M':
			_display_menu(3);
			break;
		case 'b':
		case 'B':
			_display_menu(0);
			return;
		}
	}
}

/**
 * \brief Test NAND flash with RAW data.
 */
static void _loop_raw(void)
{
	uint8_t key;

	ecc_type = ECC_NO;
	nand_set_ecc_type(ecc_type);

	PMECC->PMECC_CTRL = PMECC_CTRL_RST;
	PMECC->PMECC_CTRL = PMECC_CTRL_DISABLE;
	PMECC->PMECC_CFG = 0;

	for (;;) {
		key = console_get_char();
		switch (key) {
		case 'd':
		case 'D':
			_smc_configure(CONF_DMA);
			_display_menu(1);
			break;
#ifdef CONFIG_HAVE_NFC
		case 'n':
		case 'N':
			_smc_configure(CONF_NFC);
			_display_menu(1);
			break;
		case 'h':
		case 'H':
			_smc_configure(CONF_NFC_SRAM);
			_display_menu(1);
			break;
#endif /* CONFIG_HAVE_NFC */
		case 'p':
		case 'P':
			_page_access();
			break;
		case 'c':
		case 'C':
			_dump_smc_configuration();
			break;
		case 'm':
		case 'M':
			_display_menu(1);
			break;
		case 'b':
		case 'B':
			_display_menu(0);
			return;
		}
	}
}

/**
 * \brief Access NAND flash through SMC.
 */
static void _loop_main(void)
{
	uint8_t key;

	for (;;) {
		key = console_get_char();
		switch (key) {
		case 'r':
		case 'R':
			_display_menu(1);
			_loop_raw();
			break;
		case 'p':
		case 'P':
			_display_menu(2);
			_loop_pmecc();
			break;
		case 'c':
		case 'C':
			_dump_smc_configuration();
			break;
		case 'm':
		case 'M':
			_display_menu(0);
			break;
		}
	}
}

/*-------------------------------------------------------------------------
 *         Global functions
 *-----------------------------------------------------------------------*/

 /**
 * \brief Application entry point for test pmecc example.
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i, j;
	bool onficompatible = false;

	/* Output example information */
	console_example_info("SMC NandFlash SLC Example");

	/* Configure SMC for Nandflash accesses */
	nand_dma_configure();
	nand_initialize(&nand);

	if (!nand_onfi_device_detect(&nand)) {
		printf("\tDevice Unknown\n\r");
		while (1);
	}

	if (nand_onfi_check_compatibility(&nand)) {
		printf("\tOpen NAND Flash Interface (ONFI)-compliant\n\r");
		nand_onfi_disable_internal_ecc(&nand);
		nand_onfi_get_model(&model_from_onfi);
		onfi_ecc_correctability = nand_onfi_get_ecc_correctability();
		onfi_ecc_correctability = 0xFF ? 2 : onfi_ecc_correctability;
		onficompatible = true;
	}

	if (nand_raw_initialize(&nand, onficompatible ? &model_from_onfi : NULL)) {
		printf("-E- Device Unknown\n\r");
		return 0;
	}

	/* Get device parameters */
	page_size = nand_model_get_page_data_size(&nand.model);
	spare_size = nand_model_get_page_spare_size(&nand.model);

	ecc_type = 0;
	dma_enabled = false;
#ifdef CONFIG_HAVE_NFC
	nfc_enabled = false;
	nfc_sram_enabled = false;
#endif /* CONFIG_HAVE_NFC */
	sector_idx = 0;

	printf("-I- Size of the data area of a page in bytes: 0x%x\n\r",
			(unsigned)page_size);

	block = 3;
	page = 0;
	/* Generate page of pattern data to be test */
	for (i = 0; i < page_size / PATTERN_SIZE; i++) {
		for (j = 0; j < PATTERN_SIZE; j++)
			pattern_buffer[i * PATTERN_SIZE + j] =
				(((pattern[j] + i) % 0xff));
	}

	/* setup using current configuration */
	_smc_configure(-1);

	/* Display menu */
	_display_menu(0);

	/* Enter test mode */
	_loop_main();
	return 0;
}

/** \endcond */
