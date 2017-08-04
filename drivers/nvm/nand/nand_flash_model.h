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
 * \file
 * !Purpose
 *
 *     Type and methods for manipulating NandFlash models.
 *
 * !Usage
 *
 * -# Find the model of a NandFlash using its device ID with the
 *    nand_model_find function.
 *
 * -# Retrieve parameters of a NandFlash model using the following functions:
 *    - nand_model_get_device_id
 *    - nand_model_get_device_size_in_blocks
 *    - nand_model_get_device_size_in_pages
 *    - nand_model_get_device_size_in_bytes
 *    - nand_model_get_block_size_in_pages
 *    - nand_model_get_block_size_in_bytes
 *    - nand_model_get_page_data_size
 *    - nand_model_get_page_spare_size
 *    - nand_model_get_data_bus_width
 *    - nand_model_has_small_blocks
 */

#ifndef NAND_FLASH_MODEL_H
#define NAND_FLASH_MODEL_H

/*------------------------------------------------------------------------*/
/*                      Headers                                           */
/*------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------- */
/*         Types                                                         */
/*---------------------------------------------------------------------- */

/** Describes a particular model of NandFlash device. */
struct _nand_flash_model {
	/** Identifier for the device. */
	uint8_t device_id;

	/** Data Bus Width (8/16) */
	uint8_t data_bus_width;

	/** Size of the device in MB. */
	uint32_t device_size;

	/** Size of the data area of a page, in bytes. */
	uint16_t page_size;

	/** Size of the spare area of a page, in bytes. */
	uint16_t spare_size;

	/** Size of one block, in bytes. */
	uint32_t block_size;
};

/*---------------------------------------------------------------------- */
/*         Exported functions                                            */
/*---------------------------------------------------------------------- */

extern uint8_t nand_model_get_device_id(
		const struct _nand_flash_model *model);

extern uint16_t nand_model_get_device_size_in_blocks(
		const struct _nand_flash_model *model);

extern uint32_t nand_model_get_device_size_in_pages(
		const struct _nand_flash_model *model);

extern uint64_t nand_model_get_device_size_in_bytes(
		const struct _nand_flash_model *model);

extern uint32_t nand_model_get_device_size_in_mbytes(
		const struct _nand_flash_model *model);

extern uint16_t nand_model_get_block_size_in_pages(
		const struct _nand_flash_model *model);

extern uint32_t nand_model_get_block_size_in_bytes(
		const struct _nand_flash_model *model);

extern uint32_t nand_model_get_page_data_size(
		const struct _nand_flash_model *model);

extern uint16_t nand_model_get_page_spare_size(
		const struct _nand_flash_model *model);

extern uint8_t nand_model_get_data_bus_width(
		const struct _nand_flash_model *model);

extern bool nand_model_has_small_blocks(
		const struct _nand_flash_model *model);

/**@}*/

#endif /* NAND_FLASH_MODEL_H */
