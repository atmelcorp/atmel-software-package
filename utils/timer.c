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
 *  Implement simple TC usage as system tick.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "timer.h"
#include "peripherals/irq.h"
#include "peripherals/tc.h"
#include "peripherals/pmc.h"

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** System timer */
static struct _timer _sys_timer;

/*----------------------------------------------------------------------------
 *         Exported Functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for timer interrupt.
 */
static void timer_increment(uint32_t source, void* user_arg)
{
	assert(source == get_tc_id_from_addr(_sys_timer.tc));
	struct _timer* timer = (struct _timer*)user_arg;

	uint32_t status = tc_get_status(timer->tc, timer->channel);
	if ((status & TC_SR_CPCS) == TC_SR_CPCS)
		timer->tick++;
}

void timer_configure(struct _timer* timer)
{
	uint32_t rc = 0;
	uint32_t tc_clks = 0;
#if !defined(CONFIG_TIMER_POLLING) || defined(CONFIG_HAVE_PMC_GENERATED_CLOCKS)
	uint32_t tc_id = get_tc_id_from_addr(timer->tc);
#endif

	memcpy(&_sys_timer, timer, sizeof(_sys_timer));

#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
	// For devices that support generated clock, configure TC to use Main
	// Clock as generated clock source
	if (!pmc_is_gck_enabled(tc_id)) {
		pmc_configure_gck(tc_id, PMC_PCR_GCKCSS_MAIN_CLK, 1);
		pmc_enable_gck(tc_id);
	}
#endif

	// Select clock source, configure tc base on timer clock
	tc_clks = tc_find_best_clock_source(timer->tc, timer->resolution);
	tc_configure(timer->tc, timer->channel, tc_clks | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_CPCTRG);
	rc = (tc_get_available_freq(timer->tc, tc_clks) * timer->freq) / timer->resolution;
	tc_set_ra_rb_rc(timer->tc, timer->channel, 0, 0, &rc);

#ifdef CONFIG_TIMER_POLLING
	tc_disable_it(timer->tc, timer->channel, TC_IER_CPCS);
#else
	irq_add_handler(tc_id, timer_increment, &_sys_timer);
	irq_enable(tc_id);
	tc_enable_it(timer->tc, timer->channel, TC_IER_CPCS);
#endif
	tc_start(timer->tc, timer->channel);
}

uint64_t timer_get_interval(uint64_t start, uint64_t end)
{
	if (end >= start)
		return (end - start);
	return (end + (0xFFFFFFFFFFFFFFFF - start) + 1);
}

void timer_start_timeout(struct _timeout* timeout, uint64_t count)
{
	timeout->start = timer_get_tick();
	timeout->count = count ;
}

void timer_reset_timeout(struct _timeout* timeout)
{
	timeout->start = timer_get_tick();
}

uint8_t timer_timeout_reached(struct _timeout* timeout)
{
	return timer_get_interval(timeout->start, timer_get_tick()) >= timeout->count;
}

void timer_sleep(uint64_t count)
{
	volatile uint32_t _timeout_usec = tc_get_cv(_sys_timer.tc, _sys_timer.channel);
	volatile uint64_t _timeout_msec = timer_get_tick() + count;

	while (((int64_t)_timeout_msec - timer_get_tick()) > 0) {
#ifndef CONFIG_TIMER_POLLING
		irq_wait();
#endif
	}

	while (((int32_t)_timeout_usec - tc_get_cv(_sys_timer.tc, _sys_timer.channel)) > 0);
}

void timer_usleep(uint64_t count)
{
	volatile uint32_t _timeout_usec = tc_get_cv(_sys_timer.tc, _sys_timer.channel) + (count % 1000);
	volatile uint64_t _timeout_msec = timer_get_tick() + (count / 1000);

	while (((int64_t)_timeout_msec - timer_get_tick()) > 0) {
#ifndef CONFIG_TIMER_POLLING
		irq_wait();
#endif
	}

	while (((int64_t)_timeout_usec - tc_get_cv(_sys_timer.tc, _sys_timer.channel)) > 0);
}

uint64_t timer_get_tick(void)
{
#ifdef CONFIG_TIMER_POLLING
	timer_increment(get_tc_id_from_addr(_sys_timer.tc), &_sys_timer);
#endif
	return _sys_timer.tick;
}

void msleep(uint32_t count)
{
	timer_sleep(count);
}

void sleep(uint32_t count)
{
	msleep(count * 1000);
}

void usleep(uint32_t count)
{
	timer_usleep(count);
}
