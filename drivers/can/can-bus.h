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

#ifndef CAN_BUS_H_
#define CAN_BUS_H_

enum can_mode
{
	/* ISO 11898-1 CAN mode */
	CAN_MODE_CAN,

	/* Long CAN FD frame.
	 * - TX and RX payloads up to 64 bytes.
	 * - Slow transmitter: TX frames are sent at constant bit rate.
	 * - Fast receiver: both constant-rate (slow) and dual-rate (fast)
	 *   RX frames are supported and received. */
	CAN_MODE_CAN_FD_CONST_RATE,

	/* Long and fast CAN FD frame.
	 * - TX and RX payloads up to 64 bytes.
	 * - Fast transmitter: control, data and CRC fields are transmitted at a
	 *   higher bit rate.
	 * - Fast receiver. */
	CAN_MODE_CAN_FD_DUAL_RATE,
};

enum _cand_buf_attr {
	CAND_BUF_ATTR_STANDARD     = 0x00,
	CAND_BUF_ATTR_EXTENDED     = 0x01,
	CAND_BUF_ATTR_RX           = 0x02,
	CAND_BUF_ATTR_RX_OVERWRITE = 0x04,
	CAND_BUF_ATTR_TX           = 0x08,
	CAND_BUF_ATTR_CONSUMER     = 0x10,
	CAND_BUF_ATTR_PRODUCER     = 0x20,
	CAND_BUF_ATTR_TX_MSK       = (CAND_BUF_ATTR_TX | CAND_BUF_ATTR_CONSUMER | CAND_BUF_ATTR_PRODUCER),

	CAND_BUF_ATTR_TRANSFER_DONE= 0x40,
	CAND_BUF_ATTR_TRANSFER_ERR = 0x80,
	CAND_BUF_ATTR_TRANSFER_MSK = (CAND_BUF_ATTR_TRANSFER_DONE | CAND_BUF_ATTR_TRANSFER_ERR),

	CAND_BUF_ATTR_USING_FIFO   = 0x100,
	CAND_BUF_ATTR_USING_FIFO1  = 0x300,
};

#if defined(CONFIG_HAVE_CAN)
#include "can/cand.h"
#elif defined(CONFIG_HAVE_MCAN)
#include "can/mcand.h"
#endif
#include "errno.h"
#include "mutex.h"
#include "io.h"

typedef void (*can_bus_callback_t)(void* args);

struct _can_bus_desc {
#if defined(CONFIG_HAVE_CAN)
	struct _can_desc *cand;
#elif defined(CONFIG_HAVE_MCAN)
	struct _mcan_desc *mcand;
#endif
	mutex_t mutex;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern int can_bus_configure(uint8_t bus_id, void *iface, uint32_t freq, uint32_t freq_fd);

extern int can_bus_mode(uint8_t bus_id, enum can_mode mode);

extern int can_bus_loopback(uint8_t bus_id, bool loop_back);

extern int can_bus_transfer(uint8_t bus_id,
	uint32_t identifier, uint32_t mask, struct _buffer *buf,
	struct _callback* cb);

extern bool can_bus_wait_transfer_done(struct _buffer *buf, uint32_t wait_ms);

extern int can_bus_activate(uint8_t bus_id, uint32_t wait);

extern void can_bus_low_power(uint8_t bus_id);

#endif /* CAN_BUS_H_ */
