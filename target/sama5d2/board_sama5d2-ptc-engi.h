/**
 * \page sama5d2_ptc_engi_board_desc sama5d2-PTC-ENGI - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the sama5d2-PTC-ENGI board.
 *
 * \section Contents
 *
 *  - sama5d2-PTC-ENGI
 *  - For sama5d2-PTC-ENGI information, see \subpage sama5d2_ptc_engi_board_info.
 *  - For operating frequency information, see \subpage sama5d2_ptc_engi_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d2_ptc_engi_piodef.
 *  - For on-board memories, see \subpage sama5d2_ptc_engi_mem.
 *  - Several USB definitions are included here, see \subpage sama5d2_ptc_engi_usb.
 *  - For External components, see \subpage sama5d2_ptc_engi_extcomp.
 *  - For Individual chip definition, see \subpage sama5d2_ptc_engi_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sama5d2-PTC-ENGI board configuration, please have a look at the source file:
 * \ref board.h\n
 *
 * \section Usage
 *
 *  - The code for booting the board is provided by board_cstartup_xxx.c and
 *    board_lowlevel.c.
 *  - For using board PIOs, board characteristics (clock, etc.) and external
 *    components, see board.h.
 *  - For manipulating memories, see board_memories.h.
 *
 * This file can be used as a template and modified to fit a custom board, with
 * specific PIOs usage or memory connections.
 */

/**
 *  \file board.h
 *
 *  Definition of sama5d2-PTC-ENGI
 *  characteristics, sama5d4-dependant PIOs and external components interfacing.
 */

#ifndef _BOARD_D2_H
#define _BOARD_D2_H

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
 * \page sama5d2_ptc_engi_board_info "sama5d2-PTC-ENGI - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d2-ptc-engi"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT41K128M16

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    512*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition: use UART0 IOSET1 */
/* Note that these definitions could be omitted if the console is configured in
 * the active boot config word. */
#define BOARD_CONSOLE_ADDR     UART0
#define BOARD_CONSOLE_BAUDRATE 115200
#define BOARD_CONSOLE_TX_PIN   PIN_UART0_TXD_IOS1
#define BOARD_CONSOLE_RX_PIN   PIN_UART0_RXD_IOS1

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_RED   0
#define LED_GREEN 1
#define LED_BLUE  2

/** LED #0 pin definition (Red). */
#define PIN_LED_0 { PIO_GROUP_A, PIO_PA30, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** LED #1 pin definition (Green). */
#define PIN_LED_1 { PIO_GROUP_A, PIO_PA31, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** LED #2 pin definition (Blue). */
#define PIN_LED_2 { PIO_GROUP_B, PIO_PB2, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1, PIN_LED_2 }

#define NUM_LEDS  3

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE)

#define PIN_PUSHBUTTON_1 { PIO_GROUP_B, PIO_PB9, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* ================== TWI BUS definition ====================== */

#define BOARD_TWI_BUS0      FLEXTWI4
#define BOARD_TWI_BUS0_PINS PINS_FLEXCOM4_TWI_IOS3
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

#define BOARD_TWI_BUS1      TWI1
#define BOARD_TWI_BUS1_PINS PINS_TWI1_IOS1;
#define BOARD_TWI_BUS1_FREQ 400000
#define BOARD_TWI_BUS1_MODE BUS_TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0       SPI0
#define BOARD_SPI_BUS0_PINS  PINS_SPI0_NPCS0_IOS1
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_DMA

/* ================== ACT8945A PMIC definition ====================== */

#define BOARD_ACT8945A_TWI_BUS     BUS(BUS_TYPE_I2C, 0)
#define BOARD_ACT8945A_TWI_ADDR    0x5b
#define BOARD_ACT8945A_PIN_CHGLEV  { PIO_GROUP_A, PIO_PA22, PIO_OUTPUT_0, PIO_PULLUP }
#define BOARD_ACT8945A_PIN_IRQ     { PIO_GROUP_B, PIO_PB13, PIO_INPUT, PIO_PULLUP | PIO_IT_FALL_EDGE }
#define BOARD_ACT8945A_PIN_LBO     { PIO_GROUP_C, PIO_PC8, PIO_INPUT, PIO_PULLUP }

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x54
#define BOARD_AT24_MODEL   AT24MAC402

/* =================== AT25 device definition =================== */

#define BOARD_AT25_BUS         BUS(BUS_TYPE_SPI, 0)
#define BOARD_AT25_CHIP_SELECT 0
#define BOARD_AT25_BITRATE     40000
#define BOARD_AT25_DLYBS       0
#define BOARD_AT25_DLYBCT      0
#define BOARD_AT25_SPI_MODE    SPID_MODE_0

/* ================== PIN USB definition ======================= */

/** USB VBus pin */
#define PIN_USB_VBUS      {\
	{ PIO_GROUP_A, PIO_PA27, PIO_INPUT, PIO_DEBOUNCE | PIO_IT_BOTH_EDGE },\
}

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR     {\
	{ PIO_GROUP_A, PIO_PA29, PIO_INPUT, PIO_DEFAULT },\
}

/** USB Power Enable B, Active high  */
#define PIN_USB_POWER_ENB {\
	{ PIO_GROUP_A, PIO_PBA28, PIO_OUTPUT_0, PIO_DEFAULT },\
}

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== GMAC/PHY definition =================== */

#define GMAC0_ADDR        GMAC0
#define GMAC0_PINS        PINS_GMAC_RMII_IOS3
#define GMAC0_PHY_ADDR    0
#define GMAC0_PHY_IRQ_PIN PIN_GTSUCOM_IOS1
#define GMAC0_PHY_RETRIES PHY_DEFAULT_RETRIES

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC_RMII_IOS3
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    0
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_RETRIES PHY_DEFAULT_RETRIES
#define BOARD_ETH0_PHY_IRQ_PIN PIN_GTSUCOM_IOS1

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND8_IOS2
#define BOARD_NANDFLASH_BUS_WIDTH 8

#endif /* #ifndef _BOARD_D2_H */
