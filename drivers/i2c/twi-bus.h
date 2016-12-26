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

#ifndef TWI_BUS_H
#define TWI_BUS_H

/*------------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "i2c/twid.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Type Definitions
 *----------------------------------------------------------------------------*/

struct _twi_bus_desc {
	struct _twi_desc twid;
	struct _callback callback;
	mutex_t mutex;
	mutex_t transaction;
};

/*------------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

int32_t twi_bus_configure(uint8_t bus_id, Twi *iface, uint32_t freq, enum _twid_trans_mode mode);

int32_t twi_bus_transfer(uint8_t bus_id, uint8_t slave_addr, struct _buffer *buf, uint16_t buffers,
                         struct _callback* cb);

int32_t twi_bus_start_transaction(uint8_t bus_id);

int32_t twi_bus_stop_transaction(uint8_t bus_id);

bool twi_bus_transaction_pending(uint8_t bus_id);

bool twi_bus_is_busy(uint8_t bus_id);

void twi_bus_wait_transfer(uint8_t bus_id);

enum _twid_trans_mode twi_bus_get_transfer_mode(uint8_t bus_id);

void twi_bus_set_transfer_mode(uint8_t bus_id, enum _twid_trans_mode mode);

void twi_bus_fifo_enable(uint8_t bus_id);

void twi_bus_fifo_disable(uint8_t bus_id);

bool twi_bus_fifo_is_enabled(uint8_t bus_id);

#endif /* ! TWI_BUS_H */
