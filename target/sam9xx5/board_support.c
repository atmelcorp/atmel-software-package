/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
#ifdef CONFIG_HAVE_LCDC
#include "peripherals/lcdc.h"
#endif
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/smc.h"
#include "peripherals/wdt.h"

#include "bus/twi-bus.h"

#include "memories/ddram.h"

#include "misc/cache.h"
#include "misc/console.h"
#include "misc/led.h"

#include "timer.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

#ifdef PINS_LEDS
static struct _pin pins_leds[] = PINS_LEDS;
#endif

static const char* board_name = BOARD_NAME;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

SECTION(".region_ddr") ALIGNED(16384) static uint32_t tlb[4096];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_board_name(void)
{
	return board_name;
}

void board_cfg_clocks(void)
{
	pmc_switch_mck_to_main();
	/* Disable PLLA */
	pmc_set_plla(0, 0);
	pmc_select_external_osc();
	/* Configure PLLA */
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(199) |
		CKGR_PLLAR_DIVA(3), 0);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	//pmc_set_mck_divider(PMC_MCKR_MDIV_EQ_PCK);
	pmc_switch_mck_to_pll();
}

void board_cfg_lowlevel(bool clocks, bool ddram, bool mmu)
{
	/* Disable Watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Set the external clock values */
	pmc_set_oscillators(BOARD_SLOW_CLOCK_EXT_OSC, BOARD_MAIN_CLOCK_EXT_OSC);

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

/**
 * \brief Configure the board console if any
 */
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
	/* default console port used by ROM-code */
	const struct _pin console_pins[] = PINS_DBGU;
	pio_configure(console_pins, ARRAY_SIZE(console_pins));
	console_configure(DBGU, baudrate);
#endif
}

#if 0
void board_restore_pio_reset_state(void)
{
	int i;

	/* all pins, excluding JTAG and NTRST */
	struct _pin pins[] = {
		{ PIO_GROUP_A, 0xFFFEFEFE, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_B, 0xFCFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_C, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
		{ PIO_GROUP_D, 0xFFFFFFFF, PIO_INPUT, PIO_PULLUP },
	};

	/* For low_power_mode example, power consumption results can be affected
	* by IOs setting. To generate power consumption numbers in datasheet,
	* most IOs must be disconnected from external devices just like on
	* VB board. Then putting IOs to reset state are OK.
	*/

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

	/* disable system clocks */
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_LCD);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_SMD);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_UHP);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_UDP);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK0);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK1);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK2);
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_ISC);

	/* disable all peripheral clocks except PIOA for JTAG, serial debug port */
	for (i = ID_PIT; i < ID_PERIPH_COUNT; i++) {
		if (i == ID_PIOA)
			continue;
		pmc_disable_peripheral(i);
	}
}
#endif

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

	/* 0x00300000: SRAM */
	tlb[0x003] = TTB_SECT_ADDR(0x00300000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

	/* 0x00400000: SMD */
	tlb[0x004] = TTB_SECT_ADDR(0x00400000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_SECT_SBO
	           | TTB_TYPE_SECT;

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
	cp15_icache_enable();
	cp15_mmu_enable();
	cp15_dcache_enable();
}

void board_cfg_l2cc(void)
{
	/* N/A on SAM9 */
}

void board_cfg_matrix_for_ddr(void)
{
	uint32_t csa = MATRIX->MATRIX_EBICSA;
	csa |= MATRIX_EBICSA_EBI_CS1A_DDRC;
	csa &= ~MATRIX_EBICSA_EBI_DBPUC;
	csa |= MATRIX_EBICSA_EBI_DBPDC;
	csa |= MATRIX_EBICSA_EBI_DRIVE_HIGH;
	MATRIX->MATRIX_EBICSA = csa;
}

void board_cfg_matrix_for_nand(void)
{
	uint32_t csa = MATRIX->MATRIX_EBICSA;
	csa |= MATRIX_EBICSA_EBI_CS3A_NAND;
	csa |= MATRIX_EBICSA_DDR_MP_EN; /* only on CM Rev. B */
	csa |= MATRIX_EBICSA_NFD0_ON_D16; /* only on CM Rev. B */
	csa &= ~MATRIX_EBICSA_EBI_DRIVE;
	MATRIX->MATRIX_EBICSA = csa;
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
	board_cfg_matrix_for_nand();
	const struct _pin pins_nandflash[] = BOARD_NANDFLASH_PINS;
	pio_configure(pins_nandflash, ARRAY_SIZE(pins_nandflash));
	smc_nand_configure(BOARD_NANDFLASH_BUS_WIDTH);
#else
	trace_fatal("Cannot configure NAND: target board have no NAND definitions!");
#endif
}
#endif /* CONFIG_HAVE_NAND_FLASH */

#ifdef CONFIG_HAVE_ISI
void board_cfg_isi(void)
{
	const struct _pin pins_isi[]= BOARD_ISI_PINS;
	const struct _pin pin_rst = BOARD_ISI_RST_PIN;
	const struct _pin pin_pwd = BOARD_ISI_PWD_PIN;

	/* Configure ISI pins */
	pio_configure(pins_isi, ARRAY_SIZE(pins_isi));

	/* Reset sensor */
	pio_configure(&pin_rst,1);
	pio_configure(&pin_pwd,1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
	timer_wait(10);

	/* Enable ISI peripheral clock */
	pmc_enable_peripheral(ID_ISI);
}
#endif

#ifdef CONFIG_HAVE_LCDC
void board_cfg_lcd(void)
{
#ifdef BOARD_LCD_PINS
	const struct _pin pins_lcd[] = BOARD_LCD_PINS;
	const struct _lcdc_desc lcd_desc = {
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
	lcdc_configure(&lcd_desc);
#endif
}
#endif

void board_cfg_led(void)
{
#ifdef PINS_LEDS
	led_configure(pins_leds, ARRAY_SIZE(pins_leds));
#endif
}

void board_cfg_twi_bus(void)
{
#ifdef BOARD_TWI_BUS0
	const struct _pin pins_twi_bus0[] = BOARD_TWI_BUS0_PINS;
	pio_configure(pins_twi_bus0, ARRAY_SIZE(pins_twi_bus0));
	twi_bus_configure(0, BOARD_TWI_BUS0, BOARD_TWI_BUS0_FREQ, TWID_MODE_POLLING);
#endif
#ifdef BOARD_TWI_BUS1
	const struct _pin pins_twi_bus1[] = BOARD_TWI_BUS1_PINS;
	pio_configure(pins_twi_bus1, ARRAY_SIZE(pins_twi_bus1));
	twi_bus_configure(1, BOARD_TWI_BUS1, BOARD_TWI_BUS1_FREQ, TWID_MODE_DMA);
#endif
#ifdef BOARD_TWI_BUS2
	const struct _pin pins_twi_bus2[] = BOARD_TWI_BUS2_PINS;
	pio_configure(pins_twi_bus2, ARRAY_SIZE(pins_twi_bus2));
	twi_bus_configure(2, BOARD_TWI_BUS2, BOARD_TWI_BUS2_FREQ, TWID_MODE_DMA);
#endif
}
