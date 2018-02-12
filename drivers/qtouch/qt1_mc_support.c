/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "qt1_mc_support.h"
#include "ptc/ppp.h"
#include "ptc/qtm.h"
#include "gpio/pio.h"

#include "compiler.h"
#include "trace.h"
#include "timer.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

static uint8_t RGB_values[64][3] = {
	{20, 0, 0},  {20, 0, 0}, {19, 1, 0}, {18, 2, 0},  {17, 3, 0}, {16, 4, 0},  {15, 5, 0}, {14, 6, 0},
	{13, 7, 0},  {12, 8, 0}, {11, 9, 0}, {10, 10, 0}, {9, 11, 0}, {8, 12, 0},  {7, 13, 0}, {6, 14, 0},
	{5, 15, 0},  {4, 16, 0}, {3, 17, 0}, {2, 18, 0},  {1, 19, 0}, {0, 20, 0},  {0, 20, 0}, {0, 19, 1},
	{0, 18, 2},  {0, 17, 3}, {0, 16, 4}, {0, 15, 5},  {0, 14, 6}, {0, 13, 7},  {0, 12, 8}, {0, 11, 9},
	{0, 10, 10}, {0, 9, 11}, {0, 8, 12}, {0, 7, 13},  {0, 6, 14}, {0, 5, 15},  {0, 4, 16}, {0, 3, 17},
	{0, 2, 18},  {0, 1, 19}, {0, 0, 20}, {0, 0, 20},  {1, 0, 19}, {2, 0, 18},  {3, 0, 17}, {4, 0, 16},
	{5, 0, 15},  {6, 0, 14}, {7, 0, 13}, {8, 0, 12},  {9, 0, 11}, {10, 0, 10}, {11, 0, 9}, {12, 0, 8},
	{13, 0, 7},  {14, 0, 6}, {15, 0, 5}, {16, 0, 4},  {17, 0, 3}, {18, 0, 2},  {19, 0, 1}, {19, 0, 1},
};




static const struct _pin qt1_slider_leds[] = QT1_XPRO_MC_PTC_SLIDER_LEDS;
static const struct _pin qt1_wheel_leds[]  = QT1_XPRO_MC_PTC_WHEEL_LEDS;
static const struct _pin qt1_button_leds[] = QT1_XPRO_MC_PTC_BUTTON_LEDS;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Configure LEDs
 *
 *  Configure LEDs: cleared by default
 */
static void qt1_xpro_mc_configure_leds(void)
{
	int led;
	for (led = 0; led < ARRAY_SIZE(qt1_slider_leds); ++led)
		pio_configure(&qt1_slider_leds[led], 1);

	for (led = 0; led < ARRAY_SIZE(qt1_wheel_leds); ++led)
		pio_configure(&qt1_wheel_leds[led], 1);

	for (led = 0; led < ARRAY_SIZE(qt1_button_leds); ++led)
		pio_configure(&qt1_button_leds[led], 1);
}

void qt1_xpro_mc_set_button_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_button_leds))
		return;
	pio_clear(&qt1_button_leds[led]);
}

void qt1_xpro_mc_clear_button_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_button_leds))
		return;
	pio_set(&qt1_button_leds[led]);
}

void qt1_xpro_mc_clear_wheel_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_wheel_leds))
		return;
	pio_set(&qt1_wheel_leds[led]);
}

void qt1_xpro_mc_set_wheel_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_wheel_leds))
		return;
	pio_clear(&qt1_wheel_leds[led]);
}

void qt1_xpro_mc_set_slider_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_slider_leds))
		return;
	pio_clear(&qt1_slider_leds[led]);
}

void qt1_xpro_mc_clear_slider_led(unsigned char led)
{
	if (led >= ARRAY_SIZE(qt1_slider_leds))
		return;
	pio_set(&qt1_slider_leds[led]);
}

void qt1_xpro_mc_init(void)
{
	int i;

	trace_info("Configure QT1 XPRO MutCap LEDs\r\n");
	qt1_xpro_mc_configure_leds();

	/* Set and clear leds to signal end of initialization */
	for (i = 0 ; i < 8 ; i++) {
		qt1_xpro_mc_set_slider_led(i);
		msleep(100);
	}
	for (i = 0 ; i < 8 ; i++)
		qt1_xpro_mc_clear_slider_led(i);
}

void qt1_xpro_mc_get_rgb_val(uint16_t i, uint8_t *rgbptr)
{
	rgbptr[0] = RGB_values[i][0];
	rgbptr[1] = RGB_values[i][1];
	rgbptr[2] = RGB_values[i][2];
}