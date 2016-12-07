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


#include "irq/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/adcd.h"
#include "peripherals/adc.h"
#include "dma/dma.h"
#include "mm/cache.h"

#include "trace.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
volatile static bool single_transfer_ready;
static struct _adcd_desc* _adcd;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _adcd_dma_callback(struct dma_channel *channel, void *arg)
{
	struct _adcd_desc* desc = (struct _adcd_desc*)arg;

	/* For read, invalidate region */
	cache_invalidate_region((uint32_t*)desc->xfer.buf->data,
							desc->xfer.buf->size);
	mutex_unlock(&desc->mutex);
}

static void _adcd_transfer_buffer_dma(struct _adcd_desc* desc)
{
	struct dma_xfer_cfg cfg;

	adc_start_conversion();
	/* Allocate one DMA channel for writing message blocks to AES_IDATARx */
	desc->xfer.dma.channel = dma_allocate_channel(ID_ADC, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.channel);

	memset(&cfg, 0, sizeof(cfg));
	cfg.sa = (void*)&ADC->ADC_LCDR;
	cfg.da = (void *)(desc->xfer.buf->data);
	cfg.upd_sa_per_data = 0;
	cfg.upd_da_per_data = 1;
	cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
	cfg.chunk_size = DMA_CHUNK_SIZE_1;
	cfg.blk_size = 0;
	cfg.len = desc->xfer.buf->size;

	dma_configure_transfer(desc->xfer.dma.channel, &cfg);

	dma_set_callback(desc->xfer.dma.channel, _adcd_dma_callback, (void*)desc);
	dma_start_transfer(desc->xfer.dma.channel);

	adcd_wait_transfer(desc);
	dma_free_channel(desc->xfer.dma.channel);
	if (desc->xfer.callback)
		desc->xfer.callback(desc->xfer.cb_args);
}

/**
 * \brief Interrupt handler for the ADC.
 */
static void _adcd_handler(void)
{
	uint32_t status;
	uint8_t i;
	uint32_t value;

	/* Get Interrupt Status (ISR) */
	status = adc_get_status();

	adc_disable_it(0xFFFFFFFF);
	/* check at least one EOCn flag set */
	if(status & 0x00000FFF ) {
		for (i = 0; i < adc_get_num_channels(); i++) {
			value = adc_get_converted_data(i);
			/* Check ISR "End of Conversion" corresponding bit */
			if ((status & (1u << i))) {
				*(uint16_t *)(_adcd->xfer.buf->data + i * sizeof (uint16_t))
				= (i << ADC_LCDR_CHNB_Pos) | value;
			}
		}
	}
	single_transfer_ready = true;
}

static void _adcd_transfer_buffer_polling(struct _adcd_desc* desc)
{
	uint32_t i;
	uint32_t ier_mask = 0;
	uint8_t channels = desc->xfer.buf->size;

	single_transfer_ready = false;
	/* Enable Data ready interrupt */
	for (i = 0; i < channels; i++) {
		ier_mask |= 0x1u << desc->cfg.chan_sequence[i];
	}
	adc_enable_it(ier_mask) ;
	aic_enable(ID_ADC);
	adc_start_conversion();

	while(!single_transfer_ready);
	mutex_unlock(&desc->mutex);
	if (desc->xfer.callback)
		desc->xfer.callback(desc->xfer.cb_args);
}

/**
 * \brief (Re)Start ADC sample.
 * Initialize ADC, set clock and timing, set ADC to given mode.
 */
static void adcd_configure(struct _adcd_desc* desc)
{
	uint8_t i = 0;
	uint8_t channels = desc->xfer.buf->size;

	aic_disable(ID_ADC);

	for (i = 0; i < channels; i++)
		adc_disable_channel(desc->cfg.channel_used[i]);

	/* Enable/disable sequencer */
	if (desc->cfg.sequence_enabled) {
		/* Set user defined channel sequence */
		adc_set_sequence_by_list(desc->cfg.chan_sequence, channels);
		/* Enable sequencer */
		adc_set_sequence_mode(true);

	} else {
		adc_set_sequence(0, 0);
		/* Disable sequencer */
		adc_set_sequence_mode(false);
	}

	/* Set power save */
	if (desc->cfg.power_save_enabled) {
		adc_set_sleep_mode(true);
	} else {
		adc_set_sleep_mode(false);
	}

	/* Configure trigger mode and start convention */
	switch (desc->cfg.trigger_mode) {
		case TRIGGER_MODE_SOFTWARE:
			/* No trigger, only software trigger can start conversions */
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG0);
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

		case TRIGGER_MODE_ADC_TIMER :
			/* Trigger on internal ADC timer */
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG0);
			adc_set_trigger_period(250);
			break;
		default :
			break;
	}
	adc_set_trigger_mode(desc->cfg.trigger_edge);

		/* Enable channels, gain, single mode */
	for (i = 0; i < channels; i++) {
		adc_enable_channel(desc->cfg.channel_used[i]);
#ifdef CONFIG_HAVE_ADC_INPUT_OFFSET
		adc_disable_channel_differential_input(desc->cfg.chan_sequence[i]);
#endif
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
	adc_set_clock(desc->cfg.ferq);

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

	aic_set_source_vector(ID_ADC, _adcd_handler);
	_adcd = desc;
}

uint32_t adcd_transfer(struct _adcd_desc* desc, struct _buffer* buffer,
						adcd_callback_t cb, void* user_args)
{
	if (!mutex_try_lock(&desc->mutex)) {
		return ADCD_ERROR_LOCK;
	}

	desc->xfer.buf = buffer;
	desc->xfer.callback = cb;
	desc->xfer.cb_args = user_args;
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
		if(desc->cfg.dma_enabled)
			dma_poll();
	}
}
