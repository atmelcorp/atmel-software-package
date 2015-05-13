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
 *  Implement simple PIT usage as system tick.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "time/timetick.h"
#include "time/tc.h"
#include "time/pit.h"

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** Tick Counter united by ms */
static volatile uint32_t _tick_count = 0;

/*----------------------------------------------------------------------------
 *         Exported Functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for Sytem Tick interrupt.
 */
void timetick_increment(uint32_t inc)
{
	_tick_count += inc;
}

/**
 *  \brief Configures the PIT & reset tickCount.
 *  Systick interrupt handler will generates 1ms interrupt and increase a
 *  tickCount.
 *  \note IRQ handler must be configured before invoking this function.
 *  \note PIT is enabled automatically in this function.
 *  \param new_mck  Current master clock.
 */
extern uint32_t timetick_configure(uint32_t new_mck)
{
	_tick_count = 0;
	pit_init(1000);
	pit_enable_it();
	pit_enable();
	return 0;
}

/**
 * Get Delayed number of tick
 * \param startTick Start tick point.
 * \param endTick   End tick point.
 */
extern uint32_t timetick_get_delay_in_ticks(uint32_t startTick, uint32_t endTick)
{
	if (endTick >= startTick)
		return (endTick - startTick);
	return (endTick + (0xFFFFFFFF - startTick) + 1);
}

/**
 *  \brief Get current Tick Count, in ms.
 */
extern uint32_t timetick_get_tick_count(void)
{
	return _tick_count;
}

/**
 *  \brief Sync Wait for several ms
 */
void timetick_wait(volatile uint32_t ms)
{
	uint32_t start, current;
	start = _tick_count;
	do {
		current = _tick_count;
	} while (current - start < ms);
}

/**
 *  \brief Sync Sleep for several ms
 */
void timetick_sleep(volatile uint32_t ms)
{
	uint32_t start, current;
	asm("CPSIE   I");
	start = _tick_count;

	do {
		current = _tick_count;
		if (current - start > ms) {
			break;
		}
		asm("WFI");
	} while (1);
}
