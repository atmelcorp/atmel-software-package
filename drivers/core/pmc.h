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

#ifndef _PMC_H_
#define _PMC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** Peripheral clock maxinum frequency */
typedef struct _PeripheralClockMaxFreq {
	uint32_t bPeriphID;		/**< Peripheral ID */
	uint32_t bMaxFrequency;		/**< Max frequency*/
} PeripheralClockMaxFreq;

enum _dev_div {
	DEV_DIV1 = 0,
	DEV_DIV2 = 1,
	DEV_DIV4 = 2,
	DEV_DIV8 = 3
};

extern uint32_t board_master_clock;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern void pmc_enable_peripheral(uint32_t id);
extern void pmc_disable_peripheral(uint32_t id);

extern void pmc_enable_all_peripherals(void);
extern void pmc_disable_all_peripherals(void);

extern uint32_t pmc_is_peripheral_enabled(uint32_t id);

extern void pmc_select_external_crystal(void);
extern void pmc_select_internal_crystal(void);
extern void pmc_select_external_osc(void);
extern void pmc_select_internal_osc(void);
extern void pmc_switch_mck_to_pll(void);
extern void pmc_switch_mck_to_main(void);
extern uint32_t pmc_switch_mck_to_slck(void);
extern void pmc_set_plla(uint32_t pll, uint32_t cpcr);
extern void pmc_set_mck_prescaler(uint32_t prescaler);
extern void pmc_set_mck_divider(uint32_t divider);
extern void pmc_set_mck_plla_div(uint32_t divider);
extern void pmc_disable_plla(void);
extern uint32_t pmc_get_peripheral_max_clock(uint32_t id);
uint32_t pmc_get_peripheral_clock(uint32_t id);
extern uint32_t pmc_set_peripheral_max_clock(uint32_t id);
uint32_t pmc_set_peripheral_divider(uint32_t id, enum _dev_div div);
#ifdef __cplusplus
}
#endif
#endif /* #ifndef _PMC_H_ */
