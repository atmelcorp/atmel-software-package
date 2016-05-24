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

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/*-----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Global Types
 *----------------------------------------------------------------------------*/

/** Handler for character reception using interrupts */
typedef void (*console_rx_handler_t)(uint8_t received_char);

/* ----------------------------------------------------------------------------
 *         Global function
 * ---------------------------------------------------------------------------*/

/**
 * \brief Configures a CONSOLE peripheral with the specified parameters.
 *
 * \param addr      Peripheral address for the console (UARTx, USARTx, DBGU)
 * \param baudrate  Baudrate at which the CONSOLE should operate (in Hz).
 */
extern void console_configure(void *addr, uint32_t baudrate);

/**
 * \brief Outputs a character on the CONSOLE.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 */
extern void console_put_char(uint8_t uc);

/**
 * \brief Input a character from the CONSOLE line.
 *
 * \note This function is synchronous
 * \return character received.
 */
extern uint8_t console_get_char(void);

/**
 * \brief Check if there is Input from CONSOLE line.
 *
 * \return true if there is Input.
 */
extern bool console_is_rx_ready(void);

/**
 * \brief Set the handler function that will be called upon reception of a
 * character on the CONSOLE.
 *
 * \param handler the CONSOLE RX handler
 */
extern void console_set_rx_handler(console_rx_handler_t handler);

/**
 * \brief Enable the CONSOLE RX interrupt. The configured RX handler will be
 * called on character reception.
 */
extern void console_enable_rx_interrupt(void);

/**
 * \brief Disable the CONSOLE RX interrupt.
 */
extern void console_disable_rx_interrupt(void);

/**
 * \brief Displays the content of the given frame on the CONSOLE.
 *
 * \param frame  Pointer to the frame to dump.
 * \param size   Buffer size in bytes.
 */
extern void console_dump_frame(uint8_t *frame, uint32_t size);

/**
 * \brief Displays the content of the given buffer on the CONSOLE.
 *
 * \param buffer   Pointer to the buffer to dump.
 * \param size     Buffer size in bytes.
 * \param address  Start address to display
 */
extern void console_dump_memory(uint8_t *buffer, uint32_t size,
		uint32_t address);

/**
 * \brief Reads an integer
 *
 * \param value  Pointer to the variable to contain the input value.
 */
extern uint32_t console_get_integer(uint32_t *value);

/**
 * \brief Reads an integer and check the value
 *
 * \param value  Pointer to the variable to contain the input value.
 * \param min    Minimum value
 * \param max    Maximum value
 */
extern uint32_t console_get_integer_min_max(uint32_t *value,
		uint32_t min, uint32_t max);

/**
 * \brief Reads an hexadecimal number
 *
 * \param value Pointer to the variable to contain the input value.
 */
extern uint32_t console_get_hexa_32(uint32_t *value);

/**
 * \brief Echo the given character on the CONSOLE.
 * Several characters have a special processing:
 * - CR or LF are translated to "CR/LF" sequence
 * - ESC and BS are translated to a ANSI sequence that erases the previous
 * character and moves back one character.
 */
extern void console_echo(uint8_t c);

/**
 * \brief Send the ANSI "Clear Screen" sequence to the CONSOLE.
 */
extern void console_clear_screen(void);

/**
 * \brief Send the ANSI "Reset Cursor" sequence to the CONSOLE.
 */
extern void console_reset_cursor(void);

extern void console_example_info(const char *example_name);

#endif	/* _CONSOLE_H_ */
