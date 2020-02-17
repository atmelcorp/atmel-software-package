/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_RTC_COMPONENT_
#define _SAM9X_RTC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Real-time Clock */
/* ============================================================================= */
/** \addtogroup SAM9X_RTC Real-time Clock */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief RtcTs hardware registers */
typedef struct {
  __I uint32_t RTC_TSTR; /**< \brief (RtcTs Offset: 0x0) TimeStamp Time Register 0 */
  __I uint32_t RTC_TSDR; /**< \brief (RtcTs Offset: 0x4) TimeStamp Date Register 0 */
  __I uint32_t RTC_TSSR; /**< \brief (RtcTs Offset: 0x8) TimeStamp Source Register 0 */
} RtcTs;
/** \brief Rtc hardware registers */
#define RTCTS_NUMBER 2
typedef struct {
  __IO uint32_t RTC_CR;        /**< \brief (Rtc Offset: 0x0) Control Register */
  __IO uint32_t RTC_MR;        /**< \brief (Rtc Offset: 0x4) Mode Register */
  __IO uint32_t RTC_TIMR;      /**< \brief (Rtc Offset: 0x8) Time Register */
  __IO uint32_t RTC_CALR;      /**< \brief (Rtc Offset: 0xC) Calendar Register */
  __IO uint32_t RTC_TIMALR;    /**< \brief (Rtc Offset: 0x10) Time Alarm Register */
  __IO uint32_t RTC_CALALR;    /**< \brief (Rtc Offset: 0x14) Calendar Alarm Register */
  __I  uint32_t RTC_SR;        /**< \brief (Rtc Offset: 0x18) Status Register */
  __O  uint32_t RTC_SCCR;      /**< \brief (Rtc Offset: 0x1C) Status Clear Command Register */
  __O  uint32_t RTC_IER;       /**< \brief (Rtc Offset: 0x20) Interrupt Enable Register */
  __O  uint32_t RTC_IDR;       /**< \brief (Rtc Offset: 0x24) Interrupt Disable Register */
  __I  uint32_t RTC_IMR;       /**< \brief (Rtc Offset: 0x28) Interrupt Mask Register */
  __I  uint32_t RTC_VER;       /**< \brief (Rtc Offset: 0x2C) Valid Entry Register */
  __I  uint32_t Reserved1[10];
  __IO uint32_t RTC_TMR;       /**< \brief (Rtc Offset: 0x58) Tamper Mode register */
  __IO uint32_t RTC_TDPR;      /**< \brief (Rtc Offset: 0x5C) Tamper Debounce Period register */
  __I  uint32_t Reserved2[20];
       RtcTs    RTC_TS[RTCTS_NUMBER]; /**< \brief (Rtc Offset: 0xB0) 0 .. 1 */
} Rtc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- RTC_CR : (RTC Offset: 0x0) Control Register -------- */
#define RTC_CR_UPDTIM (0x1u << 0) /**< \brief (RTC_CR) Update Request Time Register */
#define RTC_CR_UPDCAL (0x1u << 1) /**< \brief (RTC_CR) Update Request Calendar Register */
#define RTC_CR_TIMEVSEL_Pos 8
#define RTC_CR_TIMEVSEL_Msk (0x3u << RTC_CR_TIMEVSEL_Pos) /**< \brief (RTC_CR) Time Event Selection */
#define RTC_CR_TIMEVSEL(value) ((RTC_CR_TIMEVSEL_Msk & ((value) << RTC_CR_TIMEVSEL_Pos)))
#define   RTC_CR_TIMEVSEL_MINUTE (0x0u << 8) /**< \brief (RTC_CR) Minute change */
#define   RTC_CR_TIMEVSEL_HOUR (0x1u << 8) /**< \brief (RTC_CR) Hour change */
#define   RTC_CR_TIMEVSEL_MIDNIGHT (0x2u << 8) /**< \brief (RTC_CR) Every day at midnight */
#define   RTC_CR_TIMEVSEL_NOON (0x3u << 8) /**< \brief (RTC_CR) Every day at noon */
#define RTC_CR_CALEVSEL_Pos 16
#define RTC_CR_CALEVSEL_Msk (0x3u << RTC_CR_CALEVSEL_Pos) /**< \brief (RTC_CR) Calendar Event Selection */
#define RTC_CR_CALEVSEL(value) ((RTC_CR_CALEVSEL_Msk & ((value) << RTC_CR_CALEVSEL_Pos)))
#define   RTC_CR_CALEVSEL_WEEK (0x0u << 16) /**< \brief (RTC_CR) Week change (every Monday at time 00:00:00) */
#define   RTC_CR_CALEVSEL_MONTH (0x1u << 16) /**< \brief (RTC_CR) Month change (every 01 of each month at time 00:00:00) */
#define   RTC_CR_CALEVSEL_YEAR (0x2u << 16) /**< \brief (RTC_CR) Year change (every January 1 at time 00:00:00) */
/* -------- RTC_MR : (RTC Offset: 0x4) Mode Register -------- */
#define RTC_MR_HRMOD (0x1u << 0) /**< \brief (RTC_MR) 12-/24-hour Mode */
#define RTC_MR_PERSIAN (0x1u << 1) /**< \brief (RTC_MR) PERSIAN Calendar */
#define RTC_MR_UTC (0x1u << 2) /**< \brief (RTC_MR) UTC Time Format */
#define RTC_MR_NEGPPM (0x1u << 4) /**< \brief (RTC_MR) NEGative PPM Correction */
#define RTC_MR_CORRECTION_Pos 8
#define RTC_MR_CORRECTION_Msk (0x7fu << RTC_MR_CORRECTION_Pos) /**< \brief (RTC_MR) Slow Clock Correction */
#define RTC_MR_CORRECTION(value) ((RTC_MR_CORRECTION_Msk & ((value) << RTC_MR_CORRECTION_Pos)))
#define RTC_MR_HIGHPPM (0x1u << 15) /**< \brief (RTC_MR) HIGH PPM Correction */
#define RTC_MR_OUT0_Pos 16
#define RTC_MR_OUT0_Msk (0x7u << RTC_MR_OUT0_Pos) /**< \brief (RTC_MR) All ADC Channel Trigger Event Source Selection */
#define RTC_MR_OUT0(value) ((RTC_MR_OUT0_Msk & ((value) << RTC_MR_OUT0_Pos)))
#define   RTC_MR_OUT0_NO_WAVE (0x0u << 16) /**< \brief (RTC_MR) No waveform, stuck at '0' */
#define   RTC_MR_OUT0_FREQ1HZ (0x1u << 16) /**< \brief (RTC_MR) 1 Hz square wave */
#define   RTC_MR_OUT0_FREQ32HZ (0x2u << 16) /**< \brief (RTC_MR) 32 Hz square wave */
#define   RTC_MR_OUT0_FREQ64HZ (0x3u << 16) /**< \brief (RTC_MR) 64 Hz square wave */
#define   RTC_MR_OUT0_FREQ512HZ (0x4u << 16) /**< \brief (RTC_MR) 512 Hz square wave */
#define   RTC_MR_OUT0_ALARM_TOGGLE (0x5u << 16) /**< \brief (RTC_MR) Output toggles when alarm flag rises */
#define   RTC_MR_OUT0_ALARM_FLAG (0x6u << 16) /**< \brief (RTC_MR) Output is a copy of the alarm flag */
#define   RTC_MR_OUT0_PROG_PULSE (0x7u << 16) /**< \brief (RTC_MR) Duty cycle programmable pulse */
#define RTC_MR_OUT1_Pos 20
#define RTC_MR_OUT1_Msk (0x7u << RTC_MR_OUT1_Pos) /**< \brief (RTC_MR) ADC Last Channel Trigger Event Source Selection */
#define RTC_MR_OUT1(value) ((RTC_MR_OUT1_Msk & ((value) << RTC_MR_OUT1_Pos)))
#define   RTC_MR_OUT1_NO_WAVE (0x0u << 20) /**< \brief (RTC_MR) No waveform, stuck at '0' */
#define   RTC_MR_OUT1_FREQ1HZ (0x1u << 20) /**< \brief (RTC_MR) 1 Hz square wave */
#define   RTC_MR_OUT1_FREQ32HZ (0x2u << 20) /**< \brief (RTC_MR) 32 Hz square wave */
#define   RTC_MR_OUT1_FREQ64HZ (0x3u << 20) /**< \brief (RTC_MR) 64 Hz square wave */
#define   RTC_MR_OUT1_FREQ512HZ (0x4u << 20) /**< \brief (RTC_MR) 512 Hz square wave */
#define   RTC_MR_OUT1_ALARM_TOGGLE (0x5u << 20) /**< \brief (RTC_MR) Output toggles when alarm flag rises */
#define   RTC_MR_OUT1_ALARM_FLAG (0x6u << 20) /**< \brief (RTC_MR) Output is a copy of the alarm flag */
#define   RTC_MR_OUT1_PROG_PULSE (0x7u << 20) /**< \brief (RTC_MR) Duty cycle programmable pulse */
#define RTC_MR_THIGH_Pos 24
#define RTC_MR_THIGH_Msk (0x7u << RTC_MR_THIGH_Pos) /**< \brief (RTC_MR) High Duration of the Output Pulse */
#define RTC_MR_THIGH(value) ((RTC_MR_THIGH_Msk & ((value) << RTC_MR_THIGH_Pos)))
#define   RTC_MR_THIGH_H_31MS (0x0u << 24) /**< \brief (RTC_MR) 31.2 ms */
#define   RTC_MR_THIGH_H_16MS (0x1u << 24) /**< \brief (RTC_MR) 15.6 ms */
#define   RTC_MR_THIGH_H_4MS (0x2u << 24) /**< \brief (RTC_MR) 3.91 ms */
#define   RTC_MR_THIGH_H_976US (0x3u << 24) /**< \brief (RTC_MR) 976 us */
#define   RTC_MR_THIGH_H_488US (0x4u << 24) /**< \brief (RTC_MR) 488 us */
#define   RTC_MR_THIGH_H_122US (0x5u << 24) /**< \brief (RTC_MR) 122 us */
#define   RTC_MR_THIGH_H_30US (0x6u << 24) /**< \brief (RTC_MR) 30.5 us */
#define   RTC_MR_THIGH_H_15US (0x7u << 24) /**< \brief (RTC_MR) 15.2 us */
#define RTC_MR_TPERIOD_Pos 28
#define RTC_MR_TPERIOD_Msk (0x3u << RTC_MR_TPERIOD_Pos) /**< \brief (RTC_MR) Period of the Output Pulse */
#define RTC_MR_TPERIOD(value) ((RTC_MR_TPERIOD_Msk & ((value) << RTC_MR_TPERIOD_Pos)))
#define   RTC_MR_TPERIOD_P_1S (0x0u << 28) /**< \brief (RTC_MR) 1 second */
#define   RTC_MR_TPERIOD_P_500MS (0x1u << 28) /**< \brief (RTC_MR) 500 ms */
#define   RTC_MR_TPERIOD_P_250MS (0x2u << 28) /**< \brief (RTC_MR) 250 ms */
#define   RTC_MR_TPERIOD_P_125MS (0x3u << 28) /**< \brief (RTC_MR) 125 ms */
/* -------- RTC_TIMR : (RTC Offset: 0x8) Time Register -------- */
#define RTC_TIMR_SEC_Pos 0
#define RTC_TIMR_SEC_Msk (0x7fu << RTC_TIMR_SEC_Pos) /**< \brief (RTC_TIMR) Current Second */
#define RTC_TIMR_SEC(value) ((RTC_TIMR_SEC_Msk & ((value) << RTC_TIMR_SEC_Pos)))
#define RTC_TIMR_MIN_Pos 8
#define RTC_TIMR_MIN_Msk (0x7fu << RTC_TIMR_MIN_Pos) /**< \brief (RTC_TIMR) Current Minute */
#define RTC_TIMR_MIN(value) ((RTC_TIMR_MIN_Msk & ((value) << RTC_TIMR_MIN_Pos)))
#define RTC_TIMR_HOUR_Pos 16
#define RTC_TIMR_HOUR_Msk (0x3fu << RTC_TIMR_HOUR_Pos) /**< \brief (RTC_TIMR) Current Hour */
#define RTC_TIMR_HOUR(value) ((RTC_TIMR_HOUR_Msk & ((value) << RTC_TIMR_HOUR_Pos)))
#define RTC_TIMR_AMPM (0x1u << 22) /**< \brief (RTC_TIMR) Ante Meridiem Post Meridiem Indicator */
#define RTC_TIMR_UTC_TIME_Pos 0
#define RTC_TIMR_UTC_TIME_Msk (0xffffffffu << RTC_TIMR_UTC_TIME_Pos) /**< \brief (RTC_TIMR) Current UTC Time */
#define RTC_TIMR_UTC_TIME(value) ((RTC_TIMR_UTC_TIME_Msk & ((value) << RTC_TIMR_UTC_TIME_Pos)))
/* -------- RTC_CALR : (RTC Offset: 0xC) Calendar Register -------- */
#define RTC_CALR_CENT_Pos 0
#define RTC_CALR_CENT_Msk (0x7fu << RTC_CALR_CENT_Pos) /**< \brief (RTC_CALR) Current Century */
#define RTC_CALR_CENT(value) ((RTC_CALR_CENT_Msk & ((value) << RTC_CALR_CENT_Pos)))
#define RTC_CALR_YEAR_Pos 8
#define RTC_CALR_YEAR_Msk (0xffu << RTC_CALR_YEAR_Pos) /**< \brief (RTC_CALR) Current Year */
#define RTC_CALR_YEAR(value) ((RTC_CALR_YEAR_Msk & ((value) << RTC_CALR_YEAR_Pos)))
#define RTC_CALR_MONTH_Pos 16
#define RTC_CALR_MONTH_Msk (0x1fu << RTC_CALR_MONTH_Pos) /**< \brief (RTC_CALR) Current Month */
#define RTC_CALR_MONTH(value) ((RTC_CALR_MONTH_Msk & ((value) << RTC_CALR_MONTH_Pos)))
#define RTC_CALR_DAY_Pos 21
#define RTC_CALR_DAY_Msk (0x7u << RTC_CALR_DAY_Pos) /**< \brief (RTC_CALR) Current Day in Current Week */
#define RTC_CALR_DAY(value) ((RTC_CALR_DAY_Msk & ((value) << RTC_CALR_DAY_Pos)))
#define RTC_CALR_DATE_Pos 24
#define RTC_CALR_DATE_Msk (0x3fu << RTC_CALR_DATE_Pos) /**< \brief (RTC_CALR) Current Day in Current Month */
#define RTC_CALR_DATE(value) ((RTC_CALR_DATE_Msk & ((value) << RTC_CALR_DATE_Pos)))
/* -------- RTC_TIMALR : (RTC Offset: 0x10) Time Alarm Register -------- */
#define RTC_TIMALR_SEC_Pos 0
#define RTC_TIMALR_SEC_Msk (0x7fu << RTC_TIMALR_SEC_Pos) /**< \brief (RTC_TIMALR) Second Alarm */
#define RTC_TIMALR_SEC(value) ((RTC_TIMALR_SEC_Msk & ((value) << RTC_TIMALR_SEC_Pos)))
#define RTC_TIMALR_SECEN (0x1u << 7) /**< \brief (RTC_TIMALR) Second Alarm Enable */
#define RTC_TIMALR_MIN_Pos 8
#define RTC_TIMALR_MIN_Msk (0x7fu << RTC_TIMALR_MIN_Pos) /**< \brief (RTC_TIMALR) Minute Alarm */
#define RTC_TIMALR_MIN(value) ((RTC_TIMALR_MIN_Msk & ((value) << RTC_TIMALR_MIN_Pos)))
#define RTC_TIMALR_MINEN (0x1u << 15) /**< \brief (RTC_TIMALR) Minute Alarm Enable */
#define RTC_TIMALR_HOUR_Pos 16
#define RTC_TIMALR_HOUR_Msk (0x3fu << RTC_TIMALR_HOUR_Pos) /**< \brief (RTC_TIMALR) Hour Alarm */
#define RTC_TIMALR_HOUR(value) ((RTC_TIMALR_HOUR_Msk & ((value) << RTC_TIMALR_HOUR_Pos)))
#define RTC_TIMALR_AMPM (0x1u << 22) /**< \brief (RTC_TIMALR) AM/PM Indicator */
#define RTC_TIMALR_HOUREN (0x1u << 23) /**< \brief (RTC_TIMALR) Hour Alarm Enable */
#define RTC_TIMALR_UTC_TIME_Pos 0
#define RTC_TIMALR_UTC_TIME_Msk (0xffffffffu << RTC_TIMALR_UTC_TIME_Pos) /**< \brief (RTC_TIMALR) UTC_TIME Alarm */
#define RTC_TIMALR_UTC_TIME(value) ((RTC_TIMALR_UTC_TIME_Msk & ((value) << RTC_TIMALR_UTC_TIME_Pos)))
/* -------- RTC_CALALR : (RTC Offset: 0x14) Calendar Alarm Register -------- */
#define RTC_CALALR_MONTH_Pos 16
#define RTC_CALALR_MONTH_Msk (0x1fu << RTC_CALALR_MONTH_Pos) /**< \brief (RTC_CALALR) Month Alarm */
#define RTC_CALALR_MONTH(value) ((RTC_CALALR_MONTH_Msk & ((value) << RTC_CALALR_MONTH_Pos)))
#define RTC_CALALR_MTHEN (0x1u << 23) /**< \brief (RTC_CALALR) Month Alarm Enable */
#define RTC_CALALR_DATE_Pos 24
#define RTC_CALALR_DATE_Msk (0x3fu << RTC_CALALR_DATE_Pos) /**< \brief (RTC_CALALR) Date Alarm */
#define RTC_CALALR_DATE(value) ((RTC_CALALR_DATE_Msk & ((value) << RTC_CALALR_DATE_Pos)))
#define RTC_CALALR_DATEEN (0x1u << 31) /**< \brief (RTC_CALALR) Date Alarm Enable */
#define RTC_CALALR_UTCEN (0x1u << 0) /**< \brief (RTC_CALALR) UTC Alarm Enable */
/* -------- RTC_SR : (RTC Offset: 0x18) Status Register -------- */
#define RTC_SR_ACKUPD (0x1u << 0) /**< \brief (RTC_SR) Acknowledge for Update */
#define   RTC_SR_ACKUPD_FREERUN (0x0u << 0) /**< \brief (RTC_SR) Time and calendar registers cannot be updated. */
#define   RTC_SR_ACKUPD_UPDATE (0x1u << 0) /**< \brief (RTC_SR) Time and calendar registers can be updated. */
#define RTC_SR_ALARM (0x1u << 1) /**< \brief (RTC_SR) Alarm Flag */
#define   RTC_SR_ALARM_NO_ALARMEVENT (0x0u << 1) /**< \brief (RTC_SR) No alarm matching condition occurred. */
#define   RTC_SR_ALARM_ALARMEVENT (0x1u << 1) /**< \brief (RTC_SR) An alarm matching condition has occurred. */
#define RTC_SR_SEC (0x1u << 2) /**< \brief (RTC_SR) Second Event */
#define   RTC_SR_SEC_NO_SECEVENT (0x0u << 2) /**< \brief (RTC_SR) No second event has occurred since the last clear. */
#define   RTC_SR_SEC_SECEVENT (0x1u << 2) /**< \brief (RTC_SR) At least one second event has occurred since the last clear. */
#define RTC_SR_TIMEV (0x1u << 3) /**< \brief (RTC_SR) Time Event */
#define   RTC_SR_TIMEV_NO_TIMEVENT (0x0u << 3) /**< \brief (RTC_SR) No time event has occurred since the last clear. */
#define   RTC_SR_TIMEV_TIMEVENT (0x1u << 3) /**< \brief (RTC_SR) At least one time event has occurred since the last clear. */
#define RTC_SR_CALEV (0x1u << 4) /**< \brief (RTC_SR) Calendar Event */
#define   RTC_SR_CALEV_NO_CALEVENT (0x0u << 4) /**< \brief (RTC_SR) No calendar event has occurred since the last clear. */
#define   RTC_SR_CALEV_CALEVENT (0x1u << 4) /**< \brief (RTC_SR) At least one calendar event has occurred since the last clear. */
#define RTC_SR_TDERR (0x1u << 5) /**< \brief (RTC_SR) Time and/or Date Free Running Error */
#define   RTC_SR_TDERR_CORRECT (0x0u << 5) /**< \brief (RTC_SR) The internal free running counters are carrying valid values since the last read of the Status Register (RTC_SR). */
#define   RTC_SR_TDERR_ERR_TIMEDATE (0x1u << 5) /**< \brief (RTC_SR) The internal free running counters have been corrupted (invalid date or time, non-BCD values) since the last read and/or they are still invalid. */
/* -------- RTC_SCCR : (RTC Offset: 0x1C) Status Clear Command Register -------- */
#define RTC_SCCR_ACKCLR (0x1u << 0) /**< \brief (RTC_SCCR) Acknowledge Clear */
#define RTC_SCCR_ALRCLR (0x1u << 1) /**< \brief (RTC_SCCR) Alarm Clear */
#define RTC_SCCR_SECCLR (0x1u << 2) /**< \brief (RTC_SCCR) Second Clear */
#define RTC_SCCR_TIMCLR (0x1u << 3) /**< \brief (RTC_SCCR) Time Clear */
#define RTC_SCCR_CALCLR (0x1u << 4) /**< \brief (RTC_SCCR) Calendar Clear */
#define RTC_SCCR_TDERRCLR (0x1u << 5) /**< \brief (RTC_SCCR) Time and/or Date Free Running Error Clear */
/* -------- RTC_IER : (RTC Offset: 0x20) Interrupt Enable Register -------- */
#define RTC_IER_ACKEN (0x1u << 0) /**< \brief (RTC_IER) Acknowledge Update Interrupt Enable */
#define RTC_IER_ALREN (0x1u << 1) /**< \brief (RTC_IER) Alarm Interrupt Enable */
#define RTC_IER_SECEN (0x1u << 2) /**< \brief (RTC_IER) Second Event Interrupt Enable */
#define RTC_IER_TIMEN (0x1u << 3) /**< \brief (RTC_IER) Time Event Interrupt Enable */
#define RTC_IER_CALEN (0x1u << 4) /**< \brief (RTC_IER) Calendar Event Interrupt Enable */
#define RTC_IER_TDERREN (0x1u << 5) /**< \brief (RTC_IER) Time and/or Date Error Interrupt Enable */
/* -------- RTC_IDR : (RTC Offset: 0x24) Interrupt Disable Register -------- */
#define RTC_IDR_ACKDIS (0x1u << 0) /**< \brief (RTC_IDR) Acknowledge Update Interrupt Disable */
#define RTC_IDR_ALRDIS (0x1u << 1) /**< \brief (RTC_IDR) Alarm Interrupt Disable */
#define RTC_IDR_SECDIS (0x1u << 2) /**< \brief (RTC_IDR) Second Event Interrupt Disable */
#define RTC_IDR_TIMDIS (0x1u << 3) /**< \brief (RTC_IDR) Time Event Interrupt Disable */
#define RTC_IDR_CALDIS (0x1u << 4) /**< \brief (RTC_IDR) Calendar Event Interrupt Disable */
#define RTC_IDR_TDERRDIS (0x1u << 5) /**< \brief (RTC_IDR) Time and/or Date Error Interrupt Disable */
/* -------- RTC_IMR : (RTC Offset: 0x28) Interrupt Mask Register -------- */
#define RTC_IMR_ACK (0x1u << 0) /**< \brief (RTC_IMR) Acknowledge Update Interrupt Mask */
#define RTC_IMR_ALR (0x1u << 1) /**< \brief (RTC_IMR) Alarm Interrupt Mask */
#define RTC_IMR_SEC (0x1u << 2) /**< \brief (RTC_IMR) Second Event Interrupt Mask */
#define RTC_IMR_TIM (0x1u << 3) /**< \brief (RTC_IMR) Time Event Interrupt Mask */
#define RTC_IMR_CAL (0x1u << 4) /**< \brief (RTC_IMR) Calendar Event Interrupt Mask */
#define RTC_IMR_TDERR (0x1u << 5) /**< \brief (RTC_IMR) Time and/or Date Error Mask */
/* -------- RTC_VER : (RTC Offset: 0x2C) Valid Entry Register -------- */
#define RTC_VER_NVTIM (0x1u << 0) /**< \brief (RTC_VER) Non-valid Time */
#define RTC_VER_NVCAL (0x1u << 1) /**< \brief (RTC_VER) Non-valid Calendar */
#define RTC_VER_NVTIMALR (0x1u << 2) /**< \brief (RTC_VER) Non-valid Time Alarm */
#define RTC_VER_NVCALALR (0x1u << 3) /**< \brief (RTC_VER) Non-valid Calendar Alarm */
/* -------- RTC_TMR : (RTC Offset: 0x58) Tamper Mode register -------- */
#define RTC_TMR_EN0 (0x1u << 0) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN0_DISABLE (0x0u << 0) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN0_ENABLE (0x1u << 0) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN1 (0x1u << 1) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN1_DISABLE (0x0u << 1) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN1_ENABLE (0x1u << 1) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN2 (0x1u << 2) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN2_DISABLE (0x0u << 2) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN2_ENABLE (0x1u << 2) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN3 (0x1u << 3) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN3_DISABLE (0x0u << 3) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN3_ENABLE (0x1u << 3) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN4 (0x1u << 4) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN4_DISABLE (0x0u << 4) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN4_ENABLE (0x1u << 4) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN5 (0x1u << 5) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN5_DISABLE (0x0u << 5) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN5_ENABLE (0x1u << 5) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN6 (0x1u << 6) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN6_DISABLE (0x0u << 6) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN6_ENABLE (0x1u << 6) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_EN7 (0x1u << 7) /**< \brief (RTC_TMR) WKUPx+1 Tamper Source Enable */
#define   RTC_TMR_EN7_DISABLE (0x0u << 7) /**< \brief (RTC_TMR) WKUP pin index x+1 is not enabled as a source of tamper. */
#define   RTC_TMR_EN7_ENABLE (0x1u << 7) /**< \brief (RTC_TMR) WKUP pin index x+1 is enabled as a source of tamper. */
#define RTC_TMR_POL0 (0x1u << 16) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL0_LOW (0x0u << 16) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL0_HIGH (0x1u << 16) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL1 (0x1u << 17) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL1_LOW (0x0u << 17) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL1_HIGH (0x1u << 17) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL2 (0x1u << 18) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL2_LOW (0x0u << 18) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL2_HIGH (0x1u << 18) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL3 (0x1u << 19) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL3_LOW (0x0u << 19) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL3_HIGH (0x1u << 19) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL4 (0x1u << 20) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL4_LOW (0x0u << 20) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL4_HIGH (0x1u << 20) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL5 (0x1u << 21) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL5_LOW (0x0u << 21) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL5_HIGH (0x1u << 21) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL6 (0x1u << 22) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL6_LOW (0x0u << 22) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL6_HIGH (0x1u << 22) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_POL7 (0x1u << 23) /**< \brief (RTC_TMR) WKUPx+1 Polarity */
#define   RTC_TMR_POL7_LOW (0x0u << 23) /**< \brief (RTC_TMR) If the source of tamper remains low for a debounce period, a tamper event is generated. */
#define   RTC_TMR_POL7_HIGH (0x1u << 23) /**< \brief (RTC_TMR) If the source of tamper remains high for a debounce period, a tamper event is generated. */
#define RTC_TMR_TRLOCK (0x1u << 31) /**< \brief (RTC_TMR) Tamper Registers Lock (Write-once, cleared by VDDCORE reset) */
#define   RTC_TMR_TRLOCK_UNLOCKED (0x0u << 31) /**< \brief (RTC_TMR) RTC_TMR and RTC_TDPR can be written. */
#define   RTC_TMR_TRLOCK_LOCKED (0x1u << 31) /**< \brief (RTC_TMR) RTC_TMR and RTC_TDPR cannot be written until the next VDDCORE domain reset. */
/* -------- RTC_TDPR : (RTC Offset: 0x5C) Tamper Debounce Period register -------- */
#define RTC_TDPR_PERA_Pos 0
#define RTC_TDPR_PERA_Msk (0xfu << RTC_TDPR_PERA_Pos) /**< \brief (RTC_TDPR) Debounce Period A */
#define RTC_TDPR_PERA(value) ((RTC_TDPR_PERA_Msk & ((value) << RTC_TDPR_PERA_Pos)))
#define   RTC_TDPR_PERA_MD_SLCK_2 (0x0u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 2 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_4 (0x1u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 4 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_8 (0x2u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 8 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_16 (0x3u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 16 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_32 (0x4u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 32 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_64 (0x5u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 64 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_128 (0x6u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 128 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERA_MD_SLCK_256 (0x7u << 0) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 256 monitoring domain slow clock cycles to generate a tamper event. */
#define RTC_TDPR_PERB_Pos 4
#define RTC_TDPR_PERB_Msk (0xfu << RTC_TDPR_PERB_Pos) /**< \brief (RTC_TDPR) Debounce Period B */
#define RTC_TDPR_PERB(value) ((RTC_TDPR_PERB_Msk & ((value) << RTC_TDPR_PERB_Pos)))
#define   RTC_TDPR_PERB_MD_SLCK_2 (0x0u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 2 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_4 (0x1u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 4 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_8 (0x2u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 8 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_16 (0x3u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 16 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_32 (0x4u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 32 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_64 (0x5u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 64 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_128 (0x6u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 128 monitoring domain slow clock cycles to generate a tamper event. */
#define   RTC_TDPR_PERB_MD_SLCK_256 (0x7u << 4) /**< \brief (RTC_TDPR) The source of tamper must remain active for at least 256 monitoring domain slow clock cycles to generate a tamper event. */
#define RTC_TDPR_SELP0 (0x1u << 16) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP0_SEL_PA (0x0u << 16) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP0_SEL_PB (0x1u << 16) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP1 (0x1u << 17) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP1_SEL_PA (0x0u << 17) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP1_SEL_PB (0x1u << 17) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP2 (0x1u << 18) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP2_SEL_PA (0x0u << 18) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP2_SEL_PB (0x1u << 18) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP3 (0x1u << 19) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP3_SEL_PA (0x0u << 19) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP3_SEL_PB (0x1u << 19) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP4 (0x1u << 20) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP4_SEL_PA (0x0u << 20) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP4_SEL_PB (0x1u << 20) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP5 (0x1u << 21) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP5_SEL_PA (0x0u << 21) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP5_SEL_PB (0x1u << 21) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP6 (0x1u << 22) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP6_SEL_PA (0x0u << 22) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP6_SEL_PB (0x1u << 22) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
#define RTC_TDPR_SELP7 (0x1u << 23) /**< \brief (RTC_TDPR) WKUPx+1 Debounce Period Selection */
#define   RTC_TDPR_SELP7_SEL_PA (0x0u << 23) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERA period. */
#define   RTC_TDPR_SELP7_SEL_PB (0x1u << 23) /**< \brief (RTC_TDPR) WKUP pin index x+1 is debounced with PERB period. */
/* -------- RTC_TSTR : (RTC Offset: N/A) TimeStamp Time Register 0 -------- */
#define RTC_TSTR_SEC_Pos 0
#define RTC_TSTR_SEC_Msk (0x7fu << RTC_TSTR_SEC_Pos) /**< \brief (RTC_TSTR) Seconds of the Tamper (cleared by reading RTC_TSSR0) */
#define RTC_TSTR_MIN_Pos 8
#define RTC_TSTR_MIN_Msk (0x7fu << RTC_TSTR_MIN_Pos) /**< \brief (RTC_TSTR) Minutes of the Tamper (cleared by reading RTC_TSSR0) */
#define RTC_TSTR_HOUR_Pos 16
#define RTC_TSTR_HOUR_Msk (0x3fu << RTC_TSTR_HOUR_Pos) /**< \brief (RTC_TSTR) Hours of the Tamper (cleared by reading RTC_TSSR0) */
#define RTC_TSTR_AMPM (0x1u << 22) /**< \brief (RTC_TSTR) AM/PM Indicator of the Tamper (cleared by reading RTC_TSSR0) */
#define RTC_TSTR_TEVCNT_Pos 24
#define RTC_TSTR_TEVCNT_Msk (0xfu << RTC_TSTR_TEVCNT_Pos) /**< \brief (RTC_TSTR) Tamper Events Counter (cleared by reading RTC_TSSR0) */
#define RTC_TSTR_BACKUP (0x1u << 31) /**< \brief (RTC_TSTR) System Mode of the Tamper (cleared by reading RTC_TSSR0) */
/* -------- RTC_TSDR : (RTC Offset: N/A) TimeStamp Date Register 0 -------- */
#define RTC_TSDR_CENT_Pos 0
#define RTC_TSDR_CENT_Msk (0x7fu << RTC_TSDR_CENT_Pos) /**< \brief (RTC_TSDR) Century of the Tamper (cleared by reading RTC_TSSRx) */
#define RTC_TSDR_YEAR_Pos 8
#define RTC_TSDR_YEAR_Msk (0xffu << RTC_TSDR_YEAR_Pos) /**< \brief (RTC_TSDR) Year of the Tamper (cleared by reading RTC_TSSRx) */
#define RTC_TSDR_MONTH_Pos 16
#define RTC_TSDR_MONTH_Msk (0x1fu << RTC_TSDR_MONTH_Pos) /**< \brief (RTC_TSDR) Month of the Tamper (cleared by reading RTC_TSSRx) */
#define RTC_TSDR_DAY_Pos 21
#define RTC_TSDR_DAY_Msk (0x7u << RTC_TSDR_DAY_Pos) /**< \brief (RTC_TSDR) Day of the Tamper (cleared by reading RTC_TSSRx) */
#define RTC_TSDR_DATE_Pos 24
#define RTC_TSDR_DATE_Msk (0x3fu << RTC_TSDR_DATE_Pos) /**< \brief (RTC_TSDR) Date of the Tamper (cleared by reading RTC_TSSRx) */
#define RTC_TSDR_UTC_TIME_Pos 0
#define RTC_TSDR_UTC_TIME_Msk (0xffffffffu << RTC_TSDR_UTC_TIME_Pos) /**< \brief (RTC_TSDR) Time of the Tamper (UTC format) */
/* -------- RTC_TSSR : (RTC Offset: N/A) TimeStamp Source Register 0 -------- */
#define RTC_TSSR_DET0 (0x1u << 16) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET1 (0x1u << 17) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET2 (0x1u << 18) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET3 (0x1u << 19) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET4 (0x1u << 20) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET5 (0x1u << 21) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET6 (0x1u << 22) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */
#define RTC_TSSR_DET7 (0x1u << 23) /**< \brief (RTC_TSSR) Tamper Detection on VDDCORE WKUP[8:1] (cleared on read) */

/*@}*/


#endif /* _SAM9X_RTC_COMPONENT_ */
