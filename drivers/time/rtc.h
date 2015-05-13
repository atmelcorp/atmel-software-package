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

#ifndef _RTC_
#define _RTC_

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

/* The BCD code shift value */
#define BCD_SHIFT      4

/* The BCD code mask value */
#define BCD_MASK       0xfu

/* The BCD mul/div factor value */
#define BCD_FACTOR     10


struct _time
{
  uint8_t   hour;
  uint8_t   min;
  uint8_t   sec;
} ;

struct _date
{
  unsigned short year;
  uint8_t month;
  uint8_t day;
  uint8_t week;
} ;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

void rtc_set_hour_mode(Rtc * pRtc, uint32_t mode);
extern uint32_t rtc_get_hour_mode(Rtc * pRtc);
void rtc_enable_it(Rtc * pRtc, uint32_t sources);
void rtc_disable_it(Rtc * pRtc, uint32_t sources);
extern int rtc_set_time(Rtc * pRtc, struct _time *pTime);
void rtc_get_time(Rtc * pRtc, struct _time *pTime);
extern int rtc_set_time_alarm(Rtc * pRtc, struct _time *pTime);
void rtc_get_date(Rtc * pRtc, struct _date *pDate);
extern int rtc_set_date(Rtc * pRtc, struct _date *pDate);
extern int rtc_set_date_alarm(Rtc * pRtc, struct _date *pDate);
void rtc_clear_sccr(Rtc * pRtc, uint32_t mask);
extern uint32_t rtc_get_sr(Rtc * pRtc, uint32_t mask);
void rtc_get_tamper_time(Rtc * pRtc, struct _time *pTime,  uint8_t reg_num);
void rtc_get_tamper_date(Rtc * pRtc, struct _date *pDate, uint8_t reg_num);
extern uint32_t rtc_get_tamper_source(Rtc * pRtc, uint8_t reg_num);
extern uint32_t rtc_get_tamper_event_counter(Rtc * pRtc);
extern uint8_t rtc_is_tamper_occur_in_backup_mode(Rtc * pRtc, uint8_t reg_num);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef _RTC_ */
