/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#include <assert.h>
#include "applet.h"
#include "board.h"
#include "board_lowlevel.h"
#include "trace.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *         Private functions
 *----------------------------------------------------------------------------*/

static void applet_low_level_init(void)
{
#if defined(CONFIG_SOC_SAMA5D2)
	pmc_switch_mck_to_slck();
	pmc_set_mck_h32mxdiv(PMC_MCKR_H32MXDIV_H32MXDIV2);
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_EQ_PCK);
	pmc_set_plla(0, 0);
	pmc_select_external_osc();
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(82) |
		CKGR_PLLAR_DIVA_BYPASS, 0);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_switch_mck_to_pll();
#elif defined(CONFIG_SOC_SAMA5D3)
	pmc_select_external_osc();
	pmc_switch_mck_to_main();
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		     CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(87) |
		     CKGR_PLLAR_DIVA_BYPASS, PMC_PLLICPR_IPLL_PLLA(3));
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_switch_mck_to_pll();
#elif defined(CONFIG_SOC_SAMA5D4)
	pmc_select_external_osc();
	pmc_switch_mck_to_main();
	pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
	pmc_set_plla(CKGR_PLLAR_ONE | CKGR_PLLAR_PLLACOUNT(0x3F) |
		     CKGR_PLLAR_OUTA(0x0) | CKGR_PLLAR_MULA(87) |
		     CKGR_PLLAR_DIVA_BYPASS, PMC_PLLICPR_IPLL_PLLA(0x0));
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_switch_mck_to_pll();
#else
#error Unsupported SoC!
#endif
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'Low-Level' from softpack " SOFTPACK_VERSION ".\r\n");

	trace_info_wp("Current processor clock: %dHz\r\n",
			(unsigned)pmc_get_processor_clock());
	applet_low_level_init();

	/* re-inititialize console after clock setup */
	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("Low-Level initialization complete.\r\n");
	trace_info_wp("Processor clock: %dHz\r\n",
			(unsigned)pmc_get_processor_clock());

	mbx->out.buf_addr = 0;
	mbx->out.buf_size = 0;
	mbx->out.page_size = 0;
	mbx->out.mem_size = 0;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ 0, NULL }
};
