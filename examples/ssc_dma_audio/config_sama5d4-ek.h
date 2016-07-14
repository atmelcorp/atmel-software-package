#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

#include "peripherals/twid.h"

/** TWI clock */
#define TWI_CLOCK               (400000)

/** List of pins to configure. */
static const struct _pin pins_twi[] = PINS_TWI0;

static const struct _pin pins_clk[] = PIN_PCK2_ALT1; /* DAC Master Clock */

static uint32_t pck_index = 2;

/** Twi instance*/
static struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfer_mode = TWID_MODE_POLLING
};

#endif
