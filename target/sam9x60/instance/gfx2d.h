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

#ifndef _SAM9X_GFX2D_INSTANCE_
#define _SAM9X_GFX2D_INSTANCE_

/* ========== Register definition for GFX2D peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_GFX2D_GC                      (0xF0018000U) /**< \brief (GFX2D) Global Configuration Register */
  #define REG_GFX2D_GE                      (0xF0018004U) /**< \brief (GFX2D) Global Enable Register */
  #define REG_GFX2D_GD                      (0xF0018008U) /**< \brief (GFX2D) Global Disable Register */
  #define REG_GFX2D_GS                      (0xF001800CU) /**< \brief (GFX2D) Global Status Register */
  #define REG_GFX2D_IE                      (0xF0018010U) /**< \brief (GFX2D) Interrupt Enable Register */
  #define REG_GFX2D_ID                      (0xF0018014U) /**< \brief (GFX2D) Interrupt Disable Register */
  #define REG_GFX2D_IM                      (0xF0018018U) /**< \brief (GFX2D) Interrupt Mask Register */
  #define REG_GFX2D_IS                      (0xF001801CU) /**< \brief (GFX2D) Interrupt Status Register */
  #define REG_GFX2D_PC0                     (0xF0018020U) /**< \brief (GFX2D) Performance Configuration 0 Register */
  #define REG_GFX2D_MC0                     (0xF0018024U) /**< \brief (GFX2D) Metrics Counter 0 Register */
  #define REG_GFX2D_PC1                     (0xF0018028U) /**< \brief (GFX2D) Performance Configuration 1 Register */
  #define REG_GFX2D_MC1                     (0xF001802CU) /**< \brief (GFX2D) Metrics Counter 1 Register */
  #define REG_GFX2D_BASE                    (0xF0018030U) /**< \brief (GFX2D) Ring Buffer Base Register */
  #define REG_GFX2D_LEN                     (0xF0018034U) /**< \brief (GFX2D) Ring Buffer Length Register */
  #define REG_GFX2D_HEAD                    (0xF0018038U) /**< \brief (GFX2D) Ring Buffer Head Register */
  #define REG_GFX2D_TAIL                    (0xF001803CU) /**< \brief (GFX2D) Ring Buffer Tail Register */
  #define REG_GFX2D_PA0                     (0xF0018040U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 0) */
  #define REG_GFX2D_PITCH0                  (0xF0018044U) /**< \brief (GFX2D) Surface Pitch Register (chid = 0) */
  #define REG_GFX2D_CFG0                    (0xF0018048U) /**< \brief (GFX2D) Surface Configuration Register (chid = 0) */
  #define REG_GFX2D_PA1                     (0xF0018050U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 1) */
  #define REG_GFX2D_PITCH1                  (0xF0018054U) /**< \brief (GFX2D) Surface Pitch Register (chid = 1) */
  #define REG_GFX2D_CFG1                    (0xF0018058U) /**< \brief (GFX2D) Surface Configuration Register (chid = 1) */
  #define REG_GFX2D_PA2                     (0xF0018060U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 2) */
  #define REG_GFX2D_PITCH2                  (0xF0018064U) /**< \brief (GFX2D) Surface Pitch Register (chid = 2) */
  #define REG_GFX2D_CFG2                    (0xF0018068U) /**< \brief (GFX2D) Surface Configuration Register (chid = 2) */
  #define REG_GFX2D_PA3                     (0xF0018070U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 3) */
  #define REG_GFX2D_PITCH3                  (0xF0018074U) /**< \brief (GFX2D) Surface Pitch Register (chid = 3) */
  #define REG_GFX2D_CFG3                    (0xF0018078U) /**< \brief (GFX2D) Surface Configuration Register (chid = 3) */
#else
  #define REG_GFX2D_GC     (*(__IO uint32_t*)0xF0018000U) /**< \brief (GFX2D) Global Configuration Register */
  #define REG_GFX2D_GE     (*(__O  uint32_t*)0xF0018004U) /**< \brief (GFX2D) Global Enable Register */
  #define REG_GFX2D_GD     (*(__O  uint32_t*)0xF0018008U) /**< \brief (GFX2D) Global Disable Register */
  #define REG_GFX2D_GS     (*(__I  uint32_t*)0xF001800CU) /**< \brief (GFX2D) Global Status Register */
  #define REG_GFX2D_IE     (*(__O  uint32_t*)0xF0018010U) /**< \brief (GFX2D) Interrupt Enable Register */
  #define REG_GFX2D_ID     (*(__O  uint32_t*)0xF0018014U) /**< \brief (GFX2D) Interrupt Disable Register */
  #define REG_GFX2D_IM     (*(__I  uint32_t*)0xF0018018U) /**< \brief (GFX2D) Interrupt Mask Register */
  #define REG_GFX2D_IS     (*(__I  uint32_t*)0xF001801CU) /**< \brief (GFX2D) Interrupt Status Register */
  #define REG_GFX2D_PC0    (*(__IO uint32_t*)0xF0018020U) /**< \brief (GFX2D) Performance Configuration 0 Register */
  #define REG_GFX2D_MC0    (*(__I  uint32_t*)0xF0018024U) /**< \brief (GFX2D) Metrics Counter 0 Register */
  #define REG_GFX2D_PC1    (*(__IO uint32_t*)0xF0018028U) /**< \brief (GFX2D) Performance Configuration 1 Register */
  #define REG_GFX2D_MC1    (*(__I  uint32_t*)0xF001802CU) /**< \brief (GFX2D) Metrics Counter 1 Register */
  #define REG_GFX2D_BASE   (*(__IO uint32_t*)0xF0018030U) /**< \brief (GFX2D) Ring Buffer Base Register */
  #define REG_GFX2D_LEN    (*(__IO uint32_t*)0xF0018034U) /**< \brief (GFX2D) Ring Buffer Length Register */
  #define REG_GFX2D_HEAD   (*(__IO uint32_t*)0xF0018038U) /**< \brief (GFX2D) Ring Buffer Head Register */
  #define REG_GFX2D_TAIL   (*(__IO uint32_t*)0xF001803CU) /**< \brief (GFX2D) Ring Buffer Tail Register */
  #define REG_GFX2D_PA0    (*(__IO uint32_t*)0xF0018040U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 0) */
  #define REG_GFX2D_PITCH0 (*(__IO uint32_t*)0xF0018044U) /**< \brief (GFX2D) Surface Pitch Register (chid = 0) */
  #define REG_GFX2D_CFG0   (*(__IO uint32_t*)0xF0018048U) /**< \brief (GFX2D) Surface Configuration Register (chid = 0) */
  #define REG_GFX2D_PA1    (*(__IO uint32_t*)0xF0018050U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 1) */
  #define REG_GFX2D_PITCH1 (*(__IO uint32_t*)0xF0018054U) /**< \brief (GFX2D) Surface Pitch Register (chid = 1) */
  #define REG_GFX2D_CFG1   (*(__IO uint32_t*)0xF0018058U) /**< \brief (GFX2D) Surface Configuration Register (chid = 1) */
  #define REG_GFX2D_PA2    (*(__IO uint32_t*)0xF0018060U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 2) */
  #define REG_GFX2D_PITCH2 (*(__IO uint32_t*)0xF0018064U) /**< \brief (GFX2D) Surface Pitch Register (chid = 2) */
  #define REG_GFX2D_CFG2   (*(__IO uint32_t*)0xF0018068U) /**< \brief (GFX2D) Surface Configuration Register (chid = 2) */
  #define REG_GFX2D_PA3    (*(__IO uint32_t*)0xF0018070U) /**< \brief (GFX2D) Surface Physical Address Register (chid = 3) */
  #define REG_GFX2D_PITCH3 (*(__IO uint32_t*)0xF0018074U) /**< \brief (GFX2D) Surface Pitch Register (chid = 3) */
  #define REG_GFX2D_CFG3   (*(__IO uint32_t*)0xF0018078U) /**< \brief (GFX2D) Surface Configuration Register (chid = 3) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_GFX2D_INSTANCE_ */
