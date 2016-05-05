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

#ifndef AUDIO_DEVICE_API_H
#define AUDIO_DEVICE_API_H

#include "peripherals/xdmad.h"
#include "peripherals/pio.h"


/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
typedef void (*audio_callback_t)(struct _xdmad_channel *channel, void* args);

struct codec_desc {
	/* master clock supply pin */
	struct _pin* clk_pin;
	uint32_t clk_pin_size;

	/* codec control interface */
	struct _twi_desc* codec_twid;
	struct _pin* codec_twid_pin;
	uint32_t codec_twid_pin_size;
};


enum audio_device_type {
#if defined(CONFIG_HAVE_CLASSD)
	AUDIO_DEVICE_CLASSD,
#endif
#if defined(CONFIG_HAVE_SSC)
	AUDIO_DEVICE_SSC,
#endif
};

struct _audio_desc {
	enum audio_device_type type;
	union {
#if defined(CONFIG_HAVE_CLASSD)
		struct {
			Classd *addr;
		} classd;
#endif
#if defined(CONFIG_HAVE_SSC)
		struct {
			Ssc *addr;
			/* pointer to the codec*/
			struct codec_desc* codec_chip;
		} ssc;
#endif
	} device;

	struct _pin* audio_pin;
	uint32_t audio_pin_size;
	/* Sample Frequency (fs) Ratio */
	uint32_t sample_rate;
	/* Mono = 1, Stereo = 2, etc. */
	uint16_t num_channels;
	/* 8 bits = 8, 16 bits = 16, etc. */
	uint16_t bits_per_sample;
};


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
extern void audio_play_configure(struct _audio_desc *desc);
extern void audio_play_enable(struct _audio_desc *desc, bool enable);
extern void audio_play_mute(struct _audio_desc *desc, bool mute);
extern void audio_play_stop(struct _audio_desc *desc);
extern void audio_dma_transfer(struct _audio_desc *desc, void *buffer,
									uint16_t size, audio_callback_t cb);

#endif /* AUDIO_DEVICE_API_H */
