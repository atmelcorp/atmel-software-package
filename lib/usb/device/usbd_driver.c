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
 * \addtogroup usbd_interface
 *@{
 */

/*------------------------------------------------------------------------------
 *      Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

#include <string.h>

/*------------------------------------------------------------------------------
 *      Local types
 *------------------------------------------------------------------------------*/

/**
 * \typedef USBDDriver
 * \brief USB device driver structure, holding a list of descriptors identifying
 *        the device as well as the driver current state.
 */
typedef struct _USBDDriver {
	/** List of descriptors used by the device. */
	const USBDDriverDescriptors *pDescriptors;

	/** Current setting for each interface. */
	uint8_t *pInterfaces;

	/** Current configuration number (0 -> device is not configured). */
	uint8_t cfgnum;

	/** Indicates if remote wake up has been enabled by the host. */
	uint8_t isRemoteWakeUpEnabled;

	/** Features supported by OTG */
	uint8_t otg_features_supported;
} USBDDriver;

/*------------------------------------------------------------------------------
 *      Local variables
 *------------------------------------------------------------------------------*/

/** Default device driver instance, for all class drivers in USB Lib. */
static USBDDriver driver;

/*------------------------------------------------------------------------------
 *      Local functions
 *------------------------------------------------------------------------------*/

/**
 * Send a NULL packet
 */
static void terminate_ctrl_in_with_null(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Configures the device by setting it into the Configured state and
 * initializing all endpoints.
 * \param cfgnum  Configuration number to set.
 */
static void set_configuration(uint8_t cfgnum)
{
	USBEndpointDescriptor *endpoints[17];
	const USBConfigurationDescriptor *config;

	/* Use different descriptor depending on device speed */
	if (usbd_is_high_speed() &&
			driver.pDescriptors->pHsConfiguration) {
		config = driver.pDescriptors->pHsConfiguration;
	}
	else {
		config = driver.pDescriptors->pFsConfiguration;
	}

	/* Set & save the desired configuration */
	usbd_set_configuration(cfgnum);

	driver.cfgnum = cfgnum;
	driver.isRemoteWakeUpEnabled = (config->bmAttributes & 0x20) > 0;

	/* If the configuration is not 0, configure endpoints */
	if (cfgnum != 0) {
		/* Parse configuration to get endpoint descriptors */
		usb_configuration_descriptor_parse(config, 0, endpoints, 0);

		/* Configure endpoints */
		int i = 0;
		while (endpoints[i] != 0) {
			usbd_configure_endpoint(endpoints[i]);
			i++;
		}
	}

	/* Should be done before send the ZLP */
	usbd_driver_callbacks_configuration_changed(cfgnum);

	/* Acknowledge the request */
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Sends the current configuration number to the host.
 */
static void get_configuration(void)
{
	static uint8_t data;

	if( usbd_get_state() < USBD_STATE_CONFIGURED)
		data = 0; // If device is unconfigured, returned configuration must be 0
	else
		data = driver.cfgnum;

	usbd_write(0, &data, 1, NULL, NULL);
}

/**
 * Sends the current status of the device to the host.
 */
static void get_device_status(void)
{
	static uint16_t data;
	const USBConfigurationDescriptor *config;

	data = 0;

	/* Use different configuration depending on device speed */
	if (usbd_is_high_speed()) {
		config = driver.pDescriptors->pHsConfiguration;
	}
	else {
		config = driver.pDescriptors->pFsConfiguration;
	}

	/* Check current configuration for power mode (if device is configured) */
	if (driver.cfgnum != 0) {
		if (usb_configuration_descriptor_is_self_powered(config)) {
			data |= 1;
		}
	}

	/* Check if remote wake-up is enabled */
	if (driver.isRemoteWakeUpEnabled) {
		data |= 2;
	}

	/* Send the device status */
	usbd_write(0, &data, 2, NULL, NULL);
}

/**
 * Sends the current status of an endpoints to the USB host.
 * \param endpoint  Endpoint number.
 */
static void get_endpoint_status(uint8_t endpoint)
{
	static uint16_t data;

	data = 0;
	if (usbd_is_halted(endpoint))
		data = 1;

	/* Send the endpoint status */
	usbd_write(0, &data, 2, NULL, NULL);
}

/**
 * Sends the requested USB descriptor to the host if available, or STALLs  the
 * request.
 * \param type  Type of the requested descriptor
 * \param index  Index of the requested descriptor.
 * \param length  Maximum number of bytes to return.
 */
static void get_descriptor(uint8_t type, uint8_t index, uint32_t length)
{
	const USBDeviceDescriptor *device;
	const USBConfigurationDescriptor *config;
	const USBDeviceQualifierDescriptor *qualifier;
	const USBConfigurationDescriptor *other_speed;
	const USBGenericDescriptor **strings =
		(const USBGenericDescriptor **)driver.pDescriptors->pStrings;
	const USBGenericDescriptor *string;
	bool terminate_with_null = false;

	/* Use different set of descriptors depending on device speed */

	/* By default, use full speed */
	device = driver.pDescriptors->pFsDevice;
	config = driver.pDescriptors->pFsConfiguration;

	/* if HS, try HS values */
	if (usbd_is_high_speed()) {
		LIBUSB_TRACE("HS ");
		if (driver.pDescriptors->pHsDevice)
			device = driver.pDescriptors->pHsDevice;
		if (driver.pDescriptors->pHsConfiguration)
			config = driver.pDescriptors->pHsConfiguration;
		qualifier = driver.pDescriptors->pHsQualifier;
		other_speed = driver.pDescriptors->pHsOtherSpeed;
	}
	else {
		LIBUSB_TRACE("FS ");
		qualifier = driver.pDescriptors->pFsQualifier;
		other_speed = driver.pDescriptors->pFsOtherSpeed;
	}

	/* Check the descriptor type */
	switch (type) {
		case USBGenericDescriptor_DEVICE:
			LIBUSB_TRACE("Dev ");

			/* Adjust length and send descriptor */
			if (length > usb_generic_descriptor_get_length((USBGenericDescriptor*)device)) {
				length = usb_generic_descriptor_get_length((USBGenericDescriptor*)device);
			}
			usbd_write(0, device, length, NULL, NULL);
			break;

		case USBGenericDescriptor_CONFIGURATION:
			LIBUSB_TRACE("Cfg ");

			/* Adjust length and send descriptor */
			if (length > usb_configuration_descriptor_get_total_length(config)) {
				length = usb_configuration_descriptor_get_total_length(config);
				terminate_with_null = (length % device->bMaxPacketSize0) == 0;
			}
			usbd_write(0, config, length,
					terminate_with_null ? terminate_ctrl_in_with_null : NULL, NULL);
			break;

		case USBGenericDescriptor_DEVICEQUALIFIER:
			LIBUSB_TRACE("Qua ");

			/* Check if descriptor exists */
			if (!qualifier) {
				usbd_stall(0);
			} else {
				/* Adjust length and send descriptor */
				if (length > usb_generic_descriptor_get_length((USBGenericDescriptor*)qualifier)) {
					length = usb_generic_descriptor_get_length((USBGenericDescriptor*)qualifier);
				}
				usbd_write(0, qualifier, length, NULL, NULL);
			}
			break;

		case USBGenericDescriptor_OTHERSPEEDCONFIGURATION:
			LIBUSB_TRACE("OSC ");

			/* Check if descriptor exists */
			if (!other_speed) {
				usbd_stall(0);
			} else {
				/* Adjust length and send descriptor */
				if (length > usb_configuration_descriptor_get_total_length(other_speed)) {
					length = usb_configuration_descriptor_get_total_length(other_speed);
					terminate_with_null = (length % device->bMaxPacketSize0) == 0;
				}
				usbd_write(0, other_speed, length,
						terminate_with_null ? terminate_ctrl_in_with_null : NULL, NULL);
			}
			break;

		case USBGenericDescriptor_STRING:
			LIBUSB_TRACE("Str%d ", index);

			/* Check if descriptor exists */
			if (index >= driver.pDescriptors->numStrings) {
				usbd_stall(0);
			} else {
				string = strings[index];

				/* Adjust length and send descriptor */
				if (length > usb_generic_descriptor_get_length(string)) {
					length = usb_generic_descriptor_get_length(string);
					terminate_with_null = (length % device->bMaxPacketSize0) == 0;
				}
				usbd_write(0, string, length,
						terminate_with_null ? terminate_ctrl_in_with_null : NULL, NULL);
			}
			break;

		default:
			trace_warning("USBDDriver_GetDescriptor: Unknown descriptor type (%d)\n\r", type);
			usbd_stall(0);
	}
}

/**
 * Sets the active setting of the given interface if the configuration supports
 * it; otherwise, the control pipe is STALLed. If the setting of an interface
 * changes.
 * \parma infnum  Interface number.
 * \parma setting  New active setting for the interface.
 */
static void set_interface(uint8_t infnum, uint8_t setting)
{
	/* Make sure alternate settings are supported */
	if (!driver.pInterfaces) {
		usbd_stall(0);
	} else {
		/* Change the current setting of the interface and trigger the callback */
		/* if necessary */
		if (driver.pInterfaces[infnum] != setting) {
			driver.pInterfaces[infnum] = setting;
			usbd_driver_callbacks_interface_setting_changed(infnum, setting);
		}

		/* Acknowledge the request */
		usbd_write(0, NULL, 0, NULL, NULL);
	}
}

/**
 * Sends the currently active setting of the given interface to the USB
 * host. If alternate settings are not supported, this function STALLs the
 * control pipe.
 * \param infnum  Interface number.
 */
static void get_interface(uint8_t infnum)
{
	/* Make sure alternate settings are supported, or STALL the control pipe */
	if (!driver.pInterfaces) {
		usbd_stall(0);
	}
	else {
		/* Sends the current interface setting to the host */
		usbd_write(0, &driver.pInterfaces[infnum], 1, NULL, NULL);
	}
}

/**
 * Performs the selected test on the USB device (high-speed only).
 * \param test  Test selector value.
 */
static void usbd_driver_test(uint8_t test)
{
	/* the lower byte of wIndex must be zero
	   the most significant byte of wIndex is used to specify the specific test mode */

	switch (test) {
		case USBFeatureRequest_TESTPACKET:
			/*Test mode Test_Packet: */
			/*Upon command, a port must repetitively transmit the following test packet until */
			/*the exit action is taken. This enables the testing of rise and fall times, eye */
			/*patterns, jitter, and any other dynamic waveform specifications. */
			/*The test packet is made up by concatenating the following strings. */
			/*(Note: For J/K NRZI data, and for NRZ data, the bit on the left is the first one */
			/*transmitted. “S?indicates that a bit stuff occurs, which inserts an “extra?NRZI data bit. */
			/*? N?is used to indicate N occurrences of a string of bits or symbols.) */
			/*A port in Test_Packet mode must send this packet repetitively. The inter-packet timing */
			/*must be no less than the minimum allowable inter-packet gap as defined in Section 7.1.18 and */
			/*no greater than 125 us. */

			/* Send ZLP */
			usbd_test(USBFeatureRequest_TESTSENDZLP);
			/* Tst PACKET */
			usbd_test(USBFeatureRequest_TESTPACKET);
			while (1);
			/*break; not reached */


		case USBFeatureRequest_TESTJ:
			/*Test mode Test_J: */
			/*Upon command, a port’s transceiver must enter the high-speed J state and remain in that */
			/*state until the exit action is taken. This enables the testing of the high output drive */
			/*level on the D+ line. */

			/* Send ZLP */
			usbd_test(USBFeatureRequest_TESTSENDZLP);
			/* Tst J */
			usbd_test(USBFeatureRequest_TESTJ);
			while (1);
			/*break; not reached */


		case USBFeatureRequest_TESTK:
			/*Test mode Test_K: */
			/*Upon command, a port’s transceiver must enter the high-speed K state and remain in */
			/*that state until the exit action is taken. This enables the testing of the high output drive */
			/*level on the D- line. */

			/* Send a ZLP */
			usbd_test(USBFeatureRequest_TESTSENDZLP);
			usbd_test(USBFeatureRequest_TESTK);
			while (1);
			/*break; not reached */


		case USBFeatureRequest_TESTSE0NAK:
			/*Test mode Test_SE0_NAK: */
			/*Upon command, a port transceiver must enter the high-speed receive mode */
			/*and remain in that mode until the exit action is taken. This enables the testing */
			/*of output impedance, low level output voltage, and loading characteristics. */
			/*In addition, while in this mode, upstream facing ports (and only upstream facing ports) */
			/*must respond to any IN token packet with a NAK handshake (only if the packet CRC is */
			/*determined to be correct) within the normal allowed device response time. This enables testing of */
			/*the device squelch level circuitry and, additionally, provides a general purpose stimulus/response */
			/*test for basic functional testing. */

			/* Send a ZLP */
			usbd_test(USBFeatureRequest_TESTSENDZLP);
			/* Test SE0_NAK */
			usbd_test(USBFeatureRequest_TESTSE0NAK);
			while (1);
			/*break; not reached */


		default:
			usbd_stall(0);
			break;

	}
	/* The exit action is to power cycle the device. */
	/* The device must be disconnected from the host */
}

static void usbd_set_address_callback(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining)
{
	/* unused */
	(void)status;
	(void)transferred;
	(void)remaining;

	/* TODO void* -> uint8_t cast is ugly */
	usbd_set_address((uint8_t)(uint32_t)arg);
}

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes a USBDDriver instance with a list of descriptors. If
 * interfaces can have multiple alternate settings, an array to store the
 * current setting for each interface must be provided.
 * \param driver  Pointer to a USBDDriver instance.
 * \param descriptors  Pointer to a USBDDriverDescriptors instance.
 * \param interfaces  Pointer to an array for storing the current alternate
 *                     setting of each interface (optional).
 */
void usbd_driver_initialize(const USBDDriverDescriptors *descriptors, uint8_t *interfaces, uint32_t size)
{
	driver.cfgnum = 0;
	driver.isRemoteWakeUpEnabled = 0;
	driver.pDescriptors = descriptors;
	driver.pInterfaces = interfaces;

	/* Initialize interfaces array if not null */
	if (interfaces != NULL)
		memset(interfaces, 0, size);
}

const USBDDriverDescriptors *usbd_driver_get_descriptors(void)
{
	return driver.pDescriptors;
}

/**
 * Returns configuration descriptor list.
 * \param cfgNum   Reserved.
 */
USBConfigurationDescriptor *usbd_driver_get_cfg_descriptors(uint8_t cfgnum)
{
	USBDDriverDescriptors *desc = (USBDDriverDescriptors*)driver.pDescriptors;
	USBConfigurationDescriptor *cfg;

	if (usbd_is_high_speed() && desc->pHsConfiguration)
		cfg = (USBConfigurationDescriptor*)desc->pHsConfiguration;
	else
		cfg = (USBConfigurationDescriptor*)desc->pFsConfiguration;

	return cfg;
}

/**
 * Handles the given request if it is standard, otherwise STALLs it.
 * \param request Pointer to a USBGenericRequest instance.
 */
void usbd_driver_request_handler(const USBGenericRequest *request)
{
	uint8_t cfgnum;
	uint8_t infnum;
	uint8_t eptnum;
	uint8_t setting;
	uint8_t type;
	uint8_t index_desc;
	uint32_t length;
	uint32_t address;

	LIBUSB_TRACE("Std ");

	/* Check request code */
	switch (usb_generic_request_get_request(request)) {
		case USBGenericRequest_GETDESCRIPTOR:
			LIBUSB_TRACE("gDesc ");

			/* Send the requested descriptor */
			type = usb_get_descriptor_request_get_descriptor_type(request);
			index_desc = usb_get_descriptor_request_get_descriptor_index(request);
			length = usb_generic_request_get_length(request);
			get_descriptor(type, index_desc, length);
			break;

		case USBGenericRequest_SETADDRESS:
			LIBUSB_TRACE("sAddr ");

			/* Sends a zero-length packet and then set the device address */
			address = usb_set_address_request_get_address(request);
			usbd_write(0, NULL, 0, usbd_set_address_callback, (void*)address);
			break;

		case USBGenericRequest_SETCONFIGURATION:
			LIBUSB_TRACE("sCfg ");

			/* Set the requested configuration */
			cfgnum = usb_set_configuration_request_get_configuration(request);
			set_configuration(cfgnum);
			break;

		case USBGenericRequest_GETCONFIGURATION:
			LIBUSB_TRACE("gCfg ");

			/* Send the current configuration number */
			get_configuration();
			break;

		case USBGenericRequest_GETSTATUS:
			LIBUSB_TRACE("gSta ");

			/* Check who is the recipient */
			switch (usb_generic_request_get_recipient(request)) {
				case USBGenericRequest_DEVICE:
					LIBUSB_TRACE("Dev ");

					/* Send the device status */
					get_device_status();
					break;

				case USBGenericRequest_ENDPOINT:
					LIBUSB_TRACE("Ept ");

					/* Send the endpoint status */
					eptnum = usb_generic_request_get_endpoint_number(request);
					get_endpoint_status(eptnum);
					break;

				default:
					trace_warning("usbd_driver_request_handler: Unknown recipient (%d)\n\r",
							usb_generic_request_get_recipient(request));
					usbd_stall(0);
					break;
			}
			break;

		case USBGenericRequest_CLEARFEATURE:
			LIBUSB_TRACE("cFeat ");

			/* Check which is the requested feature */
			switch (usb_feature_request_get_feature_selector(request)) {
				case USBFeatureRequest_ENDPOINTHALT:
					LIBUSB_TRACE("Hlt ");

					/* Unhalt endpoint and send a zero-length packet */
					usbd_unhalt(usb_generic_request_get_endpoint_number(request));
					usbd_write(0, NULL, 0, NULL, NULL);
					break;

				case USBFeatureRequest_DEVICEREMOTEWAKEUP:
					LIBUSB_TRACE("RmWU ");

					/* Disable remote wake-up and send a zero-length packet */
					driver.isRemoteWakeUpEnabled = 0;
					usbd_write(0, NULL, 0, NULL, NULL);
					break;

				default:
					trace_warning("usbd_driver_request_handler: Unknown feature selector (%d)\n\r",
							usb_feature_request_get_feature_selector(request));
					usbd_stall(0);
					break;
			}
			break;

	case USBGenericRequest_SETFEATURE:
		LIBUSB_TRACE("sFeat ");

		/* Check which is the selected feature */
		switch (usb_feature_request_get_feature_selector(request)) {
			case USBFeatureRequest_DEVICEREMOTEWAKEUP:
				LIBUSB_TRACE("RmWU ");

				/* Enable remote wake-up and send a ZLP */
				driver.isRemoteWakeUpEnabled = 1;
				usbd_write(0, NULL, 0, NULL, NULL);
				break;

			case USBFeatureRequest_ENDPOINTHALT:
				LIBUSB_TRACE("Halt ");

				/* Halt endpoint */
				usbd_halt(usb_generic_request_get_endpoint_number(request));
				usbd_write(0, NULL, 0, NULL, NULL);
				break;

			case USBFeatureRequest_TESTMODE:
				/* 7.1.20 Test Mode Support, 9.4.9 Set Feature */
				if (usb_generic_request_get_recipient(request) == USBGenericRequest_DEVICE
					&& (usb_generic_request_get_index(request) & 0x000f) == 0) {
					/* Handle test request */
					usbd_driver_test(usb_feature_request_get_test_selector(request));
				} else {
					usbd_stall(0);
				}
				break;

#if defined USB_OTG_REQUEST
			case USBFeatureRequest_OTG_B_HNP_ENABLE:
				LIBUSB_TRACE("OTG_B_HNP_ENABLE ");
				driver.otg_features_supported |=
					1 << USBFeatureRequest_OTG_B_HNP_ENABLE;
				usbd_write(0, NULL, 0, NULL, NULL);
				break;
			case USBFeatureRequest_OTG_A_HNP_SUPPORT:
				LIBUSB_TRACE("OTG_A_HNP_SUPPORT ");
				driver.otg_features_supported |=
					1 << USBFeatureRequest_OTG_A_HNP_SUPPORT;
				usbd_write(0, NULL, 0, NULL, NULL);
				break;
			case USBFeatureRequest_OTG_A_ALT_HNP_SUPPORT:
				LIBUSB_TRACE("OTG_A_ALT_HNP_SUPPORT ");
				driver.otg_features_supported |=
					1 << USBFeatureRequest_OTG_A_ALT_HNP_SUPPORT;
				usbd_write(0, NULL, 0, NULL, NULL);
				break;
#endif
			default:
				trace_warning("usbd_driver_request_handler: Unknown feature selector (%d)\n\r",
						usb_feature_request_get_feature_selector(request));
				usbd_stall(0);
				break;
		}
		break;

	case USBGenericRequest_SETINTERFACE:
		infnum = usb_interface_request_get_interface(request);
		setting = usb_interface_request_get_alternate_setting(request);
		LIBUSB_TRACE("sIntf%d,%d ", infnum, setting);
		set_interface(infnum, setting);
		break;

	case USBGenericRequest_GETINTERFACE:
		infnum = usb_interface_request_get_interface(request);
		LIBUSB_TRACE("gIntf%d ", infnum);
		get_interface(infnum);
		break;

	default:
		trace_warning("usbd_driver_request_handler: Unknown request code (%d)\n\r",
				usb_generic_request_get_request(request));
		usbd_stall(0);
	}
}


/**
 * Test if RemoteWakeUP feature is enabled
 * \return true if remote wake up has been enabled by the host; otherwise,
 * returns false
 */
bool usbd_driver_is_remote_wakeup_enabled(void)
{
	return driver.isRemoteWakeUpEnabled;
}

/**
 * Return OTG features supported
 * \return the OTG features
 */
uint8_t usbd_driver_return_otg_features(void)
{
	return driver.otg_features_supported;
}

/**
 * Clear OTG features supported
 * \return none
 */
void usbd_driver_clear_otg_features(void)
{
	driver.otg_features_supported = 0;
}

/**@}*/
