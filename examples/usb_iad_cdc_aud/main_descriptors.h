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

#ifndef USBD_DRIVER_DESCRIPTORS_H
#define USBD_DRIVER_DESCRIPTORS_H

/** \file
 * \addtogroup usbd_composite_cdcaud
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/audio/audd_function.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_audd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_cdc_aud_dev_codes CDC(Serial) + Audio(Speaker) Device Codes
 *      @{
 * This page lists the %device IDs and release number of the USB composite
 * %device.
 *
 * \section Codes
 * - CDCAUDDDriverDescriptors_VENDORID
 * - CDCAUDDDriverDescriptors_PRODUCTID
 * - CDCAUDDDriverDescriptors_RELEASE
 */

/** Device vendor ID. */
#define CDCAUDDDriverDescriptors_VENDORID            0x03EB
/** Device product ID. */
#define CDCAUDDDriverDescriptors_PRODUCTID           0x6131
/** Device release number in BCD format. */
#define CDCAUDDDriverDescriptors_RELEASE             0x0100
/**      @}*/

/** \addtogroup usbd_cdc_aud_eps CDC(Serial) + Audio(Speaker) Endpoints
 *      @{
 */
/** CDC(Serial) notification interrupt endpoint */
#define CDCD_Descriptors_NOTIFICATION0              3
/** CDC(Serial) data bulk in endpoint */
#define CDCD_Descriptors_DATAIN0                    2
/** CDC(Serial) data bulk out endpoint */
#define CDCD_Descriptors_DATAOUT0                   1
/** Audio(Speaker) stream ISO out endpoint */
#define AUDD_Descriptors_DATAOUT                    5
/**     @}*/

/** \addtogroup usbd_audio_config USB Audio General Configure
 *      @{
 * This page lists definitions for USB Audio Devices Drivers.
 * - \ref
 */
/** Sample rate in Hz. */
#define AUDDevice_SAMPLERATE        48000UL
/** Number of channels in audio stream. */
#define AUDDevice_NUMCHANNELS       2
/** Number of bytes in one sample. */
#define AUDDevice_BYTESPERSAMPLE    2
/** Number of bits in one sample. */
#define AUDDevice_BITSPERSAMPLE     (AUDDevice_BYTESPERSAMPLE * 8)
/** Number of bytes in one USB subframe. */
#define AUDDevice_BYTESPERSUBFRAME  (AUDDevice_NUMCHANNELS * \
									 AUDDevice_BYTESPERSAMPLE)
/** Number of samples in one USB frame. */
#define AUDDevice_SAMPLESPERFRAME   (AUDDevice_SAMPLERATE / 1000 \
									 * AUDDevice_NUMCHANNELS)
/** Number of bytes in one USB frame. */
#define AUDDevice_BYTESPERFRAME     (AUDDevice_SAMPLESPERFRAME * \
									 AUDDevice_BYTESPERSAMPLE)
/**     @}*/

/**@}*/

#endif /* USBD_DRIVER_DESCRIPTORS_H */
