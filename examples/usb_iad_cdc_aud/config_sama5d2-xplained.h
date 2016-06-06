#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"

/** Audio device instance*/
static struct _audio_desc audio_device = {
	.type = AUDIO_DEVICE_CLASSD,
	.device = {
		.classd = {
			.addr = CLASSD,
		},
	},
	.sample_rate = AUDDevice_SAMPLERATE,
	.num_channels = AUDDevice_NUMCHANNELS,
	.bits_per_sample = AUDDevice_BYTESPERSAMPLE * 8,
};

#endif
