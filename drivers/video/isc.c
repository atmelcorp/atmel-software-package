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
#include "video/isc.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* \brief Writing to the ISC_CTRLEN or ISC_CTRLDIS register requires a double domain 
  * synchronization, so it is forbidden to write these registers when the ISC_CTRLSR.SIP
  * bit is asserted.
*/
static bool isc_is_sip_asserted(void)
{
	return (ISC->ISC_CTRLSR & ISC_CTRLSR_SIP) == ISC_CTRLSR_SIP;
}

/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/

/*------------------------------------------
 *         ISC Control functions
 *----------------------------------------*/
/**
 * \brief Send Capture Input Stream Command to start a single shot capture or a
 * multiple frame.
 */
void isc_start_capture(void)
{
	while (isc_is_sip_asserted());
	ISC->ISC_CTRLEN = ISC_CTRLEN_CAPTURE;
}

/**
 * \brief end the capture at the next Vertical Synchronization Detection.
 */
void isc_stop_capture(void)
{
	while (isc_is_sip_asserted());
	ISC->ISC_CTRLDIS = ISC_CTRLDIS_DISABLE;
}

/**
 * \brief Returns ISC Control Status.
 */
uint32_t isc_get_ctrl_status(void)
{
	return ISC->ISC_CTRLSR;
}

/**
 * \brief update the color profile.
 */
void isc_update_profile(void)
{
	while (isc_is_sip_asserted());
	ISC->ISC_CTRLEN = ISC_CTRLEN_UPPRO;
	while ((ISC->ISC_CTRLSR & ISC_CTRLSR_UPPRO) == ISC_CTRLSR_UPPRO);
}

/**
 * \brief Perform software reset of the interface.
 */
void isc_software_reset(void)
{
	while (isc_is_sip_asserted());
	ISC->ISC_CTRLDIS = ISC_CTRLDIS_SWRST;
}

/*------------------------------------------
 *      PFE(Parallel Front End) functions
 *----------------------------------------*/

/**
 * \brief configure PFE(Parallel Front End) video mode.
 * \param vmode: Parallel Front End Mode
 */
void isc_pfe_set_video_mode(uint32_t vmode)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_MODE_Msk;
	ISC->ISC_PFE_CFG0 |= vmode;
}

/**
 * \brief set PFE(Parallel Front End) H/V synchronization polarity.
 * \param hpol: Horizontal Synchronization Polarity
 * \param vpol: Vertical Synchronization Polarity
 */
void isc_pfe_set_sync_polarity(uint32_t hpol, uint32_t vpol)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_HPOL;
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_VPOL;
	ISC->ISC_PFE_CFG0 |= hpol | vpol;
}

/**
 * \brief set PFE(Parallel Front End) pixel clock polarity.
 * \param ppol: pixel clock Polarity, The pixel stream is sampled on the
 *  rising or falling edge of the pixel clock
 */
void isc_pfe_set_pixel_polarity(uint32_t ppol)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_PPOL;
	ISC->ISC_PFE_CFG0 |= ppol ;
}

/**
 * \brief set PFE(Parallel Front End) field polarity.
 * \param fpol: Top/bottom field polarity configuration.
 */
void isc_pfe_set_field_polarity(uint32_t fpol)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_FPOL;
	ISC->ISC_PFE_CFG0 |= fpol ;
}

/**
 * \brief Enables/disable PFE(Parallel Front End) cropping
 * \param enable_column: Column Cropping enable/disable(1/0)
 * \param enable_row: Row Cropping enable/disable(1/0)
 */
void isc_pfe_set_cropping_enabled(uint8_t enable_column, uint8_t enable_row)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_COLEN;
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_ROWEN;
	if (enable_column)
		ISC->ISC_PFE_CFG0 |= ISC_PFE_CFG0_COLEN;
	if (enable_row)
		ISC->ISC_PFE_CFG0 |= ISC_PFE_CFG0_ROWEN;
}

/**
 * \brief set PFE(Parallel Front End) Bits Per Sample.
 * \param bps: Bits Per Sample.
 */
void isc_pfe_set_bps(uint32_t bps)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_BPS_Msk;
	ISC->ISC_PFE_CFG0 |= bps ;
}

/**
 * \brief set PFE(Parallel Front End)in single shot mode
 */
void isc_pfe_set_single_shot(void)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_CONT;
}

/**
 * \brief set PFE(Parallel Front End)in continuous mode
 */
void isc_pfe_set_continuous_shot(void)
{
	ISC->ISC_PFE_CFG0 |= ISC_PFE_CFG0_CONT;
}

/**
 * \brief set PFE(Parallel Front End) gated clock.
 * \param enable: enable/disable gated clock.
 */
void isc_pfe_set_gated_clock(uint8_t enable)
{
	ISC->ISC_PFE_CFG0 &= ~ISC_PFE_CFG0_GATED;
	if (enable)
		ISC->ISC_PFE_CFG0 |= ISC_PFE_CFG0_GATED;
}
/**
 * \brief  configure PFE(Parallel Front End) cropping area.
 * \param Hstart: Horizontal starting position of the cropping area
 * \param Hend: Horizontal ending position of the cropping area
 * \param Vstart: Vertical starting position of the cropping area
 * \param Hend: Vertical ending position of the cropping area
 */
void isc_pfe_set_cropping_area(uint32_t hstart, uint32_t hend,
                               uint32_t vstart, uint32_t vend)
{
	ISC->ISC_PFE_CFG1 = ISC_PFE_CFG1_COLMIN(hstart) | ISC_PFE_CFG1_COLMAX(hend);
	ISC->ISC_PFE_CFG2 = ISC_PFE_CFG2_ROWMIN(vstart) | ISC_PFE_CFG2_ROWMAX(vend);
}

/*------------------------------------------
 *         Clock configuration functions
 *----------------------------------------*/

/**
 * \brief Configure the ISP clock.
 * \param ispClockDiv ISP Clock Divider.
 * \param ispClockSelection ISP Clock Selection.
			0: HCLOCK is selected.
			1: GCK is selected.
 */
void isc_configure_isp_clock(uint32_t ispClockDiv, uint32_t ispClockSelection)
{
	uint32_t clkcfg = ISC->ISC_CLKCFG & ~(ISC_CLKCFG_ICDIV_Msk | ISC_CLKCFG_ICSEL);
	ISC->ISC_CLKCFG = clkcfg |
                          ISC_CLKCFG_ICDIV(ispClockDiv) |
                          (ispClockSelection << 8);
}

/**
 * \brief Enables the ISP clock.
 */
void isc_enable_isp_clock(void)
{
	ISC->ISC_CLKEN = ISC_CLKEN_ICEN;
}

/**
 * \brief Disables the ISP clock.
 */
void isc_disable_isp_clock(void)
{
	ISC->ISC_CLKDIS = ISC_CLKDIS_ICDIS;
}

/**
 * \brief Software reset the ISP clock.
 */
void isc_reset_isp_clock(void)
{
	ISC->ISC_CLKDIS = ISC_CLKDIS_ICSWRST;
}

/**
 * \brief Configure the Master clock.
 * \param masterClockDiv Master Clock Divider.
 * \param masterClockSelection Master Clock Selection.
			0: HCLOCK is selected.
			1: GCK is selected.
			2: 480-MHz system clock is selected.
 */
void isc_configure_master_clock(uint32_t masterClockDiv, uint32_t masterClockSelection)
{
	uint32_t clkcfg = ISC->ISC_CLKCFG & ~(ISC_CLKCFG_MCDIV_Msk | ISC_CLKCFG_MCSEL_Msk);
	ISC->ISC_CLKCFG = clkcfg |
                          ISC_CLKCFG_MCDIV(masterClockDiv) |
                          ISC_CLKCFG_MCSEL(masterClockSelection);
}

/**
 * \brief Enables the master clock.
 */
void isc_enable_master_clock(void)
{
	ISC->ISC_CLKEN = ISC_CLKEN_MCEN;
}

/**
 * \brief Disables the master clock.
 */
void isc_disable_master_clock(void)
{
	ISC->ISC_CLKDIS = ISC_CLKDIS_MCDIS;
}

/**
 * \brief Software reset the master clock.
 */
void isc_reset_master_clock(void)
{
	ISC->ISC_CLKDIS = ISC_CLKDIS_MCSWRST;
}

/**
 * \brief Returns ISC clock Status.
 */
uint32_t isc_get_clock_status(void)
{
	return ISC->ISC_CLKSR;
}

/*------------------------------------------
 *         Interrupt functions
 *----------------------------------------*/
/**
 * \brief Enable ISC interrupt
 * \param  flag of interrupt to enable
 */
void isc_enable_interrupt(uint32_t flag)
{
	ISC->ISC_INTEN = flag;
}

/**
 * \brief Disable ISC interrupt
 * \param  flag of interrupt to disable
 */
void isc_disable_interrupt(uint32_t flag)
{
	ISC->ISC_INTDIS = flag;
}

/**
 * \brief Return ISC status register
 * \return Status of ISC register
 */
uint32_t isc_interrupt_status(void)
{
	return ISC->ISC_INTSR;
}

/*------------------------------------------
 *         White Balance functions
 *----------------------------------------*/
/**
 * \brief Enables/disable White Balance.
 */
void isc_wb_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_WB_CTRL = ISC_WB_CTRL_ENABLE;
	else
		ISC->ISC_WB_CTRL = 0;
}

/**
 * \brief White Balance Bayer Configuration (Pixel Color Pattern).
 */
void isc_wb_set_bayer_pattern(uint8_t pattern)
{
	ISC->ISC_WB_CFG = pattern;
}

/**
 * \brief adjust White Balance with color component.
 * \param r_offset  Offset Red Component (signed 13 bits 1:12:0)
 * \param gr_offset Offset Green Component for Red Row (signed 13 bits 1:12:0)
 * \param b_offset  Offset Blue Component (signed 13 bits, 1:12:0)
 * \param gb_offset Offset Green Component for Blue Row (signed 13 bits, 1:12:0)
 * \param r_gain    Red Component Gain (unsigned 13 bits, 0:4:9)
 * \param gr_gain   Green Component (Red row) Gain (unsigned 13 bits, 0:4:9)
 * \param b_gain    Blue Component Gain (unsigned 13 bits, 0:4:9)
 * \param gb_gain   Green Component (Blue row) Gain (unsigned 13 bits, 0:4:9)
 */
void isc_wb_adjust_bayer_color(uint32_t r_offset, uint32_t gr_offset,
			       uint32_t b_offset, uint32_t gb_offset,
			       uint32_t r_gain, uint32_t gr_gain,
			       uint32_t b_gain, uint32_t gb_gain)
{
	ISC->ISC_WB_O_RGR = ISC_WB_O_RGR_ROFST(r_offset) |
	                    ISC_WB_O_RGR_GROFST(gr_offset);
	ISC->ISC_WB_O_BGB = ISC_WB_O_BGB_BOFST(b_offset) |
	                    ISC_WB_O_BGB_GBOFST(gb_offset);
	ISC->ISC_WB_G_RGR = ISC_WB_G_RGR_RGAIN(r_gain) |
	                    ISC_WB_G_RGR_GRGAIN(gr_gain);
	ISC->ISC_WB_G_BGB = ISC_WB_G_BGB_BGAIN(b_gain) |
	                    ISC_WB_G_BGB_GBGAIN(gb_gain);
}

/*------------------------------------------
 *         Color Filter Array functions
 *----------------------------------------*/

/**
 * \brief Enables/disable Color Filter Array Interpolation.
 */
void isc_cfa_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_CFA_CTRL = ISC_CFA_CTRL_ENABLE;
	else
		ISC->ISC_CFA_CTRL = 0;
}

/**
 * \brief configure color filter array interpolation.
 * \param pattern Color Filter Array Pattern
 * \param edge Edge Interpolation
			0: Edges are not interpolated.
			1: Edge interpolation is performed.
 */
void isc_cfa_configure(uint8_t pattern, uint8_t edge)
{
	ISC->ISC_CFA_CFG = pattern | (edge << 4);
}

/*------------------------------------------
 *         Color Correction functions
 *----------------------------------------*/
/**
 * \brief Enables/disable Color Correction.
 */
void isc_cc_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_CC_CTRL = ISC_CC_CTRL_ENABLE;
	else
		ISC->ISC_CC_CTRL = 0;
}

/**
 * \brief Color correction with color component.
 * \param cc Pointer to structure _color_correct
 */
void isc_cc_configure(struct _color_correct* cc)
{
	ISC->ISC_CC_RR_RG = ISC_CC_RR_RG_RRGAIN(cc->rr_gain) | ISC_CC_RR_RG_RGGAIN(cc->rg_gain);
	ISC->ISC_CC_RB_OR = ISC_CC_RB_OR_RBGAIN(cc->rb_gain) | ISC_CC_RB_OR_ROFST(cc->r_offset);
	ISC->ISC_CC_GR_GG = ISC_CC_GR_GG_GRGAIN(cc->gr_gain) | ISC_CC_GR_GG_GGGAIN(cc->gg_gain);
	ISC->ISC_CC_GB_OG = ISC_CC_GB_OG_GBGAIN(cc->gb_gain) | ISC_CC_GB_OG_ROFST(cc->g_offset);
	ISC->ISC_CC_BR_BG = ISC_CC_BR_BG_BRGAIN(cc->br_gain) | ISC_CC_BR_BG_BGGAIN(cc->bg_gain);
	ISC->ISC_CC_BB_OB = ISC_CC_BB_OB_BBGAIN(cc->bb_gain) | ISC_CC_BB_OB_BOFST(cc->b_offset);
}

/*------------------------------------------
 *         Gamma Correction functions
 *----------------------------------------*/
/**
 * \brief Enables/disable Gamma Correction with giving channels.
 * \param enabled 1: enable, 0: disable
 * \param channels ISC_GAM_CTRL_BENABLE/ISC_GAM_CTRL_GENABLE/ISC_GAM_CTRL_RENABLE
 */
void isc_gamma_enabled(uint8_t enabled, uint8_t channels)
{
	if (enabled)
		ISC->ISC_GAM_CTRL |= ISC_GAM_CTRL_ENABLE | channels;
	else
		ISC->ISC_GAM_CTRL = 0;
}

/**
 * \brief Configure gamma correction with give table.
 * \param r_gam_constant Pointer to red Color Constant instance (64 half-word).
 * \param r_gam_slope    Pointer to red Color Slope instance (64 half-word).
 * \param g_gam_constant Pointer to green Color Constant instance (64 half-word).
 * \param g_gam_slope    Pointer to green Color Slope instance (64 half-word).
 * \param b_gam_constant Pointer to blue Color Constant instance (64 half-word).
 * \param b_gam_slope    Pointer to blue Color Slope instance (64 half-word).
 */
void isc_gamma_configure(uint16_t* r_gam_constant, uint16_t* r_gam_slope,
                         uint16_t* g_gam_constant, uint16_t* g_gam_slope,
                         uint16_t* b_gam_constant, uint16_t* b_gam_slope)
{
	uint8_t i;
	for (i = 0; i < 64 ; i++) {
		ISC->ISC_GAM_BENTRY[i] = ISC_GAM_BENTRY_BCONSTANT(b_gam_constant[i]) |
		                         ISC_GAM_BENTRY_BSLOPE(b_gam_slope[i]);
		ISC->ISC_GAM_GENTRY[i] = ISC_GAM_GENTRY_GCONSTANT(b_gam_constant[i]) |
		                         ISC_GAM_GENTRY_GSLOPE(b_gam_slope[i]);
		ISC->ISC_GAM_RENTRY[i] = ISC_GAM_RENTRY_RCONSTANT(b_gam_constant[i]) |
		                         ISC_GAM_RENTRY_RSLOPE(b_gam_slope[i]);
	}
}

/*------------------------------------------
 *        Color Space Conversion functions
 *----------------------------------------*/

/**
 * \brief Enables/disable Color Space Conversion.
 */
void isc_csc_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_CSC_CTRL = ISC_CSC_CTRL_ENABLE;
	else
		ISC->ISC_CSC_CTRL = 0;
}

/**
 * \brief Color space convert with color space component.
 * \param cs Pointer to structure _color_space
 */
void isc_csc_configure(struct _color_space* cs)
{
	ISC->ISC_CSC_YR_YG = ISC_CSC_YR_YG_YRGAIN(cs->yr_gain) |
	                     ISC_CSC_YR_YG_YGGAIN(cs->yg_gain);
	ISC->ISC_CSC_YB_OY = ISC_CSC_YB_OY_YBGAIN(cs->yb_gain) |
	                     ISC_CSC_YB_OY_YOFST(cs->y_offset);
	ISC->ISC_CSC_CBR_CBG = ISC_CSC_CBR_CBG_CBRGAIN(cs->cbr_gain) |
	                       ISC_CSC_CBR_CBG_CBGGAIN(cs->cbg_gain);
	ISC->ISC_CSC_CBB_OCB = ISC_CSC_CBB_OCB_CBBGAIN(cs->cbb_gain) |
	                       ISC_CSC_CBB_OCB_CBOFST(cs->cb_offset);
	ISC->ISC_CSC_CRR_CRG = ISC_CSC_CRR_CRG_CRRGAIN(cs->crr_gain) |
	                       ISC_CSC_CRR_CRG_CRGGAIN(cs->crg_gain);
	ISC->ISC_CSC_CRB_OCR = ISC_CSC_CRB_OCR_CRBGAIN(cs->crb_gain) |
	                       ISC_CSC_CRB_OCR_CROFST(cs->cr_offset);
}

/*------------------------------------------
 *       Contrast And Brightness functions
 *----------------------------------------*/
/**
 * \brief Enables/disable contrast and brightness control.
 */
void isc_cbc_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_CBC_CTRL = ISC_CBC_CTRL_ENABLE;
	else
		ISC->ISC_CBC_CTRL = 0;
}

/**
 * \brief Configure Contrast and brightness with give parameter.
 * \param ccir656 CCIR656 Stream Enable.
				0: Raw mode
				1: CCIR mode
 * \param byte_order CCIR656 Byte Ordering.
 * \param brightness Brightness Control (signed 11 bits 1:10:0).
 * \param contrast Contrast (signed 12 bits 1:3:8).
 */
void isc_cbc_configure(uint8_t ccir656, uint8_t byte_order,
		       uint16_t brightness, uint16_t contrast)
{
	if (ccir656)
		ISC->ISC_CBC_CFG = ISC_CBC_CFG_CCIR | byte_order;
	else
		ISC->ISC_CBC_CFG = 0;
	ISC->ISC_CBC_BRIGHT = ISC_CBC_BRIGHT_BRIGHT(brightness);
	ISC->ISC_CBC_CONTRAST = ISC_CBC_CONTRAST_CONTRAST(contrast);
}

/*------------------------------------------
 *       Sub-sampling functions
 *----------------------------------------*/

/**
 * \brief Enables/disable 4:4:4 to 4:2:2 Chrominance Horizontal Subsampling Filter Enable.
 */
void isc_sub422_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_SUB422_CTRL = ISC_SUB422_CTRL_ENABLE;
	else
		ISC->ISC_SUB422_CTRL = 0;
}

/**
 * \brief Configure Subsampling 4:4:4 to 4:2:2 with giving value.
 * \param ccir656 CCIR656 Stream Enable.
				0: Raw mode
				1: CCIR mode
 * \param byte_order CCIR656 Byte Ordering.
 * \param lpf Low Pass Filter Selection.
 */
void isc_sub422_configure(uint8_t ccir656, uint8_t byte_order, uint8_t lpf)
{
	if (ccir656)
		ISC->ISC_SUB422_CFG = ISC_SUB422_CFG_CCIR | byte_order;
	else
		ISC->ISC_SUB422_CFG = 0;
	ISC->ISC_SUB422_CFG &= ~ISC_SUB422_CFG_FILTER_Msk;
	ISC->ISC_SUB422_CFG |= lpf;
}

/**
 * \brief Configure 4:2:2 to 4:2:0 Vertical Subsampling Filter Enable
		(Center Aligned) with giving value.
 * \param enabled Subsampler enabled.
				0: disabled
				1: enabled
 * \param filter Interlaced or Progressive Chrominance Filter.
		0: Progressive filter {0.5, 0.5}
		1: Field-dependent filter, top field filter is {0.75, 0.25},
			bottom field filter is {0.25, 0.75}
 */
void isc_sub420_configure(uint8_t enabled, uint8_t filter)
{
	if (enabled){
		ISC->ISC_SUB420_CTRL = ISC_SUB420_CTRL_ENABLE;
		if (filter)
			ISC->ISC_SUB420_CTRL |= ISC_SUB420_CTRL_FILTER;
	} else {
		ISC->ISC_SUB420_CTRL = 0;
	}
}

/*------------------------------------------
 * Rounding, Limiting and Packing functions
 *----------------------------------------*/

/**
 * \brief Configure Rounding, Limiting and Packing Mode.
 * \param rlp_mode Rounding, Limiting and Packing Mode.
 * \param alpha Alpha Value for Alpha-enabled RGB Mode.
 */
void isc_rlp_configure(uint8_t rlp_mode, uint8_t alpha)
{
	ISC->ISC_RLP_CFG = rlp_mode;
	if (alpha)
		ISC->ISC_RLP_CFG |= ISC_RLP_CFG_ALPHA(alpha);
}

/*------------------------------------------
 *         Histogram functions
 *----------------------------------------*/

/**
 * \brief Enables/disable Histogram
 */
void isc_histogram_enabled(uint8_t enabled)
{
	if (enabled)
		ISC->ISC_HIS_CTRL = ISC_HIS_CTRL_ENABLE;
	else
		ISC->ISC_HIS_CTRL = 0;
}

/**
 * \brief Configure Histogram.
 * \param mode Histogram Operating Mode.
 * \param baySel Bayer Color Component Selection.
 * \param reset Histogram Reset After Read
			0: Reset after read mode is disabled
			1: Reset after read mode is enabled.
 */
void isc_histogram_configure(uint8_t mode, uint8_t bay_sel, uint8_t reset)
{
	ISC->ISC_HIS_CFG = mode | bay_sel;
	if (reset)
		ISC->ISC_HIS_CFG |= ISC_HIS_CFG_RAR;
}

 /**
 * \brief update the histogram table.
 */
void isc_update_histogram_table(void)
{
	while ((ISC->ISC_CTRLSR & ISC_CTRLSR_HISREQ) == ISC_CTRLSR_HISREQ);
	ISC->ISC_CTRLEN = ISC_CTRLEN_HISREQ;
}

/**
 * \brief  clear the histogram table.
 */
void isc_clear_histogram_table(void)
{
	while (isc_is_sip_asserted());
	ISC->ISC_CTRLEN = ISC_CTRLEN_HISCLR;
}

/*------------------------------------------
 *         DMA functions
 *----------------------------------------*/

/**
 * \brief Configure ISC DMA input mode.
 * \param mode Operating Mode.
 */
void isc_dma_configure_input_mode(uint32_t mode)
{
	ISC->ISC_DCFG = mode;
}

/**
 * \brief Configure ISC DMA with giving entry.
 * \param descEntry entry of DMA descriptor VIEW.
 */
void isc_dma_configure_desc_entry(uint32_t desc_entry)
{
	ISC->ISC_DNDA = desc_entry;
}

/**
 * \brief Enable ISC DMA with giving view.
 * \param ctrl setting for DMA descriptor VIEW.
 */
void isc_dma_enable(uint32_t ctrl)
{
	ISC->ISC_DCTRL = ctrl;
}

/**
 * \brief Configure ISC DMA start address.
 * \param channel channel number.
 * \param address address for giving channel.
 * \param stride stride for giving channel.
 */
void isc_dma_address(uint8_t channel, uint32_t address, uint32_t stride)
{
	ISC->ISC_SUB0[channel].ISC_DAD = address;
	ISC->ISC_SUB0[channel].ISC_DST = stride;
}
