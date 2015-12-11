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
 * \addtogroup usbd_audio_speaker
 *@{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include "usb/device/audio/audd_speaker_driver.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup usbd_audio_stream USB Device Audio Speaker streams
 *      @{
 * This page lists codes for USB Audio Speaker stream information.
 * - \ref AUDDSpeakerDriver_SAMPLERATE
 * - \ref AUDDSpeakerDriver_NUMCHANNELS
 * - \ref AUDDSpeakerDriver_BYTESPERSAMPLE
 * - \ref AUDDSpeakerDriver_BITSPERSAMPLE
 * - \ref AUDDSpeakerDriver_SAMPLESPERFRAME
 * - \ref AUDDSpeakerDriver_BYTESPERFRAME
 */

/** Sample rate in Hz. */
#define AUDDSpeakerDriver_SAMPLERATE        48000UL
/** Number of channels in audio stream. */
#define AUDDSpeakerDriver_NUMCHANNELS       2
/** Number of bytes in one sample. */
#define AUDDSpeakerDriver_BYTESPERSAMPLE    2
/** Number of bits in one sample. */
#define AUDDSpeakerDriver_BITSPERSAMPLE     (AUDDSpeakerDriver_BYTESPERSAMPLE * 8)
/** Number of bytes in one USB subframe. */
#define AUDDSpeakerDriver_BYTESPERSUBFRAME  (AUDDSpeakerDriver_NUMCHANNELS * \
		AUDDSpeakerDriver_BYTESPERSAMPLE)
/** Number of samples in one USB frame. */
#define AUDDSpeakerDriver_SAMPLESPERFRAME   (AUDDSpeakerDriver_SAMPLERATE / 1000 * \
		AUDDSpeakerDriver_NUMCHANNELS)
/** Number of bytes in one USB frame. */
#define AUDDSpeakerDriver_BYTESPERFRAME     (AUDDSpeakerDriver_SAMPLESPERFRAME * \
		AUDDSpeakerDriver_BYTESPERSAMPLE)
/**     @}*/

/** \addtogroup usbd_audio_id USB Device Audio Speaker Codes
 *      @{
 * This section lists the device IDs and release number of the USB Audio
 * Speaker device.
 * - \ref AUDDSpeakerDriverDescriptors_VENDORID
 * - \ref AUDDSpeakerDriverDescriptors_PRODUCTID
 * - \ref AUDDSpeakerDriverDescriptors_RELEASE
 */
/** Device vendor ID. */
#define AUDDSpeakerDriverDescriptors_VENDORID            0x03EB
/** Device product ID. */
#define AUDDSpeakerDriverDescriptors_PRODUCTID           0x6128
/** Device release number in BCD format. */
#define AUDDSpeakerDriverDescriptors_RELEASE             0x0100
/**     @}*/

/** \addtogroup usbd_audio_speaker_config USB Speaker Configure
 *      @{
 * This page lists the definitions for USB Audio Speaker Device Driver.
 * - \ref AUDDSpeakerDriverDescriptors_DATAOUT
 * - \ref AUDDSpeakerDriverDescriptors_FS_INTERVAL
 * - \ref AUDDSpeakerDriverDescriptors_HS_INTERVAL
 *
 * \note for UDP, uses IN EPs that support double buffer; for UDPHS, uses
 *       IN EPs that support DMA and High bandwidth.
 */
/** Data out endpoint number. */
#define AUDDSpeakerDriverDescriptors_DATAOUT            0x02
/** Endpoint polling interval 2^(x-1) * 125us */
#define AUDDSpeakerDriverDescriptors_HS_INTERVAL        0x04
/** Endpoint polling interval 2^(x-1) * ms */
#define AUDDSpeakerDriverDescriptors_FS_INTERVAL        0x01
/**     @}*/

/**@}*/

#endif /* USBD_DRIVER_DESCRIPTORS_H */
