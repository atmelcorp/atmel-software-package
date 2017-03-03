/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */
/*                                                                              */

#ifndef _CHIP_PINS_H_
#define _CHIP_PINS_H_

/*----------------------------------------------------------------------------
 *       PIOs Define
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
 * This pages lists all the pio definitions contained in chip.h.
 * The constants are named using the following convention: PIN_* for a constant
 * which defines a single Pin instance (but may include several PIOs sharing the
 * same controller), and PINS_* for a list of Pin instances.
 */

/* ========== Pio PIN definition for DBGU peripheral ========== */

/** DBGU TXD pin definition. */
#define PIN_DBGU_TXD { PIO_GROUP_B, PIO_PB31A_DTXD, PIO_PERIPH_A, PIO_DEFAULT }

/** DBGU RXD pin definition. */
#define PIN_DBGU_RXD { PIO_GROUP_B, PIO_PB30A_DRXD, PIO_PERIPH_A, PIO_DEFAULT }

/** DBGU pin definition. */
#define PINS_DBGU {\
	PIN_DBGU_TXD,\
	PIN_DBGU_RXD,\
}

/* ========== Pio PIN definition for PMC peripheral (PCK) ========== */

#define PIN_PCK0 { PIO_GROUP_D, PIO_PD30B_PCK0, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK1 { PIO_GROUP_D, PIO_PD31B_PCK1, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK2 { PIO_GROUP_C, PIO_PC15B_PCK2, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for UART0 peripheral ========== */

/** UART0 TXD pin definition. */
#define PIN_UART0_TXD { PIO_GROUP_C, PIO_PC30A_UTXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** UART0 RXD pin definition. */
#define PIN_UART0_RXD { PIO_GROUP_C, PIO_PC29A_URXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** UART0 pins definition. */
#define PINS_UART0 {\
	PIN_UART0_TXD,\
	PIN_UART0_RXD,\
}

/* ========== Pio PIN definition for UART1 peripheral ========== */

/** UART1 TXD pin definition. */
#define PIN_UART1_TXD { PIO_GROUP_A, PIO_PA31B_UTXD1, PIO_PERIPH_B, PIO_DEFAULT }

/** UART1 RXD pin definition. */
#define PIN_UART1_RXD { PIO_GROUP_A, PIO_PA30B_URXD1, PIO_PERIPH_B, PIO_DEFAULT }

/** UART1 pins definition. */
#define PINS_UART1 {\
	PIN_UART1_TXD,\
	PIN_UART1_RXD,\
}

/* ========== Pio PIN definition for USART0 peripheral ========== */

/** USART0 TXD pin definition. */
#define PIN_USART0_TXD { PIO_GROUP_D, PIO_PD18A_TXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RXD pin definition. */
#define PIN_USART0_RXD { PIO_GROUP_D, PIO_PD17A_RXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RTS pin definition. */
#define PIN_USART0_RTS { PIO_GROUP_D, PIO_PD16A_RTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 CTS pin definition. */
#define PIN_USART0_CTS { PIO_GROUP_D, PIO_PD15A_CTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 SCK pin definition. */
#define PIN_USART0_SCK { PIO_GROUP_D, PIO_PD14A_SCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 pins definition (default) */
#define PINS_USART0 \
	{ PIN_USART0_TXD, PIN_USART0_RXD }

/** USART0 pins definition (with handshake) */
#define PINS_USART0_HS \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS, PIN_USART0_CTS }

/** USART0 pins definition (synchronous) */
#define PINS_USART0_SYNC \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_SCK }

/** USART0 pins definition (synchronous with handshake) */
#define PINS_USART0_SYNC_HS \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS, PIN_USART0_CTS, PIN_USART0_SCK }

/** USART0 pins definition (ISO7816) */
#define PINS_USART0_ISO7816 \
	{ PIN_USART0_TXD, PIN_USART0_SCK }

/** USART0 pins definition (RS485) */
#define PINS_USART0_RS485 \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS }

/* ========== Pio PIN definition for USART1 peripheral ========== */

/** USART1 TXD pin definition. */
#define PIN_USART1_TXD { PIO_GROUP_B, PIO_PB29A_TXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RXD pin definition. */
#define PIN_USART1_RXD { PIO_GROUP_B, PIO_PB28A_RXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RTS pin definition. */
#define PIN_USART1_RTS { PIO_GROUP_B, PIO_PB27A_RTS1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 CTS pin definition. */
#define PIN_USART1_CTS { PIO_GROUP_B, PIO_PB26A_CTS1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 SCK pin definition. */
#define PIN_USART1_SCK { PIO_GROUP_B, PIO_PB25A_SCK1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 pins definition (default) */
#define PINS_USART1 \
	{ PIN_USART1_TXD, PIN_USART1_RXD }

/** USART1 pins definition (with handshake) */
#define PINS_USART1_HS \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS, PIN_USART1_CTS }

/** USART1 pins definition (synchronous) */
#define PINS_USART1_SYNC \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_SCK }

/** USART1 pins definition (synchronous with handshake) */
#define PINS_USART1_SYNC_HS \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS, PIN_USART1_CTS, PIN_USART1_SCK }

/** USART1 pins definition (ISO7816) */
#define PINS_USART1_ISO7816 \
	{ PIN_USART1_TXD, PIN_USART1_SCK }

/** USART1 pins definition (RS485) */
#define PINS_USART1_RS485 \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS }

/* ========== Pio PIN definition for USART2 peripheral ========== */

/** USART2 TXD pin definition. */
#define PIN_USART2_TXD { PIO_GROUP_E, PIO_PE26B_TXD2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 RXD pin definition. */
#define PIN_USART2_RXD { PIO_GROUP_E, PIO_PE25B_RXD2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 RTS pin definition. */
#define PIN_USART2_RTS { PIO_GROUP_E, PIO_PE24B_RTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 CTS pin definition. */
#define PIN_USART2_CTS { PIO_GROUP_E, PIO_PE23B_CTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 SCK pin definition. */
#define PIN_USART2_SCK { PIO_GROUP_E, PIO_PE20B_SCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 pins definition (default) */
#define PINS_USART2 \
	{ PIN_USART2_TXD, PIN_USART2_RXD }

/** USART2 pins definition (with handshake) */
#define PINS_USART2_HS \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS, PIN_USART2_CTS }

/** USART2 pins definition (synchronous) */
#define PINS_USART2_SYNC \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_SCK }

/** USART2 pins definition (synchronous with handshake) */
#define PINS_USART2_SYNC_HS \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS, PIN_USART2_CTS, PIN_USART2_SCK }

/** USART2 pins definition (ISO7816) */
#define PINS_USART2_ISO7816 \
	{ PIN_USART2_TXD, PIN_USART2_SCK }

/** USART2 pins definition (RS485) */
#define PINS_USART2_RS485 \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS }

/* ========== Pio PIN definition for USART3 peripheral ========== */

/** USART3 TXD pin definition. */
#define PIN_USART3_TXD { PIO_GROUP_E, PIO_PE19B_TXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RXD pin definition. */
#define PIN_USART3_RXD { PIO_GROUP_E, PIO_PE18B_RXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RTS pin definition. */
#define PIN_USART3_RTS { PIO_GROUP_E, PIO_PE17B_RTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 CTS pin definition. */
#define PIN_USART3_CTS { PIO_GROUP_E, PIO_PE16B_CTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 SCK pin definition. */
#define PIN_USART3_SCK { PIO_GROUP_E, PIO_PE15B_SCK3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 pins definition (default) */
#define PINS_USART3 \
	{ PIN_USART3_TXD, PIN_USART3_RXD }

/** USART3 pins definition (with handshake) */
#define PINS_USART3_HS \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS, PIN_USART3_CTS }

/** USART3 pins definition (synchronous) */
#define PINS_USART3_SYNC \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_SCK }

/** USART3 pins definition (synchronous with handshake) */
#define PINS_USART3_SYNC_HS \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS, PIN_USART3_CTS, PIN_USART3_SCK }

/** USART3 pins definition (ISO7816) */
#define PINS_USART3_ISO7816 \
	{ PIN_USART3_TXD, PIN_USART3_SCK }

/** USART3 pins definition (RS485) */
#define PINS_USART3_RS485 \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS }

/* ========== Pio PIN definition for TWI0 peripheral ========== */

/** TWI0 data pin */
#define PIN_TWI0_TWD { PIO_GROUP_A, PIO_PA30A_TWD0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 clock pin */
#define PIN_TWI0_TWCK { PIO_GROUP_A, PIO_PA31A_TWCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 pins */
#define PINS_TWI0 { PIN_TWI0_TWD, PIN_TWI0_TWCK }

/* ========== Pio PIN definition for TWI1 peripheral ========== */

/** TWI1 data pin */
#define PIN_TWI1_TWD { PIO_GROUP_C, PIO_PC26B_TWD1, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI1 clock pin */
#define PIN_TWI1_TWCK { PIO_GROUP_C, PIO_PC27B_TWCK1, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI1 pins */
#define PINS_TWI1 { PIN_TWI1_TWD, PIN_TWI1_TWCK }

/* ========== Pio PIN definition for TWI2 peripheral ========== */

/** TWI2 data pin */
#define PIN_TWI2_TWD { PIO_GROUP_A, PIO_PA18B_TWD2, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 clock pin */
#define PIN_TWI2_TWCK { PIO_GROUP_A, PIO_PA19B_TWCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 pins */
#define PINS_TWI2 { PIN_TWI2_TWD, PIN_TWI2_TWCK }

/* ========== Pio PIN definition for CAN0 peripheral ========== */

/** CAN0 pin TX */
#define PIN_CAN0_TX { PIO_GROUP_D, PIO_PD15C_CANTX0, PIO_PERIPH_C, PIO_DEFAULT }

/** CAN0 pin RX */
#define PIN_CAN0_RX { PIO_GROUP_D, PIO_PD14C_CANRX0, PIO_PERIPH_C, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN0 { PIN_CAN0_TX, PIN_CAN0_RX }

/* ========== Pio PIN definition for CAN1 peripheral ========== */

/** CAN1 pin TX */
#define PIN_CAN1_TX { PIO_GROUP_B, PIO_PB15B_CANTX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN1 pin RX */
#define PIN_CAN1_RX { PIO_GROUP_B, PIO_PB14B_CANRX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN1 { PIN_CAN1_TX, PIN_CAN1_RX }

/* ========== Pio PIN definition for SPI0 peripheral ========== */

/** SPI0 MISO pin definition. */
#define PIN_SPI0_MISO { PIO_GROUP_D, PIO_PD10A_SPI0_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 MOSI pin definition. */
#define PIN_SPI0_MOSI { PIO_GROUP_D, PIO_PD11A_SPI0_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 SPCK pin definition. */
#define PIN_SPI0_SPCK { PIO_GROUP_D, PIO_PD12A_SPI0_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 0 pin definition. */
#define PIN_SPI0_NPCS0 { PIO_GROUP_D, PIO_PD13A_SPI0_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 1 pin definition. */
#define PIN_SPI0_NPCS1 { PIO_GROUP_D, PIO_PD14B_SPI0_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 2 pin definition. */
#define PIN_SPI0_NPCS2 { PIO_GROUP_D, PIO_PD15B_SPI0_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 3 pin definition. */
#define PIN_SPI0_NPCS3 { PIO_GROUP_D, PIO_PD16B_SPI0_NPCS3, PIO_PERIPH_B, PIO_DEFAULT }

/** List of SPI0 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI0_NPCS0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS0 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI0_NPCS1 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS1 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI0_NPCS2 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS2 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS3). */
#define PINS_SPI0_NPCS3 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS3 }

/* ========== Pio PIN definition for SPI1 peripheral ========== */

/** SPI1 MISO pin definition. */
#define PIN_SPI1_MISO { PIO_GROUP_C, PIO_PC22A_SPI1_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 MOSI pin definition. */
#define PIN_SPI1_MOSI { PIO_GROUP_C, PIO_PC23A_SPI1_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 SPCK pin definition. */
#define PIN_SPI1_SPCK { PIO_GROUP_C, PIO_PC24A_SPI1_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 0 pin definition. */
#define PIN_SPI1_NPCS0 { PIO_GROUP_C, PIO_PC25A_SPI1_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 1 pin definition. */
#define PIN_SPI1_NPCS1 { PIO_GROUP_C, PIO_PC26A_SPI1_NPCS1, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 2 pin definition. */
#define PIN_SPI1_NPCS2 { PIO_GROUP_C, PIO_PC27A_SPI1_NPCS2, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 3 pin definition. */
#define PIN_SPI1_NPCS3 { PIO_GROUP_C, PIO_PC28A_SPI1_NPCS3, PIO_PERIPH_A, PIO_DEFAULT }

/** List of SPI1 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI1_NPCS0 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS0 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI1_NPCS1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS1 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS2 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS2 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS3 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS3 }

/* ========== Pio PIN definition for SSC0 peripheral ========== */

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD0 { PIO_GROUP_C, PIO_PC18A_TD0, PIO_PERIPH_A, PIO_DEFAULT }

/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK0 { PIO_GROUP_C, PIO_PC16A_TK0, PIO_PERIPH_A, PIO_DEFAULT }

/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF0 { PIO_GROUP_C, PIO_PC17A_TF0, PIO_PERIPH_A, PIO_DEFAULT }

/** SSC pin RD */
#define PIN_SSC_RD0 { PIO_GROUP_C, PIO_PC21A_RD0, PIO_PERIPH_A, PIO_DEFAULT }

/** SSC pin RK */
#define PIN_SSC_RK0 { PIO_GROUP_C, PIO_PC19A_RK0, PIO_PERIPH_A, PIO_DEFAULT }

/** SSC pin RF */
#define PIN_SSC_RF0 { PIO_GROUP_C, PIO_PC20A_RF0, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for SSC1 peripheral ========== */

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD1 { PIO_GROUP_B, PIO_PB6, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK1 { PIO_GROUP_B, PIO_PB2, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF1 { PIO_GROUP_B, PIO_PB3, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RD */
#define PIN_SSC_RD1 { PIO_GROUP_B, PIO_PB11, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RK */
#define PIN_SSC_RK1 { PIO_GROUP_B, PIO_PB7, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RF */
#define PIN_SSC_RF1 { PIO_GROUP_B, PIO_PB10, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pins definition for codec. */
#define PINS_SSC0 { PIN_SSC_TD0,  PIN_SSC_TK0, PIN_SSC_TF0, PIN_SSC_RD0, PIN_SSC_RK0, PIN_SSC_RF0 }

#define PINS_SSC1 { PIN_SSC_TD1,  PIN_SSC_TK1, PIN_SSC_TF1, PIN_SSC_RD1, PIN_SSC_RK1, PIN_SSC_RF1 }

/* ========== Pio PIN definition for LCDC peripheral ========== */

/** LCD pin list. */

/* LCD 24 bits */
#define PINS_LCD {\
	{ PIO_GROUP_A, 0x3FFFFFFF, PIO_PERIPH_A, PIO_DEFAULT }\
}

/* LCD 24 bits (alternate configuration) */
#define PINS_LCD_ALT {\
	{ PIO_GROUP_A, 0x3F00FFFF, PIO_PERIPH_A, PIO_DEFAULT},\
	{ PIO_GROUP_C, 0x0000FC00, PIO_PERIPH_C, PIO_DEFAULT},\
	{ PIO_GROUP_E, 0x18000000, PIO_PERIPH_C, PIO_DEFAULT},\
}

/* ========== Pio PIN definition for ADC peripheral ========== */

#define PIN_AD0  { PIO_GROUP_D, PIO_PD20_AD0,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD1  { PIO_GROUP_D, PIO_PD21_AD1,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD2  { PIO_GROUP_D, PIO_PD22_AD2,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD3  { PIO_GROUP_D, PIO_PD23_AD3,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD4  { PIO_GROUP_D, PIO_PD24_AD4,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD5  { PIO_GROUP_D, PIO_PD25_AD5,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD6  { PIO_GROUP_D, PIO_PD26_AD6,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD7  { PIO_GROUP_D, PIO_PD27_AD7,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD8  { PIO_GROUP_D, PIO_PD28_AD8,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD9  { PIO_GROUP_D, PIO_PD29_AD9,  PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD10 { PIO_GROUP_D, PIO_PD30_AD10, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_AD11 { PIO_GROUP_D, PIO_PD31_AD11, PIO_PERIPH_A, PIO_DEFAULT }

/** ADC ADTRG pin (PD19). */
#define PIN_ADTRG { PIO_GROUP_D, PIO_PD19A_ADTRG, PIO_PERIPH_A, PIO_PULLUP }

/* ========== Pio PIN definition for GMAC peripheral ========== */

/** GMAC0 MII pin list */
#define PINS_GMAC0_MII  { { PIO_GROUP_B, 0x0003FFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/** GMAC0 GMII pin list */
#define PINS_GMAC0_GMII { \
	{ PIO_GROUP_B, 0x0007FEFF, PIO_PERIPH_A, PIO_DEFAULT }, \
	{ PIO_GROUP_B, 0x0FF80000, PIO_PERIPH_B, PIO_DEFAULT }, \
}

/** GMAC0 RGMII pin list */
#define PINS_GMAC0_RGMII { { PIO_GROUP_B, 0x00072BFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for EMAC0 peripheral ========== */

/** EMAC pin list */
#define PINS_EMAC0  { { PIO_GROUP_C, 0x000003FF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for NAND peripheral ========== */

/* 8-bit NAND: NANDALE, NANDCLE (other I/O are not muxed by PIO controller ) */
#define PINS_NAND8 { { PIO_GROUP_E, PIO_PE21 | PIO_PE22, PIO_PERIPH_A, PIO_DEFAULT } }

/* 16-bit NAND: NANDALE, NANDCLE (other I/O are not muxed by PIO controller ) */
#define PINS_NAND16 { { PIO_GROUP_E, PIO_PE21 | PIO_PE22, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for ISI peripheral ========== */

/** Image Sensor Interface vertical sync. */
#define PIN_ISI_VSYNC { PIO_GROUP_A, PIO_PA30C_ISI_VSYNC, PIO_PERIPH_C, PIO_DEFAULT }

/** Image Sensor Interface horizontal sync. */
#define PIN_ISI_HSYNC { PIO_GROUP_A, PIO_PA31C_ISI_HSYNC, PIO_PERIPH_C, PIO_DEFAULT }

/** Image Sensor Interface data clock. */
#define PIN_ISI_PCK { PIO_GROUP_C, PIO_PC30C_ISI_PCK, PIO_PERIPH_C, PIO_DEFAULT }

/** Image Sensor Interface data pins (8-bit) */
#define PINS_ISI_DATA_8BIT { PIO_GROUP_A, 0x00FF0000, PIO_PERIPH_C, PIO_DEFAULT }

/** Image Sensor Interface data pins (12-bit) */
#define PINS_ISI_DATA_12BIT PINS_ISI_DATA_8BIT,\
                            { PIO_GROUP_C, 0x3C000000, PIO_PERIPH_C, PIO_DEFAULT }

/** Image Sensor Interface pin list (8-bit data) */
#define PINS_ISI_8BIT { PIN_ISI_VSYNC, PIN_ISI_HSYNC, PIN_ISI_PCK, PINS_ISI_DATA_8BIT }

/** Image Sensor Interface pin list (12-bit data) */
#define PINS_ISI_12BIT { PIN_ISI_VSYNC, PIN_ISI_HSYNC, PIN_ISI_PCK, PINS_ISI_DATA_12BIT }

/* ========== Pio PIN definition for HSMCI0 peripheral ========== */

/** HSMCI0 pin Card Command slot A (CDA) */
#define PIN_HSMCI0_CMD_A { PIO_GROUP_D, PIO_PD0A_MCI0_CDA, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI0 pin Card Clock (CK) */
#define PIN_HSMCI0_CK { PIO_GROUP_D, PIO_PD9A_MCI0_CK, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI0 pin 1-bit Data slot A (DA0) */
#define PINS_HSMCI0_DATA1B_A { PIO_GROUP_D, 0x00000002, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI0 pin 4-bit Data slot A (DA0-3) */
#define PINS_HSMCI0_DATA4B_A { PIO_GROUP_D, 0x0000001E, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI0 pin 8-bit Data slot A (DA0-7) */
#define PINS_HSMCI0_DATA8B_A { PIO_GROUP_D, 0x000001FE, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for HSMCI1 peripheral ========== */

/** HSMCI1 pin Card Command slot A (CDA) */
#define PIN_HSMCI1_CMD_A { PIO_GROUP_B, PIO_PB19A_MCI1_CDA, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI1 pin Card Clock (CK) */
#define PIN_HSMCI1_CK { PIO_GROUP_B, PIO_PB24A_MCI1_CK, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI1 pin 1-bit Data slot A (DA0) */
#define PINS_HSMCI1_DATA1B_A { PIO_GROUP_B, 0x00100000, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI1 pin 4-bit Data slot A (DA0-3) */
#define PINS_HSMCI1_DATA4B_A { PIO_GROUP_B, 0x00F00000, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for HSMCI2 peripheral ========== */

/** HSMCI2 pin Card Command slot A (CDA) */
#define PIN_HSMCI2_CMD_A { PIO_GROUP_C, PIO_PC10A_MCI2_CDA, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI2 pin Card Clock (CK) */
#define PIN_HSMCI2_CK { PIO_GROUP_C, PIO_PC15A_MCI2_CK, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI2 pin 1-bit Data slot A (DA0) */
#define PINS_HSMCI2_DATA1B_A { PIO_GROUP_C, 0x00000800, PIO_PERIPH_A, PIO_DEFAULT }

/** HSMCI2 pin 4-bit Data slot A (DA0-3) */
#define PINS_HSMCI2_DATA4B_A { PIO_GROUP_C, 0x00007800, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for TC0 peripheral ========== */

#define PIN_TC0_TCLK0 { PIO_GROUP_D, PIO_PD7B_TCLK0,  PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TCLK1 { PIO_GROUP_C, PIO_PC14B_TCLK1, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TCLK2 { PIO_GROUP_E, PIO_PE29B_TCLK2, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOA0 { PIO_GROUP_D, PIO_PD5B_TIOA0,  PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOA1 { PIO_GROUP_C, PIO_PC12B_TIOA1, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOA2 { PIO_GROUP_E, PIO_PE27B_TIOA2, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOB0 { PIO_GROUP_D, PIO_PD6B_TIOB0,  PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOB1 { PIO_GROUP_C, PIO_PC13B_TIOB1, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC0_TIOB2 { PIO_GROUP_E, PIO_PE28B_TIOB2, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for TC1 peripheral ========== */

#define PIN_TC1_TCLK3 { PIO_GROUP_C, PIO_PC2B_TCLK3, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TCLK4 { PIO_GROUP_C, PIO_PC5B_TCLK4, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TCLK5 { PIO_GROUP_C, PIO_PC8B_TCLK5, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOA3 { PIO_GROUP_C, PIO_PC0B_TIOA3, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOA4 { PIO_GROUP_C, PIO_PC3B_TIOA4, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOA5 { PIO_GROUP_C, PIO_PC6B_TIOA5, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOB3 { PIO_GROUP_C, PIO_PC1B_TIOB3, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOB4 { PIO_GROUP_C, PIO_PC4B_TIOB4, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_TC1_TIOB5 { PIO_GROUP_C, PIO_PC7B_TIOB5, PIO_PERIPH_B, PIO_DEFAULT }

#endif /* _CHIP_PINS_H_ */
