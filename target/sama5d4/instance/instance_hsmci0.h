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

#ifndef _SAMA5D4_HSMCI0_INSTANCE_
#define _SAMA5D4_HSMCI0_INSTANCE_

/* ========== Register definition for HSMCI0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMCI0_CR                     (0xF8000000U) /**< \brief (HSMCI0) Control Register */
  #define REG_HSMCI0_MR                     (0xF8000004U) /**< \brief (HSMCI0) Mode Register */
  #define REG_HSMCI0_DTOR                   (0xF8000008U) /**< \brief (HSMCI0) Data Timeout Register */
  #define REG_HSMCI0_SDCR                   (0xF800000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
  #define REG_HSMCI0_ARGR                   (0xF8000010U) /**< \brief (HSMCI0) Argument Register */
  #define REG_HSMCI0_CMDR                   (0xF8000014U) /**< \brief (HSMCI0) Command Register */
  #define REG_HSMCI0_BLKR                   (0xF8000018U) /**< \brief (HSMCI0) Block Register */
  #define REG_HSMCI0_CSTOR                  (0xF800001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
  #define REG_HSMCI0_RSPR                   (0xF8000020U) /**< \brief (HSMCI0) Response Register */
  #define REG_HSMCI0_RDR                    (0xF8000030U) /**< \brief (HSMCI0) Receive Data Register */
  #define REG_HSMCI0_TDR                    (0xF8000034U) /**< \brief (HSMCI0) Transmit Data Register */
  #define REG_HSMCI0_SR                     (0xF8000040U) /**< \brief (HSMCI0) Status Register */
  #define REG_HSMCI0_IER                    (0xF8000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
  #define REG_HSMCI0_IDR                    (0xF8000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
  #define REG_HSMCI0_IMR                    (0xF800004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
  #define REG_HSMCI0_DMA                    (0xF8000050U) /**< \brief (HSMCI0) DMA Configuration Register */
  #define REG_HSMCI0_CFG                    (0xF8000054U) /**< \brief (HSMCI0) Configuration Register */
  #define REG_HSMCI0_WPMR                   (0xF80000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
  #define REG_HSMCI0_WPSR                   (0xF80000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
  #define REG_HSMCI0_FIFO                   (0xF8000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#else
  #define REG_HSMCI0_CR    (*(__O  uint32_t*)0xF8000000U) /**< \brief (HSMCI0) Control Register */
  #define REG_HSMCI0_MR    (*(__IO uint32_t*)0xF8000004U) /**< \brief (HSMCI0) Mode Register */
  #define REG_HSMCI0_DTOR  (*(__IO uint32_t*)0xF8000008U) /**< \brief (HSMCI0) Data Timeout Register */
  #define REG_HSMCI0_SDCR  (*(__IO uint32_t*)0xF800000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
  #define REG_HSMCI0_ARGR  (*(__IO uint32_t*)0xF8000010U) /**< \brief (HSMCI0) Argument Register */
  #define REG_HSMCI0_CMDR  (*(__O  uint32_t*)0xF8000014U) /**< \brief (HSMCI0) Command Register */
  #define REG_HSMCI0_BLKR  (*(__IO uint32_t*)0xF8000018U) /**< \brief (HSMCI0) Block Register */
  #define REG_HSMCI0_CSTOR (*(__IO uint32_t*)0xF800001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
  #define REG_HSMCI0_RSPR  (*(__I  uint32_t*)0xF8000020U) /**< \brief (HSMCI0) Response Register */
  #define REG_HSMCI0_RDR   (*(__I  uint32_t*)0xF8000030U) /**< \brief (HSMCI0) Receive Data Register */
  #define REG_HSMCI0_TDR   (*(__O  uint32_t*)0xF8000034U) /**< \brief (HSMCI0) Transmit Data Register */
  #define REG_HSMCI0_SR    (*(__I  uint32_t*)0xF8000040U) /**< \brief (HSMCI0) Status Register */
  #define REG_HSMCI0_IER   (*(__O  uint32_t*)0xF8000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
  #define REG_HSMCI0_IDR   (*(__O  uint32_t*)0xF8000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
  #define REG_HSMCI0_IMR   (*(__I  uint32_t*)0xF800004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
  #define REG_HSMCI0_DMA   (*(__IO uint32_t*)0xF8000050U) /**< \brief (HSMCI0) DMA Configuration Register */
  #define REG_HSMCI0_CFG   (*(__IO uint32_t*)0xF8000054U) /**< \brief (HSMCI0) Configuration Register */
  #define REG_HSMCI0_WPMR  (*(__IO uint32_t*)0xF80000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
  #define REG_HSMCI0_WPSR  (*(__I  uint32_t*)0xF80000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
  #define REG_HSMCI0_FIFO  (*(__IO uint32_t*)0xF8000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_HSMCI0_INSTANCE_ */
