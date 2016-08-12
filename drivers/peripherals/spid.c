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


#include "peripherals/aic.h"
#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/pmc.h"
#include "peripherals/spid.h"
#include "peripherals/spi.h"
#include "peripherals/dma.h"
#include "misc/cache.h"

#include "trace.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define SPID_ATTRIBUTE_MASK         SPI_MR_MSTR
#define SPID_POLLING_THRESHOLD      16

#define MAX_ADESC               8

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _async_desc
{
	struct _spi_desc* spi_desc;
	uint32_t spi_id;
	struct {
		struct _buffer *buf;
		uint32_t transferred;
	} rx;
	struct {
		struct _buffer *buf;
		uint32_t transferred;
	} tx;

	spid_callback_t callback;
	void* callback_args;
};


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _async_desc async_desc[MAX_ADESC];
static uint8_t adesc_index = 0;

static uint32_t _garbage = ~0u;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _spid_dma_finish(struct dma_channel *channel, struct _spi_desc* desc)
{
	dma_free_channel(channel);

	if (desc->flags & SPID_BUF_ATTR_RELEASE_CS)
		spi_release_cs(desc->addr);

	if (desc->callback)
		desc->callback(desc->cb_args);

	mutex_unlock(&desc->mutex);
}

static void _spid_dma_write_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*)arg;

	_spid_dma_finish(channel, desc);
}

static void _spid_dma_free_channel_callback(struct dma_channel *channel, void *arg)
{
	dma_free_channel(channel);
}

static void _spid_dma_write(struct _spi_desc* desc, uint8_t *buf, uint16_t len)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

	cache_clean_region(buf, len);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);

	desc->dma.tx.cfg.da = (void*)&desc->addr->SPI_TDR;
	desc->dma.tx.cfg.sa = buf;
	desc->dma.tx.cfg.upd_sa_per_data = 1;
	desc->dma.tx.cfg.upd_da_per_data = 0;
	desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.tx.cfg.blk_size = 0;
	desc->dma.tx.cfg.len = len;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);
	dma_set_callback(desc->dma.tx.channel, _spid_dma_write_callback, (void*)desc);

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

	desc->dma.rx.cfg.sa = (void*)&desc->addr->SPI_RDR;
	desc->dma.rx.cfg.da = &_garbage;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 0;
	desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.rx.cfg.blk_size = 0;
	desc->dma.rx.cfg.len = len;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);
	dma_set_callback(desc->dma.rx.channel, _spid_dma_free_channel_callback, NULL);

	dma_start_transfer(desc->dma.rx.channel);
	dma_start_transfer(desc->dma.tx.channel);
}

static void _spid_dma_read_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*)arg;
	cache_invalidate_region(desc->dma.rx.cfg.da, desc->dma.rx.cfg.len);
	_spid_dma_finish(channel, desc);
}

static void _spid_dma_read(struct _spi_desc* desc, uint8_t *buf, uint16_t len)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);

	desc->dma.tx.cfg.da = (void*)&desc->addr->SPI_TDR;
	desc->dma.tx.cfg.sa = &_garbage;
	desc->dma.tx.cfg.upd_sa_per_data = 0;
	desc->dma.tx.cfg.upd_da_per_data = 0;
	desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.tx.cfg.blk_size = 0;
	desc->dma.tx.cfg.len = len;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);
	dma_set_callback(desc->dma.tx.channel, _spid_dma_free_channel_callback, NULL);

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

	desc->dma.rx.cfg.sa = (void*)&desc->addr->SPI_RDR;
	desc->dma.rx.cfg.da = buf;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 1;
	desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.rx.cfg.blk_size = 0;
	desc->dma.rx.cfg.len = len;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);
	dma_set_callback(desc->dma.rx.channel, _spid_dma_read_callback, (void*)desc);

	dma_start_transfer(desc->dma.rx.channel);
	dma_start_transfer(desc->dma.tx.channel);
}

static void _spid_handler(void)
{
	int i;
	uint32_t status = 0;
	Spi* addr;
	uint32_t id = aic_get_current_interrupt_identifier();

	for (i = 0; i != MAX_ADESC; i++) {
		if (async_desc[i].spi_id == id) {
			status = 1;
			break;
		}
	}

	if (!status) {
		/* async descriptor not found, disable interrupt */
		addr = get_spi_addr_from_id(id);
		spi_disable_it(addr, SPI_IDR_RDRF | SPI_IDR_TDRE | SPI_IDR_TXEMPTY);
		return;
	}

	struct _async_desc *adesc = &async_desc[i];
	addr = adesc->spi_desc->addr;

	status = spi_get_masked_status(addr);

	if (SPI_STATUS_RDRF(status)) {
		adesc->rx.buf->data[adesc->rx.transferred] = spi_read(addr);
		adesc->rx.transferred++;

		if (adesc->rx.transferred >= adesc->rx.buf->size) {
			spi_disable_it(addr, SPI_IDR_RDRF);
			spi_enable_it(addr, SPI_IER_TXEMPTY);
		} else {
			/* Dumy write */
			spi_write(addr, 0xffff);
		}

	} else if (SPI_STATUS_TDRE(status)) {
		spi_transfer(addr, adesc->tx.buf->data[adesc->tx.transferred]);
		adesc->tx.transferred++;

		if (adesc->tx.transferred >= adesc->tx.buf->size) {
			spi_disable_it(addr, SPI_IDR_TDRE);
			spi_enable_it(addr, SPI_IER_TXEMPTY);
		}

	} else if (SPI_STATUS_TXEMPTY(status)) {
		aic_disable(adesc->spi_id);
		spi_disable_it(addr, SPI_IDR_TXEMPTY);
		adesc->spi_id = 0;

		if (adesc->spi_desc->flags & SPID_BUF_ATTR_RELEASE_CS)
			spi_release_cs(addr);

		if (adesc->callback)
			adesc->spi_desc->callback(adesc->spi_desc->cb_args);

		mutex_unlock(&adesc->spi_desc->mutex);
	}
}

static uint32_t _spid_transfer(struct _spi_desc* desc, struct _buffer* buf, spid_callback_t cb, void* user_args)
{
	Spi* spi = desc->addr;
	uint32_t i = 0;
	enum _spid_trans_mode tmode = desc->transfer_mode;

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SPID mutex already locked!\r\n");
		return SPID_ERROR_LOCK;
	}

	if (buf->size < SPID_POLLING_THRESHOLD)
		tmode = SPID_MODE_POLLING;

	desc->flags = buf->attr;
	desc->callback = cb;
	desc->cb_args = user_args;

	switch (tmode) {
	case SPID_MODE_POLLING:
		if (desc->flags & SPID_BUF_ATTR_WRITE) {
			for (i = 0; i < buf->size; ++i)
				spi_transfer(spi, buf->data[i]);
		} else {
			for (i = 0; i < buf->size; ++i)
				buf->data[i] = spi_transfer(spi, 0xff);
		}

		while (!spi_is_tx_finished(spi));

		if (desc->flags & SPID_BUF_ATTR_RELEASE_CS)
			spi_release_cs(desc->addr);

		if (desc->callback)
			desc->callback(desc->cb_args);

		mutex_unlock(&desc->mutex);
		break;

	case SPID_MODE_ASYNC:
		memset(&async_desc[adesc_index], 0, sizeof(async_desc[adesc_index]));

		async_desc[adesc_index].spi_desc = desc;
		async_desc[adesc_index].spi_id = get_spi_id_from_addr(desc->addr);

		aic_set_source_vector(async_desc[adesc_index].spi_id, _spid_handler);

		spi_disable_it(desc->addr, 0xffffffff);
		aic_enable(async_desc[adesc_index].spi_id);

		/* Start spi with send first byte */
		if (desc->flags & SPID_BUF_ATTR_WRITE) {
			async_desc[adesc_index].tx.buf = buf;

			spi_enable_it(desc->addr, SPI_IER_TDRE);
		} else {
			async_desc[adesc_index].rx.buf = buf;

			/* Trigger the IT */
			spi_enable_it(desc->addr, SPI_IER_RDRF);
			spi_get_status(desc->addr);
			spi_write(desc->addr, 0xffff);
		}

		adesc_index = (adesc_index + 1) % MAX_ADESC;
		break;

	case SPID_MODE_DMA:
		if (buf->attr & SPID_BUF_ATTR_WRITE)
			_spid_dma_write(desc, buf->data, buf->size);
		else
			_spid_dma_read(desc, buf->data, buf->size);
		break;

	default:
		trace_debug("Unknown mode");
	}

	return SPID_SUCCESS;
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

uint32_t spid_transfer(struct _spi_desc* desc, struct _buffer* buf, int buffers,
					   spid_callback_t cb, void* user_args)
{
	int b;
	uint32_t status;

	if (buf == NULL)
		return SPID_ERROR_TRANSFER;

	if (mutex_is_locked(&desc->mutex))
		return SPID_ERROR_LOCK;

	spi_chip_select(desc->addr, desc->chip_select);

	for (b = 0 ; b < buffers ; b++) {
		if ((buf[b].attr & (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ)) == 0)
			return SPID_ERROR_TRANSFER;

		if ((buf[b].attr & (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ)) == (SPID_BUF_ATTR_WRITE | SPID_BUF_ATTR_READ))
			return SPID_ERROR_TRANSFER;

		if (buf[b].size > 0) {
			if (b == (buffers - 1))
				status = _spid_transfer(desc, &buf[b], cb, user_args);
			else
				status = _spid_transfer(desc, &buf[b], NULL, NULL);
			if (status)
				return status;
			spid_wait_transfer(desc);
		}
	}

	return SPID_SUCCESS;
}

uint32_t spid_is_busy(const struct _spi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void spid_wait_transfer(const struct _spi_desc* desc)
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
	spi_configure(desc->addr, (desc->attributes & SPI_MR_MSTR));
	spi_configure_cs(desc->addr, desc->chip_select, desc->bitrate,
			 desc->dlybs, desc->dlybct, desc->spi_mode);

	spi_enable(desc->addr);
}
