/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include <assert.h>
#include <string.h>

#include "chip.h"
#include "eefc.h"
#include "errno.h"
#include "irqflags.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

void eefc_enable_frdy_it(Eefc* eefc)
{
	eefc->EEFC_FMR |= EEFC_FMR_FRDY;
}

void eefc_disable_frdy_it(Eefc* eefc)
{
	eefc->EEFC_FMR &= ~EEFC_FMR_FRDY;
}

void eefc_set_flash_wait_states(Eefc* eefc, uint8_t cycles)
{
	eefc->EEFC_FMR = (eefc->EEFC_FMR & ~EEFC_FMR_FWS_Msk) | EEFC_FMR_FWS(cycles);
}

SECTION(".ramfunc")
int eefc_read_unique_id(Eefc* eefc, uint8_t* uid)
{
	uint32_t status;
	int i;

	if (!uid)
		return -EINVAL;

	/* Disable interrupts (see following comment) */
	arch_irq_disable();

	/* From this point, no code located in flash should be called: CPU
	 * cannot fetch code from flash during "Read Unique Identifier"
	 * procedure. */

	/* Send the Start Read unique Identifier command (STUI) */
	eefc->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_STUI;

	/* Wait for Unique Identifier to be ready (i.e. !FRDY) */
	do {
		status = EEFC->EEFC_FSR;
	} while ((status & EEFC_FSR_FRDY) == EEFC_FSR_FRDY);

	/* The Unique Identifier is located in the first 128 bits of the Flash */
	for (i = 0; i < 16; i++)
		uid[i] = *(uint8_t*)(IFLASH_ADDR + i);

	/* Send the Stop Read unique Identifier command (SPUI) */
	eefc->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SPUI;

	/* Wait for Stop Unique Identifier to be complete (i.e. FRDY) */
	do {
		status = EEFC->EEFC_FSR;
	} while ((status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY);

	/* Flash is available again, re-enable interrupts */
	arch_irq_enable();

	return 0;
}

int eefc_perform_command(Eefc* eefc, uint32_t cmd, uint32_t arg)
{
	uint32_t status;

	eefc->EEFC_FCR = EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FARG(arg) | (cmd & EEFC_FCR_FCMD_Msk);
	do {
		status = EEFC->EEFC_FSR;
	} while ((status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY);

	if (status & EEFC_FSR_FLOCKE)
		return -EPERM;
	else if (status & EEFC_FSR_FLERR)
		return -EIO;
	else if (status & EEFC_FSR_FCMDE)
		return -EINVAL;

	return 0;
}

uint32_t eefc_get_status(Eefc* eefc)
{
	return eefc->EEFC_FSR;
}

uint32_t eefc_get_result(Eefc* eefc)
{
	return eefc->EEFC_FRR;
}
