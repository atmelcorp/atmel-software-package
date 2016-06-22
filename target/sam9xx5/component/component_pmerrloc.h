/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
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

#ifndef _SAM9X_PMERRLOC_COMPONENT_
#define _SAM9X_PMERRLOC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Static Memory Controller (PMERRLOC) */
/* ============================================================================= */
/** \addtogroup SAM9X_PMERRLOC Static Memory Controller (PMERRLOC) */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pmerrloc hardware registers */
typedef struct {
	__IO uint32_t PMERRLOC_CFG;       /**< \brief (Pmerrloc Offset: 0x00) PMECC Error Location Configuration Register */
	__I  uint32_t PMERRLOC_PRIM;      /**< \brief (Pmerrloc Offset: 0x04) PMECC Error Location Primitive Register */
	__O  uint32_t PMERRLOC_EN;        /**< \brief (Pmerrloc Offset: 0x08) PMECC Error Location Enable Register */
	__O  uint32_t PMERRLOC_DIS;       /**< \brief (Pmerrloc Offset: 0x0C) PMECC Error Location Disable Register */
	__I  uint32_t PMERRLOC_SR;        /**< \brief (Pmerrloc Offset: 0x10) PMECC Error Location Status Register */
	__O  uint32_t PMERRLOC_IER;       /**< \brief (Pmerrloc Offset: 0x14) PMECC Error Location Interrupt Enable register */
	__O  uint32_t PMERRLOC_IDR;       /**< \brief (Pmerrloc Offset: 0x18) PMECC Error Location Interrupt Disable Register */
	__I  uint32_t PMERRLOC_IMR;       /**< \brief (Pmerrloc Offset: 0x1C) PMECC Error Location Interrupt Mask Register */
	__I  uint32_t PMERRLOC_ISR;       /**< \brief (Pmerrloc Offset: 0x20) PMECC Error Location Interrupt Status Register */
	__I  uint32_t Reserved1[1];
	__IO uint32_t PMERRLOC_SIGMA[25]; /**< \brief (Pmerrloc Offset: 0x28) PMECC Error Location SIGMA x Register */
	__I  uint32_t PMERRLOC_EL[24];    /**< \brief (Pmerrloc Offset: 0x8C) PMECC Error Location x Register */
} Pmerrloc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PMERRLOC_CFG : (PMERRLOC Offset: 0x00) PMECC Error Location Configuration Register -------- */
#define PMERRLOC_CFG_SECTORSZ (0x1u << 0) /**< \brief (PMERRLOC_CFG) Sector Size */
#define PMERRLOC_CFG_ERRNUM_Pos 16
#define PMERRLOC_CFG_ERRNUM_Msk (0x1fu << PMERRLOC_CFG_ERRNUM_Pos) /**< \brief (PMERRLOC_CFG) Number of Errors */
#define PMERRLOC_CFG_ERRNUM(value) ((PMERRLOC_CFG_ERRNUM_Msk & ((value) << PMERRLOC_CFG_ERRNUM_Pos)))
/* -------- PMERRLOC_PRIM : (PMERRLOC Offset: 0x04) PMECC Error Location Primitive Register -------- */
#define PMERRLOC_PRIM_PRIMITIV_Pos 0
#define PMERRLOC_PRIM_PRIMITIV_Msk (0xffffu << PMERRLOC_PRIM_PRIMITIV_Pos) /**< \brief (PMERRLOC_PRIM) Primitive Polynomial */
/* -------- PMERRLOC_EN : (PMERRLOC Offset: 0x08) PMECC Error Location Enable Register -------- */
#define PMERRLOC_EN_ENINIT_Pos 0
#define PMERRLOC_EN_ENINIT_Msk (0x3fffu << PMERRLOC_EN_ENINIT_Pos) /**< \brief (PMERRLOC_EN) Initial Number of Bits in the Codeword */
#define PMERRLOC_EN_ENINIT(value) ((PMERRLOC_EN_ENINIT_Msk & ((value) << PMERRLOC_EN_ENINIT_Pos)))
/* -------- PMERRLOC_DIS : (PMERRLOC Offset: 0x0C) PMECC Error Location Disable Register -------- */
#define PMERRLOC_DIS_DIS (0x1u << 0) /**< \brief (PMERRLOC_DIS) Disable Error Location Engine */
/* -------- PMERRLOC_SR : (PMERRLOC Offset: 0x10) PMECC Error Location Status Register -------- */
#define PMERRLOC_SR_BUSY (0x1u << 0) /**< \brief (PMERRLOC_SR) Error Location Engine Busy */
/* -------- PMERRLOC_IER : (PMERRLOC Offset: 0x14) PMECC Error Location Interrupt Enable register -------- */
#define PMERRLOC_IER_DONE (0x1u << 0) /**< \brief (PMERRLOC_IER) Computation Terminated Interrupt Enable */
/* -------- PMERRLOC_IDR : (PMERRLOC Offset: 0x18) PMECC Error Location Interrupt Disable Register -------- */
#define PMERRLOC_IDR_DONE (0x1u << 0) /**< \brief (PMERRLOC_IDR) Computation Terminated Interrupt Disable */
/* -------- PMERRLOC_IMR : (PMERRLOC Offset: 0x1C) PMECC Error Location Interrupt Mask Register -------- */
#define PMERRLOC_IMR_DONE (0x1u << 0) /**< \brief (PMERRLOC_IMR) Computation Terminated Interrupt Mask */
/* -------- PMERRLOC_ISR : (PMERRLOC Offset: 0x20) PMECC Error Location Interrupt Status Register -------- */
#define PMERRLOC_ISR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ISR) Computation Terminated Interrupt Status */
#define PMERRLOC_ISR_ERR_CNT_Pos 8
#define PMERRLOC_ISR_ERR_CNT_Msk (0x1fu << PMERRLOC_ISR_ERR_CNT_Pos) /**< \brief (PMERRLOC_ISR) Error Counter value */
/* -------- PMERRLOC_SIGMA[25] : (PMERRLOC Offset: 0x28) PMECC Error Location SIGMA x Register -------- */
#define PMERRLOC_SIGMA_SIGMA_Pos 0
#define PMERRLOC_SIGMA_SIGMA_Msk (0x3fffu << PMERRLOC_SIGMA_SIGMA_Pos) /**< \brief (PMERRLOC_SIGMA[25]) Coefficient of degree x in the SIGMA polynomial. */
/* -------- PMERRLOC_EL[24] : (PMERRLOC Offset: 0x8C) PMECC Error Location x Register -------- */
#define PMERRLOC_EL_ERRLOCN_Pos 0
#define PMERRLOC_EL_ERRLOCN_Msk (0x3fffu << PMERRLOC_EL_ERRLOCN_Pos) /**< \brief (PMERRLOC_EL[24]) Error Position within the Set {sector area, spare area} */

/*@}*/

#endif /* _SAM9X_PMERRLOC_COMPONENT_ */
