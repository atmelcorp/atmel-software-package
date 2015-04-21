/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
 */

#ifndef UART_H
#define UART_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern void uart_configure(Uart* puart, uint32_t mode, uint32_t baudrate, uint32_t mck);
extern void uart_set_transmitter_enabled(Uart* puart, uint8_t enabled);
extern void uart_set_receiver_enabled (Uart* puart, uint8_t enabled);
extern void uart_set_int (Uart* puart, uint32_t int_mask);
extern void uart_put_char(Uart* puart, unsigned char c, uint8_t wait);
extern uint32_t uart_is_rx_ready(Uart* puart);
extern uint32_t uart_is_tx_ready(Uart* puart);
extern uint8_t uart_get_char(Uart* puart);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif //#ifndef UART_H

