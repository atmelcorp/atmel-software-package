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

/** \addtogroup tc_module
 * \section Purpose
 * The TC driver provides the Interface to configure the Timer Counter (TC).
 *
 * \section Usage
 * <ul>
 *  <li> Optionally, use tc_find_best_clock_source() to let the program find the best
 *     TCCLKS field value automatically.</li>
 *  <li> Configure a Timer Counter in the desired mode using tc_configure().</li>
 *  <li> Start or stop the timer clock using tc_start() and tc_stop().</li>
 *  </li>
 * </ul>
 * For more accurate information, please look at the TC section of the Datasheet.
 *
 * Related files :\n
 * \ref tc.c\n
 * \ref tc.h.\n
*/

/**
*  \file
*
*  \section Purpose
*
*  Interface for configuring and using Timer Counter (TC) peripherals.
*
*  \section Usage
*  -# Optionally, use tc_find_best_clock_source() to let the program find the best
*     TCCLKS field value automatically.
*  -# Configure a Timer Counter in the desired mode using tc_configure().
*  -# Start or stop the timer clock using tc_start() and tc_stop().
*/

/**
 * \file
 *
 * Implementation of Timer Counter (TC).
 *
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"
#include "peripherals/tc.h"
#include "peripherals/pmc.h"

#include <assert.h>

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

void tc_configure(Tc *tc, uint32_t channel, uint32_t mode)
{
	TcChannel *ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	/*  Disable TC clock */
	ch->TC_CCR = TC_CCR_CLKDIS;

	/*  Disable interrupts */
	ch->TC_IDR = ch->TC_IMR;

	/*  Clear status register */
	ch->TC_SR;

	/*  Set mode */
	ch->TC_CMR = mode;
}

void tc_start(Tc *tc, uint32_t channel)
{
	TcChannel *ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	ch->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

void tc_stop(Tc *tc, uint32_t channel)
{
	TcChannel *ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	ch->TC_CCR = TC_CCR_CLKDIS;
}

void tc_enable_it(Tc *tc, uint32_t channel, uint32_t mask)
{
	TcChannel *ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	ch->TC_IER = mask;
}

void tc_disable_it(Tc *tc, uint32_t channel, uint32_t mask)
{
	TcChannel *ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	ch->TC_IDR = mask;
}

uint32_t tc_find_best_clock_source(Tc *tc, uint32_t freq)
{
	uint32_t i;

	for (i = 0 ; i < 5 ; i++)
		if (freq > tc_get_available_freq(tc, i))
			break;

	if (i > 0)
		i--;

	return i;
}

uint32_t tc_get_status(Tc *tc, uint32_t channel)
{
	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	return tc->TC_CHANNEL[channel].TC_SR;
}

void tc_trigger_on_freq(Tc *tc, uint32_t channel, uint32_t freq)
{
	uint32_t tcclks, rc;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	tcclks = tc_find_best_clock_source(tc, freq);
	tc_configure(tc, channel, tcclks | TC_CMR_CPCTRG);
	rc = tc_get_available_freq(tc, tcclks) / freq;
	tc_set_ra_rb_rc(tc, channel, NULL, NULL, &rc);
}

uint32_t tc_get_available_freq(Tc *tc, uint8_t tc_clks)
{
	assert(tc_clks <= TC_CMR_TCCLKS_TIMER_CLOCK5);

	switch (tc_clks) {
	case TC_CMR_TCCLKS_TIMER_CLOCK1:
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		return pmc_get_gck_clock(get_tc_id_from_addr(tc));
#else
		return pmc_get_peripheral_clock(get_tc_id_from_addr(tc)) >> 1;
#endif
	case TC_CMR_TCCLKS_TIMER_CLOCK2:
		return pmc_get_peripheral_clock(get_tc_id_from_addr(tc)) >> 3;
	case TC_CMR_TCCLKS_TIMER_CLOCK3:
		return pmc_get_peripheral_clock(get_tc_id_from_addr(tc)) >> 5;
	case TC_CMR_TCCLKS_TIMER_CLOCK4:
		return pmc_get_peripheral_clock(get_tc_id_from_addr(tc)) >> 7;
	case TC_CMR_TCCLKS_TIMER_CLOCK5:
		return pmc_get_slow_clock();
	default:
		return 0;
	}
}

void tc_set_ra_rb_rc(Tc *tc, uint32_t channel,
	uint32_t *ra, uint32_t *rb, uint32_t *rc)
{
	TcChannel* ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	assert(!(ra && rb) || (ch->TC_CMR & TC_CMR_WAVE));

	if (ra)
		ch->TC_RA = *ra;
	if (rb)
		ch->TC_RB = *rb;
	if (rc)
		ch->TC_RC = *rc;
}

void tc_get_ra_rb_rc(Tc *tc, uint32_t channel,
	uint32_t *ra, uint32_t *rb, uint32_t *rc)
{
	TcChannel* ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	if (ra)
		*ra = ch->TC_RA;
	if (rb)
		*rb = ch->TC_RB;
	if (rc)
		*rc = ch->TC_RC;
}

#ifdef CONFIG_HAVE_TC_FAULT_MODE

void tc_set_fault_mode(Tc *tc, uint32_t mode)
{
	tc->TC_FMR = mode;
}

#endif /* CONFIG_HAVE_TC_FAULT_MODE */
