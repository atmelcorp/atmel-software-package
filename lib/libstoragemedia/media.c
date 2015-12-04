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
#include "media_private.h"

/*---------------------------------------------------------------------------
 *      Exported Functions
 *---------------------------------------------------------------------------*/

/**
 *  \brief Writes data on a media
 *  \param media Pointer to a media instance
 *  \param address Address at which to write
 *  \param data Pointer to the data to write
 *  \param length Size of the data buffer
 *  \param callback Optional pointer to a callback function to invoke when the
 *                  write operation terminates
 *  \param callback_arg Optional argument for the callback function
 *  \return Operation result code
 *  \see media_callback_t
 */
uint8_t media_write(struct _media* media,
		uint32_t address, void* data, uint32_t length,
		media_callback_t callback, void* callback_arg)
{
	return media->write(media, address, data, length,
			callback, callback_arg);
}

/**
 *  \brief Reads a specified amount of data from a media
 *
 *  \param media Pointer to a media instance
 *  \param address Address of the data to read
 *  \param data Pointer to the buffer in which to store the retrieved data
 *  \param length Length of the buffer
 *  \param callback Optional pointer to a callback function to invoke when the
 *                  operation is finished
 *  \param callback_arg Optional pointer to an argument for the callback
 *  \return Operation result code
 *  \see    TransferCallback
 */
uint8_t media_read(struct _media* media,
		uint32_t address, void* data, uint32_t length,
		media_callback_t callback, void* callback_arg)
{
	return media->read(media, address, data, length,
			callback, callback_arg);
}

/**
 *  \brief Locks all the regions in the given address range.
 *  \param media    Pointer to a media instance
 *  \param start  Start address of lock range.
 *  \param end  End address of lock range.
 *  \param actual_start  Start address of the actual lock range (optional).
 *  \param actual_end  End address of the actual lock range (optional).
 *  \return 0 if successful; otherwise returns an error code.
 */
uint8_t media_lock(struct _media* media, uint32_t start, uint32_t end,
		uint32_t *actual_start, uint32_t *actual_end)
{
	if (media->lock) {
		return media->lock(media, start, end,
				actual_start, actual_end);
	} else {
		*actual_start = start;
		*actual_end = end;
		return MEDIA_STATUS_SUCCESS;
	}
}

/**
 *  \brief Unlocks all the regions in the given address range
 *  \param media Pointer to a media instance
 *  \param start Start address of unlock range.
 *  \param end End address of unlock range.
 *  \param actual_start Start address of the actual unlock range (optional).
 *  \param actual_end End address of the actual unlock range (optional).
 *  \return 0 if successful; otherwise returns an error code.
 */
uint8_t media_unlock(struct _media* media, uint32_t start, uint32_t end,
		uint32_t *actual_start, uint32_t *actual_end)
{
	if (media->unlock) {
		return media->unlock(media, start, end, actual_start, actual_end);
	} else {
		*actual_start = start;
		*actual_end = end;
		return MEDIA_STATUS_SUCCESS;
	}
}

/**
 *  \brief
 *  \param  media Pointer to the media instance to use
 */
uint8_t media_flush(struct _media* media)
{
	if (media->flush) {
		return media->flush(media);
	} else {
		return MEDIA_STATUS_SUCCESS;
	}
}

/**
 *  \brief Invokes the interrupt handler of the specified media
 *  \param media Pointer to the media instance to use
 */
void media_handler(struct _media* media)
{
	if (media->handler) {
		media->handler(media);
	}
}

/**
 *  \brief Reset the media interface to un-configured state.
 *  \param media Pointer to the media instance to use
 */
void media_deinit(struct _media* media)
{
	media->state = MEDIA_STATE_NOT_READY;
}

/**
 *  \brief Check if the media instance is ready to use.
 *  \param media Pointer to the media instance to use
 */
bool media_is_initialized(struct _media* media)
{
	return media->state != MEDIA_STATE_NOT_READY;
}

/**
 *  \brief Check if the media instance is busy in transfer.
 *  \param media Pointer to the media instance to use
 */
bool media_is_busy(struct _media *media)
{
	return media->state == MEDIA_STATE_BUSY;
}

/**
 *  \brief Check if the media supports mapped reading.
 *  \param media Pointer to the media instance to use
 */
bool media_is_mapped_read_supported(struct _media *media)
{
	return media->mapped_read;
}

/**
 *  \brief Check if the media supports mapped writing.
 *  \param media Pointer to the media instance to use
 */
bool media_is_mapped_write_supported(struct _media *media)
{
	return media->mapped_write;
}

/**
 *  \brief Check if the media is write protected.
 *  \param media Pointer to the media instance to use
 */
bool media_is_write_protected(struct _media *media)
{
	return media->write_protected;
}

/**
 *  \brief Return current state of the media.
 *  \param media Pointer to the media instance to use
 */
uint8_t media_get_state(struct _media *media)
{
	return media->state;
}

/**
 *  \brief Return block size in bytes.
 *  \param media Pointer to the media instance to use
 */
uint32_t media_get_block_size(struct _media *media)
{
	return media->block_size;
}

/**
 *  \brief Return media size in number of blocks.
 *  \param media Pointer to the media instance to use
 */
uint32_t media_get_size(struct _media *media)
{
	return media->size;
}

/**
 *  \brief Return mapped memory address for a block on media.
 *  \param media Pointer to the media instance to use
 */
uint32_t media_get_mapped_address(struct _media *media, uint32_t block)
{
	return (media->base_address + block) * media->block_size;
}

/**
 *  \brief Handle interrupts on specified media
 *  \param media List of media
 *  \param num_media Number of media in list
 */
void media_handle_all(struct _media* media, int num_media)
{
	int i;

	for (i = 0 ; i < num_media; i++ ) {
		media_handler(&media[i]);
	}
}
