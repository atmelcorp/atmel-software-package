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
 * -# Configure the UART by calling usart_configure.
 * -# Enable the transmitter and/or the receiver of the USART using
 *    usart_set_transmitter_enabled and usart_set_receiver_enabled.
 * -# Send data through the USART using the usart_write methods.
 * -# Receive data from the USART using the usart_read functions; the availability of data can be polled
 *    with usart_is_data_available.
 * -# Disable the transmitter and/or the receiver of the USART with
 *    usart_set_transmitter_enabled and usart_set_receiver_enabled.
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

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern void usart_configure(Usart *usart, uint32_t mode, uint32_t baudrate, uint32_t masterClock);
extern uint32_t usart_get_status(Usart * usart);
extern void usart_enable_it(Usart *usart, uint32_t mode);
extern void usart_disable_it(Usart *usart, uint32_t mode);
extern uint32_t usart_get_it_mask(Usart *usart);
extern void usart_set_transmitter_enabled(Usart *usart, uint8_t enabled);
extern void usart_set_receiver_enabled(Usart *usart, uint8_t enabled);
extern void usart_set_rts_enabled(Usart *usart, uint8_t enabled);
extern void usart_write(Usart *usart, uint16_t data, volatile uint32_t timeOut);
extern uint16_t usart_read(Usart *usart, volatile uint32_t timeOut);
extern uint8_t usart_is_data_available(Usart *usart);
extern uint32_t usart_is_rx_ready(Usart *usart);
extern void usart_put_char(Usart *usart, uint8_t c);
extern uint8_t usart_get_char(Usart *usart);
extern void usart_set_irda_filter(Usart *usart, uint8_t filter);

#ifdef __cplusplus
}
#endif

#endif	/* #ifndef _USART_ */
