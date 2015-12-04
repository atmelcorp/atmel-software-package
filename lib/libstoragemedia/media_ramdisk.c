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

/** \file */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "media.h"
#include "media_ramdisk.h"
#include "media_private.h"

#include <string.h>

/*---------------------------------------------------------------------------
 *      Internal Functions
 *---------------------------------------------------------------------------*/

/**
 * \brief Reads a specified amount of data from a RAM Disk memory
 * \param media Pointer to a Media instance
 * \param address Address of the data to read
 * \param data Pointer to the buffer in which to store the retrieved data
 * \param length Length of the buffer
 * \param callback Optional pointer to a callback function to invoke when
 *                 the operation is finished
 * \param callback_arg Optional pointer to an argument for the callback
 * \return Operation result code
 */
static uint8_t media_ramdisk_read(struct _media *media,
		uint32_t address, void *data, uint32_t length,
		media_callback_t callback, void *callback_arg)
{
	uint8_t *source;

	// Check that the media is ready
	if (media->state != MEDIA_STATE_READY)
		return MEDIA_STATUS_BUSY;

	// Check that the data to read is not too big
	if ((address + length) > media->size)
		return MEDIA_STATUS_ERROR;

	// Enter Busy state
	media->state = MEDIA_STATE_BUSY;

	// Copy data
	source = (uint8_t*)((media->base_address + address) * media->block_size);
	memcpy(data, source, length);

	// Leave the Busy state
	media->state = MEDIA_STATE_READY;

	// Invoke callback
	if (callback)
		callback(callback_arg, MEDIA_STATUS_SUCCESS, 0, 0);

	return MEDIA_STATUS_SUCCESS;
}

/**
 *  \brief Writes data on a Ram Disk media
 *  \param media Pointer to a Media instance
 *  \param address Address at which to write
 *  \param data Pointer to the data to write
 *  \param length Size of the data buffer
 *  \param callback Optional pointer to a callback function to invoke when
 *                  the write operation terminates
 *  \param callback_arg Optional argument for the callback function
 *  \return Operation result code
 */
static uint8_t media_ramdisk_write(struct _media *media,
		uint32_t address, void *data, uint32_t length,
		media_callback_t callback, void *callback_arg)
{
	uint8_t *dest;

	// Check that the media if ready
	if (media->state != MEDIA_STATE_READY)
		return MEDIA_STATUS_BUSY;

	// Check that the data to write is not too big
	if ((address + length) > media->size)
		return MEDIA_STATUS_ERROR;

	// Put the media in Busy state
	media->state = MEDIA_STATE_BUSY;

	// Copy data
	dest = (uint8_t*)((media->base_address + address) * media->block_size);
	memcpy(dest, data, length);

	// Leave the Busy state
	media->state = MEDIA_STATE_READY;

	// Invoke the callback if it exists
	if (callback)
		callback(callback_arg, MEDIA_STATUS_SUCCESS, 0, 0);

	return MEDIA_STATUS_SUCCESS;
}

/*---------------------------------------------------------------------------
 *      Exported Functions
 *---------------------------------------------------------------------------*/

/**
 *  \brief Initializes a block of RAM as Media block.
 *  \param media Pointer to the Media instance to initialize
 */
void media_ramdisk_init(struct _media *media, uint32_t base_address, uint32_t size, uint32_t block_size)
{
	memset(media, 0, sizeof(*media));

	media->write = media_ramdisk_write;
	media->read = media_ramdisk_read;

	media->block_size = block_size;
	media->base_address = base_address;
	media->size = size;

	media->mapped_read  = true;
	media->mapped_write  = true;
	media->state = MEDIA_STATE_READY;
}
