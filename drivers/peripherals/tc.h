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

#ifndef TC_H_
#define TC_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

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
extern void tc_configure (Tc* tc, uint32_t channel, uint32_t mode);

/**
 * \brief Reset and Start the TC Channel
 *
 * Enables the timer clock and performs a software reset to start the counting.
 *
 * \param tc  Pointer to a Tc instance.
 * \param channel Channel number.
 */
extern void tc_start(Tc * tc, uint32_t channel);

/**
 * \brief Stop TC Channel
 *
 * Disables the timer clock, stopping the counting.
 * This will also disable all interrupts for the channel.
 *
 * \param tc     Pointer to a Tc instance.
 * \param channel Channel number.
 */
extern void tc_stop(Tc * tc, uint32_t channel);

/**
 * \brief Enables TC channel interrupts
 *
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \param mask mask of interrupts to enable
 */
extern void tc_enable_it(Tc* tc, uint32_t channel, uint32_t mask);

/**
 * \brief Disables TC channel interrupts
 *
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \param mask mask of interrupts to disable
 */
extern void tc_disable_it(Tc* tc, uint32_t channel, uint32_t mask);

/**
 * \brief Find the best clock source for the requested frequency
 *
 * Finds a clock source whose frequency is greater or equal to the requested
 * frequency and closer than all other clock sources to the requested
 * frequency.
 *
 * If no clock source has a frequency that is greater or equal to the requested
 * frequency, the clock source with the higher frequency is returned.
 *
 * \param tc Pointer to Tc instance.
 * \param channel Channel number.
 * \param freq Requested timer frequency
 *
 * \return The clock source (one of the TC_CMR_TCCLKS_TIMER_CLOCKx constants)
 */
extern uint32_t tc_find_best_clock_source(Tc *tc, uint8_t channel, uint32_t freq);

/**
 * \brief Get the value of the status register for a Channel
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \return value of the status register for the channel
 */
extern uint32_t tc_get_status(Tc* tc, uint32_t channel);

/**
 * \brief Get available frequency of Timer Counter according to clock selection
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \param tc_clks TC_CMR_TCCLKS_TIMER_CLOCKx field value for clock selection.
 * \return TC frequency
 */
extern uint32_t tc_get_available_freq(Tc* tc, uint8_t channel, uint8_t tc_clks);

/**
 * \brief Get current frequency of Timer Counter according to clock selection
 * \param tc Pointer to Tc instance
 * \param channel Channel number
 * \return TC frequency
 */
extern uint32_t tc_get_channel_freq(Tc* tc, uint32_t channel);

/**
 * \brief Set RA, RB, RC for Timer Counter
 * \param tc Pointer to Tc instance
 * \param channel channel number of the Timer Counter
 * \param ra Pointer to the value to set into RA
 * \param rb Pointer to the value to set into RB
 * \param rc Pointer to the value to set into RC
 */
extern void tc_set_ra_rb_rc(Tc* tc, uint32_t channel,
	uint32_t *ra, uint32_t *rb, uint32_t *rc);

/**
 * \brief Get RA, RB, RC from Timer Counter
 * \param tc Pointer to Tc instance
 * \param channel channel number of the Timer Counter
 * \param ra Pointer to the address to store RA
 * \param rb Pointer to the address to store RB
 * \param rc Pointer to the address to store RC
 */
extern void tc_get_ra_rb_rc(Tc* tc, uint32_t channel,
	uint32_t *ra, uint32_t *rb, uint32_t *rc);

#ifdef CONFIG_HAVE_TC_FAULT_MODE

/**
 * \brief Set Timer Counter Fault Mode
 * \param tc Pointer to Tc instance
 * \param mode fault mode
 */
extern void tc_set_fault_mode(Tc* tc, uint32_t mode);

#endif /* CONFIG_HAVE_TC_FAULT_MODE */

/**
 * \brief get count value from Timer Counter
 * \param tc Pointer to Tc instance
 * \param channel channel number of the Timer Counter.
 * \return cv of TC
 */
extern uint32_t tc_get_cv(Tc* tc, uint32_t channel);

#endif /* TC_H_ */
