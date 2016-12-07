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
 * this software withoupecific prior written permission.
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
/** \cond usb_iad_cdc_cdc
 * \page usb_iad_cdc_cdc USB DUAL CDC Serial Port Example
 *
 * \section Purpose
 *
 * The USB DUALCDC Project will help you to get familiar with the
 * USB Device Port(UDP)interface and also some of the other interfaces in
 * SAM9 microcontrollers. Also it can help you to be familiar with the USB
 * Framework that is used for rapid development of USB-compliant class
 * drivers such as USB Communication Device class (CDC), and how to combine
 * two USB functions to a single composite device (such as Dual CDC port).
 *
 * \section Requirements
 *
 * This package can be used with some of Atmel evaluation kits that have UDP
 * interface, depending on the functions included.
 *
 *  \section win_drv_update Windows Driver Update
 *
 * The composite device is generally supported by Microsoft windows, but some
 * patches are needed for muti-interface functions such as CDC & Audio. The
 * example composite devices are tested under windows XP (SP3). For CDC
 * serial port, additional windows driver file (CompositeCDCSerial.inf) can
 * be found at
 * libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf.
 *
 * The following is alternate update to fix the composite device support
 * on windows XP:
 *
 * \subsection install_win_sp3 Install Windows Service Pack 3 (SP3)
 *
 * All the fixes for USB generic driver are included in window XP service pack
 * 3. It can be found at
 * http://technet.microsoft.com/zh-cn/windows/bb794714(en-us).aspx .
 *
 * \subsection install_win_hotfix Install Windows Hot Fixes
 *
 * Two hot fixes are necessary for window to recognize the composite device
 * correctly:
 *
 * -# http://support.microsoft.com/kb/814560
 * -# http://support.microsoft.com/kb/918365
 *
 * \section Description
 *
 * This demo simulates 2 USB to RS-232 Serial Port Converter.
 *
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, host will notice the attachment of a USB device. No device
 * driver offered for the device now.
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
 *     -- USB Dual CDC Device Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the host reports a new USB device attachment.
 * -# You can use the inf file
 *    libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf
 *    to install the serial  port. Then new
 *    "AT91 USB to Serial Converter (COMx)" appears in the
 *    hardware device list.
 * -# You can run hyperterminal to send data to the port. And it can be seen
 *    at the other hyperterminal connected to the USART port of the EK or
 *    another USB serial port.
 *
 * \section References
 * - usb_iad_cdc_cdc/main.c
 * - pio: Pin configurations and peripheral configure.
 * - usb: USB Device Framework, USB CDC driver and UDP interface driver
 *    - \ref usbd_framework
 *        - \ref usbd_api
 *    - \ref usbd_composite "composite"
 *       - \ref usbd_composite_drv
 *    - \ref usbd_cdc "cdc-serial"
 *       - \ref usbd_cdc_serial_drv
 * - projects:
 *    - \ref usb_cdc_serial
 *
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_iad_cdc_cdc
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "chip_pins.h"
#include "trace.h"
#include "compiler.h"

#include "mm/cache.h"
#include "serial/console.h"

#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "serial/usartd.h"
#include "serial/usart.h"

#include "usb/device/composite/dual_cdcd_driver.h"
#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

/** Size in bytes of the packet used for reading data from USB */

#define DATAPACKETSIZE (1024)

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (DATAPACKETSIZE+2)

/** Basic asynchronous mode, i.e. 8 bits no parity.*/
#define USART_MODE_ASYNCHRONOUS \
					(US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT | US_MR_PAR_NO)

/*----------------------------------------------------------------------------
 *      External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors dual_cdcd_driver_descriptors;

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/

/** Buffer for storing incoming USB data for serial port 0. */
CACHE_ALIGNED static uint8_t usb_serial_buffer0[DATABUFFERSIZE];
/** Buffer for storing incoming USB data for serial port 1. */
CACHE_ALIGNED static uint8_t usb_serial_buffer1[DATABUFFERSIZE];

/** Usart openned */
static uint8_t is_usart_on = 0;
/** Serial port 0 openned */
static uint8_t is_serial_port0_on = 0;
/** Serial port 1 openned */
static uint8_t is_serial_port1_on = 0;


/*-----------------------------------------------------------------------------
 *         Callback re-implementation
 *-----------------------------------------------------------------------------*/

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	dual_cdcd_driver_configuration_change_handler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	dual_cdcd_driver_request_handler(request);
}

/*----------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/**
 * Callback invoked when data has been received on the USB.
 * For USB CDC Serial Port 0
 */
static void _usb_data_received0(void *read,
							uint8_t status,
							uint32_t received,
							uint32_t remaining)
{
	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {
		*(uint8_t *)read = 1;
		/* Send data through USBSerial 1 */
		while (cdcd_serial_port_write(dual_cdcd_driver_get_serialport(1),
							usb_serial_buffer0,
							received, 0, 0) != USBD_STATUS_SUCCESS);

		/* Check if bytes have been discarded */
		if ((received == DATABUFFERSIZE) && (remaining > 0)) {
			trace_warning(
						"_usb_data_received0: %u bytes discarded\n\r",
						(unsigned int)remaining);
		}
	} else {
		trace_warning( "_usb_data_received0: Transfer error\n\r");
	}
}

/**
 * Callback invoked when data has been received on the USB.
 * For USB CDC Serial Port 1
 */
static void _usb_data_received1(void *read,
							uint8_t status,
							uint32_t received,
							uint32_t remaining)
{
	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {
		*(uint8_t *)read = 1;
		/* Send data through USBSerial 0 */
		while (cdcd_serial_port_write(dual_cdcd_driver_get_serialport(0),
							usb_serial_buffer1,
							received, 0, 0) != USBD_STATUS_SUCCESS);

		/* Check if bytes have been discarded */
		if ((received == DATABUFFERSIZE) && (remaining > 0)) {
			trace_warning(
						"_usb_data_received1: %u bytes discarded\n\r",
						(unsigned int)remaining);
		}
	} else {
		trace_warning( "_usb_data_received1: Transfer error\n\r");
	}
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Exported function
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *          Main
 *---------------------------------------------------------------------------*/

/**
 * Initializes drivers and start the USB Dual CDC device.
 */
int main(void)
{
	uint8_t usb_connected = 0;
	uint8_t serial0_on = 0, serial1_on = 0, usart_on = 0;
	uint8_t serial0_read = 1;
	uint8_t serial1_read = 1;

	/* Output example information */
	console_example_info("USB Dual CDC Device Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* ----- CDC Function Initialize */
	/* USB DualCDC driver initialization */
	dual_cdcd_driver_initialize(&dual_cdcd_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {
		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			if (usb_connected) {
				printf("-I- USB Disconnect/Suspend\n\r");
				usb_connected = 0;
				/* Serial port closed */
				is_serial_port0_on = 0;
				is_serial_port1_on = 0;
				is_usart_on = 0;
			}
		} else {
			is_serial_port0_on = cdcd_serial_port_get_control_line_state(
								dual_cdcd_driver_get_serialport(0))
								& CDCControlLineState_DTR;
			is_serial_port1_on = cdcd_serial_port_get_control_line_state(
								dual_cdcd_driver_get_serialport(1))
								& CDCControlLineState_DTR;

			if (usb_connected == 0) {
				printf("-I- USB Connect\n\r");
				usb_connected = 1;
			}

			is_usart_on = is_serial_port0_on || is_serial_port1_on;
			if (!usart_on && is_usart_on) {

				usart_on = 1;
				printf("-I- USART ON\n\r");

			} else if (usart_on && !is_usart_on) {
				usart_on = 0;
				printf("-I- USART OFF\n\r");
			}

			if (is_serial_port0_on) {

				if(!serial0_on) {
					serial0_on = 1;
					printf("-I- SerialPort0 ON\n\r");
				}

				/* Start receiving data on the USB */
				if (serial0_read == 1) {
					serial0_read = 0;
					cdcd_serial_port_read(dual_cdcd_driver_get_serialport(0),
										  usb_serial_buffer0,
										  DATAPACKETSIZE,
										  (usbd_xfer_cb_t) _usb_data_received0,
										  &serial0_read);
				}
			} else if (serial0_on && !is_serial_port0_on) {
				serial0_on = 0;
				printf("-I- SerialPort0 OFF\n\r");
			}

			if (is_serial_port1_on) {

				if(!serial1_on) {
					serial1_on = 1;
					printf("-I- SerialPort1 ON\n\r");
				}
				/* Start receiving data on the USB */
				if (serial1_read == 1) {
					serial1_read = 0;
					cdcd_serial_port_read(dual_cdcd_driver_get_serialport(1),
										  usb_serial_buffer1,
										  DATAPACKETSIZE,
										  (usbd_xfer_cb_t) _usb_data_received1,
										  &serial1_read);
				}
			} else if (serial1_on && !is_serial_port1_on) {
				serial1_on = 0;
				printf("-I- SerialPort1 OFF\n\r");
			}
		}
	}
}
/** \endcond */
