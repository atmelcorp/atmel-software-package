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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"


#include <stdio.h>
//#include <stdint.h>
//#include <string.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define ACC_MR_INV_Pos			12		/* ACC invert output (register offset) */

#define ACC_ACR_HYST_0mv_max	0x00	/* Hysteresis levels  */
#define ACC_ACR_HYST_50mv_max	0x01
#define ACC_ACR_HYST_90mv_max	0x11

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize the ACC controller.
 *
 * \param p_acc Pointer to an Acc instance.
 * \param select_plus input connected to inp, 0~7.
 * \param select_minus input connected to inm,0~7.
 * \param edge_type CF flag triggering mode, use pattern defined in the device header file.
 * \param invert Invert comparator output.
 */
void acc_init(Acc *p_acc, uint32_t select_plus, uint32_t select_minus,
		uint32_t edge_type, uint32_t invert)
{
	/* Reset the controller */
	p_acc->ACC_CR |= ACC_CR_SWRST;

	/* Write to the MR register */
	p_acc->ACC_MR = (((select_plus << ACC_MR_SELPLUS_Pos) & ACC_MR_SELPLUS_Msk) |
			((select_minus << ACC_MR_SELMINUS_Pos) & ACC_MR_SELMINUS_Msk) |
			((edge_type << ACC_MR_EDGETYP_Pos) & ACC_MR_EDGETYP_Msk) |
			((invert << ACC_MR_INV_Pos) & ACC_MR_INV));

	/* Set hysteresis and current selection (ISEL) */
	p_acc->ACC_ACR = (ACC_ACR_ISEL_HISP | ACC_ACR_HYST(ACC_ACR_HYST_50mv_max));

	/* Automatic Output Masking Period */
	while (p_acc->ACC_ISR & (uint32_t) ACC_ISR_MASK);
}

/**
 * \brief Enable the ACC.
 * \param p_acc Pointer to ACC registers set instance.
 */
void acc_enable(Acc *p_acc)
{
	p_acc->ACC_MR |= ACC_MR_ACEN_EN;
}

/**
 * \brief Disable the ACC.
 * \param p_acc Pointer to ACC registers set instance.
 */
void acc_disable(Acc *p_acc)
{
	p_acc->ACC_MR &= ~ACC_MR_ACEN_EN;
}

/**
 * \brief Reset the ACC.
 * \param p_acc Pointer to ACC registers set instance.
 */
void acc_reset(Acc *p_acc)
{
	p_acc->ACC_CR = ACC_CR_SWRST;
}

/**
 * \brief Set the input source.
 * \param p_acc Pointer to ACC registers set instance.
 * \param select_minus Selection for minus comparator input.
 * \param select_plus Selection for plus comparator input.
 */
void acc_set_input(Acc *p_acc, uint32_t select_minus,
		uint32_t select_plus)
{
	p_acc->ACC_MR &= ~(ACC_MR_SELMINUS_Msk & ACC_MR_SELPLUS_Msk);
	p_acc->ACC_MR |= select_plus | select_minus;
}

/**
 * \brief Set the output of the ACC.
 * \param p_acc Pointer to ACC registers set instance.
 * \param invert Invert comparator output, 0 for disable, 1 for enable.
 * \param fault_enable Fault enable, 0 for disable, 1 for enable.
 * \param fault_source Selection of fault source, 0 for CF, 1 for output.
 */
void acc_set_output(Acc *p_acc, uint32_t invert, uint32_t fault_enable, uint32_t fault_source)
{
	p_acc->ACC_MR &= ~(ACC_MR_INV_EN & ACC_MR_FE_EN & ACC_MR_SELFS_OUTPUT);

	p_acc->ACC_MR |= invert | fault_source | fault_enable;
}

/**
 * \brief Get the comparison result.
 * \param p_acc Pointer to ACC registers set instance.
 * \return result of the comparison, 0 for inn>inp, 1 for inp>inn.
 */
uint32_t acc_get_comparison_result(Acc *p_acc)
{
	uint32_t temp = p_acc->ACC_MR;
	uint32_t status = p_acc->ACC_ISR;

	if ((temp & ACC_MR_INV_EN) == ACC_MR_INV_EN) {
		if (status & ACC_ISR_SCO) {
			return 0;	/* inn>inp */
		} else {
			return 1;	/* inp>inn */
		}
	} else {
		if (status & ACC_ISR_SCO) {
			return 1;	/* inp>inn */
		} else {
			return 0;	/* inn>inp */
		}
	}
}

/**
 * \brief Enable the interrupt.
 * \param p_acc Pointer to ACC registers set instance.
 */
void acc_enable_interrupt(Acc *p_acc)
{
	p_acc->ACC_IER = ACC_IER_CE;
}

/**
 * \brief Disable the interrupt.
 * \param p_acc Pointer to ACC registers set instance.
 */
void acc_disable_interrupt(Acc *p_acc)
{
	p_acc->ACC_IDR = ACC_IDR_CE;
}

/**
 * \brief Get the interrupt status.
 * \param p_acc Pointer to ACC registers set instance.
 * \return status of interrupt.
 */
uint32_t acc_get_interrupt_status(Acc *p_acc)
{
	return p_acc->ACC_ISR;
}

/**
 * \brief Set write protect of ACC registers.
 * \param p_acc Pointer to ACC registers set instance.
 * \param enable 1 to enable, 0 to disable.
 */
void acc_set_write_protect(Acc *p_acc, uint32_t enable)
{
	if (enable)
		p_acc->ACC_WPMR = ACC_WPMR_WPKEY_PASSWD | ACC_WPMR_WPEN;
	else
		p_acc->ACC_WPMR = ACC_WPMR_WPKEY_PASSWD;
}

/**
 * \brief Return write protect status.
 *
 * \retval 0 No write protection error.
 * \retval 1 Write protection error.
 */
uint32_t acc_get_write_protect_status(Acc *p_acc)
{
	return p_acc->ACC_WPSR & ACC_WPSR_WPVS;
}