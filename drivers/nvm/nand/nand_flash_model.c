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

/*-----------------------------------------------------------------------*/
/*        Headers                                                        */
/*-----------------------------------------------------------------------*/

#include "chip.h"

#include "nand_flash_common.h"
#include "nand_flash_model_list.h"

#include "trace.h"
#include <string.h>
#include <assert.h>

/*-----------------------------------------------------------------------*/
/*                 Exported functions                                    */
/*-----------------------------------------------------------------------*/

/**
 * \brief Returns the device ID of a particular NANDFLASH model.
 * \param model  Pointer to a _nand_flash_model instance.
 */
uint8_t nand_model_get_device_id(const struct _nand_flash_model *model)
{
	return model->device_id;
}

/**
 * \brief Returns the number of blocks in the entire device.
 * \param model  Pointer to a _nand_flash_model instance.
 */
uint16_t nand_model_get_device_size_in_blocks(
		const struct _nand_flash_model *model)
{
	return (model->device_size * 1024) / (model->block_size / 1024);
}

/**
 * \brief Returns the number of pages in the entire device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_device_size_in_pages(
		const struct _nand_flash_model *model)
{
	return nand_model_get_device_size_in_bytes(model)
		/ model->page_size;
}

/**
 * \brief Returns the size of the whole device in bytes (this does not include
 * the size of the spare zones).
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint64_t nand_model_get_device_size_in_bytes(
		const struct _nand_flash_model *model)
{
	return ((uint64_t)model->device_size) << 20;
}

/**
 * \brief Returns the size of the whole device in Mega bytes (this does not
 * include the size of the spare zones).
 * \param model  Pointer to a _nand_flash_model instance.
 */
uint32_t nand_model_get_device_size_in_mbytes(
		const struct _nand_flash_model *model)
{
	return model->device_size;
}

/**
 * \brief Returns the number of pages in one single block of a device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint16_t nand_model_get_block_size_in_pages(
		const struct _nand_flash_model *model)
{
	return model->block_size / model->page_size;
}

/**
 * \brief Returns the size in bytes of one single block of a device. This does
 * not take into account the spare zones size.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_block_size_in_bytes(
		const struct _nand_flash_model *model)
{
	return model->block_size;
}

/**
 * \brief Returns the size of the data area of a page in bytes.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_page_data_size(const struct _nand_flash_model *model)
{
	return model->page_size;
}

/**
 * \brief Returns the size of the spare area of a page in bytes.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint16_t nand_model_get_page_spare_size(const struct _nand_flash_model *model)
{
	return model->spare_size;
}

/**
 * \brief Returns the number of bits used by the data bus of a NandFlash device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint8_t nand_model_get_data_bus_width(const struct _nand_flash_model *model)
{
	return model->data_bus_width;
}

/**
 * \brief Returns 1 if the given NandFlash model uses the "small blocks/pages"
 * command set; otherwise returns 0.
 * \param model  Pointer to a _nand_flash_model instance.
*/
bool nand_model_has_small_blocks(const struct _nand_flash_model *model)
{
	return model->page_size <= 512 ? 1 : 0;
}
