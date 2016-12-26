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

#ifndef USART_H
#define USART_H

#ifdef CONFIG_HAVE_USART

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/* Returns 1 if the TXRDY bit (ready to transmit data) is set in the given status register value.*/
#define USART_STATUS_TXRDY(status) ((status & US_CSR_TXRDY) == US_CSR_TXRDY)

/* Returns 1 if the RXRDY bit (ready to receive data) is set in the given status register value.*/
#define USART_STATUS_RXRDY(status) ((status & US_CSR_RXRDY) == US_CSR_RXRDY)

/* Returns 1 if the TXEMPTY bit (end of transmit) is set in the given status register value.*/
#define USART_STATUS_TXEMPTY(status) ((status & US_CSR_TXEMPTY) == US_CSR_TXEMPTY)

/* Returns 1 if the TIMEOUT bit (timeout) is set in the given status register value.*/
#define USART_STATUS_TIMEOUT(status) ((status & US_CSR_TIMEOUT) == US_CSR_TIMEOUT)

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Reset status bits (PARE, OVER, MANERR, UNRE and PXBRK in US_CSR).
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_reset_status(Usart *usart);

/**
 * \brief Configures an USART peripheral with the specified parameters.
 *  \param usart  Pointer to the USART peripheral to configure.
 *  \param mode  Desired value for the USART mode register (see the datasheet).
 *  \param baudrate  Baudrate at which the USART should operate (in Hz).
 */
extern void usart_configure(Usart *usart, uint32_t mode, uint32_t baudrate);

/**
 * \brief   Get present status
 * \param usart  Pointer to an USART peripheral.
 */
extern uint32_t usart_get_status(Usart * usart);

/**
 * \brief   Get present status masked with current IRQs
 * \param usart  Pointer to an USART peripheral.
 */
extern uint32_t usart_get_masked_status(Usart *usart);

/**
 * \brief   Enable interrupt
 * \param usart  Pointer to an USART peripheral.
 * \param mode  Interrupt mode.
 */
extern void usart_enable_it(Usart *usart, uint32_t mode);

/**
 * \brief   Disable interrupt
 * \param usart  Pointer to an USART peripheral.
 * \param mode  Interrupt mode.
 */
extern void usart_disable_it(Usart *usart, uint32_t mode);

/**
 * \brief   Return interrupt mask
 * \param usart  Pointer to an USART peripheral.
 */
extern uint32_t usart_get_it_mask(Usart *usart);

/**
 * \brief Enables or disables the transmitter of an USART peripheral.
 * \param usart  Pointer to an USART peripheral
 * \param enabled  If true, the transmitter is enabled; otherwise it is
 *                disabled.
 */
extern void usart_set_transmitter_enabled(Usart *usart, uint8_t enabled);

/**
 * \brief Enables or disables the receiver of an USART peripheral
 * \param usart  Pointer to an USART peripheral
 * \param enabled  If true, the receiver is enabled; otherwise it is disabled.
 */
extern void usart_set_receiver_enabled(Usart *usart, uint8_t enabled);

/**
 * \brief Enables or disables the Request To Send (RTS) of an USART peripheral
 * \param usart  Pointer to an USART peripheral
 * \param enabled  If true, the RTS is enabled (0); otherwise it is disabled.
 */
extern void usart_set_rts_enabled(Usart *usart, uint8_t enabled);

/**
 * \brief Immediately stop and disable USART transmitter.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_reset_tx(Usart *usart);

/**
 * \brief Configure the transmit timeguard register.
 *
 * \param usart Pointer to a USART instance.
 * \param timeguard The value of transmit timeguard.
 */
extern void usart_set_tx_timeguard(Usart *usart, uint32_t timeguard);

/**
 * \brief Immediately stop and disable USART receiver.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_reset_rx(Usart *usart);

/**
 * \brief Configure the receive timeout register.
 *
 * \param usart Pointer to a USART instance.
 * \param baudrate The bitrate of the link
 * \param timeout The value of receive timeout.
 */
extern void usart_set_rx_timeout(Usart *usart, uint32_t baudrate, uint32_t timeout);

/**
 * \brief Start transmission of a break.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_start_tx_break(Usart *usart);

/**
 * \brief Stop transmission of a break.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_stop_tx_break(Usart *usart);

/**
 * \brief Start waiting for a character before clocking the timeout count.
 * Reset the status bit TIMEOUT in US_CSR.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_start_rx_timeout(Usart *usart);

/**
 * \brief Reset the ITERATION in US_CSR when the ISO7816 mode is enabled.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_reset_iterations(Usart *usart);

/**
 * \brief Reset NACK in US_CSR.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_reset_nack(Usart *usart);

/**
 * \brief Restart the receive timeout.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_restart_rx_timeout(Usart *usart);

/**
 * \brief Sends one packet of data through the specified USART peripheral. This
 * function operates synchronously, so it only returns when the data has been
 * actually sent.
 * \param usart  Pointer to an USART peripheral.
 * \param data  Data to send including 9nth bit and sync field if necessary (in
 *        the same format as the US_THR register in the datasheet).
 * \param timeout  Time out value (0 = no timeout).
 */
extern void usart_write(Usart *usart, uint16_t data, volatile uint32_t timeout);

/**
 * \brief  Reads and return a packet of data on the specified USART peripheral. This
 * function operates asynchronously, so it waits until some data has been
 * received.
 * \param usart  Pointer to an USART peripheral.
 * \param timeout  Time out value (0 -> no timeout).
 */
extern uint16_t usart_read(Usart *usart, volatile uint32_t timeout);

/**
 * \brief   Return 1 if a character can be read in USART
 * \param usart  Pointer to an USART peripheral.
 */
extern bool usart_is_rx_ready(Usart *usart);

/**
 * \brief   Return 1 if a character send in USART
 * \param usart  Pointer to an USART peripheral.
 */
extern bool usart_is_tx_ready(Usart *usart);

/**
 * \brief   Return 1 if any pending character has been sent
 * \param usart  Pointer to an USART peripheral.
 */
extern bool usart_is_tx_empty(Usart *usart);

/**
 * \brief  Sends one packet of data through the specified USART peripheral. This
 * function operates synchronously, so it only returns when the data has been
 * actually sent.
 * \param usart  Pointer to an USART peripheral.
 * \param c  Character to send
 */
extern void usart_put_char(Usart *usart, uint8_t c);

/**
 * \brief  Reads and returns a character from the USART.
 * \note This function is synchronous (i.e. uses polling).
 * \param usart  Pointer to an USART peripheral.
 * \return Character received.
 */
extern uint8_t usart_get_char(Usart *usart);

/**
 * \brief  Sets the filter value for the IRDA demodulator.
 * \param usart  Pointer to an USART instance.
 * \param filter  Filter value.
 */
extern void usart_set_irda_filter(Usart *usart, uint8_t filter);

/**
 * \brief Select the SCK pin as the source of baud rate for the USART
 * synchronous slave modes.
 *
 * \param usart Pointer to a USART instance.
 */
extern void usart_set_sync_slave_baudrate(Usart *usart);

/**
 * \brief Configure USART to work in hardware handshaking mode.
 *
 * \note By default, the transmitter and receiver aren't enabled.
 *
 * \param usart Pointer to a USART instance.
 *
 * \retval 0 on success.
 * \retval 1 on failure.
 */
extern uint32_t usart_init_hw_handshaking(Usart *usart);

/**
 * \brief Calculate a clock divider(CD) and a fractional part (FP) for the
 * USART asynchronous modes to generate a baudrate as close as possible to
 * the baudrate set point.
 *
 * \note Baud rate calculation: Baudrate = mck/(Over * (CD + FP/8))
 * (Over being 16 or 8). The maximal oversampling is selected if it allows to
 * generate a baudrate close to the set point.
 *
 * \param usart Pointer to a USART instance.
 * \param baudrate Baud rate set point.
 *
 * \retval 0 Baud rate is successfully initialized.
 * \retval 1 Baud rate set point is out of range for the given input clock
 * frequency.
 */
extern uint32_t usart_set_async_baudrate(Usart *usart, uint32_t baudrate);

#ifdef CONFIG_HAVE_USART_FIFO
/**
 * \brief Configure the FIFO of USART device
 *
 * \param usart Pointer to an USART instance.
 * \param tx_thres
 * \param rx_down_thres
 * \param rx_up_thres
 * \param ready_modes
 */
	extern void usart_fifo_configure(Usart *usart, uint8_t tx_thres,
									 uint8_t rx_down_thres, uint8_t rx_up_thres);
/**
 * \brief Enable the FIFO mode for the USART device
 *
 * \param usart Pointer to an USART instance.
 * \note receiver and transmitter are reenabled.
 */
extern void usart_fifo_enable(Usart *usart);

/**
 * \brief Disable the FIFO mode from the USART device
 *
 * \param usart Pointer to an USART instance.
 * \note receiver and transmitter are reenabled.
 */
extern void usart_fifo_disable(Usart *usart);

/**
 * \brief Enable FIFO related interrupts according to the given mask
 *
 * \param usart Pointer to an USART instance.
 * \param interrupt_mask The mask to apply
 */
extern void usart_fifo_enable_it(Usart *usart, uint32_t interrupt_mask);

/**
 * \brief Disable FIFO related interrupts according to the given mask
 *
 * \param usart Pointer to an USART instance.
 * \param interrupt_mask The mask to apply
 */
extern void usart_fifo_disable_it(Usart *usart, uint32_t interrupt_mask);

/**
 * \brief Get the size occupied in the input FIFO of USART device.
 *
 * \param usart Pointer to an USART instance.
 * \return Size occupied in the input FIFO (not read yet) in octet
 */
extern uint32_t usart_fifo_get_rx_size(Usart *usart);

/**
 * \brief Get the size occupied in the ouput FIFO of USART device.
 *
 * \param usart Pointer to an USART instance.
 * \return Size occupied in the output FIFO (not sent yet) in octet
 */
extern uint32_t usart_fifo_get_tx_size(Usart *usart);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_USART */

#endif /* USART_H */
