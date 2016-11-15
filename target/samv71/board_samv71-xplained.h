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

#ifndef _BOARD_SAMV71_XPLAINED_H
#define _BOARD_SAMV71_XPLAINED_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page samv71_xplained_board_info "samv71-xplained - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "samv71-xplained"

/*----------------------------------------------------------------------------*/

/** Frequency of the board slow clock oscillator */
#define BOARD_SLOW_CLOCK_EXT_OSC 32768

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** \def Board System timer resolution */
#define BOARD_TIMER_TC          TC1
#define BOARD_TIMER_CHANNEL     0
#define BOARD_TIMER_FREQ        1000     // IRQ frequency (1kHz)
#define BOARD_TIMER_RESOLUTION	1000000  // Precision: 1MHz

/* =================== PIN CONSOLE definition ================== */

#define BOARD_CONSOLE_PINS     PINS_USART0
#define BOARD_CONSOLE_ADDR     USART0
#define BOARD_CONSOLE_BAUDRATE 115200

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_YELLOW0   0
#define LED_YELLOW1   1

/** LED #0 pin definition (Yellow). */
#define PIN_LED_0 { PIO_GROUP_A, PIO_PA23, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** LED #1 pin definition (Yellow). */
#define PIN_LED_1 { PIO_GROUP_C, PIO_PC9, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1 }

#define NUM_LEDS 2

/* =================== PIN PUSH BUTTON definition ============== */

#define PIN_PUSHBUTTON_1 { PIO_GROUP_A, PIO_PA9, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE }
#define PIN_PUSHBUTTON_2 { PIO_GROUP_B, PIO_PB12, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2 }

/** Push button index. */
#define PUSHBUTTON_BP1 0
#define PUSHBUTTON_BP2 1

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI0
#define BOARD_TWI_BUS0_MODE TWID_MODE_DMA

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS 0
#define BOARD_AT24_ADDR    0x57
#define BOARD_AT24_MODEL   AT24MAC402

/* =================== QSPI serial flashdevice definition ======= */

#define QSPIFLASH_PINS     PINS_QSPI0
#define QSPIFLASH_ADDR     QSPI0
#define QSPIFLASH_BAUDRATE 50000000 /* 50 MHz */

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    1
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_RETRIES PHY_DEFAULT_RETRIES
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_A, PIO_PA19, PIO_INPUT, PIO_PULLUP }

#endif /* _BOARD_SAMV71_XPLAINED_H */
