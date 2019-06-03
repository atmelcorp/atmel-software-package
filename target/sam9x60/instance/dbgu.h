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

#ifndef _SAM9X_DBGU_INSTANCE_
#define _SAM9X_DBGU_INSTANCE_

/* ========== Register definition for DBGU peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_DBGU_CR                    (0xFFFFF200U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR                    (0xFFFFF204U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER                   (0xFFFFF208U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR                   (0xFFFFF20CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR                   (0xFFFFF210U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR                    (0xFFFFF214U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR                   (0xFFFFF218U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR                   (0xFFFFF21CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR                  (0xFFFFF220U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_RTOR                  (0xFFFFF228U) /**< \brief (DBGU) Receiver Timeout Register */
  #define REG_DBGU_CIDR                  (0xFFFFF240U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID                  (0xFFFFF244U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR                   (0xFFFFF248U) /**< \brief (DBGU) Force NTRST Register */
  #define REG_DBGU_WPMR                  (0xFFFFF2E4U) /**< \brief (DBGU) Write Protection Mode Register */
#else
  #define REG_DBGU_CR   (*(__O  uint32_t*)0xFFFFF200U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR   (*(__IO uint32_t*)0xFFFFF204U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER  (*(__O  uint32_t*)0xFFFFF208U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR  (*(__O  uint32_t*)0xFFFFF20CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR  (*(__I  uint32_t*)0xFFFFF210U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR   (*(__I  uint32_t*)0xFFFFF214U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR  (*(__I  uint32_t*)0xFFFFF218U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR  (*(__O  uint32_t*)0xFFFFF21CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR (*(__IO uint32_t*)0xFFFFF220U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_RTOR (*(__IO uint32_t*)0xFFFFF228U) /**< \brief (DBGU) Receiver Timeout Register */
  #define REG_DBGU_CIDR (*(__I  uint32_t*)0xFFFFF240U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID (*(__I  uint32_t*)0xFFFFF244U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR  (*(__IO uint32_t*)0xFFFFF248U) /**< \brief (DBGU) Force NTRST Register */
  #define REG_DBGU_WPMR (*(__IO uint32_t*)0xFFFFF2E4U) /**< \brief (DBGU) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_DBGU_INSTANCE_ */
