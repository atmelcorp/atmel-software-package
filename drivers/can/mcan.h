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

/* -------- MCAN Message RAM : Standard Message ID Filter Element (S0) -------- */
#define MCAN_RAM_S0_SFID2_Pos 0
#define MCAN_RAM_S0_SFID2_Msk (0x7ffu << MCAN_RAM_S0_SFID2_Pos) /**< \brief (S0) Standard Filter ID 2 */
#define MCAN_RAM_S0_SFID2(value) ((MCAN_RAM_S0_SFID2_Msk & ((value) << MCAN_RAM_S0_SFID2_Pos)))
#define   MCAN_RAM_S0_SFID2_BUF_IDX_Pos 0
#define   MCAN_RAM_S0_SFID2_BUF_IDX_Msk (0x3fu << MCAN_RAM_S0_SFID2_BUF_IDX_Pos) /**< \brief (S0) Index of Rx Buffer for storage of a matching message. */
#define   MCAN_RAM_S0_SFID2_BUF_IDX(value) ((MCAN_RAM_S0_SFID2_BUF_IDX_Msk & ((value) << MCAN_RAM_S0_SFID2_BUF_IDX_Pos)))
#define   MCAN_RAM_S0_SFID2_FE0 (0x1u << 6) /**< \brief (S0) Generate a pulse at m_can_fe0 filter event pin in case the filter matches. */
#define   MCAN_RAM_S0_SFID2_FE1 (0x1u << 7) /**< \brief (S0) Generate a pulse at m_can_fe1 filter event pin in case the filter matches. */
#define   MCAN_RAM_S0_SFID2_FE2 (0x1u << 8) /**< \brief (S0) Generate a pulse at m_can_fe2 filter event pin in case the filter matches. */
#define   MCAN_RAM_S0_SFID2_BUF (0x0u << 9) /**< \brief (S0) Store message in a Rx buffer. */
#define   MCAN_RAM_S0_SFID2_DBG_A (0x1u << 9) /**< \brief (S0) Debug Message A. */
#define   MCAN_RAM_S0_SFID2_DBG_B (0x2u << 9) /**< \brief (S0) Debug Message B. */
#define   MCAN_RAM_S0_SFID2_DBG_C (0x3u << 9) /**< \brief (S0) Debug Message C. */
#define MCAN_RAM_S0_SFID1_Pos 16
#define MCAN_RAM_S0_SFID1_Msk (0x7ffu << MCAN_RAM_S0_SFID1_Pos) /**< \brief (S0) Standard Filter ID 1 */
#define MCAN_RAM_S0_SFID1(value) ((MCAN_RAM_S0_SFID1_Msk & ((value) << MCAN_RAM_S0_SFID1_Pos)))
#define MCAN_RAM_S0_SFEC_Pos 27
#define MCAN_RAM_S0_SFEC_Msk (0x7u << MCAN_RAM_S0_SFEC_Pos) /**< \brief (S0) Standard Filter Element Configuration */
#define MCAN_RAM_S0_SFEC(value) ((MCAN_RAM_S0_SFEC_Msk & ((value) << MCAN_RAM_S0_SFEC_Pos)))
#define   MCAN_RAM_S0_SFEC_DIS (0x0u << 27) /**< \brief (S0) Disable filter element. */
#define   MCAN_RAM_S0_SFEC_FIFO0 (0x1u << 27) /**< \brief (S0) Store in Rx FIFO 0 if filter matches. */
#define   MCAN_RAM_S0_SFEC_FIFO1 (0x2u << 27) /**< \brief (S0) Store in Rx FIFO 1 if filter matches. */
#define   MCAN_RAM_S0_SFEC_INV (0x3u << 27) /**< \brief (S0) Reject ID if filter matches. */
#define   MCAN_RAM_S0_SFEC_PTY (0x4u << 27) /**< \brief (S0) Set priority if filter matches. */
#define   MCAN_RAM_S0_SFEC_PTY_FIFO0 (0x5u << 27) /**< \brief (S0) Set priority and store in FIFO 0 if filter matches. */
#define   MCAN_RAM_S0_SFEC_PTY_FIFO1 (0x6u << 27) /**< \brief (S0) Set priority and store in FIFO 1 if filter matches. */
#define   MCAN_RAM_S0_SFEC_BUF (0x7u << 27) /**< \brief (S0) Store into Rx Buffer or as debug message. */
#define MCAN_RAM_S0_SFT_Pos 30
#define MCAN_RAM_S0_SFT_Msk (0x3u << MCAN_RAM_S0_SFT_Pos) /**< \brief (S0) Standard Filter Type */
#define MCAN_RAM_S0_SFT(value) ((MCAN_RAM_S0_SFT_Msk & ((value) << MCAN_RAM_S0_SFT_Pos)))
#define   MCAN_RAM_S0_SFT_RANGE (0x0u << 30) /**< \brief (S0) Range filter from SF1ID to SF2ID. */
#define   MCAN_RAM_S0_SFT_DUAL_ID (0x1u << 30) /**< \brief (S0) Dual ID filter for SF1ID or SF2ID. */
#define   MCAN_RAM_S0_SFT_CLASSIC (0x2u << 30) /**< \brief (S0) Classic filter: SF1ID = filter, SF2ID = mask. */
/* -------- MCAN Message RAM : Extended Message ID Filter Element (F0) -------- */
#define MCAN_RAM_F0_EFID1_Pos 0
#define MCAN_RAM_F0_EFID1_Msk (0x1fffffffu << MCAN_RAM_F0_EFID1_Pos) /**< \brief (F0) Standard Filter ID 1 */
#define MCAN_RAM_F0_EFID1(value) ((MCAN_RAM_F0_EFID1_Msk & ((value) << MCAN_RAM_F0_EFID1_Pos)))
#define MCAN_RAM_F0_EFEC_Pos 29
#define MCAN_RAM_F0_EFEC_Msk (0x7u << MCAN_RAM_F0_EFEC_Pos) /**< \brief (F0) Extended Filter Element Configuration */
#define MCAN_RAM_F0_EFEC(value) ((MCAN_RAM_F0_EFEC_Msk & ((value) << MCAN_RAM_F0_EFEC_Pos)))
#define   MCAN_RAM_F0_EFEC_DIS (0x0u << 29) /**< \brief (F0) Disable filter element. */
#define   MCAN_RAM_F0_EFEC_FIFO0 (0x1u << 29) /**< \brief (F0) Store in Rx FIFO 0 if filter matches. */
#define   MCAN_RAM_F0_EFEC_FIFO1 (0x2u << 29) /**< \brief (F0) Store in Rx FIFO 1 if filter matches. */
#define   MCAN_RAM_F0_EFEC_INV (0x3u << 29) /**< \brief (F0) Reject ID if filter matches. */
#define   MCAN_RAM_F0_EFEC_PTY (0x4u << 29) /**< \brief (F0) Set priority if filter matches. */
#define   MCAN_RAM_F0_EFEC_PTY_FIFO0 (0x5u << 29) /**< \brief (F0) Set priority and store in FIFO 0 if filter matches. */
#define   MCAN_RAM_F0_EFEC_PTY_FIFO1 (0x6u << 29) /**< \brief (F0) Set priority and store in FIFO 1 if filter matches. */
#define   MCAN_RAM_F0_EFEC_BUF (0x7u << 29) /**< \brief (F0) Store into Rx Buffer or as debug message. */
/* -------- MCAN Message RAM : Extended Message ID Filter Element (F1) -------- */
#define MCAN_RAM_F1_EFID2_Pos 0
#define MCAN_RAM_F1_EFID2_Msk (0x1fffffffu << MCAN_RAM_F1_EFID2_Pos) /**< \brief (F1) Standard Filter ID 2 */
#define MCAN_RAM_F1_EFID2(value) ((MCAN_RAM_F1_EFID2_Msk & ((value) << MCAN_RAM_F1_EFID2_Pos)))
#define   MCAN_RAM_F1_EFID2_BUF_IDX_Pos 0
#define   MCAN_RAM_F1_EFID2_BUF_IDX_Msk (0x3fu << MCAN_RAM_F1_EFID2_BUF_IDX_Pos) /**< \brief (F1) Index of Rx Buffer for storage of a matching message. */
#define   MCAN_RAM_F1_EFID2_BUF_IDX(value) ((MCAN_RAM_F1_EFID2_BUF_IDX_Msk & ((value) << MCAN_RAM_F1_EFID2_BUF_IDX_Pos)))
#define   MCAN_RAM_F1_EFID2_FE0 (0x1u << 6) /**< \brief (F1) Generate a pulse at m_can_fe0 filter event pin in case the filter matches. */
#define   MCAN_RAM_F1_EFID2_FE1 (0x1u << 7) /**< \brief (F1) Generate a pulse at m_can_fe1 filter event pin in case the filter matches. */
#define   MCAN_RAM_F1_EFID2_FE2 (0x1u << 8) /**< \brief (F1) Generate a pulse at m_can_fe2 filter event pin in case the filter matches. */
#define   MCAN_RAM_F1_EFID2_BUF (0x0u << 9) /**< \brief (F1) Store message in a Rx buffer. */
#define   MCAN_RAM_F1_EFID2_DBG_A (0x1u << 9) /**< \brief (F1) Debug Message A. */
#define   MCAN_RAM_F1_EFID2_DBG_B (0x2u << 9) /**< \brief (F1) Debug Message B. */
#define   MCAN_RAM_F1_EFID2_DBG_C (0x3u << 9) /**< \brief (F1) Debug Message C. */
#define MCAN_RAM_F1_EFT_Pos 30
#define MCAN_RAM_F1_EFT_Msk (0x3u << MCAN_RAM_F1_EFT_Pos) /**< \brief (F1) Extended Filter Type */
#define MCAN_RAM_F1_EFT(value) ((MCAN_RAM_F1_EFT_Msk & ((value) << MCAN_RAM_F1_EFT_Pos)))
#define   MCAN_RAM_F1_EFT_RANGE_EIDM (0x0u << 30) /**< \brief (F1) Range filter from EF1ID to EF2ID (Extended ID Mask applied). */
#define   MCAN_RAM_F1_EFT_DUAL_ID (0x1u << 30) /**< \brief (F1) Dual ID filter for EF1ID or EF2ID. */
#define   MCAN_RAM_F1_EFT_CLASSIC (0x2u << 30) /**< \brief (F1) Classic filter: EF1ID = filter, EF2ID = mask. */
#define   MCAN_RAM_F1_EFT_RANGE (0x3u << 30) /**< \brief (F1) Range filter from EF1ID to EF2ID, Extended ID Mask not applied. */
/* -------- MCAN Message RAM : Rx Buffer Element (R0) -------- */
#define MCAN_RAM_R0_XTDID_Pos 0
#define MCAN_RAM_R0_XTDID_Msk (0x1fffffffu << MCAN_RAM_R0_XTDID_Pos) /**< \brief (R0) Extended (29-bit) Message identifier */
#define MCAN_RAM_R0_XTDID(value) ((MCAN_RAM_R0_XTDID_Msk & ((value) << MCAN_RAM_R0_XTDID_Pos)))
#define MCAN_RAM_R0_STDID_Pos 18
#define MCAN_RAM_R0_STDID_Msk (0x7ffu << MCAN_RAM_R0_STDID_Pos) /**< \brief (R0) Standard (11-bit) Message identifier */
#define MCAN_RAM_R0_STDID(value) ((MCAN_RAM_R0_STDID_Msk & ((value) << MCAN_RAM_R0_STDID_Pos)))
#define MCAN_RAM_R0_RTR (0x1u << 29) /**< \brief (R0) Remote Transmission Request */
#define MCAN_RAM_R0_XTD (0x1u << 30) /**< \brief (R0) Flag that signals an extended Message identifier */
#define MCAN_RAM_R0_ESI (0x1u << 31) /**< \brief (R0) Error State Indicator */
/* -------- MCAN Message RAM : Rx Buffer Element (R1) -------- */
#define MCAN_RAM_R1_RXTS_Pos 0
#define MCAN_RAM_R1_RXTS_Msk (0xffffu << MCAN_RAM_R1_RXTS_Pos) /**< \brief (R1) Rx Timestamp */
#define MCAN_RAM_R1_DLC_Pos 16
#define MCAN_RAM_R1_DLC_Msk (0xfu << MCAN_RAM_R1_DLC_Pos) /**< \brief (R1) Data Length Code */
#define MCAN_RAM_R1_DLC(value) ((MCAN_RAM_R1_DLC_Msk & ((value) << MCAN_RAM_R1_DLC_Pos)))
#define MCAN_RAM_R1_BRS (0x1u << 20) /**< \brief (R1) Flag that signals a frame transmitted with bit rate switching */
#define MCAN_RAM_R1_FDF (0x1u << 21) /**< \brief (R1) Flag that signals a frame in CAN FD format */
#define MCAN_RAM_R1_FIDX_Pos 24
#define MCAN_RAM_R1_FIDX_Msk (0x7fu << MCAN_RAM_R1_FIDX_Pos) /**< \brief (R1) Filter Index */
#define MCAN_RAM_R1_ANMF (0x1u << 31) /**< \brief (R1) Flag that signals a received frame accepted without matching any Rx Filter Element */
/* -------- MCAN Message RAM : Rx Buffer Element (T0) -------- */
#define MCAN_RAM_T0_XTDID_Pos 0
#define MCAN_RAM_T0_XTDID_Msk (0x1fffffffu << MCAN_RAM_T0_XTDID_Pos) /**< \brief (T0) Extended (29-bit) Message identifier */
#define MCAN_RAM_T0_XTDID(value) ((MCAN_RAM_T0_XTDID_Msk & ((value) << MCAN_RAM_T0_XTDID_Pos)))
#define MCAN_RAM_T0_STDID_Pos 18
#define MCAN_RAM_T0_STDID_Msk (0x7ffu << MCAN_RAM_T0_STDID_Pos) /**< \brief (T0) Standard (11-bit) Message identifier */
#define MCAN_RAM_T0_STDID(value) ((MCAN_RAM_T0_STDID_Msk & ((value) << MCAN_RAM_T0_STDID_Pos)))
#define MCAN_RAM_T0_RTR (0x1u << 29) /**< \brief (T0) Remote Transmission Request */
#define MCAN_RAM_T0_XTD (0x1u << 30) /**< \brief (T0) Flag that signals an extended Message identifier */
#define MCAN_RAM_T0_ESI (0x1u << 31) /**< \brief (T0) Error State Indicator */
/* -------- MCAN Message RAM : Rx Buffer Element (T1) -------- */
#define MCAN_RAM_T1_DLC_Pos 16
#define MCAN_RAM_T1_DLC_Msk (0xfu << MCAN_RAM_T1_DLC_Pos) /**< \brief (T1) Data Length Code */
#define MCAN_RAM_T1_DLC(value) ((MCAN_RAM_T1_DLC_Msk & ((value) << MCAN_RAM_T1_DLC_Pos)))
#define MCAN_RAM_T1_BRS (0x1u << 20) /**< \brief (T1) Flag that signals a frame transmitted with bit rate switching */
#define MCAN_RAM_T1_FDF (0x1u << 21) /**< \brief (T1) Flag that signals a frame in CAN FD format */
#define MCAN_RAM_T1_EFC (0x1u << 23) /**< \brief (T1) Event FIFO Control */
#define MCAN_RAM_T1_MM_Pos 24
#define MCAN_RAM_T1_MM_Msk (0xffu << MCAN_RAM_T1_MM_Pos) /**< \brief (T1) Message Marker */
#define MCAN_RAM_T1_MM(value) ((MCAN_RAM_T1_MM_Msk & ((value) << MCAN_RAM_T1_MM_Pos)))
/* -------- MCAN Message RAM : Tx Event FIFO Element (E0) -------- */
#define MCAN_RAM_E0_XTDID_Pos 0
#define MCAN_RAM_E0_XTDID_Msk (0x1fffffffu << MCAN_RAM_E0_XTDID_Pos) /**< \brief (E0) Extended (29-bit) Message identifier */
#define MCAN_RAM_E0_XTDID(value) ((MCAN_RAM_E0_XTDID_Msk & ((value) << MCAN_RAM_E0_XTDID_Pos)))
#define MCAN_RAM_E0_STDID_Pos 18
#define MCAN_RAM_E0_STDID_Msk (0x7ffu << MCAN_RAM_E0_STDID_Pos) /**< \brief (E0) Standard (11-bit) Message identifier */
#define MCAN_RAM_E0_STDID(value) ((MCAN_RAM_E0_STDID_Msk & ((value) << MCAN_RAM_E0_STDID_Pos)))
#define MCAN_RAM_E0_RTR (0x1u << 29) /**< \brief (E0) Remote Transmission Request */
#define MCAN_RAM_E0_XTD (0x1u << 30) /**< \brief (E0) Flag that signals an extended Message identifier */
#define MCAN_RAM_E0_ESI (0x1u << 31) /**< \brief (E0) Error State Indicator */
/* -------- MCAN Message RAM : Tx Event FIFO Element (E1) -------- */
#define MCAN_RAM_E1_TXTS_Pos 0
#define MCAN_RAM_E1_TXTS_Msk (0xffffu << MCAN_RAM_E1_RXTS_Pos) /**< \brief (E1) Tx Timestamp */
#define MCAN_RAM_E1_DLC_Pos 16
#define MCAN_RAM_E1_DLC_Msk (0xfu << MCAN_RAM_E1_DLC_Pos) /**< \brief (E1) Data Length Code */
#define MCAN_RAM_E1_DLC(value) ((MCAN_RAM_E1_DLC_Msk & ((value) << MCAN_RAM_E1_DLC_Pos)))
#define MCAN_RAM_E1_BRS (0x1u << 20) /**< \brief (E1) Flag that signals a frame transmitted with bit rate switching */
#define MCAN_RAM_E1_FDF (0x1u << 21) /**< \brief (E1) Flag that signals a frame in CAN FD format */
#define MCAN_RAM_E1_ET_Pos 22
#define MCAN_RAM_E1_ET_Msk (0x3u << MCAN_RAM_E1_ET_Pos) /**< \brief (E1) Event Type */
#define MCAN_RAM_E1_ET(value) ((MCAN_RAM_E1_ET_Msk & ((value) << MCAN_RAM_E1_ET_Pos)))
#define   MCAN_RAM_E1_ET_TX_EVENT (0x1u << 22) /**< \brief (E1) Tx event */
#define   MCAN_RAM_E1_ET_TX_CANCELLED (0x2u << 22) /**< \brief (E1) Transmission in spite of cancellation */
#define MCAN_RAM_E1_MM_Pos 24
#define MCAN_RAM_E1_MM_Msk (0xffu << MCAN_RAM_E1_MM_Pos) /**< \brief (E1) Message Marker */
#define MCAN_RAM_E1_MM(value) ((MCAN_RAM_E1_MM_Msk & ((value) << MCAN_RAM_E1_MM_Pos)))

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
	uint32_t val;

#if defined(MATRIX)
	if (MCAN0 ==  mcan) {
		MATRIX->CCFG_CAN0 = base_addr & 0xFFFF0000;
	} else if (MCAN1 ==  mcan) {
		val = MATRIX->CCFG_SYSIO & 0x0000FFFF;
		MATRIX->CCFG_SYSIO = val | (base_addr & 0xFFFF0000);
	}
#elif defined(SFR)
#ifdef SFR_CAN_EXT_MEM_ADDR
	val = (MCAN0 ==  mcan) ? 0 : (
		(MCAN1 ==  mcan) ? 1 : ((MCAN2 ==  mcan) ? 2 : 3));
	SFR->SFR_CAN[val] = SFR_CAN_EXT_MEM_ADDR(base_addr >> 16);
#else
	val = SFR->SFR_CAN;
	if (MCAN0 == mcan)
		SFR->SFR_CAN = (val & ~SFR_CAN_EXT_MEM_CAN0_ADDR_Msk)
			| SFR_CAN_EXT_MEM_CAN0_ADDR(base_addr >> 16);
	else
		SFR->SFR_CAN = (val & ~SFR_CAN_EXT_MEM_CAN1_ADDR_Msk)
			| SFR_CAN_EXT_MEM_CAN1_ADDR(base_addr >> 16);
#endif
#else
	#error Could not set MSB address of message RAM for MCAN
#endif
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
