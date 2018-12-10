/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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
 * \brief Real-time Timer (RTT) driver.
 *
 */


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/rtt.h"
#include "trace.h"
#include <stdint.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize the given RTT.
 *
 * \note This function restarts the real-time timer. If w_prescaler is equal to zero,
 *  the prescaler period is equal to 2^16 * SCLK period. If not, the prescaler period
 *  is equal to us_prescaler * SCLK period.
 *
 * \param prescaler Prescaler value for the RTT.
 */
void rtt_init(uint16_t prescaler)
{
	RTT->RTT_MR = (prescaler | RTT_MR_RTTRST);
}

/**
 * \brief Enable RTT.
 */
void rtt_enable(void)
{
	RTT->RTT_MR  &= ~RTT_MR_RTTDIS;
}

/**
 * \brief Disable RTT.
 *
 */
void rtt_disable(void)
{
	RTT->RTT_MR |= RTT_MR_RTTDIS;
}

/**
 * \brief Select RTT clock.
 *
 * \param is_one_hz RTT 1Hz Clock Selection.
 */
void rtt_sel_clk(bool is_one_hz)
{
	if(is_one_hz) {
		RTT->RTT_MR |= RTT_MR_RTC1HZ;
	} else {
		RTT->RTT_MR &= ~RTT_MR_RTC1HZ;
	}
}

/**
 * \brief Get the status register value of the given RTT.
 *
 * \return The Real-time Timer status.
 */
uint32_t rtt_get_status(void)
{
	return RTT->RTT_SR;
}

/**
 * \brief Read the current value of the RTT timer value.
 *
 * \return The current Real-time Timer value.
 */
uint32_t rtt_get_timer(void)
{
	uint32_t rtt_val = RTT->RTT_VR;

	/* As CRTV can be updated asynchronously, it must be read twice at the same value. */
	while (rtt_val != RTT->RTT_VR) {
		rtt_val = RTT->RTT_VR;
	}
	return rtt_val;
}

/**
 * \brief Enable RTT alarm interrupt.
 *
 */
void rtt_enable_alarm_it(void)
{
	RTT->RTT_MR |= RTT_MR_ALMIEN;
}

/**
 * \brief Disable RTT alarm interrupt.
 *
 */
void rtt_disable_alarm_it(void)
{
	RTT->RTT_MR &= ~RTT_MR_ALMIEN;
}

/**
 * \brief Enable RTT real-time interrupt.
 *
 */
void rtt_enable_timer_it(void)
{
	RTT->RTT_MR |= RTT_MR_RTTINCIEN;
}

/**
 * \brief Disable RTT real-time interrupt.
 *
 */
void rtt_disable_timer_it(void)
{
	RTT->RTT_MR &= ~RTT_MR_RTTINCIEN;
}

/**
 * \brief Configure the RTT to generate an alarm at the given time.
 * alarm happens when CRTV value equals ALMV+1, so RTT_AR should be alarmtime - 1.
 * if you want to get alarm when rtt hit 0 , ALMV should be set to 0xFFFFFFFF.
 *
 * \param alarm_time Alarm time,Alarm time = ALMV + 1.
 *
 */
void rtt_set_time_alarm(uint32_t alarm_time)
{
	uint32_t flag;

	flag = RTT->RTT_MR & RTT_MR_ALMIEN;

	/* The alarm interrupt must be disabled (ALMIEN must be cleared in RTT_MR) when writing a new ALMV value. */
	rtt_disable_alarm_it();

	/**
	 * Alarm time = ALMV + 1,If the incoming parameter 
	 * is 0, the ALMV is set to 0xFFFFFFFF.
	*/
	if(alarm_time == 0) {
		RTT->RTT_AR = 0xFFFFFFFF;
	}
	else {
		RTT->RTT_AR = alarm_time - 1;
	}

	if (flag) {
		rtt_enable_alarm_it();
	}
}
