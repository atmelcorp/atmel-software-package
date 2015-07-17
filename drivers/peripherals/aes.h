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

#ifndef _AES_
#define _AES_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

/*------------------------------------------------------------------------------*/
/*         Definition                                                           */
/*------------------------------------------------------------------------------*/
#define AES_MR_CIPHER_ENCRYPT 1
#define AES_MR_CIPHER_DECRYPT 0
/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

void aes_start(void);
void aes_soft_reset(void);
void aes_configure(uint32_t mode);
void aes_enable_it(uint32_t sources);
void aes_disable_it(uint32_t sources);
extern uint32_t aes_get_status(void);
void aes_write_key(const uint32_t * key, uint32_t len);
void aes_set_input(uint32_t * data);
void aes_get_output(uint32_t * data);
void aes_set_vector(const uint32_t * vector);
void aes_set_aad_len(uint32_t len);
void aes_set_data_len(uint32_t len);
void aes_set_gcm_hash(uint32_t * hash);
void aes_get_gcm_tag(uint32_t * tag);
void aes_get_gcm_counter(uint32_t * counter);
void aes_get_gcm_hash_subkey(uint32_t * h);

#endif				/* #ifndef _AES_ */
