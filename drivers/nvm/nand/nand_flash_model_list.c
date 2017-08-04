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

#include <string.h>

#include "chip.h"
#include "compiler.h"
#include "trace.h"
#include "nand_flash_common.h"
#include "nand_flash_model_list.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

/** List of NandFlash models which can be recognized by the software. */
static const struct _nand_flash_model nand_flash_model_list[] = {
/*	|  ID  | Bus Width   | Page  |spare  | Mo  | Block */
	{0x6e, 8, 256, 0, 1, 4},
	{0x64, 8, 256, 0, 2, 4},
	{0x68, 8, 4096, 0, 224, 1024},
	{0x6b, 8, 512, 0, 4, 8},
	{0xe8, 8, 256, 0, 1, 4},
	{0xec, 8, 256, 0, 1, 4},
	{0xea, 8, 256, 0, 2, 4},
	{0xd5, 8, 512, 0, 4, 8},
	{0xe3, 8, 512, 0, 4, 8},
	{0xe5, 8, 512, 0, 4, 8},
	{0xd6, 8, 512, 0, 8, 8},

	{0x39, 8, 512, 0, 8, 8},
	{0xe6, 8, 512, 0, 8, 8},
	{0x49, 16, 512, 0, 8, 8},
	{0x59, 16, 512, 0, 8, 8},

	{0x33, 8, 512, 0, 16, 16},
	{0x73, 8, 512, 0, 16, 16},
	{0x43, 16, 512, 0, 16, 16},
	{0x53, 16, 512, 0, 16, 16},

	{0x35, 8, 512, 0, 32, 16},
	{0x75, 8, 512, 0, 32, 16},
	{0x45, 16, 512, 0, 32, 16},
	{0x55, 16, 512, 0, 32, 16},

	{0x36, 8, 512, 0, 64, 16},
	{0x76, 8, 512, 0, 64, 16},
	{0x46, 16, 512, 0, 64, 16},
	{0x56, 16, 512, 0, 64, 16},

	{0x78, 8, 512, 0, 128, 16},
	{0x39, 8, 512, 0, 128, 16},
	{0x79, 8, 512, 0, 128, 16},
	{0x72, 16, 512, 0, 128, 16},
	{0x49, 16, 512, 0, 128, 16},
	{0x74, 16, 512, 0, 128, 16},
	{0x59, 16, 512, 0, 128, 16},

	{0x71, 8, 512, 0, 256, 16},

	/* Large blocks devices. Parameters must be fetched from the extended I */

	{0xA2, 8, 0, 0, 64, 0},
	{0xF2, 8, 0, 0, 64, 0},
	{0xB2, 16, 0, 0, 64, 0},
	{0xC2, 16, 0, 0, 64, 0},

	{0xA1, 8, 0, 0, 128, 0},
	{0xF1, 8, 0, 0, 128, 0},
	{0xB1, 16, 0, 0, 128, 0},
	{0xC1, 16, 0, 0, 128, 0},

	{0xAA, 8, 0, 0, 256, 0},
	{0xDA, 8, 0, 0, 256, 0},
	{0xBA, 16, 0, 0, 256, 0},
	{0xCA, 16, 0, 0, 256, 0},

	{0xAC, 8, 0, 0, 512, 0},
	{0xDC, 8, 0, 0, 512, 0},
	{0xBC, 16, 0, 0, 512, 0},
	{0xCC, 16, 0, 0, 512, 0},

	{0xA3, 8, 0, 0, 1024, 0},
	{0xD3, 8, 0, 0, 1024, 0},
	{0xB3, 16, 0, 0, 1024, 0},
	{0xC3, 16, 0, 0, 1024, 0},
	{0xA5, 8, 0, 0, 2048, 0},
	{0xD5, 8, 0, 0, 2048, 0},
	{0xB5, 16, 0, 0, 2048, 0},
	{0xC5, 16, 0, 0, 2048, 0},
	{0x38, 8, 0, 0, 1024, 0},
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Looks for a _nand_flash_model corresponding to the given ID inside a list of
 * model. If found, the model variable is filled with the correct values.
 * \param chip_id  Identifier returned by the NANDFLASH(id1|(id2<<8)|(id3<<16)|(id4<<24)).
 * \param model  _nand_flash_model instance to update with the model parameters.
 * \return 0 if a matching model has been found; otherwise it
 * returns NAND_ERROR_UNKNOWNMODEL.
*/
uint8_t nand_model_list_find(uint32_t chip_id, struct _nand_flash_model *model)
{
	bool found = false;
	uint8_t id2, id4;
	int i;

	id2 = (chip_id >> 8) & 0xff;
	id4 = (chip_id >> 24) & 0xff;

	trace_info_wp("Nandflash ID is 0x%08X\r\n", (unsigned int)chip_id);

	for (i = 0; i < ARRAY_SIZE(nand_flash_model_list); i++) {
		if (nand_flash_model_list[i].device_id == id2) {
			found = true;
			if (model) {
				memcpy(model, &nand_flash_model_list[i], sizeof(*model));
				if (model->page_size == 0) {
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
						model->page_size = 1024;
						break;
					case 0x01:
						model->page_size = 2048;
						break;
					case 0x02:
						model->page_size = 4096;
						break;
					case 0x03:
						model->page_size = 8192;
						break;
					}

					switch(id4 & 0x30) {
					case 0x00:
						model->block_size = 64 * 1024;
						break;
					case 0x10:
						model->block_size = 128 * 1024;
						break;
					case 0x20:
						model->block_size = 256 * 1024;
						break;
					case 0x30:
						model->block_size = 512 * 1024;
						break;
					}
				}

				if (model->spare_size == 0) {
					/* Spare size is 16/512 of data size */
					model->spare_size = model->page_size >> 5;
				}
			}

			NAND_TRACE("NAND Model found:\r\n");
			NAND_TRACE(" * device_id = 0x%02x\r\n",
					model->device_id);
			NAND_TRACE(" * device_size = %d MB\r\n",
					model->device_size);
			NAND_TRACE(" * block_size = %d bytes\r\n",
					model->block_size);
			NAND_TRACE(" * page_size = %d bytes\r\n",
					model->page_size);
			NAND_TRACE(" * spare_size = %d bytes\r\n",
					model->spare_size);
			NAND_TRACE(" * data_bus_width = %d bits\r\n",
					model->data_bus_width);
			break;
		}
	}

	// check if chip has been detected
	if (found)
		return 0;
	else
		return NAND_ERROR_UNKNOWNMODEL;
}

