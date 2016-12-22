#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"

/** Audio play device instance*/
static struct _audio_desc audio_play_device = {
	.direction = AUDIO_DEVICE_PLAY,
	.type = AUDIO_DEVICE_CLASSD,
	.device = {
		.classd = {
			.addr = BOARD_CLASSD0_ADDR,
			.desc = {
				.transfer_mode = CLASSD_MODE_DMA,
				.sample_rate = 48000,
				.mode = BOARD_CLASSD0_MODE,
				.non_ovr = CLASSD_NONOVR_10NS,
				.mono = BOARD_CLASSD0_MONO,
				.mono_mode = BOARD_CLASSD0_MONO_MODE
			},
		},
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
			.addr = BOARD_PDMIC0_ADDR,
			.desc = {
				.dsp_osr = PDMIC_OVER_SAMPLING_RATIO_64,
				.dsp_hpfbyp = PDMIC_DSP_HIGH_PASS_FILTER_ON,
				.dsp_sinbyp = PDMIC_DSP_SINCC_PASS_FILTER_ON,
				/* while shift = 0 offset = 0
				 * dgain = 100 scale = 0, gain = 40(dB)
				 */
				.dsp_shift = 0,
				.dsp_offset = 0,
				.dsp_dgain = 100,
				.dsp_scale = 0,
			},
		},
	},
	.sample_rate = 48000,
	.num_channels = 1,
	.bits_per_sample = 16,
};


#endif
