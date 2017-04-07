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
 *  \page usart_iso7816 USART ISO7816 Example
 *
 *  \section Purpose
 *  This example sends ISO 7816 commands to a smartcard connected to the
 *  Xplained board on samA5D4x.
 *
 *  \section Requirements
 *  This example can be used on SAMA5D2x Xplained board
 *  PB28 IO smartcard
 *  PB30 CLK smartcard
 *  ** with a Fieldbus shield.
 *  PB29 MODE_VCC
 *  PB31 STOP
 *  PC0  RST
 *  \section Description
 *  The iso7816 software provide in this examples is use to transform APDU
 *  commands to TPDU commands for the smart card.
 *  The iso7816 provide here is for the protocol T=0 only.
 *  The send and the receive of a character is made under polling.
 *  In the file ISO7816_Init is defined all pins of the card. User must have to
 *  change this pins according to his environment.
 *  The driver is compliant with CASE 1, 2, 3 of the ISO7816-4 specification.
 *
 *  \section Usage
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">SAM-BA User Guide</a>,
 *     the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">GNU-Based Software Development</a>
 *     application note or to the <a href="http://www.iar.com/website1/1.0.1.0/78/1/">IAR EWARM User and reference guides</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application (e.g.
 *     HyperTerminal on Microsoft Windows) with these settings:
 *        - 115200 bauds
 *        - 8 data bits
 *        - No parity
 *        - 1 stop bit
 *        - No flow control
 *  -# Connect the card reader to SAMA5D2 Xplained board:
 *        <table border="1" cellpadding="2" cellspacing="0">
 *        <tr><td> C1: Vcc:   7816_3V5V </td><td> C5: Gnd</td> <td> C4: RFU</td></tr>
 *        <tr><td> C2: Reset: 7816_RST</td> <td>  C6: Vpp</td> <td> C8: RFU</td></tr>
 *        <tr><td> C3: Clock: 7816_CLK</td> <td>  C7: 7816_IO</td> </tr>
 *        </table>
 *     The push button on board (BP1) is used to simulate the smartcard insertion or removal.
 *  -# Start the application. The following traces shall appear on the terminal:
 *     \code
 *      -- USART ISO7816 Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      Display the ATR
 *     \endcode
 *
 *   \section References
 *  - usart_iso7816/main.c
 *  - iso7816_4.c
 *  - pio.h
 *  - usart.h
 *
 */

/** \file
 *
 *  This file contains all the specific code for the usart_iso7816 example.
 *
 */


/*------------------------------------------------------------------------------
 *          Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "timer.h"

#include "peripherals/pmc.h"
#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "serial/usart_iso7816_4.h"

#include "led/led.h"
#include "serial/console.h"


#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Internal definitions
 *------------------------------------------------------------------------------*/

/** Delay for pushbutton debouncing (in milliseconds). */
#define DEBOUNCE_TIME       500

/** Num lock LED index. */
#define LED_NUMLOCK  0

/** Maximum uc_size in bytes of the smartcard answer to a uc_command. */
#define MAX_ANSWER_SIZE         10

/** Maximum ATR uc_size in bytes. */
#define MAX_ATR_SIZE            55

/** Define the baudrate of ISO7816 mode. */
#define ISO7816_BAUDRATE        9600

/** Define the FI_DI_RATIO filed value. */
#define ISO7816_FI_DI           372

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
#include "config_sama5d27-som1-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D3_EK)
#include "config_sama5d3-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
#include "config_sama5d3-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#include "config_sama5d4-xplained.h"
#elif defined(CONFIG_BOARD_SAM9G15_EK)
#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G25_EK)
#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G35_EK)
#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X25_EK)
#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X35_EK)
#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
#include "config_samv71-xplained.h"
#elif defined(CONFIG_BOARD_SAMU70_XPLAINED)
#include "config_samu70-xplained.h"
#elif defined(CONFIG_BOARD_SAMV72_XPLAINED)
#include "config_samv72-xplained.h"
#else
#error Unsupported board!
#endif

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

#ifdef PINS_PUSHBUTTONS
/** Pushbutton \#1 pin instance. */
static const struct _pin button_pins[] = PINS_PUSHBUTTONS;
#endif

/*------------------------------------------------------------------------------
 *         Internal variables ISO7816
 *------------------------------------------------------------------------------*/

/** Test command #1.*/
static const uint8_t testCommand1[] = {0x00, 0x10, 0x00, 0x00};
/** Test command #2.*/
static const uint8_t testCommand2[] = {0x00, 0x20, 0x00, 0x00, 0x02};
/** Test command #3.*/
static const uint8_t testCommand3[] = {0x00, 0x30, 0x00, 0x00, 0x02, 0x0A, 0x0B};

struct _iso7816_desc iso7816_desc = {
	.pin_stop = PIN_STOP_ISO7816,
	.pin_mod_vcc = PIN_MODE_VCC_ISO7816,
	.pin_rst = PIN_RST_ISO7816,

	.addr = USART_ADDR,
	.id = ID_USART,
};

struct _iso7816_opt iso7816_opt = {
	.protocol_type = US_MR_USART_MODE_IS07816_T_0,
	.clock_sel = US_MR_USCLKS_MCK,
	.char_length = US_MR_CHRL_8_BIT,
	.sync = 0,
	.parity_type = US_MR_PAR_EVEN,
	.num_stop_bits = US_MR_NBSTOP_2_BIT,
	.bit_order = 0,
	.inhibit_nack = 0,
	.dis_suc_nack = 0,

	.max_iterations = 3,
	.iso7816_hz = ISO7816_BAUDRATE * ISO7816_FI_DI,
	.fidi_ratio = ISO7816_FI_DI,
	.time_guard = 5,
};

static const struct _pin pins_com2[] = PIN_COM2_ISO7816;

uint8_t smartcard = 0;

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

#ifdef PINS_PUSHBUTTONS

/**
 *  \brief Process Buttons Events
 *
 */
static void process_button_evt(uint8_t bt)
{
	if ( smartcard == 0) {
		printf( "-I- Smartcard inserted\n\r" ) ;
	} else {
		printf( "-I- Smartcard removed\n\r" ) ;
	}
	smartcard = ~smartcard;
}


/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 */
static void push_button_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	int i = 0;
	(void)user_arg;
	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		if (status & button_pins[i].mask)
			process_button_evt(i);
	}
}

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void _configure_buttons(void)
{
	int i;

	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(10);

	for (i = 0; i <  ARRAY_SIZE(button_pins); ++i)
	{
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);
		/* Initialize pios interrupt with its handlers */
		pio_add_handler_to_group(button_pins[i].group,
					 button_pins[i].mask,
					 push_button_handler,
					 NULL);
		pio_enable_it(button_pins);
	}
}

#endif /* PINS_PUSHBUTTONS */

/*------------------------------------------------------------------------------
 *         Optional smartcard detection
 *------------------------------------------------------------------------------*/

/**
 * Displays a menu which enables the user to send several commands to the
 * smartcard and check its answers.
 */
static void _send_receive_commands( const struct _iso7816_desc* iso7816 )
{
	uint8_t pMessage[MAX_ANSWER_SIZE];
	uint8_t ucSize ;
	uint8_t ucKey ;
	uint8_t command;
	uint8_t i;

	/*  Clear message buffer */
	memset( pMessage, 0, sizeof( pMessage ) ) ;

	/*  Display menu */
	printf( "-I- Choose the command to send:\n\r" ) ;
	printf( "  1. " ) ;
	for ( i=0 ; i < sizeof( testCommand1 ) ; i++ ) {
		printf( "0x%X ", testCommand1[i] ) ;
	}
	printf( "\n\r  2. " ) ;
	for ( i=0 ; i < sizeof( testCommand2 ) ; i++ ) {
		printf( "0x%X ", testCommand2[i] ) ;
	}
	printf( "\n\r  3. " ) ;
	for ( i=0 ; i < sizeof( testCommand3 ) ; i++ ) {
		printf( "0x%X ", testCommand3[i] ) ;
	}
	printf( "\n\r" ) ;

	/*  Get user input */
	ucKey = 0 ;
	while ( ucKey != 'q' ) {
		printf( "\r                        " ) ;
		printf( "\rChoice ? (q to quit): " ) ;
		ucKey = console_get_char() ;
		printf( "%c", ucKey ) ;
		command = ucKey - '0';

		/*  Check user input */
		ucSize = 0 ;
		if ( command == 1 ) {
			printf( "\n\r-I- Sending command " ) ;
			for ( i=0 ; i < sizeof( testCommand1 ) ; i++ ) {
				printf( "0x%02X ", testCommand1[i] ) ;
			}
			printf( "...\n\r" ) ;
			ucSize = iso7816_xfr_block_TPDU_T0(iso7816, testCommand1, pMessage, sizeof( testCommand1 ) ) ;
		}
		else {
			if ( command == 2 ) {
				printf( "\n\r-I- Sending command " ) ;
				for ( i=0 ; i < sizeof( testCommand2 ) ; i++ ) {
					printf("0x%02X ", testCommand2[i] ) ;
				}
				printf( "...\n\r" ) ;
				ucSize = iso7816_xfr_block_TPDU_T0(iso7816, testCommand2, pMessage, sizeof( testCommand2 ) ) ;
			}
			else {
				if ( command == 3 ) {
					printf( "\n\r-I- Sending command " ) ;
					for ( i=0 ; i < sizeof( testCommand3 ) ; i++ ) {
						printf( "0x%02X ", testCommand3[i] ) ;
					}
					printf( "...\n\r" ) ;
					ucSize = iso7816_xfr_block_TPDU_T0(iso7816, testCommand3, pMessage, sizeof( testCommand3 ) ) ;
				}
			}
		}

		/*  Output smartcard answer */
		if ( ucSize > 0 ) {
			printf( "\n\rAnswer: " ) ;
			for ( i=0 ; i < ucSize ; i++ ) {
				printf( "0x%02X ", pMessage[i] ) ;
			}
			printf( "\n\r" ) ;
		}
	}
	printf( "Exit ...\n\r" ) ;
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the DBGU and ISO7816 driver, and starts some tests.
 * \return Unused (ANSI-C compatibility)
 */
extern int main( void )
{
	uint8_t Atr[MAX_ATR_SIZE] ;
	uint8_t size ;

	/* Output example information */
	console_example_info("USART ISO7816 Example");

	led_set(LED_NUMLOCK);
	msleep(500);
	led_clear(LED_NUMLOCK);

#ifdef PINS_PUSHBUTTONS
	/* PIO configuration for Button, use to simulate card detection. */
	printf("Configure buttons with debouncing.\n\r");
	_configure_buttons();
#endif

	/* Configure Pios usart*/
	pio_configure(&pins_com2[0], ARRAY_SIZE(pins_com2));

	/* Init ISO7816 interface */
	iso7816_init(&iso7816_desc, &iso7816_opt);

	/* Warm reset */
	iso7816_warm_reset(&iso7816_desc);
	/*  Read ATR */
	memset( Atr, 0, sizeof(Atr) ) ;
	iso7816_get_data_block_ATR(&iso7816_desc, Atr, &size );
	/*  Decode ATR */
	iso7816_decode_ATR(Atr);

	/*  Allow user to send some commands */
	_send_receive_commands(&iso7816_desc);

	printf("\n\r Exit App \n\r");
	while (1) ;
}
