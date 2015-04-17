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

#ifndef _SAMA5D4_USART2_INSTANCE_
#define _SAMA5D4_USART2_INSTANCE_

/* ========== Register definition for USART2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART2_CR                    (0xFC008000U) /**< \brief (USART2) Control Register */
  #define REG_USART2_MR                    (0xFC008004U) /**< \brief (USART2) Mode Register */
  #define REG_USART2_IER                   (0xFC008008U) /**< \brief (USART2) Interrupt Enable Register */
  #define REG_USART2_IDR                   (0xFC00800CU) /**< \brief (USART2) Interrupt Disable Register */
  #define REG_USART2_IMR                   (0xFC008010U) /**< \brief (USART2) Interrupt Mask Register */
  #define REG_USART2_CSR                   (0xFC008014U) /**< \brief (USART2) Channel Status Register */
  #define REG_USART2_RHR                   (0xFC008018U) /**< \brief (USART2) Receive Holding Register */
  #define REG_USART2_THR                   (0xFC00801CU) /**< \brief (USART2) Transmit Holding Register */
  #define REG_USART2_BRGR                  (0xFC008020U) /**< \brief (USART2) Baud Rate Generator Register */
  #define REG_USART2_RTOR                  (0xFC008024U) /**< \brief (USART2) Receiver Time-out Register */
  #define REG_USART2_TTGR                  (0xFC008028U) /**< \brief (USART2) Transmitter Timeguard Register */
  #define REG_USART2_FIDI                  (0xFC008040U) /**< \brief (USART2) FI DI Ratio Register */
  #define REG_USART2_NER                   (0xFC008044U) /**< \brief (USART2) Number of Errors Register */
  #define REG_USART2_IF                    (0xFC00804CU) /**< \brief (USART2) IrDA Filter Register */
  #define REG_USART2_MAN                   (0xFC008050U) /**< \brief (USART2) Manchester Configuration Register */
  #define REG_USART2_WPMR                  (0xFC0080E4U) /**< \brief (USART2) Write Protection Mode Register */
  #define REG_USART2_WPSR                  (0xFC0080E8U) /**< \brief (USART2) Write Protection Status Register */
#else
  #define REG_USART2_CR   (*(__O  uint32_t*)0xFC008000U) /**< \brief (USART2) Control Register */
  #define REG_USART2_MR   (*(__IO uint32_t*)0xFC008004U) /**< \brief (USART2) Mode Register */
  #define REG_USART2_IER  (*(__O  uint32_t*)0xFC008008U) /**< \brief (USART2) Interrupt Enable Register */
  #define REG_USART2_IDR  (*(__O  uint32_t*)0xFC00800CU) /**< \brief (USART2) Interrupt Disable Register */
  #define REG_USART2_IMR  (*(__I  uint32_t*)0xFC008010U) /**< \brief (USART2) Interrupt Mask Register */
  #define REG_USART2_CSR  (*(__I  uint32_t*)0xFC008014U) /**< \brief (USART2) Channel Status Register */
  #define REG_USART2_RHR  (*(__I  uint32_t*)0xFC008018U) /**< \brief (USART2) Receive Holding Register */
  #define REG_USART2_THR  (*(__O  uint32_t*)0xFC00801CU) /**< \brief (USART2) Transmit Holding Register */
  #define REG_USART2_BRGR (*(__IO uint32_t*)0xFC008020U) /**< \brief (USART2) Baud Rate Generator Register */
  #define REG_USART2_RTOR (*(__IO uint32_t*)0xFC008024U) /**< \brief (USART2) Receiver Time-out Register */
  #define REG_USART2_TTGR (*(__IO uint32_t*)0xFC008028U) /**< \brief (USART2) Transmitter Timeguard Register */
  #define REG_USART2_FIDI (*(__IO uint32_t*)0xFC008040U) /**< \brief (USART2) FI DI Ratio Register */
  #define REG_USART2_NER  (*(__I  uint32_t*)0xFC008044U) /**< \brief (USART2) Number of Errors Register */
  #define REG_USART2_IF   (*(__IO uint32_t*)0xFC00804CU) /**< \brief (USART2) IrDA Filter Register */
  #define REG_USART2_MAN  (*(__IO uint32_t*)0xFC008050U) /**< \brief (USART2) Manchester Configuration Register */
  #define REG_USART2_WPMR (*(__IO uint32_t*)0xFC0080E4U) /**< \brief (USART2) Write Protection Mode Register */
  #define REG_USART2_WPSR (*(__I  uint32_t*)0xFC0080E8U) /**< \brief (USART2) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_USART2_INSTANCE_ */
