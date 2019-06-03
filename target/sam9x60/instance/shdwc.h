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

#ifndef _SAM9X_SHDWC_INSTANCE_
#define _SAM9X_SHDWC_INSTANCE_

/* ========== Register definition for SHDWC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SHDWC_CR                    (0xFFFFFE10U) /**< \brief (SHDWC) Control Register */
  #define REG_SHDWC_MR                    (0xFFFFFE14U) /**< \brief (SHDWC) Mode Register */
  #define REG_SHDWC_SR                    (0xFFFFFE18U) /**< \brief (SHDWC) Status Register */
  #define REG_SHDWC_WUIR                  (0xFFFFFE1CU) /**< \brief (SHDWC) Wakeup Inputs Register */
#else
  #define REG_SHDWC_CR   (*(__O  uint32_t*)0xFFFFFE10U) /**< \brief (SHDWC) Control Register */
  #define REG_SHDWC_MR   (*(__IO uint32_t*)0xFFFFFE14U) /**< \brief (SHDWC) Mode Register */
  #define REG_SHDWC_SR   (*(__I  uint32_t*)0xFFFFFE18U) /**< \brief (SHDWC) Status Register */
  #define REG_SHDWC_WUIR (*(__IO uint32_t*)0xFFFFFE1CU) /**< \brief (SHDWC) Wakeup Inputs Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SHDWC_INSTANCE_ */
