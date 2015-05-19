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
 *  \page test board hardware with sama5d2 Microcontrollers
 *
 *  \section Purpose
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-XULT.
 *
 *  \section Description
 *
 * \file
 *
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include "io/led.h"

#include "bus/console.h"

#include "time/tc.h"
#include "time/pit.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/


extern int main()
{

	/* Disable watchdog */
	WDT_Disable(WDT);

#if defined (ddram)
	MMU_Initialize((uint32_t *) 0x20C000);
	CP15_EnableMMU();
	CP15_EnableDcache();
	CP15_EnableIcache();
#endif

	/* Output example information */
	printf("-- Test board HW %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Configure PIT. */
	printf("Configure PIT \n\r");
	ConfigurePit();


  return 0;
}
