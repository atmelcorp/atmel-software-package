#include "twi-bus.h"
#include "board.h"

#include "trace.h"

#include <string.h>
#include <assert.h>

static struct _twi_bus_desc _twi_bus[TWI_IFACE_COUNT];

static void twi_bus_callback(struct _twi_desc *twi, void *args)
{
	uint8_t bus_id = *(uint8_t *)args;

	if (bus_id >= TWI_IFACE_COUNT)
		return;

	if (_twi_bus[bus_id].callback)
		_twi_bus[bus_id].callback(_twi_bus[bus_id].cb_args);

	mutex_unlock(&_twi_bus[bus_id].mutex);
}

int32_t twi_bus_configure(uint8_t bus_id, Twi *iface, uint32_t freq, enum _twid_trans_mode mode)
{
	assert(bus_id < TWI_IFACE_COUNT);

	memset(&_twi_bus[bus_id], 0, sizeof(_twi_bus[bus_id]));
	_twi_bus[bus_id].twid.addr = iface;
	_twi_bus[bus_id].twid.freq = freq;
	_twi_bus[bus_id].twid.transfer_mode = mode;

	twid_configure(&_twi_bus[bus_id].twid);

	return 0;
}

int32_t twi_bus_transfer(uint8_t bus_id, uint8_t slave_addr, struct _buffer *buf, uint16_t buffers,
						 twi_bus_callback_t cb, void *user_args)
{
	uint32_t status;
	
	assert(bus_id < TWI_IFACE_COUNT);

	if (buffers == 0)
		return TWID_SUCCESS;
	
	if (!mutex_is_locked(&_twi_bus[bus_id].transaction)) {
		trace_error("-W- twi_bus: no opened transaction on the bus.");
		return TWID_ERROR_LOCK;
	}
	if (!mutex_try_lock(&_twi_bus[bus_id].mutex))
		return TWID_ERROR_LOCK;

	_twi_bus[bus_id].twid.slave_addr = slave_addr;
	_twi_bus[bus_id].callback = cb;
	_twi_bus[bus_id].cb_args = user_args;

	status = twid_transfer(&_twi_bus[bus_id].twid, buf, buffers, twi_bus_callback, (void *)&bus_id);
	if (status) {
		mutex_unlock(&_twi_bus[bus_id].mutex);
		return status;
	}
	twid_wait_transfer(&_twi_bus[bus_id].twid);

	return status;	
}

bool twi_bus_is_busy(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return mutex_is_locked(&_twi_bus[bus_id].mutex);
}

void twi_bus_wait_transfer(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	while (twi_bus_is_busy(bus_id));
}

int32_t twi_bus_start_transaction(const uint8_t bus_id)
{
	return mutex_try_lock(&_twi_bus[bus_id].transaction);
}

int32_t twi_bus_stop_transaction(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	mutex_unlock(&_twi_bus[bus_id].transaction);
	return 0;
}

bool twi_bus_transaction_pending(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return mutex_is_locked(&_twi_bus[bus_id].transaction);
}

enum _twid_trans_mode twi_bus_get_transfer_mode(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

	return _twi_bus[bus_id].twid.transfer_mode;
}

void twi_bus_set_transfer_mode(const uint8_t bus_id, enum _twid_trans_mode mode)
{
	assert(bus_id < TWI_IFACE_COUNT);
	assert(mode == TWID_MODE_POLLING ||
	       mode == TWID_MODE_DMA ||
	       mode == TWID_MODE_ASYNC);

	_twi_bus[bus_id].twid.transfer_mode = mode;
}

void twi_bus_fifo_enable(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	_twi_bus[bus_id].twid.use_fifo = true;
#endif
}


void twi_bus_fifo_disable(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	_twi_bus[bus_id].twid.use_fifo = false;
#endif
}

bool twi_bus_fifo_is_enabled(const uint8_t bus_id)
{
	assert(bus_id < TWI_IFACE_COUNT);

#ifdef CONFIG_HAVE_TWI_FIFO
	return _twi_bus[bus_id].twid.use_fifo;
#else
	return false;
#endif
}
