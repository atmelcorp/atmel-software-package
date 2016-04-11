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
 *  \par Purpose
 *
 *  Methods and definitions for an internal timer.
 *
 *  Defines a common and simpliest use of timer to generate delays using PIT
 *
 *  \par Usage
 *
 *  -# Configure the System Tick with timer_configure() when MCK changed
 *     \note
 *     Must be done before any invoke of timer_wait(), or timer_sleep()
 *  -# Uses timer_wait to actively wait according to your timer resolution.
 *  -# Uses timer_sleep to passively wait ccording to your timer resolution.
 *
 */

#ifndef TIMER_HEADER_
#define TIMER_HEADER_

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

struct _timeout
{
	uint32_t start;
	uint32_t count;
};

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures the timer and reset tick counter.
 *
 * If CONFIG_TIMER_POLLING is not defined, the PIT interrupt will be used to
 * increment the tick counter.  If CONFIG_TIMER_POLLING is defined, the tick
 * counter will be updated from the PIT when requested.
 *
 * \note PIT is enabled automatically in this function.
 * \warning If interrupts are used, this function also reconfigures the PIT
 * handler in AIC.
 *
 * \param resolution initialize timer resolution (=PIT period, in nano seconds)
 */
extern void timer_configure(uint32_t resolution);

/**
 * \brief Wait for count times the timer resolution
 *
 * If interrupts are enabled, the waiting loop will use WFI instructions to put
 * the core to sleep between timer ticks.  Otherwise, if polling is enabled, a
 * busy-loop is used to poll the PIT counter value.
 */
extern void timer_wait(uint32_t count);

/**
 *  \brief Alias for timer_wait.
 */
extern void timer_sleep(uint32_t count);

/**
 * \brief Retrieve current timer resolution.
 *
 * \return Current timer resolution (0 if not already configured)
 */
extern uint32_t timer_get_resolution(void);

/**
 *  \brief Initialize a timeout
 */
extern void timer_start_timeout(struct _timeout* timeout, uint32_t count);

/**
 *  \brief Reset the starting time of a timeout structure
 */
extern void timer_reset_timeout(struct _timeout* timeout);

/**
 *  \brief Tells if the timeout as been reached
 */
extern uint8_t timer_timeout_reached(struct _timeout* timeout);

/**
 * \brief Compute elapsed number of ticks between start and end with
 * taking overlaps into account
 *
 * \param start Start tick point.
 * \param end End tick point.
 */
extern uint32_t timer_get_interval(uint32_t start, uint32_t end);

/**
 * \brief Returns the current number of ticks
 */
extern uint32_t timer_get_tick(void);

#endif /* TIMER_HEADER_ */
