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

#include "board.h"
#include "clk-config.h"

struct pck_mck_cfg clock_test_setting[8] = {
	/* PLLA = BOARD_OSC*(BOARD_PMC_PLLA_MUL+1)/2, PCK = PLLA, MCK = PCK/3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = BOARD_PMC_PLLA_MUL,
			.div = BOARD_PMC_PLLA_DIV,
			.count = 0x3f,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.plla_div2 = true,
		.h32mx_div2 = true,
	},
	/* PCK = MCK = BOARD_OSC */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PCK = MCK = BOARD_OSC/16 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV16,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PCK = MCK = BOARD_OSC/64 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PCK = MCK = 32.768 kHz */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PCK = MCK = 32768/64 = 512 Hz */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PCK = MCK = 12 MHz (RC) */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla = {
			.mul = 0,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.plla_div2 = false,
		.h32mx_div2 = false,
	},
	/* PLLA = BOARD_OSC*66/2, PCK = PLLA, MCK = PCK/3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 65,
			.div = 1,
			.count = 0x3f,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.plla_div2 = true,
		.h32mx_div2 = true,
	},
};
