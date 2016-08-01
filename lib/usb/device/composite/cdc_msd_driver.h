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
 * \file
 *
 * \section Purpose
 *
 *   Definitions and methods for USB CDCMSD device implement.
 *
 * \section Usage
 *
 * -# Initialize USB function specified driver ( for MSD currently )
 *  - MSDDFunctionDriver_Initialize
 *
 * -# Initialize USB CDCMSD driver and USB driver
 *  - CDCMSDDDriver_Initialize
 *
 * -# Handle and dispatch USB requests
 *  - CDCMSDDDriver_RequestHandler
 *
 * -# Try starting a remote wake-up sequence
 *  - CDCMSDDDriver_RemoteWakeUp
 */

#ifndef CDCMSDDDRIVER_H
#define CDCMSDDDRIVER_H
/** \addtogroup usbd_composite_cdcmsd
 *@{
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/cdc/cdc_descriptors.h"
#include "usb/common/msd/msd_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/msd/msd_lun.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_driver.h"

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

/** \addtogroup usbd_cdc_msd_desc USB CDC(Serial) + MS Descriptors define
 *      @{
 */
/** Number of interfaces of the device */
#define CDCMSDDriverDescriptors_NUMINTERFACE       3
/** Number of the CDC interface. */
#define CDCMSDDriverDescriptors_CDC_INTERFACE      0
/** Number of the HID interface. */
#define CDCMSDDriverDescriptors_MSD_INTERFACE      2
/**     @}*/


/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/


/**
 * \typedef CDCMSDDriverConfigurationDescriptors
 * \brief Configuration descriptor list for a device implementing
 *        a CDCMSD driver.
 */
typedef PACKED_STRUCT _CDCMSDDriverConfigurationDescriptors {

	/**  Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;

	/*  --- CDC 0 */
	/**  IAD 0 */
	USBInterfaceAssociationDescriptor cdcIAD0;
	/**  Communication interface descriptor */
	USBInterfaceDescriptor cdcCommunication0;
	/**  CDC header functional descriptor. */
	CDCHeaderDescriptor cdcHeader0;
	/**  CDC call management functional descriptor. */
	CDCCallManagementDescriptor cdcCallManagement0;
	/**  CDC abstract control management functional descriptor. */
	CDCAbstractControlManagementDescriptor cdcAbstractControlManagement0;
	/**  CDC union functional descriptor (with one slave interface). */
	CDCUnionDescriptor cdcUnion0;
	/**  Notification endpoint descriptor. */
	USBEndpointDescriptor cdcNotification0;
	/**  Data interface descriptor. */
	USBInterfaceDescriptor cdcData0;
	/**  Data OUT endpoint descriptor. */
	USBEndpointDescriptor cdcDataOut0;
	/**  Data IN endpoint descriptor. */
	USBEndpointDescriptor cdcDataIn0;

	/*  --- MSD */
	/**  Mass storage interface descriptor. */
	USBInterfaceDescriptor msdInterface;
	/**  Bulk-out endpoint descriptor. */
	USBEndpointDescriptor msdBulkOut;
	/**  Bulk-in endpoint descriptor. */
	USBEndpointDescriptor msdBulkIn;

} CDCMSDDriverConfigurationDescriptors;


/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/* -CDCMSD */
extern void cdc_msd_driver_initialize(
	const USBDDriverDescriptors *pDescriptors,
	MSDLun *pLuns, unsigned char numLuns);

extern void cdc_msd_driver_configuration_changed_handler(unsigned char cfgnum);

extern void cdc_msd_driver_request_handler(const USBGenericRequest *request);

/**@}*/
#endif /* #ifndef CDCMSDDDRIVER_H */

