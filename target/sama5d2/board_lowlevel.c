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
 * \file
 *
 * Provides the low-level initialization function that called on chip startup.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "timer.h"

#include "peripherals/aic.h"
#include "peripherals/matrix.h"
#include "peripherals/pmc.h"

#include "board_lowlevel.h"

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Performs the low-level initialization of the chip.
 */
void low_level_init(void)
{
	/* Configure clocking if code is not in external mem */
	if ((uint32_t)low_level_init < DDR_CS_ADDR)
	{
		pmc_switch_mck_to_slck();
		pmc_set_mck_h32mxdiv(PMC_MCKR_H32MXDIV_H32MXDIV2);
		pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
		pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
		pmc_set_mck_divider(PMC_MCKR_MDIV_EQ_PCK);
		/* Disable PLLA */
		pmc_set_plla(0, PMC_PLLICPR_IPLL_PLLA(0x3));
		pmc_select_external_osc();
		/* Configure PLLA */
		pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
			CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(82) |
			CKGR_PLLAR_DIVA_BYPASS, PMC_PLLICPR_IPLL_PLLA(0x3));
		pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
		pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
		pmc_switch_mck_to_pll();
	}

	/* Setup default interrupt handlers */
	aic_initialize();

	/* Timer */
	timer_configure(BOARD_TIMER_RESOLUTION);
}
