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

#ifndef _SAMA5D4_USART3_INSTANCE_
#define _SAMA5D4_USART3_INSTANCE_

/* ========== Register definition for USART3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART3_CR                    (0xFC00C000U) /**< \brief (USART3) Control Register */
  #define REG_USART3_MR                    (0xFC00C004U) /**< \brief (USART3) Mode Register */
  #define REG_USART3_IER                   (0xFC00C008U) /**< \brief (USART3) Interrupt Enable Register */
  #define REG_USART3_IDR                   (0xFC00C00CU) /**< \brief (USART3) Interrupt Disable Register */
  #define REG_USART3_IMR                   (0xFC00C010U) /**< \brief (USART3) Interrupt Mask Register */
  #define REG_USART3_CSR                   (0xFC00C014U) /**< \brief (USART3) Channel Status Register */
  #define REG_USART3_RHR                   (0xFC00C018U) /**< \brief (USART3) Receive Holding Register */
  #define REG_USART3_THR                   (0xFC00C01CU) /**< \brief (USART3) Transmit Holding Register */
  #define REG_USART3_BRGR                  (0xFC00C020U) /**< \brief (USART3) Baud Rate Generator Register */
  #define REG_USART3_RTOR                  (0xFC00C024U) /**< \brief (USART3) Receiver Time-out Register */
  #define REG_USART3_TTGR                  (0xFC00C028U) /**< \brief (USART3) Transmitter Timeguard Register */
  #define REG_USART3_FIDI                  (0xFC00C040U) /**< \brief (USART3) FI DI Ratio Register */
  #define REG_USART3_NER                   (0xFC00C044U) /**< \brief (USART3) Number of Errors Register */
  #define REG_USART3_IF                    (0xFC00C04CU) /**< \brief (USART3) IrDA Filter Register */
  #define REG_USART3_MAN                   (0xFC00C050U) /**< \brief (USART3) Manchester Configuration Register */
  #define REG_USART3_WPMR                  (0xFC00C0E4U) /**< \brief (USART3) Write Protection Mode Register */
  #define REG_USART3_WPSR                  (0xFC00C0E8U) /**< \brief (USART3) Write Protection Status Register */
#else
  #define REG_USART3_CR   (*(__O  uint32_t*)0xFC00C000U) /**< \brief (USART3) Control Register */
  #define REG_USART3_MR   (*(__IO uint32_t*)0xFC00C004U) /**< \brief (USART3) Mode Register */
  #define REG_USART3_IER  (*(__O  uint32_t*)0xFC00C008U) /**< \brief (USART3) Interrupt Enable Register */
  #define REG_USART3_IDR  (*(__O  uint32_t*)0xFC00C00CU) /**< \brief (USART3) Interrupt Disable Register */
  #define REG_USART3_IMR  (*(__I  uint32_t*)0xFC00C010U) /**< \brief (USART3) Interrupt Mask Register */
  #define REG_USART3_CSR  (*(__I  uint32_t*)0xFC00C014U) /**< \brief (USART3) Channel Status Register */
  #define REG_USART3_RHR  (*(__I  uint32_t*)0xFC00C018U) /**< \brief (USART3) Receive Holding Register */
  #define REG_USART3_THR  (*(__O  uint32_t*)0xFC00C01CU) /**< \brief (USART3) Transmit Holding Register */
  #define REG_USART3_BRGR (*(__IO uint32_t*)0xFC00C020U) /**< \brief (USART3) Baud Rate Generator Register */
  #define REG_USART3_RTOR (*(__IO uint32_t*)0xFC00C024U) /**< \brief (USART3) Receiver Time-out Register */
  #define REG_USART3_TTGR (*(__IO uint32_t*)0xFC00C028U) /**< \brief (USART3) Transmitter Timeguard Register */
  #define REG_USART3_FIDI (*(__IO uint32_t*)0xFC00C040U) /**< \brief (USART3) FI DI Ratio Register */
  #define REG_USART3_NER  (*(__I  uint32_t*)0xFC00C044U) /**< \brief (USART3) Number of Errors Register */
  #define REG_USART3_IF   (*(__IO uint32_t*)0xFC00C04CU) /**< \brief (USART3) IrDA Filter Register */
  #define REG_USART3_MAN  (*(__IO uint32_t*)0xFC00C050U) /**< \brief (USART3) Manchester Configuration Register */
  #define REG_USART3_WPMR (*(__IO uint32_t*)0xFC00C0E4U) /**< \brief (USART3) Write Protection Mode Register */
  #define REG_USART3_WPSR (*(__I  uint32_t*)0xFC00C0E8U) /**< \brief (USART3) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_USART3_INSTANCE_ */
