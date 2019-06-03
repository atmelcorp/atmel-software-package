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

#ifndef _SAM9X_SDMMC1_INSTANCE_
#define _SAM9X_SDMMC1_INSTANCE_

/* ========== Register definition for SDMMC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SDMMC1_SSAR                     (0x90000000U) /**< \brief (SDMMC1) SDMA System Address / Argument 2 Register */
  #define REG_SDMMC1_BSR                      (0x90000004U) /**< \brief (SDMMC1) Block Size Register */
  #define REG_SDMMC1_BCR                      (0x90000006U) /**< \brief (SDMMC1) Block Count Register */
  #define REG_SDMMC1_ARG1R                    (0x90000008U) /**< \brief (SDMMC1) Argument 1 Register */
  #define REG_SDMMC1_TMR                      (0x9000000CU) /**< \brief (SDMMC1) Transfer Mode Register */
  #define REG_SDMMC1_CR                       (0x9000000EU) /**< \brief (SDMMC1) Command Register */
  #define REG_SDMMC1_RR                       (0x90000010U) /**< \brief (SDMMC1) Response Register */
  #define REG_SDMMC1_BDPR                     (0x90000020U) /**< \brief (SDMMC1) Buffer Data Port Register */
  #define REG_SDMMC1_PSR                      (0x90000024U) /**< \brief (SDMMC1) Present State Register */
  #define REG_SDMMC1_HC1R                     (0x90000028U) /**< \brief (SDMMC1) Host Control 1 Register */
  #define REG_SDMMC1_PCR                      (0x90000029U) /**< \brief (SDMMC1) Power Control Register */
  #define REG_SDMMC1_BGCR                     (0x9000002AU) /**< \brief (SDMMC1) Block Gap Control Register */
  #define REG_SDMMC1_WCR                      (0x9000002BU) /**< \brief (SDMMC1) Wakeup Control Register */
  #define REG_SDMMC1_CCR                      (0x9000002CU) /**< \brief (SDMMC1) Clock Control Register */
  #define REG_SDMMC1_TCR                      (0x9000002EU) /**< \brief (SDMMC1) Timeout Control Register */
  #define REG_SDMMC1_SRR                      (0x9000002FU) /**< \brief (SDMMC1) Software Reset Register */
  #define REG_SDMMC1_NISTR                    (0x90000030U) /**< \brief (SDMMC1) Normal Interrupt Status Register */
  #define REG_SDMMC1_EISTR                    (0x90000032U) /**< \brief (SDMMC1) Error Interrupt Status Register */
  #define REG_SDMMC1_NISTER                   (0x90000034U) /**< \brief (SDMMC1) Normal Interrupt Status Enable Register */
  #define REG_SDMMC1_EISTER                   (0x90000036U) /**< \brief (SDMMC1) Error Interrupt Status Enable Register */
  #define REG_SDMMC1_NISIER                   (0x90000038U) /**< \brief (SDMMC1) Normal Interrupt Signal Enable Register */
  #define REG_SDMMC1_EISIER                   (0x9000003AU) /**< \brief (SDMMC1) Error Interrupt Signal Enable Register */
  #define REG_SDMMC1_ACESR                    (0x9000003CU) /**< \brief (SDMMC1) Auto CMD Error Status Register */
  #define REG_SDMMC1_HC2R                     (0x9000003EU) /**< \brief (SDMMC1) Host Control 2 Register */
  #define REG_SDMMC1_CA0R                     (0x90000040U) /**< \brief (SDMMC1) Capabilities 0 Register */
  #define REG_SDMMC1_CA1R                     (0x90000044U) /**< \brief (SDMMC1) Capabilities 1 Register */
  #define REG_SDMMC1_MCCAR                    (0x90000048U) /**< \brief (SDMMC1) Maximum Current Capabilities Register */
  #define REG_SDMMC1_FERACES                  (0x90000050U) /**< \brief (SDMMC1) Force Event Register for Auto CMD Error Status */
  #define REG_SDMMC1_FEREIS                   (0x90000052U) /**< \brief (SDMMC1) Force Event Register for Error Interrupt Status */
  #define REG_SDMMC1_AESR                     (0x90000054U) /**< \brief (SDMMC1) ADMA Error Status Register */
  #define REG_SDMMC1_ASAR0                    (0x90000058U) /**< \brief (SDMMC1) ADMA System Address Register 0 */
  #define REG_SDMMC1_PVR                      (0x90000060U) /**< \brief (SDMMC1) Preset Value Register 0 (for initialization) */
  #define REG_SDMMC1_SISR                     (0x900000FCU) /**< \brief (SDMMC1) Slot Interrupt Status Register */
  #define REG_SDMMC1_HCVR                     (0x900000FEU) /**< \brief (SDMMC1) Host Controller Version Register */
  #define REG_SDMMC1_APSR                     (0x90000200U) /**< \brief (SDMMC1) Additional Present State Register */
  #define REG_SDMMC1_MC1R                     (0x90000204U) /**< \brief (SDMMC1) e.MMC Control 1 Register */
  #define REG_SDMMC1_MC2R                     (0x90000205U) /**< \brief (SDMMC1) e.MMC Control 2 Register */
  #define REG_SDMMC1_ACR                      (0x90000208U) /**< \brief (SDMMC1) AHB Control Register */
  #define REG_SDMMC1_CC2R                     (0x9000020CU) /**< \brief (SDMMC1) Clock Control 2 Register */
  #define REG_SDMMC1_TUNSR                    (0x90000224U) /**< \brief (SDMMC1) Tuning Status Register */
  #define REG_SDMMC1_CACR                     (0x90000230U) /**< \brief (SDMMC1) Capabilities Control Register */
  #define REG_SDMMC1_DBGR                     (0x90000234U) /**< \brief (SDMMC1) Debug Register */
#else
  #define REG_SDMMC1_SSAR    (*(__IO uint32_t*)0x90000000U) /**< \brief (SDMMC1) SDMA System Address / Argument 2 Register */
  #define REG_SDMMC1_BSR     (*(__IO uint32_t*)0x90000004U) /**< \brief (SDMMC1) Block Size Register */
  #define REG_SDMMC1_BCR     (*(__IO uint32_t*)0x90000006U) /**< \brief (SDMMC1) Block Count Register */
  #define REG_SDMMC1_ARG1R   (*(__IO uint32_t*)0x90000008U) /**< \brief (SDMMC1) Argument 1 Register */
  #define REG_SDMMC1_TMR     (*(__IO uint32_t*)0x9000000CU) /**< \brief (SDMMC1) Transfer Mode Register */
  #define REG_SDMMC1_CR      (*(__IO uint32_t*)0x9000000EU) /**< \brief (SDMMC1) Command Register */
  #define REG_SDMMC1_RR      (*(__I  uint32_t*)0x90000010U) /**< \brief (SDMMC1) Response Register */
  #define REG_SDMMC1_BDPR    (*(__IO uint32_t*)0x90000020U) /**< \brief (SDMMC1) Buffer Data Port Register */
  #define REG_SDMMC1_PSR     (*(__I  uint32_t*)0x90000024U) /**< \brief (SDMMC1) Present State Register */
  #define REG_SDMMC1_HC1R    (*(__IO uint32_t*)0x90000028U) /**< \brief (SDMMC1) Host Control 1 Register */
  #define REG_SDMMC1_PCR     (*(__IO uint32_t*)0x90000029U) /**< \brief (SDMMC1) Power Control Register */
  #define REG_SDMMC1_BGCR    (*(__IO uint32_t*)0x9000002AU) /**< \brief (SDMMC1) Block Gap Control Register */
  #define REG_SDMMC1_WCR     (*(__IO uint32_t*)0x9000002BU) /**< \brief (SDMMC1) Wakeup Control Register */
  #define REG_SDMMC1_CCR     (*(__IO uint32_t*)0x9000002CU) /**< \brief (SDMMC1) Clock Control Register */
  #define REG_SDMMC1_TCR     (*(__IO uint32_t*)0x9000002EU) /**< \brief (SDMMC1) Timeout Control Register */
  #define REG_SDMMC1_SRR     (*(__IO uint32_t*)0x9000002FU) /**< \brief (SDMMC1) Software Reset Register */
  #define REG_SDMMC1_NISTR   (*(__IO uint32_t*)0x90000030U) /**< \brief (SDMMC1) Normal Interrupt Status Register */
  #define REG_SDMMC1_EISTR   (*(__IO uint32_t*)0x90000032U) /**< \brief (SDMMC1) Error Interrupt Status Register */
  #define REG_SDMMC1_NISTER  (*(__IO uint32_t*)0x90000034U) /**< \brief (SDMMC1) Normal Interrupt Status Enable Register */
  #define REG_SDMMC1_EISTER  (*(__IO uint32_t*)0x90000036U) /**< \brief (SDMMC1) Error Interrupt Status Enable Register */
  #define REG_SDMMC1_NISIER  (*(__IO uint32_t*)0x90000038U) /**< \brief (SDMMC1) Normal Interrupt Signal Enable Register */
  #define REG_SDMMC1_EISIER  (*(__IO uint32_t*)0x9000003AU) /**< \brief (SDMMC1) Error Interrupt Signal Enable Register */
  #define REG_SDMMC1_ACESR   (*(__I  uint32_t*)0x9000003CU) /**< \brief (SDMMC1) Auto CMD Error Status Register */
  #define REG_SDMMC1_HC2R    (*(__IO uint32_t*)0x9000003EU) /**< \brief (SDMMC1) Host Control 2 Register */
  #define REG_SDMMC1_CA0R    (*(__IO uint32_t*)0x90000040U) /**< \brief (SDMMC1) Capabilities 0 Register */
  #define REG_SDMMC1_CA1R    (*(__IO uint32_t*)0x90000044U) /**< \brief (SDMMC1) Capabilities 1 Register */
  #define REG_SDMMC1_MCCAR   (*(__IO uint32_t*)0x90000048U) /**< \brief (SDMMC1) Maximum Current Capabilities Register */
  #define REG_SDMMC1_FERACES (*(__O  uint32_t*)0x90000050U) /**< \brief (SDMMC1) Force Event Register for Auto CMD Error Status */
  #define REG_SDMMC1_FEREIS  (*(__O  uint32_t*)0x90000052U) /**< \brief (SDMMC1) Force Event Register for Error Interrupt Status */
  #define REG_SDMMC1_AESR    (*(__I  uint32_t*)0x90000054U) /**< \brief (SDMMC1) ADMA Error Status Register */
  #define REG_SDMMC1_ASAR0   (*(__IO uint32_t*)0x90000058U) /**< \brief (SDMMC1) ADMA System Address Register 0 */
  #define REG_SDMMC1_PVR     (*(__IO uint32_t*)0x90000060U) /**< \brief (SDMMC1) Preset Value Register 0 (for initialization) */
  #define REG_SDMMC1_SISR    (*(__I  uint32_t*)0x900000FCU) /**< \brief (SDMMC1) Slot Interrupt Status Register */
  #define REG_SDMMC1_HCVR    (*(__I  uint32_t*)0x900000FEU) /**< \brief (SDMMC1) Host Controller Version Register */
  #define REG_SDMMC1_APSR    (*(__I  uint32_t*)0x90000200U) /**< \brief (SDMMC1) Additional Present State Register */
  #define REG_SDMMC1_MC1R    (*(__IO uint32_t*)0x90000204U) /**< \brief (SDMMC1) e.MMC Control 1 Register */
  #define REG_SDMMC1_MC2R    (*(__O  uint32_t*)0x90000205U) /**< \brief (SDMMC1) e.MMC Control 2 Register */
  #define REG_SDMMC1_ACR     (*(__IO uint32_t*)0x90000208U) /**< \brief (SDMMC1) AHB Control Register */
  #define REG_SDMMC1_CC2R    (*(__IO uint32_t*)0x9000020CU) /**< \brief (SDMMC1) Clock Control 2 Register */
  #define REG_SDMMC1_TUNSR   (*(__I  uint32_t*)0x90000224U) /**< \brief (SDMMC1) Tuning Status Register */
  #define REG_SDMMC1_CACR    (*(__IO uint32_t*)0x90000230U) /**< \brief (SDMMC1) Capabilities Control Register */
  #define REG_SDMMC1_DBGR    (*(__IO uint32_t*)0x90000234U) /**< \brief (SDMMC1) Debug Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SDMMC1_INSTANCE_ */
