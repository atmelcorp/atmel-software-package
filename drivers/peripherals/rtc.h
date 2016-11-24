/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
 * Interface for Real Time Clock (RTC) controller.
 *
 */

#ifndef _RTC_H_
#define _RTC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define RTC_HOUR_BIT_LEN_MASK   0x3F
#define RTC_MIN_BIT_LEN_MASK    0x7F
#define RTC_SEC_BIT_LEN_MASK    0x7F
#define RTC_CENT_BIT_LEN_MASK   0x7F
#define RTC_YEAR_BIT_LEN_MASK   0xFF
#define RTC_MONTH_BIT_LEN_MASK  0x1F
#define RTC_DATE_BIT_LEN_MASK   0x3F
#define RTC_WEEK_BIT_LEN_MASK   0x07

enum _rtc_mode {
	RTC_MODE_GREGORIAN = 0,
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
	RTC_MODE_PERSIAN,
#endif
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	RTC_MODE_UTC,
#endif
};

struct _time {
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
};

struct _date {
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  week;
};

enum _rtc_hour_mode {
	RTC_HOUR_MODE_24 = 0,
	RTC_HOUR_MODE_12,
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Sets the RTC time mode.
 *
 * \param mode  RTC mode.
 */
extern void rtc_set_mode(enum _rtc_mode mode);

/**
 * \brief Gets the RTC time mode.
 *
 * \return RTC mode.
 */
extern enum _rtc_mode rtc_get_mode(void);

/**
 * \brief Sets the RTC in either 12 or 24 hour mode.
 *
 * \param mode  Hour mode.
 */
extern void rtc_set_hour_mode(enum _rtc_hour_mode mode);

/**
 * \brief Gets the RTC mode.
 *
 * \return Hour mode.
 */
extern enum _rtc_hour_mode rtc_get_hour_mode(void);

/**
 * \brief Enables the selected interrupt sources of the RTC.
 *
 * \param sources  Interrupt sources to enable.
 */
extern void rtc_enable_it(uint32_t sources);

/**
* \brief Disables the selected interrupt sources of the RTC.
*
* \param sources  Interrupt sources to disable.
*/
extern void rtc_disable_it(uint32_t sources);

/**
 * \brief Sets the current time in the RTC.
 *
 * \note In successive update operations, the user must wait at least one second
 * after resetting the UPDTIM/UPDCAL bit in the RTC_CR before setting these
 * bits again. Please look at the RTC section of the datasheet for detail.
 *
 * \param time Pointer to structure time
 *
 * \return 0 sucess, 1 fail to set
 */
extern uint32_t rtc_set_time(struct _time *time);

/**
 * \brief Retrieves the current time as stored in the RTC in several variables.
 *
 * \param time Pointer to structure time
 */
extern void rtc_get_time(struct _time *time);

/**
 * \brief Sets a time alarm on the RTC.
 * The match is performed only on the provided variables;
 * Setting all pointers to 0 disables the time alarm.
 *
 * \note In AM/PM mode, the hour value must have bit #7 set for PM, cleared for
 * AM (as expected in the time registers).
 *
 * \param time Pointer to structure time.
 *
 * \return 0 success, 1 fail to set
 */
extern uint32_t rtc_set_time_alarm(struct _time *time);

/**
 * \brief Retrieves the current year, month and day from the RTC.
 * Month, day and week values are numbered starting at 1.
 *
 * \param date	Pointer to structure Date.
 */
extern void rtc_get_date(struct _date *date);

/**
 * \brief Sets the current year, month and day in the RTC.
 * Month, day and week values must be numbered starting from 1.
 *
 * \note In successive update operations, the user must wait at least one second
 * after resetting the UPDTIM/UPDCAL bit in the RTC_CR before setting these
 * bits again. Please look at the RTC section of the datasheet for detail.
 *
 * \param date	Pointer to structure Date
 *
 * \return 0 success, 1 fail to set
 */
extern uint32_t rtc_set_date(struct _date *date);

/**
 * \brief Sets a date alarm in the RTC.
 * The alarm will match only the provided values;
 * Passing a null-pointer disables the corresponding field match.
 *
 * \param pucMonth If not null, the RTC alarm will month-match this value.
 * \param pucDay   If not null, the RTC alarm will day-match this value.
 *
 * \return 0 success, 1 fail to set
 */
extern uint32_t rtc_set_date_alarm(struct _date *date);

/**
 * \brief Clear flag bits of status clear command register in the RTC.
 *
 * \param mask Bits mask of cleared events
 */
extern void rtc_clear_sccr(uint32_t mask);

/**
 * \brief Get flag bits of status register in the RTC.
 *
 * \param mask Bits mask of Status Register
 *
 * \return Status register & mask
 */
extern uint32_t rtc_get_sr(uint32_t mask);

#ifdef CONFIG_HAVE_RTC_TAMPER

/**
 * \brief Get the RTC tamper time value.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper time will be cleared.
 *
 * \param time Pointer to structure Time.
 * \param reg_num    Tamper register set number.
 */
extern void rtc_get_tamper_time(struct _time *time, uint8_t reg_num);

/**
 * \brief Get the RTC tamper date.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper date will be cleared.
 *
 * \param date     Pointer to structure Date
 * \param reg_num   Tamper register set number.
 */
extern void rtc_get_tamper_date(struct _date *date, uint8_t reg_num);

/**
 * \brief Get the RTC tamper source.
 *
 * \param reg_num  Current tamper register set number.
 *
 * \return Tamper source.
 */
extern uint32_t rtc_get_tamper_source(uint8_t reg_num);

/**
 * \brief Get the RTC tamper event counter.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper event counter will be cleared.
 *
 * \return Tamper event counter
 */
extern uint32_t rtc_get_tamper_event_counter(void);

/**
 * \brief Check the system is in backup mode when RTC tamper event happen.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the flag indicates tamper occur in backup
 *       mode will be cleared.
 *
 * \param reg_num  Current tamper register set number.
 *
 * \return 1 - The system is in backup mode when the tamper event occurs.
 *         0 - The system is different from backup mode.
 */
extern uint8_t rtc_is_tamper_occur_in_backup_mode(uint8_t reg_num);

#endif /* CONFIG_HAVE_RTC_TAMPER */

/**
 * \brief Convert number of second (count) to HMS format.
 *
 */
extern void rtc_convert_time_to_hms (struct _time *time, uint32_t count);

#ifdef CONFIG_HAVE_RTC_CALIBRATION

/**
 * \brief RTC calibration for Temperature or PPM drift
 */
extern void rtc_calibration(int32_t current_tempr);

#endif /* CONFIG_HAVE_RTC_CALIBRATION */

/**
 * \brief Set calendar event selection.
 *
 * \param mask Bits CALEVSEL of Control Register
 * \return Status register & mask
 */
extern uint32_t rtc_set_calendar_event (uint32_t mask);

/**
 * \brief Set time event selection.
 *
 * \param mask Bits TIMEVSEL of Control Register
 * \return Status register & mask
 */
extern uint32_t rtc_set_time_event (uint32_t maskask);

#ifdef CONFIG_HAVE_RTC_MODE_UTC

/**
 * \brief Retrieves the current utc time as stored in the RTC in several variables.
 *
 * \param utc_time Pointer to time
 */
extern void rtc_get_utc_time(uint32_t* utc_time);

/**
 * \brief Sets the current utc format time in the RTC.
 *
 * \note In successive update operations, the user must wait at least one second
 * after resetting the UPDTIM/UPDCAL bit in the RTC_CR before setting these
 * bits again. Please look at the RTC section of the datasheet for detail.
 *
 * \param utc_time utc time value to set
 *
 * \return 0 sucess, 1 fail to set
 */
extern uint32_t rtc_set_utc_time(uint32_t utc_time);

/**
 * \brief Sets a time alarm on the RTC.
 * The match is performed only on the provided variables;
 * Setting value to 0 disables the time alarm.
 *
 *
 * \param time Pointer to structure time.
 *
 * \return 0 success, 1 fail to set
 */
extern uint32_t rtc_set_utc_time_alarm(uint32_t utc_time);

#endif /* CONFIG_HAVE_RTC_MODE_UTC */

#endif /* _RTC_H_ */
