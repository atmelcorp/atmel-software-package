/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2007, Stelian Pop <stelian.pop@leadtechdesign.com>
 * Copyright (c) 2007 Lead Tech Design <www.leadtechdesign.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
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
 */
#include "hardware.h"
#include "arch/at91_ddrsdrc.h"
#include "debug.h"
#include "ddramc.h"
#include "timer.h"

/* write DDRC register */
static void write_ddramc(unsigned int address,
			unsigned int offset,
			const unsigned int value)
{
	writel(value, (address + offset));
}

/* read DDRC registers */
static unsigned int read_ddramc(unsigned int address, unsigned int offset)
{
	return readl(address + offset);
}

#ifdef CONFIG_DDR2
static int ddramc_decodtype_is_seq(unsigned int ddramc_cr)
{
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) \
	|| defined(SAMA5D4)
	if (ddramc_cr & AT91C_DDRC2_DECOD_INTERLEAVED)
		return 0;
#endif
	return 1;
}

int ddram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config)
{
	unsigned int ba_offset;
	unsigned int cr = 0;

	/* compute BA[] offset according to CR configuration */
	ba_offset = (ddramc_config->cr & AT91C_DDRC2_NC) + 9;
	if (ddramc_decodtype_is_seq(ddramc_config->cr))
		ba_offset += ((ddramc_config->cr & AT91C_DDRC2_NR) >> 2) + 11;

	ba_offset += (ddramc_config->mdr & AT91C_DDRC2_DBW) ? 1 : 2;

	dbg_very_loud(" ba_offset = %x ...\n", ba_offset);

	/*
	 * Step 1: Program the memory device type into the Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the feature of DDR2-SDRAM device into
	 * the Timing Register, and into the Configuration Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: An NOP command is issued to the DDR2-SDRAM
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	/* Now, clocks which drive the DDR2-SDRAM device are enabled */

	/* A minimum pause wait 200 us is provided to precede any signal toggle.
	(6 core cycles per iteration, core is at 396MHz: min 13340 loops) */
	udelay(200);

	/*
	 * Step 4:  An NOP command is issued to the DDR2-SDRAM
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	/* Now, CKE is driven high */
	/* wait 400 ns min */
	udelay(1);

	/*
	 * Step 5: An all banks precharge command is issued to the DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 6: An Extended Mode Register set(EMRS2) cycle is issued to chose between commercial or high
	 * temperature operations.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x2 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 7: An Extended Mode Register set(EMRS3) cycle is issued
	 * to set the Extended Mode Register to "0".
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x3 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 8: An Extened Mode Register set(EMRS1) cycle is issued to enable DLL,
	 * and to program D.I.C(Output Driver Impedance Control)
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* An additional 200 cycles of clock are required for locking DLL */
	udelay(1);

	/*
	 * Step 9: Program DLL field into the Configuration Register to high(Enable DLL reset)
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_DLL_RESET_ENABLED);

	/*
	 * Step 10: A Mode Register set(MRS) cycle is issied to reset DLL.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1:0] bits are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned int *)(ram_address + (0x0 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 11: An all banks precharge command is issued to the DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait 400 ns min (not needed on certain DDR2 devices) */
	udelay(1);

	/*
	 * Step 12: Two auto-refresh (CBR) cycles are provided.
	 * Program the auto refresh command (CBR) into the Mode Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait TRFC cycles min (135 ns min) extended to 400 ns */
	udelay(1);

	/* Set 2nd CBR */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait TRFC cycles min (135 ns min) extended to 400 ns */
	udelay(1);

	/*
	 * Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr & (~AT91C_DDRC2_DLL_RESET_ENABLED));

	/*
	 * Step 14: A Mode Register set (MRS) cycle is issued to program
	 * the parameters of the DDR2-SDRAM devices, in particular CAS latency,
	 * burst length and to disable DDL reset.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1:0] bits are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned int *)(ram_address + (0x0 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 15: Program OCD field into the Configuration Register
	 * to high (OCD calibration default).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_OCD_DEFAULT);

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 17: Program OCD field into the Configuration Register
	 * to low (OCD calibration mode exit).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr & (~AT91C_DDRC2_OCD_DEFAULT));

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 19: A Nornal mode command is provided.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/*
	 * Step 20: Perform a write access to any DDR2-SDRAM address
	 */
	*(((unsigned volatile int *)ram_address)) = 0;

	/*
	 * Step 21: Write the refresh rate into the count field in the Refresh Timer register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Now we are ready to work on the DDRSDR
	 *  wait for end of calibration
	 */
	udelay(10);

	return 0;
}

#elif defined(CONFIG_LPDDR2)

int lpddr2_sdram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config)
{
	unsigned int cr;

	write_ddramc(base_address, MPDDRC_LPDDR2_LPR,
				ddramc_config->lpddr2_lpr);

	/*
	 * Step 1: Program the memory device type into
	 * the Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the feature of Low-power DDR2-SDRAM device into
	 * the Timing Register, and into the Configuration Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: An NOP command is issued to the Low-power DDR2-SDRAM
	 * Program the NOP command into the Mode Register, the application must
	 * set the MODE field to 1 in the Mode Register. Perform a write access
	 * to any Low-power DDR2-SDRAM address to acknowledge this command.
	 * Now, clocks which drive Low-power DDR2-SDRAM device is enabled.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * A minimum pause of 100 ns must be reserved
	 * to precede any single toggle
	 */
	udelay(1);

	/*
	 * Step 4:  An NOP command is issued to the Low-power DDR2-SDRAM.
	 * Now, CKE is drive high.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/* A minimum pause of 200us must be satisfied before Reset Command*/
	udelay(200);

	/*
	 * Step 5: A reset command is issued to the Low-power DDR2-SDRAM.
	 * Now, the reset command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(63) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/* A minimum pause of 1 us must be satisfied befor any commands */
	udelay(1);

	/*
	 * Step 6: A Mode Register Read command is issued to the Low-power
	 * DDR2-SDRAM. Now, the Mode Register Read command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(0) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/* A minimum pause of 10 us must be satified before any commands */
	udelay(10);

	/*
	 * Step 7: a calibration command is issued to the Low-power DDR2-SDRAM.
	 * Now, the ZQ Calibration command is issued.
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	cr &= ~AT91C_DDRC2_ZQ;
	cr |= AT91C_DDRC2_ZQ_RESET;
	write_ddramc(base_address, HDDRSDRC2_CR, cr);

	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(10) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	cr &= ~AT91C_DDRC2_ZQ;
	cr |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, cr);

	/*
	 * Step 8: A Mode Register Write command is issued to the Low-power
	 * DDR2-SDRAM. Now, the Mode Register Write command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(1) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	/*
	 * Step 9: A Mode Register Write command is issued to the Low-power
	 * DDR2-SDRAM. Now, the Mode Register Write command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(2) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	/*
	 * Step 10: A Mode Register Write command is issued to the Low-power
	 * DDR2-SDRAM. Now, the Mode Register Write command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(3) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	/*
	 * Step 11: A Mode Register Write command is issued to the Low-power
	 * DDR2-SDRAM. Now, the Mode Register Write command is issued.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
			AT91C_DDRC2_MRS(16) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	/*
	 * Step 12: Write the refresh rate into the COUNT field in
	 * the Refresh Timer register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	udelay(1);

	/* Launch short ZQ calibration */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	cr &= ~AT91C_DDRC2_ZQ;
	cr |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, cr);
	*((unsigned volatile int *)ram_address) = 0;

	write_ddramc(base_address, MPDDRC_LPDDR2_TIM_CAL,
						ddramc_config->tim_calr);

	return 0;
}

#elif defined(CONFIG_DDR3)

int ddr3_sdram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config)
{
	unsigned int ba_offset;
	unsigned int cr = 0;

	/* Compute BA[] offset according to CR configuration */
	ba_offset = (ddramc_config->cr & AT91C_DDRC2_NC) + 9;
	if (!(ddramc_config->cr & AT91C_DDRC2_DECOD_INTERLEAVED))
		ba_offset += ((ddramc_config->cr & AT91C_DDRC2_NR) >> 2) + 11;

	ba_offset += (ddramc_config->mdr & AT91C_DDRC2_DBW) ? 1 : 2;

	dbg_very_loud(" ba_offset = %x ...\n", ba_offset);

	/*
	 * Step 1: Program the memory device type in the MPDDRC Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program features of the DDR3-SDRAM device in the MPDDRC
	 * Configuration Register and in the MPDDRC Timing Parameter 0 Register
	 * /MPDDRC Timing Parameter 1 Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	write_ddramc(base_address, MPDDRC_LPDDR2_TIM_CAL,
						ddramc_config->tim_calr);

	/*
	 * Step 3: A NOP command is issued to the DDR3-SRAM.
	 * Program the NOP command in the MPDDRC Mode Register (MPDDRC_MR).
	 * The application must write a one to the MODE field in the MPDDRC_MR
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * The clock which drive the DDR3-SDRAM device are now enabled.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 4: A pause of at least 500us must be observed before a single toggle.
	 */
	 udelay(500);

	/* Mandatory wait for DLL MASTER lock */
	while ((read_ddramc(base_address, MPDDRC_DLL_SM0) & AT91C_MPDDRC_MDLVAL) == 0)

	/*
	 * Step 5: A NOP command is issued to the DDR3-SDRAM
	 * Program the NOP command in the MPDDRC_MR.
	 * The application must write a one to the MODE field in the MPDDRC_MR.
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * CKE is now driven high.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	udelay(1);

	/*
	 * Step 6: An Extended Mode Register Set (EMRS2) cycle is issued to choose
	 * between commercial or high temperature operations. The application must
	 * write a five to the MODE field in the MPDDRC_MR and perform a write
	 * access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2] is set to 0,
	 * BA[1] is set to 1 and signal BA[0] is set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x2 << ba_offset))) = 0;

	/*
	 * Step 7: An Extended Mode Register Set (EMRS3) cycle is issued to set
	 * the Extended Mode Register to 0. The application must write a five
	 * to the MODE field in the MPDDRC_MR and perform a write access to the
	 * DDR3-SDRAM to acknowledge this command. The write address must be
	 * chosen so that signal BA[2] is set to 0, BA[1] is set to 1 and signal
	 * BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x3 << ba_offset))) = 0;

	/*
	 * Step 8: An Extended Mode Register Set (EMRS1) cycle is issued to
	 * disable and to program O.D.S. (Output Driver Strength).
	 * The application must write a five to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2:1] is set to 0
	 * and signal BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned int *)(ram_address + (0x1 << ba_offset))) = 0;

	/*
	 * Step 9: Write a one to the DLL bit (enable DLL reset) in the MPDDRC
	 * Configuration Register (MPDDRC_CR)
	 */
	//cr = read_ddramc(base_address, HDDRSDRC2_CR);
	//write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_DLL_RESET_ENABLED);

	/*
	 * Step 10: A Mode Register Set (MRS) cycle is issued to reset DLL.
	 * The application must write a three to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned int *)ram_address) = 0;

	/*
	 * Step 11: A Calibration command (MRS) is issued to calibrate RTT and
	 * RON values for the Process Voltage Temperature (PVT).
	 * The application must write a six to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_DEEP_CMD);
	*((unsigned int *)ram_address) = 0;

	udelay(50);

	/*
	 * Step 12: A Normal Mode command is provided.
	 * Program the Normal mode in the MPDDRC_MR and perform a write access
	 * to any DDR3-SDRAM address to acknowledge this command.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned int *)ram_address) = 0;

	/* Set all Bank Precharge to have DDR ready for normal operation */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*((unsigned int *)ram_address) = 0;

	udelay(10);

	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned int *)ram_address) = 0;
	/*
	 * Step 13: Perform a write access to any DDR3-SDRAM address.
	 */
	*((unsigned int *)ram_address) = 0;

	/* Allow to do calibration of DLL */
	*((unsigned int *)(ram_address + (0x2 << ba_offset))) = 0x0000ffff;
	*((unsigned int *)(ram_address + (0x2 << ba_offset) + 4)) = 0xaa5555aa;

	/*
	 * Step 14: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 * refresh rate = delay between refresh cycles.
	 * The DDR3-SDRAM device requires a refresh every 7.81 us.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/* Launch short ZQ calibration */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	cr &= ~AT91C_DDRC2_ZQ;
	cr |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, cr);
	*((unsigned volatile int *)ram_address) = 0;

	udelay(50);

	if ((read_ddramc(base_address, MPDDRC_DLL_SSL0) & AT91_MPDDRC_SDCNT) == 0)
		dbg_info("ERROR: %d\n", read_ddramc(base_address, MPDDRC_DLL_SSL0));

	return 0;
}

#else
#error "No right DDR-SDRAM device driver provided!"
#endif /* #ifndef CONFIG_PDDR2 */

void ddramc_print_config_regs(unsigned int base_address)
{
	dbg_very_loud("\n\nMPDDR Controller Registers configurations:\n");
	dbg_very_loud("MPDDRC_MDR: %d\n",
				read_ddramc(base_address, HDDRSDRC2_MDR));
	dbg_very_loud("MPDDRC_READ_DATA_PATH: %d\n",
				read_ddramc(base_address, MPDDRC_RD_DATA_PATH));
	dbg_very_loud("MPDDRC_IO_CALIBR: %d\n",
				read_ddramc(base_address, MPDDRC_IO_CALIBR));
	dbg_very_loud("MPDDRC_TPR0: %d\n",
				read_ddramc(base_address, HDDRSDRC2_T0PR));
	dbg_very_loud("MPDDRC_TPR1: %d\n",
				read_ddramc(base_address, HDDRSDRC2_T1PR));
	dbg_very_loud("MPDDRC_TPR2: %d\n",
				read_ddramc(base_address, HDDRSDRC2_T2PR));
	dbg_very_loud("MPDDRC_RTR: %d\n",
				read_ddramc(base_address, HDDRSDRC2_RTR));
	dbg_very_loud("MPDDRC_CR: %d\n",
				read_ddramc(base_address, HDDRSDRC2_CR));
}