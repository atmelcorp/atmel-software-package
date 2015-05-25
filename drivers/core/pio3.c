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

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral A. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralA(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		//pio->PIO_PUDR = mask;
		pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] &= (~mask & abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] &= (~mask & abcdsr);
	pio->PIO_PDR = mask;

}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral B. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralB(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
		pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] = (mask | abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] &= (~mask & abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral C. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralC(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
		//  pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] &= (~mask & abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] = (mask | abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral D. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralD(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] = (mask | abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] = (mask | abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) or a PIO controller as inputs. Optionally,
 * the corresponding internal pull-up(s) and glitch filter(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask indicating which pin(s) to configure as input(s).
 * \param enablePullUp  Indicates if the internal pull-up(s) must be enabled.
 * \param enableFilter  Indicates if the glitch filter(s) must be enabled.
 */
static void pio_set_input(Pio * pio, uint32_t mask, uint8_t attribute)
{
	/* Disable interrupts */
	pio->PIO_IDR = mask;
	/* Enable pull-up(s) if necessary */
	if (attribute & PIO_PULLUP) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	/* Enable Input Filter if necessary */
	if (attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
		pio->PIO_IFER = mask;
	else
		pio->PIO_IFDR = mask;
	/* Enable de-glitch or de-bounce if necessary */
	if (attribute & PIO_DEGLITCH) {
		pio->PIO_IFSCDR = mask;
	} else if (attribute & PIO_DEBOUNCE) {
		pio->PIO_IFSCER = mask;
	}
	/* Configure pin as input */
	pio->PIO_ODR = mask;
	pio->PIO_PER = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as outputs, with the
 * given default value. Optionally, the multi-drive feature can be enabled
 * on the pin(s).
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask indicating which pin(s) to configure.
 * \param defaultValue  Default level on the pin(s).
 * \param enableMultiDrive  Indicates if the pin(s) shall be configured as
 *                          open-drain.
 * \param enablePullUp  Indicates if the pin shall have its pull-up activated.
 */
static void pio_set_output(Pio * pio, uint32_t mask, uint8_t defaultValue,
						  uint8_t enableMultiDrive, uint8_t enablePullUp)
{
	/* Disable interrupts */
	pio->PIO_IDR = mask;

	/* Enable pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	/* Enable multi-drive if necessary */
	if (enableMultiDrive) {
		pio->PIO_MDER = mask;
	} else {

		pio->PIO_MDDR = mask;
	}
	/* Set default value */
	if (defaultValue) {

		pio->PIO_SODR = mask;
	} else {

		pio->PIO_CODR = mask;
	}
	/* Configure pin(s) as output(s) */
	pio->PIO_OER = mask;
	pio->PIO_PER = mask;
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
 * \param list  Pointer to a list of Pin instances.
 * \param size  Size of the Pin list (calculated using PIO_LISTSIZE).
 *
 * \return 1 if the pins have been configured properly; otherwise 0.
 */
uint8_t pio_configure(const struct _pin *list, uint32_t size)
{
	/* Configure pins */
	while (size > 0) {
		switch (list->type) {

		case PIO_PERIPH_A:
			pio_set_peripheralA(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_B:
			pio_set_peripheralB(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_C:
			pio_set_peripheralC(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_D:
			pio_set_peripheralD(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;
		case PIO_INPUT:
			pmc_enable_peripheral(list->id);
			pio_set_input(list->pio, list->mask, list->attribute);
			break;

		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			pio_set_output(list->pio, list->mask,
				      (list->type == PIO_OUTPUT_1),
				      (list->attribute & PIO_OPENDRAIN) ? 1 : 0,
				      (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		default:
			return 0;
		}
		list++;
		size--;
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
	pin->pio->PIO_SODR = pin->mask;
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
	pin->pio->PIO_CODR = pin->mask;
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
	uint32_t reg;

	if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1)) {
		reg = pin->pio->PIO_ODSR;
	} else {
		reg = pin->pio->PIO_PDSR;
	}
	if ((reg & pin->mask) == 0) {
		return 0;
	} else {
		return 1;
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
	if ((pin->pio->PIO_ODSR & pin->mask) == 0) {
		return 0;
	} else {
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
	Pio *pio = pin->pio;

	if (cuttoff == 0) {
		pio->PIO_IFSCDR = pin->mask;
		pio->PIO_SCDR = 0;
	} else {
		/* set Debouncing, 0 bit field no effect */
		pio->PIO_IFSCER = pin->mask;
		/* the lowest 14 bits work */
		pio->PIO_SCDR = ((32678 / (2 * (cuttoff))) - 1) & 0x3FFF;
	}
}

/**
 * \brief Enable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_enable_write_protect(const struct _pin *pin)
{
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_EN);
}

/**
 * \brief Disable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_disable_write_protect(const struct _pin *pin)
{
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_DIS);
}

/**
 * \brief Get write protect violation information.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
uint32_t pio_get_write_protect_violation_info(const struct _pin * pin)
{
	Pio *pio = pin->pio;
	return (pio->PIO_WPSR);
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
	PMC->PMC_PCER0 = 1 << pioId;
	pio->PIO_PUDR = mask;	// all Pull-up Disable
	pio->PIO_PPDDR = mask;	// all Pull-down Disable
	pio->PIO_PER = mask;	// all PIO enable
	pio->PIO_OER = mask;	// all PIO output mode
	pio->PIO_CODR = mask;	// all PIO clear output
}

uint32_t pio_get_interrupt_status (const struct _pin *pin)
{
	return pin->pio->PIO_ISR;
}


/*----------------------------------------------------------------------------
 *        Local definitions
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
typedef struct _InterruptSource {
	/* Pointer to the source pin instance. */
	const struct _pin *pPin;

	/* Interrupt handler. */
	void (*handler) (const struct _pin *);
} InterruptSource;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* List of interrupt sources. */
static InterruptSource _aIntSources[MAX_INTERRUPT_SOURCES];

/* Number of currently defined interrupt sources. */
static uint32_t _dwNumSources = 0;

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Handles all interrupts on the given PIO controller.
 * \param id  PIO controller ID.
 * \param pPio  PIO controller base address.
 */
static void _pio_it_handler(uint32_t id, Pio * pPio)
{
	uint32_t status;
	uint32_t i;

	/* Read PIO controller status */
	status = pPio->PIO_ISR;
	status &= pPio->PIO_IMR;

	/* Check pending events */
	if (status != 0) {
		trace_debug("PIO interrupt on PIO controller #%d\n\r", id);

		/* Find triggering source */
		i = 0;
		while (status != 0) {
			/* There cannot be an unconfigured source enabled. */
			assert(i < _dwNumSources);

			/* Source is configured on the same controller */
			if (_aIntSources[i].pPin->id == id) {
				/* Source has PIOs whose statuses have changed */
				if ((status & _aIntSources[i].pPin->mask) != 0) {
					trace_debug
					    ("Interrupt source #%d triggered\n\r",
					     i);

					_aIntSources[i].handler(_aIntSources[i].
								pPin);
					status &= ~(_aIntSources[i].pPin->mask);
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
	_pio_it_handler(ID_PIOA, PIOA);
	_pio_it_handler(ID_PIOB, PIOB);
	_pio_it_handler(ID_PIOC, PIOC);
	_pio_it_handler(ID_PIOD, PIOD);
	_pio_it_handler(ID_PIOE, PIOE);
}

/**
 * \brief Initializes the PIO interrupt management logic
 *
 * The desired priority of PIO interrupts must be provided.
 * Calling this function multiple times result in the reset of currently
 * configured interrupts.
 *
 * \param dwPriority  PIO controller interrupts priority.
 */
void pio_initialize_it(uint32_t dwPriority)
{
	/* trace_debug("PIO_Initialize()\n\r"); */

	/* /\* Reset sources *\/ */
	/* _dwNumSources = 0; */

	/* /\* Configure PIO interrupt sources *\/ */
	/* trace_debug("PIO_Initialize: Configuring PIOA\n\r"); */
	/* pmc_enable_peripheral(ID_PIOA); */
	/* PIOA->PIO_ISR; */
	/* PIOA->PIO_IDR = 0xFFFFFFFF; */
	/* aic_enable(ID_PIOA); */

	/* /\* Configure PIO interrupt sources *\/ */
	/* trace_debug("PIO_Initialize: Configuring PIOB\n\r"); */
	/* PIOB->PIO_ISR; */
	/* PIOB->PIO_IDR = 0xFFFFFFFF; */
	/* aic_enable(ID_PIOB); */

	/* /\* Configure PIO interrupt sources *\/ */
	/* trace_debug("PIO_Initialize: Configuring PIOC\n\r"); */
	/* pmc_enable_peripheral(ID_PIOC); */
	/* PIOC->PIO_ISR; */
	/* PIOC->PIO_IDR = 0xFFFFFFFF; */
	/* aic_enable(ID_PIOC); */

	/* /\* Configure PIO interrupt sources *\/ */
	/* trace_debug("PIO_Initialize: Configuring PIOD\n\r"); */
	/* pmc_enable_peripheral(ID_PIOD); */
	/* PIOD->PIO_ISR; */
	/* PIOD->PIO_IDR = 0xFFFFFFFF; */
	/* aic_enable(ID_PIOD); */

	/* /\* Configure PIO interrupt sources *\/ */
	/* trace_debug("PIO_Initialize: Configuring PIOC\n\r"); */
	/* pmc_enable_peripheral(ID_PIOE); */
	/* PIOE->PIO_ISR; */
	/* PIOE->PIO_IDR = 0xFFFFFFFF; */
	/* aic_enable(ID_PIOE); */
}

/**
 * Configures a PIO or a group of PIO to generate an interrupt on status
 * change. The provided interrupt handler will be called with the triggering
 * pin as its parameter (enabling different pin instances to share the same
 * handler).
 * \param pPin  Pointer to a _pin instance.
 */
void pio_configure_it(const struct _pin * pPin)
{
	Pio *pio;
	InterruptSource *pSource;
	
	trace_debug("Enter in pio_configure_it()\n\r");

	assert(pPin);
	pio = pPin->pio;
	
	trace_debug("Enable PIO group\n\r");
	pmc_enable_peripheral(pio_group_to_id(pPin->id));
	pio->PIO_ISR;
	pio->PIO_IDR = 0xFFFFFFFF;
	aic_enable(pio_group_to_id(pPin->id));
	
	assert(_dwNumSources < MAX_INTERRUPT_SOURCES);

	pSource = &(_aIntSources[_dwNumSources]);
	pSource->pPin = pPin;
	_dwNumSources++;

	/* PIO with additional interrupt support
	 * Configure additional interrupt mode registers */
	if (pPin->attribute & PIO_IT_AIME) {
		/* enable additional interrupt mode */
		pio->PIO_AIMER = pPin->mask;

		/* if bit field of selected pin is 1, set as Rising Edge/High level detection event */
		if (pPin->attribute & PIO_IT_RE_OR_HL) {
			pio->PIO_REHLSR = pPin->mask;
		} else {
			pio->PIO_FELLSR = pPin->mask;
		}

		/* if bit field of selected pin is 1, set as edge detection source */
		if (pPin->attribute & PIO_IT_EDGE)
			pio->PIO_ESR = pPin->mask;
		else
			pio->PIO_LSR = pPin->mask;
	} else {
		/* disable additional interrupt mode */
		pio->PIO_AIMDR = pPin->mask;
	}
}

/**
 * Enables the given interrupt source if it has been configured. The status
 * register of the corresponding PIO controller is cleared prior to enabling
 * the interrupt.
 * \param pPin  Interrupt source to enable.
 */
void pio_enable_it(const struct _pin * pPin)
{
	trace_debug("Enter in pio_enable_it()\n\r");

	assert(pPin != NULL);

#ifndef NOASSERT
	uint32_t i = 0;
	uint32_t dwFound = 0;

	while ((i < _dwNumSources) && !dwFound) {
		if (_aIntSources[i].pPin == pPin) {
			dwFound = 1;
		}
		i++;
	}
	assert(dwFound != 0);
#endif

	pPin->pio->PIO_ISR;
	pPin->pio->PIO_IER = pPin->mask;
}

/**
 * Disables a given interrupt source, with no added side effects.
 *
 * \param pPin  Interrupt source to disable.
 */
void pio_disable_it(const struct _pin * pPin)
{
	assert(pPin != NULL);

	trace_debug("Enter in pio_disable_it()\n\r");

	pPin->pio->PIO_IDR = pPin->mask;
}
