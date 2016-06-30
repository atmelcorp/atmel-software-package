/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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
#include "trace.h"

#include "peripherals/aic.h"
#include "peripherals/hsmc.h"
#ifdef CONFIG_HAVE_ISC
#include "peripherals/isc.h"
#endif
#include "peripherals/l2cc.h"
#include "peripherals/matrix.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/sdmmc.h"
#include "peripherals/sfc.h"
#include "peripherals/wdt.h"

#ifdef CONFIG_HAVE_LCDD
#include "video/lcdd.h"
#endif

#include "timer.h"
#include "memories/ddram.h"

#include "misc/cache.h"
#include "misc/console.h"
#include "misc/led.h"

#include "board_support.h"

#ifdef CONFIG_HAVE_PMIC_ACT8945A
#include "peripherals/twid.h"
#include "power/act8945a.h"
#endif

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

struct _console_cfg {
	void* addr;
	const struct _pin pins[2];
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct _l2cc_config l2cc_cfg = {
	.instruct_prefetch = true,	// Instruction prefetch enable
	.data_prefetch = true,	// Data prefetch enable
	.double_linefill = true,
	.incr_double_linefill = true,
	/* Disable Write back (enables write through, Use this setting
	   if DDR2 mem is not write-back) */
	//cfg.no_write_back = true,
	.force_write_alloc = L2CC_FWA_NO_ALLOCATE,
	.offset = 31,
	.prefetch_drop = true,
	.standby_mode = true,
	.dyn_clock_gating = true
};

static const char* board_name = BOARD_NAME;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

ALIGNED(16384) static uint32_t tlb[4096];

#ifdef CONFIG_HAVE_PMIC_ACT8945A
static struct _twi_desc act8945a_twid = {
	.addr = ACT8945A_ADDR,
	.freq = ACT8945A_FREQ,
	.transfert_mode = TWID_MODE_POLLING
};

static struct _act8945a act8945a = {
	.desc = {
		.pin_chglev = ACT8945A_PIN_CHGLEV,
		.pin_irq = ACT8945A_PIN_IRQ,
		.pin_lbo = ACT8945A_PIN_LBO
	}
};

static bool act8945a_initialized = false;
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_board_name(void)
{
	return board_name;
}

void board_cfg_clocks(void)
{
	pmc_switch_mck_to_slck();
	pmc_set_mck_h32mxdiv(PMC_MCKR_H32MXDIV_H32MXDIV2);
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_EQ_PCK);
	/* Disable PLLA */
	pmc_set_plla(0, 0);
	pmc_select_external_osc();
	/* Configure PLLA */
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(82) |
		CKGR_PLLAR_DIVA_BYPASS, 0);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_switch_mck_to_pll();
}

void board_cfg_lowlevel(bool clocks, bool ddram, bool mmu)
{
	/* Disable Watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	if (clocks) {
		/* Configure system clocks */
		board_cfg_clocks();
	}

	/* Setup default interrupt handlers */
	aic_initialize();

	if (ddram) {
		/* Configure DDRAM */
		board_cfg_ddram();
	}

	if (mmu) {
		/* Setup MMU */
		board_cfg_mmu();
	}

	/* Timer */
	timer_configure(BOARD_TIMER_RESOLUTION);
}

void board_cfg_console(uint32_t baudrate)
{
	if (!baudrate) {
#ifdef BOARD_CONSOLE_BAUDRATE
		baudrate = BOARD_CONSOLE_BAUDRATE;
#else
		baudrate = 115200;
#endif
	}

#if defined(BOARD_CONSOLE_PINS) && defined(BOARD_CONSOLE_ADDR)
	const struct _pin console_pins[] = BOARD_CONSOLE_PINS;

	pio_configure(console_pins, ARRAY_SIZE(console_pins));
	console_configure(BOARD_CONSOLE_ADDR, baudrate);
#else
	/* default console ports used by ROM-code */
	const struct _console_cfg console_cfg[] = {
		{ UART1, PINS_UART1_IOS1 },
		{ UART0, PINS_UART0_IOS1 },
		{ UART1, PINS_UART1_IOS2 },
		{ UART2, PINS_UART2_IOS1 },
		{ UART2, PINS_UART2_IOS2 },
		{ UART2, PINS_UART2_IOS3 },
		{ UART3, PINS_UART3_IOS1 },
		{ UART3, PINS_UART3_IOS2 },
		{ UART3, PINS_UART3_IOS3 },
		{ UART4, PINS_UART4_IOS1 },
	};
	uint32_t bcw;
	uint32_t console;

	/* read boot config word from fuse */
	bcw = sfc_read(16);

	/* if BSCR is not disabled and BUREG index is valid, use BUREG */
	if ((bcw & BCW_DISABLE_BSCR) == 0) {
		uint32_t bsc_cr = BSC->BSC_CR;
		if (bsc_cr & BSC_CR_BUREG_VALID) {
			uint32_t index = (bsc_cr & BSC_CR_BUREG_INDEX_Msk) >> BSC_CR_BUREG_INDEX_Pos;
			bcw = SECURAM->BUREG[index];
		}
	}

	/* configure console */
	console = (bcw & BCW_UART_CONSOLE_Msk) >> BCW_UART_CONSOLE_Pos;
	if (console < ARRAY_SIZE(console_cfg)) {
		pio_configure(console_cfg[console].pins, 2);
		console_configure(console_cfg[console].addr, baudrate);
	}
#endif
}

void board_restore_pio_reset_state(void)
{
	int i;

	/* all pins, excluding JTAG and NTRST */
	struct _pin pins[] = {
		{ PIO_GROUP_A, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_B, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_C, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_D, 0xFFF83FFF, PIO_INPUT, PIO_PULLUP },
	};

	/* For low_power_mode example, power consumption results can be affected
	* by IOs setting. To generate power consumption numbers in datasheet,
	* most IOs must be disconnected from external devices just like on
	* VB board. Then putting IOs to reset state are OK.
	* On SAMA5D2-XULT board, please put IOs to output state as below.
	*/
	//struct _pin pins[] = {
	//	{ PIO_GROUP_A, 0xFFFFFFFF, PIO_OUTPUT, PIO_PULLUP },
	//	{ PIO_GROUP_B, 0xFFFFFFFF, PIO_OUTPUT, PIO_PULLUP },
	//	{ PIO_GROUP_C, 0xFFFFFFFF, PIO_OUTPUT, PIO_PULLUP },
	//	{ PIO_GROUP_D, 0xFFF83FFF, PIO_OUTPUT, PIO_PULLUP },
	//};

	pio_configure(pins, ARRAY_SIZE(pins));
	for (i = 0; i < ARRAY_SIZE(pins); i++)
		pio_clear(&pins[i]);
}

void board_save_misc_power(void)
{
	int i;

	/* disable USB clock */
	pmc_disable_upll_clock();
	pmc_disable_upll_bias();

	/* Disable audio clock */
	pmc_disable_audio();

	/* disable system clocks */
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_LCD);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_UHP);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_UDP);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK0);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK1);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK2);
#ifdef CONFIG_HAVE_ISC
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_ISC);
#endif

	/* disable all peripheral clocks except PIOA for JTAG, serial debug port */
	for (i = ID_PIT; i < ID_PERIPH_COUNT; i++) {
		if (i == ID_PIOA)
			continue;
		pmc_disable_peripheral(i);
	}
}

void board_cfg_mmu(void)
{
	uint32_t addr;

	if (cp15_mmu_is_enabled())
		return;

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

	/* 0x00300000: UDPHS (RAM) */
	tlb[0x003] = TTB_SECT_ADDR(0x00300000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00400000: UHPHS (OHCI) */
	tlb[0x004] = TTB_SECT_ADDR(0x00400000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00500000: UDPHS (EHCI) */
	tlb[0x005] = TTB_SECT_ADDR(0x00500000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00600000: AXIMX */
	tlb[0x006] = TTB_SECT_ADDR(0x00600000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00700000: DAP */
	tlb[0x007] = TTB_SECT_ADDR(0x00700000)
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
	tlb[0x00b] = TTB_SECT_ADDR(0x00b00000)
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

	/* 0x20000000: DDR Chip Select */
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

	/* 0x40000000: DDR AESB Chip Select */
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
	for (addr = 0x800; addr < 0x900; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x90000000: QSPI0/1 AESB MEM */
	for (addr = 0x900; addr < 0xa00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xa0000000: SDMMC0 */
	for (addr = 0xa00; addr < 0xb00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  //| TTB_SECT_SHAREABLE_DEVICE
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xb0000000: SDMMC1 */
	for (addr = 0xb00; addr < 0xc00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  //| TTB_SECT_SHAREABLE_DEVICE
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xc0000000: NFC Command Register */
	for (addr = 0xc00; addr < 0xd00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  //| TTB_SECT_SHAREABLE_DEVICE
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xd0000000: QSPI0/1 MEM */
	for (addr = 0xd00; addr < 0xe00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
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

	/* Enable MMU, I-Cache and D-Cache */
	mmu_configure(tlb);
	cp15_icache_enable();
	cp15_mmu_enable();
	cp15_dcache_enable();
}

void board_cfg_l2cc(void)
{
	l2cc_configure(&l2cc_cfg);
}

void board_cfg_matrix_for_ddr(void)
{
	int i;

	/* Disable write protection */
	matrix_remove_write_protection(MATRIX0);

	/* External DDR */
	/* DDR port 0 not used */
	for (i = H64MX_SLAVE_DDR_PORT1; i <= H64MX_SLAVE_DDR_PORT7; i++) {
		matrix_configure_slave_sec(MATRIX0, i, 0xff, 0xff, 0xff);
		matrix_set_slave_split_addr(MATRIX0, i, MATRIX_AREA_128M, 0xf);
		matrix_set_slave_region_size(MATRIX0, i, MATRIX_AREA_128M, 0x1);
	}
}

void board_cfg_matrix_for_nand(void)
{
	/* Disable write protection */
	matrix_remove_write_protection(MATRIX1);

	/* NFC Command Register */
	matrix_configure_slave_sec(MATRIX1,
			H32MX_SLAVE_NFC_CMD, 0xc0, 0xc0, 0xc0);
	matrix_set_slave_split_addr(MATRIX1,
			H32MX_SLAVE_NFC_CMD, MATRIX_AREA_128M, 0xc0);
	matrix_set_slave_region_size(MATRIX1,
			H32MX_SLAVE_NFC_CMD, MATRIX_AREA_128M, 0xc0);

	/* NFC SRAM */
	matrix_configure_slave_sec(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, 0x1, 0x1, 0x1);
	matrix_set_slave_split_addr(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, MATRIX_AREA_8K, 0x1);
	matrix_set_slave_region_size(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, MATRIX_AREA_8K, 0x1);
}

void board_cfg_ddram(void)
{
#ifdef BOARD_DDRAM_TYPE
	board_cfg_matrix_for_ddr();
	struct _mpddrc_desc desc;
	ddram_init_descriptor(&desc, BOARD_DDRAM_TYPE);
	ddram_configure(&desc, ID_TC0, 0);
#endif
}

#ifdef CONFIG_HAVE_NAND_FLASH
void board_cfg_nand_flash(void)
{
#if defined(BOARD_NANDFLASH_PINS) && defined(BOARD_NANDFLASH_BUS_WIDTH)
	const struct _pin pins_nandflash[] = BOARD_NANDFLASH_PINS;
	pio_configure(pins_nandflash, ARRAY_SIZE(pins_nandflash));
	board_cfg_matrix_for_nand();
	hsmc_nand_configure(BOARD_NANDFLASH_BUS_WIDTH);
#else
	trace_fatal("Cannot configure NAND: target board has no NAND definitions!");
#endif
}
#endif /* CONFIG_HAVE_NAND_FLASH */

bool board_cfg_sdmmc(uint32_t periph_id)
{
/* mask for board capabilities defines: voltage, slot type and 8-bit support */
#define CAPS0_MASK (SDMMC_CA0R_V33VSUP | SDMMC_CA0R_V30VSUP | \
                    SDMMC_CA0R_V18VSUP | SDMMC_CA0R_SLTYPE_Msk | \
                    SDMMC_CA0R_ED8SUP)

	switch (periph_id) {
#ifdef SDMMC0
	case ID_SDMMC0:
	{
#if defined(BOARD_SDMMC0_CAPS0) && defined(BOARD_SDMMC0_PINS)
		struct _pin pins[] = BOARD_SDMMC0_PINS;
		uint32_t caps0 = BOARD_SDMMC0_CAPS0;

#ifdef CONFIG_BOARD_SAMA5D2_XPLAINED
		struct _pin vsel_pin = PIN_SDMMC0_VDDSEL_IOS1;
		int vsel_ix;

#ifndef SDMMC_TRIM_LOW_VOLTAGE
		/* Set PMIC output 7 to 1.8V (VDDSDHC1V8) */
		if (!act8945a_initialized) {
			board_cfg_pmic();
			if (!act8945a_initialized)
				return false;
		}
		if (!act8945a_set_regulator_voltage(&act8945a, 7, 1800))
			return false;
		if (!act8945a_enable_regulator(&act8945a, 7, true))
			return false;
#endif

		/* The PIOs of SDMMC0 normally include SDMMC0_VDDSEL. On regular
		 * SAMA5D2-XULT, the SDMMC0_VDDSEL line has a pull-down resistor
		 * hence at power-on time VCCQ is 3.3V. In this default config
		 * we enable SDMMC0_VDDSEL, which can switch VCCQ to 1.8V.
		 * Changing VCCQ on the fly is required with UHS-I SD cards. It
		 * is illegal with e.MMC devices. Detect if the board has been
		 * modified to supply 1.8V VCCQ at power-on time.
		 * First, search for the SDMMC0_VDDSEL PIO on this board. */
		for (vsel_ix = 0; vsel_ix < ARRAY_SIZE(pins); vsel_ix++)
			if (pins[vsel_ix].mask == vsel_pin.mask
			    && pins[vsel_ix].group == vsel_pin.group)
				break;
		if (vsel_ix < ARRAY_SIZE(pins)) {
			/* Second, sense whether the SDMMC0_VDDSEL line is
			 * pulled up or down */
			vsel_pin.type = PIO_INPUT;
			vsel_pin.attribute = PIO_PULLUP;
			pio_configure(&vsel_pin, 1);
			if (pio_get(&vsel_pin)) {
				/* The line is pulled up => at power-on time
				 * VCCQ is 1.8V. If the SDMMC0_VDDSEL function
				 * was enabled, then everytime SRR:SWRSTALL was
				 * triggered, VCCQ would switch to 3.3V. */
				pins[vsel_ix].type = PIO_OUTPUT_1;
				pins[vsel_ix].attribute = PIO_DEFAULT;
				/* Deviation from the specification: we use the
				 * Voltage Support capabilities to indicate the
				 * supported signaling levels (VCCQ). */
				caps0 &= ~SDMMC_CA0R_V33VSUP;
				caps0 &= ~SDMMC_CA0R_V30VSUP;
				caps0 |= SDMMC_CA0R_V18VSUP;
			}
		}
#endif
		/* Program capabilities for SDMMC0 */
		sdmmc_set_capabilities(SDMMC0, caps0, CAPS0_MASK, 0, 0);

		/* Configure SDMMC0 pins */
		return pio_configure(pins, ARRAY_SIZE(pins)) ? true : false;
#else
		trace_fatal("Cannot configure SDMMC0: target board has no SDMMC0 definitions!");
		return false;
#endif
	}
#endif
	case ID_SDMMC1:
	{
#if defined(BOARD_SDMMC1_CAPS0) && defined(BOARD_SDMMC1_PINS)
		const struct _pin pins[] = BOARD_SDMMC1_PINS;
		uint32_t caps0 = BOARD_SDMMC1_CAPS0;

		/* Program capabilities for SDMMC1 */
		sdmmc_set_capabilities(SDMMC1, caps0, CAPS0_MASK, 0, 0);

		/* Configure SDMMC1 pins */
		return pio_configure(pins, ARRAY_SIZE(pins)) ? true : false;
#else
		trace_fatal("Cannot configure SDMMC1: target board has no SDMMC1 definitions!");
		return false;
#endif
	}
	default:
		return false;
	}

#undef CAPS0_MASK
}

void board_cfg_pmic(void)
{
#ifdef CONFIG_HAVE_PMIC_ACT8945A
	const struct _pin pins[] = ACT8945A_PINS;

	if (act8945a_initialized)
		return;

	if (!pio_configure(pins, ARRAY_SIZE(pins)))
		goto Fail;
	if (!act8945a_configure(&act8945a, &act8945a_twid))
		goto Fail;
#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED) || defined(CONFIG_BOARD_SAMA5D2_PTC_ENGI)
	/* Set PMIC output 6 to 2.5V (VDD_LED) */
	if (!act8945a_set_regulator_voltage(&act8945a, 6, 2500))
		goto Fail;
	if (!act8945a_enable_regulator(&act8945a, 6, true))
		goto Fail;
#endif
	act8945a_initialized = true;
	return;

Fail:
	trace_error("Error initializing ACT8945A PMIC\r\n");
#endif
}

#ifdef CONFIG_HAVE_ISC
void board_cfg_isc(void)
{
	const struct _pin pins_isc[]= ISC_PINS;
	const struct _pin pin_rst = ISC_PIN_RST;
	const struct _pin pin_pwd = ISC_PIN_PWD;

	/* Configure ISC pins */
	pio_configure(pins_isc, ARRAY_SIZE(pins_isc));

	/* Reset sensor */
	pio_configure(&pin_rst,1);
	pio_configure(&pin_pwd,1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
	timer_wait(10);

	pmc_enable_peripheral(ID_ISC);
	pmc_enable_system_clock(PMC_SYSTEM_CLOCK_ISC);
	isc_configure_master_clock(7 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);

	isc_enable_master_clock();
	isc_configure_isp_clock(2 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);

	isc_enable_isp_clock();
}
#endif

#ifdef CONFIG_HAVE_LCDD
void board_cfg_lcd(void)
{
	const struct _pin pins_lcd[] = BOARD_LCD_PINS;
	const struct _lcdd_desc lcd_desc = {
		.width = BOARD_LCD_WIDTH,
		.height = BOARD_LCD_HEIGHT,
		.framerate = BOARD_LCD_FRAMERATE,
		.timing_vfp = BOARD_LCD_TIMING_VFP,
		.timing_vbp = BOARD_LCD_TIMING_VBP,
		.timing_vpw = BOARD_LCD_TIMING_VPW,
		.timing_hfp = BOARD_LCD_TIMING_HFP,
		.timing_hbp = BOARD_LCD_TIMING_HBP,
		.timing_hpw = BOARD_LCD_TIMING_HPW,
	};

	pio_configure(pins_lcd, ARRAY_SIZE(pins_lcd));
	lcdd_configure(&lcd_desc);
}
#endif

void board_cfg_led(void)
{
#ifdef NUM_LEDS
	uint8_t i;

	for (i = 0 ; i < NUM_LEDS ; ++i) {
		led_configure(i);
	}
#endif
}

#ifdef CONFIG_HAVE_PDMIC
void board_cfg_pdmic(void)
{
	const struct _pin pins_pdmic[] = PINS_PDMIC_IOS1;

	pio_configure(pins_pdmic, ARRAY_SIZE(pins_pdmic));
}
#endif

#ifdef CONFIG_HAVE_CLASSD
void board_cfg_classd(void)
{
	const struct _pin pins_classd[] = BOARD_CLASSD_PINS;

	pio_configure(pins_classd, ARRAY_SIZE(pins_classd));
}
#endif
