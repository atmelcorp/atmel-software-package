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
 *  Implements functions for Controller Area Network with Flexible Data-rate,
 *  relying on the MCAN peripheral.
 */
/** \addtogroup can_module
 *@{*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "can/mcan.h"
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

void mcan_reconfigure(Mcan *mcan)
{
	uint32_t val;

	val = mcan->MCAN_CCCR & ~MCAN_CCCR_CCE;
	assert((val & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_ENABLED);
	/* Enable writing to configuration registers */
	mcan->MCAN_CCCR = val | MCAN_CCCR_CCE_CONFIGURABLE;
}

bool mcan_set_mode(Mcan *mcan, enum can_mode mode)
{
	uint32_t val;

#ifdef MCAN_CCCR_CMR
	val = mcan->MCAN_CCCR & ~MCAN_CCCR_CME_Msk;
	switch (mode) {
	case CAN_MODE_CAN:
		if (val != MCAN_CCCR_CME_ISO11898_1) {
			val &= ~MCAN_CCCR_CMR_Msk;
			mcan->MCAN_CCCR = val | MCAN_CCCR_CMR_ISO11898_1;
			while ((mcan->MCAN_CCCR &
				(MCAN_CCCR_CMR_Msk | MCAN_CCCR_FDBS | MCAN_CCCR_FDO)) != 0)
				{ /* wait */ }
		}
		break;
	case CAN_MODE_CAN_FD_CONST_RATE:
		if (val != MCAN_CCCR_CME_FD) {
			val &= ~MCAN_CCCR_CMR_Msk;
			mcan->MCAN_CCCR = val | MCAN_CCCR_CME_FD | MCAN_CCCR_CMR_FD;
		}
		break;
	case CAN_MODE_CAN_FD_DUAL_RATE:
		if ((val == MCAN_CCCR_CME_ISO11898_1) || (val == MCAN_CCCR_CME_FD)) {
			val &= ~MCAN_CCCR_CMR_Msk;
			mcan->MCAN_CCCR = val | MCAN_CCCR_CME(2) | MCAN_CCCR_CMR_FD_BITRATE_SWITCH;
		}
		break;
	default:
		return false;
	}
#else
	val = mcan->MCAN_CCCR & ~(MCAN_CCCR_BRSE | MCAN_CCCR_FDOE);

	switch (mode) {
	case CAN_MODE_CAN:
		mcan->MCAN_CCCR = val | MCAN_CCCR_BRSE_DISABLED | MCAN_CCCR_FDOE_DISABLED;
		break;
	case CAN_MODE_CAN_FD_CONST_RATE:
		mcan->MCAN_CCCR = val | MCAN_CCCR_BRSE_DISABLED | MCAN_CCCR_FDOE_ENABLED;
		break;
	case CAN_MODE_CAN_FD_DUAL_RATE:
		mcan->MCAN_CCCR = val | MCAN_CCCR_BRSE_ENABLED | MCAN_CCCR_FDOE_ENABLED;
		break;
	default:
		return false;
	}
#endif
	return true;
}

enum can_mode mcan_get_mode(Mcan *mcan)
{
	const uint32_t cccr = mcan->MCAN_CCCR;

#ifdef CONFIG_SOC_SAMV71
	if ((cccr & MCAN_CCCR_CME_Msk) == MCAN_CCCR_CME_ISO11898_1)
		return CAN_MODE_CAN;
	if ((cccr & MCAN_CCCR_CME_Msk) == MCAN_CCCR_CME_FD)
		return CAN_MODE_CAN_FD_CONST_RATE;
#else
	if ((cccr & MCAN_CCCR_FDOE) == MCAN_CCCR_FDOE_DISABLED)
		return CAN_MODE_CAN;
	if ((cccr & MCAN_CCCR_BRSE) == MCAN_CCCR_BRSE_DISABLED)
		return CAN_MODE_CAN_FD_CONST_RATE;
#endif
	return CAN_MODE_CAN_FD_DUAL_RATE;
}

void mcan_set_tx_queue_mode(Mcan *mcan)
{
	mcan->MCAN_TXBC |= MCAN_TXBC_TFQM;
}

void mcan_enable(Mcan *mcan)
{
	uint32_t index, val;

	/* Depending on bus condition, the HW may switch back to the
	 * Initialization state, by itself. Therefore, upon timeout, return.
	 * [Using an arbitrary timeout criterion.] */
	for (index = 0; index < 1024; index++) {
		val = mcan->MCAN_CCCR;
		if ((val & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_DISABLED)
			break;
		if (index == 0)
			mcan->MCAN_CCCR = (val & ~MCAN_CCCR_INIT)
			    | MCAN_CCCR_INIT_DISABLED;
	}
}

void mcan_disable(Mcan *mcan)
{
	uint32_t val;
	bool initial;

	for (initial = true; true; initial = false) {
		val = mcan->MCAN_CCCR;
		if ((val & MCAN_CCCR_INIT) == MCAN_CCCR_INIT_ENABLED)
			break;
		if (initial)
			mcan->MCAN_CCCR = (val & ~MCAN_CCCR_INIT)
			    | MCAN_CCCR_INIT_ENABLED;
	}
}

void mcan_loopback(Mcan *mcan, bool loop_back)
{
	if (loop_back) {
		mcan->MCAN_CCCR |= MCAN_CCCR_TEST_ENABLED;
//		mcan->MCAN_CCCR |= MCAN_CCCR_MON_ENABLED;	/* for internal loop back */
		mcan->MCAN_TEST |= MCAN_TEST_LBCK_ENABLED;
	} else
		mcan->MCAN_TEST &= ~MCAN_TEST_LBCK_ENABLED;
}

bool mcan_get_length_code(uint8_t len, enum mcan_dlc *dlc)
{
	assert(dlc);

	if (len <= 8) {
		*dlc = (enum mcan_dlc)len;
		return true;
	}
	if (len % 4)
		return false;
	len /= 4;
	if (len <= 6) {
		*dlc = (enum mcan_dlc)(len + 6);
		return true;
	}
	if (len % 4)
		return false;
	len /= 4;
	if (len > 4)
		return false;
	*dlc = (enum mcan_dlc)(len + 11);
	return true;
}

bool mcan_set_rx_element_size(Mcan *mcan, uint8_t buf,
		uint8_t fifo0, uint8_t fifo1)
{
	uint32_t reg;
	enum mcan_dlc dlc;

	if ((MCAN_CCCR_CCE | MCAN_CCCR_INIT) !=
		((MCAN_CCCR_CCE | MCAN_CCCR_INIT) & mcan->MCAN_CCCR))
		return false;

	if (!mcan_get_length_code(buf, &dlc))
		return false;
	reg = MCAN_RXESC_RBDS(dlc < CAN_DLC_8 ? 0 : dlc - CAN_DLC_8);
	if (!mcan_get_length_code(fifo0, &dlc))
		return false;
	reg |= MCAN_RXESC_F0DS(dlc < CAN_DLC_8 ? 0 : dlc - CAN_DLC_8);
	if (!mcan_get_length_code(fifo1, &dlc))
		return false;
	reg |= MCAN_RXESC_F1DS(dlc < CAN_DLC_8 ? 0 : dlc - CAN_DLC_8);
	mcan->MCAN_RXESC = reg;
	return true;
}

bool mcan_set_tx_element_size(Mcan *mcan, uint8_t buf)
{
	enum mcan_dlc dlc;

	if ((MCAN_CCCR_CCE | MCAN_CCCR_INIT) !=
		((MCAN_CCCR_CCE | MCAN_CCCR_INIT) & mcan->MCAN_CCCR))
		return false;

	if (!mcan_get_length_code(buf, &dlc))
		return false;
	mcan->MCAN_TXESC = MCAN_TXESC_TBDS(dlc < CAN_DLC_8 ? 0 : dlc - CAN_DLC_8);
	return true;
}

void mcan_enable_rx_array_flag(Mcan *mcan, uint8_t line)
{
	assert(line == 0 || line == 1);

	if (line) {
		mcan->MCAN_ILS |= MCAN_ILS_DRXL;
		mcan->MCAN_ILE |= MCAN_ILE_EINT1;
	} else {
		mcan->MCAN_ILS &= ~MCAN_ILS_DRXL;
		mcan->MCAN_ILE |= MCAN_ILE_EINT0;
	}
	mcan->MCAN_IR = MCAN_IR_DRX;   /* clear previous flag */
	mcan->MCAN_IE |= MCAN_IE_DRXE;   /* enable it */
}

bool mcan_is_buffer_sent(Mcan *mcan, uint8_t buf_idx)
{
	return mcan->MCAN_TXBTO & (1 << buf_idx) ? true : false;
}

bool mcan_rx_buffer_data(Mcan *mcan, uint8_t buf_idx)
{
	if (buf_idx < 32)
		return mcan->MCAN_NDAT1 & (1 << buf_idx) ? true : false;
	else if (buf_idx < 64)
		return mcan->MCAN_NDAT2 & (1 << (buf_idx - 32)) ? true : false;
	else
		return false;
}
/**@}*/

