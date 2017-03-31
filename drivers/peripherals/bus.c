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
 *         Headers
 *----------------------------------------------------------------------------*/

#include <string.h>

#include "callback.h"
#include "dma/dma.h"
#include "errno.h"
#include "peripherals/bus.h"
#ifdef CONFIG_HAVE_BUS_SPI
#include "spi/spid.h"
#endif
#ifdef CONFIG_HAVE_BUS_I2C
#include "i2c/twid.h"
#endif
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define O_BLOCK (0x01)

struct _bus_desc {
	enum _bus_type type;
	union {
		uint32_t dummy;
#ifdef CONFIG_HAVE_SPI_BUS
		struct _spi_desc spid;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
		struct _twi_desc twid;
#endif
	} iface;

	enum _bus_transfer_mode transfer_mode;

	uint32_t options;

	uint32_t timeout;

	struct _callback callback;

	struct {
		mutex_t lock;
		mutex_t transaction;
	} mutex;
};

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _bus_desc _bus[BUS_COUNT];

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static int _bus_callback(void* arg, void* arg2)
{
	uint32_t bus_id = (uint32_t)arg;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	mutex_unlock(&_bus[bus_id].mutex.lock);

	return callback_call(&_bus[bus_id].callback, NULL);
}

static int _bus_fifo_enable(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
#ifdef CONFIG_HAVE_SPI_FIFO
		_bus[bus_id].iface.spid.use_fifo = true;
#endif
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
#ifdef CONFIG_HAVE_TWI_FIFO
		_bus[bus_id].iface.twid.use_fifo = true;
#endif
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_fifo_disable(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
#ifdef CONFIG_HAVE_SPI_FIFO
		_bus[bus_id].iface.spid.use_fifo = false;
#endif
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
#ifdef CONFIG_HAVE_TWI_FIFO
		_bus[bus_id].iface.twid.use_fifo = false;
#endif
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_fifo_is_enabled(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
#ifdef CONFIG_HAVE_SPI_FIFO
		err = _bus[bus_id].iface.spid.use_fifo;
#endif
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
#ifdef CONFIG_HAVE_TWI_FIFO
		err = _bus[bus_id].iface.twid.use_fifo;
#endif
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_enable(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_disable(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_get_transfer_mode(uint8_t bus_id)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		return _bus[bus_id].iface.spid.transfer_mode;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		return _bus[bus_id].iface.twid.transfer_mode;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static int _bus_set_transfer_mode(uint8_t bus_id, enum _bus_transfer_mode mode)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		_bus[bus_id].iface.spid.transfer_mode = mode;
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		_bus[bus_id].iface.twid.transfer_mode = mode;
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

int bus_configure(uint8_t bus_id, const struct _bus_iface* iface)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	memset(&_bus[bus_id], 0, sizeof(_bus[bus_id]));
	_bus[bus_id].transfer_mode = iface->transfer_mode;
	_bus[bus_id].options = O_BLOCK;
	_bus[bus_id].type = iface->type;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		_bus[bus_id].iface.spid.addr = iface->spi.hw;
		_bus[bus_id].iface.spid.transfer_mode = iface->transfer_mode;

		spid_configure(&_bus[bus_id].iface.spid);
		spid_configure_master(&_bus[bus_id].iface.spid, true);
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		_bus[bus_id].iface.twid.addr = iface->i2c.hw;
		_bus[bus_id].iface.twid.transfer_mode = iface->transfer_mode;
		_bus[bus_id].iface.twid.freq = iface->i2c.freq;

		twid_configure(&_bus[bus_id].iface.twid);
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	bus_ioctl(bus_id, BUS_IOCTL_ENABLE, NULL);

	return err;
}

int bus_configure_slave(uint8_t bus_id, const struct _bus_dev_cfg* cfg)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		spid_configure_cs(&_bus[bus_id].iface.spid,
		                  cfg->spi_dev.chip_select,
		                  cfg->spi_dev.bitrate,
		                  cfg->spi_dev.delay.bs,
		                  cfg->spi_dev.delay.bct,
		                  cfg->spi_dev.spi_mode);
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}

int bus_ioctl(uint8_t bus_id, int req, void* arg)
{
	int err = 0;

	if (bus_id >= BUS_COUNT)
		return -EINVAL;

	switch (req) {
	case BUS_IOCTL_ENABLE:
		err = _bus_enable(bus_id);
		break;
	case BUS_IOCTL_DISABLE:
		err = _bus_disable(bus_id);
		break;
	case BUS_IOCTL_ENABLE_FIFO:
		err = _bus_fifo_enable(bus_id);
		break;
	case BUS_IOCTL_DISABLE_FIFO:
		err = _bus_fifo_disable(bus_id);
		break;
	case BUS_IOCTL_GET_FIFO_STATUS:
		err = _bus_fifo_is_enabled(bus_id);
		if (err >= 0) {
			*(bool*)arg = err;
			err = 0;
		}
		break;
	case BUS_IOCTL_SET_TRANSFER_MODE:
		err = _bus_set_transfer_mode(bus_id, *(enum _bus_transfer_mode*)arg);
		break;
	case BUS_IOCTL_GET_TRANSFER_MODE:
		err = _bus_get_transfer_mode(bus_id);
		if (err >= 0)
			*(enum _bus_transfer_mode*)arg = (enum _bus_transfer_mode)err;
		break;
	case BUS_IOCTL_SET_TIMEOUT:
		_bus[bus_id].timeout = *(uint32_t*)arg;
		break;

	default:
		err = -EINVAL;
		break;
	}

	return err;
}

int bus_transfer(uint8_t bus_id, uint16_t remote, struct _buffer* buf, uint16_t buffers, struct _callback* cb)
{
	int err = 0;
	struct _callback _cb;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	if (buffers == 0)
		return 0;

	if (!mutex_is_locked(&_bus[bus_id].mutex.transaction)) {
		trace_error("bus: no opened transaction on the bus.");
		return -EBUSY;
	}
	if (!mutex_try_lock(&_bus[bus_id].mutex.lock))
		return -EAGAIN;

	callback_copy(&_bus[bus_id].callback, cb);

	callback_set(&_cb, _bus_callback, (void*)(uint32_t)bus_id);
	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		_bus[bus_id].iface.spid.chip_select = (uint8_t)remote;

		err = spid_transfer(&_bus[bus_id].iface.spid, buf, buffers, &_cb);
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		_bus[bus_id].iface.twid.slave_addr = (uint8_t)remote;

		err = twid_transfer(&_bus[bus_id].iface.twid, buf, buffers, &_cb);
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	if (err < 0) {
		mutex_unlock(&_bus[bus_id].mutex.lock);
		return err;
	}
	if (_bus[bus_id].options & O_BLOCK)
		while (bus_is_busy(bus_id)) {
			if (_bus[bus_id].transfer_mode == BUS_TRANSFER_MODE_DMA)
				dma_poll();
		}

	return err;
}

int bus_start_transaction(uint8_t bus_id)
{
	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	mutex_lock(&_bus[bus_id].mutex.transaction);

	return 0;
}

int bus_stop_transaction(uint8_t bus_id)
{
	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	mutex_unlock(&_bus[bus_id].mutex.transaction);

	return 0;
}

void bus_wait_transaction(uint8_t bus_id)
{
	while (mutex_is_locked(&_bus[bus_id].mutex.transaction));
}

bool bus_is_busy(uint8_t bus_id)
{
	return mutex_is_locked(&_bus[bus_id].mutex.lock);
}

int bus_wait_transfer(uint8_t bus_id)
{
	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	if (_bus[bus_id].timeout > 0) {
		struct _timeout _to;

		timer_start_timeout(&_to, _bus[bus_id].timeout);
		while (!timer_timeout_reached(&_to)) {
			if (!bus_is_busy(bus_id))
				return 0;
			if (_bus[bus_id].transfer_mode == BUS_TRANSFER_MODE_DMA)
				dma_poll();
		}

		return -ETIMEDOUT;
	} else {
		while (bus_is_busy(bus_id)) {
			if (_bus[bus_id].transfer_mode == BUS_TRANSFER_MODE_DMA)
				dma_poll();
		}
	}

	return 0;
}

int bus_suspend(uint8_t bus_id)
{
	int err = -ENOTSUP;

	if (bus_id >= BUS_COUNT)
		return -ENODEV;

	switch (_bus[bus_id].type) {
#ifdef CONFIG_HAVE_SPI_BUS
	case BUS_TYPE_SPI:
		err = 0;
		break;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
	case BUS_TYPE_I2C:
		err = 0;
		break;
#endif
	default:
		err = -EINVAL;
		break;
	}

	return err;
}
