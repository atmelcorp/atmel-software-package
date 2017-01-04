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

#include "board_lcd.h"
#include "display/lcdc.h"
#include "gpio/pio.h"

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

void board_cfg_lcd(void)
{
#ifdef BOARD_LCD_PINS
	const struct _pin pins_lcd[] = BOARD_LCD_PINS;
	const struct _lcdc_desc lcd_desc = {
		.width = BOARD_LCD_WIDTH,
		.height = BOARD_LCD_HEIGHT,
		.framerate = BOARD_LCD_FRAMERATE,
		.timing_vfp = BOARD_LCD_TIMING_VFP,
		.timing_vbp = BOARD_LCD_TIMING_VBP,
		.timing_vpw = BOARD_LCD_TIMING_VPW,
		.timing_hfp = BOARD_LCD_TIMING_HFP,
		.timing_hbp = BOARD_LCD_TIMING_HBP,
		.timing_hpw = BOARD_LCD_TIMING_HPW,
	};

	pio_configure(pins_lcd, ARRAY_SIZE(pins_lcd));
	lcdc_configure(&lcd_desc);
#endif
}
