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

/** \addtogroup adc_module Working with ADC
 * \ingroup peripherals_module
 * \section Purpose
 * The ADC driver provides the interface to configure and use the ADC peripheral.
 * \n
 *
 * It converts the analog input to digital format. The converted result could be
 * 10bit. The ADC supports up to 16 analog lines.
 *
 * To Enable a ADC conversion,the user has to follow these few steps:
 * <ul>
 * <li> Select an appropriate reference voltage on ADVREF   </li>
 * <li> Configure the ADC according to its requirements and special needs,which
 * could be  broken down into several parts:
 * -#   Select the resolution by setting or clearing ADC_MR_LOWRES bit in
 *      ADC_MR (Mode Register)
 * -#   Set ADC clock by setting ADC_MR_PRESCAL bits in ADC_MR, the clock is
 *      calculated with ADCClock = MCK / ( (PRESCAL+1) * 2 )
 * -#   Set Startup Time,Tracking Clock cycles and Transfer Clock respectively
 *      in ADC_MR.
 </li>
 * <li> Start conversion by setting ADC_CR_START in ADC_CR. </li>
 * </ul>
 *
 * \section Usage
 * <ul>
 * <li> Initialize the ADC controller using adc_initialize().
 * <li> ADC clock and timing configuration using adc_set_clock() and adc_set_timing().
 * <li> For ADC trigger using adc_set_trigger(), adc_set_trigger_mode() and
 * adc_set_trigger_period().
 * <li> For ADC sequence mode using adc_set_sequence_mode(), adc_set_sequence() and
 * adc_set_sequence_by_list().
 * <li> For ADC compare mode using adc_set_compare_channel(), adc_set_compare_mode()
 * and adc_set_comparison_window().
 * <li> ADC works with touchscreen using adc_ts_calibration(), adc_set_ts_mode(),
 * adc_set_ts_debounce(), adc_set_ts_pen_detect(), adc_set_ts_average(),
 * adc_get_ts_xposition(), adc_get_ts_yposition() and adc_get_ts_pressure().
 * </li>
 * </ul>
 *
 * For more accurate information, please look at the ADC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref adc.c\n
 * \ref adc.h\n
 */
/**
 * \file
 *
 * Implementation of Analog-to-Digital Converter (ADC).
 *
 */
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/adc.h"
#include "peripherals/pmc.h"

#include "trace.h"

#include <stdio.h>
/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** Current working clock */
static uint32_t _adc_clock = 0;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void adc_initialize(void)
{
	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_ADC);

	/*  Reset the controller */
	ADC->ADC_CR = ADC_CR_SWRST;

	/* Reset Mode Register */
	ADC->ADC_MR = 0;

}

uint32_t adc_set_clock(uint32_t clk)
{
	uint32_t prescale, mode_reg;
	uint32_t mck = pmc_get_peripheral_clock(ID_ADC);
	/* Formula for PRESCAL is:
	   ADCClock = MCK / ( (PRESCAL+1) * 2 )
	   PRESCAL = (MCK / (2 * ADCCLK)) + 1
	   First, we do the division, multiplied by 10 to get higher precision
	   If the last digit is not zero, we round up to avoid generating a higher
	   than required frequency. */
	prescale = (mck * 5) / clk;
	if (prescale % 10)
		prescale = prescale / 10;
	else {
		if (prescale == 0)
			return 0;
		prescale = prescale / 10 - 1;
	}

	mode_reg = ADC_MR_PRESCAL(prescale);
	if (mode_reg == 0)
		return 0;

	mode_reg |= (ADC->ADC_MR & ~ADC_MR_PRESCAL_Msk);
	ADC->ADC_MR = mode_reg;

	_adc_clock = mck / (prescale + 1) / 2;
	//_adc_clock = _adc_clock / 1000 * 1000;
	return _adc_clock;
}

void adc_enable_it(uint32_t mask)
{
	ADC->ADC_IER = mask;
}

void adc_set_timing(uint32_t startup, uint32_t tracking,
		    uint32_t settling)
{
	uint32_t mode_reg;

#ifndef CONFIG_HAVE_SETTLING_TIME
	if (settling) {
		settling = 0;
		trace_warning("adc: Analog settling time not supported, IGNORED!\r\n");
	}
#endif

	mode_reg = ADC->ADC_MR;
	mode_reg &= (~ADC_MR_STARTUP_Msk) & (~ADC_MR_TRACKTIM_Msk);

	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 */
	mode_reg |= ADC_MR_STARTUP(startup) | ADC_MR_TRACKTIM(tracking)
		| ADC_MR_SETTLING(settling);
	ADC->ADC_MR |= mode_reg;
}

void adc_set_trigger_mode(uint32_t mode)
{
	uint32_t trg_reg = ADC->ADC_TRGR & ~ADC_TRGR_TRGMOD_Msk;
	ADC->ADC_TRGR = trg_reg | mode;
}

void adc_set_sleep_mode(uint8_t enable)
{
	if (enable) {
		ADC->ADC_MR |= ADC_MR_SLEEP;
	} else {
		ADC->ADC_MR &= ~ADC_MR_SLEEP;
	}
}

void adc_set_sequence_mode(uint8_t enable)
{
	if (enable) {
		/* User Sequence Mode: The sequence respects what is defined in
		   ADC_SEQR1 and ADC_SEQR2 */
		ADC->ADC_MR |= ADC_MR_USEQ;
	} else {
		/* Normal Mode: The controller converts channels in a simple numeric order. */
		ADC->ADC_MR &= ~ADC_MR_USEQ;
	}
}

void adc_set_sequence(uint32_t seq1, uint32_t seq2)
{
	ADC->ADC_SEQR1 = seq1;
}

void adc_set_sequence_by_list(uint8_t channel_list[], uint8_t len)
{
	uint8_t i;
	uint8_t shift;

	ADC->ADC_SEQR1 = 0;
	for (i = 0, shift = 0; i < 8; i++, shift += 4) {
		if (i >= len)
			return;
		ADC->ADC_SEQR1 |= channel_list[i] << shift;

	}
}

void adc_set_tag_enable(uint8_t enable)
{
	if (enable) {
		ADC->ADC_EMR |= ADC_EMR_TAG;
	} else {
		ADC->ADC_EMR &= ~ADC_EMR_TAG;
	}
}

void adc_set_compare_channel(uint32_t channel)
{
	assert(channel <= 16);

	if (channel < 16) {
		ADC->ADC_EMR &= ~(ADC_EMR_CMPALL);
		ADC->ADC_EMR &= ~(ADC_EMR_CMPSEL_Msk);
		ADC->ADC_EMR |= (channel << ADC_EMR_CMPSEL_Pos);
	} else {
		ADC->ADC_EMR |= ADC_EMR_CMPALL;
	}
}

void adc_set_compare_mode(uint32_t mode)
{
	ADC->ADC_EMR &= ~(ADC_EMR_CMPMODE_Msk);
	ADC->ADC_EMR |= (mode & ADC_EMR_CMPMODE_Msk);
}

void adc_set_comparison_window(uint32_t window)
{
	ADC->ADC_CWR = window;
}

uint8_t adc_check_configuration(void)
{
	uint32_t mode_reg;
	uint32_t prescale;
	uint32_t clock;
	uint32_t mck = pmc_get_peripheral_clock(ID_ADC);

	mode_reg = ADC->ADC_MR;

	prescale = (mode_reg & ADC_MR_PRESCAL_Msk) >> ADC_MR_PRESCAL_Pos;
	/* Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 ) */
	clock = mck / ((prescale + 1) * 2);
	if (clock > ADC_CLOCK_MAX) {
		printf
		    ("ADC clock is too high (out of specification: %d Hz)\r\n",
		     (int) ADC_CLOCK_MAX);
		return 1;
	}

	return 0;
}

uint32_t adc_get_converted_data(uint32_t channel)
{
	uint32_t dwData = 0;

	assert(channel < 16);

	dwData = ADC->ADC_CDR[channel];

	return dwData;
}

void adc_set_startup_time(uint32_t startup)
{
	uint32_t start;
	uint32_t mode_reg;

	if (_adc_clock == 0)
		return;
	/* Formula for STARTUP is:
	   STARTUP = (time x ADCCLK) / (1000000) - 1
	   Division multiplied by 10 for higher precision */

	start = (startup * _adc_clock) / (100000);
	if (start % 10)
		start /= 10;
	else {
		start /= 10;
		if (start)
			start--;
	}
	if (start > 896)
		mode_reg = ADC_MR_STARTUP_SUT960;
	else if (start > 832)
		mode_reg = ADC_MR_STARTUP_SUT896;
	else if (start > 768)
		mode_reg = ADC_MR_STARTUP_SUT832;
	else if (start > 704)
		mode_reg = ADC_MR_STARTUP_SUT768;
	else if (start > 640)
		mode_reg = ADC_MR_STARTUP_SUT704;
	else if (start > 576)
		mode_reg = ADC_MR_STARTUP_SUT640;
	else if (start > 512)
		mode_reg = ADC_MR_STARTUP_SUT576;
	else if (start > 112)
		mode_reg = ADC_MR_STARTUP_SUT512;
	else if (start > 96)
		mode_reg = ADC_MR_STARTUP_SUT112;
	else if (start > 80)
		mode_reg = ADC_MR_STARTUP_SUT96;
	else if (start > 64)
		mode_reg = ADC_MR_STARTUP_SUT80;
	else if (start > 24)
		mode_reg = ADC_MR_STARTUP_SUT64;
	else if (start > 16)
		mode_reg = ADC_MR_STARTUP_SUT24;
	else if (start > 8)
		mode_reg = ADC_MR_STARTUP_SUT16;
	else if (start > 0)
		mode_reg = ADC_MR_STARTUP_SUT8;
	else
		mode_reg = ADC_MR_STARTUP_SUT0;

	mode_reg |= ADC->ADC_MR & ~ADC_MR_STARTUP_Msk;
	ADC->ADC_MR = mode_reg;
}

void adc_set_tracking_time(uint32_t dwNs)
{
	uint32_t dwShtim;
	uint32_t mode_reg;

	if (_adc_clock == 0)
		return;
	/* Formula for SHTIM is:
	   SHTIM = (time x ADCCLK) / (1000000000) - 1
	   Since 1 billion is close to the maximum value for an integer, we first
	   divide ADCCLK by 1000 to avoid an overflow */
	dwShtim = (dwNs * (_adc_clock / 1000)) / 100000;
	if (dwShtim % 10)
		dwShtim /= 10;
	else {
		dwShtim /= 10;
		if (dwShtim)
			dwShtim--;
	}
	mode_reg = ADC_MR_TRACKTIM(dwShtim);
	mode_reg |= ADC->ADC_MR & ~ADC_MR_TRACKTIM_Msk;
	ADC->ADC_MR = mode_reg;
}

void adc_set_trigger_period(uint32_t period)
{
	uint32_t trg_period;
	uint32_t trg_reg;
	if (_adc_clock == 0)
		return;
	trg_period = period * (_adc_clock/1000) - 1;
	trg_reg = ADC->ADC_TRGR & ~ADC_TRGR_TRGPER_Msk;
	trg_reg |= ADC_TRGR_TRGPER(trg_period);
	ADC->ADC_TRGR = trg_reg;
}

void adc_ts_calibration(void)
{
	ADC->ADC_CR = ADC_CR_TSCALIB;
}

void adc_set_ts_mode(uint32_t mode)
{
	ADC->ADC_TSMR = (ADC->ADC_TSMR & ~ADC_TSMR_TSMODE_Msk) | mode;
}

void adc_configure_ext_mode(uint32_t mode)
{
	ADC->ADC_EMR = mode;
}

void adc_set_ts_debounce(uint32_t time)
{
	uint32_t div = 1000000000;
	uint32_t clk = _adc_clock;
	uint32_t dwPenbc = 0;
	uint32_t target, current;
	uint32_t tsmr;
	if (time == 0 || _adc_clock == 0)
		return;
	/* Divide time & ADCCLK to avoid overflows */
	while ((div > 1) && ((time % 10) == 0)) {
		time /= 10;
		div /= 10;
	}
	while ((div > 1) && ((clk & 10) == 0)) {
		clk /= 10;
		div /= 10;
	}
	/* Compute PENDBC */
	target = time * clk / div;
	current = 1;
	while (current < target) {
		dwPenbc++;
		current *= 2;
	}
	tsmr = ADC_TSMR_PENDBC(dwPenbc);
	if (tsmr == 0)
		return;
	tsmr |= ADC->ADC_TSMR & ~ADC_TSMR_PENDBC_Msk;
	ADC->ADC_TSMR = tsmr;
}

void adc_set_ts_pen_detect(uint8_t enable)
{
	if (enable)
		ADC->ADC_TSMR |= ADC_TSMR_PENDET;
	else
		ADC->ADC_TSMR &= ~ADC_TSMR_PENDET;
}

void adc_set_ts_average(uint32_t avg_2_conv)
{
	uint32_t mode_reg = ADC->ADC_TSMR & ~ADC_TSMR_TSAV_Msk;
	uint32_t ts_av = avg_2_conv >> ADC_TSMR_TSAV_Pos;
	uint32_t ts_freq = (mode_reg & ADC_TSMR_TSFREQ_Msk) >> ADC_TSMR_TSFREQ_Pos;
	if (ts_av) {
		if (ts_av > ts_freq) {
			mode_reg &= ~ADC_TSMR_TSFREQ_Msk;
			mode_reg |= ADC_TSMR_TSFREQ(ts_av);
		}
	}
	ADC->ADC_TSMR = mode_reg | avg_2_conv;
}

uint32_t adc_get_ts_xposition(void)
{
	return ADC->ADC_XPOSR;
}

uint32_t adc_get_ts_yposition(void)
{
	return ADC->ADC_YPOSR;
}

uint32_t adc_get_ts_pressure(void)
{
	return ADC->ADC_PRESSR;
}

void adc_set_trigger(uint32_t trigger)
{
	uint32_t mode_reg;

	mode_reg = ADC->ADC_MR;
	mode_reg &= ~ADC_MR_TRGSEL_Msk;
	mode_reg |= trigger;
	ADC->ADC_MR |= mode_reg;
}

#ifdef CONFIG_HAVE_ADC_LOW_RES
void adc_set_low_resolution(uint8_t enable)
{
	if (enable) {
		ADC->ADC_MR |= ADC_MR_LOWRES;
	} else {
		ADC->ADC_MR &= ~ADC_MR_LOWRES;
	}
}
#endif
