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

#ifndef _TDES_
#define _TDES_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

/*------------------------------------------------------------------------------*/
/*         Definition                                                           */
/*------------------------------------------------------------------------------*/
#define MODE_SINGLE_DES              0x00
#define MODE_TRIPLE_DES              0x01
#define MODE_XTEA                    0x02

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

void tdes_start(void);
void tdes_soft_reset(void);
void tdes_configure(uint32_t mode);
void tdes_enable_it(uint32_t sources);
void tdes_disable_it(uint32_t sources);
extern uint32_t tdes_get_status(void);
void tdes_write_key1(uint32_t key_word0, uint32_t key_word1);
void tdes_write_key2(uint32_t key_word0, uint32_t key_word1);
void tdes_write_key3(uint32_t key_word0, uint32_t key_word1);
void tdes_set_input(uint32_t data0, uint32_t data1);
void tdes_get_output(uint32_t * data0, uint32_t * data1);
void tdes_set_vector(uint32_t v0, uint32_t v1);
void tdes_set_xtea_rounds(uint32_t rounds);

#endif				/* #ifndef _TDES_ */
