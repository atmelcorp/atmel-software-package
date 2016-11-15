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

#ifndef NVIC_H_
#define NVIC_H_

#ifdef CONFIG_HAVE_NVIC

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include "irq/irq.h"

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *         Global types
 *----------------------------------------------------------------------------*/

typedef void (*nvic_handler_t)(void);

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize the NVIC.
 *
 * This function will disable all interrupts, clear all interrupt pending flags
 * and set the default handlers.
 */
extern void nvic_initialize(nvic_handler_t irq_handler);

/**
 * \brief Configure a handler for a given interrupt source (ID_xxx).
 *
 * \param source  Interrupt source to configure
 * \param handler handler for the interrupt
 */
extern void nvic_set_source_vector(uint32_t source, nvic_handler_t handler);

/**
 * \brief Configure the interrupt priority for a given source.
 *
 * \param source   Interrupt source to configure
 * \param priority Interrupt priority
 */
extern void nvic_configure_priority(uint32_t source, uint8_t priority);

/**
 * \brief Enable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to enable
 */
extern void nvic_enable(uint32_t source);

/**
 * \brief Disable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to disable
 */
extern void nvic_disable(uint32_t source);

/**
 * \brief Get the current interrupt source number
 *
 * \return Interrupt source number
 */
extern uint32_t nvic_get_current_interrupt_source(void);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_NVIC */

#endif /* NVIC_H_ */
