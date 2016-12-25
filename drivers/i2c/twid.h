/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#ifndef TWID_H_
#define TWID_H_

/*------------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "dma/dma.h"
#include "i2c/twi.h"
#include "io.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _twi_desc
{
	Twi*  addr;
	uint32_t freq;
	uint32_t slave_addr;
	int transfer_mode;
	uint32_t flags;
	uint32_t timeout; /**< timeout (if 0, a default timeout is used) */
	mutex_t mutex;
	struct _callback callback;

#ifdef CONFIG_HAVE_TWI_FIFO
	bool use_fifo;
	struct {
		struct {
			uint16_t size;
			uint16_t threshold;
		} rx, tx;
	} fifo;
#endif

	struct {
		struct {
			struct _dma_channel *channel;
			struct _dma_cfg cfg_dma;
			struct _dma_transfer_cfg cfg;
		} rx, tx;
	} dma;
};

struct _twi_slave_ops {
	void (*on_start)(void);
	void (*on_stop)(void);
	int16_t (*on_read)(uint8_t byte);
	int16_t (*on_write)(void);
};

struct _twi_slave_desc {
	Twi* twi;
	uint16_t addr;
	uint8_t state;
#define TWID_SLAVE_STATE_STOPPED 0
#define TWID_SLAVE_STATE_STARTED 1
	struct _twi_slave_ops* ops;
};

/*------------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern int twid_configure(struct _twi_desc* desc);

extern int twid_slave_configure(struct _twi_slave_desc* desc, struct _twi_slave_ops* ops);

extern int twid_transfer(struct _twi_desc* desc, struct _buffer* buf, int buffers, struct _callback* cb);

extern bool twid_is_busy(const struct _twi_desc* desc);

extern void twid_wait_transfer(const struct _twi_desc* desc);

#endif /* TWID_H_ */
