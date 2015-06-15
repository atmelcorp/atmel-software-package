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

#ifndef _SAMA5D2_ACC_COMPONENT_
#define _SAMA5D2_ACC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Analog Comparator Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D2_ACC Analog Comparator Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Acc hardware registers */
typedef struct {
  __O  uint32_t ACC_CR;        /**< \brief (Acc Offset: 0x00) Control Register */
  __IO uint32_t ACC_MR;        /**< \brief (Acc Offset: 0x04) Mode Register */
  __I  uint32_t Reserved1[55];
  __IO uint32_t ACC_WPMR;      /**< \brief (Acc Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t ACC_WPSR;      /**< \brief (Acc Offset: 0xE8) Write Protection Status Register */
  __I  uint32_t Reserved2[4];
  __I  uint32_t ACC_VER;       /**< \brief (Acc Offset: 0xFC) Version Register */
} Acc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- ACC_CR : (ACC Offset: 0x00) Control Register -------- */
#define ACC_CR_SWRST (0x1u << 0) /**< \brief (ACC_CR) Software Reset */
/* -------- ACC_MR : (ACC Offset: 0x04) Mode Register -------- */
#define ACC_MR_ACEN (0x1u << 8) /**< \brief (ACC_MR) Analog Comparator Enable */
#define   ACC_MR_ACEN_DIS (0x0u << 8) /**< \brief (ACC_MR) Analog comparator disabled. */
#define   ACC_MR_ACEN_EN (0x1u << 8) /**< \brief (ACC_MR) Analog comparator enabled. */
#define ACC_MR_INV (0x1u << 12) /**< \brief (ACC_MR) Invert Comparator Output */
#define   ACC_MR_INV_DIS (0x0u << 12) /**< \brief (ACC_MR) Analog comparator output is directly processed. */
#define   ACC_MR_INV_EN (0x1u << 12) /**< \brief (ACC_MR) Analog comparator output is inverted prior to being processed. */
/* -------- ACC_WPMR : (ACC Offset: 0xE4) Write Protection Mode Register -------- */
#define ACC_WPMR_WPEN (0x1u << 0) /**< \brief (ACC_WPMR) Write Protection Enable */
#define ACC_WPMR_WPKEY_Pos 8
#define ACC_WPMR_WPKEY_Msk (0xffffffu << ACC_WPMR_WPKEY_Pos) /**< \brief (ACC_WPMR) Write Protection Key */
#define ACC_WPMR_WPKEY(value) ((ACC_WPMR_WPKEY_Msk & ((value) << ACC_WPMR_WPKEY_Pos)))
#define   ACC_WPMR_WPKEY_PASSWD (0x414343u << 8) /**< \brief (ACC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- ACC_WPSR : (ACC Offset: 0xE8) Write Protection Status Register -------- */
#define ACC_WPSR_WPVS (0x1u << 0) /**< \brief (ACC_WPSR) Write Protection Violation Status */
/* -------- ACC_VER : (ACC Offset: 0xFC) Version Register -------- */
#define ACC_VER_VERSION_Pos 0
#define ACC_VER_VERSION_Msk (0xfffu << ACC_VER_VERSION_Pos) /**< \brief (ACC_VER) Version of the Hardware Module */
#define ACC_VER_MFN_Pos 16
#define ACC_VER_MFN_Msk (0x7u << ACC_VER_MFN_Pos) /**< \brief (ACC_VER) Metal Fix Number */

/*@}*/


#endif /* _SAMA5D2_ACC_COMPONENT_ */
