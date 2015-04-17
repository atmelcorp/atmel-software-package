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

#ifndef _SAMA5D4_USART1_INSTANCE_
#define _SAMA5D4_USART1_INSTANCE_

/* ========== Register definition for USART1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART1_CR                    (0xF8030000U) /**< \brief (USART1) Control Register */
  #define REG_USART1_MR                    (0xF8030004U) /**< \brief (USART1) Mode Register */
  #define REG_USART1_IER                   (0xF8030008U) /**< \brief (USART1) Interrupt Enable Register */
  #define REG_USART1_IDR                   (0xF803000CU) /**< \brief (USART1) Interrupt Disable Register */
  #define REG_USART1_IMR                   (0xF8030010U) /**< \brief (USART1) Interrupt Mask Register */
  #define REG_USART1_CSR                   (0xF8030014U) /**< \brief (USART1) Channel Status Register */
  #define REG_USART1_RHR                   (0xF8030018U) /**< \brief (USART1) Receive Holding Register */
  #define REG_USART1_THR                   (0xF803001CU) /**< \brief (USART1) Transmit Holding Register */
  #define REG_USART1_BRGR                  (0xF8030020U) /**< \brief (USART1) Baud Rate Generator Register */
  #define REG_USART1_RTOR                  (0xF8030024U) /**< \brief (USART1) Receiver Time-out Register */
  #define REG_USART1_TTGR                  (0xF8030028U) /**< \brief (USART1) Transmitter Timeguard Register */
  #define REG_USART1_FIDI                  (0xF8030040U) /**< \brief (USART1) FI DI Ratio Register */
  #define REG_USART1_NER                   (0xF8030044U) /**< \brief (USART1) Number of Errors Register */
  #define REG_USART1_IF                    (0xF803004CU) /**< \brief (USART1) IrDA Filter Register */
  #define REG_USART1_MAN                   (0xF8030050U) /**< \brief (USART1) Manchester Configuration Register */
  #define REG_USART1_WPMR                  (0xF80300E4U) /**< \brief (USART1) Write Protection Mode Register */
  #define REG_USART1_WPSR                  (0xF80300E8U) /**< \brief (USART1) Write Protection Status Register */
#else
  #define REG_USART1_CR   (*(__O  uint32_t*)0xF8030000U) /**< \brief (USART1) Control Register */
  #define REG_USART1_MR   (*(__IO uint32_t*)0xF8030004U) /**< \brief (USART1) Mode Register */
  #define REG_USART1_IER  (*(__O  uint32_t*)0xF8030008U) /**< \brief (USART1) Interrupt Enable Register */
  #define REG_USART1_IDR  (*(__O  uint32_t*)0xF803000CU) /**< \brief (USART1) Interrupt Disable Register */
  #define REG_USART1_IMR  (*(__I  uint32_t*)0xF8030010U) /**< \brief (USART1) Interrupt Mask Register */
  #define REG_USART1_CSR  (*(__I  uint32_t*)0xF8030014U) /**< \brief (USART1) Channel Status Register */
  #define REG_USART1_RHR  (*(__I  uint32_t*)0xF8030018U) /**< \brief (USART1) Receive Holding Register */
  #define REG_USART1_THR  (*(__O  uint32_t*)0xF803001CU) /**< \brief (USART1) Transmit Holding Register */
  #define REG_USART1_BRGR (*(__IO uint32_t*)0xF8030020U) /**< \brief (USART1) Baud Rate Generator Register */
  #define REG_USART1_RTOR (*(__IO uint32_t*)0xF8030024U) /**< \brief (USART1) Receiver Time-out Register */
  #define REG_USART1_TTGR (*(__IO uint32_t*)0xF8030028U) /**< \brief (USART1) Transmitter Timeguard Register */
  #define REG_USART1_FIDI (*(__IO uint32_t*)0xF8030040U) /**< \brief (USART1) FI DI Ratio Register */
  #define REG_USART1_NER  (*(__I  uint32_t*)0xF8030044U) /**< \brief (USART1) Number of Errors Register */
  #define REG_USART1_IF   (*(__IO uint32_t*)0xF803004CU) /**< \brief (USART1) IrDA Filter Register */
  #define REG_USART1_MAN  (*(__IO uint32_t*)0xF8030050U) /**< \brief (USART1) Manchester Configuration Register */
  #define REG_USART1_WPMR (*(__IO uint32_t*)0xF80300E4U) /**< \brief (USART1) Write Protection Mode Register */
  #define REG_USART1_WPSR (*(__I  uint32_t*)0xF80300E8U) /**< \brief (USART1) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_USART1_INSTANCE_ */
