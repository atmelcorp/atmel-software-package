/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Atmel Corporation
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
/** \cond usb_printer_basic
 * \page usb_printer USB PRINTER Example
 *
 * \section Purpose
 *
 * This demo  implements a bare-metal(non RTOS) USB Printer Device application.
 *
 * \section Requirements
 *
 * This package can be used with some of Atmel evaluation kits that have UDP
 * interface, depending on the functions included.
 *
 * \section Description
 *
 * This demo shows how the board connected to the Windows PC enumerate as a USB
 * printer device is capable of printing.
 * This demo uses PC running Windows as a Host. The demo application on top of USB printer
 * function driver when connected to the host, enumerates as "USB Printing Support" device under
 * USB controllers in Device Manager. This demo allows the user to print the text from Notepad
 * or similar application in Windows using built in "Generic/Text Only" print driver.
 * Generic / Text Only driver simply outputs the data to the connected USB printer in raw
 * format without performing any translation on the data to be printed.
 * There is no Printer head mechanism used in this demo, instead, the print data received from
 * the host is sent to the serial terminal application running in the host itself by the demo
 * application. Open any serial terminal application with 115200/8-N-1 settings for the Virtual
 * COM port associated with the DEBUG.
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
 *     -- USB Printer basic Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the LED blinks, and the host
 *    reports a new USB device attachment.
 *
 * \section Reference
 * - usb_printer/main.c
 *    - \ref usbd_framework
 *        - \ref usbd_api
 *    - \ref usbd_printer
 *       - \ref usbd_printer_driver
 *
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_printer project
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "serial/console.h"
#include "mm/cache.h"

#include "usb/device/printer/printer_driver.h"
#include "usb/device/usbd_hal.h"

#include "main_descriptors.h"
#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
 *      Types
 *---------------------------------------------------------------------------*/
typedef struct
{
	/* 1 = No Error, 0 = Error */
	uint8_t errorStatus;
	/* 1 = Selected, 0 = Not Selected */
	uint8_t selectStatus;
	/* 1 = Paper Empty, 0 = Paper Not Empty */
	uint8_t paperEmptyStatus;
} printer_port_status;

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/
/* Length of the Device ID string including length in the first two bytes */
#define USB_DEVICE_PRINTER_DEVICE_ID_STRING_LENGTH    77

/* Device ID string including length in the first two bytes */
#define USB_DEVICE_PRINTER_DEVICE_ID_STRING  {0,77,'M','F','G',':','A','T','M','E','L',';','M','D','L',':','G','e','n','e','r','i','c',';','C','M','D',':','E','P','S','O','N',';','C','L','S',':','P','R','I','N','T','E','R',';','D','E','S',':','G','e','n','e','r','i','c','T','e','x','t','O','n','l','y','P','r','i','n','t','e','r','D','e','m','o',';'}

/** Size in bytes of the packet used for reading data from USB */
#define DATAPACKETSIZE CHIP_USB_ENDPOINT_MAXPACKETSIZE(PRINTER_Descriptors_DATAOUT0)

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (DATAPACKETSIZE + 2)

/*----------------------------------------------------------------------------
 *      Local variables
 *----------------------------------------------------------------------------*/
bool usb_is_read_complete = false;
CACHE_ALIGNED uint8_t printer_read_buf[DATABUFFERSIZE];

/*----------------------------------------------------------------------------
 *      External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors printer_driver_descriptors;

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/

uint8_t deviceID_String[USB_DEVICE_PRINTER_DEVICE_ID_STRING_LENGTH] = USB_DEVICE_PRINTER_DEVICE_ID_STRING;
printer_port_status prntrStatus;

/*-----------------------------------------------------------------------------
 *         Callback re-implementation
 *-----------------------------------------------------------------------------*/
/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	printer_driver_request_handler(request);
}

/**
 * Invoked when the configuration of the device changes. Resets the usb printer driver.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(unsigned char cfgnum)
{
	printer_driver_configuration_change_handler(cfgnum);
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/**
 * Callback invoked when data has been received on the USB.
 */
static void _usb_data_received(void *read, uint8_t status, uint32_t received, uint32_t remaining)
{
	uint32_t i;
	uint8_t* p;

	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {
		/* Send data through USART */
		p = (uint8_t*)printer_read_buf;
		for (i = 0; i < received; i++) {
			console_put_char(*p);
			p++;
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

/*---------------------------------------------------------------------------
 *         Exported function
 *---------------------------------------------------------------------------*/
void printet_driver_get_port_status(uint8_t* status)
{
	/* The host wants to know the printer's current status, in a format which is compatible
	with the status register of a standard PC parallel port. This is a control transfer request.
	 Use the USB_DEVICE_ControlSend() function to send the data to host. */
	*status = (uint8_t)(((prntrStatus.errorStatus << 3) & 0x08) |
			  ((prntrStatus.selectStatus << 4) & 0x10) |
			  ((prntrStatus.paperEmptyStatus << 5) & 0x20));
	return;
}

/*---------------------------------------------------------------------------
 *          Main
 *---------------------------------------------------------------------------*/

/**
 * Initializes drivers and start the USB printer device.
 */
int main(void)
{
	uint8_t usb_connected = 0;

	prntrStatus.errorStatus = 0;
	prntrStatus.paperEmptyStatus =  1;
	prntrStatus.selectStatus = 0;

	/* Output example information */
	console_example_info("USB Printer basic Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* USB printer driver initialization */
	printer_driver_initialize(&printer_driver_descriptors,
							  deviceID_String,
							  USB_DEVICE_PRINTER_DEVICE_ID_STRING_LENGTH );

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {
		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			if (usb_connected) {
				printf("-I- USB Disconnect/Suspend\n\r");
				usb_connected = 0;
			}
		} else {

			if (usb_connected == 0) {

				printf("-I- USB Connect\n\r");
				usb_connected = 1;
			}
			if (!usb_is_read_complete) {
				printer_driver_read(printer_read_buf,
									DATAPACKETSIZE,
									_usb_data_received,
									&usb_is_read_complete);
			}
		}
	}
}
/** \endcond */
