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

/**
 * \file
 *
 * Implementation WM8731 driver.
 *
 */

#ifndef WM8731_H
#define WM8731_H

#include <gpio/pio.h>
#include <i2c/twid.h>

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *         Types
 *----------------------------------------------------------------------------*/

struct _wm8731_desc {
	struct {
		uint8_t bus;           /* TWI bus */
		uint8_t addr;          /* TWI address of the WM8731 */
	} twi;

	uint8_t input_path;
	uint32_t mclk_pck;
	uint32_t mclk_pck_src;
	const struct _pin mclk_pin;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern void wm8731_configure(struct _wm8731_desc *wm8731);
extern void wm8731_set_left_volume(struct _wm8731_desc *wm8731, uint8_t vol);
extern void wm8731_set_right_volume(struct _wm8731_desc *wm8731, uint8_t vol);
extern void wm8731_volume_mute(struct _wm8731_desc *wm8731, bool mute);
extern void wm8731_reset(struct _wm8731_desc *wm8731);

#endif
