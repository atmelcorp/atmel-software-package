#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

#include "audio/audio_device.h"
#include "peripherals/twid.h"



/** TWI clock */
#define TWI_CLOCK               (400000)

/** Twi instance*/
static struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfert_mode = TWID_MODE_POLLING
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
};

/** Audio device instance*/
static struct _audio_desc audio_device = {
	.type = AUDIO_DEVICE_SSC,
	.device = {
		.ssc = {
			.addr = SSC0,
			.codec_chip = &wm8904_codec,
		},
	},
	.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
	.num_channels = AUDDSpeakerDriver_NUMCHANNELS,
	.bits_per_sample = AUDDSpeakerDriver_BYTESPERSAMPLE * 8,
};



#endif
