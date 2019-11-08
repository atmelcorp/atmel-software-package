/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#include "assert.h"
#include <stdio.h>

#include "board.h"
#include "low-power-config.h"
#include "clk-config.h"

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static unsigned int read_reg[3];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void low_power_cfg(uint8_t mode) {
	assert(mode <= ULP0);
	if (mode == ULP0) {
		/* Back up IOs and USB transceivers */
		read_reg[0] = PMC->PMC_PCSR0;
		read_reg[1] = PMC->PMC_SCSR;
		read_reg[2] = PMC->CKGR_UCKR;

		/* Set the I/Os to an appropriate state */
		board_restore_pio_reset_state();

		/* Disable the USB transceivers and all peripheral clocks */
		board_save_misc_power();
	}
}

void low_power_exit(uint8_t mode) {
	assert(mode == ULP0);
	if (mode == ULP0) {
		/* Restore IOs and USB transceivers */
		PMC->PMC_PCER0 = read_reg[0];
		PMC->PMC_SCER  = read_reg[1];
		PMC->CKGR_UCKR = read_reg[2];
	}
}

RAMCODE void processor_idle(void) {
	asm("mcr p15, 0, %0, c7, c10, 4" :: "r"(0) : "memory");
	/* wait for interrupt */
	asm("mcr p15, 0, %0, c7, c0, 4" :: "r"(0) : "memory");
}

RAMCODE void processor_ulp(uint8_t mode) {
	assert(mode == ULP0);
	processor_idle();
}
