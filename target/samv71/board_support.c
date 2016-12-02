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
#include "trace.h"
#include "timer.h"

#include "extram/ddram.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "nvm/eefc.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "serial/console.h"

#include "board_support.h"

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

static const char* board_name = BOARD_NAME;

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
	eefc_set_flash_wait_states(get_flash_wait_states(6));
	pmc_select_external_osc();
	pmc_configure_plla(&plla_config);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK_DIV2);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV2);
	pmc_switch_mck_to_pll();
}

void board_cfg_lowlevel(bool clocks, bool ddram, bool mpu)
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
	irq_initialize();

	/* Configure system timer */
	board_cfg_timer();

	if (ddram) {
		/* Configure DDRAM */
		board_cfg_ddram();
	}
}

void board_cfg_timer(void)
{
	struct _timer __timer = {
		.tc = BOARD_TIMER_TC,
		.channel = BOARD_TIMER_CHANNEL,
		.freq = BOARD_TIMER_FREQ,
		.resolution = BOARD_TIMER_RESOLUTION,
		.tick = 0,
	};

	timer_configure(&__timer);
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
	const struct _pin console_pins[] = PINS_UART0;
	pio_configure(console_pins, ARRAY_SIZE(console_pins));
	console_configure(UART0, baudrate);
#endif
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
