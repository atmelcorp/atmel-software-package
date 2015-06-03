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

#ifndef _PIO_H
#define _PIO_H

/*------------------------------------------------------------------------------
 *         Global Types
 *------------------------------------------------------------------------------*/

#include "chip.h"

struct _pin
{
	/** Bitmask indicating which pin(s) to configure. */
	uint32_t mask;
	/** Pointer to the PIO controller which has the pin(s). */
	Pio *pio;
	/** Peripheral ID of the PIO controller which has the pin(s). */
	uint8_t id;
	/** Pin type */
	uint8_t type;
	/** Pin config attribute. */
	uint8_t attribute;
};

#define PIO_LISTSIZE(pins)	(sizeof(pins) / sizeof(struct _pin))

/*
 *         Headers
 */

#if defined(CONFIG_HAVE_PIO3)
#include "peripherals/pio3.h"
#elif defined(CONFIG_HAVE_PIO4)
#include "peripherals/pio4.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern uint8_t pio_configure(const struct _pin *pin_list, uint32_t size);
extern void pio_set(const struct _pin *pin);
extern void pio_clear(const struct _pin *pin);
extern uint8_t pio_get(const struct _pin *pin) ;
extern uint8_t pio_get_output_data_status(const struct _pin *pin) ;
extern void pio_set_debounce_filter(const struct _pin *pin, uint32_t cuttoff);
extern void pio_enable_write_protect(const struct _pin *pin);
extern void pio_disable_write_protect(const struct _pin *pin);
extern uint32_t pio_get_write_protect_violation_info(const struct _pin * pin);
extern void pio_output_low (Pio *pio, uint32_t pioId ,uint32_t mask);

extern void pio_reset_all_it(void);
extern void pio_configure_it(const struct _pin * pin);
extern void pio_enable_it(const struct _pin * pin);
extern void pio_disable_it(const struct _pin * pin);
extern void pio_it_handlers(void);
extern void pio_capture_handler(void);
extern void pio_set_group_handler(uint32_t group, void (*handler)(uint32_t));

#ifdef __cplusplus
}
#endif
#endif /* _PIO_H */
