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
#include "board_support.h"
#include "trace.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
/*----------------------------------------------------------------------------
 *         Private definitions
 *----------------------------------------------------------------------------*/
#if defined(CONFIG_SOC_SAM9X60)
#define MAX_PRESET 2
static const uint32_t expected_proc_clock[MAX_PRESET] = { 600, 498 };
#elif defined(CONFIG_SOC_SAM9XX5)
#define EXPECTED_PROC_CLOCK 399
#elif defined(CONFIG_SOC_SAMA5D2)
#define EXPECTED_PROC_CLOCK 498
#elif defined(CONFIG_SOC_SAMA5D3)
#define EXPECTED_PROC_CLOCK 528
#elif defined(CONFIG_SOC_SAMA5D4)
#define EXPECTED_PROC_CLOCK 528
#elif defined(CONFIG_SOC_SAMV71)
#define EXPECTED_PROC_CLOCK 300
#else
#error Unsupported SoC!
#endif

#if defined(EXPECTED_PROC_CLOCK)
static inline void board_cfg_clocks_for_preset(uint32_t preset)
{
	board_cfg_clocks();
}
#endif

/*----------------------------------------------------------------------------
 *         Private functions
 *----------------------------------------------------------------------------*/

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t pck, expected_pck, preset = 0;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'Low-Level' from softpack " SOFTPACK_VERSION ".\r\n");

	pck = pmc_get_processor_clock() / 1000000;
	trace_warning_wp("Current processor clock: %d MHz\r\n", (unsigned)pck);
	while(!console_is_tx_empty());

#if defined(EXPECTED_PROC_CLOCK)
	expected_pck = EXPECTED_PROC_CLOCK;
#elif defined(MAX_PRESET)
	preset = mbx->in.parameters[0];

	if (preset >= MAX_PRESET) {
		trace_error_wp("Invalid preset value: %lu\r\n", preset);
		return APPLET_FAIL;
	}

	expected_pck = expected_proc_clock[preset];
#endif

	if (pck >= expected_pck) {
		trace_warning_wp("Clocks are already configured.\r\n");
	} else {
		/* setup clocks */
		board_cfg_clocks_for_preset(preset);

		/* re-inititialize console after clock setup */
		if (!applet_set_init_params(mbx))
			return APPLET_FAIL;

		/* display new processor clock */
		pck = pmc_get_processor_clock() / 1000000;
		trace_warning_wp("Current processor clock: %d MHz\r\n", (unsigned)pck);
	}

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
