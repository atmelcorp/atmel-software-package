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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "trace.h"
#include "ring.h"

#ifdef CONFIG_HAVE_EMAC
#include "peripherals/emacd.h"
#endif
#ifdef CONFIG_HAVE_GMAC
#include "peripherals/gmacd.h"
#endif

#include "misc/cache.h"

#include "ethd.h"

#include <string.h>

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void ethd_set_mac_addr(struct _ethd * ethd, uint8_t sa_idx, uint8_t* mac)
{
	ethd->op->set_mac_addr(ethd->addr, sa_idx, mac);
}

bool ethd_configure(struct _ethd * ethd, enum _eth_type eth_type, void * addr, uint8_t enable_caf, uint8_t enable_nbc)
{
	ethd->addr = addr;
	ethd->op = NULL;

#ifdef CONFIG_HAVE_EMAC
	if (ETH_TYPE_EMAC == eth_type)
		ethd->op = &_emac_op;
#endif
#ifdef CONFIG_HAVE_GMAC
	if (ETH_TYPE_GMAC == eth_type)
		ethd->op = &_gmac_op;
#endif

	if (NULL == ethd->op)
		return false;

	ethd->op->configure(ethd, addr, enable_caf, enable_nbc);
	return true;
}

uint8_t ethd_setup_queue(struct _ethd* ethd, uint8_t queue,
			 uint16_t rx_size, uint8_t* rx_buffer, struct _eth_desc* rx_desc,
			 uint16_t tx_size, uint8_t* tx_buffer, struct _eth_desc* tx_desc,
			 ethd_callback_t *tx_callbacks)
{
	return ethd->op->setup_queue(ethd, queue, rx_size, rx_buffer, rx_desc,
		tx_size, tx_buffer, tx_desc,
		tx_callbacks);
}

uint8_t ethd_send_sg(struct _ethd* ethd, uint8_t queue, const struct _eth_sg_list* sgl, ethd_callback_t callback)
{
	void* eth = ethd->addr;
	struct _ethd_queue* q = &ethd->queues[queue];
	struct _eth_desc* desc;
	uint16_t idx, tx_head;
	int i;

	if (callback && !q->tx_callbacks) {
		trace_error("Cannot set send callback, no tx_callbacks buffer configured for queue %u", queue);
	}

	/* Check parameter */
	if (!sgl->size) {
		trace_error("ethd_send_sg: ethernet frame is empty.\r\n");
		return ETH_PARAM;
	}
	if (sgl->size >= q->tx_size) {
		trace_error("ethd_send_sg: ethernet frame has too many buffers.\r\n");
		return ETH_PARAM;
	}

	/* Check available space */
	if (RING_SPACE(q->tx_head, q->tx_tail, q->tx_size) < sgl->size) {
		trace_error("ethd_send_sg: not enough free buffers in TX queue.\r\n");
		return ETH_TX_BUSY;
	}

	/* Tag end of TX queue */
	tx_head = fixed_mod(q->tx_head + sgl->size, q->tx_size);
	idx = tx_head;
	if (q->tx_callbacks)
		q->tx_callbacks[idx] = NULL;
	desc = &q->tx_desc[idx];
	desc->status |= ETH_TX_STATUS_USED;

	/* Update buffer descriptors in reverse order to avoid a race
	 * condition with hardware.
	 */
	for (i = sgl->size - 1; i >= 0; i--) {
		const struct _eth_sg *sg = &sgl->entries[i];
		uint32_t status;

		if (sg->size > ETH_TX_UNITSIZE) {
			trace_error("ethd_send_sg: buffer size is too big.\r\n");
			return ETH_PARAM;
		}

		RING_DEC(idx, q->tx_size);

		/* Reset TX callback */
		if (q->tx_callbacks)
			q->tx_callbacks[idx] = NULL;

		desc = &q->tx_desc[idx];

		/* Copy data into transmittion buffer */
		if (sg->buffer && sg->size) {
			memcpy((void*)desc->addr, sg->buffer, sg->size);
			cache_clean_region((void*)desc->addr, sg->size);
		}

		/* Compute buffer descriptor status word */
		status = sg->size & ETH_RX_STATUS_LENGTH_MASK;
		if (i == (sgl->size - 1)) {
			status |= ETH_TX_STATUS_LASTBUF;
			if (q->tx_callbacks)
				q->tx_callbacks[idx] = callback;
		}
		if (idx == (q->tx_size - 1)) {
			status |= ETH_TX_STATUS_WRAP;
		}

		/* Update buffer descriptor status word: clear USED bit */
		desc->status = status;
		dsb();
	}

	/* Update TX ring buffer pointers */
	q->tx_head = tx_head;

	/* Now start to transmit if it is not already done */
	ethd->op->start_transmission(eth);

	return ETH_OK;
}

void ethd_start(struct _ethd* ethd)
{
	ethd->op->start(ethd);
}

uint8_t ethd_send(struct _ethd* ethd, uint8_t queue, void *buffer, uint32_t size, ethd_callback_t callback)
{
	struct _eth_sg sg;
	struct _eth_sg_list sgl;

	/* Init single entry scatter-gather list */
	sg.size = size;
	sg.buffer = buffer;
	sgl.size = 1;
	sgl.entries = &sg;

	return ethd_send_sg(ethd, queue, &sgl, callback);
}

/**
 * Return current load of TX.
 * \param ethd   Pointer to ETH Driver instance.
 */
uint32_t ethd_get_tx_load(struct _ethd* ethd, uint8_t queue)
{
	struct _ethd_queue* q = &ethd->queues[queue];
	return RING_CNT(q->tx_head, q->tx_tail, q->tx_size);
}

uint8_t ethd_poll(struct _ethd* ethd, uint8_t queue, uint8_t* buffer, uint32_t buffer_size, uint32_t* recv_size)
{
	struct _ethd_queue* q = &ethd->queues[queue];
	struct _eth_desc *desc;
	uint32_t idx;
	uint32_t cur_frame_size = 0;
	uint8_t *cur_frame = 0;

	if (!buffer)
		return ETH_PARAM;

	/* Set the default return value */
	*recv_size = 0;

	/* Process RX descriptors */
	idx = q->rx_head;
	desc = &q->rx_desc[idx];
	while (desc->addr & ETH_RX_ADDR_OWN) {
		/* A start of frame has been received, discard previous fragments */
		if (desc->status & ETH_RX_STATUS_SOF) {
			/* Skip previous fragment */
			while (idx != q->rx_head) {
				desc = &q->rx_desc[q->rx_head];
				desc->addr &= ~ETH_RX_ADDR_OWN;
				RING_INC(q->rx_head, q->rx_size);
			}
			cur_frame = buffer;
			cur_frame_size = 0;
		}

		/* Increment the index */
		RING_INC(idx, q->rx_size);

		/* Copy data in the frame buffer */
		if (cur_frame) {
			if (idx == q->rx_head) {
				trace_info("no EOF (buffers probably too small)\r\n");

				do {
					desc = &q->rx_desc[q->rx_head];
					desc->addr &= ~ETH_RX_ADDR_OWN;
					RING_INC(q->rx_head, q->rx_size);
				} while (idx != q->rx_head);
				return ETH_RX_NULL;
			}

			/* Copy the buffer into the application frame */
			uint32_t length = ETH_RX_UNITSIZE;
			if ((cur_frame_size + length) > buffer_size) {
				length = buffer_size - cur_frame_size;
			}

			void* addr = (void*)(desc->addr & ETH_RX_ADDR_MASK);
			cache_invalidate_region(addr, length);
			memcpy(cur_frame, addr, length);
			cur_frame += length;
			cur_frame_size += length;

			/* An end of frame has been received, return the data */
			if (desc->status & ETH_RX_STATUS_EOF) {
				/* Frame size from the ETH */
				*recv_size = desc->status & ETH_RX_STATUS_LENGTH_MASK;

				/* Application frame buffer is too small all
				 * data have not been copied */
				if (cur_frame_size < *recv_size) {
					return ETH_SIZE_TOO_SMALL;
				}

				/* All data have been copied in the application
				 * frame buffer => release descriptors */
				while (q->rx_head != idx) {
					desc = &q->rx_desc[q->rx_head];
					desc->addr &= ~ETH_RX_ADDR_OWN;
					RING_INC(q->rx_head, q->rx_size);
				}

				return ETH_OK;
			}
		}

		/* SOF has not been detected, skip the fragment */
		else {
			desc->addr &= ~ETH_RX_ADDR_OWN;
			q->rx_head = idx;
		}

		/* Process the next buffer */
		desc = &q->rx_desc[idx];
	}
	return ETH_RX_NULL;
}

void ethd_set_rx_callback(struct _ethd *ethd, uint8_t queue, ethd_callback_t callback)
{
	ethd->op->set_rx_callback(ethd, queue, callback);
}

uint8_t ethd_set_tx_wakeup_callback(struct _ethd* ethd, uint8_t queue, ethd_wakeup_cb_t callback, uint16_t threshold)
{
	struct _ethd_queue* q = &ethd->queues[queue];
	if (!callback) {
		q->tx_wakeup_callback = NULL;
	} else {
		if (threshold <= q->tx_size) {
			q->tx_wakeup_callback = callback;
			q->tx_wakeup_threshold = threshold;
		} else {
			return ETH_PARAM;
		}
	}

	return ETH_OK;
}
