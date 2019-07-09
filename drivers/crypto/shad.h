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


#ifndef SHAD_H
#define SHAD_H

/*------------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "callback.h"
#include "crypto/sha.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

enum _shad_algo {
	ALGO_SHA_1,
	ALGO_SHA_224,
	ALGO_SHA_256,
	ALGO_SHA_384,
	ALGO_SHA_512,
};

enum _shad_transfer_mode
{
	SHAD_TRANS_POLLING,
	SHAD_TRANS_DMA
};

struct _shad_desc {
	/* structure to define SHA configuration */
	struct {
		enum _shad_transfer_mode transfer_mode;
		enum _shad_algo algo;
		bool _shad_generate_hmac;
	} cfg;

	/* --- following fields are used internally --- */

	mutex_t mutex;
	struct _dma_channel *dma_channel;

	/* data about current transfer */
	struct {
		struct _callback callback;
		uint32_t remaining; /* remaining data to be processed from previous shad_update call */
		uint32_t processed; /* cumulated data processed, value is included in padding data */
		struct _buffer* buffer;
	} xfer;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize the SHA peripheral
 * \param desc a SHA driver descriptor
 */
extern void shad_init(struct _shad_desc* desc);

/**
 * \brief Get number of output bytes for a given digest algorithm.
 * \param algo SHA algorithm: ALGO_SHA_1..ALGO_SHA_512
 * \return number of output bytes
 */
extern int shad_get_digest_size(enum _shad_algo algo);

/**
 * \brief Start a new SHA computation.
 * \param desc a SHA driver descriptor
 * \return 0 on success, <0 on error
 */
extern int shad_start(struct _shad_desc* desc);

/**
 * \brief Update the SHA computation with some data.
 * \param desc a SHA driver descriptor
 * \param buffer data buffer to process
 * \param auto_padding true if automatic padding is required.
 * \param cb callback called when the data processing is done
 * \return 0 on success, <0 on error
 * \note When using DMA, the buffer data pointer must be aligned to a cache
 * line.  Additionally, the buffer size must be a multiple of 4 bytes except
 * for the last call to shad_update.
 */
extern int shad_update(struct _shad_desc* desc, struct _buffer* buffer, bool auto_padding, struct _callback* cb);

/**
 * \brief Finish the SHA computation and get resulting digest.
 * \param desc a SHA driver descriptor
 * \param buffer data buffer to store the resulting digest.
 * \param auto_padding true if automatic padding is required.
 * \param cb callback called when the data processing is done
 * \return 0 on success, <0 on error
 */
extern int shad_finish(struct _shad_desc* desc, struct _buffer* buffer,  bool auto_padding, struct _callback* cb);

/**
 * \brief Checks if the SHA driver is busy processing data.
 * \param desc a SHA driver descriptor
 * \return true if the driver is busy.
 */
extern bool shad_is_busy(struct _shad_desc* desc);

/**
 * \brief Wait for the driver to finish processing data.
 * \param desc a SHA driver descriptor
 */
extern void shad_wait_completion(struct _shad_desc* desc);

/**
 * \brief the SHA computation with some data.
 * \param desc a SHA driver descriptor
 * \param buffer data buffer to process
 * \param digest data buffer to store the resulting digest.
 * \param cb callback called when the data processing is done
 * \return 0 on success, <0 on error
 * \note When using DMA, the buffer data pointer must be aligned to a cache
 * line.  Additionally, the buffer size must be a multiple of 4 bytes except
 * for the last call to shad_update.
 */
extern int shad_compute_hash(struct _shad_desc* desc,
					  struct _buffer* text,
					  struct _buffer* digest,
					  struct _callback* cb);

/**
 * \brief the HMAC KEY computation.
 * \param desc a SHA driver descriptor
 * \param key key to process
 */
extern int shad_hmac_set_key(struct _shad_desc* desc,
					  struct _buffer* key);

/**
 * \brief the HMAC computation with some data.
 * \param desc a SHA driver descriptor
 * \param buffer data buffer to process
 * \param digest data buffer to store the resulting digest.
 * \param cb callback called when the data processing is done
 * \return 0 on success, <0 on error
 * \note When using DMA, the buffer data pointer must be aligned to a cache
 * line.  Additionally, the buffer size must be a multiple of 4 bytes except
 * for the last call to shad_update.
 */
extern int shad_compute_hmac(struct _shad_desc* desc,
					  struct _buffer* text,
					  struct _buffer* digest,
					  struct _callback* cb);
#endif /* SHAD_H */
