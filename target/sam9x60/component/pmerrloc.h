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
  __IO uint32_t PMERRLOC_ELCFG;   /**< \brief (Pmerrloc Offset: 0x000) Configuration Register */
  __I  uint32_t PMERRLOC_ELPRIM;  /**< \brief (Pmerrloc Offset: 0x004) Primitive Register */
  __IO uint32_t PMERRLOC_ELEN;    /**< \brief (Pmerrloc Offset: 0x008) Enable Register */
  __IO uint32_t PMERRLOC_ELDIS;   /**< \brief (Pmerrloc Offset: 0x00C) Disable Register */
  __IO uint32_t PMERRLOC_ELSR;    /**< \brief (Pmerrloc Offset: 0x010) Status Register */
  __O  uint32_t PMERRLOC_ELIER;   /**< \brief (Pmerrloc Offset: 0x014) Interrupt Enable Register */
  __O  uint32_t PMERRLOC_ELIDR;   /**< \brief (Pmerrloc Offset: 0x018) Interrupt Disable Register */
  __I  uint32_t PMERRLOC_ELIMR;   /**< \brief (Pmerrloc Offset: 0x01C) Interrupt Mask Register */
  __I  uint32_t PMERRLOC_ELISR;   /**< \brief (Pmerrloc Offset: 0x020) Interrupt Status Register */
  __I  uint32_t Reserved1[1];
  __I  uint32_t PMERRLOC_SIGMA0;  /**< \brief (Pmerrloc Offset: 0x028) SIGMA0 Register */
  __IO uint32_t PMERRLOC_SIGMA1;  /**< \brief (Pmerrloc Offset: 0x02C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA2;  /**< \brief (Pmerrloc Offset: 0x030) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA3;  /**< \brief (Pmerrloc Offset: 0x034) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA4;  /**< \brief (Pmerrloc Offset: 0x038) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA5;  /**< \brief (Pmerrloc Offset: 0x03C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA6;  /**< \brief (Pmerrloc Offset: 0x040) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA7;  /**< \brief (Pmerrloc Offset: 0x044) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA8;  /**< \brief (Pmerrloc Offset: 0x048) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA9;  /**< \brief (Pmerrloc Offset: 0x04C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA10; /**< \brief (Pmerrloc Offset: 0x050) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA11; /**< \brief (Pmerrloc Offset: 0x054) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA12; /**< \brief (Pmerrloc Offset: 0x058) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA13; /**< \brief (Pmerrloc Offset: 0x05C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA14; /**< \brief (Pmerrloc Offset: 0x060) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA15; /**< \brief (Pmerrloc Offset: 0x064) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA16; /**< \brief (Pmerrloc Offset: 0x068) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA17; /**< \brief (Pmerrloc Offset: 0x06C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA18; /**< \brief (Pmerrloc Offset: 0x070) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA19; /**< \brief (Pmerrloc Offset: 0x074) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA20; /**< \brief (Pmerrloc Offset: 0x078) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA21; /**< \brief (Pmerrloc Offset: 0x07C) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA22; /**< \brief (Pmerrloc Offset: 0x080) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA23; /**< \brief (Pmerrloc Offset: 0x084) SIGMA1 Register */
  __IO uint32_t PMERRLOC_SIGMA24; /**< \brief (Pmerrloc Offset: 0x088) SIGMA24 Register */
  __I  uint32_t PMERRLOC_EL[24];  /**< \brief (Pmerrloc Offset: 0x08C) Error Location 0 Register */
  __I  uint32_t Reserved2[68];
  __I  uint32_t PMERRLOC_VERSION; /**< \brief (Pmerrloc Offset: 0x1FC) Version Register */
} Pmerrloc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PMERRLOC_ELCFG : (PMERRLOC Offset: 0x000) Configuration Register -------- */
#define PMERRLOC_ELCFG_SECTORSZ (0x1u << 0) /**< \brief (PMERRLOC_ELCFG) Sector Size */
#define PMERRLOC_ELCFG_ERRNUM_Pos 16
#define PMERRLOC_ELCFG_ERRNUM_Msk (0x1fu << PMERRLOC_ELCFG_ERRNUM_Pos) /**< \brief (PMERRLOC_ELCFG) Number of Errors */
#define PMERRLOC_ELCFG_ERRNUM(value) ((PMERRLOC_ELCFG_ERRNUM_Msk & ((value) << PMERRLOC_ELCFG_ERRNUM_Pos)))
/* -------- PMERRLOC_ELPRIM : (PMERRLOC Offset: 0x004) Primitive Register -------- */
#define PMERRLOC_ELPRIM_PRIMITIV_Pos 0
#define PMERRLOC_ELPRIM_PRIMITIV_Msk (0xffffu << PMERRLOC_ELPRIM_PRIMITIV_Pos) /**< \brief (PMERRLOC_ELPRIM) Primitive Polynomial */
/* -------- PMERRLOC_ELEN : (PMERRLOC Offset: 0x008) Enable Register -------- */
#define PMERRLOC_ELEN_ENINIT_Pos 0
#define PMERRLOC_ELEN_ENINIT_Msk (0x3fffu << PMERRLOC_ELEN_ENINIT_Pos) /**< \brief (PMERRLOC_ELEN) Initial Number of Bits in the Codeword */
#define PMERRLOC_ELEN_ENINIT(value) ((PMERRLOC_ELEN_ENINIT_Msk & ((value) << PMERRLOC_ELEN_ENINIT_Pos)))
/* -------- PMERRLOC_ELDIS : (PMERRLOC Offset: 0x00C) Disable Register -------- */
#define PMERRLOC_ELDIS_DIS (0x1u << 0) /**< \brief (PMERRLOC_ELDIS) Disable Error Location Engine */
/* -------- PMERRLOC_ELSR : (PMERRLOC Offset: 0x010) Status Register -------- */
#define PMERRLOC_ELSR_BUSY (0x1u << 0) /**< \brief (PMERRLOC_ELSR) Error Location Engine Busy */
/* -------- PMERRLOC_ELIER : (PMERRLOC Offset: 0x014) Interrupt Enable Register -------- */
#define PMERRLOC_ELIER_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIER) Computation Terminated Interrupt Enable */
/* -------- PMERRLOC_ELIDR : (PMERRLOC Offset: 0x018) Interrupt Disable Register -------- */
#define PMERRLOC_ELIDR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIDR) Computation Terminated Interrupt Disable */
/* -------- PMERRLOC_ELIMR : (PMERRLOC Offset: 0x01C) Interrupt Mask Register -------- */
#define PMERRLOC_ELIMR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELIMR) Computation Terminated Interrupt Mask */
/* -------- PMERRLOC_ELISR : (PMERRLOC Offset: 0x020) Interrupt Status Register -------- */
#define PMERRLOC_ELISR_DONE (0x1u << 0) /**< \brief (PMERRLOC_ELISR) Computation Terminated Interrupt Status */
#define PMERRLOC_ELISR_ERR_CNT_Pos 8
#define PMERRLOC_ELISR_ERR_CNT_Msk (0x1fu << PMERRLOC_ELISR_ERR_CNT_Pos) /**< \brief (PMERRLOC_ELISR) Error Counter Value */
/* -------- PMERRLOC_SIGMA0 : (PMERRLOC Offset: 0x028) SIGMA0 Register -------- */
#define PMERRLOC_SIGMA0_SIGMA0_Pos 0
#define PMERRLOC_SIGMA0_SIGMA0_Msk (0x3fffu << PMERRLOC_SIGMA0_SIGMA0_Pos) /**< \brief (PMERRLOC_SIGMA0) Coefficient of Degree 0 in the SIGMA Polynomial */
/* -------- PMERRLOC_SIGMA1 : (PMERRLOC Offset: 0x02C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA1_SIGMA1_Pos 0
#define PMERRLOC_SIGMA1_SIGMA1_Msk (0x3fffu << PMERRLOC_SIGMA1_SIGMA1_Pos) /**< \brief (PMERRLOC_SIGMA1) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA1_SIGMA1(value) ((PMERRLOC_SIGMA1_SIGMA1_Msk & ((value) << PMERRLOC_SIGMA1_SIGMA1_Pos)))
/* -------- PMERRLOC_SIGMA2 : (PMERRLOC Offset: 0x030) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA2_SIGMA2_Pos 0
#define PMERRLOC_SIGMA2_SIGMA2_Msk (0x3fffu << PMERRLOC_SIGMA2_SIGMA2_Pos) /**< \brief (PMERRLOC_SIGMA2) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA2_SIGMA2(value) ((PMERRLOC_SIGMA2_SIGMA2_Msk & ((value) << PMERRLOC_SIGMA2_SIGMA2_Pos)))
/* -------- PMERRLOC_SIGMA3 : (PMERRLOC Offset: 0x034) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA3_SIGMA3_Pos 0
#define PMERRLOC_SIGMA3_SIGMA3_Msk (0x3fffu << PMERRLOC_SIGMA3_SIGMA3_Pos) /**< \brief (PMERRLOC_SIGMA3) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA3_SIGMA3(value) ((PMERRLOC_SIGMA3_SIGMA3_Msk & ((value) << PMERRLOC_SIGMA3_SIGMA3_Pos)))
/* -------- PMERRLOC_SIGMA4 : (PMERRLOC Offset: 0x038) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA4_SIGMA4_Pos 0
#define PMERRLOC_SIGMA4_SIGMA4_Msk (0x3fffu << PMERRLOC_SIGMA4_SIGMA4_Pos) /**< \brief (PMERRLOC_SIGMA4) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA4_SIGMA4(value) ((PMERRLOC_SIGMA4_SIGMA4_Msk & ((value) << PMERRLOC_SIGMA4_SIGMA4_Pos)))
/* -------- PMERRLOC_SIGMA5 : (PMERRLOC Offset: 0x03C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA5_SIGMA5_Pos 0
#define PMERRLOC_SIGMA5_SIGMA5_Msk (0x3fffu << PMERRLOC_SIGMA5_SIGMA5_Pos) /**< \brief (PMERRLOC_SIGMA5) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA5_SIGMA5(value) ((PMERRLOC_SIGMA5_SIGMA5_Msk & ((value) << PMERRLOC_SIGMA5_SIGMA5_Pos)))
/* -------- PMERRLOC_SIGMA6 : (PMERRLOC Offset: 0x040) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA6_SIGMA6_Pos 0
#define PMERRLOC_SIGMA6_SIGMA6_Msk (0x3fffu << PMERRLOC_SIGMA6_SIGMA6_Pos) /**< \brief (PMERRLOC_SIGMA6) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA6_SIGMA6(value) ((PMERRLOC_SIGMA6_SIGMA6_Msk & ((value) << PMERRLOC_SIGMA6_SIGMA6_Pos)))
/* -------- PMERRLOC_SIGMA7 : (PMERRLOC Offset: 0x044) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA7_SIGMA7_Pos 0
#define PMERRLOC_SIGMA7_SIGMA7_Msk (0x3fffu << PMERRLOC_SIGMA7_SIGMA7_Pos) /**< \brief (PMERRLOC_SIGMA7) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA7_SIGMA7(value) ((PMERRLOC_SIGMA7_SIGMA7_Msk & ((value) << PMERRLOC_SIGMA7_SIGMA7_Pos)))
/* -------- PMERRLOC_SIGMA8 : (PMERRLOC Offset: 0x048) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA8_SIGMA8_Pos 0
#define PMERRLOC_SIGMA8_SIGMA8_Msk (0x3fffu << PMERRLOC_SIGMA8_SIGMA8_Pos) /**< \brief (PMERRLOC_SIGMA8) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA8_SIGMA8(value) ((PMERRLOC_SIGMA8_SIGMA8_Msk & ((value) << PMERRLOC_SIGMA8_SIGMA8_Pos)))
/* -------- PMERRLOC_SIGMA9 : (PMERRLOC Offset: 0x04C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA9_SIGMA9_Pos 0
#define PMERRLOC_SIGMA9_SIGMA9_Msk (0x3fffu << PMERRLOC_SIGMA9_SIGMA9_Pos) /**< \brief (PMERRLOC_SIGMA9) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA9_SIGMA9(value) ((PMERRLOC_SIGMA9_SIGMA9_Msk & ((value) << PMERRLOC_SIGMA9_SIGMA9_Pos)))
/* -------- PMERRLOC_SIGMA10 : (PMERRLOC Offset: 0x050) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA10_SIGMA10_Pos 0
#define PMERRLOC_SIGMA10_SIGMA10_Msk (0x3fffu << PMERRLOC_SIGMA10_SIGMA10_Pos) /**< \brief (PMERRLOC_SIGMA10) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA10_SIGMA10(value) ((PMERRLOC_SIGMA10_SIGMA10_Msk & ((value) << PMERRLOC_SIGMA10_SIGMA10_Pos)))
/* -------- PMERRLOC_SIGMA11 : (PMERRLOC Offset: 0x054) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA11_SIGMA11_Pos 0
#define PMERRLOC_SIGMA11_SIGMA11_Msk (0x3fffu << PMERRLOC_SIGMA11_SIGMA11_Pos) /**< \brief (PMERRLOC_SIGMA11) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA11_SIGMA11(value) ((PMERRLOC_SIGMA11_SIGMA11_Msk & ((value) << PMERRLOC_SIGMA11_SIGMA11_Pos)))
/* -------- PMERRLOC_SIGMA12 : (PMERRLOC Offset: 0x058) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA12_SIGMA12_Pos 0
#define PMERRLOC_SIGMA12_SIGMA12_Msk (0x3fffu << PMERRLOC_SIGMA12_SIGMA12_Pos) /**< \brief (PMERRLOC_SIGMA12) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA12_SIGMA12(value) ((PMERRLOC_SIGMA12_SIGMA12_Msk & ((value) << PMERRLOC_SIGMA12_SIGMA12_Pos)))
/* -------- PMERRLOC_SIGMA13 : (PMERRLOC Offset: 0x05C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA13_SIGMA13_Pos 0
#define PMERRLOC_SIGMA13_SIGMA13_Msk (0x3fffu << PMERRLOC_SIGMA13_SIGMA13_Pos) /**< \brief (PMERRLOC_SIGMA13) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA13_SIGMA13(value) ((PMERRLOC_SIGMA13_SIGMA13_Msk & ((value) << PMERRLOC_SIGMA13_SIGMA13_Pos)))
/* -------- PMERRLOC_SIGMA14 : (PMERRLOC Offset: 0x060) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA14_SIGMA14_Pos 0
#define PMERRLOC_SIGMA14_SIGMA14_Msk (0x3fffu << PMERRLOC_SIGMA14_SIGMA14_Pos) /**< \brief (PMERRLOC_SIGMA14) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA14_SIGMA14(value) ((PMERRLOC_SIGMA14_SIGMA14_Msk & ((value) << PMERRLOC_SIGMA14_SIGMA14_Pos)))
/* -------- PMERRLOC_SIGMA15 : (PMERRLOC Offset: 0x064) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA15_SIGMA15_Pos 0
#define PMERRLOC_SIGMA15_SIGMA15_Msk (0x3fffu << PMERRLOC_SIGMA15_SIGMA15_Pos) /**< \brief (PMERRLOC_SIGMA15) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA15_SIGMA15(value) ((PMERRLOC_SIGMA15_SIGMA15_Msk & ((value) << PMERRLOC_SIGMA15_SIGMA15_Pos)))
/* -------- PMERRLOC_SIGMA16 : (PMERRLOC Offset: 0x068) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA16_SIGMA16_Pos 0
#define PMERRLOC_SIGMA16_SIGMA16_Msk (0x3fffu << PMERRLOC_SIGMA16_SIGMA16_Pos) /**< \brief (PMERRLOC_SIGMA16) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA16_SIGMA16(value) ((PMERRLOC_SIGMA16_SIGMA16_Msk & ((value) << PMERRLOC_SIGMA16_SIGMA16_Pos)))
/* -------- PMERRLOC_SIGMA17 : (PMERRLOC Offset: 0x06C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA17_SIGMA17_Pos 0
#define PMERRLOC_SIGMA17_SIGMA17_Msk (0x3fffu << PMERRLOC_SIGMA17_SIGMA17_Pos) /**< \brief (PMERRLOC_SIGMA17) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA17_SIGMA17(value) ((PMERRLOC_SIGMA17_SIGMA17_Msk & ((value) << PMERRLOC_SIGMA17_SIGMA17_Pos)))
/* -------- PMERRLOC_SIGMA18 : (PMERRLOC Offset: 0x070) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA18_SIGMA18_Pos 0
#define PMERRLOC_SIGMA18_SIGMA18_Msk (0x3fffu << PMERRLOC_SIGMA18_SIGMA18_Pos) /**< \brief (PMERRLOC_SIGMA18) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA18_SIGMA18(value) ((PMERRLOC_SIGMA18_SIGMA18_Msk & ((value) << PMERRLOC_SIGMA18_SIGMA18_Pos)))
/* -------- PMERRLOC_SIGMA19 : (PMERRLOC Offset: 0x074) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA19_SIGMA19_Pos 0
#define PMERRLOC_SIGMA19_SIGMA19_Msk (0x3fffu << PMERRLOC_SIGMA19_SIGMA19_Pos) /**< \brief (PMERRLOC_SIGMA19) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA19_SIGMA19(value) ((PMERRLOC_SIGMA19_SIGMA19_Msk & ((value) << PMERRLOC_SIGMA19_SIGMA19_Pos)))
/* -------- PMERRLOC_SIGMA20 : (PMERRLOC Offset: 0x078) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA20_SIGMA20_Pos 0
#define PMERRLOC_SIGMA20_SIGMA20_Msk (0x3fffu << PMERRLOC_SIGMA20_SIGMA20_Pos) /**< \brief (PMERRLOC_SIGMA20) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA20_SIGMA20(value) ((PMERRLOC_SIGMA20_SIGMA20_Msk & ((value) << PMERRLOC_SIGMA20_SIGMA20_Pos)))
/* -------- PMERRLOC_SIGMA21 : (PMERRLOC Offset: 0x07C) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA21_SIGMA21_Pos 0
#define PMERRLOC_SIGMA21_SIGMA21_Msk (0x3fffu << PMERRLOC_SIGMA21_SIGMA21_Pos) /**< \brief (PMERRLOC_SIGMA21) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA21_SIGMA21(value) ((PMERRLOC_SIGMA21_SIGMA21_Msk & ((value) << PMERRLOC_SIGMA21_SIGMA21_Pos)))
/* -------- PMERRLOC_SIGMA22 : (PMERRLOC Offset: 0x080) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA22_SIGMA22_Pos 0
#define PMERRLOC_SIGMA22_SIGMA22_Msk (0x3fffu << PMERRLOC_SIGMA22_SIGMA22_Pos) /**< \brief (PMERRLOC_SIGMA22) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA22_SIGMA22(value) ((PMERRLOC_SIGMA22_SIGMA22_Msk & ((value) << PMERRLOC_SIGMA22_SIGMA22_Pos)))
/* -------- PMERRLOC_SIGMA23 : (PMERRLOC Offset: 0x084) SIGMA1 Register -------- */
#define PMERRLOC_SIGMA23_SIGMA23_Pos 0
#define PMERRLOC_SIGMA23_SIGMA23_Msk (0x3fffu << PMERRLOC_SIGMA23_SIGMA23_Pos) /**< \brief (PMERRLOC_SIGMA23) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA23_SIGMA23(value) ((PMERRLOC_SIGMA23_SIGMA23_Msk & ((value) << PMERRLOC_SIGMA23_SIGMA23_Pos)))
/* -------- PMERRLOC_SIGMA24 : (PMERRLOC Offset: 0x088) SIGMA24 Register -------- */
#define PMERRLOC_SIGMA24_SIGMA24_Pos 0
#define PMERRLOC_SIGMA24_SIGMA24_Msk (0x3fffu << PMERRLOC_SIGMA24_SIGMA24_Pos) /**< \brief (PMERRLOC_SIGMA24) Coefficient of Degree x in the SIGMA Polynomial. */
#define PMERRLOC_SIGMA24_SIGMA24(value) ((PMERRLOC_SIGMA24_SIGMA24_Msk & ((value) << PMERRLOC_SIGMA24_SIGMA24_Pos)))
/* -------- PMERRLOC_EL[24] : (PMERRLOC Offset: 0x08C) Error Location 0 Register -------- */
#define PMERRLOC_EL_ERRLOCN_Pos 0
#define PMERRLOC_EL_ERRLOCN_Msk (0x3fffu << PMERRLOC_EL_ERRLOCN_Pos) /**< \brief (PMERRLOC_EL[24]) Error Position within the Set {sector area, spare area}. */
/* -------- PMERRLOC_VERSION : (PMERRLOC Offset: 0x1FC) Version Register -------- */
#define PMERRLOC_VERSION_VERSION_Pos 0
#define PMERRLOC_VERSION_VERSION_Msk (0xfffu << PMERRLOC_VERSION_VERSION_Pos) /**< \brief (PMERRLOC_VERSION) Version of the Hardware Module */
#define PMERRLOC_VERSION_MFN_Pos 16
#define PMERRLOC_VERSION_MFN_Msk (0x7u << PMERRLOC_VERSION_MFN_Pos) /**< \brief (PMERRLOC_VERSION) Metal Fix Number */

/*@}*/


#endif /* _SAM9X_PMERRLOC_COMPONENT_ */
