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
#include "board_isc.h"

#include "gpio/pio.h"

#include "peripherals/pmc.h"
#include "video/isc.h"

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_ISC
void board_cfg_isc(void)
{
	const struct _pin pins_isc[]= BOARD_ISC_PINS;
	const struct _pin pin_rst = BOARD_ISC_PIN_RST;
	const struct _pin pin_pwd = BOARD_ISC_PIN_PWD;

	/* Configure ISC pins */
	pio_configure(pins_isc, ARRAY_SIZE(pins_isc));

	/* Reset sensor */
	pio_configure(&pin_rst,1);
	pio_configure(&pin_pwd,1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
	msleep(10);

	pmc_configure_peripheral(ID_ISC, NULL, true);
	pmc_enable_system_clock(PMC_SYSTEM_CLOCK_ISC);
	isc_configure_master_clock(7 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);

	isc_enable_master_clock();
	isc_configure_isp_clock(2 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);

	isc_enable_isp_clock();
}
#endif
