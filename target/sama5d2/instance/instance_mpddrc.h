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

#ifndef _SAMA5D2_MPDDRC_INSTANCE_
#define _SAMA5D2_MPDDRC_INSTANCE_

/* ========== Register definition for MPDDRC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MPDDRC_MR                               (0xF000C000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
  #define REG_MPDDRC_RTR                              (0xF000C004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
  #define REG_MPDDRC_CR                               (0xF000C008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
  #define REG_MPDDRC_TPR0                             (0xF000C00CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1                             (0xF000C010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2                             (0xF000C014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR                              (0xF000C01CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
  #define REG_MPDDRC_MD                               (0xF000C020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
  #define REG_MPDDRC_LPDDR23_LPR                      (0xF000C028U) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Low-power Register */
  #define REG_MPDDRC_LPDDR23_CAL_MR4                  (0xF000C02CU) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Calibration and MR4 Register */
  #define REG_MPDDRC_LPDDR23_TIM_CAL                  (0xF000C030U) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Timing Calibration Register */
  #define REG_MPDDRC_IO_CALIBR                        (0xF000C034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
  #define REG_MPDDRC_OCMS                             (0xF000C038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1                        (0xF000C03CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2                        (0xF000C040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER                     (0xF000C044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter Register */
  #define REG_MPDDRC_TIMEOUT                          (0xF000C048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 Register */
  #define REG_MPDDRC_REQ_PORT_0123                    (0xF000C04CU) /**< \brief (MPDDRC) MPDDRC Request Port 0/1/2/3 Register */
  #define REG_MPDDRC_REQ_PORT_4567                    (0xF000C050U) /**< \brief (MPDDRC) MPDDRC Request Port 4/5/6/7 Register */
  #define REG_MPDDRC_BDW_PORT_0123                    (0xF000C054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 Register */
  #define REG_MPDDRC_BDW_PORT_4567                    (0xF000C058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 Register */
  #define REG_MPDDRC_RD_DATA_PATH                     (0xF000C05CU) /**< \brief (MPDDRC) MPDDRC Read Datapath Register */
  #define REG_MPDDRC_MCFGR                            (0xF000C060U) /**< \brief (MPDDRC) MPDDRC Monitor configuration */
  #define REG_MPDDRC_MADDR0                           (0xF000C064U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 0 */
  #define REG_MPDDRC_MADDR1                           (0xF000C068U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 1 */
  #define REG_MPDDRC_MADDR2                           (0xF000C06CU) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 2 */
  #define REG_MPDDRC_MADDR3                           (0xF000C070U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 3 */
  #define REG_MPDDRC_MADDR4                           (0xF000C074U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 4 */
  #define REG_MPDDRC_MADDR5                           (0xF000C078U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 5 */
  #define REG_MPDDRC_MADDR6                           (0xF000C07CU) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 6 */
  #define REG_MPDDRC_MADDR7                           (0xF000C080U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 7 */
  #define REG_MPDDRC_MINFO0                           (0xF000C084U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 0 */
  #define REG_MPDDRC_MINFO1                           (0xF000C088U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 1 */
  #define REG_MPDDRC_MINFO2                           (0xF000C08CU) /**< \brief (MPDDRC) MPDDRC Monitor Information port 2 */
  #define REG_MPDDRC_MINFO3                           (0xF000C090U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 3 */
  #define REG_MPDDRC_MINFO4                           (0xF000C094U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 4 */
  #define REG_MPDDRC_MINFO5                           (0xF000C098U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 5 */
  #define REG_MPDDRC_MINFO6                           (0xF000C09CU) /**< \brief (MPDDRC) MPDDRC Monitor Information port 6 */
  #define REG_MPDDRC_MINFO7                           (0xF000C0A0U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 7 */
  #define REG_MPDDRC_WPMR                             (0xF000C0E4U) /**< \brief (MPDDRC) MPDDRC Write Protection Mode Register */
  #define REG_MPDDRC_WPSR                             (0xF000C0E8U) /**< \brief (MPDDRC) MPDDRC Write Protection Status Register */
  #define REG_MPDDRC_VERSION                          (0xF000C0FCU) /**< \brief (MPDDRC) MPDDRC Version Register */
  #define REG_MPDDRC_DLL_OS                           (0xF000C100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
  #define REG_MPDDRC_DLL_MAO                          (0xF000C104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
  #define REG_MPDDRC_DLL_SO0                          (0xF000C108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
  #define REG_MPDDRC_DLL_SO1                          (0xF000C10CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
  #define REG_MPDDRC_DLL_WRO                          (0xF000C110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
  #define REG_MPDDRC_DLL_ADO                          (0xF000C114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
  #define REG_MPDDRC_DLL_SM                           (0xF000C118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
  #define REG_MPDDRC_DLL_SSL                          (0xF000C128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
  #define REG_MPDDRC_DLL_SWR                          (0xF000C148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
  #define REG_MPDDRC_DLL_SAD                          (0xF000C158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#else
  #define REG_MPDDRC_MR              (*(__IO uint32_t*)0xF000C000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
  #define REG_MPDDRC_RTR             (*(__IO uint32_t*)0xF000C004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
  #define REG_MPDDRC_CR              (*(__IO uint32_t*)0xF000C008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
  #define REG_MPDDRC_TPR0            (*(__IO uint32_t*)0xF000C00CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1            (*(__IO uint32_t*)0xF000C010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2            (*(__IO uint32_t*)0xF000C014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR             (*(__IO uint32_t*)0xF000C01CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
  #define REG_MPDDRC_MD              (*(__IO uint32_t*)0xF000C020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
  #define REG_MPDDRC_LPDDR23_LPR     (*(__IO uint32_t*)0xF000C028U) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Low-power Register */
  #define REG_MPDDRC_LPDDR23_CAL_MR4 (*(__IO uint32_t*)0xF000C02CU) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Calibration and MR4 Register */
  #define REG_MPDDRC_LPDDR23_TIM_CAL (*(__IO uint32_t*)0xF000C030U) /**< \brief (MPDDRC) MPDDRC LPDDR2-LPDDR3 Timing Calibration Register */
  #define REG_MPDDRC_IO_CALIBR       (*(__IO uint32_t*)0xF000C034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
  #define REG_MPDDRC_OCMS            (*(__IO uint32_t*)0xF000C038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1       (*(__O  uint32_t*)0xF000C03CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2       (*(__O  uint32_t*)0xF000C040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER    (*(__IO uint32_t*)0xF000C044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter Register */
  #define REG_MPDDRC_TIMEOUT         (*(__IO uint32_t*)0xF000C048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 Register */
  #define REG_MPDDRC_REQ_PORT_0123   (*(__IO uint32_t*)0xF000C04CU) /**< \brief (MPDDRC) MPDDRC Request Port 0/1/2/3 Register */
  #define REG_MPDDRC_REQ_PORT_4567   (*(__IO uint32_t*)0xF000C050U) /**< \brief (MPDDRC) MPDDRC Request Port 4/5/6/7 Register */
  #define REG_MPDDRC_BDW_PORT_0123   (*(__I  uint32_t*)0xF000C054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 Register */
  #define REG_MPDDRC_BDW_PORT_4567   (*(__I  uint32_t*)0xF000C058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 Register */
  #define REG_MPDDRC_RD_DATA_PATH    (*(__IO uint32_t*)0xF000C05CU) /**< \brief (MPDDRC) MPDDRC Read Datapath Register */
  #define REG_MPDDRC_MCFGR           (*(__IO uint32_t*)0xF000C060U) /**< \brief (MPDDRC) MPDDRC Monitor configuration */
  #define REG_MPDDRC_MADDR0          (*(__IO uint32_t*)0xF000C064U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 0 */
  #define REG_MPDDRC_MADDR1          (*(__IO uint32_t*)0xF000C068U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 1 */
  #define REG_MPDDRC_MADDR2          (*(__IO uint32_t*)0xF000C06CU) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 2 */
  #define REG_MPDDRC_MADDR3          (*(__IO uint32_t*)0xF000C070U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 3 */
  #define REG_MPDDRC_MADDR4          (*(__IO uint32_t*)0xF000C074U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 4 */
  #define REG_MPDDRC_MADDR5          (*(__IO uint32_t*)0xF000C078U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 5 */
  #define REG_MPDDRC_MADDR6          (*(__IO uint32_t*)0xF000C07CU) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 6 */
  #define REG_MPDDRC_MADDR7          (*(__IO uint32_t*)0xF000C080U) /**< \brief (MPDDRC) MPDDRC Monitor Address High/Low port 7 */
  #define REG_MPDDRC_MINFO0          (*(__I  uint32_t*)0xF000C084U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 0 */
  #define REG_MPDDRC_MINFO1          (*(__I  uint32_t*)0xF000C088U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 1 */
  #define REG_MPDDRC_MINFO2          (*(__I  uint32_t*)0xF000C08CU) /**< \brief (MPDDRC) MPDDRC Monitor Information port 2 */
  #define REG_MPDDRC_MINFO3          (*(__I  uint32_t*)0xF000C090U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 3 */
  #define REG_MPDDRC_MINFO4          (*(__I  uint32_t*)0xF000C094U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 4 */
  #define REG_MPDDRC_MINFO5          (*(__I  uint32_t*)0xF000C098U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 5 */
  #define REG_MPDDRC_MINFO6          (*(__I  uint32_t*)0xF000C09CU) /**< \brief (MPDDRC) MPDDRC Monitor Information port 6 */
  #define REG_MPDDRC_MINFO7          (*(__I  uint32_t*)0xF000C0A0U) /**< \brief (MPDDRC) MPDDRC Monitor Information port 7 */
  #define REG_MPDDRC_WPMR            (*(__IO uint32_t*)0xF000C0E4U) /**< \brief (MPDDRC) MPDDRC Write Protection Mode Register */
  #define REG_MPDDRC_WPSR            (*(__I  uint32_t*)0xF000C0E8U) /**< \brief (MPDDRC) MPDDRC Write Protection Status Register */
  #define REG_MPDDRC_VERSION         (*(__I  uint32_t*)0xF000C0FCU) /**< \brief (MPDDRC) MPDDRC Version Register */
  #define REG_MPDDRC_DLL_OS          (*(__IO uint32_t*)0xF000C100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
  #define REG_MPDDRC_DLL_MAO         (*(__IO uint32_t*)0xF000C104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
  #define REG_MPDDRC_DLL_SO0         (*(__IO uint32_t*)0xF000C108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
  #define REG_MPDDRC_DLL_SO1         (*(__IO uint32_t*)0xF000C10CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
  #define REG_MPDDRC_DLL_WRO         (*(__IO uint32_t*)0xF000C110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
  #define REG_MPDDRC_DLL_ADO         (*(__IO uint32_t*)0xF000C114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
  #define REG_MPDDRC_DLL_SM          (*(__I  uint32_t*)0xF000C118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
  #define REG_MPDDRC_DLL_SSL         (*(__I  uint32_t*)0xF000C128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
  #define REG_MPDDRC_DLL_SWR         (*(__I  uint32_t*)0xF000C148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
  #define REG_MPDDRC_DLL_SAD         (*(__I  uint32_t*)0xF000C158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_MPDDRC_INSTANCE_ */
