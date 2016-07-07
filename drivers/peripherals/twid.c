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

#define TWID_DMA_THRESHOLD      16
#define TWID_TIMEOUT            100

#define MAX_ADESC               8

static struct _async_desc async_desc[MAX_ADESC];
static uint8_t adesc_index = 0;

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

static uint32_t _twid_wait_twi_transfer(struct _twi_desc* desc)
{
	struct _timeout timeout;
	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_transfer_complete(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Unable to complete transfert!\r\n");
			twid_configure(desc);
			return TWID_ERROR_TRANSFER;
		}
	}
	return TWID_SUCCESS;
}

static void _twid_dma_finish(struct dma_channel* channel, struct _twi_desc* desc)
{
	dma_free_channel(channel);

	if (desc->callback)
		desc->callback(desc, desc->cb_args);

	mutex_unlock(&desc->mutex);
}

static void _twid_dma_read_callback(struct dma_channel* channel, void* args)
{
	struct _twi_desc* desc = (struct _twi_desc *)args;
	cache_invalidate_region(desc->region_start, desc->region_length);
	_twid_dma_finish(channel, desc);
}

static void _twid_dma_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	uint32_t id = get_twi_id_from_addr(desc->addr);

	assert(id < ID_PERIPH_COUNT);

	memset(&desc->dma.rx.cfg, 0x0, sizeof(desc->dma.rx.cfg));

	desc->dma.rx.channel = dma_allocate_channel(id, DMA_PERIPH_MEMORY);
	assert(desc->dma.rx.channel);

	desc->dma.rx.cfg.sa = (void*)&desc->addr->TWI_RHR;
	desc->dma.rx.cfg.da = buffer->data;
	desc->dma.rx.cfg.upd_sa_per_data = 0;
	desc->dma.rx.cfg.upd_da_per_data = 1;
	desc->dma.rx.cfg.len = buffer->size;
	desc->dma.rx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_configure_transfer(desc->dma.rx.channel, &desc->dma.rx.cfg);
	dma_set_callback(desc->dma.rx.channel, _twid_dma_read_callback, (void*)desc);
	dma_start_transfer(desc->dma.rx.channel);
}

static void _twid_dma_write_callback(struct dma_channel* channel, void* args)
{
	struct _twi_desc* desc = (struct _twi_desc *)args;
	_twid_dma_finish(channel, desc);
}

static void _twid_dma_write(struct _twi_desc* desc, struct _buffer* buffer)
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
	desc->dma.tx.cfg.len = buffer->size;
	desc->dma.tx.cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_configure_transfer(desc->dma.tx.channel, &desc->dma.tx.cfg);
	dma_set_callback(desc->dma.tx.channel, _twid_dma_write_callback, (void*)desc);
	cache_clean_region(desc->region_start, desc->region_length);
	dma_start_transfer(desc->dma.tx.channel);
}

/*
 *
 */
static uint8_t _check_nack(Twi* addr)
{
	if (twi_get_status(addr) & TWI_SR_NACK) {
		trace_error("twid: command NACK\r\n");
		return TWID_ERROR_ACK;
	} else {
		return TWID_SUCCESS;
	}
}

/*
 *
 */
static uint8_t _check_rx_time_out(struct _twi_desc* desc)
{
	uint8_t status = TWID_SUCCESS;
	struct _timeout timeout;

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_byte_received(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Device doesn't answer (RX TIMEOUT)\r\n");
			status = TWID_ERROR_TIMEOUT;
			break;
		}
	}
	return status;
}

/*
 *
 */
static uint8_t _check_tx_time_out(struct _twi_desc* desc)
{
	uint8_t status = TWID_SUCCESS;
	struct _timeout timeout;

	timer_start_timeout(&timeout, desc->timeout);
	while (!twi_is_byte_sent(desc->addr)) {
		if (timer_timeout_reached(&timeout)) {
			trace_error("twid: Device doesn't answer (TX TIMEOUT)\r\n");
			status = TWID_ERROR_TIMEOUT;
			break;
		}
	}
	return status;
}

/*
 *
 */
static void _twid_handler(void)
{
	uint8_t i;
	uint32_t status = 0;
	Twi* addr;
	uint32_t id = aic_get_current_interrupt_identifier();

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
	addr = adesc->twi_desc.addr;
	status = twi_get_masked_status(addr);

	if (TWI_STATUS_RXRDY(status)) {
		adesc->pdata[adesc->transferred] = twi_read_byte(addr);
		adesc->transferred++;

		/* Only one byte remaining, send stop condition */
		if (adesc->transferred == (adesc->size - 1)) {
			twi_disable_it(addr, TWI_IDR_RXRDY);
			twi_enable_it(addr, TWI_IER_TXCOMP);
			twi_send_stop_condition(addr);
		}
	}
	else if (TWI_STATUS_TXRDY(status)) {

		/* Transfer finished ? */
		if (adesc->transferred == adesc->size) {
			twi_disable_it(addr, TWI_IDR_TXRDY);
			twi_enable_it(addr, TWI_IER_TXCOMP);
			twi_send_stop_condition(addr);
		}
		/* Bytes remaining */
		else {
			twi_write_byte(addr, adesc->pdata[adesc->transferred]);
			adesc->transferred++;
		}
	}
	/* Transfer complete*/
	else if (TWI_STATUS_TXCOMP(status)) {
		aic_disable(id);
		twi_disable_it(addr, TWI_IDR_RXRDY | TWI_IDR_RXRDY);
		twi_disable_it(addr, TWI_IDR_TXCOMP);
		adesc->pdata = 0;
		adesc->twi_id = 0;
		if (adesc->twi_desc.callback)
			adesc->twi_desc.callback(&adesc->twi_desc, adesc->twi_desc.cb_args);
		mutex_unlock(&adesc->twi_desc.mutex);
	}
}

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
	if (desc->transfert_mode == TWID_MODE_FIFO) {
		uint32_t fifo_depth = get_peripheral_fifo_depth(desc->addr);
		twi_fifo_configure(desc->addr, fifo_depth/2, fifo_depth/2,
		                   TWI_FMR_RXRDYM_ONE_DATA | TWI_FMR_TXRDYM_ONE_DATA);
	}
#endif

	desc->mutex = 0;
}

/*
 *
 */

#ifndef CONFIG_HAVE_TWI_ALTERNATE_CMD

static uint32_t _twid_poll_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i = 0;
	Twi* addr = desc->addr;

	/* Enable read interrupt and start the transfer */
	twi_start_read(addr, desc->slave_addr, desc->iaddr, desc->isize);

	if (buffer->size != 1) {
		/* get buffer_size-1 data */
		for (i = 0; i < buffer->size - 1; i++) {
			if (_check_rx_time_out(desc) != TWID_SUCCESS)
				break;
			buffer->data[i] = twi_read_byte(addr);
			if (_check_nack(addr) != TWID_SUCCESS)
			   return TWID_ERROR_ACK;
		}
	}
	/* Before receive last data, send stop */
	twi_send_stop_condition(addr);

	if (_check_nack(addr) != TWID_SUCCESS)
		return TWID_ERROR_ACK;
	if (_check_rx_time_out(desc) != TWID_SUCCESS)
		return TWID_ERROR_TIMEOUT;
	buffer->data[i] = twi_read_byte(addr);
	/* wait transfert to be finished */
	return _twid_wait_twi_transfer(desc);
}

static uint32_t _twid_poll_write(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i = 0;
	Twi* addr = desc->addr;

	/* Start twi with send first byte */
	twi_start_write(addr, desc->slave_addr, desc->iaddr, desc->isize, buffer->data[0]);

	/* If only one byte send stop immediatly */
	if (buffer->size == 1)
		twi_send_stop_condition(addr);

	if (_check_nack(addr) != TWID_SUCCESS)
		return TWID_ERROR_ACK;

	for (i = 1; i < buffer->size; i++) {
		if (_check_tx_time_out(desc) != TWID_SUCCESS)
			break;
		twi_write_byte(addr, buffer->data[i]);
		if (_check_nack(addr) != TWID_SUCCESS)
			return TWID_ERROR_ACK;
	}
	/* Finally send stop if more than 1 byte to send */
	if (buffer->size != 1)
		twi_send_stop_condition(addr);

	/* wait transfert to be finished */
	return _twid_wait_twi_transfer(desc);
}

#else /* CONFIG_HAVE_TWI_ALTERNATE_CMD */

static uint32_t _twid_poll_read(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i = 0;
	Twi* addr = desc->addr;

	twi_init_read_transfert(desc->addr, desc->slave_addr, desc->iaddr,
	                        desc->isize, buffer->size);

	if (_check_nack(addr) != TWID_SUCCESS)
		return TWID_ERROR_ACK;

	for (i = 0; i < buffer->size; i++) {
		if (_check_rx_time_out(desc) != TWID_SUCCESS)
				break;
		buffer->data[i] = twi_read_byte(desc->addr);
		if (_check_nack(addr) != TWID_SUCCESS)
			return TWID_ERROR_ACK;
	}

	/* wait for transfert to finish */
	return _twid_wait_twi_transfer(desc);
}

static uint32_t _twid_poll_write(struct _twi_desc* desc, struct _buffer* buffer)
{
	int i = 0;
	Twi* addr = desc->addr;

	twi_init_write_transfert(desc->addr, desc->slave_addr, desc->iaddr,
	                         desc->isize, buffer->size);

	if (_check_nack(addr) != TWID_SUCCESS)
		return TWID_ERROR_ACK;

	for (i = 0; i < buffer->size; i++) {
		if (_check_tx_time_out(desc) != TWID_SUCCESS)
			break;
		twi_write_byte(desc->addr, buffer->data[i]);
		if (_check_nack(addr) != TWID_SUCCESS)
			return TWID_ERROR_ACK;
	}

	/* wait for transfert to finish */
	return _twid_wait_twi_transfer(desc);
}

#endif /* CONFIG_HAVE_TWI_ALTERNATE_CMD */

/*
 *
 */
uint32_t twid_transfert(struct _twi_desc* desc, struct _buffer* rx, struct _buffer* tx, twid_callback_t cb, void* user_args)
{
	uint32_t status = TWID_SUCCESS;
	uint32_t id;
	uint8_t tmode;

	if (rx != NULL && tx != NULL)
		return TWID_ERROR_DUPLEX;

	if (!mutex_try_lock(&desc->mutex))
		return TWID_ERROR_LOCK;

	desc->callback = cb;
	desc->cb_args = user_args;

	tmode = desc->transfert_mode;

	/* Check if only one char to send or receive */
	if (tmode == TWID_MODE_ASYNC) {
		if ((tx && tx->size == 1) || (rx && rx->size == 1))
			tmode = TWID_MODE_POLLING;
	}

	switch (tmode) {

	case TWID_MODE_ASYNC:
		/* Copy descriptor to async descriptor */
		async_desc[adesc_index].twi_desc = *desc;
		/* Init param used by interrupt handler */
		async_desc[adesc_index].pdata = NULL;
		id = get_twi_id_from_addr(desc->addr);
		async_desc[adesc_index].twi_id = id;

		/* Set TWI handler */
		aic_set_source_vector(id, _twid_handler);
		/* Enable TWI interrupt */
		aic_enable(id);

		if (tx) {
			/* Set buffer data info to async descriptor */
			/* pnt+1 and size-1 because first data sent directly */
			async_desc[adesc_index].pdata = &tx->data[1];
			async_desc[adesc_index].size = tx->size - 1;
			/* Start twi with send first byte */
			twi_enable_it(desc->addr, TWI_IER_TXRDY);
			twi_start_write(desc->addr, desc->slave_addr, desc->iaddr, desc->isize, tx->data[0]);
		} else {
			/* Set buffer data info to async descriptor */
			async_desc[adesc_index].pdata = rx->data;
			async_desc[adesc_index].size = rx->size;
			/* Enable read interrupt and start the transfer */
			twi_enable_it(desc->addr, TWI_IER_RXRDY);
			twi_start_read(desc->addr, desc->slave_addr, desc->iaddr, desc->isize);
		}

		adesc_index = (adesc_index+1)% MAX_ADESC;
		break;


	case TWID_MODE_POLLING:
		if (tx) {
			status = _twid_poll_write(desc, tx);
		} else {
			status = _twid_poll_read(desc, rx);
		}
		if (status == TWID_SUCCESS && cb)
			cb(desc, user_args);
		mutex_unlock(&desc->mutex);
		break;

	case TWID_MODE_DMA:
		if (tx) {
			if (tx->size < TWID_DMA_THRESHOLD) {
				status = _twid_poll_write(desc, tx);
				if (status == TWID_SUCCESS && cb)
					cb(desc, user_args);
				mutex_unlock(&desc->mutex);
			} else {
#ifdef CONFIG_HAVE_TWI_ALTERNATE_CMD
				twi_init_write_transfert(desc->addr,
							 desc->slave_addr,
							 desc->iaddr,
							 desc->isize,
							 tx->size);
#endif
				desc->region_start = tx->data;
				desc->region_length = tx->size;
				_twid_dma_write(desc, tx);
			}
		} else {
			if (rx->size < TWID_DMA_THRESHOLD) {
				status = _twid_poll_read(desc, rx);
				if (status == TWID_SUCCESS && cb)
					cb(desc, user_args);
				mutex_unlock(&desc->mutex);
			} else {

#ifdef CONFIG_HAVE_TWI_ALTERNATE_CMD
				twi_init_read_transfert(desc->addr,
							desc->slave_addr,
							desc->iaddr,
							desc->isize,
							rx->size);
#endif
				desc->region_start = rx->data;
				desc->region_length = rx->size;
				status = _check_nack(desc->addr);
				if (status != TWID_SUCCESS) {
					mutex_unlock(&desc->mutex);
					break;
				}
				_twid_dma_read(desc, rx);
			}
		}
		break;

#ifdef CONFIG_HAVE_TWI_FIFO
	case TWID_MODE_FIFO:
		if (tx) {
			status = twi_write_stream(desc->addr, desc->slave_addr,
						  desc->iaddr, desc->isize,
						  tx->data, tx->size, desc->timeout);
			status = status ? TWID_SUCCESS : TWID_ERROR_ACK;
			if (status)
				break;
			status = _twid_wait_twi_transfer(desc);
			if (status)
				break;
		} else {
			status = twi_read_stream(desc->addr, desc->slave_addr,
						 desc->iaddr, desc->isize,
						 rx->data, rx->size, desc->timeout);
			status = status ? TWID_SUCCESS : TWID_ERROR_ACK;
			if (status)
				break;
			status = _twid_wait_twi_transfer(desc);
			if (status)
				break;
		}
		if (cb != NULL)
			cb(desc, user_args);
		mutex_unlock(&desc->mutex);
		break;
#endif

	default:
		trace_debug("Unknown mode");
	}

	return status;
}

uint32_t twid_is_busy(const struct _twi_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void twid_wait_transfert(const struct _twi_desc* desc)
{
	while (twid_is_busy(desc));
}
