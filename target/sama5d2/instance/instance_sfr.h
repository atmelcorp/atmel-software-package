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

#ifndef _SAMA5D2_SFR_INSTANCE_
#define _SAMA5D2_SFR_INSTANCE_

/* ========== Register definition for SFR peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SFR_EMA                         (0xF8030000U) /**< \brief (SFR) Memory Margin Adjustment Register */
#define REG_SFR_DDRCFG                      (0xF8030004U) /**< \brief (SFR) DDR Configuration Register */
#define REG_SFR_OHCIICR                     (0xF8030010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
#define REG_SFR_OHCIISR                     (0xF8030014U) /**< \brief (SFR) OHCI Interrupt Status Register */
#define REG_SFR_CORTEX                      (0xF803001CU) /**< \brief (SFR) Cortex Configuration Register */
#define REG_SFR_AHB                         (0xF8030020U) /**< \brief (SFR) AHB Configuration Register */
#define REG_SFR_BRIDGE                      (0xF8030024U) /**< \brief (SFR) Bridge Configuration Register */
#define REG_SFR_SECURE                      (0xF8030028U) /**< \brief (SFR) Security Configuration Register */
#define REG_SFR_UTMICKTRIM                  (0xF8030030U) /**< \brief (SFR) UTMI Clock Trimming Register */
#define REG_SFR_UTMIHSTRIM                  (0xF8030034U) /**< \brief (SFR) UTMI High Speed Trimming Register */
#define REG_SFR_UTMIFSTRIM                  (0xF8030038U) /**< \brief (SFR) UTMI Full Speed Trimming Register */
#define REG_SFR_UTMISWAP                    (0xF803003CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
#define REG_SFR_EBICFG                      (0xF8030040U) /**< \brief (SFR) EBI Configuration Register */
#define REG_SFR_ANACFG                      (0xF8030044U) /**< \brief (SFR) Analog Configuration Register */
#define REG_SFR_CAN                         (0xF8030048U) /**< \brief (SFR) CAN memories address based Register */
#define REG_SFR_SN0                         (0xF803004CU) /**< \brief (SFR) Serial Number 0 Register */
#define REG_SFR_SN1                         (0xF8030050U) /**< \brief (SFR) Seriel Number 1 Register */
#define REG_SFR_AICREDIR                    (0xF8030054U) /**< \brief (SFR) AIC interrupt Redirection Register */
#define REG_SFR_L2CC_HRAMC                  (0xF8030058U) /**< \brief (SFR) L2CC_HRAMC1 */
#define REG_SFR_RM0                         (0xF803005CU) /**< \brief (SFR) ReadMargin0 Register */
#define REG_SFR_RM1                         (0xF8030060U) /**< \brief (SFR) ReadMargin1 Register */
#define REG_SFR_RM2                         (0xF8030064U) /**< \brief (SFR) ReadMargin2 Register */
#define REG_SFR_RM3                         (0xF8030068U) /**< \brief (SFR) ReadMargin3 Register */
#define REG_SFR_RM4                         (0xF803006CU) /**< \brief (SFR) ReadMargin4 Register */
#define REG_SFR_RM5                         (0xF8030070U) /**< \brief (SFR) ReadMargin5 Register */
#define REG_SFR_RM6                         (0xF8030074U) /**< \brief (SFR) ReadMargin6 Register */
#define REG_SFR_RM7                         (0xF8030078U) /**< \brief (SFR) ReadMargin7 Register */
#define REG_SFR_I2SCLKSEL                   (0xF8030090U) /**< \brief (SFR) I2S Register */
#else
#define REG_SFR_EMA        (*(__IO uint32_t*)0xF8030000U) /**< \brief (SFR) Memory Margin Adjustment Register */
#define REG_SFR_DDRCFG     (*(__IO uint32_t*)0xF8030004U) /**< \brief (SFR) DDR Configuration Register */
#define REG_SFR_OHCIICR    (*(__IO uint32_t*)0xF8030010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
#define REG_SFR_OHCIISR    (*(__I  uint32_t*)0xF8030014U) /**< \brief (SFR) OHCI Interrupt Status Register */
#define REG_SFR_CORTEX     (*(__IO uint32_t*)0xF803001CU) /**< \brief (SFR) Cortex Configuration Register */
#define REG_SFR_AHB        (*(__IO uint32_t*)0xF8030020U) /**< \brief (SFR) AHB Configuration Register */
#define REG_SFR_BRIDGE     (*(__IO uint32_t*)0xF8030024U) /**< \brief (SFR) Bridge Configuration Register */
#define REG_SFR_SECURE     (*(__IO uint32_t*)0xF8030028U) /**< \brief (SFR) Security Configuration Register */
#define REG_SFR_UTMICKTRIM (*(__IO uint32_t*)0xF8030030U) /**< \brief (SFR) UTMI Clock Trimming Register */
#define REG_SFR_UTMIHSTRIM (*(__IO uint32_t*)0xF8030034U) /**< \brief (SFR) UTMI High Speed Trimming Register */
#define REG_SFR_UTMIFSTRIM (*(__IO uint32_t*)0xF8030038U) /**< \brief (SFR) UTMI Full Speed Trimming Register */
#define REG_SFR_UTMISWAP   (*(__IO uint32_t*)0xF803003CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
#define REG_SFR_EBICFG     (*(__IO uint32_t*)0xF8030040U) /**< \brief (SFR) EBI Configuration Register */
#define REG_SFR_ANACFG     (*(__IO uint32_t*)0xF8030044U) /**< \brief (SFR) Analog Configuration Register */
#define REG_SFR_CAN        (*(__IO uint32_t*)0xF8030048U) /**< \brief (SFR) CAN memories address based Register */
#define REG_SFR_SN0        (*(__I  uint32_t*)0xF803004CU) /**< \brief (SFR) Serial Number 0 Register */
#define REG_SFR_SN1        (*(__I  uint32_t*)0xF8030050U) /**< \brief (SFR) Seriel Number 1 Register */
#define REG_SFR_AICREDIR   (*(__IO uint32_t*)0xF8030054U) /**< \brief (SFR) AIC interrupt Redirection Register */
#define REG_SFR_L2CC_HRAMC (*(__IO uint32_t*)0xF8030058U) /**< \brief (SFR) L2CC_HRAMC1 */
#define REG_SFR_RM0        (*(__IO uint32_t*)0xF803005CU) /**< \brief (SFR) ReadMargin0 Register */
#define REG_SFR_RM1        (*(__IO uint32_t*)0xF8030060U) /**< \brief (SFR) ReadMargin1 Register */
#define REG_SFR_RM2        (*(__IO uint32_t*)0xF8030064U) /**< \brief (SFR) ReadMargin2 Register */
#define REG_SFR_RM3        (*(__IO uint32_t*)0xF8030068U) /**< \brief (SFR) ReadMargin3 Register */
#define REG_SFR_RM4        (*(__IO uint32_t*)0xF803006CU) /**< \brief (SFR) ReadMargin4 Register */
#define REG_SFR_RM5        (*(__IO uint32_t*)0xF8030070U) /**< \brief (SFR) ReadMargin5 Register */
#define REG_SFR_RM6        (*(__IO uint32_t*)0xF8030074U) /**< \brief (SFR) ReadMargin6 Register */
#define REG_SFR_RM7        (*(__IO uint32_t*)0xF8030078U) /**< \brief (SFR) ReadMargin7 Register */
#define REG_SFR_I2SCLKSEL  (*(__IO uint32_t*)0xF8030090U) /**< \brief (SFR) I2S Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_SFR_INSTANCE_ */
