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

#ifndef _SAMA5D4_TWI3_INSTANCE_
#define _SAMA5D4_TWI3_INSTANCE_

/* ========== Register definition for TWI3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TWI3_CR                    (0xFC038000U) /**< \brief (TWI3) Control Register */
  #define REG_TWI3_MMR                   (0xFC038004U) /**< \brief (TWI3) Master Mode Register */
  #define REG_TWI3_SMR                   (0xFC038008U) /**< \brief (TWI3) Slave Mode Register */
  #define REG_TWI3_IADR                  (0xFC03800CU) /**< \brief (TWI3) Internal Address Register */
  #define REG_TWI3_CWGR                  (0xFC038010U) /**< \brief (TWI3) Clock Waveform Generator Register */
  #define REG_TWI3_SR                    (0xFC038020U) /**< \brief (TWI3) Status Register */
  #define REG_TWI3_IER                   (0xFC038024U) /**< \brief (TWI3) Interrupt Enable Register */
  #define REG_TWI3_IDR                   (0xFC038028U) /**< \brief (TWI3) Interrupt Disable Register */
  #define REG_TWI3_IMR                   (0xFC03802CU) /**< \brief (TWI3) Interrupt Mask Register */
  #define REG_TWI3_RHR                   (0xFC038030U) /**< \brief (TWI3) Receive Holding Register */
  #define REG_TWI3_THR                   (0xFC038034U) /**< \brief (TWI3) Transmit Holding Register */
  #define REG_TWI3_WPMR                  (0xFC0380E4U) /**< \brief (TWI3) Write Protection Mode Register */
  #define REG_TWI3_WPSR                  (0xFC0380E8U) /**< \brief (TWI3) Write Protection Status Register */
#else
  #define REG_TWI3_CR   (*(__O  uint32_t*)0xFC038000U) /**< \brief (TWI3) Control Register */
  #define REG_TWI3_MMR  (*(__IO uint32_t*)0xFC038004U) /**< \brief (TWI3) Master Mode Register */
  #define REG_TWI3_SMR  (*(__IO uint32_t*)0xFC038008U) /**< \brief (TWI3) Slave Mode Register */
  #define REG_TWI3_IADR (*(__IO uint32_t*)0xFC03800CU) /**< \brief (TWI3) Internal Address Register */
  #define REG_TWI3_CWGR (*(__IO uint32_t*)0xFC038010U) /**< \brief (TWI3) Clock Waveform Generator Register */
  #define REG_TWI3_SR   (*(__I  uint32_t*)0xFC038020U) /**< \brief (TWI3) Status Register */
  #define REG_TWI3_IER  (*(__O  uint32_t*)0xFC038024U) /**< \brief (TWI3) Interrupt Enable Register */
  #define REG_TWI3_IDR  (*(__O  uint32_t*)0xFC038028U) /**< \brief (TWI3) Interrupt Disable Register */
  #define REG_TWI3_IMR  (*(__I  uint32_t*)0xFC03802CU) /**< \brief (TWI3) Interrupt Mask Register */
  #define REG_TWI3_RHR  (*(__I  uint32_t*)0xFC038030U) /**< \brief (TWI3) Receive Holding Register */
  #define REG_TWI3_THR  (*(__O  uint32_t*)0xFC038034U) /**< \brief (TWI3) Transmit Holding Register */
  #define REG_TWI3_WPMR (*(__IO uint32_t*)0xFC0380E4U) /**< \brief (TWI3) Write Protection Mode Register */
  #define REG_TWI3_WPSR (*(__I  uint32_t*)0xFC0380E8U) /**< \brief (TWI3) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_TWI3_INSTANCE_ */
