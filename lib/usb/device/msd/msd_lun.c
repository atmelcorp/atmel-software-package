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
 * \addtogroup usbd_msd
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "libstoragemedia/media.h"

#include "usb/device/msd/msd_lun.h"
#include "usb/device/usbd.h"

#include "mm/cache.h"

#include <assert.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Constants
 *------------------------------------------------------------------------------*/

/** Default LUN block size in bytes */
#define     DEFAULT_LUN_BLOCK_SIZE      512

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Inquiry data to return to the host for the Lun. (initialization data) */
static const SBCInquiryData inquiry_data_init = {
	SBC_DIRECT_ACCESS_BLOCK_DEVICE, /* Direct-access block device */
	SBC_PERIPHERAL_DEVICE_CONNECTED,/* Peripheral device is connected */
	0x00,                           /* Reserved bits */
	0x01,                           /* Media is removable */
	SBC_SPC_VERSION_4,              /* SPC-4 supported */
	0x2,                            /* Response data format, must be 0x2 */
	0,                              /* Hierarchical addressing not supported */
	0,                              /* ACA not supported */
	0x0,                            /* Obsolete bits */
	sizeof(SBCInquiryData) - 5,     /* Additional length */
	0,                              /* No embedded SCC */
	0,                              /* No access control coordinator */
	SBC_TPGS_NONE,                  /* No target port support group */
	0,                              /* Third-party copy not supported */
	0x0,                            /* Reserved bits */
	0,                              /* Protection information not supported */
	0x0,                            /* Obsolete bit */
	0,                              /* No embedded enclosure service component */
	0x0,                            /* ??? */
	0,                              /* Device is not multi-port */
	0x0,                            /* Obsolete bits */
	0x0,                            /* Unused feature */
	0x0,                            /* Unused features */
	0,                              /* Task management model not supported */
	0x0,                            /* ??? */
	{'A','T','M','E','L',' ',' ',' '},
	{'M','a','s','s',' ',
	 'S','t','o','r','a','g','e',' ',
	 'M','S','D'},
	{'0','.','0','1'},
	{'M','a','s','s',' ',
	 'S','t','o','r','a','g','e',' ',
	 'E','x','a','m','p','l','e'},
	0x00,                           /* Unused features */
	0x00,                           /* Reserved bits */
	{SBC_VERSION_DESCRIPTOR_SBC_3}, /* SBC-3 compliant device */
	{0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0,
	 0, 0} /* Reserved */
};

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief  Initializes a LUN instance. Must be invoked at least once even no
 *         Media is linked.
 * \param  lun          Pointer to the MSDLun instance to initialize
 * \param  media        Media on which the LUN is constructed, set to 0 to
 *                      disconnect the Media or initialize an ejected LUN.
 * \param  io_buffer    Pointer to a buffer used for read/write operation and
 *                      which must be block_size bytes long.
 * \param  io_buffer_size Size of the allocated IO buffer.
 * \param  base_address  Base address of the LUN in number of media blocks
 * \param  size         Total size of the LUN in number of media blocks
 * \param  block_size    One block of the LUN in number of media blocks
 * \param  readonly     The LUN area is forced to readonly even the media
 *                      is writable
 * \param  dataMonitor  Pointer to a Monitor Function to analyze the flow of
 *                      this LUN.
 */
void lun_init(MSDLun    *lun,
			  void      *media,
			  uint8_t   *io_buffer,
			  uint32_t   io_buffer_size,
			  uint32_t   base_address,
			  uint32_t   size,
			  uint16_t   block_size,
			  uint8_t    readonly,
			  void (*dataMonitor)(uint8_t flow_direction,
								  uint32_t  data_length,
								  uint32_t  fifo_null_count,
								  uint32_t  fifo_full_count))
{
	uint8_t *data_buffer;
	uint32_t logicalBlockAddress;
	trace_info("LUN init\n\r");

	/* Initialize pointers for cache-aligned buffers */

	data_buffer = (uint8_t*)ROUND_UP_MULT((uint32_t)lun->dataBuffer, L1_CACHE_BYTES);
	lun->requestSenseData = (SBCRequestSenseData*)data_buffer;
	data_buffer += ROUND_UP_MULT(sizeof(SBCRequestSenseData), L1_CACHE_BYTES);
	lun->readCapacityData = (SBCReadCapacity10Data*)data_buffer;
	data_buffer += ROUND_UP_MULT(sizeof(SBCReadCapacity10Data), L1_CACHE_BYTES);
	lun->inquiryData = (SBCInquiryData*)data_buffer;
	data_buffer += ROUND_UP_MULT(sizeof(SBCInquiryData), L1_CACHE_BYTES);
	/* overflow check */
	assert(lun->dataBuffer + sizeof(lun->dataBuffer) >= data_buffer);

	/* Initialize inquiry data */

	memcpy(lun->inquiryData, &inquiry_data_init, sizeof(SBCInquiryData));

	/* Initialize request sense data */

	lun->requestSenseData->bResponseCode = SBC_SENSE_DATA_FIXED_CURRENT;
	lun->requestSenseData->isValid = 1;
	lun->requestSenseData->bObsolete1 = 0;
	lun->requestSenseData->bSenseKey = SBC_SENSE_KEY_NO_SENSE;
	lun->requestSenseData->bReserved1 = 0;
	lun->requestSenseData->isILI = 0;
	lun->requestSenseData->isEOM = 0;
	lun->requestSenseData->isFilemark = 0;
	lun->requestSenseData->pInformation[0] = 0;
	lun->requestSenseData->pInformation[1] = 0;
	lun->requestSenseData->pInformation[2] = 0;
	lun->requestSenseData->pInformation[3] = 0;
	lun->requestSenseData->bAdditionalSenseLength = sizeof(SBCRequestSenseData) - 8;
	lun->requestSenseData->bAdditionalSenseCode = 0;
	lun->requestSenseData->bAdditionalSenseCodeQualifier = 0;
	lun->requestSenseData->bFieldReplaceableUnitCode = 0;
	lun->requestSenseData->bSenseKeySpecific = 0;
	lun->requestSenseData->pSenseKeySpecific[0] = 0;
	lun->requestSenseData->pSenseKeySpecific[0] = 0;
	lun->requestSenseData->isSKSV = 0;

	STORE_DWORDB(0, lun->readCapacityData->pLogicalBlockAddress);
	STORE_DWORDB(0, lun->readCapacityData->pLogicalBlockLength);

	/* Initialize LUN */

	lun->media = media;
	if (media == 0) {
		lun->status = LUN_NOT_PRESENT;
		return;
	}

	lun->baseAddress = base_address;

	/* Customized block size */

	if (block_size) {
		lun->blockSize = block_size;
	}
	else {
		uint32_t blkSize = media_get_block_size(media);
		if (blkSize < DEFAULT_LUN_BLOCK_SIZE)
			lun->blockSize = DEFAULT_LUN_BLOCK_SIZE / blkSize;
		else
			lun->blockSize = 1;
	}

	if (size) {
		lun->size = size;
	}
	else {
		lun->size = media_get_size(media);
	}

	trace_info("LUN: blkSize %d, size %d\n\r", (int)lun->blockSize, (int)lun->size);
	if (readonly) lun->readonly = 1;
	else           lun->readonly = media_is_write_protected(media);

	msd_io_fifo_init(&lun->ioFifo, io_buffer, io_buffer_size);

	lun->dataMonitor = dataMonitor;

	/* Initialize read capacity data */

	logicalBlockAddress = lun->size / lun->blockSize - 1;
	STORE_DWORDB(logicalBlockAddress,
				 lun->readCapacityData->pLogicalBlockAddress);
	STORE_DWORDB(lun->blockSize * media_get_block_size(media),
				 lun->readCapacityData->pLogicalBlockLength);

	/* Indicate media change */

	lun->status = LUN_CHANGED;
}

/**
 * \brief  Eject the media from a LUN
 * \param  lun          Pointer to the MSDLun instance to initialize
 * \return Operation result code
 */
uint32_t lun_eject(MSDLun *lun)
{
	if (lun->media) {

		/* Avoid any LUN R/W in progress */
		if (media_is_busy(lun->media)) {

			return USBD_STATUS_LOCKED;
		}

		/* Remove the link of the media */
		lun->media = 0;
	}
	/* LUN is removed */
	lun->status = LUN_NOT_PRESENT;

	return USBD_STATUS_SUCCESS;
}

/**
 * \brief  Check whether the specified LUN block range is accessible.
 * \param  lun          Pointer to a MSDLun instance
 * \param  block_address First block address to access
 * \param  length       Number of blocks to access
 * \param  write        Access type: write (1) or read (0).
 * \return Operation result code
 */
uint32_t lun_access(MSDLun        *lun,
					uint32_t block_address,
					uint32_t length,
					uint8_t  write)
{
	const uint32_t lun_blk_cnt = lun->size / lun->blockSize;

	if (block_address > lun_blk_cnt || length > lun_blk_cnt
	    || block_address + length > lun_blk_cnt)
		return USBD_STATUS_INVALID_PARAMETER;
	else if (lun->media == NULL || lun->status != LUN_READY)
		return USBD_STATUS_LOCKED;
	else if (write && lun->readonly)
		return USBD_STATUS_ABORTED;
	else
		return USBD_STATUS_SUCCESS;
}

/**
 * \brief  Writes data on the a LUN starting at the specified block address.
 * \param  lun          Pointer to a MSDLun instance
 * \param  block_address First block address to write
 * \param  data         Pointer to the data to write
 * \param  length       Number of blocks to write
 * \param  callback     Optional callback to invoke when the write finishes
 * \param  argument     Optional callback argument.
 * \return Operation result code
 */
uint32_t lun_write(MSDLun        *lun,
					uint32_t block_address,
					void     *data,
					uint32_t length,
					usbd_xfer_cb_t   callback,
					void     *argument)
{
	uint32_t  medBlk, medLen;
	uint8_t status;

	trace_info_wp("LUNWrite(%u) ", (unsigned)block_address);

	/* Check that the data is not too big */
	if ((length + block_address) * lun->blockSize > lun->size) {

		trace_warning("lun_write: Data too big\n\r");
		status = USBD_STATUS_ABORTED;
	}
	else if (lun->media == 0 || lun->status != LUN_READY) {

		trace_warning("lun_write: Media not ready\n\r");
		status = USBD_STATUS_ABORTED;
	}
	else if (lun->readonly) {
		trace_warning("lun_write: LUN is readonly\n\r");
		status = USBD_STATUS_ABORTED;
	}
	else {

		/* Compute write start address */
		medBlk = lun->baseAddress + block_address * lun->blockSize;
		medLen = length * lun->blockSize;

		/* Start write operation */
		status = media_write(lun->media,
						   medBlk,
						   data,
						   medLen,
						   callback,
						   argument);

		/* Check operation result code */
		if (status == MEDIA_STATUS_SUCCESS) {

			status = USBD_STATUS_SUCCESS;
		}
		else {

			trace_warning("lun_write: Cannot write media\n\r");
			status = USBD_STATUS_ABORTED;
		}
	}
	return status;
}

/**
 * \brief  Reads data from a LUN, starting at the specified block address.
 * \param  lun          Pointer to a MSDLun instance
 * \param  block_address First block address to read
 * \param  data         Pointer to a data buffer in which to store the data
 * \param  length       Number of blocks to read
 * \param  callback     Optional callback to invoke when the read finishes
 * \param  argument     Optional callback argument.
 * \return Operation result code
 */
uint32_t lun_read(MSDLun        *lun,
					uint32_t block_address,
					void     *data,
					uint32_t length,
					usbd_xfer_cb_t   callback,
					void     *argument)
{
	uint32_t medBlk, medLen;
	uint8_t status;

	/* Check that the data is not too big */
	if ((length + block_address) * lun->blockSize > lun->size) {

		trace_warning("lun_read: Area: (%d + %d)*%d > %d\n\r",
					  (int)length, (int)block_address, (int)lun->blockSize, (int)lun->size);
		status = USBD_STATUS_ABORTED;
	}
	else if (lun->media == 0 || lun->status != LUN_READY) {

		trace_warning("lun_read: Media not present\n\r");
		status = USBD_STATUS_ABORTED;
	}
	else {

		trace_info_wp("LUNRead(%u) ", (unsigned)block_address);

		/* Compute read start address */
		medBlk = lun->baseAddress + (block_address * lun->blockSize);
		medLen = length * lun->blockSize;

		/* Start write operation */
		status = media_read(lun->media,
						  medBlk,
						  data,
						  medLen,
						  callback,
						  argument);

		/* Check result code */
		if (status == MEDIA_STATUS_SUCCESS) {

			status = USBD_STATUS_SUCCESS;
		}
		else {

			trace_warning("lun_read: Cannot read media\n\r");
			status = USBD_STATUS_ABORTED;
		}
	}

	return status;
}

/**@}*/
