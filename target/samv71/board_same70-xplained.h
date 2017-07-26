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

#ifndef _BOARD_SAME70_XPLAINED_H
#define _BOARD_SAME70_XPLAINED_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page same70_xplained_board_info "same70-xplained - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "same70-xplained"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** /def Definition of SDRAM type */
#define BOARD_DDRAM_TYPE         IS42S16100E

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    (2*1024*1024)

/** SDRAM pin definition */
#define BOARD_DDRAM_PINS {\
	PIN_SDRAM_D0_7, PIN_SDRAM_D8_13, PIN_SDRAM_D14_15,\
	PIN_SDRAM_A0_9, PIN_SDRAM_A10_ALT,\
	PIN_SDRAM_BA0, PIN_SDRAM_CAS, PIN_SDRAM_RAS,\
	PIN_SDRAM_SDCKE, PIN_SDRAM_SDCK, PIN_SDRAM_SDCS,\
	PIN_SDRAM_NBS0, PIN_SDRAM_NBS1, PIN_SDRAM_SDWE }

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

#define BOARD_CONSOLE_ADDR     USART1
#define BOARD_CONSOLE_BAUDRATE 115200
#define BOARD_CONSOLE_TX_PIN   PIN_USART1_TXD
#define BOARD_CONSOLE_RX_PIN   PIN_USART1_RXD

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_GREEN 0

/** LED #0 pin definition (Green). */
#define PIN_LED_0 { PIO_GROUP_C, PIO_PC8, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0 }

#define NUM_LEDS 1

/* =================== PIN PUSH BUTTON definition ============== */

#define PIN_PUSHBUTTON_1 { PIO_GROUP_A, PIO_PA11, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI0
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x57
#define BOARD_AT24_MODEL   AT24MAC402

/* ================== CAN bus definition ====================== */

#define BOARD_CAN_BUS0         MCAN0
#define BOARD_CAN_BUS0_PINS    PINS_CAN0
#define BOARD_CAN_BUS0_FREQ    1000000
#define BOARD_CAN_BUS0_FREQ_FD 2000000

#ifdef MCAN1
#define BOARD_CAN_BUS1         MCAN1
#define BOARD_CAN_BUS1_PINS    PINS_CAN1_IOS0
#define BOARD_CAN_BUS1_FREQ    1000000
#define BOARD_CAN_BUS1_FREQ_FD 2000000
#endif

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    1
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_A, PIO_PA14, PIO_INPUT, PIO_PULLUP }

/* =================== HSMCI device definition ==================== */

/** HSMCI Card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_C, PIO_PC16, PIO_INPUT, PIO_DEFAULT }

/** HSMCI0 device interface pin set definition */
#define BOARD_HSMCI0_DEV_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PIN_HSMCI0_DATA4B_A }

/** HSMCI0 pin set definition */
#define BOARD_HSMCI0_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PIN_HSMCI0_DATA4B_A, \
	  BOARD_HSMCI0_PIN_CD }

/** HSMCI0 slot definition */
#define BOARD_HSMCI0_SLOT 0

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/** USB VBus monitoring pin definition. */
#define PIN_USB_VBUS { PIO_GROUP_C, PIO_PC16, PIO_INPUT, PIO_DEFAULT }

#endif /* _BOARD_SAME70_XPLAINED_H */
