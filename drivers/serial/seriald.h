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

#ifndef _SERIAL_H_
#define _SERIAL_H_

/*-----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Global Types
 *----------------------------------------------------------------------------*/

/** Handler for character reception using interrupts */
typedef void (*seriald_rx_handler_t)(uint8_t received_char);

/** Forward declaration of internal structure */
struct _seriald_ops;

/** Serial driver */
struct _seriald {
	uint32_t id; /* peripheral identifier */
	void *addr; /* peripheral address */
	seriald_rx_handler_t rx_handler; /* rx callback */
	const struct _seriald_ops* ops; /* low-level operations */
};

/* ----------------------------------------------------------------------------
 *         Global function
 * ---------------------------------------------------------------------------*/

/**
 * \brief Configures a SERIAL peripheral with the specified parameters.
 *
 * \param addr      Peripheral address for the seriald (UARTx, USARTx, DBGU)
 * \param baudrate  Baudrate at which the SERIAL should operate (in Hz).
 */
extern int seriald_configure(struct _seriald* seriald, void *addr, uint32_t baudrate);

/**
 * \brief Outputs a character on the SERIAL.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 */
extern void seriald_put_char(const struct _seriald* seriald, uint8_t c);

/**
 * \brief Outputs a string on the SERIAL.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param str  String to send.
 */
extern void seriald_put_string(const struct _seriald* seriald, const uint8_t* str);

/**
 * \brief Check if any pending TX character has been sent
 */
extern bool seriald_is_tx_empty(const struct _seriald* seriald);

/**
 * \brief Input a character from the SERIAL line.
 *
 * \note This function is synchronous
 * \return character received.
 */
extern uint8_t seriald_get_char(const struct _seriald* seriald);

/**
 * \brief Check if there is Input from SERIAL line.
 *
 * \return true if there is Input.
 */
extern bool seriald_is_rx_ready(const struct _seriald* seriald);

/**
 * \brief Set the handler function that will be called upon reception of a
 * character on the SERIAL.
 *
 * \param handler the SERIAL RX handler
 */
extern void seriald_set_rx_handler(struct _seriald* seriald, seriald_rx_handler_t handler);

/**
 * \brief Enable the SERIAL RX interrupt. The configured RX handler will be
 * called on character reception.
 */
extern void seriald_enable_rx_interrupt(const struct _seriald* seriald);

/**
 * \brief Disable the SERIAL RX interrupt.
 */
extern void seriald_disable_rx_interrupt(const struct _seriald* seriald);

#endif	/* _SERIAL_H_ */
