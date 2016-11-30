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

#ifndef AIC_H_
#define AIC_H_

#if defined(CONFIG_HAVE_AIC2) ||\
    defined(CONFIG_HAVE_AIC5)

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include "irq/irq.h"

#include <stdint.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
 *         Global types
 *------------------------------------------------------------------------------*/

typedef void (*aic_handler_t)(void);

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize the AIC.
 *
 * This function will disable all interrupts, clear all interrupt pending flags
 * and set the default handlers.
 */
extern void aic_initialize(aic_handler_t irq_handler);

/**
 * \brief Configure a handler for a given interrupt source (ID_xxx).
 *
 * \param source  Interrupt source to configure
 * \param handler handler for the interrupt
 */
extern void aic_set_source_vector(uint32_t source, aic_handler_t handler);

/**
 * \brief Configure the spurious interrupt handler.
 *
 * \param handler handler for the spurious interrupts
 */
extern void aic_set_spurious_vector(aic_handler_t handler);

/**
 * \brief Configure the interrupt mode for a given source.
 *
 * Interrupt mode can be one of IRQ_MODE_HIGH_LEVEL, IRQ_MODE_LOW_LEVEL,
 * IRQ_MODE_POSITIVE_EDGE, IRQ_MODE_NEGATIVE_EDGE.  For internal interrupts,
 * there is no notion of Low/High levels or Positive/Negative egdes, so either
 * one can be used.
 *
 * \param source   Interrupt source to configure
 * \param mode     Interrupt mode (Level/Edge)
 */
extern void aic_configure_mode(uint32_t source, enum _irq_mode mode);

/**
 * \brief Configure the interrupt priority for a given source.
 *
 * \param source   Interrupt source to configure
 * \param priority Interrupt priority
 */
extern void aic_configure_priority(uint32_t source, uint8_t priority);

/**
 * \brief Enable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to enable
 */
extern void aic_enable(uint32_t source);

/**
 * \brief Disable interrupts coming from the given source (ID_xxx).
 *
 * \param source  Interrupt source to disable
 */
extern void aic_disable(uint32_t source);

/**
 * \brief Get the current interrupt source number
 *
 * \return Interrupt source number
 */
extern uint32_t aic_get_current_interrupt_source(void);

/**
 * \brief Configure protection mode and general interrupt mask for debug.
 *
 * \param aic     AIC instance
 * \param protect Enable/Disable protection mode
 * \param mask    Enable/Disable mask IRQ and FIQ
 */
extern void aic_set_debug_config(Aic* aic, bool protect, bool mask);

/**
 * \brief Configure AIC write protection.
 *
 * \param aic     AIC instance
 * \param enable  Enable/Disable AIC write protection mode
 */
extern void aic_set_write_protection(Aic* aic, bool enable);

/**
 * \brief Get AIC Write Protection Violation Status.
 *
 * \param aic     AIC instance
 * \param wpvsrc  pointer to uint32_t to store the violation source
 * \return false if no violation occured, true otherwise.
 */
extern bool aic_check_write_protection_violation(Aic* aic, uint32_t *wpvsrc);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_AIC2 || CONFIG_HAVE_AIC5 */

#endif /* AIC_H_ */
