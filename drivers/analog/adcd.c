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


#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "analog/adc.h"
#include "analog/adcd.h"
#include "dma/dma.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _adcd_dma_callback(void *arg, void* arg2)
{
	struct _adcd_desc* desc = (struct _adcd_desc*)arg;

	dma_reset_channel(desc->xfer.dma.channel);

	/* For read, invalidate region */
	cache_invalidate_region((uint32_t*)desc->xfer.buf->data, desc->xfer.buf->size);

	mutex_unlock(&desc->mutex);
	callback_call(&desc->xfer.callback, NULL);

	return 0;
}

static void _adcd_transfer_buffer_dma(struct _adcd_desc* desc)
{
	struct _dma_transfer_cfg cfg;
	struct _callback _cb;

	cfg.saddr = (void*)&ADC->ADC_LCDR;
	cfg.daddr = desc->xfer.buf->data;
	cfg.len = desc->xfer.buf->size / 2;

	dma_configure_transfer(desc->xfer.dma.channel, &desc->xfer.dma.cfg_dma, &cfg, 1);
	callback_set(&_cb, _adcd_dma_callback, desc);
	dma_set_callback(desc->xfer.dma.channel, &_cb);
	dma_start_transfer(desc->xfer.dma.channel);
}

/**
 * \brief Interrupt handler for the ADC.
 */
static void _adcd_handler(uint32_t source, void* user_arg)
{
	struct _adcd_desc* desc = (struct _adcd_desc*)user_arg;
	uint16_t* data = (uint16_t*)desc->xfer.buf->data;
	uint32_t mask = 1u << (31 - CLZ(desc->cfg.channel_mask));
	uint32_t status;
	int index = 0;
	int i;

	/* Get Interrupt Status (ISR) */
	status = adc_get_status();

	if (status & mask) {
		/* Read results */
		for (i = 0; i < adc_get_num_channels(); i++) {
			uint32_t chan_bit = 1u << i;
			if (desc->cfg.channel_mask & chan_bit) {
				uint32_t value = adc_get_converted_data(i);
				data[index++] = (i << ADC_LCDR_CHNB_Pos) | value;
			}
		}

		mutex_unlock(&desc->mutex);
		callback_call(&desc->xfer.callback, NULL);
	}
}

static void _adcd_transfer_buffer_polling(struct _adcd_desc* desc)
{
	/* Enable EOC interrupt for higher numbered channel */
	adc_disable_it(0xffffffffu);
	adc_get_status();
	adc_enable_it(1u << (31 - CLZ(desc->cfg.channel_mask)));
	irq_enable(ID_ADC);
}

/**
 * \brief (Re)Start ADC sample.
 * Initialize ADC, set clock and timing, set ADC to given mode.
 */
static void adcd_configure(struct _adcd_desc* desc)
{
	int i = 0;

	irq_disable(ID_ADC);

	desc->xfer.dma.cfg_dma.incr_saddr = false;
	desc->xfer.dma.cfg_dma.incr_daddr = true;
	desc->xfer.dma.cfg_dma.loop = false;
	desc->xfer.dma.cfg_dma.data_width = DMA_DATA_WIDTH_HALF_WORD;
	desc->xfer.dma.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	for (i = 0; i < adc_get_num_channels(); i++)
		adc_disable_channel(i);

	/* Disable sequencer */
	adc_set_sequence(0, 0);
	adc_set_sequence_mode(false);

	/* Set power save */
	if (desc->cfg.power_save_enabled)
		adc_set_sleep_mode(true);
	else
		adc_set_sleep_mode(false);

	/* Configure trigger mode */
	switch (desc->cfg.trigger_mode) {
		case TRIGGER_MODE_SOFTWARE:
			/* No trigger, only software trigger can start conversions */
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_NO_TRIGGER);
			break;

		case TRIGGER_MODE_ADTRG:
			/* Trigger on ADTRG pin */
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG0);
			break;

#ifdef ADC_MR_TRGSEL_ADC_TRIG1
		case TRIGGER_MODE_TIOA0 :
			/* Trigger on TC timer*/
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG1);
			break;
#endif /* ADC_MR_TRGSEL_ADC_TRIG1 */

#ifdef ADC_MR_TRGSEL_ADC_TRIG2
		case TRIGGER_MODE_TIOA1 :
			/* Trigger on TC timer*/
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG2);
			break;
#endif /* ADC_MR_TRGSEL_ADC_TRIG2 */

#ifdef ADC_MR_TRGSEL_ADC_TRIG3
		case TRIGGER_MODE_TIOA2 :
			/* Trigger on TC timer*/
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG3);
			break;
#endif /* ADC_MR_TRGSEL_ADC_TRIG3 */

#ifdef ADC_MR_TRGSEL_ADC_TRIG4
		case TRIGGER_MODE_PWM0 :
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG4);
			break;
#endif /* ADC_MR_TRGSEL_ADC_TRIG4 */

#ifdef ADC_MR_TRGSEL_ADC_TRIG5
		case TRIGGER_MODE_PWM1 :
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG5);
			break;
#endif /* ADC_MR_TRGSEL_ADC_TRIG5 */

		case TRIGGER_MODE_ADC_TIMER:
			/* Trigger on internal ADC timer */
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_PERIOD_TRIG);
			adc_set_trigger_period(250);
			break;
		default :
			break;
	}

	/* Configure trigger edge */
	if (desc->cfg.trigger_mode != TRIGGER_MODE_SOFTWARE &&
	    desc->cfg.trigger_mode != TRIGGER_MODE_ADC_TIMER) {
		switch (desc->cfg.trigger_edge) {
			case TRIGGER_EXT_TRIG_RISE:
				adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_RISE);
				break;
			case TRIGGER_EXT_TRIG_FALL:
				adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_FALL);
				break;
			case TRIGGER_EXT_TRIG_ANY:
				adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_ANY);
				break;
			case TRIGGER_PEN:
				adc_set_trigger_mode(ADC_TRGR_TRGMOD_PEN_TRIG);
				break;
			case TRIGGER_CONTINUOUS:
				adc_set_trigger_mode(ADC_TRGR_TRGMOD_CONTINUOUS);
				break;
			default:
				break;
		}
	}

	/* Enable channels, single mode */
	for (i = 0; i < adc_get_num_channels(); i++) {
		if (desc->cfg.channel_mask & (1u << i)) {
			adc_enable_channel(i);
#ifdef CONFIG_HAVE_ADC_DIFF_INPUT
			adc_disable_channel_differential_input(i);
#endif
		}
	}
}

/*----------------------------------------------------------------------------
 *        Public functions

 *----------------------------------------------------------------------------*/

void adcd_initialize(struct _adcd_desc* desc)
{
	/* Initialize ADC */
	adc_initialize();
	adc_set_ts_mode(0);

	/*
	 * Formula: ADCClock = MCK / ((PRESCAL+1) * 2)
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 *     ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
	/* Set ADC clock */
	adc_set_clock(desc->cfg.freq);

	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 * For example, ADC clock = 6MHz (166.7 ns)
	 *     Startup time = 512 / 6MHz = 85.3 us
	 *     Transfer Time = (1 * 2 + 3) / 6MHz = 833.3 ns
	 *     Tracking Time = (0 + 1) / 6MHz = 166.7 ns
	 *     Settling Time = 3 / 6MHz = 500 ns
	 */
	/* Set ADC timing */
	adc_set_timing(ADC_MR_STARTUP_SUT512, 0, 0);

	/* Enable channel number tag */
	adc_set_tag_enable(true);

	/* Configure IRQ handler */
	irq_add_handler(ID_ADC, _adcd_handler, desc);

	/* Allocate one DMA channel for receive data from ADC_LCDR */
	if (!desc->xfer.dma.channel)
		desc->xfer.dma.channel = dma_allocate_channel(ID_ADC, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.channel);
}

uint32_t adcd_transfer(struct _adcd_desc* desc, struct _buffer* buffer, struct _callback* cb)
{
	if (!mutex_try_lock(&desc->mutex))
		return ADCD_ERROR_LOCK;

	desc->xfer.buf = buffer;
	callback_copy(&desc->xfer.callback, cb);
	adcd_configure(desc);

	if(desc->cfg.dma_enabled)
		_adcd_transfer_buffer_dma(desc);
	else
		_adcd_transfer_buffer_polling(desc);

	return ADCD_SUCCESS;
}

bool adcd_is_busy(struct _adcd_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void adcd_wait_transfer(struct _adcd_desc* desc)
{
	while (adcd_is_busy(desc)) {
		if (desc->cfg.dma_enabled)
			dma_poll();
	}
}
