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

#ifndef _SAM9X_PMC_INSTANCE_
#define _SAM9X_PMC_INSTANCE_

/* ========== Register definition for PMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PMC_SCER                       (0xFFFFFC00U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR                       (0xFFFFFC04U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR                       (0xFFFFFC08U) /**< \brief (PMC) System Clock Status Register */
  #define REG_PMC_PLL_CTRL0                  (0xFFFFFC0CU) /**< \brief (PMC) PLL Control Register 0 */
  #define REG_PMC_PLL_CTRL1                  (0xFFFFFC10U) /**< \brief (PMC) PLL Control Register 1 */
  #define REG_PMC_PLL_SSR                    (0xFFFFFC14U) /**< \brief (PMC) PLL Spread Spectrum Register */
  #define REG_PMC_PLL_ACR                    (0xFFFFFC18U) /**< \brief (PMC) PLL Analog Control Register */
  #define REG_PMC_PLL_UPDT                   (0xFFFFFC1CU) /**< \brief (PMC) PLL Update Register */
  #define REG_CKGR_MOR                       (0xFFFFFC20U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR                      (0xFFFFFC24U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_PMC_CPU_CKR                    (0xFFFFFC28U) /**< \brief (PMC) CPU Clock Register */
  #define REG_PMC_USB                        (0xFFFFFC38U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_PCK                        (0xFFFFFC40U) /**< \brief (PMC) Programmable Clock Register */
  #define REG_PMC_IER                        (0xFFFFFC60U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR                        (0xFFFFFC64U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR                         (0xFFFFFC68U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR                        (0xFFFFFC6CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FSMR                       (0xFFFFFC70U) /**< \brief (PMC) Fast Startup Mode Register */
  #define REG_PMC_WCR                        (0xFFFFFC74U) /**< \brief (PMC) Wakeup Control Register */
  #define REG_PMC_FOCR                       (0xFFFFFC78U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_WPMR                       (0xFFFFFC80U) /**< \brief (PMC) Write Protection Mode Register */
  #define REG_PMC_WPSR                       (0xFFFFFC84U) /**< \brief (PMC) Write Protection Status Register */
  #define REG_PMC_PCR                        (0xFFFFFC88U) /**< \brief (PMC) Peripheral Control Register */
  #define REG_PMC_OCR                        (0xFFFFFC8CU) /**< \brief (PMC) Oscillator Calibration Register */
  #define REG_PMC_MCKLIM                     (0xFFFFFC9CU) /**< \brief (PMC) MCK Monitor Limits Register */
  #define REG_PMC_CSR0                       (0xFFFFFCA0U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
  #define REG_PMC_CSR1                       (0xFFFFFCA4U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
  #define REG_PMC_GCSR0                      (0xFFFFFCC0U) /**< \brief (PMC) Generic Clock Status Register 0 */
  #define REG_PMC_GCSR1                      (0xFFFFFCC4U) /**< \brief (PMC) Generic Clock Status Register 1 */
  #define REG_PMC_PLL_IER                    (0xFFFFFCE0U) /**< \brief (PMC) PLL Interrupt Enable Register */
  #define REG_PMC_PLL_IDR                    (0xFFFFFCE4U) /**< \brief (PMC) PLL Interrupt Disable Register */
  #define REG_PMC_PLL_IMR                    (0xFFFFFCE8U) /**< \brief (PMC) PLL Interrupt Mask Register */
  #define REG_PMC_PLL_ISR0                   (0xFFFFFCECU) /**< \brief (PMC) PLL Interrupt Status Register 0 */
  #define REG_PMC_PLL_ISR1                   (0xFFFFFCF0U) /**< \brief (PMC) PLL Interrupt Status Register 1 */
#else
  #define REG_PMC_SCER      (*(__O  uint32_t*)0xFFFFFC00U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR      (*(__O  uint32_t*)0xFFFFFC04U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR      (*(__I  uint32_t*)0xFFFFFC08U) /**< \brief (PMC) System Clock Status Register */
  #define REG_PMC_PLL_CTRL0 (*(__IO uint32_t*)0xFFFFFC0CU) /**< \brief (PMC) PLL Control Register 0 */
  #define REG_PMC_PLL_CTRL1 (*(__IO uint32_t*)0xFFFFFC10U) /**< \brief (PMC) PLL Control Register 1 */
  #define REG_PMC_PLL_SSR   (*(__IO uint32_t*)0xFFFFFC14U) /**< \brief (PMC) PLL Spread Spectrum Register */
  #define REG_PMC_PLL_ACR   (*(__IO uint32_t*)0xFFFFFC18U) /**< \brief (PMC) PLL Analog Control Register */
  #define REG_PMC_PLL_UPDT  (*(__IO uint32_t*)0xFFFFFC1CU) /**< \brief (PMC) PLL Update Register */
  #define REG_CKGR_MOR      (*(__IO uint32_t*)0xFFFFFC20U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR     (*(__IO uint32_t*)0xFFFFFC24U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_PMC_CPU_CKR   (*(__IO uint32_t*)0xFFFFFC28U) /**< \brief (PMC) CPU Clock Register */
  #define REG_PMC_USB       (*(__IO uint32_t*)0xFFFFFC38U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_PCK       (*(__IO uint32_t*)0xFFFFFC40U) /**< \brief (PMC) Programmable Clock Register */
  #define REG_PMC_IER       (*(__O  uint32_t*)0xFFFFFC60U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR       (*(__O  uint32_t*)0xFFFFFC64U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR        (*(__I  uint32_t*)0xFFFFFC68U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR       (*(__I  uint32_t*)0xFFFFFC6CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FSMR      (*(__IO uint32_t*)0xFFFFFC70U) /**< \brief (PMC) Fast Startup Mode Register */
  #define REG_PMC_WCR       (*(__IO uint32_t*)0xFFFFFC74U) /**< \brief (PMC) Wakeup Control Register */
  #define REG_PMC_FOCR      (*(__O  uint32_t*)0xFFFFFC78U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_WPMR      (*(__IO uint32_t*)0xFFFFFC80U) /**< \brief (PMC) Write Protection Mode Register */
  #define REG_PMC_WPSR      (*(__I  uint32_t*)0xFFFFFC84U) /**< \brief (PMC) Write Protection Status Register */
  #define REG_PMC_PCR       (*(__IO uint32_t*)0xFFFFFC88U) /**< \brief (PMC) Peripheral Control Register */
  #define REG_PMC_OCR       (*(__IO uint32_t*)0xFFFFFC8CU) /**< \brief (PMC) Oscillator Calibration Register */
  #define REG_PMC_MCKLIM    (*(__IO uint32_t*)0xFFFFFC9CU) /**< \brief (PMC) MCK Monitor Limits Register */
  #define REG_PMC_CSR0      (*(__I  uint32_t*)0xFFFFFCA0U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
  #define REG_PMC_CSR1      (*(__I  uint32_t*)0xFFFFFCA4U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
  #define REG_PMC_GCSR0     (*(__I  uint32_t*)0xFFFFFCC0U) /**< \brief (PMC) Generic Clock Status Register 0 */
  #define REG_PMC_GCSR1     (*(__I  uint32_t*)0xFFFFFCC4U) /**< \brief (PMC) Generic Clock Status Register 1 */
  #define REG_PMC_PLL_IER   (*(__O  uint32_t*)0xFFFFFCE0U) /**< \brief (PMC) PLL Interrupt Enable Register */
  #define REG_PMC_PLL_IDR   (*(__O  uint32_t*)0xFFFFFCE4U) /**< \brief (PMC) PLL Interrupt Disable Register */
  #define REG_PMC_PLL_IMR   (*(__I  uint32_t*)0xFFFFFCE8U) /**< \brief (PMC) PLL Interrupt Mask Register */
  #define REG_PMC_PLL_ISR0  (*(__I  uint32_t*)0xFFFFFCECU) /**< \brief (PMC) PLL Interrupt Status Register 0 */
  #define REG_PMC_PLL_ISR1  (*(__I  uint32_t*)0xFFFFFCF0U) /**< \brief (PMC) PLL Interrupt Status Register 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PMC_INSTANCE_ */
