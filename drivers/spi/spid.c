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


#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/irq.h"
#include "peripherals/pmc.h"
#include "spi/spid.h"
#include "spi/spi.h"
#include "dma/dma.h"
#include "misc/cache.h"

#include "trace.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define SPID_POLLING_THRESHOLD      16

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint32_t _garbage = ~0u;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_SPI_FIFO

static void _spid_fifo_configure(struct _spi_desc *desc)
{
	desc->fifo.rx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.rx.threshold = desc->fifo.rx.size / 2;
	desc->fifo.tx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.tx.threshold = desc->fifo.tx.size / 2;
	spi_fifo_configure(desc->addr, desc->fifo.tx.threshold, desc->fifo.rx.threshold);
}

static void _spid_wait_tx_fifo_not_full(struct _spi_desc* desc)
{
	if (desc->use_fifo)
		while (desc->addr->SPI_SR & SPI_SR_TXFFF);
}

#endif /* CONFIG_HAVE_SPI_FIFO */

/* forward declaration */
static void _spid_transfer_next_buffer(struct _spi_desc* desc);

static void _spid_dma_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*)arg;

	if (channel == desc->xfer.dma.rx.channel ||
		channel == desc->xfer.dma.tx.channel)
		/* free channel */
		dma_free_channel(channel);
	else
		trace_fatal("Invalid DMA channel!\r\n");

	/* For read, invalidate region */
	if (channel == desc->xfer.dma.rx.channel)
		cache_invalidate_region(desc->xfer.dma.rx.cfg.da, desc->xfer.dma.rx.cfg.len);

	/* process next buffer */
	_spid_transfer_next_buffer(desc);
}

static void _spid_dma_free_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*)arg;

	if (channel == desc->xfer.dma.rx.channel ||
		channel == desc->xfer.dma.tx.channel)
		/* free channel */
		dma_free_channel(channel);
}

static void _spid_dma_write(struct _spi_desc* desc, uint8_t *buf, uint32_t len)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

	cache_clean_region(buf, len);

	memset(&desc->xfer.dma.tx.cfg, 0, sizeof(desc->xfer.dma.tx.cfg));

	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->xfer.dma.tx.channel);

	desc->xfer.dma.tx.cfg.da = (void*)&desc->addr->SPI_TDR;
	desc->xfer.dma.tx.cfg.sa = buf;
	desc->xfer.dma.tx.cfg.upd_sa_per_data = 1;
	desc->xfer.dma.tx.cfg.upd_da_per_data = 0;
	desc->xfer.dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->xfer.dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->xfer.dma.tx.cfg.blk_size = 0;
	desc->xfer.dma.tx.cfg.len = len;
	dma_configure_transfer(desc->xfer.dma.tx.channel, &desc->xfer.dma.tx.cfg);
	dma_set_callback(desc->xfer.dma.tx.channel, _spid_dma_callback, (void*)desc);

	memset(&desc->xfer.dma.rx.cfg, 0, sizeof(desc->xfer.dma.rx.cfg));

	desc->xfer.dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.rx.channel);

	desc->xfer.dma.rx.cfg.sa = (void*)&desc->addr->SPI_RDR;
	desc->xfer.dma.rx.cfg.da = &_garbage;
	desc->xfer.dma.rx.cfg.upd_sa_per_data = 0;
	desc->xfer.dma.rx.cfg.upd_da_per_data = 0;
	desc->xfer.dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->xfer.dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->xfer.dma.rx.cfg.blk_size = 0;
	desc->xfer.dma.rx.cfg.len = len;
	dma_configure_transfer(desc->xfer.dma.rx.channel, &desc->xfer.dma.rx.cfg);
	dma_set_callback(desc->xfer.dma.rx.channel, _spid_dma_free_callback, (void*)desc);

	dma_start_transfer(desc->xfer.dma.rx.channel);
	dma_start_transfer(desc->xfer.dma.tx.channel);
}

static void _spid_dma_read(struct _spi_desc* desc, uint8_t *buf, uint32_t len)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

	memset(&desc->xfer.dma.tx.cfg, 0, sizeof(desc->xfer.dma.tx.cfg));

	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->xfer.dma.tx.channel);

	desc->xfer.dma.tx.cfg.da = (void*)&desc->addr->SPI_TDR;
	desc->xfer.dma.tx.cfg.sa = &_garbage;
	desc->xfer.dma.tx.cfg.upd_sa_per_data = 0;
	desc->xfer.dma.tx.cfg.upd_da_per_data = 0;
	desc->xfer.dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->xfer.dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->xfer.dma.tx.cfg.blk_size = 0;
	desc->xfer.dma.tx.cfg.len = len;
	dma_configure_transfer(desc->xfer.dma.tx.channel, &desc->xfer.dma.tx.cfg);
	dma_set_callback(desc->xfer.dma.tx.channel, _spid_dma_free_callback, (void*)desc);

	memset(&desc->xfer.dma.rx.cfg, 0, sizeof(desc->xfer.dma.rx.cfg));

	desc->xfer.dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.rx.channel);

	desc->xfer.dma.rx.cfg.sa = (void*)&desc->addr->SPI_RDR;
	desc->xfer.dma.rx.cfg.da = buf;
	desc->xfer.dma.rx.cfg.upd_sa_per_data = 0;
	desc->xfer.dma.rx.cfg.upd_da_per_data = 1;
	desc->xfer.dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->xfer.dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->xfer.dma.rx.cfg.blk_size = 0;
	desc->xfer.dma.rx.cfg.len = len;
	dma_configure_transfer(desc->xfer.dma.rx.channel, &desc->xfer.dma.rx.cfg);
	dma_set_callback(desc->xfer.dma.rx.channel, _spid_dma_callback, (void*)desc);

	dma_start_transfer(desc->xfer.dma.rx.channel);
	dma_start_transfer(desc->xfer.dma.tx.channel);
}

static void _spid_handler(uint32_t source, void* user_arg)
{
	uint32_t status = 0;
	Spi* addr = get_spi_addr_from_id(source);
	struct _spi_desc *desc = (struct _spi_desc*)user_arg;

	if (!desc->xfer.current) {
		/* async descriptor not found, disable interrupt */
		spi_disable_it(addr, SPI_IDR_RDRF | SPI_IDR_TDRE | SPI_IDR_TXEMPTY);
		return;
	}

	status = spi_get_masked_status(addr);

	if (SPI_STATUS_RDRF(status)) {
#ifdef CONFIG_HAVE_SPI_FIFO
		_spid_wait_tx_fifo_not_full(desc);
#endif /* CONFIG_HAVE_SPI_FIFO */

		desc->xfer.current->data[desc->xfer.transferred] = spi_read(addr);
		desc->xfer.transferred++;

		if (desc->xfer.transferred >= desc->xfer.current->size) {
			/* current buffer transfer complete */
			spi_disable_it(addr, SPI_IDR_RDRF);
			spi_enable_it(addr, SPI_IER_TXEMPTY);
		} else {
			/* still some bytes to read */
			/* Dummy write to trigger the read */
			spi_write(addr, 0xffff);
		}

	} else if (SPI_STATUS_TDRE(status)) {
#ifdef CONFIG_HAVE_SPI_FIFO
		_spid_wait_tx_fifo_not_full(desc);
#endif /* CONFIG_HAVE_SPI_FIFO */

		spi_transfer(addr, desc->xfer.current->data[desc->xfer.transferred]);
		desc->xfer.transferred++;

		if (desc->xfer.transferred >= desc->xfer.current->size) {
			/* current buffer transfer complete */
			spi_disable_it(addr, SPI_IDR_TDRE);
			spi_enable_it(addr, SPI_IER_TXEMPTY);
		}

	} else if (SPI_STATUS_TXEMPTY(status)) {
		spi_disable_it(addr, SPI_IDR_TXEMPTY);
		_spid_transfer_next_buffer(desc);
	}
}

static uint32_t _spid_poll_write(struct _spi_desc* desc, struct _buffer* buffer)
{
	int i;

	for (i = 0; i < buffer->size; ++i) {
#ifdef CONFIG_HAVE_SPI_FIFO
		_spid_wait_tx_fifo_not_full(desc);
#endif /* CONFIG_HAVE_SPI_FIFO */
		spi_transfer(desc->addr, buffer->data[i]);
	}

	return SPID_SUCCESS;
}

static uint32_t _spid_poll_read(struct _spi_desc* desc, struct _buffer* buffer)
{
	int i;

	for (i = 0; i < buffer->size; ++i) {
#ifdef CONFIG_HAVE_SPI_FIFO
		_spid_wait_tx_fifo_not_full(desc);
#endif /* CONFIG_HAVE_SPI_FIFO */
		buffer->data[i] = spi_transfer(desc->addr, 0xff);
	}

	return SPID_SUCCESS;
}

static void _spid_transfer_current_buffer_async(struct _spi_desc* desc)
{
	desc->xfer.transferred = 0;

	if (desc->xfer.current->attr & SPID_BUF_ATTR_WRITE) {
		spi_enable_it(desc->addr, SPI_IER_TDRE);
	} else {
		spi_enable_it(desc->addr, SPI_IER_RDRF);
		spi_get_status(desc->addr);
		spi_write(desc->addr, 0xffff);
	}
}

static void _spid_transfer_current_buffer_dma(struct _spi_desc* desc)
{
	if (desc->xfer.current->attr & SPID_BUF_ATTR_WRITE) {
		_spid_dma_write(desc, desc->xfer.current->data, desc->xfer.current->size);
	} else {
		_spid_dma_read(desc, desc->xfer.current->data, desc->xfer.current->size);
	}
}

static void _spid_transfer_current_buffer_polling(struct _spi_desc* desc)
{
	if (desc->xfer.current->attr & SPID_BUF_ATTR_WRITE) {
		_spid_poll_write(desc, desc->xfer.current);
	} else {
		_spid_poll_read(desc, desc->xfer.current);
	}

	while (!spi_is_tx_finished(desc->addr));

	_spid_transfer_next_buffer(desc);
}

static void _spid_transfer_current_buffer(struct _spi_desc* desc)
{
	enum _spid_trans_mode tmode = desc->transfer_mode;

	if (desc->xfer.current->size < SPID_POLLING_THRESHOLD)
		tmode = SPID_MODE_POLLING;

	switch (tmode) {
	case SPID_MODE_POLLING:
		_spid_transfer_current_buffer_polling(desc);
		break;

	case SPID_MODE_ASYNC:
		_spid_transfer_current_buffer_async(desc);
		break;

	case SPID_MODE_DMA:
		_spid_transfer_current_buffer_dma(desc);
		break;

	default:
		trace_fatal("Unknown SPI transfer mode\r\n");
	}
}

static void _spid_transfer_next_buffer(struct _spi_desc* desc)
{
	if (desc->xfer.current < desc->xfer.last) {
		desc->xfer.current++;

		_spid_transfer_current_buffer(desc);
	} else {
		if (desc->xfer.current->attr & SPID_BUF_ATTR_RELEASE_CS)
			spi_release_cs(desc->addr, desc->chip_select);

		desc->xfer.current = NULL;
		if (desc->xfer.callback)
			desc->xfer.callback(desc->xfer.cb_args);
		mutex_unlock(&desc->mutex);
	}
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

uint32_t spid_transfer(struct _spi_desc* desc,
		struct _buffer* buffers, int buffer_count,
		spid_callback_t cb, void* user_args)
{
	int i;

	if (buffers == NULL)
		return SPID_ERROR_TRANSFER;

	for (i = 0 ; i < buffer_count ; i++) {
		if ((buffers[i].attr & (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ)) == 0)
			return SPID_ERROR_TRANSFER;

		if ((buffers[i].attr & (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ)) == (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ))
			return SPID_ERROR_TRANSFER;
	}

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SPID mutex already locked!\r\n");
		return SPID_ERROR_LOCK;
	}

	spi_select_cs(desc->addr, desc->chip_select);

	desc->xfer.current = buffers;
	desc->xfer.last = &buffers[buffer_count - 1];
	desc->xfer.callback = cb;
	desc->xfer.cb_args = user_args;

	_spid_transfer_current_buffer(desc);

	return SPID_SUCCESS;
}

bool spid_is_busy(struct _spi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void spid_wait_transfer(struct _spi_desc* desc)
{
	while (spid_is_busy(desc)) {
		if (desc->transfer_mode == SPID_MODE_DMA)
			dma_poll();
	}
}

void spid_configure(struct _spi_desc* desc)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(id);
	if (flexcom)
		flexcom_select(flexcom, FLEX_MR_OPMODE_SPI);
#endif
	pmc_enable_peripheral(id);
	spi_configure(desc->addr);
	spi_mode_master_enable(desc->addr, true);
#ifdef CONFIG_HAVE_SPI_FIFO
	_spid_fifo_configure(desc);
	if (desc->use_fifo)
		spi_fifo_enable(desc->addr);
#endif

	spi_disable_it(desc->addr, ~0u);
	irq_add_handler(id, _spid_handler, desc);
	irq_enable(id);

	spi_enable(desc->addr);
}

void spid_configure_cs(struct _spi_desc* desc, uint8_t cs,
		uint32_t bitrate, uint32_t delay_dlybs, uint32_t delay_dlybct,
		enum _spid_mode mode)
{
	uint32_t csr = SPI_CSR_BITS_8_BIT | SPI_CSR_CSAAT;

	switch (mode) {
	case SPID_MODE_0:
		csr |= SPI_CSR_NCPHA;
		break;
	case SPID_MODE_1:
		csr |= 0;
		break;
	case SPID_MODE_2:
		csr |= SPI_CSR_CPOL | SPI_CSR_NCPHA;
		break;
	case SPID_MODE_3:
		csr |= SPI_CSR_CPOL;
		break;
	}

	spi_configure_cs(desc->addr, cs, bitrate, delay_dlybs, delay_dlybct, csr);
}

void spid_set_cs_bitrate(struct _spi_desc* desc, uint8_t cs, uint32_t bitrate)
{
	spi_set_cs_bitrate(desc->addr, cs, bitrate);
}

void spid_configure_master(struct _spi_desc* desc, bool master)
{
	spi_disable(desc->addr);
	spi_mode_master_enable(desc->addr, master);
	spi_enable(desc->addr);
}
