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

/** \addtogroup rtc_module Working with RTC
 * \section Purpose
 * The RTC driver provides the interface to configure and use the RTC
 * peripheral.
 *
 * It manages date, time, and alarms.\n
 * This timer is clocked by the 32kHz system clock, and is not impacted by
 * power management settings (PMC). To be accurate, it is better to use an
 * external 32kHz crystal instead of the internal 32kHz RC.\n
 *
 * It uses BCD format, and time can be set in AM/PM or 24h mode through a
 * configuration bit in the mode register.\n
 *
 * To update date or time, the user has to follow these few steps :
 * <ul>
 * <li>Set UPDTIM and/or UPDCAL bit(s) in RTC_CR,</li>
 * <li>Polling or IRQ on the ACKUPD bit of RTC_CR,</li>
 * <li>Clear ACKUPD bit in RTC_SCCR,</li>
 * <li>Update Time and/or Calendar values in RTC_TIMR/RTC_CALR (BCD format),</li>
 * <li>Clear UPDTIM and/or UPDCAL bit in RTC_CR.</li>
 * </ul>
 * An alarm can be set to happen on month, date, hours, minutes or seconds,
 * by setting the proper "Enable" bit of each of these fields in the Time and
 * Calendar registers.
 * This allows a large number of configurations to be available for the user.
 * Alarm occurence can be detected even by polling or interrupt.
 *
 * A check of the validity of the date and time format and values written by the user is automatically done.
 * Errors are reported through the Valid Entry Register.
 *
 * \section Usage
 * <ul>
 * <li>  Enable & disable RTC interrupt using RTC_EnableIt() and RTC_DisableIt().
 * <li>  Set RTC data, time, alarm using rtc_set_date(), RTC_SetTime(),
 * rtc_set_time_alarm() and rtc_set_date_alarm().
 * <li>  Get RTC data, time using rtc_get_date() and rtc_get_time().
 * </li>
 * </ul>
 *
 * For more accurate information, please look at the RTC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref rtc.c\n
 * \ref rtc.h.\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Real Time Clock (RTC) controller.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

//#include "chip.h"
#include "time/rtc.h"

#include "utils/trace.h"

#include <stdint.h>
#include <assert.h>

/* The BCD code shift value */
#define BCD_SHIFT      4

/* The BCD code mask value */
#define BCD_MASK       0xfu

/* The BCD mul/div factor value */
#define BCD_FACTOR     10

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

static uint8_t _flag_alarm;
static uint8_t _flag_hms;
static uint8_t _flag_minute_change;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Sets the RTC in either 12 or 24 hour mode.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param dwMode  Hour mode.
 */
extern void rtc_set_hour_mode(Rtc * pRtc, uint32_t mode)
{
	assert((mode & 0xFFFFFFFE) == 0);
	pRtc->RTC_MR = mode;
}

/**
 * \brief Gets the RTC mode.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \return Hour mode.
 */
extern uint32_t rtc_get_hour_mode(Rtc * pRtc)
{
	uint32_t mode;
	TRACE_DEBUG("rtc_get_hour_mode()\n\r");
	mode = pRtc->RTC_MR;
	mode &= 0xFFFFFFFE;
	return mode;
}

/**
 * \brief Enables the selected interrupt sources of the RTC.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param dwSources  Interrupt sources to enable.
 */
extern void rtc_enable_it(Rtc * pRtc, uint32_t sources)
{
	assert((sources & (uint32_t) (~0x1F)) == 0);
	TRACE_DEBUG("rtc_enable_it()\n\r");
	pRtc->RTC_IER = sources;
}

/**
* \brief Disables the selected interrupt sources of the RTC.
*
 * \param pRtc  Pointer to a Rtc instance
* \param dwSources  Interrupt sources to disable.
*/
extern void rtc_disable_it(Rtc * pRtc, uint32_t sources)
{
	assert((sources & (uint32_t) (~0x1F)) == 0);
	TRACE_DEBUG("rtc_disable_it()\n\r");
	pRtc->RTC_IDR = sources;
}

/**
 * \brief Sets the current time in the RTC.
 *
 * \note In successive update operations, the user must wait at least one second
 * after resetting the UPDTIM/UPDCAL bit in the RTC_CR before setting these
 * bits again. Please look at the RTC section of the datasheet for detail.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pTime Pointer to structure time
 *
 * \return 0 sucess, 1 fail to set
 */
extern int rtc_set_time(Rtc * pRtc, struct _time *pTime)
{
	uint32_t ltime = 0;
	uint8_t hour_bcd , min_bcd, sec_bcd;

	TRACE_DEBUG("rtc_set_time(%02d:%02d:%02d)\n\r", pTime->hour, pTime->min, pTime->sec);

	/* if 12-hour mode, set AMPM bit */
	if ((pRtc->RTC_MR & RTC_MR_HRMOD) == RTC_MR_HRMOD) {
		if (pTime->hour > 12) {
			pTime->hour -= 12;
			ltime |= RTC_TIMR_AMPM;
		}
	}
	hour_bcd = (pTime->hour % 10) | ((pTime->hour / 10) << 4);
	min_bcd = (pTime->min % 10) | ((pTime->min / 10) << 4);
	sec_bcd = (pTime->sec % 10) | ((pTime->sec / 10) << 4);
	/* value overflow */
	if ((hour_bcd & (uint8_t) (~RTC_HOUR_BIT_LEN_MASK)) |
	    (min_bcd & (uint8_t) (~RTC_MIN_BIT_LEN_MASK)) |
	    (sec_bcd & (uint8_t) (~RTC_SEC_BIT_LEN_MASK))) {
		return 1;
	}
	ltime = sec_bcd | (min_bcd << 8) | (hour_bcd << 16);
	pRtc->RTC_CR |= RTC_CR_UPDTIM;
	while ((pRtc->RTC_SR & RTC_SR_ACKUPD) != RTC_SR_ACKUPD) ;
	pRtc->RTC_SCCR = RTC_SCCR_ACKCLR;
	pRtc->RTC_TIMR = ltime;
	pRtc->RTC_CR &= (uint32_t) (~RTC_CR_UPDTIM);
	pRtc->RTC_SCCR |= RTC_SCCR_SECCLR;
	return (int) (pRtc->RTC_VER & RTC_VER_NVTIM);
}

/**
 * \brief Retrieves the current time as stored in the RTC in several variables.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pTime Pointer to structure time
 */
extern void rtc_get_time(Rtc * pRtc, struct _time *pTime)
{
	uint32_t ltime;

	TRACE_DEBUG("rtc_get_time()\n\r");
	/* Get current RTC time */
	ltime = pRtc->RTC_TIMR;
	while (ltime != pRtc->RTC_TIMR) {
		ltime = pRtc->RTC_TIMR;
	}
	/* Hour */
	if (pTime->hour) {
		pTime->hour = ((ltime & 0x00300000) >> 20) * 10 + ((ltime & 0x000F0000) >> 16);
		if ((ltime & RTC_TIMR_AMPM) == RTC_TIMR_AMPM) {
			pTime->hour += 12;
		}
	}
	/* Minute */
	if (pTime->min) {
		pTime->min = ((ltime & 0x00007000) >> 12) * 10 + ((ltime & 0x00000F00) >> 8);
	}
	/* Second */
	if (pTime->sec) {
		pTime->sec = ((ltime & 0x00000070) >> 4) * 10 + (ltime & 0x0000000F);
	}
}

/**
 * \brief Sets a time alarm on the RTC.
 * The match is performed only on the provided variables;
 * Setting all pointers to 0 disables the time alarm.
 *
 * \note In AM/PM mode, the hour value must have bit #7 set for PM, cleared for
 * AM (as expected in the time registers).
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pTime Pointer to structure time.
 *
 * \return 0 success, 1 fail to set
 */
extern int rtc_set_time_alarm(Rtc * pRtc, struct _time *pTime)
{
	uint32_t alarm = 0;

	TRACE_DEBUG("rtc_set_time_alarm()\n\r");

	/* Hour */
	if (pTime->hour) {
		alarm |= RTC_TIMALR_HOUREN | ((pTime->hour / 10) << 20) | ((pTime->hour % 10) << 16);
	}
	/* Minute */
	if (pTime->min) {
		alarm |= RTC_TIMALR_MINEN | ((pTime->min / 10) << 12) | ((pTime->min % 10) << 8);
	}
	/* Second */
	if (pTime->sec) {
		alarm |= RTC_TIMALR_SECEN | ((pTime->sec / 10) << 4) | (pTime->sec % 10);
	}
	pRtc->RTC_TIMALR = alarm;
	return (int) (pRtc->RTC_VER & RTC_VER_NVTIMALR);
}

/**
 * \brief Retrieves the current year, month and day from the RTC.
 * Month, day and week values are numbered starting at 1.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pDate	Pointer to structure Date.
 */
extern void rtc_get_date(Rtc * pRtc, struct _date *pDate)
{
	uint32_t date;

	/* Get current date (multiple reads are necessary to insure a stable value) */
	do {
		date = pRtc->RTC_CALR;
	} while (date != pRtc->RTC_CALR);
	/* Retrieve year */
	if (pDate->year) {
		pDate->year = (((date >> 4) & 0x7) * 1000) + ((date & 0xF) * 100)
			+ (((date >> 12) & 0xF) * 10) + ((date >> 8) & 0xF);
	}
	/* Retrieve month */
	if (pDate->month) {
		pDate->month = (((date >> 20) & 1) * 10) + ((date >> 16) & 0xF);
	}
	/* Retrieve day */
	if (pDate->day) {
		pDate->day = (((date >> 28) & 0x3) * 10) + ((date >> 24) & 0xF);
	}
	/* Retrieve week */
	if (pDate->week) {
		pDate->week = ((date >> 21) & 0x7);
	}
}

/**
 * \brief Sets the current year, month and day in the RTC.
 * Month, day and week values must be numbered starting from 1.
 *
 * \note In successive update operations, the user must wait at least one second
 * after resetting the UPDTIM/UPDCAL bit in the RTC_CR before setting these
 * bits again. Please look at the RTC section of the datasheet for detail.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pDate	Pointer to structure Date
 *
 * \return 0 success, 1 fail to set
 */
extern int rtc_set_date(Rtc * pRtc, struct _date *pDate)
{
	uint32_t ldate;
	uint8_t cent_bcd, year_bcd, month_bcd, day_bcd, week_bcd;

	cent_bcd = ((pDate->year / 100) % 10) | ((pDate->year / 1000) << 4);
	year_bcd = (pDate->year % 10) | (((pDate->year / 10) % 10) << 4);
	month_bcd = ((pDate->month % 10) | (pDate->month / 10) << 4);
	day_bcd = ((pDate->day % 10) | (pDate->day / 10) << 4);
	week_bcd = ((pDate->week % 10) | (pDate->week / 10) << 4);
	/* value over flow */
	if ((cent_bcd & (uint8_t) (~RTC_CENT_BIT_LEN_MASK)) |
	    (year_bcd & (uint8_t) (~RTC_YEAR_BIT_LEN_MASK)) |
	    (month_bcd & (uint8_t) (~RTC_MONTH_BIT_LEN_MASK)) |
	    (week_bcd & (uint8_t) (~RTC_WEEK_BIT_LEN_MASK)) |
	    (day_bcd & (uint8_t) (~RTC_DATE_BIT_LEN_MASK))
	    ) {
		return 1;
	}
	/* Convert values to date register value */
	ldate = cent_bcd | (year_bcd << 8) | (month_bcd << 16) | (week_bcd << 21) | (day_bcd << 24);
	/* Update calendar register  */
	pRtc->RTC_CR |= RTC_CR_UPDCAL;
	while ((pRtc->RTC_SR & RTC_SR_ACKUPD) != RTC_SR_ACKUPD) ;
	pRtc->RTC_SCCR = RTC_SCCR_ACKCLR;
	pRtc->RTC_CALR = ldate;
	pRtc->RTC_CR &= (uint32_t) (~RTC_CR_UPDCAL);
	pRtc->RTC_SCCR |= RTC_SCCR_SECCLR;	/* clear SECENV in SCCR */
	return (int) (pRtc->RTC_VER & RTC_VER_NVCAL);
}

/**
 * \brief Sets a date alarm in the RTC.
 * The alarm will match only the provided values;
 * Passing a null-pointer disables the corresponding field match.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param pucMonth If not null, the RTC alarm will month-match this value.
 * \param pucDay   If not null, the RTC alarm will day-match this value.
 *
 * \return 0 success, 1 fail to set
 */
extern int rtc_set_date_alarm(Rtc * pRtc, struct _date *pDate)
{
	uint32_t alarm;

	alarm = ((pDate->month) || (pDate->day)) ? (0) : (0x01010000);
	TRACE_DEBUG("rtc_set_date_alarm()\n\r");
	/* Compute alarm field value */
	if (pDate->month) {
		alarm |= RTC_CALALR_MTHEN | ((pDate->month / 10) << 20) | ((pDate->month % 10) << 16);
	}
	if (pDate->day) {
		alarm |= RTC_CALALR_DATEEN | ((pDate->day / 10) << 28) | ((pDate->day % 10) << 24);
	}
	/* Set alarm */
	pRtc->RTC_CALALR = alarm;
	return (int) (pRtc->RTC_VER & RTC_VER_NVCALALR);
}

/**
 * \brief Clear flag bits of status clear command register in the RTC.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param dwMask Bits mask of cleared events
 */
extern void rtc_clear_sccr(Rtc * pRtc, uint32_t mask)
{
	/* Clear all flag bits in status clear command register */
	mask &= RTC_SCCR_ACKCLR | RTC_SCCR_ALRCLR | RTC_SCCR_SECCLR |
		RTC_SCCR_TIMCLR | RTC_SCCR_CALCLR;
	pRtc->RTC_SCCR = mask;
}

/**
 * \brief Get flag bits of status register in the RTC.
 *
 * \param pRtc  Pointer to a Rtc instance
 * \param dwMask Bits mask of Status Register
 *
 * \return Status register & mask
 */
extern uint32_t rtc_get_sr(Rtc * pRtc, uint32_t mask)
{
	return ((pRtc->RTC_SR) & mask);
}

/**
 * \brief Get the RTC tamper time value.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper time will be cleared.
 *
 * \param pRtc       Pointer to an RTC instance.
 * \param pTime    	 Pointer to structure Time.
 * \param reg_num    Tamper register set number.
 */
extern void rtc_get_tamper_time(Rtc * pRtc, struct _time *pTime,  uint8_t reg_num)
{
	uint32_t ltime, temp;

	TRACE_DEBUG("rtc_get_tamper_time()\n\r");

	/* Get current RTC time */
	ltime = pRtc->RTC_TS[reg_num].RTC_TSTR;
	while (ltime != pRtc->RTC_TS[reg_num].RTC_TSTR) {
		ltime = pRtc->RTC_TS[reg_num].RTC_TSTR;
	}
	/* Hour */
	if (pTime->hour) {
		temp = (ltime & RTC_TSTR_HOUR_Msk) >> RTC_TSTR_HOUR_Pos;
		pTime->hour = (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
		if ((ltime & RTC_TSTR_AMPM) == RTC_TSTR_AMPM) {
			pTime->hour += 12;
		}
	}
	/* Minute */
	if (pTime->min) {
		temp = (ltime & RTC_TSTR_MIN_Msk) >> RTC_TSTR_MIN_Pos;
		pTime->min = (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
	}
	/* Second */
	if (pTime->sec) {
		temp = (ltime & RTC_TSTR_SEC_Msk) >> RTC_TSTR_SEC_Pos;
		pTime->sec = temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
	}
}

/**
 * \brief Get the RTC tamper date.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper date will be cleared.
 *
 * \param pRtc      Pointer to an RTC instance.
 * \param pDate     Pointer to structure Date
 * \param reg_num   Tamper register set number.
 */
extern void rtc_get_tamper_date(Rtc * pRtc, struct _date *pDate, uint8_t reg_num)
{
	uint32_t date, cent, temp;

	/* Get the current date (multiple reads are to insure a stable value). */
	date = pRtc->RTC_TS[reg_num].RTC_TSDR;
	while (date != pRtc->RTC_TS[reg_num].RTC_TSDR) {
		date = pRtc->RTC_TS[reg_num].RTC_TSDR;
	}
	/* Retrieve year */
	if (pDate->year) {
		temp = (date & RTC_TSDR_CENT_Msk) >> RTC_TSDR_CENT_Pos;
		cent = (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
		temp = (date & RTC_TSDR_YEAR_Msk) >> RTC_TSDR_YEAR_Pos;
		pDate->year = (cent * BCD_FACTOR * BCD_FACTOR) + (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
	}
	/* Retrieve month */
	if (pDate->month) {
		temp = (date & RTC_TSDR_MONTH_Msk) >> RTC_TSDR_MONTH_Pos;
		pDate->month = (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
	}
	/* Retrieve day */
	if (pDate->day) {
		temp = (date & RTC_TSDR_DATE_Msk) >> RTC_TSDR_DATE_Pos;
		pDate->day = (temp >> BCD_SHIFT) * BCD_FACTOR + (temp & BCD_MASK);
	}
	/* Retrieve week */
	if (pDate->week) {
		pDate->week= ((date & RTC_TSDR_DAY_Msk) >> RTC_TSDR_DAY_Pos);
	}
}

/**
 * \brief Get the RTC tamper source.
 *
 * \param pRtc      Pointer to an RTC instance.
 * \param ucRegNum  Current tamper register set number.
 *
 * \return Tamper source.
 */
extern uint32_t rtc_get_tamper_source(Rtc * pRtc, uint8_t reg_num)
{
	return pRtc->RTC_TS[reg_num].RTC_TSSR;
}

/**
 * \brief Get the RTC tamper event counter.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the tamper event counter will be cleared.
 *
 * \param pRtc Pointer to an RTC instance.
 *
 * \return Tamper event counter
 */
extern uint32_t rtc_get_tamper_event_counter(Rtc * pRtc)
{
	return (pRtc->RTC_TS[0].RTC_TSTR & RTC_TSTR_TEVCNT_Msk) >> RTC_TSTR_TEVCNT_Pos;
}

/**
 * \brief Check the system is in backup mode when RTC tamper event happen.
 *
 * \note This function should be called before rtc_get_tamper_source()
 *       function call, Otherwise the flag indicates tamper occur in backup
 *       mode will be cleared.
 *
 * \param pRtc      Pointer to an RTC instance.
 * \param ucRegNum  Current tamper register set number.
 *
 * \return 1 - The system is in backup mode when the tamper event occurs.
 *         0 - The system is different from backup mode.
 */
extern uint8_t rtc_is_tamper_occur_in_backup_mode(Rtc * pRtc, uint8_t reg_num)
{
	if (pRtc->RTC_TS[reg_num].RTC_TSTR & RTC_TSTR_BACKUP) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * \brief Convert number of second (count) to HMS format.
 *
 */
void rtc_convert_time_to_hms (struct _time *pTime, uint32_t count)
{
  uint32_t temps = count;
  pTime->hour = pTime->min = pTime->sec= 0;
  temps = temps%86400;
  pTime->hour = temps/3600 ;
  temps -= pTime->hour*3600 ;
  pTime->min = temps/60;
  pTime->sec = temps%60;
}
