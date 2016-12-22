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

#ifndef _CLASSD_H
#define _CLASSD_H

#ifdef CONFIG_HAVE_CLASSD

/*---------------------------------------------------------------------------
 *         Includes
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "callback.h"
#include "chip.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

enum _classd_mode
{
	CLASSD_OUTPUT_SINGLE_ENDED,
	CLASSD_OUTPUT_DIFFERENTIAL,
	CLASSD_OUTPUT_HALF_BRIDGE,
	CLASSD_OUTPUT_FULL_BRIDGE,
};

enum _classd_non_ovr
{
	CLASSD_NONOVR_5NS,
	CLASSD_NONOVR_10NS,
	CLASSD_NONOVR_15NS,
	CLASSD_NONOVR_20NS,
};

enum _classd_eqcfg
{
	CLASSD_EQCFG_FLAT,
	CLASSD_EQCFG_BBOOST12,
	CLASSD_EQCFG_BBOOST6,
	CLASSD_EQCFG_BCUT12,
	CLASSD_EQCFG_BCUT6,
	CLASSD_EQCFG_MBOOST3,
	CLASSD_EQCFG_MBOOST8,
	CLASSD_EQCFG_MCUT3,
	CLASSD_EQCFG_MCUT8,
	CLASSD_EQCFG_TBOOST12,
	CLASSD_EQCFG_TBOOST6,
	CLASSD_EQCFG_TCUT12,
	CLASSD_EQCFG_TCUT6,
};

enum _classd_mono
{
	CLASSD_MONO_MIXED,
	CLASSD_MONO_SAT,
	CLASSD_MONO_LEFT,
	CLASSD_MONO_RIGHT,
};

enum _classd_trans_mode
{
	CLASSD_MODE_POLLING,
	CLASSD_MODE_DMA,
	CLASSD_MODE_ASYNC,
};

enum _classd_buf_attr {
	CLASSD_BUF_ATTR_WRITE = 0x01,
	CLASSD_BUF_ATTR_READ  = 0x02,
};

struct _classd_desc
{
	Classd* addr;
	uint32_t             sample_rate;
	enum _classd_trans_mode transfer_mode;
	enum _classd_mode    mode;
	enum _classd_non_ovr non_ovr;
	bool                 swap_channels;
	bool                 mono;
	enum _classd_mono    mono_mode;
	bool                 left_enable;
	bool                 right_enable;
	struct {
		mutex_t mutex;

		struct _buffer buffer;
		uint16_t transferred;
		struct _callback callback;
		struct {
			struct _dma_channel* channel;
			struct _dma_cfg cfg_dma;
			struct _dma_transfer_cfg cfg;
		} dma;
	} tx;
};

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern int classd_configure(struct _classd_desc *desc);

extern void classd_disable(struct _classd_desc *desc);

extern void classd_swap_channels(struct _classd_desc *desc, bool swap);

extern void classd_set_equalizer(struct _classd_desc *desc, enum _classd_eqcfg eqcfg);

extern void classd_enable_channels(struct _classd_desc *desc, bool left, bool right);

extern void classd_disable_channels(struct _classd_desc *desc, bool left, bool right);

extern void classd_set_left_attenuation(struct _classd_desc *desc, uint8_t attn);

extern void classd_set_right_attenuation(struct _classd_desc *desc, uint8_t attn);

extern void classd_volume_mute(struct _classd_desc *desc, bool left, bool right);

extern void classd_volume_unmute(struct _classd_desc *desc, bool left, bool right);

extern int classd_transfer(struct _classd_desc* desc, struct _buffer* buf, struct _callback* cb);

extern bool classd_tx_transfer_is_done(struct _classd_desc* desc);

extern void classd_tx_stop(struct _classd_desc* desc);

#endif /* CONFIG_HAVE_CLASSD */

#endif /* _CLASSD_H */
