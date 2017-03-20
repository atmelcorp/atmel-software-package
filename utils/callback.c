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

#include <stdlib.h>

#include "callback.h"
#include "errno.h"

/*----------------------------------------------------------------------------
 *         Public methods
 *----------------------------------------------------------------------------*/

/**
 * \brief Define a callback
 *
 * \param cb     Pointer to a callback object
 * \param method Pointer to the callback function
 * \param arg    Pointer to a user argument for the callback
 */
void callback_set(struct _callback* cb, callback_method_t method, void* arg)
{
	if (cb) {
		cb->method = method;
		cb->arg = arg;
	}
}

/**
 * \brief Copy a callback
 *
 * \param cb     Pointer to a callback object
 * \param orig   Pointer to the callback to copy in \cb
 */
void callback_copy(struct _callback* cb, struct _callback* orig)
{
	if (cb) {
		if (orig == NULL) {
			cb->method = NULL;
			cb->arg = NULL;
		} else {
			cb->method = orig->method;
			cb->arg = orig->arg;
		}
	}
}

int callback_call(struct _callback* cb, void* arg2)
{
	if (cb && cb->method)
		return cb->method(cb->arg, arg2);
	else
		return -ENOSYS;
}
