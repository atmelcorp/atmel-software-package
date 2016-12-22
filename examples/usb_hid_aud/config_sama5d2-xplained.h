#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"

/** Audio device instance*/
static struct _audio_desc audio_device = {
	.direction = AUDIO_DEVICE_PLAY,
	.type = AUDIO_DEVICE_CLASSD,
	.device = {
		.classd = {
			.addr = BOARD_CLASSD0_ADDR,
			.desc = {
				.transfer_mode = CLASSD_MODE_DMA,
				.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
				.mode = BOARD_CLASSD0_MODE,
				.non_ovr = CLASSD_NONOVR_10NS,
				.mono = BOARD_CLASSD0_MONO,
				.mono_mode = BOARD_CLASSD0_MONO_MODE
			},
		},
	},
	.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
	.num_channels = AUDDSpeakerDriver_NUMCHANNELS,
	.bits_per_sample = AUDDSpeakerDriver_BYTESPERSAMPLE * 8,
};

#endif
