/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

/** \file */

/**
 * \ingroup lib_board
 * \addtogroup lcdd_module LCD Driver
 *
 * \section Purpose
 *
 * Implement driver functions for LCD control and image display.
 * - Implement basic LCD controller configuration.
 * - Implement display functions for LCD layers.
 * - Implement simple drawing functions.
 * - Implement string display functions.
 *
 * \section lcdd_base_usage Usage
 *
 * Uses following functions for LCD basic configuration and displaying:
 * -# Uses lcdd_initialize() to initialize the controller and LCD.
 * -# lcdd_on() and lcdd_off() is used to turn LCD ON/OFF.
 * -# lcdd_set_backlight() is used to change LCD backlight level.
 * -# To display a image (BMP format) on LCD, lcdd_put_image_rotated()
 *    lcdd_put_image_scaled() and lcdd_put_image() can be used.
 * -# To change configuration for an overlay layer, the following functions
 *    can use:
 *    -# lcdd_enable_layer(), lcdd_is_layer_on(): Turn ON/OFF layer, check status.
 *    -# lcdd_set_position(), lcdd_set_priority(), lcdd_enable_alpha(),
 *       lcdd_set_alpha(), lcdd_set_color_keying(): Change display options.
 * -# Shortcuts for layer display are as following:
 *    -# lcdd_show_base(), lcdd_stop_base()
 *    -# lcdd_show_ovr1(), lcdd_stop_ovr1()
 *    -# lcdd_show_heo(), lcdd_stop_heo()
 *    -# lcdd_show_hcr(), lcdd_stop_hcr()
 * -# Drawing supporting functions, for drawing canvas:
 *    -# lcdd_create_canvas(): Create blank canvas on specified layer for
 *                            drawing on
 *    -# lcdd_select_canvas(): Select a displayer as canvas to drawing on
 *    -# lcdd_get_canvas():    Get current selected canvas layer
 *
 * For LCD drawing functions, refer to \ref lcdd_draw.
 *
 * For LCD string display, refer to \ref lcdd_font.
 *
 * @{
 *   \defgroup lcdd_base LCD Driver General Operations
 *   @{
 *     Implementation of LCD driver, Include LCD initialization,
 *     LCD on/off and LCD backlight control.
 *
 *     \sa \ref lcdd_base_usage "LCD Driver General Usage"
 *   @}
 *   \defgroup lcdd_draw LCD Driver Simple Drawing
 *   @{
 *   @}
 *   \defgroup lcdd_font LCD Driver Font Display
 *   @{
 *   @}
 * @}
 */

#ifndef LCDD_H
#define LCDD_H

#ifdef CONFIG_HAVE_LCDD

/** \addtogroup lcdd_base
 *  @{
 */

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/

/** \addtogroup lcdd_disp_id LCD display layers IDs
 *      @{
 */
/** LCD controller ID, no display, configuration ONLY */
#define LCDD_CONTROLLER     0
/** LCD base layer, display fixed size image */
#define LCDD_BASE           1
/** LCD Overlay 1 */
#define LCDD_OVR1           2
/** LCD Overlay 2 */
#define LCDD_OVR2           4
/** LCD HighEndOverlay, support resize */
#define LCDD_HEO            3
/** LCD Cursor, max size 128x128 */
#define LCDD_CUR            6
/**     @}*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _pin;

/** LCD display layer information */
struct _lcdd_layer {
	void    *buffer;   /**< Display image buffer */
	uint16_t width;    /**< Display image width */
	uint16_t height;   /**< Display image height */
	uint8_t  bpp;      /**< Image BPP (16,24,32) for RGB mode */
	uint8_t  layer_id; /**< Layer ID */
};

/** LCD configuration information */
struct _lcdd_desc {
	uint16_t width;    /**< Display image width */
	uint16_t height;   /**< Display image height */
	uint8_t  framerate; /**< Frame rate in Hz */

	uint8_t timing_vfp; /**< Vertical front porch in number of lines */
	uint8_t timing_vbp; /**< Vertical back porch in number of lines */
	uint8_t timing_vpw; /**< Vertical pulse width in number of lines */
	uint8_t timing_hfp; /**< Horizontal front porch in LCDDOTCLK cycles */
	uint8_t timing_hbp; /**< Horizontal back porch in LCDDOTCLK cycles */
	uint8_t timing_hpw; /**< Horizontal pulse width in LCDDOTCLK cycles */
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void lcdd_configure(const struct _lcdd_desc *desc);

extern uint8_t lcdd_is_layer_on(uint8_t layer);

extern void lcdd_enable_layer(uint8_t layer, bool enable);

extern void lcdd_refresh(uint8_t layer);

extern void lcdd_set_position(uint8_t layer, uint32_t x, uint32_t y);

extern void lcdd_set_priority(uint8_t layer, uint8_t priority);

extern uint8_t lcdd_get_priority(uint8_t layer);

extern void lcdd_enable_alpha(uint8_t layer, bool enable_local,
		bool enable_global);

extern void lcdd_set_alpha(uint8_t layer, bool reverse, uint8_t alpha);

extern uint8_t lcdd_get_alpha(uint8_t layer);

extern void lcdd_set_color_keying(uint8_t layer, bool dest_keying,
				uint32_t color, uint32_t mask);

extern void lcdd_disable_color_keying(uint8_t layer);

extern void lcdd_set_color_lut(uint8_t layer, uint32_t *clut, uint8_t bpp,
		uint8_t num_colors);

extern void *lcdd_put_image_rotated(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h,
		uint32_t img_w, uint32_t img_h, int16_t rotation);

extern void *lcdd_put_image_scaled(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h,
		uint32_t img_w, uint32_t img_h);

extern void *lcdd_put_image(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void *lcdd_show_base(void *buffer, uint8_t bpp, bool bottom_up);

extern void lcdd_stop_base(void);

extern void *lcdd_show_ovr1(void *buffer, uint8_t bpp,
			   uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void lcdd_stop_ovr1(void);

extern void *lcdd_show_heo(void *buffer, uint8_t bpp,
			  uint32_t x, uint32_t y, int32_t w, int32_t h,
			  uint32_t memW, uint32_t memH);

extern void lcdd_stop_heo(void);

extern void lcdd_on(void);

extern void lcdd_off(void);

extern void lcdd_set_backlight(uint32_t step);

extern void *lcdd_show_hcr(void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void lcdd_stop_hcr(void);

extern struct _lcdd_layer *lcdd_get_canvas(void);

extern uint8_t lcdd_select_canvas(uint8_t layer);

extern void *lcdd_create_canvas(uint8_t layer, void *buffer, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void lcdd_flush_canvas(void);

extern void lcdd_configure_input_mode(uint8_t layer, uint32_t input_mode);

extern void *lcdd_create_canvas_yuv_planar(uint8_t layer,
		void *buffer_y, void *buffer_u, void *buffer_v, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void *lcdd_create_canvas_yuv_semiplanar(uint8_t layer,
		void *buffer_y, void *buffer_uv, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

/**  @}*/

#endif /* CONFIG_HAVE_LCDD */

#endif /* #ifndef LCDD_H */
