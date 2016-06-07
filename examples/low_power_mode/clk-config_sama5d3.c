#include "peripherals/pmc.h"

struct pck_mck_cfg clock_test_setting[8] = {
	/* PLL A = 996, PCK = 498, MCK = 166 MHz */
	/* PLLA EXT12M EXT32K MULA=82 DIV=1 DIV2ON=1 PRES=0 MDIV=3 h32mxdiv2=1*/
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 82,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
	},
	/* PCK = MCK = 12MHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
	/* PCK = MCK = 750 kHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=16 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV16,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
	/* PCK = MCK = 187.5 kHz */
	/* MAIN EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=64 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
	/* PCK = MCK = 32 kHz */
	/* slow clock EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
	/* PCK = MCK = 512 Hz */
	/* slow clock EXT12M EXT32K MULA=0 DIV=1 DIV2ON=0 PRES=64 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
        /* PCK = MCK = RC12MHz */
	/* MAIN RC12M RC32K MULA=0 DIV=1 DIV2ON=0 PRES=0 MDIV=0 h32mxdiv2=0*/
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
	},
	/* PLL A = 792, PCK = 396, MCK = 132MHz */
	/* MAIN EXT12M EXT32K MULA=66 DIV=1 DIV2ON=1 PRES=0 MDIV=3 h32mxdiv2=1*/
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 65,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
	},
};
