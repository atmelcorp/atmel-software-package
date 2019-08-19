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

#ifndef _SAM9X_PMERRLOC_COMPONENT_
#define _SAM9X_PMERRLOC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Programmable Multibit ECC Error Location */
/* ============================================================================= */
/** \addtogroup SAM9X_PMERRLOC Programmable Multibit ECC Error Location */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pmerrloc hardware registers */
typedef struct {
  __IO uint32_t PMERRLOC_CFG;     /**< \brief (Pmerrloc Offset: 0x0) Configuration Register */
  __I  uint32_t PMERRLOC_PRIM;    /**< \brief (Pmerrloc Offset: 0x4) Primitive Register */
  __IO uint32_t PMERRLOC_EN;      /**< \brief (Pmerrloc Offset: 0x8) Enable Register */
  __IO uint32_t PMERRLOC_DIS;     /**< \brief (Pmerrloc Offset: 0xC) Disable Register */
  __IO uint32_t PMERRLOC_SR;      /**< \brief (Pmerrloc Offset: 0x10) Status Register */
  __O  uint32_t PMERRLOC_IER;     /**< \brief (Pmerrloc Offset: 0x14) Interrupt Enable Register */
  __O  uint32_t PMERRLOC_IDR;     /**< \brief (Pmerrloc Offset: 0x18) Interrupt Disable Register */
  __I  uint32_t PMERRLOC_IMR;     /**< \brief (Pmerrloc Offset: 0x1C) Interrupt Mask Register */
  __I  uint32_t PMERRLOC_ISR;     /**< \brief (Pmerrloc Offset: 0x20) Interrupt Status Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t PMERRLOC_SIGMA[25];
  __I  uint32_t PMERRLOC_EL[24];  /**< \brief (Pmerrloc Offset: 0x8C) Error Location 0 Register */
} Pmerrloc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PMERRLOC_ELCFG : (PMERRLOC Offset: 0x0) Configuration Register -------- */
#define PMERRLOC_CFG_SECTORSZ (0x1u << 0) /**< \brief (PMERRLOC_ELCFG) Sector Size */
#define PMERRLOC_CFG_ERRNUM_Pos 16
#define PMERRLOC_CFG_ERRNUM_Msk (0x1fu << PMERRLOC_CFG_ERRNUM_Pos) /**< \brief (PMERRLOC_ELCFG) Number of Errors */
#define PMERRLOC_CFG_ERRNUM(value) ((PMERRLOC_CFG_ERRNUM_Msk & ((value) << PMERRLOC_CFG_ERRNUM_Pos)))
/* -------- PMERRLOC_ELPRIM : (PMERRLOC Offset: 0x4) Primitive Register -------- */
#define PMERRLOC_PRIM_PRIMITIV_Pos 0
#define PMERRLOC_PRIM_PRIMITIV_Msk (0xffffu << PMERRLOC_PRIM_PRIMITIV_Pos) /**< \brief (PMERRLOC_ELPRIM) Primitive Polynomial */
/* -------- PMERRLOC_ELEN : (PMERRLOC Offset: 0x8) Enable Register -------- */
#define PMERRLOC_EN_ENINIT_Pos 0
#define PMERRLOC_EN_ENINIT_Msk (0x3fffu << PMERRLOC_EN_ENINIT_Pos) /**< \brief (PMERRLOC_ELEN) Initial Number of Bits in the Codeword */
#define PMERRLOC_EN_ENINIT(value) ((PMERRLOC_EN_ENINIT_Msk & ((value) << PMERRLOC_EN_ENINIT_Pos)))
/* -------- PMERRLOC_ELDIS : (PMERRLOC Offset: 0xC) Disable Register -------- */
#define PMERRLOC_DIS_DIS (0x1u << 0) /**< \brief (PMERRLOC_ELDIS) Disable Error Location Engine */
/* -------- PMERRLOC_ELSR : (PMERRLOC Offset: 0x10) Status Register -------- */
#define PMERRLOC_SR_BUSY (0x1u << 0) /**< \brief (PMERRLOC_ELLSR) Error Location Engine Busy */
/* -------- PMERRLOC_ELIER : (PMERRLOC Offset: 0x14) Interrupt Enable Register -------- */
#define PMERRLOC_IER_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIER) Computation Terminated Interrupt Enable */
/* -------- PMERRLOC_ELIDR : (PMERRLOC Offset: 0x18) Interrupt Disable Register -------- */
#define PMERRLOC_IDR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIDR) Computation Terminated Interrupt Disable */
/* -------- PMERRLOC_ELIMR : (PMERRLOC Offset: 0x1C) Interrupt Mask Register -------- */
#define PMERRLOC_IMR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIMR) Computation Terminated Interrupt Mask */
/* -------- PMERRLOC_ELISR : (PMERRLOC Offset: 0x20) Interrupt Status Register -------- */
#define PMERRLOC_ISR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELISR) Computation Terminated Interrupt Status */
#define PMERRLOC_ISR_ERR_CNT_Pos 8
#define PMERRLOC_ISR_ERR_CNT_Msk (0x1fu << PMERRLOC_ISR_ERR_CNT_Pos) /**< \brief (PMERRLOC_ELISR) Error Counter Value */
/* -------- PMERRLOC_SIGMA0 : (PMERRLOC Offset: 0x28) SIGMA0 Register -------- */
#define PMERRLOC_SIGMA0_SIGMA0_Pos 0
#define PMERRLOC_SIGMA0_SIGMA0_Msk (0x3fffu << PMERRLOC_SIGMA0_SIGMA0_Pos) /**< \brief (PMERRLOC_SIGMA0) Coefficient of Degree 0 in the SIGMA Polynomial */
/* -------- PMERRLOC_SIGMA1 : (PMERRLOC Offset: 0x2C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA1_SIGMA1_Pos 0
#define PMERRLOC_SIGMA1_SIGMA1_Msk (0x3fffu << PMERRLOC_SIGMA1_SIGMA1_Pos) /**< \brief (PMERRLOC_SIGMA1) Coefficient of Degree 1 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA1_SIGMA1(value) ((PMERRLOC_SIGMA1_SIGMA1_Msk & ((value) << PMERRLOC_SIGMA1_SIGMA1_Pos)))
/* -------- PMERRLOC_SIGMA2 : (PMERRLOC Offset: 0x30) SIGMA2 Register -------- */
#define PMERRLOC_SIGMA2_SIGMA2_Pos 0
#define PMERRLOC_SIGMA2_SIGMA2_Msk (0x3fffu << PMERRLOC_SIGMA2_SIGMA2_Pos) /**< \brief (PMERRLOC_SIGMA2) Coefficient of Degree 2 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA2_SIGMA2(value) ((PMERRLOC_SIGMA2_SIGMA2_Msk & ((value) << PMERRLOC_SIGMA2_SIGMA2_Pos)))
/* -------- PMERRLOC_SIGMA3 : (PMERRLOC Offset: 0x34) SIGMA3 Register -------- */
#define PMERRLOC_SIGMA3_SIGMA3_Pos 0
#define PMERRLOC_SIGMA3_SIGMA3_Msk (0x3fffu << PMERRLOC_SIGMA3_SIGMA3_Pos) /**< \brief (PMERRLOC_SIGMA3) Coefficient of Degree 3 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA3_SIGMA3(value) ((PMERRLOC_SIGMA3_SIGMA3_Msk & ((value) << PMERRLOC_SIGMA3_SIGMA3_Pos)))
/* -------- PMERRLOC_SIGMA4 : (PMERRLOC Offset: 0x38) SIGMA4 Register -------- */
#define PMERRLOC_SIGMA4_SIGMA4_Pos 0
#define PMERRLOC_SIGMA4_SIGMA4_Msk (0x3fffu << PMERRLOC_SIGMA4_SIGMA4_Pos) /**< \brief (PMERRLOC_SIGMA4) Coefficient of Degree 4 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA4_SIGMA4(value) ((PMERRLOC_SIGMA4_SIGMA4_Msk & ((value) << PMERRLOC_SIGMA4_SIGMA4_Pos)))
/* -------- PMERRLOC_SIGMA5 : (PMERRLOC Offset: 0x3C) SIGMA5 Register -------- */
#define PMERRLOC_SIGMA5_SIGMA5_Pos 0
#define PMERRLOC_SIGMA5_SIGMA5_Msk (0x3fffu << PMERRLOC_SIGMA5_SIGMA5_Pos) /**< \brief (PMERRLOC_SIGMA5) Coefficient of Degree 5 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA5_SIGMA5(value) ((PMERRLOC_SIGMA5_SIGMA5_Msk & ((value) << PMERRLOC_SIGMA5_SIGMA5_Pos)))
/* -------- PMERRLOC_SIGMA6 : (PMERRLOC Offset: 0x40) SIGMA6 Register -------- */
#define PMERRLOC_SIGMA6_SIGMA6_Pos 0
#define PMERRLOC_SIGMA6_SIGMA6_Msk (0x3fffu << PMERRLOC_SIGMA6_SIGMA6_Pos) /**< \brief (PMERRLOC_SIGMA6) Coefficient of Degree 6 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA6_SIGMA6(value) ((PMERRLOC_SIGMA6_SIGMA6_Msk & ((value) << PMERRLOC_SIGMA6_SIGMA6_Pos)))
/* -------- PMERRLOC_SIGMA7 : (PMERRLOC Offset: 0x44) SIGMA7 Register -------- */
#define PMERRLOC_SIGMA7_SIGMA7_Pos 0
#define PMERRLOC_SIGMA7_SIGMA7_Msk (0x3fffu << PMERRLOC_SIGMA7_SIGMA7_Pos) /**< \brief (PMERRLOC_SIGMA7) Coefficient of Degree 7 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA7_SIGMA7(value) ((PMERRLOC_SIGMA7_SIGMA7_Msk & ((value) << PMERRLOC_SIGMA7_SIGMA7_Pos)))
/* -------- PMERRLOC_SIGMA8 : (PMERRLOC Offset: 0x48) SIGMA8 Register -------- */
#define PMERRLOC_SIGMA8_SIGMA8_Pos 0
#define PMERRLOC_SIGMA8_SIGMA8_Msk (0x3fffu << PMERRLOC_SIGMA8_SIGMA8_Pos) /**< \brief (PMERRLOC_SIGMA8) Coefficient of Degree 8 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA8_SIGMA8(value) ((PMERRLOC_SIGMA8_SIGMA8_Msk & ((value) << PMERRLOC_SIGMA8_SIGMA8_Pos)))
/* -------- PMERRLOC_SIGMA9 : (PMERRLOC Offset: 0x4C) SIGMA9 Register -------- */
#define PMERRLOC_SIGMA9_SIGMA9_Pos 0
#define PMERRLOC_SIGMA9_SIGMA9_Msk (0x3fffu << PMERRLOC_SIGMA9_SIGMA9_Pos) /**< \brief (PMERRLOC_SIGMA9) Coefficient of Degree 9 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA9_SIGMA9(value) ((PMERRLOC_SIGMA9_SIGMA9_Msk & ((value) << PMERRLOC_SIGMA9_SIGMA9_Pos)))
/* -------- PMERRLOC_SIGMA10 : (PMERRLOC Offset: 0x50) SIGMA10 Register -------- */
#define PMERRLOC_SIGMA10_SIGMA10_Pos 0
#define PMERRLOC_SIGMA10_SIGMA10_Msk (0x3fffu << PMERRLOC_SIGMA10_SIGMA10_Pos) /**< \brief (PMERRLOC_SIGMA10) Coefficient of Degree 10 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA10_SIGMA10(value) ((PMERRLOC_SIGMA10_SIGMA10_Msk & ((value) << PMERRLOC_SIGMA10_SIGMA10_Pos)))
/* -------- PMERRLOC_SIGMA11 : (PMERRLOC Offset: 0x54) SIGMA11 Register -------- */
#define PMERRLOC_SIGMA11_SIGMA11_Pos 0
#define PMERRLOC_SIGMA11_SIGMA11_Msk (0x3fffu << PMERRLOC_SIGMA11_SIGMA11_Pos) /**< \brief (PMERRLOC_SIGMA11) Coefficient of Degree 11 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA11_SIGMA11(value) ((PMERRLOC_SIGMA11_SIGMA11_Msk & ((value) << PMERRLOC_SIGMA11_SIGMA11_Pos)))
/* -------- PMERRLOC_SIGMA12 : (PMERRLOC Offset: 0x58) SIGMA12 Register -------- */
#define PMERRLOC_SIGMA12_SIGMA12_Pos 0
#define PMERRLOC_SIGMA12_SIGMA12_Msk (0x3fffu << PMERRLOC_SIGMA12_SIGMA12_Pos) /**< \brief (PMERRLOC_SIGMA12) Coefficient of Degree 12 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA12_SIGMA12(value) ((PMERRLOC_SIGMA12_SIGMA12_Msk & ((value) << PMERRLOC_SIGMA12_SIGMA12_Pos)))
/* -------- PMERRLOC_SIGMA13 : (PMERRLOC Offset: 0x5C) SIGMA13 Register -------- */
#define PMERRLOC_SIGMA13_SIGMA13_Pos 0
#define PMERRLOC_SIGMA13_SIGMA13_Msk (0x3fffu << PMERRLOC_SIGMA13_SIGMA13_Pos) /**< \brief (PMERRLOC_SIGMA13) Coefficient of Degree 13 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA13_SIGMA13(value) ((PMERRLOC_SIGMA13_SIGMA13_Msk & ((value) << PMERRLOC_SIGMA13_SIGMA13_Pos)))
/* -------- PMERRLOC_SIGMA14 : (PMERRLOC Offset: 0x60) SIGMA14 Register -------- */
#define PMERRLOC_SIGMA14_SIGMA14_Pos 0
#define PMERRLOC_SIGMA14_SIGMA14_Msk (0x3fffu << PMERRLOC_SIGMA14_SIGMA14_Pos) /**< \brief (PMERRLOC_SIGMA14) Coefficient of Degree 14 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA14_SIGMA14(value) ((PMERRLOC_SIGMA14_SIGMA14_Msk & ((value) << PMERRLOC_SIGMA14_SIGMA14_Pos)))
/* -------- PMERRLOC_SIGMA15 : (PMERRLOC Offset: 0x64) SIGMA15 Register -------- */
#define PMERRLOC_SIGMA15_SIGMA15_Pos 0
#define PMERRLOC_SIGMA15_SIGMA15_Msk (0x3fffu << PMERRLOC_SIGMA15_SIGMA15_Pos) /**< \brief (PMERRLOC_SIGMA15) Coefficient of Degree 15 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA15_SIGMA15(value) ((PMERRLOC_SIGMA15_SIGMA15_Msk & ((value) << PMERRLOC_SIGMA15_SIGMA15_Pos)))
/* -------- PMERRLOC_SIGMA16 : (PMERRLOC Offset: 0x68) SIGMA16 Register -------- */
#define PMERRLOC_SIGMA16_SIGMA16_Pos 0
#define PMERRLOC_SIGMA16_SIGMA16_Msk (0x3fffu << PMERRLOC_SIGMA16_SIGMA16_Pos) /**< \brief (PMERRLOC_SIGMA16) Coefficient of Degree 16 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA16_SIGMA16(value) ((PMERRLOC_SIGMA16_SIGMA16_Msk & ((value) << PMERRLOC_SIGMA16_SIGMA16_Pos)))
/* -------- PMERRLOC_SIGMA17 : (PMERRLOC Offset: 0x6C) SIGMA17 Register -------- */
#define PMERRLOC_SIGMA17_SIGMA17_Pos 0
#define PMERRLOC_SIGMA17_SIGMA17_Msk (0x3fffu << PMERRLOC_SIGMA17_SIGMA17_Pos) /**< \brief (PMERRLOC_SIGMA17) Coefficient of Degree 17 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA17_SIGMA17(value) ((PMERRLOC_SIGMA17_SIGMA17_Msk & ((value) << PMERRLOC_SIGMA17_SIGMA17_Pos)))
/* -------- PMERRLOC_SIGMA18 : (PMERRLOC Offset: 0x70) SIGMA18 Register -------- */
#define PMERRLOC_SIGMA18_SIGMA18_Pos 0
#define PMERRLOC_SIGMA18_SIGMA18_Msk (0x3fffu << PMERRLOC_SIGMA18_SIGMA18_Pos) /**< \brief (PMERRLOC_SIGMA18) Coefficient of Degree 18 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA18_SIGMA18(value) ((PMERRLOC_SIGMA18_SIGMA18_Msk & ((value) << PMERRLOC_SIGMA18_SIGMA18_Pos)))
/* -------- PMERRLOC_SIGMA19 : (PMERRLOC Offset: 0x74) SIGMA19 Register -------- */
#define PMERRLOC_SIGMA19_SIGMA19_Pos 0
#define PMERRLOC_SIGMA19_SIGMA19_Msk (0x3fffu << PMERRLOC_SIGMA19_SIGMA19_Pos) /**< \brief (PMERRLOC_SIGMA19) Coefficient of Degree 19 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA19_SIGMA19(value) ((PMERRLOC_SIGMA19_SIGMA19_Msk & ((value) << PMERRLOC_SIGMA19_SIGMA19_Pos)))
/* -------- PMERRLOC_SIGMA20 : (PMERRLOC Offset: 0x78) SIGMA20 Register -------- */
#define PMERRLOC_SIGMA20_SIGMA20_Pos 0
#define PMERRLOC_SIGMA20_SIGMA20_Msk (0x3fffu << PMERRLOC_SIGMA20_SIGMA20_Pos) /**< \brief (PMERRLOC_SIGMA20) Coefficient of Degree 20 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA20_SIGMA20(value) ((PMERRLOC_SIGMA20_SIGMA20_Msk & ((value) << PMERRLOC_SIGMA20_SIGMA20_Pos)))
/* -------- PMERRLOC_SIGMA21 : (PMERRLOC Offset: 0x7C) SIGMA21 Register -------- */
#define PMERRLOC_SIGMA21_SIGMA21_Pos 0
#define PMERRLOC_SIGMA21_SIGMA21_Msk (0x3fffu << PMERRLOC_SIGMA21_SIGMA21_Pos) /**< \brief (PMERRLOC_SIGMA21) Coefficient of Degree 21 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA21_SIGMA21(value) ((PMERRLOC_SIGMA21_SIGMA21_Msk & ((value) << PMERRLOC_SIGMA21_SIGMA21_Pos)))
/* -------- PMERRLOC_SIGMA22 : (PMERRLOC Offset: 0x80) SIGMA22 Register -------- */
#define PMERRLOC_SIGMA22_SIGMA22_Pos 0
#define PMERRLOC_SIGMA22_SIGMA22_Msk (0x3fffu << PMERRLOC_SIGMA22_SIGMA22_Pos) /**< \brief (PMERRLOC_SIGMA22) Coefficient of Degree 22 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA22_SIGMA22(value) ((PMERRLOC_SIGMA22_SIGMA22_Msk & ((value) << PMERRLOC_SIGMA22_SIGMA22_Pos)))
/* -------- PMERRLOC_SIGMA23 : (PMERRLOC Offset: 0x84) SIGMA23 Register -------- */
#define PMERRLOC_SIGMA23_SIGMA23_Pos 0
#define PMERRLOC_SIGMA23_SIGMA23_Msk (0x3fffu << PMERRLOC_SIGMA23_SIGMA23_Pos) /**< \brief (PMERRLOC_SIGMA23) Coefficient of Degree 23 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA23_SIGMA23(value) ((PMERRLOC_SIGMA23_SIGMA23_Msk & ((value) << PMERRLOC_SIGMA23_SIGMA23_Pos)))
/* -------- PMERRLOC_SIGMA24 : (PMERRLOC Offset: 0x88) SIGMA24 Register -------- */
#define PMERRLOC_SIGMA24_SIGMA24_Pos 0
#define PMERRLOC_SIGMA24_SIGMA24_Msk (0x3fffu << PMERRLOC_SIGMA24_SIGMA24_Pos) /**< \brief (PMERRLOC_SIGMA24) Coefficient of Degree 24 in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA24_SIGMA24(value) ((PMERRLOC_SIGMA24_SIGMA24_Msk & ((value) << PMERRLOC_SIGMA24_SIGMA24_Pos)))
/* -------- PMERRLOC_EL[24] : (PMERRLOC Offset: 0x8C) Error Location 0 Register -------- */
#define PMERRLOC_EL_ERRLOCN_Pos 0
#define PMERRLOC_EL_ERRLOCN_Msk (0x3fffu << PMERRLOC_EL_ERRLOCN_Pos) /**< \brief (PMERRLOC_EL[24]) Error Position within the Set {sector area, spare area}. */

/*@}*/


#endif /* _SAM9X_PMERRLOC_COMPONENT_ */
