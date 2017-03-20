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

#ifndef _CALLBACK_H
#define _CALLBACK_H

/*----------------------------------------------------------------------------
 *         Public types
 *----------------------------------------------------------------------------*/

/**
 * \brief Define a callback method type
 */
typedef int (*callback_method_t)(void*, void*);

/**
 * \brief Define a generic callback type
 */
struct _callback {
	callback_method_t method; /**< Callback function */
	void* arg;                /**< Callback argument */
};

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
extern void callback_set(struct _callback* cb, callback_method_t method, void* arg);

/**
 * \brief Copy a callback
 *
 * \param cb     Pointer to a callback object
 * \param orig   Pointer to the callback to copy in \cb
 */
extern void callback_copy(struct _callback* cb, struct _callback* orig);

/**
 * \brief Call a callback
 *
 * \param cb     Pointer to a callback object
 * \param arg2    Pointer to the second generic argument
 * \return Error code from the callback, -ENOSYS if \cb or \cb.method is NULL
 */
extern int callback_call(struct _callback* cb, void* arg2);

#endif /* _CALLBACK_H */
