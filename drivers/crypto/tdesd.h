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


#ifndef TDESD_H
#define TDESD_H

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

#define TDESD_SUCCESS         (0)
#define ADES_ERROR_LOCK       (1)
#define TDESD_ERROR_TRANSFER  (2)

enum _tdesd_trans_mode
{
	TDESD_TRANS_POLLING_MANUAL = 0,
	TDESD_TRANS_POLLING_AUTO,
	TDESD_TRANS_DMA
};

enum _tdesd_algo {
	TDESD_ALGO_SINGLE = 0,
	TDESD_ALGO_TRIPLE,
	TDESD_ALGO_XTEA
};

enum _tdesd_mode {
	TDESD_MODE_ECB = 0,
	TDESD_MODE_CBC,
	TDESD_MODE_OFB,
	TDESD_MODE_CFB
};

enum _tdesd_key_mode {
	TDESD_KEY_THREE = 0,
	TDESD_KEY_TWO
};

enum _tdesd_cipher_size {
	TDESD_CFBS_64 = 0,
	TDESD_CFBS_32,
	TDESD_CFBS_16,
	TDESD_CFBS_8
};

struct _tdesd_desc {
	/* structure to define TDES parameter */

	/* following fields are used internally */
	mutex_t         mutex;
	struct {
		bool encrypt;
		enum _tdesd_trans_mode transfer_mode;
		enum _tdesd_algo algo;
		enum _tdesd_mode mode;
		enum _tdesd_key_mode key_mode;
		enum _tdesd_cipher_size cfbs;
		uint32_t key[6];
		uint32_t vector[2];
	} cfg;

	/* structure to hold data about current transfer */
	struct {
		struct _buffer *bufin;         /*< buffer input */
		struct _buffer *bufout;        /*< buffer output */
		struct _callback callback;

		struct {
			struct {
				struct _dma_channel *channel;
			} rx, tx;
		} dma;
	} xfer;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern void tdesd_init(struct _tdesd_desc* desc);

extern uint32_t tdesd_transfer(struct _tdesd_desc* desc,
		struct _buffer* buffer_in, struct _buffer* buffer_out,
			       struct _callback* cb);

extern bool tdesd_is_busy(struct _tdesd_desc* desc);

extern void tdesd_wait_transfer(struct _tdesd_desc* desc);

extern void tdesd_configure_mode(struct _tdesd_desc* desc);

#endif /* TDESD_H */
