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

#include "chip.h"

#include "peripherals/slowclock.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

RAMCODE bool slowclock_is_internal(enum _slowclock_domain domain)
{
	return (SCKC->SCKC_CR & SCKC_CR_OSCSEL) != SCKC_CR_OSCSEL;
}

RAMCODE void slowclock_select_internal(enum _slowclock_domain domain)
{
	volatile int count;

	if (slowclock_is_internal(domain))
		return;

#ifdef SCKC_CR_RCEN
	/* enable external OSC 32 kHz */
	SCKC->SCKC_CR |= SCKC_CR_RCEN;
	/* Wait 32,768 Hz Startup Time for clock stabilization (software loop) */
	for (count = 0; count < 0x1000; count++);
#endif

	/* switch from extenal OSC 32kHz to internal RC 32 kHz */
	/* switch slow clock source to internal OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_RC;

	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++);

#ifdef SCKC_CR_OSC32EN
	if ((SCKC->SCKC_CR & SCKC_CR_OSC32EN) == SCKC_CR_OSC32EN)
		SCKC->SCKC_CR &= ~SCKC_CR_OSC32EN;
#endif
}

RAMCODE void slowclock_select_external(enum _slowclock_domain domain)
{
	volatile int count;

	if (!slowclock_is_internal(domain))
		return;

#ifdef SCKC_CR_OSC32EN
	/* enable external OSC 32 kHz */
	SCKC->SCKC_CR |= SCKC_CR_OSC32EN;
	/* Wait 32,768 Hz Startup Time for clock stabilization (software loop) */
	for (count = 0; count < 0x1000; count++);
#endif

	/* switch from internal RC 32kHz to external OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_XTAL;

	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++);

#ifdef SCKC_CR_RCEN
	if ((SCKC->SCKC_CR & SCKC_CR_RCEN) == SCKC_CR_RCEN)
		SCKC->SCKC_CR &= ~SCKC_CR_RCEN;
#endif
}

uint32_t slowclock_get_clock(enum _slowclock_domain domain)
{
	if (slowclock_is_internal(domain))
		return 32000;
	else
		return 32768;
}


RAMCODE void slowclock_set_bypass(bool bypass)
{
#ifdef SCKC_CR_OSC32BYP
	uint32_t mask = bypass ? SCKC_CR_OSC32BYP : SCKC_CR_OSC32EN;

	/* set bypass or not */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~(SCKC_CR_OSC32BYP | SCKC_CR_OSC32EN)) | mask;
#endif
}
