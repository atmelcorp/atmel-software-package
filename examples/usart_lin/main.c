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

#include "board.h"
#include "chip.h"
#include "mutex.h"
#include "timer.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/l2cc.h"
#include "peripherals/tc.h"
#include "peripherals/usart.h"

#include "misc/led.h"
#include "misc/console.h"

#include "power/act8945a.h"

#include "lin.h"

#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** LED0 blink time, LED1 blink half this time, in ms */
#define BLINK_PERIOD        1000

/** Maximum number of handled led */
#define MAX_LEDS            3

/** LIN frame number */
#define LIN_FRAME_ID_12       0x12
#define LIN_FRAME_ID_15       0x15


/** LIN master node number */
#define LIN_MASTER_NODE_NUM   0

/** LIN slave node number */
#define LIN_SLAVE_NODE_NUM    1

/** Timer counter channel used */
#define TC_CHANNEL            0

/** Timer counter frequency in Hz */
#define TC_FREQ               10

/** LED0 wait count */
#define LIN_LED0_WAIT_COUNTER 10

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** Local Buffer for emission */
uint8_t lin_data_master[8];
uint8_t lin_data_slave[8];

static uint32_t lin_led_red_counter = 0;

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	struct _pin act8945a_pins[] = ACT8945A_PINS;

	struct _twi_desc act8945a_twid = {
		.addr = ACT8945A_ADDR,
		.freq = ACT8945A_FREQ,
		.transfert_mode = TWID_MODE_POLLING
	};
	struct _act8945a act8945a = {
		.desc = {
			.pin_chglev = ACT8945A_PIN_CHGLEV,
			.pin_irq = ACT8945A_PIN_IRQ,
			.pin_lbo = ACT8945A_PIN_LBO
		}
	};
#endif

/** COM2 definition **/
#define PINS_COM2_USART         PINS_FLEXCOM0_USART_IOS1
#define COM2_PER_ADD            FLEXCOM0
#define COM2_ID                 ID_FLEXCOM0
#define COM2_BAUDRATE           9600
#define COM2_MODE_LIN_MASTER    (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_MASTER)
#define COM2_MODE_LIN_SLAVE     (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_SLAVE)

/** Pins for COM2 */
static const struct _pin pins_com2[] = PINS_COM2_USART;

/* Connected to CTS */
#define PIN_LIN_COM2_CTS 	{ PIO_GROUP_B, PIO_PB31C_FLEXCOM0_IO3, PIO_OUTPUT_1, PIO_PULLUP }
/* Connected to RTS */
#define PIN_LIN_COM2_RTS 	{ PIO_GROUP_C, PIO_PC0C_FLEXCOM0_IO4, PIO_OUTPUT_1, PIO_DEFAULT }


struct _lin_desc lin_desc2 = {
	.pin_rts = PIN_LIN_COM2_RTS,
	.pin_cts = PIN_LIN_COM2_CTS,
	.addr = COM2_PER_ADD,
	.id = COM2_ID,
};


/** COM3 definition **/
#define PINS_COM3_USART         PINS_FLEXCOM1_USART_IOS1
#define COM3_PER_ADD            FLEXCOM1
#define COM3_ID                 ID_FLEXCOM1
#define COM3_BAUDRATE           9600
#define COM3_MODE_LIN_MASTER    (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_MASTER)
#define COM3_MODE_LIN_SLAVE     (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | US_MR_PAR_ODD | US_MR_USART_MODE_LIN_SLAVE)

static const struct _pin pins_com3[] = PINS_COM3_USART;

/* Connected to CTS */
#define PIN_LIN_COM3_CTS 	{ PIO_GROUP_A, PIO_PA25A_FLEXCOM1_IO3, PIO_OUTPUT_1, PIO_DEFAULT }
/* Connected to RTS */
#define PIN_LIN_COM3_RTS 	{ PIO_GROUP_A, PIO_PA26A_FLEXCOM1_IO4, PIO_OUTPUT_1, PIO_PULLUP }


struct _lin_desc lin_desc3 = {
	.pin_rts = PIN_LIN_COM3_RTS,
	.pin_cts = PIN_LIN_COM3_CTS,
	.addr = COM3_PER_ADD,
	.id = COM3_ID,
};

/* Default configure lin massage structure */
struct _lin_message lin_mes_master = {
	.id = 0,
	.dlc = 0,
	.lin_cmd = IGNORE,
	.status = 0,
	.pdata = &lin_data_master[0],
	.pfnct = NULL,
};
struct _lin_message lin_mes_slave = {
	.id = 0,
	.dlc = sizeof(lin_data_slave),
	.lin_cmd = IGNORE,
	.status = 0,
	.pdata = &lin_data_slave[0],
	.pfnct = NULL,
};

uint8_t key;

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
	switch (key) {
	case 'P':
	case 'p':
		/* No interrupt on Master */
		aic_disable(lin_desc2.id);
		/* Configure lin_descriptor MASTER */
		lin_mes_master.id = LIN_FRAME_ID_12;
		lin_mes_master.dlc = sizeof(lin_data_master);
		lin_mes_master.lin_cmd = PUBLISH;
		lin_register_descriptor(LIN_MASTER_NODE_NUM, 0, &lin_mes_master);
		/* Configure lin_descriptor SLAVE */
		lin_mes_slave.id = LIN_FRAME_ID_12;
		lin_mes_slave.dlc = sizeof(lin_data_slave);
		lin_mes_slave.lin_cmd = SUBSCRIBE;
		lin_mes_slave.pfnct = lin_slave_task_ID12,
		lin_register_descriptor(LIN_SLAVE_NODE_NUM, 0, &lin_mes_slave);
		memcpy(&lin_data_master, "12345678",sizeof(lin_data_master));
		break;

	case 'S':
	case 's':
		/* Configure lin_descriptor MASTER */
		lin_mes_master.id = LIN_FRAME_ID_15;
		lin_mes_master.dlc = sizeof(lin_data_master);
		lin_mes_master.lin_cmd = SUBSCRIBE;
		lin_register_descriptor(LIN_MASTER_NODE_NUM, 1, &lin_mes_master);
		/* Configure lin_descriptor SLAVE */
		lin_mes_slave.id = LIN_FRAME_ID_15;
		lin_mes_slave.dlc = sizeof(lin_data_slave);
		lin_mes_slave.lin_cmd = PUBLISH;
		lin_register_descriptor(LIN_SLAVE_NODE_NUM, 1, &lin_mes_slave);
		/* Interrupt Master, wait transfert complete */
		aic_enable(lin_desc2.id);
		memcpy(&lin_data_slave, "87654321",sizeof(lin_data_slave));
		break;

	default:
		aic_disable(lin_desc2.id);
		lin_mes_master.lin_cmd = IGNORE;
		lin_mes_slave.lin_cmd = IGNORE;
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
 * \brief Interrupt handler for TC0. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
static void _tc_handler(void)
{
	uint32_t dummy;
	/* Clear status bit to acknowledge interrupt */
	dummy = tc_get_status(TC0, TC_CHANNEL);
	(void) dummy;

	if(lin_mes_master.lin_cmd == PUBLISH)
		lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_12, sizeof(lin_data_master));
	else
		lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_15, sizeof(lin_data_master));
}


/**
 *  Configure Timer Counter 0 to generate an interrupt every 250ms.
 */
static void _configure_tc(void)
{
	/** Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);
	/* Put the source vector */
	aic_set_source_vector(ID_TC0, _tc_handler);
	/** Configure TC for a 50Hz frequency and trigger on RC compare. */
	tc_trigger_on_freq(TC0, TC_CHANNEL, TC_FREQ);
	/* Configure and enable interrupt on RC compare */
	tc_enable_it(TC0, TC_CHANNEL, TC_IER_CPCS);
	aic_enable(ID_TC0);
}

/**
 *  \brief Interrupt handler for Usart COM2 master node.
 */
static void _com2_master_handler (void)
{
	lin_master_usart_handler(LIN_MASTER_NODE_NUM);
}

/**
 *  \brief Interrupt handler for Usart COM3 slave node.
 */
static void _com3_slave_handler (void)
{
	lin_slave_usart_handler(LIN_SLAVE_NODE_NUM);
}

/**
 *  \brief Init Usart COM2 master.
 */
static void _init_com_master (void)
{
	Usart* usart = &lin_desc2.addr->usart;

	/* Configure Pios usart*/
	pio_configure(&pins_com2[0], ARRAY_SIZE(pins_com2));
	/* Init LIN MASTER data Node 0 */
	lin_init(&lin_desc2, LIN_MASTER_NODE_NUM, COM2_MODE_LIN_MASTER, COM2_BAUDRATE);

	usart_enable_it(usart, US_IER_LINTC);
	aic_set_source_vector(lin_desc2.id, _com2_master_handler);
}

/**
 *  \brief Init Usart COM3 slave.
 */
static void _init_com_slave (void)
{
	Usart* usart = &lin_desc3.addr->usart;

	/* Configure Pios usart*/
	pio_configure(&pins_com3[0], ARRAY_SIZE(pins_com3));
	/* Init LIN SLAVE data Node 0 */
	lin_init(&lin_desc3, LIN_SLAVE_NODE_NUM, COM3_MODE_LIN_SLAVE, COM3_BAUDRATE);

	usart_enable_it(usart, US_IER_LINID);
	aic_set_source_vector(lin_desc3.id, _com3_slave_handler);
	aic_enable(lin_desc3.id);
}

/**
 *  \brief Main menu.
 */
static void _display_menu (void)
{
	printf("\n\rMenu :\n\r ------\n\r");
	printf("  P: [%c] Run Master PUBLISHER to Slave SUBSCRIBER \n\r", (lin_mes_master.lin_cmd==PUBLISH) ? 'X' : ' ');
	printf("  S: [%c] Run Master SUBSCRIBER to Slave PUBLISHER \n\r", (lin_mes_master.lin_cmd==SUBSCRIBE) ? 'X' : ' ');
	printf("  I: [%c] Master and Slave mode IGNORE \n\r", (lin_mes_master.lin_cmd==IGNORE) ? 'X' : ' ');
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
	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console(0);
	console_clear_screen();
	console_reset_cursor();

	/* Output example information */
	printf("-- LIN Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME "\n\r"
	       "-- Compiled: "__DATE__ " at " __TIME__" --\n\r");

	/* Configure Console interrupts */
	printf("Initializing console interrupts\r\n");
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();

	/* Configure PIT. Must be always ON, used for delay */
	printf("Configure PIT \n\r");
	timer_configure(BLINK_PERIOD);

	/* PIO configuration for LEDs */
	printf("Configure LED PIOs.\n\r");
	led_configure(LED_RED);
	led_configure(LED_GREEN);
	led_configure(LED_BLUE);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	pio_configure(act8945a_pins, ARRAY_SIZE(act8945a_pins));
	if (act8945a_configure(&act8945a, &act8945a_twid)) {
		act8945a_set_regulator_voltage(&act8945a, 6, 2500); /* VLEDS */
		act8945a_enable_regulator(&act8945a, 6, true);
	} else {
		printf("--E-- Error initializing ACT8945A PMIC\n\r");
	}
#endif

	/* Configure Timer/Counter */
	_configure_tc();

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
			tc_stop(TC0, TC_CHANNEL);
			_process_button_evt();
			_display_menu();
			if ((key == 'I') || (key == 'i') ) tc_stop(TC0, 0);
			else tc_start(TC0, TC_CHANNEL);
			key = 0;
			break;
		default:
			break;
		}
	} while ( key != 'q' && key != 'Q');

	tc_stop(TC0, TC_CHANNEL);
	timer_wait(500);
	printf("\n\r End of demo \n\r");
	while (1);
}
