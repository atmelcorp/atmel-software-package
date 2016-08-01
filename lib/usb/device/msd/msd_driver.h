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
 * \section Purpose
 *
 * Mass storage %device driver implementation.
 *
 * \section Usage
 *
 * -# Enable and setup USB related pins (see pio & board.h).
 * -# Configure the memory interfaces used for Mass Storage LUNs
 *    (see memories, MSDLun.h).
 * -# Instance the USB device configure descriptor as
 *    MSDConfigurationDescriptors or MSDConfigurationDescriptorsOTG defined.
 *    Interface number should be 0.
 * -# Configure the USB MSD %driver using msd_driver_initialize.
 * -# Invoke msd_driver_state_machine in main loop to handle all Mass Storage
 *    operations.
 */

#ifndef MSDDRIVER_H
#define MSDDRIVER_H

/** \addtogroup usbd_msd
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#include "compiler.h"

#include "usb/device/msd/msdd_state_machine.h"
#include "usb/device/msd/msd_function.h"
#include "usb/device/msd/msd.h"
#include "usb/device/msd/msd_lun.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/


/**
 * \typedef MSDConfigurationDescriptors
 * \brief List of configuration descriptors used by a Mass Storage device driver.
 */
typedef PACKED_STRUCT _MSDConfigurationDescriptors {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Mass storage interface descriptor. */
	USBInterfaceDescriptor interface;
	/** Bulk-out endpoint descriptor. */
	USBEndpointDescriptor bulkOut;
	/** Bulk-in endpoint descriptor. */
	USBEndpointDescriptor bulkIn;

} MSDConfigurationDescriptors;

/**
 * \typedef MSDConfigurationDescriptorsOTG
 * \brief List of configuration descriptors used by a
 *        Mass Storage device driver, with OTG support.
 */
typedef PACKED_STRUCT _MSDConfigurationDescriptorsOTG {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/* OTG descriptor */
	USBOtgDescriptor otgDescriptor;
	/** Mass storage interface descriptor. */
	USBInterfaceDescriptor interface;
	/** Bulk-out endpoint descriptor. */
	USBEndpointDescriptor bulkOut;
	/** Bulk-in endpoint descriptor. */
	USBEndpointDescriptor bulkIn;

} MSDConfigurationDescriptorsOTG;


/*------------------------------------------------------------------------------
 *      Global functions
 *------------------------------------------------------------------------------*/

extern void msd_driver_initialize(const USBDDriverDescriptors *descriptors,
		MSDLun *luns, uint8_t num_luns);

extern void msd_driver_request_handler(
		const USBGenericRequest *request);

extern void msd_driver_configuration_change_handler(
		uint8_t cfgnum);

/**
 * State machine for the MSD driver
 * \param  pMsdDriver  Pointer to MSDDriver instance.
 */
static inline void msd_driver_state_machine(void)
{
	msd_function_state_machine();
}

/**@}*/

#endif /* #ifndef MSDDRIVER_H */

