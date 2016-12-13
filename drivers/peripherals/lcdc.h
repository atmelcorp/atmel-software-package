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
 * \ingroup drivers/video
 * \addtogroup lcdc_module LCD Driver
 *
 * \section Purpose
 *
 * Implement driver functions for LCD control and image display.
 * - Implement basic LCD controller configuration.
 * - Implement display functions for LCD layers.
 * - Implement simple drawing functions.
 * - Implement string display functions.
 *
 * \section lcdc_base_usage Usage
 *
 * Uses following functions for LCD basic configuration and displaying:
 * -# Uses lcdc_initialize() to initialize the controller and LCD.
 * -# lcdc_on() and lcdc_off() is used to turn LCD ON/OFF.
 * -# lcdc_set_backlight() is used to change LCD backlight level.
 * -# To display a image (BMP format) on LCD, lcdc_put_image_rotated()
 *    lcdc_put_image_scaled() and lcdc_put_image() can be used.
 * -# To change configuration for an overlay layer, the following functions
 *    can use:
 *    -# lcdc_enable_layer(), lcdc_is_layer_on(): Turn ON/OFF layer, check status.
 *    -# lcdc_set_position(), lcdc_set_priority(), lcdc_enable_alpha(),
 *       lcdc_set_alpha(), lcdc_set_color_keying(): Change display options.
 * -# Shortcuts for layer display are as following:
 *    -# lcdc_show_base(), lcdc_stop_base()
 *    -# lcdc_show_ovr1(), lcdc_stop_ovr1()
 *    -# lcdc_show_heo(), lcdc_stop_heo()
 * -# Drawing supporting functions, for drawing canvas:
 *    -# lcdc_create_canvas(): Create blank canvas on specified layer for
 *                            drawing on
 *    -# lcdc_select_canvas(): Select a displayer as canvas to drawing on
 *    -# lcdc_get_canvas():    Get current selected canvas layer
 *
 * For LCD drawing functions, refer to \ref lcdc_draw.
 *
 * For LCD string display, refer to \ref lcdc_font.
 *
 * @{
 *   \defgroup lcdc_base LCD Driver General Operations
 *   @{
 *     Implementation of LCD driver, Include LCD initialization,
 *     LCD on/off and LCD backlight control.
 *
 *     \sa \ref lcdc_base_usage "LCD Driver General Usage"
 *   @}
 *   \defgroup lcdc_draw LCD Driver Simple Drawing
 *   @{
 *   @}
 *   \defgroup lcdc_font LCD Driver Font Display
 *   @{
 *   @}
 * @}
 */

#ifndef LCDC_H_
#define LCDC_H_

#ifdef CONFIG_HAVE_LCDC

/** \addtogroup lcdc_base
 *  @{
 */

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/

/** \addtogroup lcdc_disp_id LCD display layers IDs
 *      @{
 */
enum {
	LCDC_CONTROLLER = 0, /**< LCD controller, no display, config. only */
	LCDC_BASE = 1,       /**< Base Layer */
	LCDC_OVR1 = 2,       /**< Overlay 1 */
	LCDC_HEO = 3,        /**< High-End Overlay */
#ifdef CONFIG_HAVE_LCDC_OVR2
	LCDC_OVR2 = 4,       /**< Overlay 2 */
#endif
};
/**     @}*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** LCD display layer information */
struct _lcdc_layer {
	void    *buffer;   /**< Display image buffer */
	uint16_t width;    /**< Display image width */
	uint16_t height;   /**< Display image height */
	uint8_t  bpp;      /**< Image BPP (16,24,32) for RGB mode */
	uint8_t  layer_id; /**< Layer ID */
};

/** LCD configuration information */
struct _lcdc_desc {
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

extern void lcdc_configure(const struct _lcdc_desc *desc);

extern uint8_t lcdc_is_layer_on(uint8_t layer);

extern void lcdc_enable_layer(uint8_t layer, bool enable);

extern void lcdc_refresh(uint8_t layer);

extern void lcdc_set_position(uint8_t layer, uint32_t x, uint32_t y);

extern void lcdc_set_priority(uint8_t layer, uint8_t priority);

extern uint8_t lcdc_get_priority(uint8_t layer);

extern void lcdc_enable_alpha(uint8_t layer, bool enable_local,
		bool enable_global);

extern void lcdc_set_alpha(uint8_t layer, bool reverse, uint8_t alpha);

extern uint8_t lcdc_get_alpha(uint8_t layer);

extern void lcdc_set_color_keying(uint8_t layer, bool dest_keying,
				uint32_t color, uint32_t mask);

extern void lcdc_disable_color_keying(uint8_t layer);

extern void lcdc_set_color_lut(uint8_t layer, uint32_t *clut, uint8_t bpp);

extern void *lcdc_put_image_rotated(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h,
		uint32_t img_w, uint32_t img_h, int16_t rotation);

extern void *lcdc_put_image_scaled(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h,
		uint32_t img_w, uint32_t img_h);

extern void *lcdc_put_image(uint8_t layer, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void *lcdc_show_base(void *buffer, uint8_t bpp, bool bottom_up);

extern void lcdc_stop_base(void);

extern void *lcdc_show_ovr1(void *buffer, uint8_t bpp,
			   uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void lcdc_stop_ovr1(void);

extern void *lcdc_show_heo(void *buffer, uint8_t bpp,
			  uint32_t x, uint32_t y, int32_t w, int32_t h,
			  uint32_t memW, uint32_t memH);

extern void lcdc_stop_heo(void);

extern void lcdc_on(void);

extern void lcdc_off(void);

extern void lcdc_set_backlight(uint32_t step);

extern struct _lcdc_layer *lcdc_get_canvas(void);

extern uint8_t lcdc_select_canvas(uint8_t layer);

extern void *lcdc_create_canvas(uint8_t layer, void *buffer, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void lcdc_flush_canvas(void);

extern void lcdc_configure_input_mode(uint8_t layer, uint32_t input_mode);

extern void *lcdc_create_canvas_yuv_planar(uint8_t layer,
		void *buffer_y, void *buffer_u, void *buffer_v, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void *lcdc_create_canvas_yuv_semiplanar(uint8_t layer,
		void *buffer_y, void *buffer_uv, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h);

/**  @}*/

#endif /* CONFIG_HAVE_LCDC */

#endif /* #ifndef LCDC_H_ */
