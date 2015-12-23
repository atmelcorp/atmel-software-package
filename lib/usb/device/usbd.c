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

/** \file
 *
 *  \section Purpose
 *
 *  Implementation of USB device functions on a UDP controller.
 *
 *  See \ref usbd_api "USBD API Methods".
 */

/** \addtogroup usbd_interface
 *@{
 */

/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/

/** Device current state. */
static volatile uint8_t device_state;

/** Indicates the previous device state */
static volatile uint8_t previous_device_state;

/*---------------------------------------------------------------------------
 *      Internal Functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *      Exported functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *      USBD: Event handlers
 *---------------------------------------------------------------------------*/

/**
 *  Handle the USB suspend event, should be invoked whenever
 *  HW reports a suspend signal.
 */
void usbd_suspend_handler(void)
{
	/* Don't do anything if the device is already suspended */
	if (device_state != USBD_STATE_SUSPENDED) {
		/* Switch to the Suspended state */
		previous_device_state = device_state;
		device_state = USBD_STATE_SUSPENDED;

		/* Suspend HW interface */
		usbd_hal_suspend();

		/* Invoke the User Suspended callback (Suspend System?) */
		usbd_callbacks_suspended();
	}
}

/**
 *  Handle the USB resume event, should be invoked whenever
 *  HW reports a resume signal.
 */
void usbd_resume_handler(void)
{
	/* Don't do anything if the device was not suspended */
	if (device_state == USBD_STATE_SUSPENDED) {
		/* Active the device */
		usbd_hal_activate();

		device_state = previous_device_state;
		if (device_state >= USBD_STATE_DEFAULT) {
			/* Invoke the Resume callback */
			usbd_callbacks_resumed();
		}
	}
}

/**
 *  Handle the USB reset event, should be invoked whenever
 *  HW found USB reset signal on bus, which usually is called
 *  "end of bus reset" status.
 */
void usbd_reset_handler(void)
{
	/* The device enters the Default state */
	device_state = USBD_STATE_DEFAULT;

	/* Active the USB HW */
	usbd_hal_activate();

	/* Only EP0 enabled */
	usbd_hal_reset_endpoints(0xFFFFFFFF, USBD_STATUS_RESET, 0);
	usbd_configure_endpoint(0);

	/* Invoke the Reset callback */
	usbd_callbacks_reset();
}

/**
 *  Handle the USB setup package received, should be invoked
 *  when an endpoint got a setup package as request.
 *  \param endpoint Endpoint number.
 *  \param request  Pointer to content of request.
 */
void usbd_request_handler(uint8_t endpoint, const USBGenericRequest* request)
{
	if (endpoint != 0) {
		trace_warning("EP%d request not supported, default EP only",
				endpoint);
	}
	else {
		usbd_callbacks_request_received(request);
	}
}

/*---------------------------------------------------------------------------
 *      USBD: Library interface
 *---------------------------------------------------------------------------*/

/**
 * Configures an endpoint according to its Endpoint Descriptor.
 * \param descriptor Pointer to an Endpoint descriptor.
 */
void usbd_configure_endpoint(const USBEndpointDescriptor *descriptor)
{
	usbd_hal_configure(descriptor);
}

/**
 * Sends data through a USB endpoint. Sets up the transfer descriptor,
 * writes one or two data payloads (depending on the number of FIFO bank
 * for the endpoint) and then starts the actual transfer. The operation is
 * complete when all the data has been sent.
 *
 * *If the size of the buffer is greater than the size of the endpoint
 *  (or twice the size if the endpoint has two FIFO banks), then the buffer
 *  must be kept allocated until the transfer is finished*. This means that
 *  it is not possible to declare it on the stack (i.e. as a local variable
 *  of a function which returns after starting a transfer).
 *
 * \param endpoint Endpoint number.
 * \param data Pointer to a buffer with the data to send.
 * \param length Size of the data buffer.
 * \param callback Optional callback function to invoke when the transfer is
 *        complete.
 * \param callback_arg Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the transfer has been started;
 *         otherwise, the corresponding error status code.
 */
uint8_t usbd_write(uint8_t endpoint, const void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	usbd_hal_set_transfer_callback(endpoint, callback, callback_arg);
	return usbd_hal_write(endpoint, data, length);
}

/**
 * Get the size of data is available for read or write
 * \param ep Endpoint number
 * \return size of data available
 */
uint16_t usbd_get_data_size(uint8_t endpoint)
{
	 return usbd_hal_get_data_size(endpoint);
}

/**
 * Reads incoming data on an USB endpoint This methods sets the transfer
 * descriptor and activate the endpoint interrupt. The actual transfer is
 * then carried out by the endpoint interrupt handler. The Read operation
 * finishes either when the buffer is full, or a short packet (inferior to
 * endpoint maximum  size) is received.
 *
 * *The buffer must be kept allocated until the transfer is finished*.
 * \param endpoint Endpoint number.
 * \param data Pointer to a data buffer.
 * \param length Size of the data buffer in bytes.
 * \param callback Optional end-of-transfer callback function.
 * \param callback_arg Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started;
 *         otherwise, the corresponding error code.
 */
uint8_t usbd_read(uint8_t endpoint, void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	usbd_hal_set_transfer_callback(endpoint, callback, callback_arg);
	return usbd_hal_read(endpoint, data, length);
}

/**
 * Sets the HALT feature on the given endpoint (if not already in this state).
 * \param b_endpoint Endpoint number.
 */
void usbd_halt(uint8_t endpoint)
{
	usbd_hal_halt(endpoint);
}

/**
 * Clears the Halt feature on the given endpoint.
 * \param b_endpoint Index of endpoint
 */
void usbd_unhalt(uint8_t endpoint)
{
	usbd_hal_unhalt(endpoint);
}

/**
 * Returns the current Halt status of an endpoint.
 * \param endpoint Index of endpoint
 * \return true if the endpoint is currently halted; otherwise false
 */
bool usbd_is_halted(uint8_t endpoint)
{
	return usbd_hal_is_halted(endpoint);
}

/**
 * Indicates if the device is running in high or full-speed. Always returns 0
 * since UDP does not support high-speed mode.
 */
bool usbd_is_high_speed(void)
{
	return usbd_hal_is_high_speed();
}

/**
 * Causes the given endpoint to acknowledge the next packet it receives
 * with a STALL handshake.
 * \param b_endpoint Endpoint number.
 * \return USBD_STATUS_SUCCESS or USBD_STATUS_LOCKED.
 */
uint8_t usbd_stall(uint8_t b_endpoint)
{
	LIBUSB_TRACE("Stall(%d) ", b_endpoint);
	return usbd_hal_stall(b_endpoint);
}

/**
 * Sets the device address to the given value.
 * \param address New device address.
 */
void usbd_set_address(uint8_t address)
{
	LIBUSB_TRACE("SetAddr(%d) ", address);

	usbd_hal_set_address(address);

	if (address == 0)
		device_state = USBD_STATE_DEFAULT;
	else
		device_state = USBD_STATE_ADDRESS;
}

/**
 * Sets the current device configuration.
 * \param cfgnum - Configuration number to set.
 */
void usbd_set_configuration(uint8_t cfgnum)
{
	LIBUSB_TRACE("SetCfg(%d) ", cfgnum);

	usbd_hal_set_configuration(cfgnum);

	if (cfgnum != 0) {
		device_state = USBD_STATE_CONFIGURED;
	} else {
		device_state = USBD_STATE_ADDRESS;

		/* Reset all endpoints but Control 0 */
		usbd_hal_reset_endpoints(0xFFFFFFFE, USBD_STATUS_RESET, 0);
	}
}

/**
 * Starts a remote wake-up procedure.
 */
void usbd_remote_wakeup(void)
{
	/* Device is NOT suspended */
	if (device_state != USBD_STATE_SUSPENDED) {

		trace_warning("usbd_remote_wakeup: Device is not suspended\n\r");
		return;
	}

	usbd_hal_activate();
	usbd_hal_remote_wakeup();
}

/**
 * Connects the pull-up on the D+ line of the USB.
 */
void usbd_connect(void)
{
	LIBUSB_TRACE("Connect ");
	usbd_hal_connect();
}

/**
 * Disconnects the pull-up from the D+ line of the USB.
 */
void usbd_disconnect(void)
{
	LIBUSB_TRACE("Disconnect ");
	usbd_hal_disconnect();

	/* Device returns to the Powered state */
	if (device_state > USBD_STATE_POWERED) {
		device_state = USBD_STATE_POWERED;
	}
	if (previous_device_state > USBD_STATE_POWERED) {
		previous_device_state = USBD_STATE_POWERED;
	}
}

/**
 * Force the device to Full-Speed mode
 */
void usbd_force_full_speed(void)
{
	usbd_hal_force_full_speed();
}

/**
 * Initializes the USB driver.
 */
void usbd_init(void)
{
	/* HW Layer Initialize */
	usbd_hal_init();

	/* Device is in the Attached state */
	device_state = USBD_STATE_SUSPENDED;
	previous_device_state = USBD_STATE_POWERED;

	/* Upper Layer Initialize */
	usbd_callbacks_initialized();
}

/**
 * Returns the current state of the USB device.
 * \return Device current state.
 */
uint8_t usbd_get_state(void)
{
	return device_state;
}

/**
 * Certification test for High Speed device.
 * \param index Test to be done
 */
void usbd_test(uint8_t index)
{
	usbd_hal_test(index);
}

/**@}*/
