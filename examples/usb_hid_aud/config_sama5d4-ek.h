/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

#include "audio/audio_device.h"
#include "audio/wm8904.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"

/** List of pins to configure. */
static struct _pin  pins_twi[] = PINS_TWI0;

static struct codec_desc wm8904_codec = {
	/* codec control interface */
	.wm8904 = {
		.twi = {
			.twid = {
				.addr = TWI0,
				.freq = 400000,
				.transfer_mode = TWID_MODE_POLLING
			},
		},
		.input_path = WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN1R,
		.mclk_pck = 2,
		.mclk_pck_src = PMC_PCK_CSS_SLOW_CLK,
		.mclk_pin = PIN_PCK2_ALT1,
	},
	.codec_twid_pin = pins_twi,
	.codec_twid_pin_size = ARRAY_SIZE(pins_twi),
};

/** Audio device instance*/
static struct _audio_desc audio_device = {
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
		},
	},
	.dma = {
		.configured = false,
	},
	.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
	.num_channels = AUDDSpeakerDriver_NUMCHANNELS,
	.bits_per_sample = AUDDSpeakerDriver_BYTESPERSAMPLE * 8,
};

#endif
