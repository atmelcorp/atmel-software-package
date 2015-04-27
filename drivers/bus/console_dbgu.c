/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 * Implements DBGU console.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include "core/pio.h"
#include "core/pmc.h"

#include "bus/console.h"
#include <stdio.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

static const struct _pin dbg_pins[] = PINS_CONSOLE;
uint8_t _bConsoleIsInitialized = 0;

/** Usart Hw interface used by the console (USART0). */
#define CONSOLE_DBGU            ((Dbgu*)CONSOLE_PER_ADD)
/** Pins description list */
#define CONSOLE_PINLIST         (dbg_pins)
/** Pins description list size */
#define CONSOLE_PINLISTSIZE     (PIO_LISTSIZE(dbg_pins))

/**
 * \brief Configures an DBGU peripheral with the specified parameters.
 *
 * \param baudrate  Baudrate at which the DBGU should operate (in Hz).
 * \param masterClock  Frequency of the system master clock (in Hz).
 */
extern void
console_configure(uint32_t baudrate, uint32_t masterClock)
{

	/* Configure PIO */
	pio_configure(CONSOLE_PINLIST, CONSOLE_PINLISTSIZE);

	if (ID_PERIPH_COUNT != CONSOLE_ID) {
		//pmc_set_peri_max_clock(CONSOLE_ID, BOARD_MCK);
		pmc_enable_peripheral(CONSOLE_ID);
	}

	/* Configure mode register */
	if (CONSOLE_DBGU != DBGU) {
		CONSOLE_DBGU->DBGU_MR =
		    DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE | US_MR_CHRL_8_BIT;
	} else {
		CONSOLE_DBGU->DBGU_MR = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE;
	}
	/* Reset and disable receiver & transmitter */
	CONSOLE_DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX;
	CONSOLE_DBGU->DBGU_IDR = 0xFFFFFFFF;
	CONSOLE_DBGU->DBGU_CR = DBGU_CR_RXDIS | DBGU_CR_TXDIS;
	/* Configure baudrate */
	CONSOLE_DBGU->DBGU_BRGR = (masterClock / 2 / baudrate) / 16;
	/* Enable receiver and transmitter */
	CONSOLE_DBGU->DBGU_CR = DBGU_CR_RXEN | DBGU_CR_TXEN;
	_bConsoleIsInitialized = 1;
#if defined(__GNUC__)
	setvbuf(stdout, (char *) NULL, _IONBF, 0);
#endif
}

/**
 * \brief Outputs a character on the DBGU line.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 */
extern void
console_put_char(uint8_t c)
{
	if (!_bConsoleIsInitialized) {
		console_configure(CONSOLE_BAUDRATE, BOARD_MCK);
	}

	/* Wait for the transmitter to be ready */
	while ((CONSOLE_DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0) ;

	/* Send character */
	CONSOLE_DBGU->DBGU_THR = c;
}

/**
 * \brief Input a character from the DBGU line.
 *
 * \note This function is synchronous
 * \return character received.
 */
extern uint32_t
console_get_char(void)
{
	if (!_bConsoleIsInitialized) {
		console_configure(CONSOLE_BAUDRATE, BOARD_MCK);
	}

	while ((CONSOLE_DBGU->DBGU_SR & DBGU_SR_RXRDY) == 0) ;
	return CONSOLE_DBGU->DBGU_RHR;
}

/**
 * \brief Check if there is Input from DBGU line.
 *
 * \return true if there is Input.
 */
extern uint32_t
console_is_rx_ready(void)
{
	if (!_bConsoleIsInitialized) {
		//console_configure( CONSOLE_BAUDRATE, BOARD_MCK ) ;
	}
	return (CONSOLE_DBGU->DBGU_SR & DBGU_SR_RXRDY) > 0;
}

/**
 *  Displays the content of the given frame on the DBGU.
 *
 *  \param pucFrame Pointer to the frame to dump.
 *  \param dwSize   Buffer size in bytes.
 */
extern void
console_dump_frame(uint8_t * pucFrame, uint32_t dwSize)
{
	uint32_t dw;

	for (dw = 0; dw < dwSize; dw++) {
		printf("%02X ", pucFrame[dw]);
	}

	printf("\n\r");
}

/**
 *  Displays the content of the given buffer on the DBGU.
 *
 *  \param pucBuffer  Pointer to the buffer to dump.
 *  \param dwSize     Buffer size in bytes.
 *  \param dwAddress  Start address to display
 */
extern void
console_dump_memory(uint8_t * pucBuffer, uint32_t dwSize, uint32_t dwAddress)
{
	uint32_t i;
	uint32_t j;
	uint32_t dwLastLineStart;
	uint8_t *pucTmp;

	for (i = 0; i < (dwSize / 16); i++) {
		printf("0x%08X: ", (unsigned int) (dwAddress + (i * 16)));
		pucTmp = (uint8_t *) & pucBuffer[i * 16];

		for (j = 0; j < 4; j++) {
			printf("%02X%02X%02X%02X ", pucTmp[0], pucTmp[1],
			       pucTmp[2], pucTmp[3]);
			pucTmp += 4;
		}

		pucTmp = (uint8_t *) & pucBuffer[i * 16];

		for (j = 0; j < 16; j++) {
			console_put_char(*pucTmp++);
		}

		printf("\n\r");
	}

	if ((dwSize % 16) != 0) {
		dwLastLineStart = dwSize - (dwSize % 16);

		printf("0x%08X: ",
		       (unsigned int) (dwAddress + dwLastLineStart));
		for (j = dwLastLineStart; j < dwLastLineStart + 16; j++) {
			if ((j != dwLastLineStart) && (j % 4 == 0)) {
				printf(" ");
			}

			if (j < dwSize) {
				printf("%02X", pucBuffer[j]);
			} else {
				printf("  ");
			}
		}

		printf(" ");
		for (j = dwLastLineStart; j < dwSize; j++) {
			console_put_char(pucBuffer[j]);
		}

		printf("\n\r");
	}
}

/**
 *  Reads an integer
 *
 *  \param pdwValue  Pointer to the uint32_t variable to contain the input value.
 */
extern uint32_t
console_get_integer(uint32_t * pdwValue)
{
	uint8_t ucKey;
	uint8_t ucNbNb = 0;
	uint32_t dwValue = 0;

	while (1) {
		ucKey = console_get_char();
		console_put_char(ucKey);

		if (ucKey >= '0' && ucKey <= '9') {
			dwValue = (dwValue * 10) + (ucKey - '0');
			ucNbNb++;
		} else {
			if (ucKey == 0x0D || ucKey == ' ') {
				if (ucNbNb == 0) {
					printf
					    ("\n\rWrite a number and press ENTER or SPACE!\n\r");
					return 0;
				} else {
					printf("\n\r");
					*pdwValue = dwValue;

					return 1;
				}
			} else {
				printf("\n\r'%c' not a number!\n\r", ucKey);

				return 0;
			}
		}
	}
}

/**
 *  Reads an integer and check the value
 *
 *  \param pdwValue  Pointer to the uint32_t variable to contain the input value.
 *  \param dwMin     Minimum value
 *  \param dwMax     Maximum value
 */
extern uint32_t
console_get_integer_min_max(uint32_t * pdwValue, uint32_t dwMin, uint32_t dwMax)
{
	uint32_t dwValue = 0;

	if (console_get_integer(&dwValue) == 0) {
		return 0;
	}

	if (dwValue < dwMin || dwValue > dwMax) {
		printf("\n\rThe number have to be between %u and %u\n\r",
		       (unsigned int) dwMin, (unsigned int) dwMax);

		return 0;
	}

	printf("\n\r");

	*pdwValue = dwValue;

	return 1;
}

/**
 *  Reads an hexadecimal number
 *
 *  \param pdwValue  Pointer to the uint32_t variable to contain the input value.
 */
extern uint32_t
console_get_hexa_32(uint32_t * pdwValue)
{
	uint8_t ucKey;
	uint32_t dw = 0;
	uint32_t dwValue = 0;

	for (dw = 0; dw < 8; dw++) {
		ucKey = console_get_char();
		console_put_char(ucKey);

		if (ucKey >= '0' && ucKey <= '9') {
			dwValue = (dwValue * 16) + (ucKey - '0');
		} else {
			if (ucKey >= 'A' && ucKey <= 'F') {
				dwValue = (dwValue * 16) + (ucKey - 'A' + 10);
			} else {
				if (ucKey >= 'a' && ucKey <= 'f') {
					dwValue =
					    (dwValue * 16) + (ucKey - 'a' + 10);
				} else {
					printf
					    ("\n\rIt is not a hexa character!\n\r");

					return 0;
				}
			}
		}
	}

	printf("\n\r");
	*pdwValue = dwValue;

	return 1;
}

#if defined __ICCARM__		/* IAR Ewarm 5.41+ */
/**
 * \brief Outputs a character on the DBGU.
 *
 * \param c  Character to output.
 *
 * \return The character that was output.
 */
extern WEAK signed int
putchar(signed int c)
{
	console_put_char(c);

	return c;
}
#endif				// defined __ICCARM__
