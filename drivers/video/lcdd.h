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
 * -# LCDD_On() and LCDD_Off() is used to turn LCD ON/OFF.
 * -# LCDD_SetBacklight() is used to change LCD backlight level.
 * -# To display a image (BMP format) on LCD, LCDD_ShowBMPRotated()
 *    LCDD_ShowBMPScaled() and LCDD_ShowBMP() can be used.
 * -# To change configuration for an overlay layer, the following functions
 *    can use:
 *    -# LCDD_EnableLayer(), LCDD_IsLayerOn(): Turn ON/OFF layer, check status.
 *    -# LCDD_SetPosition(), LCDD_SetPrioty(), LCDD_EnableAlpha(),
 *       LCDD_SetAlpha(), LCDD_SetColorKeying(): Change display options.
 * -# Shortcuts for layer display are as following:
 *    -# LCDD_ShowBase(), LCDD_StopBase()
 *    -# LCDD_ShowOvr1(), LCDD_StopOvr1()
 *    -# LCDD_ShowHeo(), LCDD_StopHeo()
 *    -# LCDD_ShowHcr(), LCDD_StopHcr()
 * -# Drawing supporting functions, for drawing canvas:
 *    -# LCDD_CreateCanvas(): Create blank canvas on specified layer for
 *                            drawing on
 *    -# LCDD_SelectCanvas(): Select a displayer as canvas to drawing on
 *    -# LCDD_GetCanvas():    Get current selected canvas layer
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

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _pin;

/** LCD display layer information */
typedef struct _LcddLayer {
	void *pBuffer;	    /**< Display image buffer */
	uint16_t wImgW;	    /**< Display image width */
	uint16_t wImgH;	    /**< Display image height */
	uint8_t bMode;	    /**< Image bpp (16,24,32) for RGB mode */
	uint8_t bLayer;	    /**< Layer ID */
} sLCDDLayer;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void lcdd_initialize(const struct _pin* pins, uint32_t pin_len);
extern uint8_t lcdd_is_layer_on(uint8_t bLayer);
extern void lcdd_enable_layer(uint8_t bLayer, uint8_t bEnDis);
extern void lcdd_refresh(uint8_t bLayer);
extern void lcdd_set_position(uint8_t bLayer, uint32_t x, uint32_t y);
extern void lcdd_set_prioty(uint8_t bLayer, uint8_t bPri);
extern uint8_t lcdd_get_prioty(uint8_t bLayer);
extern void lcdd_enable_alpha(uint8_t bLayer, uint8_t bEnDisLA,
			     uint8_t bEnDisGA);
extern void lcdd_set_alpha(uint8_t bLayer, uint8_t bReverse, uint8_t bAlpha);
extern uint8_t lcdd_get_alpha(uint8_t bLayer);
extern void lcdd_set_color_keying(uint8_t bLayer,
				uint8_t bDstSrc,
				uint32_t dwColor, uint32_t dwMask);
extern void lcdd_disable_color_keying(uint8_t bLayer);
extern void lcdd_set_color_lut(uint8_t bLayer,
			 uint32_t * pCLUT, uint8_t bpp, uint8_t nbColors);
extern void *lcdd_show_bmp_rotated(uint8_t bLayer,
				 void *pBuffer, uint8_t bpp,
				 uint32_t x, uint32_t y, int32_t w, int32_t h,
				 uint32_t imgW, uint32_t imgH, int16_t wRotate);
extern void *lcdd_show_bmp_scaled(uint8_t bLayer,
				void *pBuffer, uint8_t bpp,
				uint32_t x, uint32_t y, int32_t w, int32_t h,
				uint32_t imgW, uint32_t imgH);
extern void *lcdd_show_bmp(uint8_t bLayer,
			  void *pBuffer, uint8_t bpp,
			  uint32_t x, uint32_t y, int32_t w, int32_t h);

extern void *lcdd_show_base(void *pBuffer, uint8_t bpp, uint8_t bScanBottomUp);
extern void lcdd_stop_base(void);

extern void *lcdd_show_ovr1(void *pBuffer, uint8_t bpp,
			   uint32_t x, uint32_t y, int32_t w, int32_t h);
extern void lcdd_stop_ovr1(void);

extern void *lcdd_show_heo(void *pBuffer, uint8_t bpp,
			  uint32_t x, uint32_t y, int32_t w, int32_t h,
			  uint32_t memW, uint32_t memH);
extern void lcdd_stop_heo(void);
extern void lcdd_on(void);
extern void lcdd_off(void);
extern void lcdd_set_backlight(uint32_t step);
extern void *lcdd_show_hcr(void *pBuffer, uint8_t bpp,
			  uint32_t x, uint32_t y, int32_t w, int32_t h);
extern void lcdd_stop_hcr(void);
extern sLCDDLayer *lcdd_get_canvas(void);
extern uint8_t lcdd_select_canvas(uint8_t bLayer);
extern void *lcdd_create_canvas(uint8_t bLayer,
			       void *pBuffer, uint8_t bBPP,
			       uint16_t wX, uint16_t wY, uint16_t wW,
			       uint16_t wH);
extern void lcdd_flush_canvas(void);
extern void lcdc_configure_inputMode(uint8_t bLayer, uint32_t inputMode);
extern void * lcdd_create_canvas_yuv_planar(uint8_t bLayer,
		  void *pBuffer, void *pBufferUV, void *pBufferV, uint8_t bBPP,
		  uint16_t wX, uint16_t wY, uint16_t wW, uint16_t wH);

/**  @}*/
#endif				/* #ifndef LCDD_H */
