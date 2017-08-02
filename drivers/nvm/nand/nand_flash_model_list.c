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
#include "compiler.h"

#include "nand_flash_model_list.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Exported variables
 *----------------------------------------------------------------------------*/

/** List of NandFlash models which can be recognized by the software. */
const struct _nand_flash_model nand_flash_model_list[] = {
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

const int nand_flash_model_list_size = ARRAY_SIZE(nand_flash_model_list);
