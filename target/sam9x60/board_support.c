/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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
#include "board_timer.h"
#include "timer.h"
#include "trace.h"

#include "irq/irq.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "sdmmc/sdmmc.h"
#include "extram/smc.h"
#include "peripherals/wdt.h"
#ifdef BOARD_DDRAM_TYPE
	#include "extram/ddram.h"
#endif
#ifdef BOARD_SDRAM_TYPE
	#include "extram/sdram.h"
#endif
#include "arm/mmu_cp15.h"
#include "mm/l1cache.h"

#include "board_support.h"
#include "string.h"
/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/
#define PLLA_DIV 1
#define PLLA_COUNT 0x3f
#define PLLA_LOOP_FILTER 0
#define PLLA_LOCK_THR 0x4

#define PLLA_CFG(_mul, _fracr)			\
	{									\
		.mul = (_mul),					\
		.div = PLLA_DIV,				\
		.count = PLLA_COUNT,			\
		.fracr = (_fracr),				\
		.loop_filter = PLLA_LOOP_FILTER,\
		.lock_thr = PLLA_LOCK_THR,      \
	}

#define PLLA_FRACR(_p, _q) ((uint32_t)((((uint64_t)(_p)) << 22) / (_q)))

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
static const char* board_name = BOARD_NAME;

SECTION(".region_ddr") ALIGNED(16384) static uint32_t tlb[4096];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_board_name(void)
{
	return board_name;
}

void board_cfg_clocks_for_preset(uint32_t preset)
{
	struct _pmc_plla_cfg plla_config;

#define MAX_PRESET 2 /* PCK/MCK (MHz) = { 600/200, 500/167 } */

	static const struct _pmc_plla_cfg plla_configs[][MAX_PRESET] = {
		/* MAINCK = 12MHz */
		{ PLLA_CFG(99, 0), PLLA_CFG(82, PLLA_FRACR(1, 3)) },

		/* MAINCK = 16MHz */
		{ PLLA_CFG(74, 0), PLLA_CFG(61, PLLA_FRACR(1, 2)) },

		/* MAINCK = 24MHz */
#ifdef CONFIG_HAVE_CLASSD
		{ PLLA_CFG(48, 0x9ba5e), PLLA_CFG(40, PLLA_FRACR(2, 3)) },
#else
		{ PLLA_CFG(49, 0), PLLA_CFG(40, PLLA_FRACR(2, 3)) },
#endif
		/* MAINCK = 48MHz */
		{ PLLA_CFG(24, 0), PLLA_CFG(19, PLLA_FRACR(5, 6)) },
	};
	uint32_t row;

	switch (pmc_get_main_oscillator_freq()) {
	default:
	case 12000000:
		row = 0;
		break;
	case 16000000:
		row = 1;
		break;
	case 24000000:
		row = 2;
		break;
	case 48000000:
		row = 3;
		break;
	}

	if (preset >= MAX_PRESET)
		trace_fatal("Invalid preset for board: %lu (max %d).\r\n", preset, MAX_PRESET);
	memcpy(&plla_config, &plla_configs[row][preset], sizeof(plla_config));

	pmc_switch_mck_to_main();
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_select_external_osc(false);
	pmc_configure_plla(&plla_config);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_switch_mck_to_pll();
}

void board_cfg_clocks(void)
{
	board_cfg_clocks_for_preset(0);
}

void board_cfg_lowlevel(bool clocks, bool ddram, bool mmu)
{
	/* Disable Watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Set the external oscillator frequency */
	pmc_set_main_oscillator_freq(BOARD_MAIN_CLOCK_EXT_OSC);

	if (clocks) {
		/* Configure system clocks */
		board_cfg_clocks();
	}

	/* Setup default interrupt handlers */
	irq_initialize();

	/* Configure system timer */
	board_cfg_timer();

	if (ddram) {
		/* Configure DDRAM */
		board_cfg_ddram();
	}

	if (mmu) {
		/* Setup MMU */
		board_cfg_mmu();
	}
}

void board_restore_pio_reset_state(void)
{
	int i;
#ifdef PINS_PUSHBUTTONS
	const struct _pin button_pins = PIN_PUSHBUTTON_1;
#else
	const struct _pin button_pins = {0x0, 0x0, 0x0, 0x0};
#endif
	/* all pins except BUTTON pins */
	struct _pin pins[] = {
		{ PIO_GROUP_A, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_B, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_C, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_D, 0xFFFFFFFF ^ (button_pins.mask), PIO_INPUT, PIO_PULLUP},
	};

	pio_configure(pins, ARRAY_SIZE(pins));
	for (i = 0; i < ARRAY_SIZE(pins); i++)
		pio_clear(&pins[i]);
}

void board_save_misc_power(void)
{
	int i;
	int tc_id = get_tc_id_from_addr(BOARD_TIMER_TC, BOARD_TIMER_CHANNEL);

	/* disable USB clock */
	pmc_disable_upll_clock();

	/* disable system clocks */
#ifdef VARIANT_SRAM
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);
#endif
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_UHP);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK0);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK1);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_QSPI);

	/* disable all peripheral clocks except PIOA for JTAG, serial debug port, PIOD for BUTTON pins */
	for (i = ID_PIT; i < ID_PERIPH_COUNT; i++) {
		if (i == ID_PIOD)
			continue;
		if (i == ID_DBGU)
			continue;
		if (i == tc_id)
			continue;
#ifdef VARIANT_DDRAM
		if (i == ID_MPDDRC)
			continue;
#endif
		pmc_disable_peripheral(i);
	}
}

void board_cfg_mmu(void)
{
	uint32_t addr;

	if (mmu_is_enabled())
		return;

	/* TODO: some peripherals are configured TTB_SECT_STRONGLY_ORDERED
	   instead of TTB_SECT_SHAREABLE_DEVICE because their drivers have to
	   be verified for correct operation when write-back is enabled */

	/* Reset table entries */
	for (addr = 0; addr < 4096; addr++)
		tlb[addr] = 0;

	/* 0x00000000: SRAM (Remapped) */
	tlb[0x000] = TTB_SECT_ADDR(0x00000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00100000: ROM */
	tlb[0x001] = TTB_SECT_ADDR(0x00100000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00300000: SRAM0 */
	tlb[0x003] = TTB_SECT_ADDR(0x00300000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00400000: SRAM1 */
	tlb[0x004] = TTB_SECT_ADDR(0x00400000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

#ifdef CONFIG_HAVE_UDPHS
	/* 0x00500000: UDPHS RAM */
	tlb[0x005] = TTB_SECT_ADDR(0x00500000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00600000: UHP (OHCI) */
	tlb[0x006] = TTB_SECT_ADDR(0x00600000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00700000: UHP (EHCI) */
	tlb[0x007] = TTB_SECT_ADDR(0x00700000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;
#endif /* CONFIG_HAVE_UDPHS */

	/* 0x10000000: EBI Chip Select 0 */
	for (addr = 0x100; addr < 0x200; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x20000000: EBI Chip Select 1 / DDR CS */
	/* (64MB cacheable, 192MB strongly ordered) */
	for (addr = 0x200; addr < 0x240; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;
	for (addr = 0x240; addr < 0x300; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x30000000: EBI Chip Select 2 */
	for (addr = 0x300; addr < 0x400; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x40000000: EBI Chip Select 3 */
	for (addr = 0x400; addr < 0x500; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x50000000: EBI Chip Select 4 */
	for (addr = 0x500; addr < 0x600; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x60000000: EBI Chip Select 5 */
	for (addr = 0x600; addr < 0x700; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_SECT_SBO
	                  | TTB_TYPE_SECT;

	/* 0x70000000: QSPI0/1 AESB MEM */
	for (addr = 0x700; addr < 0x800; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
#if defined(VARIANT_QSPI0)
	                  | TTB_SECT_CACHEABLE_WB
#else
	                  | TTB_SECT_STRONGLY_ORDERED
#endif
	                  | TTB_TYPE_SECT;

	/* 0x80000000: SDMMC0 */
	for (addr = 0x800; addr < 0x900; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x90000000: SDMMC1 */
	for (addr = 0x900; addr < 0xa00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xeff00000: OTPC */
	tlb[0xeff] = TTB_SECT_ADDR(0xeff00000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0xf0000000: Peripherals */
	tlb[0xf00] = TTB_SECT_ADDR(0xf0000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0xf8000000: Peripherals */
	tlb[0xf80] = TTB_SECT_ADDR(0xf8000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0xfff0000: System Controller */
	tlb[0xfff] = TTB_SECT_ADDR(0xfff00000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* Enable MMU, I-Cache and D-Cache */
	mmu_configure(tlb);
	icache_enable();
	mmu_enable();
	dcache_enable();
}


#define VDDIOM_1V8_OUT_Z_CALN_TYP 4
#define VDDIOM_1V8_OUT_Z_CALP_TYP 10

void board_cfg_matrix_for_ddr(void)
{
	uint32_t reg;

	SFR->SFR_CCFG_EBICSA |= SFR_CCFG_EBICSA_EBI_CS1A | SFR_CCFG_EBICSA_NFD0_ON_D16 | SFR_CCFG_EBICSA_DDR_MP_EN;
	/*
	 * On the first SAM9X60 V/DWB samples, automatic calibration computes
	 * wrong value. Calibrate output impedance manually.
	 */
	reg = SFR->SFR_CAL1;
	reg &= ~(SFR_CAL1_CALN_M_Msk | SFR_CAL1_CALP_M_Msk);
	reg |= SFR_CAL1_TEST_M | SFR_CAL1_CALN_M(VDDIOM_1V8_OUT_Z_CALN_TYP) | SFR_CAL1_CALP_M(VDDIOM_1V8_OUT_Z_CALP_TYP);
	SFR->SFR_CAL1 = reg;
}

void board_cfg_matrix_for_sdr(void)
{
	SFR->SFR_CCFG_EBICSA |= SFR_CCFG_EBICSA_EBI_CS1A | SFR_CCFG_EBICSA_NFD0_ON_D16;
}

void board_cfg_matrix_for_nand(void)
{
	uint32_t mask = SFR_CCFG_EBICSA_EBI_CS3A | SFR_CCFG_EBICSA_NFD0_ON_D16;
	uint32_t value = SFR_CCFG_EBICSA_EBI_CS3A;
	uint32_t reg;

	value |= SFR_CCFG_EBICSA_NFD0_ON_D16;

	reg = SFR->SFR_CCFG_EBICSA;
	reg = (reg & ~mask) | value;
	SFR->SFR_CCFG_EBICSA = reg;
}

void board_cfg_matrix_for_nand_ex(bool nfd0_on_d16)
{
	uint32_t mask = SFR_CCFG_EBICSA_EBI_CS3A | SFR_CCFG_EBICSA_NFD0_ON_D16;
	uint32_t value = SFR_CCFG_EBICSA_EBI_CS3A;
	uint32_t reg;

	if (nfd0_on_d16)
		value |= SFR_CCFG_EBICSA_NFD0_ON_D16;

	reg = SFR->SFR_CCFG_EBICSA;
	reg = (reg & ~mask) | value;
	SFR->SFR_CCFG_EBICSA = reg;
}

void board_cfg_ddram(void)
{
#ifdef BOARD_DDRAM_TYPE
	struct _mpddrc_desc desc;
	board_cfg_matrix_for_ddr();
	ddram_init_descriptor(&desc, BOARD_DDRAM_TYPE);
	ddram_configure(&desc);
#endif
#ifdef BOARD_SDRAM_TYPE
	struct _sdramc_desc desc;
	board_cfg_matrix_for_sdr();
	sdram_init_descriptor(&desc, BOARD_SDRAM_TYPE);
	sdram_configure(&desc);
#endif
}

#ifdef CONFIG_HAVE_NAND_FLASH
void board_cfg_nand_flash(void)
{
#if defined(BOARD_NANDFLASH_PINS) && defined(BOARD_NANDFLASH_BUS_WIDTH)
	const struct _pin pins_nandflash[] = BOARD_NANDFLASH_PINS;
	pio_configure(pins_nandflash, ARRAY_SIZE(pins_nandflash));
	board_cfg_matrix_for_nand();
	smc_nand_configure(BOARD_NANDFLASH_BUS_WIDTH);
#else
	trace_fatal("Cannot configure NAND: target board has no NAND definitions!");
#endif
}
#endif /* CONFIG_HAVE_NAND_FLASH */

#if defined(BOARD_SDMMC0_PINS) || defined(BOARD_SDMMC1_PINS)
static void board_cfg_sd_clk_caps(uint32_t periph_id, uint32_t *caps0)
{
		uint32_t base_freq, mult_freq, val;

		/* Retrieve the frequency of MULTCLK.
		 * Usual values of this frequency are 100 MHz, 104 MHz. */
		mult_freq = pmc_get_gck_clock(periph_id);

		/* Retrieve the frequency of BASECLK and TEOCLK.
		 * Usual values of this frequency are 50 MHz, 52 MHz. */
		base_freq = ROUND_INT_DIV(mult_freq, 2 * 1000000lu);
		val = base_freq > (SDMMC_CA0R_BASECLKF_Msk >> SDMMC_CA0R_BASECLKF_Pos)
		    ? 0 : base_freq;
		*caps0 |= SDMMC_CA0R_BASECLKF(val);
		val = base_freq > (SDMMC_CA0R_TEOCLKF_Msk >> SDMMC_CA0R_TEOCLKF_Pos)
		    ? 0 : base_freq;
		*caps0 |= SDMMC_CA0R_TEOCLKF(val) | SDMMC_CA0R_TEOCLKU;
}
#endif

bool board_cfg_sdmmc(uint32_t periph_id)
{
	switch (periph_id) {
	case ID_SDMMC0:
	{
#if defined(BOARD_SDMMC0_CAPS0) && defined(BOARD_SDMMC0_PINS)
		struct _pin pins[] = BOARD_SDMMC0_PINS;
		uint32_t caps0 = BOARD_SDMMC0_CAPS0;
#ifdef BOARD_SDMMC0_PIO_ATTR
		uint8_t ix;
#endif

		/* Program capabilities for SDMMC0 */
		board_cfg_sd_clk_caps(ID_SDMMC0, &caps0);
		sdmmc_set_capabilities(SDMMC0, caps0, SDMMC_CA0R_SLTYPE_Msk |
		    SDMMC_CA0R_V18VSUP | SDMMC_CA0R_V30VSUP | SDMMC_CA0R_V33VSUP |
		    SDMMC_CA0R_BASECLKF_Msk | SDMMC_CA0R_TEOCLKU |
		    SDMMC_CA0R_TEOCLKF_Msk, 0, 0);

		/* Configure SDMMC0 pins */
#ifdef BOARD_SDMMC0_PIO_ATTR
		/* Tune the attributes of CMD, CK and DAT* peripheral outputs */
		for (ix = 0; ix < ARRAY_SIZE(pins); ix++) {
			if (pins[ix].type == PIO_INPUT)
				continue;
			pins[ix].attribute |= BOARD_SDMMC0_PIO_ATTR;
		}
#endif
		pio_configure(pins, ARRAY_SIZE(pins));
		return true;
#else
		trace_fatal("Cannot configure SDMMC0: target board has no SDMMC0 definitions!");
		return false;
#endif
	}
	case ID_SDMMC1:
	{
#if defined(BOARD_SDMMC1_CAPS0) && defined(BOARD_SDMMC1_PINS)
		struct _pin pins[] = BOARD_SDMMC1_PINS;
		uint32_t caps0 = BOARD_SDMMC1_CAPS0;
#ifdef BOARD_SDMMC1_PIO_ATTR
		uint8_t ix;
#endif

		/* Program capabilities for SDMMC1 */
		board_cfg_sd_clk_caps(ID_SDMMC1, &caps0);
		sdmmc_set_capabilities(SDMMC1, caps0, SDMMC_CA0R_SLTYPE_Msk |
		    SDMMC_CA0R_V18VSUP | SDMMC_CA0R_V30VSUP | SDMMC_CA0R_V33VSUP |
		    SDMMC_CA0R_BASECLKF_Msk | SDMMC_CA0R_TEOCLKU |
		    SDMMC_CA0R_TEOCLKF_Msk, 0, 0);

		/* Configure SDMMC1 pins */
#ifdef BOARD_SDMMC1_PIO_ATTR
		/* Tune the attributes of CMD, CK and DAT* peripheral outputs */
		for (ix = 0; ix < ARRAY_SIZE(pins); ix++) {
			if (pins[ix].type == PIO_INPUT)
				continue;
			pins[ix].attribute |= BOARD_SDMMC1_PIO_ATTR;
		}
#endif
		pio_configure(pins, ARRAY_SIZE(pins));
		return true;
#else
		trace_fatal("Cannot configure SDMMC1: target board has no SDMMC1 definitions!");
		return false;
#endif
	}
	default:
		return false;
	}
}

bool board_get_sdmmc_card_detect_status(uint32_t periph_id)
{
	const struct _pin *cd_input = NULL;

#ifdef BOARD_SDMMC0_PIN_CD
	const struct _pin cd0_input = BOARD_SDMMC0_PIN_CD;
	cd_input = periph_id == ID_SDMMC0 ? &cd0_input : cd_input;
#endif

#ifdef BOARD_SDMMC1_PIN_CD
	const struct _pin cd1_input = BOARD_SDMMC1_PIN_CD;
	cd_input = periph_id == ID_SDMMC1 ? &cd1_input : cd_input;
#endif

	if (periph_id != ID_SDMMC0 && periph_id != ID_SDMMC1)
		return false;

	/* No detection; assume the card/device is always present */
	if (!cd_input)
		return true;

	return pio_get(cd_input) ? false : true;
}
