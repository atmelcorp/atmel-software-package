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

#ifndef _SAMA5D2_PWM_INSTANCE_
#define _SAMA5D2_PWM_INSTANCE_

/* ========== Register definition for PWM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PWM_CLK                       (0xF802C000U) /**< \brief (PWM) PWM Clock Register */
  #define REG_PWM_ENA                       (0xF802C004U) /**< \brief (PWM) PWM Enable Register */
  #define REG_PWM_DIS                       (0xF802C008U) /**< \brief (PWM) PWM Disable Register */
  #define REG_PWM_SR                        (0xF802C00CU) /**< \brief (PWM) PWM Status Register */
  #define REG_PWM_IER1                      (0xF802C010U) /**< \brief (PWM) PWM Interrupt Enable Register 1 */
  #define REG_PWM_IDR1                      (0xF802C014U) /**< \brief (PWM) PWM Interrupt Disable Register 1 */
  #define REG_PWM_IMR1                      (0xF802C018U) /**< \brief (PWM) PWM Interrupt Mask Register 1 */
  #define REG_PWM_ISR1                      (0xF802C01CU) /**< \brief (PWM) PWM Interrupt Status Register 1 */
  #define REG_PWM_SCM                       (0xF802C020U) /**< \brief (PWM) PWM Sync Channels Mode Register */
  #define REG_PWM_DMAR                      (0xF802C024U) /**< \brief (PWM) PWM DMA Register */
  #define REG_PWM_SCUC                      (0xF802C028U) /**< \brief (PWM) PWM Sync Channels Update Control Register */
  #define REG_PWM_SCUP                      (0xF802C02CU) /**< \brief (PWM) PWM Sync Channels Update Period Register */
  #define REG_PWM_SCUPUPD                   (0xF802C030U) /**< \brief (PWM) PWM Sync Channels Update Period Update Register */
  #define REG_PWM_IER2                      (0xF802C034U) /**< \brief (PWM) PWM Interrupt Enable Register 2 */
  #define REG_PWM_IDR2                      (0xF802C038U) /**< \brief (PWM) PWM Interrupt Disable Register 2 */
  #define REG_PWM_IMR2                      (0xF802C03CU) /**< \brief (PWM) PWM Interrupt Mask Register 2 */
  #define REG_PWM_ISR2                      (0xF802C040U) /**< \brief (PWM) PWM Interrupt Status Register 2 */
  #define REG_PWM_OOV                       (0xF802C044U) /**< \brief (PWM) PWM Output Override Value Register */
  #define REG_PWM_OS                        (0xF802C048U) /**< \brief (PWM) PWM Output Selection Register */
  #define REG_PWM_OSS                       (0xF802C04CU) /**< \brief (PWM) PWM Output Selection Set Register */
  #define REG_PWM_OSC                       (0xF802C050U) /**< \brief (PWM) PWM Output Selection Clear Register */
  #define REG_PWM_OSSUPD                    (0xF802C054U) /**< \brief (PWM) PWM Output Selection Set Update Register */
  #define REG_PWM_OSCUPD                    (0xF802C058U) /**< \brief (PWM) PWM Output Selection Clear Update Register */
  #define REG_PWM_FMR                       (0xF802C05CU) /**< \brief (PWM) PWM Fault Mode Register */
  #define REG_PWM_FSR                       (0xF802C060U) /**< \brief (PWM) PWM Fault Status Register */
  #define REG_PWM_FCR                       (0xF802C064U) /**< \brief (PWM) PWM Fault Clear Register */
  #define REG_PWM_FPV1                      (0xF802C068U) /**< \brief (PWM) PWM Fault Protection Value Register 1 */
  #define REG_PWM_FPE                       (0xF802C06CU) /**< \brief (PWM) PWM Fault Protection Enable Register */
  #define REG_PWM_ELMR                      (0xF802C07CU) /**< \brief (PWM) PWM Event Line 0 Mode Register */
  #define REG_PWM_SSPR                      (0xF802C0A0U) /**< \brief (PWM) PWM Spread Spectrum Register */
  #define REG_PWM_SSPUP                     (0xF802C0A4U) /**< \brief (PWM) PWM Spread Spectrum Update Register */
  #define REG_PWM_SMMR                      (0xF802C0B0U) /**< \brief (PWM) PWM Stepper Motor Mode Register */
  #define REG_PWM_FPV2                      (0xF802C0C0U) /**< \brief (PWM) PWM Fault Protection Value 2 Register */
  #define REG_PWM_WPCR                      (0xF802C0E4U) /**< \brief (PWM) PWM Write Protection Control Register */
  #define REG_PWM_WPSR                      (0xF802C0E8U) /**< \brief (PWM) PWM Write Protection Status Register */
  #define REG_PWM_VERSION                   (0xF802C0FCU) /**< \brief (PWM) Version Register */
  #define REG_PWM_CMPV0                     (0xF802C130U) /**< \brief (PWM) PWM Comparison 0 Value Register */
  #define REG_PWM_CMPVUPD0                  (0xF802C134U) /**< \brief (PWM) PWM Comparison 0 Value Update Register */
  #define REG_PWM_CMPM0                     (0xF802C138U) /**< \brief (PWM) PWM Comparison 0 Mode Register */
  #define REG_PWM_CMPMUPD0                  (0xF802C13CU) /**< \brief (PWM) PWM Comparison 0 Mode Update Register */
  #define REG_PWM_CMPV1                     (0xF802C140U) /**< \brief (PWM) PWM Comparison 1 Value Register */
  #define REG_PWM_CMPVUPD1                  (0xF802C144U) /**< \brief (PWM) PWM Comparison 1 Value Update Register */
  #define REG_PWM_CMPM1                     (0xF802C148U) /**< \brief (PWM) PWM Comparison 1 Mode Register */
  #define REG_PWM_CMPMUPD1                  (0xF802C14CU) /**< \brief (PWM) PWM Comparison 1 Mode Update Register */
  #define REG_PWM_CMPV2                     (0xF802C150U) /**< \brief (PWM) PWM Comparison 2 Value Register */
  #define REG_PWM_CMPVUPD2                  (0xF802C154U) /**< \brief (PWM) PWM Comparison 2 Value Update Register */
  #define REG_PWM_CMPM2                     (0xF802C158U) /**< \brief (PWM) PWM Comparison 2 Mode Register */
  #define REG_PWM_CMPMUPD2                  (0xF802C15CU) /**< \brief (PWM) PWM Comparison 2 Mode Update Register */
  #define REG_PWM_CMPV3                     (0xF802C160U) /**< \brief (PWM) PWM Comparison 3 Value Register */
  #define REG_PWM_CMPVUPD3                  (0xF802C164U) /**< \brief (PWM) PWM Comparison 3 Value Update Register */
  #define REG_PWM_CMPM3                     (0xF802C168U) /**< \brief (PWM) PWM Comparison 3 Mode Register */
  #define REG_PWM_CMPMUPD3                  (0xF802C16CU) /**< \brief (PWM) PWM Comparison 3 Mode Update Register */
  #define REG_PWM_CMPV4                     (0xF802C170U) /**< \brief (PWM) PWM Comparison 4 Value Register */
  #define REG_PWM_CMPVUPD4                  (0xF802C174U) /**< \brief (PWM) PWM Comparison 4 Value Update Register */
  #define REG_PWM_CMPM4                     (0xF802C178U) /**< \brief (PWM) PWM Comparison 4 Mode Register */
  #define REG_PWM_CMPMUPD4                  (0xF802C17CU) /**< \brief (PWM) PWM Comparison 4 Mode Update Register */
  #define REG_PWM_CMPV5                     (0xF802C180U) /**< \brief (PWM) PWM Comparison 5 Value Register */
  #define REG_PWM_CMPVUPD5                  (0xF802C184U) /**< \brief (PWM) PWM Comparison 5 Value Update Register */
  #define REG_PWM_CMPM5                     (0xF802C188U) /**< \brief (PWM) PWM Comparison 5 Mode Register */
  #define REG_PWM_CMPMUPD5                  (0xF802C18CU) /**< \brief (PWM) PWM Comparison 5 Mode Update Register */
  #define REG_PWM_CMPV6                     (0xF802C190U) /**< \brief (PWM) PWM Comparison 6 Value Register */
  #define REG_PWM_CMPVUPD6                  (0xF802C194U) /**< \brief (PWM) PWM Comparison 6 Value Update Register */
  #define REG_PWM_CMPM6                     (0xF802C198U) /**< \brief (PWM) PWM Comparison 6 Mode Register */
  #define REG_PWM_CMPMUPD6                  (0xF802C19CU) /**< \brief (PWM) PWM Comparison 6 Mode Update Register */
  #define REG_PWM_CMPV7                     (0xF802C1A0U) /**< \brief (PWM) PWM Comparison 7 Value Register */
  #define REG_PWM_CMPVUPD7                  (0xF802C1A4U) /**< \brief (PWM) PWM Comparison 7 Value Update Register */
  #define REG_PWM_CMPM7                     (0xF802C1A8U) /**< \brief (PWM) PWM Comparison 7 Mode Register */
  #define REG_PWM_CMPMUPD7                  (0xF802C1ACU) /**< \brief (PWM) PWM Comparison 7 Mode Update Register */
  #define REG_PWM_CMR0                      (0xF802C200U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 0) */
  #define REG_PWM_CDTY0                     (0xF802C204U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 0) */
  #define REG_PWM_CDTYUPD0                  (0xF802C208U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 0) */
  #define REG_PWM_CPRD0                     (0xF802C20CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 0) */
  #define REG_PWM_CPRDUPD0                  (0xF802C210U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 0) */
  #define REG_PWM_CCNT0                     (0xF802C214U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 0) */
  #define REG_PWM_DT0                       (0xF802C218U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 0) */
  #define REG_PWM_DTUPD0                    (0xF802C21CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 0) */
  #define REG_PWM_CMR1                      (0xF802C220U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 1) */
  #define REG_PWM_CDTY1                     (0xF802C224U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 1) */
  #define REG_PWM_CDTYUPD1                  (0xF802C228U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 1) */
  #define REG_PWM_CPRD1                     (0xF802C22CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 1) */
  #define REG_PWM_CPRDUPD1                  (0xF802C230U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 1) */
  #define REG_PWM_CCNT1                     (0xF802C234U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 1) */
  #define REG_PWM_DT1                       (0xF802C238U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 1) */
  #define REG_PWM_DTUPD1                    (0xF802C23CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 1) */
  #define REG_PWM_CMR2                      (0xF802C240U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 2) */
  #define REG_PWM_CDTY2                     (0xF802C244U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 2) */
  #define REG_PWM_CDTYUPD2                  (0xF802C248U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 2) */
  #define REG_PWM_CPRD2                     (0xF802C24CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 2) */
  #define REG_PWM_CPRDUPD2                  (0xF802C250U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 2) */
  #define REG_PWM_CCNT2                     (0xF802C254U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 2) */
  #define REG_PWM_DT2                       (0xF802C258U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 2) */
  #define REG_PWM_DTUPD2                    (0xF802C25CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 2) */
  #define REG_PWM_CMR3                      (0xF802C260U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 3) */
  #define REG_PWM_CDTY3                     (0xF802C264U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 3) */
  #define REG_PWM_CDTYUPD3                  (0xF802C268U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 3) */
  #define REG_PWM_CPRD3                     (0xF802C26CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 3) */
  #define REG_PWM_CPRDUPD3                  (0xF802C270U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 3) */
  #define REG_PWM_CCNT3                     (0xF802C274U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 3) */
  #define REG_PWM_DT3                       (0xF802C278U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 3) */
  #define REG_PWM_DTUPD3                    (0xF802C27CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 3) */
  #define REG_PWM_CMUPD0                    (0xF802C400U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 0) */
  #define REG_PWM_CMUPD1                    (0xF802C420U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 1) */
  #define REG_PWM_ETRG1                     (0xF802C42CU) /**< \brief (PWM) PWM External Trigger Register (trg_num = 1) */
  #define REG_PWM_LEBR1                     (0xF802C430U) /**< \brief (PWM) PWM Leading-Edge Blanking Register (trg_num = 1) */
  #define REG_PWM_CMUPD2                    (0xF802C440U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 2) */
  #define REG_PWM_ETRG2                     (0xF802C44CU) /**< \brief (PWM) PWM External Trigger Register (trg_num = 2) */
  #define REG_PWM_LEBR2                     (0xF802C450U) /**< \brief (PWM) PWM Leading-Edge Blanking Register (trg_num = 2) */
  #define REG_PWM_CMUPD3                    (0xF802C460U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 3) */
#else
  #define REG_PWM_CLK      (*(__IO uint32_t*)0xF802C000U) /**< \brief (PWM) PWM Clock Register */
  #define REG_PWM_ENA      (*(__O  uint32_t*)0xF802C004U) /**< \brief (PWM) PWM Enable Register */
  #define REG_PWM_DIS      (*(__O  uint32_t*)0xF802C008U) /**< \brief (PWM) PWM Disable Register */
  #define REG_PWM_SR       (*(__I  uint32_t*)0xF802C00CU) /**< \brief (PWM) PWM Status Register */
  #define REG_PWM_IER1     (*(__O  uint32_t*)0xF802C010U) /**< \brief (PWM) PWM Interrupt Enable Register 1 */
  #define REG_PWM_IDR1     (*(__O  uint32_t*)0xF802C014U) /**< \brief (PWM) PWM Interrupt Disable Register 1 */
  #define REG_PWM_IMR1     (*(__I  uint32_t*)0xF802C018U) /**< \brief (PWM) PWM Interrupt Mask Register 1 */
  #define REG_PWM_ISR1     (*(__I  uint32_t*)0xF802C01CU) /**< \brief (PWM) PWM Interrupt Status Register 1 */
  #define REG_PWM_SCM      (*(__IO uint32_t*)0xF802C020U) /**< \brief (PWM) PWM Sync Channels Mode Register */
  #define REG_PWM_DMAR     (*(__O  uint32_t*)0xF802C024U) /**< \brief (PWM) PWM DMA Register */
  #define REG_PWM_SCUC     (*(__IO uint32_t*)0xF802C028U) /**< \brief (PWM) PWM Sync Channels Update Control Register */
  #define REG_PWM_SCUP     (*(__IO uint32_t*)0xF802C02CU) /**< \brief (PWM) PWM Sync Channels Update Period Register */
  #define REG_PWM_SCUPUPD  (*(__O  uint32_t*)0xF802C030U) /**< \brief (PWM) PWM Sync Channels Update Period Update Register */
  #define REG_PWM_IER2     (*(__O  uint32_t*)0xF802C034U) /**< \brief (PWM) PWM Interrupt Enable Register 2 */
  #define REG_PWM_IDR2     (*(__O  uint32_t*)0xF802C038U) /**< \brief (PWM) PWM Interrupt Disable Register 2 */
  #define REG_PWM_IMR2     (*(__I  uint32_t*)0xF802C03CU) /**< \brief (PWM) PWM Interrupt Mask Register 2 */
  #define REG_PWM_ISR2     (*(__I  uint32_t*)0xF802C040U) /**< \brief (PWM) PWM Interrupt Status Register 2 */
  #define REG_PWM_OOV      (*(__IO uint32_t*)0xF802C044U) /**< \brief (PWM) PWM Output Override Value Register */
  #define REG_PWM_OS       (*(__IO uint32_t*)0xF802C048U) /**< \brief (PWM) PWM Output Selection Register */
  #define REG_PWM_OSS      (*(__O  uint32_t*)0xF802C04CU) /**< \brief (PWM) PWM Output Selection Set Register */
  #define REG_PWM_OSC      (*(__O  uint32_t*)0xF802C050U) /**< \brief (PWM) PWM Output Selection Clear Register */
  #define REG_PWM_OSSUPD   (*(__O  uint32_t*)0xF802C054U) /**< \brief (PWM) PWM Output Selection Set Update Register */
  #define REG_PWM_OSCUPD   (*(__O  uint32_t*)0xF802C058U) /**< \brief (PWM) PWM Output Selection Clear Update Register */
  #define REG_PWM_FMR      (*(__IO uint32_t*)0xF802C05CU) /**< \brief (PWM) PWM Fault Mode Register */
  #define REG_PWM_FSR      (*(__I  uint32_t*)0xF802C060U) /**< \brief (PWM) PWM Fault Status Register */
  #define REG_PWM_FCR      (*(__O  uint32_t*)0xF802C064U) /**< \brief (PWM) PWM Fault Clear Register */
  #define REG_PWM_FPV1     (*(__IO uint32_t*)0xF802C068U) /**< \brief (PWM) PWM Fault Protection Value Register 1 */
  #define REG_PWM_FPE      (*(__IO uint32_t*)0xF802C06CU) /**< \brief (PWM) PWM Fault Protection Enable Register */
  #define REG_PWM_ELMR     (*(__IO uint32_t*)0xF802C07CU) /**< \brief (PWM) PWM Event Line 0 Mode Register */
  #define REG_PWM_SSPR     (*(__IO uint32_t*)0xF802C0A0U) /**< \brief (PWM) PWM Spread Spectrum Register */
  #define REG_PWM_SSPUP    (*(__O  uint32_t*)0xF802C0A4U) /**< \brief (PWM) PWM Spread Spectrum Update Register */
  #define REG_PWM_SMMR     (*(__IO uint32_t*)0xF802C0B0U) /**< \brief (PWM) PWM Stepper Motor Mode Register */
  #define REG_PWM_FPV2     (*(__IO uint32_t*)0xF802C0C0U) /**< \brief (PWM) PWM Fault Protection Value 2 Register */
  #define REG_PWM_WPCR     (*(__O  uint32_t*)0xF802C0E4U) /**< \brief (PWM) PWM Write Protection Control Register */
  #define REG_PWM_WPSR     (*(__I  uint32_t*)0xF802C0E8U) /**< \brief (PWM) PWM Write Protection Status Register */
  #define REG_PWM_VERSION  (*(__I  uint32_t*)0xF802C0FCU) /**< \brief (PWM) Version Register */
  #define REG_PWM_CMPV0    (*(__IO uint32_t*)0xF802C130U) /**< \brief (PWM) PWM Comparison 0 Value Register */
  #define REG_PWM_CMPVUPD0 (*(__O  uint32_t*)0xF802C134U) /**< \brief (PWM) PWM Comparison 0 Value Update Register */
  #define REG_PWM_CMPM0    (*(__IO uint32_t*)0xF802C138U) /**< \brief (PWM) PWM Comparison 0 Mode Register */
  #define REG_PWM_CMPMUPD0 (*(__O  uint32_t*)0xF802C13CU) /**< \brief (PWM) PWM Comparison 0 Mode Update Register */
  #define REG_PWM_CMPV1    (*(__IO uint32_t*)0xF802C140U) /**< \brief (PWM) PWM Comparison 1 Value Register */
  #define REG_PWM_CMPVUPD1 (*(__O  uint32_t*)0xF802C144U) /**< \brief (PWM) PWM Comparison 1 Value Update Register */
  #define REG_PWM_CMPM1    (*(__IO uint32_t*)0xF802C148U) /**< \brief (PWM) PWM Comparison 1 Mode Register */
  #define REG_PWM_CMPMUPD1 (*(__O  uint32_t*)0xF802C14CU) /**< \brief (PWM) PWM Comparison 1 Mode Update Register */
  #define REG_PWM_CMPV2    (*(__IO uint32_t*)0xF802C150U) /**< \brief (PWM) PWM Comparison 2 Value Register */
  #define REG_PWM_CMPVUPD2 (*(__O  uint32_t*)0xF802C154U) /**< \brief (PWM) PWM Comparison 2 Value Update Register */
  #define REG_PWM_CMPM2    (*(__IO uint32_t*)0xF802C158U) /**< \brief (PWM) PWM Comparison 2 Mode Register */
  #define REG_PWM_CMPMUPD2 (*(__O  uint32_t*)0xF802C15CU) /**< \brief (PWM) PWM Comparison 2 Mode Update Register */
  #define REG_PWM_CMPV3    (*(__IO uint32_t*)0xF802C160U) /**< \brief (PWM) PWM Comparison 3 Value Register */
  #define REG_PWM_CMPVUPD3 (*(__O  uint32_t*)0xF802C164U) /**< \brief (PWM) PWM Comparison 3 Value Update Register */
  #define REG_PWM_CMPM3    (*(__IO uint32_t*)0xF802C168U) /**< \brief (PWM) PWM Comparison 3 Mode Register */
  #define REG_PWM_CMPMUPD3 (*(__O  uint32_t*)0xF802C16CU) /**< \brief (PWM) PWM Comparison 3 Mode Update Register */
  #define REG_PWM_CMPV4    (*(__IO uint32_t*)0xF802C170U) /**< \brief (PWM) PWM Comparison 4 Value Register */
  #define REG_PWM_CMPVUPD4 (*(__O  uint32_t*)0xF802C174U) /**< \brief (PWM) PWM Comparison 4 Value Update Register */
  #define REG_PWM_CMPM4    (*(__IO uint32_t*)0xF802C178U) /**< \brief (PWM) PWM Comparison 4 Mode Register */
  #define REG_PWM_CMPMUPD4 (*(__O  uint32_t*)0xF802C17CU) /**< \brief (PWM) PWM Comparison 4 Mode Update Register */
  #define REG_PWM_CMPV5    (*(__IO uint32_t*)0xF802C180U) /**< \brief (PWM) PWM Comparison 5 Value Register */
  #define REG_PWM_CMPVUPD5 (*(__O  uint32_t*)0xF802C184U) /**< \brief (PWM) PWM Comparison 5 Value Update Register */
  #define REG_PWM_CMPM5    (*(__IO uint32_t*)0xF802C188U) /**< \brief (PWM) PWM Comparison 5 Mode Register */
  #define REG_PWM_CMPMUPD5 (*(__O  uint32_t*)0xF802C18CU) /**< \brief (PWM) PWM Comparison 5 Mode Update Register */
  #define REG_PWM_CMPV6    (*(__IO uint32_t*)0xF802C190U) /**< \brief (PWM) PWM Comparison 6 Value Register */
  #define REG_PWM_CMPVUPD6 (*(__O  uint32_t*)0xF802C194U) /**< \brief (PWM) PWM Comparison 6 Value Update Register */
  #define REG_PWM_CMPM6    (*(__IO uint32_t*)0xF802C198U) /**< \brief (PWM) PWM Comparison 6 Mode Register */
  #define REG_PWM_CMPMUPD6 (*(__O  uint32_t*)0xF802C19CU) /**< \brief (PWM) PWM Comparison 6 Mode Update Register */
  #define REG_PWM_CMPV7    (*(__IO uint32_t*)0xF802C1A0U) /**< \brief (PWM) PWM Comparison 7 Value Register */
  #define REG_PWM_CMPVUPD7 (*(__O  uint32_t*)0xF802C1A4U) /**< \brief (PWM) PWM Comparison 7 Value Update Register */
  #define REG_PWM_CMPM7    (*(__IO uint32_t*)0xF802C1A8U) /**< \brief (PWM) PWM Comparison 7 Mode Register */
  #define REG_PWM_CMPMUPD7 (*(__O  uint32_t*)0xF802C1ACU) /**< \brief (PWM) PWM Comparison 7 Mode Update Register */
  #define REG_PWM_CMR0     (*(__IO uint32_t*)0xF802C200U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 0) */
  #define REG_PWM_CDTY0    (*(__IO uint32_t*)0xF802C204U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 0) */
  #define REG_PWM_CDTYUPD0 (*(__O  uint32_t*)0xF802C208U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 0) */
  #define REG_PWM_CPRD0    (*(__IO uint32_t*)0xF802C20CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 0) */
  #define REG_PWM_CPRDUPD0 (*(__O  uint32_t*)0xF802C210U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 0) */
  #define REG_PWM_CCNT0    (*(__I  uint32_t*)0xF802C214U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 0) */
  #define REG_PWM_DT0      (*(__IO uint32_t*)0xF802C218U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 0) */
  #define REG_PWM_DTUPD0   (*(__O  uint32_t*)0xF802C21CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 0) */
  #define REG_PWM_CMR1     (*(__IO uint32_t*)0xF802C220U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 1) */
  #define REG_PWM_CDTY1    (*(__IO uint32_t*)0xF802C224U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 1) */
  #define REG_PWM_CDTYUPD1 (*(__O  uint32_t*)0xF802C228U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 1) */
  #define REG_PWM_CPRD1    (*(__IO uint32_t*)0xF802C22CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 1) */
  #define REG_PWM_CPRDUPD1 (*(__O  uint32_t*)0xF802C230U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 1) */
  #define REG_PWM_CCNT1    (*(__I  uint32_t*)0xF802C234U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 1) */
  #define REG_PWM_DT1      (*(__IO uint32_t*)0xF802C238U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 1) */
  #define REG_PWM_DTUPD1   (*(__O  uint32_t*)0xF802C23CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 1) */
  #define REG_PWM_CMR2     (*(__IO uint32_t*)0xF802C240U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 2) */
  #define REG_PWM_CDTY2    (*(__IO uint32_t*)0xF802C244U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 2) */
  #define REG_PWM_CDTYUPD2 (*(__O  uint32_t*)0xF802C248U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 2) */
  #define REG_PWM_CPRD2    (*(__IO uint32_t*)0xF802C24CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 2) */
  #define REG_PWM_CPRDUPD2 (*(__O  uint32_t*)0xF802C250U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 2) */
  #define REG_PWM_CCNT2    (*(__I  uint32_t*)0xF802C254U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 2) */
  #define REG_PWM_DT2      (*(__IO uint32_t*)0xF802C258U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 2) */
  #define REG_PWM_DTUPD2   (*(__O  uint32_t*)0xF802C25CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 2) */
  #define REG_PWM_CMR3     (*(__IO uint32_t*)0xF802C260U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 3) */
  #define REG_PWM_CDTY3    (*(__IO uint32_t*)0xF802C264U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 3) */
  #define REG_PWM_CDTYUPD3 (*(__O  uint32_t*)0xF802C268U) /**< \brief (PWM) PWM Channel Duty Cycle Update Register (ch_num = 3) */
  #define REG_PWM_CPRD3    (*(__IO uint32_t*)0xF802C26CU) /**< \brief (PWM) PWM Channel Period Register (ch_num = 3) */
  #define REG_PWM_CPRDUPD3 (*(__O  uint32_t*)0xF802C270U) /**< \brief (PWM) PWM Channel Period Update Register (ch_num = 3) */
  #define REG_PWM_CCNT3    (*(__I  uint32_t*)0xF802C274U) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 3) */
  #define REG_PWM_DT3      (*(__IO uint32_t*)0xF802C278U) /**< \brief (PWM) PWM Channel Dead Time Register (ch_num = 3) */
  #define REG_PWM_DTUPD3   (*(__O  uint32_t*)0xF802C27CU) /**< \brief (PWM) PWM Channel Dead Time Update Register (ch_num = 3) */
  #define REG_PWM_CMUPD0   (*(__O  uint32_t*)0xF802C400U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 0) */
  #define REG_PWM_CMUPD1   (*(__O  uint32_t*)0xF802C420U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 1) */
  #define REG_PWM_ETRG1    (*(__IO uint32_t*)0xF802C42CU) /**< \brief (PWM) PWM External Trigger Register (trg_num = 1) */
  #define REG_PWM_LEBR1    (*(__IO uint32_t*)0xF802C430U) /**< \brief (PWM) PWM Leading-Edge Blanking Register (trg_num = 1) */
  #define REG_PWM_CMUPD2   (*(__O  uint32_t*)0xF802C440U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 2) */
  #define REG_PWM_ETRG2    (*(__IO uint32_t*)0xF802C44CU) /**< \brief (PWM) PWM External Trigger Register (trg_num = 2) */
  #define REG_PWM_LEBR2    (*(__IO uint32_t*)0xF802C450U) /**< \brief (PWM) PWM Leading-Edge Blanking Register (trg_num = 2) */
  #define REG_PWM_CMUPD3   (*(__O  uint32_t*)0xF802C460U) /**< \brief (PWM) PWM Channel Mode Update Register (ch_num = 3) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_PWM_INSTANCE_ */
