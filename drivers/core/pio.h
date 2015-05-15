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

#ifndef _PIO_
#define _PIO_

/*------------------------------------------------------------------------------
 *         Global Types
 *------------------------------------------------------------------------------*/

#include "chip.h"

struct _pin
{
	uint32_t mask;		/*  Bitmask indicating which pin(s) to configure. */
	Pio *pio;			/*  Pointer to the PIO controller which has the pin(s). */
	uint8_t id;			/*  Peripheral ID of the PIO controller which has the pin(s). */
	uint8_t type;		/*  Pin type */
	uint8_t attribute;	/*  Pin config attribute. */
};

#define PIO_LISTSIZE(pPins)	(sizeof(pPins) / sizeof(struct _pin))

/*
 *         Headers
 */

#if defined(API_PIOv4)
#include "core/pio4.h"
#elif defined(API_PIOv3)
#include "core/pio3.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern uint8_t pio_configure(const struct _pin *pin_list, uint32_t size);
void pio_set(const struct _pin *pin);
void pio_clear(const struct _pin *pin);
extern uint8_t pio_get(const struct _pin *pin) ;
extern uint8_t pio_get_output_data_status(const struct _pin *pin) ;
void pio_set_debounce_filter(const struct _pin *pin, uint32_t cuttoff);
void pio_enable_write_protect(const struct _pin *pin);
void pio_disable_write_protect(const struct _pin *pin);
extern uint32_t pio_get_write_protect_violation_info(const struct _pin * pin);
void pio_output_low (Pio *pio, uint32_t pioId ,uint32_t mask);


#ifdef __cplusplus
}
#endif
#endif /* _PIO_ */
