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
#ifndef CLK_CONFIG_H
#define CLK_CONFIG_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Defined low power mode
 *----------------------------------------------------------------------------*/

#define IDLE 0
#define ULP0 1  //used as ULP for sama5d3/4
#if  defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAM9X60)
#define ULP1 2
#endif

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct test_mode {
	/** Test name */
	const char *name;

	/** Low power mode */
	uint8_t mode;

	/** Wake up event */
	uint8_t event;

	/** PCK MCK clock setting*/
	struct pck_mck_cfg clock_test_setting;
};

/*----------------------------------------------------------------------------
 *        Exported constants
 *----------------------------------------------------------------------------*/
 
extern struct test_mode test_setting[];

#endif /* CLK_CONFIG_H */
