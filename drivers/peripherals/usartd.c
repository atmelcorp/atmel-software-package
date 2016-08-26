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
#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/usartd.h"
#include "peripherals/usart.h"
#include "peripherals/dma.h"
#include "misc/cache.h"

#include "trace.h"
#include "io.h"
#include "mutex.h"

#include <assert.h>
#include <string.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/

#define USARTD_ATTRIBUTE_MASK     (0)
#define USARTD_POLLING_THRESHOLD  16

#define MAX_ADESC                 8

/** \brief twi asynchronous transfer descriptor.*/
struct _async_desc
{
	struct _usart_desc *usart_desc;
	uint32_t usart_id;
	struct _buffer buf;
	uint32_t transferred; /**< Number of already transferred bytes. */
};

static struct _async_desc async_desc[MAX_ADESC];
static uint8_t adesc_index = 0;

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

static void _usartd_handler(void)
{
	int i;
	uint32_t status = 0;
	Usart* addr;
	uint32_t id = aic_get_current_interrupt_identifier();
	bool _rx_stop = true;
	bool _tx_stop = true;
	
	for (i = 0; i != MAX_ADESC; i++) {
		if (async_desc[i].usart_id == id) {
			status = 1;
			break;
		}
	}

	if (!status) {
		/* async descriptor not found, disable interrupt */
		addr = get_usart_addr_from_id(id);
		usart_disable_it(addr, US_IDR_RXRDY | US_IDR_TXRDY);
		return;
	}

	struct _async_desc* adesc = &async_desc[i];
	addr = adesc->usart_desc->addr;
	status = usart_get_masked_status(addr);

	if (USART_STATUS_RXRDY(status)) {
		if (adesc->buf.attr & USARTD_BUF_ATTR_READ) {
			adesc->buf.data[adesc->transferred] = usart_get_char(addr);
			adesc->transferred++;

			if (adesc->transferred == adesc->buf.size)
				usart_disable_it(addr, US_IDR_RXRDY);
			else
				_rx_stop = false;
		}
	}

	if (USART_STATUS_TXRDY(status)) {
		if (adesc->buf.attr & USARTD_BUF_ATTR_WRITE) {
			usart_put_char(addr, adesc->buf.data[adesc->transferred]);
			adesc->transferred++;

			if (adesc->transferred >= adesc->buf.size) {
				usart_disable_it(addr, US_IDR_TXRDY);
				usart_enable_it(addr, US_IDR_TXEMPTY);
			}
			_tx_stop = false;
		}
	} else if (USART_STATUS_TXEMPTY(status)) {
		usart_disable_it(addr, US_IDR_TXEMPTY);
	}

	if (_rx_stop && _tx_stop) {
		adesc->usart_id = 0;
		aic_disable(id);

		mutex_unlock(&adesc->usart_desc->mutex);
	}
}

static void _usartd_write_dma_callback(struct dma_channel* channel, void* args)
{
	struct _usart_desc* usartd = (struct _usart_desc*)args;

	dma_free_channel(channel);

	if (usartd && usartd->callback)
		usartd->callback(usartd, usartd->cb_args);

	mutex_unlock(&usartd->mutex);
}

static void _usartd_read_dma_callback(struct dma_channel* channel, void* args)
{
	struct _usart_desc* usartd = (struct _usart_desc*)args;

	dma_free_channel(channel);

	cache_invalidate_region(usartd->dma.rx.cfg.da, usartd->dma.rx.cfg.len);

	if (usartd && usartd->callback)
		usartd->callback(usartd, usartd->cb_args);

	mutex_unlock(&usartd->mutex);
}

static void _usartd_dma_read(struct _usart_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_usart_id_from_addr(desc->addr);

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

	desc->dma.rx.cfg.sa = (void *)&desc->addr->US_RHR;
	desc->dma.rx.cfg.da = buffer->data;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 1;
	desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.rx.cfg.len = buffer->size;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);

	dma_set_callback(desc->dma.rx.channel, _usartd_read_dma_callback, (void*)desc);
	dma_start_transfer(desc->dma.rx.channel);
}

static void _usartd_dma_write(struct _usart_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_usart_id_from_addr(desc->addr);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);

	desc->dma.tx.cfg.sa = buffer->data;
	desc->dma.tx.cfg.da = (void *)&desc->addr->US_THR;
	desc->dma.tx.cfg.upd_sa_per_data = 1;
	desc->dma.tx.cfg.upd_da_per_data = 0;
	desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	desc->dma.tx.cfg.len = buffer->size;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);

	dma_set_callback(desc->dma.tx.channel, _usartd_write_dma_callback, (void*)desc);
	cache_clean_region(desc->dma.tx.cfg.sa, desc->dma.tx.cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
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
}

uint32_t usartd_transfer(struct _usart_desc* desc, struct _buffer* buf,
						 usartd_callback_t cb, void* user_args)
{
	uint32_t i = 0;
	uint32_t id;
	uint8_t tmode;

	if ((buf->attr & USARTD_BUF_ATTR_READ) && (buf->attr & USARTD_BUF_ATTR_WRITE))
		return USARTD_ERROR_DUPLEX;
	
	if ((buf == NULL) || (buf->size == 0))
		return USARTD_SUCCESS;

	if (!mutex_try_lock(&desc->mutex))
		return USARTD_ERROR_LOCK;

	desc->callback = cb;
	desc->cb_args = user_args;
	tmode = desc->transfer_mode;
	desc->flags = buf->attr;

	/* If short transfer detected, use POLLING mode */
	if (tmode != USARTD_MODE_POLLING)
		if (buf->size < USARTD_POLLING_THRESHOLD)
			tmode = USARTD_MODE_POLLING;

	switch (tmode) {
	case USARTD_MODE_POLLING:
		for (i = 0; i < buf->size; ++i) {
			if (buf->attr == USARTD_BUF_ATTR_WRITE)
				usart_put_char(desc->addr, buf->data[i]);
			else
				buf->data[i] = usart_get_char(desc->addr);
		}
		mutex_unlock(&desc->mutex);
		if (cb)
			cb(desc, user_args);
		break;

	case USARTD_MODE_ASYNC:
		/* Copy descriptor to async descriptor */
		async_desc[adesc_index].usart_desc = desc;
		/* Init param used by interrupt handler */
		async_desc[adesc_index].transferred = 0;
		async_desc[adesc_index].buf.data = buf->data;
		async_desc[adesc_index].buf.size = buf->size;
		async_desc[adesc_index].buf.attr = buf->attr;
		id = get_usart_id_from_addr(desc->addr);
		async_desc[adesc_index].usart_id = id;
		adesc_index = (adesc_index + 1) % MAX_ADESC;

		/* Set USART handler */
		aic_set_source_vector(id, _usartd_handler);
		/* Enable USART interrupt */
		aic_enable(id);

		if (desc->flags & USARTD_BUF_ATTR_WRITE)
			usart_enable_it(desc->addr, US_IER_TXRDY);

		if (desc->flags & USARTD_BUF_ATTR_READ)
			usart_enable_it(desc->addr, US_IER_RXRDY);
		break;

	case USARTD_MODE_DMA:
		if (buf->attr & USARTD_BUF_ATTR_WRITE)
			_usartd_dma_write(desc, buf);
		if (buf->attr & USARTD_BUF_ATTR_READ)
			_usartd_dma_read(desc, buf);
		break;

	default:
		trace_fatal("Unknown Usart mode!\r\n");
	}

	return USARTD_SUCCESS;
}

void usartd_finish_transfer_callback(struct _usart_desc* desc, void* user_args)
{
	(void)user_args;
	usartd_finish_transfer(desc);
}

void usartd_finish_transfer(struct _usart_desc* desc)
{
	mutex_unlock(&desc->mutex);
}

uint32_t usartd_is_busy(const struct _usart_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void usartd_wait_transfer(const struct _usart_desc* desc)
{
	while (mutex_is_locked(&desc->mutex));
}
