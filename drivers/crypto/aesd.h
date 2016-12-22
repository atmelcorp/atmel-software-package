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


#ifndef AESD_HEADER__
#define AESD_HEADER__

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

#define AESD_SUCCESS         (0)
#define ADES_ERROR_LOCK      (1)
#define AESD_ERROR_TRANSFER  (2)

enum _aesd_trans_mode
{
	AESD_TRANS_POLLING_MANUAL = 0,
	AESD_TRANS_POLLING_AUTO,
	AESD_TRANS_DMA
};

enum _aesd_mode {
	AESD_MODE_ECB = 0,
	AESD_MODE_CBC,
	AESD_MODE_OFB,
	AESD_MODE_CFB,
	AESD_MODE_CTR,
	AESD_MODE_GCM
};

enum _aesd_key_size {
	AESD_AES128 = 0,
	AESD_AES192,
	AESD_AES256
};

enum _aesd_cipher_size {
	AESD_CFBS_128 = 0,
	AESD_CFBS_64,
	AESD_CFBS_32,
	AESD_CFBS_16,
	AESD_CFBS_8
};

struct _aesd_desc {
	/* structure to define AES parameter */

	/* following fields are used internally */
	mutex_t         mutex;
	struct {
		bool encrypt;
		enum _aesd_trans_mode transfer_mode;
		enum _aesd_mode mode;
		enum _aesd_key_size key_size;
		enum _aesd_cipher_size cfbs;
		uint32_t key[8];
		uint32_t vector[4];
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
extern void aesd_configure_mode(struct _aesd_desc* desc);

extern void aesd_init(struct _aesd_desc* desc);

extern uint32_t aesd_transfer(struct _aesd_desc* desc,
			      struct _buffer* buffer_in, struct _buffer* buffer_out,
			      struct _callback* callback);

extern bool aesd_is_busy(struct _aesd_desc* desc);

extern void aesd_wait_transfer(struct _aesd_desc* desc);

#endif /* AESD_HEADER__ */
