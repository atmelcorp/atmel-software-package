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

#ifndef _SAM9X_RTC_INSTANCE_
#define _SAM9X_RTC_INSTANCE_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_RTC_CR                      (0xFFFFFEA8U) /**< \brief (RTC) Control Register */
  #define REG_RTC_MR                      (0xFFFFFEACU) /**< \brief (RTC) Mode Register */
  #define REG_RTC_TIMR                    (0xFFFFFEB0U) /**< \brief (RTC) Time Register */
  #define REG_RTC_CALR                    (0xFFFFFEB4U) /**< \brief (RTC) Calendar Register */
  #define REG_RTC_TIMALR                  (0xFFFFFEB8U) /**< \brief (RTC) Time Alarm Register */
  #define REG_RTC_CALALR                  (0xFFFFFEBCU) /**< \brief (RTC) Calendar Alarm Register */
  #define REG_RTC_SR                      (0xFFFFFEC0U) /**< \brief (RTC) Status Register */
  #define REG_RTC_SCCR                    (0xFFFFFEC4U) /**< \brief (RTC) Status Clear Command Register */
  #define REG_RTC_IER                     (0xFFFFFEC8U) /**< \brief (RTC) Interrupt Enable Register */
  #define REG_RTC_IDR                     (0xFFFFFECCU) /**< \brief (RTC) Interrupt Disable Register */
  #define REG_RTC_IMR                     (0xFFFFFED0U) /**< \brief (RTC) Interrupt Mask Register */
  #define REG_RTC_VER                     (0xFFFFFED4U) /**< \brief (RTC) Valid Entry Register */
  #define REG_RTC_TMR                     (0xFFFFFF00U) /**< \brief (RTC) Tamper Mode register */
  #define REG_RTC_TDPR                    (0xFFFFFF04U) /**< \brief (RTC) Tamper Debounce Period register */
  #define REG_RTC_TSTR0                   (0xFFFFFF58U) /**< \brief (RTC) TimeStamp Time Register 0 */
  #define REG_RTC_TSDR0                   (0xFFFFFF5CU) /**< \brief (RTC) TimeStamp Date Register 0 */
  #define REG_RTC_TSSR0                   (0xFFFFFF60U) /**< \brief (RTC) TimeStamp Source Register 0 */
  #define REG_RTC_TSTR1                   (0xFFFFFF64U) /**< \brief (RTC) TimeStamp Time Register 1 */
  #define REG_RTC_TSDR1                   (0xFFFFFF68U) /**< \brief (RTC) TimeStamp Date Register 1 */
  #define REG_RTC_TSSR1                   (0xFFFFFF6CU) /**< \brief (RTC) TimeStamp Source Register 1 */
#else
  #define REG_RTC_CR     (*(__IO uint32_t*)0xFFFFFEA8U) /**< \brief (RTC) Control Register */
  #define REG_RTC_MR     (*(__IO uint32_t*)0xFFFFFEACU) /**< \brief (RTC) Mode Register */
  #define REG_RTC_TIMR   (*(__IO uint32_t*)0xFFFFFEB0U) /**< \brief (RTC) Time Register */
  #define REG_RTC_CALR   (*(__IO uint32_t*)0xFFFFFEB4U) /**< \brief (RTC) Calendar Register */
  #define REG_RTC_TIMALR (*(__IO uint32_t*)0xFFFFFEB8U) /**< \brief (RTC) Time Alarm Register */
  #define REG_RTC_CALALR (*(__IO uint32_t*)0xFFFFFEBCU) /**< \brief (RTC) Calendar Alarm Register */
  #define REG_RTC_SR     (*(__I  uint32_t*)0xFFFFFEC0U) /**< \brief (RTC) Status Register */
  #define REG_RTC_SCCR   (*(__O  uint32_t*)0xFFFFFEC4U) /**< \brief (RTC) Status Clear Command Register */
  #define REG_RTC_IER    (*(__O  uint32_t*)0xFFFFFEC8U) /**< \brief (RTC) Interrupt Enable Register */
  #define REG_RTC_IDR    (*(__O  uint32_t*)0xFFFFFECCU) /**< \brief (RTC) Interrupt Disable Register */
  #define REG_RTC_IMR    (*(__I  uint32_t*)0xFFFFFED0U) /**< \brief (RTC) Interrupt Mask Register */
  #define REG_RTC_VER    (*(__I  uint32_t*)0xFFFFFED4U) /**< \brief (RTC) Valid Entry Register */
  #define REG_RTC_TMR    (*(__IO uint32_t*)0xFFFFFF00U) /**< \brief (RTC) Tamper Mode register */
  #define REG_RTC_TDPR   (*(__IO uint32_t*)0xFFFFFF04U) /**< \brief (RTC) Tamper Debounce Period register */
  #define REG_RTC_TSTR0  (*(__I  uint32_t*)0xFFFFFF58U) /**< \brief (RTC) TimeStamp Time Register 0 */
  #define REG_RTC_TSDR0  (*(__I  uint32_t*)0xFFFFFF5CU) /**< \brief (RTC) TimeStamp Date Register 0 */
  #define REG_RTC_TSSR0  (*(__I  uint32_t*)0xFFFFFF60U) /**< \brief (RTC) TimeStamp Source Register 0 */
  #define REG_RTC_TSTR1  (*(__I  uint32_t*)0xFFFFFF64U) /**< \brief (RTC) TimeStamp Time Register 1 */
  #define REG_RTC_TSDR1  (*(__I  uint32_t*)0xFFFFFF68U) /**< \brief (RTC) TimeStamp Date Register 1 */
  #define REG_RTC_TSSR1  (*(__I  uint32_t*)0xFFFFFF6CU) /**< \brief (RTC) TimeStamp Source Register 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_RTC_INSTANCE_ */
