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
#include "barriers.h"
#include "timer.h"
#include "trace.h"

#include "extram/mpddrc.h"
#include "peripherals/pmc.h"
#include "peripherals/sfrbu.h"

#include <assert.h>
#include <stdlib.h>

#ifndef MPDDRC_LPR_LPCB_DISABLED
#define MPDDRC_LPR_LPCB_DISABLED			(MPDDRC_LPR_LPCB_NOLOWPOWER)
#endif

static void _set_ddr_timings(struct _mpddrc_desc* desc)
{
#ifdef CONFIG_HAVE_MPDDRC_SDRAM_ONLY
	uint8_t trc_trfc, txsr;

	/* single register value for tRC and tRFC, use max */
	trc_trfc = desc->timings.trc;
	if (desc->timings.trfc > trc_trfc)
		trc_trfc = desc->timings.trfc;

	/* single register value for tXSRD and tXSNR */
	txsr = desc->timings.txsrd;
	if (desc->timings.txsnr > txsr)
		txsr = desc->timings.txsnr;

	uint32_t cr = MPDDRC->MPDDRC_CR;
	cr &= ~(MPDDRC_CR_TWR_Msk |
	        MPDDRC_CR_TRC_TRFC_Msk |
	        MPDDRC_CR_TRP_Msk |
	        MPDDRC_CR_TRCD_Msk |
	        MPDDRC_CR_TRAS_Msk |
	        MPDDRC_CR_TXSR_Msk);
	cr |= MPDDRC_CR_TWR(desc->timings.twr)
	    | MPDDRC_CR_TRC_TRFC(trc_trfc)
	    | MPDDRC_CR_TRP(desc->timings.trp)
	    | MPDDRC_CR_TRCD(desc->timings.trcd)
	    | MPDDRC_CR_TRAS(desc->timings.tras)
	    | MPDDRC_CR_TXSR(txsr);
	MPDDRC->MPDDRC_CR = cr;
#ifdef MPDDRC_CFR1_UNAL_SUPPORTED
	MPDDRC->MPDDRC_CFR1 |= MPDDRC_CFR1_UNAL_SUPPORTED;
#endif
#else /* !CONFIG_HAVE_MPDDRC_SDRAM_ONLY */
	MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TMRD(desc->timings.tmrd)
	                    | MPDDRC_TPR0_TWTR(desc->timings.twtr)
	                    | MPDDRC_TPR0_TRRD(desc->timings.trrd)
	                    | MPDDRC_TPR0_TRP(desc->timings.trp)
	                    | MPDDRC_TPR0_TRC(desc->timings.trc)
	                    | MPDDRC_TPR0_TWR(desc->timings.twr)
	                    | MPDDRC_TPR0_TRCD(desc->timings.trcd)
	                    | MPDDRC_TPR0_TRAS(desc->timings.tras);
	MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TXP(desc->timings.txp)
	                    | MPDDRC_TPR1_TXSRD(desc->timings.txsrd)
	                    | MPDDRC_TPR1_TXSNR(desc->timings.txsnr)
	                    | MPDDRC_TPR1_TRFC(desc->timings.trfc);

#ifdef CONFIG_HAVE_MPDDRC_SDRAM
	if (desc->type == MPDDRC_TYPE_SDRAM)
		return;
#endif
	MPDDRC->MPDDRC_TPR2 = MPDDRC_TPR2_TFAW(desc->timings.tfaw)
	                    | MPDDRC_TPR2_TRTP(desc->timings.trtp)
	                    | MPDDRC_TPR2_TRPA(desc->timings.trpa)
	                    | MPDDRC_TPR2_TXARDS(desc->timings.txards)
	                    | MPDDRC_TPR2_TXARD(desc->timings.txard);
#endif /* !CONFIG_HAVE_MPDDRC_SDRAM_ONLY */
}

/* Compute BA[] offset according to configuration */
static uint32_t _compute_ba_offset(void)
{
	uint8_t nc, nr;
	bool interleaved, dbw16;

#if defined CONFIG_HAVE_MPDDRC_SDRAM_ONLY
	nc = ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NC_Msk) >> MPDDRC_CR_NC_Pos) + 8;
	nr = ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NR_Msk) >> MPDDRC_CR_NR_Pos) + 11;
	interleaved = false;
	dbw16 = (MPDDRC->MPDDRC_CR & MPDDRC_CR_DBW) != 0;
#else
	nc = ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NC_Msk) >> MPDDRC_CR_NC_Pos) + 9;
	nr = ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NR_Msk) >> MPDDRC_CR_NR_Pos) + 11;
	interleaved = (MPDDRC->MPDDRC_CR & MPDDRC_CR_DECOD_INTERLEAVED) != 0;
	dbw16 = (MPDDRC->MPDDRC_MD & MPDDRC_MD_DBW) != 0;
#endif

	return nc + (interleaved ? 0 : nr) + (dbw16 ? 1 : 2);
}

static void _send_ddr_cmd(uint32_t cmd)
{
	MPDDRC->MPDDRC_MR = cmd & MPDDRC_MR_MODE_Msk;
	MPDDRC->MPDDRC_MR;
	dmb();

	/* Perform a write to DDR to acknowledge the command */
	*((uint32_t*)DDR_CS_ADDR) = 0;
}

static void _send_ext_lmr_cmd(uint32_t opcode, uint32_t ba_offset)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
	MPDDRC->MPDDRC_MR;
	dmb();

	/* Perform a write to DDR to acknowledge the command */
	*((uint32_t*)(DDR_CS_ADDR + (opcode << ba_offset))) = 0u;
}

#if defined(CONFIG_HAVE_MPDDRC_LPDDR2) || defined(CONFIG_HAVE_MPDDRC_LPDDR3)

static void _send_lpddr2_cmd(uint32_t mrs)
{
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(mrs);
	MPDDRC->MPDDRC_MR;
	dmb();

	/* Perform a write to DDR to acknowledge the command */
	*((uint32_t*)DDR_CS_ADDR) = 0;
}

#endif /* CONFIG_HAVE_MPDDRC_LPDDR2 || CONFIG_HAVE_MPDDRC_LPDDR3 */

#ifdef CONFIG_HAVE_MPDDRC_DDR3

/* Configure DDR3 */
static void _configure_ddr3(struct _mpddrc_desc* desc)
{
	uint32_t ba_offset = _compute_ba_offset();

	/* Timings */
	_set_ddr_timings(desc);

#ifdef CONFIG_HAVE_SFRBU
	/* Only initialize DDR chip when needed */
	if (sfrbu_is_ddr_backup_enabled())
		return;
#endif

	/* Step 3: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 4: Pause for at least 500μs. */
	usleep(500);

	/* Step 5: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 6: Issue Extended Mode Register Set 2 (EMRS2) cycle to choose
	 * between commercial or high temperature operations. */
	_send_ext_lmr_cmd(0x2, ba_offset);

	/* Step 7: Issue Extended Mode Register Set 3 (EMRS3) cycle to set the
	 * Extended Mode Register to 0. */
	_send_ext_lmr_cmd(0x3, ba_offset);

	/* Step 8: Issue Extended Mode Register Set 1 (EMRS1) cycle to disable
	 * and to program O.D.S. (Output Driver Strength). */
	_send_ext_lmr_cmd(0x1, ba_offset);

	/* Step 9: Write a one to the DLL bit (enable DLL reset) in the MPDDRC
	 * Configuration Register (MPDDRC_CR). */
	MPDDRC->MPDDRC_CR |= MPDDRC_CR_DLL_RESET_ENABLED;

	/* Step 10: Issue a Mode Register Set (MRS) cycle to reset DLL. */
	_send_ddr_cmd(MPDDRC_MR_MODE_LMR_CMD);

	/* Step 11: Issue a Calibration command (MRS) cycle to calibrate RTT
	 * and RON values for the Process Voltage Temperature (PVT). */
	_send_ddr_cmd(MPDDRC_MR_MODE_CALIB_CMD);

	/* Step 12: A Normal Mode command is provided.  Program the Normal mode
	 * in the MPDDRC_MR and perform a write access to any DDR3-SDRAM
	 * address to acknowledge this command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NORMAL_CMD);
}

#endif /* CONFIG_HAVE_MPDDRC_DDR3 */

#ifdef CONFIG_HAVE_MPDDRC_DDR2

/* Configure DDR2 */
static void _configure_ddr2(struct _mpddrc_desc* desc)
{
	uint32_t ba_offset = _compute_ba_offset();

	/* Timings */
	_set_ddr_timings(desc);

	/* Step 3: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 4: Pause for at least 200μs. */
	usleep(200);

	/* Step 5: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 6: Issue all banks precharge command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_PRCGALL_CMD);

	/* Step 7: Issue an Extended Mode Register Set (EMRS2) cycle to chose
	 * between commercial or high  temperature operations. */
	_send_ext_lmr_cmd(0x2, ba_offset);

	/* Step 8: Issue an Extended Mode Register Set (EMRS3) cycle to set all
	 * registers to 0. */
	_send_ext_lmr_cmd(0x3, ba_offset);

	/* Step 9: Issue an Extended Mode Register Set (EMRS1) cycle to enable
	 * DLL. */
	_send_ext_lmr_cmd(0x1, ba_offset);

	/* Step 10: An additional 200 cycles of clock are required for locking
	 * DLL (2μs should be enough). */
	usleep(2);

	/* Step 11: Program DLL field into the Configuration Register. */
	MPDDRC->MPDDRC_CR |= MPDDRC_CR_DLL_RESET_ENABLED;

	/* Step 12: A Mode Register set (MRS) cycle is issued to reset DLL. */
	_send_ddr_cmd(MPDDRC_MR_MODE_LMR_CMD);

	/* Step 13: Issue all banks precharge command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_PRCGALL_CMD);

	/* Step 14: Two auto-refresh (CBR) cycles are provided. Program the
	 * auto refresh command (CBR) into the Mode Register. */
	_send_ddr_cmd(MPDDRC_MR_MODE_RFSH_CMD);
	_send_ddr_cmd(MPDDRC_MR_MODE_RFSH_CMD);

	/* Step 15: Program DLL field into the Configuration Register to low
	 * (Disable DLL reset). */
	MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_DLL_RESET_ENABLED;

	/* Step 16: Issue a Mode Register Set (MRS) cycle to program the
	 * parameters device. */
	_send_ddr_cmd(MPDDRC_MR_MODE_LMR_CMD);

	/* Step 17: Program OCD field into the Configuration Register to high
	 * (OCD calibration default). */
	MPDDRC->MPDDRC_CR |= MPDDRC_CR_OCD_DDR2_DEFAULT_CALIB;

	/* Step 18: An Extended Mode Register Set (EMRS1) cycle is issued to
	 * OCD default value. */
	_send_ext_lmr_cmd(0x1, ba_offset);

	/* Step 19: Program OCD field into the Configuration Register to high
	 * (OCD calibration default). */
	MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_OCD_Msk;

	/* Step 20: An Extended Mode Register Set (EMRS1) cycle is issued to
	 * enable OCD exit. */
	_send_ext_lmr_cmd(0x1, ba_offset);

	/* Step 21: A mode Normal command is provided. Program the Normal mode
	 * into Mode Register. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NORMAL_CMD);
}

#endif /* CONFIG_HAVE_MPDDRC_DDR2 */

#if defined(CONFIG_HAVE_MPDDRC_LPDDR2) || defined(CONFIG_HAVE_MPDDRC_LPDDR3)

/* Configure LPDDR2 / LPDDR3 */
static void _configure_lpddr2(struct _mpddrc_desc* desc)
{
	/* Timings */
	_set_ddr_timings(desc);

	/* Step 3: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 4: Pause for at least 100ns (use 1μs instead). */
	usleep(1);

	/* Step 5: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 6: A pause of at least 200μs must be observed before issuing a
	 * Reset command. */
	usleep(200);

	/* Step 7. A Reset command is issued. */
	_send_lpddr2_cmd(0x3f);

	/* Step 8. A pause of at least tINIT5 must be observed before issuing
	 * any commands.*/
	usleep(500);

	/* Step 9. Issued a calibration command by issuing mode register write
	 * command */
	_send_lpddr2_cmd(0xa);

	/* Step 10: Perform a write access by issuing mode register write
	 * command */
	_send_lpddr2_cmd(0x1);

	/* Step 11: Program CAS Latency by issuing mode register write
	 * command. */
	_send_lpddr2_cmd(0x2);

	/* Step 12: Program Drive Strength and Slew Rate by issuing mode
	 * register write command. */
	_send_lpddr2_cmd(0x3);

	/* Step 13: Program Partial Array Self Refresh (PASR) by issuing mode
	 * register write command. */
	_send_lpddr2_cmd(0x10);

#ifdef CONFIG_SOC_SAMA5D2
	/* Step 14: In the DDR Configuration Register (SFR_DDRCFG), the
	 * application must write a 1 to fields 17 and 16 to open the input
	 * buffers (See section “Special Function Registers (SFR)”). */
	SFR->SFR_DDRCFG |= SFR_DDRCFG_FDQIEN | SFR_DDRCFG_FDQSIEN;
#endif

	/* Step 15: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 16: Read command cycle by issuing Mode register read
	 * command. */
	_send_lpddr2_cmd(0x5);

	/* Step 17: Read revision by issuing Mode register read command. */
	_send_lpddr2_cmd(0x6);

	/* Step 18: Read memory organization by issuing Mode register read
	 * command. */
	_send_lpddr2_cmd(0x8);

	/* Step 19: Read device information by issuing Mode register read
	 * command. */
	_send_lpddr2_cmd(0x0);

	/* Step 20: Issue a Normal mode command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NORMAL_CMD);

#ifdef CONFIG_SOC_SAMA5D2
	/* Step 21: In the DDR configuration Register (SFR_DDRCCFG), the
	 * application must write a 0 to fields 17 and 16 to close the input
	 * buffers. The buffers are then driven by the MPDDRC controller. */
	SFR->SFR_DDRCFG &= ~(SFR_DDRCFG_FDQIEN | SFR_DDRCFG_FDQSIEN);
#endif
}

#endif /* CONFIG_HAVE_MPDDRC_LPDDR2 */

#ifdef CONFIG_HAVE_MPDDRC_SDRAM

/* Configure SDRAM */
static void _configure_sdram(struct _mpddrc_desc* desc)
{
	uint32_t ba_offset = _compute_ba_offset();
	volatile uint32_t i;

	/* Timings */
	_set_ddr_timings(desc);

	/* Step 4: A pause of at least 200μs must be observed before issuing a
	 * Reset command. */
	usleep(200);

	/* Step 5: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 6: Issue all banks precharge command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_PRCGALL_CMD);

	/* Step 7: Issue auto-refresh (CBR) cycles command for eight times */
	for (i = 0; i < 8; i++)
		_send_ddr_cmd(MPDDRC_MR_MODE_RFSH_CMD);

	/* Step 8: Issue an Extended Mode Register Set (EMRS3) cycle to set all
	 * registers to 0. */
	_send_ddr_cmd(MPDDRC_MR_MODE_LMR_CMD);

	/* Step 9: For mobile SDRAM , Issue Extended Mode Register Set 2 (EMR)
		cycle to choose between commercial or high temperature operations.*/
#ifdef CONFIG_HAVE_MPDDRC_SDRAM_ONLY
	if (desc->mode & MPDDRC_MD_MD_LPSDRAM)
#else
	if (desc->mode & MPDDRC_MD_MD_LPSDR_SDRAM)
#endif
		_send_ext_lmr_cmd(0x1, ba_offset);

	/* Step 10: A mode Normal command is provided. Program the Normal mode
	 * into Mode Register. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NORMAL_CMD);
}

#endif /* CONFIG_HAVE_MPDDRC_SDRAM */

#ifdef CONFIG_HAVE_MPDDRC_LPDDR

/* Configure LPDDR */
static void _configure_lpddr(struct _mpddrc_desc *desc)
{
	uint32_t ba_offset = _compute_ba_offset();

	/* Timings */
	_set_ddr_timings(desc);

	/*
	 * Step 4: Program Temperature Compensated Self-refresh (TCR), Partial
	 * Array Self-refresh (PASR) and Drive Strength (DS) parameters in the
	 * Low-power register (MPDDRC_LPR).
	 */

	/* Assign one-quarter output buffer drive strength to external EMR.DS */
	uint32_t value = MPDDRC->MPDDRC_LPR & ~MPDDRC_LPR_DS_Msk;
	MPDDRC->MPDDRC_LPR = value | MPDDRC_LPR_DS(0x2);

	/* Step 5: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 6: Pause for at least 200μs. */
	usleep(200);

	/* Step 7: Issue a NOP command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NOP_CMD);

	/* Step 8: Issue a All Banks Precharge command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_PRCGALL_CMD);

	/* Step 9: Issue 2 autorefresh commands. */
	_send_ddr_cmd(MPDDRC_MR_MODE_RFSH_CMD);
	_send_ddr_cmd(MPDDRC_MR_MODE_RFSH_CMD);

	/*
	 * Step 10: An Extended Mode Register Set (EMRS) cycle is issued to
	 * program the low-power DDR1-SDRAM parameters (TCSR, PASR, DS).
	 * [...]
	 * The write address must be chosen so that signal BA[1] is set to 1
	 * and BA[0] is set to 0.
	 */
	_send_ext_lmr_cmd(0x2, ba_offset);

	/* Step 11: Issue a Mode Register Set command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_LMR_CMD);

	/* Step 12 Issue a Normal mode command. */
	_send_ddr_cmd(MPDDRC_MR_MODE_NORMAL_CMD);
}

#endif /* CONFIG_HAVE_MPDDRC_LPDDR */

extern void mpddrc_configure(struct _mpddrc_desc* desc)
{
#ifdef MPDDRC_HS_DIS_ANTICIP_READ
	/* Disable anticipated read */
	MPDDRC->MPDDRC_HS = MPDDRC_HS_DIS_ANTICIP_READ;
#endif

	/* controller and DDR clock */
#ifdef ID_MPDDRC
	pmc_configure_peripheral(ID_MPDDRC, NULL, true);
#endif
	pmc_enable_system_clock(PMC_SYSTEM_CLOCK_DDR);

	/* Step1: Program memory device type */
	MPDDRC->MPDDRC_MD = desc->mode;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	/* set driver impedance */
	uint32_t value = MPDDRC->MPDDRC_IO_CALIBR;
#ifdef MPDDRC_IO_CALIBR_RDIV_Msk
	value &= ~MPDDRC_IO_CALIBR_RDIV_Msk;
#endif
#ifdef MPDDRC_IO_CALIBR_CK_F_RANGE_Msk
	value &= ~MPDDRC_IO_CALIBR_CK_F_RANGE_Msk;
#endif
#ifdef MPDDRC_IO_CALIBR_EN_CALIB
	value &= ~MPDDRC_IO_CALIBR_EN_CALIB;
#endif
	value &= ~MPDDRC_IO_CALIBR_TZQIO_Msk;
	value &= ~MPDDRC_IO_CALIBR_CALCODEP_Msk;
	value &= ~MPDDRC_IO_CALIBR_CALCODEN_Msk;

	value |= desc->io_calibr;
	MPDDRC->MPDDRC_IO_CALIBR = value;
#endif

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	MPDDRC->MPDDRC_RD_DATA_PATH = desc->data_path;
#endif

	/* Step 2: Program features of the DDR3-SDRAM device in the
	 * configuration register and timing parameter registers (TPR0
	 * ans TPR1) */

	/* Configurations */
	MPDDRC->MPDDRC_CR = desc->control;

	uint32_t lpr_prv = MPDDRC->MPDDRC_LPR, lpr = lpr_prv;
#ifdef MPDDRC_LPR_APDE
	lpr = (lpr & ~MPDDRC_LPR_APDE) | MPDDRC_LPR_APDE_DDR2_FAST_EXIT;
#endif
#ifdef CONFIG_HAVE_SFRBU
	if (sfrbu_is_ddr_backup_enabled())
		/* The memory is in self-refresh mode; restore MPDDRC_LPR */
		lpr = (lpr & ~MPDDRC_LPR_LPCB_Msk) | MPDDRC_LPR_LPCB_SELFREFRESH;
#endif
	if (lpr != lpr_prv)
		MPDDRC->MPDDRC_LPR = lpr;

	switch(desc->type) {
#ifdef CONFIG_HAVE_MPDDRC_SDRAM
	case MPDDRC_TYPE_SDRAM:
		_configure_sdram(desc);
		break;
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR2
	case MPDDRC_TYPE_DDR2:
		_configure_ddr2(desc);
		break;
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR3
	case MPDDRC_TYPE_DDR3:
		_configure_ddr3(desc);
		break;
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR
	case MPDDRC_TYPE_LPDDR:
		_configure_lpddr(desc);
		break;
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR2
	case MPDDRC_TYPE_LPDDR2:
		_configure_lpddr2(desc);
		break;
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR3
	case MPDDRC_TYPE_LPDDR3:
		_configure_lpddr2(desc);
		break;
#endif
	default:
		trace_error("DDRAM type not handled\r\n");
		abort();
	}

	/* Last step: Write the refresh rate */
	/* Refresh Timer is (refresh_window / refresh_cycles) * master_clock */
	uint32_t master_clock = pmc_get_master_clock() / 1000;
	MPDDRC->MPDDRC_RTR = MPDDRC_RTR_COUNT(desc->refresh_window * master_clock / desc->refresh_cycles);

#ifdef CONFIG_HAVE_SFRBU
	if (sfrbu_is_ddr_backup_enabled()) {
		MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NORMAL_CMD;
		sfrbu_disable_ddr_backup();
		mpddrc_issue_low_power_command(MPDDRC_LPR_LPCB_DISABLED);
	}
#endif
}

RAMCODE void mpddrc_issue_low_power_command(uint32_t cmd)
{
	uint32_t value;
	value = MPDDRC->MPDDRC_LPR & ~MPDDRC_LPR_LPCB_Msk;
	MPDDRC->MPDDRC_LPR = value | (cmd & MPDDRC_LPR_LPCB_Msk);

#ifdef MPDDRC_LPR_SELF_DONE
	if (cmd == MPDDRC_LPR_LPCB_SELFREFRESH)
		/* Wait for the memory to enter self-refresh mode */
		while (!((MPDDRC->MPDDRC_LPR) & MPDDRC_LPR_SELF_DONE)) ;
#endif
}

RAMCODE void ddr_self_refresh(void)
{
	mpddrc_issue_low_power_command(MPDDRC_LPR_LPCB_SELFREFRESH);

#ifdef CONFIG_HAVE_SFRBU
	if (!sfrbu_is_ddr_backup_enabled()) {
		/* Disable the DDR Controller clock signal at PMC level*/
		pmc_disable_peripheral(ID_MPDDRC);
		/* Disable ddrclk */
		pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);

		sfrbu_enable_ddr_backup();
	}
#endif
}

RAMCODE void check_ddr_ready(void)
{
#ifdef CONFIG_HAVE_SFRBU
	if (sfrbu_is_ddr_backup_enabled()) {
		/* Enable the DDR Controller clock signal at PMC level */
		pmc_configure_peripheral(ID_MPDDRC, NULL, true);
		/* Enable ddrclk */
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_DDR);
		/* Disable DDR Backup mode */
		sfrbu_disable_ddr_backup();
	}
#endif

	mpddrc_issue_low_power_command(MPDDRC_LPR_LPCB_DISABLED);
}

RAMDATA struct pck_mck_cfg clock_setting_backup = {0};
#ifdef CONFIG_RAMCODE
RAMDATA volatile int _ddr_active_needed = 0;

RAMCODE void ddram_active(void) {
	/* Restore default PCK and MCK */
	while ((PMC->PMC_SR & PMC_SR_MCKRDY) == 0);
	pmc_set_custom_pck_mck(&clock_setting_backup);
	check_ddr_ready();
	_ddr_active_needed = 0;
}
#endif
