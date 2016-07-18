#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

#include "audio/audio_device.h"
#include "audio/wm8904.h"
#include "peripherals/twid.h"

/** TWI clock */
#define TWI_CLOCK               (400000)

/** Twi instance*/
static struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfer_mode = TWID_MODE_POLLING
};

/** List of pins to configure. */
static struct _pin  pins_clk[] = PIN_PCK2_ALT1;

static struct _pin  pins_twi[] = PINS_TWI0;

static struct codec_desc wm8904_codec = {
	/* master clock supply pin */
	.clk_pin = pins_clk,
	.clk_pin_size = ARRAY_SIZE(pins_clk),
	
	/* codec control interface */
	.codec_twid = &wm8904_twid,
	.codec_twid_pin = pins_twi,
	.codec_twid_pin_size = ARRAY_SIZE(pins_twi),

	.input_path = WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN1R,
};

/** Audio device instance*/
static struct _audio_desc audio_play_device = {
	.direction = AUDIO_DEVICE_PLAY,
	.type = AUDIO_DEVICE_SSC,
	.device = {
		.ssc = {
			.addr = SSC0,
			.desc = {
				.bit_rate = 0,
				/* Select TK pin as transmit and receive clock */
				.rx_cfg_cks_rk = false,
				.tx_cfg_cks_tk = true,
			},
			.codec_chip = &wm8904_codec,
			.pck = 2,
		},
	},
	.dma = {
		.configured = false,
	},
	.sample_rate = 48000,
	.num_channels = 1,
	.bits_per_sample = 16,
};

static struct _audio_desc audio_record_device = {
	.direction = AUDIO_DEVICE_RECORD,
	.type = AUDIO_DEVICE_SSC,
	.device = {
		.ssc = {
			.addr = SSC0,
			.desc = {
				.bit_rate = 0,
				/* Select TK pin as transmit and receive clock */
				.rx_cfg_cks_rk = false,
				.tx_cfg_cks_tk = true,
			},
			.codec_chip = &wm8904_codec,
			.pck = 2,
		},
	},
	.dma = {
		.configured = false,
	},
	.sample_rate = 48000,
	.num_channels = 1,
	.bits_per_sample = 16,
};
 
#endif
