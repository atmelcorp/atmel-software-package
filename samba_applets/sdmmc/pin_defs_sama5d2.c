/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
#include "board.h"
#include "pin_defs.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct _pin pins_sdmmc0[] = {
	PIN_SDMMC0_CD_IOS1,
	PIN_SDMMC0_CK_IOS1,
	PIN_SDMMC0_CMD_IOS1,
	PIN_SDMMC0_VDDSEL_IOS1,
	PINS_SDMMC0_DATA8B_IOS1
};

static const struct _pin pins_sdmmc1[] = {
	PIN_SDMMC1_CD_IOS1,
	PIN_SDMMC1_CK_IOS1,
	PIN_SDMMC1_CMD_IOS1,
	PINS_SDMMC1_DATA4B_IOS1
};

/*----------------------------------------------------------------------------
 *        Public constants
 *----------------------------------------------------------------------------*/

const struct sdmmc_pin_definition sdmmc_pin_defs[] = {
	{
		.instance = 0,
		.num_pins = ARRAY_SIZE(pins_sdmmc0),
		.addr = SDMMC0,
		.sdmmc_id = ID_SDMMC0,
		.pins = pins_sdmmc0,
	},
	{
		.instance = 1,
		.num_pins = ARRAY_SIZE(pins_sdmmc1),
		.addr = SDMMC1,
		.sdmmc_id = ID_SDMMC1,
		.pins = pins_sdmmc1,
	},
};

const int num_sdmmc_pin_defs = ARRAY_SIZE(sdmmc_pin_defs);
