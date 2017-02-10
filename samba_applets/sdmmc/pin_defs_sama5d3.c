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

#include "chip.h"
#include "compiler.h"

#include "pin_defs.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct _pin pin_hsmci0_ck = PIN_HSMCI0_CK;
static const struct _pin pin_hsmci0_cmd_a = PIN_HSMCI0_CMD_A;
static const struct _pin pins_hsmci0_data1b_a[] = { PINS_HSMCI0_DATA1B_A };
static const struct _pin pins_hsmci0_data4b_a[] = { PINS_HSMCI0_DATA4B_A };
static const struct _pin pins_hsmci0_data8b_a[] = { PINS_HSMCI0_DATA8B_A };

static const struct _pin pin_hsmci1_ck = PIN_HSMCI1_CK;
static const struct _pin pin_hsmci1_cmd_a = PIN_HSMCI1_CMD_A;
static const struct _pin pins_hsmci1_data1b_a[] = { PINS_HSMCI1_DATA1B_A };
static const struct _pin pins_hsmci1_data4b_a[] = { PINS_HSMCI1_DATA4B_A };

static const struct _pin pin_hsmci2_ck = PIN_HSMCI2_CK;
static const struct _pin pin_hsmci2_cmd_a = PIN_HSMCI2_CMD_A;
static const struct _pin pins_hsmci2_data1b_a[] = { PINS_HSMCI2_DATA1B_A };
static const struct _pin pins_hsmci2_data4b_a[] = { PINS_HSMCI2_DATA4B_A };

/*----------------------------------------------------------------------------
 *        Public constants
 *----------------------------------------------------------------------------*/

const struct sdmmc_pin_definition sdmmc_pin_defs[] = {
	{
		.instance = 0,
		.ioset = 1,
		.name = "HSMCI0",
		.addr = HSMCI0,
		.slot = HSMCI_SDCR_SDCSEL_SLOTA,
		.pin_ck = &pin_hsmci0_ck,
		.pin_cmd = &pin_hsmci0_cmd_a,
		.num_pins_data1b = ARRAY_SIZE(pins_hsmci0_data1b_a),
		.pins_data1b = pins_hsmci0_data1b_a,
		.num_pins_data4b = ARRAY_SIZE(pins_hsmci0_data4b_a),
		.pins_data4b = pins_hsmci0_data4b_a,
		.num_pins_data8b = ARRAY_SIZE(pins_hsmci0_data8b_a),
		.pins_data8b = pins_hsmci0_data8b_a,
	},
	{
		.instance = 1,
		.ioset = 1,
		.name = "HSMCI1",
		.addr = HSMCI1,
		.slot = HSMCI_SDCR_SDCSEL_SLOTA,
		.pin_ck = &pin_hsmci1_ck,
		.pin_cmd = &pin_hsmci1_cmd_a,
		.num_pins_data1b = ARRAY_SIZE(pins_hsmci1_data1b_a),
		.pins_data1b = pins_hsmci1_data1b_a,
		.num_pins_data4b = ARRAY_SIZE(pins_hsmci1_data4b_a),
		.pins_data4b = pins_hsmci1_data4b_a,
		.num_pins_data8b = 0,
		.pins_data8b = NULL,
	},
	{
		.instance = 2,
		.ioset = 1,
		.name = "HSMCI2",
		.addr = HSMCI2,
		.slot = HSMCI_SDCR_SDCSEL_SLOTA,
		.pin_ck = &pin_hsmci2_ck,
		.pin_cmd = &pin_hsmci2_cmd_a,
		.num_pins_data1b = ARRAY_SIZE(pins_hsmci2_data1b_a),
		.pins_data1b = pins_hsmci2_data1b_a,
		.num_pins_data4b = ARRAY_SIZE(pins_hsmci2_data4b_a),
		.pins_data4b = pins_hsmci2_data4b_a,
		.num_pins_data8b = 0,
		.pins_data8b = NULL,
	},
};

const int num_sdmmc_pin_defs = ARRAY_SIZE(sdmmc_pin_defs);
