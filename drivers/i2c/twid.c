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
#include <string.h>

#include "callback.h"
#include "dma/dma.h"
#include "errno.h"
#include "i2c/twi.h"
#include "i2c/twid.h"
#include "io.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/bus.h"
#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/pmc.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define TWID_POLLING_THRESHOLD  16
#define TWID_TIMEOUT            100

/** \brief twi asynchronous transfer descriptor.*/
struct _async_desc
{
	bool master;
	union {
		struct _twi_desc *twi_desc;
		struct _twi_slave_desc *twi_slave_desc;
	};
	uint32_t twi_id;
	struct _buffer buf;
	uint32_t transferred; /**< Number of already transferred bytes. */
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _async_desc async_desc[TWI_IFACE_COUNT];
static uint8_t adesc_index = 0;

/*----------------------------------------------------------------------------
 *        Local functions
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
			twid_configure(desc);
			return true;
		}

		return false;
	}
#endif

	if (twi_get_status(desc->addr) & TWI_SR_NACK) {
		trace_error("twid: command NACK\r\n");
		twid_configure(desc);
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
			twid_configure(desc);
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
			twid_configure(desc);
			return true;
		}
	}

	return false;
}

static int _twid_wait_twi_transfer(struct _twi_desc* desc)
{
	struct _timeout timeout;

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_transfer_complete(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Unable to complete transfer!\r\n");
			twid_configure(desc);
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int _twid_dma_read_callback(void* arg, void* arg2)
{
	struct _twi_desc* desc = (struct _twi_desc *)arg;

	cache_invalidate_region(desc->dma.rx.cfg.daddr, desc->dma.rx.cfg.len);

	dma_reset_channel(desc->dma.rx.channel);

	if (_check_rx_timeout(desc)) {
		mutex_unlock(&desc->mutex);
		return -ETIMEDOUT;
	}

	if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
		twi_send_stop_condition(desc->addr);

#ifdef CONFIG_HAVE_FIFO
	if (!desc->use_fifo)
#endif
	{
		((uint8_t*)desc->dma.rx.cfg.daddr)[desc->dma.rx.cfg.len] = twi_read_byte(desc->addr);

		if (_check_rx_timeout(desc)) {
			mutex_unlock(&desc->mutex);
			return -ETIMEDOUT;
		}

		((uint8_t*)desc->dma.rx.cfg.daddr)[desc->dma.rx.cfg.len + 1] = twi_read_byte(desc->addr);
	}

	mutex_unlock(&desc->mutex);

	callback_call(&desc->callback, NULL);

	return 0;
}

static void _twid_dma_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	struct _callback _cb;
	uint32_t id = get_twi_id_from_addr(desc->addr);

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.cfg.saddr = (void*)&desc->addr->TWI_RHR;
	desc->dma.rx.cfg.daddr = buffer->data;

	if(!desc->dma.rx.channel)
		desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo) {
		if ((buffer->size % 4) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_FOUR_DATA;
			desc->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
		} else if ((buffer->size % 2) == 0)  {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_TWO_DATA;
			desc->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_HALF_WORD;
		} else {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_ONE_DATA;
			desc->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
		}
		desc->dma.rx.cfg.len = buffer->size;
	} else {
		desc->dma.rx.cfg.len = buffer->size - 2;
		desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_RXRDYM_Msk) | TWI_FMR_RXRDYM_ONE_DATA;
		desc->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	}
#else
	desc->dma.rx.cfg.len = buffer->size - 2;
	desc->dma.rx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
#endif
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg_dma, &desc->dma.rx.cfg, 1);
	callback_set(&_cb, _twid_dma_read_callback, (void*)desc);
	dma_set_callback(desc->dma.rx.channel, &_cb);
	dma_start_transfer(desc->dma.rx.channel);

	if (desc->flags & BUS_I2C_BUF_ATTR_START)
		twi_send_start_condition(desc->addr);
}

static int _twid_dma_write_callback(void* arg, void* arg2)
{
	struct _twi_desc* desc = (struct _twi_desc *)arg;

	dma_reset_channel(desc->dma.tx.channel);

	if (_check_tx_timeout(desc)) {
		mutex_unlock(&desc->mutex);
		return -ETIMEDOUT;
	}

	if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
		twi_send_stop_condition(desc->addr);

#ifdef CONFIG_HAVE_TWI_FIFO
	if (!desc->use_fifo)
		twi_write_byte(desc->addr, ((uint8_t *)desc->dma.tx.cfg.saddr)[desc->dma.tx.cfg.len]);
#endif

	mutex_unlock(&desc->mutex);

	callback_call(&desc->callback, NULL);

	return 0;
}

static void _twid_dma_write(struct _twi_desc* desc, struct _buffer* buffer)
{
	struct _callback _cb;
	uint32_t id = get_twi_id_from_addr(desc->addr);

	memset(&desc->dma.tx.cfg, 0x0, sizeof(desc->dma.tx.cfg));

	if(!desc->dma.tx.channel)
		desc->dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
	assert(desc->dma.tx.channel);

	desc->dma.tx.cfg.saddr = buffer->data;
	desc->dma.tx.cfg.daddr = (void*)&desc->addr->TWI_THR;
#ifdef CONFIG_HAVE_TWI_FIFO
	if (desc->use_fifo) {
		if ((buffer->size % 4) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_FOUR_DATA;
			desc->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
		} else if ((buffer->size % 2) == 0) {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_TWO_DATA;
			desc->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_HALF_WORD;
		} else {
			desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_ONE_DATA;
			desc->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
		}
		desc->dma.tx.cfg.len = buffer->size;
	} else {
		desc->addr->TWI_FMR = (desc->addr->TWI_FMR & ~TWI_FMR_TXRDYM_Msk) | TWI_FMR_TXRDYM_ONE_DATA;
		desc->dma.tx.cfg.len = buffer->size - 1;
		desc->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	}
#else
	desc->dma.tx.cfg.len = buffer->size - 1;
	desc->dma.tx.cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
#endif
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg_dma, &desc->dma.tx.cfg, 1);
	callback_set(&_cb, _twid_dma_write_callback, (void*)desc);
	dma_set_callback(desc->dma.tx.channel, &_cb);
	cache_clean_region(desc->dma.tx.cfg.saddr, desc->dma.tx.cfg.len);
	dma_start_transfer(desc->dma.tx.channel);
}

/*
 *
 */
static void _twid_handler(uint32_t source, void* user_arg)
{
	uint32_t status = 0;
	Twi* addr;
	uint32_t buf_size;
	bool use_fifo = false;
	struct _async_desc* adesc = (struct _async_desc*)user_arg;

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
			if (adesc->twi_desc->flags & BUS_I2C_BUF_ATTR_STOP)
				twi_send_stop_condition(addr);

		if (adesc->transferred == adesc->buf.size) {
			twi_disable_it(addr, TWI_IDR_RXRDY);
			if (adesc->twi_desc->flags & BUS_I2C_BUF_ATTR_STOP) {
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
				if (adesc->twi_desc->flags & BUS_I2C_BUF_ATTR_STOP)
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
				if (adesc->twi_desc->flags & BUS_I2C_BUF_ATTR_STOP)
					twi_send_stop_condition(addr);

			twi_write_byte(addr, adesc->buf.data[adesc->transferred]);
			adesc->transferred++;
		}

		if (adesc->transferred >= adesc->buf.size){
			twi_disable_it(addr, TWI_IDR_TXRDY);
			if (adesc->twi_desc->flags & BUS_I2C_BUF_ATTR_STOP) {
				twi_enable_it(addr, TWI_IER_TXCOMP);
			} else {
				adesc->twi_id = 0;
				mutex_unlock(&adesc->twi_desc->mutex);
			}
		}
	}
	/* Transfer complete*/
	else if (TWI_STATUS_TXCOMP(status)) {
		irq_disable(adesc->twi_id);
		twi_disable_it(addr, TWI_IDR_TXCOMP);
		adesc->twi_id = 0;
		mutex_unlock(&adesc->twi_desc->mutex);
		callback_call(&adesc->twi_desc->callback, NULL);
	}
}

/*
 *
 */
static int _twid_poll_read(struct _twi_desc* desc, struct _buffer* buffer)
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

	if (desc->flags & BUS_I2C_BUF_ATTR_START)
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
				return -ECONNABORTED;
		}
#endif /* CONFIG_HAVE_TWI_FIFO */
	} else {
		for (i = 0 ; i < size ; i++) {
			if (_check_rx_timeout(desc))
				break;

			buffer->data[i] = twi_read_byte(addr);

			if (_check_nack(desc))
				return -ECONNABORTED;
		}
	}

	/* Before receive last data, send stop */
	if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
		twi_send_stop_condition(addr);

	if ((size == (buffer->size - 1)) || (size == 0)) {
		if (_check_rx_timeout(desc))
			return -ETIMEDOUT;
		buffer->data[i] = twi_read_byte(addr);
	}

	/* wait transfer to be finished */
	if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
		return _twid_wait_twi_transfer(desc);
	return 0;
}

static int _twid_poll_write(struct _twi_desc* desc, struct _buffer* buffer)
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
		if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
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
				return -ECONNABORTED;
		}
#endif /* CONFIG_HAVE_TWI_FIFO */
	} else {
		for (i = 0 ; i < size ; i++) {
			if (_check_tx_timeout(desc))
				break;
			twi_write_byte(desc->addr, buffer->data[i]);

			if (_check_nack(desc))
				return -ECONNABORTED;
		}
	}

	if (buffer->size > 1)
		if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
			twi_send_stop_condition(desc->addr);

	if (size == (buffer->size - 1)) {
		if (_check_tx_timeout(desc))
			return -ETIMEDOUT;
		twi_write_byte(desc->addr, buffer->data[i]);
		while(!twi_is_byte_sent(desc->addr));
	}

	/* wait transfer to be finished */
	if (desc->flags & BUS_I2C_BUF_ATTR_STOP)
		return _twid_wait_twi_transfer(desc);
	return 0;
}

#ifdef CONFIG_HAVE_TWI_FIFO

static void twid_fifo_configure(struct _twi_desc *desc)
{
	desc->fifo.rx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.rx.threshold = desc->fifo.rx.size / 2;
	desc->fifo.tx.size = get_peripheral_fifo_depth(desc->addr);
	desc->fifo.tx.threshold = desc->fifo.tx.size / 2;
	twi_fifo_configure(desc->addr, desc->fifo.tx.threshold, desc->fifo.rx.threshold,
			   TWI_FMR_RXRDYM_FOUR_DATA | TWI_FMR_TXRDYM_FOUR_DATA);
}

#endif /* CONFIG_HAVE_TWI_FIFO */

static void _twid_slave_handler(uint32_t source, void* user_arg)
{
	uint32_t status;
	Twi* twi;
	struct _twi_slave_desc *desc;
	struct _async_desc* adesc = (struct _async_desc*)user_arg;

	desc = adesc->twi_slave_desc;
	twi = adesc->twi_slave_desc->twi;
	status = twi_get_status(twi);

	if (TWI_STATUS_GACC(status))
		return;

	if (TWI_STATUS_EOSACC(status) || TWI_STATUS_TXCOMP(status)) {
		twi_disable_it(twi, TWI_IDR_RXRDY | TWI_IDR_TXRDY | TWI_IER_TXCOMP);

		if (desc->state == TWID_SLAVE_STATE_STARTED) {
			desc->state = TWID_SLAVE_STATE_STOPPED;
			if (desc->ops->on_stop)
				desc->ops->on_stop();
		}

		twi_enable_it(desc->twi, TWI_IER_SVACC);
	}
	else if (TWI_STATUS_SVACC(status)) {
		if (desc->state == TWID_SLAVE_STATE_STOPPED) {
			twi_disable_it(twi, TWI_IDR_SVACC);

			desc->state = TWID_SLAVE_STATE_STARTED;

			if (desc->ops->on_start)
				desc->ops->on_start();
		}

		if (TWI_STATUS_SVREAD(status)) {
			twi_disable_it(twi, TWI_IER_RXRDY);
			twi_enable_it(twi, TWI_IER_TXRDY | TWI_IER_TXCOMP);

			if (TWI_STATUS_TXRDY(status) && !TWI_STATUS_NACK(status)) {
				int16_t err = -1;
				if (desc->ops->on_write)
					err = desc->ops->on_write();
				if (err > 0)
					twi_write_byte(twi, err);
			}
		} else {
			twi_disable_it(twi, TWI_IER_TXRDY);
			twi_enable_it(twi, TWI_IER_RXRDY | TWI_IER_TXCOMP);

			if (TWI_STATUS_RXRDY(status)) {
				int16_t err = -1;
				if (desc->ops->on_read)
					err = desc->ops->on_read(twi_read_byte(twi));
				if (err > 0)
					twi_write_byte(twi, err);
			}
		}
	}

}

/*
 *
 */
static int _twid_transfer(struct _twi_desc* desc, struct _buffer* buf,  struct _callback* cb)
{
	int err = 0;
	uint32_t id;
	uint8_t tmode;

	if (!mutex_try_lock(&desc->mutex))
		return -EBUSY;

	callback_copy(&desc->callback, cb);
	desc->flags = buf->attr;
	tmode = desc->transfer_mode;

	/* If short transfer detected, use POLLING mode */
	if (tmode != BUS_TRANSFER_MODE_POLLING) {
		if (buf->size < TWID_POLLING_THRESHOLD)
			tmode = BUS_TRANSFER_MODE_POLLING;
	}

	if (desc->flags & BUS_I2C_BUF_ATTR_START) {
		if (desc->flags & BUS_BUF_ATTR_TX) {
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
	case BUS_TRANSFER_MODE_ASYNC:
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
		irq_add_handler(id, _twid_handler, &async_desc[adesc_index]);
		/* Enable TWI interrupt */
		irq_enable(id);

		if (desc->flags & BUS_BUF_ATTR_TX) {
			if (_check_tx_timeout(desc)) {
				twi_disable_it(desc->addr, TWI_IER_TXRDY);
				irq_disable(id);
				return -ETIMEDOUT;
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

			if (desc->flags & BUS_I2C_BUF_ATTR_START)
				twi_send_start_condition(desc->addr);
		}

		adesc_index = (adesc_index + 1) % TWI_IFACE_COUNT;
		break;

	case BUS_TRANSFER_MODE_POLLING:
		if (desc->flags & BUS_BUF_ATTR_TX)
			err = _twid_poll_write(desc, buf);
		else
			err = _twid_poll_read(desc, buf);

		if (err == 0)
			callback_call(&desc->callback, NULL);
		mutex_unlock(&desc->mutex);
		break;

	case BUS_TRANSFER_MODE_DMA:
		if (desc->flags & BUS_BUF_ATTR_TX)
			_twid_dma_write(desc, buf);
		else
			_twid_dma_read(desc, buf);
		break;

	default:
		trace_error("Unknown TWI transfer mode");
		err = -ENOTSUP;
	}

	return err;
}

/*----------------------------------------------------------------------------
 *        External functions
 *----------------------------------------------------------------------------*/

int twid_configure(struct _twi_desc* desc)
{
	uint32_t id = get_twi_id_from_addr(desc->addr);
	assert(id < ID_PERIPH_COUNT);

	if (desc->timeout == 0)
		desc->timeout = TWID_TIMEOUT;

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(get_twi_id_from_addr(desc->addr));
	if (flexcom)
		flexcom_select(flexcom, FLEX_MR_OPMODE_TWI);
#endif

	pmc_configure_peripheral(id, NULL, true);
	twi_configure_master(desc->addr, desc->freq);
#ifdef CONFIG_HAVE_TWI_FIFO
	twid_fifo_configure(desc);
	if (desc->use_fifo)
		twi_fifo_enable(desc->addr, true);
#endif

	if(desc->dma.rx.channel) {
		dma_stop_transfer(desc->dma.rx.channel);
		dma_free_channel(desc->dma.rx.channel);
		desc->dma.rx.channel = NULL;
	}
	desc->dma.rx.cfg_dma.incr_saddr = false;
	desc->dma.rx.cfg_dma.incr_daddr = true;
	desc->dma.rx.cfg_dma.loop = false;
	desc->dma.rx.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	if(desc->dma.tx.channel) {
		dma_stop_transfer(desc->dma.tx.channel);
		dma_free_channel(desc->dma.tx.channel);
		desc->dma.tx.channel = NULL;
	}
	desc->dma.tx.cfg_dma.incr_saddr = true;
	desc->dma.tx.cfg_dma.incr_daddr = false;
	desc->dma.tx.cfg_dma.loop = false;
	desc->dma.tx.cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	desc->mutex = 0;

	return 0;
}

int twid_slave_configure(struct _twi_slave_desc *desc, struct _twi_slave_ops* ops)
{
	uint32_t twi_id = get_twi_id_from_addr(desc->twi);

	irq_disable(twi_id);
	twi_disable_it(desc->twi, 0xffffffff);

	desc->ops = ops;
	desc->state = TWID_SLAVE_STATE_STOPPED;

	async_desc[adesc_index].twi_id = twi_id;
	async_desc[adesc_index].twi_slave_desc = desc;

#ifdef CONFIG_HAVE_FLEXCOM
	Flexcom* flexcom = get_flexcom_addr_from_id(get_twi_id_from_addr(desc->twi));
	if (flexcom)
		flexcom_select(flexcom, FLEX_MR_OPMODE_TWI);
#endif

	/* Configure TWI slave */
	pmc_configure_peripheral(twi_id, NULL, true);
	twi_configure_slave(desc->twi, desc->addr);
	irq_add_handler(twi_id, _twid_slave_handler, &async_desc[adesc_index]);
	twi_enable_it(desc->twi, TWI_IER_SVACC | TWI_IER_EOSACC);
	irq_enable(twi_id);

	adesc_index = (adesc_index + 1) % TWI_IFACE_COUNT;

	return 0;
}

int twid_transfer(struct _twi_desc* desc, struct _buffer* buf, int buffers, struct _callback* cb)
{
	int b;
	int err;

	if (buf == NULL)
		return -EINVAL;

	for (b = 0 ; b < buffers ; b++) {
		if ((buf[b].attr & (BUS_BUF_ATTR_TX | BUS_BUF_ATTR_RX)) == 0)
			return -EINVAL;

		if ((buf[b].attr & (BUS_BUF_ATTR_TX | BUS_BUF_ATTR_RX)) == (BUS_BUF_ATTR_TX | BUS_BUF_ATTR_RX))
			return -EINVAL;

		if (b == (buffers - 1)) {
			err = _twid_transfer(desc, &buf[b], cb);
		} else {
#if defined(CONFIG_SOC_SAM9XX5) || defined(CONFIG_SOC_SAMA5D3)
			/* workaround for IP versions that do not support manual restart */
			if (buf[b + 1].attr & BUS_I2C_BUF_ATTR_START)
				buf[b].attr |= BUS_I2C_BUF_ATTR_STOP;
#endif
			err = _twid_transfer(desc, &buf[b], NULL);
		}
		if (err < 0)
			return err;
		twid_wait_transfer(desc);
	}

	return 0;
}

bool twid_is_busy(const struct _twi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void twid_wait_transfer(const struct _twi_desc* desc)
{
	while (twid_is_busy(desc)) {
		if (desc->transfer_mode == BUS_TRANSFER_MODE_DMA)
			dma_poll();
	}
}
