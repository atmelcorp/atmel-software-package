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
 * \section Purpose
 *
 *   Definitions and methods for USB HID + MSD device implement.
 *
 * \section Usage
 *
 * -# Initialize USB function specified driver ( for MSD currently )
 *  - MSDDFunctionDriver_Initialize()
 *
 * -# Initialize USB HIDMSD driver and USB driver
 *  - HIDMSDDDriver_Initialize()
 *
 * -# Handle and dispatch USB requests
 *  - HIDMSDDDriver_RequestHandler()
 *
 * -# Try starting a remote wake-up sequence
 *  - HIDMSDDDriver_RemoteWakeUp()
 */

#ifndef HIDMSDDDRIVER_H
#define HIDMSDDDRIVER_H

/** \addtogroup usbd_composite_hidmsd
 *@{
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/msd/msd_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/msd/msd_lun.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_msd_desc USB HID(Kbd) + MSD Descriptors define
 *      @{
 */
/** Number of interfaces of the device */
#define HIDMSDDriverDescriptors_NUMINTERFACE       2
/** Number of the HID (Keyboard) interface. */
#define HIDMSDDriverDescriptors_HID_INTERFACE      0
/** Number of the MSD interface. */
#define HIDMSDDriverDescriptors_MSD_INTERFACE      1
/**     @}*/

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/


/**
 * \typedef HidMsdDriverConfigurationDescriptors
 * \brief Configuration descriptor list for a device implementing a
 *        HID MSD composite driver.
 */
typedef PACKED_STRUCT _HidMsdDriverConfigurationDescriptors {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;

	/* --- HID */
	USBInterfaceDescriptor hidInterface;
	HIDDescriptor1 hid;
	USBEndpointDescriptor hidInterruptIn;
	USBEndpointDescriptor hidInterruptOut;

	/* --- MSD */
	/** Mass storage interface descriptor. */
	USBInterfaceDescriptor msdInterface;
	/** Bulk-out endpoint descriptor. */
	USBEndpointDescriptor msdBulkOut;
	/** Bulk-in endpoint descriptor. */
	USBEndpointDescriptor msdBulkIn;

} HidMsdDriverConfigurationDescriptors;

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/* -HIDMSD Composite device */
extern void hid_msdd_driver_initialize(
	const USBDDriverDescriptors *pDescriptors,
	MSDLun *pLuns, uint8_t numLuns);

extern void hid_msdd_driver_configuration_changed_handler(uint8_t cfgnum);

extern void hid_msdd_driver_request_handler(const USBGenericRequest *request);

extern void hid_msdd_driver_remote_wakeup(void);

/**@}*/
#endif //#ifndef HIDMSDDDRIVER_H

