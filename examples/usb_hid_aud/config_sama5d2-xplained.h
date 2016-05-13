#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"

/** List of pins to configure. */
static  struct _pin  pins_audio[] = BOARD_CLASSD_PINS;

/** Audio device instance*/
static struct _audio_desc audio_device = {
	.type = AUDIO_DEVICE_CLASSD,
	.device = {
		.classd = {
			.addr = CLASSD,
		},
	},
	.audio_pin = pins_audio,
	.audio_pin_size = ARRAY_SIZE(pins_audio),
	.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
	.num_channels = AUDDSpeakerDriver_NUMCHANNELS,
	.bits_per_sample = AUDDSpeakerDriver_BYTESPERSAMPLE * 8,
};

#endif
