/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

#include "audio/audio_device.h"
#include "chip.h"
#include "spi/spid.h"
#include "peripherals/bus.h"

/* =================== AD1934 spi interface definition =================== */

#define AD1934_BUS      1
#define AD1934_CS       1
#define AD1934_FREQ     10000 /* (value in KHz) */
#define AD1934_DLYBS    0
#define AD1934_DLYCT    0
#define AD1934_SPI_MODE SPID_MODE_0

static struct _bus_dev_cfg ad1934_dev_desc = {
	.bus = AD1934_BUS,
	.spi_dev = {
		.chip_select = AD1934_CS,
		.bitrate = AD1934_FREQ,
		.delay = {
			.bs = AD1934_DLYBS,
			.bct = AD1934_DLYCT,
		},
		.spi_mode = AD1934_SPI_MODE,
	},
};

static struct codec_desc ad1934_codec = {
	.type = AUDIO_CODEC_AD1934,
	/* codec control interface */
	.ad1934 = {
		.dev = &ad1934_dev_desc,
	},
};

/** Audio device instance*/
static struct _audio_desc audio_device = {
	.direction = AUDIO_DEVICE_PLAY,
	.type = AUDIO_DEVICE_SSC,
	.device = {
		.ssc = {
			.addr = SSC1,
			.desc = {
				.bit_rate = 0,
				/* Select TK pin as transmit and receive clock */
				.tx_cfg_cks_tk = true,
				.tx_start_selection = SSC_TCMR_START_TF_EDGE,
			},
			.codec = &ad1934_codec,
		},
	},
	.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
	/* walk around setting */
	.num_channels = AUDDSpeakerDriver_NUMCHANNELS / 2,
	.bits_per_sample = AUDDSpeakerDriver_BYTESPERSAMPLE * 8,
};

#endif /* ! __CONFIG_SAMA5D2_XPLAINED_H__ */
