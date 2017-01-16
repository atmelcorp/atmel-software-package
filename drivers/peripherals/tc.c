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

#include <assert.h>

#include "chip.h"
#include "compiler.h"
#include "peripherals/tc.h"
#include "peripherals/pmc.h"

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

	/*  Clear status register */
	ch->TC_SR;

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

uint32_t tc_find_best_clock_source(Tc *tc, uint8_t channel, uint32_t freq)
{
	const int tcclks[] = {
		TC_CMR_TCCLKS_TIMER_CLOCK1,
		TC_CMR_TCCLKS_TIMER_CLOCK2,
		TC_CMR_TCCLKS_TIMER_CLOCK3,
		TC_CMR_TCCLKS_TIMER_CLOCK4,
		TC_CMR_TCCLKS_TIMER_CLOCK5,
	};
	int i, best, higher;
	int best_freq, higher_freq;

	best = higher = -1;
	best_freq = higher_freq = 0;
	for (i = 0 ; i < ARRAY_SIZE(tcclks) ; i++) {
		uint32_t f = tc_get_available_freq(tc, channel, tcclks[i]);
		if (higher < 0 || f > higher_freq) {
			higher_freq = f;
			higher = tcclks[i];
		}
		if (f > freq) {
			if (best < 0 || (f - freq) < (f - best_freq)) {
				best_freq = f;
				best = tcclks[i];
			}
		}
	}

	if (best < 0)
		best = higher;

	return best;
}

uint32_t tc_get_status(Tc *tc, uint32_t channel)
{
	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	return tc->TC_CHANNEL[channel].TC_SR;
}

uint32_t tc_get_available_freq(Tc *tc, uint8_t channel, uint8_t tc_clks)
{
	uint32_t tc_id = get_tc_id_from_addr(tc, channel);

	switch (tc_clks) {
	case TC_CMR_TCCLKS_TIMER_CLOCK1:
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		if (pmc_is_gck_enabled(tc_id))
			return pmc_get_gck_clock(tc_id);
		else
			return 0;
#else
		return pmc_get_peripheral_clock(tc_id) >> 1;
#endif
	case TC_CMR_TCCLKS_TIMER_CLOCK2:
		return pmc_get_peripheral_clock(tc_id) >> 3;
	case TC_CMR_TCCLKS_TIMER_CLOCK3:
		return pmc_get_peripheral_clock(tc_id) >> 5;
	case TC_CMR_TCCLKS_TIMER_CLOCK4:
		return pmc_get_peripheral_clock(tc_id) >> 7;
	case TC_CMR_TCCLKS_TIMER_CLOCK5:
		return pmc_get_slow_clock();
	default:
		return 0;
	}
}

uint32_t tc_get_channel_freq(Tc *tc, uint32_t channel)
{
	TcChannel* ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	return tc_get_available_freq(tc, channel, ch->TC_CMR & TC_CMR_TCCLKS_Msk);
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

uint32_t tc_get_cv(Tc* tc, uint32_t channel)
{
	TcChannel* ch;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	ch = &tc->TC_CHANNEL[channel];

	return ch->TC_CV;
}

