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
 *      Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"
#include "intmath.h"

#include "libstoragemedia/media.h"

#include "usb/device/msd/msdd_state_machine.h"
#include "usb/device/msd/msd_io_fifo.h"
#include "usb/device/msd/sbc_methods.h"
#include "usb/device/usbd.h"
#include "mm/cache.h"
/*------------------------------------------------------------------------------
 *      Constants
 *------------------------------------------------------------------------------*/

/**
 * \brief  Header for the mode pages data
 * \see    SBCModeParameterHeader6
 */
CACHE_ALIGNED_CONST
static const SBCModeParameterHeader6 mode_parameter_header6 = {
	sizeof(SBCModeParameterHeader6) - 1,        /*! Length is 0x03 */
	SBC_MEDIUM_TYPE_DIRECT_ACCESS_BLOCK_DEVICE, /*! Direct-access block device */
	0,                                          /*! Reserved bits */
	0,                                          /*! DPO/FUA not supported */
	0,                                          /*! Reserved bits */
	0,                                          /*! not write-protected */
	0                                           /*! No block descriptor */
};

/*------------------------------------------------------------------------------
 *      Internal functions
 *------------------------------------------------------------------------------*/

/**
 * This function is to be used as a callback for USB or LUN transfers.
 * \param  arg    Pointer to the transfer structure to update
 * \param  status      Operation result code
 * \param  transferred Number of bytes transferred by the command
 * \param  remaining   Number of bytes not transferred
 */
static void msd_driver_callback(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	MSDTransfer *transfer = (MSDTransfer*)arg;
	transfer->status = status;
	transfer->transferred = transferred;
	transfer->remaining = remaining;
	transfer->semaphore++;
}

/**
 * \brief  Check if the LUN is ready.
 * \param  lun          Pointer to the LUN affected by the command
 * \return 1 if the LUN is ready to be written
 * \see    MSDLun
 */
static bool sbc_lun_is_ready(MSDLun *lun)
{
	bool lun_is_ready = false;

	if (lun->media == 0 || lun->status < LUN_CHANGED) {
		trace_warning("sbc_lun_is_ready: Not Present!\n\r");
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_NOT_READY,
				SBC_ASC_MEDIUM_NOT_PRESENT, 0);
	} else if (lun->status < LUN_READY) {
		trace_warning("sbc_lun_is_ready: Changing!\n\r");
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_UNIT_ATTENTION,
				SBC_ASC_NOT_READY_TO_READY_CHANGE, 0);
		lun->status = LUN_READY;
	} else {
		lun_is_ready = true;
	}

	return lun_is_ready;
}

/**
 * \brief  Check if the LUN can write.
 * \param  lun          Pointer to the LUN affected by the command
 * \return true if the LUN is ready to be written
 * \see    MSDLun
 */
static bool sbc_lun_can_be_written(MSDLun *lun)
{
	bool canbe_written = false;

	if (!sbc_lun_is_ready(lun)) {
		trace_warning("sbc_lun_can_be_written: Not Ready!\n\r");
	} else if (lun->readonly) {
		trace_warning("sbc_lun_can_be_written: Protected!\n\r");

		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_DATA_PROTECT,
				SBC_ASC_WRITE_PROTECTED, 0);
	} else {
		canbe_written = true;
	}

	return canbe_written;
}

/**
 * \brief  Performs a WRITE (10) command on the specified LUN.
 *
 *         The data to write is first received from the USB host and then
 *         actually written on the media.
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDDriver_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_write10(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t status;
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	SBCRead10 *command = (SBCRead10 *) command_state->cbw.pCommand;
	MSDTransfer *transfer = &(command_state->transfer);
	MSDTransfer *disktransfer = &(command_state->disktransfer);
	MSDIOFifo *fifo = &lun->ioFifo;
	uint32_t lba, old_chunk_size, new_chunk_size;

	/* Init command state */
	if (command_state->state == 0) {
		command_state->state = SBC_STATE_WRITE;

		/* The command should not be proceeded if READONLY */
		if (!sbc_lun_can_be_written(lun)) {
			return MSDD_STATUS_RW;
		}
		else {
			/* Initialize FIFO */
			fifo->dataTotal = command_state->length;
			fifo->blockSize = lun->blockSize *
				media_get_block_size(lun->media);
#ifdef MSDIO_WRITE10_CHUNK_SIZE
			fifo->chunkSize = max_u32(fifo->blockSize,
						  MSDIO_WRITE10_CHUNK_SIZE);
#endif
			fifo->fullCnt = 0;
			fifo->nullCnt = 0;

			/* Initialize FIFO output (Disk) */
			fifo->outputNdx = 0;
			fifo->outputTotal = 0;
			fifo->outputState = MSDIO_IDLE;
			transfer->semaphore = 0;

			/* Initialize FIFO input (USB) */
			fifo->inputNdx = 0;
			fifo->inputTotal = 0;
			fifo->inputState = MSDIO_START;
			disktransfer->semaphore = 0;
		}
	}

	if (command_state->length == 0) {
		/* Perform the callback! */
		if (lun->dataMonitor) {
			lun->dataMonitor(0, fifo->dataTotal, fifo->nullCnt, fifo->fullCnt);
		}
		return MSDD_STATUS_SUCCESS;
	}

	old_chunk_size = fifo->chunkSize;
	if ((fifo->dataTotal - fifo->inputTotal) < fifo->chunkSize) {
		new_chunk_size = fifo->dataTotal - fifo->inputTotal;
		fifo->chunkSize = new_chunk_size;
	}

	/* USB receive task */
	switch(fifo->inputState) {
	case MSDIO_IDLE:
		if (fifo->inputTotal < fifo->dataTotal &&
				fifo->inputTotal - fifo->outputTotal < fifo->bufferSize) {
			fifo->inputState = MSDIO_START;
		}
		break;

	case MSDIO_START:
		/* Should not start if there is any disk error */
		if (fifo->outputState == MSDIO_ERROR) {
			LIBUSB_TRACE("udErr ");
			fifo->inputState = MSDIO_ERROR;
			break;
		}

		/* Read one block of data sent by the host */
		if (media_is_mapped_write_supported(lun->media)) {
			uint32_t mappedAddr;
			/* Validate the specified block range then write
			 * directly to the memory area assigned to the device */
			status = lun_access(lun,
					DWORDB(command->pLogicalBlockAddress),
					WORDB(command->pTransferLength), 1);
			if (status != USBD_STATUS_SUCCESS)
				msd_driver_callback(transfer,
						MEDIA_STATUS_ERROR, 0, 0);
			else {
				mappedAddr = media_get_mapped_address(lun->media,
						DWORDB(command->pLogicalBlockAddress)
						* lun->blockSize);
				status = usbd_read(command_state->pipeOUT,
						(void*)mappedAddr, fifo->dataTotal,
						msd_driver_callback, transfer);
			}
		} else {
			/* Read block to buffer */
#ifdef MSDIO_WRITE10_CHUNK_SIZE
			status = usbd_read(command_state->pipeOUT,
					&fifo->pBuffer[fifo->inputNdx], fifo->chunkSize,
					msd_driver_callback, transfer);
#else
			status = usbd_read(command_state->pipeOUT,
					&fifo->pBuffer[fifo->inputNdx], fifo->blockSize,
					msd_driver_callback, transfer);
#endif
		}

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Write10: Failed to start receiving\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_HARDWARE_ERROR, 0, 0);
			result = MSDD_STATUS_ERROR;
		} else {
			LIBUSB_TRACE("uRx ");

			/* Prepare next device state */
			fifo->inputState = MSDIO_WAIT;
		}
		break; /* MSDIO_START */

	case MSDIO_WAIT:
		LIBUSB_TRACE("uWait ");

		/* Check semaphore */
		if (transfer->semaphore > 0) {
			transfer->semaphore--;
			fifo->inputState = MSDIO_NEXT;
		}
		break;

	case MSDIO_NEXT:
		/* Check the result code of the write operation */
		if (transfer->status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Write10: Failed to received\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_HARDWARE_ERROR, 0, 0);
			result = MSDD_STATUS_ERROR;
		} else {
			LIBUSB_TRACE("uNxt ");

			/* Mapped write, all data done */
			if (media_is_mapped_write_supported(lun->media)) {
				fifo->inputTotal = fifo->dataTotal;
				fifo->inputState = MSDIO_IDLE;
			} else {
				/* Update input index */
#ifdef MSDIO_WRITE10_CHUNK_SIZE
				MSDIOFifo_IncNdx(fifo->inputNdx, fifo->chunkSize,
						fifo->bufferSize);
				fifo->inputTotal += fifo->chunkSize;
#else
				MSDIOFifo_IncNdx(fifo->inputNdx, fifo->blockSize,
						fifo->bufferSize);
				fifo->inputTotal += fifo->blockSize;
#endif

				/* Start Next block */

				/* - All Data done? */
				if (fifo->inputTotal >= fifo->dataTotal) {
					fifo->inputState = MSDIO_IDLE;
				}
				/* - Buffer full? */
				else if (fifo->inputNdx == fifo->outputNdx) {
					fifo->inputState = MSDIO_IDLE;
					fifo->fullCnt++;
					LIBUSB_TRACE("ufFull%d ", fifo->inputNdx);
				}
				/* - More data to transfer? */
				else if (fifo->inputTotal < fifo->dataTotal) {
					fifo->inputState = MSDIO_START;
					LIBUSB_TRACE("uStart ");
				}
			}
		}
		break; /* MSDIO_NEXT */

	case MSDIO_ERROR:
		LIBUSB_TRACE("uErr ");
		command_state->length -= fifo->inputTotal;
		return MSDD_STATUS_RW;
	}

	/* Disk write task */
	fifo->chunkSize = old_chunk_size;
	if ((fifo->dataTotal - fifo->outputTotal) < fifo->chunkSize) {
		new_chunk_size = fifo->dataTotal - fifo->outputTotal;
		fifo->chunkSize = new_chunk_size;
	}

	switch(fifo->outputState) {
	case MSDIO_IDLE:
		if (fifo->outputTotal < fifo->inputTotal) {
			fifo->outputState = MSDIO_START;
		}
		break;

	case MSDIO_START:
		/* Write the block to the media */
		if (media_is_mapped_write_supported(lun->media)) {
			msd_driver_callback(disktransfer, MEDIA_STATUS_SUCCESS, 0, 0);
			status = LUN_STATUS_SUCCESS;
		} else {
#ifdef MSDIO_WRITE10_CHUNK_SIZE
			status = lun_write(lun, DWORDB(command->pLogicalBlockAddress),
					&fifo->pBuffer[fifo->outputNdx],
					fifo->chunkSize / fifo->blockSize,
					msd_driver_callback, disktransfer);
#else
			status = lun_write(lun, DWORDB(command->pLogicalBlockAddress),
					&fifo->pBuffer[fifo->outputNdx], 1,
					msd_driver_callback, disktransfer);
#endif
		}

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Write10: Failed to start write - ");

			if (!sbc_lun_can_be_written(lun)) {
				sbc_update_sense_data(lun->requestSenseData,
						SBC_SENSE_KEY_NOT_READY, 0, 0);
			}

			fifo->outputState = MSDIO_ERROR;
		} else {
			/* Prepare next state */
			fifo->outputState = MSDIO_WAIT;
		}
		break; /* MSDIO_START */

	case MSDIO_WAIT:
		LIBUSB_TRACE("dWait ");

		/* Check semaphore value */
		if (disktransfer->semaphore > 0) {
			/* Take semaphore and move to next state */
			disktransfer->semaphore--;
			fifo->outputState = MSDIO_NEXT;
		}
		break;

	case MSDIO_NEXT:
		/* Check operation result code */
		if (transfer->status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Write10: Failed to write\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_RECOVERED_ERROR,
					SBC_ASC_TOO_MUCH_WRITE_DATA, 0);
			result = MSDD_STATUS_ERROR;
		}
		else {
			LIBUSB_TRACE("dNxt ");

			/* Update transfer length and block address */

			/* Mapped memory, done */
			if (media_is_mapped_write_supported(lun->media)) {
				command_state->length = 0;
				fifo->outputState = MSDIO_IDLE;
			} else {
				/* Update output index */
				lba = DWORDB(command->pLogicalBlockAddress);
#ifdef MSDIO_WRITE10_CHUNK_SIZE
				lba += fifo->chunkSize / fifo->blockSize;
				MSDIOFifo_IncNdx(fifo->outputNdx, fifo->chunkSize,
						fifo->bufferSize);
				fifo->outputTotal += fifo->chunkSize;
#else
				lba++;
				MSDIOFifo_IncNdx(fifo->outputNdx, fifo->blockSize,
						fifo->bufferSize);
				fifo->outputTotal += fifo->blockSize;
#endif
				STORE_DWORDB(lba, command->pLogicalBlockAddress);

				/* Start Next block */

				/* - All data done? */
				if (fifo->outputTotal >= fifo->dataTotal) {
					fifo->outputState = MSDIO_IDLE;
					command_state->length = 0;
					LIBUSB_TRACE("dDone ");
				}
				/* - Send next? */
				else if (fifo->outputTotal < fifo->inputTotal) {
					fifo->outputState = MSDIO_START;
					LIBUSB_TRACE("dStart ");
				}
				/* - Buffer Null? */
				else {
					fifo->outputState = MSDIO_IDLE;
					fifo->nullCnt ++;
					LIBUSB_TRACE("dfNull%d ", fifo->outputNdx);
				}
			}
		}
		break; /* MSDIO_NEXT */

	case MSDIO_ERROR:
		break;
	}

	return result;
}

/**
 * \brief  Performs a READ (10) command on specified LUN.
 *
 *         The data is first read from the media and then sent to the USB host.
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDDriver_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_read10(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t status;
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	SBCRead10 *command = (SBCRead10*)command_state->cbw.pCommand;
	MSDTransfer *transfer = &(command_state->transfer);
	MSDTransfer *disktransfer = &(command_state->disktransfer);
	MSDIOFifo   *fifo = &lun->ioFifo;
	uint32_t lba, old_chunk_size, new_chunk_size;

	/* Init command state */
	if (command_state->state == 0) {
		command_state->state = SBC_STATE_READ;

		if (!sbc_lun_is_ready(lun)) {
			return MSDD_STATUS_RW;
		}
		else {
			/* Initialize FIFO */

			fifo->dataTotal = command_state->length;
			fifo->blockSize = lun->blockSize *
				media_get_block_size(lun->media);
#ifdef MSDIO_READ10_CHUNK_SIZE
			fifo->chunkSize = max_u32(fifo->blockSize,
						  MSDIO_READ10_CHUNK_SIZE);
#endif
			fifo->fullCnt = 0;
			fifo->nullCnt = 0;

#ifdef MSDIO_FIFO_OFFSET
			/* Enable offset if total size >= 2*bufferSize */
			if (fifo->dataTotal / fifo->bufferSize >= 2)
				fifo->bufferOffset = MSDIO_FIFO_OFFSET;
			else
				fifo->bufferOffset = 0;
#endif

			/* Initialize FIFO output (USB) */
			fifo->outputNdx = 0;
			fifo->outputTotal = 0;
			fifo->outputState = MSDIO_IDLE;
			transfer->semaphore = 0;

			/* Initialize FIFO input (Disk) */
			fifo->inputNdx = 0;
			fifo->inputTotal = 0;
			fifo->inputState = MSDIO_START;
			disktransfer->semaphore = 0;
		}
	}

	/* Check length */
	if (command_state->length == 0) {
		/* Perform the callback! */
		if (lun->dataMonitor) {
			lun->dataMonitor(1, fifo->dataTotal, fifo->nullCnt, fifo->fullCnt);
		}
		return MSDD_STATUS_SUCCESS;
	}

	/* Disk reading task */
	old_chunk_size = fifo->chunkSize;
	if ((fifo->dataTotal - fifo->inputTotal) < fifo->chunkSize) {
		new_chunk_size = fifo->dataTotal - fifo->inputTotal;
		fifo->chunkSize = new_chunk_size;
	}

	switch(fifo->inputState) {
	case MSDIO_IDLE:
		if (fifo->inputTotal < fifo->dataTotal &&
				fifo->inputTotal - fifo->outputTotal < fifo->bufferSize) {
			fifo->inputState = MSDIO_START;
		}
		break;

	case MSDIO_START:
		/* Read one block of data from the media */
		if (media_is_mapped_read_supported(lun->media)) {
			/* Data are in memory already. We only need to validate
			 * the block range. */
			status = lun_access(lun,
					DWORDB(command->pLogicalBlockAddress),
					WORDB(command->pTransferLength), 0);
			msd_driver_callback(disktransfer,
					status == USBD_STATUS_SUCCESS
					? MEDIA_STATUS_SUCCESS
					: MEDIA_STATUS_ERROR, 0, 0);
		} else {
#ifdef MSDIO_READ10_CHUNK_SIZE
			status = lun_read(lun, DWORDB(command->pLogicalBlockAddress),
					&fifo->pBuffer[fifo->inputNdx],
					fifo->chunkSize / fifo->blockSize,
					msd_driver_callback, disktransfer);
#else
			status = lun_read(lun, DWORDB(command->pLogicalBlockAddress),
					&fifo->pBuffer[fifo->inputNdx], 1,
					msd_driver_callback, disktransfer);
#endif
		}

		/* Check operation result code */
		if (status != LUN_STATUS_SUCCESS) {
			trace_warning("RBC_Read10: Failed to start reading\n\r");
			if (sbc_lun_is_ready(lun))
				sbc_update_sense_data(lun->requestSenseData,
						SBC_SENSE_KEY_RECOVERED_ERROR,
						SBC_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE, 0);
			else
				sbc_update_sense_data(lun->requestSenseData,
						SBC_SENSE_KEY_NOT_READY,
						SBC_ASC_LOGICAL_UNIT_NOT_READY, 0);
			fifo->inputState = MSDIO_ERROR;
		} else {
			LIBUSB_TRACE("dRd ");

			/* Move to next command state */
			fifo->inputState = MSDIO_WAIT;
		}
		break; /* MSDIO_START */

	case MSDIO_WAIT:
		/* Check semaphore value */
		if (disktransfer->semaphore > 0) {
			LIBUSB_TRACE("dOk ");
			disktransfer->semaphore--;
			fifo->inputState = MSDIO_NEXT;
		}
		break;

	case MSDIO_NEXT:
		/* Check the operation result code */
		if (disktransfer->status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Read10: Failed to read media\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_RECOVERED_ERROR,
					SBC_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE, 0);
			result = MSDD_STATUS_ERROR;
		} else {
			LIBUSB_TRACE("dNxt ");

			if (media_is_mapped_read_supported(lun->media)) {
				/* All data is ready */
				fifo->inputState = MSDIO_IDLE;
				fifo->inputTotal = fifo->dataTotal;
			} else {
				/* Update block address, and input index */
				lba = DWORDB(command->pLogicalBlockAddress);
#ifdef MSDIO_READ10_CHUNK_SIZE
				lba += fifo->chunkSize / fifo->blockSize;
				MSDIOFifo_IncNdx(fifo->inputNdx, fifo->chunkSize,
						fifo->bufferSize);
				fifo->inputTotal += fifo->chunkSize;
#else
				lba++;
				MSDIOFifo_IncNdx(fifo->inputNdx, fifo->blockSize,
						fifo->bufferSize);
				fifo->inputTotal += fifo->blockSize;
#endif
				STORE_DWORDB(lba, command->pLogicalBlockAddress);

				/* Start Next block */

				/* - All Data done? */
				if (fifo->inputTotal >= fifo->dataTotal) {
					LIBUSB_TRACE("dDone ");
					fifo->inputState = MSDIO_IDLE;
				}
				/* - Buffer full? */
				else if (fifo->inputNdx == fifo->outputNdx) {
					LIBUSB_TRACE("dfFull%d ", (int)fifo->inputNdx);
					fifo->inputState = MSDIO_IDLE;
					fifo->fullCnt ++;
				}
				/* - More data to transfer? */
				else if (fifo->inputTotal < fifo->dataTotal) {
					LIBUSB_TRACE("dStart ");
					fifo->inputState = MSDIO_START;
				}
			}
		}
		break;

	case MSDIO_ERROR:
		break;
	}

	fifo->chunkSize = old_chunk_size;

	/* USB sending task */
	if ((fifo->dataTotal - fifo->outputTotal) < fifo->chunkSize) {
		new_chunk_size = fifo->dataTotal - fifo->outputTotal;
		fifo->chunkSize = new_chunk_size;
	}

	switch(fifo->outputState) {
	case MSDIO_IDLE:
		if (fifo->outputTotal < fifo->inputTotal) {
#ifdef MSDIO_FIFO_OFFSET
			/* Offset buffer the input data */
			if (fifo->bufferOffset) {
				if (fifo->inputTotal < fifo->bufferOffset) {
					break;
				}
				fifo->bufferOffset = 0;
			}
#endif
			fifo->outputState = MSDIO_START;
		}
		break;

	case MSDIO_START:
		/* Should not start if there is any disk error */
		if (fifo->inputState == MSDIO_ERROR) {
			fifo->outputState = MSDIO_ERROR;
			break;
		}

		/* Send the block to the host */
		if (media_is_mapped_read_supported(lun->media)) {
			uint32_t mappedAddr = media_get_mapped_address(lun->media,
					DWORDB(command->pLogicalBlockAddress) * lun->blockSize);
			status = usbd_write(command_state->pipeIN,
					(void*)mappedAddr, command_state->length,
					msd_driver_callback, transfer);
		} else {
#ifdef MSDIO_READ10_CHUNK_SIZE
			status = usbd_write(command_state->pipeIN,
					&fifo->pBuffer[fifo->outputNdx], fifo->chunkSize,
					msd_driver_callback, transfer);
#else
			status = usbd_write(command_state->pipeIN,
					&fifo->pBuffer[fifo->outputNdx], fifo->blockSize,
					msd_driver_callback, transfer);
#endif
		}

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Read10: Failed to start to send\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_HARDWARE_ERROR, 0, 0);
			result = MSDD_STATUS_ERROR;
		} else {
			LIBUSB_TRACE("uTx ");

			/* Move to next command state */
			fifo->outputState = MSDIO_WAIT;
		}
		break; /* MSDIO_START */

	case MSDIO_WAIT:
		/* Check semaphore value */
		if (transfer->semaphore > 0) {
			LIBUSB_TRACE("uOk ");
			transfer->semaphore--;
			fifo->outputState = MSDIO_NEXT;
		}
		break;

	case MSDIO_NEXT:
		/* Check operation result code */
		if (transfer->status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_Read10: Failed to send data\n\r");
			sbc_update_sense_data(lun->requestSenseData,
					SBC_SENSE_KEY_HARDWARE_ERROR, 0, 0);
			result = MSDD_STATUS_ERROR;
		} else {
			LIBUSB_TRACE("uNxt ");

			if (media_is_mapped_read_supported(lun->media)) {
				command_state->length = 0;
			} else {
				/* Update output index */
#ifdef MSDIO_READ10_CHUNK_SIZE
				MSDIOFifo_IncNdx(fifo->outputNdx, fifo->chunkSize,
						fifo->bufferSize);
				fifo->outputTotal += fifo->chunkSize;
#else
				MSDIOFifo_IncNdx(fifo->outputNdx, fifo->blockSize,
						fifo->bufferSize);
				fifo->outputTotal += fifo->blockSize;
#endif

				/* Start Next block */

				/* - All data done? */
				if (fifo->outputTotal >= fifo->dataTotal) {
					fifo->outputState = MSDIO_IDLE;
					command_state->length = 0;
					LIBUSB_TRACE("uDone ");
				}
				/* - Buffer Null? */
				else if (fifo->inputNdx == fifo->outputNdx) {
					LIBUSB_TRACE("ufNull%d ", (int)fifo->outputNdx);
					fifo->outputState = MSDIO_IDLE;
					fifo->nullCnt ++;
				}
				/* - Send next? */
				else if (fifo->outputTotal < fifo->inputTotal) {
					LIBUSB_TRACE("uStart ");
					fifo->outputState = MSDIO_START;
				}
			}
		}
		break;

	case MSDIO_ERROR:
		break;
	}

	return result;
}

/**
 * \brief  Performs a READ CAPACITY (10) command.
 *
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDD_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_read_capacity10(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	uint8_t status;
	MSDTransfer *transfer = &(command_state->transfer);

	if (!sbc_lun_is_ready(lun)) {
		trace_warning("sbc_read_capacity10: Not Ready!\n\r");
		return MSDD_STATUS_RW;
	}

	/* Initialize command state if needed */
	if (command_state->state == 0) {
		command_state->state = SBC_STATE_WRITE;
	}

	switch (command_state->state) {
	case SBC_STATE_WRITE:
		/* Start the write operation */
		status = usbd_write(command_state->pipeIN,
				lun->readCapacityData, command_state->length,
				msd_driver_callback, transfer);

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_ReadCapacity: Cannot start sending data\n\r");
			result = MSDD_STATUS_ERROR;
		}
		else {
			/* Proceed to next command state */
			LIBUSB_TRACE("Sending ");
			command_state->state = SBC_STATE_WAIT_WRITE;
		}
		break;

	case SBC_STATE_WAIT_WRITE:
		/* Check semaphore value */
		if (transfer->semaphore > 0) {
			/* Take semaphore and terminate command */
			transfer->semaphore--;

			if (transfer->status != USBD_STATUS_SUCCESS) {
				trace_warning("RBC_ReadCapacity: Cannot send data\n\r");
				result = MSDD_STATUS_ERROR;
			}
			else {
				LIBUSB_TRACE("Sent ");
				result = MSDD_STATUS_SUCCESS;
			}
			command_state->length -= transfer->transferred;
		}
		break;
	}

	return result;
}

/**
 * \brief  Handles an INQUIRY command.
 *
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDDriver_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_inquiry(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	uint8_t status;
	MSDTransfer *transfer = &(command_state->transfer);

	/* Check if required length is 0 */
	if (command_state->length == 0) {
		/* Nothing to do */
		result = MSDD_STATUS_SUCCESS;
	}
	/* Initialize command state if needed */
	else if (command_state->state == 0) {
		command_state->state = SBC_STATE_WRITE;

		/* Change additional length field of inquiry data */
		lun->inquiryData->bAdditionalLength =
			(uint8_t)(command_state->length - 5);
	}

	switch (command_state->state) {
	case SBC_STATE_WRITE:
		/* Start write operation */
		status = usbd_write(command_state->pipeIN,
				lun->inquiryData, command_state->length,
				msd_driver_callback, transfer);

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("SPC_Inquiry: Cannot start sending data\n\r");
			result = MSDD_STATUS_ERROR;
		} else {
			/* Proceed to next state */
			LIBUSB_TRACE("Sending ");
			command_state->state = SBC_STATE_WAIT_WRITE;
		}
		break;

	case SBC_STATE_WAIT_WRITE:
		/* Check the semaphore value */
		if (transfer->semaphore > 0) {
			/* Take semaphore and terminate command */
			transfer->semaphore--;

			if (transfer->status != USBD_STATUS_SUCCESS) {
				trace_warning("SPC_Inquiry: Data transfer failed\n\r");
				result = MSDD_STATUS_ERROR;
			} else {
				LIBUSB_TRACE("Sent ");
				result = MSDD_STATUS_SUCCESS;
			}

			/* Update length field */
			command_state->length -= transfer->transferred;
		}
		break;
	}

	return result;
}

/**
 * \brief  Performs a REQUEST SENSE command.
 *
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDDriver_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_request_sense(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	uint8_t status;
	MSDTransfer *transfer = &(command_state->transfer);

	/* Check if requested length is zero */
	if (command_state->length == 0) {
		/* Nothing to do */
		result = MSDD_STATUS_SUCCESS;
	}
	/* Initialize command state if needed */
	else if (command_state->state == 0) {
		command_state->state = SBC_STATE_WRITE;
	}

	/* Identify current command state */
	switch (command_state->state) {
	case SBC_STATE_WRITE:
		/* Start transfer */
		status = usbd_write(command_state->pipeIN,
				lun->requestSenseData, command_state->length,
				msd_driver_callback, transfer);

		/* Check result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("RBC_RequestSense: Cannot start sending data\n\r");
			result = MSDD_STATUS_ERROR;
		} else {
			/* Change state */
			command_state->state = SBC_STATE_WAIT_WRITE;
		}
		break;

	case SBC_STATE_WAIT_WRITE:
		/* Check the transfer semaphore */
		if (transfer->semaphore > 0) {
			/* Take semaphore and finish command */
			transfer->semaphore--;

			if (transfer->status != USBD_STATUS_SUCCESS) {
				result = MSDD_STATUS_ERROR;
			} else {
				result = MSDD_STATUS_SUCCESS;
			}

			/* Update length */
			command_state->length -= transfer->transferred;
		}
		break;
	}

	return result;
}

/**
 * \brief  Performs a MODE SENSE (6) command.
 *
 *         This function operates asynchronously and must be called multiple
 *         times to complete. A result code of MSDDriver_STATUS_INCOMPLETE
 *         indicates that at least another call of the method is necessary.
 * \param  lun          Pointer to the LUN affected by the command
 * \param  command_state Current state of the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 * \see    MSDCommandState
 */
static uint8_t sbc_mode_sense6(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	uint8_t status;
	MSDTransfer *transfer = &(command_state->transfer);
	SBCCommand *command = (SBCCommand*)command_state->cbw.pCommand;

	if (!sbc_lun_is_ready(lun)) {
		trace_warning("sbc_mode_sense6: Not Ready!\n\r");
		return MSDD_STATUS_RW;
	}

	/* Check if mode page is supported */
	if (command->modeSense6.bPageCode != SBC_PAGE_RETURN_ALL) {
		return MSDD_STATUS_PARAMETER;
	}

	/* Initialize command state if needed */
	if (command_state->state == 0) {
		command_state->state = SBC_STATE_WRITE;
	}

	/* Check current command state */
	switch (command_state->state) {
	case SBC_STATE_WRITE:
		/* Start transfer */
		status = usbd_write(command_state->pipeIN,
				(void*)&mode_parameter_header6, command_state->length,
				msd_driver_callback, transfer);

		/* Check operation result code */
		if (status != USBD_STATUS_SUCCESS) {
			trace_warning("SPC_ModeSense6: Cannot start data transfer\n\r");
			result = MSDD_STATUS_ERROR;
		} else {
			/* Proceed to next state */
			command_state->state = SBC_STATE_WAIT_WRITE;
		}
		break;

	case SBC_STATE_WAIT_WRITE:
		/* Check semaphore value */
		if (transfer->semaphore > 0) {
			/* Take semaphore and terminate command */
			transfer->semaphore--;

			if (transfer->status != USBD_STATUS_SUCCESS) {
				trace_warning("SPC_ModeSense6: Data transfer failed\n\r");
				result = MSDD_STATUS_ERROR;
			} else {
				result = MSDD_STATUS_SUCCESS;
			}

			/* Update length field */
			command_state->length -= transfer->transferred;
		}
		break;
	}

	return result;
}

/**
 * \brief  Performs a TEST UNIT READY COMMAND command.
 * \param  lun          Pointer to the LUN affected by the command
 * \return Operation result code (SUCCESS, ERROR, INCOMPLETE or PARAMETER)
 * \see    MSDLun
 */
static uint8_t sbc_test_unit_ready(MSDLun *lun)
{
	uint8_t result = MSDD_STATUS_RW;
	uint8_t sense_key = SBC_SENSE_KEY_NO_SENSE;
	uint8_t add_sense_code = 0;
	uint8_t add_sense_code_qual = 0;

	/* Check current media state */
	if (lun->status < LUN_CHANGED) {
		LIBUSB_TRACE("Ejc ");
		sense_key = SBC_SENSE_KEY_NOT_READY;
		add_sense_code = SBC_ASC_MEDIUM_NOT_PRESENT;
	} else if (lun->status == LUN_CHANGED) {
		LIBUSB_TRACE("Chg ");
		sense_key = SBC_SENSE_KEY_UNIT_ATTENTION;
		add_sense_code = SBC_ASC_NOT_READY_TO_READY_CHANGE;
		lun->status = LUN_READY;
	} else {
		switch(media_get_state(lun->media)) {
		case MEDIA_STATE_READY:
			/* Nothing to do */
			LIBUSB_TRACE("Rdy ");
			result = MSDD_STATUS_SUCCESS;
			break;

		case MEDIA_STATE_BUSY:
			LIBUSB_TRACE("Bsy ");
			sense_key = SBC_SENSE_KEY_NOT_READY;
			break;

		default:
			LIBUSB_TRACE("? ");
			sense_key = SBC_SENSE_KEY_NOT_READY;
			add_sense_code = SBC_ASC_MEDIUM_NOT_PRESENT;
			break;
		}
	}

	sbc_update_sense_data(lun->requestSenseData,
			sense_key, add_sense_code, add_sense_code_qual);

	return result;
}

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/
/**
 * \brief  Updates the sense data of a LUN with the given key and codes
 * \param  request_sense_data             Pointer to the sense data to update
 * \param  sense_key                     Sense key
 * \param  additional_sense_code          Additional sense code
 * \param  additional_sense_code_qualifier Additional sense code qualifier
 */
void sbc_update_sense_data(SBCRequestSenseData *request_sense_data,
		uint8_t sense_key, uint8_t additional_sense_code,
		uint8_t additional_sense_code_qualifier)
{
	request_sense_data->bSenseKey = sense_key;
	request_sense_data->bAdditionalSenseCode = additional_sense_code;
	request_sense_data->bAdditionalSenseCodeQualifier =
		additional_sense_code_qualifier;
}

/**
 * \brief  Return information about the transfer length and direction expected
 *         by the device for a particular command.
 * \param  command_ptr Pointer to a buffer holding the command to evaluate
 * \param  length  Expected length of the data transfer
 * \param  type    Expected direction of data transfer
 * \param  lun     Pointer to the LUN affected by the command
 */
bool sbc_get_command_information(void *command_ptr, uint32_t *length,
		uint8_t *type, MSDLun *lun)
{
	SBCCommand *command = (SBCCommand*)command_ptr;
	bool command_supported = true;

	switch (command->bOperationCode) {
	case SBC_INQUIRY:
		(*type) = MSDD_DEVICE_TO_HOST;
		(*length) = WORDB(command->inquiry.pAllocationLength);
		break;

	case SBC_MODE_SENSE_6:
		(*type) = MSDD_DEVICE_TO_HOST;
		if (command->modeSense6.bAllocationLength >
			sizeof(SBCModeParameterHeader6)) {
			*length = sizeof(SBCModeParameterHeader6);
		} else {
			*length = command->modeSense6.bAllocationLength;
		}
		break;

	case SBC_PREVENT_ALLOW_MEDIUM_REMOVAL:
		(*type) = MSDD_NO_TRANSFER;
		break;

	case SBC_REQUEST_SENSE:
		(*type) = MSDD_DEVICE_TO_HOST;
		(*length) = command->requestSense.bAllocationLength;
		break;

	case SBC_TEST_UNIT_READY:
		(*type) = MSDD_NO_TRANSFER;
		break;

	case SBC_READ_CAPACITY_10:
		(*type) = MSDD_DEVICE_TO_HOST;
		(*length) = sizeof(SBCReadCapacity10Data);
		break;

	case SBC_READ_10:
		(*type) = MSDD_DEVICE_TO_HOST;
		(*length) = WORDB(command->read10.pTransferLength) *
			lun->blockSize * media_get_block_size(lun->media);
		break;

	case SBC_WRITE_10:
		(*type) = MSDD_HOST_TO_DEVICE;
		(*length) = WORDB(command->write10.pTransferLength) *
			lun->blockSize * media_get_block_size(lun->media);
		break;

	case SBC_VERIFY_10:
		(*type) = MSDD_NO_TRANSFER;
		break;

	default:
		LIBUSB_TRACE("sbc_get_command_information: unknown command 0x%x\r\n",
				(unsigned)command->bOperationCode);
		command_supported = false;
	}

	/* If length is 0, no transfer is expected */
	if ((*length) == 0) {
		(*type) = MSDD_NO_TRANSFER;
	}

	return command_supported;
}

/**
 * \brief  Processes a SBC command by dispatching it to a subfunction.
 * \param  lun          Pointer to the affected LUN
 * \param  command_state Pointer to the current command state
 * \return Operation result code
 */
uint8_t sbc_process_command(MSDLun *lun, MSDCommandState *command_state)
{
	uint8_t result = MSDD_STATUS_INCOMPLETE;
	SBCCommand *command = (SBCCommand*)command_state->cbw.pCommand;

	switch (command->bOperationCode) {
	case SBC_READ_10:
		/* Perform the Read10 command */
		result = sbc_read10(lun, command_state);
		break;

	case SBC_WRITE_10:
		/* Perform the Write10 command */
		result = sbc_write10(lun, command_state);
		break;

	case SBC_READ_CAPACITY_10:
		/* Perform the ReadCapacity command */
		result = sbc_read_capacity10(lun, command_state);
		break;

	case SBC_VERIFY_10:
		/* Flush media */
		media_flush(lun->media);
		result = MSDD_STATUS_SUCCESS;
		break;

	case SBC_INQUIRY:
		/* Process Inquiry command */
		result = sbc_inquiry(lun, command_state);
		break;

	case SBC_MODE_SENSE_6:
		/* Process ModeSense6 command */
		result = sbc_mode_sense6(lun, command_state);
		break;

	case SBC_TEST_UNIT_READY:
		/* Process TestUnitReady command */
		/*media_flush(lun->media); */
		result = sbc_test_unit_ready(lun);
		break;

	case SBC_REQUEST_SENSE:
		/* Perform the RequestSense command */
		result = sbc_request_sense(lun, command_state);
		break;

	case SBC_PREVENT_ALLOW_MEDIUM_REMOVAL:
		/* Check parameter */
		result = command->mediumRemoval.bPrevent ?
			MSDD_STATUS_PARAMETER : MSDD_STATUS_SUCCESS;
		break;

	case SBC_READ_FORMAT_CAPACITIES:
		result = MSDD_STATUS_PARAMETER;
		break;

	default:
		result = MSDD_STATUS_PARAMETER;
	}

	return result;
}

/**@}*/
