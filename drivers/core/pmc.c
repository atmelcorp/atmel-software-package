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
#include "trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

static uint32_t _pmc_mck = 0;

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static void _pmc_compute_mck(void)
{
	uint32_t mckr = PMC->PMC_MCKR;
	uint32_t pllar = (CKGR_PLLAR_MULA_Msk & PMC->CKGR_PLLAR) >> CKGR_PLLAR_MULA_Pos;
	uint32_t mdiv = (PMC_MCKR_MDIV(mckr) < 3) ?  (1u << PMC_MCKR_MDIV(mckr)) : 3;
	_pmc_mck = BOARD_MAINOSC / mdiv / (mckr & PMC_MCKR_PLLADIV2 ? 2 : 1) * (pllar + 1);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t pmc_get_master_clock(void)
{
	if (!_pmc_mck) {
		_pmc_compute_mck();
	}
	return _pmc_mck;
}

/**
 * \brief Select external 32K crystal.
 */
void pmc_select_external_crystal(void)
{
	int return_to_sclock = 0;

	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_sclock = 1;
	}

	/* switch from internal RC 32kHz to external OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_XTAL;

	/* Wait 5 slow clock cycles for internal resynchronization */
	volatile int count;
	for (count = 0; count < 0x1000; count++);

	/* Switch to slow clock again if needed */
	if (return_to_sclock)
		pmc_switch_mck_to_slck();
}

/**
 * \brief Select internal 32K crystal.
 */
void pmc_select_internal_crystal(void)
{
	int return_to_sclock = 0;

	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_sclock = 1;
	}

	/* switch from extenal OSC 32kHz to internal RC 32 kHz */
	/* switch slow clock source to internal OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_RC;

	/* Wait 5 slow clock cycles for internal resynchronization */
	volatile int count;
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
	while (!(PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY));

	/* switch MAIN clock to external OSC 12 MHz */
	PMC->CKGR_MOR |= CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_PASSWD;

	/* wait MAIN clock status change for external OSC 12 MHz selection */
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS));

	/* in case where MCK is running on MAIN CLK */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

/**
 * \brief Select internal 12M OSC.
 */
void pmc_select_internal_osc(void)
{
	/* switch from external OSC 12 MHz to internal RC 12 MHz */
	/* Wait internal 12 MHz RC Startup Time for clock stabilization (software loop) */
	while (!(PMC->PMC_SR & PMC_SR_MOSCRCS));

	/* switch MAIN clock to internal RC 12 MHz */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCSEL) | CKGR_MOR_KEY_PASSWD;

	/* in case where MCK is running on MAIN CLK */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	/* disable external OSC 12 MHz   */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCXTEN) | CKGR_MOR_KEY_PASSWD;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

/**
 * \brief Switch PMC from MCK to PLL clock.
 */
void pmc_switch_mck_to_pll(void)
{
	/* Select PLL as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_compute_mck();
}

/**
 * \brief Switch PMC from MCK to main clock.
 */
void pmc_switch_mck_to_main(void)
{
	/* Select Main Oscillator as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_compute_mck();
}

/**
 * \brief Switch PMC from MCK to slow clock.
 */
void pmc_switch_mck_to_slck(void)
{
	/* Select Slow Clock as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_SLOW_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_compute_mck();
}

/**
 * \brief Configure MCK Prescaler.
 * \param prescaler prescaler value.
 */
void pmc_set_mck_prescaler(uint32_t prescaler)
{
	/* Change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | prescaler;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
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
			while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
		}
	} else {
		if (divider == PMC_MCKR_PLLADIV2) {
			PMC->PMC_MCKR = (PMC->PMC_MCKR | PMC_MCKR_PLLADIV2);
			while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
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
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
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
	while (!(PMC->PMC_SR & PMC_SR_LOCKA));
}

/**
 * \brief Disable PLLA Register.
 */
void pmc_disable_plla(void)
{
	PMC->CKGR_PLLAR = (PMC->CKGR_PLLAR & ~CKGR_PLLAR_MULA_Msk) | CKGR_PLLAR_MULA(0);
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
	assert(id > 1 && id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;

	PMC->PMC_PCR = pcr | PMC_PCR_CMD | PMC_PCR_EN;
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
	assert(id > 1 && id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;

	PMC->PMC_PCR = PMC_PCR_CMD | (pcr & ~PMC_PCR_EN);
}

/**
 * \brief Get Peripheral Status for the given peripheral ID.
 *
 * \param id  Peripheral ID (ID_xxx).
 */
uint32_t pmc_is_peripheral_enabled(uint32_t id)
{
	assert(id > 1 && id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;

	return !!(pcr & PMC_PCR_EN);
}

/**
 * \brief Get current frequency clock for the given peripheral ID.
 *
 * \param id  Peripheral ID (ID_xxx).
 */
uint32_t pmc_get_peripheral_clock(uint32_t id)
{
	assert(id > 1 && id < ID_PERIPH_COUNT);

	uint32_t div = get_peripheral_clock_divider(id);
	if (div)
		return pmc_get_master_clock() / div;

	return 0;
}

/**
 * \brief Disable all the peripherals clock via PMC.
 */
void pmc_disable_all_peripherals(void)
{
	int i;
	for (i = 2; i < ID_PERIPH_COUNT; i++)
		pmc_disable_peripheral(i);
}
