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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <string.h>

#include "chip.h"
#include "compiler.h"
#include "nand_flash_common.h"
#include "nand_flash_model_list.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

#define LEGACY_NAND(id, bus_width, size, erase_size) \
	{\
		.device_id = (id),\
		.data_bus_width = (bus_width),\
		.device_size = (size),\
		.page_size = 512,\
		.spare_size = 16,\
		.block_size = (erase_size),\
	}

#define NEWER_NAND(id, bus_width, size) \
	{\
		.device_id = (id),\
		.data_bus_width = (bus_width),\
		.device_size = (size),\
		.page_size = 0,\
		.spare_size = 0,\
		.block_size = 0,\
	}

/** List of known NAND models */
static const struct _nand_flash_model nand_flash_model_list[] = {
	/* 1 MB */
	LEGACY_NAND(0x6e,  8, 1, 4096),
	LEGACY_NAND(0xe8,  8, 1, 4096),
	LEGACY_NAND(0xec,  8, 1, 4096),

	/* 2 MB */
	LEGACY_NAND(0x64,  8, 2, 4096),
	LEGACY_NAND(0xea,  8, 2, 4096),

	/* 4 MB */
	LEGACY_NAND(0x6b,  8, 4, 8192),
	LEGACY_NAND(0xe3,  8, 4, 8192),
	LEGACY_NAND(0xe5,  8, 4, 8192),

	/* 8MB */
	LEGACY_NAND(0xd6,  8, 8, 8192),
	LEGACY_NAND(0xe6,  8, 8, 8192),

	/* 16 MB */
	LEGACY_NAND(0x33,  8, 16, 16384),
	LEGACY_NAND(0x43, 16, 16, 16384),
	LEGACY_NAND(0x53, 16, 16, 16384),
	LEGACY_NAND(0x73,  8, 16, 16384),

	/* 32 MB */
	LEGACY_NAND(0x35,  8, 32, 16384),
	LEGACY_NAND(0x45, 16, 32, 16384),
	LEGACY_NAND(0x55, 16, 32, 16384),
	LEGACY_NAND(0x75,  8, 32, 16384),

	/* 64 MB */
	LEGACY_NAND(0x36,  8, 64, 16384),
	LEGACY_NAND(0x46, 16, 64, 16384),
	LEGACY_NAND(0x56, 16, 64, 16384),
	LEGACY_NAND(0x76,  8, 64, 16384),

	/* 128 MB */
	LEGACY_NAND(0x39,  8, 128, 16384),
	LEGACY_NAND(0x49, 16, 128, 16384),
	LEGACY_NAND(0x59, 16, 128, 16384),
	LEGACY_NAND(0x72, 16, 128, 16384),
	LEGACY_NAND(0x74, 16, 128, 16384),
	LEGACY_NAND(0x78,  8, 128, 16384),
	LEGACY_NAND(0x79,  8, 128, 16384),

	/* 256 MB */
	LEGACY_NAND(0x71,  8, 256, 16384),

	/* Newer devices */
	/* Page size is 0: all parameters will be fetched from ID4 */

	/* 64 MB */
	NEWER_NAND(0xa0,  8, 64),
	NEWER_NAND(0xa2,  8, 64),
	NEWER_NAND(0xb0, 16, 64),
	NEWER_NAND(0xb2, 16, 64),
	NEWER_NAND(0xc0, 16, 64),
	NEWER_NAND(0xc2, 16, 64),
	NEWER_NAND(0xd0,  8, 64),
	NEWER_NAND(0xf0,  8, 64),
	NEWER_NAND(0xf2,  8, 64),

	/* 128 MB */
	NEWER_NAND(0xa1,  8, 128),
	NEWER_NAND(0xad, 16, 128),
	NEWER_NAND(0xb1, 16, 128),
	NEWER_NAND(0xc1, 16, 128),
	NEWER_NAND(0xd1,  8, 128),
	NEWER_NAND(0xf1,  8, 128),

	/* 256 MB */
	NEWER_NAND(0xaa,  8, 256),
	NEWER_NAND(0xba, 16, 256),
	NEWER_NAND(0xca, 16, 256),
	NEWER_NAND(0xda,  8, 256),

	/* 512 MB */
	NEWER_NAND(0xac,  8, 512),
	NEWER_NAND(0xbc, 16, 512),
	NEWER_NAND(0xcc, 16, 512),
	NEWER_NAND(0xdc,  8, 512),

	/* 1 GB */
	NEWER_NAND(0xa3,  8, 1024),
	NEWER_NAND(0xb3, 16, 1024),
	NEWER_NAND(0xc3, 16, 1024),
	NEWER_NAND(0xd3,  8, 1024),

	/* 2 GB */
	NEWER_NAND(0xa5,  8, 2048),
	NEWER_NAND(0xb5, 16, 2048),
	NEWER_NAND(0xc5, 16, 2048),
	NEWER_NAND(0xd5,  8, 2048),

	/* 4 GB */
	NEWER_NAND(0xa7,  8, 4096),
	NEWER_NAND(0xb7, 16, 4096),
	NEWER_NAND(0xc7, 16, 4096),
	NEWER_NAND(0xd7,  8, 4096),

	/* 8 GB */
	NEWER_NAND(0xae,  8, 8192),
	NEWER_NAND(0xbe, 16, 8192),
	NEWER_NAND(0xce, 16, 8192),
	NEWER_NAND(0xde,  8, 8192),

	/* 16 GB */
	NEWER_NAND(0x1a,  8, 16384),
	NEWER_NAND(0x2a, 16, 16384),
	NEWER_NAND(0x3a,  8, 16384),
	NEWER_NAND(0x4a, 16, 16384),

	/* 32 GB */
	NEWER_NAND(0x1c,  8, 32768),
	NEWER_NAND(0x2c, 16, 32768),
	NEWER_NAND(0x3c,  8, 32768),
	NEWER_NAND(0x4c, 16, 32768),

	/* 64 GB */
	NEWER_NAND(0x1e,  8, 65536),
	NEWER_NAND(0x2e, 16, 65536),
	NEWER_NAND(0x3e,  8, 65536),
	NEWER_NAND(0x4e, 16, 65536),
};

/*-----------------------------------------------------------------------*/
/*                 Exported functions                                    */
/*-----------------------------------------------------------------------*/

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
					/*
					 * Fetch from the extended ID4
					 * ID4 D5  D4 BlockSize || D2  SpareSize || D1  D0  PageSize
					 *     0   0   64K      || 0   8/512     || 0   0   1K
					 *     0   1   128K     || 1   16/512    || 0   1   2K
					 *     1   0   256K     ||               || 1   0   4K
					 *     1   1   512K     ||               || 1   1   8k
					 */

					switch(id4 & 0x03) {
					case 0x00:
						model->page_size = 1024;
						break;
					case 0x01:
						model->page_size = 2 * 1024;
						break;
					case 0x02:
						model->page_size = 4 * 1024;
						break;
					case 0x03:
						model->page_size = 8 * 1024;
						break;
					}

					if (id4 & 0x04)
						model->spare_size = 16 * (model->page_size / 512);
					else
						model->spare_size = 8 * (model->page_size / 512);

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
			}

			trace_info_wp("NAND Model found:\r\n");
			trace_info_wp(" * device_id = 0x%02x\r\n",
					model->device_id);
			trace_info_wp(" * device_size = %lu MB\r\n",
					model->device_size);
			trace_info_wp(" * block_size = %lu bytes\r\n",
					model->block_size);
			trace_info_wp(" * page_size = %u bytes\r\n",
					model->page_size);
			trace_info_wp(" * spare_size = %u bytes\r\n",
					model->spare_size);
			trace_info_wp(" * data_bus_width = %u bits\r\n",
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
