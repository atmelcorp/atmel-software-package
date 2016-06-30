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
 *         Includes
 *---------------------------------------------------------------------------*/

#include "peripherals/dma.h"
#include <stdbool.h>
#include <stdint.h>


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


/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

struct _pdmic_desc {
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
};


/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern bool pdmic_configure(struct _pdmic_desc *desc);

extern void pdmic_disable(void);

extern void pdmic_enable(void);

extern bool pdmic_set_gain(uint16_t dgain, uint8_t scale);

extern void pdmic_stream_convert(bool flag);

extern bool pdmic_init(struct _pdmic_desc *desc);

extern bool pdmic_data_ready(void);

extern void pdmic_dma_transfer(void *buffer, uint32_t size,
		dma_callback_t callback, void *user_arg);

#endif /* _PDMIC_H */
