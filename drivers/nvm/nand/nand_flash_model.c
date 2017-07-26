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
 * \brief Looks for a _nand_flash_model corresponding to the given ID inside a list of
 * model. If found, the model variable is filled with the correct values.
 * \param model_list  List of _nand_flash_model instances.
 * \param size  Number of models in list.
 * \param chip_id  Identifier returned by the NANDFLASH(id1|(id2<<8)|(id3<<16)|(id4<<24)).
 * \param model  _nand_flash_model instance to update with the model parameters.
 * \return 0 if a matching model has been found; otherwise it
 * returns NAND_ERROR_UNKNOWNMODEL.
*/
uint8_t nand_model_find(const struct _nand_flash_model *list, uint32_t list_size,
	uint32_t chip_id, struct _nand_flash_model *model)
{
	bool found = false;
	uint8_t id2, id4;
	int i;

	id2 = (chip_id >> 8) & 0xff;
	id4 = (chip_id >> 24) & 0xff;

	trace_info_wp("Nandflash ID is 0x%08X\r\n", (unsigned int)chip_id);

	for (i = 0; i < list_size; i++) {
		if (list[i].device_id == id2) {
			found = true;
			if (model) {
				memcpy(model, &list[i], sizeof(*model));
				if (model->block_size_in_kbytes == 0 ||
					model->page_size_in_bytes == 0) {
					NAND_TRACE("Fetch from ID4(0x%.2x):\r\n", id4);

					/*
					 * Fetch from the extended ID4
					 * ID4 D5  D4 BlockSize || D1  D0  PageSize
					 *     0   0   64K      || 0   0   1K
					 *     0   1   128K     || 0   1   2K
					 *     1   0   256K     || 1   0   4K
					 *     1   1   512K     || 1   1   8k
					 */

					switch(id4 & 0x03) {
					case 0x00:
						model->page_size_in_bytes = 1024;
						break;
					case 0x01:
						model->page_size_in_bytes = 2048;
						break;
					case 0x02:
						model->page_size_in_bytes = 4096;
						break;
					case 0x03:
						model->page_size_in_bytes = 8192;
						break;
					}

					switch(id4 & 0x30) {
					case 0x00:
						model->block_size_in_kbytes = 64;
						break;
					case 0x10:
						model->block_size_in_kbytes = 128;
						break;
					case 0x20:
						model->block_size_in_kbytes = 256;
						break;
					case 0x30:
						model->block_size_in_kbytes = 512;
						break;
					}
				}
			}

			NAND_TRACE("NAND Model found:\r\n");
			NAND_TRACE(" * deviceId = 0x%02X\r\n",
					model->device_id);
			NAND_TRACE(" * deviceSizeInMegaBytes = %d\r\n",
					model->device_size_in_mega_bytes);
			NAND_TRACE(" * blockSizeInkBytes = %d\r\n",
					model->block_size_in_kbytes);
			NAND_TRACE(" * pageSizeInBytes = %d\r\n",
					model->page_size_in_bytes);
			NAND_TRACE(" * options = 0x%02X\r\n",
					model->options);
			break;
		}
	}

	// check if chip has been detected
	if (found)
		return 0;
	else
		return NAND_ERROR_UNKNOWNMODEL;
}

/**
 * \brief Translates address/size access of a _nand_flash_model to block, page and
 * offset values. The values are stored in the provided variables if their
 * pointer is not 0.
 * \param model  Pointer to a _nand_flash_model instance.
 * \param address  Access address.
 * \param size  Access size in bytes.
 * \param block  Stores the first accessed block number.
 * \param page  Stores the first accessed page number inside the first block.
 * \param offset  Stores the byte offset inside the first accessed page.
 * \return 0 if the access is correct; otherwise returns
 * NAND_ERROR_OUTOFBOUNDS.
*/
uint8_t nand_model_translate_access(const struct _nand_flash_model *model,
	uint32_t address, uint32_t size,
	uint16_t *block, uint16_t *page, uint16_t *offset)
{
	/* Get Nand info */
	uint32_t block_size = nand_model_get_block_size_in_bytes(model);
	uint32_t page_size = nand_model_get_page_data_size(model);

	/* Translate address */
	uint16_t tmp_block = address / block_size;
	address -= tmp_block * block_size;
	uint16_t tmp_page = address / page_size;
	address -= tmp_page * page_size;
	uint16_t tmp_offset = address;

	 /* Check that access is not too big */
	if ((address + size) > nand_model_get_device_size_in_bytes(model)) {
		NAND_TRACE("nand_model_translate_access: out-of-bounds access.\r\n");
		return NAND_ERROR_OUTOFBOUNDS;
	}

	// Save results
	if (block)
		*block = tmp_block;
	if (page)
		*page = tmp_page;
	if (offset)
		*offset = tmp_offset;

	return 0;
}

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
	return (1024 * model->device_size_in_mega_bytes)
		/ model->block_size_in_kbytes;
}

/**
 * \brief Returns the number of pages in the entire device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_device_size_in_pages(
		const struct _nand_flash_model *model)
{
	return (uint32_t)nand_model_get_device_size_in_blocks(model)
		* nand_model_get_block_size_in_pages(model);
}

/**
 * \brief Returns the size of the whole device in bytes (this does not include
 * the size of the spare zones).
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint64_t nand_model_get_device_size_in_bytes(
		const struct _nand_flash_model *model)
{
	return ((uint64_t)model->device_size_in_mega_bytes) << 20;
}

/**
 * \brief Returns the size of the whole device in Mega bytes (this does not
 * include the size of the spare zones).
 * \param model  Pointer to a _nand_flash_model instance.
 */
uint32_t nand_model_get_device_size_in_mbytes(
		const struct _nand_flash_model *model)
{
	return model->device_size_in_mega_bytes;
}

/**
 * \brief Returns the number of pages in one single block of a device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint16_t nand_model_get_block_size_in_pages(
		const struct _nand_flash_model *model)
{
	return model->block_size_in_kbytes * 1024 / model->page_size_in_bytes;
}

/**
 * \brief Returns the size in bytes of one single block of a device. This does
 * not take into account the spare zones size.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_block_size_in_bytes(
		const struct _nand_flash_model *model)
{
	return model->block_size_in_kbytes * 1024;
}

/**
 * \brief Returns the size of the data area of a page in bytes.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint32_t nand_model_get_page_data_size(const struct _nand_flash_model *model)
{
	return model->page_size_in_bytes;
}

/**
 * \brief Returns the size of the spare area of a page in bytes.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint16_t nand_model_get_page_spare_size(const struct _nand_flash_model *model)
{
	if (model->spare_size_in_bytes) {
		return model->spare_size_in_bytes;
	} else {
		/* Spare size is 16/512 of data size */
		return model->page_size_in_bytes >> 5;
	}
}

/**
 * \brief Returns the number of bits used by the data bus of a NandFlash device.
 * \param model  Pointer to a _nand_flash_model instance.
*/
uint8_t nand_model_get_data_bus(const struct _nand_flash_model *model)
{
	return model->options & NANDFLASHMODEL_DATABUS16 ? 16 : 8;
}

/**
 * \brief Returns 1 if the given NandFlash model uses the "small blocks/pages"
 * command set; otherwise returns 0.
 * \param model  Pointer to a _nand_flash_model instance.
*/
bool nand_model_has_small_blocks(const struct _nand_flash_model *model)
{
	return model->page_size_in_bytes <= 512 ? 1 : 0;
}

/**
 * \brief Returns 1 if the device supports the copy-back operation. Otherwise
 * returns 0.
 * \param model  Pointer to a _nand_flash_model instance.
*/
bool nand_model_supports_copy_back(const struct _nand_flash_model *model)
{
	return (model->options & NANDFLASHMODEL_COPYBACK) != 0;
}
