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

/** \file
 *
 *  Definitions and classes for USB PRINTER class descriptors.
 */

#ifndef _PRINTERDESCRIPTORS_H_
#define _PRINTERDESCRIPTORS_H_
/** \addtogroup usb_PRINTER
 *@{
 */

/*----------------------------------------------------------------------------
 *         Includes
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "compiler.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup usb_PRINTER_descriptor USB PRINTER Device Descriptor Values
 *  @{
 * This section lists the values for PRINTER Device Descriptor.
 * - \ref PRINTERDeviceDescriptor_CLASS
 * - \ref PRINTERDeviceDescriptor_SUBCLASS
 * - \ref PRINTERDeviceDescriptor_PROTOCOL
 */
/** Device class code when using the PRINTER class. */
#define PRINTERDeviceDescriptor_CLASS               0x07
/** Device subclass code when using the PRINTER class. */
#define PRINTERDeviceDescriptor_SUBCLASS            0x01

/* Printer Interface Type */
/* 
 * 0x01 - Unidirectional interface
 * 0x02 - Bi-directional interface
 * 0x03 - 1284.4 compatible bi-directional interface
 */
/** Device protocol code when using the PRINTER class. */
#define PRINTERDeviceDescriptor_PROTOCOL            0x01

#define USB_PRINTER_INTERFACE_PROTOCOL              0x01

 /* class-specific request returns a device ID string that is compatible with
     * IEEE 1284 */
#define USB_PRINTER_GET_DEVICE_ID                   0x0
    /* class-specific request returns the printers current status */
#define USB_PRINTER_GET_PORT_STATUS                 0x01
    /* class-specific request flushes all buffers and resets the Bulk endpoints 
     * to their default states */
#define USB_PRINTER_SOFT_RESET                      0x02
/* bmRequestType for Printer class specific request */
#define USB_PRINTER_REQUEST_CLASS_SPECIFIC          0x21

/** @}*/

/*----------------------------------------------------------------------------
 *         Functions
 *----------------------------------------------------------------------------*/


/**@}*/
#endif /* #ifndef _PRINTERDESCRIPTORS_H_ */

