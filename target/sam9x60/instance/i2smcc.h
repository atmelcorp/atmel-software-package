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

#ifndef _SAM9X_I2SMCC_INSTANCE_
#define _SAM9X_I2SMCC_INSTANCE_

/* ========== Register definition for I2SMCC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_I2SMCC_CR                    (0xF001C000U) /**< \brief (I2SMCC) Control Register */
  #define REG_I2SMCC_MRA                   (0xF001C004U) /**< \brief (I2SMCC) Mode Register A */
  #define REG_I2SMCC_MRB                   (0xF001C008U) /**< \brief (I2SMCC) Mode Register B */
  #define REG_I2SMCC_SR                    (0xF001C00CU) /**< \brief (I2SMCC) Status Register */
  #define REG_I2SMCC_IERA                  (0xF001C010U) /**< \brief (I2SMCC) Interrupt Enable Register A */
  #define REG_I2SMCC_IDRA                  (0xF001C014U) /**< \brief (I2SMCC) Interrupt Disable Register A */
  #define REG_I2SMCC_IMRA                  (0xF001C018U) /**< \brief (I2SMCC) Interrupt Mask Register A */
  #define REG_I2SMCC_ISRA                  (0xF001C01CU) /**< \brief (I2SMCC) Interrupt Status Register A */
  #define REG_I2SMCC_IERB                  (0xF001C020U) /**< \brief (I2SMCC) Interrupt Enable Register B */
  #define REG_I2SMCC_IDRB                  (0xF001C024U) /**< \brief (I2SMCC) Interrupt Disable Register B */
  #define REG_I2SMCC_IMRB                  (0xF001C028U) /**< \brief (I2SMCC) Interrupt Mask Register B */
  #define REG_I2SMCC_ISRB                  (0xF001C02CU) /**< \brief (I2SMCC) Interrupt Status Register B */
  #define REG_I2SMCC_RHR                   (0xF001C030U) /**< \brief (I2SMCC) Receiver Holding Register */
  #define REG_I2SMCC_THR                   (0xF001C034U) /**< \brief (I2SMCC) Transmitter Holding Register */
  #define REG_I2SMCC_WPMR                  (0xF001C0E4U) /**< \brief (I2SMCC) Write Protection Mode Register */
  #define REG_I2SMCC_WPSR                  (0xF001C0E8U) /**< \brief (I2SMCC) Write Protection Status Register */
#else
  #define REG_I2SMCC_CR   (*(__O  uint32_t*)0xF001C000U) /**< \brief (I2SMCC) Control Register */
  #define REG_I2SMCC_MRA  (*(__IO uint32_t*)0xF001C004U) /**< \brief (I2SMCC) Mode Register A */
  #define REG_I2SMCC_MRB  (*(__IO uint32_t*)0xF001C008U) /**< \brief (I2SMCC) Mode Register B */
  #define REG_I2SMCC_SR   (*(__I  uint32_t*)0xF001C00CU) /**< \brief (I2SMCC) Status Register */
  #define REG_I2SMCC_IERA (*(__O  uint32_t*)0xF001C010U) /**< \brief (I2SMCC) Interrupt Enable Register A */
  #define REG_I2SMCC_IDRA (*(__O  uint32_t*)0xF001C014U) /**< \brief (I2SMCC) Interrupt Disable Register A */
  #define REG_I2SMCC_IMRA (*(__I  uint32_t*)0xF001C018U) /**< \brief (I2SMCC) Interrupt Mask Register A */
  #define REG_I2SMCC_ISRA (*(__I  uint32_t*)0xF001C01CU) /**< \brief (I2SMCC) Interrupt Status Register A */
  #define REG_I2SMCC_IERB (*(__O  uint32_t*)0xF001C020U) /**< \brief (I2SMCC) Interrupt Enable Register B */
  #define REG_I2SMCC_IDRB (*(__O  uint32_t*)0xF001C024U) /**< \brief (I2SMCC) Interrupt Disable Register B */
  #define REG_I2SMCC_IMRB (*(__I  uint32_t*)0xF001C028U) /**< \brief (I2SMCC) Interrupt Mask Register B */
  #define REG_I2SMCC_ISRB (*(__I  uint32_t*)0xF001C02CU) /**< \brief (I2SMCC) Interrupt Status Register B */
  #define REG_I2SMCC_RHR  (*(__I  uint32_t*)0xF001C030U) /**< \brief (I2SMCC) Receiver Holding Register */
  #define REG_I2SMCC_THR  (*(__O  uint32_t*)0xF001C034U) /**< \brief (I2SMCC) Transmitter Holding Register */
  #define REG_I2SMCC_WPMR (*(__IO uint32_t*)0xF001C0E4U) /**< \brief (I2SMCC) Write Protection Mode Register */
  #define REG_I2SMCC_WPSR (*(__I  uint32_t*)0xF001C0E8U) /**< \brief (I2SMCC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_I2SMCC_INSTANCE_ */
