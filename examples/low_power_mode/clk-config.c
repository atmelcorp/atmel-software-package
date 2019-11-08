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

#include "clk-config.h"
#include "event-config.h"

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
#ifdef CONFIG_SOC_SAM9XX5
#define EVENT RTC_INT
#else
#define EVENT USER_BTN | RTC_INT
#endif

struct test_mode test_setting[] = {
	{
		.name = "idle",
		.mode = IDLE,
		.event = EVENT,
		/* PCK = MCK = BOARD_OSC */
		.clock_test_setting = {
			.pck_input = (uint32_t)NULL,
			.extosc = NULL,
			.ext32k = NULL,
			.plla = {
				.mul = (uint32_t)NULL,
			},
			.pck_pres = (uint32_t)NULL,
			.mck_div = (uint32_t)NULL,
		},
	},

	{
		.name = "ulp0_osc",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = BOARD_OSC */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
#if defined(CONFIG_SOC_SAM9X60)
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#else
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#endif
		},
	},

	{
		.name = "ulp0_OSC/16",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = BOARD_OSC/16 */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK_DIV16,
#if defined(CONFIG_SOC_SAM9X60)
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#else
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#endif
		},
	},

	{
		.name = "ulp0_OSC/64",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = BOARD_OSC/64 */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
#if defined(CONFIG_SOC_SAM9X60)
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#else
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#endif
		},
	},

	{
		.name = "ulp0_32.768kHz",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = 32.768 kHz */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_SLOW_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
#if defined(CONFIG_SOC_SAM9X60)
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#else
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#endif
		},
	},	

	{
		.name = "ulp0_512Hz",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = 32768/64 = 512 Hz */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_SLOW_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		},
	},

	{
		.name = "ulp0_rc_12MHz",
		.mode = ULP0,
		.event = EVENT,
		/* PCK = MCK = 12 MHz (RC) */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = false,
			.ext32k = false,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
#if defined(CONFIG_SOC_SAM9X60)
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#else
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
#endif
		},
	},

	{
		.name = "ulp0_plla/3",
		.mode = ULP0,
		.event = EVENT,
		/* PLLA = BOARD_OSC*50/2, PCK = PLLA, MCK = PCK/3 */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_PLLA_CLK,
			.extosc = true,
			.ext32k = true,
			.plla = {
				.mul = 49,
				.div = 1,
				.count = 0x3f,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
#ifdef CONFIG_HAVE_PMC_PLLADIV2
			.plla_div2 = true,
#endif
#ifdef CONFIG_HAVE_PMC_H32MXDIV
			.h32mx_div2 = true,
#endif
		},
	},
#if defined(CONFIG_SOC_SAMA5D2)
	{
		.name = "ulp1_rc_12MHz",
		.mode = ULP1,
		.event = RTC_ALARM | WAKE_UP,
		/* PCK = MCK = 12 MHz (RC) */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = false,
			.ext32k = false,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
			.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		},
	},
#elif defined(CONFIG_SOC_SAM9X60)
	{
		.name = "ulp1_rc_12MHz",
		.mode = ULP1,
		.event = RTC_ALARM,
		/* PCK = MCK = 12 MHz (RC) */
		.clock_test_setting = {
			.pck_input = PMC_MCKR_CSS_MAIN_CLK,
			.extosc = false,
			.ext32k = false,
			.plla = {
				.mul = 0,
			},
			.pck_pres = PMC_MCKR_PRES_CLOCK,
			.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		},
	},	
#endif
	{
		.name = NULL,
		.mode = (uint32_t)NULL,
		.event = (uint32_t)NULL,
		/* PCK = MCK = BOARD_OSC */
		.clock_test_setting = {
			.pck_input = (uint32_t)NULL,
			.extosc = NULL,
			.ext32k = NULL,
			.plla = {
				.mul = (uint32_t)NULL,
			},
			.pck_pres = (uint32_t)NULL,
			.mck_div = (uint32_t)NULL,
		},
	},
};
