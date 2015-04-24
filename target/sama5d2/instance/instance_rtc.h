/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D2_RTC_INSTANCE_
#define _SAMA5D2_RTC_INSTANCE_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_RTC_CR                       (0xF80480B0U) /**< \brief (RTC) Control Register */
  #define REG_RTC_MR                       (0xF80480B4U) /**< \brief (RTC) Mode Register */
  #define REG_RTC_TIMR                     (0xF80480B8U) /**< \brief (RTC) Time Register */
  #define REG_RTC_CALR                     (0xF80480BCU) /**< \brief (RTC) Calendar Register */
  #define REG_RTC_TIMALR                   (0xF80480C0U) /**< \brief (RTC) Time Alarm Register */
  #define REG_RTC_CALALR                   (0xF80480C4U) /**< \brief (RTC) Calendar Alarm Register */
  #define REG_RTC_SR                       (0xF80480C8U) /**< \brief (RTC) Status Register */
  #define REG_RTC_SCCR                     (0xF80480CCU) /**< \brief (RTC) Status Clear Command Register */
  #define REG_RTC_IER                      (0xF80480D0U) /**< \brief (RTC) Interrupt Enable Register */
  #define REG_RTC_IDR                      (0xF80480D4U) /**< \brief (RTC) Interrupt Disable Register */
  #define REG_RTC_IMR                      (0xF80480D8U) /**< \brief (RTC) Interrupt Mask Register */
  #define REG_RTC_VER                      (0xF80480DCU) /**< \brief (RTC) Valid Entry Register */
  #define REG_RTC_TSTR0                    (0xF8048160U) /**< \brief (RTC) TimeStamp Time Register 0 */
  #define REG_RTC_TSDR0                    (0xF8048164U) /**< \brief (RTC) TimeStamp Date Register 0 */
  #define REG_RTC_TSSR0                    (0xF8048168U) /**< \brief (RTC) TimeStamp Source Register 0 */
  #define REG_RTC_TSTR1                    (0xF804816CU) /**< \brief (RTC) TimeStamp Time Register 1 */
  #define REG_RTC_TSDR1                    (0xF8048170U) /**< \brief (RTC) TimeStamp Date Register 1 */
  #define REG_RTC_TSSR1                    (0xF8048174U) /**< \brief (RTC) TimeStamp Source Register 1 */
  #define REG_RTC_MSR                      (0xF8048180U) /**< \brief (RTC) Milliseconds Register */
  #define REG_RTC_WPMR                     (0xF8048194U) /**< \brief (RTC) Write Protection Mode Register */
  #define REG_RTC_VERSION                  (0xF80481ACU) /**< \brief (RTC) Version Register */
#else
  #define REG_RTC_CR      (*(__IO uint32_t*)0xF80480B0U) /**< \brief (RTC) Control Register */
  #define REG_RTC_MR      (*(__IO uint32_t*)0xF80480B4U) /**< \brief (RTC) Mode Register */
  #define REG_RTC_TIMR    (*(__IO uint32_t*)0xF80480B8U) /**< \brief (RTC) Time Register */
  #define REG_RTC_CALR    (*(__IO uint32_t*)0xF80480BCU) /**< \brief (RTC) Calendar Register */
  #define REG_RTC_TIMALR  (*(__IO uint32_t*)0xF80480C0U) /**< \brief (RTC) Time Alarm Register */
  #define REG_RTC_CALALR  (*(__IO uint32_t*)0xF80480C4U) /**< \brief (RTC) Calendar Alarm Register */
  #define REG_RTC_SR      (*(__I  uint32_t*)0xF80480C8U) /**< \brief (RTC) Status Register */
  #define REG_RTC_SCCR    (*(__O  uint32_t*)0xF80480CCU) /**< \brief (RTC) Status Clear Command Register */
  #define REG_RTC_IER     (*(__O  uint32_t*)0xF80480D0U) /**< \brief (RTC) Interrupt Enable Register */
  #define REG_RTC_IDR     (*(__O  uint32_t*)0xF80480D4U) /**< \brief (RTC) Interrupt Disable Register */
  #define REG_RTC_IMR     (*(__I  uint32_t*)0xF80480D8U) /**< \brief (RTC) Interrupt Mask Register */
  #define REG_RTC_VER     (*(__I  uint32_t*)0xF80480DCU) /**< \brief (RTC) Valid Entry Register */
  #define REG_RTC_TSTR0   (*(__I  uint32_t*)0xF8048160U) /**< \brief (RTC) TimeStamp Time Register 0 */
  #define REG_RTC_TSDR0   (*(__I  uint32_t*)0xF8048164U) /**< \brief (RTC) TimeStamp Date Register 0 */
  #define REG_RTC_TSSR0   (*(__I  uint32_t*)0xF8048168U) /**< \brief (RTC) TimeStamp Source Register 0 */
  #define REG_RTC_TSTR1   (*(__I  uint32_t*)0xF804816CU) /**< \brief (RTC) TimeStamp Time Register 1 */
  #define REG_RTC_TSDR1   (*(__I  uint32_t*)0xF8048170U) /**< \brief (RTC) TimeStamp Date Register 1 */
  #define REG_RTC_TSSR1   (*(__I  uint32_t*)0xF8048174U) /**< \brief (RTC) TimeStamp Source Register 1 */
  #define REG_RTC_MSR     (*(__I  uint32_t*)0xF8048180U) /**< \brief (RTC) Milliseconds Register */
  #define REG_RTC_WPMR    (*(__IO uint32_t*)0xF8048194U) /**< \brief (RTC) Write Protection Mode Register */
  #define REG_RTC_VERSION (*(__I  uint32_t*)0xF80481ACU) /**< \brief (RTC) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_RTC_INSTANCE_ */
