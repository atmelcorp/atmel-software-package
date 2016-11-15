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

bool slowclock_is_internal(void)
{
	return (SUPC->SUPC_SR & SUPC_SR_OSCSEL) == SUPC_SR_OSCSEL_RC;
}

void slowclock_select_internal(void)
{
	if (!slowclock_is_internal())
		trace_fatal("Cannot switch back to internal 32KHz RC\r\n");
}

void slowclock_select_external(void)
{
	if (slowclock_is_internal()) {
		SUPC->SUPC_CR = SUPC_CR_KEY_PASSWD | SUPC_CR_XTALSEL_CRYSTAL_SEL;
		while (!(SUPC->SUPC_SR & SUPC_SR_OSCSEL));
	}
}
