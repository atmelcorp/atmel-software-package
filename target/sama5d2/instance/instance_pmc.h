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

#ifndef _SAMA5D2_PMC_INSTANCE_
#define _SAMA5D2_PMC_INSTANCE_

/* ========== Register definition for PMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PMC_SCER                        (0xF0014000U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR                        (0xF0014004U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR                        (0xF0014008U) /**< \brief (PMC) System Clock Status Register */
  #define REG_CKGR_UCKR                       (0xF001401CU) /**< \brief (PMC) UTMI Clock Register */
  #define REG_CKGR_MOR                        (0xF0014020U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR                       (0xF0014024U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_CKGR_PLLAR                      (0xF0014028U) /**< \brief (PMC) PLLA Register */
  #define REG_PMC_MCKR                        (0xF0014030U) /**< \brief (PMC) Master Clock Register */
  #define REG_PMC_USB                         (0xF0014038U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_PCK                         (0xF0014040U) /**< \brief (PMC) Programmable Clock 0 Register */
  #define REG_PMC_IER                         (0xF0014060U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR                         (0xF0014064U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR                          (0xF0014068U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR                         (0xF001406CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FSMR                        (0xF0014070U) /**< \brief (PMC) PMC Fast Startup Mode Register */
  #define REG_PMC_FSPR                        (0xF0014074U) /**< \brief (PMC) PMC Fast Startup Polarity Register */
  #define REG_PMC_FOCR                        (0xF0014078U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_PLLICPR                     (0xF0014080U) /**< \brief (PMC) PLL Charge Pump Current Register */
  #define REG_PMC_WPMR                        (0xF00140E4U) /**< \brief (PMC) Write ProtectIon Mode Register */
  #define REG_PMC_WPSR                        (0xF00140E8U) /**< \brief (PMC) Write Protection Status Register */
  #define REG_PMC_VERSION                     (0xF00140FCU) /**< \brief (PMC) Version Register */
  #define REG_PMC_PCR                         (0xF001410CU) /**< \brief (PMC) Peripheral Control Register */
  #define REG_PMC_OCR                         (0xF0014110U) /**< \brief (PMC) Oscillator Calibration Register */
  #define REG_PMC_SLPWK_AIPR                  (0xF0014144U) /**< \brief (PMC) SleepWalking Activity In Progress Register */
  #define REG_PMC_SLPWKCR                     (0xF0014148U) /**< \brief (PMC) SleepWalking Control Register */
  #define REG_PMC_AUDIO_PLL0                  (0xF001414CU) /**< \brief (PMC) Audio PLL Register 0 */
  #define REG_PMC_AUDIO_PLL1                  (0xF0014150U) /**< \brief (PMC) Audio PLL Register 1 */
#else
  #define REG_PMC_SCER       (*(__O  uint32_t*)0xF0014000U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR       (*(__O  uint32_t*)0xF0014004U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR       (*(__I  uint32_t*)0xF0014008U) /**< \brief (PMC) System Clock Status Register */
  #define REG_CKGR_UCKR      (*(__IO uint32_t*)0xF001401CU) /**< \brief (PMC) UTMI Clock Register */
  #define REG_CKGR_MOR       (*(__IO uint32_t*)0xF0014020U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR      (*(__IO uint32_t*)0xF0014024U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_CKGR_PLLAR     (*(__IO uint32_t*)0xF0014028U) /**< \brief (PMC) PLLA Register */
  #define REG_PMC_MCKR       (*(__IO uint32_t*)0xF0014030U) /**< \brief (PMC) Master Clock Register */
  #define REG_PMC_USB        (*(__IO uint32_t*)0xF0014038U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_PCK        (*(__IO uint32_t*)0xF0014040U) /**< \brief (PMC) Programmable Clock 0 Register */
  #define REG_PMC_IER        (*(__O  uint32_t*)0xF0014060U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR        (*(__O  uint32_t*)0xF0014064U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR         (*(__I  uint32_t*)0xF0014068U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR        (*(__I  uint32_t*)0xF001406CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FSMR       (*(__IO uint32_t*)0xF0014070U) /**< \brief (PMC) PMC Fast Startup Mode Register */
  #define REG_PMC_FSPR       (*(__IO uint32_t*)0xF0014074U) /**< \brief (PMC) PMC Fast Startup Polarity Register */
  #define REG_PMC_FOCR       (*(__O  uint32_t*)0xF0014078U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_PLLICPR    (*(__IO uint32_t*)0xF0014080U) /**< \brief (PMC) PLL Charge Pump Current Register */
  #define REG_PMC_WPMR       (*(__IO uint32_t*)0xF00140E4U) /**< \brief (PMC) Write ProtectIon Mode Register */
  #define REG_PMC_WPSR       (*(__I  uint32_t*)0xF00140E8U) /**< \brief (PMC) Write Protection Status Register */
  #define REG_PMC_VERSION    (*(__I  uint32_t*)0xF00140FCU) /**< \brief (PMC) Version Register */
  #define REG_PMC_PCR        (*(__IO uint32_t*)0xF001410CU) /**< \brief (PMC) Peripheral Control Register */
  #define REG_PMC_OCR        (*(__IO uint32_t*)0xF0014110U) /**< \brief (PMC) Oscillator Calibration Register */
  #define REG_PMC_SLPWK_AIPR (*(__I  uint32_t*)0xF0014144U) /**< \brief (PMC) SleepWalking Activity In Progress Register */
  #define REG_PMC_SLPWKCR    (*(__IO uint32_t*)0xF0014148U) /**< \brief (PMC) SleepWalking Control Register */
  #define REG_PMC_AUDIO_PLL0 (*(__IO uint32_t*)0xF001414CU) /**< \brief (PMC) Audio PLL Register 0 */
  #define REG_PMC_AUDIO_PLL1 (*(__IO uint32_t*)0xF0014150U) /**< \brief (PMC) Audio PLL Register 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_PMC_INSTANCE_ */
