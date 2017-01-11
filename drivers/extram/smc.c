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
  *  \file
  *
  *  Implementation of SMC functions.
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"

#include "peripherals/pmc.h"
#include "extram/smc.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void smc_nand_configure(uint8_t bus_width)
{
#ifdef ID_SMC
	pmc_configure_peripheral(ID_SMC, NULL, true);
#endif

	SMC->SMC_CS[NAND_EBI_CS].SMC_SETUP =
		SMC_SETUP_NWE_SETUP(2) |
		SMC_SETUP_NCS_WR_SETUP(2) |
		SMC_SETUP_NRD_SETUP(2) |
		SMC_SETUP_NCS_RD_SETUP(2);

	SMC->SMC_CS[NAND_EBI_CS].SMC_PULSE =
		SMC_PULSE_NWE_PULSE(7) |
		SMC_PULSE_NCS_WR_PULSE(7) |
		SMC_PULSE_NRD_PULSE(7) |
		SMC_PULSE_NCS_RD_PULSE(7);

	SMC->SMC_CS[NAND_EBI_CS].SMC_CYCLE =
		SMC_CYCLE_NWE_CYCLE(13) |
		SMC_CYCLE_NRD_CYCLE(13);

#ifdef SMC_TIMINGS_NFSEL
	SMC->SMC_CS[NAND_EBI_CS].SMC_TIMINGS =
		SMC_TIMINGS_TCLR(3) |
		SMC_TIMINGS_TADL(27) |
		SMC_TIMINGS_TAR(3) |
		SMC_TIMINGS_TRR(6) |
		SMC_TIMINGS_TWB(5) |
		SMC_TIMINGS_NFSEL;
#endif

	SMC->SMC_CS[NAND_EBI_CS].SMC_MODE =
		SMC_MODE_READ_MODE |
		SMC_MODE_WRITE_MODE |
		((bus_width == 8 ) ? SMC_MODE_DBW_BIT_8 : SMC_MODE_DBW_BIT_16) |
		SMC_MODE_TDF_CYCLES(1);
}

void smc_nor_configure(uint8_t cs, uint8_t bus_width)
{
#ifdef ID_SMC
	pmc_configure_peripheral(ID_SMC, NULL, true);
#endif

	SMC->SMC_CS[cs].SMC_SETUP =
		SMC_SETUP_NWE_SETUP(1) |
		SMC_SETUP_NCS_WR_SETUP(0) |
		SMC_SETUP_NRD_SETUP(2) |
		SMC_SETUP_NCS_RD_SETUP(0);

	SMC->SMC_CS[cs].SMC_PULSE =
		SMC_PULSE_NWE_PULSE(10) |
		SMC_PULSE_NCS_WR_PULSE(10) |
		SMC_PULSE_NRD_PULSE(11) |
		SMC_PULSE_NCS_RD_PULSE(11);

	SMC->SMC_CS[cs].SMC_CYCLE =
		SMC_CYCLE_NWE_CYCLE(11) |
		SMC_CYCLE_NRD_CYCLE(14);

#ifdef SMC_TIMINGS_NFSEL
	SMC->SMC_CS[cs].SMC_TIMINGS = 0;
#endif

	SMC->SMC_CS[cs].SMC_MODE =
		SMC_MODE_READ_MODE |
		SMC_MODE_WRITE_MODE |
		(bus_width == 8 ? SMC_MODE_DBW_BIT_8 : SMC_MODE_DBW_BIT_16) |
		SMC_MODE_EXNW_MODE_DISABLED |
		SMC_MODE_TDF_CYCLES(1);
}

#ifdef CONFIG_HAVE_SMC_SCRAMBLING

void smc_scrambling_set_key(uint32_t key1, uint32_t key2)
{
	SMC->SMC_KEY1 = key1;
	SMC->SMC_KEY2 = key2;
}

void smc_scrambling_enable(void)
{
	SMC->SMC_OCMS |= SMC_OCMS_SMSE;
}

void smc_scrambling_disable(void)
{
	SMC->SMC_OCMS &= ~SMC_OCMS_SMSE;
}

bool smc_scrambling_is_enabled(void)
{
	return SMC->SMC_OCMS & SMC_OCMS_SMSE;
}

#endif /* CONFIG_HAVE_SMC_SCRAMBLING */
