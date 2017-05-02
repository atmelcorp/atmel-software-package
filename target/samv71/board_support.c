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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_timer.h"
#include "timer.h"
#include "trace.h"

#include "arm/mpu_armv7m.h"
#include "extram/ddram.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "irqflags.h"
#include "mm/cache.h"
#include "mm/l1cache.h"
#include "nvm/flash/eefc.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const char* board_name = BOARD_NAME;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static bool board_cfg_sd_dev_pins(uint32_t periph_id, bool down, bool up)
{
	struct _pin *dev_pins = NULL;
	uint32_t count = 0, pin;

#ifdef BOARD_HSMCI0_DEV_PINS
	struct _pin dev0_pins[] = BOARD_HSMCI0_DEV_PINS;
	if (periph_id == ID_HSMCI0) {
		dev_pins = dev0_pins;
		count = ARRAY_SIZE(dev0_pins);
	}
#endif

	if (count == 0)
		return false;

	for (pin = 0; (down || up) && pin < count; pin++) {
		dev_pins[pin].type = up ? PIO_OUTPUT_1 : PIO_OUTPUT_0;
		dev_pins[pin].attribute = PIO_DEFAULT;
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
	struct _pmc_plla_cfg plla_config = {
		.mul = 49,
		.div = 1,
		.count = 0x3f,
	};
	eefc_set_flash_wait_states(EEFC, get_flash_wait_states(300000000));
	pmc_switch_mck_to_slck();
	pmc_disable_plla();
	pmc_select_external_osc(false);
	pmc_configure_plla(&plla_config);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK_DIV2);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV2);
	pmc_switch_mck_to_pll();
}

void board_cfg_lowlevel(bool clocks, bool ddram, bool mpu)
{
	/* Disable Watchdog */
	wdt_disable();

	/* Configure PB4/PB5 as PIO instead of JTAG */
	MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5;

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Set external oscillator frequency */
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

	if (mpu) {
		/* Configure MPU */
		board_cfg_mpu();
	}
}

void board_cfg_mpu(void)
{
	const uint32_t mpu_regions[] = {
		/* ITCM, 0x0-0x400000, 4MB=2^22 */
		MPU_REGION(0, 0x0),
		MPU_REGION_SIZE(21) |
		MPU_AP_READONLY |
		MPU_ATTR_NORMAL_WB |
		MPU_ATTR_ENABLE,

		/* Internal flash, 0x400000-0x800000, 4MB=2^22 */
		MPU_REGION(1, 0x400000),
		MPU_REGION_SIZE(21) |
		MPU_AP_READONLY |
		MPU_ATTR_NORMAL_WB |
		MPU_ATTR_ENABLE,

		/* DTCM, 0x20000000-0x20400000, 4MB=2^22 */
		MPU_REGION(2, 0x20000000),
		MPU_REGION_SIZE(21) |
		MPU_AP_READWRITE |
		MPU_ATTR_NORMAL_WB_WA |
		MPU_ATTR_ENABLE,

		/* SRAM, 0x20400000-0x20C00000, 8MB=2^23 */
		MPU_REGION(3, 0x20400000),
		MPU_REGION_SIZE(22) |
		MPU_AP_READWRITE |
		MPU_ATTR_NORMAL_WB_WA |
		MPU_ATTR_ENABLE,

		/* Not Cached SRAM, 0x2045F000-0x20460000, 4KB=2^12 */
		MPU_REGION(4, 0x2045F000),
		MPU_REGION_SIZE(11) |
		MPU_AP_READWRITE |
		MPU_ATTR_NORMAL |
		MPU_ATTR_ENABLE,

		/* Peripherals,  0x40000000, 256MB=2^28 */
		MPU_REGION(5, 0x40000000),
		MPU_REGION_SIZE(27) |
		MPU_AP_READWRITE |
		MPU_ATTR_DEVICE |
		MPU_ATTR_EXECUTE_NEVER |
		MPU_ATTR_ENABLE,

		/* EBI, 0x60000000, 256MB=2^28 */
		MPU_REGION(6, 0x60000000),
		MPU_REGION_SIZE(27) |
		MPU_AP_READWRITE |
		MPU_ATTR_STRONGLY_ORDERED |
		MPU_ATTR_EXECUTE_NEVER |
		MPU_ATTR_ENABLE,

		/* SDRAM, 0x70000000, 256MB=2^28 */
		MPU_REGION(7, 0x70000000),
		MPU_REGION_SIZE(27) |
		MPU_AP_READWRITE |
		MPU_ATTR_NORMAL_WB |
		MPU_ATTR_ENABLE,

		/* QSPI, 0x80000000, 256MB=2^28 */
		MPU_REGION(8, 0x80000000),
		MPU_REGION_SIZE(27) |
		MPU_AP_READWRITE |
		MPU_ATTR_STRONGLY_ORDERED |
		MPU_ATTR_ENABLE,

		/* USB RAM, 0xA0100000, 1MB=2^20 */
		MPU_REGION(9, 0xA0100000),
		MPU_REGION_SIZE(19) |
		MPU_AP_READWRITE |
		MPU_ATTR_DEVICE |
		MPU_ATTR_EXECUTE_NEVER |
		MPU_ATTR_ENABLE,

		/* Private Peripheral Bus, 0xE0000000, 1MB=2^20 */
		MPU_REGION(10, 0xE0000000),
		MPU_REGION_SIZE(19) |
		MPU_AP_READWRITE |
		MPU_ATTR_STRONGLY_ORDERED |
		MPU_ATTR_EXECUTE_NEVER |
		MPU_ATTR_ENABLE,

		/* end marker */
		0, 0
	};

	if (mpu_is_enabled())
		return;

	/* Enable MPU, I-Cache and D-Cache */
	mpu_configure(mpu_regions);
	mpu_enable();
	icache_enable();
	dcache_enable();
}

void board_cfg_mpu_for_flash_write(void)
{
	const uint32_t flash_region[] = {
		/* Internal flash, 0x400000-0x800000, 4MB=2^22 */
		MPU_REGION(1, 0x400000),
		MPU_REGION_SIZE(21) |
		MPU_AP_READWRITE |
		MPU_ATTR_STRONGLY_ORDERED |
		MPU_ATTR_ENABLE,

		/* end marker */
		0, 0
	};

	if (!mpu_is_enabled())
		return;

	mpu_configure(flash_region);
}

void board_cfg_mpu_for_flash_read(void)
{
	const uint32_t flash_region[] = {
		/* Internal flash, 0x400000-0x800000, 4MB=2^22 */
		MPU_REGION(1, 0x400000),
		MPU_REGION_SIZE(21) |
		MPU_AP_READONLY |
		MPU_ATTR_NORMAL_WB |
		MPU_ATTR_ENABLE,

		/* end marker */
		0, 0
	};

	if (!mpu_is_enabled())
		return;

	mpu_configure(flash_region);
	cache_invalidate_region((void*)0x400000, 1u << 22);
}

void board_cfg_matrix_for_ddr(void)
{
	MATRIX->CCFG_SMCNFCS = CCFG_SMCNFCS_SDRAMEN;
}

void board_cfg_ddram(void)
{
#ifdef BOARD_DDRAM_TYPE
#ifdef BOARD_DDRAM_PINS
	const struct _pin ddram_pins[] = BOARD_DDRAM_PINS;
	pio_configure(ddram_pins, ARRAY_SIZE(ddram_pins));
#endif
	board_cfg_matrix_for_ddr();
	struct _mpddrc_desc desc;
	ddram_init_descriptor(&desc, BOARD_DDRAM_TYPE);
	ddram_configure(&desc);
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
	default:
		return false;
	}
}

bool board_get_hsmci_card_detect_status(uint32_t periph_id)
{
	const struct _pin *cd_input = NULL;

#ifdef BOARD_HSMCI0_PIN_CD
	const struct _pin cd0_input = BOARD_HSMCI0_PIN_CD;
	cd_input = periph_id == ID_HSMCI0 ? &cd0_input : cd_input;
#endif

	if (periph_id != ID_HSMCI0)
		return false;

	/* no detection, assume card is always present */
	if (!cd_input)
		return true;

	return pio_get(cd_input) ? false : true;
}

bool board_set_hsmci_card_power(uint32_t periph_id, bool on)
{
	const struct _pin *pwr_ctrl = NULL;

#ifdef BOARD_HSMCI0_PIN_POWER
	const struct _pin pwr0_ctrl = BOARD_HSMCI0_PIN_POWER;
	pwr_ctrl = periph_id == ID_HSMCI0 ? &pwr0_ctrl : pwr_ctrl;
#endif

	if (periph_id != ID_HSMCI0)
		return false;

	/* This slot doesn't support switching VDD on/off */
	if (!pwr_ctrl)
		return false;

	if (on) {
		/*
		 * Workaround HW issue: flipping straight the VDD switch often
		 * causes the VCC_3V3 rail to drop and trigger reset upon
		 * under-voltage.
		 */
		board_cfg_sd_dev_pins(periph_id, false, true);
		msleep(100);
		pio_clear(pwr_ctrl);
		/* Wait for the VDD rail to settle at nominal voltage */
		msleep(1);
		board_cfg_sd_dev_pins(periph_id, false, false);
		msleep(1);
	} else {
		pio_set(pwr_ctrl);
		/*
		 * Drive all device signals low, in an attempt to have VDD
		 * falling quicker.
		 */
		board_cfg_sd_dev_pins(periph_id, true, false);
	}

	return true;
}
