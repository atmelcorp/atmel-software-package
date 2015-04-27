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

#include <string.h>

/*----------------------------------------------------------------------------
 *        Local define
 *----------------------------------------------------------------------------*/

struct _bitfield_pio_cfgr_func {
	uint32_t
	func		: 3,
	rfu3_7		: 5,
	dir			: 1,
	puen		: 1,
	pden		: 1,
	rfu11		: 1,
	ifen		: 1,
	ifscen		: 1,
	opd			: 1,
	schmitt		: 1,
	drvstr		: 2,
	rfu18_23	: 6,
	evtsel		: 3,
	rfu27_28	: 2,
	pcfs		: 1,
	icfs		: 1,
	tampen		: 1;
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/



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
	struct _bitfield_pio_cfgr_func 	bf1;
	uint8_t group;
	PioIo_group* pioiog;

	/* Configure pins */
	while (size > 0)
	{
		memset (&bf1, 0x00, sizeof(struct _bitfield_pio_cfgr_func));
		group = pin_list->id;
		pioiog = &pin_list->pio->PIO_IO_GROUP[group];

		if ( pin_list->attribute != PIO_DEFAULT) {
			bf1.puen = (pin_list->attribute & PIO_PULLUP)? 1:0 ;
			bf1.pden = (pin_list->attribute & PIO_PULLDOWN)? 1:0 ;
			bf1.ifen = (pin_list->attribute & PIO_DEGLITCH)? 1:0 ;
			bf1.ifscen = (pin_list->attribute & PIO_FILTER_SLOW_CLOCK)? 1:0 ;
			bf1.opd	= (pin_list->attribute & PIO_OPENDRAIN)? 1:0 ;
			bf1.schmitt	= (pin_list->attribute & PIO_TRIGGER_DIS)? 1:0 ;
			bf1.drvstr = pin_list->attribute & PIO_DRVSTR_Msk;
			bf1.evtsel = pin_list->attribute & PIO_EVTSEL_Msk;
			bf1.pcfs = (pin_list->attribute & PIO_PCFS_FREEZE)? 1:0 ;
			bf1.icfs = (pin_list->attribute & PIO_ICFS_FREEZE)? 1:0 ;
			bf1.tampen = (pin_list->attribute & PIO_TAMPEN_FREEZE)? 1:0 ;
		}

        switch ( pin_list->type ){

            case PIO_PERIPH_A:
				bf1.func = PIO_CFGR_FUNC_PERIPH_A;
				break;
			case PIO_PERIPH_B:
				bf1.func = PIO_CFGR_FUNC_PERIPH_B;
				break;
            case PIO_PERIPH_C:
				bf1.func = PIO_CFGR_FUNC_PERIPH_C;
				break;
            case PIO_PERIPH_D:
				bf1.func = PIO_CFGR_FUNC_PERIPH_D;
				break;
            case PIO_PERIPH_E:
				bf1.func = PIO_CFGR_FUNC_PERIPH_E;
				break;

			case PIO_GENERIC:
			case PIO_INPUT:
				bf1.dir = 0;
                break;

            case PIO_OUTPUT_0:
				bf1.dir = 1;
				pio_clear(pin_list);
                break;

			case PIO_OUTPUT_1:
				bf1.dir = 1;
				pio_set(pin_list);
                break;

            default:
			case PIO_PERIPH_F:
            case PIO_PERIPH_G:
				return 0;
        }

		pioiog->PIO_MSKR = pin_list->mask;
		memcpy ((void*)pioiog->PIO_CFGR, &bf1, sizeof(struct _bitfield_pio_cfgr_func));

  		pin_list++;
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
