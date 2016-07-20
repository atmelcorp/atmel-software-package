#ifndef TWI_BUS_H
#define TWI_BUS_H

#include "peripherals/twid.h"
#include "mutex.h"

typedef void (*twi_bus_callback_t)(void* args);

struct _twi_bus_desc {
	struct _twi_desc twid;

	twi_bus_callback_t callback;
	void *cb_args;

	mutex_t mutex;
	mutex_t transaction;
};


int32_t twi_bus_configure(uint8_t bus_id, Twi *iface, uint32_t freq, enum _twid_trans_mode mode);

int32_t twi_bus_transfer(uint8_t bus_id, uint8_t slave_addr, struct _buffer *buf, uint16_t buffers,
						 twi_bus_callback_t cb, void *user_args);

int32_t twi_bus_start_transaction(const uint8_t bus_id);

int32_t twi_bus_stop_transaction(const uint8_t bus_id);

bool twi_bus_transaction_pending(const uint8_t bus_id);

bool twi_bus_is_busy(const uint8_t bus_id);

void twi_bus_wait_transfer(const uint8_t bus_id);

enum _twid_trans_mode twi_bus_get_transfer_mode(const uint8_t bus_id);

void twi_bus_set_transfer_mode(const uint8_t bus_id, enum _twid_trans_mode mode);

void twi_bus_fifo_enable(const uint8_t bus_id);

void twi_bus_fifo_disable(const uint8_t bus_id);

bool twi_bus_fifo_is_enabled(const uint8_t bus_id);

#endif /* ! TWI_BUS_H */
