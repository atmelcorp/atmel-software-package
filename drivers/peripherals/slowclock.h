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

#ifndef SLOWCLOCK_H_
#define SLOWCLOCK_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

enum _slowclock_domain {
	SLOWCLOCK_DOMAIN_DEFAULT, /* Default slow clock, used as input for peripherals */
#ifdef CONFIG_HAVE_SLOWCLOCK_TIMING_DOMAIN
	SLOWCLOCK_DOMAIN_TIMING,  /* Timing Domain slow clock (RTC, RTT) */
#endif
};

/**
 * \brief Check if the slow clock is using the internal or external oscillator.
 * \param domain slow clock domain
 * \return true if the slow clock source is the internal RC oscillator, false if it is
 * the external crystal oscillator.
 */
extern bool slowclock_is_internal(enum _slowclock_domain domain);

/**
 * \brief Select internal slow clock RC oscillator.
 * \param domain slow clock domain
 */
extern void slowclock_select_internal(enum _slowclock_domain domain);

/**
 * \brief Select external slow clock crystal oscillator.
 * \param domain slow clock domain
 */
extern void slowclock_select_external(enum _slowclock_domain domain);

/*
 * \brief Get the frequency of the currently selected slow clock oscillator (32K or 32.768K)
 * \param domain slow clock domain
 * \return the oscillator frequency in Hertz.
 */
extern uint32_t slowclock_get_clock(enum _slowclock_domain domain);


#ifdef __cplusplus
}
#endif
#endif /* #ifndef SLOWCLOCK_H_ */
