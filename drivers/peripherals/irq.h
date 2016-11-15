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

#ifndef IRQ_H_
#define IRQ_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

typedef void (*irq_handler_t)(uint32_t source, void* user_arg);

enum _irq_mode {
	IRQ_MODE_HIGH_LEVEL,
	IRQ_MODE_LOW_LEVEL,
	IRQ_MODE_POSITIVE_EDGE,
	IRQ_MODE_NEGATIVE_EDGE,
};

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize the interrupt controller.
 *
 * This function will disable all interrupts, clear all interrupt pending flags
 * and set the default handlers.
 *
 * It will also initialize the data structure used to handle shared IRQs.
 */
extern void irq_initialize(void);

/**
 * \brief Configure the interrupt mode for a given source.
 *
 * \param source   Interrupt source to configure
 * \param mode     Interrupt mode (Level/Edge)
 */
extern void irq_configure_mode(uint32_t source, enum _irq_mode mode);

/**
 * \brief Configure the interrupt priority for a given source.
 *
 * \param source   Interrupt source to configure
 * \param priority Interrupt priority
 */
extern void irq_configure_priority(uint32_t source, uint8_t priority);

/**
 * \brief Add a handler for a given interrupt source (ID_xxx).
 *
 * If the handler is already configured for the interrupt source, this function
 * does nothing.
 *
 * \param source   Interrupt source to configure
 * \param handler  Handler for the interrupt
 * \param user_arg User argument for the interrupt
 */
extern void irq_add_handler(uint32_t source, irq_handler_t handler, void* user_arg);

/**
 * \brief Add a handler for a given interrupt source (ID_xxx).
 *
 * If the handler is not configured for the interrupt source, this function
 * does nothing.
 *
 * \param source  Interrupt source to configure
 * \param handler handler for the interrupt
 */
extern void irq_remove_handler(uint32_t source, irq_handler_t handler);

/**
 * \brief Enable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to enable
 */
extern void irq_enable(uint32_t source);

/**
 * \brief Disable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to disable
 */
extern void irq_disable(uint32_t source);

#ifdef __cplusplus
}
#endif

#endif /* IRQ_H_ */
