/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

/**
 * \file
 *
 * \par Purpose
 *
 * This module provides several definitions and methods for using an USART
 * peripheral.
 *
 * \par Usage
 *
 * -# Enable the USART peripheral clock in the PMC.
 * -# Enable the required USART PIOs (see pio.h).
 * -# Configure the UART by calling USART_Configure.
 * -# Enable the transmitter and/or the receiver of the USART using
 *    USART_SetTransmitterEnabled and USART_SetReceiverEnabled.
 * -# Send data through the USART using the USART_Write methods.
 * -# Receive data from the USART using the USART_Read functions; the availability of data can be polled
 *    with USART_IsDataAvailable.
 * -# Disable the transmitter and/or the receiver of the USART with
 *    USART_SetTransmitterEnabled and USART_SetReceiverEnabled.
 */

#ifndef _USART_
#define _USART_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \section USART_mode USART modes
 * This section lists several common operating modes for an USART peripheral.
 *
 * \b Modes
 * - USART_MODE_ASYNCHRONOUS
 * - USART_MODE_IRDA
 */

/** Basic asynchronous mode, i.e. 8 bits no parity.*/
#define USART_MODE_ASYNCHRONOUS	(US_MR_CHRL_8_BIT | US_MR_PAR_NO)

/** IRDA mode*/
#define USART_MODE_IRDA \
    (US_MR_USART_MODE_IRDA | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_FILTER)

/** SPI mode*/
#define AT91C_US_USMODE_SPIM	0xE
#define US_SPI_CPOL_0			(0x0<<16)
#define US_SPI_CPHA_0			(0x0<<8)
#define US_SPI_CPOL_1			(0x1<<16)
#define US_SPI_CPHA_1			(0x1<<8)
#define US_SPI_BPMODE_0			(US_SPI_CPOL_0|US_SPI_CPHA_1)
#define US_SPI_BPMODE_1			(US_SPI_CPOL_0|US_SPI_CPHA_0)
#define US_SPI_BPMODE_2			(US_SPI_CPOL_1|US_SPI_CPHA_1)
#define US_SPI_BPMODE_3			(US_SPI_CPOL_1|US_SPI_CPHA_0)


#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \note Duplicate register Usart used for Flexcom usart mode */
/** \brief Usart hardware registers */
typedef struct {
  __O  uint32_t US_CR;         /**< \brief (Usart Offset: 0x0000) Control Register */
  __IO uint32_t US_MR;         /**< \brief (Usart Offset: 0x0004) Mode Register */
  __O  uint32_t US_IER;        /**< \brief (Usart Offset: 0x0008) Interrupt Enable Register */
  __O  uint32_t US_IDR;        /**< \brief (Usart Offset: 0x000C) Interrupt Disable Register */
  __I  uint32_t US_IMR;        /**< \brief (Usart Offset: 0x0010) Interrupt Mask Register */
  __I  uint32_t US_CSR;        /**< \brief (Usart Offset: 0x0014) Channel Status Register */
  __I  uint32_t US_RHR;        /**< \brief (Usart Offset: 0x0018) Receiver Holding Register */
  __O  uint32_t US_THR;        /**< \brief (Usart Offset: 0x001C) Transmitter Holding Register */
  __IO uint32_t US_BRGR;       /**< \brief (Usart Offset: 0x0020) Baud Rate Generator Register */
  __IO uint32_t US_RTOR;       /**< \brief (Usart Offset: 0x0024) Receiver Time-out Register */
  __IO uint32_t US_TTGR;       /**< \brief (Usart Offset: 0x0028) Transmitter Timeguard Register */
  __I  uint32_t Reserved1[5];
  __IO uint32_t US_FIDI;       /**< \brief (Usart Offset: 0x0040) FI DI Ratio Register */
  __I  uint32_t US_NER;        /**< \brief (Usart Offset: 0x0044) Number of Errors Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t US_IF;         /**< \brief (Usart Offset: 0x004C) IrDA Filter Register */
  __IO uint32_t US_MAN;        /**< \brief (Usart Offset: 0x0050) Manchester Encoder Decoder Register */
  __I  uint32_t Reserved3[36];
  __IO uint32_t US_WPMR;       /**< \brief (Usart Offset: 0x00E4) Write Protect Mode Register */
  __I  uint32_t US_WPSR;       /**< \brief (Usart Offset: 0x00E8) Write Protect Status Register */
} Usart;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern void usart_configure(Usart *pUsart, uint32_t mode, uint32_t baudrate, uint32_t masterClock);
extern uint32_t usart_get_status(Usart * pUsart);
extern void usart_enable_it(Usart *pUsart, uint32_t mode);
extern void usart_disable_it(Usart *pUsart, uint32_t mode);
extern uint32_t usart_get_it_mask(Usart *pUsart);
extern void usart_set_transmitter_enabled(Usart *pUsart, uint8_t enabled);
extern void usart_set_receiver_enabled(Usart *pUsart, uint8_t enabled);
extern void usart_set_rts_enabled(Usart *pUsart, uint8_t enabled);
extern void usart_write(Usart *pUsart, uint16_t data, volatile uint32_t timeOut);
extern uint16_t usart_read(Usart *pUsart, volatile uint32_t timeOut);
extern uint8_t usart_is_data_available(Usart *pUsart);
extern uint32_t usart_is_rx_ready(Usart *pUsart);
extern void usart_put_char(Usart *pUsart, uint8_t c);
extern uint8_t usart_get_char(Usart *pUsart);
extern void usart_set_irda_filter(Usart *pUsart, uint8_t filter);

#ifdef __cplusplus
}
#endif

#endif	/* #ifndef _USART_ */
