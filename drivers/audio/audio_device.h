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

#include "peripherals/dma.h"
#include "peripherals/pio.h"

#if defined(CONFIG_HAVE_CLASSD)
#include "peripherals/classd.h"
#endif

#if defined(CONFIG_HAVE_PDMIC)
#include "peripherals/pdmic.h"
#endif

#if defined(CONFIG_HAVE_SSC)
#include "peripherals/ssc.h"
#ifdef CONFIG_HAVE_AUDIO_WM8904
#include "audio/wm8904.h"
#endif
#endif

#define AUDIO_PLAY_MAX_VOLUME    (100)
/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
typedef void (*audio_callback_t)(struct dma_channel *channel, void* args);

struct codec_desc {
	/* master clock supply pin */
	struct _pin* clk_pin;
	uint32_t clk_pin_size;

	/* codec control interface */
	struct _twi_desc* codec_twid;
	struct _pin* codec_twid_pin;
	uint32_t codec_twid_pin_size;
	uint8_t input_path;
};


enum audio_device_type {
#if defined(CONFIG_HAVE_CLASSD)
	AUDIO_DEVICE_CLASSD,
#endif
#if defined(CONFIG_HAVE_SSC)
	AUDIO_DEVICE_SSC,
#endif
#if defined(CONFIG_HAVE_PDMIC)
	AUDIO_DEVICE_PDMIC,
#endif
};

enum audio_device_direction {
	AUDIO_DEVICE_PLAY,
	AUDIO_DEVICE_RECORD,
};

struct _audio_desc {
	enum audio_device_direction direction;
	enum audio_device_type type;
	union {
#if defined(CONFIG_HAVE_CLASSD)
		struct {
			Classd *addr;
			struct _classd_desc desc;
		} classd;
#endif
#if defined(CONFIG_HAVE_SSC)
		struct {
			Ssc *addr;
			struct _ssc_desc desc;
			struct codec_desc* codec_chip; /* pointer to the codec*/
			uint8_t pck;
		} ssc;
#endif
#if defined(CONFIG_HAVE_PDMIC)
		struct {
			Pdmic *addr;
			struct _pdmic_desc desc;
		} pdmic;
#endif
	} device;
	struct {
		struct dma_channel *channel;
		struct dma_xfer_cfg cfg;
		bool configured;
	} dma;

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
/**
 * \brief Configure audio descriptor
 * \param desc     Audio descriptor
 */
extern void audio_configure(struct _audio_desc *desc);

/**
 * \brief Enable/Disable the audio channel
 * \param desc     Audio descriptor
 * \param enable   Enable/Disable the channel
 */
extern void audio_enable(struct _audio_desc *desc, bool enable);

/**
 * \brief Un/Mute the channel configured in the audio descriptor
 * \param desc     Audio descriptor
 * \param mute     Un/mute the audio channel
 */
extern void audio_play_mute(struct _audio_desc *desc, bool mute);

/**
 * \brief Set volume for specific audio descriptor
 * \param desc     Audio descriptor
 * \param vol      Volume level
 */
extern void audio_play_set_volume(struct _audio_desc *desc, uint8_t vol);

/**
 * \brief Audio stop DMA trasnfer
 * \param desc     Audio descriptor
 */
extern void audio_dma_stop(struct _audio_desc *desc);

/**
 * \brief Start the DMA trasnfer and 
 * \param desc     Audio descriptor
 * \param buffer   Data buffer (input/output according to configuration in descriptor)
 * \param size     Data buffer size
 * \param cb       Callback at end of DMA transfer
 */
extern void audio_dma_transfer(struct _audio_desc *desc, void *buffer, uint32_t size, audio_callback_t cb);

#endif /* AUDIO_DEVICE_API_H */
