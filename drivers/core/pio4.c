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
 * </li>
 * </ul>
 *
 * For more accurate information, please look at the PIT section of the Datasheet.
 *
 * Related files :\n
 * \ref pio.c\n
 * \ref pio3.h\n
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
#include "core/pio.h"
#include "core/pmc.h"
#include "core/aic.h"

#include "utils/trace.h"

#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local define
 *----------------------------------------------------------------------------*/

/* Maximum number of interrupt sources that can be defined. This
 * constant can be increased, but the current value is the smallest possible
 * that will be compatible with all existing projects. */
#define MAX_INTERRUPT_SOURCES       7

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/**
 * Describes a PIO interrupt source, including the PIO instance triggering the
 * interrupt and the associated interrupt handler.
 */
struct _interrupt_source {
	const struct _pin *pin;					/* Pointer to the source pin instance. */
	void (*handler) (const struct _pin *); 	/* Interrupt handler. */
} ;

struct _bitfield_pio_cfgr_func {
	uint32_t
	func		: 3,
	rfu3_7		: 5,
	dir		: 1,
	puen		: 1,
	pden		: 1,
	rfu11		: 1,
	ifen		: 1,
	ifscen		: 1,
	opd		: 1,
	schmitt		: 1,
	drvstr		: 2,
	rfu18_23	: 6,
	evtsel		: 3,
	rfu27_28	: 2,
	pcfs		: 1,
	icfs		: 1,
	tampen		: 1;
};

union _pio_cfg {
	struct _bitfield_pio_cfgr_func bitfield;
	uint32_t uint32_value;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* List of interrupt sources. */
static struct _interrupt_source int_sources[MAX_INTERRUPT_SOURCES];

/* Number of currently defined interrupt sources. */
static uint32_t num_sources = 0;

const uint8_t idt[PIOIO_GROUP_NUMBER] = {ID_PIOA, ID_PIOB, ID_PIOC, ID_PIOD};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static inline uint32_t get_pio_id_from_group(uint32_t group) {
	switch(group) {
	case PIO_GROUP_A:
		return ID_PIOA;
	case PIO_GROUP_B:
		return ID_PIOB;
	case PIO_GROUP_C:
		return ID_PIOC;
	case PIO_GROUP_D:
		return ID_PIOD;
	default:
		return ID_PERIPH_COUNT;
	}
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures a list of Pin instances, each of which can either hold a single
 * pin or a group of pins, depending on the mask value; all pins are configured
 * by this function. The size of the array must also be provided and is easily
 * computed using PIO_LISTSIZE whenever its length is not known in advance.
 *
 * \param list  Pointer to a list of _pin instances.
 * \param size  Size of the _pin list (calculated using PIN_LISTSIZE).
 *
 * \return 1 if the pins have been configured properly; otherwise 0.
 */

uint8_t pio_configure(const struct _pin *pin_list, uint32_t size)
{
	union _pio_cfg cfg;
	uint8_t group;
	PioIo_group* pioiog;

	/* Configure pins */
	while (size--)
	{
		assert(pin_list->id < PIO_GROUP_LENGTH);
		cfg.uint32_value = 0;
		group = pin_list->id;
		pioiog = &pin_list->pio->PIO_IO_GROUP[group];

		if ( pin_list->attribute != PIO_DEFAULT) {
			cfg.bitfield.puen = (pin_list->attribute & PIO_PULLUP)? 1:0 ;
			cfg.bitfield.pden = (pin_list->attribute & PIO_PULLDOWN)? 1:0 ;
			cfg.bitfield.ifen = (pin_list->attribute & PIO_DEGLITCH)? 1:0 ;
			cfg.bitfield.ifscen = (pin_list->attribute & PIO_FILTER_SLOW_CLOCK)? 1:0 ;
			cfg.bitfield.opd	= (pin_list->attribute & PIO_OPENDRAIN)? 1:0 ;
			cfg.bitfield.schmitt	= (pin_list->attribute & PIO_TRIGGER_DIS)? 1:0 ;
			cfg.bitfield.drvstr = pin_list->attribute & PIO_DRVSTR_Msk;
			cfg.bitfield.evtsel = pin_list->attribute & PIO_EVTSEL_Msk;
			cfg.bitfield.pcfs = (pin_list->attribute & PIO_PCFS_FREEZE)? 1:0 ;
			cfg.bitfield.icfs = (pin_list->attribute & PIO_ICFS_FREEZE)? 1:0 ;
			/* cfg.bitfield.tampen = (pin_list->attribute & PIO_TAMPEN_FREEZE)? 1:0 ; */
		}

		switch ( pin_list->type ){

		case PIO_PERIPH_A:
			cfg.bitfield.func = PIO_CFGR_FUNC_PERIPH_A;
			break;
		case PIO_PERIPH_B:
			cfg.bitfield.func = PIO_CFGR_FUNC_PERIPH_B;
			break;
		case PIO_PERIPH_C:
			cfg.bitfield.func = PIO_CFGR_FUNC_PERIPH_C;
			break;
		case PIO_PERIPH_D:
			cfg.bitfield.func = PIO_CFGR_FUNC_PERIPH_D;
			break;
		case PIO_PERIPH_E:
			cfg.bitfield.func = PIO_CFGR_FUNC_PERIPH_E;
			break;

		case PIO_GENERIC:
		case PIO_INPUT:
			cfg.bitfield.dir = 0;
			break;

		case PIO_OUTPUT_0:
			cfg.bitfield.dir = 1;
			pio_clear(pin_list);
			break;

		case PIO_OUTPUT_1:
			cfg.bitfield.dir = 1;
			pio_set(pin_list);
			break;

		default:
		case PIO_PERIPH_F:
		case PIO_PERIPH_G:
			return 0;
		}

		pioiog->PIO_MSKR = pin_list->mask;
		pioiog->PIO_CFGR = cfg.uint32_value;

		/* Enable the PIO group if needed */
		uint32_t pio_group = get_pio_id_from_group(pin_list->id);
		pmc_enable_peripheral(pio_group);

		++pin_list;
	}
	return 1;
}

/**
 * \brief Sets a high output level on all the PIOs defined in the given Pin instance.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will memorize the value they are changed to outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_set(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];
	pioiog->PIO_SODR = pin->mask;
}

/**
 * \brief Sets a low output level on all the PIOs defined in the given Pin instance.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will memorize the value they are changed to outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_clear(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];
	pioiog->PIO_CODR = pin->mask;
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin instance currently have
 * a high level; otherwise returns 0. This method returns the actual value that
 * is being read on the pin. To return the supposed output value of a pin, use
 * pio_get_output_date_status() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that currently has
 * a high level; otherwise 0.
 */
uint8_t pio_get(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
    uint32_t reg ;
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];

    if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1)) {
	reg = pioiog->PIO_ODSR ;
    }
    else {
	reg = pioiog->PIO_PDSR ;
    }
    if ( (reg & pin->mask) == 0 ) {
	return 0 ;
    }
    else {
	return 1 ;
    }
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin are configured to output a
 * high level (even if they are not output).
 * To get the actual value of the pin, use pio_get() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that is configured
 * to output a high level; otherwise 0.
 */
uint8_t pio_get_output_data_status(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];
	if ((pioiog->PIO_ODSR & pin->mask) == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

/**
 * \brief Configures Glitch or Debouncing filter for input.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 * \param cuttoff  Cutt off frequency for debounce filter.
 */
void pio_set_debounce_filter(const struct _pin *pin, uint32_t cuttoff)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	Pio *pio = pin->pio;
	if (cuttoff == 0) {
	   pio->S_PIO_SCDR = 0;
	}
	else {
		/* the lowest 14 bits work */
		pio->S_PIO_SCDR = ((32678/(2*(cuttoff))) - 1) & 0x3FFF;
	}
}

/**
 * \brief Enable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_enable_write_protect(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_EN  );
}

/**
 * \brief Disable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_disable_write_protect(const struct _pin *pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_DIS );
}

/**
 * \brief Get write protect violation information.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
uint32_t pio_get_write_protect_violation_info(const struct _pin * pin)
{
	assert(pin->id < PIO_GROUP_LENGTH);
	Pio *pio = pin->pio;
	return pio->PIO_WPSR;
}

/**
 * \brief Configure all pio output low
 *
 * \param pio  Pointer to a Pio instance describing one or more pins.
 * \param pioId PIO ID
 * \param mask  Bitmask of one or more pin(s) to configure.
 */
void pio_output_low (Pio *pio, uint32_t pioId ,uint32_t mask)
{
}

uint32_t pio_get_interrupt_status(const struct _pin *pin)
{
	return pin->pio->PIO_IO_GROUP[pin->id].PIO_ISR;
}

/**
 * \brief Handles all interrupts on the given PIO controller.
 * \param id  PIO controller ID.
 * \param pPio  PIO controller base address.
 */
static void _pio_it_handler(uint8_t id)
{
	uint32_t status;
	uint32_t i;
	PioIo_group* pioiog = &PIO_ADD->PIO_IO_GROUP[id];

	/* Read PIO controller status */
	status = pioiog->PIO_ISR;
	status &= pioiog->PIO_IMR;

	/* Check pending events */
	if (status != 0) {
		trace_debug("PIO interrupt on PIO controller #%d\n\r", id);
		/* Find triggering source */
		i = 0;
		while (status != 0) {
			/* There cannot be an unconfigured source enabled. */
			assert(i < num_sources);
			/* Source is configured on the same controller */
			if ( int_sources[i].pin->id == id) {
				/* Source has PIOs whose statuses have changed */
				if ((status & int_sources[i].pin->mask) != 0) {
					trace_debug ("Interrupt source #%d triggered\n\r", i);
					int_sources[i].handler(int_sources[i].pin);
					status &= ~(int_sources[i].pin->mask);
				}
			}
			i++;
		}
	}
}


/*----------------------------------------------------------------------------
 *        Global Functions
 *----------------------------------------------------------------------------*/

/**
 * Generic PIO interrupt handler. Single entry point for interrupts coming
 * from any PIO controller (PIO A, B, C ...). Dispatches the interrupt to
 * the user-configured handlers.
 */
void pio_it_handlers(void)
{
	uint8_t i;
	for(i=0; i<PIOIO_GROUP_NUMBER; i++) {
		_pio_it_handler(idt[i]);
	}
}

/**
 * \brief Initializes the PIO interrupt management logic
 *
 * The desired priority of PIO interrupts must be provided.
 * Calling this function multiple times result in the reset of currently
 * configured interrupts.
 *
 * \param priority  PIO controller interrupts priority.
 */
void pio_initialize_it(uint32_t priority)
{
	/* uint8_t i; */
	/* uint32_t status, id ; */

	/* trace_debug("pio_initialize_it()\n\r"); */
	/* /\* Reset sources *\/ */
	/* num_sources = 0; */

	/* for(i=0; i<PIOIO_GROUP_NUMBER; i++) { */
	/* 	/\* Configure PIO interrupt sources *\/ */
	/* 	id = idt[i]; */
	/* 	trace_debug("PIO_Initialize: Configuring PIO%c \n\r", 0x40+id); */
	/* 	pmc_enable_peripheral(id); */
	/* 	PioIo_group* pioiog = &PIO_ADD->PIO_IO_GROUP[id]; */
	/* 	/\* Read PIO Interrupt Status Register *\/ */
	/* 	status = pioiog->PIO_ISR; */
	/* 	(void)status; */
	/* 	/\* Disable all interrupt *\/ */
	/* 	pioiog->PIO_IDR = 0xFFFFFFFF; */
	/* 	aic_enable(id); */
	/* } */
}

/**
 * Configures a PIO or a group of PIO to generate an interrupt on status
 * change. The provided interrupt handler will be called with the triggering
 * pin as its parameter (enabling different pin instances to share the same
 * handler).
 * \param pPin  Pointer to a Pin instance.
 */
void pio_configure_it(const struct _pin *pin)
{
	trace_debug("pio_configure_it()\n\r");
	assert(pin != NULL);
	assert(num_sources < MAX_INTERRUPT_SOURCES);
	struct _interrupt_source *p_int_source;
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];

	// Add pio interrupt to int_sources
	p_int_source = &(int_sources[num_sources]);
	p_int_source->pin = pin;
	num_sources++;
	/* disable additional interrupt mode */
	pioiog->PIO_ISR;
	pioiog->PIO_IDR = 0xFFFFFFFF;
	aic_enable(pio_group_to_id(pin->id));
}

/**
 * Enables the given interrupt source if it has been configured. The status
 * register of the corresponding PIO controller is cleared prior to enabling
 * the interrupt.
 * \param pin  Interrupt source to enable.
 */
void pio_enable_it(const struct _pin *pin)
{
	trace_debug("pio_enable_it() \n\r");
	assert(pin != NULL);
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];

#ifndef NOASSERT
	uint32_t i = 0;
	uint32_t dwFound = 0;

	while ((i < num_sources) && !dwFound) {
		if (int_sources[i].pin == pin) {
			dwFound = 1;
		}
		i++;
	}
	assert(dwFound != 0);
#endif

	i = pioiog->PIO_ISR;
 	/* Configure interrupt enable register */
	pioiog->PIO_IER = pin->mask;	/* enable interrupt register */
}

/**
 * Disables a given interrupt source, with no added side effects.
 *
 * \param pin  Interrupt source to disable.
 */
void pio_disable_it(const struct _pin *pin)
{
	assert(pin != NULL);
	trace_debug("pio_enable_it()\n\r");
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];
	pioiog->PIO_IDR = pin->mask;
}
