/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include <string.h>

#include "board.h"
#include "board_console.h"
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

void board_cfg_console(uint32_t baudrate)
{
	struct _console_cfg console_cfg;

	if (!baudrate) {
#ifdef BOARD_CONSOLE_BAUDRATE
		baudrate = BOARD_CONSOLE_BAUDRATE;
#else
		baudrate = 115200;
#endif
	}

#ifdef BOARD_CONSOLE_ADDR
	memset(&console_cfg, 0, sizeof(console_cfg));
	console_cfg.addr = BOARD_CONSOLE_ADDR;
	console_cfg.baudrate = baudrate;
#  ifdef BOARD_CONSOLE_TX_PIN
	const struct _pin tx_pin = BOARD_CONSOLE_TX_PIN;
	console_cfg.tx_pin = tx_pin;
#  endif
#  ifdef BOARD_CONSOLE_RX_PIN
	const struct _pin rx_pin = BOARD_CONSOLE_RX_PIN;
	console_cfg.rx_pin = rx_pin;
#  endif
#else
	get_romcode_console(&console_cfg);
#endif

	console_configure(&console_cfg);
}

