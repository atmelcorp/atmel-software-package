/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#ifndef TCD_H
#define TCD_H

/*------------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "io.h"
#include "callback.h"
#include "dma/dma.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

enum _tcd_transfer_mode
{
	TCD_TRANSFER_MODE_POLLING = 0,
	TCD_TRANSFER_MODE_DMA,
};

enum _tcd_mode
{
	TCD_MODE_COUNTER = 0,
	TCD_MODE_WAVEFORM,
	TCD_MODE_CAPTURE,
};

struct _tcd_desc {
	Tc* addr;
	uint8_t channel;
	enum _tcd_mode mode;
	mutex_t mutex;
	struct _callback callback;

	union {
		struct {
			uint32_t min_timer_freq;
			uint32_t frequency;
		} counter;
		struct {
			uint32_t min_timer_freq;
			uint32_t frequency;
			uint32_t duty_cycle;
		} waveform;
		struct {
			bool use_ext_clk;
			uint32_t ext_clk_sel;
			uint32_t frequency;
			enum _tcd_transfer_mode transfer_mode;
		} capture;
	} cfg;

	/* structure to hold data about current transfer */
	struct {
		struct _buffer buffer;
#ifdef CONFIG_HAVE_TC_DMA_MODE
		struct {
			struct _dma_channel* channel;
		} dma;
#endif
	} capture;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configure a timer in counter mode according to \frequency
 * \param min_timer_freq  Minimum frequency at which the timer will be configured
 * \param frequency       Trigger frequency of the counter
 * \return exact frequency at which the counter will trigger
 */
extern int tcd_configure_counter(
		struct _tcd_desc* desc,
		uint32_t min_timer_freq,
		uint32_t frequency);

/**
 * \brief Configure a timer as a waveform generator
 * \param min_timer_freq  Minimum frequency at which the timer will be configured
 * \param frequency       Frequency of the generated waveform
 * \param duty_cycle      Duty cycle of the generated waveform. It is given in unit: per mille.
 *                        For example 100% -> 1000, 50.1% -> 501, and so on.
 * \return exact frequency of the generated waveform
 */
extern int tcd_configure_waveform(
		struct _tcd_desc* desc,
		uint32_t min_timer_freq,
		uint32_t frequency,
		uint16_t duty_cycle);

/**
 * \brief Configure a timer to capture a signal
 * \param frequency   Frequency of the timer
 * \param buffer      Buffer to store captured samples
 * \return exact frequency at which the timer will increment
 */
extern int tcd_configure_capture(
		struct _tcd_desc* desc,
		uint32_t frequency,
		struct _buffer* buffer);

/**
 * \brief Start a configured timer and register the calback \cb
 * \param desc   TC driver descriptor
 * \param cb     Callback
 * \return 0 on succes
 */
extern int tcd_start(struct _tcd_desc* desc, struct _callback* cb);

/**
 * \brief Stop a running timer
 * \param desc   TC driver descriptor
 * \return 0 on succes
 */
extern int tcd_stop(struct _tcd_desc* desc);

/**
 * \brief Wait a TCD fo finish its current action
 * \param desc   TC driver descriptor
 */
extern void tcd_wait(struct _tcd_desc* desc);

#endif /* TCD_H */
