#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"

/** Audio play device instance*/
static struct _audio_desc audio_play_device = {
	.direction = AUDIO_DEVICE_PLAY,
	.type = AUDIO_DEVICE_CLASSD,
	.device = {
		.classd = {
			.addr = CLASSD,
		},
	},
	.dma = {
		.configured = false,
	},
	.sample_rate = 48000,
	.num_channels = 1,
	.bits_per_sample = 16,
};

/** Audio recoder device instance*/
static struct _audio_desc audio_record_device = {
	.direction = AUDIO_DEVICE_RECORD,
	.type = AUDIO_DEVICE_PDMIC,
	.device = {
		.pdmic = {
			.addr = PDMIC,
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
