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

#include "trace.h"

#include "irq/irq.h"

#include "mm/cache.h"

#include "video/image_sensor_inf.h"
#include "video/isi.h"
#include "video/isid.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static struct _isi_dma_desc _isi_dma_preview[ISID_MAX_DMA_DESC];
CACHE_ALIGNED static struct _isi_dma_desc _isi_dma_codec[ISID_MAX_DMA_DESC];

struct _isid_desc* isid;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief ISC interrupt handler.
 */
static void _isi_handler(uint32_t source, void* arg)
{
	uint32_t status;

	status = isi_get_status();
	if ((status & ISI_SR_PXFR_DONE) == ISI_SR_PXFR_DONE) {
		if (isid->pipe.frame_idx == (isid->cfg.multi_bufs - 1))
			isid->pipe.frame_idx = 0;
		else
			isid->pipe.frame_idx++;
		if (isid->dma.callback)
			isid->dma.callback(isid->pipe.frame_idx);
	}
	if ((status & ISI_SR_CXFR_DONE) == ISI_SR_CXFR_DONE) {
		/* TODO */
	}
}

/**
 * \brief Set up DMA Descriptors.
 */
static uint8_t _isid_configure_dma(struct _isid_desc* desc)
{
	uint32_t i;

	if (desc->cfg.multi_bufs > ISID_MAX_DMA_DESC)
		return ISID_ERROR_CONFIG;

	if (desc->pipe.pipe != ISID_PIPE_CODEC) {
		for(i = 0; i < desc->cfg.multi_bufs; i++) {
			_isi_dma_preview[i].address = (uint32_t)desc->dma.address_p
										+ i * desc->dma.size_p;
			_isi_dma_preview[i].control = ISI_DMA_P_CTRL_P_FETCH | ISI_DMA_P_CTRL_P_WB;
			_isi_dma_preview[i].next = (uint32_t)&_isi_dma_preview[i + 1];
		}
		/* Wrapping to first FBD */
		_isi_dma_preview[i - 1].next = (uint32_t)_isi_dma_preview;
		cache_clean_region(_isi_dma_preview, sizeof(_isi_dma_preview));
	}
	if (desc->pipe.pipe != ISID_PIPE_PREVIEW) {
		for(i = 0; i < desc->cfg.multi_bufs; i++) {
			_isi_dma_codec[i].address = (uint32_t)desc->dma.address_c
										+ i * desc->dma.size_c;
			_isi_dma_codec[i].control = ISI_DMA_C_CTRL_C_FETCH | ISI_DMA_C_CTRL_C_WB;
			_isi_dma_codec[i].next = (uint32_t)&_isi_dma_codec[i + 1];
		}
		_isi_dma_codec[i - 1].next = (uint32_t)_isi_dma_codec;
		cache_clean_region(_isi_dma_codec, sizeof(_isi_dma_codec));
	}
	return ISID_OK;
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/
uint8_t isid_pipe_start(struct _isid_desc* desc)
{
	isid = desc;

	irq_disable(ID_ISI);
	/* Reset ISI peripheral */
	isi_reset();

	if (desc->cfg.input_format == RAW_BAYER)
		/* Can not support BAYER input */
		return ISID_ERROR_CONFIG;

	isi_dma_preview_channel_enabled(0);
	isi_dma_codec_channel_enabled(0);

	isi_set_framerate(desc->cfg.capture_rate);
	/* Set the windows blank */
	isi_set_blank(0, 0);
	/* Set vertical and horizontal Size of the Image Sensor for preview path*/
	isi_set_sensor_size(desc->cfg.width, desc->cfg.height);

	/* Set preview size to fit LCD size*/
	isi_set_preview_size(desc->pipe.px, desc->pipe.py);
	/* calculate scaler factor automatically. */
	isi_calc_scaler_factor();

	if (desc->pipe.pipe == ISID_PIPE_BOTH)
		isi_codec_path_full();

	/*  Set data stream in YUV/RGB format.*/
	if (desc->cfg.input_format == RGB)
		isi_set_input_stream(1);
	else
		isi_set_input_stream(0);

	if (desc->cfg.input_format == MONO)
		isi_set_grayscale_mode(1, desc->pipe.gray_pixel);

	/* Defines YCrCb swap format.*/
	isi_ycrcb_format(ISI_CFG2_YCC_SWAP(desc->pipe.yuv));

	/* Defines RGB format.*/
	isi_rgb_pixel_mapping(ISI_CFG2_RGB_CFG(desc->pipe.rgb));

	/* Set Matrix color space for YUV to RBG convert */
	if (desc->pipe.yuv2rgb_matrix)
		isi_set_matrix_yuv2rgb(desc->pipe.yuv2rgb_matrix);
	/* Set Matrix color space for RGB to YUV convert */
	if (desc->pipe.rgb2yuv_matrix)
		isi_set_matrix_rgb2yuv(desc->pipe.rgb2yuv_matrix);

	_isid_configure_dma(desc);
	isi_disable_interrupt(-1);

	/* Configure DMA for preview path. */
	if (desc->pipe.pipe != ISID_PIPE_CODEC) {
		isi_set_dma_preview_path((uint32_t)_isi_dma_preview,
								ISI_DMA_P_CTRL_P_FETCH,
								(uint32_t)desc->dma.address_p);
		isi_dma_preview_channel_enabled(1);
		isi_enable_interrupt(ISI_IER_PXFR_DONE);
	}

	/* Configure DMA for preview path. */
	if (desc->pipe.pipe != ISID_PIPE_PREVIEW) {
		isi_set_dma_codec_path((uint32_t)_isi_dma_codec,
								ISI_DMA_C_CTRL_C_FETCH,
								(uint32_t)desc->dma.address_c);
		isi_dma_codec_channel_enabled(1);
		isi_enable_interrupt(ISI_IER_CXFR_DONE);
	}

	isi_enable();
	isid->pipe.frame_idx = 0;
	irq_add_handler(ID_ISI, _isi_handler, NULL);
	isi_get_status();
	irq_enable(ID_ISI);

	return ISID_OK;
}
