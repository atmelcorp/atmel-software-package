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
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "irqflags.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "timer.h"

/*----------------------------------------------------------------------------
 *         Local type definitions
 *----------------------------------------------------------------------------*/

struct _timer {
	Tc* tc;
	uint8_t channel;
	uint32_t channel_freq;
	volatile uint32_t upper;
};

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** System timer */
static struct _timer _timer;

/*----------------------------------------------------------------------------
 *         Local Functions
 *----------------------------------------------------------------------------*/

static void timer_update_upper_tick_counter(void)
{
	uint32_t status = tc_get_status(_timer.tc, _timer.channel);
	if ((status & TC_SR_COVFS) == TC_SR_COVFS)
		_timer.upper++;
}

static uint32_t timer_get_upper_tick_counter(void)
{
	timer_update_upper_tick_counter();
	return _timer.upper;
}

#ifndef CONFIG_TIMER_POLLING

/**
 *  \brief Handler for timer interrupt.
 */
static void timer_irq_handler(uint32_t source, void* user_arg)
{
	timer_update_upper_tick_counter();
}

#endif /* !CONFIG_TIMER_POLLING */

static uint64_t _timer_get_tick(void)
{
	uint32_t upper, lower;

	do {
		upper = timer_get_upper_tick_counter();
		COMPILER_BARRIER();
		lower = tc_get_cv(_timer.tc, _timer.channel);
	} while (upper != timer_get_upper_tick_counter());
	return (((uint64_t)upper) << TC_CHANNEL_SIZE) | lower;
}

/*----------------------------------------------------------------------------
 *         Exported Functions
 *----------------------------------------------------------------------------*/

void timer_configure(Tc* tc, uint8_t channel, uint32_t clock_source)
{
	uint32_t tc_id = get_tc_id_from_addr(tc, channel);

	_timer.tc = tc;
	_timer.channel = channel;

	if (!pmc_is_peripheral_enabled(tc_id))
		pmc_configure_peripheral(tc_id, NULL, true);

	tc_configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP |
			(clock_source & TC_CMR_TCCLKS_Msk));
	_timer.channel_freq = tc_get_channel_freq(tc, channel);
#ifndef CONFIG_TIMER_POLLING
	irq_add_handler(tc_id, timer_irq_handler, &_timer);
	irq_enable(tc_id);
	tc_enable_it(tc, channel, TC_IER_COVFS);
#endif
	tc_start(tc, channel);
}

uint64_t timer_get_interval(uint64_t start, uint64_t end)
{
	if (end >= start)
		return end - start;
	return end + (0xffffffffffffffffu - start) + 1;
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
	uint64_t end_tick = timer_get_tick() + count;

	while (timer_get_tick() <= end_tick);
}

uint64_t timer_get_tick(void)
{
	return (_timer_get_tick() * 1000) / _timer.channel_freq;
}

void sleep(uint32_t count)
{
	timer_sleep(count * 1000);
}

void msleep(uint32_t count)
{
	timer_sleep(count);
}

void usleep(uint32_t count)
{
	uint64_t deadline;

	/* Disable interrupts */
	arch_irq_disable();

	/* Compute deadline */
	deadline = _timer_get_tick();
	deadline += ROUND_INT_DIV((_timer.channel_freq / 1000) * count, 1000);

	/* Wait for deadline to be reached */
	while ((int64_t)(_timer_get_tick() - deadline) < 0);

	/* Re-enable interrupts */
	arch_irq_enable();
}
