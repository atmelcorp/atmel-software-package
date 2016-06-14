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

/**
 * \brief Configures a Timer Counter Channel
 *
 * Configures a Timer Counter to operate in the given mode. Timer is stopped
 * after configuration and must be restarted with tc_start(). All the
 * interrupts of the timer are also disabled.
 *
 * \param tc  Pointer to a Tc instance.
 * \param channel Channel number.
 * \param mode  Operating mode (TC_CMR value).
 */
void tc_configure(Tc *tc, uint32_t channel, uint32_t mode)
{
	volatile TcChannel *tc_channel;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	tc_channel = tc->TC_CHANNEL + channel;

	/*  Disable TC clock */
	tc_channel->TC_CCR = TC_CCR_CLKDIS;

	/*  Disable interrupts */
	tc_channel->TC_IDR = 0xFFFFFFFF;

	/*  Clear status register */
	tc_channel->TC_SR;

	/*  Set mode */
	tc_channel->TC_CMR = mode;
}

/**
 * \brief Reset and Start the TC Channel
 *
 * Enables the timer clock and performs a software reset to start the counting.
 *
 * \param tc  Pointer to a Tc instance.
 * \param channel Channel number.
 */
void tc_start(Tc *tc, uint32_t channel)
{
	volatile TcChannel *tc_channel;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	tc_channel = tc->TC_CHANNEL + channel;
	tc_channel->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	tc_channel->TC_IER = TC_IER_COVFS;
}

/**
 * \brief Stop TC Channel
 *
 * Disables the timer clock, stopping the counting.
 *
 * \param tc     Pointer to a Tc instance.
 * \param channel Channel number.
 */
void tc_stop(Tc *tc, uint32_t channel)
{
	volatile TcChannel *tc_channel;

	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	tc_channel = tc->TC_CHANNEL + channel;
	tc_channel->TC_CCR = TC_CCR_CLKDIS;
	tc_channel->TC_IDR = TC_IER_COVFS;
}

/**
 * \brief Enables TC channel interrupts
 *
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \param mask mask of interrupts to enable
 */
void tc_enable_it(Tc *tc, uint32_t channel, uint32_t mask)
{
	assert(channel < ARRAY_SIZE(tc->TC_CHANNEL));

	tc->TC_CHANNEL[channel].TC_IER = mask;
}

/**
 * \brief Find the best clock source for the required frequency
 *
 * Finds the best clock source 
 *
 * \param tc    TC instance.
 * \param freq  Desired timer freq.
 *
 * \return The clock source index
 */
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

uint32_t tc_get_status(Tc *tc, uint32_t channel_num)
{
	return tc->TC_CHANNEL[channel_num].TC_SR;
}


void tc_trigger_on_freq(Tc *tc, uint32_t channel_num, uint32_t freq)
{
	uint32_t tcclks = 0;
	TcChannel* channel = &tc->TC_CHANNEL[channel_num];

	tcclks = tc_find_best_clock_source(tc, freq);
	tc_configure(tc, channel_num, tcclks | TC_CMR_CPCTRG);
	channel->TC_RC = tc_get_available_freq(tc, tcclks) / freq;
}

/**
 * \brief Get available frequency of Timer Counter according to clock selection
 * \param tc Pointer to Tc instance
 * \param tc_clks TC_CMR_TCCLKS_TIMER_CLOCKx field value for clock selection.
 * \return TC frequency
 */
uint32_t tc_get_available_freq(Tc *tc, uint8_t tc_clks)
{
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
		assert(tc_clks <= TC_CMR_TCCLKS_TIMER_CLOCK5);
		return 0;
	}
}

/**
 * \brief Set RA, RB, RC for Timer Counter
 * \param tc Pointer to Tc instance
 * \param channel_num channel number of the Timer Counter
 * \param ra Pointer to the value to set into RA
 * \param rb Pointer to the value to set into RB
 * \param rc Pointer to the value to set into RC
 */
void tc_set_ra_rb_rc(Tc *tc, uint32_t channel_num,
	uint32_t *ra, uint32_t *rb, uint32_t *rc)
{
	TcChannel* channel = &tc->TC_CHANNEL[channel_num];

	if (ra) {
		assert(TC_CMR_WAVE == (channel->TC_CMR & TC_CMR_WAVE));
		channel->TC_RA = *ra;
	}
	if (rb) {
		assert(TC_CMR_WAVE == (channel->TC_CMR & TC_CMR_WAVE));
		channel->TC_RB = *rb;
	}
	if (rc)
		channel->TC_RC = *rc;
}

/**
 * \brief Get RA, RB, RC from Timer Counter
 * \param tc Pointer to Tc instance
 * \param channel_num channel number of the Timer Counter
 * \param ra Pointer to the address to store RA
 * \param rb Pointer to the address to store RB
 * \param rc Pointer to the address to store RC
 */
void tc_get_ra_rb_rc(Tc *tc, uint32_t channel_num,
	uint32_t *ra, uint32_t *rb, uint32_t *rc)
{
	TcChannel* channel = &tc->TC_CHANNEL[channel_num];

	if (ra)
		*ra = channel->TC_RA;
	if (rb)
		*rb = channel->TC_RB;
	if (rc)
		*rc = channel->TC_RC;
}

/**
 * \brief Set Timer Counter Fault Mode
 * \param tc Pointer to Tc instance
 * \param mode fault mode
 */
void tc_set_fault_mode(Tc *tc, uint32_t mode)
{
	tc->TC_FMR = mode;
}
