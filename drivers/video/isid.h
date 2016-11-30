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


#ifndef ISID_HEADER__
#define ISID_HEADER__

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*------------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/

#define ISID_MAX_DMA_DESC     10

#define ISID_OK              (0)
#define ISID_ERROR_LOCK      (1)
#define ISID_ERROR_CONFIG    (2)

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

typedef void (*isid_callback_t)(uint8_t frame_idx);

enum _isid_pipe {
	ISID_PIPE_PREVIEW = 0,
	ISID_PIPE_CODEC,
	ISID_PIPE_BOTH
};

enum _isid_yuv_pattern {
	ISID_CB_Y_CR_Y = 0,
	ISID_CR_Y_CB_Y,
	ISID_Y_CB_Y_CR,
	ISID_Y_CR_Y_CB,
};

enum _isid_rgb_pattern {
	ISID_RGRG = 0,
	ISID_BGBG,
	ISID_GBGB,
	ISID_GRGR,
};

struct _isid_desc {
	/* structure to define ISCD parameter */
	struct {
		uint8_t input_format;
		uint32_t width;
		uint32_t height;
		uint8_t multi_bufs;
		uint8_t capture_rate;
	} cfg;
	struct {
		enum _isid_pipe pipe;
		uint32_t px;
		uint32_t py;
		uint8_t gray_pixel;
		enum _isid_yuv_pattern yuv;
		enum _isid_rgb_pattern rgb;
		struct _isi_yuv2rgb* yuv2rgb_matrix;
		struct _isi_rgb2yuv* rgb2yuv_matrix;
		uint8_t frame_idx;
	} pipe;
	struct {
		uint32_t address_p;
		uint32_t size_p;
		uint32_t address_c;
		uint32_t size_c;
		isid_callback_t callback;
		void* cb_args;
	} dma;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern uint8_t isid_pipe_start(struct _isid_desc* desc);

#endif /* ISID_HEADER__ */
