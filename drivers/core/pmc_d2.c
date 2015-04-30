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
#include "core/pmc_d2.h"
#include "utils/trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Definition and functions SAMA5D2
 *----------------------------------------------------------------------------*/

/** List of peripheral support MCK frequency */
const uint32_t _peripheral_id_master_mck[] = {
	ID_XDMAC0,
	ID_XDMAC1,
	ID_MATRIX0,
	ID_LCDC,
	ID_SDHC0,
	ID_SDHC1,
	ID_AESB,
};

#define PERIPH_ID_MCK_COUNT sizeof(_peripheral_id_master_mck)

/*----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

/**
 * \brief Return the frequency divider for giving peripheral ID.
 * \ use to define MCK or MCK/2
 * \param dwId  Peripheral ID (ID_xxx).
 */
extern uint32_t _pmc_get_mck_divider (uint32_t id)
{
	uint8_t i;
	for (i = 0; i < PERIPH_ID_MCK_COUNT; i++) {
		if (id == _peripheral_id_master_mck[i])
			return 1;
	}
	/* ID not found in _peripheral_id_master_mck -> use master_clock / 2 */
	return 2;
}


/*----------------------------------------------------------------------------
 *        Exported functions SAMA5D2
 *----------------------------------------------------------------------------*/

/**
 * \brief Set maximum frequency clock for giving peripheral ID.
 *
 * \param dwId  Peripheral ID (ID_xxx).
 * \param mck  Master clock.
 * \return Peripheral clock.
 */
extern uint32_t pmc_get_peripheral_max_clock(uint32_t id, uint32_t mck)
{
	uint32_t max_clock;
	uint8_t i;

	assert (id > ID_PERIPH_COUNT);

	/* Disable peripheral clock */
	pmc_disable_peripheral(id);
	max_clock = mck / _pmc_get_mck_divider(id);
	for (i = 0; i < 4; i++) {
		if (mck / (1 << i) <= max_clock)
			break;
	}
	pmc_enable_peripheral(id);
	return max_clock;
}

/**
 * \brief Enables the clock of a peripheral. The peripheral ID is used
 * to identify which peripheral is targeted.
 *
 * \note The ID must NOT be shifted (i.e. 1 << ID_xxx).
 *
 * \param dwId  Peripheral ID (ID_xxx).
 */
extern void pmc_enable_peripheral(uint32_t id)
{
	assert (id > ID_PERIPH_COUNT);
	PMC->PMC_PCR = PMC_PCR_PID(id) | PMC_PCR_CMD | PMC_PCR_EN;
}

/**
 * \brief Disables the clock of a peripheral. The peripheral ID is used
 * to identify which peripheral is targeted.
 *
 * \note The ID must NOT be shifted (i.e. 1 << ID_xxx).
 *
 * \param dwId  Peripheral ID (ID_xxx).
 */
extern void pmc_disable_peripheral(uint32_t id)
{
	assert (id > ID_PERIPH_COUNT);
	PMC->PMC_PCR = PMC_PCR_PID(id) | PMC_PCR_CMD;
}

/**
 * \brief Enable all the peripherals clock via PMC.
 */
extern void pmc_enable_all_peripherals(void)
{
}

/**
 * \brief Disable all the peripherals clock via PMC.
 */
extern void pmc_disable_all_peripherals(void)
{
}

/**
 * \brief Get Peripheral Status for the given peripheral ID.
 *
 * \param dwId  Peripheral ID (ID_xxx).
 */
extern uint32_t pmc_is_peripheral_enabled(uint32_t id)
{
	return PMC_PCR_PID(id) & PMC_PCR_EN;;
}

/**
 * \brief Select external 32K crystal.
 */
extern void pmc_select_external_slow_clock_32Khz(void)
{
	volatile uint32_t count;
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_XTAL;
	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++) ;
	/* wait slow clock status change for external OSC 32 kHz selection */
}

/**
 * \brief Select internal 12K RC oscillator.
 */
extern void pmc_select_internal_slow_clock_12KHz(void)
{
	/* switch from external RC 32kHz to internal OSC 32 kHz */
	volatile uint32_t count;
	/* switch slow clock source to internal OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_RC;
	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++) ;
	/* wait slow clock status change for internal RC 32 kHz selection */
	//   while(PMC->PMC_SR & PMC_SR_OSCSELS);
}

/**
 * \brief Select internal 32K RC oscillator.
 */
extern void pmc_select_internal_slow_clock_32KHz(void)
{
	/* switch from external RC 32kHz to internal OSC 32 kHz */
	volatile uint32_t count;
	/* switch slow clock source to internal OSC 32 kHz */
	SCKC->SCKC_CR = (SCKC->SCKC_CR & ~SCKC_CR_OSCSEL) | SCKC_CR_OSCSEL_RC;
	/* Wait 5 slow clock cycles for internal resynchronization */
	for (count = 0; count < 0x1000; count++) ;
	/* wait slow clock status change for internal RC 32 kHz selection */
	//   while(PMC->PMC_SR & PMC_SR_OSCSELS);
}

/**
 * \brief Select external main OSC.
 */
extern void pmc_select_external_main_osc(void)
{
	/* switch from internal RC 12 MHz to external osc 8 to 24MHz */
	/* Check if main clock osc is previously selected */
	if ((PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) == CKGR_MOR_MOSCSEL)
		return;
	/* enable external crystal osc 8 to 24MHz */
	PMC->CKGR_MOR = CKGR_MOR_MOSCXTEN | CKGR_MOR_KEY_PASSWD;
	/* wait Main CLK Ready */
	while (!(PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY)) ;
	/* switch MAIN clock to external osc 8 to 24MHz */
	PMC->CKGR_MOR |= CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_PASSWD;
	/* wait MAIN clock status for external osc 8 to 24MHz selection is done*/
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS)) ;
	/* Wait master clock ready */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Select internal RC 12M OSC.
 * When switching the source of the main clock between the RC oscillator
 * and the crystal oscillator, both oscillators must be enabled.
 * After completion of the switch, the unused oscillator can be disabled.
 */
extern void pmc_select_internal_12MHz(void)
{
	/* switch from external osc (8 to 24MHz) to internal RC 12 MHz */

	/* Check if external osc (8 to 24MHz) is selected */
	if ((PMC->PMC_SR & PMC_SR_MOSCSELS) != PMC_SR_MOSCSELS)
		return;
	/* Wait internal 12 MHz RC Startup Time for clock stabilization */
	while (!(PMC->PMC_SR & PMC_SR_MOSCRCS)) ;
	/* switch MAIN clock to internal RC 12 MHz */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCSEL) | CKGR_MOR_KEY_PASSWD;
	/* in case where MCK is running on MAIN CLK */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
	/* disable external OSC 12 MHz   */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCXTEN) | CKGR_MOR_KEY_PASSWD;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Switch PMC from MCK to PLL clock.
 */
extern void pmc_switch_mck_to_pll(void)
{
	/* Select PLL as input clock for PCK and MCK */
	PMC->PMC_MCKR =
	    (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Switch PMC from MCK to main clock.
 */
extern void pmc_switch_mck_to_main(void)
{
	/* Select Main Oscillator as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Switch PMC from MCK to slow clock.
 */
extern uint32_t pmc_switch_mck_to_slck(void)
{
	/* Select Slow Clock as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_PCK_CSS_SLOW_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
	return PMC->PMC_MCKR;
}

/**
 * \brief Configure MCK Prescaler.
 * \param prescaler prescaler value.
 */
extern void pmc_set_mck_prescaler(uint32_t prescaler)
{
	/* Change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | prescaler;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) ;
}

/**
 * \brief Configure MCK PLLA divider.
 * \param divider PLL divider value.
 */
extern void pmc_set_mck_plla_div(uint32_t divider)
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
extern void pmc_set_mck_divider(uint32_t divider)
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
extern void pmc_set_plla(uint32_t pll, uint32_t cpcr)
{
	PMC->CKGR_PLLAR = pll;
	PMC->PMC_PLLICPR = cpcr;
	while (!(PMC->PMC_SR & PMC_SR_LOCKA)) ;
}

/**
 * \brief Disable PLLA Register.
 */
extern void pmc_disable_plla(void)
{
	PMC->CKGR_PLLAR =
	    (PMC->CKGR_PLLAR & ~CKGR_PLLAR_MULA_Msk) | CKGR_PLLAR_MULA(0);
}