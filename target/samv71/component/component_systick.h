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

#ifndef _CORTEXM7_SYSTICK_COMPONENT_
#define _CORTEXM7_SYSTICK_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 Systick */
/* ============================================================================= */
/** \addtogroup Cortex-M7 Systick */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__IO uint32_t SYST_CSR;   /**< \brief (Systick Offset: 0x00) SysTick Control and Status Register */
	__IO uint32_t SYST_RVR;   /**< \brief (Systick Offset: 0x04) SysTick Reload Value Register */
	__IO uint32_t SYST_CVR;   /**< \brief (Systick Offset: 0x08) SysTick Current Value Register */
	__I  uint32_t SYST_CALIB; /**< \brief (Systick Offset: 0x0C) SysTick Calibration Value Register */
} Systick;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SYST_CSR : (SYSTICK Offset: 0x00) SysTick Control and Status Register -------- */
#define SYST_CSR_ENABLE (0x1u << 0)
#define SYST_CSR_TICKINT (0x1u << 1)
#define SYST_CSR_CLKSOURCE_Pos 2
#define SYST_CSR_CLKSOURCE_Msk (0x1u << 2)
#define   SYST_CSR_CLKSOURCE_EXT (0x0u << 2)
#define   SYST_CSR_CLKSOURCE_PROC (0x1u << 2)
#define SYST_CSR_COUNTFLAG (0x1u << 16)
/* -------- SYST_RVR : (SYSTICK Offset: 0x04) SysTick Reload Value Register -------- */
#define SYST_CSR_RVR_RELOAD_Pos 0
#define SYST_CSR_RVR_RELOAD_Msk (0xffffffu << 0)
#define SYST_CSR_RVR_RELOAD(value) ((SYST_CSR_RVR_RELOAD_Msk & ((value) << SYST_CSR_RVR_RELOAD_Pos)))
/* -------- SYST_CVR : (SYSTICK Offset: 0x08) SysTick Current Value Register -------- */
#define SYST_CSR_CVR_CURRENT_Pos 0
#define SYST_CSR_CVR_CURRENT_Msk (0xffffffu << 0)
#define SYST_CSR_CVR_CURRENT(value) ((SYST_CSR_CVR_CURRENT_Msk & ((value) << SYST_CSR_CVR_CURRENT_Pos)))
/* -------- SYST_CALIB : (SYSTICK Offset: 0x0C) SysTick Calibration Value Register -------- */
#define SYST_CSR_CALIB_TENMS_Pos 0
#define SYST_CSR_CALIB_TENMS_Msk (0xffffffu << 0)
#define SYST_CSR_CALIB_TENMS(value) ((SYST_CSR_CALIB_TENMS_Msk & ((value) << SYST_CSR_CALIB_TENMS_Pos)))
#define SYST_CSR_CALIB_SKEW (0x1 << 30)
#define SYST_CSR_CALIB_NOREF (0x1 << 31)

/*@}*/

#endif /* _CORTEXM7_SYSTICK_COMPONENT_ */
