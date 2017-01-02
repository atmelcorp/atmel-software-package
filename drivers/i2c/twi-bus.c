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

#include "board.h"
#include "callback.h"
#include "errno.h"
#include "trace.h"
#include "twi-bus.h"

/*------------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _twi_bus_desc _twi_bus[TWI_IFACE_COUNT];

/*------------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _twi_bus_callback(void* arg)
{
	uint8_t bus_id = *(uint8_t *)arg;

	if (bus_id >= TWI_IFACE_COUNT)
		return -ENODEV;

	mutex_unlock(&_twi_bus[bus_id].mutex);

	callback_call(&_twi_bus[bus_id].callback);

	return 0;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

int twi_bus_configure(uint8_t bus_id, Twi *iface, uint32_t freq, enum _twid_trans_mode mode)
{
	assert(bus_id < TWI_IFACE_COUNT);

	memset(&_twi_bus[bus_id], 0, sizeof(_twi_bus[bus_id]));
	_twi_bus[bus_id].twid.addr = iface;
	_twi_bus[bus_id].twid.freq = freq;
	_twi_bus[bus_id].twid.transfer_mode = mode;

	twid_configure(&_twi_bus[bus_id].twid);

	return 0;
}

int twi_bus_transfer(uint8_t bus_id, uint8_t slave_addr, struct _buffer *buf, uint16_t buffers,
                         struct _callback* cb)
{
	struct _callback _cb;
	int err;

	assert(bus_id < TWI_IFACE_COUNT);

	if (buffers == 0)
		return 0;

	if (!mutex_is_locked(&_twi_bus[bus_id].transaction)) {
		trace_error("twi_bus: no opened transaction on the bus.");
		return -ECONNREFUSED;
	}
	if (!mutex_try_lock(&_twi_bus[bus_id].mutex))
		return -EBUSY;

	_twi_bus[bus_id].twid.slave_addr = slave_addr;
	callback_copy(&_twi_bus[bus_id].callback, cb);

	callback_set(&_cb, _twi_bus_callback, &bus_id);
	err = twid_transfer(&_twi_bus[bus_id].twid, buf, buffers, &_cb);
	if (err < 0) {
		mutex_unlock(&_twi_bus[bus_id].mutex);
		return err;
	}

	return 0;
}

bool twi_bus_is_busy(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return mutex_is_locked(&_twi_bus[bus_id].mutex);
}

void twi_bus_wait_transfer(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	while (twi_bus_is_busy(bus_id));
}

bool twi_bus_start_transaction(uint8_t bus_id)
{
	return mutex_try_lock(&_twi_bus[bus_id].transaction);
}

int twi_bus_stop_transaction(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	mutex_unlock(&_twi_bus[bus_id].transaction);
	return 0;
}

bool twi_bus_transaction_pending(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return mutex_is_locked(&_twi_bus[bus_id].transaction);
}

enum _twid_trans_mode twi_bus_get_transfer_mode(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return _twi_bus[bus_id].twid.transfer_mode;
}

void twi_bus_set_transfer_mode(uint8_t bus_id, enum _twid_trans_mode mode)
{
	assert(bus_id < TWI_IFACE_COUNT);
	assert(mode == TWID_MODE_POLLING ||
	       mode == TWID_MODE_DMA ||
	       mode == TWID_MODE_ASYNC);

	_twi_bus[bus_id].twid.transfer_mode = mode;
}

void twi_bus_fifo_enable(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	_twi_bus[bus_id].twid.use_fifo = true;
#endif
}


void twi_bus_fifo_disable(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	_twi_bus[bus_id].twid.use_fifo = false;
#endif
}

bool twi_bus_fifo_is_enabled(uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	return _twi_bus[bus_id].twid.use_fifo;
#else
	return false;
#endif
}
