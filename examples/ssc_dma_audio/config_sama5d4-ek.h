#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

#include "peripherals/twid.h"

/** TWI clock */
#define TWI_CLOCK               (400000)

/** Wav feature. */
#define SAMPLE_RATE             (48000)
#define SLOT_BY_FRAME           (1)
#define BITS_BY_SLOT            (16)

/** List of pins to configure. */
static const struct _pin pins_twi[] = PINS_TWI0;

static const struct _pin pins_clk[] = PIN_PCK2_ALT1; /* DAC Master Clock */

static uint32_t pck_index = 2;

static uint8_t input_path = WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN1R;

/** Twi instance*/
static struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfer_mode = TWID_MODE_POLLING
};

/** SSC instance*/
static struct _ssc_desc ssc_dev_desc = {
	.addr = SSC0,
	.bit_rate = 0,
	.sample_rate = SAMPLE_RATE,
	.slot_num = SLOT_BY_FRAME,
	.slot_length = BITS_BY_SLOT,
	/* Select TK pin as transmit and receive clock */
	.rx_cfg_cks_rk = false,
	.tx_cfg_cks_tk = true,
};

#endif
