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

#include "nand_flash_spare_scheme.h"
#include "nand_flash_model_list.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Exported variables
 *----------------------------------------------------------------------------*/
/** List of NandFlash models which can be recognized by the software. */
const struct _nand_flash_model nand_flash_model_list[NANDFLASH_MODEL_LIST_SIZE] = {

/*	|  ID  | Options   | Page  |spare  | Mo  | Block   |BlkPg   |DevBlk */
	{0x6e, NANDFLASHMODEL_DATABUS8, 256, 0, 1, 4, &nand_spare_scheme256},
	{0x64, NANDFLASHMODEL_DATABUS8, 256, 0, 2, 4, &nand_spare_scheme256},
	{0x68, NANDFLASHMODEL_DATABUS8, 4096, 0, 224, 1024, &nand_spare_scheme4096},
	{0x6b, NANDFLASHMODEL_DATABUS8, 512, 0, 4, 8, &nand_spare_scheme512},
	{0xe8, NANDFLASHMODEL_DATABUS8, 256, 0, 1, 4, &nand_spare_scheme256},
	{0xec, NANDFLASHMODEL_DATABUS8, 256, 0, 1, 4, &nand_spare_scheme256},
	{0xea, NANDFLASHMODEL_DATABUS8, 256, 0, 2, 4, &nand_spare_scheme256},
	{0xd5, NANDFLASHMODEL_DATABUS8, 512, 0, 4, 8, &nand_spare_scheme512},
	{0xe3, NANDFLASHMODEL_DATABUS8, 512, 0, 4, 8, &nand_spare_scheme512},
	{0xe5, NANDFLASHMODEL_DATABUS8, 512, 0, 4, 8, &nand_spare_scheme512},
	{0xd6, NANDFLASHMODEL_DATABUS8, 512, 0, 8, 8, &nand_spare_scheme512},

	{0x39, NANDFLASHMODEL_DATABUS8, 512, 0, 8, 8, &nand_spare_scheme512},
	{0xe6, NANDFLASHMODEL_DATABUS8, 512, 0, 8, 8, &nand_spare_scheme512},
	{0x49, NANDFLASHMODEL_DATABUS16, 512, 0, 8, 8, &nand_spare_scheme512},
	{0x59, NANDFLASHMODEL_DATABUS16, 512, 0, 8, 8, &nand_spare_scheme512},

	{0x33, NANDFLASHMODEL_DATABUS8, 512, 0, 16, 16, &nand_spare_scheme512},
	{0x73, NANDFLASHMODEL_DATABUS8, 512, 0, 16, 16, &nand_spare_scheme512},
	{0x43, NANDFLASHMODEL_DATABUS16, 512, 0, 16, 16, &nand_spare_scheme512},
	{0x53, NANDFLASHMODEL_DATABUS16, 512, 0, 16, 16, &nand_spare_scheme512},

	{0x35, NANDFLASHMODEL_DATABUS8, 512, 0, 32, 16, &nand_spare_scheme512},
	{0x75, NANDFLASHMODEL_DATABUS8, 512, 0, 32, 16, &nand_spare_scheme512},
	{0x45, NANDFLASHMODEL_DATABUS16, 512, 0, 32, 16, &nand_spare_scheme512},
	{0x55, NANDFLASHMODEL_DATABUS16, 512, 0, 32, 16, &nand_spare_scheme512},

	{0x36, NANDFLASHMODEL_DATABUS8, 512, 0, 64, 16, &nand_spare_scheme512},
	{0x76, NANDFLASHMODEL_DATABUS8, 512, 0, 64, 16, &nand_spare_scheme512},
	{0x46, NANDFLASHMODEL_DATABUS16, 512, 0, 64, 16, &nand_spare_scheme512},
	{0x56, NANDFLASHMODEL_DATABUS16, 512, 0, 64, 16, &nand_spare_scheme512},

	{0x78, NANDFLASHMODEL_DATABUS8, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x39, NANDFLASHMODEL_DATABUS8, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x79, NANDFLASHMODEL_DATABUS8, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x72, NANDFLASHMODEL_DATABUS16, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x49, NANDFLASHMODEL_DATABUS16, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x74, NANDFLASHMODEL_DATABUS16, 512, 0, 128, 16, &nand_spare_scheme512},
	{0x59, NANDFLASHMODEL_DATABUS16, 512, 0, 128, 16, &nand_spare_scheme512},

	{0x71, NANDFLASHMODEL_DATABUS8, 512, 0, 256, 16, &nand_spare_scheme512},

/* Large blocks devices. Parameters must be fetched from the extended I */
#define OPTIONS     NANDFLASHMODEL_COPYBACK

	{0xA2, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 64, 0, &nand_spare_scheme2048},
	{0xF2, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 64, 0, &nand_spare_scheme2048},
	{0xB2, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 64, 0, &nand_spare_scheme2048},
	{0xC2, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 64, 0, &nand_spare_scheme2048},

	{0xA1, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 128, 0, &nand_spare_scheme2048},
	{0xF1, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 128, 0, &nand_spare_scheme2048},
	{0xB1, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 128, 0, &nand_spare_scheme2048},
	{0xC1, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 128, 0, &nand_spare_scheme2048},

	{0xAA, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 256, 0, &nand_spare_scheme2048},
	{0xDA, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 256, 0, &nand_spare_scheme2048},
	{0xBA, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 256, 0, &nand_spare_scheme2048},
	{0xCA, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 256, 0, &nand_spare_scheme2048},

	{0xAC, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 512, 0, &nand_spare_scheme2048},
	{0xDC, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 512, 0, &nand_spare_scheme2048},
	{0xBC, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 512, 0, &nand_spare_scheme2048},
	{0xCC, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 512, 0, &nand_spare_scheme2048},

	{0xA3, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 1024, 0, &nand_spare_scheme2048},
	{0xD3, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 1024, 0, &nand_spare_scheme2048},
	{0xB3, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 1024, 0, &nand_spare_scheme2048},
	{0xC3, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 1024, 0, &nand_spare_scheme2048},
	{0xA5, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 2048, 0, &nand_spare_scheme2048},
	{0xD5, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 2048, 0, &nand_spare_scheme2048},
	{0xB5, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 2048, 0, &nand_spare_scheme2048},
	{0xC5, NANDFLASHMODEL_DATABUS16 | OPTIONS, 0, 0, 2048, 0, &nand_spare_scheme2048},
	{0x38, NANDFLASHMODEL_DATABUS8 | OPTIONS, 0, 0, 1024, 0, &nand_spare_scheme4096},
};
