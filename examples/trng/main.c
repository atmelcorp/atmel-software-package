/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 *  \page trng True Random Number Generator Example with sama5d4x Microcontrollers
 *
 *  \section Purpose
 *  The TRNG example shows how to generate random data with TRNG peripheral.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-EK and SAMA5D4-XULT.
 *
 * \section Description
 *
 * The demonstration program configure TRNG peripheral. As soon as the TRNG is enabled
 * the generator provides one 32-bit value every 84 clock cycles.
 * TRNG interrupt status DATRDY is set when a new random value is ready, it can be read
 * out on the 32-bit output data register (TRNG_ODATA)in TRNG interrupt routine.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- TRNG Example xxx --
 *      -- SAMxxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      \endcode
 *  -# Input command according to the menu.
 *
 * \section References
 * - trng/main.c
 * - trng.h
 * - trng.h
 */

/** \file
 *
 *  This file contains all the specific code for the TRNG
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <board.h>

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"

#include "peripherals/trng.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
//static uint32_t uData;
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
static void trng_handler(void)
{
	if (TRNG_GetStatus() == TRNG_ISR_DATRDY) {
		TRNG_DisableIt();
		printf("0x%x \n\r", (unsigned int)TRNG_GetRandData());
		TRNG_EnableIt();
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief $page_name$ Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 *  \callgraph
 */
int main(void)
{
	/* Disable watchdog */
	WDT_Disable(WDT);

#if defined (ddram)
	mmu_initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_icache();
	cp15_enable_dcache();
#endif

	/* Output example information */
	printf("-- TRNG Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Enable TRNG peripheral clock */
	pmc_enable_peripheral(ID_TRNG);

	aic_set_source_vector(ID_TRNG, trng_handler);
	aic_enable(ID_TRNG);
	TRNG_EnableIt();
	TRNG_Enable(0x524e47);
	while (1) ;
}
