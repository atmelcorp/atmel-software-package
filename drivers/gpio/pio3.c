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

/** \addtogroup pio_module Working with PIO
 * \section Purpose
 * The PIO driver provides the Interface for configuration the Parallel Input/Output
 *  Controller (PIO).
 *
 * \section Usage
 * <ul>
 * <li>  Initialize the PIO with the desired period using pio_configure().
 * <li>  Set a high or low output level on the given PIO using pio_set() or pio_clear().
 * <li>  Get the level of the given PIOs using pio_get() or pio_get_output_date_status().
 * <li>  Configures Glitch or Debouncing filter for given input PIO using pio_set_debounce_filter().
 * <li>  Enable & disable write protect of the given PIOs using pio_enable_write_protect() or pio_disable_write_protect().
 * <li>  Get write protect violation information of given PIO using pio_get_write_protect_violation_info().
 * </ul>
 *
 * For more accurate information, please look at the PIO section of the Datasheet.
 *
 * Related files:\n
 * \ref pio.h\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of PIO V3 (Parallel Input/Output) controller.
 *
 */
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "irq/irq.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"

#include "trace.h"
#include "compiler.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

struct _handler {
	uint32_t      group;
	uint32_t      mask;
	pio_handler_t handler;
	void         *user_arg;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _handler _handlers[IRQ_PIO_HANDLERS_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static bool _pio_has_group(uint32_t group)
{
#ifdef ID_PIOA
	if (group == 0)
		return true;
#endif
#ifdef ID_PIOB
	if (group == 1)
		return true;
#endif
#ifdef ID_PIOC
	if (group == 2)
		return true;
#endif
#ifdef ID_PIOD
	if (group == 3)
		return true;
#endif
#ifdef ID_PIOE
	if (group == 4)
		return true;
#endif
	return false;
}

static uint32_t _pio_get_group_mask(uint32_t id)
{
	uint32_t group = 0;

#ifdef ID_PIOA
	if (id == ID_PIOA)
		group |= (1 << PIO_GROUP_A);
#endif
#ifdef ID_PIOB
	if (id == ID_PIOB)
		group |= (1 << PIO_GROUP_B);
#endif
#ifdef ID_PIOC
	if (id == ID_PIOC)
		group |= (1 << PIO_GROUP_C);
#endif
#ifdef ID_PIOD
	if (id == ID_PIOD)
		group |= (1 << PIO_GROUP_D);
#endif
#ifdef ID_PIOE
	if (id == ID_PIOE)
		group |= (1 << PIO_GROUP_E);
#endif

	return group;
}

static Pio* _pio_get_instance(uint32_t group)
{
	switch (group) {
#ifdef PIOA
	case PIO_GROUP_A:
		return PIOA;
#endif
#ifdef PIOB
	case PIO_GROUP_B:
		return PIOB;
#endif
#ifdef PIOC
	case PIO_GROUP_C:
		return PIOC;
#endif
#ifdef PIOD
	case PIO_GROUP_D:
		return PIOD;
#endif
#ifdef PIOE
	case PIO_GROUP_E:
		return PIOE;
#endif
	default:
		trace_fatal("Invalid PIO group!");
	}
}

static uint32_t _pio_get_periph_id(uint32_t group)
{
	switch (group) {
#ifdef ID_PIOA
	case PIO_GROUP_A:
		return ID_PIOA;
#endif
#ifdef ID_PIOB
	case PIO_GROUP_B:
		return ID_PIOB;
#endif
#ifdef ID_PIOC
	case PIO_GROUP_C:
		return ID_PIOC;
#endif
#ifdef ID_PIOD
	case PIO_GROUP_D:
		return ID_PIOD;
#endif
#ifdef ID_PIOE
	case PIO_GROUP_E:
		return ID_PIOE;
#endif
	default:
		trace_fatal("Invalid PIO group!");
	}
}

static void _handler_push(uint32_t group, uint32_t mask, pio_handler_t handler, void* user_arg)
{
	static int i = 0;
	assert(i < (ARRAY_SIZE(_handlers) - 1));
	_handlers[i].group = group;
	_handlers[i].mask = mask;
	_handlers[i].handler = handler;
	_handlers[i].user_arg = user_arg;
	i++;
}

static void _pio_handle_interrupt(uint32_t group, Pio* pio)
{
	int i;
	uint32_t status = pio->PIO_ISR;
	for (i = 0; i < ARRAY_SIZE(_handlers); i++) {
		if (_handlers[i].group == group && (_handlers[i].mask & status))
			_handlers[i].handler(group, status, _handlers[i].user_arg);
	}
}

static void _pio_handler(uint32_t source, void* user_arg)
{
	uint32_t group_mask = _pio_get_group_mask(source);

#ifdef PIOA
	if (group_mask & (1 << PIO_GROUP_A))
		_pio_handle_interrupt(PIO_GROUP_A, PIOA);
#endif
#ifdef PIOB
	if (group_mask & (1 << PIO_GROUP_B))
		_pio_handle_interrupt(PIO_GROUP_B, PIOB);
#endif
#ifdef PIOC
	if (group_mask & (1 << PIO_GROUP_C))
		_pio_handle_interrupt(PIO_GROUP_C, PIOC);
#endif
#ifdef PIOD
	if (group_mask & (1 << PIO_GROUP_D))
		_pio_handle_interrupt(PIO_GROUP_D, PIOD);
#endif
#ifdef PIOE
	if (group_mask & (1 << PIO_GROUP_E))
		_pio_handle_interrupt(PIO_GROUP_E, PIOE);
#endif
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

void pio_configure(const struct _pin *pin_list, uint32_t size)
{
	int i;

	for (i = 0; i < size; i++) {
		const struct _pin *pin = &pin_list[i];
		Pio* pio = _pio_get_instance(pin->group);

		/* Disable interrupts */
		pio->PIO_IDR = pin->mask;

		/* The PIO input logic requires the peripheral clock */
		if (pin->type == PIO_INPUT)
			pmc_configure_peripheral(_pio_get_periph_id(pin->group), NULL, true);

		/* Enable pull-up resistors as requested */
		if (pin->attribute & PIO_PULLUP)
			pio->PIO_PUER = pin->mask;
		else
			pio->PIO_PUDR = pin->mask;

		/* Enable pull-down resistors as requested */
		if (pin->attribute & PIO_PULLDOWN)
			pio->PIO_PPDER = pin->mask;
		else
			pio->PIO_PPDDR = pin->mask;

		/* Select open-drain output stage as requested */
		if (pin->attribute & PIO_OPENDRAIN)
			pio->PIO_MDER = pin->mask;
		else
			pio->PIO_MDDR = pin->mask;

		/* Enable the input filter if requested */
		if (pin->attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
			pio->PIO_IFER = pin->mask;
		else
			pio->PIO_IFDR = pin->mask;

		/* The de-bounce input filter depends on the slow clock */
		if (pin->attribute & PIO_DEBOUNCE)
			pio->PIO_IFSCER = pin->mask;
		else
			pio->PIO_IFSCDR = pin->mask;

		if (pin->attribute & PIO_NO_SCHMITT_TRIG)
			pio->PIO_SCHMITT |= pin->mask;
		else
			pio->PIO_SCHMITT &= ~pin->mask;

		if (pin->attribute & PIO_DRVSTR_MASK)
			trace_fatal("Invalid pin drive strength\r\n");

		switch (pin->attribute & PIO_IT_MASK) {
		case PIO_IT_FALL_EDGE:
			pio->PIO_AIMER = pin->mask;
			pio->PIO_ESR = pin->mask;
			pio->PIO_FELLSR = pin->mask;
			break;
		case PIO_IT_RISE_EDGE:
			pio->PIO_AIMER = pin->mask;
			pio->PIO_ESR = pin->mask;
			pio->PIO_REHLSR = pin->mask;
			break;
		case PIO_IT_BOTH_EDGE:
			pio->PIO_AIMDR = pin->mask;
			break;
		case PIO_IT_LOW_LEVEL:
			pio->PIO_AIMER = pin->mask;
			pio->PIO_LSR = pin->mask;
			pio->PIO_FELLSR = pin->mask;
			break;
		case PIO_IT_HIGH_LEVEL:
			pio->PIO_AIMER = pin->mask;
			pio->PIO_LSR = pin->mask;
			pio->PIO_REHLSR = pin->mask;
			break;
		default:
			trace_fatal("Invalid pin interrupt type\r\n");
			break;
		}

		switch (pin->type) {
		case PIO_PERIPH_A:
			pio->PIO_ABCDSR[0] &= ~pin->mask;
			pio->PIO_ABCDSR[1] &= ~pin->mask;
			pio->PIO_PDR = pin->mask;
			break;
		case PIO_PERIPH_B:
			pio->PIO_ABCDSR[0] |= pin->mask;
			pio->PIO_ABCDSR[1] &= ~pin->mask;
			pio->PIO_PDR = pin->mask;
			break;
		case PIO_PERIPH_C:
			pio->PIO_ABCDSR[0] &= ~pin->mask;
			pio->PIO_ABCDSR[1] |= pin->mask;
			pio->PIO_PDR = pin->mask;
			break;
		case PIO_PERIPH_D:
			pio->PIO_ABCDSR[0] |= pin->mask;
			pio->PIO_ABCDSR[1] |= pin->mask;
			pio->PIO_PDR = pin->mask;
			break;
		case PIO_INPUT:
			pio->PIO_ODR = pin->mask;
			pio->PIO_PER = pin->mask;
			break;
		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			/* Select the logic level to be driven */
			if (pin->type == PIO_OUTPUT_1)
				pio->PIO_SODR = pin->mask;
			else
				pio->PIO_CODR = pin->mask;
			/* Give control of the pin(s) to the PIO (vs to the
			 * peripheral), and enable the output stage */
			pio->PIO_OER = pin->mask;
			pio->PIO_PER = pin->mask;
			break;
		default:
			trace_fatal("Invalid pin type\r\n");
		}
	}
}

void pio_set(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_SODR = pin->mask;
}

void pio_clear(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_CODR = pin->mask;
}

uint32_t pio_get(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1))
		return pio->PIO_ODSR & pin->mask;
	else
		return pio->PIO_PDSR & pin->mask;
}

uint32_t pio_get_output_data_status(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	return pio->PIO_ODSR & pin->mask;
}

void pio_set_debounce_filter(uint32_t cutoff)
{
	int i;
	cutoff = ((pmc_get_slow_clock() / (2 * cutoff)) - 1) & 0x3FFF;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		if (!_pio_has_group(i))
			continue;
		Pio* pio = _pio_get_instance(i);
		pio->PIO_SCDR = cutoff;
	}
}

void pio_enable_write_protect(void)
{
	int i;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		if (!_pio_has_group(i))
			continue;
		Pio* pio = _pio_get_instance(i);
		pio->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD | PIO_WPMR_WPEN;
	}
}

void pio_disable_write_protect(void)
{
	int i;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		if (!_pio_has_group(i))
			continue;
		Pio* pio = _pio_get_instance(i);
		pio->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
	}
}

uint32_t pio_get_write_protect_violation_info(void)
{
	int i;
	uint32_t wpsr = 0;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		if (!_pio_has_group(i))
			continue;
		Pio* pio = _pio_get_instance(i);
		wpsr |= pio->PIO_WPSR;
	}
	return wpsr;
}

void pio_output_low(uint32_t group, uint32_t mask)
{
	Pio* pio = _pio_get_instance(group);
	pmc_configure_peripheral(_pio_get_periph_id(group), NULL, true);
	pio->PIO_PUDR = mask;	// all Pull-up Disable
	pio->PIO_PPDDR = mask;	// all Pull-down Disable
	pio->PIO_PER = mask;	// all PIO enable
	pio->PIO_OER = mask;	// all PIO output mode
	pio->PIO_CODR = mask;	// all PIO clear output
}

void pio_add_handler_to_group(uint32_t group, uint32_t mask,
			      pio_handler_t handler, void* user_arg)
{
	uint32_t periph_id = _pio_get_periph_id(group);

	_handler_push(group, mask, handler, user_arg);

	irq_add_handler(periph_id, _pio_handler, NULL);
	irq_enable(periph_id);
}

void pio_reset_all_it(void)
{
	int i;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		if (!_pio_has_group(i))
			continue;
		Pio* pio = _pio_get_instance(i);
		pio->PIO_ISR;
		pio->PIO_IDR = ~0u;
	}
}

void pio_enable_it(const struct _pin *pin)
{
	assert(pin);
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_ISR;
	pio->PIO_IER = pin->mask;
}

void pio_disable_it(const struct _pin *pin)
{
	assert(pin);
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_IDR = pin->mask;
}
