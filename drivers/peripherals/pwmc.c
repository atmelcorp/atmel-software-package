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

/** \addtogroup pwm_module Working with PWM
 * \section Purpose
 * The PWM driver provides the interface to configure and use the PWM
 * peripheral.
 *
 * The PWM macrocell controls square output waveforms of 4 channels.
 * Characteristics of output waveforms such as period, duty-cycle can be configured.\n
 *
 * Before enabling the channels, they must have been configured first.
 * The main settings include:
 * <ul>
 * <li>Configuration of the clock generator.</li>
 * <li>Selection of the clock for each channel.</li>
 * <li>Configuration of output waveform characteristics, such as period, duty-cycle etc.</li>
 * </ul>
 *
 * After the channels is enabled, the user must use respective update registers
 * to change the wave characteristics to prevent unexpected output waveform.
 * i.e. PWM_CUPDx register should be used if user want to change duty-cycle
 * when the channel is enabled.
 *
 * \section Usage
 * <ul>
 * <li>  Configure PWM clock using pwmc_configure_clocks().
 * <li>  Enable & disable given PWM channel using pwmc_enable_channel() and pwmc_disable_channel().
 * <li>  Enable & disable interrupt of given PWM channel using pwmc_enable_channel_it()
 * and pwmc_disable_channel_it().
 * <li>  Set feature of the given PWM channel's output signal using pwmc_set_period()
 * and pwmc_set_duty_cycle().
 * </li>
 * </ul>
 *
 * For more accurate information, please look at the PWM section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref pwmc.c\n
 * \ref pwmc.h.\n
 */
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of the Pulse Width Modulation Controller (PWM) peripheral.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "callback.h"
#include "chip.h"
#include "dma/dma.h"
#include "mm/cache.h"
#include "peripherals/pwmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PWMC_DMA
static struct _dma_channel* pwm_dma_channel = NULL;
static struct _callback pwmc_cb;
#endif /* CONFIG_HAVE_PWMC_DMA */

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void pwmc_configure_clocks(Pwm *pwm, uint32_t mode)
{
	pwm->PWM_CLK = mode;
}

void pwmc_enable_channel(Pwm *pwm, uint8_t channel)
{
	pwm->PWM_ENA = 0x1ul << channel;
}

void pwmc_disable_channel(Pwm *pwm, uint8_t channel)
{
	pwm->PWM_DIS = 0x1ul << channel;
}

void pwmc_enable_channel_it(Pwm *pwm, uint8_t channel)
{
	pwm->PWM_IER1 = 0x1ul << channel;
}

void pwmc_disable_channel_it(Pwm *pwm, uint8_t channel)
{
	pwm->PWM_IDR1 = 0x1ul << channel;
}

uint32_t pwmc_get_it_status1(Pwm *pwm)
{
	return pwm->PWM_ISR1;
}

void pwmc_enable_it(Pwm *pwm, uint32_t sources1, uint32_t sources2)
{
	pwm->PWM_IER1 = sources1;
#ifdef CONFIG_HAVE_PWMC_CMP_UNIT
	pwm->PWM_IER2 = sources2;
#endif
}

void pwmc_disable_it(Pwm *pwm, uint32_t sources1, uint32_t sources2)
{
	pwm->PWM_IDR1 = sources1;
#ifdef CONFIG_HAVE_PWMC_CMP_UNIT
	pwm->PWM_IDR2 = sources2;
#endif
}

#ifdef CONFIG_HAVE_PWMC_CMP_UNIT
uint32_t pwmc_get_it_status2(Pwm *pwm)
{
	return pwm->PWM_ISR2;
}

void pwmc_configure_comparison_unit(Pwm *pwm, uint32_t x,
		uint32_t value, uint32_t mode)
{
	assert(x < 8);

	/* If channel is disabled, write to CMPxM & CMPxV */
	if ((pwm->PWM_SR & (1 << 0)) == 0) {
		pwm->PWM_CMP[x].PWM_CMPM = mode;
		pwm->PWM_CMP[x].PWM_CMPV = value;
	} else {
		/* Otherwise use update register */
		pwm->PWM_CMP[x].PWM_CMPMUPD = mode;
		pwm->PWM_CMP[x].PWM_CMPVUPD = value;
	}
}

#endif /* CONFIG_HAVE_PWMC_CMP_UNIT */

void pwmc_configure_channel(Pwm *pwm, uint8_t channel, uint32_t mode)
{
	assert(channel < ARRAY_SIZE(pwm->PWM_CH));

	trace_debug("pwm: set channel %u with mode 0x%08x\n\r", \
			(unsigned)channel, (unsigned)mode);

#ifdef PWM_CMUPD0_CPOLUP
	if ((pwm->PWM_SR & (1 << channel)) == 0)
		pwm->PWM_CH[channel].PWM_CMR = mode;
	else {
		switch (channel) {
			case 0:
				pwm->PWM_CMUPD0 = mode;
				break;
			case 1:
				pwm->PWM_CMUPD1 = mode;
				break;
			case 2:
				pwm->PWM_CMUPD2 = mode;
				break;
			case 3:
			default:
				pwm->PWM_CMUPD3 = mode;
				break;
		}
	}
#else
	pwm->PWM_CH[channel].PWM_CMR = mode;
#endif
}

void pwmc_set_period(Pwm *pwm, uint8_t channel, uint16_t period)
{
	assert(channel < ARRAY_SIZE(pwm->PWM_CH));

	/* If channel is disabled, write to CPRD */
	if ((pwm->PWM_SR & (1 << channel)) == 0) {
		pwm->PWM_CH[channel].PWM_CPRD = period;
	}
	/* Otherwise use update register */
	else {
#ifdef PWM_CMR_CPD
		pwm->PWM_CH[channel].PWM_CMR |= PWM_CMR_CPD;
		pwm->PWM_CH[channel].PWM_CUPD = period;
#else
		pwm->PWM_CH[channel].PWM_CPRDUPD = period;
#endif
	}
}

void pwmc_set_duty_cycle(Pwm *pwm, uint8_t channel, uint16_t duty)
{
	assert(channel < ARRAY_SIZE(pwm->PWM_CH));
	assert(pwm->PWM_CH[channel].PWM_CPRD >= duty);

	/* If channel is disabled, write to CDTY */
	if ((pwm->PWM_SR & (1 << channel)) == 0) {
		pwm->PWM_CH[channel].PWM_CDTY = duty;
	}
	/* Otherwise use update register */
	else {
#ifdef PWM_CMR_CPD
		pwm->PWM_CH[channel].PWM_CMR &= ~PWM_CMR_CPD;
		pwm->PWM_CH[channel].PWM_CUPD = duty;
#else
		pwm->PWM_CH[channel].PWM_CDTYUPD = duty;
#endif
	}
}

#ifdef CONFIG_HAVE_PWMC_SYNC_MODE
void pwmc_configure_sync_channels(Pwm *pwm, uint32_t mode)
{
#ifndef NDEBUG
	uint32_t sync_bits = mode & (PWM_SCM_SYNC0 | PWM_SCM_SYNC1 \
				     | PWM_SCM_SYNC2 | PWM_SCM_SYNC3);
#ifdef CONFIG_HAVE_PWMC_DMA
	trace_debug("pwm: SYNC CHs bitmap 0x%x, Update Mode %u, " \
		    "DMA Request Mode %u, Request Comparison Selection %u\n\r",
		    (unsigned)sync_bits,
		    (unsigned)((mode & PWM_SCM_UPDM_Msk) >> PWM_SCM_UPDM_Pos), \
		    (unsigned)(0 != (mode & PWM_SCM_PTRM)),		\
		    (unsigned)((mode & PWM_SCM_PTRCS_Msk) >> PWM_SCM_PTRCS_Pos));
#else
	trace_debug("pwm: SYNC CHs bitmap 0x%x, Update Mode %u, " ,
		    (unsigned)sync_bits,
		    (unsigned)((mode & PWM_SCM_UPDM_Msk) >> PWM_SCM_UPDM_Pos));
#endif

	/* Defining a channel as a synchronous channel while it is an asynchronous
	channel (by writing the bit SYNCx to '1' while it was at '0') is allowed
	only if the channel is disabled at this time (CHIDx = 0 in PWM_SR). In the
	same way, defining a channel as an asynchronous channel while it is a
	synchronous channel (by writing the SYNCx bit to '0' while it was '1') is
	allowed only if the channel is disabled at this time. */
	uint32_t pwm_sr = pwm->PWM_SR;
	assert((pwm_sr & (pwm->PWM_SCM ^ sync_bits)) == 0);
	/* Mode3 does not exist */
	assert(((mode & PWM_SCM_UPDM_Msk) >> PWM_SCM_UPDM_Pos) != 3);
#ifndef CONFIG_HAVE_PWMC_DMA
	/* Mode2 does not exist if PWM does not support DMA */
	assert(((mode & PWM_SCM_UPDM_Msk) >> PWM_SCM_UPDM_Pos) != 2);
#endif
#endif
	pwm->PWM_SCM = mode;
}

void pwmc_set_sync_channels_update_unlock(Pwm *pwm)
{
	pwm->PWM_SCUC = PWM_SCUC_UPDULOCK;
}

void pwmc_set_sync_channels_update_period(Pwm *pwm,
		uint8_t counter, uint8_t period)
{
	pwm->PWM_SCUP = PWM_SCUP_UPRCNT(counter) | PWM_SCUP_UPR(period);
}

void pwmc_set_sync_channels_update_period_update(Pwm *pwm, uint8_t period)
{
	pwm->PWM_SCUPUPD = PWM_SCUPUPD_UPRUPD(period);
}
#endif /* CONFIG_HAVE_PWMC_SYNC_MODE */

#ifdef CONFIG_HAVE_PWMC_DMA
static int _pwm_dma_callback_wrapper(void* arg, void* arg2)
{
	struct _dma_channel* dma_channel = (struct _dma_channel*)arg;

	if (dma_is_transfer_done(dma_channel)) {
		dma_free_channel(dma_channel);
		callback_call(&pwmc_cb, NULL);
	}

	return 0;
}

void pwmc_set_dma_finished_callback(Pwm *pwm, struct _callback* cb)
{
	uint32_t id = get_pwm_id_from_addr(pwm);

	if (!pwm_dma_channel) {
		pwm_dma_channel = dma_allocate_channel(DMA_PERIPH_MEMORY, id);
		assert(pwm_dma_channel);
	}
	callback_copy(&pwmc_cb, cb);
}

void pwmc_dma_duty_cycle(Pwm* pwm, uint16_t *duty, uint32_t size)
{
	struct _callback _cb;
	struct _dma_cfg dma_cfg;
	struct _dma_transfer_cfg cfg;

	assert(pwm_dma_channel);
	memset(&cfg, 0, sizeof(cfg));
	cfg.saddr = (void*)duty;
	cfg.daddr = (void*)&pwm->PWM_DMAR;
	cfg.len = size;
	dma_cfg.incr_saddr = true;
	dma_cfg.incr_daddr = false;
	dma_cfg.loop = false;
	dma_cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
	dma_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_reset_channel(pwm_dma_channel);
	dma_configure_transfer(pwm_dma_channel, &dma_cfg, &cfg, 1);
	callback_set(&_cb, _pwm_dma_callback_wrapper, pwm_dma_channel);
	dma_set_callback(pwm_dma_channel, &_cb);

	cache_clean_region(duty, size);
	dma_start_transfer(pwm_dma_channel);
}

#endif /* CONFIG_HAVE_PWMC_DMA */

#ifdef CONFIG_HAVE_PWMC_OOV
void pwmc_output_override(Pwm *pwm, uint8_t channel,
		uint8_t is_pwmh, uint8_t level, uint8_t sync)
{
	volatile uint32_t tmp;
	uint32_t mask;

	assert(channel < ARRAY_SIZE(pwm->PWM_CH));

	trace_debug("pwm: CH%u PWM%c output overridden to %u\n\r",
			(unsigned)channel, (0 != is_pwmh) ? 'H' : 'L', (unsigned)level);

	if (0 == is_pwmh)
		mask = PWM_OSS_OSSH0 << channel;
	else
		mask = PWM_OSS_OSSL0 << channel;

	tmp = pwm->PWM_OOV;
	if (0 == level)
		tmp &= ~mask;
	else
		tmp |= mask;
	pwm->PWM_OOV = tmp;

	/* If channel is disabled, write to OSS */
	if (((pwm->PWM_SR & (1 << channel)) == 0) || (0 != sync))
		pwm->PWM_OSS = mask;
	/* Otherwise use update register */
	else
		pwm->PWM_OSSUPD = mask;
}

void pwmc_disable_output_override(Pwm *pwm, uint8_t channel,
		uint8_t is_pwmh, uint8_t sync)
{
	uint32_t mask;

	assert(channel < ARRAY_SIZE(pwm->PWM_CH));

	trace_debug("pwm: CH%u PWM%c output override disabled\n\r",
			(unsigned)channel, (0 != is_pwmh) ? 'H' : 'L');

	if (0 == is_pwmh)
		mask = PWM_OSS_OSSH0 << channel;
	else
		mask = PWM_OSS_OSSL0 << channel;

	/* If channel is disabled, write to OSS */
	if (((pwm->PWM_SR & (1 << channel)) == 0) || (0 != sync))
		pwm->PWM_OSC = mask;
	/* Otherwise use update register */
	else
		pwm->PWM_OSCUPD = mask;
}

#endif /* CONFIG_HAVE_PWMC_OOV */

#ifdef CONFIG_HAVE_PWMC_DTIME
void pwmc_output_dead_time(Pwm *pwm, uint8_t channel,
		uint16_t time_h, uint16_t time_l)
{
	uint32_t dead_time;

	assert(channel < ARRAY_SIZE(pwm->PWM_CH));

	trace_debug("pwm: CH%u output dead time H: %u, L: %u\n\r",
			(unsigned)channel, (unsigned)time_h, (unsigned)time_l);

#ifndef NDEBUG
	uint32_t pwm_cprd = pwm->PWM_CH[channel].PWM_CPRD;
	uint32_t pwm_cdty = pwm->PWM_CH[channel].PWM_CDTY;
	assert(pwm_cprd - pwm_cdty >= time_h);
	assert(pwm_cdty >= time_l);
#endif

	dead_time = PWM_DT_DTH(time_h) | PWM_DT_DTL(time_l);

	/* If channel is disabled, write to DT */
	if ((pwm->PWM_SR & (1 << channel)) == 0)
		pwm->PWM_CH[channel].PWM_DT = dead_time;
	/* Otherwise use update register */
	else
		pwm->PWM_CH[channel].PWM_DTUPD = dead_time;
}

#endif /* CONFIG_HAVE_PWMC_DTIME */

#ifdef CONFIG_HAVE_PWMC_FMODE
void pwmc_set_fault_mode(Pwm *pwm, uint32_t mode)
{
	pwm->PWM_FMR = mode;
}

uint32_t pwmc_get_fault_status(Pwm *pwm)
{
	return pwm->PWM_FSR;
}

void pwmc_fault_clear(Pwm *pwm, uint32_t fault)
{
	pwm->PWM_FCR = fault;
}

void pwmc_set_fault_protection(Pwm *pwm, uint32_t value)
{
	pwm->PWM_FPV1 = value;
}

void pwmc_enable_fault_protection(Pwm *pwm, uint8_t channel,
		uint8_t fault_inputs)
{
	volatile uint32_t tmp;
	assert(channel < ARRAY_SIZE(pwm->PWM_CH));
	tmp = pwm->PWM_FPE;
	tmp &= ~(PWM_FPE_FPE0_Msk << (8 * channel));
	pwm->PWM_FPE = tmp | ((uint32_t)fault_inputs << (8 * channel));
}

#endif /* CONFIG_HAVE_PWMC_FMODE */

#ifdef CONFIG_HAVE_PWMC_FAULT_PROT_HIZ
void pwmc_set_fault_protection_to_hiz(Pwm *pwm, uint32_t value)
{
	pwm->PWM_FPV2 = value;
}

#endif /* CONFIG_HAVE_PWMC_FAULT_PROT_HIZ */

#ifdef CONFIG_HAVE_PWMC_ELINE
void pwmc_configure_event_line_mode(Pwm *pwm, uint32_t value)
{
	pwm->PWM_ELMR[0] = value;
}
#endif /* CONFIG_HAVE_PWMC_ELINE */

#ifdef CONFIG_HAVE_PWMC_SPREAD_SPECTRUM
void pwmc_configure_spread_spectrum_mode(Pwm *pwm, uint32_t value)
{
	/* If channel 0 is disabled, write to SSPR */
	if (0 == (pwm->PWM_SR & (1 << 0)))
		pwm->PWM_SSPR = value;
	/* Otherwise use update register */
	else
		pwm->PWM_SSPUP = PWM_SSPUP_SPRDUP(value);
}

#endif /* CONFIG_HAVE_PWMC_SPREAD_SPECTRUM */

#ifdef CONFIG_HAVE_PWMC_STEPPER_MOTOR
void pwmc_configure_stepper_motor_mode(Pwm *pwm, uint32_t value)
{
	trace_debug("pwm: CH0-1 Gray Count %s %s, CH2-3 Gray Count %s %s\n\r", \
			(0 != (value & PWM_SMMR_DOWN0)) ? "Down" : "Up", \
			(0 != (value & PWM_SMMR_GCEN0)) ? "Enable" : "Disable", \
			(0 != (value & PWM_SMMR_DOWN1)) ? "Down" : "Up", \
			(0 != (value & PWM_SMMR_GCEN1)) ? "Enable" : "Disable");
	pwm->PWM_SMMR = value;
}
#endif /* CONFIG_HAVE_PWMC_STEPPER_MOTOR */

#ifdef CONFIG_HAVE_PWMC_WP
void pwmc_set_write_protection_control(Pwm *pwm, uint32_t value)
{
	pwm->PWM_WPCR = value;
}

uint32_t pwmc_get_write_protection_status(Pwm *pwm)
{
	return pwm->PWM_WPSR;
}
#endif /* CONFIG_HAVE_PWMC_WP */

#ifdef CONFIG_HAVE_PWMC_EXTERNAL_TRIGGER
void pwmc_configure_external_trigger(Pwm *pwm,
		uint32_t channel, uint32_t value)
{
	trace_debug("pwm: external trigger for channel %u, value %08x\n\r", \
		(unsigned)channel, (unsigned)value);
	switch (channel) {
	case 1:
		pwm->PWM_ETRG1 = value;
		break;
	case 2:
		pwm->PWM_ETRG2 = value;
		break;
	default:
		assert(0);
		break;
	}
}

void pwmc_configure_leading_edge_blanking(Pwm *pwm,
		uint32_t channel, uint32_t value)
{
	trace_debug("pwm: leading-edge blanking channel %u, value %08x\n\r", \
		(unsigned)channel, (unsigned)value);
	switch (channel) {
	case 1:
		pwm->PWM_LEBR1 = value;
		break;
	case 2:
		pwm->PWM_LEBR2 = value;
		break;
	default:
		assert(0);
		break;
	}
}
#endif /* CONFIG_HAVE_PWMC_EXTERNAL_TRIGGER */
