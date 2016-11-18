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
 * \section Purpose
 *
 * Controller Area Network with Flexible Data-rate.
 * Interface for configuring and using the MCAN peripheral.
 */

#ifndef _MCAN_H_
#define _MCAN_H_

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <assert.h>

#include "can/can-bus.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

enum mcan_dlc
{
	CAN_DLC_0 = 0,
	CAN_DLC_1 = 1,
	CAN_DLC_2 = 2,
	CAN_DLC_3 = 3,
	CAN_DLC_4 = 4,
	CAN_DLC_5 = 5,
	CAN_DLC_6 = 6,
	CAN_DLC_7 = 7,
	CAN_DLC_8 = 8,
	CAN_DLC_12 = 9,
	CAN_DLC_16 = 10,
	CAN_DLC_20 = 11,
	CAN_DLC_24 = 12,
	CAN_DLC_32 = 13,
	CAN_DLC_48 = 14,
	CAN_DLC_64 = 15
};

/* Flag signalling a standard (11-bit) message identifiers */
#define CAN_STD_MSG_ID (0x0u << 30)
/* Flag to be bitwise or'ed to extended (29-bit) message identifiers */
#define CAN_EXT_MSG_ID (0x1u << 30)

struct mcan_msg_info
{
	uint32_t id;
	uint32_t timestamp;
	uint8_t *data;
	uint8_t full_len;
	uint8_t data_len;
};

/*----------------------------------------------------------------------------
 *         Exported symbols
 *----------------------------------------------------------------------------*/

static inline void mcan_set_base_addr_msb16(Mcan *mcan, uint32_t base_addr)
{
	/* Configure the MSB of the Message RAM Base Address */
	uint32_t val = SFR->SFR_CAN;

	if (MCAN0 == mcan)
		SFR->SFR_CAN = (val & ~SFR_CAN_EXT_MEM_CAN0_ADDR_Msk)
			| SFR_CAN_EXT_MEM_CAN0_ADDR(base_addr >> 16);
	else
		SFR->SFR_CAN = (val & ~SFR_CAN_EXT_MEM_CAN1_ADDR_Msk)
			| SFR_CAN_EXT_MEM_CAN1_ADDR(base_addr >> 16);
}

static inline uint32_t mcan_get_status(Mcan *mcan)
{
	return mcan->MCAN_IR;
}

static inline void mcan_clear_status(Mcan *mcan, uint32_t sources)
{
	mcan->MCAN_IR = sources;
}

static inline void mcan_enable_it(Mcan *mcan, uint32_t sources)
{
	mcan->MCAN_IE |= sources;
}

static inline void mcan_disable_it(Mcan *mcan, uint32_t sources)
{
	mcan->MCAN_IE &= (~sources);
}

static inline void mcan_line0_it(Mcan *mcan, uint32_t sources)
{
	mcan->MCAN_ILS &= (~sources);
}

static inline void mcan_line1_it(Mcan *mcan, uint32_t sources)
{
	mcan->MCAN_ILS |= sources;
}

static inline void mcan_enable_line_it(Mcan *mcan, uint32_t line_mask)
{
	mcan->MCAN_ILE |= (line_mask & 3);
}

static inline void mcan_disable_line_it(Mcan *mcan, uint32_t line_mask)
{
	mcan->MCAN_ILE &= (~(line_mask & 3));
}

static inline void mcan_rx_fifo0_ack(Mcan *mcan, uint32_t index)
{
	mcan->MCAN_RXF0A = MCAN_RXF0A_F0AI(index);
}

static inline void mcan_rx_fifo1_ack(Mcan *mcan, uint32_t index)
{
	mcan->MCAN_RXF1A = MCAN_RXF1A_F1AI(index);
}

static inline bool mcan_is_enabled(Mcan *mcan)
{
	return ((mcan->MCAN_CCCR & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_DISABLED);
}

static inline bool mcan_is_extended_id(uint32_t msg_id)
{
	return msg_id & CAN_EXT_MSG_ID ? true : false;
}

static inline uint32_t mcan_get_id(uint32_t msg_id)
{
	return msg_id & CAN_EXT_MSG_ID ? msg_id & 0x1fffffff : msg_id & 0x7ff;
}

static inline bool mcan_is_tx_complete(Mcan *mcan)
{
	return mcan->MCAN_IR & MCAN_IR_TC ? true : false;
}

static inline void mcan_clear_tx_flag(Mcan *mcan)
{
	mcan->MCAN_IR = MCAN_IR_TC;
}

static inline bool mcan_rx_array_data(Mcan *mcan)
{
	return mcan->MCAN_IR & MCAN_IR_DRX ? true : false;
}

static inline void mcan_clear_rx_array_flag(Mcan *mcan)
{
	mcan->MCAN_IR = MCAN_IR_DRX;
}

static inline bool mcan_rx_fifo_data(Mcan *mcan, uint8_t fifo)
{
	assert(fifo == 0 || fifo == 1);

	return mcan->MCAN_IR & (fifo ? MCAN_IR_RF1N : MCAN_IR_RF0N) ? true
	    : false;
}

static inline void mcan_clear_rx_fifo_flag(Mcan *mcan,
    uint8_t fifo)
{
	assert(fifo == 0 || fifo == 1);

	mcan->MCAN_IR = fifo ? MCAN_IR_RF1N : MCAN_IR_RF0N;
}

/**
 * \brief Unlock the peripheral configuration so it can be altered.
 * Prerequisite: the peripheral shall be disabled. In case the device has been
 * enabled, call mcan_disable.
 * \param set  Pointer to driver instance data.
 */
extern void mcan_reconfigure(Mcan *mcan);

/**
 * \brief Select either the legacy ISO 11898-1 CAN mode or the CAN-FD mode,
 * along with the FD variant in the latter case.
 * Should be called further to mcan_initialize() or mcan_reconfigure(), before
 * mcan_enable().
 * \param set  Pointer to driver instance data.
 * \param mode  CAN mode, and FD variant in case of FD mode.
 */
extern bool mcan_set_mode(Mcan *mcan, enum can_mode mode);

/**
 * \brief Query the current CAN mode.
 * \param set  Pointer to driver instance data.
 * \return Currently selected CAN mode, and FD variant in case of CAN FD mode.
 */
extern enum can_mode mcan_get_mode(Mcan *mcan);

/**
 * \brief Select the TX Queue mode, disable TX FIFO mode.
 * INIT must be set - so this should be called between mcan_initialize() and
 * mcan_enable().
 * \param set  Pointer to driver instance data.
 */
extern void mcan_set_tx_queue_mode(Mcan *mcan);

/**
 * \brief Enable the peripheral I/O stage. Synchronize with the bus.
 * INIT must be set - so this should be called after mcan_initialize().
 * \param set  Pointer to driver instance data.
 */
extern void mcan_enable(Mcan *mcan);

/**
 * \brief Disable the peripheral I/O stage. Go Bus_Off.
 * \note Subsequent operations may include reconfiguring the peripheral
 * (mcan_reconfigure) and/or re-enabling it (mcan_enable).
 * \param set  Pointer to driver instance data.
 */
extern void mcan_disable(Mcan *mcan);

/**
 * \brief Turn the loop-back mode ON/OFF.
 * \note TEST must be set in MCAN_CCCR. This mode should have been enabled upon
 * initialization.
 * \param set  Pointer to driver instance data.
 */
extern void mcan_loopback(Mcan *mcan, bool loop_back);

/**
 * \brief Convert data length to Data Length Code.
 * \param len  length, in bytes
 * \param dlc  address where the matching Data Length Code will be written
 * \return true if a code matched the provided length, false if this exact
 * length is not supported.
 */
extern bool mcan_get_length_code(uint8_t len, enum mcan_dlc *dlc);

extern bool mcan_set_rx_element_size(Mcan *mcan, uint8_t buf,
		uint8_t fifo0, uint8_t fifo1);

extern bool mcan_set_tx_element_size(Mcan *mcan, uint8_t buf);

/**
 * \brief Select either the m_can_int0 or the m_can_int1 interrupt line.
 * Also, enable the 'Message stored to Dedicated Receive Buffer' specific
 * interrupt.
 * \param set  Pointer to driver instance data.
 * \param int_line  The interrupt line to be enabled:
 *    0   -> m_can_int0
 *    1   -> m_can_int1.
 */
extern void mcan_enable_rx_array_flag(Mcan *mcan, uint8_t int_line);

/**
 * \brief Check if message transmitted from the specified TX Buffer, either
 * dedicated or part of the TX FIFO or TX Queue.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the transmit buffer to be queried.
 * \return true if the message has been successfully transmitted, false
 * otherwise.
 */
extern bool mcan_is_buffer_sent(Mcan *mcan, uint8_t buf_idx);

/**
 * \brief Check whether some data has been received into the specified RX
 * Buffer.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the receive buffer to be queried.
 * \return true if the receive buffer is flagged as containing an unfetched
 * frame, and false otherwise.
 */
extern bool mcan_rx_buffer_data(Mcan *mcan, uint8_t buf_idx);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _MCAN_H_ */
