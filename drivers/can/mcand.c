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

/** \file */
/** \addtogroup cand_module
 *@{*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>

#include "barriers.h"
#include "board.h"
#include "can/mcand.h"
#include "errno.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define MCAN_INT_ALL 0x3FCFFFFF

#define MCAN_ERRS 0xFFFFFFFF

struct _mcan_quanta {
	uint16_t before_sp; /* duration of the time segment before the
			     * sample point (Sync_Seg + Prop_Seg +
			     * Phase_Seg1), expressed in CAN time quanta */

	uint8_t after_sp;  /* duration of the time segment after the sample point
			    * (Phase_Seg2), expressed in CAN time quanta */

	uint8_t sync_jump; /* duration of a (re)synchronization jump,
			    * expressed in CAN time quanta */
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* size of Rx/Tx Buffer Element: 2 bytes (R0+R1 or T0+T1)*/
#define MCAN_RAM_BUF_HDR_SIZE 2

/* size of Standard Message ID Filter: 1 byte (S0) */
#define MCAN_RAM_FILT_STD_SIZE 1

/* size of Extended Message ID Filter: 2 bytes (F0+F1) */
#define MCAN_RAM_FILT_EXT_SIZE 2

/* size of Tx Event FIFO Element: 2 bytes (E0+E1) */
#define MCAN_RAM_TX_EVT_SIZE 2

/* size of our custom Rx and Tx Buffer Elements, in words */
#define RAM_BUF_SIZE                  (MCAN_RAM_BUF_HDR_SIZE + 64u / 4)

#define RAM_FILT_STD_CNT       (8u)
#define RAM_FILT_EXT_CNT       (8u)
#define RAM_RX_FIFO0_CNT       (12u)
/* no Rx FIFO 1 in our Message RAM */
#define RAM_RX_FIFO1_CNT       (0u)
#define RAM_RX_BUF_CNT         (4u)
/* no Tx Event FIFO in our Message RAM */
#define RAM_TX_EVENT_CNT       (0u)
#define RAM_TX_BUF_CNT         (4u)
#define RAM_TX_FIFO_CNT        (4u)

#define MSG_RAM_SIZE0      ( \
	RAM_FILT_STD_CNT * MCAN_RAM_FILT_STD_SIZE \
	+ RAM_FILT_EXT_CNT * MCAN_RAM_FILT_EXT_SIZE \
	+ RAM_TX_BUF_CNT * RAM_BUF_SIZE \
	+ RAM_TX_FIFO_CNT * RAM_BUF_SIZE )

#define MSG_RAM_SIZE1      ( 0 \
	+ RAM_RX_FIFO0_CNT * RAM_BUF_SIZE \
	+ RAM_RX_FIFO1_CNT * RAM_BUF_SIZE \
	+ RAM_RX_BUF_CNT * RAM_BUF_SIZE )

#define MSG_RAM_ITEM_CNT (\
	  RAM_FILT_STD_CNT \
	+ RAM_FILT_EXT_CNT \
	+ RAM_RX_FIFO0_CNT \
	+ RAM_RX_FIFO1_CNT \
	+ RAM_RX_BUF_CNT \
	+ RAM_TX_BUF_CNT \
	+ RAM_TX_FIFO_CNT)


/* Allocate the Message RAM from non-cached memory.
 * The Buffer Elements in the Message RAM are contiguous and not aligned on
 * cache lines. If caching was turned on, it would be necessary to explicitly
 * clean the data cache lines matching transmit buffers, and then invalidate the
 * data cache lines matching receive buffers. Since these sections overlap in
 * the cache, strong constraints would apply as soon as several transmit and
 * receive buffers were used concurrently.
 * An alternative solution: if spare Buffers Elements are available, they may be
 * used to separate otherwise conflicting, active Buffer Elements, and then
 * benefit from memory caching.
 */
NOT_CACHED
static uint32_t mcan_msg_ram0[CAN_IFACE_COUNT][MSG_RAM_SIZE0];
NOT_CACHED
static uint32_t mcan_msg_ram1[CAN_IFACE_COUNT][MSG_RAM_SIZE1];

static struct mcan_config mcan_cfg = {
	.item_count[MCAN_RAM_STD_FILTER] = RAM_FILT_STD_CNT,
	.item_count[MCAN_RAM_EXT_FILTER] = RAM_FILT_EXT_CNT,
	.item_count[MCAN_RAM_RX_FIFO0]	 = RAM_RX_FIFO0_CNT,
	.item_count[MCAN_RAM_RX_FIFO1]	 = RAM_RX_FIFO1_CNT,
	.item_count[MCAN_RAM_RX_BUFFER]  = RAM_RX_BUF_CNT,
	.item_count[MCAN_RAM_TX_EVENT]	 = RAM_TX_EVENT_CNT,
	.item_count[MCAN_RAM_TX_BUFFER]  = RAM_TX_BUF_CNT,
	.item_count[MCAN_RAM_TX_FIFO]	 = RAM_TX_FIFO_CNT,

	.buf_size_rx_fifo0 = 64,
	.buf_size_rx_fifo1 = 0,
	.buf_size_rx = 64,
	.buf_size_tx = 64,
};

static struct _cand_ram_item mcan_ram_item[MSG_RAM_ITEM_CNT];

static struct _mcan_desc mcan_desc[CAN_IFACE_COUNT];

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Convert Data Length Code to actual data length.
 * \param dlc  CAN_DLC_xx enum value
 * \return Data length, expressed in bytes.
 */
static uint8_t get_data_length(enum mcan_dlc dlc)
{
	assert((dlc == CAN_DLC_0 || dlc > CAN_DLC_0) && dlc <= CAN_DLC_64);

	if (dlc <= CAN_DLC_8)
		return (uint8_t)dlc;
	if (dlc <= CAN_DLC_24)
		return ((uint8_t)dlc - 6) * 4;
	return ((uint8_t)dlc - 11) * 16;
}

/**
 * \brief Compute the size of the Message RAM, depending on the application.
 * \param set  Pointer to a MCAN instance that will be setup accordingly.
 * \param cfg  MCAN configuration to be considered. Only integer size parameters
 * need to be configured. The other parameters can be left blank at this stage.
 * \param size  address where the required size of the Message RAM will be
 * written, expressed in (32-bit) words.
 * \return 0 if successful
 * value.
 */
static int configure_ram(struct mcan_set *set, const struct mcan_config *cfg)
{
	uint32_t size[2];
	if (cfg->item_count[MCAN_RAM_STD_FILTER] > 128
		|| cfg->item_count[MCAN_RAM_EXT_FILTER] > 64
		|| cfg->item_count[MCAN_RAM_RX_FIFO0] > 64
		|| cfg->item_count[MCAN_RAM_RX_FIFO1] > 64
		|| cfg->item_count[MCAN_RAM_RX_BUFFER] > 64
		|| cfg->item_count[MCAN_RAM_TX_EVENT] > 32
		|| cfg->item_count[MCAN_RAM_TX_BUFFER] > 32
		|| cfg->item_count[MCAN_RAM_TX_FIFO] > 32
		|| cfg->item_count[MCAN_RAM_TX_BUFFER] + cfg->item_count[MCAN_RAM_TX_FIFO] > 32
		|| cfg->buf_size_rx_fifo0 > 64
		|| cfg->buf_size_rx_fifo1 > 64
		|| cfg->buf_size_rx > 64 || cfg->buf_size_tx > 64)
		return -EINVAL;

	set->ram_filt_std = cfg->msg_ram[0];
	size[0] = (uint32_t)cfg->item_count[MCAN_RAM_STD_FILTER] *
				MCAN_RAM_FILT_STD_SIZE;

	set->ram_filt_ext = cfg->msg_ram[0] + size[0];
	size[0] += (uint32_t)cfg->item_count[MCAN_RAM_EXT_FILTER] *
				MCAN_RAM_FILT_EXT_SIZE;

	set->ram_fifo_rx0 = cfg->msg_ram[1];
	size[1] = (uint32_t)cfg->item_count[MCAN_RAM_RX_FIFO0] *
				(MCAN_RAM_BUF_HDR_SIZE + cfg->buf_size_rx_fifo0 / 4);

	set->ram_fifo_rx1 = cfg->msg_ram[1] + size[1];
	size[1] += (uint32_t)cfg->item_count[MCAN_RAM_RX_FIFO1] *
				(MCAN_RAM_BUF_HDR_SIZE + cfg->buf_size_rx_fifo1 / 4);

	set->ram_array_rx = cfg->msg_ram[1] + size[1];
	size[1] += (uint32_t)cfg->item_count[MCAN_RAM_RX_BUFFER] *
				(MCAN_RAM_BUF_HDR_SIZE + cfg->buf_size_rx / 4);

	set->ram_fifo_tx_evt = cfg->msg_ram[0] + size[0];
	size[0] += (uint32_t)cfg->item_count[MCAN_RAM_TX_EVENT] *
				MCAN_RAM_TX_EVT_SIZE;

	set->ram_array_tx = cfg->msg_ram[0] + size[0];
	size[0] += (uint32_t)cfg->item_count[MCAN_RAM_TX_BUFFER] *
				(MCAN_RAM_BUF_HDR_SIZE + cfg->buf_size_tx / 4);
	size[0] += (uint32_t)cfg->item_count[MCAN_RAM_TX_FIFO] *
				(MCAN_RAM_BUF_HDR_SIZE + cfg->buf_size_tx / 4);

	return 0;
}

static int mcan_get_index(Mcan *mcan)
{
	if (MCAN0 == mcan)
		return 0;
#ifdef MCAN1
	if (MCAN1 == mcan)
		return 1;
#endif
#ifdef MCAN2
	if (MCAN2 == mcan)
		return 2;
#endif
#ifdef MCAN3
	if (MCAN3 == mcan)
		return 3;
#endif
	trace_error("failed when getting the index of MCAN\r\n");
	return 0;
}

/**
 * \brief Initialize the MCAN hardware for the given peripheral.
 * Default: Non-FD, ISO 11898-1 CAN mode; mixed mode TX Buffer + FIFO.
 * \param set  Pointer to uninitialized driver instance data.
 * \param cfg  MCAN configuration to be used.
 * \return 0 if successful
 * value.
 */
static int mcan_initialize(struct _mcan_desc* desc, const struct mcan_config *cfg)
{
	struct mcan_set *set = &desc->set;
	int err;

	assert(set);
	assert(cfg);
	assert(cfg->msg_ram[0]);
	assert(cfg->msg_ram[1]);

	Mcan *mcan = desc->addr;

	memset(set, 0, sizeof(*set));
	err = configure_ram(set, cfg);
	if (err < 0)
		return err;
	set->cfg = *cfg;

	/* Configure the MSB of the Message RAM Base Address */
	mcan_set_base_addr_msb16(mcan, (uint32_t)cfg->msg_ram[0]);

	/* Reset the CC Control Register */
	mcan->MCAN_CCCR = 0 | MCAN_CCCR_INIT_ENABLED;

	mcan_disable(mcan);
	mcan_reconfigure(mcan);

	/* Global Filter Configuration: Reject remote frames, reject non-matching frames */
	mcan->MCAN_GFC = MCAN_GFC_RRFE_REJECT | MCAN_GFC_RRFS_REJECT
		| MCAN_GFC_ANFE(2) | MCAN_GFC_ANFS(2);

	/* Extended ID Filter AND mask */
	mcan->MCAN_XIDAM = 0x1FFFFFFF;

	/* Interrupt configuration - leave initialization with all interrupts off
	 * Disable all interrupts */
	mcan_disable_it(mcan, MCAN_INT_ALL);
	mcan->MCAN_TXBTIE = 0x00000000;
	/* All interrupts directed to Line 0 */
	mcan_line0_it(mcan, MCAN_INT_ALL);
	/* Disable both interrupt LINE 0 & LINE 1 */
	mcan_disable_line_it(mcan, MCAN_ILE_EINT1 | MCAN_ILE_EINT0);
	/* Clear all interrupt flags */
	mcan_clear_status(mcan, MCAN_INT_ALL);

	/* Configure Message RAM starting addresses and element count */
	/* 11-bit Message ID Rx Filters */
	mcan->MCAN_SIDFC =
		MCAN_SIDFC_FLSSA((uint32_t)set->ram_filt_std >> 2)
		| MCAN_SIDFC_LSS(cfg->item_count[MCAN_RAM_STD_FILTER]);
	/* 29-bit Message ID Rx Filters */
	mcan->MCAN_XIDFC =
		MCAN_XIDFC_FLESA((uint32_t)set->ram_filt_ext >> 2)
		| MCAN_XIDFC_LSE(cfg->item_count[MCAN_RAM_EXT_FILTER]);
	/* Rx FIFO 0 */
	mcan->MCAN_RXF0C =
		MCAN_RXF0C_F0SA((uint32_t)set->ram_fifo_rx0 >> 2)
		| MCAN_RXF0C_F0S(cfg->item_count[MCAN_RAM_RX_FIFO0])
		| MCAN_RXF0C_F0WM(0)
		| 0;   /* clear MCAN_RXF0C_F0OM */
	/* Rx FIFO 1 */
	mcan->MCAN_RXF1C =
		MCAN_RXF1C_F1SA((uint32_t)set->ram_fifo_rx1 >> 2)
		| MCAN_RXF1C_F1S(cfg->item_count[MCAN_RAM_RX_FIFO1])
		| MCAN_RXF1C_F1WM(0)
		| 0;   /* clear MCAN_RXF1C_F1OM */
	/* Dedicated Rx Buffers
	 * Note: the HW does not know (and does not care about) how many
	 * dedicated Rx Buffers are used by the application. */
	mcan->MCAN_RXBC =
		MCAN_RXBC_RBSA((uint32_t)set->ram_array_rx >> 2);
	/* Tx Event FIFO */
	mcan->MCAN_TXEFC =
		MCAN_TXEFC_EFSA((uint32_t)set->ram_fifo_tx_evt >> 2)
		| MCAN_TXEFC_EFS(cfg->item_count[MCAN_RAM_TX_EVENT])
		| MCAN_TXEFC_EFWM(0);
	/* Tx Buffers */
	mcan->MCAN_TXBC =
		MCAN_TXBC_TBSA((uint32_t)set->ram_array_tx >> 2)
		| MCAN_TXBC_NDTB(cfg->item_count[MCAN_RAM_TX_BUFFER])
		| MCAN_TXBC_TFQS(cfg->item_count[MCAN_RAM_TX_FIFO])
		| 0;   /* clear MCAN_TXBC_TFQM */

	/* Configure the size of data fields in Rx and Tx Buffer Elements */
	if (!mcan_set_rx_element_size(mcan,
			cfg->buf_size_rx, cfg->buf_size_rx_fifo0, cfg->buf_size_rx_fifo1))
		return -EINVAL;

	if (!mcan_set_tx_element_size(mcan, cfg->buf_size_tx))
		return -EINVAL;

	mcan->MCAN_NDAT1 = 0xFFFFFFFF;   /* clear new (rx) data flags */
	mcan->MCAN_NDAT2 = 0xFFFFFFFF;   /* clear new (rx) data flags */

#ifdef MCAN_CCCR_CME
	uint32_t reg = mcan->MCAN_CCCR & ~(MCAN_CCCR_CME_Msk | MCAN_CCCR_CMR_Msk);
	mcan->MCAN_CCCR = reg | MCAN_CCCR_CME_ISO11898_1;
	mcan->MCAN_CCCR = reg | (MCAN_CCCR_CMR_ISO11898_1 | MCAN_CCCR_CME_ISO11898_1);
#else
	mcan->MCAN_CCCR = (mcan->MCAN_CCCR & ~(MCAN_CCCR_BRSE | MCAN_CCCR_FDOE)) |
			MCAN_CCCR_PXHD | MCAN_CCCR_BRSE_DISABLED | MCAN_CCCR_FDOE_DISABLED;
#endif
	mcan_enable_it(mcan, MCAN_IE_BOE);

	return 0;
}

static int mcand_get_ram(struct _mcan_desc *desc,
				enum _mcan_ram item, uint8_t *index)
{
	bool rv = true;
	uint8_t i;
	uint8_t cnt;
	uint32_t *status;

	assert(item < MCAN_RAM_TOTAL);
	assert(index);

	cnt = desc->set.cfg.item_count[(uint32_t)item];
	if (item == MCAN_RAM_TX_FIFO) {
		/* Configured for FifoQ and FifoQ not full? */
		if (cnt == 0 || (desc->addr->MCAN_TXFQS & MCAN_TXFQS_TFQF))
			return -EINVAL;
		i = (uint8_t)((desc->addr->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk)
			>> MCAN_TXFQS_TFQPI_Pos);
		i -= desc->set.cfg.item_count[MCAN_RAM_TX_BUFFER];
	} else if (item == MCAN_RAM_RX_FIFO0) {
		i = (uint8_t)((desc->addr->MCAN_RXF0S & MCAN_RXF0S_F0PI_Msk)
			>> MCAN_RXF0S_F0PI_Pos);
	} else if (item == MCAN_RAM_RX_FIFO1) {
		i = (uint8_t)((desc->addr->MCAN_RXF1S & MCAN_RXF1S_F1PI_Msk)
			>> MCAN_RXF1S_F1PI_Pos);
	} else
		rv = false;

	status = &desc->set.cfg.ram_status[(uint32_t)item];

	if (rv) {
		if ((i >= cnt) || (status[i / 32] & (1 << (i & 0x1F))))
			return -EINVAL;
		status[i / 32] |= (1 << (i & 0x1F));
		*index = i;
		return 0;
	}

	for (i = 0; i < cnt; i ++) {
		if ((status[i / 32] & (1 << (i & 0x1F))) == 0) {
			status[i / 32] |= (1 << (i & 0x1F));
			*index = i;
			return 0;
		}
	}

	return -ENOSYS;
}

static void mcand_release_ram(struct _mcan_desc *desc,
				enum _mcan_ram item, uint8_t index)
{
	uint32_t *status;
	uint32_t *filter;

	assert(item < MCAN_RAM_TOTAL);
	if (index >= desc->set.cfg.item_count[(uint32_t)item]) {
		trace_error("MCAND: release the ram which is not used. %u %u\n\r", (unsigned)item, (unsigned)index);
	}
	assert(index < desc->set.cfg.item_count[(uint32_t)item]);

	status = &desc->set.cfg.ram_status[(uint32_t)item];

	if (0 != (status[index / 32] & (1 << (index & 0x1F)))) {
		status[index / 32] &= (~(1 << (index & 0x1F)));
	} else
		trace_error("MCAND: release the ram which is not used. %u %u\n\r", (unsigned)item, (unsigned)index);

	if (item == MCAN_RAM_STD_FILTER) {
		filter = desc->set.ram_filt_std + index * MCAN_RAM_FILT_STD_SIZE;
		*filter = MCAN_RAM_S0_SFEC_DIS;
	} else if (item == MCAN_RAM_EXT_FILTER) {
		filter = desc->set.ram_filt_ext + index * MCAN_RAM_FILT_EXT_SIZE;
		*filter = MCAN_RAM_F0_EFEC_DIS;
	} else if (item == MCAN_RAM_RX_FIFO0) {
		mcan_rx_fifo0_ack(desc->addr, index);
	} else if (item == MCAN_RAM_RX_FIFO1) {
		mcan_rx_fifo1_ack(desc->addr, index);
	}
}

static void _mcand_tx_buffer_handler(struct _mcan_desc *desc)
{
	uint32_t buf_idx;
	uint32_t status;
	struct _cand_ram_item *ram_item;
	uint32_t *tx_buf;

	uint32_t buf_count = desc->set.cfg.item_count[MCAN_RAM_TX_BUFFER];
	uint32_t ram_idx =	desc->set.cfg.ram_index[MCAN_RAM_TX_BUFFER];
	Mcan *mcan = desc->addr;

	status = mcan->MCAN_TXBTO;
	for (buf_idx = 0; buf_idx < buf_count; buf_idx ++) {
		if (status & (1 << buf_idx) & mcan->MCAN_TXBTIE) {
			mcan->MCAN_TXBTIE &= ~(1 << buf_idx);
			ram_item = &desc->ram_item[ram_idx + buf_idx];
			tx_buf = desc->set.ram_array_tx +
				buf_idx *
				(MCAN_RAM_BUF_HDR_SIZE + desc->set.cfg.buf_size_tx / sizeof(uint32_t));

			if (tx_buf[0] & MCAN_RAM_T0_ESI) {
				// Error State Indicator
			}
			if (tx_buf[0] & MCAN_RAM_T0_RTR) {
				// Remote Transmission Request
			}

			if (ram_item->buf)
				ram_item->buf->attr |= CAND_BUF_ATTR_TRANSFER_DONE;
			else
				trace_error("tx_buf null, idx=%u\n\r", (unsigned)buf_idx);

			if (buf_idx >= buf_count)
				mcand_release_ram(desc, MCAN_RAM_TX_FIFO, buf_idx);
			else
				mcand_release_ram(desc, MCAN_RAM_TX_BUFFER, buf_idx);

			callback_copy(&ram_item->cb, NULL);
		}
	}
}

static void _mcand_tx_fifo_handler(struct _mcan_desc *desc)
{
	uint32_t fifo_idx;
	uint32_t id;
	uint32_t len;
	struct _cand_ram_item *ram_item;
	uint32_t *tx_fifo;
	uint32_t fifo_start = desc->set.cfg.item_count[MCAN_RAM_TX_BUFFER];
	uint32_t fifo_count = desc->set.cfg.item_count[MCAN_RAM_TX_FIFO];
	uint32_t ram_idx =	desc->set.cfg.ram_index[MCAN_RAM_TX_BUFFER];
	Mcan *mcan = desc->addr;
	uint8_t get_index = (uint8_t)
		((mcan->MCAN_TXFQS & MCAN_TXFQS_TFGI_Msk) >> MCAN_TXFQS_TFGI_Pos);
	uint8_t put_index = (uint8_t)
		((mcan->MCAN_TXFQS & MCAN_TXFQS_TFGI_Msk) >> MCAN_TXFQS_TFGI_Pos);

	get_index = (get_index == fifo_start) ? fifo_start + fifo_count - 1 : get_index - 1;

	for (fifo_idx = get_index; ; fifo_idx ++) {
		if (fifo_idx >= fifo_start + fifo_count)
			fifo_idx = fifo_start;
		if (fifo_idx == put_index)
			break;

		ram_item = &desc->ram_item[ram_idx + fifo_idx];
		tx_fifo = desc->set.ram_array_tx +
			fifo_idx *
			(MCAN_RAM_BUF_HDR_SIZE + desc->set.cfg.buf_size_tx / sizeof(uint32_t));

		if (tx_fifo[0] & MCAN_RAM_T0_ESI) {
			// Error State Indicator
		}
		if (tx_fifo[0] & MCAN_RAM_T0_RTR) {
			// Remote Transmission Request
		}
		if (tx_fifo[0] & MCAN_RAM_T0_XTD)
			id = (tx_fifo[0] & MCAN_RAM_T0_XTDID_Msk) >> MCAN_RAM_T0_XTDID_Pos;
		else
			id = (tx_fifo[0] & MCAN_RAM_T0_STDID_Msk) >> MCAN_RAM_T0_STDID_Pos;

		len = get_data_length((enum mcan_dlc)
				((tx_fifo[1] & MCAN_RAM_T1_DLC_Msk) >> MCAN_RAM_T1_DLC_Pos));
		printf("tx_fifo idx=%u, id=0x%x, len=%u, data=%08x %08x\n\r",
			(unsigned)fifo_idx, (unsigned)id, (unsigned)len,
			(unsigned)tx_fifo[2], (unsigned)tx_fifo[3]);
		if (ram_item->buf)
			ram_item->buf->attr |= CAND_BUF_ATTR_TRANSFER_DONE;
		else {
			trace_error("tx_fifo null, idx=%u\n\r", (unsigned)fifo_idx);
		}

		mcand_release_ram(desc, MCAN_RAM_TX_FIFO, fifo_idx - fifo_start);

		callback_copy(&ram_item->cb, NULL);
	}
}

static void _mcand_rx_proc(struct _mcan_desc *desc, enum _mcan_ram ram, uint32_t buf_idx)
{
	uint32_t ram_idx =  desc->set.cfg.ram_index[ram];
	struct _cand_ram_item *ram_item = &desc->ram_item[ram_idx + buf_idx];
	uint32_t *rx_buf;
	uint32_t ram_size;

	uint32_t len;
	enum _mcan_ram filter;
	uint8_t filter_idx;
	uint8_t filter_cnt;

	if (MCAN_RAM_RX_FIFO0 == ram) {
		ram_size = desc->set.cfg.buf_size_rx_fifo0;
		rx_buf = desc->set.ram_fifo_rx0;
	} else if (MCAN_RAM_RX_FIFO1 == ram) {
		ram_size = desc->set.cfg.buf_size_rx_fifo1;
		rx_buf = desc->set.ram_fifo_rx1;
	} else if (MCAN_RAM_RX_BUFFER == ram) {
		ram_size = desc->set.cfg.buf_size_rx;
		rx_buf = desc->set.ram_array_rx;
	} else
		assert(false);

	rx_buf += buf_idx * (MCAN_RAM_BUF_HDR_SIZE + ram_size / sizeof(uint32_t));

	if (rx_buf[0] & MCAN_RAM_R0_ESI) {
		// Error State Indicator
	}
	if (rx_buf[0] & MCAN_RAM_R0_RTR) {
		// Remote Transmission Request
	}
	if (rx_buf[0] & MCAN_RAM_R0_XTD) {
		filter = MCAN_RAM_EXT_FILTER;
		filter_cnt = desc->set.cfg.item_count[MCAN_RAM_EXT_FILTER];
	} else {
		filter = MCAN_RAM_STD_FILTER;
		filter_cnt = desc->set.cfg.item_count[MCAN_RAM_STD_FILTER];
	}

	filter_idx = (rx_buf[1] & MCAN_RAM_R1_FIDX_Msk) >> MCAN_RAM_R1_FIDX_Pos;
	len = get_data_length((enum mcan_dlc)
			((rx_buf[1] & MCAN_RAM_R1_DLC_Msk) >> MCAN_RAM_R1_DLC_Pos));

	if (ram_item->buf) {
		/* copy data from the Rx FIFO/Buffer to the application-owned buffer */
		if (len > ram_size)
			len = ram_size;
		if (len > ram_item->buf->size)
			len = ram_item->buf->size;
		memcpy(ram_item->buf->data, &rx_buf[2], len);
		ram_item->buf->size = len;
		ram_item->buf->attr |= CAND_BUF_ATTR_TRANSFER_DONE;
	} else {
		trace_error("rx_buf null, idx=%u\n\r", (unsigned)buf_idx);
	}

	if (0 == (rx_buf[1] & MCAN_RAM_R1_ANMF)) {
		if (filter_idx >= filter_cnt)
			trace_warning("Total %d filters, item %d is invalid!\n\r",
				filter_cnt, filter_idx);
		else
			if ((ram_item->buf->attr & CAND_BUF_ATTR_RX_OVERWRITE) == 0)
				mcand_release_ram(desc, filter, filter_idx);
	}
	if ((ram_item->buf->attr & CAND_BUF_ATTR_RX_OVERWRITE) == 0)
		mcand_release_ram(desc, ram, buf_idx);

	callback_copy(&ram_item->cb, NULL);
}

static void _mcand_rx_buffer_handler(struct _mcan_desc *desc)
{
	uint32_t buf_idx;
	uint32_t status;

	uint32_t buf_count = desc->set.cfg.item_count[MCAN_RAM_RX_BUFFER];
	Mcan *mcan = desc->addr;

	status = mcan->MCAN_NDAT1;
	mcan->MCAN_NDAT1 = status;
	for (buf_idx = 0; buf_idx < buf_count; buf_idx ++) {
		if (status & (1 << buf_idx))
			_mcand_rx_proc(desc, MCAN_RAM_RX_BUFFER, buf_idx);
	}

	if (buf_count < 32)
		return;

	status = mcan->MCAN_NDAT2;
	mcan->MCAN_NDAT2 = status;
	for (buf_idx = 32; buf_idx < buf_count; buf_idx ++) {
		if (status & (1 << (buf_idx - 32)))
			_mcand_rx_proc(desc, MCAN_RAM_RX_BUFFER, buf_idx);
	}
}

static void _mcand_rx_fifo_handler(struct _mcan_desc *desc, enum _mcan_ram fifo)
{
	uint32_t cnt;
	uint32_t get;
	uint32_t total;
	Mcan *mcan = desc->addr;

	if (fifo == MCAN_RAM_RX_FIFO0) {
		cnt = (mcan->MCAN_RXF0S & MCAN_RXF0S_F0FL_Msk) >> MCAN_RXF0S_F0FL_Pos;
		get = (mcan->MCAN_RXF0S & MCAN_RXF0S_F0GI_Msk) >> MCAN_RXF0S_F0GI_Pos;
	} else if (fifo == MCAN_RAM_RX_FIFO1) {
		cnt = (mcan->MCAN_RXF1S & MCAN_RXF1S_F1FL_Msk) >> MCAN_RXF1S_F1FL_Pos;
		get = (mcan->MCAN_RXF1S & MCAN_RXF1S_F1GI_Msk) >> MCAN_RXF1S_F1GI_Pos;
	}
	total = desc->set.cfg.item_count[fifo];

	while (cnt--) {
		_mcand_rx_proc(desc, fifo, get);
		get ++;
		if (get >= total)
			get = 0;
	}
}

/**
 * Interrupt handler for MCAN Driver.
 */
static void _mcan_handler(uint32_t source, void* user_arg)
{
	uint8_t mcan_if;
	uint32_t status;
	struct _mcan_desc *desc;
	Mcan *mcan;

	if ((ID_MCAN0_INT0 == source) || (ID_MCAN0_INT1 == source))
		mcan_if = 0;
#ifdef MCAN1
	else if ((ID_MCAN1_INT0 == source) || (ID_MCAN1_INT1 == source))
		mcan_if = 1;
#endif
#ifdef MCAN2
	else if ((ID_MCAN2_INT0 == source) || (ID_MCAN2_INT1 == source))
		mcan_if = 2;
#endif
#ifdef MCAN3
	else if ((ID_MCAN3_INT0 == source) || (ID_MCAN3_INT1 == source))
		mcan_if = 3;
#endif
	else {
		trace_fatal("MCAN handler error!");
	}

	desc = &mcan_desc[mcan_if];
	mcan = desc->addr;
	status = mcan_get_status(mcan);

	dsb();
	if (status & MCAN_IR_RF0N) {
		mcan_clear_status(mcan, MCAN_IR_RF0N);
		_mcand_rx_fifo_handler(desc, MCAN_RAM_RX_FIFO0);
	}
	if (status & MCAN_IR_RF1N) {
		mcan_clear_status(mcan, MCAN_IR_RF1N);
		_mcand_rx_fifo_handler(desc, MCAN_RAM_RX_FIFO1);
	}

	if (status & MCAN_IR_RF0F) {
		mcan_clear_status(mcan, MCAN_IR_RF0F);
		trace_warning("Receive FIFO 0 Watermark Reached\n\r");
	}
	if (status & MCAN_IR_RF0W) {
		mcan_clear_status(mcan, MCAN_IR_RF0W);
		trace_warning("Receive FIFO 0 Full\n\r");
	}
	if (status & MCAN_IR_RF0L) {
		mcan_clear_status(mcan, MCAN_IR_RF0L);
		trace_warning("Receive FIFO 0 Message Lost\n\r");
	}
	if (status & MCAN_IR_RF1F) {
		mcan_clear_status(mcan, MCAN_IR_RF1F);
		trace_warning("Receive FIFO 1 Watermark Reached\n\r");
	}
	if (status & MCAN_IR_RF1W) {
		mcan_clear_status(mcan, MCAN_IR_RF1W);
		trace_warning("Receive FIFO 1 Full\n\r");
	}
	if (status & MCAN_IR_RF1L) {
		mcan_clear_status(mcan, MCAN_IR_RF1L);
		trace_warning("Receive FIFO 1 Message Lost\n\r");
	}
	if (status & MCAN_IR_HPM) {
		mcan_clear_status(mcan, MCAN_IR_HPM);
		trace_warning("High priority message received\n\r");
	}

	if (status & MCAN_IR_TC) {
		mcan_clear_status(mcan, MCAN_IR_TC);
		_mcand_tx_buffer_handler(desc);
	}

	if (status & MCAN_IR_TCF) {
		mcan_clear_status(mcan, MCAN_IR_TCF);
		trace_info("Transmission Cancellation Finished\n\r");
	}
	if (status & MCAN_IR_TFE) {
		mcan_clear_status(mcan, MCAN_IR_TFE);
		_mcand_tx_fifo_handler(desc);
	}
	if (status & MCAN_IR_TEFN) {
		mcan_clear_status(mcan, MCAN_IR_TEFN);
		trace_info(" Tx Handler wrote Tx Event FIFO element\n\r");
	}
	if (status & MCAN_IR_TEFW) {
		mcan_clear_status(mcan, MCAN_IR_TEFW);
		trace_info("Tx Event FIFO fill level reached watermark\n\r");
	}
	if (status & MCAN_IR_TEFF) {
		mcan_clear_status(mcan, MCAN_IR_TEFF);
		trace_info("Tx Event FIFO full\n\r");
	}
	if (status & MCAN_IR_TEFL) {
		mcan_clear_status(mcan, MCAN_IR_TEFL);
		trace_info("Tx Event FIFO element lost\n\r");
	}
	if (status & MCAN_IR_TSW) {
		mcan_clear_status(mcan, MCAN_IR_TSW);
		trace_info("Timestamp counter wrapped around\n\r");
	}

	if (status & MCAN_IR_DRX) {
		mcan_clear_status(mcan, MCAN_IR_DRX);
		_mcand_rx_buffer_handler(desc);
	}
	if (status & MCAN_IR_ELO) {
		mcan_clear_status(mcan, MCAN_IR_ELO);
		trace_info("Error Logging Overflow\n\r");
	}
	if (status & MCAN_IR_EP) {
		mcan_clear_status(mcan, MCAN_IR_EP);
		trace_info("Error_Passive status changed\n\r");
	}
	if (status & MCAN_IR_EW) {
		mcan_clear_status(mcan, MCAN_IR_EW);
		trace_info("Error_Warning status changed\n\r");
	}
	if (status & MCAN_IR_BO) {
		mcan_clear_status(mcan, MCAN_IR_BO);
		trace_info("Bus_Off status changed\n\r");
		memset(mcan_desc[mcan_if].set.cfg.ram_status, 0,
			sizeof(mcan_desc[mcan_if].set.cfg.ram_status));
	}
	if (status & MCAN_IR_WDI) {
		mcan_clear_status(mcan, MCAN_IR_WDI);
		trace_info("Message RAM Watchdog event due to missing READY\n\r");
	}
#ifdef MCAN_IR_PEA
	if (status & MCAN_IR_PEA) {
		mcan_clear_status(mcan, MCAN_IR_PEA);
		trace_info("Protocol Error in Arbitration Phase\n\r");
	}
#endif
#ifdef MCAN_IR_PED
	if (status & MCAN_IR_PED) {
		mcan_clear_status(mcan, MCAN_IR_PED);
		trace_info("Protocol Error in Data Phase\n\r");
	}
#endif
#ifdef MCAN_IR_CRCE
	if (status & MCAN_IR_CRCE) {
		mcan_clear_status(mcan, MCAN_IR_CRCE);
		trace_info("CRC Error\n\r");
	}
#endif
#ifdef MCAN_IR_BE
	if (status & MCAN_IR_BE) {
		mcan_clear_status(mcan, MCAN_IR_BE);
		trace_info("Bit Error\n\r");
	}
#endif
#ifdef MCAN_IR_ARA
	if (status & MCAN_IR_ARA) {
		mcan_clear_status(mcan, MCAN_IR_ARA);
		trace_info("Access to Reserved Address\n\r");
	}
#endif
#ifdef MCAN_IR_ACKE
	if (status & MCAN_IR_ACKE) {
		mcan_clear_status(mcan, MCAN_IR_ACKE);
		trace_info("Acknowledge Error\n\r");
	}
#endif
#ifdef MCAN_IR_FOE
	if (status & MCAN_IR_FOE) {
		mcan_clear_status(mcan, MCAN_IR_FOE);
		trace_info("Format Error\n\r");
	}
#endif
#ifdef MCAN_IR_STE
	if (status & MCAN_IR_STE) {
		mcan_clear_status(mcan, MCAN_IR_STE);
		trace_info("Stuff Error\n\r");
	}
#endif
}

/**
 * \brief Calculate and configure the baudrate
 * \return 0 in success
 */
static int mcand_set_baudrate(Mcan *mcan, uint32_t freq, uint32_t freq_fd)
{
	uint32_t id;
	uint32_t clk;
	uint32_t val;

	const struct _mcan_quanta quanta = {
		.before_sp = 1 + 2 + 12,
		.after_sp  = 12,
		.sync_jump = 4,
	};
	const struct _mcan_quanta quanta_fd = {
		.before_sp = 1 + 2 + 5,
		.after_sp  = 5,
		.sync_jump = 2,
	};

	id = get_mcan_id_from_addr(mcan, 0);
	assert(id < ID_PERIPH_COUNT);

#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
	/* Retrieve the frequency of the CAN core clock i.e. the Generated Clock */
	clk = pmc_get_gck_clock(id);
#else
	clk = pmc_get_peripheral_clock(id);
#endif

	/* Configure CAN bit timing */
	if (freq == 0 || quanta.before_sp < 3 || quanta.before_sp > 257
		|| quanta.after_sp < 1 || quanta.after_sp > 128
		|| quanta.sync_jump < 1 || quanta.sync_jump > 128)
		return -EINVAL;
	/* Compute the Nominal Baud Rate Prescaler */
	val = ROUND_INT_DIV(clk, freq * (quanta.before_sp + quanta.after_sp));
	if (val < 1 || val > 512)
		return -EINVAL;
#ifdef MCAN_NBTP_NBRP
	/* Apply bit timing configuration */
	mcan->MCAN_NBTP = MCAN_NBTP_NBRP(val - 1)
		| MCAN_NBTP_NTSEG1(quanta.before_sp - 1 - 1)
		| MCAN_NBTP_NTSEG2(quanta.after_sp - 1)
		| MCAN_NBTP_NSJW(quanta.sync_jump - 1);
#endif
#ifdef MCAN_BTP_BRP
	mcan->MCAN_BTP = MCAN_BTP_BRP(val - 1)
		| MCAN_BTP_TSEG1(quanta.before_sp - 1 - 1)
		| MCAN_BTP_TSEG2(quanta.after_sp - 1)
		| MCAN_BTP_SJW(quanta.sync_jump - 1);
#endif
	/* Configure fast CAN FD bit timing */
	if (freq_fd < freq || quanta_fd.before_sp < 3 || quanta_fd.before_sp > 33
		|| quanta_fd.after_sp < 1 || quanta_fd.after_sp > 16
		|| quanta_fd.sync_jump < 1 || quanta_fd.sync_jump > 8)
		return -EINVAL;
	/* Compute the Fast Baud Rate Prescaler */
	val = ROUND_INT_DIV(clk,
			freq_fd * (quanta_fd.before_sp + quanta_fd.after_sp));
	if (val < 1 || val > 32)
		return -EINVAL;
	/* Apply bit timing configuration */
#ifdef MCAN_DBTP_DBRP
	mcan->MCAN_DBTP = MCAN_DBTP_DBRP(val - 1)
		| MCAN_DBTP_DTSEG1(quanta_fd.before_sp - 1 - 1)
		| MCAN_DBTP_DTSEG2(quanta_fd.after_sp - 1)
		| MCAN_DBTP_DSJW(quanta_fd.sync_jump - 1);
#endif
#ifdef MCAN_FBTP_FBRP
	mcan->MCAN_FBTP = MCAN_FBTP_FBRP(val - 1)
		| MCAN_FBTP_FTSEG1(quanta_fd.before_sp - 1 - 1)
		| MCAN_FBTP_FTSEG2(quanta_fd.after_sp - 1)
		| MCAN_FBTP_FSJW(quanta_fd.sync_jump - 1);
#endif
	return 0;
}

static uint8_t* mcan_prepare_tx_buffer(struct _mcan_desc *desc, uint8_t buf_idx, uint32_t id, uint8_t len)
{
	struct mcan_set *set = &desc->set;
	assert(buf_idx < set->cfg.item_count[MCAN_RAM_TX_BUFFER]);
	assert(len <= set->cfg.buf_size_tx);

	Mcan *mcan = desc->addr;
	uint32_t *tx_buf = 0;
	uint32_t val;
	const enum can_mode mode = mcan_get_mode(mcan);
	enum mcan_dlc dlc;

	if (buf_idx >= set->cfg.item_count[MCAN_RAM_TX_BUFFER])
		return NULL;
	if (!mcan_get_length_code(len, &dlc))
		dlc = CAN_DLC_0;
	tx_buf = set->ram_array_tx + buf_idx
		* (MCAN_RAM_BUF_HDR_SIZE + set->cfg.buf_size_tx / 4);
	if (id & MCAN_RAM_T0_XTD)
		*tx_buf++ = MCAN_RAM_T0_XTD | MCAN_RAM_T0_XTDID(id);
	else
		*tx_buf++ = MCAN_RAM_T0_STDID(id);
	val = MCAN_RAM_T1_MM(0) | MCAN_RAM_T1_DLC((uint32_t)dlc);
	if (mode == CAN_MODE_CAN_FD_CONST_RATE)
		val |= MCAN_RAM_T1_FDF;
	else if (mode == CAN_MODE_CAN_FD_DUAL_RATE)
		val |= MCAN_RAM_T1_FDF | MCAN_RAM_T1_BRS;
	*tx_buf++ = val;
	/* enable transmit from buffer to set TC interrupt bit in IR,
	 * but interrupt will not happen unless TC interrupt is enabled */
	mcan->MCAN_TXBTIE = (1 << buf_idx);
	return (uint8_t *)tx_buf;   /* now it points to the data field */
}

static void mcan_enqueue_outgoing_msg(struct _mcan_desc *desc,
			uint8_t putIdx, uint32_t id, uint8_t len, const uint8_t *data)
{
	struct mcan_set *set = &desc->set;
	assert(len <= set->cfg.buf_size_tx);

	Mcan *mcan = desc->addr;
	uint32_t val;
	uint32_t *tx_buf = 0;
	const enum can_mode mode = mcan_get_mode(mcan);
	enum mcan_dlc dlc;

	if (!mcan_get_length_code(len, &dlc))
		dlc = CAN_DLC_0;
	tx_buf = set->ram_array_tx + (uint32_t)
		putIdx * (MCAN_RAM_BUF_HDR_SIZE + set->cfg.buf_size_tx / 4);
	if (id & MCAN_RAM_T0_XTD)
		*tx_buf++ = MCAN_RAM_T0_XTD | MCAN_RAM_T0_XTDID(id);
	else
		*tx_buf++ = MCAN_RAM_T0_STDID(id);
	val = MCAN_RAM_T1_MM(0) | MCAN_RAM_T1_DLC((uint32_t)dlc);
	if (mode == CAN_MODE_CAN_FD_CONST_RATE)
		val |= MCAN_RAM_T1_FDF;
	else if (mode == CAN_MODE_CAN_FD_DUAL_RATE)
		val |= MCAN_RAM_T1_FDF | MCAN_RAM_T1_BRS;
	*tx_buf++ = val;
	memcpy(tx_buf, data, len);
	dsb();
	/* enable transmit from buffer to set TC interrupt bit in IR,
	 * but interrupt will not happen unless TC interrupt is enabled
	 */
	mcan->MCAN_TXBTIE = (1 << putIdx);
	/* request to send */
	mcan->MCAN_TXBAR = (1 << putIdx);
}

static int mcand_tx(struct _mcan_desc *desc, struct _buffer *buf,
			struct _callback* cb)
{
	int status = 0;
	struct _cand_ram_item * ram_item;
	uint8_t buf_idx;
	uint32_t id = (buf->attr & CAND_BUF_ATTR_EXTENDED) ?
			MCAN_RAM_T0_XTD | MCAN_RAM_T0_XTDID(desc->identifier) :
			desc->identifier;
	if (buf->attr & CAND_BUF_ATTR_USING_FIFO) {
		status = mcand_get_ram(desc, MCAN_RAM_TX_FIFO, &buf_idx);
		if (status < 0)
			return status;
		ram_item = &desc->ram_item[desc->set.cfg.ram_index[MCAN_RAM_TX_FIFO] + buf_idx];
		ram_item->buf = buf;
		callback_copy(&ram_item->cb, cb);
		ram_item->state = 0;

		mcan_enqueue_outgoing_msg(desc, buf_idx + desc->set.cfg.item_count[MCAN_RAM_TX_BUFFER], id, buf->size, buf->data);
	} else {
		status = mcand_get_ram(desc, MCAN_RAM_TX_BUFFER, &buf_idx);
		if (status < 0)
			return status;
		uint8_t * tx_buf;
		tx_buf = mcan_prepare_tx_buffer(desc, buf_idx, id, buf->size);

		ram_item = &desc->ram_item[desc->set.cfg.ram_index[MCAN_RAM_TX_BUFFER] + buf_idx];
		ram_item->buf = buf;
		callback_copy(&ram_item->cb, cb);
		ram_item->state = 0;

		/* Send standard ID from a dedicated buffer */
		/* Write data into CAN mailbox */
		memcpy(tx_buf, buf->data, buf->size);
		dsb();
		/* Send data */
		if (buf_idx < desc->set.cfg.item_count[MCAN_RAM_TX_BUFFER])
			desc->addr->MCAN_TXBAR = (1 << buf_idx);

	}
	mcan_enable_it(desc->addr, MCAN_IE_TCE);

	return 0;
}

static int mcand_rx(struct _mcan_desc *desc, struct _buffer *buf,
			struct _callback* cb)
{
	struct _cand_ram_item * ram_item;
	struct mcan_set *set = &desc->set;
	uint8_t filt_idx;
	uint8_t buf_idx;
	uint32_t *filter;
	uint32_t it;
	enum _mcan_ram ram;
	int status = 0;

	if (buf->attr & CAND_BUF_ATTR_USING_FIFO) {
		if (buf->attr & CAND_BUF_ATTR_RX_OVERWRITE)
			return -EACCES;
		if (CAND_BUF_ATTR_USING_FIFO1 == (buf->attr & CAND_BUF_ATTR_USING_FIFO1)) {
			ram = MCAN_RAM_RX_FIFO1;
			it = MCAN_IE_RF1NE | MCAN_IE_RF1WE | MCAN_IE_RF1FE | MCAN_IE_RF1LE;
		} else {
			ram = MCAN_RAM_RX_FIFO0;
			it = MCAN_IE_RF0NE | MCAN_IE_RF0WE | MCAN_IE_RF0FE | MCAN_IE_RF0LE;
		}
	} else {
		ram = MCAN_RAM_RX_BUFFER;
		it = MCAN_IE_DRXE;
	}

	// get rx buffer
	status = mcand_get_ram(desc, ram, &buf_idx);
	if (status < 0)
		return status;
	assert(buf_idx < set->cfg.item_count[ram]);

	// get filter
	if (buf->attr & CAND_BUF_ATTR_EXTENDED) {
		assert(desc->identifier <= 0x1fffffff);
		if (desc->mask != 0x1fffffff) {
			trace_info("Not support current ID mask yet!");
			return -ENOTSUP;
		}
		status = mcand_get_ram(desc, MCAN_RAM_EXT_FILTER, &filt_idx);
		if (status < 0) {
			mcand_release_ram(desc, ram, buf_idx);
			return status;
		}
		assert(filt_idx < set->cfg.item_count[MCAN_RAM_EXT_FILTER]);
	} else {
		assert(desc->identifier <= 0x7ff);
		if (desc->mask != 0x7ff) {
			trace_info("Current ID mask not supported!");
			return -ENOTSUP;
		}
		status = mcand_get_ram(desc, MCAN_RAM_STD_FILTER, &filt_idx);
		if (status < 0) {
			mcand_release_ram(desc, ram, buf_idx);
			return status;
		}
		assert(filt_idx < set->cfg.item_count[MCAN_RAM_STD_FILTER]);
	}

	// filter configuration
	if (buf->attr & CAND_BUF_ATTR_USING_FIFO) {
		if (buf->attr & CAND_BUF_ATTR_EXTENDED) {
			filter = set->ram_filt_ext + filt_idx * MCAN_RAM_FILT_EXT_SIZE;
			*filter++ =
				((ram == MCAN_RAM_RX_FIFO1) ?
					MCAN_RAM_F0_EFEC_FIFO1 : MCAN_RAM_F0_EFEC_FIFO0)
				| MCAN_RAM_F0_EFID1(desc->identifier);
			*filter = MCAN_RAM_F1_EFID2(desc->identifier);
		} else {
			filter = set->ram_filt_std + filt_idx * MCAN_RAM_FILT_STD_SIZE;
			*filter =
				((ram == MCAN_RAM_RX_FIFO1) ?
					MCAN_RAM_S0_SFEC_FIFO1 : MCAN_RAM_S0_SFEC_FIFO0)
				| MCAN_RAM_S0_SFID1(desc->identifier)
				| MCAN_RAM_S0_SFID2(desc->identifier);
		}
		ram_item = &desc->ram_item[set->cfg.ram_index[ram] + buf_idx];
	} else {
		if (buf->attr & CAND_BUF_ATTR_EXTENDED) {
			filter = set->ram_filt_ext + filt_idx * MCAN_RAM_FILT_EXT_SIZE;
			*filter++ = MCAN_RAM_F0_EFEC_BUF
				| MCAN_RAM_F0_EFID1(desc->identifier);
			*filter = MCAN_RAM_F1_EFID2_BUF
				| MCAN_RAM_F1_EFID2_BUF_IDX(buf_idx);
		} else {
			filter = set->ram_filt_std + filt_idx * MCAN_RAM_FILT_STD_SIZE;
			*filter = MCAN_RAM_S0_SFEC_BUF
				| MCAN_RAM_S0_SFID1(desc->identifier)
				| MCAN_RAM_S0_SFID2_BUF
				| MCAN_RAM_S0_SFID2_BUF_IDX(buf_idx);
		}
		ram_item = &desc->ram_item[set->cfg.ram_index[MCAN_RAM_RX_BUFFER] + buf_idx];
	}
	dsb();

	// rx buffer configuration
	ram_item->buf = buf;
	callback_copy(&ram_item->cb, cb);
	ram_item->state = 0;

	mcan_enable_it(desc->addr, it);
	return 0;
}

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

struct _mcan_desc* mcand_get_desc(Mcan * mcan_if)
{
	return &mcan_desc[mcan_get_index(mcan_if)];
}

int mcand_configure(struct _mcan_desc* desc)
{
	int err;
	Mcan *mcan = desc->addr;
	uint32_t index;
	uint32_t id0 = get_mcan_id_from_addr(mcan, 0);
	uint32_t id1 = get_mcan_id_from_addr(mcan, 1);
	assert(id0 < ID_PERIPH_COUNT);
	assert(id1 < ID_PERIPH_COUNT);

#ifdef PMC_PCR_GCKCSS
	/* The MCAN peripheral is clocked by both its Peripheral Clock
	 * and Generated Clock (at least on SAMA5D2x). */
	/* Configure GCLK = <Master clock> divided by 1
	 * FIXME follow datasheet recommendation: configure GCLK = <UPLL clock>
	 * divided by 24, 12 or 6 */
	struct _pmc_periph_cfg cfg = {
		.gck = {
			.css = PMC_PCR_GCKCSS_MCK_CLK,
			.div = 1,
		},
	};
	pmc_configure_peripheral(id0, &cfg, true);
#else
	pmc_configure_pck(PMC_PCK_CAN, PMC_PCK_CSS_MCK, 0);
	pmc_enable_pck(PMC_PCK_CAN);
	pmc_configure_peripheral(id0, NULL, true);
#endif

	mcan_cfg.msg_ram[0] = mcan_msg_ram0[mcan_get_index(mcan)];
	mcan_cfg.ram_size[0] = ARRAY_SIZE(mcan_msg_ram0);
	memset(mcan_cfg.msg_ram[0], 0, mcan_cfg.ram_size[0]);

	mcan_cfg.msg_ram[1] = mcan_msg_ram1[mcan_get_index(mcan)];
	mcan_cfg.ram_size[1] = ARRAY_SIZE(mcan_msg_ram1);
	memset(mcan_cfg.msg_ram[1], 0, mcan_cfg.ram_size[1]);

	index = 0;
	mcan_cfg.ram_index[MCAN_RAM_STD_FILTER] = index;
	index += mcan_cfg.item_count[MCAN_RAM_STD_FILTER];
	mcan_cfg.ram_index[MCAN_RAM_EXT_FILTER] = index;
	index += mcan_cfg.item_count[MCAN_RAM_EXT_FILTER];
	mcan_cfg.ram_index[MCAN_RAM_RX_FIFO0]   = index;
	index += mcan_cfg.item_count[MCAN_RAM_RX_FIFO0];
	mcan_cfg.ram_index[MCAN_RAM_RX_FIFO1]   = index;
	index += mcan_cfg.item_count[MCAN_RAM_RX_FIFO1];
	mcan_cfg.ram_index[MCAN_RAM_RX_BUFFER]  = index;
	index += mcan_cfg.item_count[MCAN_RAM_RX_BUFFER];
	mcan_cfg.ram_index[MCAN_RAM_TX_EVENT]   = index;
	index += mcan_cfg.item_count[MCAN_RAM_TX_EVENT];
	mcan_cfg.ram_index[MCAN_RAM_TX_BUFFER]  = index;
	index += mcan_cfg.item_count[MCAN_RAM_TX_BUFFER];
	mcan_cfg.ram_index[MCAN_RAM_TX_FIFO]    = index;
	index += mcan_cfg.item_count[MCAN_RAM_TX_FIFO];
	assert(index <= ARRAY_SIZE(mcan_ram_item));
	desc->ram_item = mcan_ram_item;

	err = mcan_initialize(desc, &mcan_cfg);
	if (err < 0) {
		trace_error("Configure message RAM failed!");
		return err;
	}

	err = mcand_set_baudrate(mcan, desc->freq, desc->freq_fd);
	if (err < 0) {
		trace_error("Set baudrate for can bus failed!");
		return err;
	}

	mcan_line0_it(mcan, MCAN_ERRS);
	mcan_enable_line_it(mcan, MCAN_ILE_EINT0);

	irq_add_handler(id0, _mcan_handler, NULL);
	irq_enable(id0);

	irq_add_handler(id1, _mcan_handler, NULL);
	irq_enable(id1);

	return 0;
}

int mcand_transfer(struct _mcan_desc *desc, struct _buffer *buf,
			struct _callback* cb)
{
	if (buf->attr & CAND_BUF_ATTR_TX)
		return mcand_tx(desc, buf, cb);
	else if (buf->attr & CAND_BUF_ATTR_RX)
		return mcand_rx(desc, buf, cb);
	return -EINVAL;
}
