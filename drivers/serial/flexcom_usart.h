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

#include <stdint.h>

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
#define FX_USART_MODE_ASYNCHRONOUS      (FX_US_MR_CHRL_8_BIT | FX_US_MR_PAR_NO)

/** IRDA mode*/
#define FX_USART_MODE_IRDA \
    (FX_US_MR_USART_MODE_IRDA | FX_US_MR_CHRL_8_BIT | FX_US_MR_PAR_NO | FX_US_MR_FILTER)

/** SPI mode*/
#define AT91C_US_USMODE_SPIM    0xE
#define US_SPI_CPOL_0           (0x0<<16)
#define US_SPI_CPHA_0           (0x0<<8)
#define US_SPI_CPOL_1           (0x1<<16)
#define US_SPI_CPHA_1           (0x1<<8)
#define US_SPI_BPMODE_0         (US_SPI_CPOL_0|US_SPI_CPHA_1)
#define US_SPI_BPMODE_1         (US_SPI_CPOL_0|US_SPI_CPHA_0)
#define US_SPI_BPMODE_2         (US_SPI_CPOL_1|US_SPI_CPHA_1)
#define US_SPI_BPMODE_3         (US_SPI_CPOL_1|US_SPI_CPHA_0)

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern void flexcom_usart_configure(Flexcom * pflexcom, uint32_t mode,
				    uint32_t baudrate,
				    uint32_t masterClock);
extern uint32_t flexcom_usart_get_status(Flexcom * pflexcom);
extern void flexcom_usart_enable_it(Flexcom * pflexcom, uint32_t mode);
extern void flexcom_usart_disable_it(Flexcom * pflexcom, uint32_t mode);
extern uint32_t flexcom_usart_get_it_mask(Flexcom * pflexcom);
extern void flexcom_usart_set_transmitter_enabled(Flexcom * pflexcom,
						  uint8_t enabled);
extern void flexcom_usart_set_receiver_enabled(Flexcom * pflexcom,
					       uint8_t enabled);
extern void flexcom_usart_set_rts_enabled(Flexcom * pflexcom,
					  uint8_t enabled);
extern void flexcom_usart_write(Flexcom * pflexcom, uint16_t data,
				volatile uint32_t timeOut);
extern uint16_t flexcom_usart_read(Flexcom * pflexcom,
				   volatile uint32_t timeOut);
extern uint8_t flexcom_usart_is_data_available(Flexcom * pflexcom);
extern void flexcom_usart_set_irda_filter(Flexcom * pflexcom,
					  uint8_t filter);
extern void flexcom_usart_put_char(Flexcom * pflexcom, uint8_t c);
extern uint32_t flexcom_usart_is_rx_ready(Flexcom * pflexcom);
extern uint8_t flexcom_usart_get_char(Flexcom * pflexcom);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _USART_ */
