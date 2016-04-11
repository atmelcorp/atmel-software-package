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
 * Implementation of media layer for the SdCard.
 *
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/
#include "trace.h"
#include "media.h"
#include "media_sdcard.h"
#include "media_private.h"
#include "libsdmmc.h"
#include <assert.h>
#include <string.h>
/*------------------------------------------------------------------------------
 *         Constants
 *------------------------------------------------------------------------------*/

/** Number of SD Slots */
#define NUM_SD_SLOTS        2
/** Default block size for SD/MMC card access */
#define SD_BLOCK_SIZE       512
/**
 * \brief  Reads a specified amount of data from a SDCARD memory
 * \param  media    Pointer to a Media instance
 * \param  address  Address of the data to read
 * \param  data     Pointer to the buffer in which to store the retrieved
 *                   data
 * \param  length   Length of the buffer
 * \param  callback Optional pointer to a callback function to invoke when
 *                   the operation is finished
 * \param  argument Optional pointer to an argument for the callback
 * \return Operation result code
 */
static uint8_t media_sdcard_read(struct _media *media,
								uint32_t  address,
								void          *data,
								uint32_t  length,
								media_callback_t callback,
								void          *argument)
{
	uint8_t error;

	/* Check that the media is ready */
	if (media->state != MEDIA_STATE_READY) {

		trace_info("Media busy\n\r");
		return MEDIA_STATUS_BUSY;
	}

	/* Check that the data to read is not too big */
	if ((length + address) > media->size) {

		trace_warning("MEDSdcard_Read: Data too big: %d, %d\n\r",
					  (int)length, (int)address);
		return MEDIA_STATUS_ERROR;
	}

	/* Enter Busy state */
	media->state = MEDIA_STATE_BUSY;

	error = SD_ReadBlocks((sSdCard *)media->interface, address, data, length);

	/* Leave the Busy state */
	media->state = MEDIA_STATE_READY;

	/* Invoke callback */
	if (callback != 0)

		callback(argument, error, 0, 0);

	return error;
}

/**
 * \brief  Writes data on a SDRAM media
 * \param  media    Pointer to a Media instance
 * \param  address  Address at which to write
 * \param  data     Pointer to the data to write
 * \param  length   Size of the data buffer
 * \param  callback Optional pointer to a callback function to invoke when
 *                   the write operation terminates
 * \param  argument Optional argument for the callback function
 * \return Operation result code
 * \see    Media
 * \see    MediaCallback
 */
static uint8_t media_sdcard_write(struct _media *media,
								uint32_t         address,
								void             *data,
								uint32_t         length,
								media_callback_t callback,
								void             *argument)
{
	uint8_t error;

	/* Check that the media if ready */
	if (media->state != MEDIA_STATE_READY) {

		trace_warning("MEDSdcard_Write: Media is busy\n\r");
		return MEDIA_STATUS_BUSY;
	}

	/* Check that the data to write is not too big */
	if ((length + address) > media->size) {

		trace_warning("MEDSdcard_Write: Data too big\n\r");
		return MEDIA_STATUS_ERROR;
	}

	/* Put the media in Busy state */
	media->state = MEDIA_STATE_BUSY;

	//error = SD_Write((sSdCard*)media->interface, address,data,length,NULL,NULL);
	error = SD_WriteBlocks((sSdCard *)media->interface, address, data, length);

	/* Leave the Busy state */
	media->state = MEDIA_STATE_READY;

	/*  Invoke the callback if it exists */
	if (callback != 0)

		callback(argument, error, 0, 0);

	return error;
}

/**
 * \brief  Reads a specified amount of data from a SDCARD memory
 * \param  media    Pointer to a Media instance
 * \param  address  Address of the data to read
 * \param  data     Pointer to the buffer in which to store the retrieved
 *                   data
 * \param  length   Length of the buffer
 * \param  callback Optional pointer to a callback function to invoke when
 *                   the operation is finished
 * \param  argument Optional pointer to an argument for the callback
 * \return Operation result code
 */
static uint8_t media_sdusb_read(struct _media *media,
								uint32_t       address,
								void          *data,
								uint32_t       length,
								media_callback_t  callback,
								void          *argument)
{
	uint8_t error;

	/* Check that the media is ready */
	if (media->state != MEDIA_STATE_READY) {
		trace_warning("MEDSdusb_Read: Busy\n\r");
		return MEDIA_STATUS_BUSY;
	}

	/* Check that the data to read is not too big */
	if ((length + address) > media->size) {
		trace_warning("MEDSdusb_Read: Data too big: %d, %d\n\r",  (int)length,
					  (int)address);
		return MEDIA_STATUS_ERROR;
	}

	/* Enter Busy state */
	media->state = MEDIA_STATE_BUSY;
	error = SD_Read((sSdCard *)media->interface, address, data, length,
			NULL, NULL);
	error = (error ? MEDIA_STATUS_ERROR : MEDIA_STATUS_SUCCESS);
	media->state = MEDIA_STATE_READY;

	if (callback) callback(argument, error, 0, 0);

	return error;

}

/**
 * \brief  Writes data on a SDRAM media
 * \param  media    Pointer to a Media instance
 * \param  address  Address at which to write
 * \param  data     Pointer to the data to write
 * \param  length   Size of the data buffer
 * \param  callback Optional pointer to a callback function to invoke when
 *                   the write operation terminates
 * \param  argument Optional argument for the callback function
 * \return Operation result code
 * \see    Media
 * \see    MediaCallback
 */
static uint8_t media_sdusb_write(struct _media *media,
								uint32_t       address,
								void          *data,
								uint32_t       length,
								media_callback_t  callback,
								void          *argument)
{
	uint8_t error;

	if (media->state != MEDIA_STATE_READY) {
		trace_info("MEDSdusb_Write: Busy\n\r");
		return MEDIA_STATUS_BUSY;
	}

	/* Check that the data to write is not too big */
	if ((length + address) > media->size) {
		trace_warning("MEDSdcard_Write: Data too big\n\r");
		return MEDIA_STATUS_ERROR;
	}

	/* Put the media in Busy state */
	media->state = MEDIA_STATE_BUSY;
	error = SD_Write((sSdCard *)media->interface, address, data, length,
			 NULL, NULL);
	error = (error ? MEDIA_STATUS_ERROR : MEDIA_STATUS_SUCCESS);
	media->state = MEDIA_STATE_READY;

	if (callback) callback(argument, error, 0, 0);

	return error;

}

/**
 * \brief  Initializes a Media instance
 * \param  media Pointer to the Media instance to initialize
 * \param  sd_drv Pointer to SD/MMC card driver structure
 * \return 1 if success.
 */
uint8_t media_sdcard_initialize(struct _media *media, sSdCard *sd_drv)
{
	trace_info("MEDSdcard init\n\r");
	/*  Initialize media fields */
	media->interface = sd_drv;
#if !defined(OP_BOOTSTRAP_MCI_ON)
	media->write = media_sdcard_write;
#else
	media->write = 0;
#endif
	media->read = media_sdcard_read;
	media->lock = 0;
	media->unlock = 0;
	media->handler = 0;
	media->flush = 0;

	media->block_size = SD_BLOCK_SIZE;
	media->base_address = 0;
	media->size = sd_drv->dwNbBlocks;

	media->mapped_read  = 0;
	media->mapped_write  = 0;
	media->removable = 1;

	media->state = MEDIA_STATE_READY;

	media->transfer.data = 0;
	media->transfer.address = 0;
	media->transfer.length = 0;
	media->transfer.callback = 0;
	media->transfer.callback_arg = 0;

	return 1;
}

/**
 * \brief  Initializes a Media instance
 * \param  media Pointer to the Media instance to initialize
 * \param  sd_drv Pointer to SD/MMC card driver structure
 * \return 1 if success.
 */
uint8_t media_sdusb_initialize(struct _media *media, sSdCard *sd_drv)
{
	trace_info("MEDSdusb init\n\r");

	/* Initialize media fields */
	media->interface = sd_drv;
	media->write = media_sdusb_write;
	media->read = media_sdusb_read;
	media->lock = 0;
	media->unlock = 0;
	media->handler = 0;
	media->flush = 0;

	media->block_size = SD_BLOCK_SIZE;
	media->base_address = 0;
	media->size = sd_drv->dwNbBlocks;

	media->mapped_read  = 0;
	media->mapped_write  = 0;
	media->write_protected = 0;
	media->removable = 1;

	media->state = MEDIA_STATE_READY;

	media->transfer.data = 0;
	media->transfer.address = 0;
	media->transfer.length = 0;
	media->transfer.callback = 0;
	media->transfer.callback_arg = 0;

	return 1;
}

/**
 * \brief  erase all the Sdcard
 * \param  media Pointer to the Media instance to initialize
 */

void media_sdcard_erase_all(struct _media *media)
{
	uint8_t buffer[SD_BLOCK_SIZE];
	uint32_t block;
	uint32_t multi_block = 1; /* change buffer size for multiblocks */
	uint8_t error;

	trace_info("MEDSdcard Erase All ...\n\r");

	/* Clear the block buffer */
	memset(buffer, 0, media->block_size * multi_block);

	for (block = 0;
		 block < (media->size - multi_block);
		 block += multi_block) {
		error = SD_WriteBlocks((sSdCard *)media->interface, block, buffer, multi_block);

		if (error) {
			trace_error("\n\r-F- Failed to erase block (%u) #%u\n\r",  (unsigned int)error,
					(unsigned int)block);

			/* Wait for watchdog reset or freeze the program */
			while (1);
		}
	}
}

/**
 * \brief  erase block
 * \param  media Pointer to the Media instance to initialize
 * \param  block to erase
 */
void media_sdcard_erase_block(struct _media *media, uint32_t block)
{
	uint8_t buffer[SD_BLOCK_SIZE];
	uint8_t error;

	/* Clear the block buffer */
	memset(buffer, 0, media->block_size);
	error = SD_WriteBlocks((sSdCard *)media->interface, block, buffer, 1);

	if (error) {
		trace_error("\n\r-F- Failed to write block (%u) #%u\n\r",  (unsigned int)error,
					(unsigned int)block);

		/* Wait for watchdog reset or freeze the program */
		while (1);
	}
}

