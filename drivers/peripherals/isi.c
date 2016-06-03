/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
#include "peripherals/isi.h"

#include "trace.h"

/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enable ISI
 */
void isi_enable(void)
{
	ISI->ISI_CR |= ISI_CR_ISI_EN;
	while ((ISI->ISI_SR & ISI_SR_ENABLE) != ISI_SR_ENABLE);
}

/**
 * \brief Disable ISI
 */
void isi_disable(void)
{
	/* Write one to this field to disable the module */
	ISI->ISI_CR |= ISI_CR_ISI_DIS;
	/* Software must poll DIS_DONE field in the ISI_STATUS register to verify that the command
	has successfully completed.*/
	while ((ISI->ISI_SR & ISI_SR_DIS_DONE) != ISI_SR_DIS_DONE);
}

/**
 * \brief Enable ISI Dma channel
 * \param  channel to be enabled
 */
void isi_dma_channel_enable(uint32_t channel)
{
	ISI->ISI_DMA_CHER = channel;
}

/**
 * \brief Disable ISI Dma channel
 * \param  channel to be disabled
 */
void isi_dma_channel_disable(uint32_t channel)
{
	ISI->ISI_DMA_CHDR = channel;
}

/**
 * \brief Enables/disable DMA channel for preview path.
 * \param  enabled 1: Enable 0: disable
 */
void isi_dma_preview_channel_enabled(uint8_t enabled)
{
	if (enabled)
		ISI->ISI_DMA_CHER = ISI->ISI_DMA_CHSR | ISI_DMA_CHER_P_CH_EN;
	else
		ISI->ISI_DMA_CHDR = ISI_DMA_CHDR_P_CH_DIS;
}

/**
 * \brief Enables/disable DMA channel for code path.
 * \param  enabled 1: Enable 0: disable
 */
void isi_dma_codec_channel_enabled(uint8_t enabled)
{
	if (enabled)
		ISI->ISI_DMA_CHER = ISI->ISI_DMA_CHSR | ISI_DMA_CHER_C_CH_EN;
	else
		ISI->ISI_DMA_CHDR = ISI_DMA_CHDR_C_CH_DIS;
}

/**
 * \brief Enable ISI interrupt
 * \param  flag of interrupt to enable
 */
void isi_enable_interrupt(uint32_t flag)
{
	ISI->ISI_IER = flag;
}

/**
 * \brief Disable ISI interrupt
 * \param  flag of interrupt to disable
 */
void isi_disable_interrupt(uint32_t flag)
{
	ISI->ISI_IDR = flag;
}

/**
 * \brief Return ISI status register
 * \return Status of ISI register
 */
uint32_t isi_get_status(void)
{
	return ISI->ISI_SR;
}

/**
 * \brief ISI wait for coded channel transfer done
 */
void isi_codec_wait_dma_completed(void)
{
	while ((ISI->ISI_SR & ISI_SR_CXFR_DONE) != ISI_SR_CXFR_DONE);
}

/**
 * \brief ISI wait for preview channel transfer done
 */
void isi_preview_wait_dma_completed(void)
{
	while ((ISI->ISI_SR & ISI_SR_CXFR_DONE) != ISI_SR_CXFR_DONE);
}

/**
 * \brief Enable Codec path for capture next frame
 */
void isi_codec_path_full(void)
{
	// The codec path is enabled and the next frame is captured.
	// Both codec and preview data-paths are working simultaneously
	ISI->ISI_CR = ISI_CR_ISI_CDC;
	ISI->ISI_CFG1 |= ISI_CFG1_FULL;
}

/**
 * \brief enable the codec datapath and capture a Full resolution Frame
 */
void isi_codec_request(void)
{
	ISI->ISI_CR = ISI_CR_ISI_CDC;
	// Indicates that the request has been taken into account but cannot be serviced 
	// within the current frame. The operation is postponed
	while ((ISI->ISI_SR & ISI_SR_CDC_PND) != ISI_SR_CDC_PND);
}

/**
 * \brief Set frame rate
 * \param frame frame rate capture
 */
void isi_set_framerate(uint32_t frame)
{
	uint32_t isicfg1 = ISI->ISI_CFG1 & ~ISI_CFG1_FRATE_Msk;
	if (frame > 7) {
		trace_error("rate too big\n\r");
		frame = 7;
	}
	ISI->ISI_CFG1 = isicfg1 | ISI_CFG1_FRATE(frame);
}

/**
 * \brief Get the number of byte per pixels
 * \param bmp_rgb BMP type can be YUV or RGB
 */
uint8_t isi_bytes_one_pixel(uint8_t bmp_rgb)
{
	uint8_t number_byte_per_pixel;

	if (bmp_rgb == RGB_INPUT) {
		if ((ISI->ISI_CFG2 & ISI_CFG2_RGB_MODE) == ISI_CFG2_RGB_MODE) {
			// RGB: 5:6:5 16bits/pixels
			number_byte_per_pixel = 2;
		} else {
			// RGB: 8:8:8 24bits/pixels
			number_byte_per_pixel = 3;
		}
	} else {
		// YUV: 2 pixels for 4 bytes
		number_byte_per_pixel = 2;
	}
	return number_byte_per_pixel;
}

/**
 * \brief Reset ISI
 */
void isi_reset(void)
{
	uint32_t timeout = 0;

	// Resets the image sensor interface.
	// Finish capturing the current frame and then shut down the module.
	ISI->ISI_CR = ISI_CR_ISI_SRST | ISI_CR_ISI_DIS;
	// wait Software reset has completed successfully.
	while( (!(ISI->ISI_SR & ISI_SR_SRST))
			&& (timeout < 0x50000) ) {
		timeout++;
	}
	if( timeout == 0x50000) {
		trace_error("ISI-Reset timeout\n\r");
	}
}

/**
 * \brief Set the windows blank
 * \param horizontal_bank  pixel clock periods to wait before the beginning of a line.
 * \param vertical_bank  lines are skipped at the beginning of the frame.
 */
void isi_set_blank(uint8_t horizontal_bank, uint8_t vertical_bank)
{
	uint32_t isicfg1 = ISI->ISI_CFG1 & ~(ISI_CFG1_SLD_Msk | ISI_CFG1_SFD_Msk);
	ISI->ISI_CFG1 = isicfg1
	              | ISI_CFG1_SLD(horizontal_bank)
	              | ISI_CFG1_SFD(vertical_bank);
}

/**
 * \brief Set vertical and horizontal Size of the Image Sensor
 * \param horizontal_size  Horizontal size of the Image sensor [0..2047].
 * \param vertical_size  Vertical size of the Image sensor [0..2047].
 */
void isi_set_sensor_size(uint32_t horizontal_size, uint32_t vertical_size)
{
	uint32_t isicfg2 = ISI->ISI_CFG2 & ~(ISI_CFG2_IM_VSIZE_Msk | ISI_CFG2_IM_HSIZE_Msk);
	// IM_VSIZE: Vertical size of the Image sensor [0..2047]
	// Vertical size = IM_VSIZE + 1
	// IM_HSIZE: Horizontal size of the Image sensor [0..2047]
	// Horizontal size = IM_HSIZE + 1
	ISI->ISI_CFG2 = isicfg2
	              | ISI_CFG2_IM_VSIZE(vertical_size - 1)
	              | ISI_CFG2_IM_HSIZE(horizontal_size - 1);
}

/**
 * \brief Defines RGB pattern when RGB_MODE is set to 1.
 * \param rgb_pixel_pattern  RGB pattern
 */
void isi_rgb_pixel_mapping(uint32_t rgb_pixel_pattern)
{
	uint32_t isicfg2 = ISI->ISI_CFG2 & ~ISI_CFG2_RGB_CFG_Msk;
	ISI->ISI_CFG2 = isicfg2 | rgb_pixel_pattern | ISI_CFG2_RGB_MODE;
}

/**
 * \brief Enables RGB swap
 * \param rgb_swap  0: D7-R7, 1: D0-R7
 */
void isi_rgb_swap_mode(uint32_t rgb_swap)
{
	if (rgb_swap)
		ISI->ISI_CFG2 |= ISI_CFG2_RGB_SWAP;
	else
		ISI->ISI_CFG2 &= ~ISI_CFG2_RGB_SWAP;
}

/**
 * \brief Defines YCrCb swap format.
 * \param yuv_swap YUV Swap format
 */
void isi_ycrcb_format(uint32_t yuv_swap)
{
	uint32_t isicfg2 = ISI->ISI_CFG2 & ~ISI_CFG2_YCC_SWAP_Msk;
	ISI->ISI_CFG2 = isicfg2 | (yuv_swap & ISI_CFG2_YCC_SWAP_Msk);
}

/**
 * \brief Input image is assumed to be grayscale-coded.
 * \param pixel_format  0: 2 pixels per word, 1:1 pixel per word.
 */
void isi_set_grayscale_mode(uint32_t pixel_format)
{
	if (pixel_format)
		ISI->ISI_CFG2 |= ISI_CFG2_GS_MODE;
	else
		ISI->ISI_CFG2 &= ~ISI_CFG2_GS_MODE;
}

/**
 * \brief Set data stream format.
 * \param stream_mode  0: YUV input, 1: RGB 8:8:8/5:6:5 input
 */
void isi_set_input_stream(uint32_t stream_mode)
{
	if (stream_mode)
		ISI->ISI_CFG2 |= ISI_CFG2_COL_SPACE;
	else
		ISI->ISI_CFG2 &= ~ISI_CFG2_COL_SPACE;
}

/**
 * \brief Set preview size.
 * \param horizontal_size  Horizontal Preview size  (640 max only in RGB mode).
 * \param vertical_size  Vertical Preview size  (480 max only in RGB mode).
 */
void isi_set_preview_size(uint32_t horizontal_size, uint32_t vertical_size)
{
	if (horizontal_size > 640)
		horizontal_size = 640;

	if (vertical_size > 480)
		vertical_size = 480;

	ISI->ISI_PSIZE = ISI_PSIZE_PREV_VSIZE(vertical_size - 1)
	               | ISI_PSIZE_PREV_HSIZE(horizontal_size - 1);
}

/**
 * \brief calculate scaler factor automatically.
 * \note The sensor size and preview size for LCD was configured before this setting.
 */
void isi_calc_scaler_factor(void)
{
	uint32_t horizontal_lcd_size, horizontal_sensor_size;
	uint32_t vertical_lcd_size, vertical_sensor_size;
	uint32_t horizontal_ratio, vertical_ratio, ratio;

	horizontal_lcd_size = ((ISI->ISI_PSIZE & ISI_PSIZE_PREV_HSIZE_Msk) >> ISI_PSIZE_PREV_HSIZE_Pos) + 1;
	horizontal_sensor_size = ((ISI->ISI_CFG2 & ISI_CFG2_IM_HSIZE_Msk ) >> ISI_CFG2_IM_HSIZE_Pos) + 1;

	vertical_lcd_size = ((ISI->ISI_PSIZE & ISI_PSIZE_PREV_VSIZE_Msk) >> ISI_PSIZE_PREV_VSIZE_Pos) + 1;
	vertical_sensor_size = ((ISI->ISI_CFG2 & ISI_CFG2_IM_VSIZE_Msk ) >> ISI_CFG2_IM_VSIZE_Pos) + 1;

	horizontal_ratio = (1600 * horizontal_sensor_size ) / horizontal_lcd_size;
	vertical_ratio = (1600 * vertical_sensor_size ) / vertical_lcd_size;
	ratio = (horizontal_ratio > vertical_ratio) ? vertical_ratio : horizontal_ratio;
	ratio = (ratio > 16) ? ratio : 16;
	ISI->ISI_PDECF = ratio / 100;
}

/**
 * \brief Configure DMA for preview path.
 * \param descriptor_address  Preview Descriptor Address.
 * \param descriptor_dma_control  DMA Preview Control.
 * \param frame_buffer_address  DMA Preview Base Address.
 */
void isi_set_dma_preview_path(uint32_t descriptor_address,
		uint32_t descriptor_dma_control,
		uint32_t frame_buffer_address)
{
	ISI->ISI_DMA_P_DSCR = descriptor_address;
	ISI->ISI_DMA_P_CTRL = descriptor_dma_control;
	ISI->ISI_DMA_P_ADDR = frame_buffer_address;
}

/**
 * \brief Configure DMA for Codec path.
 * \param descriptor_address  Preview Descriptor Address.
 * \param descriptor_dma_control  DMA Preview Control.
 * \param frame_buffer_address  DMA Preview Base Address.
 */
void isi_set_dma_codec_path(uint32_t descriptor_address,
		uint32_t descriptor_dma_control,
		uint32_t frame_buffer_address)
{
	ISI->ISI_DMA_C_DSCR = descriptor_address;
	ISI->ISI_DMA_C_CTRL = descriptor_dma_control;
	ISI->ISI_DMA_C_ADDR = frame_buffer_address;
}

/**
 * \brief ISI set matrix for YUV to RGB color space for preview path.
 * \param yuv2rgb structure of YUV to RBG parameters.
 */
void isi_set_matrix_yuv2rgb(struct _isi_yuv2rgb *yuv2rgb)
{
	ISI->ISI_Y2R_SET0 = ISI_Y2R_SET0_C0(yuv2rgb->c0)
	                  | ISI_Y2R_SET0_C1(yuv2rgb->c1)
	                  | ISI_Y2R_SET0_C2(yuv2rgb->c2)
	                  | ISI_Y2R_SET0_C3(yuv2rgb->c3);

	ISI->ISI_Y2R_SET1 = ISI_Y2R_SET1_C4(yuv2rgb->c4)
	                  | (yuv2rgb->yoff == 1 ? ISI_Y2R_SET1_Yoff : 0)
	                  | (yuv2rgb->croff == 1 ? ISI_Y2R_SET1_Croff : 0)
	                  | (yuv2rgb->cboff == 1 ? ISI_Y2R_SET1_Cboff : 0);
}

/**
 * \brief ISI set matrix for RGB to YUV color space for codec path.
 * \param rgb2yuv structure of RGB to YUV parameters.
 */
void isi_set_matrix_rgb2yuv(struct _isi_rgb2yuv *rgb2yuv)
{
	ISI->ISI_R2Y_SET0 = ISI_R2Y_SET0_C0(rgb2yuv->c0)
	                  | ISI_R2Y_SET0_C1(rgb2yuv->c1)
	                  | ISI_R2Y_SET0_C2(rgb2yuv->c2)
	                  | (rgb2yuv->roff == 1 ? ISI_R2Y_SET0_Roff : 0);

	ISI->ISI_R2Y_SET1 = ISI_R2Y_SET1_C3(rgb2yuv->c3)
	                  | ISI_R2Y_SET1_C4(rgb2yuv->c4)
	                  | ISI_R2Y_SET1_C5(rgb2yuv->c5)
	                  | (rgb2yuv->goff == 1 ? ISI_R2Y_SET1_Goff : 0);

	ISI->ISI_R2Y_SET2 = ISI_R2Y_SET2_C6(rgb2yuv->c6)
	                  | ISI_R2Y_SET2_C7(rgb2yuv->c7)
	                  | ISI_R2Y_SET2_C8(rgb2yuv->c8)
	                  | (rgb2yuv->boff == 1 ? ISI_R2Y_SET2_Boff : 0);
}
