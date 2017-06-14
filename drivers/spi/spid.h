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

#include "callback.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

enum _spid_mode {
	SPID_MODE_0 = 0x00, // POL=0, CPHA=0
	SPID_MODE_1 = 0x01, // POL=0, CPHA=1
	SPID_MODE_2 = 0x02, // POL=1, CPHA=0
	SPID_MODE_3 = 0x03, // POL=1, CPHA=1
};

struct _spi_desc {
	Spi* addr;
	uint8_t chip_select;
	int transfer_mode;
	/* following fields are used internally */
	mutex_t mutex;

#ifdef CONFIG_HAVE_SPI_FIFO
	bool use_fifo;
	struct {
		struct {
			uint16_t size;
			uint16_t threshold;
		} rx, tx;
	} fifo;
#endif

	/* structure to hold data about current transfer */
	struct {
		struct _buffer*  current;     /*< Current buffer */
		struct _buffer*  last;        /*< Last buffer */
		struct _callback callback;

		struct {
			uint32_t rx, tx; /*< index of next byte to receive/transmit for current buffer */
		} async;

		struct {
			struct _dma_channel* rx_channel;
			struct _dma_channel* tx_channel;
		} dma;
	} xfer;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern int spid_configure(struct _spi_desc* desc);

extern int spid_transfer(struct _spi_desc* desc,
		struct _buffer* buffers, int buffer_count,
		struct _callback* cb);

extern bool spid_is_busy(struct _spi_desc* desc);

extern void spid_wait_transfer(struct _spi_desc* desc);

extern void spid_configure_cs(struct _spi_desc* desc, uint8_t cs,
		uint32_t bitrate, uint32_t delay_dlybs, uint32_t delay_dlybct,
		enum _spid_mode mode);

extern void spid_set_cs_bitrate(struct _spi_desc* desc, uint8_t cs,
		uint32_t bitrate);

extern int spid_configure_master(struct _spi_desc* desc, bool master);


#endif /* SPID_HEADER__ */
