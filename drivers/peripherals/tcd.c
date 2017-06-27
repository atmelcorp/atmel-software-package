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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "dma/dma.h"
#include "errno.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/tcd.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_TC_DMA_MODE
static int _tcd_dma_transfer_callback(void* args, void* arg2)
{
	struct _tcd_desc* desc = (struct _tcd_desc *)args;

	cache_invalidate_region((uint32_t*)desc->capture.buffer.data, desc->capture.buffer.size);

	dma_reset_channel(desc->capture.dma.channel);
	mutex_unlock(&desc->mutex);

	return callback_call(&desc->callback, NULL);
}
#endif

/**
 * \brief Interrupt handler for the TC capture.
 */
static void _tcd_counter_handler(uint32_t source, void* user_arg)
{
	struct _tcd_desc* desc = (struct _tcd_desc *)user_arg;
	uint32_t status = tc_get_status(desc->addr, desc->channel);

	if (desc->mode == TCD_MODE_COUNTER)
		if ((status & TC_SR_CPCS) == TC_SR_CPCS)
			callback_call(&desc->callback, NULL);
}

#ifdef CONFIG_HAVE_TC_DMA_MODE
static int _tcd_capture_dma(struct _tcd_desc* desc)
{
	struct _dma_transfer_cfg cfg;
	struct _dma_cfg cfg_dma;
	struct _callback _cb;

	memset(&cfg_dma, 0, sizeof(cfg_dma));
	cfg_dma.incr_saddr = false;
	cfg_dma.incr_daddr = true;
	cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
	cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	memset(&cfg, 0, sizeof(cfg));
	cfg.saddr = (uint32_t*)&(desc->addr->TC_CHANNEL[desc->channel].TC_RAB);
	cfg.daddr = desc->capture.buffer.data;
	cfg.len = desc->capture.buffer.size / sizeof(uint32_t);
	dma_configure_transfer(desc->capture.dma.channel, &cfg_dma, &cfg, 1);

	callback_set(&_cb, _tcd_dma_transfer_callback, (void*)desc);
	dma_set_callback(desc->capture.dma.channel, &_cb);

	tc_get_status(desc->addr, desc->channel);
	tc_start(desc->addr, desc->channel);

	dma_start_transfer(desc->capture.dma.channel);

	return -EAGAIN;
}
#endif

static int _tcd_capture_polling(struct _tcd_desc* desc)
{
	uint32_t i;
	uint32_t* rab_data = (uint32_t*)desc->capture.buffer.data;

	tc_start(desc->addr, desc->channel);
	for (i = 0; i < desc->capture.buffer.size / sizeof(uint32_t); i += 2) {
		while ((tc_get_status(desc->addr, desc->channel) & TC_SR_LDRBS) != TC_SR_LDRBS);
		tc_get_ra_rb_rc(desc->addr, desc->channel, &rab_data[i], &rab_data[i + 1], 0);
	}
	tc_stop(desc->addr, desc->channel);

	mutex_unlock(&desc->mutex);

	return callback_call(&desc->callback, NULL);
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

int tcd_configure_counter(struct _tcd_desc* desc, uint32_t min_timer_freq, uint32_t frequency)
{
	uint32_t tc_id = get_tc_id_from_addr(desc->addr, desc->channel);
	uint32_t tc_clks, config, rc, chan_freq;

	desc->mutex = 0;
	desc->mode = TCD_MODE_COUNTER;
	callback_set(&desc->callback, NULL, NULL);
	desc->cfg.counter.min_timer_freq = min_timer_freq;
	desc->cfg.counter.frequency = frequency;

	if (!pmc_is_peripheral_enabled(tc_id))
		pmc_configure_peripheral(tc_id, NULL, true);

	if (min_timer_freq < frequency)
		min_timer_freq = frequency;

	tc_clks = tc_find_best_clock_source(desc->addr, desc->channel, min_timer_freq);
	config = tc_clks | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;
	tc_configure(desc->addr, desc->channel, config);
	chan_freq = tc_get_channel_freq(desc->addr, desc->channel);

	rc = chan_freq / frequency;
	tc_set_ra_rb_rc(desc->addr, desc->channel, NULL, NULL, &rc);

	return chan_freq / rc;
}

int tcd_configure_waveform(struct _tcd_desc* desc, uint32_t min_timer_freq, uint32_t frequency, uint16_t duty_cycle)
{
	uint32_t tc_id = get_tc_id_from_addr(desc->addr, desc->channel);
	uint32_t tc_clks, config, ra, rc, duty, chan_freq;

	if (duty_cycle > 1000)
		return -EINVAL;

	desc->mutex = 0;
	desc->mode = TCD_MODE_WAVEFORM;
	callback_set(&desc->callback, NULL, NULL);
	desc->cfg.waveform.min_timer_freq = min_timer_freq;
	desc->cfg.waveform.frequency = frequency;
	desc->cfg.waveform.duty_cycle = duty_cycle;
	
	if (!pmc_is_peripheral_enabled(tc_id))
		pmc_configure_peripheral(tc_id, NULL, true);

	if (min_timer_freq < frequency)
		min_timer_freq = frequency;

	tc_clks = tc_find_best_clock_source(desc->addr, desc->channel, min_timer_freq);
	config = tc_clks | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET | TC_CMR_ASWTRG_SET;
	tc_configure(desc->addr, desc->channel, config);
	chan_freq = tc_get_channel_freq(desc->addr, desc->channel);

	rc = chan_freq / frequency;
	duty = ((uint64_t)duty_cycle * ((1ull << TC_CHANNEL_SIZE) - 1)) / 1000;
	ra = (uint32_t)(((uint64_t)duty * rc + (1ull << (TC_CHANNEL_SIZE - 1))) >> TC_CHANNEL_SIZE);
	tc_set_ra_rb_rc(desc->addr, desc->channel, &ra, NULL, &rc);

	return chan_freq / rc;
}

int tcd_configure_capture(struct _tcd_desc* desc, uint32_t frequency, struct _buffer* buffer)
{
	uint32_t tc_id = get_tc_id_from_addr(desc->addr, desc->channel);
	uint32_t tc_clks, config, chan_freq;

	desc->mutex = 0;
	desc->mode = TCD_MODE_CAPTURE;
	callback_set(&desc->callback, NULL, NULL);
	desc->cfg.capture.frequency = frequency;
	desc->capture.buffer.data = buffer->data;
	desc->capture.buffer.size = buffer->size;

#ifdef CONFIG_HAVE_TC_DMA_MODE
	/* Allocate one DMA channel for TC capture */
	desc->capture.dma.channel = dma_allocate_channel(tc_id, DMA_PERIPH_MEMORY);
	assert(desc->capture.dma.channel);
#endif

	if (!pmc_is_peripheral_enabled(tc_id))
		pmc_configure_peripheral(tc_id, NULL, true);
	if (desc->cfg.capture.use_ext_clk) {
		config = desc->cfg.capture.ext_clk_sel | TC_CMR_LDRA_RISING |
		         TC_CMR_LDRB_FALLING | TC_CMR_ABETRG | TC_CMR_ETRGEDG_FALLING;
	}
	else {
		tc_clks = tc_find_best_clock_source(desc->addr, desc->channel, frequency);
		config = tc_clks | TC_CMR_LDRA_RISING | TC_CMR_LDRB_FALLING | TC_CMR_ABETRG | TC_CMR_ETRGEDG_FALLING;
	}
	tc_configure(desc->addr, desc->channel, config);
	if (desc->cfg.capture.use_ext_clk)
		chan_freq = frequency;
	else
		chan_freq = tc_get_channel_freq(desc->addr, desc->channel);
	return chan_freq;
}

int tcd_start(struct _tcd_desc* desc, struct _callback* cb)
{
	uint32_t tc_id = get_tc_id_from_addr(desc->addr, desc->channel);

	if (!mutex_try_lock(&desc->mutex))
		return -EBUSY;

	callback_copy(&desc->callback, cb);

	switch (desc->mode) {
	case TCD_MODE_COUNTER:
		irq_add_handler(tc_id, _tcd_counter_handler, (void*)desc);
		irq_enable(tc_id);
		tc_enable_it(desc->addr, desc->channel, TC_IER_CPCS);
		tc_start(desc->addr, desc->channel);
		break;
	case TCD_MODE_WAVEFORM:
		tc_start(desc->addr, desc->channel);
		break;
	case TCD_MODE_CAPTURE:
		switch (desc->cfg.capture.transfer_mode) {
		case TCD_TRANSFER_MODE_POLLING:
			_tcd_capture_polling(desc);
			break;
#ifdef CONFIG_HAVE_TC_DMA_MODE
		case TCD_TRANSFER_MODE_DMA:
			_tcd_capture_dma(desc);
			break;
#endif
		default:
			return -EINVAL;
		}
		break;
	default:
		return -ENOTSUP;
	}

	return 0;
}

int tcd_stop(struct _tcd_desc* desc)
{
	tc_stop(desc->addr, desc->channel);
	if (mutex_is_locked(&desc->mutex))
		mutex_unlock(&desc->mutex);

	return 0;
}

void tcd_wait(struct _tcd_desc* desc)
{
	while (mutex_is_locked(&desc->mutex)) {
#ifdef CONFIG_HAVE_TC_DMA_MODE
		if (desc->mode == TCD_MODE_CAPTURE){
			if (desc->cfg.capture.transfer_mode == TCD_TRANSFER_MODE_DMA)
				dma_poll();
		}
#endif
	}
}
