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

#include "chip.h"
#include "trace.h"

#include "nand_flash_skip_block.h"
#include "nand_flash_raw.h"
#include "nand_flash_ecc.h"
#include "mm/cache.h"

#include <string.h>


/*---------------------------------------------------------------------- */
/*         Local variables                                               */
/*---------------------------------------------------------------------- */

CACHE_ALIGNED static uint8_t spare_buf[NAND_MAX_PAGE_SPARE_SIZE];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Returns BADBLOCK if the given block of a NANDFLASH device is bad; returns
 * GOODBLOCK if the block is good; or returns a NandCommon_ERROR code.
 *
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of block to check.
 */

uint8_t nand_skipblock_check_block(const struct _nand_flash *nand,
		uint16_t block)
{
	uint8_t error;
	uint8_t marker;

	/* Read spare area of first page of block */
	error = nand_raw_read_page(nand, block, 0, NULL, spare_buf);
	if (error) {
		trace_error("nand_skipblock_check_block: "
				"Cannot read page #0 of block #%d\r\n", block);
		return error;
	}
	marker = spare_buf[nand->badblock_marker_pos];
	if (marker != 0xff)
		return BADBLOCK;

	/* Read spare area of second page of block */
	error = nand_raw_read_page(nand, block, 1, NULL, spare_buf);
	if (error) {
		trace_error("nand_skipblock_check_block: "
				"Cannot read page #1 of block #%d\r\n", block);
		return error;
	}
	marker = spare_buf[nand->badblock_marker_pos];
	if (marker != 0xff)
		return BADBLOCK;

	return GOODBLOCK;
}

/**
 * \brief Erases a block of a SkipBlock NandFlash.
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of block to erase.
 * \param erase_type Erase type: NORMAL_ERASE/SCRUB_ERASE
 * \return the nand_raw_erase_block code or NAND_ERROR_WRONGSTATUS.
*/
uint8_t nand_skipblock_erase_block(struct _nand_flash *nand,
		uint16_t block, uint32_t erase_type)
{
	uint8_t error;

	if (erase_type != SCRUB_ERASE) {
		/* Check block status */
		if (nand_skipblock_check_block(nand, block) != GOODBLOCK) {
			trace_info("nand_skipblock_erase_block: Block is BAD\r\n");
			return NAND_ERROR_BADBLOCK;
		}
	}

	/* Erase block */
	error = nand_raw_erase_block(nand, block);
	if (error) {
		/* Try to mark the block as BAD */
		trace_error("nand_skipblock_erase_block: Cannot erase block, try to mark it BAD\r\n");

		memset(spare_buf, 0xff, sizeof(spare_buf));
		spare_buf[nand->badblock_marker_pos] = NANDBLOCK_STATUS_BAD;
		return nand_raw_write_page(nand, block, 0, 0, spare_buf);
	}

	return 0;
}

/**
 * \brief Reads the data and/or the spare area of a page on a SkipBlock nandflash. If
 * the data pointer is not 0, then the block MUST not be BAD
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param page  Number of page to read inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_read_page(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, void *data, void *spare)
{
	/* Check that the block is not BAD if data is requested */
	if (nand_skipblock_check_block(nand, block) != GOODBLOCK) {
		trace_error("nand_skipblock_read_page: Block is BAD.\r\n");
		return NAND_ERROR_BADBLOCK;
	}

	/* Read data with ECC verification */
	return nand_ecc_read_page(nand, block, page, data, spare);
}

/**
 * \brief Reads the data of a whole block on a SkipBlock nandflash.
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param data  Data area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_read_block(const struct _nand_flash *nand,
	uint16_t block, void *data)
{
	uint32_t num_pages_per_block, page_size;
	uint16_t i;
	uint8_t error = 0;

	/* Retrieve model information */
	page_size = nand_model_get_page_data_size(&nand->model);
	num_pages_per_block = nand_model_get_block_size_in_pages(&nand->model);

	/* Check that the block is not BAD if data is requested */
	if (nand_skipblock_check_block(nand, block) != GOODBLOCK) {

		trace_error("nand_skipblock_read_block: Block is BAD.\r\n");
		return NAND_ERROR_BADBLOCK;
	}

	/* Read all the pages of the block */
	for (i = 0; i < num_pages_per_block; i++) {
		error = nand_ecc_read_page(nand, block, i, data, 0);
		if (error) {
			trace_error("nand_skipblock_read_block: Cannot read page %d of block %d.\r\n", i, block);
			return error;
		}
		data = (void*)((uint8_t*)data + page_size);
	}

	return 0;
}

/**
 * \brief Writes the data and/or spare area of a page on a SkipBlock NandFlash.
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block to write.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return NAND_ERROR_BADBLOCK if the page is BAD; otherwise,
 * returns nand_ecc_write_page().
 */

uint8_t nand_skipblock_write_page(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, void *data, void *spare)
{
	/* Check that the block is LIVE */
	if (nand_skipblock_check_block(nand, block) != GOODBLOCK) {
		trace_error("nand_skipblock_write_page: Block is BAD.\r\n");
		return NAND_ERROR_BADBLOCK;
	}

	/* Write data with ECC calculation */
	return nand_ecc_write_page(nand, block, page, data, spare);
}

/**
 * \brief Writes the data of a whole block on a SkipBlock NANDFLASH.
 * \param nand  Pointer to a _raw_nand_flash instance.
 * \param block  Number of block to read page from.
 * \param data  Data area buffer, can be 0.
 * \return NAND_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * nand_ecc_read_page().
*/

uint8_t nand_skipblock_write_block(const struct _nand_flash *nand,
	uint16_t block, void *data)
{
	uint32_t num_pages_per_block, page_size;
	uint16_t i;
	uint8_t error = 0;

	/* Retrieve model information */
	page_size = nand_model_get_page_data_size(&nand->model);
	num_pages_per_block = nand_model_get_block_size_in_pages(&nand->model);

	/* Check that the block is LIVE */
	if (nand_skipblock_check_block(nand, block) != GOODBLOCK) {
		trace_error("nand_skipblock_write_block: Block is BAD.\r\n");
		return NAND_ERROR_BADBLOCK;
	}

	for (i = 0; i < num_pages_per_block; i++) {
		error = nand_ecc_write_page(nand, block, i, data, 0);
		if (error) {
			trace_error("nand_skipblock_write_block: Cannot write page %d of block %d.\r\n", i, block);
			return NAND_ERROR_CANNOTWRITE;
		}
		data = (void*)((uint8_t*)data + page_size);
	}

	return 0;
}

