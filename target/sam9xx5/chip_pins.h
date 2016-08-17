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

/** DBGU Monitor IO pin (detect any DBGU operation). */
#define PIN_DBGU_MON { PIO_GROUP_A, PIO_PA9A_DRXD, PIO_INPUT, PIO_IT_RISE_EDGE }

/** DBGU pin definition. */
#define PINS_DBGU {\
	{ PIO_GROUP_A, PIO_PA9A_DRXD | PIO_PA10A_DTXD, PIO_PERIPH_A, PIO_DEFAULT },\
}

/* ========== Pio PIN definition for PMC peripheral ========== */

#define PIN_PCK0 { PIO_GROUP_B, PIO_PB10B_PCK0, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK1 { PIO_GROUP_B, PIO_PB9B_PCK1, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK1_ALT { PIO_GROUP_C, PIO_PC31C_PCK1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for USART peripheral ========== */

/** USART0 TXD pin definition. */
#define PIN_USART0_TXD { PIO_GROUP_A, PIO_PA0A_TXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RXD pin definition. */
#define PIN_USART0_RXD { PIO_GROUP_A, PIO_PA1A_RXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RTS pin definition. */
#define PIN_USART0_RTS { PIO_GROUP_A, PIO_PA2A_RTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 CTS pin definition. */
#define PIN_USART0_CTS { PIO_GROUP_A, PIO_PA3A_CTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 SCK pin definition. */
#define PIN_USART0_SCK { PIO_GROUP_A, PIO_PA4A_SCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 pins definition. */
#define PINS_USART0 {\
	PIN_USART0_TXD,\
	PIN_USART0_RXD,\
	PIN_USART0_RTS,\
	PIN_USART0_CTS,\
	PIN_USART0_SCK,\
}

/** USART1 TXD pin definition. */
#define PIN_USART1_TXD { PIO_GROUP_A, PIO_PA5A_TXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RXD pin definition. */
#define PIN_USART1_RXD { PIO_GROUP_A, PIO_PA6A_RXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RTS pin definition. */
#define PIN_USART1_RTS { PIO_GROUP_C, PIO_PC27C_RTS1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 CTS pin definition. */
#define PIN_USART1_CTS { PIO_GROUP_C, PIO_PC28C_CTS1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 SCK pin definition. */
#define PIN_USART1_SCK { PIO_GROUP_C, PIO_PC29C_SCK1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 pins definition. */
#define PINS_USART1 {\
	PIN_USART1_TXD,\
	PIN_USART1_RXD,\
	PIN_USART1_RTS,\
	PIN_USART1_CTS,\
	PIN_USART1_SCK,\
}

/** USART2 TXD pin definition. */
#define PIN_USART2_TXD { PIO_GROUP_A, PIO_PA7A_TXD2, PIO_PERIPH_A, PIO_DEFAULT }

/** USART2 RXD pin definition. */
#define PIN_USART2_RXD { PIO_GROUP_A, PIO_PA8A_RXD2, PIO_PERIPH_A, PIO_DEFAULT }

/** USART2 RTS pin definition. */
#define PIN_USART2_RTS { PIO_GROUP_B, PIO_PB0B_RTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 CTS pin definition. */
#define PIN_USART2_CTS { PIO_GROUP_B, PIO_PB1B_CTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 SCK pin definition. */
#define PIN_USART2_SCK { PIO_GROUP_B, PIO_PB2B_SCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 pins definition. */
#define PINS_USART2 {\
	PIN_USART2_TXD,\
	PIN_USART2_RXD,\
	PIN_USART2_RTS,\
	PIN_USART2_CTS,\
	PIN_USART2_SCK,\
}

/** USART3 TXD pin definition. */
#define PIN_USART3_TXD { PIO_GROUP_C, PIO_PC22B_TXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RXD pin definition. */
#define PIN_USART3_RXD { PIO_GROUP_C, PIO_PC23B_RXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RTS pin definition. */
#define PIN_USART3_RTS { PIO_GROUP_C, PIO_P24B_RTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 CTS pin definition. */
#define PIN_USART3_CTS { PIO_GROUP_C, PIO_PC25B_CTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 SCK pin definition. */
#define PIN_USART3_SCK { PIO_GROUP_C, PIO_PC26B_SCK3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 pins definition. */
#define PINS_USART3 {\
	PIN_USART3_TXD,\
	PIN_USART3_RXD,\
	PIN_USART3_RTS,\
	PIN_USART3_CTS,\
	PIN_USART3_SCK,\
}

/* ========== Pio PIN definition for TWI peripheral ========== */

/** TWI0 data pin */
#define PIN_TWI_TWD0 { PIO_GROUP_A, PIO_PA30A_TWD0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 clock pin */
#define PIN_TWI_TWCK0 { PIO_GROUP_A, PIO_PA31A_TWCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 pins */
#define PINS_TWI0 { PIN_TWI_TWD0, PIN_TWI_TWCK0 }

/** TWI1 data pin */
#define PIN_TWI_TWD1 { PIO_GROUP_C, PIO_PC0C_TWD1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 clock pin */
#define PIN_TWI_TWCK1 { PIO_GROUP_C, PIO_PC1C_TWCK1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 pins */
#define PINS_TWI1 { PIN_TWI_TWD1, PIN_TWI_TWCK1 }

/** TWI2 data pin */
#define PIN_TWI_TWD2 { PIO_GROUP_B, PIO_PB4B_TWD1, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 clock pin */
#define PIN_TWI_TWCK2 { PIO_GROUP_B, PIO_PB5B_TWCK1, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 pins */
#define PINS_TWI2 { PIN_TWI_TWD2, PIN_TWI_TWCK2 }

/* ========== Pio PIN definition for CAN peripheral ========== */

/** CAN0 pin TX */
#define PIN_CAN0_TX     { PIO_GROUP_A, PIO_PA10B_CANTX0, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pin RX */
#define PIN_CAN0_RX     { PIO_GROUP_A, PIO_PA9B_CANRX0, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN0       { PIN_CAN0_TX, PIN_CAN0_RX }

/** CAN1 pin TX */
#define PIN_CAN1_TX     { PIO_GROUP_A, PIO_PA5B_CANTX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN1 pin RX */
#define PIN_CAN1_RX     { PIO_GROUP_A, PIO_PA6B_CANRX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN1       { PIN_CAN1_TX, PIN_CAN1_RX }

/* ========== Pio PIN definition for SPI peripheral ========== */

/** SPI0 MISO pin definition. */
#define PIN_SPI0_MISO { PIO_GROUP_A, PIO_PA11A_SPI0_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 MOSI pin definition. */
#define PIN_SPI0_MOSI { PIO_GROUP_A, PIO_PA12A_SPI0_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 SPCK pin definition. */
#define PIN_SPI0_SPCK { PIO_GROUP_A, PIO_PA13A_SPI0_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 0 pin definition. */
#define PIN_SPI0_NPCS0 { PIO_GROUP_A, PIO_PA14A_SPI0_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 1 pin definition. */
#define PIN_SPI0_NPCS1 { PIO_GROUP_A, PIO_PA7B_SPI0_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 2 pin definition. */
#define PIN_SPI0_NPCS2 { PIO_GROUP_A, PIO_PA1B_SPI0_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 3 pin definition. */
#define PIN_SPI0_NPCS3 { PIO_GROUP_A, PIO_PB3B_SPI0_NPCS3, PIO_PERIPH_B, PIO_DEFAULT }

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

/** SPI1 MISO pin definition. */
#define PIN_SPI1_MISO { PIO_GROUP_A, PIO_PA21B_SPI1_MISO, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 MOSI pin definition. */
#define PIN_SPI1_MOSI { PIO_GROUP_A, PIO_PA22B_SPI1_MOSI, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 SPCK pin definition. */
#define PIN_SPI1_SPCK { PIO_GROUP_A, PIO_PA23B_SPI1_SPCK, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 0 pin definition. */
#define PIN_SPI1_NPCS0 { PIO_GROUP_A, PIO_PA8B_SPI1_NPCS0, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 1 pin definition. */
#define PIN_SPI1_NPCS1 { PIO_GROUP_A, PIO_PA0B_SPI1_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 2 pin definition. */
#define PIN_SPI1_NPCS2 { PIO_GROUP_A, PIO_PA31B_SPI1_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 3 pin definition. */
#define PIN_SPI1_NPCS3 { PIO_GROUP_A, PIO_PA30B_SPI1_NPCS3, PIO_PERIPH_B, PIO_DEFAULT }

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

/* ========== Pio PIN definition for SSC peripheral ========== */

#define SSC0_TX (PIO_PA24B_TK0 | PIO_PA25B_TF0 | PIO_PA26B_TD0)

#define SSC0_RX (PIO_PA27B_RD0 | PIO_PA28B_RK0 | PIO_PA29B_RF0)

#define PINS_SSC0 {\
	{ PIO_GROUP_C, SSC0_TX | SSC0_RX, PIO_PERIPH_A, PIO_DEFAULT },\
}

/* ========== Pio PIN definition for LCDC peripheral ========== */

/* LCD 24 bits */
#define PINS_LCD { { PIO_GROUP_C, 0x7DFFFFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for ADC peripheral ========== */

/** ADC ADTRG pin (PD19). */
#define PIN_ADTRG { PIO_GROUP_B, PIO_PB18B_ADTRG, PIO_PERIPH_B, PIO_PULLUP }

/* ========== Pio PIN definition for NAND peripheral ========== */

/* 8-bit NAND: D16-D23, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND8 { { PIO_GROUP_D, 0x00003FFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* 8-bit NAND: D16-D31, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND16 { { PIO_GROUP_D, 0x03FFFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ============================================================ */

#endif /* _CHIP_PINS_H_ */
