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

#ifndef TIMER_H_
#define TIMER_H_

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"

/*----------------------------------------------------------------------------
 *         Type definitions
 *----------------------------------------------------------------------------*/

struct _timeout
{
	uint64_t start;
	uint64_t count;
};

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures the timer and reset tick counter.
 *
 * If CONFIG_TIMER_POLLING is not defined, the TC interrupt will be used to
 * increment the tick counter.  If CONFIG_TIMER_POLLING is defined, the tick
 * counter will be updated from the TC when requested.
 *
 * \note TC is enabled automatically in this function.
 * \warning If interrupts are used, this function also reconfigures the TC
 * handler in AIC.
 *
 * \param timer Pointer to a struct _timer instance
 */
extern void timer_configure(Tc* tc, uint8_t channel, uint32_t clock_source);

/**
 * \brief Wait for count times the timer resolution
 *
 * If interrupts are enabled, the waiting loop will use WFI instructions to put
 * the core to sleep between timer ticks.  Otherwise, if polling is enabled, a
 * busy-loop is used to poll the TC counter value.
 */
extern void timer_sleep(uint64_t count);

/**
 *  \brief Initialize a timeout
 */
extern void timer_start_timeout(struct _timeout* timeout, uint64_t count);

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
extern uint64_t timer_get_interval(uint64_t start, uint64_t end);

/**
 * \brief Returns the current number of ticks
 */
extern uint64_t timer_get_tick(void);

/**
 *  \brief Wait for at least count seconds.
 */
extern void sleep(uint32_t count);

/**
 *  \brief Wait for at least count milliseconds
 */
extern void msleep(uint32_t count);

/**
 *  \brief Wait for at least count microseconds
 *
 * Notes:
 * - interrupts are disabled during the wait
 * - if count is <2, it is assumed to be 2
 * - maximum wait interval depends on the effective TC frequency and the TC
 * channel resolution (it is expected that this function is called with
 * count<1000)
 */
extern void usleep(uint32_t count);

#endif /* TIMER_H_ */
