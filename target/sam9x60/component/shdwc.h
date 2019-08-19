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

#ifndef _SAM9X_SHDWC_COMPONENT_
#define _SAM9X_SHDWC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Shutdown Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_SHDWC Shutdown Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Shdwc hardware registers */
typedef struct {
  __O  uint32_t SHDW_CR;   /**< \brief (Shdwc Offset: 0x0) Control Register */
  __IO uint32_t SHDW_MR;   /**< \brief (Shdwc Offset: 0x4) Mode Register */
  __I  uint32_t SHDW_SR;   /**< \brief (Shdwc Offset: 0x8) Status Register */
  __IO uint32_t SHDW_WUIR; /**< \brief (Shdwc Offset: 0xC) Wakeup Inputs Register */
} Shdwc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SHDW_CR : (SHDWC Offset: 0x0) Control Register -------- */
#define SHDW_CR_SHDW (0x1u << 0) /**< \brief (SHDW_CR) Shutdown Command */
#define SHDW_CR_KEY_Pos 24
#define SHDW_CR_KEY_Msk (0xffu << SHDW_CR_KEY_Pos) /**< \brief (SHDW_CR) Password */
#define SHDW_CR_KEY(value) ((SHDW_CR_KEY_Msk & ((value) << SHDW_CR_KEY_Pos)))
#define   SHDW_CR_KEY_PASSWD (0xA5u << 24) /**< \brief (SHDW_CR) Writing any other value in this field aborts the write operation. */
/* -------- SHDW_MR : (SHDWC Offset: 0x4) Mode Register -------- */
#define SHDW_MR_RTTWKEN (0x1u << 16) /**< \brief (SHDW_MR) Real-time Timer Wakeup Enable */
#define SHDW_MR_RTCWKEN (0x1u << 17) /**< \brief (SHDW_MR) Real-time Clock Wakeup Enable */
#define SHDW_MR_WKUPDBC_Pos 24
#define SHDW_MR_WKUPDBC_Msk (0x7u << SHDW_MR_WKUPDBC_Pos) /**< \brief (SHDW_MR) Wakeup Inputs Debouncer Period */
#define SHDW_MR_WKUPDBC(value) ((SHDW_MR_WKUPDBC_Msk & ((value) << SHDW_MR_WKUPDBC_Pos)))
#define   SHDW_MR_WKUPDBC_IMMEDIATE (0x0u << 24) /**< \brief (SHDW_MR) Immediate, no debouncing, detected active at least on one MD_SLCK edge. */
#define   SHDW_MR_WKUPDBC_3_SLCK (0x1u << 24) /**< \brief (SHDW_MR) WKUP shall be in its active state for at least 3 MD_SLCK periods */
#define   SHDW_MR_WKUPDBC_32_SLCK (0x2u << 24) /**< \brief (SHDW_MR) WKUP shall be in its active state for at least 32 MD_SLCK periods */
#define   SHDW_MR_WKUPDBC_512_SLCK (0x3u << 24) /**< \brief (SHDW_MR) WKUP shall be in its active state for at least 512 MD_SLCK periods */
#define   SHDW_MR_WKUPDBC_4096_SLCK (0x4u << 24) /**< \brief (SHDW_MR) WKUP shall be in its active state for at least 4,096 MD_SLCK periods */
#define   SHDW_MR_WKUPDBC_32768_SLCK (0x5u << 24) /**< \brief (SHDW_MR) WKUP shall be in its active state for at least 32,768 MD_SLCK periods */
/* -------- SHDW_SR : (SHDWC Offset: 0x8) Status Register -------- */
#define SHDW_SR_WKUPS (0x1u << 0) /**< \brief (SHDW_SR) WKUP Wakeup Status */
#define   SHDW_SR_WKUPS_NO (0x0u << 0) /**< \brief (SHDW_SR) No wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR. */
#define   SHDW_SR_WKUPS_PRESENT (0x1u << 0) /**< \brief (SHDW_SR) At least one wakeup due to the assertion of the WKUP pin has occurred since the last read of SHDW_SR. */
#define SHDW_SR_RTTWK (0x1u << 4) /**< \brief (SHDW_SR) Real-time Timer Wakeup */
#define SHDW_SR_RTCWK (0x1u << 5) /**< \brief (SHDW_SR) Real-time Clock Wakeup */
#define SHDW_SR_WKUPIS0 (0x1u << 16) /**< \brief (SHDW_SR) Wakeup 0 Input Status */
#define   SHDW_SR_WKUPIS0_DISABLE (0x0u << 16) /**< \brief (SHDW_SR) The wakeup 0 input is disabled, or was inactive at the time the debouncer triggered a wakeup event. */
#define   SHDW_SR_WKUPIS0_ENABLE (0x1u << 16) /**< \brief (SHDW_SR) The wakeup 0 input was active at the time the debouncer triggered a wakeup event. */
/* -------- SHDW_WUIR : (SHDWC Offset: 0xC) Wakeup Inputs Register -------- */
#define SHDW_WUIR_WKUPEN0 (0x1u << 0) /**< \brief (SHDW_WUIR) Wakeup 0 Input Enable */
#define   SHDW_WUIR_WKUPEN0_DISABLE (0x0u << 0) /**< \brief (SHDW_WUIR) The wakeup 0 input has no wakeup effect. */
#define   SHDW_WUIR_WKUPEN0_ENABLE (0x1u << 0) /**< \brief (SHDW_WUIR) The wakeup 0 input forces wakeup of the core power supply. */
#define SHDW_WUIR_WKUPT0 (0x1u << 16) /**< \brief (SHDW_WUIR) Wakeup 0 Input Type */
#define   SHDW_WUIR_WKUPT0_LOW (0x0u << 16) /**< \brief (SHDW_WUIR) A falling edge followed by a low level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply. */
#define   SHDW_WUIR_WKUPT0_HIGH (0x1u << 16) /**< \brief (SHDW_WUIR) A rising edge followed by a high level on the wakeup 0 input, for a period defined by WKUPDBC, forces wakeup of the core power supply. */

/*@}*/


#endif /* _SAM9X_SHDWC_COMPONENT_ */
