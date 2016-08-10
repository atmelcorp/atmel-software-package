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


#ifndef SPID_HEADER__
#define SPID_HEADER__

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include "mutex.h"
#include "io.h"

#include "peripherals/dma.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define SPID_SUCCESS         (0)
#define SPID_INVALID_ID      (1)
#define SPID_INVALID_BITRATE (2)
#define SPID_ERROR_LOCK      (3)
#define SPID_ERROR_TRANSFER  (4)

struct _spi_desc;

typedef void (*spid_callback_t)(void* args);

enum _spid_buf_attr {
	SPID_BUF_ATTR_READ       = 0x01,
	SPID_BUF_ATTR_WRITE      = 0x02,
	SPID_BUF_ATTR_RELEASE_CS = 0x04,
};

enum _spid_trans_mode
{
	SPID_MODE_POLLING,
	SPID_MODE_DMA
};

struct _spi_desc
{
	Spi*            addr;
	uint32_t        bitrate;
	uint32_t        attributes;
	uint8_t         dlybs;
	uint8_t         dlybct;
	uint8_t         chip_select;
	uint8_t         spi_mode;
	enum _spid_trans_mode transfer_mode;
	/* following fields are used internally */
	mutex_t         mutex;
	spid_callback_t callback;
	void*           cb_args;

	uint32_t        flags;

	struct {
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} rx;
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} tx;
	} dma;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern void spid_configure(struct _spi_desc* desc);

extern uint32_t spid_transfer(struct _spi_desc* desc, struct _buffer* buf, int buffers,
							  spid_callback_t cb, void* user_args);

extern uint32_t spid_is_busy(const struct _spi_desc* desc);

extern void spid_wait_transfer(const struct _spi_desc* desc);

#endif /* SPID_HEADER__ */
