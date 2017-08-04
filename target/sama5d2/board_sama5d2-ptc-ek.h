/**
 * \page sama5d2_ptc_ek_board_desc SAMA5D2-PTC-EK - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the SAMA5D2-PTC-EK board.
 *
 * \section Contents
 *
 *  - SAMA5D2-PTC-EK
 *  - For SAMA5D2-PTC-EK information, see \subpage sama5d2_ptc_ek_board_info.
 *  - For operating frequency information, see \subpage sama5d2_ptc_ek_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d2_ptc_ek_piodef.
 *  - For on-board memories, see \subpage SAMA5D2_ptc_ek_mem.
 *  - Several USB definitions are included here, see \subpage SAMA5D2_ptc_ek_usb.
 *  - For External components, see \subpage SAMA5D2_ptc_ek_extcomp.
 *  - For Individual chip definition, see \subpage SAMA5D2_ptc_ek_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * SAMA5D2-PTC-EK board configuration, please have a look at the source file:
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
 *  Definition of SAMA5D2-PTC-EK
 *  characteristics, SAMA5D2-dependant PIOs and external components interfacing.
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
 * \page SAMA5D2_ptc_ek_board_info "SAMA5D2-PTC-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d2-ptc-ek"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** PMC PLLA configuration */
#define BOARD_PMC_PLLA_MUL 82
#define BOARD_PMC_PLLA_DIV 1

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         W972GG6KB

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    256*1024*1024

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
#define PIN_LED_0 { PIO_GROUP_B, PIO_PB9, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** LED #1 pin definition (Green). */
#define PIN_LED_1 { PIO_GROUP_B, PIO_PB8, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** LED #2 pin definition (Blue). */
#define PIN_LED_2 { PIO_GROUP_B, PIO_PB6, PIO_OUTPUT_1, PIO_OPENDRAIN }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1, PIN_LED_2 }

#define NUM_LEDS  3

/* =================== PIN PUSH BUTTON definition ============== */

/** Connected to PIOBU */
#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE)

#define PIN_PUSHBUTTON_1 { PIO_GROUP_B, PIO_PB10, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* ================== TWI BUS definition ====================== */

/** Connected to EEPROM and XPRO */
#define BOARD_TWI_BUS0      TWI1
#define BOARD_TWI_BUS0_PINS PINS_TWI1_IOS1
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_MODE TRANSFER_MODE_DMA

/** Connected to Qtouch and mxt LCD */
#define BOARD_TWI_BUS1      FLEXTWI0
#define BOARD_TWI_BUS1_PINS PINS_FLEXCOM0_TWI_IOS1
#define BOARD_TWI_BUS1_FREQ 400000
#define BOARD_TWI_BUS1_MODE TRANSFER_MODE_DMA

#define BOARD_TWI_BUS2      FLEXTWI4
#define BOARD_TWI_BUS2_PINS PINS_FLEXCOM4_TWI_IOS3
#define BOARD_TWI_BUS2_FREQ 400000
#define BOARD_TWI_BUS2_MODE TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

/* SPI Flash type SST26VF032B Microchip */
#define BOARD_SPI_BUS0       SPI1
#define BOARD_SPI_BUS0_PINS  PINS_SPI1_NPCS0_IOS1
#define BOARD_SPI_BUS0_MODE  TRANSFER_MODE_DMA

/* #define BOARD_SPI_BUS1       SPI1 */
/* #define BOARD_SPI_BUS0_PINS  PINS_SPI1_NPCS0_IOS1 */
/* #define BOARD_SPI_BUS0_MODE  TRANSFER_MODE_POLLING */

/* ================== PIN USB definition ======================= */

/** USB VBus pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_B, PIO_PB11, PIO_INPUT, PIO_DEBOUNCE | PIO_IT_BOTH_EDGE }

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR \
	{ PIO_GROUP_B, PIO_PB13, PIO_INPUT, PIO_DEFAULT }

/** USB Power Enable B, Active high  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_B, PIO_PB12, PIO_OUTPUT_0, PIO_DEFAULT }

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== SDMMC device definition ==================== */

#define BOARD_SDMMC0_PINS { PIN_SDMMC0_CD_IOS1, PIN_SDMMC0_CK_IOS1,\
                            PIN_SDMMC0_CMD_IOS1, PIN_SDMMC0_RSTN_IOS1,\
                            PIN_SDMMC0_VDDSEL_IOS1, PINS_SDMMC0_DATA8B_IOS1 }

/* Deviation from the SD Host Controller Specification: we use the Voltage
 * Support capabilities to indicate the supported signaling levels (VCCQ),
 * rather than the power supply voltage (VCC). */
#define BOARD_SDMMC0_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_V18VSUP | \
                            SDMMC_CA0R_SLTYPE_EMBEDDED | \
                            SDMMC_CA0R_ED8SUP)

#define BOARD_SDMMC1_PINS { PIN_SDMMC1_CD_IOS1, PIN_SDMMC1_CK_IOS1,\
                            PIN_SDMMC1_CMD_IOS1, PINS_SDMMC1_DATA4B_IOS1 }

#define BOARD_SDMMC1_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_SLTYPE_REMOVABLECARD)

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x50
#define BOARD_AT24_MODEL   MCP24AA02E48

/* =================== AT25 device definition =================== */

#define BOARD_AT25_BUS         BUS(BUS_TYPE_SPI, 0)
#define BOARD_AT25_CHIP_SELECT 0
#define BOARD_AT25_BITRATE     40000
#define BOARD_AT25_DLYBS       0
#define BOARD_AT25_DLYBCT      0
#define BOARD_AT25_SPI_MODE    SPID_MODE_0

/* =================== QSPI serial flashdevice definition ======= */

#define BOARD_QSPIFLASH_PINS     PINS_QSPI0_IOS3
#define BOARD_QSPIFLASH_ADDR     QSPI0
#define BOARD_QSPIFLASH_BAUDRATE 50000000 /* 50 MHz */

/* =================== GMAC/PHY definition =================== */

#define PIN_PHY_INT {\
	{ PIO_GROUP_B, PIO_PB24, PIO_PERIPH_A, PIO_PULLUP | PIO_IT_FALL_EDGE },\
}

#define GMAC0_ADDR        GMAC0
#define GMAC0_PINS        PINS_GMAC_RMII_IOS3
#define GMAC0_PHY_ADDR    0
#define GMAC0_PHY_IRQ_PIN PIN_PHY_INT
#define GMAC0_PHY_RETRIES PHY_DEFAULT_RETRIES

/* =================== NANDFLASH device definition =================== */

/* WARNING: PIOs nand Flash shared with SDMMC0 */

#define BOARD_NANDFLASH_PINS      PINS_NAND8_IOS2
#define BOARD_NANDFLASH_BUS_WIDTH 8

/* ======================== LCD definition ======================== */

/** PIO pins for LCD */
#define BOARD_LCD_PINS              PINS_LCD_IOS2

/** Display width in pixels. */
#define BOARD_LCD_WIDTH             480
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            272
/** Frame rate in Hz. */
#define BOARD_LCD_FRAMERATE         40

/** Vertical front porch in number of lines. */
#define BOARD_LCD_TIMING_VFP        22
/** Vertical back porch in number of lines. */
#define BOARD_LCD_TIMING_VBP        21
/** Vertical pulse width in number of lines. */
#define BOARD_LCD_TIMING_VPW        2
/** Horizontal front porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HFP        64
/** Horizontal back porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HBP        64
/** Horizontal pulse width in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HPW        128


/* ================= PIN MIKROBUS interface definition ===================== */
/* MBUS1 */

/** Connected to mikroBUS */

#define PIN_MBUS1_AN  { PIO_GROUP_D, PIO_PD25, PIO_INPUT, PIO_PULLUP | PIO_IT_LOW_LEVEL }
#define PIN_MBUS1_PWM  { PIO_GROUP_D, PIO_PD20, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS1_RST { PIO_GROUP_A, PIO_PA29, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS1_INT { PIO_GROUP_D, PIO_PD19, PIO_INPUT, PIO_PULLUP | PIO_IT_LOW_LEVEL }

#define BOARD_MBUS1_SERIAL_PINS     PINS_UART2_IOS2
#define BOARD_MBUS1_SERIAL_ADDR     UART2
#define BOARD_MBUS1_SERIAL_BAUDRATE 115200

#endif /* #ifndef _BOARD_D2_H */
