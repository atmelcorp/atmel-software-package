/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

/** \addtogroup aic_module
 *
 * \section Purpose
 * The Advanced Interrupt Controller (AIC) is an 8-level priority, individually
 * maskable, vectored interrupt controller, providing handling of up to thirty-two interrupt sources.
 *
 * \section Usage
 * <ul>
 * <li> Each interrupt source can be enabled or disabled by using the aic_enable() and aic_disable()</li>
 * </ul>
 *
 * For more accurate information, please look at the AIC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref aic.c\n
 * \ref aic.h\n
 */
/*@{*/
/*@}*/

/**
* \file
*
* Implementation of Advanced Interrupt Controller (AIC) controller.
*
*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "core/aic.h"
#include "core/cp15.h"
#include "core/cp15_pmu.h"

#include <stdint.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures an interrupt in the AIC. The interrupt is identified by its
 * source (ID_xxx) and is configured to use the specified mode and
 * interrupt handler function. Mode is the value that will be put in AIC_SMRx
 * and the function address will be set in AIC_SVRx.
 * The interrupt is disabled before configuration, so it is useless
 * to do it before calling this function. When aic_configure returns, the
 * interrupt will always be disabled and cleared; it must be enabled by a
 * call to aic_enable().
 *
 * \param source  Interrupt source to configure.
 * \param mode  Triggering mode and priority of the interrupt.
 * \param handler  Interrupt handler function.
 */

static void
_aic_ConfigureIT(uint32_t source, uint8_t mode)
{
	AIC->AIC_SSR = source;
	/* Disable the interrupt first */
	AIC->AIC_IDCR = AIC_IDCR_INTD;
	/* Configure mode and handler */
	AIC->AIC_SMR = mode;
	/* Clear interrupt */
	AIC->AIC_ICCR = AIC_ICCR_INTCLR;
}

/**
 * \brief Enables interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 * \param source  Interrupt source to enable.
 */
static void
_aic_EnableIT(Aic * aic, uint32_t source)
{
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_IECR = AIC_IECR_INTEN;
}

/**
 * \brief Disables interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 * \param source  Interrupt source to disable.
 */
static void
_aic_DisableIT(Aic * aic, uint32_t source)
{
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_IDCR = AIC_IDCR_INTD;
}

/**
 * \brief Configure corresponding handler for the interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 * \param source  Interrupt source to configure.
 * \param handler handler for the interrupt.
 */
static void
_aic_SetSourceVector(Aic * aic, uint32_t source, uint32_t handler)
{
	if (aic->AIC_WPMR & AIC_WPMR_WPEN) {
		aic_write_protection(aic, 1);
	}
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_SVR = handler;
}

/**
 * \brief Clears interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 * \param source  Interrupt source to disable.
 */
static void
_aic_ClearIT(Aic * aic, uint32_t source)
{
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_ICCR = AIC_ICCR_INTCLR;
}

/**
 * \brief Sets interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 * \param source  Interrupt source to disable.
 */
static void
_aic_SetIT(Aic * aic, uint32_t source)
{
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_ISCR = AIC_ISCR_INTSET;
}

/**
 * \brief return if the giving peripheral is H64 Matrix
 *
 * \param pid  peripheral ID
 */
static uint8_t
_isH64Matrix(uint32_t pid)
{
	if (/* (pid == ID_ARM) || */ (pid == ID_XDMAC0) ||
	    //(pid == ID_PKCC) ||
	    (pid == ID_AESB) ||
	    (pid == ID_MPDDRC) ||
	    /* (pid == ID_VDEC) || */
	    (pid == ID_XDMAC1) ||
	    (pid == ID_LCDC) /* || (pid == ID_ISI) */ || (pid == ID_L2CC)) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * \brief Enables interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to enable.
 */
void
aic_enable(uint32_t source)
{
	volatile unsigned int AicFuse = REG_SFR_AICREDIR;

	if (AicFuse) {
		_aic_EnableIT(AIC, source);
	} else {
		if (_isH64Matrix(source)) {
			if (MATRIX0->
			    MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
				_aic_EnableIT(AIC, source);
			else
				_aic_EnableIT(SAIC, source);
		} else {
			if (MATRIX1->
			    MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
				_aic_EnableIT(AIC, source);
			else
				_aic_EnableIT(SAIC, source);
		}
	}
}

/**
 * \brief Disables interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to disable.
 */
void
aic_disable(uint32_t source)
{
	volatile unsigned int AicFuse = REG_SFR_AICREDIR;

	if (AicFuse) {
		_aic_DisableIT(AIC, source);
		return;
	}

	if (_isH64Matrix(source)) {
		if (MATRIX0->MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
			_aic_DisableIT(AIC, source);
		else
			_aic_DisableIT(SAIC, source);
	} else {
		if (MATRIX1->MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
			_aic_DisableIT(AIC, source);
		else
			_aic_DisableIT(SAIC, source);
	}
}

/**
 * \brief Configure interrupts' source mode.
 *
 * \param source  Interrupt source to configure.
 * \param mode    mode combined of priority level and interrupt source type.
 */
void
aic_configure(uint32_t source, uint8_t mode)
{
	volatile unsigned int AicFuse = REG_SFR_AICREDIR;

	if (AicFuse) {
		_aic_ConfigureIT(source, mode);
	} else {
		if (_isH64Matrix(source)) {
			if (MATRIX0->
			    MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
				_aic_ConfigureIT(source, mode);
			else {
				// Does not apply For SAIC
			}
		} else {
			if (MATRIX1->
			    MATRIX_SPSELR[source / 32] & (1 << (source % 32)))
				_aic_ConfigureIT(source, mode);
			else {
				// does not apply for SAIC
			}
		}
	}
}

/**
 * \brief Configure corresponding handler for the interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to configure.
 * \param handler handler for the interrupt.
 */
void
aic_set_source_vector(uint32_t source, uint32_t handler)
{
	Matrix *pMatrix;
	Aic *aic = AIC;
	volatile unsigned int AicFuse = REG_SFR_AICREDIR;

	if (0 == AicFuse) {
		pMatrix = (_isH64Matrix(source)) ? MATRIX0 : MATRIX1;
		if (0 ==
		    (pMatrix->
		     MATRIX_SPSELR[source / 32] & (1 << (source % 32))))
			aic = SAIC;
	}
	_aic_SetSourceVector(aic, source, handler);
}

/**
 * \brief Configure interrupts' source mode.
 *
 * \param source  Interrupt source to configure.
 * \param mode    mode combined of priority level and interrupt source type.
 */
void
aic_set_or_clear(uint32_t source, uint8_t set)
{
	Matrix *pMatrix;
	Aic *aic = AIC;
	volatile unsigned int AicFuse = REG_SFR_AICREDIR;

	if (0 == AicFuse) {
		pMatrix = (_isH64Matrix(source)) ? MATRIX0 : MATRIX1;
		if (0 ==
		    (pMatrix->
		     MATRIX_SPSELR[source / 32] & (1 << (source % 32))))
			aic = SAIC;
	}
	if (set)
		_aic_SetIT(aic, source);
	else
		_aic_ClearIT(aic, source);
}

/**
 * \brief Indicate treatment completion for interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 */
void
aic_end_interrupt(Aic * aic)
{
	aic->AIC_EOICR = AIC_EOICR_ENDIT;
}

/**
 * \brief Configuration of protection mode and general interrupt mask for debug.
 *
 * \param aic     AIC instance.
 * \param protect Enable/Disable protection mode.
 * \param mask    Enable/Disable mask IRQ and FIQ.
 *
 * \retval        0 - succeed.  1 - failed.
 */
uint32_t
aic_debug_config(Aic * aic, uint8_t protect, uint8_t mask)
{
	uint32_t tmp;

	/* return in case the "Write Protection Mode" is enabled */
	if (aic->AIC_WPMR & AIC_WPMR_WPEN)
		return 1;

	tmp = protect ? (1 << 1) : (0 << 1);
	if (mask)
		tmp++;
	aic->AIC_DCR = tmp;
	return 0;
}

/**
 * \brief Enable/Disable AIC write protection mode.
 *
 * \param aic     AIC instance.
 * \param enable  Enable/Disable AIC write protection mode.
 */
void
aic_write_protection(Aic * aic, uint32_t enable)
{
	if (enable) {
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD | AIC_WPMR_WPEN;
	} else {
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD;
	}
}

/**
 * \brief Get AIC Write Protection Status.
 *
 * \param aic     AIC instance.
 * \param pViolationSource pointer to address to store the violation source
 *
 * \retval        0 - No violation occured.  1 - violation occured.
 */
uint32_t
aic_violation_occured(Aic * aic, uint32_t * pViolationSource)
{
	if (aic->AIC_WPSR & AIC_WPSR_WPVS) {
		*pViolationSource =
		    (aic->
		     AIC_WPSR & AIC_WPSR_WPVSRC_Msk) >> AIC_WPSR_WPVSRC_Pos;
	}
	return 0;
}
