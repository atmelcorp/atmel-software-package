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

#include <assert.h>
#include <errno.h>

#include "chip.h"
#include "timer.h"
#include "peripherals/pmc.h"
#include "peripherals/slowclock.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _pmc_main_osc {
	uint32_t rc_freq;
	uint32_t crystal_freq;
};

#define OSC_STARTUP_TIME	0xFFu
#define MAINFRDY_TIMEOUT	32u
#define MOSCXTS_TIMEOUT		((OSC_STARTUP_TIME * 8) + 8)
#define MOSCSELS_TIMEOUT	32u

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

static uint32_t _pmc_mck = 0;
static struct _pmc_main_osc _pmc_main_oscillators = {
	.rc_freq = MAIN_CLOCK_INT_OSC,
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static void _pmc_compute_mck(void)
{
	uint32_t clk = 0;
	uint32_t mckr = PMC->PMC_MCKR;

	uint32_t css = mckr & PMC_MCKR_CSS_Msk;
	switch (css) {
	case PMC_MCKR_CSS_SLOW_CLK:
		clk = pmc_get_slow_clock();
		break;
	case PMC_MCKR_CSS_MAIN_CLK:
		clk = pmc_get_main_clock();
		break;
	case PMC_MCKR_CSS_PLLA_CLK:
		clk = pmc_get_plla_clock();
		break;
	case PMC_MCKR_CSS_UPLL_CLK:
		clk = pmc_get_upll_clock();
		break;
	default:
		/* should never get here... */
		break;
	}

	uint32_t pres = mckr & PMC_MCKR_PRES_Msk;
	switch (pres) {
	case PMC_MCKR_PRES_CLOCK:
		break;
	case PMC_MCKR_PRES_CLOCK_DIV2:
		clk >>= 1;
		break;
	case PMC_MCKR_PRES_CLOCK_DIV4:
		clk >>= 2;
		break;
	case PMC_MCKR_PRES_CLOCK_DIV8:
		clk >>= 3;
		break;
	case PMC_MCKR_PRES_CLOCK_DIV16:
		clk >>= 4;
		break;
	case PMC_MCKR_PRES_CLOCK_DIV32:
		clk >>= 5;
		break;
	case PMC_MCKR_PRES_CLOCK_DIV64:
		clk >>= 6;
		break;
#ifdef PMC_MCKR_PRES_CLOCK_DIV3
	case PMC_MCKR_PRES_CLOCK_DIV3:
		clk /= 3;
		break;
#endif
	default:
		/* should never get here... */
		break;
	}

	uint32_t mdiv = mckr & PMC_MCKR_MDIV_Msk;
	switch (mdiv) {
	case PMC_MCKR_MDIV_EQ_PCK:
		break;
	case PMC_MCKR_MDIV_PCK_DIV2:
		clk >>= 1; // divide by 2
		break;
	case PMC_MCKR_MDIV_PCK_DIV4:
		clk >>= 2; // divide by 4
		break;
	case PMC_MCKR_MDIV_PCK_DIV3:
		clk /= 3;  // divide by 3
		break;
	default:
		/* should never get here... */
		break;
	}

	_pmc_mck = clk;
}

static uint32_t _pmc_get_pck_clock(uint32_t index)
{
	uint32_t clk = 0;
	uint32_t pck = PMC->PMC_PCK[index];

	switch (pck & PMC_PCK_CSS_Msk) {
	case PMC_PCK_CSS_SLOW_CLK:
		clk = pmc_get_slow_clock();
		break;
	case PMC_PCK_CSS_MAIN_CLK:
		clk = pmc_get_main_clock();
		break;
	case PMC_PCK_CSS_PLLA_CLK:
		clk = pmc_get_plla_clock();
		break;
	case PMC_PCK_CSS_UPLL_CLK:
		clk = pmc_get_upll_clock();
		break;
	case PMC_PCK_CSS_MCK:
		clk = pmc_get_master_clock();
		break;
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	case PMC_PCK_CSS_AUDIO_CLK:
		clk = pmc_get_audio_pmc_clock();
		break;
#endif
	}

	uint32_t prescaler = (pck & PMC_PCK_PRES_Msk) >> PMC_PCK_PRES_Pos;
	return clk / (prescaler + 1);
}

static bool _pmc_get_system_clock_bits(enum _pmc_system_clock clock,
	uint32_t *scer, uint32_t* scdr, uint32_t *scsr)
{
	uint32_t e, d, s;

	switch (clock)
	{
#ifdef PMC_SCER_DDRCK
	case PMC_SYSTEM_CLOCK_DDR:
		e = PMC_SCER_DDRCK;
		d = PMC_SCDR_DDRCK;
		s = PMC_SCSR_DDRCK;
		break;
#endif
#ifdef PMC_SCER_LCDCK
	case PMC_SYSTEM_CLOCK_LCD:
		e = PMC_SCER_LCDCK;
		d = PMC_SCDR_LCDCK;
		s = PMC_SCSR_LCDCK;
		break;
#endif
#ifdef PMC_SCER_SMDCK
	case PMC_SYSTEM_CLOCK_SMD:
		e = PMC_SCER_SMDCK;
		d = PMC_SCDR_SMDCK;
		s = PMC_SCSR_SMDCK;
		break;
#endif
#ifdef PMC_SCER_UHP
	case PMC_SYSTEM_CLOCK_UHP:
		e = PMC_SCER_UHP;
		d = PMC_SCDR_UHP;
		s = PMC_SCSR_UHP;
		break;
#endif
#ifdef PMC_SCER_UDP
	case PMC_SYSTEM_CLOCK_UDP:
		e = PMC_SCER_UDP;
		d = PMC_SCDR_UDP;
		s = PMC_SCSR_UDP;
		break;
#endif
#ifdef PMC_SCER_PCK0
	case PMC_SYSTEM_CLOCK_PCK0:
		e = PMC_SCER_PCK0;
		d = PMC_SCDR_PCK0;
		s = PMC_SCSR_PCK0;
		break;
#endif
#ifdef PMC_SCER_PCK1
	case PMC_SYSTEM_CLOCK_PCK1:
		e = PMC_SCER_PCK1;
		d = PMC_SCDR_PCK1;
		s = PMC_SCSR_PCK1;
		break;
#endif
#ifdef PMC_SCER_PCK2
	case PMC_SYSTEM_CLOCK_PCK2:
		e = PMC_SCER_PCK2;
		d = PMC_SCDR_PCK2;
		s = PMC_SCSR_PCK2;
		break;
#endif
#ifdef PMC_SCER_PCK3
	case PMC_SYSTEM_CLOCK_PCK3:
		e = PMC_SCER_PCK3;
		d = PMC_SCDR_PCK3;
		s = PMC_SCSR_PCK3;
		break;
#endif
#ifdef PMC_SCER_PCK4
	case PMC_SYSTEM_CLOCK_PCK4:
		e = PMC_SCER_PCK4;
		d = PMC_SCDR_PCK4;
		s = PMC_SCSR_PCK4;
		break;
#endif
#ifdef PMC_SCER_PCK5
	case PMC_SYSTEM_CLOCK_PCK5:
		e = PMC_SCER_PCK5;
		d = PMC_SCDR_PCK5;
		s = PMC_SCSR_PCK5;
		break;
#endif
#ifdef PMC_SCER_PCK6
	case PMC_SYSTEM_CLOCK_PCK6:
		e = PMC_SCER_PCK6;
		d = PMC_SCDR_PCK6;
		s = PMC_SCSR_PCK6;
		break;
#endif
#ifdef PMC_SCER_ISCCK
	case PMC_SYSTEM_CLOCK_ISC:
		e = PMC_SCER_ISCCK;
		d = PMC_SCDR_ISCCK;
		s = PMC_SCSR_ISCCK;
		break;
#endif
	default:
		return false;
	}

	if (scer) {
		if (e)
			*scer = e;
		else
			return false;
	}

	if (scdr) {
		if (d)
			*scdr = d;
		else
			return false;
	}

	if (scsr) {
		if (s)
			*scsr = s;
		else
			return false;
	}

	return true;
}

#ifdef CONFIG_HAVE_PMC_PERIPH_DIV
static void _pmc_configure_peripheral_div(uint32_t id, uint32_t div)
{
	uint32_t clk_max;
	bool can_divide;

	can_divide = peripheral_has_clock_div(id);
	clk_max = get_peripheral_clock_max_freq(id);

	if (div == 0) {
		if (can_divide) {
			for (div = 0; div < ((PMC_PCR_DIV_Msk >> PMC_PCR_DIV_Pos)); div++)
				if ((pmc_get_master_clock() >> div) <= clk_max)
					break;
		}
	} else {
		if (div > 1 && !can_divide)
			trace_fatal("Peripheral does not support divided clock\r\n");
		div--;
	}

	if ((pmc_get_master_clock() >> div) <= clk_max) {
		PMC->PMC_PCR = PMC_PCR_PID(id);
		volatile uint32_t pcr = PMC->PMC_PCR;
		PMC->PMC_PCR = (pcr & ~PMC_PCR_DIV_Msk) | PMC_PCR_DIV(div) | PMC_PCR_CMD;
	} else {
		trace_fatal("Peripheral clock for periph#%d is too high\r\n", (int)id);
	}
}
#endif

static uint16_t _pmc_measure_main_osc_freq(bool external_xt)
{
	volatile uint32_t timeout = MAINFRDY_TIMEOUT;

#ifdef CKGR_MCFR_CCSS
	PMC->CKGR_MCFR = external_xt ? CKGR_MCFR_CCSS : 0;
#endif

#ifdef CKGR_MCFR_RCMEAS
	PMC->CKGR_MCFR |= CKGR_MCFR_RCMEAS;
#endif
	timeout = MAINFRDY_TIMEOUT;
	while (!(PMC->CKGR_MCFR & CKGR_MCFR_MAINFRDY) && --timeout > 0);

	return (timeout ?
		((PMC->CKGR_MCFR & CKGR_MCFR_MAINF_Msk) >> CKGR_MCFR_MAINF_Pos) :
		0u);
}

/*----------------------------------------------------------------------------
 *        Exported functions (General)
 *----------------------------------------------------------------------------*/

uint32_t pmc_set_main_oscillator_freq(uint32_t freq)
{
	uint32_t mor, mckr, mckr_mask;
	uint16_t mainf_rc, mainf_xt = 0;

	_pmc_main_oscillators.crystal_freq = freq;
	if (freq > 0)
		return freq;

	/*
	 * Save the current value of the CKGR_MCKR register then swith to
	 * the slow clock.
	 */
	mckr = PMC->PMC_MCKR;
	pmc_switch_mck_to_slck();
	mckr_mask = PMC_MCKR_MDIV_Msk | PMC_MCKR_PRES_Msk;
	PMC->PMC_MCKR &= ~mckr_mask;

	/* Save the current value of the CKGR_MOR register. */
	mor = PMC->CKGR_MOR;

	/* Measure the 12MHz RC frequency. */
	pmc_select_internal_osc();
	mainf_rc = _pmc_measure_main_osc_freq(false);

	/* Measure the crystal or by-pass frequency. */

	/* Try by-pass first. */
	if (pmc_select_external_osc(true) == 0)
		mainf_xt = _pmc_measure_main_osc_freq(true);

	/* Then try external crytal if no by-pass. */
	if (!mainf_xt) {
		if (pmc_select_external_osc(false) == 0)
			mainf_xt = _pmc_measure_main_osc_freq(true);
	}

	/* Switch back to internal 12MHz RC if it was selected initially */
	if (!(mor & CKGR_MOR_MOSCSEL))
		pmc_select_internal_osc();

#ifdef CKGR_MOR_MOSCRCEN
	/* Disable internal oscillator if it wasn't enabled initially */
	if (!(mor & CKGR_MOR_MOSCRCEN))
		pmc_disable_internal_osc();
#endif

	/* Switch back to the former MCK source. */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~mckr_mask) | (mckr & mckr_mask);
	pmc_switch_mck_to_new_source(mckr & PMC_MCKR_CSS_Msk);

	/* Guess the external crystal frequency, if available. */
	if (mainf_rc && mainf_xt) {
		uint32_t ratio = (mainf_xt * 1000) / mainf_rc;

		// Use 10% low and high margins
		if (1800 <= ratio && ratio <= 2200) {
			// 24/12 => ratio = 2000
			_pmc_main_oscillators.crystal_freq = 24000000u;
		} else if (1200 <= ratio && ratio <= 1467) {
			// 16/12 => ratio = 1333
			_pmc_main_oscillators.crystal_freq = 16000000u;
		} else if (900 <= ratio && ratio <= 1100) {
			// 12/12 => ratio = 1000
			_pmc_main_oscillators.crystal_freq = 12000000u;
		} else if (600 <= ratio && ratio <= 733) {
			// 8/12 => ratio = 667
			_pmc_main_oscillators.crystal_freq = 8000000u;
		}
	}

	return _pmc_main_oscillators.crystal_freq;
}

uint32_t pmc_get_main_oscillator_freq(void)
{
	if (_pmc_main_oscillators.crystal_freq > 0)
		return _pmc_main_oscillators.crystal_freq;
	else
		return pmc_set_main_oscillator_freq(0);
}

uint32_t pmc_get_master_clock(void)
{
	if (!_pmc_mck)
		_pmc_compute_mck();
	return _pmc_mck;
}

uint32_t pmc_get_slow_clock(void)
{
	return slowclock_get_clock(SLOWCLOCK_DOMAIN_DEFAULT);
}

uint32_t pmc_get_main_clock(void)
{
	if (PMC->CKGR_MOR & CKGR_MOR_MOSCSEL)
		return _pmc_main_oscillators.crystal_freq; /* external crystal */
	else
		return _pmc_main_oscillators.rc_freq; /* on-chip main clock RC */
}

uint32_t pmc_get_plla_clock(void)
{
	uint32_t pllaclk, pllar, pllmula, plldiva;

	pllar = PMC->CKGR_PLLAR;
	pllmula = (pllar & CKGR_PLLAR_MULA_Msk) >> CKGR_PLLAR_MULA_Pos;
	plldiva = (pllar & CKGR_PLLAR_DIVA_Msk) >> CKGR_PLLAR_DIVA_Pos;
	if (plldiva == 0 || pllmula == 0)
		return 0;

	pllaclk = pmc_get_main_clock();
	pllaclk = pllaclk * (pllmula + 1) / plldiva;
#ifdef CONFIG_HAVE_PMC_PLLADIV2
	if (PMC->PMC_MCKR & PMC_MCKR_PLLADIV2)
		pllaclk >>= 1;
#endif
	return pllaclk;
}

uint32_t pmc_get_processor_clock(void)
{
	uint32_t procclk, mdiv;

	procclk = pmc_get_master_clock();

	mdiv = PMC->PMC_MCKR & PMC_MCKR_MDIV_Msk;
	switch (mdiv) {
	case PMC_MCKR_MDIV_EQ_PCK:
		break;
	case PMC_MCKR_MDIV_PCK_DIV2:
		procclk <<= 1; // multiply by 2
		break;
	case PMC_MCKR_MDIV_PCK_DIV3:
		procclk *= 3;  // multiply by 3
		break;
	case PMC_MCKR_MDIV_PCK_DIV4:
		procclk <<= 2; // multiply by 4
		break;
	default:
		/* should never get here... */
		break;
	}

	return procclk;
}

void pmc_select_external_crystal(void)
{
	bool return_to_slck = false;

	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_slck = true;
	}

	slowclock_select_external(SLOWCLOCK_DOMAIN_DEFAULT);

	/* Switch to slow clock again if needed */
	if (return_to_slck)
		pmc_switch_mck_to_slck();
}

void pmc_select_internal_crystal(void)
{
	bool return_to_slck = false;

	if (PMC->PMC_MCKR == PMC_MCKR_CSS(PMC_MCKR_CSS_SLOW_CLK)) {
		pmc_switch_mck_to_main();
		return_to_slck = true;
	}

	slowclock_select_internal(SLOWCLOCK_DOMAIN_DEFAULT);

	/* Switch to slow clock again if needed */
	if (return_to_slck)
		pmc_switch_mck_to_slck();
}

int pmc_select_external_osc(bool bypass)
{
	int err;
	volatile uint32_t timeout;

	/* Return if external oscillator had been selected */
	if ((PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) == CKGR_MOR_MOSCSEL) {
		uint32_t mask = bypass ? CKGR_MOR_MOSCXTBY : CKGR_MOR_MOSCXTEN;
		if ((PMC->CKGR_MOR & mask) == mask)
			return 0;
	}

	/*
	 * When switching the source of the main clock between the RC oscillator and the crystal
	 * oscillator, both oscillators must be enabled. After completion of the switch, the
	 * unused oscillator can be disabled.
	 */
	pmc_enable_internal_osc();
	err = pmc_enable_external_osc(bypass);
	if (err < 0)
		return err;

	/* switch MAIN clock to external oscillator */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_KEY_Msk) | CKGR_MOR_MOSCSEL
	    | CKGR_MOR_KEY_PASSWD;

	/* wait for the command to be taken into account */
	while ((PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) != CKGR_MOR_MOSCSEL);

	/* wait MAIN clock status change for external oscillator selection */
	timeout = MOSCSELS_TIMEOUT;
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS) && --timeout > 0);
	if (!timeout) {
		PMC->CKGR_MOR &= ~CKGR_MOR_MOSCSEL;
		return -ETIMEDOUT;
	}

	/* in case where MCK is running on MAIN CLK */
	if ((PMC->PMC_MCKR & PMC_MCKR_CSS_PLLA_CLK) || (PMC->PMC_MCKR & PMC_MCKR_CSS_MAIN_CLK))
		while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	/* disable internal 12MHz RC to save power */
	pmc_disable_internal_osc();

	return 0;
}

int pmc_enable_external_osc(bool bypass)
{
	uint32_t cgmor = PMC->CKGR_MOR;
	uint32_t mask = CKGR_MOR_MOSCXTEN;
	volatile uint32_t timeout;

	if (bypass)
		mask = CKGR_MOR_MOSCXTBY;

	/* Enable Crystal Oscillator if needed */
	if ((cgmor & mask) != mask) {
		cgmor &= ~CKGR_MOR_KEY_Msk;
		cgmor |= CKGR_MOR_KEY_PASSWD;

		if (bypass) {
			/* Disable Crystal Oscillator */
			cgmor &= ~CKGR_MOR_MOSCXTEN;
			PMC->CKGR_MOR = cgmor;

			/* Wait Main Oscillator not ready */
			while (PMC->PMC_SR & PMC_SR_MOSCXTS);

			/* Enable Crystal Oscillator Bypass */
			cgmor |= CKGR_MOR_MOSCXTBY;
			PMC->CKGR_MOR = cgmor;
		} else {
			/* Disable Crystal Oscillator Bypass */
			cgmor &= ~CKGR_MOR_MOSCXTBY;
			PMC->CKGR_MOR = cgmor;

			/* Wait Main Oscillator not ready */
			while (PMC->PMC_SR & PMC_SR_MOSCXTS);

			/* Set Oscillator Startup Time */
			cgmor &= ~CKGR_MOR_MOSCXTST_Msk;
			cgmor |= CKGR_MOR_MOSCXTST(18);
			PMC->CKGR_MOR = cgmor;

			/* Enable Crystal Oscillator */
			cgmor |= CKGR_MOR_MOSCXTEN;
			PMC->CKGR_MOR = cgmor;
		}

		/* Wait Main Oscillator ready */
		timeout = MOSCXTS_TIMEOUT;
		while (!(PMC->PMC_SR & PMC_SR_MOSCXTS) && --timeout > 0);

		/* Return true if oscillator ready before timeout */
		return timeout == 0 ? -ETIMEDOUT : 0;
	} else {
		/* Crystal Oscillator already selected, just check if ready */
		if (PMC->PMC_SR & PMC_SR_MOSCXTS)
			return 0;
		else
			return -ENOTSUP;
	}
}

void pmc_disable_external_osc(void)
{
	/* disable external OSC */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~(CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_Msk)) | CKGR_MOR_KEY_PASSWD;
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~(CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTBY | CKGR_MOR_KEY_Msk)) | CKGR_MOR_KEY_PASSWD;
}

void pmc_select_internal_osc(void)
{
	pmc_enable_internal_osc();

	/* switch MAIN clock to internal 12MHz RC */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~(CKGR_MOR_MOSCSEL | CKGR_MOR_KEY_Msk)) | CKGR_MOR_KEY_PASSWD;

	/* in case where MCK is running on MAIN CLK */
	if ((PMC->PMC_MCKR & PMC_MCKR_CSS_PLLA_CLK) || (PMC->PMC_MCKR & PMC_MCKR_CSS_MAIN_CLK))
		while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	/* disable external OSC 12 MHz to save power*/
	pmc_disable_external_osc();
}

void pmc_enable_internal_osc(void)
{
#ifdef CKGR_MOR_MOSCRCEN
	/* Enable internal 12MHz RC when needed */
	if ((PMC->CKGR_MOR & CKGR_MOR_MOSCRCEN) != CKGR_MOR_MOSCRCEN) {
		PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_KEY_Msk) | CKGR_MOR_MOSCRCEN | CKGR_MOR_KEY_PASSWD;
		/* Wait internal 12MHz RC Startup Time for clock stabilization */
		while (!(PMC->PMC_SR & PMC_SR_MOSCRCS));
	}
#endif
}

void pmc_disable_internal_osc(void)
{
#ifdef CKGR_MOR_MOSCRCEN
	/* disable internal 12MHz RC */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCRCEN & ~CKGR_MOR_KEY_Msk) | CKGR_MOR_KEY_PASSWD;
#endif
}

void pmc_switch_mck_to_new_source(uint32_t mckr_css)
{
	uint32_t mckr = PMC->PMC_MCKR;
	uint32_t mask = PMC_MCKR_CSS_Msk;

	if ((mckr ^ mckr_css) & mask) {
		PMC->PMC_MCKR = (mckr & ~mask) | (mckr_css & mask);
		while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
	}

	_pmc_mck = 0;
}

void pmc_switch_mck_to_pll(void)
{
	/* Select PLL as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_mck = 0;
}

void pmc_switch_mck_to_upll(void)
{
	/* Select UPLL as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_UPLL_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_mck = 0;
}

void pmc_switch_mck_to_main(void)
{
	/* Select Main Oscillator as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_mck = 0;
}

void pmc_switch_mck_to_slck(void)
{
	/* Select Slow Clock as input clock for PCK and MCK */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_SLOW_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	_pmc_mck = 0;
}

void pmc_set_mck_prescaler(uint32_t prescaler)
{
	assert(!(prescaler & ~PMC_MCKR_PRES_Msk));

	/* Change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | prescaler;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

#ifdef CONFIG_HAVE_PMC_PLLADIV2
void pmc_set_mck_plladiv2(bool div2)
{
	uint32_t mckr = PMC->PMC_MCKR;
	if (div2) {
		if ((mckr & PMC_MCKR_PLLADIV2) != PMC_MCKR_PLLADIV2)
			PMC->PMC_MCKR = mckr | PMC_MCKR_PLLADIV2;
	} else {
		if ((mckr & PMC_MCKR_PLLADIV2) == PMC_MCKR_PLLADIV2)
			PMC->PMC_MCKR = mckr & ~PMC_MCKR_PLLADIV2;
	}
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}
#endif

#ifdef CONFIG_HAVE_PMC_UPLLDIV2
void pmc_set_mck_uplldiv2(bool div2)
{
	uint32_t mckr = PMC->PMC_MCKR;
	if (div2) {
		if ((mckr & PMC_MCKR_UPLLDIV2) != PMC_MCKR_UPLLDIV2)
			PMC->PMC_MCKR = mckr | PMC_MCKR_UPLLDIV2;
	} else {
		if ((PMC->PMC_MCKR & PMC_MCKR_UPLLDIV2) == PMC_MCKR_UPLLDIV2)
			PMC->PMC_MCKR = mckr & ~PMC_MCKR_UPLLDIV2;
	}
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}
#endif

#ifdef CONFIG_HAVE_PMC_H32MXDIV
void pmc_set_mck_h32mxdiv(bool div2)
{
	uint32_t mckr = PMC->PMC_MCKR;
	if (div2) {
		if ((mckr & PMC_MCKR_H32MXDIV) != PMC_MCKR_H32MXDIV_H32MXDIV2)
			PMC->PMC_MCKR = (mckr & ~PMC_MCKR_H32MXDIV) | PMC_MCKR_H32MXDIV_H32MXDIV2;
	} else {
		if ((mckr & PMC_MCKR_H32MXDIV) != PMC_MCKR_H32MXDIV_H32MXDIV1)
			PMC->PMC_MCKR = (mckr & ~PMC_MCKR_H32MXDIV) | PMC_MCKR_H32MXDIV_H32MXDIV1;
	}
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}
#endif /* CONFIG_HAVE_PMC_H32MXDIV */

void pmc_set_mck_divider(uint32_t divider)
{
	assert(!(divider & ~PMC_MCKR_MDIV_Msk));

	/* change MCK Prescaler divider in PMC_MCKR register */
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_MDIV_Msk) | divider;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
}

void pmc_configure_plla(const struct _pmc_plla_cfg* plla)
{
	uint32_t pllar = 0;

#ifdef CKGR_PLLAR_ONE
	pllar |= CKGR_PLLAR_ONE;
#endif
	pllar |= CKGR_PLLAR_MULA(plla->mul);
	pllar |= CKGR_PLLAR_DIVA(plla->div);
	pllar |= CKGR_PLLAR_PLLACOUNT(plla->count);
	PMC->CKGR_PLLAR = pllar;

#ifdef CONFIG_HAVE_PMC_PLLA_CHARGEPUMP
	PMC->PMC_PLLICPR = plla->icp & PMC_PLLICPR_ICP_PLLA_Msk;
#endif /* CONFIG_HAVE_PMC_PLLA_CHARGEPUMP */

	if (plla->mul > 0)
		while (!(PMC->PMC_SR & PMC_SR_LOCKA));
}

void pmc_disable_plla(void)
{
	PMC->CKGR_PLLAR = (PMC->CKGR_PLLAR & ~CKGR_PLLAR_MULA_Msk) | CKGR_PLLAR_MULA(0);
}

bool pmc_has_system_clock(enum _pmc_system_clock clock)
{
	return _pmc_get_system_clock_bits(clock, NULL, NULL, NULL);
}

void pmc_enable_system_clock(enum _pmc_system_clock clock)
{
	uint32_t scer, scsr;

	if (!_pmc_get_system_clock_bits(clock, &scer, NULL, &scsr)) {
		trace_debug("Unknown System clock: %d\r\n", clock);
		return;
	}

	PMC->PMC_SCER |= scer;
	while (!(PMC->PMC_SCSR & scsr));
}

void pmc_disable_system_clock(enum _pmc_system_clock clock)
{
	uint32_t scdr, scsr;

	if (!_pmc_get_system_clock_bits(clock, NULL, &scdr, &scsr)) {
		trace_debug("Unknown System clock: %d\r\n", clock);
		return;
	}

	PMC->PMC_SCDR |= scdr;
	while (PMC->PMC_SCSR & scsr);
}

bool pmc_is_system_clock_enabled(enum _pmc_system_clock clock)
{
	uint32_t scsr;

	if (!_pmc_get_system_clock_bits(clock, NULL, NULL, &scsr)) {
		trace_debug("Unknown System clock: %d\r\n", clock);
		return false;
	}

	return (PMC->PMC_SCSR & scsr) == scsr;
}

#ifdef CONFIG_HAVE_PMC_FAST_STARTUP
void pmc_set_fast_startup_mode(uint32_t startup_mode)
{
	PMC->PMC_FSMR = startup_mode;
}

void pmc_set_fast_startup_polarity(uint32_t high_level, uint32_t low_level)
{
	PMC->PMC_FSPR &= ~low_level;
	PMC->PMC_FSPR |= high_level;
}
#endif /* CONFIG_HAVE_PMC_FAST_STARTUP */

void pmc_set_custom_pck_mck(const struct pck_mck_cfg *cfg)
{
	pmc_switch_mck_to_slck();

	if (cfg->ext12m)
		pmc_select_external_osc(cfg->ext_bypass);
	else
		pmc_select_internal_osc();

	pmc_switch_mck_to_main();

	if (cfg->ext32k)
		pmc_select_external_crystal();
	else
		pmc_select_internal_crystal();

	pmc_disable_plla();
	if (cfg->plla.mul > 0 && cfg->plla.div > 0) {
#ifdef CONFIG_HAVE_PMC_PLLADIV2
		pmc_set_mck_plladiv2(cfg->plla_div2);
#endif
		pmc_configure_plla(&cfg->plla);
	}

#ifdef CONFIG_HAVE_PMC_UPLLDIV2
	pmc_set_mck_uplldiv2(cfg->upll_div2);
#endif
	pmc_set_mck_prescaler(cfg->pck_pres);
	pmc_set_mck_divider(cfg->mck_div);
#ifdef CONFIG_HAVE_PMC_H32MXDIV
	pmc_set_mck_h32mxdiv(cfg->h32mx_div2);
#endif

	switch (cfg->pck_input) {
	case PMC_MCKR_CSS_PLLA_CLK:
		pmc_switch_mck_to_pll();
		break;

	case PMC_MCKR_CSS_UPLL_CLK:
		pmc_switch_mck_to_upll();
		break;

	case PMC_MCKR_CSS_SLOW_CLK:
		pmc_switch_mck_to_slck();
		pmc_disable_internal_osc();
		pmc_disable_external_osc();
		break;
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions (Peripherals)
 *----------------------------------------------------------------------------*/

void pmc_configure_peripheral(uint32_t id, const struct _pmc_periph_cfg* cfg, bool enable)
{
	assert(id < ID_PERIPH_COUNT);

	pmc_disable_peripheral(id);

	if (cfg != NULL) {
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		if (cfg->gck.div > 0)
			pmc_configure_gck(id, cfg->gck.css, cfg->gck.div);
#endif

#ifdef CONFIG_HAVE_PMC_PERIPH_DIV
		_pmc_configure_peripheral_div(id, cfg->div);
#endif
	} else {
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		pmc_disable_gck(id);
#endif
#ifdef CONFIG_HAVE_PMC_PERIPH_DIV
		_pmc_configure_peripheral_div(id, 0);
#endif
	}

	/* Enable peripheral, gck or only configure it */
	if (enable) {
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		if (cfg && cfg->gck.div > 0)
			pmc_enable_gck(id);
#endif
		pmc_enable_peripheral(id);
	}
}

void pmc_enable_peripheral(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	// select peripheral
	PMC->PMC_PCR = PMC_PCR_PID(id);

	volatile uint32_t pcr = PMC->PMC_PCR;
	PMC->PMC_PCR = pcr | PMC_PCR_CMD | PMC_PCR_EN;
}

void pmc_disable_peripheral(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	// select peripheral
	PMC->PMC_PCR = PMC_PCR_PID(id);

	// disable it but keep previous configuration
	PMC->PMC_PCR = (PMC->PMC_PCR & ~PMC_PCR_EN) | PMC_PCR_CMD;
}

bool pmc_is_peripheral_enabled(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

#ifdef PMC_CSR_PID0
	return (PMC->PMC_CSR[(id >> 5) & 3] & (1 << (id & 31))) != 0;
#else
	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;

	return (pcr & PMC_PCR_EN) != 0;
#endif
}

uint32_t pmc_get_peripheral_clock(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	uint32_t div = get_peripheral_clock_matrix_div(id);
#ifdef CONFIG_HAVE_PMC_PERIPH_DIV
	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;
	div *= 1 << ((pcr & PMC_PCR_DIV_Msk) >> PMC_PCR_DIV_Pos);
#endif

	return pmc_get_master_clock() / div;
}

void pmc_disable_all_peripherals(void)
{
	int i;
	for (i = 2; i < ID_PERIPH_COUNT; i++)
		pmc_disable_peripheral(i);
}

/*----------------------------------------------------------------------------
 *        Exported functions (PCK)
 *----------------------------------------------------------------------------*/

void pmc_configure_pck(uint32_t index, uint32_t clock_source, uint32_t prescaler)
{
	assert(index < ARRAY_SIZE(PMC->PMC_PCK));
	assert(!(clock_source & ~PMC_PCK_CSS_Msk));
	assert(!(prescaler << PMC_PCK_PRES_Pos & ~PMC_PCK_PRES_Msk));

	pmc_disable_pck(index);
	PMC->PMC_PCK[index] = clock_source | PMC_PCK_PRES(prescaler);
}

void pmc_enable_pck(uint32_t index)
{
	assert(index < ARRAY_SIZE(PMC->PMC_PCK));

	switch (index) {
#ifdef PMC_SCER_PCK0
	case 0:
		PMC->PMC_SCER = PMC_SCER_PCK0;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY0));
		break;
#endif
#ifdef PMC_SCER_PCK1
	case 1:
		PMC->PMC_SCER = PMC_SCER_PCK1;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY1));
		break;
#endif
#ifdef PMC_SCER_PCK2
	case 2:
		PMC->PMC_SCER = PMC_SCER_PCK2;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY2));
		break;
#endif
#ifdef PMC_SCER_PCK3
	case 3:
		PMC->PMC_SCER = PMC_SCER_PCK3;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY3));
		break;
#endif
#ifdef PMC_SCER_PCK4
	case 4:
		PMC->PMC_SCER = PMC_SCER_PCK4;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY4));
		break;
#endif
#ifdef PMC_SCER_PCK5
	case 5:
		PMC->PMC_SCER = PMC_SCER_PCK5;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY5));
		break;
#endif
#ifdef PMC_SCER_PCK6
	case 6:
		PMC->PMC_SCER = PMC_SCER_PCK6;
		while (!(PMC->PMC_SR & PMC_SR_PCKRDY6));
		break;
#endif
	default:
		assert(0);
	}
}

void pmc_disable_pck(uint32_t index)
{
	assert(index < ARRAY_SIZE(PMC->PMC_PCK));

	switch (index) {
#ifdef PMC_SCDR_PCK0
	case 0:
		PMC->PMC_SCDR = PMC_SCDR_PCK0;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK0);
		break;
#endif
#ifdef PMC_SCDR_PCK1
	case 1:
		PMC->PMC_SCDR = PMC_SCDR_PCK1;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK1);
		break;
#endif
#ifdef PMC_SCDR_PCK2
	case 2:
		PMC->PMC_SCDR = PMC_SCDR_PCK2;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK2);
		break;
#endif
#ifdef PMC_SCDR_PCK3
	case 3:
		PMC->PMC_SCDR = PMC_SCDR_PCK3;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK3);
		break;
#endif
#ifdef PMC_SCDR_PCK4
	case 4:
		PMC->PMC_SCDR = PMC_SCDR_PCK4;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK4);
		break;
#endif
#ifdef PMC_SCDR_PCK5
	case 5:
		PMC->PMC_SCDR = PMC_SCDR_PCK5;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK5);
		break;
#endif
#ifdef PMC_SCDR_PCK6
	case 6:
		PMC->PMC_SCDR = PMC_SCDR_PCK6;
		while (PMC->PMC_SCSR & PMC_SCSR_PCK6);
		break;
#endif
	default:
		assert(0);
	}
}

uint32_t pmc_get_pck_clock(uint32_t index)
{
	assert(index < ARRAY_SIZE(PMC->PMC_PCK));
	return _pmc_get_pck_clock(index);
}

/*----------------------------------------------------------------------------
 *        Exported functions (UPLL)
 *----------------------------------------------------------------------------*/

void pmc_enable_upll_clock(void)
{
	uint32_t uckr = CKGR_UCKR_UPLLEN | CKGR_UCKR_UPLLCOUNT(0x3);

#ifdef CONFIG_HAVE_PMC_UPLL_BIAS
	uckr |= CKGR_UCKR_BIASCOUNT(0x1);
#endif

#if defined(SFR_UTMICKTRIM_FREQ_Msk)
	switch (_pmc_main_oscillators.crystal_freq) {
#ifdef SFR_UTMICKTRIM_FREQ_48
	case 48000000:
		SFR->SFR_UTMICKTRIM = (SFR->SFR_UTMICKTRIM & ~SFR_UTMICKTRIM_FREQ_Msk) | SFR_UTMICKTRIM_FREQ_48;
		break;
#endif
	case 24000000:
		SFR->SFR_UTMICKTRIM = (SFR->SFR_UTMICKTRIM & ~SFR_UTMICKTRIM_FREQ_Msk) | SFR_UTMICKTRIM_FREQ_24;
		break;
	case 16000000:
		SFR->SFR_UTMICKTRIM = (SFR->SFR_UTMICKTRIM & ~SFR_UTMICKTRIM_FREQ_Msk) | SFR_UTMICKTRIM_FREQ_16;
		break;
	default:
		SFR->SFR_UTMICKTRIM = (SFR->SFR_UTMICKTRIM & ~SFR_UTMICKTRIM_FREQ_Msk) | SFR_UTMICKTRIM_FREQ_12;
	}
#elif defined(UTMI_CKTRIM_FREQ_Msk)
	switch (_pmc_main_oscillators.crystal_freq) {
	case 16000000:
		UTMI->UTMI_CKTRIM = (UTMI->UTMI_CKTRIM & ~UTMI_CKTRIM_FREQ_Msk) | UTMI_CKTRIM_FREQ_XTAL16;
		break;
	default:
		UTMI->UTMI_CKTRIM = (UTMI->UTMI_CKTRIM & ~UTMI_CKTRIM_FREQ_Msk) | UTMI_CKTRIM_FREQ_XTAL12;
	}
#endif

	/* enable the 480MHz UTMI PLL  */
	PMC->CKGR_UCKR = uckr;

	/* wait until UPLL is locked */
	while (!(PMC->PMC_SR & PMC_SR_LOCKU));
}

void pmc_disable_upll_clock(void)
{
	PMC->CKGR_UCKR &= ~CKGR_UCKR_UPLLEN;
}

bool pmc_is_upll_clock_enabled(void)
{
	return (PMC->PMC_SR & PMC_SR_LOCKU) != 0;
}

uint32_t pmc_get_upll_clock(void)
{
	uint32_t upllclk;

#if defined(SFR_UTMICKTRIM_FREQ_Msk)
	uint32_t clktrim = SFR->SFR_UTMICKTRIM & SFR_UTMICKTRIM_FREQ_Msk;
	switch (clktrim) {
#ifdef SFR_UTMICKTRIM_FREQ_48
		case SFR_UTMICKTRIM_FREQ_48:
			upllclk = 10 * _pmc_main_oscillators.crystal_freq;
			break;
#endif
		case SFR_UTMICKTRIM_FREQ_24:
			upllclk = 20 * _pmc_main_oscillators.crystal_freq;
			break;
		case SFR_UTMICKTRIM_FREQ_16:
			upllclk = 30 * _pmc_main_oscillators.crystal_freq;
			break;
		default:
			upllclk = 40 * _pmc_main_oscillators.crystal_freq;
			break;
	}
#elif defined(UTMI_CKTRIM_FREQ_Msk)
	uint32_t clktrim = UTMI->UTMI_CKTRIM & UTMI_CKTRIM_FREQ_Msk;
	switch (clktrim) {
		case UTMI_CKTRIM_FREQ_XTAL16:
			upllclk = 30 * _pmc_main_oscillators.crystal_freq;
			break;
		default:
			upllclk = 40 * _pmc_main_oscillators.crystal_freq;
			break;
	}
#else
	upllclk = 40 * _pmc_main_oscillators.crystal_freq;
#endif

#ifdef CONFIG_HAVE_PMC_UPLLDIV2
	if (PMC->PMC_MCKR & PMC_MCKR_UPLLDIV2)
		upllclk >>= 1;
#endif

	return upllclk;
}

#ifdef CONFIG_HAVE_PMC_UPLL_BIAS
void pmc_enable_upll_bias(void)
{
	PMC->CKGR_UCKR |= CKGR_UCKR_BIASEN;
}

void pmc_disable_upll_bias(void)
{
	PMC->CKGR_UCKR &= ~CKGR_UCKR_BIASEN;
}
#endif /* CONFIG_HAVE_PMC_UPLL_BIAS */

uint32_t pmc_get_utmi_clock_trim(void)
{
#if defined(SFR_UTMICKTRIM_FREQ_Msk)
	uint32_t clktrim = SFR->SFR_UTMICKTRIM & SFR_UTMICKTRIM_FREQ_Msk;
	switch (clktrim) {
#ifdef SFR_UTMICKTRIM_FREQ_48
		case SFR_UTMICKTRIM_FREQ_48:
			return 48000000;
#endif
		case SFR_UTMICKTRIM_FREQ_24:
			return 24000000;
		case SFR_UTMICKTRIM_FREQ_16:
			return 16000000;
		default:
			return 12000000;
	}
#elif defined(UTMI_CKTRIM_FREQ_Msk)
	uint32_t clktrim = UTMI->UTMI_CKTRIM & UTMI_CKTRIM_FREQ_Msk;
	switch (clktrim) {
		case UTMI_CKTRIM_FREQ_XTAL16:
			return 16000000;
		default:
			return 12000000;
	}
#else
	return 12000000;
#endif
}

/*----------------------------------------------------------------------------
 *        Exported functions (Generated clocks)
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS

void pmc_configure_gck(uint32_t id, uint32_t clock_source, uint32_t div)
{
	assert(id < ID_PERIPH_COUNT);
	assert(!(clock_source & ~PMC_PCR_GCKCSS_Msk));
	assert(div > 0);
	assert(!((div << PMC_PCR_GCKDIV_Pos) & ~PMC_PCR_GCKDIV_Msk));

	pmc_disable_gck(id);
	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR & ~(PMC_PCR_GCKCSS_Msk | PMC_PCR_GCKDIV_Msk);
	PMC->PMC_PCR = pcr | clock_source | PMC_PCR_CMD | PMC_PCR_GCKDIV(div - 1);
}

void pmc_enable_gck(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;
	PMC->PMC_PCR = pcr | PMC_PCR_CMD | PMC_PCR_GCKEN;

#ifdef PMC_GCSR_PID0
	while ((PMC->PMC_GCSR[(id >> 5) & 3] & (1 << (id & 31))) == 0);
#else
	while (!(PMC->PMC_SR & PMC_SR_GCKRDY));
#endif
}

void pmc_disable_gck(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;
	PMC->PMC_PCR = PMC_PCR_CMD | (pcr & ~PMC_PCR_GCKEN);
}

uint32_t pmc_get_gck_clock(uint32_t id)
{
	uint32_t clk = 0;
	assert(id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);
	volatile uint32_t pcr = PMC->PMC_PCR;

	switch (pcr & PMC_PCR_GCKCSS_Msk) {
	case PMC_PCR_GCKCSS_SLOW_CLK:
		clk = pmc_get_slow_clock();
		break;
	case PMC_PCR_GCKCSS_MAIN_CLK:
		clk = pmc_get_main_clock();
		break;
	case PMC_PCR_GCKCSS_PLLA_CLK:
		clk = pmc_get_plla_clock();
		break;
	case PMC_PCR_GCKCSS_UPLL_CLK:
		clk = pmc_get_upll_clock();
		break;
	case PMC_PCR_GCKCSS_MCK_CLK:
		clk = pmc_get_master_clock();
		break;
#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
	case PMC_PCR_GCKCSS_AUDIO_CLK:
		clk = pmc_get_audio_pmc_clock();
		break;
#endif
	}

	uint32_t div = (pcr & PMC_PCR_GCKDIV_Msk) >> PMC_PCR_GCKDIV_Pos;
	return ROUND_INT_DIV(clk, div + 1);
}

bool pmc_is_gck_enabled(uint32_t id)
{
	assert(id < ID_PERIPH_COUNT);

	PMC->PMC_PCR = PMC_PCR_PID(id);

	return (PMC->PMC_PCR & PMC_PCR_GCKEN) != 0;
}

#endif /* CONFIG_HAVE_PMC_GENERATED_CLOCKS */

/*----------------------------------------------------------------------------
 *        Exported functions (Audio PLL)
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PMC_AUDIO_CLOCK
void pmc_configure_audio(const struct _pmc_audio_cfg *cfg)
{
#ifdef PMC_AUDIO_PLL0_PLLEN
	/* reset audio clock */
	PMC->PMC_AUDIO_PLL0 &= ~(PMC_AUDIO_PLL0_RESETN |
	                         PMC_AUDIO_PLL0_PLLEN);
	PMC->PMC_AUDIO_PLL0 |= PMC_AUDIO_PLL0_RESETN;

	/* configure values */
	PMC->PMC_AUDIO_PLL0 = PMC_AUDIO_PLL0_ND(cfg->nd)
	                    | PMC_AUDIO_PLL0_QDPMC(cfg->qdpmc)
	                    | PMC_AUDIO_PLL0_PLLFLT_STD
	                    | PMC_AUDIO_PLL0_RESETN;
	PMC->PMC_AUDIO_PLL1 = PMC_AUDIO_PLL1_FRACR(cfg->fracr)
	                    | PMC_AUDIO_PLL1_DIV(cfg->div)
	                    | PMC_AUDIO_PLL1_QDAUDIO(cfg->qdaudio);
#else
	/* reset audio clock */
	PMC->PMC_APLLCCR &= ~(PMC_APLLCCR_RESETN |
	                      PMC_APLLCCR_PLLEN);
	PMC->PMC_APLLCCR |= PMC_APLLCCR_RESETN;

	/* configure values */
	PMC->PMC_APLLCCR = PMC_APLLCCR_ND(cfg->nd)
	                 | PMC_APLLCCR_FRACR(cfg->fracr)
	                 | PMC_APLLCCR_RESETN;
	PMC->PMC_APLLPCR = PMC_APLLPCR_QDAUDIO(cfg->div * cfg->qdaudio);
	PMC->PMC_APLLICR = PMC_APLLICR_QDPMC(cfg->qdpmc);
#endif
}

void pmc_enable_audio(bool pmc_clock, bool pad_clock)
{
#ifdef PMC_AUDIO_PLL0_PLLEN
	uint32_t pll0 = PMC->PMC_AUDIO_PLL0;
	pll0 &= ~(PMC_AUDIO_PLL0_PADEN | PMC_AUDIO_PLL0_PMCEN);
	pll0 |= PMC_AUDIO_PLL0_PLLEN;
	if (pad_clock)
		pll0 |= PMC_AUDIO_PLL0_PADEN;
	if (pmc_clock)
		pll0 |= PMC_AUDIO_PLL0_PMCEN;
	PMC->PMC_AUDIO_PLL0 = pll0;
#else
	PMC->PMC_APLLCCR |= PMC_APLLCCR_PLLEN;

	if (pad_clock)
		PMC->PMC_APLLPCR |= PMC_APLLPCR_PADEN;
	else
		PMC->PMC_APLLPCR &= ~PMC_APLLPCR_PADEN;

	if (pmc_clock)
		PMC->PMC_APLLICR |= PMC_APLLICR_PMCEN;
	else
		PMC->PMC_APLLICR &= ~PMC_APLLICR_PMCEN;
#endif

	/* Wait for the Audio PLL Startup Time (tSTART = 100 usec) */
	usleep(100);
}

void pmc_disable_audio()
{
#ifdef PMC_AUDIO_PLL0_PLLEN
	PMC->PMC_AUDIO_PLL0 &= ~(PMC_AUDIO_PLL0_PLLEN | PMC_AUDIO_PLL0_PADEN | PMC_AUDIO_PLL0_PMCEN);
#else
	PMC->PMC_APLLPCR &= ~PMC_APLLPCR_PADEN;
	PMC->PMC_APLLICR &= ~PMC_APLLICR_PMCEN;
	PMC->PMC_APLLCCR &= ~PMC_APLLCCR_PLLEN;
#endif
}

uint32_t pmc_get_audio_pmc_clock(void)
{
	uint32_t nd, fracr, qdpmc;
	uint64_t clk = _pmc_main_oscillators.crystal_freq;

#ifdef PMC_AUDIO_PLL0_PLLEN
	uint32_t pll0 = PMC->PMC_AUDIO_PLL0;
	uint32_t pll1 = PMC->PMC_AUDIO_PLL1;
	nd = (pll0 & PMC_AUDIO_PLL0_ND_Msk) >> PMC_AUDIO_PLL0_ND_Pos;
	fracr = (pll1 & PMC_AUDIO_PLL1_FRACR_Msk) >> PMC_AUDIO_PLL1_FRACR_Pos;
	qdpmc = (pll0 & PMC_AUDIO_PLL0_QDPMC_Msk) >> PMC_AUDIO_PLL0_QDPMC_Pos;
#else
	uint32_t ccr = PMC->PMC_APLLCCR;
	nd = (ccr & PMC_APLLCCR_ND_Msk) >> PMC_APLLCCR_ND_Pos;
	fracr = (ccr & PMC_APLLCCR_FRACR_Msk) >> PMC_APLLCCR_FRACR_Pos;
	qdpmc = (PMC->PMC_APLLICR & PMC_APLLICR_QDPMC_Msk) >> PMC_APLLICR_QDPMC_Pos;
#endif

	clk *= ((nd + 1) << 22) + fracr;
	clk /= 1 << 22;
	clk /= qdpmc + 1;
	return (uint32_t)clk;
}

uint32_t pmc_get_audio_pad_clock(void)
{
	uint32_t nd, fracr, qdaudio, div;
	uint64_t clk = _pmc_main_oscillators.crystal_freq;

#ifdef PMC_AUDIO_PLL0_PLLEN
	uint32_t pll0 = PMC->PMC_AUDIO_PLL0;
	uint32_t pll1 = PMC->PMC_AUDIO_PLL1;
	nd = (pll0 & PMC_AUDIO_PLL0_ND_Msk) >> PMC_AUDIO_PLL0_ND_Pos;
	fracr = (pll1 & PMC_AUDIO_PLL1_FRACR_Msk) >> PMC_AUDIO_PLL1_FRACR_Pos;
	qdaudio = (pll1 & PMC_AUDIO_PLL1_QDAUDIO_Msk) >> PMC_AUDIO_PLL1_QDAUDIO_Pos;
	if (qdaudio == 0)
		return 0;
	div = (pll1 & PMC_AUDIO_PLL1_DIV_Msk) >> PMC_AUDIO_PLL1_DIV_Pos;
	if (div != 2 && div != 3)
		return 0;
#else
	uint32_t ccr = PMC->PMC_APLLCCR;
	nd = (ccr & PMC_APLLCCR_ND_Msk) >> PMC_APLLCCR_ND_Pos;
	fracr = (ccr & PMC_APLLCCR_FRACR_Msk) >> PMC_APLLCCR_FRACR_Pos;
	qdaudio = (PMC->PMC_APLLPCR & PMC_APLLPCR_QDAUDIO_Msk) >> PMC_APLLPCR_QDAUDIO_Pos;
	if (qdaudio == 0)
		return 0;
	div = 1;
#endif

	clk *= ((nd + 1) << 22) + fracr;
	clk /= 1 << 22;
	clk /= div * qdaudio;
	return (uint32_t)clk;
}
#endif /* CONFIG_HAVE_PMC_AUDIO_CLOCK */
