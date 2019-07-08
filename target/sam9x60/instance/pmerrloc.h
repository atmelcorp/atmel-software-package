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

#ifndef _SAM9X_PMERRLOC_INSTANCE_
#define _SAM9X_PMERRLOC_INSTANCE_

/* ========== Register definition for PMERRLOC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PMERRLOC_ELCFG                    (0xFFFFE600U) /**< \brief (PMERRLOC) Configuration Register */
  #define REG_PMERRLOC_ELPRIM                   (0xFFFFE604U) /**< \brief (PMERRLOC) Primitive Register */
  #define REG_PMERRLOC_ELEN                     (0xFFFFE608U) /**< \brief (PMERRLOC) Enable Register */
  #define REG_PMERRLOC_ELDIS                    (0xFFFFE60CU) /**< \brief (PMERRLOC) Disable Register */
  #define REG_PMERRLOC_ELSR                     (0xFFFFE610U) /**< \brief (PMERRLOC) Status Register */
  #define REG_PMERRLOC_ELIER                    (0xFFFFE614U) /**< \brief (PMERRLOC) Interrupt Enable Register */
  #define REG_PMERRLOC_ELIDR                    (0xFFFFE618U) /**< \brief (PMERRLOC) Interrupt Disable Register */
  #define REG_PMERRLOC_ELIMR                    (0xFFFFE61CU) /**< \brief (PMERRLOC) Interrupt Mask Register */
  #define REG_PMERRLOC_ELISR                    (0xFFFFE620U) /**< \brief (PMERRLOC) Interrupt Status Register */
  #define REG_PMERRLOC_SIGMA0                   (0xFFFFE628U) /**< \brief (PMERRLOC) SIGMA0 Register */
  #define REG_PMERRLOC_SIGMA1                   (0xFFFFE62CU) /**< \brief (PMERRLOC) SIGMA1 Register */
  #define REG_PMERRLOC_SIGMA2                   (0xFFFFE630U) /**< \brief (PMERRLOC) SIGMA2 Register */
  #define REG_PMERRLOC_SIGMA3                   (0xFFFFE634U) /**< \brief (PMERRLOC) SIGMA3 Register */
  #define REG_PMERRLOC_SIGMA4                   (0xFFFFE638U) /**< \brief (PMERRLOC) SIGMA4 Register */
  #define REG_PMERRLOC_SIGMA5                   (0xFFFFE63CU) /**< \brief (PMERRLOC) SIGMA5 Register */
  #define REG_PMERRLOC_SIGMA6                   (0xFFFFE640U) /**< \brief (PMERRLOC) SIGMA6 Register */
  #define REG_PMERRLOC_SIGMA7                   (0xFFFFE644U) /**< \brief (PMERRLOC) SIGMA7 Register */
  #define REG_PMERRLOC_SIGMA8                   (0xFFFFE648U) /**< \brief (PMERRLOC) SIGMA8 Register */
  #define REG_PMERRLOC_SIGMA9                   (0xFFFFE64CU) /**< \brief (PMERRLOC) SIGMA9 Register */
  #define REG_PMERRLOC_SIGMA10                  (0xFFFFE650U) /**< \brief (PMERRLOC) SIGMA10 Register */
  #define REG_PMERRLOC_SIGMA11                  (0xFFFFE654U) /**< \brief (PMERRLOC) SIGMA11 Register */
  #define REG_PMERRLOC_SIGMA12                  (0xFFFFE658U) /**< \brief (PMERRLOC) SIGMA12 Register */
  #define REG_PMERRLOC_SIGMA13                  (0xFFFFE65CU) /**< \brief (PMERRLOC) SIGMA13 Register */
  #define REG_PMERRLOC_SIGMA14                  (0xFFFFE660U) /**< \brief (PMERRLOC) SIGMA14 Register */
  #define REG_PMERRLOC_SIGMA15                  (0xFFFFE664U) /**< \brief (PMERRLOC) SIGMA15 Register */
  #define REG_PMERRLOC_SIGMA16                  (0xFFFFE668U) /**< \brief (PMERRLOC) SIGMA16 Register */
  #define REG_PMERRLOC_SIGMA17                  (0xFFFFE66CU) /**< \brief (PMERRLOC) SIGMA17 Register */
  #define REG_PMERRLOC_SIGMA18                  (0xFFFFE670U) /**< \brief (PMERRLOC) SIGMA18 Register */
  #define REG_PMERRLOC_SIGMA19                  (0xFFFFE674U) /**< \brief (PMERRLOC) SIGMA19 Register */
  #define REG_PMERRLOC_SIGMA20                  (0xFFFFE678U) /**< \brief (PMERRLOC) SIGMA20 Register */
  #define REG_PMERRLOC_SIGMA21                  (0xFFFFE67CU) /**< \brief (PMERRLOC) SIGMA21 Register */
  #define REG_PMERRLOC_SIGMA22                  (0xFFFFE680U) /**< \brief (PMERRLOC) SIGMA22 Register */
  #define REG_PMERRLOC_SIGMA23                  (0xFFFFE684U) /**< \brief (PMERRLOC) SIGMA23 Register */
  #define REG_PMERRLOC_SIGMA24                  (0xFFFFE688U) /**< \brief (PMERRLOC) SIGMA24 Register */
  #define REG_PMERRLOC_EL                       (0xFFFFE68CU) /**< \brief (PMERRLOC) Error Location 0 Register */
#else
  #define REG_PMERRLOC_ELCFG   (*(__IO uint32_t*)0xFFFFE600U) /**< \brief (PMERRLOC) Configuration Register */
  #define REG_PMERRLOC_ELPRIM  (*(__I  uint32_t*)0xFFFFE604U) /**< \brief (PMERRLOC) Primitive Register */
  #define REG_PMERRLOC_ELEN    (*(__IO uint32_t*)0xFFFFE608U) /**< \brief (PMERRLOC) Enable Register */
  #define REG_PMERRLOC_ELDIS   (*(__IO uint32_t*)0xFFFFE60CU) /**< \brief (PMERRLOC) Disable Register */
  #define REG_PMERRLOC_ELSR    (*(__IO uint32_t*)0xFFFFE610U) /**< \brief (PMERRLOC) Status Register */
  #define REG_PMERRLOC_ELIER   (*(__O  uint32_t*)0xFFFFE614U) /**< \brief (PMERRLOC) Interrupt Enable Register */
  #define REG_PMERRLOC_ELIDR   (*(__O  uint32_t*)0xFFFFE618U) /**< \brief (PMERRLOC) Interrupt Disable Register */
  #define REG_PMERRLOC_ELIMR   (*(__I  uint32_t*)0xFFFFE61CU) /**< \brief (PMERRLOC) Interrupt Mask Register */
  #define REG_PMERRLOC_ELISR   (*(__I  uint32_t*)0xFFFFE620U) /**< \brief (PMERRLOC) Interrupt Status Register */
  #define REG_PMERRLOC_SIGMA0  (*(__I  uint32_t*)0xFFFFE628U) /**< \brief (PMERRLOC) SIGMA0 Register */
  #define REG_PMERRLOC_SIGMA1  (*(__IO uint32_t*)0xFFFFE62CU) /**< \brief (PMERRLOC) SIGMA1 Register */
  #define REG_PMERRLOC_SIGMA2  (*(__IO uint32_t*)0xFFFFE630U) /**< \brief (PMERRLOC) SIGMA2 Register */
  #define REG_PMERRLOC_SIGMA3  (*(__IO uint32_t*)0xFFFFE634U) /**< \brief (PMERRLOC) SIGMA3 Register */
  #define REG_PMERRLOC_SIGMA4  (*(__IO uint32_t*)0xFFFFE638U) /**< \brief (PMERRLOC) SIGMA4 Register */
  #define REG_PMERRLOC_SIGMA5  (*(__IO uint32_t*)0xFFFFE63CU) /**< \brief (PMERRLOC) SIGMA5 Register */
  #define REG_PMERRLOC_SIGMA6  (*(__IO uint32_t*)0xFFFFE640U) /**< \brief (PMERRLOC) SIGMA6 Register */
  #define REG_PMERRLOC_SIGMA7  (*(__IO uint32_t*)0xFFFFE644U) /**< \brief (PMERRLOC) SIGMA7 Register */
  #define REG_PMERRLOC_SIGMA8  (*(__IO uint32_t*)0xFFFFE648U) /**< \brief (PMERRLOC) SIGMA8 Register */
  #define REG_PMERRLOC_SIGMA9  (*(__IO uint32_t*)0xFFFFE64CU) /**< \brief (PMERRLOC) SIGMA9 Register */
  #define REG_PMERRLOC_SIGMA10 (*(__IO uint32_t*)0xFFFFE650U) /**< \brief (PMERRLOC) SIGMA10 Register */
  #define REG_PMERRLOC_SIGMA11 (*(__IO uint32_t*)0xFFFFE654U) /**< \brief (PMERRLOC) SIGMA11 Register */
  #define REG_PMERRLOC_SIGMA12 (*(__IO uint32_t*)0xFFFFE658U) /**< \brief (PMERRLOC) SIGMA12 Register */
  #define REG_PMERRLOC_SIGMA13 (*(__IO uint32_t*)0xFFFFE65CU) /**< \brief (PMERRLOC) SIGMA13 Register */
  #define REG_PMERRLOC_SIGMA14 (*(__IO uint32_t*)0xFFFFE660U) /**< \brief (PMERRLOC) SIGMA14 Register */
  #define REG_PMERRLOC_SIGMA15 (*(__IO uint32_t*)0xFFFFE664U) /**< \brief (PMERRLOC) SIGMA15 Register */
  #define REG_PMERRLOC_SIGMA16 (*(__IO uint32_t*)0xFFFFE668U) /**< \brief (PMERRLOC) SIGMA16 Register */
  #define REG_PMERRLOC_SIGMA17 (*(__IO uint32_t*)0xFFFFE66CU) /**< \brief (PMERRLOC) SIGMA17 Register */
  #define REG_PMERRLOC_SIGMA18 (*(__IO uint32_t*)0xFFFFE670U) /**< \brief (PMERRLOC) SIGMA18 Register */
  #define REG_PMERRLOC_SIGMA19 (*(__IO uint32_t*)0xFFFFE674U) /**< \brief (PMERRLOC) SIGMA19 Register */
  #define REG_PMERRLOC_SIGMA20 (*(__IO uint32_t*)0xFFFFE678U) /**< \brief (PMERRLOC) SIGMA20 Register */
  #define REG_PMERRLOC_SIGMA21 (*(__IO uint32_t*)0xFFFFE67CU) /**< \brief (PMERRLOC) SIGMA21 Register */
  #define REG_PMERRLOC_SIGMA22 (*(__IO uint32_t*)0xFFFFE680U) /**< \brief (PMERRLOC) SIGMA22 Register */
  #define REG_PMERRLOC_SIGMA23 (*(__IO uint32_t*)0xFFFFE684U) /**< \brief (PMERRLOC) SIGMA23 Register */
  #define REG_PMERRLOC_SIGMA24 (*(__IO uint32_t*)0xFFFFE688U) /**< \brief (PMERRLOC) SIGMA24 Register */
  #define REG_PMERRLOC_EL      (*(__I  uint32_t*)0xFFFFE68CU) /**< \brief (PMERRLOC) Error Location 0 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PMERRLOC_INSTANCE_ */
