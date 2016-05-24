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

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/
#define WM8904_CSB_STATE            (0x0 << 0)

/** Slave address */
#define WM8904_SLAVE_ADDRESS        0x1a | WM8904_CSB_STATE

/** Reset register*/
#define WM8904_REG_RESET                           0x00

/** Bias control 0 register*/
#define WM8904_REG_BIAS_CTRL0                      0x04

/** VMID control 0 register*/
#define WM8904_REG_VMID_CTRL0                      0x05

/** MIC Bias control 0 register*/
#define WM8904_REG_MICBIAS_CTRL0                   0x06

/** Bias control 1 register*/
#define WM8904_REG_BIAS_CTRL1                      0x07

/** Power management control 0 register*/
#define WM8904_REG_POWER_MANG0                     0x0C
/** Power management control 2 register*/
#define WM8904_REG_POWER_MANG2                     0x0E
/** Power management control 3 register*/
#define WM8904_REG_POWER_MANG3                     0x0F
/** Power management control 6 register*/
#define WM8904_REG_POWER_MANG6                     0x12

/** Clock rate0 register*/
#define WM8904_REG_CLOCK_RATE0                     0x14
/** Clock rate1 register*/
#define WM8904_REG_CLOCK_RATE1                     0x15

/** Clock rate2 register*/
#define WM8904_REG_CLOCK_RATE2                     0x16

/** Audio interface0 register*/
#define WM8904_REG_AUD_INF0                        0x18

/** Audio interface1 register*/
#define WM8904_REG_AUD_INF1                        0x19
/** Audio interface2 register*/
#define WM8904_REG_AUD_INF2                        0x1A
/** Audio interface3 register*/
#define WM8904_REG_AUD_INF3                        0x1B

/** ADC digital 0 register*/
#define WM8904_REG_ADC_DIG0                        0x20
/** ADC digital 1 register*/
#define WM8904_REG_ADC_DIG1                        0x21

/** Analogue left input 0 register*/
#define WM8904_REG_ANALOGUE_LIN0                   0x2C
/** Analogue right input 0 register*/
#define WM8904_REG_ANALOGUE_RIN0                   0x2D

/** Analogue left input 1 register*/
#define WM8904_REG_ANALOGUE_LIN1                   0x2E
/** Analogue right input 1 register*/
#define WM8904_REG_ANALOGUE_RIN1                   0x2F

/** Analogue left output 1 register*/
#define WM8904_REG_ANALOGUE_LOUT1                  0x39
/** Analogue right output 1 register*/
#define WM8904_REG_ANALOGUE_ROUT1                  0x3A

/** Analogue left output 2 register*/
#define WM8904_REG_ANALOGUE_LOUT2                  0x3B
/** Analogue right output 2 register*/
#define WM8904_REG_ANALOGUE_ROUT2                  0x3C

/** Analogue output 12 ZC register*/
#define WM8904_REG_ANALOGUE_OUT12ZC                0x3D

/** DC servo 0 register*/
#define WM8904_REG_DC_SERVO0                       0x43

/** Analogue HP 0 register*/
#define WM8904_REG_ANALOGUE_HP0                    0x5A

/** Charge pump 0 register*/
#define WM8904_REG_CHARGE_PUMP0                    0x62

/** Class W 0 register*/
#define WM8904_REG_CLASS0                          0x68

/** FLL control 1 register*/
#define WM8904_REG_FLL_CRTL1                       0x74
/** FLL control 2 register*/
#define WM8904_REG_FLL_CRTL2                       0x75
/** FLL control 3 register*/
#define WM8904_REG_FLL_CRTL3                       0x76
/** FLL control 4 register*/
#define WM8904_REG_FLL_CRTL4                       0x77
/** FLL control 5 register*/
#define WM8904_REG_FLL_CRTL5                       0x78

/** DUMMY register*/
#define WM8904_REG_END                             0xFF

/* 0x39 Analogue OUT1 Left */
/* 0x3a Analogue OUT1 Right */

#define WM8904_HPOUT_MUTE            (1 << 8)  /* Bit 8:  Headphone output mute */
#define WM8904_HPOUT_VU              (1 << 7)  /* Bit 7:  Headphone output volume update */
#define WM8904_HPOUTZC               (1 << 6)  /* Bit 6:  Headphone output zero cross enable */
#define WM8904_HPOUT_VOL_SHIFT       (0)       /* Bits 0-5: Headphone output volume */
#define WM8904_HPOUT_MAX_VOLUME      (63)      /* Headphone output max volume */

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern uint16_t wm8904_read(struct _twi_desc* twid, uint32_t device, uint32_t reg_addr);
extern void wm8904_write(struct _twi_desc* twid, uint32_t device, uint32_t reg_addr,
				uint16_t data);
extern uint8_t wm8904_init(struct _twi_desc* twid, uint32_t device, uint32_t PCK);
extern void wm8904_in2r_in1l(struct _twi_desc* twid, uint32_t device);
extern void wm8904_set_left_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol);
extern void wm8904_set_right_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol);
extern void wm8904_volume_mute(struct _twi_desc* twid, uint32_t device, bool left, bool right);
#endif
