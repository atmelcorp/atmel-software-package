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

/**
* \file
*
* Implementation of Analog Comparator Controller (ACC).
*
*/


#ifndef ACC_H
#define ACC_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

include "chip.h"

#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

extern void acc_init(Acc *p_acc, uint32_t select_plus, uint32_t select_minus, uint32_t edge_type, uint32_t invert);
extern void acc_enable(Acc *p_acc);
extern void acc_disable(Acc *p_acc);
extern void acc_reset(Acc *p_acc);
extern void acc_set_input(Acc *p_acc, uint32_t select_minus, uint32_t select_plus);
extern void acc_set_output(Acc *p_acc, uint32_t invert, uint32_t fault_enable, uint32_t fault_source);
extern uint32_t acc_get_comparison_result(Acc *p_acc);
extern void acc_enable_interrupt(Acc *p_acc);
extern void acc_disable_interrupt(Acc *p_acc);
extern uint32_t acc_get_interrupt_status(Acc *p_acc);
extern void acc_set_write_protect(Acc *p_acc, uint32_t enable);
extern uint32_t acc_get_write_protect_status(Acc *p_acc);


#endif /* ACC_H */
