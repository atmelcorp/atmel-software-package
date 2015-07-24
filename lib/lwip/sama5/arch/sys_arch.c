/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"

#include "sys_arch.h"

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/** clock tick count */
static volatile uint32_t clock_tick;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  Interrupt handler for TC0 interrupt.
 */
static void tc_handler(void)
{
	uint32_t dummy;

	/* Clear status bit to acknowledge interrupt */
	dummy = tc_get_status(TC0, 0);
	(void) dummy;

	clock_tick++;
}

/**
 * Initialize for timing operation
 */
void sys_init_timing(void)
{
	/** Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);

	/* Put the source vector */
	aic_set_source_vector(ID_TC0, tc_handler);

	/** Configure TC for a CLOCK_CONF_SECOND frequency and trigger on RC compare. */
	tc_trigger_on_freq(TC0, 0, CLOCK_CONF_SECOND);

	/* Configure and enable interrupt on RC compare */
	tc_enable_it(TC0, 0, TC_IER_CPCS);
	aic_enable(ID_TC0);

	/* Start the counter if LED1 is enabled. */
	tc_start(TC0, 0);
}

/**
 * Read for clock time (ms)
 */
unsigned int sys_get_ms(void)
{
	return clock_tick;
}

