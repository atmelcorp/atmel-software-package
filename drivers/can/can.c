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
 *  Implements functions for Controller Area Network (CAN)
 *  peripheral operations.
 */
/** \addtogroup can_module
 *@{*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "can/can.h"
#include "peripherals/pmc.h"

#include <assert.h>

/*---------------------------------------------------------------------------
 *      Local definitions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *      Local functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *      Exported functions
 *---------------------------------------------------------------------------*/

void can_configure_mode(Can *can, uint32_t mr)
{
	can->CAN_MR = mr;
}

void can_enable(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_CANEN;
	else        can->CAN_MR &= ~CAN_MR_CANEN;
}

void can_enable_low_power(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_LPM;
	else        can->CAN_MR &= ~CAN_MR_LPM;
}

void can_enable_autobaud(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_ABM;
	else        can->CAN_MR &= ~CAN_MR_ABM;
}

void can_enable_overload_frame(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_OVL;
	else        can->CAN_MR &= ~CAN_MR_OVL;
}

void can_enable_timestamp_eof(Can *can, uint8_t eof)
{
	if (eof) can->CAN_MR |=  CAN_MR_TEOF;
	else     can->CAN_MR &= ~CAN_MR_TEOF;
}

void can_enable_time_trigger_mode(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_TTM;
	else        can->CAN_MR &= ~CAN_MR_TTM;
}

void can_enable_timer_freeze(Can *can, uint8_t enable)
{
	if (enable) can->CAN_MR |=  CAN_MR_TIMFRZ;
	else        can->CAN_MR &= ~CAN_MR_TIMFRZ;
}

void can_disable_repeat(Can *can, uint8_t disable)
{
	if (disable) can->CAN_MR |=  CAN_MR_DRPT;
	else         can->CAN_MR &= ~CAN_MR_DRPT;
}

/* ---------- Interrupt settings ------------- */

void can_enable_it(Can *can, uint32_t sources)
{
	can->CAN_IER = sources;
}

void can_disable_it(Can *can, uint32_t sources)
{
	can->CAN_IDR = sources;
}

uint32_t can_get_it_mask(Can *can)
{
	return can->CAN_IMR;
}

uint32_t can_get_status(Can *can)
{
	return can->CAN_SR;
}

void can_configure_baudrate(Can *can, uint32_t baudrate)
{
	can->CAN_BR = baudrate;
}

void can_set_sampling_mode(Can *can, uint8_t avg3)
{
	if (avg3) can->CAN_BR |=  CAN_BR_SMP;
	else      can->CAN_BR &= ~CAN_BR_SMP;
}

uint32_t can_get_timer(Can *can)
{
	return can->CAN_TIM;
}

uint32_t can_get_timestamp(Can *can)
{
	return can->CAN_TIMESTP;
}

uint32_t can_get_error_count(Can *can)
{
	return can->CAN_ECR;
}

uint32_t can_get_rx_error_count(Can *can)
{
	return (can->CAN_ECR & CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos;
}

uint32_t can_get_tx_error_count(Can *can)
{
	return (can->CAN_ECR & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos;
}

void can_command(Can *can, uint32_t requests)
{
	can->CAN_TCR = requests;
}

void can_reset_timer(Can *can)
{
	can->CAN_TCR = CAN_TCR_TIMRST;
}

void can_tx(Can *can, uint8_t mailbox)
{
	can->CAN_TCR = CAN_TCR_MB0 << mailbox;
}

void can_abort(Can *can, uint32_t aborts)
{
	can->CAN_ACR = aborts;
}

void can_abort_mailbox(Can *can, uint8_t mailbox)
{
	can->CAN_ACR = CAN_ACR_MB0 << mailbox;
}

void can_configure_message_mode(Can *can, uint8_t mailbox, uint32_t mr)
{
	can->CAN_MB[mailbox].CAN_MMR = mr;
}

uint32_t can_get_message_mode(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MMR;
}

void can_set_timemark(Can *can, uint8_t mailbox, uint8_t timemarks)
{
	uint32_t mmr = (can->CAN_MB[mailbox].CAN_MMR) & (~0xFFu);
	can->CAN_MB[mailbox].CAN_MMR = mmr | ((timemarks << 0) & 0xFF);
}

void can_set_priority(Can *can, uint8_t mailbox, uint8_t priority)
{
	uint32_t mmr = (can->CAN_MB[mailbox].CAN_MMR & ~CAN_MMR_PRIOR_Msk);
	can->CAN_MB[mailbox].CAN_MMR = mmr | CAN_MMR_PRIOR(priority);
}

void can_set_object_type(Can *can, uint8_t mailbox, uint8_t type)
{
	uint32_t mmr = (can->CAN_MB[mailbox].CAN_MMR & CAN_MMR_MOT_Msk) >> CAN_MMR_MOT_Pos;
	can->CAN_MB[mailbox].CAN_MMR |= mmr | ((type << CAN_MMR_MOT_Pos) & CAN_MMR_MOT_Msk);
}

void can_configure_msg_mask(Can *can, uint8_t mailbox, uint32_t mam)
{
	can->CAN_MB[mailbox].CAN_MAM = mam;
}

uint32_t can_get_msg_mask(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MAM;
}

void can_configure_identifier_mask(Can *can, uint8_t mailbox, uint8_t cfg)
{
	if (cfg) can->CAN_MB[mailbox].CAN_MAM |=  CAN_MAM_MIDE;
	else     can->CAN_MB[mailbox].CAN_MAM &= ~CAN_MAM_MIDE;
}

void can_set_midva_mask(Can *can, uint8_t mailbox, uint32_t id)
{
	uint32_t dwMam = can->CAN_MB[mailbox].CAN_MAM & CAN_MAM_MIDvA_Msk;
	can->CAN_MB[mailbox].CAN_MAM = dwMam | CAN_MAM_MIDvA(id);
}

void can_set_midvb_mask(Can *can, uint8_t mailbox, uint32_t id)
{
	uint32_t dwMam = can->CAN_MB[mailbox].CAN_MAM & CAN_MAM_MIDvB_Msk;
	can->CAN_MB[mailbox].CAN_MAM = dwMam | CAN_MAM_MIDvB(id);
}

void can_configure_message_id(Can *can, uint8_t mailbox, uint32_t mid)
{
	can->CAN_MB[mailbox].CAN_MID = mid;
}

uint32_t can_get_message_id(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MID;
}

void can_configure_id_ver(Can *can, uint8_t mailbox, uint8_t ver)
{
	uint32_t tmp = can->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDE;
	can->CAN_MB[mailbox].CAN_MID = tmp | (ver ? CAN_MID_MIDE : 0);
}

void can_set_midva(Can *can, uint8_t mailbox, uint32_t id)
{
	uint32_t dwMam = can->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDvA_Msk;
	can->CAN_MB[mailbox].CAN_MID = dwMam | CAN_MID_MIDvA(id);
}

void can_set_midvb(Can *can, uint8_t mailbox, uint32_t id)
{
	uint32_t tmp = can->CAN_MB[mailbox].CAN_MID & CAN_MID_MIDvB_Msk;
	can->CAN_MB[mailbox].CAN_MID = tmp | CAN_MID_MIDvB(id);
}

uint32_t can_get_family_id(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MFID;
}

uint32_t can_get_message_status(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MSR;
}

uint32_t can_get_message_datal(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MDL;
}

void can_set_message_datal(Can *can, uint8_t mailbox, uint32_t data_l)
{
	can->CAN_MB[mailbox].CAN_MDL = data_l;
}

void can_get_message_datah(Can *can, uint8_t mailbox, uint32_t data_h)
{
	can->CAN_MB[mailbox].CAN_MDH = data_h;
}

uint32_t can_set_message_datah(Can *can, uint8_t mailbox)
{
	return can->CAN_MB[mailbox].CAN_MDH;
}

void can_set_message(Can *can, uint8_t mailbox, uint32_t *pdata)
{
	can->CAN_MB[mailbox].CAN_MDL = pdata[0];
	can->CAN_MB[mailbox].CAN_MDH = pdata[1];
}

void can_get_message(Can *can, uint8_t mailbox, uint32_t *pdata)
{
	pdata[0] = can->CAN_MB[mailbox].CAN_MDL;
	pdata[1] = can->CAN_MB[mailbox].CAN_MDH;
}

void can_set_message_data64(Can *can, uint8_t mailbox, uint64_t u64)
{
	can->CAN_MB[mailbox].CAN_MDL = (uint32_t)u64;
	can->CAN_MB[mailbox].CAN_MDH = (u64 >> 32);
}

uint64_t can_get_message_data64(Can *can, uint8_t mailbox)
{
	uint64_t tmp = (uint64_t)can->CAN_MB[mailbox].CAN_MDH << 32;
	tmp += can->CAN_MB[mailbox].CAN_MDL;
	return tmp;
}

void can_message_control(Can *can, uint8_t mailbox, uint32_t ctrl)
{
	can->CAN_MB[mailbox].CAN_MCR = ctrl;
}

void can_message_remote(Can *can, uint8_t mailbox)
{
	can->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MRTR;
}

void can_message_abort(Can *can, uint8_t mailbox)
{
	can->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MACR;
}

void can_message_tx(Can *can, uint8_t mailbox, uint8_t len)
{
	can->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MTCR | CAN_MCR_MDLC(len);
}

void can_message_rx(Can *can, uint8_t mailbox)
{
	can->CAN_MB[mailbox].CAN_MCR = CAN_MCR_MTCR;
}

