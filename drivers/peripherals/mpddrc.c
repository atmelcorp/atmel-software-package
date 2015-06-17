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

#include "peripherals/mpddrc.h"
#include "peripherals/pmc.h"

#include "trace.h"
#include "timer.h"
#include "compiler.h"

#include <stdlib.h>

static void _set_ddr3_timings(void)
{
	/*
	 * According to MT41K128M16 datasheet
	 * Maximum fresh period: 64ms, refresh count: 8k
	 */

	/* Assume timings for 8ns min clock period */
	MPDDRC->MPDDRC_TPR0 = (MPDDRC_TPR0_TRAS(6)
			| MPDDRC_TPR0_TRCD(3)
			| MPDDRC_TPR0_TWR(3)
			| MPDDRC_TPR0_TRC(9)
			| MPDDRC_TPR0_TRP(3)
			| MPDDRC_TPR0_TRRD(1)
			| MPDDRC_TPR0_TWTR(2)
			| MPDDRC_TPR0_TMRD(3));

	MPDDRC->MPDDRC_TPR1 = (MPDDRC_TPR1_TRFC(27)
			| MPDDRC_TPR1_TXSNR(29)
			| MPDDRC_TPR1_TXSRD(0)
			| MPDDRC_TPR1_TXP(3));

	MPDDRC->MPDDRC_TPR2 = (MPDDRC_TPR2_TXARD(8)
			| MPDDRC_TPR2_TXARDS(2)
			| MPDDRC_TPR2_TRPA(3)
			| MPDDRC_TPR2_TRTP(2)
			| MPDDRC_TPR2_TFAW(7));
}

static uint32_t _compute_ba_offset(void)
{
	/* Compute BA[] offset according to CR configuration */
	uint32_t offset = (MPDDRC->MPDDRC_CR & MPDDRC_CR_NC_Msk) + 9;
	if (!(MPDDRC->MPDDRC_CR & MPDDRC_CR_DECOD_INTERLEAVED))
		offset += ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NR_Msk) >> 2) + 11;

	offset += (MPDDRC->MPDDRC_MD & MPDDRC_MD_DBW) ? 1 : 2;

	return offset;
}

/**
 * \brief Send a NOP command
 */
static void _send_nop_cmd(void)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
	/* Perform a write to a DDR memory access to acknoledge the command */
	*((uint32_t *)DDR_CS_ADDR) = 0;
}

static void _send_lmr_cmd(uint32_t opcode, uint32_t ba_offset)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LMR_CMD;

	/* Perform a write to a DDR memory access to acknoledge the command */
	*((uint32_t *)(DDR_CS_ADDR + (opcode << ba_offset))) = 0u;
}

static void _send_ext_lmr_cmd(uint32_t opcode, uint32_t ba_offset)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;

	/* Perform a write to a DDR memory access to acknoledge the command */
	*((uint32_t *)(DDR_CS_ADDR + (opcode << ba_offset))) = 0u;
}

static void _send_normal_cmd(void)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NORMAL_CMD;
	/* Perform a write to a DDR memory access to acknoledge the command */
	*((uint32_t *)DDR_CS_ADDR) = 0;
}

#ifdef CONFIG_HAVE_DDR3

static void _send_calib_cmd(void)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_DEEP_CALIB_MD;
	/* Perform a write to a DDR memory access to acknoledge the command */
	*((uint32_t *)DDR_CS_ADDR) = 0;
}

static void _configure_ddr3(void)
{
	pmc_enable_peripheral(ID_MPDDRC);
	pmc_enable_ddr_clock();

	/* Configure time to have microseconds resolution */
	timer_configure(1000);
	/* Step1: Program memory device type */
	MPDDRC->MPDDRC_MD = MPDDRC_MD_MD_DDR3_SDRAM;

	/* set driver impedance */
	uint32_t value = MPDDRC->MPDDRC_IO_CALIBR;
	value &= ~MPDDRC_IO_CALIBR_RDIV_Msk;
	value |= MPDDRC_IO_CALIBR_RDIV_RZQ_60_RZQ_57_RZQ_55_RZQ_52;
	MPDDRC->MPDDRC_IO_CALIBR = value;

	MPDDRC->MPDDRC_RD_DATA_PATH =
		MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES;

	/* Step 2: Program features of the DDR3-SDRAM device in the
	 * configuration register and timing parameter registers (TPR0
	 * ans TPR1) */

	/* Configurations */
	MPDDRC->MPDDRC_CR = (MPDDRC_CR_NC_DDR10_MDDR9_COL_BITS
			     | MPDDRC_CR_NR_14_ROW_BITS
			     | MPDDRC_CR_CAS_DDR_CAS5
			     | MPDDRC_CR_DIS_DLL
			     | MPDDRC_CR_NB_8_BANKS
			     | MPDDRC_CR_DECOD_INTERLEAVED
			     | MPDDRC_CR_UNAL_SUPPORTED);

	/* Timings */
	_set_ddr3_timings();
	uint32_t ba_offset = _compute_ba_offset();

	/*
	 * Step 3: Issue a NOP command to the memory controller using
	 * its mode register (MPDDRC_MR).
	 */
	_send_nop_cmd();

	/*
	 * Step 4: A pause of at least 500us must be observed before a single toggle.
	 */
	timer_wait(500);
	/*
	 * Step 5: Issue a NOP command to the memory controller using
	 * its mode register (MPDDRC_MR). CKE is now driven high.
	 */
	_send_nop_cmd();
	timer_wait(10);
	/*
	 * Step 6: Issue Extended Mode Register Set 2 (EMRS2) cycle to
	 * choose between commercial or high temperature
	 * operations.
	 */
	_send_ext_lmr_cmd(0x2, ba_offset);
	timer_wait(10);
	/*
	 * Step 7: Issue Extended Mode Register Set 3 (EMRS3) cycle to set
	 * the Extended Mode Register to 0.
	 */
	_send_ext_lmr_cmd(0x3, ba_offset);
	timer_wait(10);
	/*
	 * Step 8: Issue Extended Mode Register Set 1 (EMRS1) cycle to
	 * disable and to program O.D.S. (Output Driver Strength).
	 */
	_send_ext_lmr_cmd(0x1, ba_offset);
	timer_wait(10);
	/*
	 * Step 9: Write a one to the DLL bit (enable DLL reset) in the MPDDRC
	 * Configuration Register (MPDDRC_CR)
	 */
	/* Not done here */

	/*
	 * Step 10: Issue a Mode Register Set (MRS) cycle to reset DLL.
	 */
	_send_lmr_cmd(0x0, ba_offset);
	timer_wait(50);
	/*
	 * Step 11: Issue a Calibration command (MRS) cycle to calibrate RTT and
	 * RON values for the Process Voltage Temperature (PVT).
	 * The application must write a six to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0.
	 */
	_send_calib_cmd();
	timer_wait(10);

	/*
	 * Step 12: A Normal Mode command is provided.
	 * Program the Normal mode in the MPDDRC_MR and perform a write access
	 * to any DDR3-SDRAM address to acknowledge this command.
	 */
	_send_normal_cmd();
	/*
	 * Step 13: Perform a write access to any DDR3-SDRAM address.
	 */
	*((uint32_t *)(DDR_CS_ADDR)) = 0;

	/*
	 * Step 14: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 * refresh rate = delay between refresh cycles.
	 * The DDR3-SDRAM device requires a refresh every 7.81 us.
	 */
	/* Refresh Timer is (64ms / 8k) * master_clock */
	uint32_t master_clock = pmc_get_master_clock()/1000000;
	MPDDRC->MPDDRC_RTR = 64000*master_clock/8192;
	/* this value should be 0x511 with master_clock = 166 MHz */
}

#endif

#ifdef CONFIG_HAVE_DDR2
static void _configure_ddr2(void)
{
}
#endif

extern void mpddrc_configure(enum _ram_type ram)
{
#if defined(CONFIG_HAVE_DDR3)
		_configure_ddr3();
#elif defined(CONFIG_HAVE_DDR2)
		_configure_ddr2();
#else
#error "Memory type not supported!"
#endif
}
