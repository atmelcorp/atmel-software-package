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
#include "peripherals/bus.h"

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
#define LED_YELLOW0   0
#define LED_YELLOW1   1
#define LED_RED       1
#define LED_BLUE      1

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

/* =================== QSPI serial flashdevice definition ======= */

#define BOARD_QSPIFLASH_PINS     PINS_QSPI0
#define BOARD_QSPIFLASH_ADDR     QSPI0
#define BOARD_QSPIFLASH_BAUDRATE 50000000 /* 50 MHz */

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    1
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_A, PIO_PA19, PIO_INPUT, PIO_PULLUP }

/* =================== HSMCI device definition ==================== */

/** HSMCI Card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_D, PIO_PD18, PIO_INPUT, PIO_DEFAULT }

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

/** SSC definition */
#define BOARD_SSC0_PINS PINS_SSC0

/** WM8904 definition */
#define BOARD_WM8904_TWI_BUS      BUS(BUS_TYPE_I2C, 0)
#define BOARD_WM8904_SLAVE_ADDR   0x1a
#define BOARD_WM8904_INPUT_PATH   (WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN1R)
#define BOARD_WM8904_MCLK_PCK     2
#define BOARD_WM8904_MCLK_PCK_SRC PMC_PCK_CSS_SLOW_CLK
#define BOARD_WM8904_MCLK_PIN     PIN_PCK2_ALT1

#endif /* _BOARD_SAMV71_XPLAINED_H */
