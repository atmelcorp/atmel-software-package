/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#ifndef _CORTEXM7_MPU_COMPONENT_
#define _CORTEXM7_MPU_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 Memory Protection Unit */
/* ============================================================================= */
/** \addtogroup Cortex-M7 Memory Protection Unit */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__IO uint32_t MPU_RBAR;       /**< \brief (MpuRegion Offset: 0x00) MPU Region Base Address Register */
	__IO uint32_t MPU_RASR;       /**< \brief (MpuRegion Offset: 0x04) MPU Region Attribute and Size Register */
} MpuRegion;
typedef struct {
	__I  uint32_t  MPU_TYPE;      /**< \brief (Mpu Offset: 0x00) MPU Type Register */
	__IO uint32_t  MPU_CTRL;      /**< \brief (Mpu Offset: 0x04) MPU Control Register */
	__IO uint32_t  MPU_RNR;       /**< \brief (Mpu Offset: 0x08) MPU Region Number Register */
	     MpuRegion MPU_REGION[4]; /**< \brief (Mpu Offset: 0x0C) MPU Region Addresses, Attributes and Size Registers */
} Mpu;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MPU_TYPE : (MPU Offset: 0x00) MPU Type Register --------  */
#define MPU_TYPE_SEPARATE (0x1u << 0)
#define MPU_TYPE_DREGION_Pos 8
#define MPU_TYPE_DREGION_Msk (0xffu << 8)
#define   MPU_TYPE_DREGION_8 (0x8u << 8)
#define   MPU_TYPE_DREGION_16 (0xfu << 8)
#define MPU_TYPE_IREGION_Pos 16
#define MPU_TYPE_IREGION_Msk (0xffu << 16)
#define   MPU_TYPE_IREGION_0 (0x0u << 16)
/* -------- MPU_CTRL : (MPU Offset: 0x04) MPU Control Register --------  */
#define MPU_CTRL_ENABLE (0x1u << 0)
#define MPU_CTRL_HFNMIENA (0x1u << 1)
#define MPU_CTRL_PRIVDEFENA (0x1u << 2)
/* -------- MPU_RNR : (MPU Offset: 0x008) MPU Region Number Register --------  */
#define MPU_RNR_REGION_Pos 0
#define MPU_RNR_REGION_Msk (0xffu << 0)
#define MPU_RNR_REGION(value) ((MPU_RNR_REGION_Msk & ((value) << MPU_RNR_REGION_Pos)))
/* -------- MPU_RBAR : (MPU Offset: N/A) MPU Region Base Address Register --------  */
#define MPU_RBAR_REGION_Pos 0
#define MPU_RBAR_REGION_Msk (0xfu << 0)
#define MPU_RBAR_REGION(value) ((MPU_RBAR_REGION_Msk & ((value) << MPU_RBAR_REGION_Pos)))
#define MPU_RBAR_VALID (0x1u << 4)
#define MPU_RBAR_ADDR_Pos 5
#define MPU_RBAR_ADDR_Msk (0x7ffffffu << 5)
#define MPU_RBAR_ADDR(value) ((MPU_RBAR_ADDR_Msk & ((value) << MPU_RBAR_ADDR_Pos)))
/* -------- MPU_RASR : (MPU Offset: N/A) MPU Region Attribute and Size Register -------- */
#define MPU_RASR_ENABLE (0x1u << 0)
#define MPU_RASR_SIZE_Pos 1
#define MPU_RASR_SIZE_Msk (0x1fu << 1)
#define MPU_RASR_SIZE(value) ((MPU_RASR_SIZE_Msk & ((value) << MPU_RASR_SIZE_Pos)))
#define MPU_RASR_SRD_Pos 8
#define MPU_RASR_SRD_Msk (0xffu << 8)
#define MPU_RASR_SRD(value) ((MPU_RASR_SRD_Msk & ((value) << MPU_RASR_SRD_Pos)))
#define MPU_RASR_B (0x1u << 16)
#define MPU_RASR_C (0x1u << 17)
#define MPU_RASR_S (0x1u << 18)
#define MPU_RASR_TEX_Pos 19
#define MPU_RASR_TEX_Msk (0x7u << 19)
#define MPU_RASR_TEX(value) ((MPU_RASR_TEX_Msk & ((value) << MPU_RASR_TEX_Pos)))
#define MPU_RASR_AP_Pos 24
#define MPU_RASR_AP_Msk (0x7u << 24)
#define MPU_RASR_AP(value) ((MPU_RASR_AP_Msk & ((value) << MPU_RASR_AP_Pos)))
#define MPU_RASR_XN (0x1u << 28)

/*@}*/

#endif /* _CM7_SCS_COMPONENT_ */
