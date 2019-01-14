/* ----------------------------------------------------------------------------
 *        SAM Software Package License
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

/**
 * \file
 *
 * Implementation of Watchdog Timer (WDT) controller.
 *
 */

/** \addtogroup wdt_module Working with WDT
 * \section Purpose
 * The WDT driver provides the interface to configure and use the WDT
 * peripheral.
 *
 * The WDT can be used to prevent system lock-up if the software becomes
 * trapped in a deadlock. It can generate a general reset or a processor
 * reset only. It is clocked by slow clock divided by 128.
 *
 * The WDT is running at reset with 16 seconds watchdog period (slow clock at 32.768 kHz)
 * and external reset generation enabled. The user must either disable it or
 * reprogram it to meet the application requires.
 *
 * \section Usage
 * To use the WDT, the user could follow these few steps:
 * <ul>
 * <li>Enable watchdog with given mode using \ref wdt_enable().
 * <li>Restart the watchdog using \ref wdt_restart() within the watchdog period.
 * </ul>
 *
 * For more accurate information, please look at the WDT section of the
 * Datasheet.
 *
 * \note
 * The Watchdog Mode Register (WDT_MR) can be written only once.\n
 *
 * Related files :\n
 * \ref wdt.c\n
 * \ref wdt.h.\n
 */
/*@{*/
/*@}*/

/*---------------------------------------------------------------------------
 *        Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "trace.h"
#include "timer.h"
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint32_t _wdt_compute_period(uint32_t timeout)
{
	/* Calculate the reload value to achive this (appoximate) timeout.
	*
	* Examples with WDT_FREQUENCY = 32768 / 128 = 256:
	*  timeout = 4     -> reload = 1
	*  timeout = 16000 -> reload = 4096
	*/
	uint32_t reload = (timeout * (pmc_get_slow_clock() >> 7) + 500) / 1000;
	if (reload < 1) {
		reload = 1;
	}
	else if (reload > 4095) {
		reload = 4095;
	}
	return reload;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void wdt_enable(bool en_int,
				bool en_rst,
				bool en_dbghlt,
				bool en_idlehlt,
				uint32_t delta,
				uint32_t counter)
{
	uint32_t mode = 0;

#ifdef CONFIG_HAVE_DWDT
	uint32_t wc;

	mode &= ~(WDT_MR_WDDIS);
	WDT->WDT_MR = mode;
	wc = _wdt_compute_period(counter);
	WDT->WDT_WLR = WDT_WLR_PERIOD(wc) | WDT_WLR_RPTH(_wdt_compute_period(delta));
	WDT->WDT_ILR = WDT_ILR_LVLTH(wc);
	if (en_int)
		WDT->WDT_IER = WDT_IER_PERINT | WDT_IER_RPTHINT | WDT_IER_LVLINT;
	else
		WDT->WDT_IER = 0;

	if (en_rst)
		mode |= WDT_MR_PERIODRST;
	if (en_dbghlt)
		mode |= WDT_MR_WDDBGHLT;
	if (en_idlehlt)
		mode |= WDT_MR_WDIDLEHLT;
	WDT->WDT_MR = mode;

#else
	mode &= ~(WDT_MR_WDDIS | WDT_MR_WDD_Msk | WDT_MR_WDV_Msk);
	mode &= ~(WDT_MR_WDD_Msk | WDT_MR_WDV_Msk);
	WDT->WDT_MR = mode;
	usleep(100);
	if (en_int)
		mode |= WDT_MR_WDFIEN;
	if (en_rst)
		mode |= WDT_MR_WDRSTEN;
	if (en_dbghlt)
		mode |= WDT_MR_WDDBGHLT;
	if (en_idlehlt)
		mode |= WDT_MR_WDIDLEHLT;
	WDT->WDT_MR = mode |
				  WDT_MR_WDD(_wdt_compute_period(delta)) |
				  WDT_MR_WDV(_wdt_compute_period(counter));
#endif
}

void wdt_disable(void)
{
	WDT->WDT_MR = WDT_MR_WDDIS;
}

void wdt_restart()
{
	WDT->WDT_CR = WDT_CR_KEY_PASSWD | WDT_CR_WDRSTT;
}

uint32_t wdt_get_status(void)
{
#ifdef CONFIG_HAVE_DWDT
	return WDT->WDT_ISR;
#else
	return WDT->WDT_SR & (WDT_SR_WDUNF | WDT_SR_WDERR);
#endif
}

uint32_t wdt_get_counter_value(void)
{
#ifdef CONFIG_HAVE_DWDT
	return (WDT->WDT_VR & WDT_VR_COUNTER_Msk) >> WDT_VR_COUNTER_Pos;
#else
	return (WDT->WDT_MR & WDT_MR_WDV_Msk) >> WDT_MR_WDV_Pos;
#endif
}
