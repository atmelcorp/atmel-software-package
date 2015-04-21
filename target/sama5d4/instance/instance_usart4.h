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

#ifndef _SAMA5D4_USART4_INSTANCE_
#define _SAMA5D4_USART4_INSTANCE_

/* ========== Register definition for USART4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_USART4_CR                    (0xFC010000U) /**< \brief (USART4) Control Register */
#define REG_USART4_MR                    (0xFC010004U) /**< \brief (USART4) Mode Register */
#define REG_USART4_IER                   (0xFC010008U) /**< \brief (USART4) Interrupt Enable Register */
#define REG_USART4_IDR                   (0xFC01000CU) /**< \brief (USART4) Interrupt Disable Register */
#define REG_USART4_IMR                   (0xFC010010U) /**< \brief (USART4) Interrupt Mask Register */
#define REG_USART4_CSR                   (0xFC010014U) /**< \brief (USART4) Channel Status Register */
#define REG_USART4_RHR                   (0xFC010018U) /**< \brief (USART4) Receive Holding Register */
#define REG_USART4_THR                   (0xFC01001CU) /**< \brief (USART4) Transmit Holding Register */
#define REG_USART4_BRGR                  (0xFC010020U) /**< \brief (USART4) Baud Rate Generator Register */
#define REG_USART4_RTOR                  (0xFC010024U) /**< \brief (USART4) Receiver Time-out Register */
#define REG_USART4_TTGR                  (0xFC010028U) /**< \brief (USART4) Transmitter Timeguard Register */
#define REG_USART4_FIDI                  (0xFC010040U) /**< \brief (USART4) FI DI Ratio Register */
#define REG_USART4_NER                   (0xFC010044U) /**< \brief (USART4) Number of Errors Register */
#define REG_USART4_IF                    (0xFC01004CU) /**< \brief (USART4) IrDA Filter Register */
#define REG_USART4_MAN                   (0xFC010050U) /**< \brief (USART4) Manchester Configuration Register */
#define REG_USART4_WPMR                  (0xFC0100E4U) /**< \brief (USART4) Write Protection Mode Register */
#define REG_USART4_WPSR                  (0xFC0100E8U) /**< \brief (USART4) Write Protection Status Register */
#else
#define REG_USART4_CR   (*(__O  uint32_t*)0xFC010000U) /**< \brief (USART4) Control Register */
#define REG_USART4_MR   (*(__IO uint32_t*)0xFC010004U) /**< \brief (USART4) Mode Register */
#define REG_USART4_IER  (*(__O  uint32_t*)0xFC010008U) /**< \brief (USART4) Interrupt Enable Register */
#define REG_USART4_IDR  (*(__O  uint32_t*)0xFC01000CU) /**< \brief (USART4) Interrupt Disable Register */
#define REG_USART4_IMR  (*(__I  uint32_t*)0xFC010010U) /**< \brief (USART4) Interrupt Mask Register */
#define REG_USART4_CSR  (*(__I  uint32_t*)0xFC010014U) /**< \brief (USART4) Channel Status Register */
#define REG_USART4_RHR  (*(__I  uint32_t*)0xFC010018U) /**< \brief (USART4) Receive Holding Register */
#define REG_USART4_THR  (*(__O  uint32_t*)0xFC01001CU) /**< \brief (USART4) Transmit Holding Register */
#define REG_USART4_BRGR (*(__IO uint32_t*)0xFC010020U) /**< \brief (USART4) Baud Rate Generator Register */
#define REG_USART4_RTOR (*(__IO uint32_t*)0xFC010024U) /**< \brief (USART4) Receiver Time-out Register */
#define REG_USART4_TTGR (*(__IO uint32_t*)0xFC010028U) /**< \brief (USART4) Transmitter Timeguard Register */
#define REG_USART4_FIDI (*(__IO uint32_t*)0xFC010040U) /**< \brief (USART4) FI DI Ratio Register */
#define REG_USART4_NER  (*(__I  uint32_t*)0xFC010044U) /**< \brief (USART4) Number of Errors Register */
#define REG_USART4_IF   (*(__IO uint32_t*)0xFC01004CU) /**< \brief (USART4) IrDA Filter Register */
#define REG_USART4_MAN  (*(__IO uint32_t*)0xFC010050U) /**< \brief (USART4) Manchester Configuration Register */
#define REG_USART4_WPMR (*(__IO uint32_t*)0xFC0100E4U) /**< \brief (USART4) Write Protection Mode Register */
#define REG_USART4_WPSR (*(__I  uint32_t*)0xFC0100E8U) /**< \brief (USART4) Write Protection Status Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_USART4_INSTANCE_ */
