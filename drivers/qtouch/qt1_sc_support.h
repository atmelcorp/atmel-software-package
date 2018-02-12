/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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
#ifndef _QT1_SC_SUPPORT_H
#define _QT1_SC_SUPPORT_H

#include "chip.h"

#ifdef CONFIG_BOARD_SAMA5D2_PTC_EK

/* ======== QT1 Xplained Pro (EXT1 & EXT2) device definition ======== */

/**
 * @brief Prepare COL IO for initialization
 */
#define QT1_XPRO_SC_PTC_COLS {	\
		PTC_COL0,		\
		PTC_COL1,		\
		PTC_COL2,		\
		PTC_COL3,		\
		PTC_COL4,		\
		PTC_COL5,		\
		PTC_COL6,		\
		PTC_COL7,		\
	}

/**
 * @brief Define the LED IOs of ATQT1 XPRO extension board
 */
#define QT1_XPRO_SC_PTC_LED0  { PIO_GROUP_B, PIO_PB9,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED1  { PIO_GROUP_C, PIO_PC0,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED2  { PIO_GROUP_D, PIO_PD17, PIO_OUTPUT_1, PIO_OPENDRAIN }

#define QT1_XPRO_SC_PTC_LED3  { PIO_GROUP_D, PIO_PD26, PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED4  { PIO_GROUP_D, PIO_PD3,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED5  { PIO_GROUP_D, PIO_PD4,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED6  { PIO_GROUP_D, PIO_PD5,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LED7  { PIO_GROUP_D, PIO_PD6,  PIO_OUTPUT_1, PIO_OPENDRAIN }

#define QT1_XPRO_SC_PTC_LEDB1 { PIO_GROUP_D, PIO_PD7,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LEDB2 { PIO_GROUP_D, PIO_PD8,  PIO_OUTPUT_1, PIO_OPENDRAIN }

#define QT1_XPRO_SC_PTC_LEDR  { PIO_GROUP_D, PIO_PD9,  PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LEDG  { PIO_GROUP_D, PIO_PD10, PIO_OUTPUT_1, PIO_OPENDRAIN }
#define QT1_XPRO_SC_PTC_LEDB  { PIO_GROUP_B, PIO_PB25, PIO_OUTPUT_1, PIO_OPENDRAIN }

/**
 * @brief Define the slider LEDs
 */
#define QT1_XPRO_SC_PTC_SLIDER_LEDS { \
		QT1_XPRO_SC_PTC_LED0,	\
		QT1_XPRO_SC_PTC_LED1,	\
		QT1_XPRO_SC_PTC_LED2,	\
		QT1_XPRO_SC_PTC_LED3,	\
		QT1_XPRO_SC_PTC_LED4,	\
		QT1_XPRO_SC_PTC_LED5,	\
		QT1_XPRO_SC_PTC_LED6,	\
		QT1_XPRO_SC_PTC_LED7,	\
	}

/**
 * @brief Define the button LEDs
 */
#define QT1_XPRO_SC_PTC_BUTTON_LEDS {	 \
		QT1_XPRO_SC_PTC_LEDB1, \
		QT1_XPRO_SC_PTC_LEDB2, \
	}

/**
 * @brief Define the wheel LEDs
 */
#define QT1_XPRO_SC_PTC_WHEEL_LEDS {		\
		QT1_XPRO_SC_PTC_LEDR,		\
		QT1_XPRO_SC_PTC_LEDG,		\
		QT1_XPRO_SC_PTC_LEDB,		\
	}

#else
#error "Board not supported..."
#endif

/**
 * @brief Initialize the LED and PTC COL IOs
 */
void qt1_xpro_sc_init(void);

/**
 * @brief Light ON button LEDs
 * @param led      [0, 1] LEDB1 or LEDB2
 */
void qt1_xpro_sc_set_button_led(unsigned char led);

/**
 * @brief Light OFF button LEDs
 * @param led      [0, 1] LEDB1 or LEDB2
 */
void qt1_xpro_sc_clear_button_led(unsigned char led);

/**
 * @brief Light ON button LEDs
 * @param led      [0, 1, 2] LED-RGB
 */
void qt1_xpro_sc_set_wheel_led(unsigned char led);

/**
 * @brief Light OFF button LEDs
 * @param led      [0, 1, 2] LED-RGB
 */
void qt1_xpro_sc_clear_wheel_led(unsigned char led);

/**
 * @brief Light ON button LEDs
 * @param led      [0, .., 7] LED0, .., LED7
 */
void qt1_xpro_sc_set_slider_led(unsigned char led);

/**
 * @brief Light OFF button LEDs
 * @param led      [0, .., 7] LED0, .., LED7
 */
void qt1_xpro_sc_clear_slider_led(unsigned char led);


void qt1_xpro_sc_get_rgb_val(uint16_t i,uint8_t *rgbptr);

#endif /* ! _QT1_SC_SUPPORT_H */
