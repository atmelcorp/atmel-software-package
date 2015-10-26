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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <chip.h>
#include "trace.h"

#include "memories/nand-flash/nand_flash_skip_block.h"
#include "memories/nand-flash/nand_flash_common.h"
#include "memories/nand-flash/nand_flash_spare_scheme.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Casts */
#define ECC(skip_block)    ((struct _ecc_nand_flash *)skip_block)
#define RAW(skip_block)    ((struct _raw_nand_flash *)skip_block)

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Returns BADBLOCK if the given block of a NANDFLASH device is bad; returns
 * GOODBLOCK if the block is good; or returns a NandCommon_ERROR code.
 *
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of block to check.
 */

uint8_t nand_skipblock_check_block(
	const struct _skip_block_nand_flash *skip_block,
	uint16_t block)
{
	uint8_t spare[NAND_MAX_PAGE_DATA_SIZE];
	uint8_t error;
	uint8_t marker;
	const struct _nand_spare_scheme *scheme;
	/* Retrieve model scheme */
	scheme = nand_model_get_scheme(MODEL(skip_block));

	/* Read spare area of first page of block */
	error = nand_raw_read_page(RAW(skip_block), block, 0, 0, spare);
	if (error) {
		trace_error("CheckBlock: Cannot read page #0 of block #%d\n\r", block);
		return error;
	}

	nand_spare_scheme_read_bad_block_marker(scheme, spare, &marker);
	if (marker != 0xFF)
		return BADBLOCK;

	/* Read spare area of second page of block */
	error = nand_raw_read_page(RAW(skip_block), block, 1, 0, spare);
	if (error) {
		trace_error("CheckBlock: Cannot read page #1 of block #%d\n\r", block);
		return error;
	}

	nand_spare_scheme_read_bad_block_marker(scheme, spare, &marker);
	if (marker != 0xFF)
		return BADBLOCK;
	return GOODBLOCK;
}

/**
 * \brief Initializes a _skip_block_nand_flash instance. Scans the device to retrieve or
 * create block status information.
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param model  Pointer to the underlying NANDFLASH chip model. Can be 0.
 * \param command_addr  Address at which commands are sent.
 * \param address_addr  Address at which addresses are sent.
 * \param data_addr  Address at which data is sent.
 * \param pin_chip_enable  Pin controlling the CE signal of the NandFlash.
 * \param pin_ready_busy  Pin used to monitor the ready/busy signal of the NANDFLASH.
 */

uint8_t nand_skipblock_initialize(
	struct _skip_block_nand_flash *skip_block,
	const struct _nand_flash_model *model,
	uint32_t command_addr,
	uint32_t address_addr,
	uint32_t data_addr,
	const struct _pin *pin_chip_enable,
	const struct _pin *pin_ready_busy)
{
	uint8_t error;

	uint32_t num_blocks;
	uint32_t block;

	trace_debug("nand_skipblock_initialize()\n\r");

	/* Initialize SkipBlockNandFlash */
	error = nand_ecc_initialize(ECC(skip_block), model,
			command_addr, address_addr, data_addr,
			pin_chip_enable, pin_ready_busy);
	if (error)
		return error;

	/* Retrieve model information */
	num_blocks = nand_model_get_device_size_in_blocks(MODEL(skip_block));

	/* Initialize block statuses */
	trace_debug("Retrieving bad block information ...\n\r");

	/* Retrieve block status from their first page spare area */

	for (block = 0; block < num_blocks; block++) {
		/* Read spare of first page */
		error = nand_skipblock_check_block(skip_block, block);
		if (error != GOODBLOCK) {
			if (error == BADBLOCK) {
				trace_debug("Block #%d is bad\n\r",
						(unsigned int)block);
			} else {
				trace_error("nand_skipblock_initialize: Cannot retrieve info from block #%u\n\r",
						(unsigned int)block);
			}
		}
	}
	return 0;
}


/**
 * \brief Erases a block of a SkipBlock NandFlash.
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of block to erase.
 * \param erase_type Erase type: NORMAL_ERASE/SCRUB_ERASE
 * \return the nand_raw_erase_block code or NAND_ERROR_WRONGSTATUS.
*/
uint8_t nand_skipblock_erase_block(
	struct _skip_block_nand_flash *skip_block,
	uint16_t block,
	uint32_t erase_type)
{
	uint8_t error;
	const struct _nand_spare_scheme *scheme;
	uint8_t spare[NAND_MAX_PAGE_SPARE_SIZE];

	if (erase_type != SCRUB_ERASE) {
		/* Check block status */
		if (nand_skipblock_check_block(skip_block, block) != GOODBLOCK) {
			trace_info("nand_skipblock_erase_block: Block is BAD\n\r");
			return NAND_ERROR_BADBLOCK;
		}
	}

	/* Erase block */
	error = nand_raw_erase_block(RAW(skip_block), block);
	if (error) {

		/* Try to mark the block as BAD */
		trace_error("nand_skipblock_erase_block: Cannot erase block, try to mark it BAD\n\r");

		/* Retrieve model scheme */
		scheme = nand_model_get_scheme(MODEL(skip_block));

		memset(spare, 0xFF, NAND_MAX_PAGE_SPARE_SIZE);
		nand_spare_scheme_write_bad_block_marker(scheme, spare, NANDBLOCK_STATUS_BAD);
		return nand_raw_write_page(RAW(skip_block), block, 0, 0, spare);
	}

	return 0;
}

/**
 * \brief Reads the data and/or the spare area of a page on a SkipBlock nandflash. If
 * the data pointer is not 0, then the block MUST not be BAD
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param page  Number of page to read inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_read_page(
	const struct _skip_block_nand_flash *skip_block,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{

	/* Check that the block is not BAD if data is requested */
	if (nand_skipblock_check_block(skip_block, block) != GOODBLOCK) {
		trace_error("nand_skipblock_read_page: Block is BAD.\n\r");
		return NAND_ERROR_BADBLOCK;
	}
	/* Read data with ECC verification */
	return nand_ecc_read_page(ECC(skip_block), block, page, data, spare);
}

/**
 * \brief Reads the data of a whole block on a SkipBlock nandflash.
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param data  Data area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_read_block(
	const struct _skip_block_nand_flash *skip_block,
	uint16_t block,
	void *data)
{
	/* Number of pages per block */
	uint32_t num_pages_per_block, page_size;
	/* Page index */
	uint16_t i;
	/* Error returned by nand_skipblock_write_page */
	uint8_t error = 0;

	/* Retrieve model information */
	page_size = nand_model_get_page_data_size(MODEL(skip_block));
	num_pages_per_block = nand_model_get_block_size_in_pages(MODEL(skip_block));

	/* Check that the block is not BAD if data is requested */
	if (nand_skipblock_check_block(skip_block, block) != GOODBLOCK) {

		trace_error("nand_skipblock_read_block: Block is BAD.\n\r");
		return NAND_ERROR_BADBLOCK;
	}

	/* Read all the pages of the block */
	for (i = 0; i < num_pages_per_block; i++) {
		error = nand_ecc_read_page(ECC(skip_block), block, i, data, 0);
		if (error) {
			trace_error("nand_skipblock_read_block: Cannot read page %d of block %d.\n\r", i, block);
			return error;
		}
		data = (void *) ((uint8_t *) data + page_size);
	}

	return 0;
}

/**
 * \brief Writes the data and/or spare area of a page on a SkipBlock NandFlash.
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of the block to write.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return NAND_ERROR_BADBLOCK if the page is BAD; otherwise,
 * returns nand_ecc_write_page().
 */

uint8_t nand_skipblock_write_page(
	const struct _skip_block_nand_flash *skip_block,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	/* Check that the block is LIVE */
	if (nand_skipblock_check_block(skip_block, block) != GOODBLOCK) {
		trace_error("nand_skipblock_write_page: Block is BAD.\n\r");
		return NAND_ERROR_BADBLOCK;
	}

	/* Write data with ECC calculation */
	return nand_ecc_write_page(ECC(skip_block), block, page, data, spare);
}

/**
 * \brief Writes the data of a whole block on a SkipBlock NANDFLASH.
 * \param skip_block  Pointer to a _skip_block_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param data  Data area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_write_block(
	const struct _skip_block_nand_flash *skip_block,
	uint16_t block,
	void *data)
{
	/* Number of pages per block */
	uint32_t num_pages_per_block;
	/* Page size */
	uint32_t page_size;
	/* Page index */
	uint16_t i;
	/* Error returned by nand_skipblock_write_page */
	uint8_t error = 0;

	/* Retrieve model information */
	page_size = nand_model_get_page_data_size(MODEL(skip_block));
	num_pages_per_block = nand_model_get_block_size_in_pages(MODEL(skip_block));

	/* Check that the block is LIVE */
	if (nand_skipblock_check_block(skip_block, block) != GOODBLOCK) {
		trace_error("nand_skipblock_write_block: Block is BAD.\n\r");
		return NAND_ERROR_BADBLOCK;
	}

	for (i = 0; i < num_pages_per_block; i++) {
		error = nand_ecc_write_page(ECC(skip_block), block, i, data, 0);
		if (error) {
			trace_error("nand_skipblock_write_block: Cannot write page %d of block %d.\n\r", i, block);
			return NAND_ERROR_CANNOTWRITE;
		}
		data = (void *) ((uint8_t *) data + page_size);
	}

	return 0;
}

