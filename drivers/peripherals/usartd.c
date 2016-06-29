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

#include "chip.h"

#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/pmc.h"
#include "peripherals/usartd.h"
#include "peripherals/usart.h"
#include "peripherals/dma.h"
#include "misc/cache.h"

#include "trace.h"
#include "mutex.h"

#include <assert.h>
#include <string.h>
#include <stdint.h>

#define USARTD_ATTRIBUTE_MASK     (0)
#define USARTD_DMA_THRESHOLD      16

static void _usartd_dma_callback_wrapper(struct dma_channel* channel, void* args)
{
	trace_debug("USARTD DMA Transfert Finished\r\n");
	struct _usart_desc* usartd = (struct _usart_desc*) args;

	dma_free_channel(channel);

	if (usartd->region_start && usartd->region_length)
		cache_invalidate_region(usartd->region_start, usartd->region_length);

	if (usartd && usartd->callback)
		usartd->callback(usartd, usartd->cb_args);
}

static void _usartd_dma_read(const struct _usart_desc* desc, struct _buffer* buffer)
{
	struct dma_channel* channel = NULL;
	struct dma_xfer_cfg cfg;
	uint32_t id = get_usart_id_from_addr(desc->addr);

	memset(&cfg, 0x0, sizeof(cfg));

	channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(channel);

	cfg.sa = (void *)&desc->addr->US_RHR;
	cfg.da = buffer->data;
	cfg.upd_sa_per_data = 0;
	cfg.upd_da_per_data = 1;
	cfg.data_width = DMA_DATA_WIDTH_BYTE;
	cfg.chunk_size = DMA_CHUNK_SIZE_1;
	cfg.len = buffer->size;
	dma_configure_transfer(channel, &cfg);

	dma_set_callback(channel, _usartd_dma_callback_wrapper, (void*)desc);
	dma_start_transfer(channel);
}

static void _usartd_dma_write(const struct _usart_desc* desc, struct _buffer* buffer)
{
	struct dma_channel *channel = NULL;
	struct dma_xfer_cfg cfg;
	uint32_t id = get_usart_id_from_addr(desc->addr);

	memset(&cfg, 0x0, sizeof(cfg));

	channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(channel);

	cfg.sa = buffer->data;
	cfg.da = (void *)&desc->addr->US_THR;
	cfg.upd_sa_per_data = 1;
	cfg.upd_da_per_data = 0;
	cfg.data_width = DMA_DATA_WIDTH_BYTE;
	cfg.chunk_size = DMA_CHUNK_SIZE_1;
	cfg.len =  buffer->size;
	dma_configure_transfer(channel, &cfg);

	dma_set_callback(channel, _usartd_dma_callback_wrapper, (void*)desc);
	cache_clean_region(desc->region_start, desc->region_length);
	dma_start_transfer(channel);
}

void usartd_configure(struct _usart_desc* desc)
{
	uint32_t id = get_usart_id_from_addr(desc->addr);
	assert(id < ID_PERIPH_COUNT);

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(id);
	if (flexcom) {
		flexcom_select(flexcom, FLEX_MR_OPMODE_USART);
	}
#endif
	pmc_enable_peripheral(id);
	usart_configure(desc->addr, desc->mode, desc->baudrate);

#ifdef CONFIG_HAVE_USART_FIFO
	if (desc->transfert_mode == USARTD_MODE_FIFO) {
		uint32_t fifo_size = get_peripheral_fifo_depth(desc->addr);
		uint32_t tx_thres = fifo_size >> 1;
		uint32_t rx_thres1 = (fifo_size >> 1) + (fifo_size >> 2);
		uint32_t rx_thres2 = (fifo_size >> 1) - (fifo_size >> 2);
		usart_fifo_configure(desc->addr, tx_thres, rx_thres1, rx_thres2,
				     US_FMR_RXRDYM_ONE_DATA | US_FMR_TXRDYM_FOUR_DATA);
	}
#endif
}

uint32_t usartd_transfert(struct _usart_desc* desc, struct _buffer* rx,
			  struct _buffer* tx, usartd_callback_t cb,
			  void* user_args)
{
	uint32_t i = 0;

	desc->callback = cb;
	desc->cb_args = user_args;

	if (!mutex_try_lock(&desc->mutex)) {
		return USARTD_ERROR_LOCK;
	}

	switch (desc->transfert_mode) {
	case USARTD_MODE_POLLING:
		if (tx) {
			for (i = 0; i < tx->size; ++i) {
				usart_put_char(desc->addr, tx->data[i]);
			}
		}
		if (rx) {
			for (i = 0; i < rx->size; ++i) {
				rx->data[i] = usart_get_char(desc->addr);
			}
		}
		mutex_unlock(&desc->mutex);
		if (cb)
			cb(desc, user_args);
		break;
	case USARTD_MODE_DMA:
		if (!(rx || tx)) {
			return USARTD_ERROR_DUPLEX;
		}

		if (tx) {
			if (tx->size < USARTD_DMA_THRESHOLD) {
				for (i = 0; i < tx->size; ++i) {
					usart_put_char(desc->addr, tx->data[i]);
				}
				if (cb)
					cb(desc, user_args);
				mutex_unlock(&desc->mutex);
			} else {
				desc->region_start = tx->data;
				desc->region_length = tx->size;
				_usartd_dma_write(desc, tx);
			}
		} else if (rx) {
			if (rx->size < USARTD_DMA_THRESHOLD) {
				for (i = 0; i < rx->size; ++i) {
					rx->data[i] = usart_get_char(desc->addr);
				}
				if (cb)
					cb(desc, user_args);
				mutex_unlock(&desc->mutex);
			} else {
				desc->region_start = rx->data;
				desc->region_length = rx->size;
				_usartd_dma_read(desc, rx);
			}
		} else {
			mutex_unlock(&desc->mutex);
		}
		break;

#ifdef CONFIG_HAVE_USART_FIFO
	case USARTD_MODE_FIFO:
		if (tx) {
			usart_write_stream(desc->addr, tx->data, tx->size);
		}
		if (rx) {
			usart_read_stream(desc->addr, rx->data, rx->size);
		}
		mutex_unlock(&desc->mutex);
		if (cb)
			cb(desc, user_args);
		break;
#endif
	default:
		trace_debug("Unkown mode");
	}

	return USARTD_SUCCESS;
}

void usartd_finish_transfert_callback(struct _usart_desc* desc,
				      void* user_args)
{
	(void)user_args;
	usartd_finish_transfert(desc);
}

void usartd_finish_transfert(struct _usart_desc* desc)
{
	mutex_unlock(&desc->mutex);
}

uint32_t usartd_is_busy(const struct _usart_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void usartd_wait_transfert(const struct _usart_desc* desc)
{
	while (mutex_is_locked(&desc->mutex));
}
