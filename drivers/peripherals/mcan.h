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

typedef enum
{
	CAN_STD_ID = 0,
	CAN_EXT_ID = 1
} MCan_IdType;

typedef enum
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
} MCan_DlcType;

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

typedef struct MCan_MsgRamPntrsTag
{
	uint32_t *pStdFilts;
	uint32_t *pExtFilts;
	uint32_t *pRxFifo0;
	uint32_t *pRxFifo1;
	uint32_t *pRxDedBuf;
	uint32_t *pTxEvtFifo;
	uint32_t *pTxDedBuf;
	uint32_t *pTxFifoQ;
} MCan_MsgRamPntrs;

typedef struct MCan_ConfigTag
{
	Mcan *pMCan;
	uint32_t bitTiming;
	uint32_t fastBitTiming;
	uint32_t nmbrStdFilts;
	uint32_t nmbrExtFilts;
	uint32_t nmbrFifo0Elmts;
	uint32_t nmbrFifo1Elmts;
	uint32_t nmbrRxDedBufElmts;
	uint32_t nmbrTxEvtFifoElmts;
	uint32_t nmbrTxDedBufElmts;
	uint32_t nmbrTxFifoQElmts;
	uint32_t rxFifo0ElmtSize;
	uint32_t rxFifo1ElmtSize;
	uint32_t rxBufElmtSize;
	/* Element sizes and data sizes (encoded element size) */
	uint32_t txBufElmtSize;
	/* Element size and data size (encoded element size) */
	MCan_MsgRamPntrs msgRam;
} MCan_ConfigType;

/*----------------------------------------------------------------------------
 *         Exported symbols
 *----------------------------------------------------------------------------*/

extern const MCan_ConfigType mcan0Config;
#ifdef MCAN1
extern const MCan_ConfigType mcan1Config;
#endif

static inline bool MCAN_IsEnabled(const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	return ((mcan->MCAN_CCCR & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_DISABLED);
}

static inline uint32_t MCAN_IsTxComplete(const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	return (mcan->MCAN_IR & MCAN_IR_TC);
}

static inline void MCAN_ClearTxComplete(const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	mcan->MCAN_IR = MCAN_IR_TC;
}

static inline uint32_t MCAN_IsMessageStoredToRxDedBuffer(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	return (mcan->MCAN_IR & MCAN_IR_DRX);
}

static inline void MCAN_ClearMessageStoredToRxBuffer(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	mcan->MCAN_IR = MCAN_IR_DRX;
}

static inline uint32_t MCAN_IsMessageStoredToRxFifo0(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	return (mcan->MCAN_IR & MCAN_IR_RF0N);
}

static inline void MCAN_ClearMessageStoredToRxFifo0(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	mcan->MCAN_IR = MCAN_IR_RF0N;
}

static inline uint32_t MCAN_IsMessageStoredToRxFifo1(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	return (mcan->MCAN_IR & MCAN_IR_RF1N);
}

static inline void MCAN_ClearMessageStoredToRxFifo1(
    const MCan_ConfigType *mcanConfig)
{
	Mcan *mcan = mcanConfig->pMCan;
	mcan->MCAN_IR = MCAN_IR_RF1N;
}

/**
 * \brief Initialize the MCAN hardware for the given peripheral.
 * Default: Non-FD, ISO 11898-1 CAN mode; mixed mode TX Buffer + FIFO.
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_Init(const MCan_ConfigType *mcanConfig);

/**
 * \brief Unlock the peripheral configuration so it can be altered.
 * Prerequisite: the peripheral shall be disabled. In case the device has been
 * enabled, call MCAN_Disable.
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_Reconfigure(const MCan_ConfigType *mcanConfig);

/**
 * \brief Select either the legacy ISO 11898-1 CAN mode or the CAN-FD mode,
 * along with the FD variant in the latter case.
 * Should be called further to MCAN_Init() or MCAN_Reconfigure(), before
 * MCAN_Enable().
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param mode  CAN mode, and FD variant in case of FD mode.
 */
void MCAN_SetMode(const MCan_ConfigType *mcanConfig, enum mcan_can_mode mode);

/**
 * \brief Initialize the MCAN queue for TX.
 * INIT must be set - so this should be called between MCAN_Init() and
 * MCAN_Enable().
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_InitTxQueue(const MCan_ConfigType *mcanConfig);

/**
 * \brief Initialize the MCAN in loop back mode.
 * INIT must be set - so this should be called between MCAN_Init() and
 * MCAN_Enable().
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_InitLoopback(const MCan_ConfigType *mcanConfig);

/**
 * \brief Enable the peripheral I/O stage. Synchronize with the bus.
 * INIT must be set - so this should be called after MCAN_Init().
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_Enable(const MCan_ConfigType *mcanConfig);

/**
 * \brief Disable the peripheral I/O stage. Go Bus_Off.
 * \note Subsequent operations may include reconfiguring the peripheral
 * (MCAN_Reconfigure) and/or re-enabling it (MCAN_Enable).
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_Disable(const MCan_ConfigType *mcanConfig);

/**
 * \brief Turn the loop-back mode ON.
 * \note TEST must be set in MCAN_CCCR. This mode should have been enabled upon
 * initialization.
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_LoopbackOn(const MCan_ConfigType *mcanConfig);

/**
 * \brief Turn the loop-back mode OFF.
 * \param mcanConfig  Pointer to a MCAN instance.
 */
void MCAN_LoopbackOff(const MCan_ConfigType *mcanConfig);

/**
 * \brief Enable message line and message stored to Dedicated Receive Buffer
 * Interrupt Line.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param line  Message line.
 */
void MCAN_IEnableMessageStoredToRxDedBuffer(
    const MCan_ConfigType *mcanConfig, MCan_IntrLineType line);

/**
 * \brief Configure a Dedicated TX Buffer.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the transmit buffer to be used.
 * \param id  Message ID.
 * \param idType  Type of ID.
 * \param dlc  Type of DLC.
 */
uint8_t * MCAN_ConfigTxDedBuffer(const MCan_ConfigType *mcanConfig,
    uint8_t buffer, uint32_t id, MCan_IdType idType, MCan_DlcType dlc);

/**
 * \brief Send TX buffer.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the transmit buffer to be used.
 */
void MCAN_SendTxDedBuffer(const MCan_ConfigType *mcanConfig,
    uint8_t buffer);

/**
 * \brief Add message to TX FIFO / queue.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param id  Message ID.
 * \param idType  Type of ID.
 * \param dlc  Type of DLC.
 * \param data  Pointer to data.
 */
uint32_t MCAN_AddToTxFifoQ(const MCan_ConfigType *mcanConfig,
    uint32_t id, MCan_IdType idType, MCan_DlcType dlc, uint8_t *data);

/**
 * \brief Check if data transmitted from buffer/FIFO/queue.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the transmit buffer to be queried.
 */
uint8_t MCAN_IsBufferTxd(const MCan_ConfigType *mcanConfig, uint8_t buffer);

/**
 * \brief Configure RX buffer filter.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the receive buffer to be used.
 * \param filter  Data of filter.
 * \param id  Message ID, must match exactly a RX buffer filter.
 * \param idType  Type of ID.
 */
void MCAN_ConfigRxBufferFilter(const MCan_ConfigType *mcanConfig,
    uint32_t buffer, uint32_t filter, uint32_t id, MCan_IdType idType);

/**
 * \brief Configure classic filter.
 * The classic filters direct the accepted messages to a FIFO, and include both
 * an ID and an ID mask.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param fifo  FIFO number.
 * \param filter  Data of filter.
 * \param id  Message ID.
 * \param idType  Type of ID.
 * \param mask  Mask to be matched.
 */
void MCAN_ConfigRxClassicFilter(const MCan_ConfigType *mcanConfig,
    MCan_FifoType fifo, uint8_t filter, uint32_t id, MCan_IdType idType,
    uint32_t mask);

/**
 * \brief Check whether some data has been received into the buffer.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the receive buffer to be queried.
 */
uint8_t MCAN_IsNewDataInRxDedBuffer(const MCan_ConfigType *mcanConfig,
    uint8_t buffer);

/**
 * \brief Get RX buffer.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param buffer  Index of the receive buffer to be read.
 * \param pRxMailbox  Pointer to RX mailbox.
 */
void MCAN_GetRxDedBuffer(const MCan_ConfigType *mcanConfig, uint8_t buffer,
    Mailbox64Type *pRxMailbox);

/**
 * \brief Get from the receive FIFO, to a mailbox owned by the application.
 * \param mcanConfig  Pointer to a MCAN instance.
 * \param fifo  FIFO Number
 * \param pRxMailbox  Pointer to RX mailbox.
 * \return: # of FIFO entries at the time the function was entered:
 *         0 -> The FIFO was initially empty.
 *         1 -> The FIFO had 1 entry upon entry, but is empty upon exit.
 *         2 -> The FIFO had 2 entries upon entry, has 1 entry upon exit.
 */
uint32_t MCAN_GetRxFifoBuffer(const MCan_ConfigType *mcanConfig,
    MCan_FifoType fifo, Mailbox64Type *pRxMailbox);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _MCAN_H_ */
