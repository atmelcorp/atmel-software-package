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

#ifndef _SAM9X_SFR_INSTANCE_
#define _SAM9X_SFR_INSTANCE_

/* ========== Register definition for SFR peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SFR_CCFG_EBICSA                      (0xF8050004U) /**< \brief (SFR) EBI Chip Select Register */
  #define REG_SFR_OHCIICR                          (0xF8050010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
  #define REG_SFR_OHCIISR                          (0xF8050014U) /**< \brief (SFR) OHCI Interrupt Status Register */
  #define REG_SFR_BU_OTPC_CONF_R0                  (0xF8050018U) /**< \brief (SFR) OTPC Configuration 0 Register (BackUp) */
  #define REG_SFR_BU_OTPC_CONF_R1                  (0xF805001CU) /**< \brief (SFR) OTPC Configuration 1 Register (BackUp) */
  #define REG_SFR_BU_RC_XTAL_TRIM                  (0xF8050020U) /**< \brief (SFR) RC and XTAL Oscillator Trimming Register (BackUp) */
  #define REG_SFR_UTMICKTRIM                       (0xF8050030U) /**< \brief (SFR) UTMI Clock Trimming Register */
  #define REG_SFR_UTMIHSTRIM                       (0xF8050034U) /**< \brief (SFR) UTMI High-Speed Trimming Register */
  #define REG_SFR_UTMIFSTRIM                       (0xF8050038U) /**< \brief (SFR) UTMI Full-Speed Trimming Register */
  #define REG_SFR_UTMISWAP                         (0xF805003CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
  #define REG_SFR_RM0                              (0xF805005CU) /**< \brief (SFR) Read Margin0 Register */
  #define REG_SFR_RM1                              (0xF8050060U) /**< \brief (SFR) Read Margin1 Register */
  #define REG_SFR_RM2                              (0xF8050064U) /**< \brief (SFR) Read Margin2 Register */
  #define REG_SFR_RM3                              (0xF8050068U) /**< \brief (SFR) Read Margin3 Register */
  #define REG_SFR_RM4                              (0xF805006CU) /**< \brief (SFR) Read Margin4 Register */
  #define REG_SFR_RM5                              (0xF8050070U) /**< \brief (SFR) Read Margin5 Register */
  #define REG_SFR_LS                               (0xF805007CU) /**< \brief (SFR) Light Sleep Register */
  #define REG_SFR_CAL0                             (0xF80500B0U) /**< \brief (SFR) I/O Calibration 0 Register */
  #define REG_SFR_CAL1                             (0xF80500B4U) /**< \brief (SFR) I/O Calibration 1 Register */
  #define REG_SFR_WPMR                             (0xF80500E4U) /**< \brief (SFR) Write Protection Mode Register */
  #define REG_SFR_SPARE                            (0xF8050100U) /**< \brief (SFR) Spare Register */
  #define REG_SFR_BU_SPARE                         (0xF8050104U) /**< \brief (SFR) Spare Register (BackUp) */
#else
  #define REG_SFR_CCFG_EBICSA     (*(__IO uint32_t*)0xF8050004U) /**< \brief (SFR) EBI Chip Select Register */
  #define REG_SFR_OHCIICR         (*(__IO uint32_t*)0xF8050010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
  #define REG_SFR_OHCIISR         (*(__I  uint32_t*)0xF8050014U) /**< \brief (SFR) OHCI Interrupt Status Register */
  #define REG_SFR_BU_OTPC_CONF_R0 (*(__IO uint32_t*)0xF8050018U) /**< \brief (SFR) OTPC Configuration 0 Register (BackUp) */
  #define REG_SFR_BU_OTPC_CONF_R1 (*(__IO uint32_t*)0xF805001CU) /**< \brief (SFR) OTPC Configuration 1 Register (BackUp) */
  #define REG_SFR_BU_RC_XTAL_TRIM (*(__IO uint32_t*)0xF8050020U) /**< \brief (SFR) RC and XTAL Oscillator Trimming Register (BackUp) */
  #define REG_SFR_UTMICKTRIM      (*(__IO uint32_t*)0xF8050030U) /**< \brief (SFR) UTMI Clock Trimming Register */
  #define REG_SFR_UTMIHSTRIM      (*(__IO uint32_t*)0xF8050034U) /**< \brief (SFR) UTMI High-Speed Trimming Register */
  #define REG_SFR_UTMIFSTRIM      (*(__IO uint32_t*)0xF8050038U) /**< \brief (SFR) UTMI Full-Speed Trimming Register */
  #define REG_SFR_UTMISWAP        (*(__IO uint32_t*)0xF805003CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
  #define REG_SFR_RM0             (*(__IO uint32_t*)0xF805005CU) /**< \brief (SFR) Read Margin0 Register */
  #define REG_SFR_RM1             (*(__IO uint32_t*)0xF8050060U) /**< \brief (SFR) Read Margin1 Register */
  #define REG_SFR_RM2             (*(__IO uint32_t*)0xF8050064U) /**< \brief (SFR) Read Margin2 Register */
  #define REG_SFR_RM3             (*(__IO uint32_t*)0xF8050068U) /**< \brief (SFR) Read Margin3 Register */
  #define REG_SFR_RM4             (*(__IO uint32_t*)0xF805006CU) /**< \brief (SFR) Read Margin4 Register */
  #define REG_SFR_RM5             (*(__IO uint32_t*)0xF8050070U) /**< \brief (SFR) Read Margin5 Register */
  #define REG_SFR_LS              (*(__IO uint32_t*)0xF805007CU) /**< \brief (SFR) Light Sleep Register */
  #define REG_SFR_CAL0            (*(__IO uint32_t*)0xF80500B0U) /**< \brief (SFR) I/O Calibration 0 Register */
  #define REG_SFR_CAL1            (*(__IO uint32_t*)0xF80500B4U) /**< \brief (SFR) I/O Calibration 1 Register */
  #define REG_SFR_WPMR            (*(__IO uint32_t*)0xF80500E4U) /**< \brief (SFR) Write Protection Mode Register */
  #define REG_SFR_SPARE           (*(__IO uint32_t*)0xF8050100U) /**< \brief (SFR) Spare Register */
  #define REG_SFR_BU_SPARE        (*(__IO uint32_t*)0xF8050104U) /**< \brief (SFR) Spare Register (BackUp) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SFR_INSTANCE_ */
