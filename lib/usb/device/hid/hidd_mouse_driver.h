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

/**\file
 *
 * \section Purpose
 *
 * Definition of methods for using a HID mouse device driver.
 *
 * \section Usage
 *
 * -# Re-implement the usbd_callbacks_request_received callback to forward
 *    requests to hidd_mouse_driver_request_handler. This is done
 *    automatically unless the NOAUTOCALLBACK symbol is defined during
 *    compilation.
 * -# Initialize the driver using hidd_mouse_driver_initialize. The
 *    USB driver is automatically initialized by this method.
 * -# Call the hidd_mouse_driver_change_points method when one or more
 *    keys are pressed/released.
 */

#ifndef HIDDKEYBOARDDRIVER_H
#define HIDDKEYBOARDDRIVER_H

/** \addtogroup usbd_hid_mouse
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/hid/hid_requests.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_mouse_button_bitmaps HID Mouse Button bitmaps
 *      @{
 * \section Bits
 * - HIDDMouse_LEFT_BUTTON
 * - HIDDMouse_RIGHT_BUTTON
 * - HIDDMouse_MIDDLE_BUTTON
 */

/** Left mouse button */
#define HIDDMouse_LEFT_BUTTON   (1 << 0)
/** Right mouse button */
#define HIDDMouse_RIGHT_BUTTON  (1 << 1)
/** Middle mouse button */
#define HIDDMouse_MIDDLE_BUTTON (1 << 2)
/**      @}*/

/** Size of the report descriptor in bytes. */
#define HIDDMouseDriver_REPORTDESCRIPTORSIZE              50

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/


/**
 * \typedef HIDDMouseDriverConfigurationDescriptors
 * \brief List of descriptors that make up the configuration descriptors of a
 *        device using the HID Mouse driver.
 */
typedef PACKED_STRUCT _HIDDMouseDriverConfigurationDescriptors {

	/** Configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Interface descriptor. */
	USBInterfaceDescriptor interface;
	/** HID descriptor. */
	HIDDescriptor1 hid;
	/** Interrupt IN endpoint descriptor. */
	USBEndpointDescriptor interruptIn;

} HIDDMouseDriverConfigurationDescriptors;

/**
 * \typedef HIDDMouseInputReport
 * \brief HID input report data struct used by the Mouse driver to notify the
 *        host of pressed keys.
 */
typedef PACKED_STRUCT _HIDDMouseInputReport {

	uint8_t bmButtons;          /**< Bitmap state of three mouse buttons. */
	int8_t  bX;                 /**< Pointer displacement along the X axis. */
	int8_t  bY;                 /**< Pointer displacement along the Y axis. */
} HIDDMouseInputReport; /* GCC */


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void hidd_mouse_driver_initialize(const USBDDriverDescriptors *pDescriptors);

extern void hidd_mouse_driver_configuration_changed_handler(uint8_t cfgnum);

extern void hidd_mouse_driver_request_handler(const USBGenericRequest *request);

extern uint8_t hidd_mouse_driver_change_points(uint8_t bmButtons,
											int8_t deltaX,
											int8_t deltaY);

extern void hidd_mouse_driver_remote_wakeup(void);

/**@}*/

#endif /*#ifndef HIDDKEYBOARDDRIVER_H */

