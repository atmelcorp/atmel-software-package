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

#ifndef SPI_BUS_H
#define SPI_BUS_H

#include "peripherals/spid.h"
#include "mutex.h"

typedef void (*spi_bus_callback_t)(void* args);

struct _spi_bus_desc {
	struct _spi_desc spid;

	spi_bus_callback_t callback;
	void *cb_args;

	mutex_t mutex;
	mutex_t transaction;
};

struct _spi_dev_desc {
	uint8_t bus;
	uint8_t chip_select;
	uint32_t bitrate;
	struct {
		uint32_t bs;
		uint32_t bct;
	} delay;
	enum _spid_mode spi_mode;
};

int32_t spi_bus_configure(uint8_t bus_id, Spi *iface, enum _spid_trans_mode mode);

void spi_bus_configure_cs(uint8_t bus_id, uint8_t cs, uint32_t bitrate, uint32_t dlybs, uint32_t dlybct,
						  enum _spid_mode mode);

int32_t spi_bus_transfer(uint8_t bus_id, uint8_t cs, struct _buffer *buf, uint16_t buffers,
						 spi_bus_callback_t cb, void *user_args);

int32_t spi_bus_start_transaction(uint8_t bus_id);

int32_t spi_bus_stop_transaction(uint8_t bus_id);

bool spi_bus_transaction_pending(uint8_t bus_id);

bool spi_bus_is_busy(uint8_t bus_id);

void spi_bus_wait_transfer(uint8_t bus_id);

enum _spid_trans_mode spi_bus_get_transfer_mode(uint8_t bus_id);

void spi_bus_set_transfer_mode(uint8_t bus_id, enum _spid_trans_mode mode);

void spi_bus_set_cs_bitrate(uint8_t bus_id, uint8_t cs, uint32_t bitrate);

void spi_bus_fifo_enable(uint8_t bus_id);

void spi_bus_fifo_disable(uint8_t bus_id);

bool spi_bus_fifo_is_enabled(uint8_t bus_id);

#endif /* ! SPI_BUS_H */
