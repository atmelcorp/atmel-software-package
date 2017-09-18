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

#include "irq/irq.h"

#include "mm/cache.h"

#include "video/image_sensor_inf.h"
#include "video/isc.h"
#include "video/iscd.h"

#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static union {
	struct _isc_dma_view0 view0[ISCD_MAX_DMA_DESC];
	struct _isc_dma_view1 view1[ISCD_MAX_DMA_DESC];
	struct _isc_dma_view2 view2[ISCD_MAX_DMA_DESC];
} _isc_dma_view_pool;

static struct _iscd_awb awb;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Callback entry for histogram DMA transfer done.
 */
static int _dma_histo_callback(void *arg, void* arg2)
{
	struct _iscd_desc* iscd = (struct _iscd_desc*)arg;

	dma_reset_channel(awb.dma.dma_histo_channel);

	cache_invalidate_region((uint32_t*)iscd->pipe.histo_buf,
			HIST_ENTRIES * sizeof(uint32_t));
	awb.dma.dma_histo_done = true;

	return 0;
}

/**
 * \brief Configure xDMA to read Histogram entries.
 */
static void _iscd_dma_read_histogram(uint32_t buf)
{
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg cfg;

	cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
	cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = true;
	cfg_dma.loop = false;

	cfg.saddr = (uint32_t*)&ISC->ISC_HIS_ENTRY[0];
	cfg.daddr = (uint32_t*)buf;
	cfg.len = HIST_ENTRIES;

	dma_configure_transfer(awb.dma.dma_histo_channel, &cfg_dma, &cfg, 1);
	dma_start_transfer(awb.dma.dma_histo_channel);
}

/**
 * \brief Convert float data to HEX with giving format.
 * \param sign_bit length of sign in bit
 * \param magnitude_bit length of magnitude in bit
 * \param fractional_bit length of fractional in bit
 * \param f float value to be converted
 */
static uint32_t _float2hex(uint8_t sign_bit, uint8_t magnitude_bit,
                          uint8_t fractional_bit, float f)
{
	uint32_t hex;
	uint32_t hex_mask = (1 << (magnitude_bit + fractional_bit + 1)) - 1;

	if (!sign_bit) {
		if (f < 0.0)
			return 0;
		hex = (uint32_t)(f * (1 << fractional_bit));
		hex &= hex_mask;
	} else {
		if (f < 0.0) {
			hex = (uint32_t)((f) * (-1.0) * (1 << fractional_bit));
			hex &= hex_mask;
			hex = ~hex - 1;
		} else {
			hex = (uint32_t)(f * (1 << fractional_bit));
			hex &= hex_mask;
		}
	}
	return hex;
}

/**
 * \brief Calculate gain for RGGB bayer and perform them with ISC WB module.
 */
static void _awb_update(void)
{
	uint32_t count[BAYER_COUNT];
	float gain[BAYER_COUNT];
	uint32_t gain_049[BAYER_COUNT];

	count[HISTOGRAM_R] = (awb.count[HISTOGRAM_R] + awb.backup[HISTOGRAM_R]) / 2;
	count[HISTOGRAM_GB] = (awb.count[HISTOGRAM_GB] +  awb.backup[HISTOGRAM_GB]) / 2;
	count[HISTOGRAM_GR] = (awb.count[HISTOGRAM_GR] + awb.backup[HISTOGRAM_GR]) / 2;
	count[HISTOGRAM_B] = (awb.count[HISTOGRAM_B] + awb.backup[HISTOGRAM_B]) / 2;

	gain[HISTOGRAM_R] = (float)(count[HISTOGRAM_GB]) / (float)(count[HISTOGRAM_R]);
	gain[HISTOGRAM_GB] = 1.0000000;
	gain[HISTOGRAM_GR] = 1.0000000;
	gain[HISTOGRAM_B] = (float)(count[HISTOGRAM_GB]) / (float)(count[HISTOGRAM_B]);

	/* Convert R/G/BGAIN component gain to unsigned 13 bits (0:4:9) */
	gain_049[HISTOGRAM_R] = _float2hex(0, 4, 9, gain[HISTOGRAM_R]);
	gain_049[HISTOGRAM_GB] = _float2hex(0, 4, 9, gain[HISTOGRAM_GB]);
	gain_049[HISTOGRAM_GR] = _float2hex(0, 4, 9, gain[HISTOGRAM_GR]);
	gain_049[HISTOGRAM_B] = _float2hex(0, 4, 9, gain[HISTOGRAM_B]);

	isc_wb_adjust_bayer_color(0, 0, 0, 0, gain_049[HISTOGRAM_R], gain_049[HISTOGRAM_GR],
                                  gain_049[HISTOGRAM_B], gain_049[HISTOGRAM_GB]);
	isc_update_profile();

	awb.backup[HISTOGRAM_R] = awb.count[HISTOGRAM_R];
	awb.backup[HISTOGRAM_GB] = awb.count[HISTOGRAM_GB];
	awb.backup[HISTOGRAM_GR] = awb.count[HISTOGRAM_GR];
	awb.backup[HISTOGRAM_B] = awb.count[HISTOGRAM_B];
}

/**
 * \brief Count up 4 channel R/G/Gr/Gb histogram data.
 */
static void _awb_count_up(uint32_t* buf)
{
	uint32_t i;

	awb.count[awb.op_mode] = 0;
	for (i = 0; i < HIST_ENTRIES; i++)
		awb.count[awb.op_mode] += (*buf++) * i;
}

/**
 * \brief ISC interrupt handler.
 */
static void _isc_handler(uint32_t source, void* arg)
{
	struct _iscd_desc* iscd = (struct _iscd_desc*)arg;
	uint32_t status;

	status = isc_interrupt_status();
	if ((status & ISC_INTSR_VD) == ISC_INTSR_VD) {
		if (iscd->pipe.frame_idx == (iscd->cfg.multi_bufs - 1))
			iscd->pipe.frame_idx = 0;
		else
			iscd->pipe.frame_idx++;
		if (iscd->dma.callback)
			iscd->dma.callback(iscd->pipe.frame_idx);
	}
	if ((status & ISC_INTSR_HISDONE) == ISC_INTSR_HISDONE)
		awb.dma.dma_histo_ready = true;
}

/**
 * \brief Setup DMA Descriptors.
 */
static uint8_t _iscd_configure_dma(struct _iscd_desc* desc)
{
	uint32_t i;
	struct _isc_dma_view0* dma_view0;
	struct _isc_dma_view1* dma_view1;
	struct _isc_dma_view2* dma_view2;

	switch (desc->cfg.layout) {
	case ISCD_LAYOUT_PACKED8:
	case ISCD_LAYOUT_PACKED16:
	case ISCD_LAYOUT_PACKED32:
		dma_view0 = _isc_dma_view_pool.view0;
		for (i = 0; i < desc->cfg.multi_bufs; i++) {
			dma_view0[i].ctrl = ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE;
			dma_view0[i].next_desc = (uint32_t)&dma_view0[i + 1];
			dma_view0[i].addr = (uint32_t)desc->dma.address0 + i * desc->dma.size;
			dma_view0[i].stride = 0;
		}
		dma_view0[i - 1].next_desc = (uint32_t)&dma_view0[0];
		cache_clean_region(dma_view0, sizeof(struct _isc_dma_view0) * desc->cfg.multi_bufs);
		isc_dma_configure_desc_entry((uint32_t)&dma_view0[0]);
		isc_dma_configure_input_mode(ISC_DCFG_IMODE(desc->cfg.layout) |
		                             ISC_DCFG_YMBSIZE_BEATS8);
		isc_dma_enable(ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE);
		break;

	case ISCD_LAYOUT_YC420SP:
	case ISCD_LAYOUT_YC422SP:
		/* Set DAM for 16-bit YC422SP/YC420SP with stream descriptor view 1
			for YCbCr planar pixel stream */
		dma_view1 = _isc_dma_view_pool.view1;
		for(i = 0; i < desc->cfg.multi_bufs; i++) {
			dma_view1[i].ctrl = ISC_DCTRL_DVIEW_SEMIPLANAR | ISC_DCTRL_DE;
			dma_view1[i].next_desc = (uint32_t)&dma_view1[i + 1];
			dma_view1[i].addr0 = (uint32_t)desc->dma.address0 + i * desc->dma.size;
			dma_view1[i].stride0 = 0;
			dma_view1[i].addr1 = (uint32_t)desc->dma.address1 + i * desc->dma.size;;
			dma_view1[i].stride1 = 0;
		}
		dma_view1[i - 1].next_desc = (uint32_t)&dma_view1[0];
		cache_clean_region(dma_view1, sizeof(struct _isc_dma_view1) * desc->cfg.multi_bufs);
		isc_dma_configure_desc_entry((uint32_t)&dma_view1[0]);
		isc_dma_configure_input_mode(ISC_DCFG_IMODE(desc->cfg.layout) |
		                             ISC_DCFG_YMBSIZE_BEATS8 | ISC_DCFG_CMBSIZE_BEATS8);
		isc_dma_enable(ISC_DCTRL_DVIEW_SEMIPLANAR | ISC_DCTRL_DE);
		break;

	case ISCD_LAYOUT_YC422P:
	case ISCD_LAYOUT_YC420P:
		/* Set DAM for 16-bit YC422P/YC420P with stream descriptor view 2
			for YCbCr planar pixel stream */
		dma_view2 = _isc_dma_view_pool.view2;
		for(i = 0; i < desc->cfg.multi_bufs; i++) {
			dma_view2[i].ctrl = ISC_DCTRL_DVIEW_PLANAR | ISC_DCTRL_DE;
			dma_view2[i].next_desc = (uint32_t)&dma_view2[i + 1];
			dma_view2[i].addr0 = (uint32_t)desc->dma.address0 + i * desc->dma.size;;
			dma_view2[i].stride0 = 0;
			dma_view2[i].addr1 = (uint32_t)desc->dma.address1 + i * desc->dma.size;;
			dma_view2[i].stride1 = 0;
			dma_view2[i].addr2 = (uint32_t)desc->dma.address2 + i * desc->dma.size;;
			dma_view2[i].stride2 = 0;
		}
		dma_view2[i - 1].next_desc = (uint32_t)&dma_view2[0];
		cache_clean_region(dma_view2, sizeof(struct _isc_dma_view2) * desc->cfg.multi_bufs);
		isc_dma_configure_desc_entry((uint32_t)&dma_view2[0]);
		isc_dma_configure_input_mode(ISC_DCFG_IMODE(desc->cfg.layout) |
		                             ISC_DCFG_YMBSIZE_BEATS8 | ISC_DCFG_CMBSIZE_BEATS8);
		isc_dma_enable(ISC_DCTRL_DVIEW_PLANAR | ISC_DCTRL_DE);
		break;

	default:
		return ISCD_ERROR_CONFIG;
	}

	return ISCD_OK;
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

uint8_t iscd_pipe_start(struct _iscd_desc* desc)
{
	uint32_t i;
	uint32_t* gg;
	uint32_t* rg;
	uint32_t* bg;
	struct _callback _cb;

	irq_disable(ID_ISC);
	isc_software_reset();

	/* Set Continuous Acquisition mode */
	isc_pfe_set_continuous_shot();
	isc_cfa_enabled(0);
	isc_wb_enabled(0);
	isc_gamma_enabled(0, 0);
	isc_csc_enabled(0);
	isc_sub422_enabled(0);
	isc_sub420_configure(0, 0);
	isc_update_profile();

	if (desc->pipe.histo_enable) {
		if (!awb.dma.dma_histo_channel) {
			/* Allocate a XDMA channel for histogram read. */
			awb.dma.dma_histo_channel =
				dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
			callback_set(&_cb, _dma_histo_callback, (void*)desc);
			dma_set_callback(awb.dma.dma_histo_channel, &_cb);
			if (!awb.dma.dma_histo_channel) {
				trace_error("Can't allocate DMA channel \n\r");
				return ISCD_ERROR_CONFIG;
			}
		}
		isc_histogram_enabled(1);
		isc_clear_histogram_table();
	}

	/* Configurer the Parallel Front End module performs data
	 * re-sampling across clock domain boundary. ISC_PFE_CFG0.BPS
	 * shows the number of bits per sample depends on the bit
	 * width of sensor output. The PFE module outputs a 12-bit
	 * data on the vp_data[11:0] bus */
	isc_pfe_set_video_mode(ISC_PFE_CFG0_MODE_PROGRESSIVE);
	isc_pfe_set_bps(ISC_PFE_CFG0_BPS(4 - desc->cfg.input_bits));
	isc_pfe_set_sync_polarity(0, ISC_PFE_CFG0_VPOL);

	if (desc->pipe.gamma.gamma_enable) {
		if (!desc->pipe.gamma.rg_table ||
		    !desc->pipe.gamma.gg_table ||
		    !desc->pipe.gamma.bg_table) {
			isc_gamma_enabled(1, 0);
		} else {
			rg = desc->pipe.gamma.rg_table;
			bg = desc->pipe.gamma.bg_table;
			gg = desc->pipe.gamma.gg_table;

			isc_gamma_enabled(1, ISC_GAM_CTRL_RENABLE |
			                     ISC_GAM_CTRL_GENABLE |
			                     ISC_GAM_CTRL_BENABLE);
			for (i = 0; i< GAMMA_ENTRIES; i++) {
				ISC->ISC_GAM_RENTRY[i] = *rg++;
				ISC->ISC_GAM_GENTRY[i] = *gg++;
				ISC->ISC_GAM_BENTRY[i] = *bg++;
			}
		}
	} else {
		isc_gamma_enabled(0, 0);
	}

	switch (desc->cfg.input_format) {
	case RAW_BAYER:
		/* In a single-sensor system, each cell on the sensor
		 * has a specific color filter and microlens
		 * positioned above it. The raw data obtained from the
		 * sensor do not have the full R/G/B information at
		 * each cell position. Color interpolation is required
		 * to retrieve the missing components. */
		isc_cfa_enabled(1);
		isc_cfa_configure(desc->pipe.bayer_pattern, 1);

		/* The White Balance (WB) module captures the data bus
		 * from the PFE module, each Bayer color component (R,
		 * Gr, B, Gb) can be manually adjusted using an offset
		 * and a gain. */
		isc_wb_enabled(1);
		isc_wb_set_bayer_pattern(desc->pipe.bayer_pattern);

		/* Default value for White balance setting */
		isc_wb_adjust_bayer_color(0, 0, 0, 0, 0x200, 0x200, 0x200, 0x200);
		isc_cbc_enabled(1);
		/* Convert bright to signed 11 bits 1:10:0.
			Convert contrast to unsigned 12 bits 0:4:8 */
		isc_cbc_configure(0, 0,
		                  _float2hex(1, 10, 0, desc->pipe.cbc.bright),
		                  _float2hex(0, 4, 8, desc->pipe.cbc.contrast));
		isc_cc_enabled(1);
		isc_cc_configure(desc->pipe.color_correction);

		if (desc->cfg.layout == ISCD_LAYOUT_YC422SP ||
		    desc->cfg.layout == ISCD_LAYOUT_YC420SP ||
		    desc->cfg.layout == ISCD_LAYOUT_YC422P ||
		    desc->cfg.layout == ISCD_LAYOUT_YC420P) {
			/* By converting an image from RGB to YCbCr
			 * color space, it is possible to separate Y,
			 * Cb and Cr information. */
			isc_csc_enabled(1);
			isc_csc_configure(desc->pipe.cs);
			/* The color space conversion output stream is
			 * a full-bandwidth YCbCr 4:4:4 signal. The
			 * chrominance subsampling divides the
			 * horizontal chrominance sampling rate by
			 * two */
			isc_sub422_enabled(1);
			if (desc->cfg.layout == ISCD_LAYOUT_YC420SP ||
			    desc->cfg.layout == ISCD_LAYOUT_YC420P)
				isc_sub420_configure(1, 0);
		}
		break;

	case YUV_422:
		isc_cfa_enabled(0);
		isc_wb_enabled(0);
		isc_gamma_enabled(0, 0);
		isc_csc_enabled(0);
		isc_csc_enabled(0);
		isc_sub422_enabled(0);
		isc_sub420_configure(0, 0);
		break;

	default:
		/* TODO */
		break;
	}
	isc_rlp_configure(desc->pipe.rlp_mode, 0);

	_iscd_configure_dma(desc);

	awb.state = AWB_INIT;
	awb.op_mode = 0;
	desc->pipe.frame_idx = 0;

	isc_update_profile();
	irq_add_handler(ID_ISC, _isc_handler, desc);
	isc_enable_interrupt(ISC_INTEN_VD | ISC_INTEN_HISDONE);
	isc_interrupt_status();

	irq_enable(ID_ISC);
	isc_start_capture();

	return ISCD_OK;
}

/**
 * \brief Image tuning for AWB, this is a reference algrothm only.
 */
void iscd_auto_white_balance_ref_algo(uint32_t* histo_buf)
{
	switch (awb.state) {
	case AWB_INIT:
		isc_histogram_configure(awb.op_mode, ISC_HIS_CFG_BAYSEL_BGBG, 1);
		isc_update_profile();
		awb.dma.dma_histo_ready = false;
		awb.dma.dma_histo_done = false;
		isc_update_histogram_table();
		awb.state = AWB_WAIT_HIS_READY;
		break;
	case AWB_WAIT_HIS_READY:
		if (!awb.dma.dma_histo_ready)
			break;
		awb.dma.dma_histo_ready = false;
		_iscd_dma_read_histogram((uint32_t)histo_buf);
		awb.state = AWB_WAIT_DMA_READY;
		break;
	case AWB_WAIT_DMA_READY:
		if (!awb.dma.dma_histo_done)
			break;
		awb.dma.dma_histo_done = false;
		_awb_count_up(histo_buf);
		awb.op_mode++;
		if (awb.op_mode < BAYER_COUNT)
			awb.state = AWB_INIT;
		else
			awb.state = AWB_WAIT_ISC_PERFORMED;
		break;
	case AWB_WAIT_ISC_PERFORMED:
		_awb_update();
		awb.op_mode = 0;
		awb.state = AWB_INIT;
		break;
	}
}
