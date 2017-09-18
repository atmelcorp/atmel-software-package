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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "callback.h"
#include "chip.h"
#include "dma/dma.h"
#include "io.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "mutex.h"
#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/pmc.h"
#include "serial/usart.h"
#include "serial/usartd.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/

#define USARTD_ATTRIBUTE_MASK     (0)
#define USARTD_POLLING_THRESHOLD  16

static struct _usart_desc *_serial[USART_IFACE_COUNT];

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

static int _usartd_dma_write_callback(void* arg, void* arg2)
{
	uint8_t iface = (uint32_t)arg;
	assert(iface < USART_IFACE_COUNT);

	dma_reset_channel(_serial[iface]->dma.tx.channel);

	mutex_unlock(&_serial[iface]->tx.mutex);

	callback_call(&_serial[iface]->tx.callback, NULL);

	return 0;
}

static int _usartd_dma_read_callback(void* arg, void* arg2)
{
	uint8_t iface = (uint32_t)arg;
	assert(iface < USART_IFACE_COUNT);
	struct _usart_desc *desc = _serial[iface];
	struct _dma_channel* channel = desc->dma.rx.channel;

	if (desc->timeout > 0) {
		desc->addr->US_CR = US_CR_STTTO;
		usart_disable_it(desc->addr, US_IDR_TIMEOUT);
	}

	if (!dma_is_transfer_done(channel))
		dma_stop_transfer(channel);
	dma_fifo_flush(channel);

	desc->rx.transferred = dma_get_transferred_data_len(channel, desc->dma.rx.cfg_dma.chunk_size, desc->dma.rx.cfg.len);
	dma_reset_channel(desc->dma.rx.channel);

	if (desc->rx.transferred > 0)
		cache_invalidate_region(desc->dma.rx.cfg.daddr, desc->rx.transferred);

	desc->rx.buffer.size = 0;

	mutex_unlock(&desc->rx.mutex);

	callback_call(&desc->rx.callback, NULL);

	return 0;
}

static void _usartd_dma_read(uint8_t iface)
{
	struct _callback _cb;
	assert(iface < USART_IFACE_COUNT);
	struct _usart_desc* desc = _serial[iface];

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.cfg.saddr = (void *)&desc->addr->US_RHR;
	desc->dma.rx.cfg.daddr = desc->rx.buffer.data;
	desc->dma.rx.cfg.len = desc->rx.buffer.size;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg_dma, &desc->dma.rx.cfg, 1);

	callback_set(&_cb, _usartd_dma_read_callback, (void*)(uint32_t)iface);
	dma_set_callback(desc->dma.rx.channel, &_cb);
	usart_enable_it(desc->addr, US_IER_TIMEOUT);
	usart_restart_rx_timeout(desc->addr);
	dma_start_transfer(desc->dma.rx.channel);
}

static void _usartd_dma_write(uint8_t iface)
{
	struct _callback _cb;
	assert(iface < USART_IFACE_COUNT);
	struct _usart_desc* desc = _serial[iface];
	struct _dma_transfer_cfg cfg;

	cfg.saddr = desc->tx.buffer.data;
	cfg.daddr = (void *)&desc->addr->US_THR;
	cfg.len = desc->tx.buffer.size;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg_dma, &cfg, 1);

	callback_set(&_cb, _usartd_dma_write_callback, (void*)(uint32_t)iface);
	dma_set_callback(desc->dma.tx.channel, &_cb);
	cache_clean_region(cfg.saddr, cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
}

static void _usartd_handler(uint32_t source, void* user_arg)
{
	int iface;
	uint32_t status = 0;
	Usart* addr = get_usart_addr_from_id(source);
	bool _rx_stop = true;
	bool _tx_stop = true;

	for (iface = 0; iface < USART_IFACE_COUNT; iface++) {
		if (_serial[iface]->addr == addr) {
			status = 1;
			break;
		}
	}

	if (!status) {
		/* async descriptor not found, disable interrupt */
		usart_disable_it(addr, US_IDR_RXRDY | US_IDR_TXRDY | US_IDR_TXEMPTY | US_IDR_TIMEOUT);
		return;
	}

	struct _usart_desc* desc = _serial[iface];
	status = usart_get_masked_status(addr);
	desc->rx.has_timeout = false;

	if (USART_STATUS_RXRDY(status)) {
		if (desc->rx.buffer.size) {
			desc->rx.buffer.data[desc->rx.transferred] = usart_get_char(addr);
			desc->rx.transferred++;

			if (desc->rx.transferred >= desc->rx.buffer.size)
				usart_disable_it(addr, US_IDR_RXRDY);
			else
				_rx_stop = false;
		}
	}

	if (USART_STATUS_TXRDY(status)) {
		if (desc->tx.buffer.size) {
			usart_put_char(addr, desc->tx.buffer.data[desc->tx.transferred]);
			desc->tx.transferred++;

			if (desc->tx.transferred > desc->tx.buffer.size) {
				usart_disable_it(addr, US_IDR_TXRDY);
				usart_enable_it(addr, US_IER_TXEMPTY);
			}
			_tx_stop = false;
		}
	}

	if (USART_STATUS_TIMEOUT(status)) {
		switch (desc->transfer_mode) {
		case USARTD_MODE_ASYNC:
			desc->addr->US_CR = US_CR_STTTO;
			usart_disable_it(addr, US_IDR_TIMEOUT);
			break;
		case USARTD_MODE_DMA:
			_usartd_dma_read_callback((void *)iface, NULL);
			break;
		}

		if (desc->rx.buffer.size)
			usart_disable_it(addr, US_IDR_RXRDY);

		if (desc->tx.buffer.size)
			usart_disable_it(addr, US_IDR_TXRDY | US_IDR_TXEMPTY);

		desc->rx.has_timeout = true;
	}

	if (USART_STATUS_TXEMPTY(status)) {
		usart_disable_it(addr, US_IDR_TXEMPTY);
	}

	if (_rx_stop) {
		desc->addr->US_CR = US_CR_STTTO;
		desc->rx.buffer.size = 0;
		mutex_unlock(&desc->rx.mutex);
	}
	if (_tx_stop) {
		desc->tx.buffer.size = 0;
		mutex_unlock(&desc->tx.mutex);
	}
}

void usartd_configure(uint8_t iface, struct _usart_desc* config)
{
	uint32_t id = get_usart_id_from_addr(config->addr);
	assert(id < ID_PERIPH_COUNT);
	assert(iface < USART_IFACE_COUNT);

	_serial[iface] = config;

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(id);
	if (flexcom) {
		flexcom_select(flexcom, FLEX_MR_OPMODE_USART);
	}
#endif
	pmc_configure_peripheral(id, NULL, true);
	usart_configure(config->addr, config->mode, config->baudrate);
	usart_set_rx_timeout(config->addr, config->baudrate, config->timeout);
	irq_add_handler(get_usart_id_from_addr(config->addr), _usartd_handler, NULL);
	/* Enable USART interrupt */
	irq_enable(id);

#ifdef CONFIG_HAVE_USART_FIFO
	config->fifo.rx.size = get_peripheral_fifo_depth(config->addr);
	config->fifo.tx.size = get_peripheral_fifo_depth(config->addr);
	usart_fifo_configure(config->addr, config->fifo.tx.threshold,
						 config->fifo.rx.threshold, config->fifo.rx.threshold);
	if (config->use_fifo)
		usart_fifo_enable(config->addr);
#endif

	config->dma.rx.cfg_dma.incr_saddr = false;
	config->dma.rx.cfg_dma.incr_daddr = true;
	config->dma.rx.cfg_dma.loop = false;
	config->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	config->dma.rx.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	config->dma.tx.cfg_dma.incr_saddr = true;
	config->dma.tx.cfg_dma.incr_daddr = false;
	config->dma.tx.cfg_dma.loop = false;
	config->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	config->dma.tx.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	config->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(config->dma.rx.channel);

	config->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(config->dma.tx.channel);
}

uint32_t usartd_transfer(uint8_t iface, struct _buffer* buf, struct _callback* cb)
{
	assert(iface < USART_IFACE_COUNT);
	struct _usart_desc *desc = _serial[iface];
	uint8_t tmode;
	uint32_t csr;
	uint32_t i;

	if ((buf == NULL) || (buf->size == 0))
		return USARTD_SUCCESS;

	if (buf->attr & USARTD_BUF_ATTR_READ) {
		if (!mutex_try_lock(&desc->rx.mutex))
			return USARTD_ERROR_LOCK;

		desc->rx.transferred = 0;
		desc->rx.buffer.data = buf->data;
		desc->rx.buffer.size = buf->size;
		desc->rx.buffer.attr = buf->attr;
		callback_copy(&desc->rx.callback, cb);

		desc->rx.has_timeout = false;
	}

	if (buf->attr & USARTD_BUF_ATTR_WRITE) {
		if (!mutex_try_lock(&desc->tx.mutex))
			return USARTD_ERROR_LOCK;

		desc->tx.transferred = 0;
		desc->tx.buffer.data = buf->data;
		desc->tx.buffer.size = buf->size;
		desc->tx.buffer.attr = buf->attr;
		callback_copy(&desc->tx.callback, cb);
	}

	tmode = desc->transfer_mode;

	/* If short transfer detected, use POLLING mode */
	if (tmode != USARTD_MODE_POLLING)
		if (buf->size < USARTD_POLLING_THRESHOLD)
			tmode = USARTD_MODE_POLLING;

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
					mutex_unlock(&desc->tx.mutex);
					callback_call(&desc->tx.callback, NULL);
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
							desc->addr->US_CR = US_CR_STTTO;
							desc->rx.buffer.size = 0;
							desc->rx.transferred = i;
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
					mutex_unlock(&desc->rx.mutex);
					callback_call(&desc->rx.callback, NULL);
				}
			}
		}
		break;

	case USARTD_MODE_ASYNC:
		if (buf->attr & USARTD_BUF_ATTR_WRITE)
			usart_enable_it(desc->addr, US_IER_TXRDY);

		if (buf->attr & USARTD_BUF_ATTR_READ) {
			usart_get_status(desc->addr);

			usart_restart_rx_timeout(desc->addr);
			usart_enable_it(desc->addr, US_IER_RXRDY | US_IER_TIMEOUT);
		}
		break;

	case USARTD_MODE_DMA:
		if (buf->attr & USARTD_BUF_ATTR_WRITE)
			_usartd_dma_write(0);
		if (buf->attr & USARTD_BUF_ATTR_READ)
			_usartd_dma_read(0);
		break;

	default:
		trace_fatal("Unknown Usart mode!\r\n");
	}

	return USARTD_SUCCESS;
}

void usartd_finish_rx_transfer(uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	mutex_unlock(&_serial[iface]->rx.mutex);
}

void usartd_finish_tx_transfer(uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	mutex_unlock(&_serial[iface]->tx.mutex);
}

uint32_t usartd_rx_is_busy(const uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	return mutex_is_locked(&_serial[iface]->rx.mutex);
}

uint32_t usartd_tx_is_busy(const uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	return mutex_is_locked(&_serial[iface]->tx.mutex);
}

void usartd_wait_rx_transfer(const uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	while (mutex_is_locked(&_serial[iface]->rx.mutex));
}

void usartd_wait_tx_transfer(const uint8_t iface)
{
	assert(iface < USART_IFACE_COUNT);
	while (mutex_is_locked(&_serial[iface]->tx.mutex));
}
