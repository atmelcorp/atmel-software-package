/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
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

/**
* \file
*
* Implements CONSOLE.
*
*/

/*----------------------------------------------------------------------------
*        Headers
*----------------------------------------------------------------------------*/

#include "board.h"

#include "core/pio.h"
#include "core/pmc.h"

#include "bus/console.h"
#include "serial/uart.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
*        Definitions
*----------------------------------------------------------------------------*/

/** The Pheripheral has no HW ID */
#define ID_NOTUSED         0xFF

/*----------------------------------------------------------------------------
*        Types
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*        Variables
*----------------------------------------------------------------------------*/

/** Pins for CONSOLE */
static const pin_t pinsConsole[] = PINS_CONSOLE;

/** Console initialize status */
static uint8_t _bConsoleIsInitialized = 0;

/*------------------------------------------------------------------------------
*         Exported functions
*------------------------------------------------------------------------------*/

/**
* \brief Configures a CONSOLE peripheral with the specified parameters.
*
* \param baudrate  Baudrate at which the CONSOLE should operate (in Hz).
* \param masterClock  Frequency of the system master clock (in Hz).
*/
extern void console_configure(uint32_t baudrate, uint32_t masterclock)
{
	uint32_t mode;

	/* Configure PIO */
	pio_configure(pinsConsole, PIN_LISTSIZE(pinsConsole));
	/* Enable peripheral */
	pmc_enable_peripheral(CONSOLE_ID);
	/* Configure mode register */
	mode = UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO;
	uart_configure(CONSOLE_PER_ADD, mode, baudrate, masterclock);
	/* Enable Receiver and transmitter */
	uart_set_transmitter_enabled(CONSOLE_PER_ADD, 1);
	uart_set_receiver_enabled(CONSOLE_PER_ADD, 1);
	/* Finally */
	_bConsoleIsInitialized = 1;

#if defined(__GNUC__)
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
#endif
}

/**
* \brief Outputs a character on the CONSOLE line.
*
* \note This function is synchronous (i.e. uses polling).
* \param c  Character to send.
*/
extern void console_put_char(uint8_t c)
{
	if (!_bConsoleIsInitialized)
		return;
	uart_put_char(CONSOLE_PER_ADD, c, 0);
}

/**
* \brief Input a character from the CONSOLE line.
*
* \note This function is synchronous
* \return character received.
*/
extern uint32_t console_get_char(void)
{
	if (!_bConsoleIsInitialized)
		return 0;
	return uart_get_char(CONSOLE_PER_ADD);
}

/**
* \brief Check if there is Input from DBGU line.
*
* \return true if there is Input.
*/
extern uint32_t console_is_rx_ready(void)
{
	if (!_bConsoleIsInitialized)
		return 0;
	return uart_is_rx_ready(CONSOLE_PER_ADD);
}

/**
*  Displays the content of the given frame on the DBGU.
*
*  \param pucFrame Pointer to the frame to dump.
*  \param size   Buffer size in bytes.
*/
extern void console_dump_frame(uint8_t * pframe, uint32_t size)
{
	uint32_t dw;

	for (dw = 0; dw < size; dw++) {
		printf("%02X ", pframe[dw]);
	}
	printf("\n\r");
}

/**
*  Displays the content of the given buffer on the DBGU.
*
*  \param pbuffer  Pointer to the buffer to dump.
*  \param size     Buffer size in bytes.
*  \param address  Start address to display
*/
extern void console_dump_memory(uint8_t * pbuffer, uint32_t size,
				uint32_t address)
{
	uint32_t i, j;
	uint32_t last_line_start;
	uint8_t *tmp;

	for (i = 0; i < (size / 16); i++) {
		printf("0x%08X: ", (unsigned int)(address + (i * 16)));
		tmp = (uint8_t *) & pbuffer[i * 16];

		for (j = 0; j < 4; j++) {
			printf("%02X%02X%02X%02X ", tmp[0], tmp[1], tmp[2],
			       tmp[3]);
			tmp += 4;
		}
		tmp = (uint8_t *) & pbuffer[i * 16];

		for (j = 0; j < 16; j++) {
			console_put_char(*tmp++);
		}
		printf("\n\r");
	}

	if ((size % 16) != 0) {
		last_line_start = size - (size % 16);
		printf("0x%08X: ", (unsigned int)(address + last_line_start));
		for (j = last_line_start; j < last_line_start + 16; j++) {
			if ((j != last_line_start) && (j % 4 == 0)) {
				printf(" ");
			}
			if (j < size)
				printf("%02X", pbuffer[j]);
			else
				printf("  ");
		}
		printf(" ");
		for (j = last_line_start; j < size; j++) {
			console_put_char(pbuffer[j]);
		}
		printf("\n\r");
	}
}

/**
*  Reads an integer
*
*  \param pvalue  Pointer to the uint32_t variable to contain the input value.
*/
extern uint32_t console_get_integer(uint32_t * pvalue)
{
	uint8_t key;
	uint8_t nb = 0;
	uint32_t value = 0;

	while (1) {
		key = console_get_char();
		console_put_char(key);

		if (key >= '0' && key <= '9') {
			value = (value * 10) + (key - '0');
			nb++;
		} else {
			if (key == 0x0D || key == ' ') {
				if (nb == 0) {
					printf
					    ("\n\rWrite a number and press ENTER or SPACE!\n\r");
					return 0;
				} else {
					printf("\n\r");
					*pvalue = value;
					return 1;
				}
			} else {
				printf("\n\r'%c' not a number!\n\r", key);
				return 0;
			}
		}
	}
}

/**
*  Reads an integer and check the value
*
*  \param pvalue  Pointer to the uint32_t variable to contain the input value.
*  \param dwMin     Minimum value
*  \param dwMax     Maximum value
*/
extern uint32_t console_GetIntegerMinMax(uint32_t * pvalue, uint32_t min,
					 uint32_t max)
{
	uint32_t value = 0;

	if (console_GetInteger(&value) == 0)
		return 0;
	if (value < min || value > max) {
		printf("\n\rThe number have to be between %u and %u\n\r",
		       (unsigned int)min, (unsigned int)max);
		return 0;
	}
	printf("\n\r");
	*pvalue = value;
	return 1;
}

/**
*  Reads an hexadecimal number
*
*  \param pvalue  Pointer to the uint32_t variable to contain the input value.
*/
extern uint32_t console_GetHexa32(uint32_t * pvalue)
{
	uint8_t key;
	uint32_t dw = 0;
	uint32_t value = 0;

	for (dw = 0; dw < 8; dw++) {
		key = console_get_char();
		console_put_char(key);

		if (key >= '0' && key <= '9') {
			value = (value * 16) + (key - '0');
		} else {
			if (key >= 'A' && key <= 'F') {
				value = (value * 16) + (key - 'A' + 10);
			} else {
				if (key >= 'a' && key <= 'f') {
					value = (value * 16) + (key - 'a' + 10);
				} else {
					printf
					    ("\n\rIt is not a hexa character!\n\r");
					return 0;
				}
			}
		}
	}
	printf("\n\r");
	*pvalue = value;
	return 1;
}

//=============================================================================
// End Of File
