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
  * Implementation WM8904 driver.
  *
  */

#ifndef WM8904_H
#define WM8904_H

#include <peripherals/twid.h>

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** Slave address */
#define WM8904_SLAVE_ADDRESS 0x1a

#define WM8904_INPUT_PATH_IN1L 0x01
#define WM8904_INPUT_PATH_IN1R 0x02
#define WM8904_INPUT_PATH_IN2L 0x04
#define WM8904_INPUT_PATH_IN2R 0x08

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern void wm8904_configure(struct _twi_desc* twid, uint32_t device, uint32_t pck, uint8_t input_path);
extern void wm8904_in2r_in1l(struct _twi_desc* twid, uint32_t device);
extern void wm8904_set_left_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol);
extern void wm8904_set_right_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol);
extern void wm8904_volume_mute(struct _twi_desc* twid, uint32_t device, bool left, bool right);
extern bool wm8904_detect(struct _twi_desc* twid, uint32_t device);
extern void wm8904_reset(struct _twi_desc* twid, uint32_t device);
extern void wm8904_sync(struct _twi_desc* twid, uint32_t device, int32_t adjust);

#endif
