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
  * Implementation driver: IS31FL3728 AUDIO MODULATED MATRIX LED DRIVER.
  *
  */

#ifndef _IS31FL3728_H_
#define _IS31FL3728_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "i2c/twi.h"
#include "i2c/twid.h"
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** Internal Register Address Allocation */
/** Configuration register */
#define IS31FL3728_REG_CONFIGURATION		0x00

/** Column Data Register*/
#define IS31FL3728_REG_COLUMN_DATA1		0x01
#define IS31FL3728_REG_COLUMN_DATA2		0x02
#define IS31FL3728_REG_COLUMN_DATA3		0x03
#define IS31FL3728_REG_COLUMN_DATA4		0x04
#define IS31FL3728_REG_COLUMN_DATA5		0x05
#define IS31FL3728_REG_COLUMN_DATA6		0x06
#define IS31FL3728_REG_COLUMN_DATA7		0x07
#define IS31FL3728_REG_COLUMN_DATA8		0x08
#define IS31FL3728_REG_COLUMN_DATA9		0x09
#define IS31FL3728_REG_COLUMN_DATA10		0x0A
#define IS31FL3728_REG_COLUMN_DATA11		0x0B

/**Update Column Register */
#define IS31FL3728_REG_UPDATE_COLUMN       0x0C

/** Lighting Effect Register */
#define IS31FL3728_REG_LIGHTING_EFFECT		0x0D

/** CS Full Current Setting For Each Row Output */
#define IS31FL3728_CURRENT_SETTING_40		0
#define IS31FL3728_CURRENT_SETTING_45		1
#define IS31FL3728_CURRENT_SETTING_50		2
#define IS31FL3728_CURRENT_SETTING_55		3
#define IS31FL3728_CURRENT_SETTING_60		4
#define IS31FL3728_CURRENT_SETTING_65		5
#define IS31FL3728_CURRENT_SETTING_70		6
#define IS31FL3728_CURRENT_SETTING_75		7
#define IS31FL3728_CURRENT_SETTING_5		8
#define IS31FL3728_CURRENT_SETTING_10		9
#define IS31FL3728_CURRENT_SETTING_15		10
#define IS31FL3728_CURRENT_SETTING_20		11
#define IS31FL3728_CURRENT_SETTING_25		12
#define IS31FL3728_CURRENT_SETTING_30		13
#define IS31FL3728_CURRENT_SETTING_35		14

/** AGS Audio Input Gain Selection */
#define IS31FL3728_AUDIO_GAIN_SELECT_POS	  7
#define IS31FL3728_AUDIO_GAIN_SELECT_0DB	  (0 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_3DB	  (1 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_6DB	  (2 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_9DB	  (3 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_12DB	  (4 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_15DB	  (5 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_18DB	  (6 << IS31FL3728_AUDIO_GAIN_SELECT_POS)
#define IS31FL3728_AUDIO_GAIN_SELECT_MINUS6DB (7 << IS31FL3728_AUDIO_GAIN_SELECT_POS)

/** Audio EQ Register */
#define IS31FL3728_REG_AUDIO_EQ			0x0E

/*----------------------------------------------------------------------------
 *         Local Definitions
 *----------------------------------------------------------------------------*/

struct _is31fl3728_desc {
	const char *name;
	struct {
		uint8_t cols;
		uint8_t rows;
	} matrix;
};

struct _is31fl3728 {
	struct {
		uint8_t bus;
		uint8_t addr;
	} twi;
	struct _is31fl3728_desc desc;

	struct {
		uint8_t config;
		uint8_t column;
		uint8_t lighting;
	} settings;

	uint8_t *fb; // Let's define a framebuffer with correct size
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/
/**
 * Configure the LED driver
 * @param is31fl3728      Control structure
 * @param fb              Framebuffer to hold the LED status
 * @return 0 on success
 */
extern int is31fl3728_configure(struct _is31fl3728 *is31fl3728, uint8_t addr, uint8_t *fb);

/**
 * Refresh the framebuffer. It updates the IS31FL3728 to drive the LED to the framebuffer state
 * @param is31fl3728      Control structure
 */
extern void is31fl3728_refresh(struct _is31fl3728 *is31fl3728);

/**
 * Set one LED to 1 in the frame buffer
 * @param is31fl3728      Control structure
 * @param x               X coordinate
 * @param y               Y coordinate
 */
extern void is31fl3728_fb_set(struct _is31fl3728 *is31fl3728, uint8_t x, uint8_t y);

/**
 * Reset the framebuffer to the given value
 * @param is31fl3728      Control structure
 * @param value
 */
extern void is31fl3728_fb_reset(struct _is31fl3728 *is31fl3728, uint8_t value);


#endif /* _IS31FL3728_H_ */
