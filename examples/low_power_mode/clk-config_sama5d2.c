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

#include "clk-config.h"

struct pck_mck_cfg clock_test_setting[8] = {
	/* PLLA = 12*83/2 = 498 Mhz, PCK = PLLA = 498 Mhz, MCK = PCK/3 = 166 MHz */
	/* PLLA EXT12M EXT32K MULA=82 DIV=1 DIV2ON=1 PRES=0 MDIV=3 H32MXDIV2=1 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla = {
			.mul = 82,
			.div = 1,
			.count = 0x3f,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.plla_div2 = true,
		.h32mx_div2 = true,
	},
	/* PCK = MCK = 12 MHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 H32MXDIV2=0 */
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
	/* PCK = MCK = 12000000/16 = 750 kHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=16 MDIV=0 H32MXDIV2=0 */
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
	/* PCK = MCK = 12000000/64 = 187.5 kHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=64 MDIV=0 H32MXDIV2=0 */
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
	/* slow clock EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 H32MXDIV2=0 */
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
	/* slow clock EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=64 MDIV=0 H32MXDIV2=0 */
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
	/* MAIN RC12M RC32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 H32MXDIV2=0 */
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
	/* PLLA = 12*66/2 = 396 Mhz, PCK = PLLA = 396 Mhz, MCK = PCK/3 = 132MHz */
	/* MAIN EXT12M EXT32K MULA=66 DIV=1 DIV2ON=1 PRES=0 MDIV=3 H32MXDIV2=1 */
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
