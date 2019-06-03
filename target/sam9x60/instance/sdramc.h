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

#ifndef _SAM9X_SDRAMC_INSTANCE_
#define _SAM9X_SDRAMC_INSTANCE_

/* ========== Register definition for SDRAMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SDRAMC_MR                         (0xFFFFEC00U) /**< \brief (SDRAMC) Mode Register */
  #define REG_SDRAMC_TR                         (0xFFFFEC04U) /**< \brief (SDRAMC) Refresh Timer Register */
  #define REG_SDRAMC_CR                         (0xFFFFEC08U) /**< \brief (SDRAMC) Configuration Register */
  #define REG_SDRAMC_HSR                        (0xFFFFEC0CU) /**< \brief (SDRAMC) High-Speed Register */
  #define REG_SDRAMC_LPR                        (0xFFFFEC10U) /**< \brief (SDRAMC) Low-Power Register */
  #define REG_SDRAMC_IER                        (0xFFFFEC14U) /**< \brief (SDRAMC) Interrupt Enable Register */
  #define REG_SDRAMC_IDR                        (0xFFFFEC18U) /**< \brief (SDRAMC) Interrupt Disable Register */
  #define REG_SDRAMC_IMR                        (0xFFFFEC1CU) /**< \brief (SDRAMC) Interrupt Mask Register */
  #define REG_SDRAMC_ISR                        (0xFFFFEC20U) /**< \brief (SDRAMC) Interrupt Status Register */
  #define REG_SDRAMC_MDR                        (0xFFFFEC24U) /**< \brief (SDRAMC) Memory Device Register */
  #define REG_SDRAMC_CFR1                       (0xFFFFEC28U) /**< \brief (SDRAMC) Configuration Register 1 */
  #define REG_SDRAMC_OCMS                       (0xFFFFEC2CU) /**< \brief (SDRAMC) OCMS Register */
  #define REG_SDRAMC_OCMS_KEY1                  (0xFFFFEC30U) /**< \brief (SDRAMC) OCMS KEY1 Register */
  #define REG_SDRAMC_OCMS_KEY2                  (0xFFFFEC34U) /**< \brief (SDRAMC) OCMS KEY2 Register */
  #define REG_SDRAMC_WPMR                       (0xFFFFEC3CU) /**< \brief (SDRAMC) Write Protection Mode Register */
  #define REG_SDRAMC_WPSR                       (0xFFFFEC40U) /**< \brief (SDRAMC) Write Protection Status Register */
#else
  #define REG_SDRAMC_MR        (*(__IO uint32_t*)0xFFFFEC00U) /**< \brief (SDRAMC) Mode Register */
  #define REG_SDRAMC_TR        (*(__IO uint32_t*)0xFFFFEC04U) /**< \brief (SDRAMC) Refresh Timer Register */
  #define REG_SDRAMC_CR        (*(__IO uint32_t*)0xFFFFEC08U) /**< \brief (SDRAMC) Configuration Register */
  #define REG_SDRAMC_HSR       (*(__IO uint32_t*)0xFFFFEC0CU) /**< \brief (SDRAMC) High-Speed Register */
  #define REG_SDRAMC_LPR       (*(__IO uint32_t*)0xFFFFEC10U) /**< \brief (SDRAMC) Low-Power Register */
  #define REG_SDRAMC_IER       (*(__O  uint32_t*)0xFFFFEC14U) /**< \brief (SDRAMC) Interrupt Enable Register */
  #define REG_SDRAMC_IDR       (*(__O  uint32_t*)0xFFFFEC18U) /**< \brief (SDRAMC) Interrupt Disable Register */
  #define REG_SDRAMC_IMR       (*(__I  uint32_t*)0xFFFFEC1CU) /**< \brief (SDRAMC) Interrupt Mask Register */
  #define REG_SDRAMC_ISR       (*(__I  uint32_t*)0xFFFFEC20U) /**< \brief (SDRAMC) Interrupt Status Register */
  #define REG_SDRAMC_MDR       (*(__IO uint32_t*)0xFFFFEC24U) /**< \brief (SDRAMC) Memory Device Register */
  #define REG_SDRAMC_CFR1      (*(__IO uint32_t*)0xFFFFEC28U) /**< \brief (SDRAMC) Configuration Register 1 */
  #define REG_SDRAMC_OCMS      (*(__IO uint32_t*)0xFFFFEC2CU) /**< \brief (SDRAMC) OCMS Register */
  #define REG_SDRAMC_OCMS_KEY1 (*(__O  uint32_t*)0xFFFFEC30U) /**< \brief (SDRAMC) OCMS KEY1 Register */
  #define REG_SDRAMC_OCMS_KEY2 (*(__O  uint32_t*)0xFFFFEC34U) /**< \brief (SDRAMC) OCMS KEY2 Register */
  #define REG_SDRAMC_WPMR      (*(__IO uint32_t*)0xFFFFEC3CU) /**< \brief (SDRAMC) Write Protection Mode Register */
  #define REG_SDRAMC_WPSR      (*(__I  uint32_t*)0xFFFFEC40U) /**< \brief (SDRAMC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SDRAMC_INSTANCE_ */
