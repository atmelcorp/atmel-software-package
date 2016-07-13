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

/**
 * \file
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "compiler.h"

#include "misc/led.h"

#include "peripherals/pio.h"

/*------------------------------------------------------------------------------
 *         Local Variables
 *------------------------------------------------------------------------------*/

/* Pins list asociated to LEDs */
static struct _pin *pins_leds;

/* Number of LEDs */
static uint32_t led_count = 0;

/*------------------------------------------------------------------------------
 *         Global Functions
 *------------------------------------------------------------------------------*/

extern uint32_t led_configure(struct _pin *leds, uint32_t count)
{
	uint32_t status = 0;
	uint32_t led;

	// Configure LED
	led_count = count;
	pins_leds = leds;

	for (led = 0 ; led < led_count ; led++)
		if (pio_configure(&pins_leds[led], 1) == 1)
			status |= (1 << led);

	return status;
}

extern uint32_t led_set(uint32_t led)
{
	/* Check if LED exists */
	if (led >= led_count)
		return 0;

	/* Turn LED on */
	if (pins_leds[led].type == PIO_OUTPUT_0)
		pio_set(&pins_leds[led]);
	else
		pio_clear(&pins_leds[led]);

	return 1;
}

extern uint32_t led_clear (uint32_t led)
{
	/* Check if LED exists */
	if (led >= led_count)
		return 0;

	/* Turn LED off */
	if (pins_leds[led].type == PIO_OUTPUT_0)
		pio_clear(&pins_leds[led]);
	else
		pio_set(&pins_leds[led]);

	return 1;
}

extern uint32_t led_toggle(uint32_t led)
{
	/* Check if LED exists */
	if (led >= led_count)
		return 0;

	/* Toggle LED */
	if (pio_get_output_data_status(&pins_leds[led]))
		pio_clear(&pins_leds[led]);
	else
		pio_set(&pins_leds[led]);

	return 1;
}
