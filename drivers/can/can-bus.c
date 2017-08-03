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

#include <assert.h>
#include <string.h>

#include "board.h"
#include "can-bus.h"
#include "errno.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _can_bus_desc _can_bus[CAN_IFACE_COUNT];

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

int can_bus_configure(uint8_t bus_id, void *iface, uint32_t freq, uint32_t freq_fd)
{
	assert(bus_id < CAN_IFACE_COUNT);

	memset(&_can_bus[bus_id], 0, sizeof(_can_bus[bus_id]));

#if defined(CONFIG_HAVE_CAN)
	_can_bus[bus_id].cand = cand_get_desc(bus_id);
	_can_bus[bus_id].cand->addr = (Can *)iface;
	_can_bus[bus_id].cand->freq = freq;
	cand_configure(_can_bus[bus_id].cand);
#elif defined(CONFIG_HAVE_MCAN)
	_can_bus[bus_id].mcand = mcand_get_desc(iface);
	memset(_can_bus[bus_id].mcand, 0, sizeof(struct _mcan_desc));
	_can_bus[bus_id].mcand->addr = (Mcan *)iface;
	_can_bus[bus_id].mcand->freq = freq;
	_can_bus[bus_id].mcand->freq_fd = freq_fd;

	mcand_configure(_can_bus[bus_id].mcand);
#endif

	return 0;
}

int can_bus_mode(uint8_t bus_id, enum can_mode mode)
{
	assert(bus_id < CAN_IFACE_COUNT);

#if defined(CONFIG_HAVE_CAN)
	if (mode != CAN_MODE_CAN)
		return -ENOTSUP;
#elif defined(CONFIG_HAVE_MCAN)
	Mcan *mcan = _can_bus[bus_id].mcand->addr;
	mcan_disable(mcan);
	mcan_reconfigure(mcan);
	if (!mcan_set_mode(mcan, mode)) {
		mcan_enable(mcan);
		return -ENOTSUP;
	}
	mcan_enable(mcan);
#endif

	return 0;
}

int can_bus_loopback(uint8_t bus_id, bool loop_back)
{
	assert(bus_id < CAN_IFACE_COUNT);

#if defined(CONFIG_HAVE_CAN)
	if (loop_back)
		return -ENOTSUP;
#elif defined(CONFIG_HAVE_MCAN)
	Mcan *mcan = _can_bus[bus_id].mcand->addr;
	mcan_disable(mcan);
	mcan_loopback(mcan, loop_back);
	mcan_enable(mcan);
#endif

	return 0;
}

int can_bus_transfer(uint8_t bus_id,
	uint32_t identifier, uint32_t mask, struct _buffer *buf,
	struct _callback* cb)
{
	uint32_t status;

	assert(bus_id < CAN_IFACE_COUNT);

	if (buf == NULL)
		return 0;

	if (!mutex_try_lock(&_can_bus[bus_id].mutex))
		return -EBUSY;

#if defined(CONFIG_HAVE_CAN)
	_can_bus[bus_id].cand->identifier = identifier;
	_can_bus[bus_id].cand->mask = mask;
#elif defined(CONFIG_HAVE_MCAN)
	_can_bus[bus_id].mcand->identifier = identifier;
	_can_bus[bus_id].mcand->mask = mask;
#endif

	buf->attr &= ~CAND_BUF_ATTR_TRANSFER_MSK;

#if defined(CONFIG_HAVE_CAN)
	status = cand_transfer(_can_bus[bus_id].cand, buf, cb);
#elif defined(CONFIG_HAVE_MCAN)
	status = mcand_transfer(_can_bus[bus_id].mcand, buf, cb);
#endif

	mutex_unlock(&_can_bus[bus_id].mutex);
	return status;

}

bool can_bus_wait_transfer_done(struct _buffer *buf, uint32_t wait_ms)
{
	struct _timeout timeout;

	if (wait_ms) {
		timer_start_timeout(&timeout, wait_ms);
		while (!timer_timeout_reached(&timeout)) {
			if (buf->attr & CAND_BUF_ATTR_TRANSFER_MSK)
				return true;
		}
	} else {
		if (buf->attr & CAND_BUF_ATTR_TRANSFER_MSK)
			return true;
	}
	return false;
}

int can_bus_activate(uint8_t bus_id, uint32_t wait_ms)
{
	struct _timeout timeout;

	assert(bus_id < CAN_IFACE_COUNT);

#if defined(CONFIG_HAVE_CAN)
	struct _can_desc *desc = _can_bus[bus_id].cand;
	cand_enable(desc);
#elif defined(CONFIG_HAVE_MCAN)
	Mcan *mcan = _can_bus[bus_id].mcand->addr;
	if (!mcan_is_enabled(mcan))
		mcan_enable(mcan);
#endif

	timer_start_timeout(&timeout, wait_ms);
	while (!timer_timeout_reached(&timeout)) {
#if defined(CONFIG_HAVE_CAN)
		if (cand_is_enabled(desc))
			return 0;
#elif defined(CONFIG_HAVE_MCAN)
		if (mcan_is_enabled(mcan))
			return 0;
#endif
	}
	return -ETIMEDOUT;
}

void can_bus_low_power(uint8_t bus_id)
{
	assert(bus_id < CAN_IFACE_COUNT);

#if defined(CONFIG_HAVE_CAN)
	Can *can = _can_bus[bus_id].cand->addr;
	can_enable_it(can, CAN_IER_SLEEP);
	can_enable_low_power(can, 1);
#elif defined(CONFIG_HAVE_MCAN)
	// unsupported
#endif
}
