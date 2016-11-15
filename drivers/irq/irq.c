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
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
#include "irq/aic.h"
#endif
#include "irq/irq.h"
#if defined(CONFIG_HAVE_NVIC)
#include "irq/nvic.h"
#endif

#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local types
 *------------------------------------------------------------------------------*/

struct handler_entry {
	irq_handler_t handler;
	void* user_arg;
	struct handler_entry* next;
};

/*------------------------------------------------------------------------------
 *         Local variables
 *------------------------------------------------------------------------------*/

static struct handler_entry  handlers_pool[ID_PERIPH_COUNT * 2];
static struct handler_entry* next_free_handler;
static struct handler_entry* handlers[ID_PERIPH_COUNT];

/*------------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------------*/

static void _initialize_handlers_pool(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(handlers_pool); i++) {
		handlers_pool[i].handler = NULL;
		handlers_pool[i].next = &handlers_pool[i + 1];
	}
	handlers_pool[i - 1].next = NULL;

	next_free_handler = &handlers_pool[0];
}

static struct handler_entry* _alloc_handler(void)
{
	struct handler_entry* entry;

	assert(next_free_handler);

	entry = next_free_handler;
	next_free_handler = next_free_handler->next;
	entry->handler = NULL;
	entry->user_arg = NULL;
	entry->next = NULL;
	return entry;
}

static void _free_handler(struct handler_entry* entry)
{
	entry->handler = NULL;
	entry->next = next_free_handler;
	next_free_handler = entry;
}

static void _default_irq_handler(void)
{
	uint32_t source;
	struct handler_entry *entry;

#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	source = aic_get_current_interrupt_source();
#elif defined(CONFIG_HAVE_NVIC)
	source = nvic_get_current_interrupt_source();
#else
#error Unknown IRQ controller!
#endif

	entry = handlers[source];
	if (!entry) {
		// no handler for interrupt, block
		while (1);
	}

	while (entry) {
		if (entry->handler)
			entry->handler(source, entry->user_arg);
		entry = entry->next;
	}
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

void irq_initialize(void)
{
	_initialize_handlers_pool();

#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	aic_initialize(_default_irq_handler);
#elif defined(CONFIG_HAVE_NVIC)
	nvic_initialize(_default_irq_handler);
#else
#error Unknown IRQ controller!
#endif
}

void irq_configure_mode(uint32_t source, enum _irq_mode mode)
{
#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	aic_configure_mode(source, mode);
#elif defined(CONFIG_HAVE_NVIC)
	// ignored, not implemented on NVIC
#else
#error Unknown IRQ controller!
#endif
}

void irq_configure_priority(uint32_t source, uint8_t priority)
{
#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	aic_configure_priority(source, priority);
#elif defined(CONFIG_HAVE_NVIC)
	nvic_configure_priority(source, priority);
#else
#error Unknown IRQ controller!
#endif
}

void irq_add_handler(uint32_t source, irq_handler_t handler, void* user_arg)
{
	struct handler_entry* entry;

	/* check if handler is already registered */
	entry = handlers[source];
	while (entry) {
		if (entry->handler == handler) {
			entry->user_arg = user_arg;
			return;
		}
		entry = entry->next;
	}

	/* add handler to linked list */
	entry = _alloc_handler();
	entry->handler = handler;
	entry->user_arg = user_arg;
	entry->next = handlers[source];
	handlers[source] = entry;
}

void irq_remove_handler(uint32_t source, irq_handler_t handler)
{
	struct handler_entry* prev;
	struct handler_entry* cur;

	/* remove handler from linked list */
	prev = NULL;
	cur = handlers[source];
	while (cur) {
		if (cur->handler == handler) {
			if (prev)
				prev->next = cur->next;
			_free_handler(cur);
			return;
		}
		cur = cur->next;
	}
}

void irq_enable(uint32_t source)
{
#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	aic_enable(source);
#elif defined(CONFIG_HAVE_NVIC)
	nvic_enable(source);
#else
#error Unknown IRQ controller!
#endif
}

void irq_disable(uint32_t source)
{
#if defined(CONFIG_HAVE_AIC2) || defined(CONFIG_HAVE_AIC5)
	aic_disable(source);
#elif defined(CONFIG_HAVE_NVIC)
	nvic_disable(source);
#else
#error Unknown IRQ controller!
#endif
}
