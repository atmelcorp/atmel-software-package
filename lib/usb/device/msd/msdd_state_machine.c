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

/*-----------------------------------------------------------------------------
 *      Includes
 *-----------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/msd/sbc_methods.h"
#include "usb/device/msd/msdd_state_machine.h"

/*-----------------------------------------------------------------------------
 *      Internal functions
 *-----------------------------------------------------------------------------*/

/**
 * This function is to be used as a callback for USB or LUN transfers.
 * \param  arg         Pointer to the transfer structure to update
 * \param  status      Operation result code
 * \param  transferred Number of bytes transferred by the command
 * \param  remaining   Number of bytes not transferred
 */
static void msd_driver_callback(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	MSDTransfer *transfer = (MSDTransfer *)arg;
	if (transfer->semaphore == 0) {
		transfer->status = status;
		transfer->transferred = transferred;
		transfer->remaining = remaining;
		transfer->semaphore++;
	}
}

/**
 * Returns the expected transfer length and direction (IN, OUT or don't care)
 * from the host point-of-view.
 * \param  cbw     Pointer to the CBW to examinate
 * \param  pLength Expected length of command
 * \param  pType   Expected direction of command
 */
static void msdd_get_command_information(MSCbw *cbw,
		uint32_t *length, uint8_t *type)
{
	/* Expected host transfer direction and length */
	(*length) = cbw->dCBWDataTransferLength;

	if (*length == 0) {
		(*type) = MSDD_NO_TRANSFER;
	} else if ((cbw->bmCBWFlags & MSD_CBW_DEVICE_TO_HOST) != 0) {
		(*type) = MSDD_DEVICE_TO_HOST;
	} else {
		(*type) = MSDD_HOST_TO_DEVICE;
	}
}

/**
 * Pre-processes a command by checking the differences between the host and
 * device expectations in term of transfer type and length.
 * Once one of the thirteen cases is identified, the actions to do during the
 * post-processing phase are stored in the dCase variable of the command
 * state.
 * \param  driver Pointer to a MSDDriver instance
 * \return 1 if the command is supported, false otherwise
 */
static bool msdd_preprocess_command(MSDDriver *driver)
{
	uint32_t host_length = 0;
	uint32_t device_length = 0;
	uint8_t host_type;
	uint8_t device_type;
	bool command_supported;
	MSDCommandState *command_state = &(driver->commandState);
	MSCsw           *csw = &(command_state->csw);
	MSCbw           *cbw = &(command_state->cbw);
	MSDLun          *lun = &(driver->luns[(uint8_t)cbw->bCBWLUN]);

	/* Get information about the command */
	/* Host-side */
	msdd_get_command_information(cbw, &host_length, &host_type);

	/* Device-side */
	command_supported = sbc_get_command_information(cbw->pCommand, &device_length, &device_type, lun);

	/* Initialize data residue and result status */
	csw->dCSWDataResidue = 0;
	csw->bCSWStatus = MSD_CSW_COMMAND_PASSED;

	/* Check if the command is supported */
	if (command_supported) {
		/* Identify the command case */
		if (host_type == MSDD_NO_TRANSFER) {
			if (device_type == MSDD_NO_TRANSFER) {
				/* Case 1  (Hn = Dn) */
				command_state->postprocess = 0;
				command_state->length = 0;
				csw->bCSWStatus = MSD_CSW_COMMAND_PASSED;
			} else if (device_type == MSDD_DEVICE_TO_HOST) {
				/* Case 2  (Hn < Di) */
				trace_warning("msdd_preprocess_command: Case 2\n\r");
				command_state->postprocess = MSDD_CASE_STALL_IN;
				command_state->length = 0;
				csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
			} else {
				/* Case 3  (Hn < Do) */
				trace_warning("msdd_preprocess_command: Case 3\n\r");
				command_state->postprocess = MSDD_CASE_STALL_IN;
				command_state->length = 0;
				csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
			}
		} else if (host_type == MSDD_DEVICE_TO_HOST) {
			if (device_type == MSDD_NO_TRANSFER) {
				/* Case 4  (Hi > Dn) */
				trace_warning("msdd_preprocess_command: Case 4\n\r");
				command_state->postprocess = MSDD_CASE_STALL_IN;
				command_state->length = 0;
				csw->dCSWDataResidue = host_length;
			} else if (device_type == MSDD_DEVICE_TO_HOST) {
				if (host_length > device_length) {
					/* Case 5  (Hi > Di) */
					trace_warning("msdd_preprocess_command: Case 5\n\r");
					command_state->postprocess = MSDD_CASE_STALL_IN;
					command_state->length = device_length;
					csw->dCSWDataResidue = host_length - device_length;
				} else if (host_length == device_length) {
					/* Case 6  (Hi = Di) */
					command_state->postprocess = 0;
					command_state->length = device_length;
				} else {
					/* Case 7  (Hi < Di) */
					trace_warning("msdd_preprocess_command: Case 7\n\r");
					command_state->postprocess = MSDD_CASE_STALL_IN;
					command_state->length = host_length;
					csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;;
				}
			} else {
				/* Case 8  (Hi <> Do) */
				trace_warning("msdd_preprocess_command: Case 8\n\r");
				command_state->postprocess = MSDD_CASE_STALL_IN;
				command_state->length = 0;
				csw->dCSWDataResidue = host_length;
				csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
			}
		} else if (host_type == MSDD_HOST_TO_DEVICE) {
			if (device_type == MSDD_NO_TRANSFER) {
				/* Case 9  (Ho > Dn) */
				command_state->postprocess = MSDD_CASE_STALL_OUT;
				command_state->length = 0;
				csw->dCSWDataResidue = host_length;
				csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
			} else if (device_type == MSDD_DEVICE_TO_HOST) {
				/* Case 10 (Ho <> Di) */
				command_state->postprocess = MSDD_CASE_STALL_OUT;
				command_state->length = 0;
				csw->dCSWDataResidue = host_length;
				csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
			} else {
				if (host_length > device_length) {
					/* Case 11 (Ho > Do) */
					command_state->postprocess = MSDD_CASE_STALL_OUT;
					command_state->length = 0;
					csw->dCSWDataResidue = device_length;
				} else if (host_length == device_length) {
					/* Case 12 (Ho = Do) */
					command_state->postprocess = 0;
					command_state->length = device_length;
				} else {
					/* Case 13 (Ho < Do) */
					command_state->postprocess = MSDD_CASE_STALL_OUT;
					command_state->length = host_length;
					csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
				}
			}
		}
	}

	return command_supported;
}

/**
 * Post-processes a command given the case identified during the
 * pre-processing step.
 * Depending on the case, one of the following actions can be done:
 *           - Bulk IN endpoint is stalled
 *           - Bulk OUT endpoint is stalled
 *           - CSW status set to phase error
 * \param  driver Pointer to a MSDDriver instance
 * \return If the device is halted
 */
static bool msdd_postprocess_command(MSDDriver *driver)
{
	MSDCommandState *command_state = &(driver->commandState);
	MSCsw *csw = &(command_state->csw);
	bool has_halted = false;

	/* Set CSW status code to phase error ? */
	if ((command_state->postprocess & MSDD_CASE_PHASE_ERROR) != 0) {

		LIBUSB_TRACE("PhaseErr ");
		csw->bCSWStatus = MSD_CSW_PHASE_ERROR;
	}

	/* STALL Bulk IN endpoint ? */
	if ((command_state->postprocess & MSDD_CASE_STALL_IN) != 0) {
		LIBUSB_TRACE("StallIn ");
		usbd_halt(command_state->pipeIN);
		has_halted = true;
	}

	/* STALL Bulk OUT endpoint ? */
	if ((command_state->postprocess & MSDD_CASE_STALL_OUT) != 0) {
		LIBUSB_TRACE("StallOut ");
		usbd_halt(command_state->pipeOUT);
		has_halted = true;
	}

	return has_halted;
}

/**
 * Processes the latest command received by the %device.
 * \param  driver Pointer to a MSDDriver instance
 * \return 1 if the command has been completed, false otherwise.
 */
static unsigned char msdd_process_command(MSDDriver * driver)
{
	unsigned char   status;
	MSDCommandState *command_state = &(driver->commandState);
	MSCbw           *cbw = &(command_state->cbw);
	MSCsw           *csw = &(command_state->csw);
	MSDLun          *lun = &(driver->luns[(unsigned char) cbw->bCBWLUN]);
	bool command_complete = true;

	/* Check if LUN is valid */
	if (cbw->bCBWLUN > driver->maxLun) {
		trace_warning("msdd_process_command: LUN %d not exist\n\r",
				cbw->bCBWLUN);
		status = MSDD_STATUS_ERROR;
	} else {
		/* Process command */
		if (driver->maxLun > 0) {
			LIBUSB_TRACE("LUN%d ", cbw->bCBWLUN);
		}

		status = sbc_process_command(lun, command_state);
	}

	/* Check command result code */
	switch (status) {
	case MSDD_STATUS_PARAMETER:
		LIBUSB_TRACE("msdd_process_command: Unknown cmd 0x%02X\n\r",
			cbw->pCommand[0]);

		/* Update sense data */
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_ILLEGAL_REQUEST,
				SBC_ASC_INVALID_FIELD_IN_CDB, 0);

		/* Result codes */
		csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;

		/* stall the request, IN or OUT */
		if (((cbw->bmCBWFlags & MSD_CBW_DEVICE_TO_HOST) == 0)
			&& (cbw->dCBWDataTransferLength > 0)) {

			/* Stall the OUT endpoint : host to device */
			command_state->postprocess = MSDD_CASE_STALL_OUT;
			LIBUSB_TRACE("StaOUT ");
		} else {
			/* Stall the IN endpoint : device to host */
			command_state->postprocess = MSDD_CASE_STALL_IN;
			LIBUSB_TRACE("StaIN ");
		}
		break;

	case MSDD_STATUS_ERROR:
		LIBUSB_TRACE("MSD_ProcessCommand: Cmd %x fail\n\r",
				   (unsigned)command_state->cbw.pCommand[0]);

		/* Update sense data */
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_MEDIUM_ERROR,
				SBC_ASC_INVALID_FIELD_IN_CDB, 0);

		/* Result codes */
		csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
		break;

	case MSDD_STATUS_RW:
		csw->bCSWStatus = MSD_CSW_COMMAND_FAILED;
		break;

	case MSDD_STATUS_INCOMPLETE:
		command_complete = false;

		/* Update sense data */
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_NO_SENSE, 0, 0);

		break;

	case MSDD_STATUS_SUCCESS:
		/* Update sense data */
		sbc_update_sense_data(lun->requestSenseData,
				SBC_SENSE_KEY_NO_SENSE, 0, 0);

		break;
	}

	/* Check if command has been completed */
	if (command_complete) {
		LIBUSB_TRACE("Cplt ");

		/* Adjust data residue */
		if (command_state->length != 0) {
			csw->dCSWDataResidue += command_state->length;

			/* STALL the endpoint waiting for data */
			if ((cbw->bmCBWFlags & MSD_CBW_DEVICE_TO_HOST) == 0) {
				/* Stall the OUT endpoint : host to device */
				command_state->postprocess = MSDD_CASE_STALL_OUT;
				LIBUSB_TRACE("StaOUT ");
			} else {
				/* Stall the IN endpoint : device to host */
				command_state->postprocess = MSDD_CASE_STALL_IN;
				LIBUSB_TRACE("StaIN ");
			}
		}

		/* Reset command state */
		command_state->state = 0;
	}

	return command_complete;
}

/**
 * State machine for the MSD %device driver
 * \param  driver Pointer to a MSDDriver instance
 */
void msdd_state_machine(MSDDriver * driver)
{
	MSDCommandState *command_state = &(driver->commandState);
	MSCbw           *cbw = &(command_state->cbw);
	MSCsw           *csw = &(command_state->csw);
	MSDTransfer     *transfer = &(command_state->transfer);
	unsigned char   status;

	/* Identify current driver state */
	switch (driver->state) {
	case MSDD_STATE_READ_CBW:
		LIBUSB_TRACE("<ReadCBW>");

		if (driver->waitResetRecovery) {
			LIBUSB_TRACE("<WR!>");
			break;
		}
		
		if (!usbd_get_data_size(command_state->pipeOUT)) {
			LIBUSB_TRACE("<NoData!>");
			break;
		}
		/* Start the CBW read operation */
		transfer->semaphore = 0;
		status = usbd_read(command_state->pipeOUT, cbw, MSD_CBW_SIZE,
				msd_driver_callback, transfer);

		/* Check operation result code */
		if (status == USBD_STATUS_SUCCESS) {
			/* If the command was successful, wait for transfer */
			driver->state = MSDD_STATE_WAIT_CBW;
		}
		break;

	case MSDD_STATE_WAIT_CBW:
		//LIBUSB_TRACE("<WaitCBW>");

		/* Check transfer semaphore */
		if (transfer->semaphore > 0) {
			/* Check if transfer was successful */
			if (transfer->status == USBD_STATUS_SUCCESS) {
				LIBUSB_TRACE("<GotCSW>");
				/* Process received command */
				driver->state = MSDD_STATE_PROCESS_CBW;
				/* Take semaphore and terminate transfer */
				transfer->semaphore--;
			} else if (transfer->status == USBD_STATUS_RESET) {
				trace_warning("msdd_state_machine: EP resetted\n\r");
				driver->state = MSDD_STATE_READ_CBW;
			} else {
				trace_warning("msdd_state_machine: Failed to read CBW\n\r");
				driver->state = MSDD_STATE_READ_CBW;
			}
		}
		break;

	case MSDD_STATE_PROCESS_CBW:
		LIBUSB_TRACE("<ProcessCBW>");

		/* Check if this is a new command */
		if (command_state->state == 0) {
			/* Copy the CBW tag */
			csw->dCSWTag = cbw->dCBWTag;

			/* Check that the CBW is 31 bytes long and check CBW Signature */
			if ((transfer->transferred != MSD_CBW_SIZE) ||
					(cbw->dCBWSignature != MSD_CBW_SIGNATURE)) {
				LIBUSB_TRACE("msdd_state_machine: Invalid CBW (len %d) (signature 0x%08x)\n\r",
					(int)transfer->transferred, (unsigned)cbw->dCBWSignature);

				/* Wait for a reset recovery */
				driver->waitResetRecovery = 1;

				/* Halt the Bulk-IN and Bulk-OUT pipes */
				usbd_halt(command_state->pipeIN);
				usbd_halt(command_state->pipeOUT);

				driver->state = MSDD_STATE_READ_CBW;
				break;
			} else {
				/* Pre-process command */
				msdd_preprocess_command(driver);
			}
		}

		/* Process command */
		if (csw->bCSWStatus == MSD_CSW_COMMAND_PASSED) {
			if (!msdd_process_command(driver)) {
				/* skip postprocess if processing failed */
				LIBUSB_TRACE("<!>");
				break;
			}
		}

		/* Post-process command if it is finished */
		if (msdd_postprocess_command(driver)) {
			LIBUSB_TRACE("WaitHALT ");
			driver->state = MSDD_STATE_WAIT_HALT;
		} else {
			driver->state = MSDD_STATE_SEND_CSW;
		}
		break;

	case MSDD_STATE_SEND_CSW:
		LIBUSB_TRACE("<SendCSW>");

		/* Set signature */
		csw->dCSWSignature = MSD_CSW_SIGNATURE;

		/* Start the CSW write operation */
		status = usbd_write(command_state->pipeIN, csw, MSD_CSW_SIZE,
				msd_driver_callback, transfer);

		/* Check operation result code */
		if (status == USBD_STATUS_SUCCESS) {
			/* Wait for end of transfer */
			driver->state = MSDD_STATE_WAIT_CSW;
		}
		break;

	case MSDD_STATE_WAIT_CSW:
		//LIBUSB_TRACE("<WaitCSW>");

		/* Check transfer semaphore */
		if (transfer->semaphore > 0) {
			/* Take semaphore and terminate transfer */
			transfer->semaphore--;

			/* Check if transfer was successful */
			if (transfer->status == USBD_STATUS_RESET) {
				trace_warning("msdd_state_machine: EP resetted\n\r");
			} else if (transfer->status == USBD_STATUS_ABORTED) {
				trace_warning("msdd_state_machine: Failed to send CSW\n\r");
			} else {
				LIBUSB_TRACE("<SentCSW>");
			}

			/* Read new CBW */
			driver->state = MSDD_STATE_READ_CBW;
		}
		break;

	case MSDD_STATE_WAIT_HALT:
		//LIBUSB_TRACE("<WaitHalt>");

		if (!usbd_is_halted(command_state->pipeIN)) {
			driver->state = MSDD_STATE_SEND_CSW;
		}
		break;
	}
}

/**@}*/
