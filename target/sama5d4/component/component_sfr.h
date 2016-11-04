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

#ifndef _SAMA5D4_SFR_COMPONENT_
#define _SAMA5D4_SFR_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SFR Special Function Registers */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfr hardware registers */
typedef struct {
	__I  uint32_t Reserved1[1];
	__IO uint32_t SFR_DDRCFG;     /**< \brief (Sfr Offset: 0x04) DDR Configuration Register */
	__I  uint32_t Reserved2[2];
	__IO uint32_t SFR_OHCIICR;    /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
	__I  uint32_t SFR_OHCIISR;    /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
	__I  uint32_t Reserved3[4];
	__IO uint32_t SFR_SECURE;     /**< \brief (Sfr Offset: 0x28) Security Configuration Register */
	__I  uint32_t Reserved4[5];
	__IO uint32_t SFR_EBICFG;     /**< \brief (Sfr Offset: 0x40) EBI Configuration Register */
	__I  uint32_t Reserved5[2];
	__I  uint32_t SFR_SN0;        /**< \brief (Sfr Offset: 0x4C) Serial Number 0 Register */
	__I  uint32_t SFR_SN1;        /**< \brief (Sfr Offset: 0x50) Serial Number 1 Register */
	__IO uint32_t SFR_AICREDIR;   /**< \brief (Sfr Offset: 0x54) AIC interrupt Redirection Register */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_DDRCFG : (SFR Offset: 0x04) DDR Configuration Register -------- */
#define SFR_DDRCFG_FDQIEN (0x1u << 16) /**< \brief (SFR_DDRCFG) Force DDR_DQ Input Buffer Always On */
#define SFR_DDRCFG_FDQSIEN (0x1u << 17) /**< \brief (SFR_DDRCFG) Force DDR_DQS Input Buffer Always On */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) Reserved */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) USB DEVICE PULL-UP DISABLE */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
/* -------- SFR_SECURE : (SFR Offset: 0x28) Security Configuration Register -------- */
#define SFR_SECURE_ROM (0x1u << 0) /**< \brief (SFR_SECURE) Disable Access to ROM Code */
#define SFR_SECURE_FUSE (0x1u << 8) /**< \brief (SFR_SECURE) Disable Access to Fuse Controller */
/* -------- SFR_EBICFG : (SFR Offset: 0x40) EBI Configuration Register -------- */
#define SFR_EBICFG_DRIVE0_Pos 0
#define SFR_EBICFG_DRIVE0_Msk (0x3u << SFR_EBICFG_DRIVE0_Pos) /**< \brief (SFR_EBICFG) EBI Pins Drive Level */
#define SFR_EBICFG_DRIVE0(value) ((SFR_EBICFG_DRIVE0_Msk & ((value) << SFR_EBICFG_DRIVE0_Pos)))
#define   SFR_EBICFG_DRIVE0_LOW (0x0u << 0) /**< \brief (SFR_EBICFG) Low drive level */
#define   SFR_EBICFG_DRIVE0_MEDIUM (0x2u << 0) /**< \brief (SFR_EBICFG) Medium drive level */
#define   SFR_EBICFG_DRIVE0_HIGH (0x3u << 0) /**< \brief (SFR_EBICFG) High drive level */
#define SFR_EBICFG_PULL0_Pos 2
#define SFR_EBICFG_PULL0_Msk (0x3u << SFR_EBICFG_PULL0_Pos) /**< \brief (SFR_EBICFG) EBI Pins Pull Value */
#define SFR_EBICFG_PULL0(value) ((SFR_EBICFG_PULL0_Msk & ((value) << SFR_EBICFG_PULL0_Pos)))
#define   SFR_EBICFG_PULL0_UP (0x0u << 2) /**< \brief (SFR_EBICFG) Pull-up */
#define   SFR_EBICFG_PULL0_NONE (0x1u << 2) /**< \brief (SFR_EBICFG) No Pull */
#define   SFR_EBICFG_PULL0_DOWN (0x3u << 2) /**< \brief (SFR_EBICFG) Pull-down */
#define SFR_EBICFG_SCH0 (0x1u << 4) /**< \brief (SFR_EBICFG) EBI Pins Schmitt Trigger */
#define SFR_EBICFG_DRIVE1_Pos 8
#define SFR_EBICFG_DRIVE1_Msk (0x3u << SFR_EBICFG_DRIVE1_Pos) /**< \brief (SFR_EBICFG) EBI Pins Drive Level */
#define SFR_EBICFG_DRIVE1(value) ((SFR_EBICFG_DRIVE1_Msk & ((value) << SFR_EBICFG_DRIVE1_Pos)))
#define   SFR_EBICFG_DRIVE1_LOW (0x0u << 8) /**< \brief (SFR_EBICFG) Low drive level */
#define   SFR_EBICFG_DRIVE1_MEDIUM (0x2u << 8) /**< \brief (SFR_EBICFG) Medium drive level */
#define   SFR_EBICFG_DRIVE1_HIGH (0x3u << 8) /**< \brief (SFR_EBICFG) High drive level */
#define SFR_EBICFG_PULL1_Pos 10
#define SFR_EBICFG_PULL1_Msk (0x3u << SFR_EBICFG_PULL1_Pos) /**< \brief (SFR_EBICFG) EBI Pins Pull Value */
#define SFR_EBICFG_PULL1(value) ((SFR_EBICFG_PULL1_Msk & ((value) << SFR_EBICFG_PULL1_Pos)))
#define   SFR_EBICFG_PULL1_UP (0x0u << 10) /**< \brief (SFR_EBICFG) Pull-up */
#define   SFR_EBICFG_PULL1_NONE (0x1u << 10) /**< \brief (SFR_EBICFG) No Pull */
#define   SFR_EBICFG_PULL1_DOWN (0x3u << 10) /**< \brief (SFR_EBICFG) Pull-down */
#define SFR_EBICFG_SCH1 (0x1u << 12) /**< \brief (SFR_EBICFG) EBI Pins Schmitt Trigger */
/* -------- SFR_SN0 : (SFR Offset: 0x4C) Serial Number 0 Register -------- */
#define SFR_SN0_SN0_Pos 0
#define SFR_SN0_SN0_Msk (0xffffffffu << SFR_SN0_SN0_Pos) /**< \brief (SFR_SN0) Serial Number 0 */
/* -------- SFR_SN1 : (SFR Offset: 0x50) Serial Number 1 Register -------- */
#define SFR_SN1_SN1_Pos 0
#define SFR_SN1_SN1_Msk (0xffffffffu << SFR_SN1_SN1_Pos) /**< \brief (SFR_SN1) Serial Number 1 */
/* -------- SFR_AICREDIR : (SFR Offset: 0x54) AIC interrupt Redirection Register -------- */
#define SFR_AICREDIR_NSAIC (0x1u << 0) /**< \brief (SFR_AICREDIR) Interrupt redirection to Non-Secure AIC */
#define SFR_AICREDIR_AICREDIRKEY_Pos 1
#define SFR_AICREDIR_AICREDIRKEY_Msk (0x7fffffffu << SFR_AICREDIR_AICREDIRKEY_Pos) /**< \brief (SFR_AICREDIR) Unlock Key */
#define SFR_AICREDIR_AICREDIRKEY(value) ((SFR_AICREDIR_AICREDIRKEY_Msk & ((value) << SFR_AICREDIR_AICREDIRKEY_Pos)))

/*@}*/

#endif /* _SAMA5D4_SFR_COMPONENT_ */
