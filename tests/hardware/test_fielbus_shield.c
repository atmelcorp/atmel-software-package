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

#include "compiler.h"
#include "test_fielbus_shield.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

/* External push buttons connected on PA17 & PA18 */
#define PIN_EXT_PB1 { PIO_GROUP_B, PIO_PB24, PIO_INPUT, PIO_PULLUP | PIO_IT_FALL_EDGE }
#define PIN_EXT_PB2 { PIO_GROUP_B, PIO_PB25, PIO_INPUT, PIO_PULLUP | PIO_IT_FALL_EDGE }
#define EXT_PB1	0
#define EXT_PB2	1
static const struct _pin ext_pb_pins[] = {PIN_EXT_PB1, PIN_EXT_PB2};

/* Command relays using PA16 & PA19 */
#define PIN_EXT_RL1 { PIO_GROUP_D, PIO_PD23, PIO_OUTPUT_1, PIO_DEFAULT }
#define PIN_EXT_RL2 { PIO_GROUP_D, PIO_PD24, PIO_OUTPUT_1, PIO_DEFAULT }
#define EXT_REL1	0
#define EXT_REL2	1
static const struct _pin ext_rl1_pins[] = {PIN_EXT_RL1};
static const struct _pin ext_rl2_pins[] = {PIN_EXT_RL2};

/*
Fieldbus shield
COM0 (Rx, Tx) PD12/PD13 Flexcom4 Ios2
COM1 (Rx, Tx) PB22/PB23 Flexcom3 Ios3
*/

/** COM0 RS232 definition **/
#define PINS_COM0_USART         PINS_FLEXCOM4_USART_IOS2
#define COM0_PER_ADD            FLEXCOM4
#define COM0_ID                 ID_FLEXCOM4
#define COM0_BAUDRATE           115200
#define COM0_MODE_RS232         (US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM0 */
static const struct _pin pinsCom0[] = PINS_COM0_USART;

/** COM1 RS232 definition **/
#define PINS_COM1_USART         PINS_FLEXCOM3_USART_IOS3
#define COM1_PER_ADD            FLEXCOM3
#define COM1_ID                 ID_FLEXCOM3
#define COM1_BAUDRATE           115200
#define COM1_MODE_RS232         (US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

/** Pins for COM1 */
static const struct _pin pinsCom1[] = PINS_COM1_USART;


/** COM2 RS232 definition **/
#define PINS_COM2_USART         PINS_FLEXCOM0_USART_IOS1
#define COM2_PER_ADD            FLEXCOM0
#define COM2_ID                 ID_FLEXCOM0
#define COM2_BAUDRATE           115200
#define COM2_MODE_RS232         (US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)


#define PINS_COM2_RS485         PINS_FLEXCOM0_USART_IOS1_RS485
#define COM2_MODE_RS485         (US_MR_USART_MODE_RS485 | US_MR_USCLKS_MCK | \
				 				US_MR_CHMODE_NORMAL | US_MR_PAR_NO | \
				 				US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT)

/** Pins for COM2 */
static const struct _pin pinsCom2[] = PINS_COM2_USART;
static const struct _pin pinsCom20[] = PINS_COM2_RS485;

/** COM3 RS232 definition **/
#define PINS_COM3_USART         PINS_FLEXCOM1_USART_IOS1
#define COM3_PER_ADD            FLEXCOM1
#define COM3_ID                 ID_FLEXCOM1
#define COM3_BAUDRATE           115200
#define COM3_MODE_RS232         (US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT)

#define PINS_COM3_RS485         PINS_FLEXCOM1_USART_IOS1_RS485
#define COM3_MODE_RS485         (US_MR_USART_MODE_RS485 | US_MR_USCLKS_MCK | \
				 				US_MR_CHMODE_NORMAL | US_MR_PAR_NO | \
				 				US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT)

/** Pins for COM3 */
static const struct _pin pinsCom3[] = PINS_COM3_USART;
static const struct _pin pinsCom30[] = PINS_COM3_RS485;

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 */
static void external_pb1_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	(void)user_arg;
	if (status & ext_pb_pins[EXT_PB1].mask) {
		if( pio_get_output_data_status(&ext_rl1_pins[0]))
			pio_clear(&ext_rl1_pins[0]);
		else
			pio_set(&ext_rl1_pins[0]);
	}
}
static void external_pb2_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	(void)user_arg;
	if (status & ext_pb_pins[EXT_PB2].mask) {
		if( pio_get_output_data_status(&ext_rl2_pins[0]))
			pio_clear(&ext_rl2_pins[0]);
		else
			pio_set(&ext_rl2_pins[0]);
	}
}
static void configure_external_buttons(void)
{
	/* Configure pios as inputs. */
	pio_configure(&ext_pb_pins[EXT_PB1], 1);
	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(&ext_pb_pins[EXT_PB1], 10);
	/* Initialize pios ext_pb_pins with its handlers */
	pio_configure_it(&ext_pb_pins[EXT_PB1]);
	pio_add_handler_to_group(ext_pb_pins[EXT_PB1].group,
				 ext_pb_pins[EXT_PB1].mask,
				 external_pb1_handler,
				 NULL);
	pio_enable_it(&ext_pb_pins[EXT_PB1]);

	/* Configure pios as inputs. */
	pio_configure(&ext_pb_pins[EXT_PB2], 1);
	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(&ext_pb_pins[EXT_PB2], 10);
	/* Initialize pios ext_pb_pins with its handlers */
	pio_configure_it(&ext_pb_pins[EXT_PB2]);
	pio_add_handler_to_group(ext_pb_pins[EXT_PB2].group,
				 ext_pb_pins[EXT_PB2].mask,
				 external_pb2_handler,
				 NULL);
	pio_enable_it(&ext_pb_pins[EXT_PB2]);

}

static void configure_command_relays (void)
{
	pio_configure(&ext_rl1_pins[0], 1);
	pio_configure(&ext_rl2_pins[0], 1);
}

/* Init Com port
 * Mode FIFO ON
 *
 */

void com0_configure(const struct _pin * pin, uint32_t size, uint32_t mode)
{
	/* Configure Pios */
	pio_configure(pin, size);
	pmc_enable_peripheral(COM0_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM0_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM0_PER_ADD->usart, mode, COM0_BAUDRATE);
	usart_fifo_configure(&COM0_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);

	//usart_set_transmitter_enabled(&COM0_PER_ADD->usart, 1);
	//usart_set_receiver_enabled(&COM0_PER_ADD->usart, 1);
	//usart_enable_it(&COM0_PER_ADD->usart, UART_IER_RXRDY | UART_IER_TXRDY);
}

void com1_configure(const struct _pin* pin, uint32_t size, uint32_t mode)
{
	/* Configure Pios */
	pio_configure(pin, size);
	pmc_enable_peripheral(COM1_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM1_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM1_PER_ADD->usart, mode, COM1_BAUDRATE);
	usart_fifo_configure(&COM1_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}

void com2_configure(const struct _pin* pin, uint32_t size, uint32_t mode)
{
	/* Configure Pios */
	pio_configure(pin, size);
	pmc_enable_peripheral(COM2_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM2_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM2_PER_ADD->usart, mode, COM2_BAUDRATE);
	usart_fifo_configure(&COM2_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}

void com3_configure(const struct _pin* pin, uint32_t size, uint32_t mode)
{
	/* Configure Pios */
	pio_configure(pin, size);
	pmc_enable_peripheral(COM3_ID);
	/*Flexcom mode Usart */
	flexcom_select(COM3_PER_ADD, FLEX_MR_OPMODE_USART);
	/* Initialize driver to use */
	usart_configure (&COM3_PER_ADD->usart, mode, COM3_BAUDRATE);
	usart_fifo_configure(&COM3_PER_ADD->usart, 16, 16, 16, US_FMR_TXRDYM_ONE_DATA|US_FMR_RXRDYM_ONE_DATA);
}


void test_flexcom_usart(void)
{
	const char* str = "Test FieldBus Shield Atmel2015.";
	char str1[48] = {0};
	uint32_t len;

	configure_command_relays();
	configure_external_buttons();

	/* test RS232 mode */
	/* Loop com0 to Com1: TX0->RX1->TX1->RX0*/
	com0_configure(&pinsCom0[0], ARRAY_SIZE(pinsCom0), COM0_MODE_RS232);
	com1_configure(&pinsCom1[0], ARRAY_SIZE(pinsCom1), COM1_MODE_RS232);
	len = usart_write_stream(&COM0_PER_ADD->usart, str, strlen(str));
	len = usart_read_stream(&COM1_PER_ADD->usart, str1, len);
	len = usart_write_stream(&COM1_PER_ADD->usart, str1, len);
	len = usart_read_stream(&COM0_PER_ADD->usart, str1, len);
	printf("rx_len: %d str: %s \n\r", (uint32_t)len, str1);

	/* test RS232 mode */
	/* Loop com2 to Com3: TX com2/RX com3 */
	com2_configure(&pinsCom2[0], ARRAY_SIZE(pinsCom2), COM2_MODE_RS232);
	com3_configure(&pinsCom3[0], ARRAY_SIZE(pinsCom3), COM3_MODE_RS232);
	len = usart_write_stream(&COM2_PER_ADD->usart, str1, len);
	len = usart_read_stream(&COM3_PER_ADD->usart, str1, len);
	printf("rx_len: %d str: %s \n\r", (uint32_t)len, str1);

	/* test RS485 mode */
	/* Loop com2 to Com3 */
	com2_configure(&pinsCom20[0], ARRAY_SIZE(pinsCom20), COM2_MODE_RS485);
	com3_configure(&pinsCom30[0], ARRAY_SIZE(pinsCom30), COM3_MODE_RS485);
	len = usart_write_stream(&COM2_PER_ADD->usart, str, len);
	len = usart_read_stream(&COM3_PER_ADD->usart, str1, len);
	printf("rx_len: %d str: %s \n\r", (uint32_t)len, str1);
}
