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
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define SHAD_SUCCESS         (0)
#define SHAD_ERROR_LOCK      (1)
#define SHAD_ERROR_PARAM     (2)
#define SHAD_ERROR_TRANSFER  (3)

enum _shad_trans_mode
{
	SHAD_TRANS_POLLING_MANUAL = 0,
	SHAD_TRANS_POLLING_AUTO,
	SHAD_TRANS_DMA
};

enum _shad_mode {
	SHAD_MODE_SHA1 = 0,
	SHAD_MODE_SHA256,
	SHAD_MODE_SHA384,
	SHAD_MODE_SHA512,
	SHAD_MODE_SHA224,
};

struct _shad_desc {
	/* structure to define SHA parameter */

	/* following fields are used internally */
	mutex_t         mutex;
	struct {
		enum _shad_trans_mode transfer_mode;
		enum _shad_mode mode;
	} cfg;

	/* structure to hold data about current transfer */
	struct {
		struct _buffer *bufin;         /*< buffer input */
		struct _buffer *bufout;        /*< buffer output */
		struct _callback callback;

		struct {
			struct {
				struct _dma_channel *channel;
				struct dma_xfer_cfg cfg;
			} rx, tx;
		} dma;
	} xfer;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern void shad_init(struct _shad_desc* desc);

extern uint32_t shad_transfer(struct _shad_desc* desc,
			      struct _buffer* buffer_in, struct _buffer* buffer_out,
			      struct _callback* cb);

extern bool shad_is_busy(struct _shad_desc* desc);

extern void shad_wait_transfer(struct _shad_desc* desc);

/**
 * \brief According to the standard, the message must be padded to an even
 * 512 bits.  The first padding bit must be a '1'.  The last 64 bits represent
 * the length of the original message.  All bits in between should be 0.
 * \param message The context to pad
 * \param l length of message in byte
 * \param mode SHA mode
 * \note: the size of massage is limit to 32 bytes.
 * return length of padded message.
*/
extern uint32_t shad_pad_message(uint8_t *message, uint32_t len, uint8_t mode);

#endif /* SHAD_H */
