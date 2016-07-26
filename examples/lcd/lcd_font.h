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

/**
 * \file
 *
 * Interface for draw font on LCD.
 *
 */

/**
 * \addtogroup lcd_font LCD Font Drawing
 *
 * \section Purpose
 *
 * The lcd_font.h files declares a font structure and a lcd_draw_char() function
 * that must be implemented by a font definition file to be used with the
 * lcd_draw_string() method of draw.h.
 *
 * The font10x14.c implements the necessary variable and function for a 10x14
 * font.
 *
 * \note Before drawing fonts, <b>canvas</b> should be selected via
 *       lcdc_select_canvas(), or created by lcdc_create_canvas().
 *
 * \section Usage
 *
 * -# Declare a gFont global variable with the necessary Font information.
 * -# Implement an lcd_draw_char() function which displays the specified
 *    character on the LCD.
 * -# Select or create canvas via lcdc_select_canvas() or lcdc_create_canvas().
 * -# Use the lcd_draw_string() method defined in draw.h to display a complete
 *    string.
 *
 * \sa \ref lcd_module, \ref lcd_draw.
 */

#ifndef _LCD_FONT_
#define _LCD_FONT_
/** \addtogroup lcd_font
 *@{
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "font.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \brief Describes the font (width, height, supported characters, etc.) used by
 * the LCD driver draw API.
 */
struct _font {
	uint8_t width;	/* Font width in pixels. */
	uint8_t height;	/* Font height in pixels. */
};

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup lcd_font_func Font Functions */
/** @{*/

extern struct _font_parameters* lcd_select_font (_FONT_enum font);

extern uint8_t lcd_get_selected_font (void);

extern void lcd_draw_char(uint32_t x, uint32_t y, uint8_t c, uint32_t color);

extern void lcd_draw_char_with_bgcolor(uint32_t x, uint32_t y, uint8_t c,
				     uint32_t fontColor, uint32_t bgColor);
/** @}*/
/**@}*/
#endif				/* #ifndef LCD_FONT_ */
