/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
 */

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "chip.h"

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

/* 
 * Initializes the UART with the given parameters, and enables both the
 * transmitter and the receiver. The mode parameter contains the value of the
 * UART_MR register.
 * Value UART_STANDARD can be used for mode to get the most common configuration
 * (i.e. aysnchronous, 8bits, no parity, 1 stop bit, no flow control).
 * \param mode  Operating mode to configure.
 * \param baudrate  Desired baudrate (e.g. 115200).
 * \param mck  Frequency of the system master clock in Hz.
 */
void uart_configure(Uart* pUart, uint32_t mode, uint32_t baudrate, uint32_t mck)
{
    // Reset & disable receiver and transmitter, disable interrupts
    pUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;
    pUart->UART_IDR = 0xFFFFFFFF;
    // Configure baud rate
    pUart->UART_BRGR = mck / (baudrate * 16);
    // Configure mode register
    pUart->UART_MR = mode;
    // Enable receiver and transmitter
    pUart->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
}

/* Enable transmitter
 *
 */
void uart_set_transmitter_enabled (Uart* pUart, uint8_t enabled)
{
    if (enabled) pUart->UART_CR = UART_CR_TXEN;
    else pUart->UART_CR = UART_CR_TXDIS;
}

/* Enable receiver
 *
 */
void uart_set_receiver_enabled (Uart* pUart, uint8_t enabled)
{
  if (enabled) pUart->UART_CR = UART_CR_RXEN;
  else pUart->UART_CR = UART_CR_RXDIS;
}

/* Set interrupt register
 *
 */
void uart_set_int (Uart* pUart, uint32_t int_mask)
{
  pUart->UART_IER |= int_mask; 
}

/**
 * Outputs a character on the UART line.
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 * \param wait = 1 if wait transfer complete
 */
void uart_put_char(Uart* pUart, unsigned char c, uint8_t wait)
{
    // Wait for the transmitter to be ready
    while ((pUart->UART_SR & UART_SR_TXEMPTY) == 0);
    // Send character
    pUart->UART_THR = c;
    if (wait)
    {  
      // Wait for the transfer to complete
      while ((pUart->UART_SR & UART_SR_TXEMPTY) == 0);
    }  
}

/**
 * Return 1 if a character can be read in UART
 */
uint32_t uart_is_rx_ready(Uart* pUart)
{
    return (pUart->UART_SR & UART_SR_RXRDY);
}

/**
 * Return 1 if a character can be write in UART
 */
uint32_t uart_is_tx_ready(Uart* pUart)
{
    return (pUart->UART_SR & UART_SR_TXRDY);
}

/**
 * \brief Reads and returns a character from the UART.
 * \note This function is synchronous (i.e. uses polling).
 * \return Character received.
 */
uint8_t uart_get_char(Uart* pUart)
{    
    while ((pUart->UART_SR & UART_SR_RXRDY) == 0);
    return pUart->UART_RHR;
}




