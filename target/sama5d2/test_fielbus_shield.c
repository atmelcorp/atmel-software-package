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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/flexcom.h"
#include "peripherals/usart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------


/*
Fieldbus shield
COM0 (Rx, Tx) PD12/PD13 Flexcom4 Ios2
COM1 (Rx, Tx) PB22/PB23 Flexcom3 Ios3
*/

/** COM0 definition **/
#define PINS_COM0            	PINS_FLEXCOM4_USART_IOS2
#define COM0_PER_ADD         	FLEXCOM4
#define COM0_ID              	ID_FLEXCOM4
#define COM0_BAUDRATE        	115200
#define COM0_MODE				(US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM0 */
static const struct _pin pinsCom0[] = PINS_COM0;

/** COM1 definition **/
#define PINS_COM1            	PINS_FLEXCOM3_USART_IOS3
#define COM1_PER_ADD         	FLEXCOM3
#define COM1_ID              	ID_FLEXCOM3
#define COM1_BAUDRATE        	115200
#define COM1_MODE				(US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM1 */
static const struct _pin pinsCom1[] = PINS_COM1;


/** COM2 definition **/
#define PINS_COM2            	PINS_FLEXCOM0_USART_IOS1
#define COM2_PER_ADD         	FLEXCOM0
#define COM2_ID              	ID_FLEXCOM0
#define COM2_BAUDRATE        	115200
#define COM2_MODE				(US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM1 */
static const struct _pin pinsCom2[] = PINS_COM2;


/** COM2 definition **/
#define PINS_COM3            	PINS_FLEXCOM1_USART_IOS1
#define COM3_PER_ADD         	FLEXCOM1
#define COM3_ID              	ID_FLEXCOM1
#define COM3_BAUDRATE        	115200
#define COM3_MODE				(US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM1 */
static const struct _pin pinsCom3[] = PINS_COM3;

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

void com0_configure(void)
{
	/* Configure Pios */
	pio_configure(pinsCom0, ARRAY_SIZE(pinsCom0));
	pmc_enable_peripheral(COM0_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM0_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM0_PER_ADD->usart, COM0_MODE, COM0_BAUDRATE);

	usart_fifo_configure(&COM0_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);

	//usart_set_transmitter_enabled(&COM0_PER_ADD->usart, 1);
	//usart_set_receiver_enabled(&COM0_PER_ADD->usart, 1);
	//usart_enable_it(&COM0_PER_ADD->usart, UART_IER_RXRDY | UART_IER_TXRDY);
}

void com1_configure(void)
{
	/* Configure Pios */
	pio_configure(pinsCom1, ARRAY_SIZE(pinsCom1));
	pmc_enable_peripheral(COM1_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM1_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM1_PER_ADD->usart, COM1_MODE, COM1_BAUDRATE);

	usart_fifo_configure(&COM1_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}

void com2_configure(void)
{
	/* Configure Pios */
	pio_configure(pinsCom2, ARRAY_SIZE(pinsCom2));
	pmc_enable_peripheral(COM2_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM2_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM2_PER_ADD->usart, COM2_MODE, COM2_BAUDRATE);

	usart_fifo_configure(&COM2_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}

void com3_configure(void)
{
	/* Configure Pios */
	pio_configure(pinsCom3, ARRAY_SIZE(pinsCom3));
	pmc_enable_peripheral(COM3_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM3_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM3_PER_ADD->usart, COM3_MODE, COM3_BAUDRATE);

	usart_fifo_configure(&COM3_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}


void test_flexcom_usart (void)
{
	uint8_t str[] = "Test FieldBus Shield Atmel 2015";
	uint8_t str1[48] = {0};
	uint32_t len;

	com0_configure();
	com1_configure();
	com2_configure();
	com3_configure();
/*
	usart_put_char(&COM0_PER_ADD->usart, 'x');
	ch = usart_get_char(&COM1_PER_ADD->usart);
	usart_put_char(&COM1_PER_ADD->usart, ch);
	ch = 0;
	ch = usart_get_char(&COM0_PER_ADD->usart);
*/
	/* Loop com0 to Com1 */
	len = usart_write_stream(&COM0_PER_ADD->usart, str, sizeof(str));
	len = usart_read_stream(&COM1_PER_ADD->usart, str1, len);
	printf("rx_len: %d str: %s \n\r", len, str1);

	/* Loop com2 to Com3 */
	/* str tx len max 32 */
	len = usart_write_stream(&COM2_PER_ADD->usart, str1, len);
	len = usart_read_stream(&COM3_PER_ADD->usart, str1, len);
	printf("rx_len: %d str: %s \n\r", len, str1);
}

