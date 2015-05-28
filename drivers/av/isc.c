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
#include "av/isc.h"
 
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
 

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
	ISC->ISC_CTRLEN = ISC_CTRLEN_CAPTURE;
}

/**
 * \brief end the capture at the next Vertical Synchronization Detection. 
 */
void isc_stop_capture(void)
{
	ISC->ISC_CTRLDIS = ISC_CTRLDIS_DISABLE;
}

/**
 * \brief Returns ISC Control Status.
 */
uint32_t isc_get_ctrl_status(void)
{
	return (ISC->ISC_CTRLSR);
}

/**
 * \brief update the color profile.
 */
void isc_update_profile(void)
{
	ISC->ISC_CTRLEN = ISC_CTRLEN_UPPRO;
}

/**
 * \brief update the histogram table.
 */
void isc_update_histogram_table(void)
{
	ISC->ISC_CTRLEN = ISC_CTRLEN_HISREQ;
}

/**
 * \brief  clear the histogram table.
 */
void isc_clear_histogram_table(void)
{
	ISC->ISC_CTRLEN = ISC_CTRLEN_HISCLR;
}

/**
 * \brief Perform software reset of the interface.
 */
void isc_software_reset(void)
{
	ISC->ISC_CTRLDIS = ISC_CTRLDIS_SWRST;
}

/*------------------------------------------
 *      PFE(Parallel Front End) functions
 *----------------------------------------*/
 
/**
 * \brief  configure PFE(Parallel Front End) cropping area.
 * \param Hstart: Horizontal starting position of the cropping area
 * \param Hend: Horizontal ending position of the cropping area
 * \param Vstart: Vertical starting position of the cropping area
 * \param Hend: Vertical ending position of the cropping area
 */
void isc_pfe_set_cropping_area( 
					uint32_t Hstart, uint32_t Hend, uint32_t Vstart, uint32_t Vend)
{
	ISC->ISC_PFE_CFG1 = ISC_PFE_CFG1_COLMIN(Hstart)
					 | ISC_PFE_CFG1_COLMAX(Hend)
					 | ISC_PFE_CFG2_ROWMIN(Vstart)
					 | ISC_PFE_CFG2_ROWMAX(Vend);
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
	ISC->ISC_CLKCFG |= ISC_CLKCFG_ICDIV(ispClockDiv) | (ispClockSelection << 8);
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
	ISC->ISC_CLKCFG |= ISC_CLKCFG_MCDIV(masterClockDiv) 
					| ISC_CLKCFG_MCSEL(masterClockSelection);
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
	return (ISC->ISC_CLKSR);
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
	return(ISC->ISC_INTSR);
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
 * \param rOffset Offset Red Component (signed 13 bits 1:12:0)
 * \param grOffset Offset Green Component for Red Row (signed 13 bits 1:12:0)
 * \param bOffset Offset Blue Component (signed 13 bits, 1:12:0)
 * \param gbOffset Offset Green Component for Blue Row (signed 13 bits, 1:12:0)
 * \param rGain Red Component Gain (unsigned 13 bits, 0:4:9)
 * \param grGain Green Component (Red row) Gain (unsigned 13 bits, 0:4:9)
 * \param bGain Blue Component Gain (unsigned 13 bits, 0:4:9)
 * \param gbGain Green Component (Blue row) Gain (unsigned 13 bits, 0:4:9)
 */
void isc_wb_adjust_bayer_color(
				uint32_t rOffset, uint32_t grOffset, uint32_t bOffset, uint32_t gbOffset,
				uint32_t rGain, uint32_t grGain, uint32_t bGain, uint32_t gbGain )
{
	ISC->ISC_WB_O_RGR = ISC_WB_O_RGR_ROFST(rOffset) | ISC_WB_O_RGR_GROFST(grOffset);
	ISC->ISC_WB_O_BGB = ISC_WB_O_BGB_BOFST(bOffset) | ISC_WB_O_BGB_GBOFST(gbOffset);
	ISC->ISC_WB_G_RGR = ISC_WB_G_RGR_RGAIN(rGain) | ISC_WB_G_RGR_GRGAIN(grGain);
	ISC->ISC_WB_G_BGB = ISC_WB_G_BGB_BGAIN(bGain) | ISC_WB_G_BGB_GBGAIN(gbGain);
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
	ISC->ISC_CFA_CFG = pattern | (edge << 4) 
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
		ISC->ISC_CFA_CTRL = 0;
}

/**
 * \brief Color correction with color component.
 * \param cc Pointer to structure sColorCorrectComponents
 */
void isc_cc_configure(sColorCorrectComponents* cc)
{
	ISC->ISC_CC_RR_RG = ISC_CC_RR_RG_RRGAIN(cc->rrGain) | ISC_CC_RR_RG_RGGAIN(cc->rgGain);
	ISC->ISC_CC_RB_OR = ISC_CC_RB_OR_RBGAIN(cc->rbGain) | ISC_CC_RB_OR_ROFST(cc->rOffset);
	ISC->ISC_CC_GR_GG = ISC_CC_GR_GG_GRGAIN(cc->grGain) | ISC_CC_GR_GG_GGGAIN(cc->ggGain);
	ISC->ISC_CC_GB_OG = ISC_CC_GB_OG_GBGAIN(cc->gbGain) | ISC_CC_GB_OG_ROFST(cc->gOffset);
	ISC->ISC_CC_BR_BG = ISC_CC_BR_BG_BRGAIN(cc->brGain) | ISC_CC_BR_BG_BGGAIN(cc->bgGain);
	ISC->ISC_CC_BB_OB = ISC_CC_BB_OB_BBGAIN(cc->bbGain) | ISC_CC_BB_OB_BOFST(cc->bOffset);
}
