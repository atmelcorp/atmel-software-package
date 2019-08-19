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

#ifndef _SAM9X_WDT_COMPONENT_
#define _SAM9X_WDT_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Watchdog Timer */
/* ============================================================================= */
/** \addtogroup SAM9X_WDT Watchdog Timer */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Wdt hardware registers */
typedef struct {
  __O  uint32_t WDT_CR;  /**< \brief (Wdt Offset: 0x0) Control Register */
  __IO uint32_t WDT_MR;  /**< \brief (Wdt Offset: 0x4) Mode Register */
  __I  uint32_t WDT_VR;  /**< \brief (Wdt Offset: 0x8) Value Register */
  __IO uint32_t WDT_WLR; /**< \brief (Wdt Offset: 0xC) Window Level Register */
  __IO uint32_t WDT_ILR; /**< \brief (Wdt Offset: 0x10) Interrupt Level Register */
  __O  uint32_t WDT_IER; /**< \brief (Wdt Offset: 0x14) Interrupt Enable Register */
  __O  uint32_t WDT_IDR; /**< \brief (Wdt Offset: 0x18) Interrupt Disable Register */
  __I  uint32_t WDT_ISR; /**< \brief (Wdt Offset: 0x1C) Interrupt Status Register */
  __I  uint32_t WDT_IMR; /**< \brief (Wdt Offset: 0x20) Interrupt Mask Register */
} Wdt;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- WDT_CR : (WDT Offset: 0x0) Control Register -------- */
#define WDT_CR_WDRSTT (0x1u << 0) /**< \brief (WDT_CR) Watchdog Restart */
#define WDT_CR_LOCKMR (0x1u << 4) /**< \brief (WDT_CR) Lock Mode Register Write Access */
#define WDT_CR_KEY_Pos 24
#define WDT_CR_KEY_Msk (0xffu << WDT_CR_KEY_Pos) /**< \brief (WDT_CR) Password */
#define WDT_CR_KEY(value) ((WDT_CR_KEY_Msk & ((value) << WDT_CR_KEY_Pos)))
#define   WDT_CR_KEY_PASSWD (0xA5u << 24) /**< \brief (WDT_CR) Writing any other value in this field aborts the write operation. */
/* -------- WDT_MR : (WDT Offset: 0x4) Mode Register -------- */
#define WDT_MR_PERIODRST (0x1u << 4) /**< \brief (WDT_MR) Period Reset */
#define WDT_MR_RPTHRST (0x1u << 5) /**< \brief (WDT_MR) Minimum Restart Period */
#define WDT_MR_WDDIS (0x1u << 12) /**< \brief (WDT_MR) Watchdog Disable */
#define WDT_MR_WDDBGHLT (0x1u << 28) /**< \brief (WDT_MR) Watchdog Debug Halt */
#define WDT_MR_WDIDLEHLT (0x1u << 29) /**< \brief (WDT_MR) Watchdog Idle Halt */
/* -------- WDT_VR : (WDT Offset: 0x8) Value Register -------- */
#define WDT_VR_COUNTER_Pos 0
#define WDT_VR_COUNTER_Msk (0xfffu << WDT_VR_COUNTER_Pos) /**< \brief (WDT_VR) Watchdog Down Counter Value */
/* -------- WDT_WLR : (WDT Offset: 0xC) Window Level Register -------- */
#define WDT_WLR_PERIOD_Pos 0
#define WDT_WLR_PERIOD_Msk (0xfffu << WDT_WLR_PERIOD_Pos) /**< \brief (WDT_WLR) Watchdog Period */
#define WDT_WLR_PERIOD(value) ((WDT_WLR_PERIOD_Msk & ((value) << WDT_WLR_PERIOD_Pos)))
#define WDT_WLR_RPTH_Pos 16
#define WDT_WLR_RPTH_Msk (0xfffu << WDT_WLR_RPTH_Pos) /**< \brief (WDT_WLR) Repeat Threshold */
#define WDT_WLR_RPTH(value) ((WDT_WLR_RPTH_Msk & ((value) << WDT_WLR_RPTH_Pos)))
/* -------- WDT_ILR : (WDT Offset: 0x10) Interrupt Level Register -------- */
#define WDT_ILR_LVLTH_Pos 0
#define WDT_ILR_LVLTH_Msk (0xfffu << WDT_ILR_LVLTH_Pos) /**< \brief (WDT_ILR) Level Threshold */
#define WDT_ILR_LVLTH(value) ((WDT_ILR_LVLTH_Msk & ((value) << WDT_ILR_LVLTH_Pos)))
/* -------- WDT_IER : (WDT Offset: 0x14) Interrupt Enable Register -------- */
#define WDT_IER_PERINT (0x1u << 0) /**< \brief (WDT_IER) Period Interrupt Enable */
#define WDT_IER_RPTHINT (0x1u << 1) /**< \brief (WDT_IER) Repeat Threshold Interrupt Enable */
#define WDT_IER_LVLINT (0x1u << 2) /**< \brief (WDT_IER) Interrupt Level Threshold Interrupt Enable */
/* -------- WDT_IDR : (WDT Offset: 0x18) Interrupt Disable Register -------- */
#define WDT_IDR_PERINT (0x1u << 0) /**< \brief (WDT_IDR) Period Interrupt Disable */
#define WDT_IDR_RPTHINT (0x1u << 1) /**< \brief (WDT_IDR) Repeat Threshold Interrupt Disable */
#define WDT_IDR_LVLINT (0x1u << 2) /**< \brief (WDT_IDR) Interrupt Level Threshold Interrupt Disable */
/* -------- WDT_ISR : (WDT Offset: 0x1C) Interrupt Status Register -------- */
#define WDT_ISR_PERINT (0x1u << 0) /**< \brief (WDT_ISR) Period Interrupt Status (cleared on read) */
#define WDT_ISR_RPTHINT (0x1u << 1) /**< \brief (WDT_ISR) Repeat Threshold Interrupt Status (cleared on read) */
#define WDT_ISR_LVLINT (0x1u << 2) /**< \brief (WDT_ISR) Interrupt Level Threshold Interrupt Status (cleared on read) */
/* -------- WDT_IMR : (WDT Offset: 0x20) Interrupt Mask Register -------- */
#define WDT_IMR_PERINT (0x1u << 0) /**< \brief (WDT_IMR) Period Interrupt Mask */
#define WDT_IMR_RPTHINT (0x1u << 1) /**< \brief (WDT_IMR) Repeat Threshold Interrupt Mask */
#define WDT_IMR_LVLINT (0x1u << 2) /**< \brief (WDT_IMR) Interrupt Level Threshold Interrupt Mask */

/*@}*/


#endif /* _SAM9X_WDT_COMPONENT_ */
