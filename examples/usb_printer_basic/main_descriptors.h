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

#ifndef USBD_DRIVER_DESCRIPTORS_H
#define USBD_DRIVER_DESCRIPTORS_H

/** \addtogroup usbd_printer
 *@{
 */

/*----------------------------------------------------------------------------
 *      Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/printer/printer_driver.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/
/** Address of the PRINTER bulk-in endpoint. */
#define PRINTER_Descriptors_DATAIN0                    2
/** Address of the PRINTER bulk-out endpoint. */
#define PRINTER_Descriptors_DATAOUT0                   1

/** Device product ID. */
#define PRINTERDriverDescriptors_PRODUCTID       0x6138
/** Device vendor ID (Atmel). */
#define PRINTERDriverDescriptors_VENDORID        0x03EB
/** Device release number. */
#define PRINTERDriverDescriptors_RELEASE         0x0001

/**@}*/

#endif /* USBD_DRIVER_DESCRIPTORS_H */
