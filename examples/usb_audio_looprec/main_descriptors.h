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
 * \addtogroup usbd_audio_looprec
 *@{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/audio/audd_speaker_phone_driver.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/**
 * \addtogroup usbd_aud_speakerphone_stream_info Audio SpeakerPhone stream
 * information
 *      @{
 * This page lists codes for USB Audio Speakerphone stream information.
 *
 * \section Code
 * - AUDDSpeakerPhoneDriver_SAMPLERATE
 * - AUDDSpeakerPhoneDriver_NUMCHANNELS
 * - AUDDSpeakerPhoneDriver_BYTESPERSAMPLE
 * - AUDDSpeakerPhoneDriver_BITSPERSAMPLE
 * - AUDDSpeakerPhoneDriver_SAMPLESPERFRAME
 * - AUDDSpeakerPhoneDriver_BYTESPERFRAME
 */

/** Sample rate in Hz. */
#define AUDDSpeakerPhoneDriver_SAMPLERATE        48000UL
/** Number of channels in audio stream. */
#define AUDDSpeakerPhoneDriver_NUMCHANNELS       2
/** Number of bytes in one sample. */
#define AUDDSpeakerPhoneDriver_BYTESPERSAMPLE    2
/** Number of bits in one sample. */
#define AUDDSpeakerPhoneDriver_BITSPERSAMPLE     (AUDDSpeakerPhoneDriver_BYTESPERSAMPLE * 8)
/** Number of bytes in one USB subframe. */
#define AUDDSpeakerPhoneDriver_BYTESPERSUBFRAME  (AUDDSpeakerPhoneDriver_NUMCHANNELS * \
		AUDDSpeakerPhoneDriver_BYTESPERSAMPLE)
/** Number of samples in one USB frame. */
#define AUDDSpeakerPhoneDriver_SAMPLESPERFRAME   (AUDDSpeakerPhoneDriver_SAMPLERATE / 1000 * \
		AUDDSpeakerPhoneDriver_NUMCHANNELS)
/** Number of bytes in one USB frame. */
#define AUDDSpeakerPhoneDriver_BYTESPERFRAME     (AUDDSpeakerPhoneDriver_SAMPLESPERFRAME * \
		AUDDSpeakerPhoneDriver_BYTESPERSUBFRAME)
/**      @}*/

/** \addtogroup usbd_audio_loop_record_device_codes Audio SpeakerPhone Device Codes
 *      @{
 * This page lists the %device IDs and release number of the USB Audio
 * Speakerphone %device.
 *
 * \section Codes
 * - AUDDSpeakerPhoneDriverDescriptors_VENDORID
 * - AUDDSpeakerPhoneDriverDescriptors_PRODUCTID
 * - AUDDSpeakerPhoneDriverDescriptors_RELEASE
 */

/** Device vendor ID. */
#define AUDDSpeakerPhoneDriverDescriptors_VENDORID            0x03EB
/** Device product ID. */
#define AUDDSpeakerPhoneDriverDescriptors_PRODUCTID           0x6128
/** Device release number in BCD format. */
#define AUDDSpeakerPhoneDriverDescriptors_RELEASE             0x0100
/**      @}*/

/** \addtogroup usbd_audio_speakerphone_config USB Speaker Phone Configure
 *      @{
 * This page lists the definitions for USB Audio Speaker Phone Device Driver.
 * - \ref AUDDSpeakerPhoneDriverDescriptors_DATAOUT
 * - \ref AUDDSpeakerPhoneDriverDescriptors_DATAIN
 * - \ref AUDDSpeakerPhoneDriverDescriptors_HS_INTERVAL
 * - \ref AUDDSpeakerPhoneDriverDescriptors_FS_INTERVAL
 */

/** Data out endpoint number, size 192B */
#define AUDDSpeakerPhoneDriverDescriptors_DATAOUT        0x02
/** Data in endpoint number, size 192B */
#define AUDDSpeakerPhoneDriverDescriptors_DATAIN         0x01

/** Endpoint polling interval 2^(x-1) * 125us */
#define AUDDSpeakerPhoneDriverDescriptors_HS_INTERVAL        0x04
/** Endpoint polling interval 2^(x-1) * ms */
#define AUDDSpeakerPhoneDriverDescriptors_FS_INTERVAL        0x01
/**      @}*/

/**@}*/

#endif /* USBD_DRIVER_DESCRIPTORS_H */
