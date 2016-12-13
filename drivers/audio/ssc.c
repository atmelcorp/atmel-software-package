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

/** \addtogroup ssc_module Working with SSC
 * \section Purpose
 * The SSC driver provides the interface to configure and use the SSC
 * peripheral.
 *
 * \section Usage
 * -# Enable the SSC interface pins.
 * -# Configure the SSC to operate at a specific frequency by calling
 *    SSC_Configure(). This function enables the peripheral clock of the SSC,
 *    but not its PIOs.
 * -# Configure the transmitter and/or the receiver using the
 *    SSC_ConfigureTransmitter() and SSC_ConfigureEmitter() functions.
 * -# Enable the PIOs or the transmitter and/or the received.
 * -# Enable the transmitter and/or the receiver using SSC_EnableTransmitter()
 *    and SSC_EnableReceiver()
 * -# Send data through the transmitter using SSC_Write()
 * -# Receive data from the receiver using SSC_Read()
 * -# Disable the transmitter and/or the receiver using SSC_DisableTransmitter()
 *    and SSC_DisableReceiver()
 *
 * For more accurate information, please look at the SSC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref ssc.c\n
 * \ref ssc.h.\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Synchronous Serial (SSC) controller.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>

#include "audio/ssc.h"
#include "chip.h"
#include "errno.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *       Local functions
 *----------------------------------------------------------------------------*/

static void _ssc_dma_rx_callback(struct dma_channel* channel, void* args)
{
	struct _ssc_desc* desc = (struct _ssc_desc *)args;

	cache_invalidate_region(desc->dma.rx.cfg.da, desc->dma.rx.cfg.len);

	dma_reset_channel(channel);

	mutex_unlock(&desc->rx.mutex);

	callback_call(&desc->rx.callback);
}

static void _ssc_dma_rx_transfer(struct _ssc_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_ssc_id_from_addr(desc->addr);

	assert(id < ID_PERIPH_COUNT);

	memset(&desc->dma.rx.cfg, 0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.cfg.sa = (void*)&desc->addr->SSC_RHR;
	desc->dma.rx.cfg.da = buffer->data;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 1;
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;

	if (desc->slot_length == 8) {
		desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
		desc->dma.rx.cfg.len  = buffer->size;
	} else if (desc->slot_length == 16) {
		desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		desc->dma.rx.cfg.len  = buffer->size/2;
	} else if (desc->slot_length == 32) {
		desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_WORD;
		desc->dma.rx.cfg.len  = buffer->size/4;
	}
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);
	dma_set_callback(desc->dma.rx.channel, _ssc_dma_rx_callback, (void*)desc);
	dma_start_transfer(desc->dma.rx.channel);
}

static void _ssc_dma_tx_callback(struct dma_channel* channel, void* args)
{
	struct _ssc_desc* desc = (struct _ssc_desc *)args;

	dma_reset_channel(channel);

	mutex_unlock(&desc->tx.mutex);

	callback_call(&desc->tx.callback);
}

static void _ssc_dma_tx_transfer(struct _ssc_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_ssc_id_from_addr(desc->addr);

	assert(id < ID_PERIPH_COUNT);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	desc->dma.tx.cfg.sa = buffer->data;
	desc->dma.tx.cfg.da = (void*)&desc->addr->SSC_THR;
	desc->dma.tx.cfg.upd_sa_per_data = 1;
	desc->dma.tx.cfg.upd_da_per_data = 0;
	desc->dma.tx.cfg.blk_size = 0;
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;

	if (desc->slot_length == 8) {
		desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
		desc->dma.tx.cfg.len  = buffer->size;
	} else if (desc->slot_length == 16) {
		desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		desc->dma.tx.cfg.len  = buffer->size/2;
	} else if (desc->slot_length == 32) {
		desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_WORD;
		desc->dma.tx.cfg.len  = buffer->size/4;
	}

	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);
	dma_set_callback(desc->dma.tx.channel, _ssc_dma_tx_callback, (void*)desc);
	cache_clean_region(desc->dma.tx.cfg.sa, desc->dma.tx.cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
}

/*----------------------------------------------------------------------------
 *       Exported functions
 *----------------------------------------------------------------------------*/

void ssc_configure(struct _ssc_desc* desc)
{
	uint32_t id;
	uint32_t clock;
	uint32_t rcmr, rfmr, tcmr, tfmr;

	id = get_ssc_id_from_addr(desc->addr);
	clock = pmc_get_peripheral_clock(id);

	/* Reset, disable receiver & transmitter */
	desc->addr->SSC_CR = SSC_CR_RXDIS | SSC_CR_TXDIS | SSC_CR_SWRST;

	/* Configure clock frequency */
	if (desc->bit_rate != 0)
		desc->addr->SSC_CMR = clock / (2 * desc->bit_rate);
	else
		desc->addr->SSC_CMR = 0;

	if (desc->rx_cfg_cks_rk) {
		rcmr = SSC_RCMR_CKS_RK |
		       SSC_RCMR_CKO_NONE |
		       SSC_RCMR_CKI |
		       desc->rx_start_selection |
		       SSC_RCMR_STTDLY(1) |
		       SSC_RCMR_PERIOD(0);
	} else {
		rcmr = SSC_RCMR_CKS_TK |
		       SSC_RCMR_CKO_NONE |
		       SSC_RCMR_CKI |
		       desc->rx_start_selection |
		       SSC_RCMR_STTDLY(1) |
		       SSC_RCMR_PERIOD(0);
	}

	rfmr = SSC_RFMR_DATLEN(desc->slot_length - 1) |
	       SSC_RFMR_MSBF |
	       SSC_RFMR_DATNB(desc->slot_num - 1) |
	       SSC_RFMR_FSOS_NONE;

	ssc_configure_receiver(desc, rcmr, rfmr);

	if (desc->tx_cfg_cks_tk) {
		tcmr = SSC_TCMR_CKS_TK |
		       SSC_TCMR_CKO_NONE |
		       desc->tx_start_selection |
		       SSC_TCMR_STTDLY(1) |
		       SSC_TCMR_PERIOD(0);

	} else {
		tcmr = SSC_TCMR_CKS_RK |
		       SSC_TCMR_CKO_NONE |
		       desc->tx_start_selection |
		       SSC_TCMR_STTDLY(1) |
		       SSC_TCMR_PERIOD(0);
	}

	tfmr = SSC_TFMR_DATLEN(desc->slot_length - 1) |
	       SSC_TFMR_MSBF |
	       SSC_TFMR_DATNB(desc->slot_num - 1) |
	       SSC_TFMR_FSOS_NONE;

	ssc_configure_transmitter(desc, tcmr, tfmr);

	/* Enable SSC peripheral clock */
	pmc_configure_peripheral(id, NULL, true);

	desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);
	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);
}

void ssc_configure_transmitter(struct _ssc_desc* desc, uint32_t tcmr, uint32_t tfmr)
{
	desc->addr->SSC_TCMR = tcmr;
	desc->addr->SSC_TFMR = tfmr;
}

void ssc_configure_receiver(struct _ssc_desc* desc, uint32_t rcmr, uint32_t rfmr)
{
	desc->addr->SSC_RCMR = rcmr;
	desc->addr->SSC_RFMR = rfmr;
}

void ssc_enable_transmitter(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_TXEN;
}

void ssc_disable_transmitter(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_TXDIS;
}

void ssc_enable_receiver(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_RXEN;
}

void ssc_disable_receiver(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_RXDIS;
}

void ssc_enable_interrupts(struct _ssc_desc* desc, uint32_t sources)
{
	desc->addr->SSC_IER = sources;
}

void ssc_disable_interrupts(struct _ssc_desc* desc, uint32_t sources)
{
	desc->addr->SSC_IDR = sources;
}

void ssc_write(struct _ssc_desc* desc, uint32_t frame)
{
	while ((desc->addr->SSC_SR & SSC_SR_TXRDY) == 0) ;
	desc->addr->SSC_THR = frame;
}

uint32_t ssc_read(struct _ssc_desc* desc)
{
	while ((desc->addr->SSC_SR & SSC_SR_RXRDY) == 0) ;
	return desc->addr->SSC_RHR;
}

bool ssc_is_rx_ready(struct _ssc_desc* desc)
{
	return ((desc->addr->SSC_SR & SSC_SR_RXRDY) == SSC_SR_RXRDY);
}

int ssc_transfer(struct _ssc_desc* desc, struct _buffer* buf, struct _callback* cb)
{
	if ((buf == NULL) || (buf->size == 0))
		return -EINVAL;

	if (buf->attr & SSC_BUF_ATTR_READ) {
		mutex_lock(&desc->rx.mutex);

		callback_copy(&desc->rx.callback, cb);

		desc->rx.transferred = 0;
		desc->rx.buffer.data = buf->data;
		desc->rx.buffer.size = buf->size;
		desc->rx.buffer.attr = buf->attr;
		_ssc_dma_rx_transfer(desc, buf);
	} else if (buf->attr & SSC_BUF_ATTR_WRITE) {
		mutex_lock(&desc->tx.mutex);

		callback_copy(&desc->tx.callback, cb);

		desc->tx.transferred = 0;
		desc->tx.buffer.data = buf->data;
		desc->tx.buffer.size = buf->size;
		desc->tx.buffer.attr = buf->attr;
		_ssc_dma_tx_transfer(desc, buf);
	}

	return 0;
}

bool ssc_dma_tx_transfer_is_done(struct _ssc_desc* desc)
{
	return (!mutex_is_locked(&desc->tx.mutex));
}

bool ssc_dma_rx_transfer_is_done(struct _ssc_desc* desc)
{
	return (!mutex_is_locked(&desc->rx.mutex));
}

void ssc_dma_tx_stop(struct _ssc_desc* desc)
{
	if (desc->dma.tx.channel) {
		dma_stop_transfer(desc->dma.tx.channel);
		mutex_unlock(&desc->tx.mutex);
	}
}

void ssc_dma_rx_stop(struct _ssc_desc* desc)
{
	if (desc->dma.rx.channel) {
		dma_stop_transfer(desc->dma.rx.channel);
		mutex_unlock(&desc->rx.mutex);
	}
}
