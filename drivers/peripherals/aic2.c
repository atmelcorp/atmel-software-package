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

/** \addtogroup aic_module
 *
 * \section Purpose
 * The Advanced Interrupt Controller (AIC) is an 8-level priority, individually
 * maskable, vectored interrupt controller, providing handling of up to 32 interrupt sources.
 *
 * \section Usage
 * <ul>
 * <li> Each interrupt source can be enabled or disabled by using the aic_enable() and aic_disable()</li>
 * </ul>
 *
 * For more accurate information, please look at the AIC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref aic2.c\n
 * \ref aic.h\n
 */
/*@{*/
/*@}*/

/**
* \file
*
* Implementation of Advanced Interrupt Controller (AIC) controller.
*
*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/aic.h"
#include "peripherals/matrix.h"

#include <stdint.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local constants
 *------------------------------------------------------------------------------*/

#define MAX_HANDLER_NODES (ID_PERIPH_COUNT * 2)

/*------------------------------------------------------------------------------
 *         Local types
 *------------------------------------------------------------------------------*/

struct handler_node {
	void (*handler)(void);
	struct handler_node* next;
};

/*------------------------------------------------------------------------------
 *         Local variables
 *------------------------------------------------------------------------------*/

static struct handler_node handler_node_pool[MAX_HANDLER_NODES];
static struct handler_node* next_free_handler_node;
static struct handler_node* handlers[ID_PERIPH_COUNT];

/*------------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------------*/

static void _initialize_handler_node_pool(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(handler_node_pool); i++) {
		handler_node_pool[i].handler = NULL;
		handler_node_pool[i].next = &handler_node_pool[i + 1];
	}
	handler_node_pool[i - 1].next = NULL;

	next_free_handler_node = &handler_node_pool[0];
}

static struct handler_node* _alloc_handler_node(void (*handler)(void))
{
	struct handler_node* node;

	assert(next_free_handler_node);

	node = next_free_handler_node;
	next_free_handler_node = next_free_handler_node->next;
	node->handler = handler;
	node->next = NULL;
	return node;
}

/* unused for now, there is no aic_unset_source_vector function */
#if 0
static void _free_handler_node(struct handler_node* node)
{
	node->handler = NULL;
	node->next = next_free_handler_node;
	next_free_handler_node = node;
}
#endif

/**
 * \brief Default interrupt handler.
 */
static void _aic_default_irq_handler(void)
{
	struct handler_node *node = handlers[aic_get_current_interrupt_identifier()];

	if (!node) {
		// no handler for interrupt, block
		while (1);
	}

	while (node && node->handler) {
		node->handler();
		node = node->next;
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Set the default handler for all interrupts
 */
void aic_initialize(void)
{
	int i;

	/* Disable interrupts at core level */
	irq_disable_all();

	/* Disable all interrupts */
	AIC->AIC_IDCR = 0xffffffffu;

	/* Clear All pending interrupts flags */
	AIC->AIC_ICCR = 0xffffffffu;

	/* Perform 8 IT acknowledge (write any value in EOICR) */
	for (i = 0; i < 8; i++)
		aic_end_interrupt(AIC);

	/* Assign default handler */
	_initialize_handler_node_pool();
	for (i = 0; i < ID_PERIPH_COUNT; i++) {
		handlers[i] = NULL;
		AIC->AIC_SVR[i] = (uint32_t)_aic_default_irq_handler;
	}
	aic_set_spurious_vector(_aic_default_irq_handler);

	/* Enable interrupts at core level */
	irq_enable_all();
}

/**
 * \brief Enables interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to enable.
 */
void aic_enable(uint32_t source)
{
	AIC->AIC_IECR = 1 << source;
}

/**
 * \brief Disables interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to disable.
 */
void aic_disable(uint32_t source)
{
	AIC->AIC_IDCR = 1 << source;
}

/**
 * \brief Configure interrupts' source mode.
 *
 * \param source  Interrupt source to configure.
 * \param mode    mode combined of priority level and interrupt source type.
 */
void aic_configure(uint32_t source, uint32_t mode)
{
	/* Disable the interrupt first */
	AIC->AIC_IDCR = 1 << source;

	/* Configure mode */
	AIC->AIC_SMR[source] = mode;

	/* Clear interrupt */
	AIC->AIC_ICCR = 1 << source;
}

/**
 * \brief Configure corresponding handler for the interrupts coming from the given (unique) source (ID_xxx).
 *
 * \param source  Interrupt source to configure.
 * \param handler handler for the interrupt.
 */
void aic_set_source_vector(uint32_t source, void (*handler)(void))
{
	struct handler_node* node = _alloc_handler_node(handler);
	node->next = handlers[source];
	handlers[source] = node;
}

/**
 * \brief Configure the spurious interrupt handler
 *
 * \param handler handler for the interrupt.
 */
void aic_set_spurious_vector(void (*handler)(void))
{
	if (AIC->AIC_WPMR & AIC_WPMR_WPEN)
		aic_write_protection(AIC, false);

	AIC->AIC_SPU = (uint32_t)handler;
}

/**
 * \brief Configure interrupts' source mode.
 *
 * \param source  Interrupt source to configure.
 * \param mode    mode combined of priority level and interrupt source type.
 */
void aic_set_or_clear(uint32_t source, bool set)
{
	if (set) {
		AIC->AIC_ISCR = 1 << source;
	} else {
		AIC->AIC_ICCR = 1 << source;
	}
}

/**
 * \brief Indicate treatment completion for interrupts coming from the given AIC and (unique) source (ID_xxx).
 *
 * \param aic  AIC instance.
 */
void aic_end_interrupt(Aic * aic)
{
	AIC->AIC_EOICR = AIC_EOICR_ENDIT;
}

/**
 * \brief Configuration of protection mode and general interrupt mask for debug.
 *
 * \param aic     AIC instance.
 * \param protect Enable/Disable protection mode.
 * \param mask    Enable/Disable mask IRQ and FIQ.
 *
 * \retval        0 - succeed.  1 - failed.
 */
uint32_t aic_debug_config(Aic * aic, bool protect, bool mask)
{
	uint32_t dcr;

	/* return in case the "Write Protection Mode" is enabled */
	if (aic->AIC_WPMR & AIC_WPMR_WPEN)
		return 1;

	dcr = 0;
	if (protect)
		dcr |= AIC_DCR_PROT;
	if (mask)
		dcr |= AIC_DCR_GMSK;
	aic->AIC_DCR = dcr;

	return 0;
}

/**
 * \brief Enable/Disable AIC write protection mode.
 *
 * \param aic     AIC instance.
 * \param enable  Enable/Disable AIC write protection mode.
 */
void aic_write_protection(Aic * aic, bool enable)
{
	if (enable) {
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD | AIC_WPMR_WPEN;
	} else {
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD;
	}
}

/**
 * \brief Get AIC Write Protection Status.
 *
 * \param aic     AIC instance.
 * \param pViolationSource pointer to address to store the violation source
 *
 * \retval        0 - No violation occured.  1 - violation occured.
 */
uint32_t aic_violation_occured(Aic * aic, uint32_t * pViolationSource)
{
	if (aic->AIC_WPSR & AIC_WPSR_WPVS) {
		*pViolationSource =
		    (aic->
		     AIC_WPSR & AIC_WPSR_WPVSRC_Msk) >> AIC_WPSR_WPVSRC_Pos;
	}
	return 0;
}

/**
 * \brief Get AIC Current Interrupt Identifier.
 *
 * \retval      IRQID: Current Interrupt Identifier
 */
uint32_t aic_get_current_interrupt_identifier(void)
{
	return AIC->AIC_ISR;
}

