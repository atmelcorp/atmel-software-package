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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "trace.h"

#include "peripherals/aic.h"
#include "peripherals/pdmic.h"
#include "peripherals/pmc.h"
#include "peripherals/dma.h"

#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct dma_channel *pdmic_dma_channel;

static uint8_t pdmic_dsp_size = PDMIC_DSPR0_SIZE_16;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void pdmic_enable(void)
{
	pmc_enable_gck(ID_PDMIC);
	pmc_enable_peripheral(ID_PDMIC);
	/* Enable the overrun error interrupt */
	PDMIC->PDMIC_IER |= PDMIC_IER_OVRE;
}


void pdmic_disable(void)
{
	/* Disable the overrun error interrupt */
	PDMIC->PDMIC_IDR |= PDMIC_IDR_OVRE;
	pmc_disable_gck(ID_PDMIC);
	pmc_disable_peripheral(ID_PDMIC);
}


bool pdmic_configure(struct _pdmic_desc *desc)
{
	uint32_t mr_val;
	uint32_t dspr0_val, dspr1_val;
	uint32_t pclk_rate, gclk_rate;
	uint32_t pclk_prescal, gclk_prescal;
	uint32_t f_pdmic;

	PDMIC -> PDMIC_CR = PDMIC_CR_SWRST;

	if (desc->channels != 1) {
		trace_error("only supports one channel\n");
		return false;
	}

	switch (desc->dsp_size) {
	case PDMIC_CONVERTED_DATA_SIZE_16:
		dspr0_val = PDMIC_DSPR0_SIZE_16;
		pdmic_dsp_size = PDMIC_DSPR0_SIZE_16;
		break;

	case PDMIC_CONVERTED_DATA_SIZE_32:
		dspr0_val = PDMIC_DSPR0_SIZE_32;
		pdmic_dsp_size = PDMIC_DSPR0_SIZE_32;
		break;

	default:
		return false;
	}

	switch (desc->dsp_osr) {
	case PDMIC_OVER_SAMPLING_RATIO_64:
		dspr0_val |= PDMIC_DSPR0_OSR(1);
		break;

	case PDMIC_OVER_SAMPLING_RATIO_128:
		dspr0_val |= PDMIC_DSPR0_OSR(0);
		break;

	default:
		return false;
	}

	switch (desc->dsp_hpfbyp) {
	case PDMIC_DSP_HIGH_PASS_FILTER_ON:
		dspr0_val &= ~PDMIC_DSPR0_HPFBYP;
		break;

	case PDMIC_DSP_HIGH_PASS_FILTER_OFF:
		dspr0_val |= PDMIC_DSPR0_HPFBYP;
		break;

	default:
		return false;
	}

	switch (desc->dsp_sinbyp) {
	case PDMIC_DSP_SINCC_PASS_FILTER_ON:
		dspr0_val &= ~PDMIC_DSPR0_SINBYP;
		break;

	case PDMIC_DSP_SINCC_PASS_FILTER_OFF:
		dspr0_val |= PDMIC_DSPR0_SINBYP;
		break;

	default:
		return false;
	}

	if (desc->dsp_shift < PDMIC_DSPR_SHIFT_MAX_VAL)
		dspr0_val |= PDMIC_DSPR0_SHIFT(desc->dsp_shift);
	else
		return false;

	if (desc->dsp_scale < PDMIC_DSPR_SCALE_MAX_VAL)
		dspr0_val |= PDMIC_DSPR0_SCALE(desc->dsp_scale);
	else
		return false;

	dspr1_val = PDMIC_DSPR1_OFFSET(desc->dsp_offset);

	if (desc->dsp_dgain < PDMIC_DSPR_DGAIN_MAX_VAL)
		dspr1_val |= PDMIC_DSPR1_DGAIN(desc->dsp_dgain);
	else
		return false;

	PDMIC->PDMIC_DSPR0 = dspr0_val;
	PDMIC->PDMIC_DSPR1 = dspr1_val;

	f_pdmic = (desc->sample_rate * desc->dsp_osr);

	pclk_rate = pmc_get_peripheral_clock(ID_PDMIC);
	gclk_rate = pmc_get_gck_clock(ID_PDMIC);

	/* PRESCAL = SELCK/(2*f_pdmic) - 1*/
	pclk_prescal = (uint32_t)(pclk_rate / (f_pdmic << 1)) - 1;
	gclk_prescal = (uint32_t)(gclk_rate / (f_pdmic << 1)) - 1;

	if (pclk_prescal < PDMIC_MR_PRESCAL_MAX_VAL) {
		mr_val = PDMIC_MR_PRESCAL(pclk_prescal) | PDMIC_MR_CLKS_PCLK;
	} else if (gclk_prescal < PDMIC_MR_PRESCAL_MAX_VAL) {
		mr_val = PDMIC_MR_PRESCAL(gclk_prescal) | PDMIC_MR_CLKS_GCLK;
	} else {
		trace_error("PDMIC Prescal configure error");
		return false;
	}

	/* write configuration */
	PDMIC->PDMIC_MR = mr_val;

	return true;
}


bool pdmic_set_gain(uint16_t dgain, uint8_t scale)
{
	uint32_t dspr0_scale, dspr1_dgain;

	if (dgain < PDMIC_DSPR_DGAIN_MAX_VAL &&
			scale < PDMIC_DSPR_SCALE_MAX_VAL) {
		dspr0_scale = PDMIC_DSPR0_SCALE(scale);
		dspr1_dgain = PDMIC_DSPR1_DGAIN(dgain);

		PDMIC->PDMIC_DSPR0 &= ~PDMIC_DSPR0_SCALE_Msk;
		PDMIC->PDMIC_DSPR1 &= ~PDMIC_DSPR1_DGAIN_Msk;

		PDMIC->PDMIC_DSPR0 |= dspr0_scale;
		PDMIC->PDMIC_DSPR1 |= dspr1_dgain;

		return true;
	}

	return false;
}

void pdmic_stream_convert(bool flag)
{
	if (flag)
		PDMIC->PDMIC_CR |= PDMIC_CR_ENPDM;
	else
		PDMIC->PDMIC_CR &= ~PDMIC_CR_ENPDM;
}

/**
 * \brief Pdmic DMA channel initialize
 */
static void pdmic_dma_init(void)
{
	/* Allocate DMA TX channels for pdmic */
	pdmic_dma_channel = dma_allocate_channel(ID_PDMIC, DMA_PERIPH_MEMORY);

	if (!pdmic_dma_channel) {
		trace_info("PDMIC DMA channel allocation error\n\r");
	}
}


bool pdmic_init(struct _pdmic_desc *desc)
{
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
	uint32_t pclk, gclk;
	pclk = pmc_get_peripheral_clock(ID_PDMIC);
	trace_debug("-- PDMIC PCLK: %uMHz --\n\r", (unsigned)(pclk / 1000000));
#endif

	/* The gclk clock frequency must always be three times
	 * lower than the pclk clock frequency
	 */
	pmc_configure_gck(ID_PDMIC, PMC_PCR_GCKCSS_PLLA_CLK, 18 - 1);

#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
	gclk = pmc_get_gck_clock(ID_PDMIC);
	trace_debug("-- PDMIC GCLK: %uMHz --\n\r", (unsigned)(gclk / 1000000));
#endif

	pdmic_dma_init();
	pdmic_enable();

	return pdmic_configure(desc);
}

bool pdmic_data_ready(void)
{
	return (PDMIC->PDMIC_ISR & PDMIC_ISR_DRDY) == PDMIC_ISR_DRDY;
}

void pdmic_dma_transfer(void *buffer, uint32_t size,
		dma_callback_t callback, void *user_arg)
{
	struct dma_xfer_cfg cfg;
	/* Configure PDMIC DMA transfer */
	
	cfg.sa = (void *)&PDMIC->PDMIC_CDR;
	cfg.da = buffer;
	cfg.upd_sa_per_data = 0;
	cfg.upd_da_per_data = 1;
	cfg.blk_size = 0;
	cfg.chunk_size = DMA_CHUNK_SIZE_1;

	if (pdmic_dsp_size == PDMIC_DSPR0_SIZE_32) {
		cfg.len = size / 4;
		cfg.data_width = DMA_DATA_WIDTH_WORD;
	} else {
		cfg.len = size / 2;
		cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
	}

	dma_configure_transfer(pdmic_dma_channel, &cfg);
	dma_set_callback(pdmic_dma_channel, callback, user_arg);
	dma_start_transfer(pdmic_dma_channel);
}
