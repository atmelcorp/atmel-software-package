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
 * \section Purpose
 *
 * Definitions, structs, functions  required by a Mass Storage device driver
 * state machine..
 *
 * \section Usage
 *
 * - For a USB device:
 *     -# msdd_state_machine is invoked to run the MSD state machine.
 *
 *-----------------------------------------------------------------------------*/

#ifndef MSDDSTATEMACHINE_H
#define MSDDSTATEMACHINE_H

/** \addtogroup usbd_msd
 *@{
 */

/*-----------------------------------------------------------------------------
 *         Headers
 *-----------------------------------------------------------------------------*/

#include "usb/device/msd/msd.h"
#include "usb/device/msd/msd_lun.h"
#include "usb/device/usbd_driver.h"

/*-----------------------------------------------------------------------------
 *      Definitions
 *-----------------------------------------------------------------------------*/

/** \addtogroup usbd_msd_driver_possible_states MSD Driver Possible states
 *      @{
 *
 * - MSDD_STATE_READ_CBW
 * - MSDD_STATE_WAIT_CBW
 * - MSDD_STATE_PROCESS_CBW
 * - MSDD_STATE_WAIT_HALT
 * - MSDD_STATE_SEND_CSW
 * - MSDD_STATE_WAIT_CSW
 * - MSDD_STATE_WAIT_RESET
 */

/** \brief  Driver is expecting a command block wrapper */
#define MSDD_STATE_READ_CBW              (1 << 0)

/** \brief  Driver is waiting for the transfer to finish */
#define MSDD_STATE_WAIT_CBW              (1 << 1)

/** \brief  Driver is processing the received command */
#define MSDD_STATE_PROCESS_CBW           (1 << 2)

/** \brief  Driver is halted because pipe halt or wait reset */
#define MSDD_STATE_WAIT_HALT             (1 << 3)

/** \brief  Driver is starting the transmission of a command status wrapper */
#define MSDD_STATE_SEND_CSW              (1 << 4)

/** \brief  Driver is waiting for the CSW transmission to finish */
#define MSDD_STATE_WAIT_CSW              (1 << 5)

/** \brief  Driver is waiting for the MassStorageReset */
#define MSDD_STATE_WAIT_RESET            (1 << 6)
/**      @}*/

/** \addtogroup usbd_msd_driver_result_codes MSD Driver Result Codes
 *      @{
 * This page lists result codes for MSD functions.
 *
 * \section Codes
 * - MSDD_STATUS_SUCCESS
 * - MSDD_STATUS_ERROR
 * - MSDD_STATUS_INCOMPLETE
 * - MSDD_STATUS_PARAMETER
 * - MSDD_STATUS_RW
 */

/** \brief  Method was successful */
#define MSDD_STATUS_SUCCESS              0x00

/** \brief  There was an error when trying to perform a method */
#define MSDD_STATUS_ERROR                0x01

/** \brief  No error was encountered but the application should call the
			method again to continue the operation */
#define MSDD_STATUS_INCOMPLETE           0x02

/** \brief  A wrong parameter has been passed to the method */
#define MSDD_STATUS_PARAMETER            0x03

/** \brief An error when reading/writing disk (protected or not present) */
#define MSDD_STATUS_RW                   0x04
/**      @}*/

/** \addtogroup usbd_msd_driver_action_cases MSD Driver Action Cases
 *      @{
 * This page lists actions to perform during the post-processing phase of a
 * command.
 *
 * \section Actions
 * - MSDD_CASE_PHASE_ERROR
 * - MSDD_CASE_STALL_IN
 * - MSDD_CASE_STALL_OUT
 */

/** \brief  Indicates that the CSW should report a phase error */
#define MSDD_CASE_PHASE_ERROR       (1 << 0)

/** \brief  The driver should halt the Bulk IN pipe after the transfer */
#define MSDD_CASE_STALL_IN               (1 << 1)

/** \brief  The driver should halt the Bulk OUT pipe after the transfer */
#define MSDD_CASE_STALL_OUT              (1 << 2)
/**      @}*/

/*------------------------------------------------------------------------------ */

/** \addtogroup usbd_msd_driver_xfr_directions MSD Driver Xfr Directions
 *      @{
 * This page lists possible direction values for a data transfer
 * - MSDD_DEVICE_TO_HOST
 * - MSDD_HOST_TO_DEVICE
 * - MSDD_NO_TRANSFER
 */
/** Data transfer from device to host (READ) */
#define MSDD_DEVICE_TO_HOST              (1 << 3)
/** Data transfer from host to device (WRITE) */
#define MSDD_HOST_TO_DEVICE              (1 << 4)
/** No data transfer */
#define MSDD_NO_TRANSFER                    (1 << 5)
/**      @}*/

/*-----------------------------------------------------------------------------
 *         Types
 *-----------------------------------------------------------------------------*/

/**
 * \typedef MSDTransfer
 * \brief  Structure for holding the result of a USB transfer
 * \see    msd_driver_callback
 */
typedef struct _MSDTransfer {
	 uint32_t transferred; /** Number of bytes transferred */
	 uint32_t remaining;   /** Number of bytes not transferred */
	 uint16_t semaphore;   /** Semaphore to indicate transfer completion */
	 uint16_t status;      /** Operation result code */
} MSDTransfer;

/**
 * \typedef MSDCommandState
 * \brief  Status of an executing command
 * \see    MSDCbw
 * \see    MSDCsw
 * \see    MSDTransfer
 *------------------------------------------------------------------------------*/
typedef struct _MSDCommandState {
	MSCbw           cbw;         /**< Received CBW (31 bytes) */
	uint8_t         reserved1;   /**< Pad up to cache line boundary */
	MSCsw           csw;         /**< CSW to send  (13 bytes) */
	MSDTransfer     transfer;    /**< Current transfer status (USB) */
	MSDTransfer     disktransfer;/**< Current transfer status (Disk) */
	uint32_t        length;      /**< Remaining length of command */
	uint8_t         state;       /**< Current command state */
	uint8_t         postprocess; /**< Actions to perform when command is complete */
	uint8_t         pipeIN;      /**< Pipe ID for input */
	uint8_t         pipeOUT;     /**< Pipe ID for output */
} MSDCommandState;

/**
 * \typedef MSDDriver
 * \brief  MSD driver state variables
 * \see    MSDCommandState
 * \see    MSDLun
 */
typedef struct _MSDDriver {
	/** State of the currently executing command */
	MSDCommandState commandState;
	/** LUN list for the %device. */
	MSDLun *luns;
	/** Associated interface number */
	uint8_t interfaceNb;
	/** Maximum LUN index */
	uint8_t maxLun;
	/** Current state of the driver */
	uint8_t state;
	/** Indicates if the driver is waiting for a reset recovery */
	uint8_t waitResetRecovery;
} MSDDriver;

/*-----------------------------------------------------------------------------
 *      Inline functions
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *      Exported functions
 *-----------------------------------------------------------------------------*/

extern void msdd_state_machine(MSDDriver * pMsdDriver);

/**@}*/

#endif /* #define MSDDSTATEMACHINE_H */

