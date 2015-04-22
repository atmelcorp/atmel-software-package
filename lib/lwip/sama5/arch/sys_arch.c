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

#include "core/aic.h"
#include "core/pmc.h"
#include "time/tc.h"

#include "sys_arch.h"

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/** clock tick count */
static volatile uint32_t dwClockTick;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_IrqHandler( void )
{
    volatile uint32_t dwDummy ;

    /* Clear status bit to acknowledge interrupt */
    dwDummy = TC0->TC_CHANNEL[0].TC_SR ;

    /* Increase tick */
    dwClockTick ++;
}


/**
 * Initialize for timing operation
 */
void sys_init_timing(void)
{
    uint32_t div;
    uint32_t tcclks;

    /* Clear tick value */
    dwClockTick = 0;

    /* Enable peripheral clock. */
    PMC_EnablePeripheral( ID_TC0 ) ;

    /* Configure TC for a CLOCK_CONF_SECOND frequency. */
    TC_FindMckDivisor( CLOCK_CONF_SECOND, BOARD_MCK, &div, &tcclks, BOARD_MCK );
    TC_Configure( TC0, 0, tcclks | TC_CMR_CPCTRG );
    TC0->TC_CHANNEL[0].TC_RC = BOARD_MCK / (CLOCK_CONF_SECOND * div);

    /* Configure and enable interrupt on RC compare */
    //IRQ_ConfigureIT(ID_TC0,(0x0 << 5), TC0_IrqHandler);
    AIC_EnableIT(ID_TC0);
    TC0->TC_CHANNEL[ 0 ].TC_IER = TC_IER_CPCS ;

    /* Start timer */
    TC_Start( TC0, 0 );
}

/**
 * Read for clock time (ms)
 */
unsigned int sys_get_ms(void)
{
    return dwClockTick;
}

