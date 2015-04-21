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

#ifndef _SAMA5D4_MPDDRC_INSTANCE_
#define _SAMA5D4_MPDDRC_INSTANCE_

/* ========== Register definition for MPDDRC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MPDDRC_MR                              (0xF0010000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
#define REG_MPDDRC_RTR                             (0xF0010004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
#define REG_MPDDRC_CR                              (0xF0010008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
#define REG_MPDDRC_TPR0                            (0xF001000CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
#define REG_MPDDRC_TPR1                            (0xF0010010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
#define REG_MPDDRC_TPR2                            (0xF0010014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
#define REG_MPDDRC_LPR                             (0xF001001CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
#define REG_MPDDRC_MD                              (0xF0010020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
#define REG_MPDDRC_LPDDR2_LPR                      (0xF0010028U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
#define REG_MPDDRC_LPDDR2_CAL_MR4                  (0xF001002CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
#define REG_MPDDRC_LPDDR2_TIM_CAL                  (0xF0010030U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
#define REG_MPDDRC_IO_CALIBR                       (0xF0010034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
#define REG_MPDDRC_OCMS                            (0xF0010038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
#define REG_MPDDRC_OCMS_KEY1                       (0xF001003CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
#define REG_MPDDRC_OCMS_KEY2                       (0xF0010040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
#define REG_MPDDRC_CONF_ARBITER                    (0xF0010044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter Register */
#define REG_MPDDRC_TIMEOUT                         (0xF0010048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 Register */
#define REG_MPDDRC_REQ_PORT_0123                   (0xF001004CU) /**< \brief (MPDDRC) MPDDRC Request Port 0/1/2/3 Register */
#define REG_MPDDRC_REQ_PORT_4567                   (0xF0010050U) /**< \brief (MPDDRC) MPDDRC Request Port 4/5/6/7 Register */
#define REG_MPDDRC_BDW_PORT_0123                   (0xF0010054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 Register */
#define REG_MPDDRC_BDW_PORT_4567                   (0xF0010058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 Register */
#define REG_MPDDRC_RD_DATA_PATH                    (0xF001005CU) /**< \brief (MPDDRC) MPDDRC Read Datapath Register */
#define REG_MPDDRC_SAW                             (0xF0010060U) /**< \brief (MPDDRC) MPDDRC Smart Adaptation Wrapper 0 Register */
#define REG_MPDDRC_WPMR                            (0xF00100E4U) /**< \brief (MPDDRC) MPDDRC Write Protection Mode Register */
#define REG_MPDDRC_WPSR                            (0xF00100E8U) /**< \brief (MPDDRC) MPDDRC Write Protection Status Register */
#define REG_MPDDRC_DLL_OS                          (0xF0010100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
#define REG_MPDDRC_DLL_MO                          (0xF0010104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
#define REG_MPDDRC_DLL_SO0                         (0xF0010108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
#define REG_MPDDRC_DLL_SO1                         (0xF001010CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
#define REG_MPDDRC_DLL_WRO                         (0xF0010110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
#define REG_MPDDRC_DLL_ADO                         (0xF0010114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
#define REG_MPDDRC_DLL_SM                          (0xF0010118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
#define REG_MPDDRC_DLL_SSL                         (0xF0010128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
#define REG_MPDDRC_DLL_SWR                         (0xF0010148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
#define REG_MPDDRC_DLL_SAD                         (0xF0010158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#else
#define REG_MPDDRC_MR             (*(__IO uint32_t*)0xF0010000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
#define REG_MPDDRC_RTR            (*(__IO uint32_t*)0xF0010004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
#define REG_MPDDRC_CR             (*(__IO uint32_t*)0xF0010008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
#define REG_MPDDRC_TPR0           (*(__IO uint32_t*)0xF001000CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
#define REG_MPDDRC_TPR1           (*(__IO uint32_t*)0xF0010010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
#define REG_MPDDRC_TPR2           (*(__IO uint32_t*)0xF0010014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
#define REG_MPDDRC_LPR            (*(__IO uint32_t*)0xF001001CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
#define REG_MPDDRC_MD             (*(__IO uint32_t*)0xF0010020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
#define REG_MPDDRC_LPDDR2_LPR     (*(__IO uint32_t*)0xF0010028U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
#define REG_MPDDRC_LPDDR2_CAL_MR4 (*(__IO uint32_t*)0xF001002CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
#define REG_MPDDRC_LPDDR2_TIM_CAL (*(__IO uint32_t*)0xF0010030U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
#define REG_MPDDRC_IO_CALIBR      (*(__IO uint32_t*)0xF0010034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
#define REG_MPDDRC_OCMS           (*(__IO uint32_t*)0xF0010038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
#define REG_MPDDRC_OCMS_KEY1      (*(__O  uint32_t*)0xF001003CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
#define REG_MPDDRC_OCMS_KEY2      (*(__O  uint32_t*)0xF0010040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
#define REG_MPDDRC_CONF_ARBITER   (*(__IO uint32_t*)0xF0010044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter Register */
#define REG_MPDDRC_TIMEOUT        (*(__IO uint32_t*)0xF0010048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 Register */
#define REG_MPDDRC_REQ_PORT_0123  (*(__IO uint32_t*)0xF001004CU) /**< \brief (MPDDRC) MPDDRC Request Port 0/1/2/3 Register */
#define REG_MPDDRC_REQ_PORT_4567  (*(__IO uint32_t*)0xF0010050U) /**< \brief (MPDDRC) MPDDRC Request Port 4/5/6/7 Register */
#define REG_MPDDRC_BDW_PORT_0123  (*(__I  uint32_t*)0xF0010054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 Register */
#define REG_MPDDRC_BDW_PORT_4567  (*(__I  uint32_t*)0xF0010058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 Register */
#define REG_MPDDRC_RD_DATA_PATH   (*(__IO uint32_t*)0xF001005CU) /**< \brief (MPDDRC) MPDDRC Read Datapath Register */
#define REG_MPDDRC_SAW            (*(__IO uint32_t*)0xF0010060U) /**< \brief (MPDDRC) MPDDRC Smart Adaptation Wrapper 0 Register */
#define REG_MPDDRC_WPMR           (*(__IO uint32_t*)0xF00100E4U) /**< \brief (MPDDRC) MPDDRC Write Protection Mode Register */
#define REG_MPDDRC_WPSR           (*(__I  uint32_t*)0xF00100E8U) /**< \brief (MPDDRC) MPDDRC Write Protection Status Register */
#define REG_MPDDRC_DLL_OS         (*(__IO uint32_t*)0xF0010100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
#define REG_MPDDRC_DLL_MO         (*(__IO uint32_t*)0xF0010104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
#define REG_MPDDRC_DLL_SO0        (*(__IO uint32_t*)0xF0010108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
#define REG_MPDDRC_DLL_SO1        (*(__IO uint32_t*)0xF001010CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
#define REG_MPDDRC_DLL_WRO        (*(__IO uint32_t*)0xF0010110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
#define REG_MPDDRC_DLL_ADO        (*(__IO uint32_t*)0xF0010114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
#define REG_MPDDRC_DLL_SM         (*(__I  uint32_t*)0xF0010118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
#define REG_MPDDRC_DLL_SSL        (*(__I  uint32_t*)0xF0010128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
#define REG_MPDDRC_DLL_SWR        (*(__I  uint32_t*)0xF0010148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
#define REG_MPDDRC_DLL_SAD        (*(__I  uint32_t*)0xF0010158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_MPDDRC_INSTANCE_ */
