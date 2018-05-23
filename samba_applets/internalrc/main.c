/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>

#include "applet.h"
#include "board.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *         Private functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_SOC_SAMA5D2)

#define SAMA5D2_PLLA_MULA	62
#define SAMA5D2_PLLA_DIVA	1
#define SAMA5D2_PLLA_COUNT	0x10

static void switch_to_internal_rc(void)
{
	static const struct _pmc_plla_cfg plla = {
		.mul = SAMA5D2_PLLA_MULA,
		.div = SAMA5D2_PLLA_DIVA,
		.count = SAMA5D2_PLLA_COUNT,
	};

	pmc_switch_mck_to_slck();
	pmc_enable_internal_osc();

	/* switch MAIN clock to internal 12MHz RC */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~(CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_Msk)) | CKGR_MOR_KEY_PASSWD;

	pmc_disable_plla();
	pmc_set_mck_plladiv2(true);
	pmc_configure_plla(&plla);
	pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
	pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
	pmc_set_mck_h32mxdiv(true);
	pmc_switch_mck_to_pll();
}
#else
#error Unsupported SOC!
#endif

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox *)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	switch_to_internal_rc();

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	memset(&mbx->out, 0, sizeof(mbx->out));

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ 0, NULL }
};
