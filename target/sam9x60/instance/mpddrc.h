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

#ifndef _SAM9X_MPDDRC_INSTANCE_
#define _SAM9X_MPDDRC_INSTANCE_

/* ========== Register definition for MPDDRC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MPDDRC_MR                             (0xFFFFE800U) /**< \brief (MPDDRC) Mode Register */
  #define REG_MPDDRC_RTR                            (0xFFFFE804U) /**< \brief (MPDDRC) Refresh Timer Register */
  #define REG_MPDDRC_CR                             (0xFFFFE808U) /**< \brief (MPDDRC) Configuration Register */
  #define REG_MPDDRC_TPR0                           (0xFFFFE80CU) /**< \brief (MPDDRC) Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1                           (0xFFFFE810U) /**< \brief (MPDDRC) Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2                           (0xFFFFE814U) /**< \brief (MPDDRC) Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR                            (0xFFFFE81CU) /**< \brief (MPDDRC) Low-Power Register */
  #define REG_MPDDRC_MD                             (0xFFFFE820U) /**< \brief (MPDDRC) Memory Device Register */
  #define REG_MPDDRC_IO_CALIBR                      (0xFFFFE834U) /**< \brief (MPDDRC) I/O Calibration Register */
  #define REG_MPDDRC_OCMS                           (0xFFFFE838U) /**< \brief (MPDDRC) OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1                      (0xFFFFE83CU) /**< \brief (MPDDRC) OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2                      (0xFFFFE840U) /**< \brief (MPDDRC) OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER                   (0xFFFFE844U) /**< \brief (MPDDRC) Configuration Arbiter Register */
  #define REG_MPDDRC_TIMEOUT                        (0xFFFFE848U) /**< \brief (MPDDRC) Timeout Register */
  #define REG_MPDDRC_REQ_PORT_0123                  (0xFFFFE84CU) /**< \brief (MPDDRC) Request Port 0-1-2-3 Register */
  #define REG_MPDDRC_BDW_PORT_0123                  (0xFFFFE854U) /**< \brief (MPDDRC) Current/Maximum Bandwidth Port 0-1-2-3 Register */
  #define REG_MPDDRC_RD_DATA_PATH                   (0xFFFFE85CU) /**< \brief (MPDDRC) Read Data Path Register */
  #define REG_MPDDRC_MCFGR                          (0xFFFFE860U) /**< \brief (MPDDRC) Monitor Configuration Register */
  #define REG_MPDDRC_MADDR0                         (0xFFFFE864U) /**< \brief (MPDDRC) Monitor Address High/Low Port 0 Register */
  #define REG_MPDDRC_MADDR1                         (0xFFFFE868U) /**< \brief (MPDDRC) Monitor Address High/Low Port 1 Register */
  #define REG_MPDDRC_MADDR2                         (0xFFFFE86CU) /**< \brief (MPDDRC) Monitor Address High/Low Port 2 Register */
  #define REG_MPDDRC_MADDR3                         (0xFFFFE870U) /**< \brief (MPDDRC) Monitor Address High/Low Port 3 Register */
  #define REG_MPDDRC_MINFO0                         (0xFFFFE884U) /**< \brief (MPDDRC) Monitor Information Port 0 Register */
  #define REG_MPDDRC_MINFO1                         (0xFFFFE888U) /**< \brief (MPDDRC) Monitor Information Port 1 Register */
  #define REG_MPDDRC_MINFO2                         (0xFFFFE88CU) /**< \brief (MPDDRC) Monitor Information Port 2 Register */
  #define REG_MPDDRC_MINFO3                         (0xFFFFE890U) /**< \brief (MPDDRC) Monitor Information Port 3 Register */
  #define REG_MPDDRC_IER                            (0xFFFFE8C0U) /**< \brief (MPDDRC) Interrupt Enable Register */
  #define REG_MPDDRC_IDR                            (0xFFFFE8C4U) /**< \brief (MPDDRC) Interrupt Disable Register */
  #define REG_MPDDRC_IMR                            (0xFFFFE8C8U) /**< \brief (MPDDRC) Interrupt Mask Register */
  #define REG_MPDDRC_ISR                            (0xFFFFE8CCU) /**< \brief (MPDDRC) Interrupt Status Register */
  #define REG_MPDDRC_SAFETY                         (0xFFFFE8D0U) /**< \brief (MPDDRC) Safety Register */
  #define REG_MPDDRC_WPMR                           (0xFFFFE8E4U) /**< \brief (MPDDRC) Write Protection Mode Register */
  #define REG_MPDDRC_WPSR                           (0xFFFFE8E8U) /**< \brief (MPDDRC) Write Protection Status Register */
#else
  #define REG_MPDDRC_MR            (*(__IO uint32_t*)0xFFFFE800U) /**< \brief (MPDDRC) Mode Register */
  #define REG_MPDDRC_RTR           (*(__IO uint32_t*)0xFFFFE804U) /**< \brief (MPDDRC) Refresh Timer Register */
  #define REG_MPDDRC_CR            (*(__IO uint32_t*)0xFFFFE808U) /**< \brief (MPDDRC) Configuration Register */
  #define REG_MPDDRC_TPR0          (*(__IO uint32_t*)0xFFFFE80CU) /**< \brief (MPDDRC) Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1          (*(__IO uint32_t*)0xFFFFE810U) /**< \brief (MPDDRC) Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2          (*(__IO uint32_t*)0xFFFFE814U) /**< \brief (MPDDRC) Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR           (*(__IO uint32_t*)0xFFFFE81CU) /**< \brief (MPDDRC) Low-Power Register */
  #define REG_MPDDRC_MD            (*(__IO uint32_t*)0xFFFFE820U) /**< \brief (MPDDRC) Memory Device Register */
  #define REG_MPDDRC_IO_CALIBR     (*(__IO uint32_t*)0xFFFFE834U) /**< \brief (MPDDRC) I/O Calibration Register */
  #define REG_MPDDRC_OCMS          (*(__IO uint32_t*)0xFFFFE838U) /**< \brief (MPDDRC) OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1     (*(__O  uint32_t*)0xFFFFE83CU) /**< \brief (MPDDRC) OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2     (*(__O  uint32_t*)0xFFFFE840U) /**< \brief (MPDDRC) OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER  (*(__IO uint32_t*)0xFFFFE844U) /**< \brief (MPDDRC) Configuration Arbiter Register */
  #define REG_MPDDRC_TIMEOUT       (*(__IO uint32_t*)0xFFFFE848U) /**< \brief (MPDDRC) Timeout Register */
  #define REG_MPDDRC_REQ_PORT_0123 (*(__IO uint32_t*)0xFFFFE84CU) /**< \brief (MPDDRC) Request Port 0-1-2-3 Register */
  #define REG_MPDDRC_BDW_PORT_0123 (*(__I  uint32_t*)0xFFFFE854U) /**< \brief (MPDDRC) Current/Maximum Bandwidth Port 0-1-2-3 Register */
  #define REG_MPDDRC_RD_DATA_PATH  (*(__IO uint32_t*)0xFFFFE85CU) /**< \brief (MPDDRC) Read Data Path Register */
  #define REG_MPDDRC_MCFGR         (*(__IO uint32_t*)0xFFFFE860U) /**< \brief (MPDDRC) Monitor Configuration Register */
  #define REG_MPDDRC_MADDR0        (*(__IO uint32_t*)0xFFFFE864U) /**< \brief (MPDDRC) Monitor Address High/Low Port 0 Register */
  #define REG_MPDDRC_MADDR1        (*(__IO uint32_t*)0xFFFFE868U) /**< \brief (MPDDRC) Monitor Address High/Low Port 1 Register */
  #define REG_MPDDRC_MADDR2        (*(__IO uint32_t*)0xFFFFE86CU) /**< \brief (MPDDRC) Monitor Address High/Low Port 2 Register */
  #define REG_MPDDRC_MADDR3        (*(__IO uint32_t*)0xFFFFE870U) /**< \brief (MPDDRC) Monitor Address High/Low Port 3 Register */
  #define REG_MPDDRC_MINFO0        (*(__I  uint32_t*)0xFFFFE884U) /**< \brief (MPDDRC) Monitor Information Port 0 Register */
  #define REG_MPDDRC_MINFO1        (*(__I  uint32_t*)0xFFFFE888U) /**< \brief (MPDDRC) Monitor Information Port 1 Register */
  #define REG_MPDDRC_MINFO2        (*(__I  uint32_t*)0xFFFFE88CU) /**< \brief (MPDDRC) Monitor Information Port 2 Register */
  #define REG_MPDDRC_MINFO3        (*(__I  uint32_t*)0xFFFFE890U) /**< \brief (MPDDRC) Monitor Information Port 3 Register */
  #define REG_MPDDRC_IER           (*(__O  uint32_t*)0xFFFFE8C0U) /**< \brief (MPDDRC) Interrupt Enable Register */
  #define REG_MPDDRC_IDR           (*(__O  uint32_t*)0xFFFFE8C4U) /**< \brief (MPDDRC) Interrupt Disable Register */
  #define REG_MPDDRC_IMR           (*(__I  uint32_t*)0xFFFFE8C8U) /**< \brief (MPDDRC) Interrupt Mask Register */
  #define REG_MPDDRC_ISR           (*(__I  uint32_t*)0xFFFFE8CCU) /**< \brief (MPDDRC) Interrupt Status Register */
  #define REG_MPDDRC_SAFETY        (*(__IO uint32_t*)0xFFFFE8D0U) /**< \brief (MPDDRC) Safety Register */
  #define REG_MPDDRC_WPMR          (*(__IO uint32_t*)0xFFFFE8E4U) /**< \brief (MPDDRC) Write Protection Mode Register */
  #define REG_MPDDRC_WPSR          (*(__I  uint32_t*)0xFFFFE8E8U) /**< \brief (MPDDRC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_MPDDRC_INSTANCE_ */
