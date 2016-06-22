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

/** \file */
/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/rstc.h"

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_RSTC_CONFIGURABLE_USER_RESET

void rstc_set_user_reset_enable(bool enable)
{
	uint32_t mr = RSTC->RSTC_MR;
	if (enable) {
		mr |= RSTC_MR_URSTEN;
	} else {
		mr &= ~RSTC_MR_URSTEN;
	}
	RSTC->RSTC_MR = mr | RSTC_MR_KEY_PASSWD;
}

void rstc_set_user_reset_interrupt_enable(bool enable)
{
	uint32_t mr = RSTC->RSTC_MR;
	if (enable) {
		mr |= RSTC_MR_URSTIEN;
	} else {
		mr &= ~RSTC_MR_URSTIEN;
	}
	RSTC->RSTC_MR = mr | RSTC_MR_KEY_PASSWD;
}

#endif /* CONFIG_HAVE_RSTC_CONFIGURABLE_USER_RESET */

#ifdef CONFIG_HAVE_RSTC_EXTERNAL_RESET

void rstc_set_ext_reset_length(uint8_t length)
{
	RSTC->RSTC_MR = RSTC->RSTC_MR | RSTC_MR_ERSTL(length) | RSTC_MR_KEY_PASSWD;
}

void rstc_reset_processor_and_peripherals_and_ext(void)
{
	RSTC->RSTC_CR = RSTC_CR_EXTRST | RSTC_MR_KEY_PASSWD;
}

#endif /* CONFIG_HAVE_RSTC_EXTERNAL_RESET */

void rstc_reset_processor_and_peripherals(void)
{
#ifdef RSTC_CR_PERRST
	RSTC->RSTC_CR = RSTC_CR_PERRST | RSTC_CR_PROCRST | RSTC_MR_KEY_PASSWD;
#else
	RSTC->RSTC_CR = RSTC_CR_PROCRST | RSTC_MR_KEY_PASSWD;
#endif
}

#ifdef CONFIG_HAVE_RSTC_INDEPENDENT_RESET

void rstc_reset_processor(void)
{
	RSTC->RSTC_CR = RSTC_CR_PROCRST | RSTC_MR_KEY_PASSWD;
}

void rstc_reset_peripherals(void)
{
	RSTC->RSTC_CR = RSTC_CR_PERRST | RSTC_MR_KEY_PASSWD;
}

#endif /* CONFIG_HAVE_RSTC_INDEPENDENT_RESET */

bool rstc_get_nrst_level(void)
{
	return (RSTC->RSTC_SR & RSTC_SR_NRSTL) != 0;
}

bool rstc_is_user_reset_detected(void)
{
	return (RSTC->RSTC_SR & RSTC_SR_URSTS) != 0;
}

bool rstc_is_busy(void)
{
	return (RSTC->RSTC_SR & RSTC_SR_SRCMP) != 0;
}

uint32_t rstc_get_status(void)
{
	return RSTC->RSTC_SR;
}
