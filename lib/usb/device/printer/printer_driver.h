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
#ifndef PRINTERDRIVER_H
#define PRINTERDRIVER_H

/** \addtogroup usbd_printer
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/printer/printer_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/printer/printer_driver.h"
#include "usb/device/usbd.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/
typedef struct _printer_instance {
	/** USB interrupt IN EP */
	uint8_t bPipeIn;
	/** USB interrupt OUT EP */
	uint8_t bPipeOut;
} printer_instance;

/**
 * \typedef PRINTERDriverConfigurationDescriptors
 * \brief List of descriptors that make up the configuration descriptors of a
 *        device using the USB printer driver.
 */
typedef PACKED_STRUCT _PRINTERDriverConfigurationDescriptors {

	/** Configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Interface descriptor. */
	USBInterfaceDescriptor interface;
	/** Interrupt OUT endpoint descriptor. */
	USBEndpointDescriptor interruptOut;

} PRINTERDriverConfigurationDescriptors;


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void printer_driver_initialize(const USBDDriverDescriptors *pDescriptors, 
									  uint8_t * string,
									  uint8_t len);
extern void printer_driver_request_handler(const USBGenericRequest *request);

extern void printet_driver_get_port_status(uint8_t* status);

extern void printer_driver_configuration_change_handler(uint8_t cfgnum);

extern uint32_t printer_driver_read(void *data,
									uint32_t length,
									usbd_xfer_cb_t callback,
									void *callback_arg);
/**@}*/

#endif /*#ifndef PRINTERDRIVER_H */

