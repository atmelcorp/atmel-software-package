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

#ifndef _SAM9X_GFX2D_COMPONENT_
#define _SAM9X_GFX2D_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR 2D Graphics Engine */
/* ============================================================================= */
/** \addtogroup SAM9X_GFX2D 2D Graphics Engine */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Gfx2dChid hardware registers */
typedef struct {
  __IO uint32_t GFX2D_PA;     /**< \brief (Gfx2dChid Offset: 0x0) Surface Physical Address Register */
  __IO uint32_t GFX2D_PITCH;  /**< \brief (Gfx2dChid Offset: 0x4) Surface Pitch Register */
  __IO uint32_t GFX2D_CFG;    /**< \brief (Gfx2dChid Offset: 0x8) Surface Configuration Register */
  __I  uint32_t Reserved1[1];
} Gfx2dChid;
/** \brief Gfx2dSub0 hardware registers */
typedef struct {
  __IO uint32_t GFX2D_PC; /**< \brief (Gfx2dSub0 Offset: 0x0) Performance Configuration 0 Register */
  __I  uint32_t GFX2D_MC; /**< \brief (Gfx2dSub0 Offset: 0x4) Metrics Counter 0 Register */
} Gfx2dSub0;
/** \brief Gfx2d hardware registers */
#define GFX2DSUB0_NUMBER 2
#define GFX2DCHID_NUMBER 4
typedef struct {
  __IO uint32_t  GFX2D_GC;                     /**< \brief (Gfx2d Offset: 0x0) Global Configuration Register */
  __O  uint32_t  GFX2D_GE;                     /**< \brief (Gfx2d Offset: 0x4) Global Enable Register */
  __O  uint32_t  GFX2D_GD;                     /**< \brief (Gfx2d Offset: 0x8) Global Disable Register */
  __I  uint32_t  GFX2D_GS;                     /**< \brief (Gfx2d Offset: 0xC) Global Status Register */
  __O  uint32_t  GFX2D_IE;                     /**< \brief (Gfx2d Offset: 0x10) Interrupt Enable Register */
  __O  uint32_t  GFX2D_ID;                     /**< \brief (Gfx2d Offset: 0x14) Interrupt Disable Register */
  __I  uint32_t  GFX2D_IM;                     /**< \brief (Gfx2d Offset: 0x18) Interrupt Mask Register */
  __I  uint32_t  GFX2D_IS;                     /**< \brief (Gfx2d Offset: 0x1C) Interrupt Status Register */
       Gfx2dSub0 GFX2D_SUB0[GFX2DSUB0_NUMBER]; /**< \brief (Gfx2d Offset: 0x20) 0 .. 1 */
  __IO uint32_t  GFX2D_BASE;                   /**< \brief (Gfx2d Offset: 0x30) Ring Buffer Base Register */
  __IO uint32_t  GFX2D_LEN;                    /**< \brief (Gfx2d Offset: 0x34) Ring Buffer Length Register */
  __IO uint32_t  GFX2D_HEAD;                   /**< \brief (Gfx2d Offset: 0x38) Ring Buffer Head Register */
  __IO uint32_t  GFX2D_TAIL;                   /**< \brief (Gfx2d Offset: 0x3C) Ring Buffer Tail Register */
       Gfx2dChid GFX2D_CHID[GFX2DCHID_NUMBER]; /**< \brief (Gfx2d Offset: 0x40) chid = 0 .. 3 */
} Gfx2d;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- GFX2D_GC : (GFX2D Offset: 0x0) Global Configuration Register -------- */
#define GFX2D_GC_CGDISCORE (0x1u << 0) /**< \brief (GFX2D_GC) Clock Gating Disable Core */
#define GFX2D_GC_CGDISAXI (0x1u << 1) /**< \brief (GFX2D_GC) Clock Gating Disable AXI */
#define GFX2D_GC_CGDISFIFO (0x1u << 2) /**< \brief (GFX2D_GC) Clock Gating Disable FIFO */
#define GFX2D_GC_REGEN (0x1u << 4) /**< \brief (GFX2D_GC) Outstanding Regulation Enable */
#define GFX2D_GC_MTY (0x1u << 6) /**< \brief (GFX2D_GC) Memory Tile Access */
#define GFX2D_GC_REGQOS1_Pos 8
#define GFX2D_GC_REGQOS1_Msk (0xfu << GFX2D_GC_REGQOS1_Pos) /**< \brief (GFX2D_GC) Regulation for QoS Level 1 */
#define GFX2D_GC_REGQOS1(value) ((GFX2D_GC_REGQOS1_Msk & ((value) << GFX2D_GC_REGQOS1_Pos)))
#define GFX2D_GC_REGQOS2_Pos 12
#define GFX2D_GC_REGQOS2_Msk (0xfu << GFX2D_GC_REGQOS2_Pos) /**< \brief (GFX2D_GC) Regulation for QoS Level 2 */
#define GFX2D_GC_REGQOS2(value) ((GFX2D_GC_REGQOS2_Msk & ((value) << GFX2D_GC_REGQOS2_Pos)))
#define GFX2D_GC_REGQOS3_Pos 16
#define GFX2D_GC_REGQOS3_Msk (0xfu << GFX2D_GC_REGQOS3_Pos) /**< \brief (GFX2D_GC) Regulation for QoS Level 3 */
#define GFX2D_GC_REGQOS3(value) ((GFX2D_GC_REGQOS3_Msk & ((value) << GFX2D_GC_REGQOS3_Pos)))
/* -------- GFX2D_GE : (GFX2D Offset: 0x4) Global Enable Register -------- */
#define GFX2D_GE_ENABLE (0x1u << 0) /**< \brief (GFX2D_GE) GFX2D Enable */
/* -------- GFX2D_GD : (GFX2D Offset: 0x8) Global Disable Register -------- */
#define GFX2D_GD_DISABLE (0x1u << 0) /**< \brief (GFX2D_GD) GFX2D Disable Bit */
#define GFX2D_GD_WFERES (0x1u << 8) /**< \brief (GFX2D_GD) WFE Software Resume bit */
/* -------- GFX2D_GS : (GFX2D Offset: 0xC) Global Status Register -------- */
#define GFX2D_GS_STATUS (0x1u << 0) /**< \brief (GFX2D_GS) GFX2D Status Bit */
#define GFX2D_GS_BUSY (0x1u << 4) /**< \brief (GFX2D_GS) GFX2D Busy Bit */
#define GFX2D_GS_WFEIP (0x1u << 8) /**< \brief (GFX2D_GS) Wait For Event Status bit */
/* -------- GFX2D_IE : (GFX2D Offset: 0x10) Interrupt Enable Register -------- */
#define GFX2D_IE_RBEMPTY (0x1u << 0) /**< \brief (GFX2D_IE) Ring Buffer Empty Interrupt Enable Bit */
#define GFX2D_IE_EXEND (0x1u << 1) /**< \brief (GFX2D_IE) End of Execution Interrupt Enable Bit */
#define GFX2D_IE_RERR (0x1u << 2) /**< \brief (GFX2D_IE) Read Data Bus Error Interrupt Enable Bit */
#define GFX2D_IE_BERR (0x1u << 3) /**< \brief (GFX2D_IE) Write Data Bus Error Interrupt Enable Bit */
#define GFX2D_IE_IERR (0x1u << 4) /**< \brief (GFX2D_IE) Illegal Instruction Interrupt Enable Bit */
/* -------- GFX2D_ID : (GFX2D Offset: 0x14) Interrupt Disable Register -------- */
#define GFX2D_ID_RBEMPTY (0x1u << 0) /**< \brief (GFX2D_ID) Ring Buffer Empty Interrupt Disable Bit */
#define GFX2D_ID_EXEND (0x1u << 1) /**< \brief (GFX2D_ID) End of Execution Interrupt Disable Bit */
#define GFX2D_ID_RERR (0x1u << 2) /**< \brief (GFX2D_ID) Read Access Error Interrupt Disable Bit */
#define GFX2D_ID_BERR (0x1u << 3) /**< \brief (GFX2D_ID) Write Access Error Interrupt Disable bit */
#define GFX2D_ID_IERR (0x1u << 4) /**< \brief (GFX2D_ID) Illegal Instruction Interrupt Disable bit */
/* -------- GFX2D_IM : (GFX2D Offset: 0x18) Interrupt Mask Register -------- */
#define GFX2D_IM_RBEMPTY (0x1u << 0) /**< \brief (GFX2D_IM) Ring Buffer Empty Interrupt Mask Bit */
#define GFX2D_IM_EXEND (0x1u << 1) /**< \brief (GFX2D_IM) Execution Ended Empty Interrupt Mask Bit */
#define GFX2D_IM_RERR (0x1u << 2) /**< \brief (GFX2D_IM) Read Error Interrupt Mask Bit */
#define GFX2D_IM_BERR (0x1u << 3) /**< \brief (GFX2D_IM) Write Error Interrupt Mask Bit */
#define GFX2D_IM_IERR (0x1u << 4) /**< \brief (GFX2D_IM) Illegal Instruction Interrupt Mask Bit */
/* -------- GFX2D_IS : (GFX2D Offset: 0x1C) Interrupt Status Register -------- */
#define GFX2D_IS_RBEMPTY (0x1u << 0) /**< \brief (GFX2D_IS) Ring Buffer Empty Interrupt Status Bit */
#define GFX2D_IS_EXEND (0x1u << 1) /**< \brief (GFX2D_IS) End of Execution Status Bit */
#define GFX2D_IS_RERR (0x1u << 2) /**< \brief (GFX2D_IS) Read Error Interrupt Status Bit */
#define GFX2D_IS_BERR (0x1u << 3) /**< \brief (GFX2D_IS) Write Error Interrupt Status Bit */
#define GFX2D_IS_IERR (0x1u << 4) /**< \brief (GFX2D_IS) Illegal Instruction Interrupt Status Bit */
/* -------- GFX2D_PC : (GFX2D Offset: N/A) Performance Configuration 0 Register -------- */
#define GFX2D_PC_SEL_Pos 0
#define GFX2D_PC_SEL_Msk (0x3u << GFX2D_PC_SEL_Pos) /**< \brief (GFX2D_PC) Performance Metrics Selection */
#define GFX2D_PC_SEL(value) ((GFX2D_PC_SEL_Msk & ((value) << GFX2D_PC_SEL_Pos)))
#define   GFX2D_PC_SEL_DISABLED (0x0u << 0) /**< \brief (GFX2D_PC) The performance counter is disabled and reset. */
#define   GFX2D_PC_SEL_READ (0x1u << 0) /**< \brief (GFX2D_PC) The performance counter is incremented when a Read access is performed. */
#define   GFX2D_PC_SEL_WRITE (0x2u << 0) /**< \brief (GFX2D_PC) The performance counter is incremented when a Write access is performed. */
#define   GFX2D_PC_SEL_CYCLE (0x3u << 0) /**< \brief (GFX2D_PC) Number of clock cycles */
#define GFX2D_PC_FILT_Pos 4
#define GFX2D_PC_FILT_Msk (0x7u << GFX2D_PC_FILT_Pos) /**< \brief (GFX2D_PC) Filter Configuration */
#define GFX2D_PC_FILT(value) ((GFX2D_PC_FILT_Msk & ((value) << GFX2D_PC_FILT_Pos)))
#define   GFX2D_PC_FILT_DISABLED (0x0u << 4) /**< \brief (GFX2D_PC) The filter is disabled. */
#define   GFX2D_PC_FILT_QOS0 (0x1u << 4) /**< \brief (GFX2D_PC) Events are valid when input QoS is equal to 0. */
#define   GFX2D_PC_FILT_QOS1 (0x2u << 4) /**< \brief (GFX2D_PC) Events are valid when input QoS is equal to 1. */
#define   GFX2D_PC_FILT_QOS2 (0x3u << 4) /**< \brief (GFX2D_PC) Events are valid when input QoS is equal to 2. */
#define   GFX2D_PC_FILT_QOS3 (0x4u << 4) /**< \brief (GFX2D_PC) Events are valid when input QoS is equal to 3. */
/* -------- GFX2D_MC : (GFX2D Offset: N/A) Metrics Counter 0 Register -------- */
#define GFX2D_MC_COUNTER_Pos 0
#define GFX2D_MC_COUNTER_Msk (0xffffffffu << GFX2D_MC_COUNTER_Pos) /**< \brief (GFX2D_MC) Metrics Counter */
/* -------- GFX2D_BASE : (GFX2D Offset: 0x30) Ring Buffer Base Register -------- */
#define GFX2D_BASE_BASE_Pos 8
#define GFX2D_BASE_BASE_Msk (0xffffffu << GFX2D_BASE_BASE_Pos) /**< \brief (GFX2D_BASE) Ring Buffer Base Register */
#define GFX2D_BASE_BASE(value) ((GFX2D_BASE_BASE_Msk & ((value) << GFX2D_BASE_BASE_Pos)))
/* -------- GFX2D_LEN : (GFX2D Offset: 0x34) Ring Buffer Length Register -------- */
#define GFX2D_LEN_LEN_Pos 0
#define GFX2D_LEN_LEN_Msk (0xfu << GFX2D_LEN_LEN_Pos) /**< \brief (GFX2D_LEN) Ring Buffer Length Multiplier */
#define GFX2D_LEN_LEN(value) ((GFX2D_LEN_LEN_Msk & ((value) << GFX2D_LEN_LEN_Pos)))
/* -------- GFX2D_HEAD : (GFX2D Offset: 0x38) Ring Buffer Head Register -------- */
#define GFX2D_HEAD_HEAD_Pos 0
#define GFX2D_HEAD_HEAD_Msk (0x3ffu << GFX2D_HEAD_HEAD_Pos) /**< \brief (GFX2D_HEAD) Ring Buffer Head Pointer */
#define GFX2D_HEAD_HEAD(value) ((GFX2D_HEAD_HEAD_Msk & ((value) << GFX2D_HEAD_HEAD_Pos)))
/* -------- GFX2D_TAIL : (GFX2D Offset: 0x3C) Ring Buffer Tail Register -------- */
#define GFX2D_TAIL_TAIL_Pos 0
#define GFX2D_TAIL_TAIL_Msk (0x3ffu << GFX2D_TAIL_TAIL_Pos) /**< \brief (GFX2D_TAIL) Ring Buffer Tail Pointer */
#define GFX2D_TAIL_TAIL(value) ((GFX2D_TAIL_TAIL_Msk & ((value) << GFX2D_TAIL_TAIL_Pos)))
/* -------- GFX2D_PA : (GFX2D Offset: N/A) Surface Physical Address Register -------- */
#define GFX2D_PA_PA_Pos 0
#define GFX2D_PA_PA_Msk (0xffffffffu << GFX2D_PA_PA_Pos) /**< \brief (GFX2D_PA) Surface Physical Start Address */
#define GFX2D_PA_PA(value) ((GFX2D_PA_PA_Msk & ((value) << GFX2D_PA_PA_Pos)))
/* -------- GFX2D_PITCH : (GFX2D Offset: N/A) Surface Pitch Register -------- */
#define GFX2D_PITCH_PITCH_Pos 0
#define GFX2D_PITCH_PITCH_Msk (0xffffu << GFX2D_PITCH_PITCH_Pos) /**< \brief (GFX2D_PITCH) Surface Pitch */
#define GFX2D_PITCH_PITCH(value) ((GFX2D_PITCH_PITCH_Msk & ((value) << GFX2D_PITCH_PITCH_Pos)))
/* -------- GFX2D_CFG : (GFX2D Offset: N/A) Surface Configuration Register -------- */
#define GFX2D_CFG_PF_Pos 0
#define GFX2D_CFG_PF_Msk (0xfu << GFX2D_CFG_PF_Pos) /**< \brief (GFX2D_CFG) Pixel Format */
#define GFX2D_CFG_PF(value) ((GFX2D_CFG_PF_Msk & ((value) << GFX2D_CFG_PF_Pos)))
#define   GFX2D_CFG_PF_A4IDX4 (0x0u << 0) /**< \brief (GFX2D_CFG) 4-bit indexed color, with 4-bit alpha value */
#define   GFX2D_CFG_PF_A8 (0x1u << 0) /**< \brief (GFX2D_CFG) 8 bits per pixel alpha, with user-defined constant color */
#define   GFX2D_CFG_PF_IDX8 (0x2u << 0) /**< \brief (GFX2D_CFG) 8 bits indexed color, uses the Color Look-Up Table to expand to true color */
#define   GFX2D_CFG_PF_A8IDX8 (0x3u << 0) /**< \brief (GFX2D_CFG) 8-bit indexed color, with 8-bit alpha value */
#define   GFX2D_CFG_PF_RGB12 (0x4u << 0) /**< \brief (GFX2D_CFG) 12 bits per pixel, 4 bits per color channel */
#define   GFX2D_CFG_PF_ARGB16 (0x5u << 0) /**< \brief (GFX2D_CFG) 16 bits per pixel with 4-bit width alpha value, and 4 bits per color channel */
#define   GFX2D_CFG_PF_RGB15 (0x6u << 0) /**< \brief (GFX2D_CFG) 15 bits per pixel, 5 bits per color channel */
#define   GFX2D_CFG_PF_TRGB16 (0x7u << 0) /**< \brief (GFX2D_CFG) 16 bits per pixel, 5 bits for the red and blue channels and 6 bits for the green channel */
#define   GFX2D_CFG_PF_RGBT16 (0x8u << 0) /**< \brief (GFX2D_CFG) 16 bits per pixel, with 1 bit for transparency and 5 bits for color channels */
#define   GFX2D_CFG_PF_RGB16 (0x9u << 0) /**< \brief (GFX2D_CFG) 16 bits per pixel, 5 bits for the red and blue channels and 6 bits for the green channel */
#define   GFX2D_CFG_PF_RGB24 (0xAu << 0) /**< \brief (GFX2D_CFG) 24 bits per pixel, 8 bits for alpha and color channels */
#define   GFX2D_CFG_PF_ARGB32 (0xBu << 0) /**< \brief (GFX2D_CFG) 32 bits per pixel, 8 bits for alpha and color channels */
#define   GFX2D_CFG_PF_RGBA32 (0xCu << 0) /**< \brief (GFX2D_CFG) 32 bits per pixel, 8 bits for alpha and color channels */
#define GFX2D_CFG_IDXCX (0x1u << 4) /**< \brief (GFX2D_CFG) Color Look-Up Table Selection */

/*@}*/


#endif /* _SAM9X_GFX2D_COMPONENT_ */
