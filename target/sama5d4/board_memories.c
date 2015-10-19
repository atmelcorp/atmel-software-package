/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 20143, Atmel Corporation
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

/** \addtogroup ddrd_module
 *
 * The DDR/SDR SDRAM Controller (DDRSDRC) is a multiport memory controller. It comprises
 * four slave AHB interfaces. All simultaneous accesses (four independent AHB ports) are interleaved
 * to maximize memory bandwidth and minimize transaction latency due to SDRAM protocol.
 *
 * \section ddr2 Configures DDR2
 *
 * The DDR2-SDRAM devices are initialized by the following sequence:
 * <ul>
 * <li> EBI Chip Select 1 is assigned to the DDR2SDR Controller, Enable DDR2 clock x2 in PMC.</li>
 * <li> Step 1: Program the memory device type</li>
 * <li> Step 2:
 *  -# Program the features of DDR2-SDRAM device into the Configuration Register.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T0PR.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T1PR.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T2PR. </li>
 * <li> Step 3: An NOP command is issued to the DDR2-SDRAM to enable clock. </li>
 * <li> Step 4:  An NOP command is issued to the DDR2-SDRAM </li>
 * <li> Step 5: An all banks precharge command is issued to the DDR2-SDRAM. </li>
 * <li> Step 6: An Extended Mode Register set (EMRS2) cycle is  issued to chose between commercialor high  temperature operations.</li>
 * <li> Step 7: An Extended Mode Register set (EMRS3) cycle is issued to set all registers to 0. </li>
 * <li> Step 8:  An Extended Mode Register set (EMRS1) cycle is issued to enable DLL.</li>
 * <li> Step 9:  Program DLL field into the Configuration Register.</li>
 * <li> Step 10: A Mode Register set (MRS) cycle is issued to reset DLL.</li>
 * <li> Step 11: An all banks precharge command is issued to the DDR2-SDRAM.</li>
 * <li> Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register.</li>
 * <li> Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).</li>
 * <li> Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices.</li>
 * <li> Step 15: Program OCD field into the Configuration Register to high (OCD calibration default). </li>
 * <li> Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.</li>
 * <li> Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit).</li>
 * <li> Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.</li>
 * <li> Step 19,20: A mode Normal command is provided. Program the Normal mode into Mode Register.</li>
 * <li> Step 21: Write the refresh rate into the count field in the Refresh Timer register. The DDR2-SDRAM device requires a refresh every 15.625 or 7.81. </li>
 * </ul>
*/
/*@{*/
/*@}*/

/** \addtogroup sdram_module
 *
 * \section sdram Configures SDRAM
 *
 * The SDR-SDRAM devices are initialized by the following sequence:
 * <ul>
 * <li> EBI Chip Select 1 is assigned to the DDR2SDR Controller, Enable DDR2 clock x2 in PMC.</li>
 * <li> Step 1. Program the memory device type into the Memory Device Register</li>
 * <li> Step 2. Program the features of the SDR-SDRAM device into the Timing Register and into the Configuration Register.</li>
 * <li> Step 3. For low-power SDRAM, temperature-compensated self refresh (TCSR), drive strength (DS) and partial array self refresh (PASR) must be set in the Low-power Register.</li>
 * <li> Step 4. A NOP command is issued to the SDR-SDRAM. Program NOP command into Mode Register, the application must
 * set Mode to 1 in the Mode Register. Perform a write access to any SDR-SDRAM address to acknowledge this command.
 * Now the clock which drives SDR-SDRAM device is enabled.</li>
 * <li> Step 5. An all banks precharge command is issued to the SDR-SDRAM. Program all banks precharge command into Mode Register, the application must set Mode to 2 in the
 * Mode Register . Perform a write access to any SDRSDRAM address to acknowledge this command.</li>
 * <li> Step 6. Eight auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into Mode Register, the application must set Mode to 4 in the Mode Register.
 * Once in the idle state, two AUTO REFRESH cycles must be performed.</li>
 * <li> Step 7. A Mode Register set (MRS) cycle is issued to program the parameters of the SDRSDRAM
 * devices, in particular CAS latency and burst length. </li>
 * <li> Step 8. For low-power SDR-SDRAM initialization, an Extended Mode Register set (EMRS) cycle is issued to program the SDR-SDRAM parameters (TCSR, PASR, DS). The write
 * address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0 </li>
 * <li> Step 9. The application must go into Normal Mode, setting Mode to 0 in the Mode Register and perform a write access at any location in the SDRAM to acknowledge this command.</li>
 * <li> Step 10. Write the refresh rate into the count field in the DDRSDRC Refresh Timer register </li>
* </ul>
*/
/*@{*/
/*@}*/

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
#include "board_memories.h"

#include "cortex-a/mmu.h"

#include "peripherals/l2cc.h"
#include "peripherals/pmc.h"
#include "peripherals/matrix.h"

#include "memories/ddram.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define DDR2_BA0(r) (1 << (26 + r))
#define DDR2_BA1(r) (1 << (27 + r))

#define H64MX_DDR_SLAVE_PORT0   3

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

const static struct _l2cc_control l2cc_cfg = {
	.instruct_prefetch = true,	// Instruction prefetch enable
	.data_prefetch = true,	// Data prefetch enable
	.double_linefill = true,
	.incr_double_linefill = true,
	/* Disable Write back (enables write through, Use this setting
	   if DDR2 mem is not write-back) */
	//cfg.no_write_back = true,
	.force_write_alloc = FWA_NO_ALLOCATE,
	.offset = 31,
	.prefetch_drop = true,
	.standby_mode = true,
	.dyn_clock_gating = true
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void matrix_configure_slave_ddr(void)
{
	int port;

	/* Disable write protection */
	matrix_remove_write_protection(MATRIX0);

	/* Partition internal SRAM */
	matrix_configure_slave_sec(MATRIX0, 11, 0, 0, 0);
	matrix_set_slave_region_size(MATRIX0, 11, MATRIX_AREA_128K, 0x1);
	matrix_set_slave_split_addr(MATRIX0, 11, MATRIX_AREA_64K, 0x1);

	/* Partition external DDR */
	/* DDR port 0 not used from NWd */
	for (port = 1; port < 8; port++)
	{
		matrix_configure_slave_sec(MATRIX0,
					   H64MX_DDR_SLAVE_PORT0 + port,
					   0xff, 0xff, 0xff);
		matrix_set_slave_region_size(MATRIX0,
					     H64MX_DDR_SLAVE_PORT0 + port,
					     MATRIX_AREA_128M,
					     0x1);
		matrix_set_slave_split_addr(MATRIX0,
					     H64MX_DDR_SLAVE_PORT0 + port,
					     MATRIX_AREA_128M,
					     0xF);
	}
}

static void matrix_configure_slave_nand(void)
{
	/* Disable write protection */
	matrix_remove_write_protection(MATRIX0);

	/* Partition internal SRAM */
	matrix_configure_slave_sec(MATRIX0, 11, 0x1, 0x1, 0x1);
	matrix_set_slave_region_size(MATRIX0, 11, MATRIX_AREA_128K, 0x1);
	matrix_set_slave_split_addr(MATRIX0, 11, MATRIX_AREA_128K, 0x1);

	matrix_configure_slave_sec(MATRIX1, 3, 0xFF, 0xFF, 0xFF);
	matrix_set_slave_region_size(MATRIX1, 3, MATRIX_AREA_8M, 0xFF);
	matrix_set_slave_split_addr(MATRIX1, 3, MATRIX_AREA_8M, 0xFF);

	matrix_configure_slave_sec(MATRIX1, 4, 0xFF,0xFF,0xFF);
	matrix_set_slave_region_size(MATRIX1, 4, MATRIX_AREA_8K, 0x1);
	matrix_set_slave_split_addr(MATRIX1, 4, MATRIX_AREA_128M, 0x4F);
	MATRIX1->MATRIX_MEIER = 0x3FF;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_setup_tlb(uint32_t *tlb)
{
	uint32_t addr;

	/* TODO: some peripherals are configured TTB_SECT_STRONGLY_ORDERED
	   instead of TTB_SECT_SHAREABLE_DEVICE because their drivers have to
	   be verified for correct operation when write-back is enabled */

	/* Reset table entries */
	for (addr = 0; addr < 4096; addr++)
		tlb[addr] = 0;

	/* 0x00000000: ROM */
	tlb[0x000] = TTB_SECT_ADDR(0x00000000)
	           | TTB_SECT_AP_READ_ONLY
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_TYPE_SECT;

	/* 0x00100000: NFC SRAM */
	tlb[0x001] = TTB_SECT_ADDR(0x00100000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00200000: SRAM */
	tlb[0x002] = TTB_SECT_ADDR(0x00200000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_TYPE_SECT;

	/* 0x00300000: VDEC */
	tlb[0x003] = TTB_SECT_ADDR(0x00300000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00400000: UDPHS (RAM) */
	tlb[0x004] = TTB_SECT_ADDR(0x00400000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00500000: UHP (OHCI) */
	tlb[0x005] = TTB_SECT_ADDR(0x00500000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00600000: UHP (EHCI) */
	tlb[0x006] = TTB_SECT_ADDR(0x00600000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00700000: AXI Matrix */
	tlb[0x007] = TTB_SECT_ADDR(0x00700000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00800000: DAP */
	tlb[0x008] = TTB_SECT_ADDR(0x00800000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00900000: SMD */
	tlb[0x009] = TTB_SECT_ADDR(0x00900000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00a00000: L2CC */
	tlb[0x00a] = TTB_SECT_ADDR(0x00a00000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x10000000: EBI Chip Select 0 */
	for (addr = 0x100; addr < 0x200; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x20000000: DDR CS */
	/* (64MB cacheable, 448MB strongly ordered) */
	for (addr = 0x200; addr < 0x240; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_TYPE_SECT;
	for (addr = 0x240; addr < 0x400; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x40000000: DDR CS/AES */
	for (addr = 0x400; addr < 0x600; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_TYPE_SECT;

	/* 0x60000000: EBI Chip Select 1 */
	for (addr = 0x600; addr < 0x700; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x70000000: EBI Chip Select 2 */
	for (addr = 0x700; addr < 0x800; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x80000000: EBI Chip Select 3 */
	for (addr = 0x800; addr < 0x880; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x90000000: NFC Command Registers */
	for (addr = 0x900; addr < 0xa00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  //| TTB_SECT_SHAREABLE_DEVICE
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xf0000000: Internal Peripherals */
	tlb[0xf00] = TTB_SECT_ADDR(0xf0000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;

	/* 0xf8000000: Internal Peripherals */
	tlb[0xf80] = TTB_SECT_ADDR(0xf8000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;

	/* 0xfc000000: Internal Peripherals */
	tlb[0xfc0] = TTB_SECT_ADDR(0xfc000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;
}

void board_cfg_l2cc(void)
{
	l2cc_configure(&l2cc_cfg);
}

void board_cfg_vdd_mem_sel(uint8_t VddMemSel)
{
}

void board_cfg_ddram(void)
{
	matrix_configure_slave_ddr();
	struct _mpddrc_desc desc;
	ddram_init_descriptor(&desc, BOARD_DDRAM_TYPE);
	ddram_configure(&desc);
}

void board_cfg_sdram(void)
{
}

void board_cfg_nand_flash(uint8_t busWidth)
{
	pmc_enable_peripheral(ID_HSMC);

	matrix_configure_slave_nand();

	HSMC->SMC_CS_NUMBER[3].HSMC_SETUP = HSMC_SETUP_NWE_SETUP(2) |
		HSMC_SETUP_NCS_WR_SETUP(2) |
		HSMC_SETUP_NRD_SETUP(2) |
		HSMC_SETUP_NCS_RD_SETUP(2);
	HSMC->SMC_CS_NUMBER[3].HSMC_PULSE = HSMC_PULSE_NWE_PULSE(7) |
		HSMC_PULSE_NCS_WR_PULSE(7) |
		HSMC_PULSE_NRD_PULSE(7) |
		HSMC_PULSE_NCS_RD_PULSE(7);
	HSMC->SMC_CS_NUMBER[3].HSMC_CYCLE = HSMC_CYCLE_NWE_CYCLE(13) |
		HSMC_CYCLE_NRD_CYCLE(13);
	HSMC->SMC_CS_NUMBER[3].HSMC_TIMINGS = HSMC_TIMINGS_TCLR(3) |
		HSMC_TIMINGS_TADL(27) |
		HSMC_TIMINGS_TAR(3) |
		HSMC_TIMINGS_TRR(6) |
		HSMC_TIMINGS_TWB(5) |
		HSMC_TIMINGS_RBNSEL(3) |
		HSMC_TIMINGS_NFSEL;
	HSMC->SMC_CS_NUMBER[3].HSMC_MODE = HSMC_MODE_READ_MODE |
		HSMC_MODE_WRITE_MODE |
		(busWidth == 8 ? HSMC_MODE_DBW_BIT_8 : HSMC_MODE_DBW_BIT_16) |
		HSMC_MODE_TDF_CYCLES(1);
}

void board_cfg_nor_flash(uint8_t busWidth)
{
	pmc_enable_peripheral(ID_HSMC);

	HSMC->SMC_CS_NUMBER[0].HSMC_SETUP = HSMC_SETUP_NWE_SETUP(1) |
		HSMC_SETUP_NCS_WR_SETUP(0) |
		HSMC_SETUP_NRD_SETUP(2) |
		HSMC_SETUP_NCS_RD_SETUP(0);
	HSMC->SMC_CS_NUMBER[0].HSMC_PULSE = HSMC_PULSE_NWE_PULSE(10) |
		HSMC_PULSE_NCS_WR_PULSE(10) |
		HSMC_PULSE_NRD_PULSE(11) |
		HSMC_PULSE_NCS_RD_PULSE(11);
	HSMC->SMC_CS_NUMBER[0].HSMC_CYCLE = HSMC_CYCLE_NWE_CYCLE(11) |
		HSMC_CYCLE_NRD_CYCLE(14);
	HSMC->SMC_CS_NUMBER[0].HSMC_TIMINGS = 0;
	HSMC->SMC_CS_NUMBER[0].HSMC_MODE = HSMC_MODE_READ_MODE |
		HSMC_MODE_WRITE_MODE |
		(busWidth == 8 ? HSMC_MODE_DBW_BIT_8 : HSMC_MODE_DBW_BIT_16) |
		HSMC_MODE_EXNW_MODE_DISABLED |
		HSMC_MODE_TDF_CYCLES(1);
}
