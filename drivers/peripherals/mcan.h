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

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

enum mcan_can_mode
{
	/* ISO 11898-1 CAN mode */
	MCAN_MODE_CAN,

	/* Long CAN FD frame.
	 * - TX and RX payloads up to 64 bytes.
	 * - Slow transmitter: TX frames are sent at constant bit rate.
	 * - Fast receiver: both constant-rate (slow) and dual-rate (fast)
	 *   RX frames are supported and received. */
	MCAN_MODE_EXT_LEN_CONST_RATE,

	/* Long and fast CAN FD frame.
	 * - TX and RX payloads up to 64 bytes.
	 * - Fast transmitter: control, data and CRC fields are transmitted at a
	 *   higher bit rate.
	 * - Fast receiver. */
	MCAN_MODE_EXT_LEN_DUAL_RATE,
};

/* Flag signalling a standard (11-bit) message identifiers */
#define CAN_STD_MSG_ID (0x0u << 30)
/* Flag to be bitwise or'ed to extended (29-bit) message identifiers */
#define CAN_EXT_MSG_ID (0x1u << 30)

typedef enum
{
	CAN_FIFO_0 = 0,
	CAN_FIFO_1 = 1
} MCan_FifoType;

typedef enum
{
	CAN_INTR_LINE_0 = 0,
	CAN_INTR_LINE_1 = 1
} MCan_IntrLineType;

typedef struct MailboxInfoTag
{
	uint32_t id;
	uint32_t length;
	uint32_t timestamp;
} MailboxInfoType;

typedef struct MailBox8Tag
{
	MailboxInfoType info;
	uint8_t data[8];
} Mailbox8Type;

typedef struct MailBox12Tag
{
	MailboxInfoType info;
	uint8_t data[12];
} Mailbox12Type;

typedef struct MailBox16Tag
{
	MailboxInfoType info;
	uint8_t data[16];
} Mailbox16Type;

typedef struct MailBox20Tag
{
	MailboxInfoType info;
	uint8_t data[20];
} Mailbox20Type;

typedef struct MailBox24Tag
{
	MailboxInfoType info;
	uint8_t data[24];
} Mailbox24Type;

typedef struct MailBox32Tag
{
	MailboxInfoType info;
	uint8_t data[32];
} Mailbox32ype;

typedef struct MailBox48Tag
{
	MailboxInfoType info;
	uint8_t data[48];
} Mailbox48Type;

typedef struct MailBox64Tag
{
	MailboxInfoType info;
	uint8_t data[64];
} Mailbox64Type;

struct mcan_config
{
	uint32_t id;                  /* peripheral ID (ID_xxx) */
	Mcan *regs;                   /* set of MCAN hardware registers */
	uint32_t *msg_ram;            /* base address of the Message RAM to be
	                               * assigned to this MCAN instance */

	uint8_t array_size_filt_std;  /* # of 11-bit Message ID Rx Filters */
	uint8_t array_size_filt_ext;  /* # of 29-bit Message ID Rx Filters */
	uint8_t fifo_size_rx0;        /* # of Rx Buffers in Rx FIFO 0 */
	uint8_t fifo_size_rx1;        /* # of Rx Buffers in Rx FIFO 1 */
	uint8_t array_size_rx;        /* # of dedicated Rx Buffers */
	uint8_t fifo_size_tx_evt;     /* # of Tx Event Elements in the Tx Event
	                               * FIFO */
	uint8_t array_size_tx;        /* # of dedicated Tx Buffers */
	uint8_t fifo_size_tx;         /* # of Tx Buffers in the Tx FIFO or Tx
	                               * Queue */

	uint8_t buf_size_rx_fifo0;    /* size of the data field in each Rx
	                               * Buffer of Rx FIFO 0, in bytes */
	uint8_t buf_size_rx_fifo1;    /* size of the data field in each Rx
	                               * Buffer of Rx FIFO 1, in bytes */
	uint8_t buf_size_rx;          /* size of the data field in each
	                               * dedicated Rx Buffer, in bytes */
	uint8_t buf_size_tx;          /* size of the data field in each Tx
	                               * Buffer, in bytes. Applies to all Tx
	                               * Buffers, dedicated and in Tx FIFO /
	                               * Queue. */

	uint32_t bit_rate;            /* requested CAN bit rate in CAN mode,
	                               * in bps */
	uint16_t quanta_before_sp;    /* duration of the time segment before the
	                               * sample point (Sync_Seg + Prop_Seg +
	                               * Phase_Seg1), while in CAN mode,
	                               * expressed in CAN time quanta */
	uint8_t quanta_after_sp;      /* duration of the time segment after the
	                               * sample point (Phase_Seg2), while in CAN
	                               * mode, expressed in CAN time quanta */

	uint32_t bit_rate_fd;         /* requested CAN bit rate in fast CAN FD
	                               * mode, in bps */
	uint8_t quanta_before_sp_fd;  /* duration of the time segment before the
	                               * sample point (Sync_Seg + Prop_Seg +
	                               * Phase_Seg1), while in fast CAN FD mode,
	                               * expressed in CAN time quanta */
	uint8_t quanta_after_sp_fd;   /* duration of the time segment after the
	                               * sample point (Phase_Seg2), while in
	                               * fast CAN FD mode, expressed in CAN time
	                               * quanta */

	uint8_t quanta_sync_jump;     /* duration of a (re)synchronization jump,
	                               * while in CAN mode, expressed in CAN
	                               * time quanta */
	uint8_t quanta_sync_jump_fd;  /* duration of a (re)synchronization jump,
	                               * while in fast CAN FD mode, expressed in
	                               * CAN time quanta */
};

/* This structure is private to the MCAN Driver.
 * Allocate it but ignore its members. */
struct mcan_set
{
	struct mcan_config cfg;
	uint32_t *ram_filt_std;
	uint32_t *ram_filt_ext;
	uint32_t *ram_fifo_rx0;
	uint32_t *ram_fifo_rx1;
	uint32_t *ram_array_rx;
	uint32_t *ram_fifo_tx_evt;
	uint32_t *ram_array_tx;
};

/*----------------------------------------------------------------------------
 *         Exported symbols
 *----------------------------------------------------------------------------*/

static inline bool MCAN_IsEnabled(const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	return ((mcan->MCAN_CCCR & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_DISABLED);
}

static inline bool MCAN_IsExtendedID(uint32_t msg_id)
{
	return msg_id & CAN_EXT_MSG_ID ? true : false;
}

static inline uint32_t MCAN_GetID(uint32_t msg_id)
{
	return msg_id & CAN_EXT_MSG_ID ? msg_id & 0x1fffffff : msg_id & 0x7ff;
}

static inline bool MCAN_IsTxComplete(const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	return mcan->MCAN_IR & MCAN_IR_TC ? true : false;
}

static inline void MCAN_ClearTxComplete(const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	mcan->MCAN_IR = MCAN_IR_TC;
}

static inline bool MCAN_IsMessageStoredToRxDedBuffer(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	return mcan->MCAN_IR & MCAN_IR_DRX ? true : false;
}

static inline void MCAN_ClearMessageStoredToRxBuffer(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	mcan->MCAN_IR = MCAN_IR_DRX;
}

static inline bool MCAN_IsMessageStoredToRxFifo0(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	return mcan->MCAN_IR & MCAN_IR_RF0N ? true : false;
}

static inline void MCAN_ClearMessageStoredToRxFifo0(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	mcan->MCAN_IR = MCAN_IR_RF0N;
}

static inline bool MCAN_IsMessageStoredToRxFifo1(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	return mcan->MCAN_IR & MCAN_IR_RF1N ? true : false;
}

static inline void MCAN_ClearMessageStoredToRxFifo1(
    const struct mcan_set *set)
{
	Mcan *mcan = set->cfg.regs;
	mcan->MCAN_IR = MCAN_IR_RF1N;
}

/**
 * \brief Compute the size of the Message RAM to be assigned to the MCAN.
 * \param cfg  MCAN configuration to be considered. Only integer size parameters
 * need to be configured. The other parameters can be left blank at this stage.
 * \param size  address where the required size of the Message RAM will be
 * written, expressed in (32-bit) words.
 * \return true if successful, false if a parameter is set to an unsupported
 * value.
 */
bool MCAN_Configure_Msg_RAM(const struct mcan_config *cfg, uint32_t *size);

/**
 * \brief Initialize the MCAN hardware for the given peripheral.
 * Default: Non-FD, ISO 11898-1 CAN mode; mixed mode TX Buffer + FIFO.
 * \param set  Pointer to uninitialized driver instance data.
 * \param cfg  MCAN configuration to be used.
 * \return true if successful, false if a parameter is set to an unsupported
 * value.
 */
bool MCAN_Init(struct mcan_set *set, const struct mcan_config *cfg);

/**
 * \brief Unlock the peripheral configuration so it can be altered.
 * Prerequisite: the peripheral shall be disabled. In case the device has been
 * enabled, call MCAN_Disable.
 * \param set  Pointer to driver instance data.
 */
void MCAN_Reconfigure(struct mcan_set *set);

/**
 * \brief Select either the legacy ISO 11898-1 CAN mode or the CAN-FD mode,
 * along with the FD variant in the latter case.
 * Should be called further to MCAN_Init() or MCAN_Reconfigure(), before
 * MCAN_Enable().
 * \param set  Pointer to driver instance data.
 * \param mode  CAN mode, and FD variant in case of FD mode.
 */
void MCAN_SetMode(struct mcan_set *set, enum mcan_can_mode mode);

/**
 * \brief Query the current CAN mode.
 * \param set  Pointer to driver instance data.
 * \return Currently selected CAN mode, and FD variant in case of CAN FD mode.
 */
enum mcan_can_mode MCAN_GetMode(const struct mcan_set *set);

/**
 * \brief Initialize the MCAN queue for TX.
 * INIT must be set - so this should be called between MCAN_Init() and
 * MCAN_Enable().
 * \param set  Pointer to driver instance data.
 */
void MCAN_InitTxQueue(struct mcan_set *set);

/**
 * \brief Initialize the MCAN in loop back mode.
 * INIT must be set - so this should be called between MCAN_Init() and
 * MCAN_Enable().
 * \param set  Pointer to driver instance data.
 */
void MCAN_InitLoopback(struct mcan_set *set);

/**
 * \brief Enable the peripheral I/O stage. Synchronize with the bus.
 * INIT must be set - so this should be called after MCAN_Init().
 * \param set  Pointer to driver instance data.
 */
void MCAN_Enable(struct mcan_set *set);

/**
 * \brief Disable the peripheral I/O stage. Go Bus_Off.
 * \note Subsequent operations may include reconfiguring the peripheral
 * (MCAN_Reconfigure) and/or re-enabling it (MCAN_Enable).
 * \param set  Pointer to driver instance data.
 */
void MCAN_Disable(struct mcan_set *set);

/**
 * \brief Turn the loop-back mode ON.
 * \note TEST must be set in MCAN_CCCR. This mode should have been enabled upon
 * initialization.
 * \param set  Pointer to driver instance data.
 */
void MCAN_LoopbackOn(struct mcan_set *set);

/**
 * \brief Turn the loop-back mode OFF.
 * \param set  Pointer to driver instance data.
 */
void MCAN_LoopbackOff(struct mcan_set *set);

/**
 * \brief Enable message line and message stored to Dedicated Receive Buffer
 * Interrupt Line.
 * \param set  Pointer to driver instance data.
 * \param line  Message line.
 */
void MCAN_IEnableMessageStoredToRxDedBuffer(
    struct mcan_set *set, MCan_IntrLineType line);

/**
 * \brief Configure a Dedicated TX Buffer.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the transmit buffer to be used.
 * \param id  Message ID.
 * \param len  Data length, in bytes.
 * \return Address of data byte 0, part of the transmit buffer.
 */
uint8_t * MCAN_ConfigTxDedBuffer(struct mcan_set *set,
    uint8_t buf_idx, uint32_t id, uint8_t len);

/**
 * \brief Send TX buffer.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the transmit buffer to be used.
 */
void MCAN_SendTxDedBuffer(struct mcan_set *set, uint8_t buf_idx);

/**
 * \brief Add message to TX FIFO / queue.
 * \param set  Pointer to driver instance data.
 * \param id  Message ID.
 * \param len  Data length, in bytes.
 * \param data  Pointer to data.
 * \return Index of the assigned transmit buffer, part of the FIFO / queue.
 * Or 0xff if the TX FIFO was full, or an error occurred.
 */
uint32_t MCAN_AddToTxFifoQ(struct mcan_set *set,
    uint32_t id, uint8_t len, const uint8_t *data);

/**
 * \brief Check if data transmitted from buffer/FIFO/queue.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the transmit buffer to be queried.
 * \return true if the message has been successfully transmitted, false
 * otherwise.
 */
bool MCAN_IsBufferTxd(const struct mcan_set *set, uint8_t buf_idx);

/**
 * \brief Configure RX buffer filter.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the receive buffer to be used.
 * \param filter  Data of filter.
 * \param id  Message ID, must match exactly a RX buffer filter.
 */
void MCAN_ConfigRxBufferFilter(struct mcan_set *set,
    uint32_t buf_idx, uint32_t filter, uint32_t id);

/**
 * \brief Configure classic filter.
 * The classic filters direct the accepted messages to a FIFO, and include both
 * an ID and an ID mask.
 * \param set  Pointer to driver instance data.
 * \param fifo  FIFO number.
 * \param filter  Data of filter.
 * \param id  Message ID.
 * \param mask  Mask to be matched.
 */
void MCAN_ConfigRxClassicFilter(struct mcan_set *set,
    MCan_FifoType fifo, uint8_t filter, uint32_t id, uint32_t mask);

/**
 * \brief Check whether some data has been received into the buffer.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the receive buffer to be queried.
 * \return true if the receive buffer is flagged as containing an unfetched
 * frame, and false otherwise.
 */
bool MCAN_IsNewDataInRxDedBuffer(const struct mcan_set *set,
    uint8_t buf_idx);

/**
 * \brief Get RX buffer.
 * \param set  Pointer to driver instance data.
 * \param buf_idx  Index of the receive buffer to be read.
 * \param pRxMailbox  Pointer to RX mailbox.
 */
void MCAN_GetRxDedBuffer(struct mcan_set *set, uint8_t buf_idx,
    Mailbox64Type *pRxMailbox);

/**
 * \brief Get from the receive FIFO, to a mailbox owned by the application.
 * \param set  Pointer to driver instance data.
 * \param fifo  FIFO Number
 * \param pRxMailbox  Pointer to RX mailbox.
 * \return: # of FIFO entries at the time the function was entered:
 *    0       -> The FIFO was initially empty.
 *    1       -> The FIFO had 1 entry upon entry, but is empty upon exit.
 *    2 to 64 -> The FIFO had several entries upon entry, and still holds one
 *               or more entries upon exit.
 */
uint8_t MCAN_GetRxFifoBuffer(struct mcan_set *set,
    MCan_FifoType fifo, Mailbox64Type *pRxMailbox);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _MCAN_H_ */
