/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

#include "board_twi.h"

#include "i2c/twi-bus.h"

#include "gpio/pio.h"

#include "nvm/i2c/at24.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_TWI_AT24
static struct _at24 at24;
#endif

void board_cfg_twi_bus(void)
{
#ifdef BOARD_TWI_BUS0
	const struct _pin pins_twi_bus0[] = BOARD_TWI_BUS0_PINS;
	pio_configure(pins_twi_bus0, ARRAY_SIZE(pins_twi_bus0));
	twi_bus_configure(0, BOARD_TWI_BUS0, BOARD_TWI_BUS0_FREQ, BOARD_TWI_BUS0_MODE);
#endif
#ifdef BOARD_TWI_BUS1
	const struct _pin pins_twi_bus1[] = BOARD_TWI_BUS1_PINS;
	pio_configure(pins_twi_bus1, ARRAY_SIZE(pins_twi_bus1));
	twi_bus_configure(1, BOARD_TWI_BUS1, BOARD_TWI_BUS1_FREQ, BOARD_TWI_BUS1_MODE);
#endif
#ifdef BOARD_TWI_BUS2
	const struct _pin pins_twi_bus2[] = BOARD_TWI_BUS2_PINS;
	pio_configure(pins_twi_bus2, ARRAY_SIZE(pins_twi_bus2));
	twi_bus_configure(2, BOARD_TWI_BUS2, BOARD_TWI_BUS2_FREQ, BOARD_TWI_BUS2_MODE);
#endif
#ifdef BOARD_TWI_BUS3
	const struct _pin pins_twi_bus3[] = BOARD_TWI_BUS3_PINS;
	pio_configure(pins_twi_bus3, ARRAY_SIZE(pins_twi_bus3));
	twi_bus_configure(3, BOARD_TWI_BUS3, BOARD_TWI_BUS3_FREQ, BOARD_TWI_BUS3_MODE);
#endif
#ifdef BOARD_TWI_BUS4
	const struct _pin pins_twi_bus4[] = BOARD_TWI_BUS4_PINS;
	pio_configure(pins_twi_bus4, ARRAY_SIZE(pins_twi_bus4));
	twi_bus_configure(4, BOARD_TWI_BUS4, BOARD_TWI_BUS4_FREQ, BOARD_TWI_BUS4_MODE);
#endif
#ifdef BOARD_TWI_BUS5
	const struct _pin pins_twi_bus5[] = BOARD_TWI_BUS5_PINS;
	pio_configure(pins_twi_bus5, ARRAY_SIZE(pins_twi_bus2));
	twi_bus_configure(5, BOARD_TWI_BUS5, BOARD_TWI_BUS5_FREQ, BOARD_TWI_BUS5_MODE);
#endif
#ifdef BOARD_TWI_BUS6
	const struct _pin pins_twi_bus6[] = BOARD_TWI_BUS6_PINS;
	pio_configure(pins_twi_bus6, ARRAY_SIZE(pins_twi_bus6));
	twi_bus_configure(6, BOARD_TWI_BUS6, BOARD_TWI_BUS6_FREQ, BOARD_TWI_BUS6_MODE);
#endif
}

#ifdef CONFIG_HAVE_TWI_AT24
void board_cfg_at24(void)
{
	const struct _at24_config at24_device_cfg = {
		.bus = BOARD_AT24_TWI_BUS,
		.addr = BOARD_AT24_ADDR,
		.model = BOARD_AT24_MODEL,
	};
	at24_configure(&at24, &at24_device_cfg);
}

struct _at24 * board_get_at24(void)
{
	return &at24;
}
#endif /* CONFIG_HAVE_TWI_AT24 */
