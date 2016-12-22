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

#include "board.h"
#include "board_audio.h"

#include "gpio/pio.h"

#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PDMIC
void board_cfg_pdmic(void)
{
#ifdef BOARD_PDMIC0_PINS
	const struct _pin pins_pdmic[] = BOARD_PDMIC0_PINS;
	pio_configure(pins_pdmic, ARRAY_SIZE(pins_pdmic));
#endif
}
#endif

#ifdef CONFIG_HAVE_CLASSD
void board_cfg_classd(void)
{
#ifdef BOARD_CLASSD0_PINS
	const struct _pin pins_classd[] = BOARD_CLASSD0_PINS;
	pio_configure(pins_classd, ARRAY_SIZE(pins_classd));
#endif
}
#endif

#ifdef CONFIG_HAVE_SSC
void board_cfg_ssc(void)
{
#ifdef BOARD_SSC0_PINS
	const struct _pin pins_ssc0[] = BOARD_SSC0_PINS;
	pio_configure(pins_ssc0, ARRAY_SIZE(pins_ssc0));
#endif
#ifdef BOARD_SSC1_PINS
	const struct _pin pins_ssc1[] = BOARD_SSC1_PINS;
	pio_configure(pins_ssc1, ARRAY_SIZE(pins_ssc1));
#endif
}
#endif /* CONFIG_HAVE_SSC */
