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

#ifndef CONFIG_SAM9XX5_EK_H_
#define CONFIG_SAM9XX5_EK_H_

#include "audio/audio_device.h"
#include "audio/wm8731.h"
#include "peripherals/pmc.h"
#include "board.h"

static struct codec_desc wm8731_codec = {
	/* codec control interface */
	.type = AUDIO_CODEC_WM8731,
	.wm8731 = {
		.twi = {
			.bus = BOARD_WM8731_TWI_BUS,
			.addr = BOARD_WM8731_SLAVE_ADDR,
		},
		//.input_path = BOARD_WM8731_INPUT_PATH,
		.mclk_pck = BOARD_WM8731_MCLK_PCK,
		.mclk_pck_src = BOARD_WM8731_MCLK_PCK_SRC,
		.mclk_pin = BOARD_WM8731_MCLK_PIN,
	},
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
				.tx_cfg_cks_tk = true,
				.tx_start_selection = SSC_TCMR_START_TF_EDGE,
			},
			.codec = &wm8731_codec,
		},
	},
	.num_channels = AUDDevice_NUMCHANNELS,
	.bits_per_sample = AUDDevice_BYTESPERSAMPLE * 8,
};

#endif /* CONFIG_SAM9XX5_EK_H_ */
