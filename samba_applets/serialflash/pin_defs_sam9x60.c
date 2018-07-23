/* ----------------------------------------------------------------------------
 *         MICROCHIP Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip
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

static const struct _pin flexspi0_ioset1[] = PINS_FLEXCOM0_SPI_IOS1;
static const struct _pin flexspi0_ioset1_npcs0 = PIN_FLEXCOM0_SPI_NPCS0_IOS1;
static const struct _pin flexspi0_ioset1_npcs1 = PIN_FLEXCOM0_SPI_NPCS1_IOS1;

static const struct _pin flexspi1_ioset1[] = PINS_FLEXCOM1_SPI_IOS1;
static const struct _pin flexspi1_ioset1_npcs0 = PIN_FLEXCOM1_SPI_NPCS0_IOS1;
static const struct _pin flexspi1_ioset1_npcs1 = PIN_FLEXCOM1_SPI_NPCS1_IOS1;

static const struct _pin flexspi2_ioset1[] = PINS_FLEXCOM2_SPI_IOS1;
static const struct _pin flexspi2_ioset1_npcs0 = PIN_FLEXCOM2_SPI_NPCS0_IOS1;
static const struct _pin flexspi2_ioset1_npcs1 = PIN_FLEXCOM2_SPI_NPCS1_IOS1;

static const struct _pin flexspi3_ioset1[] = PINS_FLEXCOM3_SPI_IOS1;
static const struct _pin flexspi3_ioset1_npcs0 = PIN_FLEXCOM3_SPI_NPCS0_IOS1;
static const struct _pin flexspi3_ioset1_npcs1 = PIN_FLEXCOM3_SPI_NPCS1_IOS1;

static const struct _pin flexspi4_ioset1[] = PINS_FLEXCOM4_SPI_IOS1;
static const struct _pin flexspi4_ioset1_npcs0 = PIN_FLEXCOM4_SPI_NPCS0_IOS1;
static const struct _pin flexspi4_ioset1_npcs1 = PIN_FLEXCOM4_SPI_NPCS1_IOS1;
static const struct _pin flexspi4_ioset1_npcs2 = PIN_FLEXCOM4_SPI_NPCS2_IOS1;
static const struct _pin flexspi4_ioset1_npcs3 = PIN_FLEXCOM4_SPI_NPCS3_IOS1;

static const struct _pin flexspi4_ioset2[] = PINS_FLEXCOM4_SPI_IOS2;
static const struct _pin flexspi4_ioset2_npcs0 = PIN_FLEXCOM4_SPI_NPCS0_IOS2;
static const struct _pin flexspi4_ioset2_npcs1 = PIN_FLEXCOM4_SPI_NPCS1_IOS2;
static const struct _pin flexspi4_ioset2_npcs2 = PIN_FLEXCOM4_SPI_NPCS2_IOS2;
static const struct _pin flexspi4_ioset2_npcs3 = PIN_FLEXCOM4_SPI_NPCS3_IOS2;

static const struct _pin flexspi5_ioset1[] = PINS_FLEXCOM5_SPI_IOS1;
static const struct _pin flexspi5_ioset1_npcs0 = PIN_FLEXCOM5_SPI_NPCS0_IOS1;
static const struct _pin flexspi5_ioset1_npcs1 = PIN_FLEXCOM5_SPI_NPCS1_IOS1;
static const struct _pin flexspi5_ioset1_npcs2 = PIN_FLEXCOM5_SPI_NPCS2_IOS1;
static const struct _pin flexspi5_ioset1_npcs3 = PIN_FLEXCOM5_SPI_NPCS3_IOS1;

static const struct _pin flexspi5_ioset2[] = PINS_FLEXCOM5_SPI_IOS2;
static const struct _pin flexspi5_ioset2_npcs0 = PIN_FLEXCOM5_SPI_NPCS0_IOS2;
static const struct _pin flexspi5_ioset2_npcs1 = PIN_FLEXCOM5_SPI_NPCS1_IOS2;
static const struct _pin flexspi5_ioset2_npcs2 = PIN_FLEXCOM5_SPI_NPCS2_IOS2;
static const struct _pin flexspi5_ioset2_npcs3 = PIN_FLEXCOM5_SPI_NPCS3_IOS2;

/*----------------------------------------------------------------------------
 *        Public constants
 *----------------------------------------------------------------------------*/

const struct serialflash_pin_definition serialflash_pin_defs[] = {
	{
		.instance = 0,
		.ioset = 1,
		.addr = FLEXSPI0,
		.num_pins = ARRAY_SIZE(flexspi0_ioset1),
		.pins = flexspi0_ioset1,
		.npcs_pins = {
			&flexspi0_ioset1_npcs0, &flexspi0_ioset1_npcs1
		}
	},
	{
		.instance = 1,
		.ioset = 1,
		.addr = FLEXSPI1,
		.num_pins = ARRAY_SIZE(flexspi1_ioset1),
		.pins = flexspi1_ioset1,
		.npcs_pins = {
			&flexspi1_ioset1_npcs0, &flexspi1_ioset1_npcs1
		}
	},
	{
		.instance = 2,
		.ioset = 1,
		.addr = FLEXSPI2,
		.num_pins = ARRAY_SIZE(flexspi2_ioset1),
		.pins = flexspi2_ioset1,
		.npcs_pins = {
			&flexspi2_ioset1_npcs0, &flexspi2_ioset1_npcs1
		}
	},
	{
		.instance = 3,
		.ioset = 1,
		.addr = FLEXSPI3,
		.num_pins = ARRAY_SIZE(flexspi3_ioset1),
		.pins = flexspi3_ioset1,
		.npcs_pins = {
			&flexspi3_ioset1_npcs0, &flexspi3_ioset1_npcs1
		}
	},
	{
		.instance = 4,
		.ioset = 1,
		.addr = FLEXSPI4,
		.num_pins = ARRAY_SIZE(flexspi4_ioset1),
		.pins = flexspi4_ioset1,
		.npcs_pins = {
			&flexspi4_ioset1_npcs0, &flexspi4_ioset1_npcs1,
			&flexspi4_ioset1_npcs2, &flexspi4_ioset1_npcs3
		}
	},
	{
		.instance = 4,
		.ioset = 2,
		.addr = FLEXSPI4,
		.num_pins = ARRAY_SIZE(flexspi4_ioset2),
		.pins = flexspi4_ioset2,
		.npcs_pins = {
			&flexspi4_ioset2_npcs0, &flexspi4_ioset2_npcs1,
			&flexspi4_ioset2_npcs2, &flexspi4_ioset2_npcs3
		}
	},
	{
		.instance = 5,
		.ioset = 1,
		.addr = FLEXSPI5,
		.num_pins = ARRAY_SIZE(flexspi5_ioset1),
		.pins = flexspi5_ioset1,
		.npcs_pins = {
			&flexspi5_ioset1_npcs0, &flexspi5_ioset1_npcs1,
			&flexspi5_ioset1_npcs2, &flexspi5_ioset1_npcs3
		}
	},
	{
		.instance = 5,
		.ioset = 2,
		.addr = FLEXSPI5,
		.num_pins = ARRAY_SIZE(flexspi5_ioset2),
		.pins = flexspi5_ioset2,
		.npcs_pins = {
			&flexspi5_ioset2_npcs0, &flexspi5_ioset2_npcs1,
			&flexspi5_ioset2_npcs2, &flexspi5_ioset2_npcs3
		}
	},
};

const int num_serialflash_pin_defs = ARRAY_SIZE(serialflash_pin_defs);
