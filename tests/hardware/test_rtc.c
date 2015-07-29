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

#include "peripherals/aic.h"
#include "peripherals/rtc.h"

#include "test_rtc.h"

#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

static uint8_t flgrtc;

/*------------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

static void rtc_irq_handler(void)
{
	uint32_t reset_flag = 0;
	uint8_t reg;

	reg = (uint8_t)RTC->RTC_SR;
	flgrtc |= reg;

	if (reg& RTC_SR_ACKUPD) {
	  reset_flag |= RTC_SCCR_ACKCLR;
	}
	if (reg & RTC_SR_ALARM) {
	  reset_flag |= RTC_SCCR_ALRCLR;
	}
	if (reg & RTC_SR_SEC) {
	  reset_flag |= RTC_SCCR_SECCLR;
	}
	if (reg & RTC_SR_TIMEV) {
	  reset_flag |= RTC_SCCR_TIMCLR;
	}
	if (reg & RTC_SR_CALEV) {
	  reset_flag |= RTC_SCCR_CALCLR;
	}
	if (reg & RTC_SR_TDERR) {
	  reset_flag |= RTC_SCCR_TDERRCLR;
	}
	RTC->RTC_SCCR = reset_flag;
}

/**
* \brief Get flag sources interrupt
*
*/
uint8_t get_flag_rtc (void)
{
	return flgrtc;
}
void set_flag_rtc (uint8_t frtc)
{
	flgrtc = frtc;
}

/**
* \brief Configure RTC for test
* \Set alarm ewery second
*/
void _configure_rtc (void)
{
  	uint32_t status;
	struct _time MTU = {00, 00, 00};
	struct _time MTA = {18, 30, 00};
	struct _date MDT = {2015, 06, 01, 1};

	rtc_set_hour_mode(0); // mode 24h
	status = rtc_set_time(&MTU);
	status |= rtc_set_date(&MDT);
	status |= rtc_set_time_alarm(&MTA);
	status |= rtc_set_time_event (RTC_CR_TIMEVSEL_MINUTE);
	rtc_disable_it (RTC_IER_ACKEN | RTC_IER_ALREN | RTC_IER_SECEN | RTC_IER_TIMEN | RTC_IER_CALEN);
	rtc_enable_it (RTC_IER_SECEN);

	aic_set_source_vector(ID_SYSC, rtc_irq_handler);
	aic_enable(ID_SYSC);
}
