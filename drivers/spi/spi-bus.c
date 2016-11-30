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

#include "spi-bus.h"
#include "spi/spid.h"
#include "spi/spi.h"
#include "board.h"

#include "trace.h"

#include <string.h>
#include <assert.h>

static struct _spi_bus_desc _spi_bus[SPI_IFACE_COUNT];

static void spi_bus_callback(void *args)
{
	uint8_t bus_id = *(uint8_t *)args;

	if (bus_id >= SPI_IFACE_COUNT)
		return;

	if (_spi_bus[bus_id].callback)
		_spi_bus[bus_id].callback(_spi_bus[bus_id].cb_args);

	mutex_unlock(&_spi_bus[bus_id].mutex);
}

int32_t spi_bus_configure(uint8_t bus_id, Spi *iface, enum _spid_trans_mode mode)
{
	assert(bus_id < SPI_IFACE_COUNT);

	memset(&_spi_bus[bus_id], 0, sizeof(_spi_bus[bus_id]));
	_spi_bus[bus_id].spid.addr = iface;
	_spi_bus[bus_id].spid.transfer_mode = mode;

	spid_configure(&_spi_bus[bus_id].spid);
	spid_configure_master(&_spi_bus[bus_id].spid, true);

	return 0;
}

void spi_bus_configure_cs(uint8_t bus_id, uint8_t cs, uint32_t bitrate, uint32_t dlybs, uint32_t dlybct,
						  enum _spid_mode mode)
{
	assert(bus_id < SPI_IFACE_COUNT);
	spid_configure_cs(&_spi_bus[bus_id].spid, cs, bitrate, dlybs, dlybct, mode);
}

int32_t spi_bus_transfer(uint8_t bus_id, uint8_t cs, struct _buffer *buf, uint16_t buffers,
						 spi_bus_callback_t cb, void *user_args)
{
	uint32_t status;

	assert(bus_id < SPI_IFACE_COUNT);

	if (buffers == 0)
		return SPID_SUCCESS;

	if (!mutex_is_locked(&_spi_bus[bus_id].transaction)) {
		trace_error("-W- spi_bus: no opened transaction on the bus.");
		return SPID_ERROR_LOCK;
	}
	if (!mutex_try_lock(&_spi_bus[bus_id].mutex))
		return SPID_ERROR_LOCK;

	_spi_bus[bus_id].spid.chip_select = cs;
	_spi_bus[bus_id].callback = cb;
	_spi_bus[bus_id].cb_args = user_args;

	status = spid_transfer(&_spi_bus[bus_id].spid, buf, buffers, spi_bus_callback, (void *)&bus_id);
	if (status) {
		mutex_unlock(&_spi_bus[bus_id].mutex);
		return status;
	}
	spid_wait_transfer(&_spi_bus[bus_id].spid);

	return status;
}

bool spi_bus_is_busy(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

	return mutex_is_locked(&_spi_bus[bus_id].mutex);
}

void spi_bus_wait_transfer(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

	while (spi_bus_is_busy(bus_id));
}

int32_t spi_bus_start_transaction(const uint8_t bus_id)
{
	return mutex_try_lock(&_spi_bus[bus_id].transaction);
}

int32_t spi_bus_stop_transaction(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

	mutex_unlock(&_spi_bus[bus_id].transaction);
	return 0;
}

bool spi_bus_transaction_pending(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

	return mutex_is_locked(&_spi_bus[bus_id].transaction);
}

enum _spid_trans_mode spi_bus_get_transfer_mode(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

	return _spi_bus[bus_id].spid.transfer_mode;
}

void spi_bus_set_transfer_mode(const uint8_t bus_id, enum _spid_trans_mode mode)
{
	assert(bus_id < SPI_IFACE_COUNT);
	assert(mode == SPID_MODE_POLLING ||
	       mode == SPID_MODE_DMA ||
	       mode == SPID_MODE_ASYNC);

	_spi_bus[bus_id].spid.transfer_mode = mode;
}

void spi_bus_set_cs_bitrate(const uint8_t bus_id, uint8_t cs, uint32_t bitrate)
{
	assert(bus_id < SPI_IFACE_COUNT);

	spid_set_cs_bitrate(&_spi_bus[bus_id].spid, cs, bitrate);
}


void spi_bus_fifo_enable(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

#ifdef CONFIG_HAVE_SPI_FIFO
	_spi_bus[bus_id].spid.use_fifo = true;
#endif
}

void spi_bus_fifo_disable(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

#ifdef CONFIG_HAVE_SPI_FIFO
	_spi_bus[bus_id].spid.use_fifo = false;
#endif
}

bool spi_bus_fifo_is_enabled(const uint8_t bus_id)
{
	assert(bus_id < SPI_IFACE_COUNT);

#ifdef CONFIG_HAVE_SPI_FIFO
	return _spi_bus[bus_id].spid.use_fifo;
#else
	return false;
#endif
}
