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
#include "timer.h"

#include "peripherals/aic.h"
#include "peripherals/l2cc.h"
#include "peripherals/lcdc.h"
#include "peripherals/matrix.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/smc.h"
#include "peripherals/wdt.h"

#include "memories/ddram.h"

#include "misc/cache.h"
#include "misc/console.h"
#include "misc/led.h"

#include "timer.h"

#include "board_support.h"

#ifdef CONFIG_HAVE_PMIC_ACT8865
#include "power/act8865.h"
#endif

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

#ifdef PINS_LEDS
static struct _pin pins_leds[] = PINS_LEDS;
#endif

static const char* board_name = BOARD_NAME;

#ifdef CONFIG_HAVE_PMIC_ACT8865
static struct _twi_desc act8865_twid = {
	.addr = BOARD_ACT8865_ADDR,
	.freq = BOARD_ACT8865_FREQ,
	.transfer_mode = TWID_MODE_POLLING
};

static struct _act8865 pmic = {
	.twid = &act8865_twid,
	.addr = BOARD_ACT8865_TWI_ADDR,
};
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

ALIGNED(16384) static uint32_t tlb[4096];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static bool board_cfg_sd_dev_pins(uint32_t periph_id, bool down, bool up)
{
	struct _pin *dev_pins = NULL;
	uint32_t count = 0, pin_ix;
#ifdef BOARD_HSMCI0_DEV_PINS
	struct _pin dev0_pins[] = BOARD_HSMCI0_DEV_PINS;
	dev_pins = periph_id == ID_HSMCI0 ? dev0_pins : dev_pins;
	count = periph_id == ID_HSMCI0 ? ARRAY_SIZE(dev0_pins) : count;
#endif
#ifdef BOARD_HSMCI1_DEV_PINS
	struct _pin dev1_pins[] = BOARD_HSMCI1_DEV_PINS;
	dev_pins = periph_id == ID_HSMCI1 ? dev1_pins : dev_pins;
	count = periph_id == ID_HSMCI1 ? ARRAY_SIZE(dev1_pins) : count;
#endif

	if (count == 0)
		return false;
	for (pin_ix = 0; (down || up) && pin_ix < count; pin_ix++) {
		dev_pins[pin_ix].type = up ? PIO_OUTPUT_1 : PIO_OUTPUT_0;
		dev_pins[pin_ix].attribute = PIO_DEFAULT;
	}
	pio_configure(dev_pins, count);
	return true;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_board_name(void)
{
	return board_name;
}

void board_cfg_clocks(void)
{
	pmc_select_external_osc();
	pmc_switch_mck_to_main();
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		     CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(87) |
		     CKGR_PLLAR_DIVA_BYPASS, PMC_PLLICPR_IPLL_PLLA(0x0));
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
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
	const struct _pin console_pins[] = { PIN_USART3_TXD, PIN_USART3_RXD };
	pio_configure(console_pins, 2);
	console_configure(USART3, baudrate);
#endif
}

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
#ifdef CONFIG_HAVE_SMD
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_SMD);
#endif
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

	/* Internal SRAM */
	matrix_configure_slave_sec(MATRIX0,
			H64MX_SLAVE_SRAM, 0, 0, 0);
	matrix_set_slave_region_size(MATRIX0,
			H64MX_SLAVE_SRAM, MATRIX_AREA_128K, 0x1);
	matrix_set_slave_split_addr(MATRIX0,
			H64MX_SLAVE_SRAM, MATRIX_AREA_64K, 0x1);

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
	matrix_remove_write_protection(MATRIX0);
	matrix_remove_write_protection(MATRIX1);

	/* Internal SRAM */
	matrix_configure_slave_sec(MATRIX0,
			H64MX_SLAVE_SRAM, 0x1, 0x1, 0x1);
	matrix_set_slave_split_addr(MATRIX0,
			H64MX_SLAVE_SRAM, MATRIX_AREA_128K, 0x1);
	matrix_set_slave_region_size(MATRIX0,
			H64MX_SLAVE_SRAM, MATRIX_AREA_128K, 0x1);

	/* NFC Command Register */
	matrix_configure_slave_sec(MATRIX1,
			H32MX_SLAVE_NFC_CMD, 0xff, 0xff, 0xff);
	matrix_set_slave_split_addr(MATRIX1,
			H32MX_SLAVE_NFC_CMD, MATRIX_AREA_8M, 0xff);
	matrix_set_slave_region_size(MATRIX1,
			H32MX_SLAVE_NFC_CMD, MATRIX_AREA_8M, 0xff);

	/* NFC SRAM */
	matrix_configure_slave_sec(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, 0xff,0xff,0xff);
	matrix_set_slave_split_addr(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, MATRIX_AREA_128M, 0x4f);
	matrix_set_slave_region_size(MATRIX1,
			H32MX_SLAVE_NFC_SRAM, MATRIX_AREA_8K, 0x1);

	MATRIX1->MATRIX_MEIER = 0x3ff;
}


void board_cfg_ddram(void)
{
#ifdef BOARD_DDRAM_TYPE
	board_cfg_matrix_for_ddr();
	struct _mpddrc_desc desc;
	ddram_init_descriptor(&desc, BOARD_DDRAM_TYPE);
	ddram_configure(&desc, ID_TC0, 0);
#else
	trace_fatal("Cannot configure DDRAM: target board have no DDRAM type definition!");
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

void board_cfg_nor_flash(void)
{
#if defined(BOARD_NORFLASH_CS) && defined(BOARD_NORFLASH_BUS_WIDTH)
	smc_nor_configure(BOARD_NORFLASH_CS, BOARD_NORFLASH_BUS_WIDTH);
#else
	trace_fatal("Cannot configure NOR: target board have no NOR definitions!");
#endif
}

void board_cfg_pmic()
{
#ifdef CONFIG_HAVE_PMIC_ACT8865
	struct _pin act8865_pins[] = BOARD_ACT8865_PINS;

	/* configure and enable the PMIC TWI */
	pio_configure(act8865_pins, ARRAY_SIZE(act8865_pins));
	twid_configure(pmic.twid);

	/* check PMIC chip presence */
	if (act8865_check_twi_status(&pmic)) {
#if defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
		/* Setup PMIC output 5 to 3.3V (VDDANA) */
		act8865_set_reg_voltage(&pmic, REG5_0, ACT8865_3V3);
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
		/* Setup PMIC output 5 to 3.3V (VDDANA, 3V3_AUDIO) */
		act8865_set_reg_voltage(&pmic, REG5_0, ACT8865_3V3);
		/* Setup PMIC output 6 to 1.8V (1V8_AUDIO) */
		act8865_set_reg_voltage(&pmic, REG6_0, ACT8865_1V8);
#endif
	} else {
		trace_error("Error initializing ACT8865 PMIC\n\r");
		return;
	}
#endif
}

#ifdef CONFIG_HAVE_ISI
void board_cfg_isi(void)
{
	const struct _pin pins_isi[]= BOARD_ISI_PINS;
	const struct _pin pin_rst = BOARD_ISI_RST_PIN;
	const struct _pin pin_pwd = BOARD_ISI_PWD_PIN;

	/* Configure ISI pins */
	pio_configure(pins_isi, ARRAY_SIZE(pins_isi));

	/* Configure PMC programmable clock (PCK1) */
	pmc_configure_pck(1, PMC_PCK_CSS_MCK_CLK, 3);
	pmc_enable_pck(1);

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

bool board_cfg_sdmmc(uint32_t periph_id)
{
	switch (periph_id) {
	case ID_HSMCI0:
	{
#ifdef BOARD_HSMCI0_PINS
		const struct _pin pins[] = BOARD_HSMCI0_PINS;

		/* Configure HSMCI0 pins */
		pio_configure(pins, ARRAY_SIZE(pins));
		return true;
#else
		trace_fatal("Target board misses HSMCI0 pins");
		return false;
#endif
	}
	case ID_HSMCI1:
	{
#ifdef BOARD_HSMCI1_PINS
		const struct _pin pins[] = BOARD_HSMCI1_PINS;

		/* Configure HSMCI1 pins */
		pio_configure(pins, ARRAY_SIZE(pins));
		return true;
#else
		trace_fatal("Target board misses HSMCI1 pins");
		return false;
#endif
	}
	default:
		return false;
	}
}

bool board_is_sdmmc_inserted(uint32_t periph_id)
{
	const struct _pin *cd_input = NULL;
	bool res;
#ifdef BOARD_HSMCI0_PIN_CD
	const struct _pin cd0_input = BOARD_HSMCI0_PIN_CD;
	cd_input = periph_id == ID_HSMCI0 ? &cd0_input : cd_input;
#endif
#ifdef BOARD_HSMCI1_PIN_CD
	const struct _pin cd1_input = BOARD_HSMCI1_PIN_CD;
	cd_input = periph_id == ID_HSMCI1 ? &cd1_input : cd_input;
#endif

	if (!cd_input)
		return false;
#ifdef CONFIG_BOARD_SAMA5D4_EK
	/* HW erratum affecting the HSMCI1 slot of the SAMA5D4-EK board;
	 * card detection status is valid only when power is supplied to
	 * the microSD connector. */
	const struct _pin pwr_sig = BOARD_HSMCI1_PIN_POWER;
	const bool powered = periph_id == ID_HSMCI1
		? (pio_get(&pwr_sig) ? false : true) : true;
	if (!powered)
		if (!board_power_sdmmc_device(periph_id, true))
			return false;
#endif
	res = pio_get(cd_input) ? false : true;
#ifdef CONFIG_BOARD_SAMA5D4_EK
	if (!powered)
		board_power_sdmmc_device(periph_id, false);
#endif
	return res;
}

bool board_power_sdmmc_device(uint32_t periph_id, bool on)
{
	const struct _pin *pwr_ctrl = NULL;
#ifdef BOARD_HSMCI0_PIN_POWER
	const struct _pin pwr0_ctrl = BOARD_HSMCI0_PIN_POWER;
	pwr_ctrl = periph_id == ID_HSMCI0 ? &pwr0_ctrl : pwr_ctrl;
#endif
#ifdef BOARD_HSMCI1_PIN_POWER
	const struct _pin pwr1_ctrl = BOARD_HSMCI1_PIN_POWER;
	pwr_ctrl = periph_id == ID_HSMCI1 ? &pwr1_ctrl : pwr_ctrl;
#endif

	if (periph_id != ID_HSMCI0 && periph_id != ID_HSMCI1)
		return false;
	if (!pwr_ctrl)
		/* This slot doesn't support switching VDD off */
		return on;
	if (on) {
		/* Workaround HW issue affecting SAMA5D4-EK and SAMA5D4-XULT;
		 * flipping straight the VDD switch often causes the VCC_3V3
		 * rail to drop and trigger reset upon under-voltage. */
		board_cfg_sd_dev_pins(periph_id, false, true);
		timer_sleep(100);
		pio_clear(pwr_ctrl);
		/* Wait for the VDD rail to settle at nominal voltage */
		timer_sleep(1);
		board_cfg_sd_dev_pins(periph_id, false, false);
		timer_sleep(1);
	} else {
		pio_set(pwr_ctrl);
		/* Drive all device signals low, in an attempt to have VDD
		 * falling quicker. This also workarounds the unswitched pull-up
		 * resistors found on the SAMA5D4-XULT board. */
		board_cfg_sd_dev_pins(periph_id, true, false);
	}
	return true;
}

#ifdef CONFIG_HAVE_SSC
void board_cfg_ssc(void)
{
#ifdef BOARD_SSC0_PINS
	const struct _pin pins_ssc0[] = BOARD_SSC0_PINS;
	pio_configure(pins_ssc0, ARRAY_SIZE(pins_ssc0));
#endif
#ifdef BOARD_SSC1_PINS
	const struct _pin pins_ssc1[] = BOARD_SSC1_PINS;
	pio_configure(pins_ssc1, ARRAY_SIZE(pins_ssc1));
#endif
}
#endif /* CONFIG_HAVE_SSC */
