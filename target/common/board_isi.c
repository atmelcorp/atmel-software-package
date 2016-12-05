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

#include "timer.h"
#include "board.h"
#include "board_isi.h"

#include "gpio/pio.h"

#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

void board_cfg_isi(void)
{
	const struct _pin pins_isi[]= BOARD_ISI_PINS;
	const struct _pin pin_mck = BOARD_ISI_MCK_PIN;
	const struct _pin pin_rst = BOARD_ISI_RST_PIN;
	const struct _pin pin_pwd = BOARD_ISI_PWD_PIN;

	/* Configure ISI pins */
	pio_configure(pins_isi, ARRAY_SIZE(pins_isi));

	/* Configure PMC programmable clock (PCK1) */
	pio_configure(&pin_mck, 1);
	pmc_configure_pck(BOARD_ISI_MCK_PCK,
	                  BOARD_ISI_MCK_PCK_SRC,
	                  BOARD_ISI_MCK_PCK_DIV);
	pmc_enable_pck(BOARD_ISI_MCK_PCK);

	/* Reset sensor */
	pio_configure(&pin_rst, 1);
	pio_configure(&pin_pwd, 1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
	msleep(10);

	/* Enable ISI peripheral clock */
	pmc_configure_peripheral(ID_ISI, NULL, true);
}
