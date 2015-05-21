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

/** \addtogroup pmc_module Working with PMC
 * \section Purpose
 * The PMC driver provides the Interface for configuration the Power Management
 *  Controller (PMC).
 *
 * \section Usage
 * <ul>
 * <li>  Enable & disable peripherals using pmc_enable_peripheral() and
 * pmc_enable_all_peripherals() or pmc_disable_peripheral() and
 * pmc_disable_all_peripherals().
 * <li>  Get & set maximum frequency clock for giving peripheral using
 * pmc_get_peri_max_freq() and pmc_set_peri_max_clock().
 * <li>  Get Peripheral Status for the given peripheral using pmc_is_periph_enabled()
 * <li>  Select clocks's source using pmc_select_external_crystal(),
 * pmc_select_internal_crystal(), pmc_select_external_osc() and pmc_select_internal_osc().
 * <li>  Switch MCK using pmc_switch_mck_to_pll(), pmc_switch_mck_to_main() and
 * pmc_switch_mck_to_slck().
 * <li>  Config PLL using pmc_set_pll_a() and pmc_disable_pll_a().
 * </li>
 * </ul>
 * For more accurate information, please look at the PMC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref pmc.c\n
 * \ref pmc.h\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of PIO (Parallel Input/Output) controller.
 *
 */
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "core/pmc.h"
#include "utils/trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/
#define MAX_PERI_ID  ID_L2CC

extern const uint32_t peripherals_min_clock_dividers[];
uint32_t board_master_clock;

static void _pmc_compute_mck(void)
{
	uint32_t mckr_value = PMC->PMC_MCKR;
	uint32_t pllar_value = (CKGR_PLLAR_MULA_Msk & PMC->CKGR_PLLAR) >> CKGR_PLLAR_MULA_Pos;
	uint32_t mdiv = (PMC_MCKR_MDIV(mckr_value) < 3) ?
		(1u << PMC_MCKR_MDIV(mckr_value)) : 3;

	board_master_clock = BOARD_MAINOSC / mdiv / (mckr_value & PMC_MCKR_PLLADIV2 ? 2:1)
		* (pllar_value + 1);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Get maximum frequency clock for giving peripheral ID.
 *
 * \param id  Peripheral ID (ID_xxx).
 */
uint32_t pmc_get_peripheral_max_clock(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);
	uint32_t divider = peripherals_min_clock_dividers[id];
	if (divider) {
		return board_master_clock / divider;
	} else {
		return 0;
	}
}

uint32_t pmc_get_peripheral_clock(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);
	PMC->PMC_PCR = PMC_PCR_PID(id);
	return (PMC->PMC_PCR & (0x3u << 16)) >> 16;
}

uint32_t pmc_get_master_clock(void)
{
	if (!board_master_clock) {
		_pmc_compute_mck();
	}
	return board_master_clock;
}

uint32_t pmc_set_peripheral_divider(uint32_t id, enum _dev_div div)
{
	uint32_t clock = board_master_clock >> (uint32_t)div;
	uint32_t max_clock = pmc_get_peripheral_max_clock(id);
	if (clock > max_clock)
		pmc_set_peripheral_max_clock(id);
	else
		PMC->PMC_PCR = PMC_PCR_PID(id) | PMC_PCR_CMD | ( div << 16) | PMC_PCR_EN;
	return clock;
}

/**
 * \brief Set maximum frequency clock for giving peripheral ID.
 *
 * \param id  Peripheral ID (ID_xxx).
 * \param mck  Master clock.
 * \return Peripheral clock.
 */
extern uint32_t pmc_set_peripheral_max_clock(uint32_t id)
{
	uint32_t maxClock;
	uint8_t i;
	/* Disable peripheral clock */
	PMC->PMC_PCR = PMC_PCR_PID(id) | PMC_PCR_CMD;
	maxClock = pmc_get_peripheral_max_clock(id);
	for (i = 0; i < 4; i++) {
		if (board_master_clock / (1 << i) <= maxClock)
			break;
	}
	PMC->PMC_PCR = PMC_PCR_PID(id) | PMC_PCR_CMD | (i << 16) | PMC_PCR_EN;
	return maxClock;
}

/**
 * \brief Enables the clock of a peripheral. The peripheral ID is used
 * to identify which peripheral is targeted.
 *
 * \note The ID must NOT be shifted (i.e. 1 << ID_xxx).
 *
 * \param id  Peripheral ID (ID_xxx).
 */
void pmc_enable_peripheral(uint32_t id)
{
/*
	if (id < 32) {
		if ((PMC->PMC_PCSR0 & ((uint32_t) 1 << id)) ==
		    ((uint32_t) 1 << id)) {
			//   TRACE_DEBUG( "pmc_enable_peripheral: clock of peripheral"  " %u is already enabled\n\r", id ) ;
		} else {
			PMC->PMC_PCER0 = (1 << id);
		}
	} else {
		if ((PMC->PMC_PCSR1 & ((uint32_t) 1 << (id - 32))) ==
		    ((uint32_t) 1 << (id - 32))) {
			// TRACE_DEBUG( "pmc_enable_peripheral: clock of peripheral"  " %u is already enabled\n\r", id ) ;
		} else {
			PMC->PMC_PCER1 = 1 << (id - 32);
		}
	}
*/

	uint32_t pcr_value;
	PMC->PMC_PCR = PMC_PCR_PID(id); // map the Peripheral dw_id to PMC_PCR register for next Read operation
	pcr_value = PMC->PMC_PCR;          // to retrieve info related to the Peripheral Clock of interest
	if ((pcr_value & PMC_PCR_EN) != 0x0)
	{
		TRACE_DEBUG( "pmc_enable_peripheral: clock of peripheral"  " %u is already enabled\n\r", dw_id);
	}
	else
		PMC->PMC_PCR = (pcr_value & ~PMC_PCR_PID_Msk) | PMC_PCR_CMD | PMC_PCR_PID(id) | PMC_PCR_EN;
}

/**
 * \brief Disables the clock of a peripheral. The peripheral ID is used
 * to identify which peripheral is targeted.
 *
 * \note The ID must NOT be shifted (i.e. 1 << ID_xxx).
 *
 * \param id  Peripheral ID (ID_xxx).
 */
void pmc_disable_peripheral(uint32_t id)
{
	if (id < 32) {
		if ((PMC->PMC_PCSR0 & ((uint32_t) 1 << id)) !=
		    ((uint32_t) 1 << id)) {
			TRACE_DEBUG("pmc_disable_peripheral: clock of peripheral"
				    " %u is not enabled\n\r",
				    (unsigned int) id);
		} else {
			PMC->PMC_PCDR0 = 1 << id;
		}
	} else {
		if ((PMC->PMC_PCSR1 & ((uint32_t) 1 << (id - 32))) !=
		    ((uint32_t) 1 << (id - 32))) {
			TRACE_DEBUG("pmc_disable_peripheral: clock of peripheral"
				    " %u is not enabled\n\r",
				    (unsigned int) id);
		} else {
			PMC->PMC_PCDR1 = 1 << (id - 32);
		}
	}
}

/**
 * \brief Enable all the peripherals clock via PMC.
 */
void pmc_enable_all_peripherals(void)
{
	PMC->PMC_PCER0 = 0xFFFFFFFF;
	PMC->PMC_PCER1 = 0xFFFFFFFF;
	TRACE_DEBUG("Enable all periph clocks\n\r");
}

/**
 * \brief Disable all the peripherals clock via PMC.
 */
void pmc_disable_all_peripherals(void)
{
	TRACE_DEBUG("Disable all periph clocks\n\r");
	PMC->PMC_PCDR0 = 0xFFFFFFFF;
	PMC->PMC_PCDR1 = 0xFFFFFFFF;
}

/**
 * \brief Get Peripheral Status for the given peripheral ID.
 *
 * \param id  Peripheral ID (ID_xxx).
 */
extern uint32_t pmc_is_peripheral_enabled(uint32_t id)
{
	if (id < 32) {
		return (PMC->PMC_PCSR0 & (1 << id));
	} else {
		return (PMC->PMC_PCSR1 & (1 << (id - 32)));
	}
}

/**
 * \brief Select external 32K crystal.
 */
void pmc_select_external_crystal(void)
{
	int8_t return_to_sclock = 0;
	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_sclock = 1;
	}
	/* switch from internal RC 32kHz to external OSC 32 kHz */
	volatile uint32_t count;
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_XTAL;
	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++) ;
	/* Switch to slow clock again if needed */
	if (return_to_sclock)
		pmc_switch_mck_to_slck();
}

/**
 * \brief Select internal 32K crystal.
 */
void pmc_select_internal_crystal(void)
{
	int8_t return_to_sclock = 0;
	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_sclock = 1;
	}
	/* switch from extenal OSC 32kHz to internal RC 32 kHz */
	volatile uint32_t count;
	/* switch slow clock source to internal OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_RC;
	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++);
	/* Switch to slow clock again if needed */
	if (return_to_sclock)
		pmc_switch_mck_to_slck();
}

/**
 * \brief Select external 12M OSC.
 */
void pmc_select_external_osc(void)
{
	/* switch from internal RC 12 MHz to external OSC 12 MHz */
	/* wait Main XTAL Oscillator stabilization */
	if ((PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) == CKGR_MOR_MOSCSEL)
		return;
	/* enable external OSC 12 MHz */
	PMC->CKGR_MOR |= CKGR_MOR_MOSCXTEN | CKGR_MOR_KEY_PASSWD;
	/* wait Main CLK Ready */
	while (!(PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY)) ;
	/* switch MAIN clock to external OSC 12 MHz */
	PMC->CKGR_MOR |= CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_PASSWD;
	/* wait MAIN clock status change for external OSC 12 MHz selection */
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS)) ;
	/* in case where MCK is running on MAIN CLK */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Select internal 12M OSC.
 */
void pmc_select_internal_osc(void)
{
	/* switch from external OSC 12 MHz to internal RC 12 MHz */
	/* Wait internal 12 MHz RC Startup Time for clock stabilization (software loop) */
	while (!(PMC->PMC_SR & PMC_SR_MOSCRCS)) ;
	/* switch MAIN clock to internal RC 12 MHz */
	PMC->CKGR_MOR =
	    (PMC->CKGR_MOR & ~CKGR_MOR_MOSCSEL) | CKGR_MOR_KEY_PASSWD;
	/* in case where MCK is running on MAIN CLK */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
	/* disable external OSC 12 MHz   */
	PMC->CKGR_MOR =
	    (PMC->CKGR_MOR & ~CKGR_MOR_MOSCXTEN) | CKGR_MOR_KEY_PASSWD;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Switch PMC from MCK to PLL clock.
 */
void pmc_switch_mck_to_pll(void)
{
	/* Select PLL as input clock for PCK and MCK */
	PMC->PMC_MCKR =
	    (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
	_pmc_compute_mck();
}

/**
 * \brief Switch PMC from MCK to main clock.
 */
void pmc_switch_mck_to_main(void)
{
	/* Select Main Oscillator as input clock for PCK and MCK */
	PMC->PMC_MCKR =
	    (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
	_pmc_compute_mck();
}

/**
 * \brief Switch PMC from MCK to slow clock.
 */
extern uint32_t pmc_switch_mck_to_slck(void)
{
	/* Select Slow Clock as input clock for PCK and MCK */
	PMC->PMC_MCKR =
	    (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_SLOW_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
	_pmc_compute_mck();
	return PMC->PMC_MCKR;
}

/**
 * \brief Configure MCK Prescaler.
 * \param prescaler prescaler value.
 */
void pmc_set_mck_prescaler(uint32_t prescaler)
{
	/* Change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | prescaler;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Configure MCK PLLA divider.
 * \param divider PLL divider value.
 */
void pmc_set_mck_plla_div(uint32_t divider)
{
	if ((PMC->PMC_MCKR & PMC_MCKR_PLLADIV2) == PMC_MCKR_PLLADIV2) {
		if (divider == 0) {
			PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PLLADIV2);
			while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
		}
	} else {
		if (divider == PMC_MCKR_PLLADIV2) {
			PMC->PMC_MCKR = (PMC->PMC_MCKR | PMC_MCKR_PLLADIV2);
			while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
		}
	}
}

/**
 * \brief Configure MCK Divider.
 * \param divider divider value.
 */
void pmc_set_mck_divider(uint32_t divider)
{
	/* change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_MDIV_Msk) | divider;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Configure PLL Register.
 * \param pll pll value.
 * \param cpcr cpcr value.
 */
void pmc_set_plla(uint32_t pll, uint32_t cpcr)
{
	PMC->CKGR_PLLAR = pll;
	PMC->PMC_PLLICPR = cpcr;
	while (!(PMC->PMC_SR & PMC_SR_LOCKA)) ;
}

/**
 * \brief Disable PLLA Register.
 */
void pmc_disable_plla(void)
{
	PMC->CKGR_PLLAR =
	    (PMC->CKGR_PLLAR & ~CKGR_PLLAR_MULA_Msk) | CKGR_PLLAR_MULA(0);
}
