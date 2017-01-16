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

#ifndef CONFIG_SAMV71_XPLAINED_H
#define CONFIG_SAMV71_XPLAINED_H

#include "chip_pins.h"

/** define timer/counter */
#define EXAMPLE_TC TC3

/** define channel for timer/counter */
#define EXAMPLE_TC_CHANNEL_COUNTER 1

/** define channel to output the waveform */
#define EXAMPLE_TC_CHANNEL_WAVEFORM_OUT 2

/** define channel to output the waveform */
#define EXAMPLE_TC_CHANNEL_CAPTURE_IN 0

/** define pin to output the waveform */
#define PIN_TC_WAVEFORM_OUT PIN_TC3_TIOA11

/** define pin to capture the waveform */
#define PIN_TC_CAPTURE_IN PIN_TC0_TIOA0

#endif /* CONFIG_SAMV71_XPLAINED_H */
