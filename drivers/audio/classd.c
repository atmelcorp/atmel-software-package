/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "audio/classd.h"
#include "callback.h"
#include "chip.h"
#include "errno.h"
#include "io.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct {
	uint32_t rate;
	uint32_t sample_rate;
	uint32_t dsp_clk;
} audio_info[] = {
	{ 8000,  CLASSD_INTPMR_FRAME_FRAME_8K,  CLASSD_INTPMR_DSPCLKFREQ_12M288 },
	{ 16000, CLASSD_INTPMR_FRAME_FRAME_16K, CLASSD_INTPMR_DSPCLKFREQ_12M288 },
	{ 32000, CLASSD_INTPMR_FRAME_FRAME_32K, CLASSD_INTPMR_DSPCLKFREQ_12M288 },
	{ 48000, CLASSD_INTPMR_FRAME_FRAME_48K, CLASSD_INTPMR_DSPCLKFREQ_12M288 },
	{ 96000, CLASSD_INTPMR_FRAME_FRAME_96K, CLASSD_INTPMR_DSPCLKFREQ_12M288 },
	{ 22050, CLASSD_INTPMR_FRAME_FRAME_22K, CLASSD_INTPMR_DSPCLKFREQ_11M2896 },
	{ 44100, CLASSD_INTPMR_FRAME_FRAME_44K, CLASSD_INTPMR_DSPCLKFREQ_11M2896 },
	{ 88200, CLASSD_INTPMR_FRAME_FRAME_88K, CLASSD_INTPMR_DSPCLKFREQ_11M2896 },
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
static bool _dspclk_configure(uint32_t dsp_clk)
{
	struct _pmc_audio_cfg cfg;

	/* Pad Clock: not used */
	cfg.div = 0;
	cfg.qdaudio = 0;

	/* PMC Clock: */
	/* 12Mhz * (ND + 1 + FRACR/2^22) / (QDPMC + 1) = 8 * DSPCLK */
	switch (dsp_clk) {
	case CLASSD_INTPMR_DSPCLKFREQ_12M288:
		/* 12Mhz * (56 + 1 + 1442841/2^22) / (6 + 1) = 8 * 12.288Mhz */
		cfg.nd = 56;
		cfg.fracr = 1442841;
		cfg.qdpmc = 6;
		break;
	case CLASSD_INTPMR_DSPCLKFREQ_11M2896:
		/* 12Mhz * (59 + 1 + 885837/2^22) / (7 + 1) = 8 * 11.2896Mhz */
		cfg.nd = 59;
		cfg.fracr = 885837;
		cfg.qdpmc = 7;
		break;
	default:
		return false;
	}

	pmc_configure_audio(&cfg);
	pmc_enable_audio(true, false);

#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
	{
		uint32_t clk;
		clk = pmc_get_audio_pmc_clock();
		trace_debug("Configured Audio PLL PMC Clock: %u (= 8 * %u)\r\n",
			    (unsigned)clk, (unsigned)(clk >> 3));
	}
#endif
	return true;
}
#endif

static bool _set_eqcfg_bits(enum _classd_eqcfg eqcfg, volatile uint32_t *intpmr)
{
	uint32_t mask = CLASSD_INTPMR_EQCFG_Msk;
	uint32_t bits = 0;

	switch (eqcfg) {
	case CLASSD_EQCFG_FLAT:
		bits = CLASSD_INTPMR_EQCFG_FLAT;
		break;
	case CLASSD_EQCFG_BBOOST12:
		bits = CLASSD_INTPMR_EQCFG_BBOOST12;
		break;
	case CLASSD_EQCFG_BBOOST6:
		bits = CLASSD_INTPMR_EQCFG_BBOOST6;
		break;
	case CLASSD_EQCFG_BCUT12:
		bits = CLASSD_INTPMR_EQCFG_BCUT12;
		break;
	case CLASSD_EQCFG_BCUT6:
		bits = CLASSD_INTPMR_EQCFG_BCUT6;
		break;
	case CLASSD_EQCFG_MBOOST3:
		bits = CLASSD_INTPMR_EQCFG_MBOOST3;
		break;
	case CLASSD_EQCFG_MBOOST8:
		bits = CLASSD_INTPMR_EQCFG_MBOOST8;
		break;
	case CLASSD_EQCFG_MCUT3:
		bits = CLASSD_INTPMR_EQCFG_MCUT3;
		break;
	case CLASSD_EQCFG_MCUT8:
		bits = CLASSD_INTPMR_EQCFG_MCUT8;
		break;
	case CLASSD_EQCFG_TBOOST12:
		bits = CLASSD_INTPMR_EQCFG_TBOOST12;
		break;
	case CLASSD_EQCFG_TBOOST6:
		bits = CLASSD_INTPMR_EQCFG_TBOOST6;
		break;
	case CLASSD_EQCFG_TCUT12:
		bits = CLASSD_INTPMR_EQCFG_TCUT12;
		break;
	case CLASSD_EQCFG_TCUT6:
		bits = CLASSD_INTPMR_EQCFG_TCUT6;
		break;
	default:
		trace_warning("classd: invalid equalizer config %u\r\n",
			      (unsigned)eqcfg);
		return false;
	};

	*intpmr = (*intpmr & ~mask) | bits;
	return true;
}

static bool _set_mono_bits(bool mono, enum _classd_mono mono_mode, volatile uint32_t *intpmr)
{
	uint32_t mask = CLASSD_INTPMR_MONO_ENABLED | CLASSD_INTPMR_MONOMODE_Msk;
	uint32_t bits = 0;

	if (mono) {
		bits = CLASSD_INTPMR_MONO_ENABLED;
		switch (mono_mode) {
		case CLASSD_MONO_MIXED:
			bits |= CLASSD_INTPMR_MONOMODE_MONOMIX;
			break;
		case CLASSD_MONO_SAT:
			bits |= CLASSD_INTPMR_MONOMODE_MONOSAT;
			break;
		case CLASSD_MONO_LEFT:
			bits |= CLASSD_INTPMR_MONOMODE_MONOLEFT;
			break;
		case CLASSD_MONO_RIGHT:
			bits |= CLASSD_INTPMR_MONOMODE_MONORIGHT;
			break;
		default:
			trace_warning("classd: invalid mono mode %u\r\n",
				      (unsigned)mono_mode);
			return false;
		}
	}

	*intpmr = (*intpmr & ~mask) | bits;
	return true;
}

static int _classd_dma_transfer_callback(void* arg, void* arg2)
{
	struct _classd_desc* desc = (struct _classd_desc*)arg;

	dma_reset_channel(desc->tx.dma.channel);

	mutex_unlock(&desc->tx.mutex);

	return callback_call(&desc->tx.callback, NULL);
}

static void _classd_dma_transfer(struct _classd_desc* desc, struct _buffer* buffer)
{
	struct _callback _cb;

	memset(&desc->tx.dma.cfg, 0x0, sizeof(desc->tx.dma.cfg));

	desc->tx.dma.cfg.saddr = buffer->data;
	desc->tx.dma.cfg.daddr = (void*)&desc->addr->CLASSD_THR;

	if (desc->left_enable && desc->right_enable) {
		desc->tx.dma.cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
		desc->tx.dma.cfg.len = buffer->size / 4;
	} else {
		desc->tx.dma.cfg_dma.data_width = DMA_DATA_WIDTH_HALF_WORD;
		desc->tx.dma.cfg.len = buffer->size / 2;
	}
	dma_configure_transfer(desc->tx.dma.channel, &desc->tx.dma.cfg_dma, &desc->tx.dma.cfg, 1);
	callback_set(&_cb, _classd_dma_transfer_callback, (void*)desc);
	dma_set_callback(desc->tx.dma.channel, &_cb);
	cache_clean_region(desc->tx.dma.cfg.saddr, desc->tx.dma.cfg.len);
	dma_start_transfer(desc->tx.dma.channel);
}

static void _classd_polling_transfer(struct _classd_desc* desc, struct _buffer* buffer)
{
	uint16_t* start = (uint16_t*)buffer->data;
	uint32_t  length = buffer->size / sizeof(uint16_t);
	uint16_t* end = start + length;
	uint16_t* current = start;

	while (1) {
		if (desc->addr->CLASSD_ISR & CLASSD_ISR_DATRDY) {
			uint16_t left = 0, right = 0;
			if (desc->left_enable)
				left = *current++;
			if (desc->right_enable)
				right = *current++;
			desc->addr->CLASSD_THR = CLASSD_THR_RDATA(right)
			                       | CLASSD_THR_LDATA(left);
		}
		if (current >= end)
			break;
	}

	mutex_unlock(&desc->tx.mutex);

	callback_call(&desc->tx.callback, NULL);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

int classd_configure(struct _classd_desc *desc)
{
	uint8_t i;
	uint32_t mr, intpmr, dsp_clk_set, frame_set;
	uint32_t id = get_classd_id_from_addr(desc->addr);

	if (!desc->left_enable && !desc->right_enable)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(audio_info); i++) {
		if (audio_info[i].rate == desc->sample_rate) {
			dsp_clk_set  = audio_info[i].dsp_clk;
			frame_set = audio_info[i].sample_rate;
			break;
		}
	}
	if (i == ARRAY_SIZE(audio_info))
		return -EINVAL;
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	if (!_dspclk_configure(dsp_clk_set))
		return -EINVAL;
#endif
	struct _pmc_periph_cfg cfg = {
		.gck = {
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
			.css = PMC_PCR_GCKCSS_AUDIO_CLK,
			.div = 1,
#else
			.css = PMC_PCR_GCKCSS_MCK_CLK,
			.div = 2,
#endif	
		},
	};
	pmc_configure_peripheral(id, &cfg, true);

	/* perform soft reset */
	desc->addr->CLASSD_CR  = CLASSD_CR_SWRST;
	desc->addr->CLASSD_IDR = CLASSD_IDR_DATRDY;

	/* initial MR/INTPMR values */
	mr = 0;
	intpmr = dsp_clk_set | frame_set;

	/* configure output mode */
	switch (desc->mode) {
	case CLASSD_OUTPUT_SINGLE_ENDED:
		break;
	case CLASSD_OUTPUT_DIFFERENTIAL:
		mr |= CLASSD_MR_PWMTYP;
		break;
	case CLASSD_OUTPUT_HALF_BRIDGE:
		mr |= CLASSD_MR_NON_OVERLAP;
		break;
	case CLASSD_OUTPUT_FULL_BRIDGE:
		mr |= CLASSD_MR_PWMTYP | CLASSD_MR_NON_OVERLAP;
		break;
	default:
		trace_warning("classd: invalid mode %u\n", (unsigned)desc->mode);
		return -EINVAL;
	}

	/* configure non-overlapping time */
	if (mr & CLASSD_MR_NON_OVERLAP) {
		switch (desc->non_ovr) {
		case CLASSD_NONOVR_5NS:
			mr |= CLASSD_MR_NOVRVAL_5NS;
			break;
		case CLASSD_NONOVR_10NS:
			mr |= CLASSD_MR_NOVRVAL_10NS;
			break;
		case CLASSD_NONOVR_15NS:
			mr |= CLASSD_MR_NOVRVAL_15NS;
			break;
		case CLASSD_NONOVR_20NS:
			mr |= CLASSD_MR_NOVRVAL_20NS;
			break;
		default:
			trace_warning("classd: invalid non overlap value %u\r\n",
				      (unsigned)desc->non_ovr);
			return -EINVAL;
		}
	}

	/* configure mono/stereo */
	if (desc->swap_channels)
		intpmr |= CLASSD_INTPMR_SWAP;
	if (!_set_mono_bits(desc->mono, desc->mono_mode, &intpmr))
		return -EINVAL;

	/* configure left channel (muted, max attn) */
	if (desc->left_enable)
		mr |= CLASSD_MR_LEN;
	mr |= CLASSD_MR_LMUTE;
	intpmr |= CLASSD_INTPMR_ATTL(CLASSD_INTPMR_ATTL_Msk);

	/* configure right channel (muted, max attn)  */
	if (desc->right_enable)
		mr |= CLASSD_MR_REN;
	mr |= CLASSD_MR_RMUTE;
	intpmr |= CLASSD_INTPMR_ATTR(CLASSD_INTPMR_ATTL_Msk);

	/* write configuration */
	desc->addr->CLASSD_MR = mr;
	desc->addr->CLASSD_INTPMR = intpmr;

	desc->tx.dma.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->tx.dma.channel != NULL);

	desc->tx.dma.cfg_dma.incr_saddr = true;
	desc->tx.dma.cfg_dma.incr_daddr = false;
	desc->tx.dma.cfg_dma.loop = false;
	desc->tx.dma.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	desc->tx.mutex = 0;

	if ((desc->addr->CLASSD_INTSR & CLASSD_INTSR_CFGERR) != 0)
		return -ENODEV;

	return 0;
}

void classd_disable(struct _classd_desc *desc)
{
	uint32_t id = get_classd_id_from_addr(desc->addr);
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	pmc_disable_audio();
#endif
	pmc_disable_gck(id);
	pmc_disable_peripheral(id);
}

void classd_swap_channels(struct _classd_desc *desc, bool swap)
{
	if (swap) {
		desc->addr->CLASSD_INTPMR |= CLASSD_INTPMR_SWAP;
	} else {
		desc->addr->CLASSD_INTPMR &= ~CLASSD_INTPMR_SWAP;
	}
}

void classd_set_equalizer(struct _classd_desc *desc, enum _classd_eqcfg eqcfg)
{
	_set_eqcfg_bits(eqcfg, &desc->addr->CLASSD_INTPMR);
}

void classd_enable_channels(struct _classd_desc *desc, bool left, bool right)
{
	uint32_t bits = 0;
	if (left)
		bits |= CLASSD_MR_LEN;
	if (right)
		bits |= CLASSD_MR_REN;
	desc->addr->CLASSD_MR |= bits;
}

void classd_disable_channels(struct _classd_desc *desc, bool left, bool right)
{
	uint32_t bits = 0;
	if (left)
		bits |= CLASSD_MR_LEN;
	if (right)
		bits |= CLASSD_MR_REN;
	desc->addr->CLASSD_MR &= ~bits;
}

void classd_set_left_attenuation(struct _classd_desc *desc, uint8_t attn)
{
	if (attn > (CLASSD_INTPMR_ATTL_Msk >> CLASSD_INTPMR_ATTL_Pos))
		attn = (CLASSD_INTPMR_ATTL_Msk >> CLASSD_INTPMR_ATTL_Pos);

	uint32_t intpmr = desc->addr->CLASSD_INTPMR & ~CLASSD_INTPMR_ATTL_Msk;
	desc->addr->CLASSD_INTPMR = intpmr | CLASSD_INTPMR_ATTL(attn);
}

void classd_set_right_attenuation(struct _classd_desc *desc, uint8_t attn)
{
	if (attn > (CLASSD_INTPMR_ATTL_Msk >> CLASSD_INTPMR_ATTL_Pos))
		attn = (CLASSD_INTPMR_ATTL_Msk >> CLASSD_INTPMR_ATTL_Pos);

	uint32_t intpmr = desc->addr->CLASSD_INTPMR & ~CLASSD_INTPMR_ATTR_Msk;
	desc->addr->CLASSD_INTPMR = intpmr | CLASSD_INTPMR_ATTR(attn);
}

void classd_volume_mute(struct _classd_desc *desc, bool left, bool right)
{
	uint32_t bits = 0;
	if (left)
		bits |= CLASSD_MR_LMUTE;
	if (right)
		bits |= CLASSD_MR_RMUTE;
	desc->addr->CLASSD_MR |= bits;
}

void classd_volume_unmute(struct _classd_desc *desc, bool left, bool right)
{
	uint32_t bits = 0;
	if (left)
		bits |= CLASSD_MR_LMUTE;
	if (right)
		bits |= CLASSD_MR_RMUTE;
	desc->addr->CLASSD_MR &= ~bits;
}

int classd_transfer(struct _classd_desc* desc, struct _buffer* buf, struct _callback* cb)
{
	uint8_t tmode;

	tmode = desc->transfer_mode;

	if ((buf == NULL) || (buf->size == 0))
		return -EINVAL;

	if (buf->attr & CLASSD_BUF_ATTR_WRITE) {
		mutex_lock(&desc->tx.mutex);

		desc->tx.transferred = 0;
		desc->tx.buffer.data = buf->data;
		desc->tx.buffer.size = buf->size;
		desc->tx.buffer.attr = buf->attr;

		callback_copy(&desc->tx.callback, cb);

		if (tmode == CLASSD_MODE_DMA)
			_classd_dma_transfer(desc, buf);
		else if (tmode == CLASSD_MODE_POLLING)
			_classd_polling_transfer(desc, buf);
	}
	return 0;
}

bool classd_tx_transfer_is_done(struct _classd_desc* desc)
{
	return (!mutex_is_locked(&desc->tx.mutex));
}

void classd_tx_stop(struct _classd_desc* desc)
{
	if (desc->transfer_mode == CLASSD_MODE_DMA) {
		if (desc->tx.dma.channel){
			dma_stop_transfer(desc->tx.dma.channel);
			mutex_unlock(&desc->tx.mutex);
		}
	}
}
