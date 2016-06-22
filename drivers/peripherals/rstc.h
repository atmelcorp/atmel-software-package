/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

#ifndef _RSTC_H
#define _RSTC_H

/*---------------------------------------------------------------------------
 *         Includes
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_RSTC_CONFIGURABLE_USER_RESET

/**
 * Enable/Disable the detection of a low level on the pin NRST as User Reset
 * \param enable true to enable & false to disable.
 */
extern void rstc_set_user_reset_enable(bool enable);

/**
 * Enable/Disable the interrupt of a User Reset (USRTS bit in RSTC_RST).
 * \param enable true to enable & false to disable.
 */
extern void rstc_set_user_reset_interrupt_enable(bool enable);

#endif /* CONFIG_HAVE_RSTC_CONFIGURABLE_USER_RESET */

#ifdef CONFIG_HAVE_RSTC_EXTERNAL_RESET

/**
 * Sets the assertion duration for the external reset.
 * The external reset is asserted during a time of 2^(length+1) Slow Clock cycles.
 */
extern void rstc_set_ext_reset_length(uint8_t length);

/**
 * Resets the processor and the peripherals and asserts external reset
 */
extern void rstc_reset_processor_and_peripherals_and_ext(void);

#endif /* CONFIG_HAVE_RSTC_EXTERNAL_RESET */

/**
 * Resets both the processor and the peripherals.
 */
extern void rstc_reset_processor_and_peripherals(void);

#ifdef CONFIG_HAVE_RSTC_INDEPENDENT_RESET

/**
 * Resets only the processor.
 */
extern void rstc_reset_processor(void);

/**
 * Resets only the peripherals.
 */
extern void rstc_reset_peripherals(void);

#endif /* CONFIG_HAVE_RSTC_INDEPENDENT_RESET */

/**
 * Return NRST pin level.
 */
extern bool rstc_get_nrst_level(void);

/**
 * Returns true if at least one high-to-low transition of NRST (User Reset) has
 * been detected since the last read of RSTC_RSR.
 */
extern bool rstc_is_user_reset_detected(void);

/**
 * Return true if a software reset command is being performed by the reset
 * controller. The reset controller is busy.
 */
extern bool rstc_is_busy(void);

/**
 * Get the value of the RSTC status register
 */
extern uint32_t rstc_get_status(void);

#endif				/* #ifndef _RSTC_H */
