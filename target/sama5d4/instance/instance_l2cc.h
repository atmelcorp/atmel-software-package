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

#ifndef _SAMA5D4_L2CC_INSTANCE_
#define _SAMA5D4_L2CC_INSTANCE_

/* ========== Register definition for L2CC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_L2CC_IDR                     (0x00A00000U) /**< \brief (L2CC) Cache ID Register */
#define REG_L2CC_TYPR                    (0x00A00004U) /**< \brief (L2CC) Cache Type Register */
#define REG_L2CC_CR                      (0x00A00100U) /**< \brief (L2CC) Control Register */
#define REG_L2CC_ACR                     (0x00A00104U) /**< \brief (L2CC) Auxiliary Control Register */
#define REG_L2CC_TRCR                    (0x00A00108U) /**< \brief (L2CC) Tag RAM Control Register */
#define REG_L2CC_DRCR                    (0x00A0010CU) /**< \brief (L2CC) Data RAM Control Register */
#define REG_L2CC_ECR                     (0x00A00200U) /**< \brief (L2CC) Event Counter Control Register */
#define REG_L2CC_ECFGR1                  (0x00A00204U) /**< \brief (L2CC) Event Counter 1 Configuration Register */
#define REG_L2CC_ECFGR0                  (0x00A00208U) /**< \brief (L2CC) Event Counter 0 Configuration Register */
#define REG_L2CC_EVR1                    (0x00A0020CU) /**< \brief (L2CC) Event Counter 1 Value Register */
#define REG_L2CC_EVR0                    (0x00A00210U) /**< \brief (L2CC) Event Counter 0 Value Register */
#define REG_L2CC_IMR                     (0x00A00214U) /**< \brief (L2CC) Interrupt Mask Register */
#define REG_L2CC_MISR                    (0x00A00218U) /**< \brief (L2CC) Masked Interrupt Status Register */
#define REG_L2CC_RISR                    (0x00A0021CU) /**< \brief (L2CC) Raw Interrupt Status Register */
#define REG_L2CC_ICR                     (0x00A00220U) /**< \brief (L2CC) Interrupt Clear Register */
#define REG_L2CC_CSR                     (0x00A00730U) /**< \brief (L2CC) Cache Synchronization Register */
#define REG_L2CC_IPALR                   (0x00A00770U) /**< \brief (L2CC) Invalidate Physical Address Line Register */
#define REG_L2CC_IWR                     (0x00A0077CU) /**< \brief (L2CC) Invalidate Way Register */
#define REG_L2CC_CPALR                   (0x00A007B0U) /**< \brief (L2CC) Clean Physical Address Line Register */
#define REG_L2CC_CIR                     (0x00A007B8U) /**< \brief (L2CC) Clean Index Register */
#define REG_L2CC_CWR                     (0x00A007BCU) /**< \brief (L2CC) Clean Way Register */
#define REG_L2CC_CIPALR                  (0x00A007F0U) /**< \brief (L2CC) Clean Invalidate Physical Address Line Register */
#define REG_L2CC_CIIR                    (0x00A007F8U) /**< \brief (L2CC) Clean Invalidate Index Register */
#define REG_L2CC_CIWR                    (0x00A007FCU) /**< \brief (L2CC) Clean Invalidate Way Register */
#define REG_L2CC_DLKR                    (0x00A00900U) /**< \brief (L2CC) Data Lockdown Register */
#define REG_L2CC_ILKR                    (0x00A00904U) /**< \brief (L2CC) Instruction Lockdown Register */
#define REG_L2CC_DCR                     (0x00A00F40U) /**< \brief (L2CC) Debug Control Register */
#define REG_L2CC_PCR                     (0x00A00F60U) /**< \brief (L2CC) Prefetch Control Register */
#define REG_L2CC_POWCR                   (0x00A00F80U) /**< \brief (L2CC) Power Control Register */
#else
#define REG_L2CC_IDR    (*(__I  uint32_t*)0x00A00000U) /**< \brief (L2CC) Cache ID Register */
#define REG_L2CC_TYPR   (*(__I  uint32_t*)0x00A00004U) /**< \brief (L2CC) Cache Type Register */
#define REG_L2CC_CR     (*(__IO uint32_t*)0x00A00100U) /**< \brief (L2CC) Control Register */
#define REG_L2CC_ACR    (*(__IO uint32_t*)0x00A00104U) /**< \brief (L2CC) Auxiliary Control Register */
#define REG_L2CC_TRCR   (*(__IO uint32_t*)0x00A00108U) /**< \brief (L2CC) Tag RAM Control Register */
#define REG_L2CC_DRCR   (*(__IO uint32_t*)0x00A0010CU) /**< \brief (L2CC) Data RAM Control Register */
#define REG_L2CC_ECR    (*(__IO uint32_t*)0x00A00200U) /**< \brief (L2CC) Event Counter Control Register */
#define REG_L2CC_ECFGR1 (*(__IO uint32_t*)0x00A00204U) /**< \brief (L2CC) Event Counter 1 Configuration Register */
#define REG_L2CC_ECFGR0 (*(__IO uint32_t*)0x00A00208U) /**< \brief (L2CC) Event Counter 0 Configuration Register */
#define REG_L2CC_EVR1   (*(__IO uint32_t*)0x00A0020CU) /**< \brief (L2CC) Event Counter 1 Value Register */
#define REG_L2CC_EVR0   (*(__IO uint32_t*)0x00A00210U) /**< \brief (L2CC) Event Counter 0 Value Register */
#define REG_L2CC_IMR    (*(__IO uint32_t*)0x00A00214U) /**< \brief (L2CC) Interrupt Mask Register */
#define REG_L2CC_MISR   (*(__I  uint32_t*)0x00A00218U) /**< \brief (L2CC) Masked Interrupt Status Register */
#define REG_L2CC_RISR   (*(__I  uint32_t*)0x00A0021CU) /**< \brief (L2CC) Raw Interrupt Status Register */
#define REG_L2CC_ICR    (*(__IO uint32_t*)0x00A00220U) /**< \brief (L2CC) Interrupt Clear Register */
#define REG_L2CC_CSR    (*(__IO uint32_t*)0x00A00730U) /**< \brief (L2CC) Cache Synchronization Register */
#define REG_L2CC_IPALR  (*(__IO uint32_t*)0x00A00770U) /**< \brief (L2CC) Invalidate Physical Address Line Register */
#define REG_L2CC_IWR    (*(__IO uint32_t*)0x00A0077CU) /**< \brief (L2CC) Invalidate Way Register */
#define REG_L2CC_CPALR  (*(__IO uint32_t*)0x00A007B0U) /**< \brief (L2CC) Clean Physical Address Line Register */
#define REG_L2CC_CIR    (*(__IO uint32_t*)0x00A007B8U) /**< \brief (L2CC) Clean Index Register */
#define REG_L2CC_CWR    (*(__IO uint32_t*)0x00A007BCU) /**< \brief (L2CC) Clean Way Register */
#define REG_L2CC_CIPALR (*(__IO uint32_t*)0x00A007F0U) /**< \brief (L2CC) Clean Invalidate Physical Address Line Register */
#define REG_L2CC_CIIR   (*(__IO uint32_t*)0x00A007F8U) /**< \brief (L2CC) Clean Invalidate Index Register */
#define REG_L2CC_CIWR   (*(__IO uint32_t*)0x00A007FCU) /**< \brief (L2CC) Clean Invalidate Way Register */
#define REG_L2CC_DLKR   (*(__IO uint32_t*)0x00A00900U) /**< \brief (L2CC) Data Lockdown Register */
#define REG_L2CC_ILKR   (*(__IO uint32_t*)0x00A00904U) /**< \brief (L2CC) Instruction Lockdown Register */
#define REG_L2CC_DCR    (*(__IO uint32_t*)0x00A00F40U) /**< \brief (L2CC) Debug Control Register */
#define REG_L2CC_PCR    (*(__IO uint32_t*)0x00A00F60U) /**< \brief (L2CC) Prefetch Control Register */
#define REG_L2CC_POWCR  (*(__IO uint32_t*)0x00A00F80U) /**< \brief (L2CC) Power Control Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_L2CC_INSTANCE_ */
