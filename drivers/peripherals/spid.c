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

#define SPID_ATTRIBUTE_MASK         SPI_MR_MSTR
#define SPID_POLLING_THRESHOLD      16

static uint32_t _garbage = ~0u;

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

		if (cb)
			cb(user_args);

		mutex_unlock(&desc->mutex);
		break;

	case SPID_MODE_DMA:
		desc->callback = cb;
		desc->cb_args = user_args;
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
