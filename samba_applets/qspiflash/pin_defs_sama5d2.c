/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

#include "chip.h"
#include "compiler.h"

#include "pin_defs.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/


static const struct _pin qspi0_ioset1[] = PINS_QSPI0_IOS1;
static const struct _pin qspi0_ioset2[] = PINS_QSPI0_IOS2;
static const struct _pin qspi0_ioset3[] = PINS_QSPI0_IOS3;

static const struct _pin qspi1_ioset1[] = PINS_QSPI1_IOS1;
static const struct _pin qspi1_ioset2[] = PINS_QSPI1_IOS2;
static const struct _pin qspi1_ioset3[] = PINS_QSPI1_IOS3;

/*----------------------------------------------------------------------------
 *        Public constants
 *----------------------------------------------------------------------------*/

const struct qspiflash_pin_definition qspiflash_pin_defs[] = {
	{
		.instance = 0,
		.ioset = 1,
		.addr = QSPI0,
		.num_pins = ARRAY_SIZE(qspi0_ioset1),
		.pins = qspi0_ioset1
	},
	{
		.instance = 0,
		.ioset = 2,
		.addr = QSPI0,
		.num_pins = ARRAY_SIZE(qspi0_ioset2),
		.pins = qspi0_ioset2
	},
	{
		.instance = 0,
		.ioset = 3,
		.addr = QSPI0,
		.num_pins = ARRAY_SIZE(qspi0_ioset3),
		.pins = qspi0_ioset3
	},
	{
		.instance = 1,
		.ioset = 1,
		.addr = QSPI1,
		.num_pins = ARRAY_SIZE(qspi1_ioset1),
		.pins = qspi1_ioset1
	},
	{
		.instance = 1,
		.ioset = 2,
		.addr = QSPI1,
		.num_pins = ARRAY_SIZE(qspi1_ioset2),
		.pins = qspi1_ioset2
	},
	{
		.instance = 1,
		.ioset = 3,
		.addr = QSPI1,
		.num_pins = ARRAY_SIZE(qspi1_ioset3),
		.pins = qspi1_ioset3
	},
};

const int num_qspiflash_pin_defs = ARRAY_SIZE(qspiflash_pin_defs);
