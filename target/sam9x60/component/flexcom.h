/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_FLEXCOM_COMPONENT_
#define _SAM9X_FLEXCOM_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Flexible Serial Communication */
/* ============================================================================= */
/** \addtogroup SAM9X_FLEXCOM Flexible Serial Communication */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Flexcom hardware registers */
typedef struct {
  __IO uint32_t FLEX_MR;          /**< \brief (Flexcom Offset: 0x0) FLEXCOM Mode Register */
  __I  uint32_t Reserved1[3];
  __I  uint32_t FLEX_RHR;         /**< \brief (Flexcom Offset: 0x10) FLEXCOM Receive Holding Register */
  __I  uint32_t Reserved2[3];
  __IO uint32_t FLEX_THR;         /**< \brief (Flexcom Offset: 0x20) FLEXCOM Transmit Holding Register */
  __I  uint32_t Reserved3[119];
  __O  uint32_t FLEX_US_CR;       /**< \brief (Flexcom Offset: 0x200) USART Control Register */
  __IO uint32_t FLEX_US_MR;       /**< \brief (Flexcom Offset: 0x204) USART Mode Register */
  __O  uint32_t FLEX_US_IER;      /**< \brief (Flexcom Offset: 0x208) USART Interrupt Enable Register */
  __O  uint32_t FLEX_US_IDR;      /**< \brief (Flexcom Offset: 0x20C) USART Interrupt Disable Register */
  __I  uint32_t FLEX_US_IMR;      /**< \brief (Flexcom Offset: 0x210) USART Interrupt Mask Register */
  __I  uint32_t FLEX_US_CSR;      /**< \brief (Flexcom Offset: 0x214) USART Channel Status Register */
  __I  uint32_t FLEX_US_RHR;      /**< \brief (Flexcom Offset: 0x218) USART Receive Holding Register */
  __O  uint32_t FLEX_US_THR;      /**< \brief (Flexcom Offset: 0x21C) USART Transmit Holding Register */
  __IO uint32_t FLEX_US_BRGR;     /**< \brief (Flexcom Offset: 0x220) USART Baud Rate Generator Register */
  __IO uint32_t FLEX_US_RTOR;     /**< \brief (Flexcom Offset: 0x224) USART Receiver Timeout Register */
  __IO uint32_t FLEX_US_TTGR;     /**< \brief (Flexcom Offset: 0x228) USART Transmitter Timeguard Register */
  __I  uint32_t Reserved4[5];
  __IO uint32_t FLEX_US_FIDI;     /**< \brief (Flexcom Offset: 0x240) USART FI DI Ratio Register */
  __I  uint32_t FLEX_US_NER;      /**< \brief (Flexcom Offset: 0x244) USART Number of Errors Register */
  __I  uint32_t Reserved5[1];
  __IO uint32_t FLEX_US_IF;       /**< \brief (Flexcom Offset: 0x24C) USART IrDA Filter Register */
  __IO uint32_t FLEX_US_MAN;      /**< \brief (Flexcom Offset: 0x250) USART Manchester Configuration Register */
  __IO uint32_t FLEX_US_LINMR;    /**< \brief (Flexcom Offset: 0x254) USART LIN Mode Register */
  __IO uint32_t FLEX_US_LINIR;    /**< \brief (Flexcom Offset: 0x258) USART LIN Identifier Register */
  __I  uint32_t FLEX_US_LINBRR;   /**< \brief (Flexcom Offset: 0x25C) USART LIN Baud Rate Register */
  __IO uint32_t FLEX_US_LONMR;    /**< \brief (Flexcom Offset: 0x260) USART LON Mode Register */
  __IO uint32_t FLEX_US_LONPR;    /**< \brief (Flexcom Offset: 0x264) USART LON Preamble Register */
  __IO uint32_t FLEX_US_LONDL;    /**< \brief (Flexcom Offset: 0x268) USART LON Data Length Register */
  __IO uint32_t FLEX_US_LONL2HDR; /**< \brief (Flexcom Offset: 0x26C) USART LON L2HDR Register */
  __I  uint32_t FLEX_US_LONBL;    /**< \brief (Flexcom Offset: 0x270) USART LON Backlog Register */
  __IO uint32_t FLEX_US_LONB1TX;  /**< \brief (Flexcom Offset: 0x274) USART LON Beta1 Tx Register */
  __IO uint32_t FLEX_US_LONB1RX;  /**< \brief (Flexcom Offset: 0x278) USART LON Beta1 Rx Register */
  __IO uint32_t FLEX_US_LONPRIO;  /**< \brief (Flexcom Offset: 0x27C) USART LON Priority Register */
  __IO uint32_t FLEX_US_IDTTX;    /**< \brief (Flexcom Offset: 0x280) USART LON IDT Tx Register */
  __IO uint32_t FLEX_US_IDTRX;    /**< \brief (Flexcom Offset: 0x284) USART LON IDT Rx Register */
  __IO uint32_t FLEX_US_ICDIFF;   /**< \brief (Flexcom Offset: 0x288) USART IC DIFF Register */
  __I  uint32_t Reserved6[1];
  __IO uint32_t FLEX_US_CMPR;     /**< \brief (Flexcom Offset: 0x290) USART Comparison Register */
  __I  uint32_t Reserved7[3];
  __IO uint32_t FLEX_US_FMR;      /**< \brief (Flexcom Offset: 0x2A0) USART FIFO Mode Register */
  __I  uint32_t FLEX_US_FLR;      /**< \brief (Flexcom Offset: 0x2A4) USART FIFO Level Register */
  __O  uint32_t FLEX_US_FIER;     /**< \brief (Flexcom Offset: 0x2A8) USART FIFO Interrupt Enable Register */
  __O  uint32_t FLEX_US_FIDR;     /**< \brief (Flexcom Offset: 0x2AC) USART FIFO Interrupt Disable Register */
  __I  uint32_t FLEX_US_FIMR;     /**< \brief (Flexcom Offset: 0x2B0) USART FIFO Interrupt Mask Register */
  __I  uint32_t FLEX_US_FESR;     /**< \brief (Flexcom Offset: 0x2B4) USART FIFO Event Status Register */
  __I  uint32_t Reserved8[11];
  __IO uint32_t FLEX_US_WPMR;     /**< \brief (Flexcom Offset: 0x2E4) USART Write Protection Mode Register */
  __I  uint32_t FLEX_US_WPSR;     /**< \brief (Flexcom Offset: 0x2E8) USART Write Protection Status Register */
  __I  uint32_t Reserved9[69];
  __O  uint32_t FLEX_SPI_CR;      /**< \brief (Flexcom Offset: 0x400) SPI Control Register */
  __IO uint32_t FLEX_SPI_MR;      /**< \brief (Flexcom Offset: 0x404) SPI Mode Register */
  __I  uint32_t FLEX_SPI_RDR;     /**< \brief (Flexcom Offset: 0x408) SPI Receive Data Register */
  __O  uint32_t FLEX_SPI_TDR;     /**< \brief (Flexcom Offset: 0x40C) SPI Transmit Data Register */
  __I  uint32_t FLEX_SPI_SR;      /**< \brief (Flexcom Offset: 0x410) SPI Status Register */
  __O  uint32_t FLEX_SPI_IER;     /**< \brief (Flexcom Offset: 0x414) SPI Interrupt Enable Register */
  __O  uint32_t FLEX_SPI_IDR;     /**< \brief (Flexcom Offset: 0x418) SPI Interrupt Disable Register */
  __I  uint32_t FLEX_SPI_IMR;     /**< \brief (Flexcom Offset: 0x41C) SPI Interrupt Mask Register */
  __I  uint32_t Reserved10[4];
  __IO uint32_t FLEX_SPI_CSR[4];  /**< \brief (Flexcom Offset: 0x430) SPI Chip Select Register */
  __IO uint32_t FLEX_SPI_FMR;     /**< \brief (Flexcom Offset: 0x440) SPI FIFO Mode Register */
  __I  uint32_t FLEX_SPI_FLR;     /**< \brief (Flexcom Offset: 0x444) SPI FIFO Level Register */
  __IO uint32_t FLEX_SPI_CMPR;    /**< \brief (Flexcom Offset: 0x448) SPI Comparison Register */
  __I  uint32_t Reserved11[38];
  __IO uint32_t FLEX_SPI_WPMR;    /**< \brief (Flexcom Offset: 0x4E4) SPI Write Protection Mode Register */
  __I  uint32_t FLEX_SPI_WPSR;    /**< \brief (Flexcom Offset: 0x4E8) SPI Write Protection Status Register */
  __I  uint32_t Reserved12[69];
  __O  uint32_t FLEX_TWI_CR;      /**< \brief (Flexcom Offset: 0x600) TWI Control Register */
  __IO uint32_t FLEX_TWI_MMR;     /**< \brief (Flexcom Offset: 0x604) TWI Master Mode Register */
  __IO uint32_t FLEX_TWI_SMR;     /**< \brief (Flexcom Offset: 0x608) TWI Slave Mode Register */
  __IO uint32_t FLEX_TWI_IADR;    /**< \brief (Flexcom Offset: 0x60C) TWI Internal Address Register */
  __IO uint32_t FLEX_TWI_CWGR;    /**< \brief (Flexcom Offset: 0x610) TWI Clock Waveform Generator Register */
  __I  uint32_t Reserved13[3];
  __I  uint32_t FLEX_TWI_SR;      /**< \brief (Flexcom Offset: 0x620) TWI Status Register */
  __O  uint32_t FLEX_TWI_IER;     /**< \brief (Flexcom Offset: 0x624) TWI Interrupt Enable Register */
  __O  uint32_t FLEX_TWI_IDR;     /**< \brief (Flexcom Offset: 0x628) TWI Interrupt Disable Register */
  __I  uint32_t FLEX_TWI_IMR;     /**< \brief (Flexcom Offset: 0x62C) TWI Interrupt Mask Register */
  __I  uint32_t FLEX_TWI_RHR;     /**< \brief (Flexcom Offset: 0x630) TWI Receive Holding Register */
  __O  uint32_t FLEX_TWI_THR;     /**< \brief (Flexcom Offset: 0x634) TWI Transmit Holding Register */
  __IO uint32_t FLEX_TWI_SMBTR;   /**< \brief (Flexcom Offset: 0x638) TWI SMBus Timing Register */
  __I  uint32_t Reserved14[1];
  __IO uint32_t FLEX_TWI_ACR;     /**< \brief (Flexcom Offset: 0x640) TWI Alternative Command Register */
  __IO uint32_t FLEX_TWI_FILTR;   /**< \brief (Flexcom Offset: 0x644) TWI Filter Register */
  __I  uint32_t Reserved15[2];
  __IO uint32_t FLEX_TWI_FMR;     /**< \brief (Flexcom Offset: 0x650) TWI FIFO Mode Register */
  __I  uint32_t FLEX_TWI_FLR;     /**< \brief (Flexcom Offset: 0x654) TWI FIFO Level Register */
  __I  uint32_t Reserved16[2];
  __I  uint32_t FLEX_TWI_FSR;     /**< \brief (Flexcom Offset: 0x660) TWI FIFO Status Register */
  __O  uint32_t FLEX_TWI_FIER;    /**< \brief (Flexcom Offset: 0x664) TWI FIFO Interrupt Enable Register */
  __O  uint32_t FLEX_TWI_FIDR;    /**< \brief (Flexcom Offset: 0x668) TWI FIFO Interrupt Disable Register */
  __I  uint32_t FLEX_TWI_FIMR;    /**< \brief (Flexcom Offset: 0x66C) TWI FIFO Interrupt Mask Register */
  __I  uint32_t Reserved17[29];
  __IO uint32_t FLEX_TWI_WPMR;    /**< \brief (Flexcom Offset: 0x6E4) TWI Write Protection Mode Register */
  __I  uint32_t FLEX_TWI_WPSR;    /**< \brief (Flexcom Offset: 0x6E8) TWI Write Protection Status Register */
} Flexcom;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- FLEX_MR : (FLEXCOM Offset: 0x0) FLEXCOM Mode Register -------- */
#define FLEX_MR_OPMODE_Pos 0
#define FLEX_MR_OPMODE_Msk (0x3u << FLEX_MR_OPMODE_Pos) /**< \brief (FLEX_MR) FLEXCOM Operating Mode */
#define FLEX_MR_OPMODE(value) ((FLEX_MR_OPMODE_Msk & ((value) << FLEX_MR_OPMODE_Pos)))
#define   FLEX_MR_OPMODE_NO_COM (0x0u << 0) /**< \brief (FLEX_MR) No communication */
#define   FLEX_MR_OPMODE_USART (0x1u << 0) /**< \brief (FLEX_MR) All UART related protocols are selected (RS232, RS485, IrDA, ISO7816, LIN, LON) SPI/TWI related registers are not accessible and have no impact on IOs. */
#define   FLEX_MR_OPMODE_SPI (0x2u << 0) /**< \brief (FLEX_MR) SPI operating mode is selected. USART/TWI related registers are not accessible and have no impact on IOs. */
#define   FLEX_MR_OPMODE_TWI (0x3u << 0) /**< \brief (FLEX_MR) All TWI related protocols are selected (TWI, SMBus). USART/SPI related registers are not accessible and have no impact on IOs. */
/* -------- FLEX_RHR : (FLEXCOM Offset: 0x10) FLEXCOM Receive Holding Register -------- */
#define FLEX_RHR_RXDATA_Pos 0
#define FLEX_RHR_RXDATA_Msk (0xffffu << FLEX_RHR_RXDATA_Pos) /**< \brief (FLEX_RHR) Receive Data */
/* -------- FLEX_THR : (FLEXCOM Offset: 0x20) FLEXCOM Transmit Holding Register -------- */
#define FLEX_THR_TXDATA_Pos 0
#define FLEX_THR_TXDATA_Msk (0xffffu << FLEX_THR_TXDATA_Pos) /**< \brief (FLEX_THR) Transmit Data */
#define FLEX_THR_TXDATA(value) ((FLEX_THR_TXDATA_Msk & ((value) << FLEX_THR_TXDATA_Pos)))
/* -------- FLEX_US_CR : (FLEXCOM Offset: 0x200) USART Control Register -------- */
#define FLEX_US_CR_RSTRX (0x1u << 2) /**< \brief (FLEX_US_CR) Reset Receiver */
#define FLEX_US_CR_RSTTX (0x1u << 3) /**< \brief (FLEX_US_CR) Reset Transmitter */
#define FLEX_US_CR_RXEN (0x1u << 4) /**< \brief (FLEX_US_CR) Receiver Enable */
#define FLEX_US_CR_RXDIS (0x1u << 5) /**< \brief (FLEX_US_CR) Receiver Disable */
#define FLEX_US_CR_TXEN (0x1u << 6) /**< \brief (FLEX_US_CR) Transmitter Enable */
#define FLEX_US_CR_TXDIS (0x1u << 7) /**< \brief (FLEX_US_CR) Transmitter Disable */
#define FLEX_US_CR_RSTSTA (0x1u << 8) /**< \brief (FLEX_US_CR) Reset Status Bits */
#define FLEX_US_CR_STTBRK (0x1u << 9) /**< \brief (FLEX_US_CR) Start Break */
#define FLEX_US_CR_STPBRK (0x1u << 10) /**< \brief (FLEX_US_CR) Stop Break */
#define FLEX_US_CR_STTTO (0x1u << 11) /**< \brief (FLEX_US_CR) Clear TIMEOUT Flag and Start Timeout After Next Character Received */
#define FLEX_US_CR_SENDA (0x1u << 12) /**< \brief (FLEX_US_CR) Send Address */
#define FLEX_US_CR_RSTIT (0x1u << 13) /**< \brief (FLEX_US_CR) Reset Iterations */
#define FLEX_US_CR_RSTNACK (0x1u << 14) /**< \brief (FLEX_US_CR) Reset Non Acknowledge */
#define FLEX_US_CR_RETTO (0x1u << 15) /**< \brief (FLEX_US_CR) Start Timeout Immediately */
#define FLEX_US_CR_RTSEN (0x1u << 18) /**< \brief (FLEX_US_CR) Request to Send Enable */
#define FLEX_US_CR_RTSDIS (0x1u << 19) /**< \brief (FLEX_US_CR) Request to Send Disable */
#define FLEX_US_CR_LINABT (0x1u << 20) /**< \brief (FLEX_US_CR) Abort LIN Transmission */
#define FLEX_US_CR_LINWKUP (0x1u << 21) /**< \brief (FLEX_US_CR) Send LIN Wakeup Signal */
#define FLEX_US_CR_TXFCLR (0x1u << 24) /**< \brief (FLEX_US_CR) Transmit FIFO Clear */
#define FLEX_US_CR_RXFCLR (0x1u << 25) /**< \brief (FLEX_US_CR) Receive FIFO Clear */
#define FLEX_US_CR_TXFLCLR (0x1u << 26) /**< \brief (FLEX_US_CR) Transmit FIFO Lock CLEAR */
#define FLEX_US_CR_REQCLR (0x1u << 28) /**< \brief (FLEX_US_CR) Request to Clear the Comparison Trigger */
#define FLEX_US_CR_FIFOEN (0x1u << 30) /**< \brief (FLEX_US_CR) FIFO Enable */
#define FLEX_US_CR_FIFODIS (0x1u << 31) /**< \brief (FLEX_US_CR) FIFO Disable */
/* -------- FLEX_US_MR : (FLEXCOM Offset: 0x204) USART Mode Register -------- */
#define FLEX_US_MR_USART_MODE_Pos 0
#define FLEX_US_MR_USART_MODE_Msk (0xfu << FLEX_US_MR_USART_MODE_Pos) /**< \brief (FLEX_US_MR) USART Mode of Operation */
#define FLEX_US_MR_USART_MODE(value) ((FLEX_US_MR_USART_MODE_Msk & ((value) << FLEX_US_MR_USART_MODE_Pos)))
#define   FLEX_US_MR_USART_MODE_NORMAL (0x0u << 0) /**< \brief (FLEX_US_MR) Normal mode */
#define   FLEX_US_MR_USART_MODE_RS485 (0x1u << 0) /**< \brief (FLEX_US_MR) RS485 */
#define   FLEX_US_MR_USART_MODE_HW_HANDSHAKING (0x2u << 0) /**< \brief (FLEX_US_MR) Hardware handshaking */
#define   FLEX_US_MR_USART_MODE_IS07816_T_0 (0x4u << 0) /**< \brief (FLEX_US_MR) IS07816 Protocol: T = 0 */
#define   FLEX_US_MR_USART_MODE_IS07816_T_1 (0x6u << 0) /**< \brief (FLEX_US_MR) IS07816 Protocol: T = 1 */
#define   FLEX_US_MR_USART_MODE_IRDA (0x8u << 0) /**< \brief (FLEX_US_MR) IrDA */
#define   FLEX_US_MR_USART_MODE_LON (0x9u << 0) /**< \brief (FLEX_US_MR) LON */
#define   FLEX_US_MR_USART_MODE_LIN_MASTER (0xAu << 0) /**< \brief (FLEX_US_MR) LIN Master mode */
#define   FLEX_US_MR_USART_MODE_LIN_SLAVE (0xBu << 0) /**< \brief (FLEX_US_MR) LIN Slave mode */
#define   FLEX_US_MR_USART_MODE_DATA16BIT_MASTER (0xCu << 0) /**< \brief (FLEX_US_MR) 16-bit data master */
#define   FLEX_US_MR_USART_MODE_DATA16BIT_SLAVE (0xDu << 0) /**< \brief (FLEX_US_MR) 16-bit data slave */
#define FLEX_US_MR_USCLKS_Pos 4
#define FLEX_US_MR_USCLKS_Msk (0x3u << FLEX_US_MR_USCLKS_Pos) /**< \brief (FLEX_US_MR) Clock Selection */
#define FLEX_US_MR_USCLKS(value) ((FLEX_US_MR_USCLKS_Msk & ((value) << FLEX_US_MR_USCLKS_Pos)))
#define   FLEX_US_MR_USCLKS_MCK (0x0u << 4) /**< \brief (FLEX_US_MR) Peripheral clock is selected */
#define   FLEX_US_MR_USCLKS_DIV (0x1u << 4) /**< \brief (FLEX_US_MR) Peripheral clock divided (DIV = 8) is selected */
#define   FLEX_US_MR_USCLKS_GCLK (0x2u << 4) /**< \brief (FLEX_US_MR) PMC generic clock is selected. If the SCK pin is driven (CLKO = 1), the CD field must be greater than 1. */
#define   FLEX_US_MR_USCLKS_SCK (0x3u << 4) /**< \brief (FLEX_US_MR) External pin SCK is selected */
#define FLEX_US_MR_CHRL_Pos 6
#define FLEX_US_MR_CHRL_Msk (0x3u << FLEX_US_MR_CHRL_Pos) /**< \brief (FLEX_US_MR) Character Length */
#define FLEX_US_MR_CHRL(value) ((FLEX_US_MR_CHRL_Msk & ((value) << FLEX_US_MR_CHRL_Pos)))
#define   FLEX_US_MR_CHRL_5_BIT (0x0u << 6) /**< \brief (FLEX_US_MR) Character length is 5 bits */
#define   FLEX_US_MR_CHRL_6_BIT (0x1u << 6) /**< \brief (FLEX_US_MR) Character length is 6 bits */
#define   FLEX_US_MR_CHRL_7_BIT (0x2u << 6) /**< \brief (FLEX_US_MR) Character length is 7 bits */
#define   FLEX_US_MR_CHRL_8_BIT (0x3u << 6) /**< \brief (FLEX_US_MR) Character length is 8 bits */
#define FLEX_US_MR_SYNC (0x1u << 8) /**< \brief (FLEX_US_MR) Synchronous Mode Select */
#define FLEX_US_MR_PAR_Pos 9
#define FLEX_US_MR_PAR_Msk (0x7u << FLEX_US_MR_PAR_Pos) /**< \brief (FLEX_US_MR) Parity Type */
#define FLEX_US_MR_PAR(value) ((FLEX_US_MR_PAR_Msk & ((value) << FLEX_US_MR_PAR_Pos)))
#define   FLEX_US_MR_PAR_EVEN (0x0u << 9) /**< \brief (FLEX_US_MR) Even parity */
#define   FLEX_US_MR_PAR_ODD (0x1u << 9) /**< \brief (FLEX_US_MR) Odd parity */
#define   FLEX_US_MR_PAR_SPACE (0x2u << 9) /**< \brief (FLEX_US_MR) Parity forced to 0 (Space) */
#define   FLEX_US_MR_PAR_MARK (0x3u << 9) /**< \brief (FLEX_US_MR) Parity forced to 1 (Mark) */
#define   FLEX_US_MR_PAR_NO (0x4u << 9) /**< \brief (FLEX_US_MR) No parity */
#define   FLEX_US_MR_PAR_MULTIDROP (0x6u << 9) /**< \brief (FLEX_US_MR) Multidrop mode */
#define FLEX_US_MR_NBSTOP_Pos 12
#define FLEX_US_MR_NBSTOP_Msk (0x3u << FLEX_US_MR_NBSTOP_Pos) /**< \brief (FLEX_US_MR) Number of Stop Bits */
#define FLEX_US_MR_NBSTOP(value) ((FLEX_US_MR_NBSTOP_Msk & ((value) << FLEX_US_MR_NBSTOP_Pos)))
#define   FLEX_US_MR_NBSTOP_1_BIT (0x0u << 12) /**< \brief (FLEX_US_MR) 1 stop bit */
#define   FLEX_US_MR_NBSTOP_1_5_BIT (0x1u << 12) /**< \brief (FLEX_US_MR) 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1) */
#define   FLEX_US_MR_NBSTOP_2_BIT (0x2u << 12) /**< \brief (FLEX_US_MR) 2 stop bits */
#define FLEX_US_MR_CHMODE_Pos 14
#define FLEX_US_MR_CHMODE_Msk (0x3u << FLEX_US_MR_CHMODE_Pos) /**< \brief (FLEX_US_MR) Channel Mode */
#define FLEX_US_MR_CHMODE(value) ((FLEX_US_MR_CHMODE_Msk & ((value) << FLEX_US_MR_CHMODE_Pos)))
#define   FLEX_US_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (FLEX_US_MR) Normal mode */
#define   FLEX_US_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (FLEX_US_MR) Automatic Echo. Receiver input is connected to the TXD pin. */
#define   FLEX_US_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (FLEX_US_MR) Local Loopback. Transmitter output is connected to the Receiver Input. */
#define   FLEX_US_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (FLEX_US_MR) Remote Loopback. RXD pin is internally connected to the TXD pin. */
#define FLEX_US_MR_MSBF (0x1u << 16) /**< \brief (FLEX_US_MR) Bit Order */
#define FLEX_US_MR_MODE9 (0x1u << 17) /**< \brief (FLEX_US_MR) 9-bit Character Length */
#define FLEX_US_MR_CLKO (0x1u << 18) /**< \brief (FLEX_US_MR) Clock Output Select */
#define FLEX_US_MR_OVER (0x1u << 19) /**< \brief (FLEX_US_MR) Oversampling Mode */
#define FLEX_US_MR_INACK (0x1u << 20) /**< \brief (FLEX_US_MR) Inhibit Non Acknowledge */
#define FLEX_US_MR_DSNACK (0x1u << 21) /**< \brief (FLEX_US_MR) Disable Successive NACK */
#define FLEX_US_MR_VAR_SYNC (0x1u << 22) /**< \brief (FLEX_US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter */
#define FLEX_US_MR_INVDATA (0x1u << 23) /**< \brief (FLEX_US_MR) Inverted Data */
#define FLEX_US_MR_MAX_ITERATION_Pos 24
#define FLEX_US_MR_MAX_ITERATION_Msk (0x7u << FLEX_US_MR_MAX_ITERATION_Pos) /**< \brief (FLEX_US_MR) Maximum Number of Automatic Iteration */
#define FLEX_US_MR_MAX_ITERATION(value) ((FLEX_US_MR_MAX_ITERATION_Msk & ((value) << FLEX_US_MR_MAX_ITERATION_Pos)))
#define FLEX_US_MR_FILTER (0x1u << 28) /**< \brief (FLEX_US_MR) Receive Line Filter */
#define FLEX_US_MR_MAN (0x1u << 29) /**< \brief (FLEX_US_MR) Manchester Encoder/Decoder Enable */
#define FLEX_US_MR_MODSYNC (0x1u << 30) /**< \brief (FLEX_US_MR) Manchester Synchronization Mode */
#define FLEX_US_MR_ONEBIT (0x1u << 31) /**< \brief (FLEX_US_MR) Start Frame Delimiter Selector */
/* -------- FLEX_US_IER : (FLEXCOM Offset: 0x208) USART Interrupt Enable Register -------- */
#define FLEX_US_IER_RXRDY (0x1u << 0) /**< \brief (FLEX_US_IER) RXRDY Interrupt Enable */
#define FLEX_US_IER_TXRDY (0x1u << 1) /**< \brief (FLEX_US_IER) TXRDY Interrupt Enable */
#define FLEX_US_IER_RXBRK (0x1u << 2) /**< \brief (FLEX_US_IER) Receiver Break Interrupt Enable */
#define FLEX_US_IER_OVRE (0x1u << 5) /**< \brief (FLEX_US_IER) Overrun Error Interrupt Enable */
#define FLEX_US_IER_FRAME (0x1u << 6) /**< \brief (FLEX_US_IER) Framing Error Interrupt Enable */
#define FLEX_US_IER_PARE (0x1u << 7) /**< \brief (FLEX_US_IER) Parity Error Interrupt Enable */
#define FLEX_US_IER_TIMEOUT (0x1u << 8) /**< \brief (FLEX_US_IER) Timeout Interrupt Enable */
#define FLEX_US_IER_TXEMPTY (0x1u << 9) /**< \brief (FLEX_US_IER) TXEMPTY Interrupt Enable */
#define FLEX_US_IER_ITER (0x1u << 10) /**< \brief (FLEX_US_IER) Max number of Repetitions Reached Interrupt Enable */
#define FLEX_US_IER_NACK (0x1u << 13) /**< \brief (FLEX_US_IER) Non Acknowledge Interrupt Enable */
#define FLEX_US_IER_CTSIC (0x1u << 19) /**< \brief (FLEX_US_IER) Clear to Send Input Change Interrupt Enable */
#define FLEX_US_IER_CMP (0x1u << 22) /**< \brief (FLEX_US_IER) Comparison Interrupt Enable */
#define FLEX_US_IER_MANE (0x1u << 24) /**< \brief (FLEX_US_IER) Manchester Error Interrupt Enable */
#define FLEX_US_IER_LINBK (0x1u << 13) /**< \brief (FLEX_US_IER) LIN Break Sent or LIN Break Received Interrupt Enable */
#define FLEX_US_IER_LINID (0x1u << 14) /**< \brief (FLEX_US_IER) LIN Identifier Sent or LIN Identifier Received Interrupt Enable */
#define FLEX_US_IER_LINTC (0x1u << 15) /**< \brief (FLEX_US_IER) LIN Transfer Completed Interrupt Enable */
#define FLEX_US_IER_LINBE (0x1u << 25) /**< \brief (FLEX_US_IER) LIN Bus Error Interrupt Enable */
#define FLEX_US_IER_LINISFE (0x1u << 26) /**< \brief (FLEX_US_IER) LIN Inconsistent Synch Field Error Interrupt Enable */
#define FLEX_US_IER_LINIPE (0x1u << 27) /**< \brief (FLEX_US_IER) LIN Identifier Parity Interrupt Enable */
#define FLEX_US_IER_LINCE (0x1u << 28) /**< \brief (FLEX_US_IER) LIN Checksum Error Interrupt Enable */
#define FLEX_US_IER_LINSNRE (0x1u << 29) /**< \brief (FLEX_US_IER) LIN Slave Not Responding Error Interrupt Enable */
#define FLEX_US_IER_LINSTE (0x1u << 30) /**< \brief (FLEX_US_IER) LIN Synch Tolerance Error Interrupt Enable */
#define FLEX_US_IER_LINHTE (0x1u << 31) /**< \brief (FLEX_US_IER) LIN Header Timeout Error Interrupt Enable */
#define FLEX_US_IER_LSFE (0x1u << 6) /**< \brief (FLEX_US_IER) LON Short Frame Error Interrupt Enable */
#define FLEX_US_IER_LCRCE (0x1u << 7) /**< \brief (FLEX_US_IER) LON CRC Error Interrupt Enable */
#define FLEX_US_IER_UNRE (0x1u << 10) /**< \brief (FLEX_US_IER) Underrun Error Interrupt Enable */
#define FLEX_US_IER_LTXD (0x1u << 24) /**< \brief (FLEX_US_IER) LON Transmission Done Interrupt Enable */
#define FLEX_US_IER_LCOL (0x1u << 25) /**< \brief (FLEX_US_IER) LON Collision Interrupt Enable */
#define FLEX_US_IER_LFET (0x1u << 26) /**< \brief (FLEX_US_IER) LON Frame Early Termination Interrupt Enable */
#define FLEX_US_IER_LRXD (0x1u << 27) /**< \brief (FLEX_US_IER) LON Reception Done Interrupt Enable */
#define FLEX_US_IER_LBLOVFE (0x1u << 28) /**< \brief (FLEX_US_IER) LON Backlog Overflow Error Interrupt Enable */
/* -------- FLEX_US_IDR : (FLEXCOM Offset: 0x20C) USART Interrupt Disable Register -------- */
#define FLEX_US_IDR_RXRDY (0x1u << 0) /**< \brief (FLEX_US_IDR) RXRDY Interrupt Disable */
#define FLEX_US_IDR_TXRDY (0x1u << 1) /**< \brief (FLEX_US_IDR) TXRDY Interrupt Disable */
#define FLEX_US_IDR_RXBRK (0x1u << 2) /**< \brief (FLEX_US_IDR) Receiver Break Interrupt Disable */
#define FLEX_US_IDR_OVRE (0x1u << 5) /**< \brief (FLEX_US_IDR) Overrun Error Interrupt Disable */
#define FLEX_US_IDR_FRAME (0x1u << 6) /**< \brief (FLEX_US_IDR) Framing Error Interrupt Disable */
#define FLEX_US_IDR_PARE (0x1u << 7) /**< \brief (FLEX_US_IDR) Parity Error Interrupt Disable */
#define FLEX_US_IDR_TIMEOUT (0x1u << 8) /**< \brief (FLEX_US_IDR) Timeout Interrupt Disable */
#define FLEX_US_IDR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_US_IDR) TXEMPTY Interrupt Disable */
#define FLEX_US_IDR_ITER (0x1u << 10) /**< \brief (FLEX_US_IDR) Max Number of Repetitions Reached Interrupt Disable */
#define FLEX_US_IDR_NACK (0x1u << 13) /**< \brief (FLEX_US_IDR) Non Acknowledge Interrupt Disable */
#define FLEX_US_IDR_CTSIC (0x1u << 19) /**< \brief (FLEX_US_IDR) Clear to Send Input Change Interrupt Disable */
#define FLEX_US_IDR_CMP (0x1u << 22) /**< \brief (FLEX_US_IDR) Comparison Interrupt Disable */
#define FLEX_US_IDR_MANE (0x1u << 24) /**< \brief (FLEX_US_IDR) Manchester Error Interrupt Disable */
#define FLEX_US_IDR_LINBK (0x1u << 13) /**< \brief (FLEX_US_IDR) LIN Break Sent or LIN Break Received Interrupt Disable */
#define FLEX_US_IDR_LINID (0x1u << 14) /**< \brief (FLEX_US_IDR) LIN Identifier Sent or LIN Identifier Received Interrupt Disable */
#define FLEX_US_IDR_LINTC (0x1u << 15) /**< \brief (FLEX_US_IDR) LIN Transfer Completed Interrupt Disable */
#define FLEX_US_IDR_LINBE (0x1u << 25) /**< \brief (FLEX_US_IDR) LIN Bus Error Interrupt Disable */
#define FLEX_US_IDR_LINISFE (0x1u << 26) /**< \brief (FLEX_US_IDR) LIN Inconsistent Synch Field Error Interrupt Disable */
#define FLEX_US_IDR_LINIPE (0x1u << 27) /**< \brief (FLEX_US_IDR) LIN Identifier Parity Interrupt Disable */
#define FLEX_US_IDR_LINCE (0x1u << 28) /**< \brief (FLEX_US_IDR) LIN Checksum Error Interrupt Disable */
#define FLEX_US_IDR_LINSNRE (0x1u << 29) /**< \brief (FLEX_US_IDR) LIN Slave Not Responding Error Interrupt Disable */
#define FLEX_US_IDR_LINSTE (0x1u << 30) /**< \brief (FLEX_US_IDR) LIN Synch Tolerance Error Interrupt Disable */
#define FLEX_US_IDR_LINHTE (0x1u << 31) /**< \brief (FLEX_US_IDR) LIN Header Timeout Error Interrupt Disable */
#define FLEX_US_IDR_LSFE (0x1u << 6) /**< \brief (FLEX_US_IDR) LON Short Frame Error Interrupt Disable */
#define FLEX_US_IDR_LCRCE (0x1u << 7) /**< \brief (FLEX_US_IDR) LON CRC Error Interrupt Disable */
#define FLEX_US_IDR_UNRE (0x1u << 10) /**< \brief (FLEX_US_IDR) Underrun Error Interrupt Disable */
#define FLEX_US_IDR_LTXD (0x1u << 24) /**< \brief (FLEX_US_IDR) LON Transmission Done Interrupt Disable */
#define FLEX_US_IDR_LCOL (0x1u << 25) /**< \brief (FLEX_US_IDR) LON Collision Interrupt Disable */
#define FLEX_US_IDR_LFET (0x1u << 26) /**< \brief (FLEX_US_IDR) LON Frame Early Termination Interrupt Disable */
#define FLEX_US_IDR_LRXD (0x1u << 27) /**< \brief (FLEX_US_IDR) LON Reception Done Interrupt Disable */
#define FLEX_US_IDR_LBLOVFE (0x1u << 28) /**< \brief (FLEX_US_IDR) LON Backlog Overflow Error Interrupt Disable */
/* -------- FLEX_US_IMR : (FLEXCOM Offset: 0x210) USART Interrupt Mask Register -------- */
#define FLEX_US_IMR_RXRDY (0x1u << 0) /**< \brief (FLEX_US_IMR) RXRDY Interrupt Mask */
#define FLEX_US_IMR_TXRDY (0x1u << 1) /**< \brief (FLEX_US_IMR) TXRDY Interrupt Mask */
#define FLEX_US_IMR_RXBRK (0x1u << 2) /**< \brief (FLEX_US_IMR) Receiver Break Interrupt Mask */
#define FLEX_US_IMR_OVRE (0x1u << 5) /**< \brief (FLEX_US_IMR) Overrun Error Interrupt Mask */
#define FLEX_US_IMR_FRAME (0x1u << 6) /**< \brief (FLEX_US_IMR) Framing Error Interrupt Mask */
#define FLEX_US_IMR_PARE (0x1u << 7) /**< \brief (FLEX_US_IMR) Parity Error Interrupt Mask */
#define FLEX_US_IMR_TIMEOUT (0x1u << 8) /**< \brief (FLEX_US_IMR) Timeout Interrupt Mask */
#define FLEX_US_IMR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_US_IMR) TXEMPTY Interrupt Mask */
#define FLEX_US_IMR_ITER (0x1u << 10) /**< \brief (FLEX_US_IMR) Max Number of Repetitions Reached Interrupt Mask */
#define FLEX_US_IMR_NACK (0x1u << 13) /**< \brief (FLEX_US_IMR) Non Acknowledge Interrupt Mask */
#define FLEX_US_IMR_CTSIC (0x1u << 19) /**< \brief (FLEX_US_IMR) Clear to Send Input Change Interrupt Mask */
#define FLEX_US_IMR_CMP (0x1u << 22) /**< \brief (FLEX_US_IMR) Comparison Interrupt Mask */
#define FLEX_US_IMR_MANE (0x1u << 24) /**< \brief (FLEX_US_IMR) Manchester Error Interrupt Mask */
#define FLEX_US_IMR_LINBK (0x1u << 13) /**< \brief (FLEX_US_IMR) LIN Break Sent or LIN Break Received Interrupt Mask */
#define FLEX_US_IMR_LINID (0x1u << 14) /**< \brief (FLEX_US_IMR) LIN Identifier Sent or LIN Identifier Received Interrupt Mask */
#define FLEX_US_IMR_LINTC (0x1u << 15) /**< \brief (FLEX_US_IMR) LIN Transfer Completed Interrupt Mask */
#define FLEX_US_IMR_LINBE (0x1u << 25) /**< \brief (FLEX_US_IMR) LIN Bus Error Interrupt Mask */
#define FLEX_US_IMR_LINISFE (0x1u << 26) /**< \brief (FLEX_US_IMR) LIN Inconsistent Synch Field Error Interrupt Mask */
#define FLEX_US_IMR_LINIPE (0x1u << 27) /**< \brief (FLEX_US_IMR) LIN Identifier Parity Interrupt Mask */
#define FLEX_US_IMR_LINCE (0x1u << 28) /**< \brief (FLEX_US_IMR) LIN Checksum Error Interrupt Mask */
#define FLEX_US_IMR_LINSNRE (0x1u << 29) /**< \brief (FLEX_US_IMR) LIN Slave Not Responding Error Interrupt Mask */
#define FLEX_US_IMR_LINSTE (0x1u << 30) /**< \brief (FLEX_US_IMR) LIN Synch Tolerance Error Interrupt Mask */
#define FLEX_US_IMR_LINHTE (0x1u << 31) /**< \brief (FLEX_US_IMR) LIN Header Timeout Error Interrupt Mask */
#define FLEX_US_IMR_LSFE (0x1u << 6) /**< \brief (FLEX_US_IMR) LON Short Frame Error Interrupt Mask */
#define FLEX_US_IMR_LCRCE (0x1u << 7) /**< \brief (FLEX_US_IMR) LON CRC Error Interrupt Mask */
#define FLEX_US_IMR_UNRE (0x1u << 10) /**< \brief (FLEX_US_IMR) Underrun Error Interrupt Mask */
#define FLEX_US_IMR_LTXD (0x1u << 24) /**< \brief (FLEX_US_IMR) LON Transmission Done Interrupt Mask */
#define FLEX_US_IMR_LCOL (0x1u << 25) /**< \brief (FLEX_US_IMR) LON Collision Interrupt Mask */
#define FLEX_US_IMR_LFET (0x1u << 26) /**< \brief (FLEX_US_IMR) LON Frame Early Termination Interrupt Mask */
#define FLEX_US_IMR_LRXD (0x1u << 27) /**< \brief (FLEX_US_IMR) LON Reception Done Interrupt Mask */
#define FLEX_US_IMR_LBLOVFE (0x1u << 28) /**< \brief (FLEX_US_IMR) LON Backlog Overflow Error Interrupt Mask */
/* -------- FLEX_US_CSR : (FLEXCOM Offset: 0x214) USART Channel Status Register -------- */
#define FLEX_US_CSR_RXRDY (0x1u << 0) /**< \brief (FLEX_US_CSR) Receiver Ready (cleared by reading FLEX_US_RHR) */
#define FLEX_US_CSR_TXRDY (0x1u << 1) /**< \brief (FLEX_US_CSR) Transmitter Ready (cleared by writing FLEX_US_THR) */
#define FLEX_US_CSR_RXBRK (0x1u << 2) /**< \brief (FLEX_US_CSR) Break Received/End of Break */
#define FLEX_US_CSR_OVRE (0x1u << 5) /**< \brief (FLEX_US_CSR) Overrun Error */
#define FLEX_US_CSR_FRAME (0x1u << 6) /**< \brief (FLEX_US_CSR) Framing Error */
#define FLEX_US_CSR_PARE (0x1u << 7) /**< \brief (FLEX_US_CSR) Parity Error */
#define FLEX_US_CSR_TIMEOUT (0x1u << 8) /**< \brief (FLEX_US_CSR) Receiver Timeout */
#define FLEX_US_CSR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_US_CSR) Transmitter Empty (cleared by writing FLEX_US_THR) */
#define FLEX_US_CSR_ITER (0x1u << 10) /**< \brief (FLEX_US_CSR) Max Number of Repetitions Reached */
#define FLEX_US_CSR_NACK (0x1u << 13) /**< \brief (FLEX_US_CSR) Non Acknowledge Interrupt */
#define FLEX_US_CSR_CTSIC (0x1u << 19) /**< \brief (FLEX_US_CSR) Clear to Send Input Change Flag */
#define FLEX_US_CSR_CMP (0x1u << 22) /**< \brief (FLEX_US_CSR) Comparison Status */
#define FLEX_US_CSR_CTS (0x1u << 23) /**< \brief (FLEX_US_CSR) Image of CTS Input */
#define FLEX_US_CSR_MANE (0x1u << 24) /**< \brief (FLEX_US_CSR) Manchester Error */
#define FLEX_US_CSR_LINBK (0x1u << 13) /**< \brief (FLEX_US_CSR) LIN Break Sent or LIN Break Received */
#define FLEX_US_CSR_LINID (0x1u << 14) /**< \brief (FLEX_US_CSR) LIN Identifier Sent or LIN Identifier Received */
#define FLEX_US_CSR_LINTC (0x1u << 15) /**< \brief (FLEX_US_CSR) LIN Transfer Completed */
#define FLEX_US_CSR_LINBLS (0x1u << 23) /**< \brief (FLEX_US_CSR) LIN Bus Line Status */
#define FLEX_US_CSR_LINBE (0x1u << 25) /**< \brief (FLEX_US_CSR) LIN Bit Error */
#define FLEX_US_CSR_LINISFE (0x1u << 26) /**< \brief (FLEX_US_CSR) LIN Inconsistent Synch Field Error */
#define FLEX_US_CSR_LINIPE (0x1u << 27) /**< \brief (FLEX_US_CSR) LIN Identifier Parity Error */
#define FLEX_US_CSR_LINCE (0x1u << 28) /**< \brief (FLEX_US_CSR) LIN Checksum Error */
#define FLEX_US_CSR_LINSNRE (0x1u << 29) /**< \brief (FLEX_US_CSR) LIN Slave Not Responding Error */
#define FLEX_US_CSR_LINSTE (0x1u << 30) /**< \brief (FLEX_US_CSR) LIN Synch Tolerance Error */
#define FLEX_US_CSR_LINHTE (0x1u << 31) /**< \brief (FLEX_US_CSR) LIN Header Timeout Error */
#define FLEX_US_CSR_LSFE (0x1u << 6) /**< \brief (FLEX_US_CSR) LON Short Frame Error */
#define FLEX_US_CSR_LCRCE (0x1u << 7) /**< \brief (FLEX_US_CSR) LON CRC Error */
#define FLEX_US_CSR_UNRE (0x1u << 10) /**< \brief (FLEX_US_CSR) Underrun Error */
#define FLEX_US_CSR_LTXD (0x1u << 24) /**< \brief (FLEX_US_CSR) LON Transmission End Flag */
#define FLEX_US_CSR_LCOL (0x1u << 25) /**< \brief (FLEX_US_CSR) LON Collision Detected Flag */
#define FLEX_US_CSR_LFET (0x1u << 26) /**< \brief (FLEX_US_CSR) LON Frame Early Termination */
#define FLEX_US_CSR_LRXD (0x1u << 27) /**< \brief (FLEX_US_CSR) LON Reception End Flag */
#define FLEX_US_CSR_LBLOVFE (0x1u << 28) /**< \brief (FLEX_US_CSR) LON Backlog Overflow Error */
/* -------- FLEX_US_RHR : (FLEXCOM Offset: 0x218) USART Receive Holding Register -------- */
#define FLEX_US_RHR_RXCHR_Pos 0
#define FLEX_US_RHR_RXCHR_Msk (0x1ffu << FLEX_US_RHR_RXCHR_Pos) /**< \brief (FLEX_US_RHR) Received Character */
#define FLEX_US_RHR_RXSYNH (0x1u << 15) /**< \brief (FLEX_US_RHR) Received Sync */
#define FLEX_US_RHR_RXCHR0_Pos 0
#define FLEX_US_RHR_RXCHR0_Msk (0xffu << FLEX_US_RHR_RXCHR0_Pos) /**< \brief (FLEX_US_RHR) Received Character */
#define FLEX_US_RHR_RXCHR1_Pos 8
#define FLEX_US_RHR_RXCHR1_Msk (0xffu << FLEX_US_RHR_RXCHR1_Pos) /**< \brief (FLEX_US_RHR) Received Character */
#define FLEX_US_RHR_RXCHR2_Pos 16
#define FLEX_US_RHR_RXCHR2_Msk (0xffu << FLEX_US_RHR_RXCHR2_Pos) /**< \brief (FLEX_US_RHR) Received Character */
#define FLEX_US_RHR_RXCHR3_Pos 24
#define FLEX_US_RHR_RXCHR3_Msk (0xffu << FLEX_US_RHR_RXCHR3_Pos) /**< \brief (FLEX_US_RHR) Received Character */
/* -------- FLEX_US_THR : (FLEXCOM Offset: 0x21C) USART Transmit Holding Register -------- */
#define FLEX_US_THR_TXCHR_Pos 0
#define FLEX_US_THR_TXCHR_Msk (0x1ffu << FLEX_US_THR_TXCHR_Pos) /**< \brief (FLEX_US_THR) Character to be Transmitted */
#define FLEX_US_THR_TXCHR(value) ((FLEX_US_THR_TXCHR_Msk & ((value) << FLEX_US_THR_TXCHR_Pos)))
#define FLEX_US_THR_TXSYNH (0x1u << 15) /**< \brief (FLEX_US_THR) Sync Field to be Transmitted */
#define FLEX_US_THR_TXCHR0_Pos 0
#define FLEX_US_THR_TXCHR0_Msk (0xffu << FLEX_US_THR_TXCHR0_Pos) /**< \brief (FLEX_US_THR) Character to be Transmitted */
#define FLEX_US_THR_TXCHR0(value) ((FLEX_US_THR_TXCHR0_Msk & ((value) << FLEX_US_THR_TXCHR0_Pos)))
#define FLEX_US_THR_TXCHR1_Pos 8
#define FLEX_US_THR_TXCHR1_Msk (0xffu << FLEX_US_THR_TXCHR1_Pos) /**< \brief (FLEX_US_THR) Character to be Transmitted */
#define FLEX_US_THR_TXCHR1(value) ((FLEX_US_THR_TXCHR1_Msk & ((value) << FLEX_US_THR_TXCHR1_Pos)))
#define FLEX_US_THR_TXCHR2_Pos 16
#define FLEX_US_THR_TXCHR2_Msk (0xffu << FLEX_US_THR_TXCHR2_Pos) /**< \brief (FLEX_US_THR) Character to be Transmitted */
#define FLEX_US_THR_TXCHR2(value) ((FLEX_US_THR_TXCHR2_Msk & ((value) << FLEX_US_THR_TXCHR2_Pos)))
#define FLEX_US_THR_TXCHR3_Pos 24
#define FLEX_US_THR_TXCHR3_Msk (0xffu << FLEX_US_THR_TXCHR3_Pos) /**< \brief (FLEX_US_THR) Character to be Transmitted */
#define FLEX_US_THR_TXCHR3(value) ((FLEX_US_THR_TXCHR3_Msk & ((value) << FLEX_US_THR_TXCHR3_Pos)))
/* -------- FLEX_US_BRGR : (FLEXCOM Offset: 0x220) USART Baud Rate Generator Register -------- */
#define FLEX_US_BRGR_CD_Pos 0
#define FLEX_US_BRGR_CD_Msk (0xffffu << FLEX_US_BRGR_CD_Pos) /**< \brief (FLEX_US_BRGR) Clock Divider */
#define FLEX_US_BRGR_CD(value) ((FLEX_US_BRGR_CD_Msk & ((value) << FLEX_US_BRGR_CD_Pos)))
#define FLEX_US_BRGR_FP_Pos 16
#define FLEX_US_BRGR_FP_Msk (0x7u << FLEX_US_BRGR_FP_Pos) /**< \brief (FLEX_US_BRGR) Fractional Part */
#define FLEX_US_BRGR_FP(value) ((FLEX_US_BRGR_FP_Msk & ((value) << FLEX_US_BRGR_FP_Pos)))
/* -------- FLEX_US_RTOR : (FLEXCOM Offset: 0x224) USART Receiver Timeout Register -------- */
#define FLEX_US_RTOR_TO_Pos 0
#define FLEX_US_RTOR_TO_Msk (0x1ffffu << FLEX_US_RTOR_TO_Pos) /**< \brief (FLEX_US_RTOR) Timeout Value */
#define FLEX_US_RTOR_TO(value) ((FLEX_US_RTOR_TO_Msk & ((value) << FLEX_US_RTOR_TO_Pos)))
/* -------- FLEX_US_TTGR : (FLEXCOM Offset: 0x228) USART Transmitter Timeguard Register -------- */
#define FLEX_US_TTGR_TG_Pos 0
#define FLEX_US_TTGR_TG_Msk (0xffu << FLEX_US_TTGR_TG_Pos) /**< \brief (FLEX_US_TTGR) Timeguard Value */
#define FLEX_US_TTGR_TG(value) ((FLEX_US_TTGR_TG_Msk & ((value) << FLEX_US_TTGR_TG_Pos)))
#define FLEX_US_TTGR_PCYCLE_Pos 0
#define FLEX_US_TTGR_PCYCLE_Msk (0xffffffu << FLEX_US_TTGR_PCYCLE_Pos) /**< \brief (FLEX_US_TTGR) LON PCYCLE Length */
#define FLEX_US_TTGR_PCYCLE(value) ((FLEX_US_TTGR_PCYCLE_Msk & ((value) << FLEX_US_TTGR_PCYCLE_Pos)))
/* -------- FLEX_US_FIDI : (FLEXCOM Offset: 0x240) USART FI DI Ratio Register -------- */
#define FLEX_US_FIDI_FI_DI_RATIO_Pos 0
#define FLEX_US_FIDI_FI_DI_RATIO_Msk (0xffffu << FLEX_US_FIDI_FI_DI_RATIO_Pos) /**< \brief (FLEX_US_FIDI) FI Over DI Ratio Value */
#define FLEX_US_FIDI_FI_DI_RATIO(value) ((FLEX_US_FIDI_FI_DI_RATIO_Msk & ((value) << FLEX_US_FIDI_FI_DI_RATIO_Pos)))
#define FLEX_US_FIDI_BETA2_Pos 0
#define FLEX_US_FIDI_BETA2_Msk (0xffffffu << FLEX_US_FIDI_BETA2_Pos) /**< \brief (FLEX_US_FIDI) LON BETA2 Length */
#define FLEX_US_FIDI_BETA2(value) ((FLEX_US_FIDI_BETA2_Msk & ((value) << FLEX_US_FIDI_BETA2_Pos)))
/* -------- FLEX_US_NER : (FLEXCOM Offset: 0x244) USART Number of Errors Register -------- */
#define FLEX_US_NER_NB_ERRORS_Pos 0
#define FLEX_US_NER_NB_ERRORS_Msk (0xffu << FLEX_US_NER_NB_ERRORS_Pos) /**< \brief (FLEX_US_NER) Number of Errors */
/* -------- FLEX_US_IF : (FLEXCOM Offset: 0x24C) USART IrDA Filter Register -------- */
#define FLEX_US_IF_IRDA_FILTER_Pos 0
#define FLEX_US_IF_IRDA_FILTER_Msk (0xffu << FLEX_US_IF_IRDA_FILTER_Pos) /**< \brief (FLEX_US_IF) IrDA Filter */
#define FLEX_US_IF_IRDA_FILTER(value) ((FLEX_US_IF_IRDA_FILTER_Msk & ((value) << FLEX_US_IF_IRDA_FILTER_Pos)))
/* -------- FLEX_US_MAN : (FLEXCOM Offset: 0x250) USART Manchester Configuration Register -------- */
#define FLEX_US_MAN_TX_PL_Pos 0
#define FLEX_US_MAN_TX_PL_Msk (0xfu << FLEX_US_MAN_TX_PL_Pos) /**< \brief (FLEX_US_MAN) Transmitter Preamble Length */
#define FLEX_US_MAN_TX_PL(value) ((FLEX_US_MAN_TX_PL_Msk & ((value) << FLEX_US_MAN_TX_PL_Pos)))
#define FLEX_US_MAN_TX_PP_Pos 8
#define FLEX_US_MAN_TX_PP_Msk (0x3u << FLEX_US_MAN_TX_PP_Pos) /**< \brief (FLEX_US_MAN) Transmitter Preamble Pattern */
#define FLEX_US_MAN_TX_PP(value) ((FLEX_US_MAN_TX_PP_Msk & ((value) << FLEX_US_MAN_TX_PP_Pos)))
#define   FLEX_US_MAN_TX_PP_ALL_ONE (0x0u << 8) /**< \brief (FLEX_US_MAN) The preamble is composed of '1's */
#define   FLEX_US_MAN_TX_PP_ALL_ZERO (0x1u << 8) /**< \brief (FLEX_US_MAN) The preamble is composed of '0's */
#define   FLEX_US_MAN_TX_PP_ZERO_ONE (0x2u << 8) /**< \brief (FLEX_US_MAN) The preamble is composed of '01's */
#define   FLEX_US_MAN_TX_PP_ONE_ZERO (0x3u << 8) /**< \brief (FLEX_US_MAN) The preamble is composed of '10's */
#define FLEX_US_MAN_TX_MPOL (0x1u << 12) /**< \brief (FLEX_US_MAN) Transmitter Manchester Polarity */
#define FLEX_US_MAN_RX_PL_Pos 16
#define FLEX_US_MAN_RX_PL_Msk (0xfu << FLEX_US_MAN_RX_PL_Pos) /**< \brief (FLEX_US_MAN) Receiver Preamble Length */
#define FLEX_US_MAN_RX_PL(value) ((FLEX_US_MAN_RX_PL_Msk & ((value) << FLEX_US_MAN_RX_PL_Pos)))
#define FLEX_US_MAN_RX_PP_Pos 24
#define FLEX_US_MAN_RX_PP_Msk (0x3u << FLEX_US_MAN_RX_PP_Pos) /**< \brief (FLEX_US_MAN) Receiver Preamble Pattern detected */
#define FLEX_US_MAN_RX_PP(value) ((FLEX_US_MAN_RX_PP_Msk & ((value) << FLEX_US_MAN_RX_PP_Pos)))
#define   FLEX_US_MAN_RX_PP_ALL_ONE (0x0u << 24) /**< \brief (FLEX_US_MAN) The preamble is composed of '1's */
#define   FLEX_US_MAN_RX_PP_ALL_ZERO (0x1u << 24) /**< \brief (FLEX_US_MAN) The preamble is composed of '0's */
#define   FLEX_US_MAN_RX_PP_ZERO_ONE (0x2u << 24) /**< \brief (FLEX_US_MAN) The preamble is composed of '01's */
#define   FLEX_US_MAN_RX_PP_ONE_ZERO (0x3u << 24) /**< \brief (FLEX_US_MAN) The preamble is composed of '10's */
#define FLEX_US_MAN_RX_MPOL (0x1u << 28) /**< \brief (FLEX_US_MAN) Receiver Manchester Polarity */
#define FLEX_US_MAN_ONE (0x1u << 29) /**< \brief (FLEX_US_MAN) Must Be Set to 1 */
#define FLEX_US_MAN_DRIFT (0x1u << 30) /**< \brief (FLEX_US_MAN) Drift Compensation */
#define FLEX_US_MAN_RXIDLEV (0x1u << 31) /**< \brief (FLEX_US_MAN) Receiver Idle Value */
/* -------- FLEX_US_LINMR : (FLEXCOM Offset: 0x254) USART LIN Mode Register -------- */
#define FLEX_US_LINMR_NACT_Pos 0
#define FLEX_US_LINMR_NACT_Msk (0x3u << FLEX_US_LINMR_NACT_Pos) /**< \brief (FLEX_US_LINMR) LIN Node Action */
#define FLEX_US_LINMR_NACT(value) ((FLEX_US_LINMR_NACT_Msk & ((value) << FLEX_US_LINMR_NACT_Pos)))
#define   FLEX_US_LINMR_NACT_PUBLISH (0x0u << 0) /**< \brief (FLEX_US_LINMR) The USART transmits the response. */
#define   FLEX_US_LINMR_NACT_SUBSCRIBE (0x1u << 0) /**< \brief (FLEX_US_LINMR) The USART receives the response. */
#define   FLEX_US_LINMR_NACT_IGNORE (0x2u << 0) /**< \brief (FLEX_US_LINMR) The USART does not transmit and does not receive the response. */
#define FLEX_US_LINMR_PARDIS (0x1u << 2) /**< \brief (FLEX_US_LINMR) Parity Disable */
#define FLEX_US_LINMR_CHKDIS (0x1u << 3) /**< \brief (FLEX_US_LINMR) Checksum Disable */
#define FLEX_US_LINMR_CHKTYP (0x1u << 4) /**< \brief (FLEX_US_LINMR) Checksum Type */
#define FLEX_US_LINMR_DLM (0x1u << 5) /**< \brief (FLEX_US_LINMR) Data Length Mode */
#define FLEX_US_LINMR_FSDIS (0x1u << 6) /**< \brief (FLEX_US_LINMR) Frame Slot Mode Disable */
#define FLEX_US_LINMR_WKUPTYP (0x1u << 7) /**< \brief (FLEX_US_LINMR) Wakeup Signal Type */
#define FLEX_US_LINMR_DLC_Pos 8
#define FLEX_US_LINMR_DLC_Msk (0xffu << FLEX_US_LINMR_DLC_Pos) /**< \brief (FLEX_US_LINMR) Data Length Control */
#define FLEX_US_LINMR_DLC(value) ((FLEX_US_LINMR_DLC_Msk & ((value) << FLEX_US_LINMR_DLC_Pos)))
#define FLEX_US_LINMR_PDCM (0x1u << 16) /**< \brief (FLEX_US_LINMR) DMA Mode */
#define FLEX_US_LINMR_SYNCDIS (0x1u << 17) /**< \brief (FLEX_US_LINMR) Synchronization Disable */
/* -------- FLEX_US_LINIR : (FLEXCOM Offset: 0x258) USART LIN Identifier Register -------- */
#define FLEX_US_LINIR_IDCHR_Pos 0
#define FLEX_US_LINIR_IDCHR_Msk (0xffu << FLEX_US_LINIR_IDCHR_Pos) /**< \brief (FLEX_US_LINIR) Identifier Character */
#define FLEX_US_LINIR_IDCHR(value) ((FLEX_US_LINIR_IDCHR_Msk & ((value) << FLEX_US_LINIR_IDCHR_Pos)))
/* -------- FLEX_US_LINBRR : (FLEXCOM Offset: 0x25C) USART LIN Baud Rate Register -------- */
#define FLEX_US_LINBRR_LINCD_Pos 0
#define FLEX_US_LINBRR_LINCD_Msk (0xffffu << FLEX_US_LINBRR_LINCD_Pos) /**< \brief (FLEX_US_LINBRR) Clock Divider after Synchronization */
#define FLEX_US_LINBRR_LINFP_Pos 16
#define FLEX_US_LINBRR_LINFP_Msk (0x7u << FLEX_US_LINBRR_LINFP_Pos) /**< \brief (FLEX_US_LINBRR) Fractional Part after Synchronization */
/* -------- FLEX_US_LONMR : (FLEXCOM Offset: 0x260) USART LON Mode Register -------- */
#define FLEX_US_LONMR_COMMT (0x1u << 0) /**< \brief (FLEX_US_LONMR) LON comm_type Parameter Value */
#define FLEX_US_LONMR_COLDET (0x1u << 1) /**< \brief (FLEX_US_LONMR) LON Collision Detection Feature */
#define FLEX_US_LONMR_TCOL (0x1u << 2) /**< \brief (FLEX_US_LONMR) Terminate Frame upon Collision Notification */
#define FLEX_US_LONMR_CDTAIL (0x1u << 3) /**< \brief (FLEX_US_LONMR) LON Collision Detection on Frame Tail */
#define FLEX_US_LONMR_DMAM (0x1u << 4) /**< \brief (FLEX_US_LONMR) LON DMA Mode */
#define FLEX_US_LONMR_LCDS (0x1u << 5) /**< \brief (FLEX_US_LONMR) LON Collision Detection Source */
#define FLEX_US_LONMR_EOFS_Pos 16
#define FLEX_US_LONMR_EOFS_Msk (0xffu << FLEX_US_LONMR_EOFS_Pos) /**< \brief (FLEX_US_LONMR) End of Frame Condition Size */
#define FLEX_US_LONMR_EOFS(value) ((FLEX_US_LONMR_EOFS_Msk & ((value) << FLEX_US_LONMR_EOFS_Pos)))
/* -------- FLEX_US_LONPR : (FLEXCOM Offset: 0x264) USART LON Preamble Register -------- */
#define FLEX_US_LONPR_LONPL_Pos 0
#define FLEX_US_LONPR_LONPL_Msk (0x3fffu << FLEX_US_LONPR_LONPL_Pos) /**< \brief (FLEX_US_LONPR) LON Preamble Length */
#define FLEX_US_LONPR_LONPL(value) ((FLEX_US_LONPR_LONPL_Msk & ((value) << FLEX_US_LONPR_LONPL_Pos)))
/* -------- FLEX_US_LONDL : (FLEXCOM Offset: 0x268) USART LON Data Length Register -------- */
#define FLEX_US_LONDL_LONDL_Pos 0
#define FLEX_US_LONDL_LONDL_Msk (0xffu << FLEX_US_LONDL_LONDL_Pos) /**< \brief (FLEX_US_LONDL) LON Data Length */
#define FLEX_US_LONDL_LONDL(value) ((FLEX_US_LONDL_LONDL_Msk & ((value) << FLEX_US_LONDL_LONDL_Pos)))
/* -------- FLEX_US_LONL2HDR : (FLEXCOM Offset: 0x26C) USART LON L2HDR Register -------- */
#define FLEX_US_LONL2HDR_BLI_Pos 0
#define FLEX_US_LONL2HDR_BLI_Msk (0x3fu << FLEX_US_LONL2HDR_BLI_Pos) /**< \brief (FLEX_US_LONL2HDR) LON Backlog Increment */
#define FLEX_US_LONL2HDR_BLI(value) ((FLEX_US_LONL2HDR_BLI_Msk & ((value) << FLEX_US_LONL2HDR_BLI_Pos)))
#define FLEX_US_LONL2HDR_ALTP (0x1u << 6) /**< \brief (FLEX_US_LONL2HDR) LON Alternate Path Bit */
#define FLEX_US_LONL2HDR_PB (0x1u << 7) /**< \brief (FLEX_US_LONL2HDR) LON Priority Bit */
/* -------- FLEX_US_LONBL : (FLEXCOM Offset: 0x270) USART LON Backlog Register -------- */
#define FLEX_US_LONBL_LONBL_Pos 0
#define FLEX_US_LONBL_LONBL_Msk (0x3fu << FLEX_US_LONBL_LONBL_Pos) /**< \brief (FLEX_US_LONBL) LON Node Backlog Value */
/* -------- FLEX_US_LONB1TX : (FLEXCOM Offset: 0x274) USART LON Beta1 Tx Register -------- */
#define FLEX_US_LONB1TX_BETA1TX_Pos 0
#define FLEX_US_LONB1TX_BETA1TX_Msk (0xffffffu << FLEX_US_LONB1TX_BETA1TX_Pos) /**< \brief (FLEX_US_LONB1TX) LON Beta1 Length after Transmission */
#define FLEX_US_LONB1TX_BETA1TX(value) ((FLEX_US_LONB1TX_BETA1TX_Msk & ((value) << FLEX_US_LONB1TX_BETA1TX_Pos)))
/* -------- FLEX_US_LONB1RX : (FLEXCOM Offset: 0x278) USART LON Beta1 Rx Register -------- */
#define FLEX_US_LONB1RX_BETA1RX_Pos 0
#define FLEX_US_LONB1RX_BETA1RX_Msk (0xffffffu << FLEX_US_LONB1RX_BETA1RX_Pos) /**< \brief (FLEX_US_LONB1RX) LON Beta1 Length after Reception */
#define FLEX_US_LONB1RX_BETA1RX(value) ((FLEX_US_LONB1RX_BETA1RX_Msk & ((value) << FLEX_US_LONB1RX_BETA1RX_Pos)))
/* -------- FLEX_US_LONPRIO : (FLEXCOM Offset: 0x27C) USART LON Priority Register -------- */
#define FLEX_US_LONPRIO_PSNB_Pos 0
#define FLEX_US_LONPRIO_PSNB_Msk (0x7fu << FLEX_US_LONPRIO_PSNB_Pos) /**< \brief (FLEX_US_LONPRIO) LON Priority Slot Number */
#define FLEX_US_LONPRIO_PSNB(value) ((FLEX_US_LONPRIO_PSNB_Msk & ((value) << FLEX_US_LONPRIO_PSNB_Pos)))
#define FLEX_US_LONPRIO_NPS_Pos 8
#define FLEX_US_LONPRIO_NPS_Msk (0x7fu << FLEX_US_LONPRIO_NPS_Pos) /**< \brief (FLEX_US_LONPRIO) LON Node Priority Slot */
#define FLEX_US_LONPRIO_NPS(value) ((FLEX_US_LONPRIO_NPS_Msk & ((value) << FLEX_US_LONPRIO_NPS_Pos)))
/* -------- FLEX_US_IDTTX : (FLEXCOM Offset: 0x280) USART LON IDT Tx Register -------- */
#define FLEX_US_IDTTX_IDTTX_Pos 0
#define FLEX_US_IDTTX_IDTTX_Msk (0xffffffu << FLEX_US_IDTTX_IDTTX_Pos) /**< \brief (FLEX_US_IDTTX) LON Indeterminate Time after Transmission (comm_type = 1 mode only) */
#define FLEX_US_IDTTX_IDTTX(value) ((FLEX_US_IDTTX_IDTTX_Msk & ((value) << FLEX_US_IDTTX_IDTTX_Pos)))
/* -------- FLEX_US_IDTRX : (FLEXCOM Offset: 0x284) USART LON IDT Rx Register -------- */
#define FLEX_US_IDTRX_IDTRX_Pos 0
#define FLEX_US_IDTRX_IDTRX_Msk (0xffffffu << FLEX_US_IDTRX_IDTRX_Pos) /**< \brief (FLEX_US_IDTRX) LON Indeterminate Time after Reception (comm_type = 1 mode only) */
#define FLEX_US_IDTRX_IDTRX(value) ((FLEX_US_IDTRX_IDTRX_Msk & ((value) << FLEX_US_IDTRX_IDTRX_Pos)))
/* -------- FLEX_US_ICDIFF : (FLEXCOM Offset: 0x288) USART IC DIFF Register -------- */
#define FLEX_US_ICDIFF_ICDIFF_Pos 0
#define FLEX_US_ICDIFF_ICDIFF_Msk (0xfu << FLEX_US_ICDIFF_ICDIFF_Pos) /**< \brief (FLEX_US_ICDIFF) IC Differentiator Number */
#define FLEX_US_ICDIFF_ICDIFF(value) ((FLEX_US_ICDIFF_ICDIFF_Msk & ((value) << FLEX_US_ICDIFF_ICDIFF_Pos)))
/* -------- FLEX_US_CMPR : (FLEXCOM Offset: 0x290) USART Comparison Register -------- */
#define FLEX_US_CMPR_VAL1_Pos 0
#define FLEX_US_CMPR_VAL1_Msk (0x1ffu << FLEX_US_CMPR_VAL1_Pos) /**< \brief (FLEX_US_CMPR) First Comparison Value for Received Character */
#define FLEX_US_CMPR_VAL1(value) ((FLEX_US_CMPR_VAL1_Msk & ((value) << FLEX_US_CMPR_VAL1_Pos)))
#define FLEX_US_CMPR_CMPMODE_Pos 12
#define FLEX_US_CMPR_CMPMODE_Msk (0x3u << FLEX_US_CMPR_CMPMODE_Pos) /**< \brief (FLEX_US_CMPR) Comparison Mode */
#define FLEX_US_CMPR_CMPMODE(value) ((FLEX_US_CMPR_CMPMODE_Msk & ((value) << FLEX_US_CMPR_CMPMODE_Pos)))
#define   FLEX_US_CMPR_CMPMODE_FLAG_ONLY (0x0u << 12) /**< \brief (FLEX_US_CMPR) Any character is received and comparison function drives CMP flag. */
#define   FLEX_US_CMPR_CMPMODE_START_CONDITION (0x1u << 12) /**< \brief (FLEX_US_CMPR) Comparison condition must be met to start reception. */
#define   FLEX_US_CMPR_CMPMODE_FILTER (0x2u << 12) /**< \brief (FLEX_US_CMPR) Comparison must be met to receive the current data only */
#define FLEX_US_CMPR_CMPPAR (0x1u << 14) /**< \brief (FLEX_US_CMPR) Compare Parity */
#define FLEX_US_CMPR_VAL2_Pos 16
#define FLEX_US_CMPR_VAL2_Msk (0x1ffu << FLEX_US_CMPR_VAL2_Pos) /**< \brief (FLEX_US_CMPR) Second Comparison Value for Received Character */
#define FLEX_US_CMPR_VAL2(value) ((FLEX_US_CMPR_VAL2_Msk & ((value) << FLEX_US_CMPR_VAL2_Pos)))
/* -------- FLEX_US_FMR : (FLEXCOM Offset: 0x2A0) USART FIFO Mode Register -------- */
#define FLEX_US_FMR_TXRDYM_Pos 0
#define FLEX_US_FMR_TXRDYM_Msk (0x3u << FLEX_US_FMR_TXRDYM_Pos) /**< \brief (FLEX_US_FMR) Transmitter Ready Mode */
#define FLEX_US_FMR_TXRDYM(value) ((FLEX_US_FMR_TXRDYM_Msk & ((value) << FLEX_US_FMR_TXRDYM_Pos)))
#define   FLEX_US_FMR_TXRDYM_ONE_DATA (0x0u << 0) /**< \brief (FLEX_US_FMR) TXRDY will be at level '1' when at least one data can be written in the Transmit FIFO */
#define   FLEX_US_FMR_TXRDYM_TWO_DATA (0x1u << 0) /**< \brief (FLEX_US_FMR) TXRDY will be at level '1' when at least two data can be written in the Transmit FIFO */
#define   FLEX_US_FMR_TXRDYM_FOUR_DATA (0x2u << 0) /**< \brief (FLEX_US_FMR) TXRDY will be at level '1' when at least four data can be written in the Transmit FIFO */
#define FLEX_US_FMR_RXRDYM_Pos 4
#define FLEX_US_FMR_RXRDYM_Msk (0x3u << FLEX_US_FMR_RXRDYM_Pos) /**< \brief (FLEX_US_FMR) Receiver Ready Mode */
#define FLEX_US_FMR_RXRDYM(value) ((FLEX_US_FMR_RXRDYM_Msk & ((value) << FLEX_US_FMR_RXRDYM_Pos)))
#define   FLEX_US_FMR_RXRDYM_ONE_DATA (0x0u << 4) /**< \brief (FLEX_US_FMR) RXRDY will be at level '1' when at least one unread data is in the Receive FIFO */
#define   FLEX_US_FMR_RXRDYM_TWO_DATA (0x1u << 4) /**< \brief (FLEX_US_FMR) RXRDY will be at level '1' when at least two unread data are in the Receive FIFO */
#define   FLEX_US_FMR_RXRDYM_FOUR_DATA (0x2u << 4) /**< \brief (FLEX_US_FMR) RXRDY will be at level '1' when at least four unread data are in the Receive FIFO */
#define FLEX_US_FMR_FRTSC (0x1u << 7) /**< \brief (FLEX_US_FMR) FIFO RTS Pin Control enable (Hardware Handshaking mode only) */
#define FLEX_US_FMR_TXFTHRES_Pos 8
#define FLEX_US_FMR_TXFTHRES_Msk (0x3fu << FLEX_US_FMR_TXFTHRES_Pos) /**< \brief (FLEX_US_FMR) Transmit FIFO Threshold */
#define FLEX_US_FMR_TXFTHRES(value) ((FLEX_US_FMR_TXFTHRES_Msk & ((value) << FLEX_US_FMR_TXFTHRES_Pos)))
#define FLEX_US_FMR_RXFTHRES_Pos 16
#define FLEX_US_FMR_RXFTHRES_Msk (0x3fu << FLEX_US_FMR_RXFTHRES_Pos) /**< \brief (FLEX_US_FMR) Receive FIFO Threshold */
#define FLEX_US_FMR_RXFTHRES(value) ((FLEX_US_FMR_RXFTHRES_Msk & ((value) << FLEX_US_FMR_RXFTHRES_Pos)))
#define FLEX_US_FMR_RXFTHRES2_Pos 24
#define FLEX_US_FMR_RXFTHRES2_Msk (0x3fu << FLEX_US_FMR_RXFTHRES2_Pos) /**< \brief (FLEX_US_FMR) Receive FIFO Threshold 2 */
#define FLEX_US_FMR_RXFTHRES2(value) ((FLEX_US_FMR_RXFTHRES2_Msk & ((value) << FLEX_US_FMR_RXFTHRES2_Pos)))
/* -------- FLEX_US_FLR : (FLEXCOM Offset: 0x2A4) USART FIFO Level Register -------- */
#define FLEX_US_FLR_TXFL_Pos 0
#define FLEX_US_FLR_TXFL_Msk (0x3fu << FLEX_US_FLR_TXFL_Pos) /**< \brief (FLEX_US_FLR) Transmit FIFO Level */
#define FLEX_US_FLR_RXFL_Pos 16
#define FLEX_US_FLR_RXFL_Msk (0x3fu << FLEX_US_FLR_RXFL_Pos) /**< \brief (FLEX_US_FLR) Receive FIFO Level */
/* -------- FLEX_US_FIER : (FLEXCOM Offset: 0x2A8) USART FIFO Interrupt Enable Register -------- */
#define FLEX_US_FIER_TXFEF (0x1u << 0) /**< \brief (FLEX_US_FIER) TXFEF Interrupt Enable */
#define FLEX_US_FIER_TXFFF (0x1u << 1) /**< \brief (FLEX_US_FIER) TXFFF Interrupt Enable */
#define FLEX_US_FIER_TXFTHF (0x1u << 2) /**< \brief (FLEX_US_FIER) TXFTHF Interrupt Enable */
#define FLEX_US_FIER_RXFEF (0x1u << 3) /**< \brief (FLEX_US_FIER) RXFEF Interrupt Enable */
#define FLEX_US_FIER_RXFFF (0x1u << 4) /**< \brief (FLEX_US_FIER) RXFFF Interrupt Enable */
#define FLEX_US_FIER_RXFTHF (0x1u << 5) /**< \brief (FLEX_US_FIER) RXFTHF Interrupt Enable */
#define FLEX_US_FIER_TXFPTEF (0x1u << 6) /**< \brief (FLEX_US_FIER) TXFPTEF Interrupt Enable */
#define FLEX_US_FIER_RXFPTEF (0x1u << 7) /**< \brief (FLEX_US_FIER) RXFPTEF Interrupt Enable */
#define FLEX_US_FIER_RXFTHF2 (0x1u << 9) /**< \brief (FLEX_US_FIER) RXFTHF2 Interrupt Enable */
/* -------- FLEX_US_FIDR : (FLEXCOM Offset: 0x2AC) USART FIFO Interrupt Disable Register -------- */
#define FLEX_US_FIDR_TXFEF (0x1u << 0) /**< \brief (FLEX_US_FIDR) TXFEF Interrupt Disable */
#define FLEX_US_FIDR_TXFFF (0x1u << 1) /**< \brief (FLEX_US_FIDR) TXFFF Interrupt Disable */
#define FLEX_US_FIDR_TXFTHF (0x1u << 2) /**< \brief (FLEX_US_FIDR) TXFTHF Interrupt Disable */
#define FLEX_US_FIDR_RXFEF (0x1u << 3) /**< \brief (FLEX_US_FIDR) RXFEF Interrupt Disable */
#define FLEX_US_FIDR_RXFFF (0x1u << 4) /**< \brief (FLEX_US_FIDR) RXFFF Interrupt Disable */
#define FLEX_US_FIDR_RXFTHF (0x1u << 5) /**< \brief (FLEX_US_FIDR) RXFTHF Interrupt Disable */
#define FLEX_US_FIDR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_US_FIDR) TXFPTEF Interrupt Disable */
#define FLEX_US_FIDR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_US_FIDR) RXFPTEF Interrupt Disable */
#define FLEX_US_FIDR_RXFTHF2 (0x1u << 9) /**< \brief (FLEX_US_FIDR) RXFTHF2 Interrupt Disable */
/* -------- FLEX_US_FIMR : (FLEXCOM Offset: 0x2B0) USART FIFO Interrupt Mask Register -------- */
#define FLEX_US_FIMR_TXFEF (0x1u << 0) /**< \brief (FLEX_US_FIMR) TXFEF Interrupt Mask */
#define FLEX_US_FIMR_TXFFF (0x1u << 1) /**< \brief (FLEX_US_FIMR) TXFFF Interrupt Mask */
#define FLEX_US_FIMR_TXFTHF (0x1u << 2) /**< \brief (FLEX_US_FIMR) TXFTHF Interrupt Mask */
#define FLEX_US_FIMR_RXFEF (0x1u << 3) /**< \brief (FLEX_US_FIMR) RXFEF Interrupt Mask */
#define FLEX_US_FIMR_RXFFF (0x1u << 4) /**< \brief (FLEX_US_FIMR) RXFFF Interrupt Mask */
#define FLEX_US_FIMR_RXFTHF (0x1u << 5) /**< \brief (FLEX_US_FIMR) RXFTHF Interrupt Mask */
#define FLEX_US_FIMR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_US_FIMR) TXFPTEF Interrupt Mask */
#define FLEX_US_FIMR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_US_FIMR) RXFPTEF Interrupt Mask */
#define FLEX_US_FIMR_RXFTHF2 (0x1u << 9) /**< \brief (FLEX_US_FIMR) RXFTHF2 Interrupt Mask */
/* -------- FLEX_US_FESR : (FLEXCOM Offset: 0x2B4) USART FIFO Event Status Register -------- */
#define FLEX_US_FESR_TXFEF (0x1u << 0) /**< \brief (FLEX_US_FESR) Transmit FIFO Empty Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_TXFFF (0x1u << 1) /**< \brief (FLEX_US_FESR) Transmit FIFO Full Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_TXFTHF (0x1u << 2) /**< \brief (FLEX_US_FESR) Transmit FIFO Threshold Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_RXFEF (0x1u << 3) /**< \brief (FLEX_US_FESR) Receive FIFO Empty Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_RXFFF (0x1u << 4) /**< \brief (FLEX_US_FESR) Receive FIFO Full Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_RXFTHF (0x1u << 5) /**< \brief (FLEX_US_FESR) Receive FIFO Threshold Flag (cleared by writing the FLEX_US_CR.RSTSTA bit) */
#define FLEX_US_FESR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_US_FESR) Transmit FIFO Pointer Error Flag */
#define FLEX_US_FESR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_US_FESR) Receive FIFO Pointer Error Flag */
#define FLEX_US_FESR_TXFLOCK (0x1u << 8) /**< \brief (FLEX_US_FESR) Transmit FIFO Lock */
#define FLEX_US_FESR_RXFTHF2 (0x1u << 9) /**< \brief (FLEX_US_FESR) Receive FIFO Threshold Flag 2 (cleared by writing the FLEX_US_CR.RSTSTA bit) */
/* -------- FLEX_US_WPMR : (FLEXCOM Offset: 0x2E4) USART Write Protection Mode Register -------- */
#define FLEX_US_WPMR_WPEN (0x1u << 0) /**< \brief (FLEX_US_WPMR) Write Protection Enable */
#define FLEX_US_WPMR_WPITEN (0x1u << 1) /**< \brief (FLEX_US_WPMR) Write Protection Interrupt Enable */
#define FLEX_US_WPMR_WPCREN (0x1u << 2) /**< \brief (FLEX_US_WPMR) Write Protection Control Enable */
#define FLEX_US_WPMR_WPKEY_Pos 8
#define FLEX_US_WPMR_WPKEY_Msk (0xffffffu << FLEX_US_WPMR_WPKEY_Pos) /**< \brief (FLEX_US_WPMR) Write Protection Key */
#define FLEX_US_WPMR_WPKEY(value) ((FLEX_US_WPMR_WPKEY_Msk & ((value) << FLEX_US_WPMR_WPKEY_Pos)))
#define   FLEX_US_WPMR_WPKEY_PASSWD (0x555341u << 8) /**< \brief (FLEX_US_WPMR) Writing any other value in this field aborts the write operation of bits WPEN, WPITEN and WPCREN. Always reads as 0. */
/* -------- FLEX_US_WPSR : (FLEXCOM Offset: 0x2E8) USART Write Protection Status Register -------- */
#define FLEX_US_WPSR_WPVS (0x1u << 0) /**< \brief (FLEX_US_WPSR) Write Protection Violation Status */
#define FLEX_US_WPSR_WPVSRC_Pos 8
#define FLEX_US_WPSR_WPVSRC_Msk (0xffffu << FLEX_US_WPSR_WPVSRC_Pos) /**< \brief (FLEX_US_WPSR) Write Protection Violation Source */
/* -------- FLEX_SPI_CR : (FLEXCOM Offset: 0x400) SPI Control Register -------- */
#define FLEX_SPI_CR_SPIEN (0x1u << 0) /**< \brief (FLEX_SPI_CR) SPI Enable */
#define FLEX_SPI_CR_SPIDIS (0x1u << 1) /**< \brief (FLEX_SPI_CR) SPI Disable */
#define FLEX_SPI_CR_SWRST (0x1u << 7) /**< \brief (FLEX_SPI_CR) SPI Software Reset */
#define FLEX_SPI_CR_REQCLR (0x1u << 12) /**< \brief (FLEX_SPI_CR) Request to Clear the Comparison Trigger */
#define FLEX_SPI_CR_TXFCLR (0x1u << 16) /**< \brief (FLEX_SPI_CR) Transmit FIFO Clear */
#define FLEX_SPI_CR_RXFCLR (0x1u << 17) /**< \brief (FLEX_SPI_CR) Receive FIFO Clear */
#define FLEX_SPI_CR_LASTXFER (0x1u << 24) /**< \brief (FLEX_SPI_CR) Last Transfer */
#define FLEX_SPI_CR_FIFOEN (0x1u << 30) /**< \brief (FLEX_SPI_CR) FIFO Enable */
#define FLEX_SPI_CR_FIFODIS (0x1u << 31) /**< \brief (FLEX_SPI_CR) FIFO Disable */
/* -------- FLEX_SPI_MR : (FLEXCOM Offset: 0x404) SPI Mode Register -------- */
#define FLEX_SPI_MR_MSTR (0x1u << 0) /**< \brief (FLEX_SPI_MR) Master/Slave Mode */
#define FLEX_SPI_MR_PS (0x1u << 1) /**< \brief (FLEX_SPI_MR) Peripheral Select */
#define FLEX_SPI_MR_PCSDEC (0x1u << 2) /**< \brief (FLEX_SPI_MR) Chip Select Decode */
#define FLEX_SPI_MR_BRSRCCLK (0x1u << 3) /**< \brief (FLEX_SPI_MR) Bit Rate Source Clock */
#define   FLEX_SPI_MR_BRSRCCLK_PERIPH_CLK (0x0u << 3) /**< \brief (FLEX_SPI_MR) The peripheral clock is the source clock for the bit rate generation. */
#define   FLEX_SPI_MR_BRSRCCLK_GCLK (0x1u << 3) /**< \brief (FLEX_SPI_MR) GCLK is the source clock for the bit rate generation, thus the bit rate can be independent of the core/peripheral clock. */
#define FLEX_SPI_MR_MODFDIS (0x1u << 4) /**< \brief (FLEX_SPI_MR) Mode Fault Detection */
#define FLEX_SPI_MR_WDRBT (0x1u << 5) /**< \brief (FLEX_SPI_MR) Wait Data Read Before Transfer */
#define FLEX_SPI_MR_LLB (0x1u << 7) /**< \brief (FLEX_SPI_MR) Local Loopback Enable */
#define FLEX_SPI_MR_CMPMODE (0x1u << 12) /**< \brief (FLEX_SPI_MR) Comparison Mode */
#define   FLEX_SPI_MR_CMPMODE_FLAG_ONLY (0x0u << 12) /**< \brief (FLEX_SPI_MR) Any character is received and comparison function drives CMP flag. */
#define   FLEX_SPI_MR_CMPMODE_START_CONDITION (0x1u << 12) /**< \brief (FLEX_SPI_MR) Comparison condition must be met to start reception of all incoming characters until REQCLR is set. */
#define FLEX_SPI_MR_PCS_Pos 16
#define FLEX_SPI_MR_PCS_Msk (0xfu << FLEX_SPI_MR_PCS_Pos) /**< \brief (FLEX_SPI_MR) Peripheral Chip Select */
#define FLEX_SPI_MR_PCS(value) ((FLEX_SPI_MR_PCS_Msk & ((value) << FLEX_SPI_MR_PCS_Pos)))
#define FLEX_SPI_MR_DLYBCS_Pos 24
#define FLEX_SPI_MR_DLYBCS_Msk (0xffu << FLEX_SPI_MR_DLYBCS_Pos) /**< \brief (FLEX_SPI_MR) Delay Between Chip Selects */
#define FLEX_SPI_MR_DLYBCS(value) ((FLEX_SPI_MR_DLYBCS_Msk & ((value) << FLEX_SPI_MR_DLYBCS_Pos)))
/* -------- FLEX_SPI_RDR : (FLEXCOM Offset: 0x408) SPI Receive Data Register -------- */
#define FLEX_SPI_RDR_RD_Pos 0
#define FLEX_SPI_RDR_RD_Msk (0xffffu << FLEX_SPI_RDR_RD_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_PCS_Pos 16
#define FLEX_SPI_RDR_PCS_Msk (0xfu << FLEX_SPI_RDR_PCS_Pos) /**< \brief (FLEX_SPI_RDR) Peripheral Chip Select */
#define FLEX_SPI_RDR_RD0_Pos 0
#define FLEX_SPI_RDR_RD0_Msk (0xffu << FLEX_SPI_RDR_RD0_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_RD1_Pos 8
#define FLEX_SPI_RDR_RD1_Msk (0xffu << FLEX_SPI_RDR_RD1_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_RD2_Pos 16
#define FLEX_SPI_RDR_RD2_Msk (0xffu << FLEX_SPI_RDR_RD2_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_RD3_Pos 24
#define FLEX_SPI_RDR_RD3_Msk (0xffu << FLEX_SPI_RDR_RD3_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_RD0_FIFO_MULTI_DATA_16_Pos 0
#define FLEX_SPI_RDR_RD0_FIFO_MULTI_DATA_16_Msk (0xffffu << FLEX_SPI_RDR_RD0_FIFO_MULTI_DATA_16_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
#define FLEX_SPI_RDR_RD1_FIFO_MULTI_DATA_16_Pos 16
#define FLEX_SPI_RDR_RD1_FIFO_MULTI_DATA_16_Msk (0xffffu << FLEX_SPI_RDR_RD1_FIFO_MULTI_DATA_16_Pos) /**< \brief (FLEX_SPI_RDR) Receive Data */
/* -------- FLEX_SPI_TDR : (FLEXCOM Offset: 0x40C) SPI Transmit Data Register -------- */
#define FLEX_SPI_TDR_TD_Pos 0
#define FLEX_SPI_TDR_TD_Msk (0xffffu << FLEX_SPI_TDR_TD_Pos) /**< \brief (FLEX_SPI_TDR) Transmit Data */
#define FLEX_SPI_TDR_TD(value) ((FLEX_SPI_TDR_TD_Msk & ((value) << FLEX_SPI_TDR_TD_Pos)))
#define FLEX_SPI_TDR_PCS_Pos 16
#define FLEX_SPI_TDR_PCS_Msk (0xfu << FLEX_SPI_TDR_PCS_Pos) /**< \brief (FLEX_SPI_TDR) Peripheral Chip Select */
#define FLEX_SPI_TDR_PCS(value) ((FLEX_SPI_TDR_PCS_Msk & ((value) << FLEX_SPI_TDR_PCS_Pos)))
#define FLEX_SPI_TDR_LASTXFER (0x1u << 24) /**< \brief (FLEX_SPI_TDR) Last Transfer */
#define FLEX_SPI_TDR_TD0_Pos 0
#define FLEX_SPI_TDR_TD0_Msk (0xffffu << FLEX_SPI_TDR_TD0_Pos) /**< \brief (FLEX_SPI_TDR) Transmit Data */
#define FLEX_SPI_TDR_TD0(value) ((FLEX_SPI_TDR_TD0_Msk & ((value) << FLEX_SPI_TDR_TD0_Pos)))
#define FLEX_SPI_TDR_TD1_Pos 16
#define FLEX_SPI_TDR_TD1_Msk (0xffffu << FLEX_SPI_TDR_TD1_Pos) /**< \brief (FLEX_SPI_TDR) Transmit Data */
#define FLEX_SPI_TDR_TD1(value) ((FLEX_SPI_TDR_TD1_Msk & ((value) << FLEX_SPI_TDR_TD1_Pos)))
/* -------- FLEX_SPI_SR : (FLEXCOM Offset: 0x410) SPI Status Register -------- */
#define FLEX_SPI_SR_RDRF (0x1u << 0) /**< \brief (FLEX_SPI_SR) Receive Data Register Full (cleared by reading FLEX_SPI_RDR) */
#define FLEX_SPI_SR_TDRE (0x1u << 1) /**< \brief (FLEX_SPI_SR) Transmit Data Register Empty (cleared by writing FLEX_SPI_TDR) */
#define FLEX_SPI_SR_MODF (0x1u << 2) /**< \brief (FLEX_SPI_SR) Mode Fault Error (cleared on read) */
#define FLEX_SPI_SR_OVRES (0x1u << 3) /**< \brief (FLEX_SPI_SR) Overrun Error Status (cleared on read) */
#define FLEX_SPI_SR_NSSR (0x1u << 8) /**< \brief (FLEX_SPI_SR) NSS Rising (cleared on read) */
#define FLEX_SPI_SR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_SPI_SR) Transmission Registers Empty (cleared by writing FLEX_SPI_TDR) */
#define FLEX_SPI_SR_UNDES (0x1u << 10) /**< \brief (FLEX_SPI_SR) Underrun Error Status (Slave mode only) (cleared on read) */
#define FLEX_SPI_SR_CMP (0x1u << 11) /**< \brief (FLEX_SPI_SR) Comparison Status (cleared on read) */
#define FLEX_SPI_SR_SFERR (0x1u << 12) /**< \brief (FLEX_SPI_SR) Slave Frame Error (cleared on read) */
#define FLEX_SPI_SR_SPIENS (0x1u << 16) /**< \brief (FLEX_SPI_SR) SPI Enable Status */
#define FLEX_SPI_SR_TXFEF (0x1u << 24) /**< \brief (FLEX_SPI_SR) Transmit FIFO Empty Flag (cleared on read) */
#define FLEX_SPI_SR_TXFFF (0x1u << 25) /**< \brief (FLEX_SPI_SR) Transmit FIFO Full Flag (cleared on read) */
#define FLEX_SPI_SR_TXFTHF (0x1u << 26) /**< \brief (FLEX_SPI_SR) Transmit FIFO Threshold Flag (cleared on read) */
#define FLEX_SPI_SR_RXFEF (0x1u << 27) /**< \brief (FLEX_SPI_SR) Receive FIFO Empty Flag */
#define FLEX_SPI_SR_RXFFF (0x1u << 28) /**< \brief (FLEX_SPI_SR) Receive FIFO Full Flag */
#define FLEX_SPI_SR_RXFTHF (0x1u << 29) /**< \brief (FLEX_SPI_SR) Receive FIFO Threshold Flag */
#define FLEX_SPI_SR_TXFPTEF (0x1u << 30) /**< \brief (FLEX_SPI_SR) Transmit FIFO Pointer Error Flag */
#define FLEX_SPI_SR_RXFPTEF (0x1u << 31) /**< \brief (FLEX_SPI_SR) Receive FIFO Pointer Error Flag */
/* -------- FLEX_SPI_IER : (FLEXCOM Offset: 0x414) SPI Interrupt Enable Register -------- */
#define FLEX_SPI_IER_RDRF (0x1u << 0) /**< \brief (FLEX_SPI_IER) Receive Data Register Full Interrupt Enable */
#define FLEX_SPI_IER_TDRE (0x1u << 1) /**< \brief (FLEX_SPI_IER) SPI Transmit Data Register Empty Interrupt Enable */
#define FLEX_SPI_IER_MODF (0x1u << 2) /**< \brief (FLEX_SPI_IER) Mode Fault Error Interrupt Enable */
#define FLEX_SPI_IER_OVRES (0x1u << 3) /**< \brief (FLEX_SPI_IER) Overrun Error Interrupt Enable */
#define FLEX_SPI_IER_NSSR (0x1u << 8) /**< \brief (FLEX_SPI_IER) NSS Rising Interrupt Enable */
#define FLEX_SPI_IER_TXEMPTY (0x1u << 9) /**< \brief (FLEX_SPI_IER) Transmission Registers Empty Enable */
#define FLEX_SPI_IER_UNDES (0x1u << 10) /**< \brief (FLEX_SPI_IER) Underrun Error Interrupt Enable */
#define FLEX_SPI_IER_CMP (0x1u << 11) /**< \brief (FLEX_SPI_IER) Comparison Interrupt Enable */
#define FLEX_SPI_IER_TXFEF (0x1u << 24) /**< \brief (FLEX_SPI_IER) TXFEF Interrupt Enable */
#define FLEX_SPI_IER_TXFFF (0x1u << 25) /**< \brief (FLEX_SPI_IER) TXFFF Interrupt Enable */
#define FLEX_SPI_IER_TXFTHF (0x1u << 26) /**< \brief (FLEX_SPI_IER) TXFTHF Interrupt Enable */
#define FLEX_SPI_IER_RXFEF (0x1u << 27) /**< \brief (FLEX_SPI_IER) RXFEF Interrupt Enable */
#define FLEX_SPI_IER_RXFFF (0x1u << 28) /**< \brief (FLEX_SPI_IER) RXFFF Interrupt Enable */
#define FLEX_SPI_IER_RXFTHF (0x1u << 29) /**< \brief (FLEX_SPI_IER) RXFTHF Interrupt Enable */
#define FLEX_SPI_IER_TXFPTEF (0x1u << 30) /**< \brief (FLEX_SPI_IER) TXFPTEF Interrupt Enable */
#define FLEX_SPI_IER_RXFPTEF (0x1u << 31) /**< \brief (FLEX_SPI_IER) RXFPTEF Interrupt Enable */
/* -------- FLEX_SPI_IDR : (FLEXCOM Offset: 0x418) SPI Interrupt Disable Register -------- */
#define FLEX_SPI_IDR_RDRF (0x1u << 0) /**< \brief (FLEX_SPI_IDR) Receive Data Register Full Interrupt Disable */
#define FLEX_SPI_IDR_TDRE (0x1u << 1) /**< \brief (FLEX_SPI_IDR) SPI Transmit Data Register Empty Interrupt Disable */
#define FLEX_SPI_IDR_MODF (0x1u << 2) /**< \brief (FLEX_SPI_IDR) Mode Fault Error Interrupt Disable */
#define FLEX_SPI_IDR_OVRES (0x1u << 3) /**< \brief (FLEX_SPI_IDR) Overrun Error Interrupt Disable */
#define FLEX_SPI_IDR_NSSR (0x1u << 8) /**< \brief (FLEX_SPI_IDR) NSS Rising Interrupt Disable */
#define FLEX_SPI_IDR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_SPI_IDR) Transmission Registers Empty Disable */
#define FLEX_SPI_IDR_UNDES (0x1u << 10) /**< \brief (FLEX_SPI_IDR) Underrun Error Interrupt Disable */
#define FLEX_SPI_IDR_CMP (0x1u << 11) /**< \brief (FLEX_SPI_IDR) Comparison Interrupt Disable */
#define FLEX_SPI_IDR_TXFEF (0x1u << 24) /**< \brief (FLEX_SPI_IDR) TXFEF Interrupt Disable */
#define FLEX_SPI_IDR_TXFFF (0x1u << 25) /**< \brief (FLEX_SPI_IDR) TXFFF Interrupt Disable */
#define FLEX_SPI_IDR_TXFTHF (0x1u << 26) /**< \brief (FLEX_SPI_IDR) TXFTHF Interrupt Disable */
#define FLEX_SPI_IDR_RXFEF (0x1u << 27) /**< \brief (FLEX_SPI_IDR) RXFEF Interrupt Disable */
#define FLEX_SPI_IDR_RXFFF (0x1u << 28) /**< \brief (FLEX_SPI_IDR) RXFFF Interrupt Disable */
#define FLEX_SPI_IDR_RXFTHF (0x1u << 29) /**< \brief (FLEX_SPI_IDR) RXFTHF Interrupt Disable */
#define FLEX_SPI_IDR_TXFPTEF (0x1u << 30) /**< \brief (FLEX_SPI_IDR) TXFPTEF Interrupt Disable */
#define FLEX_SPI_IDR_RXFPTEF (0x1u << 31) /**< \brief (FLEX_SPI_IDR) RXFPTEF Interrupt Disable */
/* -------- FLEX_SPI_IMR : (FLEXCOM Offset: 0x41C) SPI Interrupt Mask Register -------- */
#define FLEX_SPI_IMR_RDRF (0x1u << 0) /**< \brief (FLEX_SPI_IMR) Receive Data Register Full Interrupt Mask */
#define FLEX_SPI_IMR_TDRE (0x1u << 1) /**< \brief (FLEX_SPI_IMR) SPI Transmit Data Register Empty Interrupt Mask */
#define FLEX_SPI_IMR_MODF (0x1u << 2) /**< \brief (FLEX_SPI_IMR) Mode Fault Error Interrupt Mask */
#define FLEX_SPI_IMR_OVRES (0x1u << 3) /**< \brief (FLEX_SPI_IMR) Overrun Error Interrupt Mask */
#define FLEX_SPI_IMR_NSSR (0x1u << 8) /**< \brief (FLEX_SPI_IMR) NSS Rising Interrupt Mask */
#define FLEX_SPI_IMR_TXEMPTY (0x1u << 9) /**< \brief (FLEX_SPI_IMR) Transmission Registers Empty Mask */
#define FLEX_SPI_IMR_UNDES (0x1u << 10) /**< \brief (FLEX_SPI_IMR) Underrun Error Interrupt Mask */
#define FLEX_SPI_IMR_CMP (0x1u << 11) /**< \brief (FLEX_SPI_IMR) Comparison Interrupt Mask */
#define FLEX_SPI_IMR_TXFEF (0x1u << 24) /**< \brief (FLEX_SPI_IMR) TXFEF Interrupt Mask */
#define FLEX_SPI_IMR_TXFFF (0x1u << 25) /**< \brief (FLEX_SPI_IMR) TXFFF Interrupt Mask */
#define FLEX_SPI_IMR_TXFTHF (0x1u << 26) /**< \brief (FLEX_SPI_IMR) TXFTHF Interrupt Mask */
#define FLEX_SPI_IMR_RXFEF (0x1u << 27) /**< \brief (FLEX_SPI_IMR) RXFEF Interrupt Mask */
#define FLEX_SPI_IMR_RXFFF (0x1u << 28) /**< \brief (FLEX_SPI_IMR) RXFFF Interrupt Mask */
#define FLEX_SPI_IMR_RXFTHF (0x1u << 29) /**< \brief (FLEX_SPI_IMR) RXFTHF Interrupt Mask */
#define FLEX_SPI_IMR_TXFPTEF (0x1u << 30) /**< \brief (FLEX_SPI_IMR) TXFPTEF Interrupt Mask */
#define FLEX_SPI_IMR_RXFPTEF (0x1u << 31) /**< \brief (FLEX_SPI_IMR) RXFPTEF Interrupt Mask */
/* -------- FLEX_SPI_CSR[4] : (FLEXCOM Offset: 0x430) SPI Chip Select Register -------- */
#define FLEX_SPI_CSR_CPOL (0x1u << 0) /**< \brief (FLEX_SPI_CSR[4]) Clock Polarity */
#define FLEX_SPI_CSR_NCPHA (0x1u << 1) /**< \brief (FLEX_SPI_CSR[4]) Clock Phase */
#define FLEX_SPI_CSR_CSNAAT (0x1u << 2) /**< \brief (FLEX_SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
#define FLEX_SPI_CSR_CSAAT (0x1u << 3) /**< \brief (FLEX_SPI_CSR[4]) Chip Select Active After Transfer */
#define FLEX_SPI_CSR_BITS_Pos 4
#define FLEX_SPI_CSR_BITS_Msk (0xfu << FLEX_SPI_CSR_BITS_Pos) /**< \brief (FLEX_SPI_CSR[4]) Bits Per Transfer */
#define FLEX_SPI_CSR_BITS(value) ((FLEX_SPI_CSR_BITS_Msk & ((value) << FLEX_SPI_CSR_BITS_Pos)))
#define   FLEX_SPI_CSR_BITS_8_BIT (0x0u << 4) /**< \brief (FLEX_SPI_CSR[4]) 8 bits for transfer */
#define   FLEX_SPI_CSR_BITS_9_BIT (0x1u << 4) /**< \brief (FLEX_SPI_CSR[4]) 9 bits for transfer */
#define   FLEX_SPI_CSR_BITS_10_BIT (0x2u << 4) /**< \brief (FLEX_SPI_CSR[4]) 10 bits for transfer */
#define   FLEX_SPI_CSR_BITS_11_BIT (0x3u << 4) /**< \brief (FLEX_SPI_CSR[4]) 11 bits for transfer */
#define   FLEX_SPI_CSR_BITS_12_BIT (0x4u << 4) /**< \brief (FLEX_SPI_CSR[4]) 12 bits for transfer */
#define   FLEX_SPI_CSR_BITS_13_BIT (0x5u << 4) /**< \brief (FLEX_SPI_CSR[4]) 13 bits for transfer */
#define   FLEX_SPI_CSR_BITS_14_BIT (0x6u << 4) /**< \brief (FLEX_SPI_CSR[4]) 14 bits for transfer */
#define   FLEX_SPI_CSR_BITS_15_BIT (0x7u << 4) /**< \brief (FLEX_SPI_CSR[4]) 15 bits for transfer */
#define   FLEX_SPI_CSR_BITS_16_BIT (0x8u << 4) /**< \brief (FLEX_SPI_CSR[4]) 16 bits for transfer */
#define FLEX_SPI_CSR_SCBR_Pos 8
#define FLEX_SPI_CSR_SCBR_Msk (0xffu << FLEX_SPI_CSR_SCBR_Pos) /**< \brief (FLEX_SPI_CSR[4]) Serial Clock Bit Rate */
#define FLEX_SPI_CSR_SCBR(value) ((FLEX_SPI_CSR_SCBR_Msk & ((value) << FLEX_SPI_CSR_SCBR_Pos)))
#define FLEX_SPI_CSR_DLYBS_Pos 16
#define FLEX_SPI_CSR_DLYBS_Msk (0xffu << FLEX_SPI_CSR_DLYBS_Pos) /**< \brief (FLEX_SPI_CSR[4]) Delay Before SPCK */
#define FLEX_SPI_CSR_DLYBS(value) ((FLEX_SPI_CSR_DLYBS_Msk & ((value) << FLEX_SPI_CSR_DLYBS_Pos)))
#define FLEX_SPI_CSR_DLYBCT_Pos 24
#define FLEX_SPI_CSR_DLYBCT_Msk (0xffu << FLEX_SPI_CSR_DLYBCT_Pos) /**< \brief (FLEX_SPI_CSR[4]) Delay Between Consecutive Transfers */
#define FLEX_SPI_CSR_DLYBCT(value) ((FLEX_SPI_CSR_DLYBCT_Msk & ((value) << FLEX_SPI_CSR_DLYBCT_Pos)))
/* -------- FLEX_SPI_FMR : (FLEXCOM Offset: 0x440) SPI FIFO Mode Register -------- */
#define FLEX_SPI_FMR_TXRDYM_Pos 0
#define FLEX_SPI_FMR_TXRDYM_Msk (0x3u << FLEX_SPI_FMR_TXRDYM_Pos) /**< \brief (FLEX_SPI_FMR) Transmit Data Register Empty Mode */
#define FLEX_SPI_FMR_TXRDYM(value) ((FLEX_SPI_FMR_TXRDYM_Msk & ((value) << FLEX_SPI_FMR_TXRDYM_Pos)))
#define   FLEX_SPI_FMR_TXRDYM_ONE_DATA (0x0u << 0) /**< \brief (FLEX_SPI_FMR) TDRE will be at level '1' when at least one data can be written in the Transmit FIFO. */
#define   FLEX_SPI_FMR_TXRDYM_TWO_DATA (0x1u << 0) /**< \brief (FLEX_SPI_FMR) TDRE will be at level '1' when at least two data can be written in the Transmit FIFO. Cannot be used if FLEX_SPI_MR.PS =1. */
#define FLEX_SPI_FMR_RXRDYM_Pos 4
#define FLEX_SPI_FMR_RXRDYM_Msk (0x3u << FLEX_SPI_FMR_RXRDYM_Pos) /**< \brief (FLEX_SPI_FMR) Receive Data Register Full Mode */
#define FLEX_SPI_FMR_RXRDYM(value) ((FLEX_SPI_FMR_RXRDYM_Msk & ((value) << FLEX_SPI_FMR_RXRDYM_Pos)))
#define   FLEX_SPI_FMR_RXRDYM_ONE_DATA (0x0u << 4) /**< \brief (FLEX_SPI_FMR) RDRF will be at level '1' when at least one unread data is in the Receive FIFO. */
#define   FLEX_SPI_FMR_RXRDYM_TWO_DATA (0x1u << 4) /**< \brief (FLEX_SPI_FMR) RDRF will be at level '1' when at least two unread data are in the Receive FIFO. Cannot be used when FLEX_SPI_MR.MSTR =1, or if FLEX_SPI_MR.PS =1. */
#define   FLEX_SPI_FMR_RXRDYM_FOUR_DATA (0x2u << 4) /**< \brief (FLEX_SPI_FMR) RDRF will be at level '1' when at least four unread data are in the Receive FIFO. Cannot be used when FLEX_SPI_CSRx.BITS is greater than 0, or if FLEX_SPI_MR.MSTR =1, or if FLEX_SPI_MR.PS =1. */
#define FLEX_SPI_FMR_TXFTHRES_Pos 16
#define FLEX_SPI_FMR_TXFTHRES_Msk (0x3fu << FLEX_SPI_FMR_TXFTHRES_Pos) /**< \brief (FLEX_SPI_FMR) Transmit FIFO Threshold */
#define FLEX_SPI_FMR_TXFTHRES(value) ((FLEX_SPI_FMR_TXFTHRES_Msk & ((value) << FLEX_SPI_FMR_TXFTHRES_Pos)))
#define FLEX_SPI_FMR_RXFTHRES_Pos 24
#define FLEX_SPI_FMR_RXFTHRES_Msk (0x3fu << FLEX_SPI_FMR_RXFTHRES_Pos) /**< \brief (FLEX_SPI_FMR) Receive FIFO Threshold */
#define FLEX_SPI_FMR_RXFTHRES(value) ((FLEX_SPI_FMR_RXFTHRES_Msk & ((value) << FLEX_SPI_FMR_RXFTHRES_Pos)))
/* -------- FLEX_SPI_FLR : (FLEXCOM Offset: 0x444) SPI FIFO Level Register -------- */
#define FLEX_SPI_FLR_TXFL_Pos 0
#define FLEX_SPI_FLR_TXFL_Msk (0x3fu << FLEX_SPI_FLR_TXFL_Pos) /**< \brief (FLEX_SPI_FLR) Transmit FIFO Level */
#define FLEX_SPI_FLR_RXFL_Pos 16
#define FLEX_SPI_FLR_RXFL_Msk (0x3fu << FLEX_SPI_FLR_RXFL_Pos) /**< \brief (FLEX_SPI_FLR) Receive FIFO Level */
/* -------- FLEX_SPI_CMPR : (FLEXCOM Offset: 0x448) SPI Comparison Register -------- */
#define FLEX_SPI_CMPR_VAL1_Pos 0
#define FLEX_SPI_CMPR_VAL1_Msk (0xffffu << FLEX_SPI_CMPR_VAL1_Pos) /**< \brief (FLEX_SPI_CMPR) First Comparison Value for Received Character */
#define FLEX_SPI_CMPR_VAL1(value) ((FLEX_SPI_CMPR_VAL1_Msk & ((value) << FLEX_SPI_CMPR_VAL1_Pos)))
#define FLEX_SPI_CMPR_VAL2_Pos 16
#define FLEX_SPI_CMPR_VAL2_Msk (0xffffu << FLEX_SPI_CMPR_VAL2_Pos) /**< \brief (FLEX_SPI_CMPR) Second Comparison Value for Received Character */
#define FLEX_SPI_CMPR_VAL2(value) ((FLEX_SPI_CMPR_VAL2_Msk & ((value) << FLEX_SPI_CMPR_VAL2_Pos)))
/* -------- FLEX_SPI_WPMR : (FLEXCOM Offset: 0x4E4) SPI Write Protection Mode Register -------- */
#define FLEX_SPI_WPMR_WPEN (0x1u << 0) /**< \brief (FLEX_SPI_WPMR) Write Protection Enable */
#define FLEX_SPI_WPMR_WPITEN (0x1u << 1) /**< \brief (FLEX_SPI_WPMR) Write Protection Interrupt Enable */
#define FLEX_SPI_WPMR_WPCREN (0x1u << 2) /**< \brief (FLEX_SPI_WPMR) Write Protection Control Enable */
#define FLEX_SPI_WPMR_WPKEY_Pos 8
#define FLEX_SPI_WPMR_WPKEY_Msk (0xffffffu << FLEX_SPI_WPMR_WPKEY_Pos) /**< \brief (FLEX_SPI_WPMR) Write Protection Key */
#define FLEX_SPI_WPMR_WPKEY(value) ((FLEX_SPI_WPMR_WPKEY_Msk & ((value) << FLEX_SPI_WPMR_WPKEY_Pos)))
#define   FLEX_SPI_WPMR_WPKEY_PASSWD (0x535049u << 8) /**< \brief (FLEX_SPI_WPMR) Writing any other value in this field aborts the write operation of bits WPEN, WPITEN and WPCREN. Always reads as 0 */
/* -------- FLEX_SPI_WPSR : (FLEXCOM Offset: 0x4E8) SPI Write Protection Status Register -------- */
#define FLEX_SPI_WPSR_WPVS (0x1u << 0) /**< \brief (FLEX_SPI_WPSR) Write Protection Violation Status */
#define FLEX_SPI_WPSR_WPVSRC_Pos 8
#define FLEX_SPI_WPSR_WPVSRC_Msk (0xffu << FLEX_SPI_WPSR_WPVSRC_Pos) /**< \brief (FLEX_SPI_WPSR) Write Protection Violation Source */
/* -------- FLEX_TWI_CR : (FLEXCOM Offset: 0x600) TWI Control Register -------- */
#define FLEX_TWI_CR_START (0x1u << 0) /**< \brief (FLEX_TWI_CR) Send a START Condition */
#define FLEX_TWI_CR_STOP (0x1u << 1) /**< \brief (FLEX_TWI_CR) Send a STOP Condition */
#define FLEX_TWI_CR_MSEN (0x1u << 2) /**< \brief (FLEX_TWI_CR) TWI Master Mode Enabled */
#define FLEX_TWI_CR_MSDIS (0x1u << 3) /**< \brief (FLEX_TWI_CR) TWI Master Mode Disabled */
#define FLEX_TWI_CR_SVEN (0x1u << 4) /**< \brief (FLEX_TWI_CR) TWI Slave Mode Enabled */
#define FLEX_TWI_CR_SVDIS (0x1u << 5) /**< \brief (FLEX_TWI_CR) TWI Slave Mode Disabled */
#define FLEX_TWI_CR_QUICK (0x1u << 6) /**< \brief (FLEX_TWI_CR) SMBus Quick Command */
#define FLEX_TWI_CR_SWRST (0x1u << 7) /**< \brief (FLEX_TWI_CR) Software Reset */
#define FLEX_TWI_CR_HSEN (0x1u << 8) /**< \brief (FLEX_TWI_CR) TWI High-Speed Mode Enabled */
#define FLEX_TWI_CR_HSDIS (0x1u << 9) /**< \brief (FLEX_TWI_CR) TWI High-Speed Mode Disabled */
#define FLEX_TWI_CR_SMBEN (0x1u << 10) /**< \brief (FLEX_TWI_CR) SMBus Mode Enabled */
#define FLEX_TWI_CR_SMBDIS (0x1u << 11) /**< \brief (FLEX_TWI_CR) SMBus Mode Disabled */
#define FLEX_TWI_CR_PECEN (0x1u << 12) /**< \brief (FLEX_TWI_CR) Packet Error Checking Enable */
#define FLEX_TWI_CR_PECDIS (0x1u << 13) /**< \brief (FLEX_TWI_CR) Packet Error Checking Disable */
#define FLEX_TWI_CR_PECRQ (0x1u << 14) /**< \brief (FLEX_TWI_CR) PEC Request */
#define FLEX_TWI_CR_CLEAR (0x1u << 15) /**< \brief (FLEX_TWI_CR) Bus CLEAR Command */
#define FLEX_TWI_CR_ACMEN (0x1u << 16) /**< \brief (FLEX_TWI_CR) Alternative Command Mode Enable */
#define FLEX_TWI_CR_ACMDIS (0x1u << 17) /**< \brief (FLEX_TWI_CR) Alternative Command Mode Disable */
#define FLEX_TWI_CR_THRCLR (0x1u << 24) /**< \brief (FLEX_TWI_CR) Transmit Holding Register Clear */
#define FLEX_TWI_CR_LOCKCLR (0x1u << 26) /**< \brief (FLEX_TWI_CR) Lock Clear */
#define FLEX_TWI_CR_FIFOEN (0x1u << 28) /**< \brief (FLEX_TWI_CR) FIFO Enable */
#define FLEX_TWI_CR_FIFODIS (0x1u << 29) /**< \brief (FLEX_TWI_CR) FIFO Disable */
#define FLEX_TWI_CR_TXFCLR (0x1u << 24) /**< \brief (FLEX_TWI_CR) Transmit FIFO Clear */
#define FLEX_TWI_CR_RXFCLR (0x1u << 25) /**< \brief (FLEX_TWI_CR) Receive FIFO Clear */
#define FLEX_TWI_CR_TXFLCLR (0x1u << 26) /**< \brief (FLEX_TWI_CR) Transmit FIFO Lock CLEAR */
/* -------- FLEX_TWI_MMR : (FLEXCOM Offset: 0x604) TWI Master Mode Register -------- */
#define FLEX_TWI_MMR_IADRSZ_Pos 8
#define FLEX_TWI_MMR_IADRSZ_Msk (0x3u << FLEX_TWI_MMR_IADRSZ_Pos) /**< \brief (FLEX_TWI_MMR) Internal Device Address Size */
#define FLEX_TWI_MMR_IADRSZ(value) ((FLEX_TWI_MMR_IADRSZ_Msk & ((value) << FLEX_TWI_MMR_IADRSZ_Pos)))
#define   FLEX_TWI_MMR_IADRSZ_NONE (0x0u << 8) /**< \brief (FLEX_TWI_MMR) No internal device address */
#define   FLEX_TWI_MMR_IADRSZ_1_BYTE (0x1u << 8) /**< \brief (FLEX_TWI_MMR) One-byte internal device address */
#define   FLEX_TWI_MMR_IADRSZ_2_BYTE (0x2u << 8) /**< \brief (FLEX_TWI_MMR) Two-byte internal device address */
#define   FLEX_TWI_MMR_IADRSZ_3_BYTE (0x3u << 8) /**< \brief (FLEX_TWI_MMR) Three-byte internal device address */
#define FLEX_TWI_MMR_MREAD (0x1u << 12) /**< \brief (FLEX_TWI_MMR) Master Read Direction */
#define FLEX_TWI_MMR_DADR_Pos 16
#define FLEX_TWI_MMR_DADR_Msk (0x7fu << FLEX_TWI_MMR_DADR_Pos) /**< \brief (FLEX_TWI_MMR) Device Address */
#define FLEX_TWI_MMR_DADR(value) ((FLEX_TWI_MMR_DADR_Msk & ((value) << FLEX_TWI_MMR_DADR_Pos)))
#define FLEX_TWI_MMR_NOAP (0x1u << 24) /**< \brief (FLEX_TWI_MMR) No Auto-Stop On NACK Error */
/* -------- FLEX_TWI_SMR : (FLEXCOM Offset: 0x608) TWI Slave Mode Register -------- */
#define FLEX_TWI_SMR_NACKEN (0x1u << 0) /**< \brief (FLEX_TWI_SMR) Slave Receiver Data Phase NACK Enable */
#define FLEX_TWI_SMR_SMDA (0x1u << 2) /**< \brief (FLEX_TWI_SMR) SMBus Default Address */
#define FLEX_TWI_SMR_SMHH (0x1u << 3) /**< \brief (FLEX_TWI_SMR) SMBus Host Header */
#define FLEX_TWI_SMR_SADAT (0x1u << 4) /**< \brief (FLEX_TWI_SMR) Slave Address Treated as Data */
#define FLEX_TWI_SMR_BSEL (0x1u << 5) /**< \brief (FLEX_TWI_SMR) TWI Bus Selection */
#define FLEX_TWI_SMR_SCLWSDIS (0x1u << 6) /**< \brief (FLEX_TWI_SMR) Clock Wait State Disable */
#define FLEX_TWI_SMR_SNIFF (0x1u << 7) /**< \brief (FLEX_TWI_SMR) Slave Sniffer Mode */
#define FLEX_TWI_SMR_MASK_Pos 8
#define FLEX_TWI_SMR_MASK_Msk (0x7fu << FLEX_TWI_SMR_MASK_Pos) /**< \brief (FLEX_TWI_SMR) Slave Address Mask */
#define FLEX_TWI_SMR_MASK(value) ((FLEX_TWI_SMR_MASK_Msk & ((value) << FLEX_TWI_SMR_MASK_Pos)))
#define FLEX_TWI_SMR_SADR_Pos 16
#define FLEX_TWI_SMR_SADR_Msk (0x7fu << FLEX_TWI_SMR_SADR_Pos) /**< \brief (FLEX_TWI_SMR) Slave Address */
#define FLEX_TWI_SMR_SADR(value) ((FLEX_TWI_SMR_SADR_Msk & ((value) << FLEX_TWI_SMR_SADR_Pos)))
/* -------- FLEX_TWI_IADR : (FLEXCOM Offset: 0x60C) TWI Internal Address Register -------- */
#define FLEX_TWI_IADR_IADR_Pos 0
#define FLEX_TWI_IADR_IADR_Msk (0xffffffu << FLEX_TWI_IADR_IADR_Pos) /**< \brief (FLEX_TWI_IADR) Internal Address */
#define FLEX_TWI_IADR_IADR(value) ((FLEX_TWI_IADR_IADR_Msk & ((value) << FLEX_TWI_IADR_IADR_Pos)))
/* -------- FLEX_TWI_CWGR : (FLEXCOM Offset: 0x610) TWI Clock Waveform Generator Register -------- */
#define FLEX_TWI_CWGR_CLDIV_Pos 0
#define FLEX_TWI_CWGR_CLDIV_Msk (0xffu << FLEX_TWI_CWGR_CLDIV_Pos) /**< \brief (FLEX_TWI_CWGR) Clock Low Divider */
#define FLEX_TWI_CWGR_CLDIV(value) ((FLEX_TWI_CWGR_CLDIV_Msk & ((value) << FLEX_TWI_CWGR_CLDIV_Pos)))
#define FLEX_TWI_CWGR_CHDIV_Pos 8
#define FLEX_TWI_CWGR_CHDIV_Msk (0xffu << FLEX_TWI_CWGR_CHDIV_Pos) /**< \brief (FLEX_TWI_CWGR) Clock High Divider */
#define FLEX_TWI_CWGR_CHDIV(value) ((FLEX_TWI_CWGR_CHDIV_Msk & ((value) << FLEX_TWI_CWGR_CHDIV_Pos)))
#define FLEX_TWI_CWGR_CKDIV_Pos 16
#define FLEX_TWI_CWGR_CKDIV_Msk (0x7u << FLEX_TWI_CWGR_CKDIV_Pos) /**< \brief (FLEX_TWI_CWGR) Clock Divider */
#define FLEX_TWI_CWGR_CKDIV(value) ((FLEX_TWI_CWGR_CKDIV_Msk & ((value) << FLEX_TWI_CWGR_CKDIV_Pos)))
#define FLEX_TWI_CWGR_BRSRCCLK (0x1u << 20) /**< \brief (FLEX_TWI_CWGR) Bit Rate Source Clock */
#define   FLEX_TWI_CWGR_BRSRCCLK_PERIPH_CLK (0x0u << 20) /**< \brief (FLEX_TWI_CWGR) The peripheral clock is the source clock for the bit rate generation. */
#define   FLEX_TWI_CWGR_BRSRCCLK_GCLK (0x1u << 20) /**< \brief (FLEX_TWI_CWGR) GCLK is the source clock for the bit rate generation, thus the bit rate can be independent of the core/peripheral clock. */
#define FLEX_TWI_CWGR_HOLD_Pos 24
#define FLEX_TWI_CWGR_HOLD_Msk (0x3fu << FLEX_TWI_CWGR_HOLD_Pos) /**< \brief (FLEX_TWI_CWGR) TWD Hold Time Versus TWCK Falling */
#define FLEX_TWI_CWGR_HOLD(value) ((FLEX_TWI_CWGR_HOLD_Msk & ((value) << FLEX_TWI_CWGR_HOLD_Pos)))
/* -------- FLEX_TWI_SR : (FLEXCOM Offset: 0x620) TWI Status Register -------- */
#define FLEX_TWI_SR_TXCOMP (0x1u << 0) /**< \brief (FLEX_TWI_SR) Transmission Completed (cleared by writing FLEX_TWI_THR) */
#define FLEX_TWI_SR_RXRDY (0x1u << 1) /**< \brief (FLEX_TWI_SR) Receive Holding Register Ready (cleared when reading FLEX_TWI_RHR) */
#define FLEX_TWI_SR_TXRDY (0x1u << 2) /**< \brief (FLEX_TWI_SR) Transmit Holding Register Ready (cleared by writing FLEX_TWI_THR) */
#define FLEX_TWI_SR_SVREAD (0x1u << 3) /**< \brief (FLEX_TWI_SR) Slave Read */
#define FLEX_TWI_SR_SVACC (0x1u << 4) /**< \brief (FLEX_TWI_SR) Slave Access */
#define FLEX_TWI_SR_GACC (0x1u << 5) /**< \brief (FLEX_TWI_SR) General Call Access (cleared on read) */
#define FLEX_TWI_SR_OVRE (0x1u << 6) /**< \brief (FLEX_TWI_SR) Overrun Error (cleared on read) */
#define FLEX_TWI_SR_UNRE (0x1u << 7) /**< \brief (FLEX_TWI_SR) Underrun Error (cleared on read) */
#define FLEX_TWI_SR_NACK (0x1u << 8) /**< \brief (FLEX_TWI_SR) Not Acknowledged (cleared on read) */
#define FLEX_TWI_SR_ARBLST (0x1u << 9) /**< \brief (FLEX_TWI_SR) Arbitration Lost (cleared on read) */
#define FLEX_TWI_SR_SCLWS (0x1u << 10) /**< \brief (FLEX_TWI_SR) Clock Wait State */
#define FLEX_TWI_SR_EOSACC (0x1u << 11) /**< \brief (FLEX_TWI_SR) End Of Slave Access (cleared on read) */
#define FLEX_TWI_SR_MCACK (0x1u << 16) /**< \brief (FLEX_TWI_SR) Master Code Acknowledge (cleared on read) */
#define FLEX_TWI_SR_TOUT (0x1u << 18) /**< \brief (FLEX_TWI_SR) Timeout Error (cleared on read) */
#define FLEX_TWI_SR_PECERR (0x1u << 19) /**< \brief (FLEX_TWI_SR) PEC Error (cleared on read) */
#define FLEX_TWI_SR_SMBDAM (0x1u << 20) /**< \brief (FLEX_TWI_SR) SMBus Default Address Match (cleared on read) */
#define FLEX_TWI_SR_SMBHHM (0x1u << 21) /**< \brief (FLEX_TWI_SR) SMBus Host Header Address Match (cleared on read) */
#define FLEX_TWI_SR_LOCK (0x1u << 23) /**< \brief (FLEX_TWI_SR) TWI Lock Due to Frame Errors */
#define FLEX_TWI_SR_SCL (0x1u << 24) /**< \brief (FLEX_TWI_SR) SCL Line Value */
#define FLEX_TWI_SR_SDA (0x1u << 25) /**< \brief (FLEX_TWI_SR) SDA Line Value */
#define FLEX_TWI_SR_SR (0x1u << 26) /**< \brief (FLEX_TWI_SR) Start Repeated */
#define FLEX_TWI_SR_TXFLOCK (0x1u << 23) /**< \brief (FLEX_TWI_SR) Transmit FIFO Lock */
/* -------- FLEX_TWI_IER : (FLEXCOM Offset: 0x624) TWI Interrupt Enable Register -------- */
#define FLEX_TWI_IER_TXCOMP (0x1u << 0) /**< \brief (FLEX_TWI_IER) Transmission Completed Interrupt Enable */
#define FLEX_TWI_IER_RXRDY (0x1u << 1) /**< \brief (FLEX_TWI_IER) Receive Holding Register Ready Interrupt Enable */
#define FLEX_TWI_IER_TXRDY (0x1u << 2) /**< \brief (FLEX_TWI_IER) Transmit Holding Register Ready Interrupt Enable */
#define FLEX_TWI_IER_SVACC (0x1u << 4) /**< \brief (FLEX_TWI_IER) Slave Access Interrupt Enable */
#define FLEX_TWI_IER_GACC (0x1u << 5) /**< \brief (FLEX_TWI_IER) General Call Access Interrupt Enable */
#define FLEX_TWI_IER_OVRE (0x1u << 6) /**< \brief (FLEX_TWI_IER) Overrun Error Interrupt Enable */
#define FLEX_TWI_IER_UNRE (0x1u << 7) /**< \brief (FLEX_TWI_IER) Underrun Error Interrupt Enable */
#define FLEX_TWI_IER_NACK (0x1u << 8) /**< \brief (FLEX_TWI_IER) Not Acknowledge Interrupt Enable */
#define FLEX_TWI_IER_ARBLST (0x1u << 9) /**< \brief (FLEX_TWI_IER) Arbitration Lost Interrupt Enable */
#define FLEX_TWI_IER_SCL_WS (0x1u << 10) /**< \brief (FLEX_TWI_IER) Clock Wait State Interrupt Enable */
#define FLEX_TWI_IER_EOSACC (0x1u << 11) /**< \brief (FLEX_TWI_IER) End Of Slave Access Interrupt Enable */
#define FLEX_TWI_IER_ENDRX (0x1u << 12) /**< \brief (FLEX_TWI_IER) End of Receive Buffer Interrupt Enable */
#define FLEX_TWI_IER_ENDTX (0x1u << 13) /**< \brief (FLEX_TWI_IER) End of Transmit Buffer Interrupt Enable */
#define FLEX_TWI_IER_RXBUFF (0x1u << 14) /**< \brief (FLEX_TWI_IER) Receive Buffer Full Interrupt Enable */
#define FLEX_TWI_IER_TXBUFE (0x1u << 15) /**< \brief (FLEX_TWI_IER) Transmit Buffer Empty Interrupt Enable */
#define FLEX_TWI_IER_MCACK (0x1u << 16) /**< \brief (FLEX_TWI_IER) Master Code Acknowledge Interrupt Enable */
#define FLEX_TWI_IER_TOUT (0x1u << 18) /**< \brief (FLEX_TWI_IER) Timeout Error Interrupt Enable */
#define FLEX_TWI_IER_PECERR (0x1u << 19) /**< \brief (FLEX_TWI_IER) PEC Error Interrupt Enable */
#define FLEX_TWI_IER_SMBDAM (0x1u << 20) /**< \brief (FLEX_TWI_IER) SMBus Default Address Match Interrupt Enable */
#define FLEX_TWI_IER_SMBHHM (0x1u << 21) /**< \brief (FLEX_TWI_IER) SMBus Host Header Address Match Interrupt Enable */
/* -------- FLEX_TWI_IDR : (FLEXCOM Offset: 0x628) TWI Interrupt Disable Register -------- */
#define FLEX_TWI_IDR_TXCOMP (0x1u << 0) /**< \brief (FLEX_TWI_IDR) Transmission Completed Interrupt Disable */
#define FLEX_TWI_IDR_RXRDY (0x1u << 1) /**< \brief (FLEX_TWI_IDR) Receive Holding Register Ready Interrupt Disable */
#define FLEX_TWI_IDR_TXRDY (0x1u << 2) /**< \brief (FLEX_TWI_IDR) Transmit Holding Register Ready Interrupt Disable */
#define FLEX_TWI_IDR_SVACC (0x1u << 4) /**< \brief (FLEX_TWI_IDR) Slave Access Interrupt Disable */
#define FLEX_TWI_IDR_GACC (0x1u << 5) /**< \brief (FLEX_TWI_IDR) General Call Access Interrupt Disable */
#define FLEX_TWI_IDR_OVRE (0x1u << 6) /**< \brief (FLEX_TWI_IDR) Overrun Error Interrupt Disable */
#define FLEX_TWI_IDR_UNRE (0x1u << 7) /**< \brief (FLEX_TWI_IDR) Underrun Error Interrupt Disable */
#define FLEX_TWI_IDR_NACK (0x1u << 8) /**< \brief (FLEX_TWI_IDR) Not Acknowledge Interrupt Disable */
#define FLEX_TWI_IDR_ARBLST (0x1u << 9) /**< \brief (FLEX_TWI_IDR) Arbitration Lost Interrupt Disable */
#define FLEX_TWI_IDR_SCL_WS (0x1u << 10) /**< \brief (FLEX_TWI_IDR) Clock Wait State Interrupt Disable */
#define FLEX_TWI_IDR_EOSACC (0x1u << 11) /**< \brief (FLEX_TWI_IDR) End Of Slave Access Interrupt Disable */
#define FLEX_TWI_IDR_ENDRX (0x1u << 12) /**< \brief (FLEX_TWI_IDR) End of Receive Buffer Interrupt Disable */
#define FLEX_TWI_IDR_ENDTX (0x1u << 13) /**< \brief (FLEX_TWI_IDR) End of Transmit Buffer Interrupt Disable */
#define FLEX_TWI_IDR_RXBUFF (0x1u << 14) /**< \brief (FLEX_TWI_IDR) Receive Buffer Full Interrupt Disable */
#define FLEX_TWI_IDR_TXBUFE (0x1u << 15) /**< \brief (FLEX_TWI_IDR) Transmit Buffer Empty Interrupt Disable */
#define FLEX_TWI_IDR_MCACK (0x1u << 16) /**< \brief (FLEX_TWI_IDR) Master Code Acknowledge Interrupt Disable */
#define FLEX_TWI_IDR_TOUT (0x1u << 18) /**< \brief (FLEX_TWI_IDR) Timeout Error Interrupt Disable */
#define FLEX_TWI_IDR_PECERR (0x1u << 19) /**< \brief (FLEX_TWI_IDR) PEC Error Interrupt Disable */
#define FLEX_TWI_IDR_SMBDAM (0x1u << 20) /**< \brief (FLEX_TWI_IDR) SMBus Default Address Match Interrupt Disable */
#define FLEX_TWI_IDR_SMBHHM (0x1u << 21) /**< \brief (FLEX_TWI_IDR) SMBus Host Header Address Match Interrupt Disable */
/* -------- FLEX_TWI_IMR : (FLEXCOM Offset: 0x62C) TWI Interrupt Mask Register -------- */
#define FLEX_TWI_IMR_TXCOMP (0x1u << 0) /**< \brief (FLEX_TWI_IMR) Transmission Completed Interrupt Mask */
#define FLEX_TWI_IMR_RXRDY (0x1u << 1) /**< \brief (FLEX_TWI_IMR) Receive Holding Register Ready Interrupt Mask */
#define FLEX_TWI_IMR_TXRDY (0x1u << 2) /**< \brief (FLEX_TWI_IMR) Transmit Holding Register Ready Interrupt Mask */
#define FLEX_TWI_IMR_SVACC (0x1u << 4) /**< \brief (FLEX_TWI_IMR) Slave Access Interrupt Mask */
#define FLEX_TWI_IMR_GACC (0x1u << 5) /**< \brief (FLEX_TWI_IMR) General Call Access Interrupt Mask */
#define FLEX_TWI_IMR_OVRE (0x1u << 6) /**< \brief (FLEX_TWI_IMR) Overrun Error Interrupt Mask */
#define FLEX_TWI_IMR_UNRE (0x1u << 7) /**< \brief (FLEX_TWI_IMR) Underrun Error Interrupt Mask */
#define FLEX_TWI_IMR_NACK (0x1u << 8) /**< \brief (FLEX_TWI_IMR) Not Acknowledge Interrupt Mask */
#define FLEX_TWI_IMR_ARBLST (0x1u << 9) /**< \brief (FLEX_TWI_IMR) Arbitration Lost Interrupt Mask */
#define FLEX_TWI_IMR_SCL_WS (0x1u << 10) /**< \brief (FLEX_TWI_IMR) Clock Wait State Interrupt Mask */
#define FLEX_TWI_IMR_EOSACC (0x1u << 11) /**< \brief (FLEX_TWI_IMR) End Of Slave Access Interrupt Mask */
#define FLEX_TWI_IMR_ENDRX (0x1u << 12) /**< \brief (FLEX_TWI_IMR) End of Receive Buffer Interrupt Mask */
#define FLEX_TWI_IMR_ENDTX (0x1u << 13) /**< \brief (FLEX_TWI_IMR) End of Transmit Buffer Interrupt Mask */
#define FLEX_TWI_IMR_RXBUFF (0x1u << 14) /**< \brief (FLEX_TWI_IMR) Receive Buffer Full Interrupt Mask */
#define FLEX_TWI_IMR_TXBUFE (0x1u << 15) /**< \brief (FLEX_TWI_IMR) Transmit Buffer Empty Interrupt Mask */
#define FLEX_TWI_IMR_MCACK (0x1u << 16) /**< \brief (FLEX_TWI_IMR) Master Code Acknowledge Interrupt Mask */
#define FLEX_TWI_IMR_TOUT (0x1u << 18) /**< \brief (FLEX_TWI_IMR) Timeout Error Interrupt Mask */
#define FLEX_TWI_IMR_PECERR (0x1u << 19) /**< \brief (FLEX_TWI_IMR) PEC Error Interrupt Mask */
#define FLEX_TWI_IMR_SMBDAM (0x1u << 20) /**< \brief (FLEX_TWI_IMR) SMBus Default Address Match Interrupt Mask */
#define FLEX_TWI_IMR_SMBHHM (0x1u << 21) /**< \brief (FLEX_TWI_IMR) SMBus Host Header Address Match Interrupt Mask */
/* -------- FLEX_TWI_RHR : (FLEXCOM Offset: 0x630) TWI Receive Holding Register -------- */
#define FLEX_TWI_RHR_RXDATA_Pos 0
#define FLEX_TWI_RHR_RXDATA_Msk (0xffu << FLEX_TWI_RHR_RXDATA_Pos) /**< \brief (FLEX_TWI_RHR) Master or Slave Receive Holding Data */
#define FLEX_TWI_RHR_SSTATE_Pos 8
#define FLEX_TWI_RHR_SSTATE_Msk (0x3u << FLEX_TWI_RHR_SSTATE_Pos) /**< \brief (FLEX_TWI_RHR) Start State (Slave Sniffer Mode only) */
#define   FLEX_TWI_RHR_SSTATE_NOSTART (0x0u << 8) /**< \brief (FLEX_TWI_RHR) No START detected with the logged data */
#define   FLEX_TWI_RHR_SSTATE_START (0x1u << 8) /**< \brief (FLEX_TWI_RHR) START (S) detected with the logged data */
#define   FLEX_TWI_RHR_SSTATE_RSTART (0x2u << 8) /**< \brief (FLEX_TWI_RHR) Repeated START (Sr) detected with the logged data */
#define   FLEX_TWI_RHR_SSTATE_UNDEF (0x3u << 8) /**< \brief (FLEX_TWI_RHR) Not defined */
#define FLEX_TWI_RHR_PSTATE (0x1u << 10) /**< \brief (FLEX_TWI_RHR) Stop State (Slave Sniffer Mode only) */
#define FLEX_TWI_RHR_ASTATE_Pos 11
#define FLEX_TWI_RHR_ASTATE_Msk (0x3u << FLEX_TWI_RHR_ASTATE_Pos) /**< \brief (FLEX_TWI_RHR) Acknowledge State (Slave Sniffer Mode only) */
#define   FLEX_TWI_RHR_ASTATE_NONE (0x0u << 11) /**< \brief (FLEX_TWI_RHR) No Acknowledge or Nacknowledge detected after previously logged data */
#define   FLEX_TWI_RHR_ASTATE_ACK (0x1u << 11) /**< \brief (FLEX_TWI_RHR) Acknowledge (A) detected after previously logged data */
#define   FLEX_TWI_RHR_ASTATE_NACK (0x2u << 11) /**< \brief (FLEX_TWI_RHR) Nacknowledge (NA) detected after previously logged data */
#define   FLEX_TWI_RHR_ASTATE_UNDEF (0x3u << 11) /**< \brief (FLEX_TWI_RHR) Not defined */
#define FLEX_TWI_RHR_RXDATA0_Pos 0
#define FLEX_TWI_RHR_RXDATA0_Msk (0xffu << FLEX_TWI_RHR_RXDATA0_Pos) /**< \brief (FLEX_TWI_RHR) Master or Slave Receive Holding Data 0 */
#define FLEX_TWI_RHR_RXDATA1_Pos 8
#define FLEX_TWI_RHR_RXDATA1_Msk (0xffu << FLEX_TWI_RHR_RXDATA1_Pos) /**< \brief (FLEX_TWI_RHR) Master or Slave Receive Holding Data 1 */
#define FLEX_TWI_RHR_RXDATA2_Pos 16
#define FLEX_TWI_RHR_RXDATA2_Msk (0xffu << FLEX_TWI_RHR_RXDATA2_Pos) /**< \brief (FLEX_TWI_RHR) Master or Slave Receive Holding Data 2 */
#define FLEX_TWI_RHR_RXDATA3_Pos 24
#define FLEX_TWI_RHR_RXDATA3_Msk (0xffu << FLEX_TWI_RHR_RXDATA3_Pos) /**< \brief (FLEX_TWI_RHR) Master or Slave Receive Holding Data 3 */
/* -------- FLEX_TWI_THR : (FLEXCOM Offset: 0x634) TWI Transmit Holding Register -------- */
#define FLEX_TWI_THR_TXDATA_Pos 0
#define FLEX_TWI_THR_TXDATA_Msk (0xffu << FLEX_TWI_THR_TXDATA_Pos) /**< \brief (FLEX_TWI_THR) Master or Slave Transmit Holding Data */
#define FLEX_TWI_THR_TXDATA(value) ((FLEX_TWI_THR_TXDATA_Msk & ((value) << FLEX_TWI_THR_TXDATA_Pos)))
#define FLEX_TWI_THR_TXDATA0_Pos 0
#define FLEX_TWI_THR_TXDATA0_Msk (0xffu << FLEX_TWI_THR_TXDATA0_Pos) /**< \brief (FLEX_TWI_THR) Master or Slave Transmit Holding Data 0 */
#define FLEX_TWI_THR_TXDATA0(value) ((FLEX_TWI_THR_TXDATA0_Msk & ((value) << FLEX_TWI_THR_TXDATA0_Pos)))
#define FLEX_TWI_THR_TXDATA1_Pos 8
#define FLEX_TWI_THR_TXDATA1_Msk (0xffu << FLEX_TWI_THR_TXDATA1_Pos) /**< \brief (FLEX_TWI_THR) Master or Slave Transmit Holding Data 1 */
#define FLEX_TWI_THR_TXDATA1(value) ((FLEX_TWI_THR_TXDATA1_Msk & ((value) << FLEX_TWI_THR_TXDATA1_Pos)))
#define FLEX_TWI_THR_TXDATA2_Pos 16
#define FLEX_TWI_THR_TXDATA2_Msk (0xffu << FLEX_TWI_THR_TXDATA2_Pos) /**< \brief (FLEX_TWI_THR) Master or Slave Transmit Holding Data 2 */
#define FLEX_TWI_THR_TXDATA2(value) ((FLEX_TWI_THR_TXDATA2_Msk & ((value) << FLEX_TWI_THR_TXDATA2_Pos)))
#define FLEX_TWI_THR_TXDATA3_Pos 24
#define FLEX_TWI_THR_TXDATA3_Msk (0xffu << FLEX_TWI_THR_TXDATA3_Pos) /**< \brief (FLEX_TWI_THR) Master or Slave Transmit Holding Data 3 */
#define FLEX_TWI_THR_TXDATA3(value) ((FLEX_TWI_THR_TXDATA3_Msk & ((value) << FLEX_TWI_THR_TXDATA3_Pos)))
/* -------- FLEX_TWI_SMBTR : (FLEXCOM Offset: 0x638) TWI SMBus Timing Register -------- */
#define FLEX_TWI_SMBTR_PRESC_Pos 0
#define FLEX_TWI_SMBTR_PRESC_Msk (0xfu << FLEX_TWI_SMBTR_PRESC_Pos) /**< \brief (FLEX_TWI_SMBTR) SMBus Clock Prescaler */
#define FLEX_TWI_SMBTR_PRESC(value) ((FLEX_TWI_SMBTR_PRESC_Msk & ((value) << FLEX_TWI_SMBTR_PRESC_Pos)))
#define FLEX_TWI_SMBTR_TLOWS_Pos 8
#define FLEX_TWI_SMBTR_TLOWS_Msk (0xffu << FLEX_TWI_SMBTR_TLOWS_Pos) /**< \brief (FLEX_TWI_SMBTR) Slave Clock Stretch Maximum Cycles */
#define FLEX_TWI_SMBTR_TLOWS(value) ((FLEX_TWI_SMBTR_TLOWS_Msk & ((value) << FLEX_TWI_SMBTR_TLOWS_Pos)))
#define FLEX_TWI_SMBTR_TLOWM_Pos 16
#define FLEX_TWI_SMBTR_TLOWM_Msk (0xffu << FLEX_TWI_SMBTR_TLOWM_Pos) /**< \brief (FLEX_TWI_SMBTR) Master Clock Stretch Maximum Cycles */
#define FLEX_TWI_SMBTR_TLOWM(value) ((FLEX_TWI_SMBTR_TLOWM_Msk & ((value) << FLEX_TWI_SMBTR_TLOWM_Pos)))
#define FLEX_TWI_SMBTR_THMAX_Pos 24
#define FLEX_TWI_SMBTR_THMAX_Msk (0xffu << FLEX_TWI_SMBTR_THMAX_Pos) /**< \brief (FLEX_TWI_SMBTR) Clock High Maximum Cycles */
#define FLEX_TWI_SMBTR_THMAX(value) ((FLEX_TWI_SMBTR_THMAX_Msk & ((value) << FLEX_TWI_SMBTR_THMAX_Pos)))
/* -------- FLEX_TWI_ACR : (FLEXCOM Offset: 0x640) TWI Alternative Command Register -------- */
#define FLEX_TWI_ACR_DATAL_Pos 0
#define FLEX_TWI_ACR_DATAL_Msk (0xffu << FLEX_TWI_ACR_DATAL_Pos) /**< \brief (FLEX_TWI_ACR) Data Length */
#define FLEX_TWI_ACR_DATAL(value) ((FLEX_TWI_ACR_DATAL_Msk & ((value) << FLEX_TWI_ACR_DATAL_Pos)))
#define FLEX_TWI_ACR_DIR (0x1u << 8) /**< \brief (FLEX_TWI_ACR) Transfer Direction */
#define FLEX_TWI_ACR_PEC (0x1u << 9) /**< \brief (FLEX_TWI_ACR) PEC Request (SMBus Mode only) */
#define FLEX_TWI_ACR_NDATAL_Pos 16
#define FLEX_TWI_ACR_NDATAL_Msk (0xffu << FLEX_TWI_ACR_NDATAL_Pos) /**< \brief (FLEX_TWI_ACR) Next Data Length */
#define FLEX_TWI_ACR_NDATAL(value) ((FLEX_TWI_ACR_NDATAL_Msk & ((value) << FLEX_TWI_ACR_NDATAL_Pos)))
#define FLEX_TWI_ACR_NDIR (0x1u << 24) /**< \brief (FLEX_TWI_ACR) Next Transfer Direction */
#define FLEX_TWI_ACR_NPEC (0x1u << 25) /**< \brief (FLEX_TWI_ACR) Next PEC Request (SMBus Mode only) */
/* -------- FLEX_TWI_FILTR : (FLEXCOM Offset: 0x644) TWI Filter Register -------- */
#define FLEX_TWI_FILTR_FILT (0x1u << 0) /**< \brief (FLEX_TWI_FILTR) RX Digital Filter */
#define FLEX_TWI_FILTR_PADFEN (0x1u << 1) /**< \brief (FLEX_TWI_FILTR) PAD Filter Enable */
#define FLEX_TWI_FILTR_THRES_Pos 8
#define FLEX_TWI_FILTR_THRES_Msk (0x7u << FLEX_TWI_FILTR_THRES_Pos) /**< \brief (FLEX_TWI_FILTR) Digital Filter Threshold */
#define FLEX_TWI_FILTR_THRES(value) ((FLEX_TWI_FILTR_THRES_Msk & ((value) << FLEX_TWI_FILTR_THRES_Pos)))
/* -------- FLEX_TWI_FMR : (FLEXCOM Offset: 0x650) TWI FIFO Mode Register -------- */
#define FLEX_TWI_FMR_TXRDYM_Pos 0
#define FLEX_TWI_FMR_TXRDYM_Msk (0x3u << FLEX_TWI_FMR_TXRDYM_Pos) /**< \brief (FLEX_TWI_FMR) Transmitter Ready Mode */
#define FLEX_TWI_FMR_TXRDYM(value) ((FLEX_TWI_FMR_TXRDYM_Msk & ((value) << FLEX_TWI_FMR_TXRDYM_Pos)))
#define   FLEX_TWI_FMR_TXRDYM_ONE_DATA (0x0u << 0) /**< \brief (FLEX_TWI_FMR) TXRDY will be at level '1' when at least one data can be written in the Transmit FIFO */
#define   FLEX_TWI_FMR_TXRDYM_TWO_DATA (0x1u << 0) /**< \brief (FLEX_TWI_FMR) TXRDY will be at level '1' when at least two data can be written in the Transmit FIFO */
#define   FLEX_TWI_FMR_TXRDYM_FOUR_DATA (0x2u << 0) /**< \brief (FLEX_TWI_FMR) TXRDY will be at level '1' when at least four data can be written in the Transmit FIFO */
#define FLEX_TWI_FMR_RXRDYM_Pos 4
#define FLEX_TWI_FMR_RXRDYM_Msk (0x3u << FLEX_TWI_FMR_RXRDYM_Pos) /**< \brief (FLEX_TWI_FMR) Receiver Ready Mode */
#define FLEX_TWI_FMR_RXRDYM(value) ((FLEX_TWI_FMR_RXRDYM_Msk & ((value) << FLEX_TWI_FMR_RXRDYM_Pos)))
#define   FLEX_TWI_FMR_RXRDYM_ONE_DATA (0x0u << 4) /**< \brief (FLEX_TWI_FMR) RXRDY will be at level '1' when at least one unread data is in the Receive FIFO */
#define   FLEX_TWI_FMR_RXRDYM_TWO_DATA (0x1u << 4) /**< \brief (FLEX_TWI_FMR) RXRDY will be at level '1' when at least two unread data are in the Receive FIFO */
#define   FLEX_TWI_FMR_RXRDYM_FOUR_DATA (0x2u << 4) /**< \brief (FLEX_TWI_FMR) RXRDY will be at level '1' when at least four unread data are in the Receive FIFO */
#define FLEX_TWI_FMR_TXFTHRES_Pos 16
#define FLEX_TWI_FMR_TXFTHRES_Msk (0x3fu << FLEX_TWI_FMR_TXFTHRES_Pos) /**< \brief (FLEX_TWI_FMR) Transmit FIFO Threshold */
#define FLEX_TWI_FMR_TXFTHRES(value) ((FLEX_TWI_FMR_TXFTHRES_Msk & ((value) << FLEX_TWI_FMR_TXFTHRES_Pos)))
#define FLEX_TWI_FMR_RXFTHRES_Pos 24
#define FLEX_TWI_FMR_RXFTHRES_Msk (0x3fu << FLEX_TWI_FMR_RXFTHRES_Pos) /**< \brief (FLEX_TWI_FMR) Receive FIFO Threshold */
#define FLEX_TWI_FMR_RXFTHRES(value) ((FLEX_TWI_FMR_RXFTHRES_Msk & ((value) << FLEX_TWI_FMR_RXFTHRES_Pos)))
/* -------- FLEX_TWI_FLR : (FLEXCOM Offset: 0x654) TWI FIFO Level Register -------- */
#define FLEX_TWI_FLR_TXFL_Pos 0
#define FLEX_TWI_FLR_TXFL_Msk (0x3fu << FLEX_TWI_FLR_TXFL_Pos) /**< \brief (FLEX_TWI_FLR) Transmit FIFO Level */
#define FLEX_TWI_FLR_RXFL_Pos 16
#define FLEX_TWI_FLR_RXFL_Msk (0x3fu << FLEX_TWI_FLR_RXFL_Pos) /**< \brief (FLEX_TWI_FLR) Receive FIFO Level */
/* -------- FLEX_TWI_FSR : (FLEXCOM Offset: 0x660) TWI FIFO Status Register -------- */
#define FLEX_TWI_FSR_TXFEF (0x1u << 0) /**< \brief (FLEX_TWI_FSR) Transmit FIFO Empty Flag (cleared on read) */
#define FLEX_TWI_FSR_TXFFF (0x1u << 1) /**< \brief (FLEX_TWI_FSR) Transmit FIFO Full Flag (cleared on read) */
#define FLEX_TWI_FSR_TXFTHF (0x1u << 2) /**< \brief (FLEX_TWI_FSR) Transmit FIFO Threshold Flag (cleared on read) */
#define FLEX_TWI_FSR_RXFEF (0x1u << 3) /**< \brief (FLEX_TWI_FSR) Receive FIFO Empty Flag */
#define FLEX_TWI_FSR_RXFFF (0x1u << 4) /**< \brief (FLEX_TWI_FSR) Receive FIFO Full Flag */
#define FLEX_TWI_FSR_RXFTHF (0x1u << 5) /**< \brief (FLEX_TWI_FSR) Receive FIFO Threshold Flag */
#define FLEX_TWI_FSR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_TWI_FSR) Transmit FIFO Pointer Error Flag */
#define FLEX_TWI_FSR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_TWI_FSR) Receive FIFO Pointer Error Flag */
/* -------- FLEX_TWI_FIER : (FLEXCOM Offset: 0x664) TWI FIFO Interrupt Enable Register -------- */
#define FLEX_TWI_FIER_TXFEF (0x1u << 0) /**< \brief (FLEX_TWI_FIER) TXFEF Interrupt Enable */
#define FLEX_TWI_FIER_TXFFF (0x1u << 1) /**< \brief (FLEX_TWI_FIER) TXFFF Interrupt Enable */
#define FLEX_TWI_FIER_TXFTHF (0x1u << 2) /**< \brief (FLEX_TWI_FIER) TXFTHF Interrupt Enable */
#define FLEX_TWI_FIER_RXFEF (0x1u << 3) /**< \brief (FLEX_TWI_FIER) RXFEF Interrupt Enable */
#define FLEX_TWI_FIER_RXFFF (0x1u << 4) /**< \brief (FLEX_TWI_FIER) RXFFF Interrupt Enable */
#define FLEX_TWI_FIER_RXFTHF (0x1u << 5) /**< \brief (FLEX_TWI_FIER) RXFTHF Interrupt Enable */
#define FLEX_TWI_FIER_TXFPTEF (0x1u << 6) /**< \brief (FLEX_TWI_FIER) TXFPTEF Interrupt Enable */
#define FLEX_TWI_FIER_RXFPTEF (0x1u << 7) /**< \brief (FLEX_TWI_FIER) RXFPTEF Interrupt Enable */
/* -------- FLEX_TWI_FIDR : (FLEXCOM Offset: 0x668) TWI FIFO Interrupt Disable Register -------- */
#define FLEX_TWI_FIDR_TXFEF (0x1u << 0) /**< \brief (FLEX_TWI_FIDR) TXFEF Interrupt Disable */
#define FLEX_TWI_FIDR_TXFFF (0x1u << 1) /**< \brief (FLEX_TWI_FIDR) TXFFF Interrupt Disable */
#define FLEX_TWI_FIDR_TXFTHF (0x1u << 2) /**< \brief (FLEX_TWI_FIDR) TXFTHF Interrupt Disable */
#define FLEX_TWI_FIDR_RXFEF (0x1u << 3) /**< \brief (FLEX_TWI_FIDR) RXFEF Interrupt Disable */
#define FLEX_TWI_FIDR_RXFFF (0x1u << 4) /**< \brief (FLEX_TWI_FIDR) RXFFF Interrupt Disable */
#define FLEX_TWI_FIDR_RXFTHF (0x1u << 5) /**< \brief (FLEX_TWI_FIDR) RXFTHF Interrupt Disable */
#define FLEX_TWI_FIDR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_TWI_FIDR) TXFPTEF Interrupt Disable */
#define FLEX_TWI_FIDR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_TWI_FIDR) RXFPTEF Interrupt Disable */
/* -------- FLEX_TWI_FIMR : (FLEXCOM Offset: 0x66C) TWI FIFO Interrupt Mask Register -------- */
#define FLEX_TWI_FIMR_TXFEF (0x1u << 0) /**< \brief (FLEX_TWI_FIMR) TXFEF Interrupt Mask */
#define FLEX_TWI_FIMR_TXFFF (0x1u << 1) /**< \brief (FLEX_TWI_FIMR) TXFFF Interrupt Mask */
#define FLEX_TWI_FIMR_TXFTHF (0x1u << 2) /**< \brief (FLEX_TWI_FIMR) TXFTHF Interrupt Mask */
#define FLEX_TWI_FIMR_RXFEF (0x1u << 3) /**< \brief (FLEX_TWI_FIMR) RXFEF Interrupt Mask */
#define FLEX_TWI_FIMR_RXFFF (0x1u << 4) /**< \brief (FLEX_TWI_FIMR) RXFFF Interrupt Mask */
#define FLEX_TWI_FIMR_RXFTHF (0x1u << 5) /**< \brief (FLEX_TWI_FIMR) RXFTHF Interrupt Mask */
#define FLEX_TWI_FIMR_TXFPTEF (0x1u << 6) /**< \brief (FLEX_TWI_FIMR) TXFPTEF Interrupt Mask */
#define FLEX_TWI_FIMR_RXFPTEF (0x1u << 7) /**< \brief (FLEX_TWI_FIMR) RXFPTEF Interrupt Mask */
/* -------- FLEX_TWI_WPMR : (FLEXCOM Offset: 0x6E4) TWI Write Protection Mode Register -------- */
#define FLEX_TWI_WPMR_WPEN (0x1u << 0) /**< \brief (FLEX_TWI_WPMR) Write Protection Enable */
#define FLEX_TWI_WPMR_WPITEN (0x1u << 1) /**< \brief (FLEX_TWI_WPMR) Write Protection Interrupt Enable */
#define FLEX_TWI_WPMR_WPCREN (0x1u << 2) /**< \brief (FLEX_TWI_WPMR) Write Protection Control Enable */
#define FLEX_TWI_WPMR_WPKEY_Pos 8
#define FLEX_TWI_WPMR_WPKEY_Msk (0xffffffu << FLEX_TWI_WPMR_WPKEY_Pos) /**< \brief (FLEX_TWI_WPMR) Write Protection Key */
#define FLEX_TWI_WPMR_WPKEY(value) ((FLEX_TWI_WPMR_WPKEY_Msk & ((value) << FLEX_TWI_WPMR_WPKEY_Pos)))
#define   FLEX_TWI_WPMR_WPKEY_PASSWD (0x545749u << 8) /**< \brief (FLEX_TWI_WPMR) Writing any other value in this field aborts the write operation of bits WPEN, WPITEN and WPCREN. Always reads as 0 */
/* -------- FLEX_TWI_WPSR : (FLEXCOM Offset: 0x6E8) TWI Write Protection Status Register -------- */
#define FLEX_TWI_WPSR_WPVS (0x1u << 0) /**< \brief (FLEX_TWI_WPSR) Write Protect Violation Status */
#define FLEX_TWI_WPSR_WPVSRC_Pos 8
#define FLEX_TWI_WPSR_WPVSRC_Msk (0xffffffu << FLEX_TWI_WPSR_WPVSRC_Pos) /**< \brief (FLEX_TWI_WPSR) Write Protection Violation Source */

/*@}*/


#endif /* _SAM9X_FLEXCOM_COMPONENT_ */
