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
 * Implementation of memories configuration on board.
 *
 */


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal ROM or the EBI CS0.
 */
void board_remap_rom(void)
{
    AXIMX->AXIMX_REMAP = 0;
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal RAM.
 */

void board_remap_ram(void)
{
	volatile uint32_t i;
    AXIMX->AXIMX_REMAP = AXIMX_REMAP_REMAP0;
	for(i=1000;--i;);
}

/**
 * \brief Initialize Vdd EBI drive
 * \param 0: 1.8V 1: 3.3V
 */
void board_cfg_vdd_mem_sel(uint8_t VddMemSel)
{
}

#if 0
static void matrix_configure_slave_ddr(void)
{
     /* Disable write protection */
	MATRIX0->MATRIX_WPMR = MPDDRC_WPMR_WPKEY_PASSWD;
 
	/* Partition external DDR */
	/* DDR port 0 not used from NWd */

	MATRIX0->MATRIX_SSR3   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR3 = 0x00000005;
	MATRIX0->MATRIX_SASSR3 = 0x00005555;
	MATRIX0->MATRIX_SSR4   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR4 = 0x00000005;
	MATRIX0->MATRIX_SASSR4 = 0x00005555;
	MATRIX0->MATRIX_SSR5   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR5 = 0x00000005;
	MATRIX0->MATRIX_SASSR5 = 0x00005555;
	MATRIX0->MATRIX_SSR6   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR6 = 0x00000005;
	MATRIX0->MATRIX_SASSR6 = 0x00005555;
	MATRIX0->MATRIX_SSR7   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR7 = 0x00000005;
	MATRIX0->MATRIX_SASSR7 = 0x00005555;
	MATRIX0->MATRIX_SSR8   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR8 = 0x00000005;
	MATRIX0->MATRIX_SASSR8 = 0x00005555;
	MATRIX0->MATRIX_SSR9   = 0x0F0F0F;
	MATRIX0->MATRIX_SRTSR9 = 0x00000005;
	MATRIX0->MATRIX_SASSR9 = 0x00005555;

}

static void matrix_configure_slave_nand(void)
{
}
#endif

/**
 * \brief Configures DDR3
 */
void board_cfg_ddram(void)
{
	uint32_t ba_offset;
	volatile uint32_t i;
	volatile uint32_t reg ;
	
	matrix_configure_slave_ddr();
	/* Enable DDR2 clock x2 in PMC */
	pmc_enable_peripheral(ID_MPDDRC);
	PMC->PMC_SCER  |= PMC_SCER_DDRCK;

	reg = MPDDRC->MPDDRC_IO_CALIBR;
	reg &= ~MPDDRC_IO_CALIBR_RDIV_Msk;
	reg |= MPDDRC_IO_CALIBR_RDIV_RZQ_60_RZQ_57_RZQ_55_RZQ_52;
	MPDDRC->MPDDRC_IO_CALIBR = reg;
	MPDDRC->MPDDRC_RD_DATA_PATH = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES;

	/*
	 * Step 1: Program the memory device type in the MPDDRC Memory Device Register
	 */
	MPDDRC->MPDDRC_MD = (MPDDRC_MD_DBW_DBW_32_BITS | MPDDRC_MD_MD_DDR3_SDRAM);
	/*
	 * Step 2: Program features of the DDR3-SDRAM device in the MPDDRC
	 * Configuration Register and in the MPDDRC Timing Parameter 0 Register
	 * /MPDDRC Timing Parameter 1 Register
	 */
	MPDDRC->MPDDRC_CR = (MPDDRC_CR_NC_DDR10_MDDR9_COL_BITS
				| MPDDRC_CR_NR_14_ROW_BITS
				| MPDDRC_CR_CAS_DDR_CAS5
				| MPDDRC_CR_DIS_DLL
				| MPDDRC_CR_NB_8_BANKS
				| MPDDRC_CR_DECOD_INTERLEAVED
				| MPDDRC_CR_UNAL_SUPPORTED);

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
		
	/* Compute BA[] offset according to CR configuration */
	ba_offset = (MPDDRC->MPDDRC_CR & MPDDRC_CR_NC_Msk) + 9;
	if (!(MPDDRC->MPDDRC_CR & MPDDRC_CR_DECOD_INTERLEAVED))
		ba_offset += ((MPDDRC->MPDDRC_CR & MPDDRC_CR_NR_Msk) >> 2) + 11;

	ba_offset += (MPDDRC->MPDDRC_MD & MPDDRC_MD_DBW) ? 1 : 2;

	/*
	 * Step 3: A NOP command is issued to the DDR3-SRAM.
	 * Program the NOP command in the MPDDRC Mode Register (MPDDRC_MR).
	 * The application must write a one to the MODE field in the MPDDRC_MR
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * The clock which drive the DDR3-SDRAM device are now enabled.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
	*((uint32_t *)DDR_CS_ADDR) = 0;

	/*
	 * Step 4: A pause of at least 500us must be observed before a single toggle.
	 */
	for (i = 0; i < 100000; i++) {
		asm("nop");
	} 
	/*
	 * Step 5: A NOP command is issued to the DDR3-SDRAM
	 * Program the NOP command in the MPDDRC_MR.
	 * The application must write a one to the MODE field in the MPDDRC_MR.
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * CKE is now driven high.
	 */
	 MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
	*((uint32_t *)DDR_CS_ADDR) = 0;
	for (i = 0; i < 2000; i++) {
		asm("nop");
	} 
	/*
	 * Step 6: An Extended Mode Register Set (EMRS2) cycle is issued to choose
	 * between commercial or high temperature operations. The application must
	 * write a five to the MODE field in the MPDDRC_MR and perform a write
	 * access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2] is set to 0,
	 * BA[1] is set to 1 and signal BA[0] is set to 0.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
	*((uint32_t *)(DDR_CS_ADDR + (0x2 << ba_offset))) = 0;
	for (i = 0; i < 2000; i++) {
		asm("nop");
	} 
	/*
	 * Step 7: An Extended Mode Register Set (EMRS3) cycle is issued to set
	 * the Extended Mode Register to 0. The application must write a five
	 * to the MODE field in the MPDDRC_MR and perform a write access to the
	 * DDR3-SDRAM to acknowledge this command. The write address must be
	 * chosen so that signal BA[2] is set to 0, BA[1] is set to 1 and signal
	 * BA[0] is set to 1.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
	*((uint32_t *)(DDR_CS_ADDR + (0x3 << ba_offset))) = 0;
	for (i = 0; i < 2000; i++) {
		asm("nop");
	} 
	/*
	 * Step 8: An Extended Mode Register Set (EMRS1) cycle is issued to
	 * disable and to program O.D.S. (Output Driver Strength).
	 * The application must write a five to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2:1] is set to 0
	 * and signal BA[0] is set to 1.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
	*((uint32_t *)(DDR_CS_ADDR + (0x1 << ba_offset))) = 0;
	for (i = 0; i < 2000; i++) {
		asm("nop");
	}

	/*
	 * Step 9: Write a one to the DLL bit (enable DLL reset) in the MPDDRC
	 * Configuration Register (MPDDRC_CR)
	 */
	/*
	 * Step 10: A Mode Register Set (MRS) cycle is issued to reset DLL.
	 * The application must write a three to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LMR_CMD;
	*((uint32_t *)(DDR_CS_ADDR )) = 0;
	for (i = 0; i < 10000; i++) {
		asm("nop");
	} 

	/*
	 * Step 11: A Calibration command (MRS) is issued to calibrate RTT and
	 * RON values for the Process Voltage Temperature (PVT).
	 * The application must write a six to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_DEEP_CALIB_MD;
	*((uint32_t *)(DDR_CS_ADDR )) = 0;
	for (i = 0; i < 2000; i++) {
		asm("nop");
	}

	/*
	 * Step 12: A Normal Mode command is provided.
	 * Program the Normal mode in the MPDDRC_MR and perform a write access
	 * to any DDR3-SDRAM address to acknowledge this command.
	 */
	MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NORMAL_CMD;
	*((uint32_t *)(DDR_CS_ADDR )) = 0;

	/*
	 * Step 13: Perform a write access to any DDR3-SDRAM address.
	 */
		*((uint32_t *)(DDR_CS_ADDR )) = 0;

	/*
	 * Step 14: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 * refresh rate = delay between refresh cycles.
	 * The DDR3-SDRAM device requires a refresh every 7.81 us.
	 */
	/* Refresh Timer is (64ms / 8k) * 166MHz = 1297(0x511) */
	MPDDRC->MPDDRC_RTR = 0x511;
}

/**
 * \brief Configures SDRAM.
 */
void board_cfg_sdram(void)
{
}

/** \brief Configures NandFlash
 */
void board_cfg_nand_flash(uint8_t busWidth)
{
}

/** \brief Configures NorFlash
 */
void  board_cfg_nor_flash(uint8_t busWidth)
{
}
