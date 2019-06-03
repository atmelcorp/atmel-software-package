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

#ifndef _SAM9X_SDMMC0_INSTANCE_
#define _SAM9X_SDMMC0_INSTANCE_

/* ========== Register definition for SDMMC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SDMMC0_SSAR                     (0x80000000U) /**< \brief (SDMMC0) SDMA System Address / Argument 2 Register */
  #define REG_SDMMC0_BSR                      (0x80000004U) /**< \brief (SDMMC0) Block Size Register */
  #define REG_SDMMC0_BCR                      (0x80000006U) /**< \brief (SDMMC0) Block Count Register */
  #define REG_SDMMC0_ARG1R                    (0x80000008U) /**< \brief (SDMMC0) Argument 1 Register */
  #define REG_SDMMC0_TMR                      (0x8000000CU) /**< \brief (SDMMC0) Transfer Mode Register */
  #define REG_SDMMC0_CR                       (0x8000000EU) /**< \brief (SDMMC0) Command Register */
  #define REG_SDMMC0_RR                       (0x80000010U) /**< \brief (SDMMC0) Response Register */
  #define REG_SDMMC0_BDPR                     (0x80000020U) /**< \brief (SDMMC0) Buffer Data Port Register */
  #define REG_SDMMC0_PSR                      (0x80000024U) /**< \brief (SDMMC0) Present State Register */
  #define REG_SDMMC0_HC1R                     (0x80000028U) /**< \brief (SDMMC0) Host Control 1 Register */
  #define REG_SDMMC0_PCR                      (0x80000029U) /**< \brief (SDMMC0) Power Control Register */
  #define REG_SDMMC0_BGCR                     (0x8000002AU) /**< \brief (SDMMC0) Block Gap Control Register */
  #define REG_SDMMC0_WCR                      (0x8000002BU) /**< \brief (SDMMC0) Wakeup Control Register */
  #define REG_SDMMC0_CCR                      (0x8000002CU) /**< \brief (SDMMC0) Clock Control Register */
  #define REG_SDMMC0_TCR                      (0x8000002EU) /**< \brief (SDMMC0) Timeout Control Register */
  #define REG_SDMMC0_SRR                      (0x8000002FU) /**< \brief (SDMMC0) Software Reset Register */
  #define REG_SDMMC0_NISTR                    (0x80000030U) /**< \brief (SDMMC0) Normal Interrupt Status Register */
  #define REG_SDMMC0_EISTR                    (0x80000032U) /**< \brief (SDMMC0) Error Interrupt Status Register */
  #define REG_SDMMC0_NISTER                   (0x80000034U) /**< \brief (SDMMC0) Normal Interrupt Status Enable Register */
  #define REG_SDMMC0_EISTER                   (0x80000036U) /**< \brief (SDMMC0) Error Interrupt Status Enable Register */
  #define REG_SDMMC0_NISIER                   (0x80000038U) /**< \brief (SDMMC0) Normal Interrupt Signal Enable Register */
  #define REG_SDMMC0_EISIER                   (0x8000003AU) /**< \brief (SDMMC0) Error Interrupt Signal Enable Register */
  #define REG_SDMMC0_ACESR                    (0x8000003CU) /**< \brief (SDMMC0) Auto CMD Error Status Register */
  #define REG_SDMMC0_HC2R                     (0x8000003EU) /**< \brief (SDMMC0) Host Control 2 Register */
  #define REG_SDMMC0_CA0R                     (0x80000040U) /**< \brief (SDMMC0) Capabilities 0 Register */
  #define REG_SDMMC0_CA1R                     (0x80000044U) /**< \brief (SDMMC0) Capabilities 1 Register */
  #define REG_SDMMC0_MCCAR                    (0x80000048U) /**< \brief (SDMMC0) Maximum Current Capabilities Register */
  #define REG_SDMMC0_FERACES                  (0x80000050U) /**< \brief (SDMMC0) Force Event Register for Auto CMD Error Status */
  #define REG_SDMMC0_FEREIS                   (0x80000052U) /**< \brief (SDMMC0) Force Event Register for Error Interrupt Status */
  #define REG_SDMMC0_AESR                     (0x80000054U) /**< \brief (SDMMC0) ADMA Error Status Register */
  #define REG_SDMMC0_ASAR0                    (0x80000058U) /**< \brief (SDMMC0) ADMA System Address Register 0 */
  #define REG_SDMMC0_PVR                      (0x80000060U) /**< \brief (SDMMC0) Preset Value Register 0 (for initialization) */
  #define REG_SDMMC0_SISR                     (0x800000FCU) /**< \brief (SDMMC0) Slot Interrupt Status Register */
  #define REG_SDMMC0_HCVR                     (0x800000FEU) /**< \brief (SDMMC0) Host Controller Version Register */
  #define REG_SDMMC0_APSR                     (0x80000200U) /**< \brief (SDMMC0) Additional Present State Register */
  #define REG_SDMMC0_MC1R                     (0x80000204U) /**< \brief (SDMMC0) e.MMC Control 1 Register */
  #define REG_SDMMC0_MC2R                     (0x80000205U) /**< \brief (SDMMC0) e.MMC Control 2 Register */
  #define REG_SDMMC0_ACR                      (0x80000208U) /**< \brief (SDMMC0) AHB Control Register */
  #define REG_SDMMC0_CC2R                     (0x8000020CU) /**< \brief (SDMMC0) Clock Control 2 Register */
  #define REG_SDMMC0_TUNSR                    (0x80000224U) /**< \brief (SDMMC0) Tuning Status Register */
  #define REG_SDMMC0_CACR                     (0x80000230U) /**< \brief (SDMMC0) Capabilities Control Register */
  #define REG_SDMMC0_DBGR                     (0x80000234U) /**< \brief (SDMMC0) Debug Register */
#else
  #define REG_SDMMC0_SSAR    (*(__IO uint32_t*)0x80000000U) /**< \brief (SDMMC0) SDMA System Address / Argument 2 Register */
  #define REG_SDMMC0_BSR     (*(__IO uint32_t*)0x80000004U) /**< \brief (SDMMC0) Block Size Register */
  #define REG_SDMMC0_BCR     (*(__IO uint32_t*)0x80000006U) /**< \brief (SDMMC0) Block Count Register */
  #define REG_SDMMC0_ARG1R   (*(__IO uint32_t*)0x80000008U) /**< \brief (SDMMC0) Argument 1 Register */
  #define REG_SDMMC0_TMR     (*(__IO uint32_t*)0x8000000CU) /**< \brief (SDMMC0) Transfer Mode Register */
  #define REG_SDMMC0_CR      (*(__IO uint32_t*)0x8000000EU) /**< \brief (SDMMC0) Command Register */
  #define REG_SDMMC0_RR      (*(__I  uint32_t*)0x80000010U) /**< \brief (SDMMC0) Response Register */
  #define REG_SDMMC0_BDPR    (*(__IO uint32_t*)0x80000020U) /**< \brief (SDMMC0) Buffer Data Port Register */
  #define REG_SDMMC0_PSR     (*(__I  uint32_t*)0x80000024U) /**< \brief (SDMMC0) Present State Register */
  #define REG_SDMMC0_HC1R    (*(__IO uint32_t*)0x80000028U) /**< \brief (SDMMC0) Host Control 1 Register */
  #define REG_SDMMC0_PCR     (*(__IO uint32_t*)0x80000029U) /**< \brief (SDMMC0) Power Control Register */
  #define REG_SDMMC0_BGCR    (*(__IO uint32_t*)0x8000002AU) /**< \brief (SDMMC0) Block Gap Control Register */
  #define REG_SDMMC0_WCR     (*(__IO uint32_t*)0x8000002BU) /**< \brief (SDMMC0) Wakeup Control Register */
  #define REG_SDMMC0_CCR     (*(__IO uint32_t*)0x8000002CU) /**< \brief (SDMMC0) Clock Control Register */
  #define REG_SDMMC0_TCR     (*(__IO uint32_t*)0x8000002EU) /**< \brief (SDMMC0) Timeout Control Register */
  #define REG_SDMMC0_SRR     (*(__IO uint32_t*)0x8000002FU) /**< \brief (SDMMC0) Software Reset Register */
  #define REG_SDMMC0_NISTR   (*(__IO uint32_t*)0x80000030U) /**< \brief (SDMMC0) Normal Interrupt Status Register */
  #define REG_SDMMC0_EISTR   (*(__IO uint32_t*)0x80000032U) /**< \brief (SDMMC0) Error Interrupt Status Register */
  #define REG_SDMMC0_NISTER  (*(__IO uint32_t*)0x80000034U) /**< \brief (SDMMC0) Normal Interrupt Status Enable Register */
  #define REG_SDMMC0_EISTER  (*(__IO uint32_t*)0x80000036U) /**< \brief (SDMMC0) Error Interrupt Status Enable Register */
  #define REG_SDMMC0_NISIER  (*(__IO uint32_t*)0x80000038U) /**< \brief (SDMMC0) Normal Interrupt Signal Enable Register */
  #define REG_SDMMC0_EISIER  (*(__IO uint32_t*)0x8000003AU) /**< \brief (SDMMC0) Error Interrupt Signal Enable Register */
  #define REG_SDMMC0_ACESR   (*(__I  uint32_t*)0x8000003CU) /**< \brief (SDMMC0) Auto CMD Error Status Register */
  #define REG_SDMMC0_HC2R    (*(__IO uint32_t*)0x8000003EU) /**< \brief (SDMMC0) Host Control 2 Register */
  #define REG_SDMMC0_CA0R    (*(__IO uint32_t*)0x80000040U) /**< \brief (SDMMC0) Capabilities 0 Register */
  #define REG_SDMMC0_CA1R    (*(__IO uint32_t*)0x80000044U) /**< \brief (SDMMC0) Capabilities 1 Register */
  #define REG_SDMMC0_MCCAR   (*(__IO uint32_t*)0x80000048U) /**< \brief (SDMMC0) Maximum Current Capabilities Register */
  #define REG_SDMMC0_FERACES (*(__O  uint32_t*)0x80000050U) /**< \brief (SDMMC0) Force Event Register for Auto CMD Error Status */
  #define REG_SDMMC0_FEREIS  (*(__O  uint32_t*)0x80000052U) /**< \brief (SDMMC0) Force Event Register for Error Interrupt Status */
  #define REG_SDMMC0_AESR    (*(__I  uint32_t*)0x80000054U) /**< \brief (SDMMC0) ADMA Error Status Register */
  #define REG_SDMMC0_ASAR0   (*(__IO uint32_t*)0x80000058U) /**< \brief (SDMMC0) ADMA System Address Register 0 */
  #define REG_SDMMC0_PVR     (*(__IO uint32_t*)0x80000060U) /**< \brief (SDMMC0) Preset Value Register 0 (for initialization) */
  #define REG_SDMMC0_SISR    (*(__I  uint32_t*)0x800000FCU) /**< \brief (SDMMC0) Slot Interrupt Status Register */
  #define REG_SDMMC0_HCVR    (*(__I  uint32_t*)0x800000FEU) /**< \brief (SDMMC0) Host Controller Version Register */
  #define REG_SDMMC0_APSR    (*(__I  uint32_t*)0x80000200U) /**< \brief (SDMMC0) Additional Present State Register */
  #define REG_SDMMC0_MC1R    (*(__IO uint32_t*)0x80000204U) /**< \brief (SDMMC0) e.MMC Control 1 Register */
  #define REG_SDMMC0_MC2R    (*(__O  uint32_t*)0x80000205U) /**< \brief (SDMMC0) e.MMC Control 2 Register */
  #define REG_SDMMC0_ACR     (*(__IO uint32_t*)0x80000208U) /**< \brief (SDMMC0) AHB Control Register */
  #define REG_SDMMC0_CC2R    (*(__IO uint32_t*)0x8000020CU) /**< \brief (SDMMC0) Clock Control 2 Register */
  #define REG_SDMMC0_TUNSR   (*(__I  uint32_t*)0x80000224U) /**< \brief (SDMMC0) Tuning Status Register */
  #define REG_SDMMC0_CACR    (*(__IO uint32_t*)0x80000230U) /**< \brief (SDMMC0) Capabilities Control Register */
  #define REG_SDMMC0_DBGR    (*(__IO uint32_t*)0x80000234U) /**< \brief (SDMMC0) Debug Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SDMMC0_INSTANCE_ */
