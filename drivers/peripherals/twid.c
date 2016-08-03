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

#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"
#include "peripherals/twi.h"
#include "peripherals/dma.h"
#include "misc/cache.h"

#include "trace.h"
#include "io.h"
#include "timer.h"

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/

#define TWID_POLLING_THRESHOLD  16
#define TWID_TIMEOUT            100

#define MAX_ADESC               8

static struct _async_desc async_desc[MAX_ADESC];
static uint8_t adesc_index = 0;

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

/*
 *
 */
static bool _check_nack(struct _twi_desc *desc)
{
#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo) {
		if (twi_fifo_is_locked(desc->addr)) {
			twi_fifo_unlock(desc->addr);
			twi_fifo_flush_tx(desc->addr);
			trace_error("twid: command NACK\r\n");
			return true;
		}

		return false;
	}
#endif

	if (twi_get_status(desc->addr) & TWI_SR_NACK) {
		trace_error("twid: command NACK\r\n");
		return true;
	}

	return false;
}

/*
 *
 */
static bool _check_rx_timeout(struct _twi_desc* desc)
{
	struct _timeout timeout;

#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo)
		return false;
#endif

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_byte_received(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Device doesn't answer (RX TIMEOUT)\r\n");
			return true;
		}
	}

	return false;
}

/*
 *
 */
static bool _check_tx_timeout(struct _twi_desc* desc)
{
	struct _timeout timeout;

#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo)
		return false;
#endif

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_byte_sent(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Device doesn't answer (TX TIMEOUT)\r\n");
			return true;
		}
	}

	return false;
}

static uint32_t _twid_wait_twi_transfer(struct _twi_desc* desc)
{
	struct _timeout timeout;

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_transfer_complete(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Unable to complete transfer!\r\n");
			twid_configure(desc);
			return TWID_ERROR_TRANSFER;
		}
	}

	return TWID_SUCCESS;
}

static void _twid_dma_read_callback(struct dma_channel* channel, void* args)
{
	struct _twi_desc* desc = (struct _twi_desc *)args;

	cache_invalidate_region(desc->dma.rx.cfg.da, desc->dma.rx.cfg.len);

	dma_free_channel(channel);

	if (_check_rx_timeout(desc)) {
		mutex_unlock(&desc->mutex);
		return;
	}

	if (desc->flags & TWID_BUF_ATTR_STOP)
		twi_send_stop_condition(desc->addr);

#ifdef CONFIG_HAVE_FIFO
	if (!desc->use_fifo)
#endif
	{
		((uint8_t*)desc->dma.rx.cfg.da)[desc->dma.rx.cfg.len] = twi_read_byte(desc->addr);

		if (_check_rx_timeout(desc)) {
			mutex_unlock(&desc->mutex);
			return;
		}

		((uint8_t*)desc->dma.rx.cfg.da)[desc->dma.rx.cfg.len + 1] = twi_read_byte(desc->addr);
	}

	if (desc->callback)
		desc->callback(desc, desc->cb_args);

	mutex_unlock(&desc->mutex);
}

static void _twid_dma_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_twi_id_from_addr(desc->addr);

	assert(id < ID_PERIPH_COUNT);

	memset(&desc->dma.rx.cfg, 0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

	desc->dma.rx.cfg.sa = (void*)&desc->addr->TWI_RHR;
	desc->dma.rx.cfg.da = buffer->data;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 1;
#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo) {
		if ((buffer->size % 4) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_FOUR_DATA;
			desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_WORD;
		} else if ((buffer->size % 2) == 0)  {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_TWO_DATA;
			desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		} else {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_ONE_DATA;
			desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
		}
		desc->dma.rx.cfg.len = buffer->size;
	} else {
		desc->dma.rx.cfg.len = buffer->size - 2;
		desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_ONE_DATA;
		desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	}
#else
	desc->dma.rx.cfg.len = buffer->size - 2;
	desc->dma.rx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
#endif
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);
	dma_set_callback(desc->dma.rx.channel, _twid_dma_read_callback, (void*)desc);
	dma_start_transfer(desc->dma.rx.channel);

	if (desc->flags & TWID_BUF_ATTR_START)
		twi_send_start_condition(desc->addr);
}

static void _twid_dma_write_callback(struct dma_channel* channel, void* args)
{
	struct _twi_desc* desc = (struct _twi_desc *)args;

	dma_free_channel(channel);

	if (_check_tx_timeout(desc)) {
		mutex_unlock(&desc->mutex);
		return;
	}

	if (desc->flags & TWID_BUF_ATTR_STOP)
		twi_send_stop_condition(desc->addr);

#ifdef CONFIG_HAVE_TWI_FIFO
	if (!desc->use_fifo)
		twi_write_byte(desc->addr, ((uint8_t *)desc->dma.tx.cfg.sa)[desc->dma.tx.cfg.len]);
#endif

	if (desc->callback)
		desc->callback(desc, desc->cb_args);

	mutex_unlock(&desc->mutex);
}

static void _twid_dma_write(struct _twi_desc *desc, struct _buffer *buffer)
{
	uint32_t id = get_twi_id_from_addr(desc->addr);

	assert(id < ID_PERIPH_COUNT);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);

	desc->dma.tx.cfg.sa = buffer->data;
	desc->dma.tx.cfg.da = (void*)&desc->addr->TWI_THR;
	desc->dma.tx.cfg.upd_sa_per_data = 1;
	desc->dma.tx.cfg.upd_da_per_data = 0;
#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo) {
		if ((buffer->size % 4) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_FOUR_DATA;
			desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_WORD;
		} else if ((buffer->size % 2) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_TWO_DATA;
			desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		} else {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_ONE_DATA;
			desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
		}
		desc->dma.tx.cfg.len = buffer->size;
	} else {
		desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_ONE_DATA;
		desc->dma.tx.cfg.len = buffer->size - 1;
		desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
	}
#else
	desc->dma.tx.cfg.len = buffer->size - 1;
	desc->dma.tx.cfg.data_width = DMA_DATA_WIDTH_BYTE;
#endif
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);
	dma_set_callback(desc->dma.tx.channel, _twid_dma_write_callback, (void*)desc);
	cache_clean_region(desc->dma.tx.cfg.sa, desc->dma.tx.cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
}

/*
 *
 */
static void _twid_handler(void)
{
	int i;
	uint32_t status = 0;
	Twi* addr;
	uint32_t id = aic_get_current_interrupt_identifier();
	uint32_t buf_size;
	bool use_fifo = false;

	for (i = 0; i != MAX_ADESC; i++) {
		if (async_desc[i].twi_id == id) {
			status = 1;
			break;
		}
	}

	if (!status) {
		/* async descriptor not found, disable interrupt */
		addr = get_twi_addr_from_id(id);
		twi_disable_it(addr, TWI_IDR_RXRDY | TWI_IDR_TXRDY);
		return;
	}

	struct _async_desc* adesc = &async_desc[i];
	addr = adesc->twi_desc->addr;
	status = twi_get_masked_status(addr);

#if defined(CONFIG_HAVE_TWI_FIFO)
	use_fifo = adesc->twi_desc->use_fifo;
#endif

	if (TWI_STATUS_RXRDY(status)) {
		if (use_fifo) {
#ifdef CONFIG_HAVE_TWI_FIFO
			uint8_t size = twi_fifo_get_rx_size(addr);

			adesc->transferred += twi_fifo_read(addr, &adesc->buf.data[adesc->transferred], size);

			if ((adesc->buf.size - adesc->transferred) >= 4)
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_FOUR_DATA;
			else if ((adesc->buf.size - adesc->transferred) >= 2)
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_TWO_DATA;
			else
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_ONE_DATA;

			buf_size = adesc->buf.size;
#endif /* CONFIG_HAVE_TWI_FIFO */
		} else {
			adesc->buf.data[adesc->transferred] = twi_read_byte(addr);
			adesc->transferred++;
			buf_size = adesc->buf.size - 1;
		}

		/* Only one byte remaining, send stop condition */
		if (adesc->transferred == buf_size)
			if (adesc->twi_desc->flags & TWID_BUF_ATTR_STOP)
				twi_send_stop_condition(addr);

		if (adesc->transferred == adesc->buf.size) {
			twi_disable_it(addr, TWI_IDR_RXRDY);
			if (adesc->twi_desc->flags & TWID_BUF_ATTR_STOP) {
				twi_enable_it(addr, TWI_IER_TXCOMP);
			} else {
				adesc->twi_id = 0;
				mutex_unlock(&adesc->twi_desc->mutex);
			}
		}
	} else if (TWI_STATUS_TXRDY(status)) {
		if (use_fifo) {
#ifdef CONFIG_HAVE_TWI_FIFO
			uint8_t len = 0;
			uint8_t size = adesc->twi_desc->fifo.tx.size - twi_fifo_get_tx_size(addr);

			if ((adesc->buf.size - adesc->transferred) > size)
				len = size;
			else
				len = adesc->buf.size - adesc->transferred;
			adesc->transferred += twi_fifo_write(addr, &adesc->buf.data[adesc->transferred], len);

			/* Transfer finished ? */
			if (adesc->transferred == adesc->buf.size)
				if (adesc->twi_desc->flags & TWID_BUF_ATTR_STOP)
					twi_send_stop_condition(addr);

			if ((adesc->buf.size - adesc->transferred) >= 4)
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_FOUR_DATA;
			else if ((adesc->buf.size - adesc->transferred) >= 2)
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_TWO_DATA;
			else
				addr->TWI_FMR = (addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_ONE_DATA;
#endif /* CONFIG_HAVE_TWI_FIFO */
		} else {
			/* Transfer finished ? */
			if (adesc->transferred == adesc->buf.size - 1)
				if (adesc->twi_desc->flags & TWID_BUF_ATTR_STOP)
					twi_send_stop_condition(addr);

			twi_write_byte(addr, adesc->buf.data[adesc->transferred]);
			adesc->transferred++;
		}

		if (adesc->transferred >= adesc->buf.size){
			twi_disable_it(addr, TWI_IDR_TXRDY);
			if (adesc->twi_desc->flags & TWID_BUF_ATTR_STOP) {
				twi_enable_it(addr, TWI_IER_TXCOMP);
			} else {
				adesc->twi_id = 0;
				mutex_unlock(&adesc->twi_desc->mutex);
			}
		}
	}
	/* Transfer complete*/
	else if (TWI_STATUS_TXCOMP(status)) {
		aic_disable(id);
		twi_disable_it(addr, TWI_IDR_TXCOMP);
		if (adesc->twi_desc->callback)
			adesc->twi_desc->callback(adesc->twi_desc, adesc->twi_desc->cb_args);
		adesc->twi_id = 0;
		mutex_unlock(&adesc->twi_desc->mutex);
	}
}

/*
 *
 */
static uint32_t _twid_poll_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i;
	Twi* addr = desc->addr;
	int32_t size;
	bool use_fifo = false;

#if defined(CONFIG_HAVE_TWI_FIFO)
	use_fifo = desc->use_fifo;
#endif

	if (use_fifo)
		size = buffer->size;
	else
		size = buffer->size - 1;
	if (size < 0)
		size = 0;

	if (desc->flags & TWID_BUF_ATTR_START)
		twi_send_start_condition(addr);

	if (use_fifo) {
#ifdef CONFIG_HAVE_TWI_FIFO
		for (i = 0 ; i < size ; ) {
			int len;

			do {
				uint8_t _size;

				do {
					_size = twi_fifo_get_rx_size(desc->addr);
				} while (_size == 0);

				if (size > _size)
					len = _size;
				else
					len = size;
			} while (len == 0);

			i += twi_fifo_read(desc->addr, &buffer->data[i], len);

			if ((i < size) && _check_nack(desc))
				return TWID_ERROR_ACK;
		}
#endif /* CONFIG_HAVE_TWI_FIFO */
	} else {
		for (i = 0 ; i < size ; i++) {
			if (_check_rx_timeout(desc))
				break;

			buffer->data[i] = twi_read_byte(addr);

			if (_check_nack(desc))
				return TWID_ERROR_ACK;
		}
	}

	/* Before receive last data, send stop */
	if (desc->flags & TWID_BUF_ATTR_STOP)
		twi_send_stop_condition(addr);

	if ((size == buffer->size - 1) || (size == 0)) {
		if (_check_rx_timeout(desc))
			return TWID_ERROR_TIMEOUT;
		buffer->data[i] = twi_read_byte(addr);
	}

	/* wait transfer to be finished */
	if (desc->flags & TWID_BUF_ATTR_STOP)
		return _twid_wait_twi_transfer(desc);
	return TWID_SUCCESS;
}

static uint32_t _twid_poll_write(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i = 0;
	int size;
	bool use_fifo = false;

#if defined(CONFIG_HAVE_TWI_FIFO)
	use_fifo = desc->use_fifo;
#endif

	if (use_fifo)
		size = buffer->size;
	else
		size = buffer->size - 1;
	if (size < 0)
		size = 0;

	/* If only one byte send stop immediatly */
	if (buffer->size <= 1)
		if (desc->flags & TWID_BUF_ATTR_STOP)
			twi_send_stop_condition(desc->addr);

	if (use_fifo) {
#ifdef CONFIG_HAVE_TWI_FIFO
		for (i = 0 ; i < size ; ) {
			uint8_t len;
			do {
				volatile uint8_t _size =  twi_fifo_get_tx_size(desc->addr);

				/* Fill the FIFO as much as possible */
				len = desc->fifo.tx.size - _size;
				len = len > (size) ? size : len;
			} while (len == 0);

			i += twi_fifo_write(desc->addr, &buffer->data[i], len);

			if ((i < size - 1) && _check_nack(desc))
				return TWID_ERROR_ACK;
		}
#endif /* CONFIG_HAVE_TWI_FIFO */
	} else {
		for (i = 0 ; i < size ; i++) {
			if (_check_tx_timeout(desc))
				break;
			twi_write_byte(desc->addr, buffer->data[i]);

			if (_check_nack(desc))
				return TWID_ERROR_ACK;
		}
	}

	if (buffer->size > 1)
		if (desc->flags & TWID_BUF_ATTR_STOP)
			twi_send_stop_condition(desc->addr);

	if (size == buffer->size - 1) {
		if (_check_tx_timeout(desc))
			return TWID_TIMEOUT;
		twi_write_byte(desc->addr, buffer->data[i]);
	}

	/* wait transfer to be finished */
	if (desc->flags & TWID_BUF_ATTR_STOP)
		return _twid_wait_twi_transfer(desc);
	return TWID_SUCCESS;
}

#ifdef CONFIG_HAVE_TWI_FIFO

static void twid_fifo_configure(struct _twi_desc *desc)
{
	desc->fifo.rx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.rx.threshold = desc->fifo.rx.size / 2;
	desc->fifo.tx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.tx.threshold = desc->fifo.tx.size / 2;
	twi_fifo_configure(desc->addr, desc->fifo.rx.threshold, desc->fifo.tx.threshold,
	                   TWI_FMR_RXRDYM_FOUR_DATA | TWI_FMR_TXRDYM_FOUR_DATA);
}

#endif /* CONFIG_HAVE_TWI_FIFO */

/*----------------------------------------------------------------------------
 *        External functions
 *----------------------------------------------------------------------------*/

void twid_configure(struct _twi_desc* desc)
{
	uint32_t id = get_twi_id_from_addr(desc->addr);
	assert(id < ID_PERIPH_COUNT);

	if (desc->timeout == 0)
		desc->timeout = TWID_TIMEOUT;

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(get_twi_id_from_addr(desc->addr));
	if (flexcom) {
		flexcom_select(flexcom, FLEX_MR_OPMODE_TWI);
	}
#endif

	pmc_enable_peripheral(id);
	twi_configure_master(desc->addr, desc->freq);
#ifdef CONFIG_HAVE_TWI_FIFO
	twid_fifo_configure(desc);
	if (desc->use_fifo)
		twi_fifo_enable(desc->addr, true);
#endif

	desc->mutex = 0;
}

/*
 *
 */
static uint32_t _twid_transfer(struct _twi_desc* desc, struct _buffer* buf, twid_callback_t cb, void* user_args)
{
	uint32_t status = TWID_SUCCESS;
	uint32_t id;
	uint8_t tmode;

	if (!mutex_try_lock(&desc->mutex))
		return TWID_ERROR_LOCK;

	desc->callback = cb;
	desc->cb_args = user_args;
	desc->flags = buf->attr;
	tmode = desc->transfer_mode;

	/* If short transfer detected, use POLLING mode */
	if (tmode != TWID_MODE_POLLING) {
		if (buf->size == 0)
			tmode = TWID_MODE_POLLING;
		else if (buf->size < TWID_POLLING_THRESHOLD)
			tmode = TWID_MODE_POLLING;
	}
	
	if (desc->flags & TWID_BUF_ATTR_START) {
		if (desc->flags & TWID_BUF_ATTR_WRITE) {
			twi_init_write(desc->addr, desc->slave_addr, 0, 0);
#ifdef CONFIG_HAVE_TWI_FIFO
			if (desc->use_fifo)
				twi_fifo_flush_tx(desc->addr);
#endif
		} else {
			twi_init_read(desc->addr, desc->slave_addr, 0, 0);
#ifdef CONFIG_HAVE_TWI_FIFO
			if (desc->use_fifo)
				twi_fifo_flush_rx(desc->addr);
#endif
		}
	}

	switch (tmode) {
	case TWID_MODE_ASYNC:
		/* Copy descriptor to async descriptor */
		async_desc[adesc_index].twi_desc = desc;
		/* Init param used by interrupt handler */
		async_desc[adesc_index].transferred = 0;
		async_desc[adesc_index].buf.data = buf->data;
		async_desc[adesc_index].buf.size = buf->size;
		async_desc[adesc_index].buf.attr = buf->attr;
		id = get_twi_id_from_addr(desc->addr);
		async_desc[adesc_index].twi_id = id;

		/* Set TWI handler */
		aic_set_source_vector(id, _twid_handler);
		/* Enable TWI interrupt */
		aic_enable(id);

		if (desc->flags & TWID_BUF_ATTR_WRITE) {
			if (_check_tx_timeout(desc)) {
				twi_disable_it(desc->addr, TWI_IER_TXRDY);
				aic_disable(id);
				return TWID_TIMEOUT;
			}

#ifdef CONFIG_HAVE_TWI_FIFO
			if (desc->use_fifo)
				desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_FOUR_DATA;
#endif /* CONFIG_HAVE_TWI_FIFO */

			/* Start twi with send first byte */
			async_desc[adesc_index].transferred = 1;
			twi_enable_it(desc->addr, TWI_IER_TXRDY);
			twi_write_byte(desc->addr, buf->data[0]);
		} else {
#ifdef CONFIG_HAVE_TWI_FIFO
			if (desc->use_fifo)
				desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_FOUR_DATA;
#endif /* CONFIG_HAVE_TWI_FIFO */

			/* Enable read interrupt and start the transfer */
			twi_enable_it(desc->addr, TWI_IER_RXRDY);

			if (desc->flags & TWID_BUF_ATTR_START)
				twi_send_start_condition(desc->addr);
		}

		adesc_index = (adesc_index + 1) % MAX_ADESC;
		break;

	case TWID_MODE_POLLING:
		if (desc->flags & TWID_BUF_ATTR_WRITE)
			status = _twid_poll_write(desc, buf);
		else
			status = _twid_poll_read(desc, buf);

		if (status == TWID_SUCCESS && cb)
			cb(desc, user_args);
		mutex_unlock(&desc->mutex);
		break;

	case TWID_MODE_DMA:
		if (desc->flags & TWID_BUF_ATTR_WRITE)
			_twid_dma_write(desc, buf);
		else
			_twid_dma_read(desc, buf);
		break;

	default:
		trace_fatal("Unknown TWI transfer mode");
	}

	return status;
}

uint32_t twid_transfer(struct _twi_desc* desc, struct _buffer* buf, int buffers,
					   twid_callback_t cb, void* user_args)
{
	int b;
	uint32_t status;

	if (buf == NULL)
		return TWID_ERROR_TRANSFER;

	for (b = 0 ; b < buffers ; b++) {
		if ((buf[b].attr & (TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_READ)) == 0)
			return TWID_ERROR_TRANSFER;

		if ((buf[b].attr & (TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_READ)) == (TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_READ))
			return TWID_ERROR_DUPLEX;

		if (b == (buffers - 1))
			status = _twid_transfer(desc, &buf[b], cb, user_args);
		else
			status = _twid_transfer(desc, &buf[b], NULL, NULL);
		if (status)
			return status;
		twid_wait_transfer(desc);
	}

	return TWID_SUCCESS;
}

uint32_t twid_is_busy(const struct _twi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void twid_wait_transfer(const struct _twi_desc* desc)
{
	while (twid_is_busy(desc));
}
