/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology
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

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "barriers.h"
#include "timer.h"
#include "trace.h"

#include "extram/sdram.h"
#include "peripherals/pmc.h"

#include <string.h>

/*------------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

/*---------------------------------------------------------------------------
 *      Local functions
 *---------------------------------------------------------------------------*/

static uint32_t _compute_ba_offset(const struct _sdramc_desc *desc)
{
	return desc->nb_rows + desc->nb_columns +
		(desc->data_bus_width == 16 ? 1 : 2);
}

static void _send_sdram_cmd(uint32_t cmd)
{
	SDRAMC->SDRAMC_MR = cmd & SDRAMC_MR_MODE_Msk;
	SDRAMC->SDRAMC_MR;
	dmb();

	/* Perform a write to SDRAM to acknowledge the command */
	*((uint32_t *)DDR_CS_ADDR) = 0;
}

static void _send_ext_lmr_cmd(uint32_t opcode, uint32_t ba_offset)
{
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_EXT_LOAD_MODEREG;
	SDRAMC->SDRAMC_MR;
	dmb();

	/* Perform a write to the SDRAM to acknowledge the command */
	*((uint32_t *)(DDR_CS_ADDR + (opcode << ba_offset))) = 0u;
}

/*------------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

void sdramc_configure(const struct _sdramc_desc *desc)
{
	uint32_t master_clock_khz = pmc_get_master_clock() / 1000;
	uint32_t ba_offset = _compute_ba_offset(desc);
	uint8_t trc_trfc = MAX(desc->timings.trc, desc->timings.trfc);
	uint32_t cr, cfr1, mdr;
	int i;

	/* Enable the controller clock */
#ifdef ID_SDRAMC
	pmc_configure_peripheral(ID_SDRAMC, NULL, true);
#endif
	pmc_enable_system_clock(PMC_SYSTEM_CLOCK_DDR);

	/*
	 * Step 1: Set the SDRAM features in tht SDRAMC_CR: asynchronous
	 * timings (TRC, TRAS, etc.), number of columns, number of rows, CAS
	 * latency and data bus width. Set UNAL bit in SDRAMC_CFR1.
	 */
	cr = SDRAMC_CR_TWR(desc->timings.twr) |
	     SDRAMC_CR_TRC_TRFC(trc_trfc) |
	     SDRAMC_CR_TRP(desc->timings.trp) |
	     SDRAMC_CR_TRCD(desc->timings.trcd) |
	     SDRAMC_CR_TRAS(desc->timings.tras) |
	     SDRAMC_CR_TXSR(desc->timings.txsr);

	switch (desc->nb_columns) {
	case 8:
		cr |= SDRAMC_CR_NC_COL8;
		break;
	case 9:
		cr |= SDRAMC_CR_NC_COL9;
		break;
	case 10:
		cr |= SDRAMC_CR_NC_COL10;
		break;
	case 11:
		cr |= SDRAMC_CR_NC_COL11;
		break;
	default:
		trace_fatal("Unsupported number of columns\r\n");
		break;
	}

	switch (desc->nb_rows) {
	case 11:
		cr |= SDRAMC_CR_NR_ROW11;
		break;
	case 12:
		cr |= SDRAMC_CR_NR_ROW12;
		break;
	case 13:
		cr |= SDRAMC_CR_NR_ROW13;
		break;
	default:
		trace_fatal("Unsupported number of rows\r\n");
		break;
	}

	switch (desc->nb_banks) {
	case 2:
		cr |= SDRAMC_CR_NB_BANK2;
		break;
	case 4:
		cr |= SDRAMC_CR_NB_BANK4;
		break;
	default:
		trace_fatal("Unsupported number of banks\r\n");
		break;
	}

	switch (desc->cas_latency) {
	case 2:
		cr |= SDRAMC_CR_CAS_LATENCY2;
		break;
	case 3:
		cr |= SDRAMC_CR_CAS_LATENCY3;
		break;
	default:
		trace_fatal("Unsupported CAS latency\r\n");
		break;
	}

	switch (desc->data_bus_width) {
	case 16:
		cr |= SDRAMC_CR_DBW;
		break;
	case 32:
		break;
	default:
		trace_fatal("Unsupported data width\r\n");
		break;
	}

	SDRAMC->SDRAMC_CR = cr;

	cfr1 = SDRAMC_CFR1_TMRD(desc->timings.tmrd) |
	       SDRAMC_CFR1_UNAL;
	SDRAMC->SDRAMC_CFR1 = cfr1;

	/*
	 * Step 2: For mobile SDRAM, configure temperature-compensated
	 * self-refresh (TCSR), drive strength (DS) and partial array
	 * self-refresh (PASR) in the Low Power register (SDRAMC_LPR).
	 */
	if (desc->is_lpsdr) {
		SDRAMC->SDRAMC_LPR = SDRAMC_LPR_LPCB_SELF_REFRESH |
		                     SDRAMC_LPR_PASR(0) | /* Full array */
		                     SDRAMC_LPR_TCSR(0) |
		                     SDRAMC_LPR_DS(2) | /* Quarter */
		                     SDRAMC_LPR_TIMEOUT_LP_LAST_XFER_128;
	}

	/*
	 * Step 3: Select the SDRAM memory device type and the shift sampling
	 * value int he Memory Device register (SDRAMC_MDR).
	 */
	mdr = desc->is_lpsdr ? SDRAMC_MDR_MD_LPSDRAM : SDRAMC_MDR_MD_SDRAM;
	switch (desc->shift_sampling) {
	case 1:
	case 2:
	case 3:
		mdr |= SDRAMC_MDR_SHIFT_SAMPLING(desc->shift_sampling);
		break;
	default:
		trace_fatal("Unsupported shift sampling\r\n");
		break;
	}

	SDRAMC->SDRAMC_MDR = mdr;

	/*
	 * Step 4: A pause of at least 200 us must be observed before a signal
	 * toggle.
	 */
	usleep(200);

	/* Step 5: A NOP command is issued to the SDRAM devices. */
	_send_sdram_cmd(SDRAMC_MR_MODE_NOP);

	/* Step 6: An All Banks Precharge command is issued to the SDRAM. */
	_send_sdram_cmd(SDRAMC_MR_MODE_ALLBANKS_PRECHARGE);

	/* Step 7: Eight autorefresh (CBR) cycles are provided. */
	for (i = 0; i < 8; i++)
		_send_sdram_cmd(SDRAMC_MR_MODE_AUTO_REFRESH);

	/*
	 * Step 8: A Mode Register set (MRS) cycle is issued to program the
	 * parameters of the SDRAM, in particular CAS latency and burst length.
	 * The application must write a 3 to the MODE field in the SDRAMC_MR.
	 * Read the SDRAMC_MR and add a memory barrier assembler instruction
	 * just after the read. Perform a write access to the SDRAM. The write
	 * address must be chosen so that BA[1:0] are set to 0.
	 */
	_send_sdram_cmd(SDRAMC_MR_MODE_LOAD_MODEREG);

	/*
	 * Step 9: For mobile SDRAM initialization, an Extended Mode Register
	 * set (EMRS) cycle is issued to program the SDRAM parametres (TCSR,
	 * PASR, DS). The application must set the MODE field to 5 in the
	 * SDRAMC_MR. Read the SDRAMC_MR and add a memory barrier assembler
	 * instruction just after the read. Perform a write access to the SDRAM.
	 * The write address must be chosen so that BA[1] or BA[0] are set to 1.
	 */
	if (desc->is_lpsdr)
		_send_ext_lmr_cmd(2, ba_offset);

	/* Step 10: The application must go into Normal mode. */
	_send_sdram_cmd(SDRAMC_MR_MODE_NORMAL);

	/*
	 * Step 11: Write the refresh rate into the COUNT field in the Refresh
	 * Timer register (SDRAMC_TR). (Refresh rate = delay between refresh
	 * cycles.)
	 * Refresh Timer is (refresh window / refresh_cycles) * master_clock_khz
	 */
	SDRAMC->SDRAMC_TR = SDRAMC_TR_COUNT(desc->refresh_window * master_clock_khz / desc->refresh_cycles);
}
