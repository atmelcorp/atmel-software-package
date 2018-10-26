/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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

#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_

#include <stdint.h>
#include "trace.h"

#include "gpio/pio.h"
#include "spi/qspi.h"

#if defined (CONFIG_SOC_SAMA5D2)

/* Instance/IOSet PIO configuration */
struct qspiflash_pin_definition
{
	uint32_t           instance;
	uint32_t           ioset;
	Qspi*              addr;
	uint32_t           num_pins;
	const struct _pin *pins;
};

/*----------------------------------------------------------------------------
 *        static constants
 *----------------------------------------------------------------------------*/
static const struct _pin qspi0_ioset1[] = PINS_QSPI0_IOS1;
static const struct _pin qspi0_ioset2[] = PINS_QSPI0_IOS2;
static const struct _pin qspi0_ioset3[] = PINS_QSPI0_IOS3;

static const struct _pin qspi1_ioset1[] = PINS_QSPI1_IOS1;
static const struct _pin qspi1_ioset2[] = PINS_QSPI1_IOS2;
static const struct _pin qspi1_ioset3[] = PINS_QSPI1_IOS3;

static const struct qspiflash_pin_definition qspiflash_pin_defs[] = {
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

static const int num_qspiflash_pin_defs = ARRAY_SIZE(qspiflash_pin_defs);

bool qspi_pio_configure(uint32_t instance, uint32_t ioset, Qspi** addr)
{
	int i;
	for (i = 0; i < num_qspiflash_pin_defs; i++) {
		const struct qspiflash_pin_definition* def =
			&qspiflash_pin_defs[i];
		if (def->instance == instance && def->ioset == ioset) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}

	trace_error_wp("Invalid configuration: QSPI%u IOSet%u\r\n",
		(unsigned)instance, (unsigned)ioset);
	return false;
}

#elif defined (CONFIG_SOC_SAM9X60)

bool qspi_pio_configure(uint32_t instance, Qspi** addr)
{
	struct _pin pins_qspi[] = PINS_QSPI;

	if (0 == instance) {
		pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));
		*addr = QSPI0;
		return true;
	}

	trace_error_wp("Peripheral not exists: QSPI%u\r\n", (unsigned)instance);
	return true;
}

#endif

#endif /* _PIN_DEFS_H_ */
