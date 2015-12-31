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
/** \cond usb_cdc_serial
 * \page usb_cdc_serial USB CDC Serial Converter Example
 *
 * \section Purpose
 *
 * The USB CDC Serial Project will help you to get familiar with the
 * USB Device Port(UDP) and USART interface on SAMA5D4x microcontrollers. Also
 * it can help you to be familiar with the USB Framework that is used for
 * rapid development of USB-compliant class drivers such as USB Communication
 * Device class (CDC).
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4EK and SAMA5D4-XULT board.
 *
 * \section Description
 *
 * This demo simulates a USB to RS-232 Serial Port Converter.
 *
 * When the board running this program connected to a host (PC for example), with
 * USB cable, the board appears as a serial COM port for the host, after driver
 * installation with the offered 6119.inf. Then the host can send or receive
 * data through the port with host software. The data stream from the host is
 * then sent to the board, and forward to USART port of AT91SAM chips. The USART
 * port of the board is monitored by the timer and the incoming data will be sent
 * to the host.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB Device CDC Serial Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the host
 *    reports a new USB device attachment (if it's the first time you connect
 *    an %audio speaker demo board to your host). You can use the inf file
 *    libraries\\usb\\device\\cdc-serial\\drv\\6119.inf to install the serial
 *    port. Then new "AT91 USB to Serial Converter (COMx)" appears in the
 *    hardware device list.
 * -# You can run hyperterminal to send data to the port. And it can be seen
 *    at the other hyperterminal connected to the USART port of the boad.
 *
 * \section References
 * - usb_cdc_serial/main.c
 * - usart: USART interface driver
  * - usb: USB Framework, USB CDC driver and UDP interface driver
 *    - \ref usbd_framework
 *       - \ref usbd_api
 *    - \ref usbd_cdc
 *       - \ref usbd_cdc_serial_drv
 *       - \ref usbd_cdc_host_drv
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_cdc_serial example.
 *
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "trace.h"
#include "compiler.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#include "misc/console.h"

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/twid.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"
#include "peripherals/usart.h"

#include "usb/device/cdc/cdcd_serial_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"

#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *      Definitions
 *----------------------------------------------------------------------------*/

/** Size in bytes of the packet used for reading data from the USB & USART */
#define DATAPACKETSIZE (64)

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (DATAPACKETSIZE+2)

/** Basic asynchronous mode, i.e. 8 bits no parity.*/
#define USART_MODE_ASYNCHRONOUS        (US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_PAR_NO)

/** Register base for USART operation */
#define BASE_USART      USART1

/** USART ID */
#define ID_USART        ID_USART1

/** test buffer size */
#define TEST_BUFFER_SIZE    (2*1024)

/** write loop count */
#define TEST_COUNT          (30)

/*----------------------------------------------------------------------------
 *      External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors cdcd_serial_driver_descriptors;

/*----------------------------------------------------------------------------
 *      Internal variables
----------------------------------------------------------------------------*/


/** DMA channel for RX */
static struct _xdmad_channel* usart_dma_rx_channel;
/** DMA channel for TX */
static struct _xdmad_channel* usart_dma_tx_channel;

/** USART link list for data RX */
static struct _xdmad_desc_view1 dma_rx_link_list[2];

/** List of pins that must be configured for use by the application. */
static const struct _pin pins[] = PINS_FLEXCOM1_USART_IOS1;

/** Double-buffer for storing incoming USART data. */
static uint8_t usart_buffers[2][DATABUFFERSIZE];

/** Current USART buffer index. */
static uint8_t usart_current_buffer = 0;

/** Buffer for storing incoming USB data. */
static uint8_t usb_buffer[DATABUFFERSIZE];

/** Serial Port ON/OFF */
static uint8_t is_cdc_serial_on = 0;

/** CDC Echo back ON/OFF */
static uint8_t is_cdc_echo_on = 0;

/** USB Tx flag */
static volatile uint8_t tx_done_flag = 0;
/** Test buffer */
static uint8_t test_buffer[TEST_BUFFER_SIZE];

/*----------------------------------------------------------------------------
 *         Internal Prototypes
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Interrupt handlers
 *----------------------------------------------------------------------------*/

/**
 * USART interrupt handler
 */
static void usart_irq_handler( void )
{
	Usart *p_us = BASE_USART;
	uint32_t status;
	uint16_t serial_state;

	status  = usart_get_status(p_us);
	status &= usart_get_it_mask(p_us);

	/* If USB device is not configured, do nothing */
	if (!is_cdc_serial_on)
	{
		usart_disable_it(p_us, 0xFFFFFFFF);
		return;
	}

	/* Errors */
	serial_state = cdcd_serial_driver_get_serial_state();
	/* Overrun */
	if ((status & US_CSR_OVRE) != 0) {
		trace_warning( "usart_irq_handler: Overrun\n\r");
		serial_state |= CDCSerialState_OVERRUN;
	}

	/* Framing error */
	if ((status & US_CSR_FRAME) != 0) {
		trace_warning( "usart_irq_handler: Framing error\n\r");
		serial_state |= CDCSerialState_FRAMING;
	}
	cdcd_serial_driver_set_serial_state(serial_state);
}

/*-----------------------------------------------------------------------------
 *         Callback re-implementation
 *-----------------------------------------------------------------------------*/

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(unsigned char cfgnum)
{
	cdcd_serial_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	cdcd_serial_driver_request_handler(request);
}

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Send single buffer data through DMA
 */
static void _usart_dma_tx( uint32_t dw_dest_addr,
			void* pBuffer, uint16_t wSize )
{
	/* Setup transfer */
	struct _xdmad_cfg xdmad_cfg;
	xdmad_cfg.ublock_size = wSize ;
	xdmad_cfg.src_addr = (void*) pBuffer;
	xdmad_cfg.dest_addr = (void*) dw_dest_addr;
	xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
				| XDMAC_CC_MEMSET_NORMAL_MODE
				| XDMAC_CC_CSIZE_CHK_1
				| XDMAC_CC_DWIDTH_BYTE
				| XDMAC_CC_SIF_AHB_IF0
				| XDMAC_CC_DIF_AHB_IF1
				| XDMAC_CC_SAM_INCREMENTED_AM
				| XDMAC_CC_DAM_FIXED_AM;

	xdmad_cfg.block_size = 0;
	xdmad_configure_transfer( usart_dma_tx_channel, &xdmad_cfg, 0, 0);
	xdmad_start_transfer( usart_dma_tx_channel );
}

/**
 *  \brief Prepare link list for USART RX
 *  Ringed link list initialized for 2 USART buffer.
 */
static void _usart_dma_rx_setup( void )
{
	uint8_t i;
	Usart *p_us = BASE_USART;
	for (i = 0; i < 2; i++) {

		dma_rx_link_list[i].ublock_size = XDMA_UBC_NVIEW_NDV1
				| XDMA_UBC_NDE_FETCH_EN
				| XDMA_UBC_NSEN_UPDATED
				| XDMAC_CUBC_UBLEN(DATAPACKETSIZE);

		dma_rx_link_list[i].src_addr  = (void*)&p_us->US_RHR;
		dma_rx_link_list[i].dest_addr = (void*)usart_buffers[i];
		dma_rx_link_list[i].next_desc = (void*)&dma_rx_link_list[i];
	}
}

/**
 *  \brief Start waiting USART data
 *  Start DMA, the 1st DMA buffer is free USART buffer assigned.
 */
static void _usart_dma_rx( uint32_t start_buffer )
{
	struct _xdmad_cfg xdmad_usart_rx_cfg;
	uint32_t xdma_usart_rx_cndc;

	xdmad_usart_rx_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
				| XDMAC_CC_MBSIZE_SINGLE
				| XDMAC_CC_DSYNC_PER2MEM
				| XDMAC_CC_CSIZE_CHK_1
				| XDMAC_CC_DWIDTH_BYTE
				| XDMAC_CC_SIF_AHB_IF1
				| XDMAC_CC_DIF_AHB_IF0
				| XDMAC_CC_SAM_FIXED_AM
				| XDMAC_CC_DAM_INCREMENTED_AM;

	xdma_usart_rx_cndc = XDMAC_CNDC_NDVIEW_NDV1
				| XDMAC_CNDC_NDE_DSCR_FETCH_EN
				| XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
				| XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED ;

	xdmad_configure_transfer( usart_dma_rx_channel, &xdmad_usart_rx_cfg,
			xdma_usart_rx_cndc, (void*)&dma_rx_link_list[start_buffer]);
	xdmad_start_transfer( usart_dma_rx_channel);
}

/**
 * console help dump
 */
static void _debug_help(void)
{
	printf("-- ESC to Enable/Disable ECHO on cdc serial --\n\r");
	printf("-- Press 't' to test trasfer --\n\r");
}

/**
 * Callback invoked when data has been received on the USB.
 */
static void _usb_data_received(void *arg, uint8_t status,
		uint32_t received, uint32_t remaining)
{
	Usart *p_us = BASE_USART;

	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {

		/* Send back CDC data */
		if (is_cdc_echo_on){

			cdcd_serial_driver_write(usb_buffer, received, 0, 0);
		}
		/* Send data through USART */
		if (is_cdc_serial_on) {

			_usart_dma_tx( (uint32_t)&p_us->US_THR,
					usb_buffer, received );
		}

		/* Check if bytes have been discarded */
		if ((received == DATAPACKETSIZE) && (remaining > 0)) {

			trace_warning(
				"_usb_data_received: %u bytes discarded\n\r",
					(unsigned int)remaining);
		}
	} else {

		trace_warning( "_usb_data_received: Transfer error\n\r");
	}
}

/**
 * Callback invoked when data has been sent.
 */
static void _usb_data_sent(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining)
{
	tx_done_flag = 1;
}

/**
 * \brief DMA RX callback function
 */
static void _us_dma_rx_callback( uint8_t status, void *p_arg)
{
	p_arg = p_arg;
	if (status != XDMAD_OK) return;

	/* Send buffer through the USB */
	while (cdcd_serial_driver_write(usart_buffers[usart_current_buffer],
			DATAPACKETSIZE, 0, 0) != USBD_STATUS_SUCCESS);

	/* Restart read on buffer */
	usart_current_buffer = 1 - usart_current_buffer;
	_usart_dma_rx(usart_current_buffer);

}

/**
 * \brief DMA TX callback function
 */
static void _us_dma_tx_callback( uint8_t status, void *p_arg)
{
	p_arg = p_arg;
	if (status != XDMAD_OK) return;

	/* Restart USB read */
	cdcd_serial_driver_read(usb_buffer, DATAPACKETSIZE,
			_usb_data_received, NULL);
}

/**
 * \brief DMA driver configuration
 */
static void _configure_dma( void )
{
	/* Driver initialize */
	xdmad_initialize(0);

	/* Allocate DMA channels for USART */
	usart_dma_tx_channel =
			xdmad_allocate_channel( XDMAD_PERIPH_MEMORY, ID_USART);
	usart_dma_rx_channel =
			xdmad_allocate_channel( ID_USART, XDMAD_PERIPH_MEMORY);

	/* Set RX callback */
	xdmad_set_callback( usart_dma_rx_channel,
				(xdmad_callback_t)_us_dma_rx_callback, 0);
	/* Set TX callback */
	xdmad_set_callback( usart_dma_tx_channel,
				(xdmad_callback_t)_us_dma_tx_callback, 0);

	xdmad_prepare_channel( usart_dma_rx_channel);
	xdmad_prepare_channel( usart_dma_tx_channel);
}

/**
 * Configure USART to work @ 115200
 */
static void _configure_usart(void)
{
	pio_configure(pins, ARRAY_SIZE(pins));
	pmc_enable_peripheral(ID_USART);
	usart_disable_it(BASE_USART, 0xFFFFFFFF);
	usart_configure(BASE_USART,
			USART_MODE_ASYNCHRONOUS,
			115200
			);

	usart_set_transmitter_enabled(BASE_USART, 1);
	usart_set_receiver_enabled(BASE_USART, 1);
	aic_set_source_vector(ID_USART, usart_irq_handler);
	aic_enable(ID_USART);
}

/**
 * Test USB CDC Serial
 */
static void _send_text(void)
{
	uint32_t i, test_cnt;

	if (!is_cdc_serial_on) {

		printf("\n\r!! Host serial program not ready!\n\r");
		return;
	}
	printf("\n\r- USB CDC Serial writing ...\n\r");

	/* Test data initialize */
	for (i = 0; i < TEST_BUFFER_SIZE; i ++) test_buffer[i] = (i % 10) + '0';

	printf("- Send 0,1,2 ... to host:\n\r");
	for (test_cnt = 0; test_cnt < TEST_COUNT; test_cnt ++) {

		tx_done_flag = 0;
		cdcd_serial_driver_write(test_buffer, TEST_BUFFER_SIZE,
				_usb_data_sent, NULL);
		while(!tx_done_flag);
	}

	/* Finish sending */
	cdcd_serial_driver_write(NULL, 0, NULL, NULL);
}

/*----------------------------------------------------------------------------
 *          Main
 *----------------------------------------------------------------------------*/

/**
 * \brief usb_cdc_serial Application entry point.
 *
 * Initializes drivers and start the USB <-> Serial bridge.
 */
int main(void)
{
	uint8_t is_usb_connected = 0;

	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console();

#ifndef VARIANT_DDRAM
	board_cfg_ddram();
#endif

	/* Output example information */
	printf("-- USB Device CDC Serial Project %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* Configure DMA driver */
	_configure_dma();

	/* Configure USART */
	_configure_usart();
	_usart_dma_rx_setup();

	/* CDC serial driver initialization */
	cdcd_serial_driver_initialize(&cdcd_serial_driver_descriptors);

	/* Help informaiton */
	_debug_help();

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {

		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {

			if (is_usb_connected) {
				is_usb_connected = 0;
				is_cdc_serial_on  = 0;
			}

		} else if (is_usb_connected == 0) {
				is_usb_connected = 1;
		}

		/* Serial port ON/OFF */
		if (cdcd_serial_driver_get_control_line_state()
					& CDCControlLineState_DTR) {
			if (!is_cdc_serial_on) {
				is_cdc_serial_on = 1;

				/* Start receiving data on the USART */
				usart_current_buffer = 0;
				_usart_dma_rx(usart_current_buffer);
				usart_enable_it(BASE_USART,
						US_CSR_FRAME | US_CSR_OVRE);
			}

			/* Start receiving data on the USB */
			cdcd_serial_driver_read(usb_buffer, DATAPACKETSIZE,
					_usb_data_received, NULL);
		} else if (is_cdc_serial_on) {
			is_cdc_serial_on = 0;
		}

		if (console_is_rx_ready()) {

			uint8_t key = console_get_char();
			/* ESC: CDC Echo ON/OFF */
			if (key == 27) {

				printf("** CDC Echo %s\n\r",
						is_cdc_echo_on ? "OFF" : "ON");
				is_cdc_echo_on = !is_cdc_echo_on;

			} else if (key == 't') {
				/* 't': Test CDC writing  */
				_send_text();

			} else {
				printf("Alive\n\r");
				cdcd_serial_driver_write((char*)"Alive\n\r", 8,
						NULL, NULL);
				_debug_help();
			}
		}
	}
}
/** \endcond */
