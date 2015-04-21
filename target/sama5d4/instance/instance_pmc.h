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

#ifndef _SAMA5D4_PMC_INSTANCE_
#define _SAMA5D4_PMC_INSTANCE_

/* ========== Register definition for PMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PMC_SCER                     (0xF0018000U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                     (0xF0018004U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                     (0xF0018008U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0                    (0xF0018010U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0                    (0xF0018014U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0                    (0xF0018018U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_UCKR                    (0xF001801CU) /**< \brief (PMC) UTMI Clock Register */
#define REG_CKGR_MOR                     (0xF0018020U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_MCFR                    (0xF0018024U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR                   (0xF0018028U) /**< \brief (PMC) PLLA Register */
#define REG_PMC_MCKR                     (0xF0018030U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB                      (0xF0018038U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_SMD                      (0xF001803CU) /**< \brief (PMC) Soft Modem Clock Register */
#define REG_PMC_PCK                      (0xF0018040U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER                      (0xF0018060U) /**< \brief (PMC) Interrupt Enable Register */
#define REG_PMC_IDR                      (0xF0018064U) /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR                       (0xF0018068U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR                      (0xF001806CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_FOCR                     (0xF0018078U) /**< \brief (PMC) Fault Output Clear Register */
#define REG_PMC_PLLICPR                  (0xF0018080U) /**< \brief (PMC) PLL Charge Pump Current Register */
#define REG_PMC_WPMR                     (0xF00180E4U) /**< \brief (PMC) Write ProtectIon Mode Register */
#define REG_PMC_WPSR                     (0xF00180E8U) /**< \brief (PMC) Write Protection Status Register */
#define REG_PMC_PCER1                    (0xF0018100U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
#define REG_PMC_PCDR1                    (0xF0018104U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
#define REG_PMC_PCSR1                    (0xF0018108U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
#define REG_PMC_PCR                      (0xF001810CU) /**< \brief (PMC) Peripheral Control Register */
#else
#define REG_PMC_SCER    (*(__O  uint32_t*)0xF0018000U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR    (*(__O  uint32_t*)0xF0018004U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR    (*(__I  uint32_t*)0xF0018008U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0   (*(__O  uint32_t*)0xF0018010U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0   (*(__O  uint32_t*)0xF0018014U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0   (*(__I  uint32_t*)0xF0018018U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_UCKR   (*(__IO uint32_t*)0xF001801CU) /**< \brief (PMC) UTMI Clock Register */
#define REG_CKGR_MOR    (*(__IO uint32_t*)0xF0018020U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_MCFR   (*(__IO uint32_t*)0xF0018024U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR  (*(__IO uint32_t*)0xF0018028U) /**< \brief (PMC) PLLA Register */
#define REG_PMC_MCKR    (*(__IO uint32_t*)0xF0018030U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB     (*(__IO uint32_t*)0xF0018038U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_SMD     (*(__IO uint32_t*)0xF001803CU) /**< \brief (PMC) Soft Modem Clock Register */
#define REG_PMC_PCK     (*(__IO uint32_t*)0xF0018040U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER     (*(__O  uint32_t*)0xF0018060U) /**< \brief (PMC) Interrupt Enable Register */
#define REG_PMC_IDR     (*(__O  uint32_t*)0xF0018064U) /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR      (*(__I  uint32_t*)0xF0018068U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR     (*(__I  uint32_t*)0xF001806CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_FOCR    (*(__O  uint32_t*)0xF0018078U) /**< \brief (PMC) Fault Output Clear Register */
#define REG_PMC_PLLICPR (*(__IO uint32_t*)0xF0018080U) /**< \brief (PMC) PLL Charge Pump Current Register */
#define REG_PMC_WPMR    (*(__IO uint32_t*)0xF00180E4U) /**< \brief (PMC) Write ProtectIon Mode Register */
#define REG_PMC_WPSR    (*(__I  uint32_t*)0xF00180E8U) /**< \brief (PMC) Write Protection Status Register */
#define REG_PMC_PCER1   (*(__O  uint32_t*)0xF0018100U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
#define REG_PMC_PCDR1   (*(__O  uint32_t*)0xF0018104U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
#define REG_PMC_PCSR1   (*(__I  uint32_t*)0xF0018108U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
#define REG_PMC_PCR     (*(__IO uint32_t*)0xF001810CU) /**< \brief (PMC) Peripheral Control Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_PMC_INSTANCE_ */
