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

#ifndef CAND_H_
#define CAND_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "can/can.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Number of mailboxes in a CAN controller */
#define CAN_NUM_MAILBOX 8

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _cand_mailbox {
	struct _buffer *buf;
	struct _callback cb;
	uint8_t state;
};

struct _can_desc {
	Can* addr;             /**< Pointer to HW register base */
	uint32_t freq;         /**< Current working baudrate */
	uint32_t identifier;
	uint32_t mask;
	uint8_t state;         /**< CAN states */
	struct _cand_mailbox mailboxes[CAN_NUM_MAILBOX];
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern struct _can_desc* cand_get_desc(uint8_t can_if);

extern int cand_configure(struct _can_desc* desc);

extern void cand_enable(struct _can_desc* desc);

extern bool cand_is_enabled(struct _can_desc* desc);

/**
 * Configure the CAN Mailbox for message transfer.
 * \param desc Pointer to CAN Driver descriptor instance.
 * \param buf  Pointer to buffer to transfer.
 * \param cb   Pointer to call back structure.
 */
extern int cand_transfer(struct _can_desc* desc, struct _buffer* buf,
			struct _callback* cb);

#endif /* CAND_H_ */
