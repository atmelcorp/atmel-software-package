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

#if defined(CONFIG_HAVE_CLASSD)
#include "audio/classd.h"
#endif

#if defined(CONFIG_HAVE_PDMIC)
#include "audio/pdmic.h"
#endif

#if defined(CONFIG_HAVE_SSC)
#include "audio/ssc.h"
#ifdef CONFIG_HAVE_AUDIO_WM8904
#include "audio/wm8904.h"
#endif
#ifdef CONFIG_HAVE_AUDIO_WM8731
#include "audio/wm8731.h"
#endif
#ifdef CONFIG_HAVE_AUDIO_AD1934
#include "audio/ad1934.h"
#endif
#endif /* CONFIG_HAVE_SSC */
#include "callback.h"
#include "dma/dma.h"
#include "gpio/pio.h"

#define AUDIO_PLAY_MAX_VOLUME    (100)

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

enum audio_codec_type {
	AUDIO_CODEC_NONE,
#if defined(CONFIG_HAVE_SSC)
#if defined(CONFIG_HAVE_AUDIO_WM8904)
	AUDIO_CODEC_WM8904,
#endif
#if defined(CONFIG_HAVE_AUDIO_WM8731)
	AUDIO_CODEC_WM8731,
#endif
#if defined(CONFIG_HAVE_AUDIO_AD1934)
	AUDIO_CODEC_AD1934,
#endif
#endif /* CONFIG_HAVE_SSC */
};

/* codec control interface */
struct codec_desc {
	enum audio_codec_type type;
	union {
		uint8_t dummy; /* avoid an error with IAR compiler */
#if defined(CONFIG_HAVE_SSC)
#if defined(CONFIG_HAVE_AUDIO_WM8904)
		struct _wm8904_desc wm8904;
#endif
#if defined(CONFIG_HAVE_AUDIO_WM8731)
		struct _wm8731_desc wm8731;
#endif
#if defined(CONFIG_HAVE_AUDIO_AD1934)
		struct _ad1934_desc ad1934;
#endif
#endif /* CONFIG_HAVE_SSC */
	};
};

enum audio_device_type {
	AUDIO_DEVICE_NONE, /* avoid an error with IAR compiler */
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
		uint32_t dummy; /* avoid an error with IAR compiler */
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
			struct codec_desc* codec;
		} ssc;
#endif
#if defined(CONFIG_HAVE_PDMIC)
		struct {
			Pdmic *addr;
			struct _pdmic_desc desc;
		} pdmic;
#endif
	} device;
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
extern void audio_mute(struct _audio_desc *desc, bool mute);

/**
 * \brief Set volume for specific audio descriptor
 * \param desc     Audio descriptor
 * \param vol      Volume level
 */
extern void audio_set_volume(struct _audio_desc *desc, uint8_t vol);

/**
 * \brief Stop audio transfer
 * \param desc     Audio descriptor
 */
extern void audio_stop(struct _audio_desc *desc);

/**
 * \brief Configure and start audio transfer
 * \param desc     Audio descriptor
 * \param buffer   Data buffer (input/output according to configuration in descriptor)
 * \param size     Data buffer size
 * \param cb       Callback at end of DMA transfer
 */
extern void audio_transfer(struct _audio_desc *desc, void *buffer, uint32_t size, struct _callback* cb);

/**
 * \brief Check the audio transfer status
 * \param desc     Audio descriptor
 */
extern bool audio_transfer_is_done(struct _audio_desc *desc);

/**
 * \brief Increase or decrease CODEC clock
 * \param desc     Audio descriptor
 * \param adjust   faster or slower the speed of codec
 */
extern void audio_sync_adjust(struct _audio_desc *desc, int32_t adjust);

#endif /* AUDIO_DEVICE_API_H */
