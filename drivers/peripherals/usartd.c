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
#define USARTD_POLLING_THRESHOLD  1

#define MAX_ADESC                 8

/** \brief twi asynchronous transfer descriptor.*/
struct _async_desc
{
	struct _usart_desc *usart_desc;
	uint32_t usart_id;
};

static struct _async_desc async_desc[MAX_ADESC];
static uint8_t adesc_index = 0;

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

static void _usartd_dma_write_callback(struct dma_channel* channel, void* args)
{
	struct _usart_desc* usartd = (struct _usart_desc*)args;

	dma_free_channel(channel);

	if (usartd && usartd->tx.callback)
		usartd->tx.callback(usartd, usartd->tx.cb_args);

	mutex_unlock(&usartd->tx.mutex);
}

static void _usartd_dma_read_callback(struct dma_channel* channel, void* args)
{
	struct _usart_desc* usartd = (struct _usart_desc*)args;

	usartd->rx.transferred = usartd->dma.rx.cfg.len - dma_get_remaining_data_len(channel, usartd->dma.rx.cfg.chunk_size);

	dma_free_channel(channel);

	if (usartd->rx.transferred > 0) {
		cache_invalidate_region(usartd->dma.rx.cfg.da, usartd->rx.transferred);

		if (usartd && usartd->rx.callback)
			usartd->rx.callback(usartd, usartd->rx.cb_args);
	}

	usartd->rx.buffer.size = 0;

	mutex_unlock(&usartd->rx.mutex);
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

	dma_set_callback(desc->dma.rx.channel, _usartd_dma_read_callback, (void*)desc);
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

	dma_set_callback(desc->dma.tx.channel, _usartd_dma_write_callback, (void*)desc);
	cache_clean_region(desc->dma.tx.cfg.sa, desc->dma.tx.cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
}

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
		usart_disable_it(addr, US_IDR_RXRDY | US_IDR_TXRDY | US_IDR_TIMEOUT);
		return;
	}

	struct _async_desc* adesc = &async_desc[i];
	addr = adesc->usart_desc->addr;
	status = usart_get_masked_status(addr);
	adesc->usart_desc->rx.has_timeout = false;

	if (USART_STATUS_TIMEOUT(status)) {
		usart_disable_it(addr, US_IDR_TIMEOUT);
		adesc->usart_desc->rx.has_timeout = true;
	}

	if (USART_STATUS_RXRDY(status) && !adesc->usart_desc->rx.has_timeout) {
		if (adesc->usart_desc->rx.buffer.size) {
			adesc->usart_desc->rx.buffer.data[adesc->usart_desc->rx.transferred] = usart_get_char(addr);
			adesc->usart_desc->rx.transferred++;

			if (adesc->usart_desc->rx.transferred == adesc->usart_desc->rx.buffer.size)
				usart_disable_it(addr, US_IDR_RXRDY);
			else
				_rx_stop = false;
		}
	}

	if (USART_STATUS_TXRDY(status)) {
		if (adesc->usart_desc->tx.buffer.size) {
			usart_put_char(addr, adesc->usart_desc->tx.buffer.data[adesc->usart_desc->tx.transferred]);
			adesc->usart_desc->tx.transferred++;

			if (adesc->usart_desc->tx.transferred >= adesc->usart_desc->tx.buffer.size) {
				usart_disable_it(addr, US_IDR_TXRDY);
				usart_enable_it(addr, US_IDR_TXEMPTY);
			}
			_tx_stop = false;
		}
	} else if (USART_STATUS_TXEMPTY(status)) {
		usart_disable_it(addr, US_IDR_TXEMPTY);
	}

	if (_rx_stop && _tx_stop)
		adesc->usart_id = 0;

	if (_rx_stop) {
		adesc->usart_desc->rx.buffer.size = 0;
		mutex_unlock(&adesc->usart_desc->rx.mutex);
	}
	if (_tx_stop) {
		adesc->usart_desc->tx.buffer.size = 0;
		mutex_unlock(&adesc->usart_desc->tx.mutex);
	}
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
	usart_set_rx_timeout(desc->addr, desc->baudrate, desc->timeout);
	aic_set_source_vector(get_usart_id_from_addr(desc->addr), _usartd_handler);
	/* Enable USART interrupt */
	aic_enable(id);

#ifdef CONFIG_HAVE_USART_FIFO
	desc->fifo.rx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.tx.size = get_peripheral_fifo_depth(desc->addr);
	usart_fifo_configure(desc->addr, desc->fifo.tx.threshold,
						 desc->fifo.rx.threshold, desc->fifo.rx.threshold);
	if (desc->use_fifo)
		usart_fifo_enable(desc->addr);
#endif
}

uint32_t usartd_transfer(struct _usart_desc* desc, struct _buffer* buf,
						 usartd_callback_t cb, void* user_args)
{
	uint32_t i = 0;
	uint32_t id;
	uint8_t tmode;
	uint8_t _adesc_idx;
	uint32_t csr;

	if ((buf == NULL) || (buf->size == 0))
		return USARTD_SUCCESS;

	if (buf->attr & USARTD_BUF_ATTR_READ) {
		if (!mutex_try_lock(&desc->rx.mutex))
			return USARTD_ERROR_LOCK;

		desc->rx.transferred = 0;
		desc->rx.buffer.data = buf->data;
		desc->rx.buffer.size = buf->size;
		desc->rx.buffer.attr = buf->attr;
		desc->rx.callback = cb;
		desc->rx.cb_args = user_args;

		desc->rx.has_timeout = false;
	}

	if (buf->attr & USARTD_BUF_ATTR_WRITE) {
		if (!mutex_try_lock(&desc->tx.mutex))
			return USARTD_ERROR_LOCK;

		desc->tx.transferred = 0;
		desc->tx.buffer.data = buf->data;
		desc->tx.buffer.size = buf->size;
		desc->tx.buffer.attr = buf->attr;
		desc->tx.callback = cb;
		desc->tx.cb_args = user_args;
	}

	tmode = desc->transfer_mode;

	/* If short transfer detected, use POLLING mode */
	if (tmode != USARTD_MODE_POLLING)
		if (buf->size < USARTD_POLLING_THRESHOLD)
			tmode = USARTD_MODE_POLLING;

	id = get_usart_id_from_addr(desc->addr);
	for (_adesc_idx = 0 ; _adesc_idx < MAX_ADESC ; _adesc_idx++)
		if (async_desc[_adesc_idx].usart_id == id)
			break;

	if (_adesc_idx >= MAX_ADESC) {
		_adesc_idx = adesc_index;
		adesc_index = (adesc_index + 1) % MAX_ADESC;
		/* Copy descriptor to async descriptor */
		async_desc[_adesc_idx].usart_desc = desc;
		async_desc[_adesc_idx].usart_id = id;
	}

	if (tmode == USARTD_MODE_DMA) {
		if (desc->timeout > 0) {
			trace_fatal("Usart TIMEOUT not implemented for DMA transfer\r\n");
		}
	}

	switch (tmode) {
	case USARTD_MODE_POLLING:
		i = 0;

		if (buf->attr & USARTD_BUF_ATTR_READ) {
			desc->addr->US_CSR;
			usart_restart_rx_timeout(desc->addr);
		}

		while (i < buf->size) {
			if (i < desc->tx.buffer.size) {
#ifdef CONFIG_HAVE_USART_FIFO
				if (desc->use_fifo) {
					if ((desc->fifo.tx.size - usart_fifo_get_tx_size(desc->addr)) > 0) {
						if ((desc->tx.buffer.size - i) >= 4) {
							writew(&desc->addr->US_THR, *(uint32_t*)&desc->tx.buffer.data[i]);
							i += 4;
						} else if ((desc->tx.buffer.size - i) >= 2) {
							writehw(&desc->addr->US_THR, *(uint16_t*)&desc->tx.buffer.data[i]);
							i += 2;
						} else {
							writeb(&desc->addr->US_THR, *(uint8_t*)&desc->tx.buffer.data[i]);
							i += 1;
						}
					}
				} else
#endif /* CONFIG_HAVE_USART_FIFO */
				{
					/* Wait for the transmitter to be ready */
					while (!USART_STATUS_TXRDY(desc->addr->US_CSR));

					writeb(&desc->addr->US_THR, desc->tx.buffer.data[i]);
					i++;
				}
				desc->tx.transferred = i;

				if (desc->tx.transferred >= desc->tx.buffer.size) {
					desc->tx.buffer.size = 0;
					if (desc->rx.buffer.size == 0)
						async_desc[_adesc_idx].usart_id = 0;
					if (desc->tx.callback)
						desc->tx.callback(desc, desc->tx.cb_args);
					mutex_unlock(&desc->tx.mutex);
				}
			}
			if (i < desc->rx.buffer.size) {
#ifdef CONFIG_HAVE_USART_FIFO
				if (desc->use_fifo) {
					if ((desc->fifo.rx.size - usart_fifo_get_rx_size(desc->addr)) > 0) {
						if ((desc->rx.buffer.size - i) >= 4) {
							readw(&desc->addr->US_RHR, (uint32_t*)&desc->rx.buffer.data[i]);
							i += 4;
						} else if (usart_fifo_get_rx_size(desc->addr) >= 2) {
							readhw(&desc->addr->US_RHR, (uint16_t*)&desc->rx.buffer.data[i]);
							i += 2;
						} else {
							readb(&desc->addr->US_RHR, (uint8_t*)&desc->rx.buffer.data[i]);
							i += 1;
						}
					}
				} else
#endif /* CONFIG_HAVE_USART_FIFO */
				{
					/* Wait for the transmitter to be ready */
					csr = desc->addr->US_CSR;
					while (!USART_STATUS_RXRDY(csr)) {
						if (USART_STATUS_TIMEOUT(csr)) {
							desc->rx.buffer.size = 0;
							desc->rx.transferred = i;
							if (desc->tx.buffer.size == 0)
								async_desc[_adesc_idx].usart_id = 0;
							mutex_unlock(&desc->rx.mutex);
							return USARTD_ERROR_TIMEOUT;
						}
						csr = desc->addr->US_CSR;
					}

					readb(&desc->addr->US_RHR, &desc->rx.buffer.data[i]);
					i++;
				}
				desc->rx.transferred = i;

				if (desc->rx.transferred >= desc->rx.buffer.size) {
					desc->rx.buffer.size = 0;
					if (desc->tx.buffer.size == 0)
						async_desc[_adesc_idx].usart_id = 0;
					if (desc->rx.callback)
						desc->rx.callback(desc, desc->rx.cb_args);
					mutex_unlock(&desc->rx.mutex);
				}
			}
		}
		break;

	case USARTD_MODE_ASYNC:
		if (buf->attr & USARTD_BUF_ATTR_WRITE) {
			async_desc[_adesc_idx].usart_desc->tx.transferred = 0;
			usart_enable_it(desc->addr, US_IER_TXRDY);
		}

		if (buf->attr & USARTD_BUF_ATTR_READ) {
			usart_get_status(desc->addr);

			usart_restart_rx_timeout(desc->addr);

			async_desc[_adesc_idx].usart_desc->rx.transferred = 0;
			usart_enable_it(desc->addr, US_IER_RXRDY | US_IER_TIMEOUT);
		}
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

void usartd_finish_rx_transfer_callback(struct _usart_desc* desc, void* user_args)
{
	(void)user_args;
	usartd_finish_rx_transfer(desc);
}

void usartd_finish_tx_transfer_callback(struct _usart_desc* desc, void* user_args)
{
	(void)user_args;
	usartd_finish_tx_transfer(desc);
}

void usartd_finish_rx_transfer(struct _usart_desc* desc)
{
	mutex_unlock(&desc->rx.mutex);
}

void usartd_finish_tx_transfer(struct _usart_desc* desc)
{
	mutex_unlock(&desc->tx.mutex);
}

uint32_t usartd_rx_is_busy(const struct _usart_desc* desc)
{
	return mutex_is_locked(&desc->rx.mutex);
}

uint32_t usartd_tx_is_busy(const struct _usart_desc* desc)
{
	return mutex_is_locked(&desc->tx.mutex);
}

void usartd_wait_rx_transfer(const struct _usart_desc* desc)
{
	while (mutex_is_locked(&desc->rx.mutex));
}

void usartd_wait_tx_transfer(const struct _usart_desc* desc)
{
	while (mutex_is_locked(&desc->tx.mutex));
}
