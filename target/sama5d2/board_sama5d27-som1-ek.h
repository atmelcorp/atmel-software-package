/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

/** Name of the board */
#define BOARD_NAME "sama5d27-som1-ek"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 24000000

/** PMC PLLA configuration */
#define BOARD_PMC_PLLA_MUL 40
#define BOARD_PMC_PLLA_DIV 1

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE W971G16SG

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE 128*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition: use UART1 IOSET1 */
/* Note that these definitions could be omitted if the console is configured in
 * the active boot config word. */
#define BOARD_CONSOLE_ADDR     UART1
#define BOARD_CONSOLE_BAUDRATE 115200
#define BOARD_CONSOLE_TX_PIN   PIN_UART1_TXD_IOS1
#define BOARD_CONSOLE_RX_PIN   PIN_UART1_RXD_IOS1

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_RED   0
#define LED_GREEN 1
#define LED_BLUE  2

/** LED #0 pin definition (Red). */
#define PIN_LED_0 { PIO_GROUP_A, PIO_PA10, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (Green). */
#define PIN_LED_1 { PIO_GROUP_B, PIO_PB1, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #2 pin definition (Blue). */
#define PIN_LED_2 { PIO_GROUP_A, PIO_PA31, PIO_OUTPUT_1, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1, PIN_LED_2 }

#define NUM_LEDS  3

/* =================== PWM LED definition ====================== */

/** LED #0 PWM Channel */
//define PWM_LED_CH_0 0
//define PWM_ID_LED0 	ID_PWM0

/** LED #1 PWM Channel */
#define PWM_LED_CH_1 1
#define PWM_ID_LED1 ID_PWM0

/** LED #2 PWM Channel */
#define PWM_LED_CH_2 0
#define PWM_ID_LED2 ID_PWM0

/** LED #1 pin definition (Green). */
#define PIN_PWM_LED_1 { PIO_GROUP_B, PIO_PB1D_PWM0_L1, PIO_PERIPH_D, PIO_PULLUP }

/** LED #2 pin definition (Blue). */
#define PIN_PWM_LED_2 { PIO_GROUP_A, PIO_PA31D_PWM0_L0, PIO_PERIPH_D, PIO_PULLUP }

/** List of all PWM LED channels */
#define PWM_LEDS_CH { PWM_LED_CH_1, PWM_LED_CH_2 }

/** List of all LEDs definitions in PWM mode (red LED is not on a PWM pin) */
#define PINS_PWM_LEDS { PIN_PWM_LED_1, PIN_PWM_LED_2 }

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE)

#define PIN_PUSHBUTTON_1 { PIO_GROUP_A, PIO_PA29, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_USER 0

/* ================== TWI bus definition ====================== */

// TWI 24AA02E48 and CryptoATECC508
#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 150000 /* Warning Freq used by ECC508 WakeUp */
#define BOARD_TWI_BUS0_PINS PINS_TWI0_IOS4
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_POLLING

// TWI LCD and ISC
#define BOARD_TWI_BUS1      TWI1
#define BOARD_TWI_BUS1_FREQ 400000
#define BOARD_TWI_BUS1_PINS PINS_TWI1_IOS2
#define BOARD_TWI_BUS1_MODE BUS_TRANSFER_MODE_DMA

// TWI MBUS interface 1&2
#define BOARD_TWI_BUS2      FLEXTWI1
#define BOARD_TWI_BUS2_FREQ 400000
#define BOARD_TWI_BUS2_PINS PINS_FLEXCOM1_TWI_IOS1
#define BOARD_TWI_BUS2_MODE BUS_TRANSFER_MODE_POLLING

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0_PINS  {\
	PIN_FLEXCOM4_SPI_MOSI_IOS1, PIN_FLEXCOM4_SPI_MISO_IOS1, PIN_FLEXCOM4_SPI_SPCK_IOS1,\
	PIN_FLEXCOM4_SPI_NPCS0_IOS1, PIN_FLEXCOM4_SPI_NPCS1_IOS1 }
#define BOARD_SPI_BUS0       FLEXSPI4
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_POLLING

/* ================== PIN USB definition ======================= */

/** USB VBus pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_D, PIO_PD20, PIO_INPUT, PIO_DEBOUNCE | PIO_IT_BOTH_EDGE }

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR \
	{ PIO_GROUP_D, PIO_PD19, PIO_INPUT, PIO_DEFAULT }

/** USB Power Enable B, Active high  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_A, PIO_PA10, PIO_OUTPUT_0, PIO_DEFAULT }

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== PIN ISC definition ======================= */

#define BOARD_ISC_TWI_BUS  BUS(BUS_TYPE_I2C, 1)
#define BOARD_ISC_PINS     PINS_ISC_IOS1
#define BOARD_ISC_PIN_RST  { PIO_GROUP_D, PIO_PD6, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISC_PIN_PWD  { PIO_GROUP_D, PIO_PD7, PIO_OUTPUT_1, PIO_DEFAULT }


/* =================== SDMMC device definition ==================== */

#define BOARD_SDMMC0_PINS { PIN_SDMMC0_CD_IOS1, PIN_SDMMC0_CK_IOS1,\
                            PIN_SDMMC0_CMD_IOS1, PIN_SDMMC0_VDDSEL_IOS1,\
                            PINS_SDMMC0_DATA8B_IOS1, PIN_SDMMC0_WP_IOS1 }

/* Deviation from the SD Host Controller Specification: we use the Voltage
 * Support capabilities to indicate the supported signaling levels (VCCQ),
 * rather than the power supply voltage (VCC). */
#define BOARD_SDMMC0_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_V18VSUP | \
                            SDMMC_CA0R_SLTYPE_REMOVABLECARD | \
                            SDMMC_CA0R_ED8SUP)

#define BOARD_SDMMC1_PINS { PIN_SDMMC1_CD_IOS1, PIN_SDMMC1_CK_IOS1,\
                            PIN_SDMMC1_CMD_IOS1, PINS_SDMMC1_DATA4B_IOS1 }

#define BOARD_SDMMC1_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_SLTYPE_REMOVABLECARD)


/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x50
#define BOARD_AT24_MODEL   MCP24AA02E48

/* =================== QSPI serial flashdevice definition ======= */

// Optional QSPI, avalaible for protoytypes only

#define BOARD_QSPIFLASH_PINS     PINS_QSPI1_IOS2
#define BOARD_QSPIFLASH_ADDR     QSPI1
#define BOARD_QSPIFLASH_BAUDRATE 50000000 /* 50 MHz */

/* ================== MCAN bus definition ====================== */

#define BOARD_CAN_BUS0         MCAN0
#define BOARD_CAN_BUS0_PINS    PINS_CAN0_IOS1
#define BOARD_CAN_BUS0_FREQ    1000000
#define BOARD_CAN_BUS0_FREQ_FD 2000000

#define BOARD_CAN_BUS1         MCAN1
#define BOARD_CAN_BUS1_PINS    PINS_CAN1_IOS0
#define BOARD_CAN_BUS1_FREQ    1000000
#define BOARD_CAN_BUS1_FREQ_FD 2000000

/* =================== GMAC/PHY definition =================== */

#define PIN_PHY_IRQ {\
	{ PIO_GROUP_D, PIO_PD31, PIO_PERIPH_C, PIO_PULLUP | PIO_IT_FALL_EDGE },\
}

#define BOARD_ETH0_PINS        PINS_GMAC_RMII_IOS2
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    0
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_IRQ_PIN PIN_PHY_IRQ

/* ======================== LCD definition ======================== */

/** PIO pins for LCD */
#define BOARD_LCD_PINS              PINS_LCD_IOS1

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

#define TM4301

/* =================== MXTxxx device definition =================== */

#define BOARD_MXT_TWI_BUS BUS(BUS_TYPE_I2C, 1)
#define BOARD_MXT_ADDR    0x1B
#define BOARD_MXT_DESC    {"MXT", 0x00, 00}

/* ================= PIN LCD IRQ definition ===================== */

#define PIO_CFG_LCD_IRQ  (PIO_PULLUP | PIO_IT_FALL_EDGE)

#define PIN_MXT_IRQ  { PIO_GROUP_D, PIO_PD1, PIO_INPUT, PIO_PULLUP | PIO_IT_LOW_LEVEL}

#define PIN_QT1070_IRQ { PIO_GROUP_C, PIO_PC25, PIO_INPUT, PIO_CFG_LCD_IRQ  }

/* ================= PIN PMOD interface definition ===================== */

/*** Warning shared with pins ISC */
/************** Need to be updated

#define BOARD_SPI_BUSx    FLEXCOM3
#define PMOD_SPI_PINS     PIN_FLEXCOM3_SPI_NPCS0_IOS2
#define PMOD_SPI_ADDR     SPI1
#define PMOD_SPI_BAUDRATE 50000000

#define BOARD_TWI_BUSx      TWI1
#define BOARD_TWI_BUSx_FREQ 400000
#define BOARD_TWI_BUSx_PINS PINS_FLEXCOM3_TWI_IOS2
#define BOARD_TWI_BUSx_MODE TWID_MODE_DMA

#define BOARD_PMOD_SERIAL_PINS     PINS_FLEXCOM3_USART_HS_IOS2
#define BOARD_PMOD_SERIAL_ADDR     UART3
#define BOARD_PMOD_SERIAL_BAUDRATE 115200
*/

/* ================= PIN MBUS interface definition ===================== */
// MBUS1

#define PIN_MBUS1_AN  { PIO_GROUP_D, PIO_PD25, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS1_PWM  { PIO_GROUP_B, PIO_PB1, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS1_RST { PIO_GROUP_B, PIO_PB2, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS1_INT { PIO_GROUP_B, PIO_PB0, PIO_INPUT, PIO_PULLUP | PIO_IT_LOW_LEVEL }

#define BOARD_MBUS1_SERIAL_PINS     PINS_UART4_IOS1
#define BOARD_MBUS1_SERIAL_ADDR     UART4
#define BOARD_MBUS1_SERIAL_BAUDRATE 115200

// MBUS2

#define PIN_MBUS2_AN  { PIO_GROUP_D, PIO_PD26, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS2_PWM  { PIO_GROUP_A, PIO_PA31, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS2_RST { PIO_GROUP_A, PIO_PA26, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_MBUS2_INT { PIO_GROUP_A, PIO_PA25, PIO_INPUT, PIO_PULLUP | PIO_IT_LOW_LEVEL }

#define BOARD_MBUS2_SERIAL_PINS     PINS_UART2_IOS2
#define BOARD_MBUS2_SERIAL_ADDR     UART2
#define BOARD_MBUS2_SERIAL_BAUDRATE 115200

/* =========================== BOARD INFO  ============================= */

#define SIZE_SUBC 6
#define SIZE_MANUF_COUNTRY 3
#define SIZE_BOARD_IDENT 12
#define SIZE_HW_REVISION 3

struct _board_info {
	uint8_t page_size;
	uint8_t manufacturer[SIZE_SUBC];
	uint8_t country[SIZE_MANUF_COUNTRY];
	uint8_t manuf_year;
	uint8_t manuf_week;
	uint8_t rev_code[SIZE_HW_REVISION];
	uint8_t crc_sn;
	uint16_t addr_ext_config;
	uint8_t board_ident[SIZE_BOARD_IDENT];
	uint8_t rev_mapping;
	uint8_t crc;
};

#define AT24_INFO_SIZE sizeof(struct _board_info)

#endif /* #ifndef _BOARD_D2_H */
