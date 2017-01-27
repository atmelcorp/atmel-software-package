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
#include "trace.h"

#include "peripherals/slowclock.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

bool slowclock_is_internal(enum _slowclock_domain domain)
{
#ifdef CONFIG_HAVE_SLOWCLOCK_TIMING_DOMAIN
	if (domain == SLOWCLOCK_DOMAIN_TIMING)
		return (SUPC->SUPC_SR & SUPC_SR_TDOSCSEL) == SUPC_SR_TDOSCSEL_RC;
	else
		return (SUPC->SUPC_PWR & SUPC_PWR_MONSELS) == SUPC_PWR_MONSELS_RC;
#else
	return (SUPC->SUPC_SR & SUPC_SR_OSCSEL) == SUPC_SR_OSCSEL_RC;
#endif
}

void slowclock_select_internal(enum _slowclock_domain domain)
{
	if (!slowclock_is_internal(domain))
		trace_fatal("Cannot switch back to internal 32KHz RC\r\n");
}

void slowclock_select_external(enum _slowclock_domain domain)
{
	if (slowclock_is_internal(domain)) {
#ifdef CONFIG_HAVE_SLOWCLOCK_TIMING_DOMAIN
		if (domain == SLOWCLOCK_DOMAIN_TIMING) {
			SUPC->SUPC_CR = SUPC_CR_KEY_PASSWD | SUPC_CR_TDXTALSEL_CRYSTAL_SEL;
			while ((SUPC->SUPC_SR & SUPC_SR_TDOSCSEL) != SUPC_SR_TDOSCSEL_CRYST);
		} else {
			SUPC->SUPC_CR = SUPC_CR_KEY_PASSWD | SUPC_CR_MDXTALSEL_CRYSTAL_SEL;
			while ((SUPC->SUPC_PWR & SUPC_PWR_MONSELS) != SUPC_PWR_MONSELS_CRYST);
		}
#else
		SUPC->SUPC_CR = SUPC_CR_KEY_PASSWD | SUPC_CR_XTALSEL_CRYSTAL_SEL;
		while ((SUPC->SUPC_SR & SUPC_SR_OSCSEL) != SUPC_SR_OSCSEL_CRYST);
#endif
	}
}

uint32_t slowclock_get_clock(enum _slowclock_domain domain)
{
	if (slowclock_is_internal(domain))
		return 32000;
	else
		return 32768;
}
