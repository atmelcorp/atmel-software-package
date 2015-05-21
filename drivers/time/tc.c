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
 *  <li> Optionally, use tc_find_mck_divisor() to let the program find the best
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
*  -# Optionally, use tc_find_mck_divisor() to let the program find the best
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
#include "time/tc.h"
#include "core/pmc.h"

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
 * \param pTc  Pointer to a Tc instance.
 * \param channel Channel number.
 * \param mode  Operating mode (TC_CMR value).
 */
void tc_configure(Tc * pTc, uint32_t channel, uint32_t mode)
{
	volatile TcChannel *pTcCh;

	assert(channel <
	       (sizeof (pTc->TC_CHANNEL) / sizeof (pTc->TC_CHANNEL[0])));
	pTcCh = pTc->TC_CHANNEL + channel;

	/*  Disable TC clock */
	pTcCh->TC_CCR = TC_CCR_CLKDIS;

	/*  Disable interrupts */
	pTcCh->TC_IDR = 0xFFFFFFFF;

	/*  Clear status register */
	pTcCh->TC_SR;

	/*  Set mode */
	pTcCh->TC_CMR = mode;
}

/**
 * \brief Reset and Start the TC Channel
 *
 * Enables the timer clock and performs a software reset to start the counting.
 *
 * \param pTc  Pointer to a Tc instance.
 * \param channel Channel number.
 */
void tc_start(Tc * pTc, uint32_t channel)
{
	volatile TcChannel *pTcCh;

	assert(channel <
	       (sizeof (pTc->TC_CHANNEL) / sizeof (pTc->TC_CHANNEL[0])));

	pTcCh = pTc->TC_CHANNEL + channel;
	pTcCh->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	pTcCh->TC_IER = TC_IER_COVFS;
}

/**
 * \brief Stop TC Channel
 *
 * Disables the timer clock, stopping the counting.
 *
 * \param pTc     Pointer to a Tc instance.
 * \param channel Channel number.
 */
void tc_stop(Tc * pTc, uint32_t channel)
{
	volatile TcChannel *pTcCh;

	assert(channel <
	       (sizeof (pTc->TC_CHANNEL) / sizeof (pTc->TC_CHANNEL[0])));

	pTcCh = pTc->TC_CHANNEL + channel;
	pTcCh->TC_CCR = TC_CCR_CLKDIS;
	pTcCh->TC_IDR = TC_IER_COVFS;
}

/**
 * \brief Find best MCK divisor
 *
 * Finds the best MCK divisor given the timer frequency and MCK. The result
 * is guaranteed to satisfy the following equation:
 * \code
 *   (MCK / (DIV * 65536)) <= freq <= (MCK / DIV)
 * \endcode
 * with DIV being the highest possible value.
 *
 * \param freq  Desired timer frequency.
 * \param dwMCk  Master clock frequency.
 * \param div  Divisor value.
 * \param tc_clks  TCCLKS field value for divisor.
 * \param board_mck  Board clock frequency.
 *
 * \return 1 if a proper divisor has been found, otherwise 0.
 */
extern uint32_t tc_find_mck_divisor (uint32_t freq, uint32_t * div,
				  uint32_t * tc_clks)
{
	const uint32_t master_clock = pmc_get_master_clock();
	const uint32_t periph_clock = pmc_get_peripheral_clock(ID_TC0);
	const uint32_t adivisors[5] = { 2, 8, 32, 128, master_clock / 32768 };

	uint32_t dwIndex = 0;

	/*  Satisfy lower bound */
	while (freq < ((periph_clock / adivisors[dwIndex]) / 65536)) {
		dwIndex++;

		/*  If no divisor can be found, return 0 */
		if (dwIndex == (sizeof (adivisors) / sizeof (adivisors[0]))) {
			return 0;
		}
	}

	/*  Try to maximize DIV while satisfying upper bound */
	while (dwIndex < 4) {

		if (freq > (periph_clock / adivisors[dwIndex + 1])) {
			break;
		}
		dwIndex++;
	}

	/*  Store results */
	if (div) {
		*div = adivisors[dwIndex];
	}
	if (tc_clks) {
		*tc_clks = dwIndex;
	}

	return 1;
}
