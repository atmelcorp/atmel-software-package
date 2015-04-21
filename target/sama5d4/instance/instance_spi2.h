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

#ifndef _SAMA5D4_SPI2_INSTANCE_
#define _SAMA5D4_SPI2_INSTANCE_

/* ========== Register definition for SPI2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SPI2_CR                    (0xFC01C000U) /**< \brief (SPI2) Control Register */
#define REG_SPI2_MR                    (0xFC01C004U) /**< \brief (SPI2) Mode Register */
#define REG_SPI2_RDR                   (0xFC01C008U) /**< \brief (SPI2) Receive Data Register */
#define REG_SPI2_TDR                   (0xFC01C00CU) /**< \brief (SPI2) Transmit Data Register */
#define REG_SPI2_SR                    (0xFC01C010U) /**< \brief (SPI2) Status Register */
#define REG_SPI2_IER                   (0xFC01C014U) /**< \brief (SPI2) Interrupt Enable Register */
#define REG_SPI2_IDR                   (0xFC01C018U) /**< \brief (SPI2) Interrupt Disable Register */
#define REG_SPI2_IMR                   (0xFC01C01CU) /**< \brief (SPI2) Interrupt Mask Register */
#define REG_SPI2_CSR                   (0xFC01C030U) /**< \brief (SPI2) Chip Select Register */
#define REG_SPI2_WPMR                  (0xFC01C0E4U) /**< \brief (SPI2) Write Protection Mode Register */
#define REG_SPI2_WPSR                  (0xFC01C0E8U) /**< \brief (SPI2) Write Protection Status Register */
#else
#define REG_SPI2_CR   (*(__O  uint32_t*)0xFC01C000U) /**< \brief (SPI2) Control Register */
#define REG_SPI2_MR   (*(__IO uint32_t*)0xFC01C004U) /**< \brief (SPI2) Mode Register */
#define REG_SPI2_RDR  (*(__I  uint32_t*)0xFC01C008U) /**< \brief (SPI2) Receive Data Register */
#define REG_SPI2_TDR  (*(__O  uint32_t*)0xFC01C00CU) /**< \brief (SPI2) Transmit Data Register */
#define REG_SPI2_SR   (*(__I  uint32_t*)0xFC01C010U) /**< \brief (SPI2) Status Register */
#define REG_SPI2_IER  (*(__O  uint32_t*)0xFC01C014U) /**< \brief (SPI2) Interrupt Enable Register */
#define REG_SPI2_IDR  (*(__O  uint32_t*)0xFC01C018U) /**< \brief (SPI2) Interrupt Disable Register */
#define REG_SPI2_IMR  (*(__I  uint32_t*)0xFC01C01CU) /**< \brief (SPI2) Interrupt Mask Register */
#define REG_SPI2_CSR  (*(__IO uint32_t*)0xFC01C030U) /**< \brief (SPI2) Chip Select Register */
#define REG_SPI2_WPMR (*(__IO uint32_t*)0xFC01C0E4U) /**< \brief (SPI2) Write Protection Mode Register */
#define REG_SPI2_WPSR (*(__I  uint32_t*)0xFC01C0E8U) /**< \brief (SPI2) Write Protection Status Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_SPI2_INSTANCE_ */
