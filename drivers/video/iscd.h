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


#ifndef ISCD_H_
#define ISCD_H_

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "callback.h"
#include "dma/dma.h"

/*------------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/

#define MAX_DMA_VIEW_SIZE (sizeof(struct _isc_dma_view2) / sizeof(uint32_t))
#define ISCD_MAX_DMA_DESC (10)

/* GAMMA and HISTOGRAM definitions */
#define GAMMA_ENTRIES (64)

#define HISTOGRAM_GR (0)
#define HISTOGRAM_R  (1)
#define HISTOGRAM_GB (2)
#define HISTOGRAM_B  (3)

#define BAYER_COUNT (HISTOGRAM_B + 1)

#define HIST_ENTRIES (512)

#define ISCD_OK           (0)
#define ISCD_ERROR_LOCK   (1)
#define ISCD_ERROR_CONFIG (2)

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

typedef void (*iscd_callback_t)(uint8_t frame_idx);

enum _iscd_layout {
	ISCD_LAYOUT_PACKED8 = 0,
	ISCD_LAYOUT_PACKED16,
	ISCD_LAYOUT_PACKED32,
	ISCD_LAYOUT_YC422SP,
	ISCD_LAYOUT_YC422P,
	ISCD_LAYOUT_YC420SP,
	ISCD_LAYOUT_YC420P
};

enum _iscd_rlp_mode {
	ISCD_RLP_MODE_DAT8 = 0,  /**< \brief (ISC_RLP_CFG) 8-bit data */
	ISCD_RLP_MODE_DAT9,      /**< \brief (ISC_RLP_CFG) 9-bit data */
	ISCD_RLP_MODE_DAT10,     /**< \brief (ISC_RLP_CFG) 10-bit data */
	ISCD_RLP_MODE_DAT11,     /**< \brief (ISC_RLP_CFG) 11-bit data */
	ISCD_RLP_MODE_DAT12,     /**< \brief (ISC_RLP_CFG) 12-bit data */
	ISCD_RLP_MODE_DATY8,     /**< \brief (ISC_RLP_CFG) 8-bit luminance only */
	ISCD_RLP_MODE_DATY10,    /**< \brief (ISC_RLP_CFG) 10-bit luminance only */
	ISCD_RLP_MODE_ARGB444,   /**< \brief (ISC_RLP_CFG) 12-bit RGB+4-bit Alpha (MSB) */
	ISCD_RLP_MODE_ARGB555,   /**< \brief (ISC_RLP_CFG) 15-bit RGB+1-bit Alpha (MSB) */
	ISCD_RLP_MODE_RGB565,    /**< \brief (ISC_RLP_CFG) 16-bit RGB */
	ISCD_RLP_MODE_ARGB32,    /**< \brief (ISC_RLP_CFG) 24-bits RGB mode+8-bit Alpha */
	ISCD_RLP_MODE_YYCC,      /**< \brief (ISC_RLP_CFG) YCbCr mode (full range, [0-255]) */
	ISCD_RLP_MODE_YYCC_LIMIT /**< \brief (ISC_RLP_CFG) YCbCr mode (limited range) */
};

enum _iscd_bayer_pattern {
	ISCD_GRGR = 0,
	ISCD_RGRG,
	ISCD_GBGB,
	ISCD_BGBG,
};

enum _iscd_awb_state {
	AWB_INIT = 0,
	AWB_WAIT_HIS_READY,
	AWB_WAIT_DMA_READY,
	AWB_WAIT_ISC_PERFORMED,
};

struct _iscd_desc {
	/* structure to define ISCD parameter */
	struct {
		uint8_t input_format;
		uint8_t input_bits;
		enum _iscd_layout layout;
		uint8_t multi_bufs;
	} cfg;
	struct {
		uint8_t bayer_color_filter;
		enum _iscd_bayer_pattern bayer_pattern;
		bool histo_enable;
		uint32_t* histo_buf;
		struct _color_space* cs;
		struct {
			bool gamma_enable;
			bool rg_enable;
			uint32_t* rg_table;
			bool gg_enable;
			uint32_t* gg_table;
			bool bg_enable;
			uint32_t* bg_table;
		} gamma;
		struct {
			float bright;
			float contrast;
		} cbc;
		struct _color_correct* color_correction;
		enum _iscd_rlp_mode rlp_mode;
		uint8_t frame_idx;
	} pipe;
	struct {
		uint32_t address0;
		uint32_t address1;
		uint32_t address2;
		uint32_t size;
		iscd_callback_t callback;
	} dma;
};

struct _iscd_awb {
	struct {
		struct _dma_channel* dma_histo_channel;
		bool dma_histo_ready;
		bool dma_histo_done;
	} dma;
	uint32_t backup[BAYER_COUNT];
	uint32_t count[BAYER_COUNT];
	uint32_t op_mode;
	enum _iscd_awb_state state;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern uint8_t iscd_pipe_start(struct _iscd_desc* desc);

extern void iscd_auto_white_balance_ref_algo(uint32_t* histo_buf);

#endif /* ISCD_H_ */
