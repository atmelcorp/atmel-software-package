/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 *  Definitions and prototypes for Controller Area Network (CAN)
 *  peripheral operations.
 */

/** \ingroup lib_chip
 *  \ingroup cand_module
 *  \addtogroup can_module Working with CAN
 *
 *  \section Purpose
 *  Interface for Controller Area Network (CAN).
 *
 *  \section Usage
 *
 *  Before CAN operation, its peripheral clock should be enabled, see
 *  PMC_EnablePeripheral().
 *
 *  Modify CAN registers or register fields with API functions:
 *  - Modify CAN Mode register with can_configure_mode().
 *    - Enable/Disable CAN with can_enable().
 *  - Change CAN interrupt settings with can_enable_it(), can_disable_it(),
 *    get interrupt mask by can_get_it_mask().
 *  - Get CAN status with can_get_status().
 *  - Setup CAN baudrate via can_set_baudrate().
 *  - Start several mailbox transmition through can_command().
 *  - The following functions setup mailboxes for message transfer:
 *    - can_configure_message_mode() : setup _MMRx.
 *    - can_configure_msg_mask() : setup _MARx.
 *    - can_configure_message_id() : setup _MIDx.
 *    - can_set_message() : setup _MDLx and _MDHx.
 *    - can_message_control() : setup _MCRx.
 *  - The following get status and data from mailbox:
 *    - can_get_message() :
 *    - can_get_message_status() :
 */

#ifndef _CAN_H_
#define _CAN_H_
/**@{*/

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"
#include "can/can-bus.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        External function
 *----------------------------------------------------------------------------*/

/* ----------- CAN_MR Operations --------------- */
/**
 * \brief Set CAN Mode Register (CAN_MR)
 * \param can Pointer to Can instance.
 * \param dwMr Mode register settings.
 */
extern void can_configure_mode(Can * can, uint32_t mr);

/**
 * \brief CAN Controller Enable/Disable
 * \param can   Pointer to Can instance.
 * \param enable 1 to enable and 0 to disable.
 */
extern void can_enable(Can * can, uint8_t enable);

/**
 * \brief CAN Low Power Mode Enable/Disable
 * \param can   Pointer to Can instance.
 * \param enable 1 to enable and 0 to disable.
 */
extern void can_enable_low_power(Can * can, uint8_t enable);

/**
 * \brief CAN Autobaud/Listen mode
 * \param can   Pointer to Can instance.
 * \param enable 1 to enable and 0 to disable.
 */
extern void can_enable_autobaud(Can * can, uint8_t enable);

/**
 * \brief CAN Overload Frame Enable/Disable
 * \param can   Pointer to Can instance.
 * \param enable 1 to enable and 0 to disable.
 */
extern void can_enable_overload_frame(Can * can, uint8_t enable);

/**
 * \brief CAN Timestamp capture mode (@EOF/@SOF).
 * \param can      Pointer to Can instance.
 * \param eof      1 for EOF/0 for SOF.
 */
extern void can_enable_timestamp_eof(Can * can, uint8_t eof);

/**
 * \brief CAN Time Triggered Mode Enable/Disable
 * \param can      Pointer to Can instance.
 * \param enable    Enable/Disable Time Trigger Mode.
 */
extern void can_enable_time_trigger_mode(Can * can, uint8_t enable);

/**
 * \brief CAN Timer Freeze Enable/Disable
 * \param can      Pointer to Can instance.
 * \param enable    Enable/Disable Timer Freeze.
 */
extern void can_enable_timer_freeze(Can * can, uint8_t enable);

/**
 * \brief CAN Repeat Disable/Enable.
 * \param can      Pointer to Can instance.
 * \param disable  Disable/Enable Repeat.
 */
extern void can_disable_repeat(Can * can, uint8_t disable);

/**
 * \brief CAN Interrupts Enable
 * \param can      Pointer to Can instance.
 * \param sources  Interrupt sources bits.
 */
extern void can_enable_it(Can * can, uint32_t sources);

/**
 * \brief CAN Interrupts Disable
 * \param can      Pointer to Can instance.
 * \param sources Interrupt sources bits.
 */
extern void can_disable_it(Can * can, uint32_t sources);

/**
 * \brief Return CAN Interrupts Masks
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_it_mask(Can * can);

/**
 * \brief Return CAN Statuses
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_status(Can * can);

/**
 * \brief Set CAN baudrate register
 * \param can      Pointer to Can instance.
 * \param baudrate Setting value for CAN_BR.
 */
extern void can_configure_baudrate(Can * can, uint32_t baudrate);

/**
 * \brief Set CAN Sampling Mode
 * \param can      Pointer to Can instance.
 * \param avg3     Sample 3 times/sample once at sample point.
 */
extern void can_set_sampling_mode(Can * can, uint8_t avg3);

/**
 * \brief Return CAN Timer Register
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_timer(Can * can);

/**
 * \brief Return CAN TimeStamp Register
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_timestamp(Can * can);

/**
 * \brief Return Error Count (TEC << 16) + REC
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_error_count(Can * can);

/**
 * \brief Return Receive Error Count
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_rx_error_count(Can * can);

/**
 * \brief Return Transmit Error Count
 * \param can      Pointer to Can instance.
 */
extern uint32_t can_get_tx_error_count(Can * can);

/**
 * \brief Set Transfer Command Register to initialize transfer requests.
 * \param can       Pointer to Can instance.
 * \param requests  Transfer Command Requests.
 */
extern void can_command(Can * can, uint32_t requests);

/**
 * \brief Resets CAN internal timer counter.
 * \param can       Pointer to Can instance.
 */
extern void can_reset_timer(Can * can);

/**
 * \brief Request transfer on mailbox.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_tx(Can * can, uint8_t mailbox);

/**
 * \brief Abort transfer on several mailboxes.
 * \param can       Pointer to Can instance.
 * \param aborts    Abort requests.
 */
extern void can_abort(Can * can, uint32_t aborts);

/**
 * \brief Abort transfer on single mailbox.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_abort_mailbox(Can * can, uint8_t mailbox);

/**
 * \brief Configure CAN Message Mode (_MMRx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param mr        Mode settings.
 */
extern void can_configure_message_mode(Can * can, uint8_t mailbox, uint32_t mr);

/**
 * \brief Return CAN Message Mode (_MMRx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_get_message_mode(Can * can, uint8_t mailbox);

/**
 * \brief Set Mailbox Timemark for Time Triggered Mode.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param timemarks Mailbox timemarks.
 */
extern void can_set_timemark(Can * can, uint8_t mailbox, uint8_t timemarks);

/**
 * \brief Set Mailbox Priority.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param priority  Mailbox Priority.
 */
extern void can_set_priority(Can * can, uint8_t mailbox, uint8_t priority);

/**
 * \brief Set Mailbox Object Type.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param type      Mailbox Object Type.
 */
extern void can_set_object_type(Can * can, uint8_t mailbox, uint8_t type);

/**
 * \brief Configure CAN Message Acceptance Mask (_MAMx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param mam       The setting value for _MAMx.
 */
extern void can_configure_msg_mask(Can * can, uint8_t mailbox, uint32_t mam);

/**
 * \brief Return CAN Message Acceptance Mask (_MAMx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_get_msg_mask(Can * can, uint8_t mailbox);

/**
 * \brief Configure Identifier Version in CAN Message Acceptance Mask (_MAMx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param cfg       IDvA and IDvB/IDvA only Identify.
 */
extern void can_configure_identifier_mask(Can * can, uint8_t mailbox, uint8_t cfg);

/**
 * \brief Set Identifier for standard frame mode (MIDvA) mask
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param id        Identifier for standard frame mode.
 */
extern void can_set_midva_mask(Can * can, uint8_t mailbox, uint32_t id);

/**
 * \brief Set Complementary bits for identifier in extended frame mode (MIDvB) mask
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param id        Identifier for extended frame mode.
 */
extern void can_set_midvb_mask(Can * can, uint8_t mailbox, uint32_t id);

/**
 * \brief Configure CAN Message ID (_MIDx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param mid       The setting value for _MIDx.
 */
extern void can_configure_message_id(Can * can, uint8_t mailbox, uint32_t mid);

/**
 * \brief Return CAN Message ID (_MIDx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_get_message_id(Can * can, uint8_t mailbox);

/**
 * \brief Configure Identifier Version in CAN Message ID register (_MIDx)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param ver       2.0 Part B/2.0 Part A.
 */
extern void can_configure_id_ver(Can * can, uint8_t mailbox, uint8_t ver);

/**
 * \brief Set Identifier for standard frame mode (MIDvA) value
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param id        Identifier for standard frame mode.
 */
extern void can_set_midva(Can * can, uint8_t mailbox, uint32_t id);

/**
 * \brief Set Complementary bits for identifier in extended frame mode (MIDvB) value
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param id        Identifier for extended frame mode.
 */
extern void can_set_midvb(Can * can, uint8_t mailbox, uint32_t id);

/**
 * \brief Return CAN Message Family ID (Masked ID)
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_get_family_id(Can * can, uint8_t mailbox);

/**
 * \brief Return CAN Message Status
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_get_message_status(Can * can, uint8_t mailbox);

/**
 * \brief Return CAN Message Data Low
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_set_message_datal(Can * can, uint8_t mailbox, uint32_t data_l);

/**
 * \brief Set CAN Message Data Low
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param data_l    Data Low Value.
 */
extern uint32_t can_get_message_datal(Can * can, uint8_t mailbox);

/**
 * \brief Set CAN Message Data High
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param data_h    Data High Value.
 */
extern void can_get_message_datah(Can * can, uint8_t mailbox, uint32_t data_h);

/**
 * \brief Return CAN Message Data High
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint32_t can_set_message_datah(Can * can, uint8_t mailbox);

/**
 * \brief Copy DW array to CAN Message Data.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param pdata     Pointer to a buffer for data.
 */
extern void can_set_message(Can * can, uint8_t mailbox, uint32_t * pdata);

/**
 * \brief Copy CAN Message Data to DW array.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param pdata     Pointer to a buffer for data.
 */
extern void can_get_message(Can * can, uint8_t mailbox, uint32_t * pdata);

/**
 * \brief Set CAN Message Data in u64
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_set_message_data64(Can * can, uint8_t mailbox, uint64_t u64);

/**
 * \brief Return CAN Message Data in u64
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern uint64_t can_get_message_data64(Can * can, uint8_t mailbox);

/**
 * \brief Set CAN Message Control Register (_MCRx).
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param ctrl      Control value.
 */
extern void can_message_control(Can * can, uint8_t mailbox, uint32_t ctrl);

/**
 * \brief Start remote frame.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_message_remote(Can * can, uint8_t mailbox);

/**
 * \brief Abort transmission.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_message_abort(Can * can, uint8_t mailbox);

/**
 * \brief Start transmission.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 * \param len       Message length.
 */
extern void can_message_tx(Can * can, uint8_t mailbox, uint8_t len);

/**
 * \brief Start reception.
 * \param can       Pointer to Can instance.
 * \param mailbox   Mailbox number.
 */
extern void can_message_rx(Can * can, uint8_t mailbox);

#include "cand.h"
/**@}*/
#endif /* #ifndef _CAN_H_ */
