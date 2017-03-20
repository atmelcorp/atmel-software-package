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
 * \page lin Network.
 * An example using the LIN peripheral of SAMA5D2x Microcontrollers.
 * Using a FIELBUS-SHIELD board
 * \section Purpose
 *
 * The LIN example will help new users get familiar
 * with the FLEXCOM-USART used in Atmel's SAMA5D2x microcontrollers.
 *
 * \section Requirements
 *
 * This package is compatible with the evaluation boards listed below:
 * - SAMA5D2-VB
 * - SAMA5D2-XULT
 *
 * \section Description
 *
 * The demonstration program use different mode if the LIN protocol.
 *
 *
 *
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- LIN Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     LIN menu:
 *     Press P to run master node PUBLISH and slave node SUBSCRIBE
 *     Press S to run master node SUBSCRIBE and slave node PUBLISH
 *     Press I to set master and slave node IGNORE
 * -# Input command according to the menu.
 *
 * \section References
 * - usart_lin/main.c
 * - lin.c
 * - lin.h
 */

/** \file
 *
 *  This file contains all the specific code for the LIN example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chip.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "led/led.h"
#include "lin.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tcd.h"
#include "serial/console.h"
#include "serial/usart.h"
#include "timer.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** COM2 definition **/
#define COM2_USART_PINS         PINS_FLEXCOM0_USART_IOS1
#define COM2_USART_ENA_PIN      { PIO_GROUP_C, PIO_PC0C_FLEXCOM0_IO4, PIO_OUTPUT_1, PIO_DEFAULT }
#define COM2_USART_ADDR         FLEXUSART0
#define COM2_USART_BAUDRATE     9600
#define COM2_USART_MODE         (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_MASTER)

/** COM3 definition **/
#define COM3_USART_PINS         PINS_FLEXCOM1_USART_IOS1
#define COM3_USART_ENA_PIN      { PIO_GROUP_A, PIO_PA26A_FLEXCOM1_IO4, PIO_OUTPUT_1, PIO_DEFAULT }
#define COM3_USART_ADDR         FLEXUSART1
#define COM3_USART_BAUDRATE     9600
#define COM3_USART_MODE         (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_SLAVE)

/** LIN frame number */
#define LIN_FRAME_ID_12       0x12
#define LIN_FRAME_ID_15       0x15

/** LIN master node number */
#define LIN_MASTER_NODE_NUM   0

/** LIN slave node number */
#define LIN_SLAVE_NODE_NUM    1

/** Timer counter used */
#define TC_ADDR               TC0

/** Timer counter channel used */
#define TC_CHANNEL            0

/** Timer counter frequency in Hz */
#define TC_FREQ               10

/** LED0 wait count */
#define LIN_LED0_WAIT_COUNTER 10

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _tcd_desc _tc = {
	.addr = TC_ADDR,
	.channel = TC_CHANNEL,
};

static const struct _pin pins_com2[] = COM2_USART_PINS;

static struct _lin_desc lin_desc2 = {
	.pin_enable = COM2_USART_ENA_PIN,
	.addr = COM2_USART_ADDR,
	.mode = COM2_USART_MODE,
	.baudrate = COM2_USART_BAUDRATE
};

static const struct _pin pins_com3[] = COM3_USART_PINS;

static struct _lin_desc lin_desc3 = {
	.pin_enable = COM3_USART_ENA_PIN,
	.addr = COM3_USART_ADDR,
	.mode = COM3_USART_MODE,
	.baudrate = COM3_USART_BAUDRATE
};

static uint8_t lin_data_master[8];

static struct _lin_message lin_msg_master = {
	.id = 0,
	.dlc = 0,
	.lin_cmd = IGNORE,
	.status = 0,
	.pdata = &lin_data_master[0],
	.pfnct = NULL,
};

static uint8_t lin_data_slave[8];

static struct _lin_message lin_msg_slave = {
	.id = 0,
	.dlc = sizeof(lin_data_slave),
	.lin_cmd = IGNORE,
	.status = 0,
	.pdata = &lin_data_slave[0],
	.pfnct = NULL,
};

static uint32_t lin_led_red_counter = 0;

static volatile uint8_t key;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/


/**
 * \brief lin_slave_task_ID12
 */
static void  lin_slave_task_ID12(uint8_t *buf)
{
	if (buf[0] == 0x55) {
		lin_led_red_counter++;
		if (lin_led_red_counter == LIN_LED0_WAIT_COUNTER) {
			led_toggle(LED_RED);
			lin_led_red_counter = 0;
		}
	}
	led_toggle(LED_GREEN);
}

/**
 * \brief Button event.
 */
static void _process_button_evt(void)
{
	uint32_t id = get_usart_id_from_addr(lin_desc2.addr);

	switch (key) {
	case 'P':
	case 'p':
		/* No interrupt on Master */
		irq_disable(id);
		/* Configure lin_descriptor MASTER */
		lin_msg_master.id = LIN_FRAME_ID_12;
		lin_msg_master.dlc = sizeof(lin_data_master);
		lin_msg_master.lin_cmd = PUBLISH;
		lin_register_descriptor(LIN_MASTER_NODE_NUM, 0, &lin_msg_master);
		/* Configure lin_descriptor SLAVE */
		lin_msg_slave.id = LIN_FRAME_ID_12;
		lin_msg_slave.dlc = sizeof(lin_data_slave);
		lin_msg_slave.lin_cmd = SUBSCRIBE;
		lin_msg_slave.pfnct = lin_slave_task_ID12,
		lin_register_descriptor(LIN_SLAVE_NODE_NUM, 0, &lin_msg_slave);
		memcpy(&lin_data_master, "12345678", sizeof(lin_data_master));
		break;

	case 'S':
	case 's':
		/* Configure lin_descriptor MASTER */
		lin_msg_master.id = LIN_FRAME_ID_15;
		lin_msg_master.dlc = sizeof(lin_data_master);
		lin_msg_master.lin_cmd = SUBSCRIBE;
		lin_register_descriptor(LIN_MASTER_NODE_NUM, 1, &lin_msg_master);
		/* Configure lin_descriptor SLAVE */
		lin_msg_slave.id = LIN_FRAME_ID_15;
		lin_msg_slave.dlc = sizeof(lin_data_slave);
		lin_msg_slave.lin_cmd = PUBLISH;
		lin_register_descriptor(LIN_SLAVE_NODE_NUM, 1, &lin_msg_slave);
		/* Interrupt Master, wait transfer complete */
		irq_enable(id);
		memcpy(&lin_data_slave, "87654321", sizeof(lin_data_slave));
		break;

	default:
		irq_disable(id);
		lin_msg_master.lin_cmd = IGNORE;
		lin_msg_slave.lin_cmd = IGNORE;
		break;
	}
}


/**
 *  \brief Handler for Console input.
 *
 *  Handle process LED1 or LED2 status change.
 */
static void _console_handler(uint8_t k)
{
	key = k;
}

/**
 * \brief Interrupt handler for TC. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
static int _tc_handler(void* arg, void* arg2)
{
	if (lin_msg_master.lin_cmd == PUBLISH)
		lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_12, sizeof(lin_data_master));
	else
		lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_15, sizeof(lin_data_master));

	return 0;
}

/**
 * \brief start the TC
 */
static void _start_tc(void)
{
	struct _callback _cb;

	callback_set(&_cb, _tc_handler, NULL);
	tcd_start(&_tc, &_cb);
}

/**
 *  \brief Interrupt handler for Usart COM2 master node.
 */
static void _com2_master_handler(uint32_t source, void* arg)
{
	lin_master_usart_handler(LIN_MASTER_NODE_NUM);
}

/**
 *  \brief Interrupt handler for Usart COM3 slave node.
 */
static void _com3_slave_handler(uint32_t source, void* user_arg)
{
	lin_slave_usart_handler(LIN_SLAVE_NODE_NUM);
}

/**
 *  \brief Init Usart COM2 master.
 */
static void _init_com_master (void)
{
	uint32_t id = get_usart_id_from_addr(lin_desc2.addr);

	/* Configure Pios usart*/
	pio_configure(&pins_com2[0], ARRAY_SIZE(pins_com2));

	/* Init LIN MASTER data Node 0 */
	lin_init(&lin_desc2, LIN_MASTER_NODE_NUM);

	/* Configure interrupts */
	usart_enable_it(lin_desc2.addr, US_IER_LINTC);
	irq_add_handler(id, _com2_master_handler, NULL);
}

/**
 *  \brief Init Usart COM3 slave.
 */
static void _init_com_slave (void)
{
	uint32_t id = get_usart_id_from_addr(lin_desc3.addr);

	/* Configure Pios usart*/
	pio_configure(&pins_com3[0], ARRAY_SIZE(pins_com3));

	/* Init LIN SLAVE data Node 0 */
	lin_init(&lin_desc3, LIN_SLAVE_NODE_NUM);

	/* Configure interrupts */
	usart_enable_it(lin_desc3.addr, US_IER_LINID);
	irq_add_handler(id, _com3_slave_handler, NULL);
	irq_enable(id);
}

/**
 *  \brief Main menu.
 */
static void _display_menu (void)
{
	printf("\n\rMenu :\n\r ------\n\r");
	printf("  P: [%c] Run Master PUBLISHER to Slave SUBSCRIBER \n\r", (lin_msg_master.lin_cmd==PUBLISH) ? 'X' : ' ');
	printf("  S: [%c] Run Master SUBSCRIBER to Slave PUBLISHER \n\r", (lin_msg_master.lin_cmd==SUBSCRIBE) ? 'X' : ' ');
	printf("  I: [%c] Master and Slave mode IGNORE \n\r", (lin_msg_master.lin_cmd==IGNORE) ? 'X' : ' ');
	printf("  Q: Stop demo and Quit \n\r ------\n\r\r");
}

/*----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

/**
 *  \brief LIN Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Output example information */
	console_example_info("LIN Example");

	/* Configure Console interrupts */
	printf("Initializing console interrupts\r\n");
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();

	/* Configure Timer/Counter */
	tcd_configure_counter(&_tc, 0, TC_FREQ);

	/* Configure com port */
	_init_com_master();
	_init_com_slave();

	/* main LIN program */
	_display_menu();
	do {
		switch (key) {
		case 'P':
		case 'p':
		case 'S':
		case 's':
		case 'I':
		case 'i':
			tcd_stop(&_tc);
			_process_button_evt();
			_display_menu();
			if (key == 'I' || key == 'i')
				tcd_stop(&_tc);
			else
				_start_tc();
			key = 0;
			break;
		default:
			break;
		}
	} while (key != 'q' && key != 'Q');

	tcd_stop(&_tc);
	msleep(500);
	printf("\n\rEnd of demo\n\r");
	while (1);
}
