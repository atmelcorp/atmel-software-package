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

/**
 * \file
 *
 * \par Purpose
 *
 * Interface for configuration the Pulse Width Modulation Controller (PWM) peripheral.
 *
 * \par Usage
 *
 *    -# Configures PWM clocks A & B to run at the given frequencies using
 *       pwmc_configure_clocks().
 *    -# Configure PWMC channel using pwmc_configure_channel(), pwmc_set_period()
 *       and pwmc_set_duty_cycle().
 *    -# Enable & disable channel using pwmc_enable_channel() and pwmc_disable_channel().
 *    -# Enable & disable the period interrupt for the given PWM channel using
 *       pwmc_enable_channel_it() and pwmc_disable_channel_it().
 *
 */

#ifndef PWMC_H_
#define PWMC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/** definitions for PWM fault inputs */
enum _pwm_fault_inputs{
	PWM_FAULT_INPUT_PWMFI0 = 0,
	PWM_FAULT_INPUT_PWMFI1 = 1,
	PWM_FAULT_INPUT_MAIN_OSC = 2,
	PWM_FAULT_INPUT_ADC = 3,
	PWM_FAULT_INPUT_TIMER0 = 4,
	PWM_FAULT_INPUT_TIMER1 = 5,
};

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** definitions for PWM callback function */
typedef void (*pwmc_callback_t)(void* args);

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures PWM clocks
 * \param pwm  Pointer to a Pwm instance
 * \param mode  PWM clock source selection and divide factor.
 */
extern void pwmc_configure_clocks(Pwm *pwm, uint32_t mode);

/**
 * \brief Enables the given PWM channel.
 *
 * This does NOT enable the corresponding pin; this must be done in the user
 * code.
 *
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 */
extern void pwmc_enable_channel(Pwm *pwm, uint8_t channel);

/**
 * \brief Disables the given PWM channel.
 *
 * Beware, the channel will be effectively disabled at the end of the current
 * period.
 * Applications may check whether the channel is disabled using the following
 * wait loop:
 * 	while ((PWM->PWM_SR & (1 << channel)) != 0) {};
 *
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 */
extern void pwmc_disable_channel(Pwm *pwm, uint8_t channel);

/**
 * \brief Enables the selected interrupts sources on a PWMC peripheral.
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 */
extern void pwmc_enable_channel_it(Pwm *pwm, uint8_t channel);

/**
 * \brief Disables the selected interrupts sources on a PWMC peripheral.
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 */
extern void pwmc_disable_channel_it(Pwm *pwm, uint8_t channel);

/**
 * \brief Return PWM Interrupt Status1 Register
 * \param pwm Pointer to a Pwm instance.
 */
extern uint32_t pwmc_get_it_status1(Pwm *pwm);

/**
 * \brief Enables the selected interrupts sources on a PWMC peripheral.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param sources1  Bitwise OR of selected interrupt sources of PWM_IER1.
 * \param sources2  Bitwise OR of selected interrupt sources of PWM_IER2.
 */
extern void pwmc_enable_it(Pwm *pwm, uint32_t sources1, uint32_t sources2);

/**
 * \brief Disables the selected interrupts sources on a PWMC peripheral.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param sources1  Bitwise OR of selected interrupt sources of PWM_IDR1.
 * \param sources2  Bitwise OR of selected interrupt sources of PWM_IDR2.
 */
extern void pwmc_disable_it(Pwm *pwm, uint32_t sources1, uint32_t sources2);

/**
 * \brief Return PWM Interrupt Status2 Register
 * \param pwm Pointer to a Pwm instance.
 */
extern uint32_t pwmc_get_it_status2(Pwm *pwm);

/**
 * \brief Configures a PWM channel with the given parameters, basic configure
 * function.
 *
 * The PWM controller must have been clocked in the PMC prior to calling this
 * function.
 * Beware: this function disables the channel. It will wait until the channel is
 * effectively disabled.
 *
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 * \param mode  Channel mode.
 */
extern void pwmc_configure_channel(Pwm *pwm, uint8_t channel, uint32_t mode);

/**
 * \brief Sets the period value used by a PWM channel.
 *
 * This function writes directly to the CPRD register if the channel is
 * disabled. Otherwise it sets the update register CPRDUPD.
 *
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 * \param period  Period value.
 */
extern void pwmc_set_period(Pwm *pwm, uint8_t channel, uint16_t period);

/**
 * \brief Sets the duty cycle used by a PWM channel.
 * This function writes directly to the CDTY register if the channel is
 * disabled. Otherwise it sets the update register CDTYUPD.
 * Note that the duty cycle must always be inferior or equal to the channel
 * period.
 *
 * \param pwm  Pointer to a Pwm instance
 * \param channel  Channel number.
 * \param duty  Duty cycle value.
 */
extern void pwmc_set_duty_cycle(Pwm *pwm, uint8_t channel, uint16_t duty);

/**
 * \brief Set PWM synchronous channels mode.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param mode Channel number.
 */
extern void pwmc_configure_sync_channels(Pwm *pwm, uint32_t mode);

/**
 * \brief Sets synchronous channels update unlock.
 * \param pwm Pointer to a Pwm instance.
 */
extern void pwmc_set_sync_channels_update_unlock(Pwm *pwm);

/**
 * \brief Sets synchronous channels update period.
 * \param pwm Pointer to a Pwm instance.
 * \param counter update period counter.
 * \param period update period.
 */
extern void pwmc_set_sync_channels_update_period(Pwm *pwm,
		uint8_t counter, uint8_t period);

/**
 * \brief Sets synchronous channels update period update register.
 * \param pwm Pointer to a Pwm instance.
 * \param period update period.
 */
extern void pwmc_set_sync_channels_update_period_update(Pwm *pwm, uint8_t period);

#ifdef CONFIG_HAVE_PWM_DMA

/**
 * \brief Sets the update period of the synchronous channels.
 *
 * \param cb Point to PWM call back routine.
 * \param user_args parameter for call back routine.
 */
extern void pwmc_set_dma_finished_callback(pwmc_callback_t cb, void *user_args);

/**
 * \brief Sets the update period of the synchronous channels.
 * \param pwm Pointer to a Pwm instance.
 * \param duty Pointer to a duty buffer to be set.
 * \param size size of duties to be transfered.
 */
extern void pwmc_dma_duty_cycle(Pwm *pwm, uint16_t *duty, uint32_t size);

#endif /* CONFIG_HAVE_PWM_DMA */

/**
 * \brief Set override output.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param is_pwmh which output to override 0: PWML, others: PWMH.
 * \param level Output level for override.
 * \param sync 0: enable the output asynchronously, 1: enable it synchronously
 */
extern void pwmc_output_override(Pwm *pwm, uint8_t channel,
		uint8_t is_pwmh, uint8_t level, uint8_t sync);

/**
 * \brief Disable override output.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param is_pwmh which output to override 0: PWML, others: PWMH.
 * \param sync 0: enable the output asynchronously, 1: enable it synchronously
 */
extern void pwmc_disable_output_override(Pwm *pwm, uint8_t channel,
		uint8_t is_pwmh, uint8_t sync);

/**
 * \brief Sets the dead time used by a PWM channel.
 * This function writes directly to the DT register if the channel is disabled;
 * otherwise it uses the update register DTUPD.
 * Note that the dead time must always be inferior or equal to the channel
 * period.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param time_h Dead time value for PWMHx output.
 * \param time_l Dead time value for PWMLx output.
 */
extern void pwmc_output_dead_time(Pwm *pwm, uint8_t channel,
		uint16_t time_h, uint16_t time_l);

/**
 * \brief Set PWM fault mode.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param mode Bitwise OR of fault mode.
 */
extern void pwmc_set_fault_mode(Pwm *pwm, uint32_t mode);

/**
 * \brief Get fault status.
 *
 * \param pwm Pointer to a Pwm instance.
 * \return Fault status.
 */
extern uint32_t pwmc_get_fault_status(Pwm *pwm);

/**
 * \brief PWM fault clear.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param fault Bitwise OR of fault to clear.
 */
extern void pwmc_fault_clear(Pwm *pwm, uint32_t fault);

/**
 * \brief Set PWM fault protections.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param value Bitwise OR for PWM_FPV1.
 */
extern void pwmc_set_fault_protection(Pwm *pwm, uint32_t value);

#ifdef CONFIG_HAVE_PWM_FAULT_PROT_HIZ

/**
 * \brief Set PWM fault protections to Hi-Z
 *
 * \param pwm Pointer to a Pwm instance.
 * \param value Bitwise OR for PWM_FPV2.
 */
extern void pwmc_set_fault_protection_to_hiz(Pwm *pwm, uint32_t value);

#endif /* CONFIG_HAVE_PWM_FAULT_PROT_HIZ */

/**
 * \brief Enable PWM fault protection.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param fault_inputs Bitwise OR of FPEx[y].
 */
extern void pwmc_enable_fault_protection(Pwm *pwm, uint8_t channel,
		uint8_t fault_inputs);

/**
 * \brief Configure event line mode.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param value Bitwise OR of ELMR[y].
 */
extern void pwmc_configure_event_line_mode(Pwm *pwm, uint32_t value);

#ifdef CONFIG_HAVE_PWM_SPREAD_SPECTRUM

/**
 * \brief Configure spread spectrum mode.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param mode Bitwise OR for SSPR
 */
extern void pwmc_configure_spread_spectrum_mode(Pwm *pwm, uint32_t value);

#endif /* CONFIG_HAVE_PWM_SPREAD_SPECTRUM */

#ifdef CONFIG_HAVE_PWM_STEPPER_MOTOR

/**
 * \brief Configure stepper motor mode.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param mode Bitwise OR for SMMR
 */
extern void pwmc_configure_stepper_motor_mode(Pwm *pwm, uint32_t value);

#endif /* CONFIG_HAVE_PWM_STEPPER_MOTOR */

/**
 * \brief Set write protection.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param value Write protection control value.
 */
extern void pwmc_set_write_protection_control(Pwm *pwm, uint32_t value);

/**
 * \brief Get write protection status.
 *
 * \param pwm Pointer to a Pwm instance.
 * \return Write protection status.
 */
extern uint32_t pwmc_get_write_protection_status(Pwm *pwm);

/**
 * \brief Configure comparison unit.
 *
 * \param x comparison x index
 * \param value comparison x value.
 * \param mode comparison x mode
 */
extern void pwmc_configure_comparison_unit(Pwm *pwm, uint32_t x,
		uint32_t value, uint32_t mode);

#ifdef CONFIG_HAVE_PWM_EXTERNAL_TRIGGER

/**
 * \brief Configure external trigger.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param value External trigger configuration.
 */
extern void pwmc_configure_external_trigger(Pwm *pwm,
		uint32_t channel, uint32_t value);

/**
 * \brief Configure leading-edge blanking.
 *
 * \param pwm Pointer to a Pwm instance.
 * \param channel Channel number.
 * \param value Leading-edge blanking configuration.
 */
extern void pwmc_configure_leading_edge_blanking(Pwm *pwm,
		uint32_t channel, uint32_t value);

#endif /* CONFIG_HAVE_PWM_EXTERNAL_TRIGGER */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef PWMC_H_ */
