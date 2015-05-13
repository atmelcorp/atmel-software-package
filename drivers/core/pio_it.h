/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 *  \file
 *
 *  \par Purpose
 *
 *  Configuration and handling of interrupts on PIO status changes. The API
 *  provided here have several advantages over the traditional PIO interrupt
 *  configuration approach:
 *     - It is highly portable
 *     - It automatically demultiplexes interrupts when multiples pins have been
 *       configured on a single PIO controller
 *     - It allows a group of pins to share the same interrupt
 *
 *  However, it also has several minor drawbacks that may prevent from using it
 *  in particular applications:
 *     - It enables the clocks of all PIO controllers
 *     - PIO controllers all share the same interrupt handler, which does the
 *       demultiplexing and can be slower than direct configuration
 *     - It reserves space for a fixed number of interrupts, which can be
 *       increased by modifying the appropriate constant in pio_it.c.
 *
 *  \par Usage
 *
 *  -# Initialize the PIO interrupt mechanism using pio_initialize_it()
 *     with the desired priority (0 ... 7).
 *  -# Configure a status change interrupt on one or more pin(s) with
 *     pio_configure_it().
 *  -# Enable & disable interrupts on pins using pio_enable_it() and
 *     pio_enable_it().
 */

#ifndef _PIO_IT_
#define _PIO_IT_

/*
 *         Headers
 */

#include "pio.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *         Global functions
 */

void pio_initialize_it(uint32_t prority);

void pio_configure_it(const struct _pin * pin);

void pio_enable_it(const struct _pin * pin);

void pio_disable_it(const struct _pin * pin);

void pio_it_handlers(void);

void pio_capture_handler(void);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef _PIO_IT_ */
