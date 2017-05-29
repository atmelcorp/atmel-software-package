/**
 * \page sama5d2_xult_board_desc sama5d2-XULT - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the sama5d2-XULT board.
 *
 * \section Contents
 *
 *  - sama5d2-XULT
 *  - For sama5d2-XULT information, see \subpage sama5d2_xult_board_info.
 *  - For operating frequency information, see \subpage sama5d2_xult_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d2_xult_piodef.
 *  - For on-board memories, see \subpage sama5d2_xult_mem.
 *  - Several USB definitions are included here, see \subpage sama5d2_xult_usb.
 *  - For External components, see \subpage sama5d2_xult_extcomp.
 *  - For Individual chip definition, see \subpage sama5d2_xult_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sama5d2-XULT board configuration, please have a look at the source file:
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
 *  Definition of sama5d2-xb
 *  characteristics, sama5d2-dependant PIOs and external components interfacing.
 */

#ifndef _BOARD_D2_H
#define _BOARD_D2_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page sama5d2_vb_board_info "sama5d2-vb - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d2-vb-bga196"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** PMC PLLA configuration */
#define BOARD_PMC_PLLA_MUL 82
#define BOARD_PMC_PLLA_DIV 1

/* no DDR defined by default for VB.  Please uncomment/edit the
 * BOARD_DDRAM_TYPE and BOARD_DDR_MEMORY_SIZE defines to enable it.
 */

/** /def Definition of DDRAM's type */
//#define BOARD_DDRAM_TYPE         MT41K128M16

/** \def Board DDR memory size in bytes */
//#define BOARD_DDR_MEMORY_SIZE    512*1024*1024

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
#define LED_RED   0    /* led red shared with SDMMC0 (eMMC) card detect used only by RomBoot */
#define LED_GREEN 1
#define LED_BLUE  2

/** LED #0 pin definition (Red). */
#define PIN_LED_0       { PIO_GROUP_D, PIO_PD21, PIO_OUTPUT_0, PIO_OPENDRAIN }

/** LED #1 pin definition (Green). */
#define PIN_LED_1       { PIO_GROUP_D, PIO_PD22, PIO_OUTPUT_0, PIO_OPENDRAIN }

/** List of all LEDs definitions. */
#define PINS_LEDS       { PIN_LED_0, PIN_LED_1 }

#define NUM_LEDS        2

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE)

#define PIN_PUSHBUTTON_1 { PIO_GROUP_D, PIO_PD19, PIO_INPUT, PIO_CFG_PB }

#define PIN_PUSHBUTTON_2 { PIO_GROUP_D, PIO_PD20, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2 }

/** Push button index. */
#define PUSHBUTTON_BP1 0
#define PUSHBUTTON_BP2 1

/* ================== PIN USB definition ======================= */

/** USB VBus pin */
#define PIN_USB_VBUS      {\
	{ PIO_GROUP_A, PIO_PA31, PIO_INPUT, PIO_DEFAULT },\
}
/** USB OverCurrent detection*/
#define PIN_USB_OVCUR     {\
	{ PIO_GROUP_A, PIO_PA29, PIO_INPUT, PIO_DEFAULT },\
}
/** USB Power Enable A, Active high */
#define PIN_USB_POWER_ENA {\
	{ PIO_GROUP_B, PIO_PB9, PIO_OUTPUT_0, PIO_DEFAULT },\
}
/** USB Power Enable B, Active high  */
#define PIN_USB_POWER_ENB {\
	{ PIO_GROUP_B, PIO_PB10, PIO_OUTPUT_0, PIO_DEFAULT },\
}

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== PIN ISC definition ======================= */

#define PIN_ISC_RST	{\
	{ PIO_GROUP_B, PIO_PB11, PIO_OUTPUT_1, PIO_DEFAULT },\
}
#define PIN_ISC_PWD	{\
	{ PIO_GROUP_B, PIO_PB12, PIO_OUTPUT_1, PIO_DEFAULT  },\
}

/* =================== PIN CAN definition ======================= */
/* CAN0 {PC1; PC2} is wired to the J18 connector via an AT6561 transceiver. */

#define CAN0_PINS          PINS_CAN0_IOS0

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND16_IOS1
#define BOARD_NANDFLASH_BUS_WIDTH 8

#endif /* #ifndef _BOARD_D2_H */
