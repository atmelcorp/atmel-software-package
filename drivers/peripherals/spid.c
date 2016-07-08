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

#define SPID_ATTRIBUTE_MASK     (SPI_MR_PS | SPI_MR_MODFDIS | SPI_MR_MSTR | SPI_MR_WDRBT)
#define SPID_DMA_THRESHOLD      16

static uint32_t _garbage = 0;

#ifdef CONFIG_HAVE_SPI_FIFO
static void spid_fifo_error(void)
{
	trace_error("Fifo pointer error encountered !!\r\n");
}
#endif

void spid_configure(struct _spi_desc* desc)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(id);
	if (flexcom)
		flexcom_select(flexcom, FLEX_MR_OPMODE_SPI);
#endif
	/* Enable SPI early otherwise FIFO configuration won't be applied */
	pmc_enable_peripheral(id);
	if (desc->transfert_mode == SPID_MODE_FIFO) {
		desc->attributes &= ~SPI_MR_WDRBT;
	}
	spi_configure(desc->addr, (desc->attributes & SPID_ATTRIBUTE_MASK));
	spi_chip_select(desc->addr, desc->chip_select);
	spi_configure_cs(desc->addr, desc->chip_select, desc->bitrate,
			 desc->dlybs, desc->dlybct, desc->spi_mode, 0);
#ifdef CONFIG_HAVE_SPI_FIFO
	if (desc->transfert_mode == SPID_MODE_FIFO) {
		spi_fifo_configure(desc->addr, SPI_FIFO_DEPTH, SPI_FIFO_DEPTH,
				   SPI_FMR_TXRDYM_ONE_DATA | SPI_FMR_RXRDYM_ONE_DATA);
		spi_enable_it(desc->addr, SPI_IER_TXFPTEF | SPI_IER_RXFPTEF);
		aic_set_source_vector(id, spid_fifo_error);
		aic_enable(id);
	}
#endif
	(void)spi_get_status(desc->addr);

	spi_enable(desc->addr);
}

void spid_begin_transfert(struct _spi_desc* desc)
{
	spi_chip_select(desc->addr, desc->chip_select);
	spi_configure_cs_mode(desc->addr, desc->chip_select, SPI_KEEP_CS_OW);
}

static void _spid_dma_finish(struct dma_channel *channel, struct _spi_desc* desc)
{
	dma_free_channel(channel);

	if (desc->dma_callback)
		desc->dma_callback(desc, desc->dma_callback_args);

	if (desc->dma_unlocks_mutex)
		mutex_unlock(&desc->mutex);
}

static void _spid_dma_write_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*)arg;
	_spid_dma_finish(channel, desc);
}

static void _spid_dma_write(struct _spi_desc* desc, bool wait_completion)
{
	struct dma_channel* w_channel = NULL;
	struct dma_channel* r_channel = NULL;
	struct dma_xfer_cfg w_cfg;
	struct dma_xfer_cfg r_cfg;
	uint32_t id = get_spi_id_from_addr(desc->addr);

	cache_clean_region(desc->dma_region_start, desc->dma_region_length);

	memset(&w_cfg, 0x0, sizeof(w_cfg));

	w_channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(w_channel);

	w_cfg.da = (void*)&desc->addr->SPI_TDR;
	w_cfg.sa = desc->dma_region_start;
	w_cfg.upd_sa_per_data = 1;
	w_cfg.upd_da_per_data = 0;
	w_cfg.data_width = DMA_DATA_WIDTH_BYTE;
	w_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	w_cfg.blk_size = 0;
	w_cfg.len = desc->dma_region_length;
	dma_configure_transfer(w_channel, &w_cfg);
	dma_set_callback(w_channel, _spid_dma_write_callback, (void*)desc);

	memset(&r_cfg, 0x0, sizeof(r_cfg));

	r_channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(r_channel);

	r_cfg.sa = (void*)&desc->addr->SPI_RDR;
	r_cfg.da = &_garbage;
	r_cfg.upd_sa_per_data = 0;
	r_cfg.upd_da_per_data = 0;
	r_cfg.data_width = DMA_DATA_WIDTH_BYTE;
	r_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	r_cfg.blk_size = 0;
	r_cfg.len = desc->dma_region_length;
	dma_configure_transfer(r_channel, &r_cfg);
	dma_set_callback(r_channel, NULL, NULL);

	dma_start_transfer(w_channel);
	dma_start_transfer(r_channel);

	if (wait_completion) {
		while (!dma_is_transfer_done(w_channel));
	}
}

static void _spid_dma_read_callback(struct dma_channel *channel, void *arg)
{
	struct _spi_desc* desc = (struct _spi_desc*) arg;
	cache_invalidate_region(desc->dma_region_start, desc->dma_region_length);
	_spid_dma_finish(channel, desc);
}

static void _spid_dma_read(const struct _spi_desc* desc)
{
	struct dma_channel* w_channel = NULL;
	struct dma_channel* r_channel = NULL;
	struct dma_xfer_cfg w_cfg;
	struct dma_xfer_cfg r_cfg;
	uint32_t id = get_spi_id_from_addr(desc->addr);

	memset(&w_cfg, 0x0, sizeof(w_cfg));

	w_channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(w_channel);

	w_cfg.da = (void*)&desc->addr->SPI_TDR;
	w_cfg.sa = &_garbage;
	w_cfg.upd_sa_per_data = 0;
	w_cfg.upd_da_per_data = 0;
	w_cfg.data_width = DMA_DATA_WIDTH_BYTE;
	w_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	w_cfg.blk_size = 0;
	w_cfg.len = desc->dma_region_length;
	dma_configure_transfer(w_channel, &w_cfg);
	dma_set_callback(r_channel, NULL, NULL);

	memset(&r_cfg, 0x0, sizeof(r_cfg));

	r_channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(r_channel);

	r_cfg.sa = (void*)&desc->addr->SPI_RDR;
	r_cfg.da = desc->dma_region_start;
	r_cfg.upd_sa_per_data = 0;
	r_cfg.upd_da_per_data = 1;
	r_cfg.data_width = DMA_DATA_WIDTH_BYTE;
	r_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	r_cfg.blk_size = 0;
	r_cfg.len = desc->dma_region_length;
	dma_configure_transfer(r_channel, &r_cfg);
	dma_set_callback(r_channel, _spid_dma_read_callback, (void*)desc);

	dma_start_transfer(w_channel);
	dma_start_transfer(r_channel);
}

uint32_t spid_transfert(struct _spi_desc* desc, struct _buffer* rx,
			struct _buffer* tx, spid_callback_t cb,
			void* user_args)
{
	Spi* spi = desc->addr;
	uint32_t i = 0;

	switch (desc->transfert_mode) {
	case SPID_MODE_POLLING:
		if (!mutex_try_lock(&desc->mutex)) {
			trace_error("SPID mutex already locked!\r\n");
			return SPID_ERROR_LOCK;
		}

		if (tx) {
			for (i = 0; i < tx->size; ++i)
				spi_write(spi, desc->chip_select, tx->data[i]);
		}

		if (rx) {
			for (i = 0; i < rx->size; ++i)
				rx->data[i] = spi_read(spi, desc->chip_select);
		}

		if (cb)
			cb(desc, user_args);

		mutex_unlock(&desc->mutex);

		break;

	case SPID_MODE_DMA:
		if (!mutex_try_lock(&desc->mutex)) {
			trace_error("SPID mutex already locked!\r\n");
			return SPID_ERROR_LOCK;
		}

		if (tx) {
			if (tx->size < SPID_DMA_THRESHOLD) {
				for (i = 0; i < tx->size; ++i)
					spi_write(spi, desc->chip_select, tx->data[i]);
				if (!rx) {
					if (cb)
						cb(desc, user_args);
					mutex_unlock(&desc->mutex);
				}
			} else {
				desc->dma_region_start = tx->data;
				desc->dma_region_length = tx->size;
				if (rx) {
					desc->dma_unlocks_mutex = false;
					desc->dma_callback = NULL;
					desc->dma_callback_args = NULL;
					_spid_dma_write(desc, true);
				} else {
					desc->dma_unlocks_mutex = true;
					desc->dma_callback = cb;
					desc->dma_callback_args = user_args;
					_spid_dma_write(desc, false);
				}
			}
		}

		if (rx) {
			if (rx->size < SPID_DMA_THRESHOLD) {
				for (i = 0; i < rx->size; ++i)
					rx->data[i] = spi_read(spi, desc->chip_select);
				if (cb)
					cb(desc, user_args);
				mutex_unlock(&desc->mutex);
			} else {
				desc->dma_region_start = rx->data;
				desc->dma_region_length = rx->size;
				desc->dma_unlocks_mutex = true;
				desc->dma_callback = cb;
				desc->dma_callback_args = user_args;
				_spid_dma_read(desc);
			}
		}

		break;

#ifdef CONFIG_HAVE_SPI_FIFO
	case SPID_MODE_FIFO:
		if (!mutex_try_lock(&desc->mutex)) {
			trace_error("SPID mutex already locked!\r\n");
			return SPID_ERROR_LOCK;
		}

		if (tx)
			spi_write_stream(spi, desc->chip_select, tx->data, tx->size);

		if (rx)
			spi_read_stream(spi, desc->chip_select, rx->data, rx->size);

		if (cb)
			cb(desc, user_args);

		mutex_unlock(&desc->mutex);

		break;
#endif
	default:
		trace_debug("Unknown mode");
	}

	return SPID_SUCCESS;
}

void spid_finish_transfert_callback(struct _spi_desc* desc, void* user_args)
{
	(void)user_args;
	spid_finish_transfert(desc);
}

void spid_finish_transfert(struct _spi_desc* desc)
{
	spi_release_cs(desc->addr);
}

void spid_close(const struct _spi_desc* desc)
{
	uint32_t id = get_spi_id_from_addr(desc->addr);
#ifdef CONFIG_HAVE_SPI_FIFO
	spi_fifo_disable(desc->addr);
	spi_disable_it(desc->addr, SPI_IER_TXFPTEF | SPI_IER_RXFPTEF);
	aic_disable(id);
#endif
	spi_disable(desc->addr);
	pmc_disable_peripheral(id);
}

uint32_t spid_is_busy(const struct _spi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void spid_wait_transfert(const struct _spi_desc* desc)
{
	while (spid_is_busy(desc)) {}
}
