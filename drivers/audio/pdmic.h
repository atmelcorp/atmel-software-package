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

#ifndef _PDMIC_H
#define _PDMIC_H

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "callback.h"
#include "chip.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

#define PDMIC_OVER_SAMPLING_RATIO_64        (64)
#define PDMIC_OVER_SAMPLING_RATIO_128       (128)

#define PDMIC_CONVERTED_DATA_SIZE_16        (16)
#define PDMIC_CONVERTED_DATA_SIZE_32        (32)

#define PDMIC_DSP_HIGH_PASS_FILTER_ON       (0)
#define PDMIC_DSP_HIGH_PASS_FILTER_OFF      (1)

#define PDMIC_DSP_SINCC_PASS_FILTER_ON       (0)
#define PDMIC_DSP_SINCC_PASS_FILTER_OFF      (1)

#define PDMIC_MR_PRESCAL_MAX_VAL (128)
#define PDMIC_DSPR_SCALE_MAX_VAL (16)
#define PDMIC_DSPR_SHIFT_MAX_VAL (16)
#define PDMIC_DSPR_DGAIN_MAX_VAL (32768)

#define PDMIC_SUCCESS           (0)
#define PDMIC_INVALID_PARAMETER (1)
#define PDMIC_ERROR_LOCK        (2)

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

enum _pdmic_trans_mode
{
	PDMIC_MODE_POLLING,
	PDMIC_MODE_DMA,
	PDMIC_MODE_ASYNC,
};

enum _pdmic_buf_attr {
	PDMIC_BUF_ATTR_READ  = 0x02,
};

struct _pdmic_desc {
	Pdmic *addr;
	enum _pdmic_trans_mode transfer_mode;
	uint32_t sample_rate;
	uint8_t  channels;
	uint8_t  dsp_osr;
	uint8_t  dsp_size;
	uint8_t  dsp_hpfbyp;
	uint8_t  dsp_sinbyp;
	uint8_t  dsp_scale;
	uint8_t  dsp_shift;
	uint16_t dsp_dgain;
	uint16_t dsp_offset;
	struct {
		mutex_t mutex;

		struct _buffer buffer;
		uint16_t transferred;
		struct _callback callback;
		struct {
			struct _dma_channel *channel;
			struct _dma_cfg cfg_dma;
			struct _dma_transfer_cfg cfg;
		} dma;
	} rx;
};

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern int pdmic_configure(struct _pdmic_desc *desc);

extern void pdmic_disable(struct _pdmic_desc* desc);

extern void pdmic_enable(struct _pdmic_desc* desc);

extern int pdmic_set_gain(struct _pdmic_desc* desc, uint16_t dgain, uint8_t scale);

extern void pdmic_stream_convert(struct _pdmic_desc* desc, bool flag);

extern int pdmic_init(struct _pdmic_desc *desc);

extern bool pdmic_data_ready(struct _pdmic_desc* desc);

extern int pdmic_transfer(struct _pdmic_desc* desc, struct _buffer* buf, struct _callback* cb);

extern void pdmic_rx_stop(struct _pdmic_desc* desc);

extern bool pdmic_rx_transfer_is_done(struct _pdmic_desc* desc);

#endif /* _PDMIC_H */
