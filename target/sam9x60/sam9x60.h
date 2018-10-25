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

#ifndef _SAM9X60_
#define _SAM9X60_

/** \addtogroup SAM9X60_definitions SAM9X60 definitions
  This file defines all structures and symbols for SAM9X60:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#endif

typedef enum IRQn
{
  SYSC_IRQn            =  1, /**<  1 SAM9X60 logical-OR interrupt of SYSC, PMC, DWDT, SHDWC, PIT, RTC (SYSC) */
  PIOA_IRQn            =  2, /**<  2 SAM9X60 Parallel I/O Controller A (PIOA) */
  PIOB_IRQn            =  3, /**<  3 SAM9X60 Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            =  4, /**<  4 SAM9X60 Parallel I/O Controller C (PIOC) */
  FLEXCOM0_IRQn        =  5, /**<  5 SAM9X60 /!\\ was USART 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM0) */
  FLEXCOM1_IRQn        =  6, /**<  6 SAM9X60 /!\\ was USART 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM1) */
  FLEXCOM2_IRQn        =  7, /**<  7 SAM9X60 /!\\ was USART 2 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM2) */
  FLEXCOM3_IRQn        =  8, /**<  8 SAM9X60 /!\\ was USART 3 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM3) */
  FLEXCOM6_IRQn        =  9, /**<  9 SAM9X60 /!\\ was TWI 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM6) */
  FLEXCOM7_IRQn        = 10, /**< 10 SAM9X60 /!\\ was TWI 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM7) */
  FLEXCOM8_IRQn        = 11, /**< 11 SAM9X60 /!\\ was TWI 2 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM8) */
  SDMMC0_IRQn          = 12, /**< 12 SAM9X60 Secure Data Memory Card Controller 0 - There is a divider by two and we need 52MHz on the I/F clock. Miniminum requirement is 104MHz. (SDMMC0) */
  FLEXCOM4_IRQn        = 13, /**< 13 SAM9X60 /!\\ was SPI 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM4) */
  FLEXCOM5_IRQn        = 14, /**< 14 SAM9X60 /!\\ was SPI 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM5) */
  FLEXCOM9_IRQn        = 15, /**< 15 SAM9X60 /!\\ was UART 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM9) */
  FLEXCOM10_IRQn       = 16, /**< 16 SAM9X60 /!\\ was UART 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM10) */
  TC0_IRQn             = 17, /**< 17 SAM9X60 TC 0,1,2 - fGCLK < fMCK0 / 3 - False Path (TC0) */
  PWM_IRQn             = 18, /**< 18 SAM9X60 Pulse Width Modulation Controller (PWM) */
  ADC_IRQn             = 19, /**< 19 SAM9X60 ADC Controller - fGCLK < fMCK0 / 3 - False Path (ADC) */
  XDMAC_IRQn           = 20, /**< 20 SAM9X60 Extended DMA Controller (XDMAC) */
  MATRIX_IRQn          = 21, /**< 21 SAM9X60 Matrix (MATRIX) */
  UHPHS_IRQn           = 22, /**< 22 SAM9X60 USB Host High Speed (UHPHS) */
  UDPHS_IRQn           = 23, /**< 23 SAM9X60 USB Device High Speed (UDPHS) */
  EMAC0_IRQn           = 24, /**< 24 SAM9X60 Ethernet MAC 0 (EMAC0) */
  LCDC_IRQn            = 25, /**< 25 SAM9X60 LCD Controller (LCDC) */
  SDMMC1_IRQn          = 26, /**< 26 SAM9X60 Secure Data Memory Card Controller 1 - There is a divider by two and we need 52MHz on the I/F clock. Miniminum requirement is 104MHz. (SDMMC1) */
  EMAC1_IRQn           = 27, /**< 27 SAM9X60 Ethernet MAC 1 (EMAC1) */
  SSC_IRQn             = 28, /**< 28 SAM9X60 Synchronous Serial Controller (SSC) */
  CAN0_IRQn            = 29, /**< 29 SAM9X60 CAN controller 0 (CAN0) */
  CAN1_IRQn            = 30, /**< 30 SAM9X60 CAN controller 1 (CAN1) */
  FLEXCOM11_IRQn       = 32, /**< 32 SAM9X60 /!\\ new - UART addition - fGCLK < fMCK0 / 3 - False Path (FLEXCOM11) */
  FLEXCOM12_IRQn       = 33, /**< 33 SAM9X60 /!\\ new - UART addition - fGCLK < fMCK0 / 3 - False Path (FLEXCOM12) */
  I2SMCC_IRQn          = 34, /**< 34 SAM9X60 I2S Multi Channel Controller (I2SMCC) */
  QSPI_IRQn            = 35, /**< 35 SAM9X60 Quad I/O SPI Controller (QSPI) */
  GFX2D_IRQn           = 36, /**< 36 SAM9X60 2D Graphic Controller (GFX2D) */
  PIT64B_IRQn          = 37, /**< 37 SAM9X60 64-b Timer - fGCLK < fMCK0 / 3 - False Path (PIT64B) */
  TRNG_IRQn            = 38, /**< 38 SAM9X60 True Random Number Generator (TRNG) */
  AES_IRQn             = 39, /**< 39 SAM9X60 Advanced Encryption Standard (AES) */
  TDES_IRQn            = 40, /**< 40 SAM9X60 Triple Data Encryption Standard (TDES) */
  SHA_IRQn             = 41, /**< 41 SAM9X60 Secure Hash Algorithm (SHA) */
  CLASSD_IRQn          = 42, /**< 42 SAM9X60 CLASS D Controller (CLASSD) */
  ISI_IRQn             = 43, /**< 43 SAM9X60 Image Sensor Interface (ISI) */
  PIOD_IRQn            = 44, /**< 44 SAM9X60 Parallel I/O Controller D (PIOD) */
  TC1_IRQn             = 45, /**< 45 SAM9X60 TC 3,4,5 - fGCLK < fMCK0 / 3 - False Path (TC1) */
  OTPC_IRQn            = 46, /**< 46 SAM9X60 OTP Controller (OTPC) */
  DBGU_IRQn            = 47, /**< 47 SAM9X60 DBGU - fGCLK < fMCK0 / 3 - False Path (DBGU) */
  PMECC_IRQn           = 48, /**< 48 SAM9X60 logical-OR interrupt of PMECC and PMERRLOC (PMECC) */
  SDRAMC_IRQn          = 49, /**< 49 SAM9X60 logical-OR interrupt of SDRAMC and MPDDRC and HSMC (SDRAMC) */

  PERIPH_COUNT_IRQn    = 50  /**< Number of peripheral IDs */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAM9X60 */
/* ************************************************************************** */
/** \addtogroup SAM9X60_api Peripheral Software API */
/*@{*/

#include "component/adc.h"
#include "component/aes.h"
#include "component/aic.h"
#include "component/bsc.h"
#include "component/can.h"
#include "component/classd.h"
#include "component/dbgu.h"
#include "component/emac.h"
#include "component/flexcom.h"
#include "component/gfx2d.h"
#include "component/gpbr.h"
#include "component/i2smcc.h"
#include "component/isi.h"
#include "component/lcdc.h"
#include "component/matrix.h"
#include "component/mpddrc.h"
#include "component/otpc.h"
#include "component/pio.h"
#include "component/pit.h"
#include "component/pit64b.h"
#include "component/pmc.h"
#include "component/pmecc.h"
#include "component/pmerrloc.h"
#include "component/pwm.h"
#include "component/qspi.h"
#include "component/rstc.h"
#include "component/rtc.h"
#include "component/rtt.h"
#include "component/sckc.h"
#include "component/sdmmc.h"
#include "component/sdramc.h"
#include "component/sfr.h"
#include "component/sha.h"
#include "component/shdwc.h"
#include "component/smc.h"
#include "component/ssc.h"
#include "component/syscwp.h"
#include "component/tc.h"
#include "component/tdes.h"
#include "component/trng.h"
#include "component/udphs.h"
#include "component/uhpfs.h"
#include "component/uhphs.h"
#include "component/wdt.h"
#include "component/xdmac.h"
/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */
/** \addtogroup SAM9X60_reg Registers Access Definitions */
/*@{*/

#include "instance/uhphs_ohci.h"
#include "instance/uhphs_ehci.h"
#include "instance/sdmmc0.h"
#include "instance/sdmmc1.h"
#include "instance/otpc.h"
#include "instance/flexcom4.h"
#include "instance/flexcom5.h"
#include "instance/xdmac.h"
#include "instance/ssc.h"
#include "instance/qspi.h"
#include "instance/gfx2d.h"
#include "instance/i2smcc.h"
#include "instance/flexcom11.h"
#include "instance/flexcom12.h"
#include "instance/pit64b.h"
#include "instance/sha.h"
#include "instance/trng.h"
#include "instance/aes.h"
#include "instance/tdes.h"
#include "instance/classd.h"
#include "instance/can0.h"
#include "instance/can1.h"
#include "instance/tc0.h"
#include "instance/tc1.h"
#include "instance/flexcom6.h"
#include "instance/flexcom7.h"
#include "instance/flexcom8.h"
#include "instance/flexcom0.h"
#include "instance/flexcom1.h"
#include "instance/flexcom2.h"
#include "instance/flexcom3.h"
#include "instance/emac0.h"
#include "instance/emac1.h"
#include "instance/pwm.h"
#include "instance/lcdc.h"
#include "instance/udphs.h"
#include "instance/flexcom9.h"
#include "instance/flexcom10.h"
#include "instance/isi.h"
#include "instance/adc.h"
#include "instance/sfr.h"
#include "instance/matrix.h"
#include "instance/pmecc.h"
#include "instance/pmerrloc.h"
#include "instance/mpddrc.h"
#include "instance/smc.h"
#include "instance/sdramc.h"
#include "instance/aic.h"
#include "instance/dbgu.h"
#include "instance/pioa.h"
#include "instance/piob.h"
#include "instance/pioc.h"
#include "instance/piod.h"
#include "instance/pmc.h"
#include "instance/rstc.h"
#include "instance/shdwc.h"
#include "instance/rtt.h"
#include "instance/pit.h"
#include "instance/sckc.h"
#include "instance/bsc.h"
#include "instance/gpbr.h"
#include "instance/rtc.h"
#include "instance/syscwp.h"
#include "instance/wdt.h"
/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */
/** \addtogroup SAM9X60_id Peripheral Ids Definitions */
/*@{*/

#define ID_SYSC      ( 1) /**< \brief logical-OR interrupt of SYSC, PMC, DWDT, SHDWC, PIT, RTC (SYSC) */
#define ID_PIOA      ( 2) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB      ( 3) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC      ( 4) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_FLEXCOM0  ( 5) /**< \brief /!\\ was USART 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM0) */
#define ID_FLEXCOM1  ( 6) /**< \brief /!\\ was USART 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM1) */
#define ID_FLEXCOM2  ( 7) /**< \brief /!\\ was USART 2 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM2) */
#define ID_FLEXCOM3  ( 8) /**< \brief /!\\ was USART 3 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM3) */
#define ID_FLEXCOM6  ( 9) /**< \brief /!\\ was TWI 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM6) */
#define ID_FLEXCOM7  (10) /**< \brief /!\\ was TWI 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM7) */
#define ID_FLEXCOM8  (11) /**< \brief /!\\ was TWI 2 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM8) */
#define ID_SDMMC0    (12) /**< \brief Secure Data Memory Card Controller 0 - There is a divider by two and we need 52MHz on the I/F clock. Miniminum requirement is 104MHz. (SDMMC0) */
#define ID_FLEXCOM4  (13) /**< \brief /!\\ was SPI 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM4) */
#define ID_FLEXCOM5  (14) /**< \brief /!\\ was SPI 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM5) */
#define ID_FLEXCOM9  (15) /**< \brief /!\\ was UART 0 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM9) */
#define ID_FLEXCOM10 (16) /**< \brief /!\\ was UART 1 - fGCLK < fMCK0 / 3 - False Path (FLEXCOM10) */
#define ID_TC0       (17) /**< \brief TC 0,1,2 - fGCLK < fMCK0 / 3 - False Path (TC0) */
#define ID_PWM       (18) /**< \brief Pulse Width Modulation Controller (PWM) */
#define ID_ADC       (19) /**< \brief ADC Controller - fGCLK < fMCK0 / 3 - False Path (ADC) */
#define ID_XDMAC     (20) /**< \brief Extended DMA Controller (XDMAC) */
#define ID_MATRIX    (21) /**< \brief Matrix (MATRIX) */
#define ID_UHPHS     (22) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS     (23) /**< \brief USB Device High Speed (UDPHS) */
#define ID_EMAC0     (24) /**< \brief Ethernet MAC 0 (EMAC0) */
#define ID_LCDC      (25) /**< \brief LCD Controller (LCDC) */
#define ID_SDMMC1    (26) /**< \brief Secure Data Memory Card Controller 1 - There is a divider by two and we need 52MHz on the I/F clock. Miniminum requirement is 104MHz. (SDMMC1) */
#define ID_EMAC1     (27) /**< \brief Ethernet MAC 1 (EMAC1) */
#define ID_SSC       (28) /**< \brief Synchronous Serial Controller (SSC) */
#define ID_CAN0      (29) /**< \brief CAN controller 0 (CAN0) */
#define ID_CAN1      (30) /**< \brief CAN controller 1 (CAN1) */
#define ID_FLEXCOM11 (32) /**< \brief /!\\ new - UART addition - fGCLK < fMCK0 / 3 - False Path (FLEXCOM11) */
#define ID_FLEXCOM12 (33) /**< \brief /!\\ new - UART addition - fGCLK < fMCK0 / 3 - False Path (FLEXCOM12) */
#define ID_I2SMCC    (34) /**< \brief I2S Multi Channel Controller (I2SMCC) */
#define ID_QSPI      (35) /**< \brief Quad I/O SPI Controller (QSPI) */
#define ID_GFX2D     (36) /**< \brief 2D Graphic Controller (GFX2D) */
#define ID_PIT64B    (37) /**< \brief 64-b Timer - fGCLK < fMCK0 / 3 - False Path (PIT64B) */
#define ID_TRNG      (38) /**< \brief True Random Number Generator (TRNG) */
#define ID_AES       (39) /**< \brief Advanced Encryption Standard (AES) */
#define ID_TDES      (40) /**< \brief Triple Data Encryption Standard (TDES) */
#define ID_SHA       (41) /**< \brief Secure Hash Algorithm (SHA) */
#define ID_CLASSD    (42) /**< \brief CLASS D Controller (CLASSD) */
#define ID_ISI       (43) /**< \brief Image Sensor Interface (ISI) */
#define ID_PIOD      (44) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_TC1       (45) /**< \brief TC 3,4,5 - fGCLK < fMCK0 / 3 - False Path (TC1) */
#define ID_OTPC      (46) /**< \brief OTP Controller (OTPC) */
#define ID_DBGU      (47) /**< \brief DBGU - fGCLK < fMCK0 / 3 - False Path (DBGU) */
#define ID_PMECC     (48) /**< \brief logical-OR interrupt of PMECC and PMERRLOC (PMECC) */
#define ID_SDRAMC    (49) /**< \brief logical-OR interrupt of SDRAMC and MPDDRC and HSMC (SDRAMC) */

#define ID_PERIPH_COUNT (50) /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */
/** \addtogroup SAM9X60_base Peripheral Base Address Definitions */
/*@{*/

#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define UHPHS_OHCI (0x00600000U) /**< \brief (UHPHS_OHCI) Base Address */
#define UHPHS_EHCI (0x00700000U) /**< \brief (UHPHS_EHCI) Base Address */
#define SDMMC0     (0x80000000U) /**< \brief (SDMMC0    ) Base Address */
#define SDMMC1     (0x90000000U) /**< \brief (SDMMC1    ) Base Address */
#define OTPC       (0xEFF00000U) /**< \brief (OTPC      ) Base Address */
#define FLEXCOM4   (0xF0000000U) /**< \brief (FLEXCOM4  ) Base Address */
#define FLEXCOM5   (0xF0004000U) /**< \brief (FLEXCOM5  ) Base Address */
#define XDMAC      (0xF0008000U) /**< \brief (XDMAC     ) Base Address */
#define SSC        (0xF0010000U) /**< \brief (SSC       ) Base Address */
#define QSPI       (0xF0014000U) /**< \brief (QSPI      ) Base Address */
#define GFX2D      (0xF0018000U) /**< \brief (GFX2D     ) Base Address */
#define I2SMCC     (0xF001C000U) /**< \brief (I2SMCC    ) Base Address */
#define FLEXCOM11  (0xF0020000U) /**< \brief (FLEXCOM11 ) Base Address */
#define FLEXCOM12  (0xF0024000U) /**< \brief (FLEXCOM12 ) Base Address */
#define PIT64B     (0xF0028000U) /**< \brief (PIT64B    ) Base Address */
#define SHA        (0xF002C000U) /**< \brief (SHA       ) Base Address */
#define TRNG       (0xF0030000U) /**< \brief (TRNG      ) Base Address */
#define AES        (0xF0034000U) /**< \brief (AES       ) Base Address */
#define TDES       (0xF0038000U) /**< \brief (TDES      ) Base Address */
#define CLASSD     (0xF003C000U) /**< \brief (CLASSD    ) Base Address */
#define CAN0       (0xF8000000U) /**< \brief (CAN0      ) Base Address */
#define CAN1       (0xF8004000U) /**< \brief (CAN1      ) Base Address */
#define TC0        (0xF8008000U) /**< \brief (TC0       ) Base Address */
#define TC1        (0xF800C000U) /**< \brief (TC1       ) Base Address */
#define FLEXCOM6   (0xF8010000U) /**< \brief (FLEXCOM6  ) Base Address */
#define FLEXCOM7   (0xF8014000U) /**< \brief (FLEXCOM7  ) Base Address */
#define FLEXCOM8   (0xF8018000U) /**< \brief (FLEXCOM8  ) Base Address */
#define FLEXCOM0   (0xF801C000U) /**< \brief (FLEXCOM0  ) Base Address */
#define FLEXCOM1   (0xF8020000U) /**< \brief (FLEXCOM1  ) Base Address */
#define FLEXCOM2   (0xF8024000U) /**< \brief (FLEXCOM2  ) Base Address */
#define FLEXCOM3   (0xF8028000U) /**< \brief (FLEXCOM3  ) Base Address */
#define EMAC0      (0xF802C000U) /**< \brief (EMAC0     ) Base Address */
#define EMAC1      (0xF8030000U) /**< \brief (EMAC1     ) Base Address */
#define PWM        (0xF8034000U) /**< \brief (PWM       ) Base Address */
#define LCDC       (0xF8038000U) /**< \brief (LCDC      ) Base Address */
#define UDPHS      (0xF803C000U) /**< \brief (UDPHS     ) Base Address */
#define FLEXCOM9   (0xF8040000U) /**< \brief (FLEXCOM9  ) Base Address */
#define FLEXCOM10  (0xF8044000U) /**< \brief (FLEXCOM10 ) Base Address */
#define ISI        (0xF8048000U) /**< \brief (ISI       ) Base Address */
#define ADC        (0xF804C000U) /**< \brief (ADC       ) Base Address */
#define SFR        (0xF8050000U) /**< \brief (SFR       ) Base Address */
#define MATRIX     (0xFFFFDE00U) /**< \brief (MATRIX    ) Base Address */
#define PMECC      (0xFFFFE000U) /**< \brief (PMECC     ) Base Address */
#define PMERRLOC   (0xFFFFE600U) /**< \brief (PMERRLOC  ) Base Address */
#define MPDDRC     (0xFFFFE800U) /**< \brief (MPDDRC    ) Base Address */
#define SMC        (0xFFFFEA00U) /**< \brief (SMC       ) Base Address */
#define SDRAMC     (0xFFFFEC00U) /**< \brief (SDRAMC    ) Base Address */
#define AIC        (0xFFFFF100U) /**< \brief (AIC       ) Base Address */
#define DBGU       (0xFFFFF200U) /**< \brief (DBGU      ) Base Address */
#define PIOA       (0xFFFFF400U) /**< \brief (PIOA      ) Base Address */
#define PIOB       (0xFFFFF600U) /**< \brief (PIOB      ) Base Address */
#define PIOC       (0xFFFFF800U) /**< \brief (PIOC      ) Base Address */
#define PIOD       (0xFFFFFA00U) /**< \brief (PIOD      ) Base Address */
#define PMC        (0xFFFFFC00U) /**< \brief (PMC       ) Base Address */
#define RSTC       (0xFFFFFE00U) /**< \brief (RSTC      ) Base Address */
#define SHDWC      (0xFFFFFE10U) /**< \brief (SHDWC     ) Base Address */
#define RTT        (0xFFFFFE20U) /**< \brief (RTT       ) Base Address */
#define PIT        (0xFFFFFE40U) /**< \brief (PIT       ) Base Address */
#define SCKC       (0xFFFFFE50U) /**< \brief (SCKC      ) Base Address */
#define BSC        (0xFFFFFE54U) /**< \brief (BSC       ) Base Address */
#define GPBR       (0xFFFFFE60U) /**< \brief (GPBR      ) Base Address */
#define RTC        (0xFFFFFEA8U) /**< \brief (RTC       ) Base Address */
#define SYSCWP     (0xFFFFFEDCU) /**< \brief (SYSCWP    ) Base Address */
#define WDT        (0xFFFFFF80U) /**< \brief (WDT       ) Base Address */
#else
#define UHPHS_OHCI ((Uhpfs      *)0x00600000U) /**< \brief (UHPHS_OHCI) Base Address */
#define UHPHS_EHCI ((Uhphs      *)0x00700000U) /**< \brief (UHPHS_EHCI) Base Address */
#define SDMMC0     ((Sdmmc      *)0x80000000U) /**< \brief (SDMMC0    ) Base Address */
#define SDMMC1     ((Sdmmc      *)0x90000000U) /**< \brief (SDMMC1    ) Base Address */
#define OTPC       ((Otpc       *)0xEFF00000U) /**< \brief (OTPC      ) Base Address */
#define FLEXCOM4   ((Flexcom    *)0xF0000000U) /**< \brief (FLEXCOM4  ) Base Address */
#define FLEXCOM5   ((Flexcom    *)0xF0004000U) /**< \brief (FLEXCOM5  ) Base Address */
#define XDMAC      ((Xdmac      *)0xF0008000U) /**< \brief (XDMAC     ) Base Address */
#define SSC        ((Ssc        *)0xF0010000U) /**< \brief (SSC       ) Base Address */
#define QSPI       ((Qspi       *)0xF0014000U) /**< \brief (QSPI      ) Base Address */
#define GFX2D      ((Gfx2d      *)0xF0018000U) /**< \brief (GFX2D     ) Base Address */
#define I2SMCC     ((I2smcc     *)0xF001C000U) /**< \brief (I2SMCC    ) Base Address */
#define FLEXCOM11  ((Flexcom    *)0xF0020000U) /**< \brief (FLEXCOM11 ) Base Address */
#define FLEXCOM12  ((Flexcom    *)0xF0024000U) /**< \brief (FLEXCOM12 ) Base Address */
#define PIT64B     ((Pit64b     *)0xF0028000U) /**< \brief (PIT64B    ) Base Address */
#define SHA        ((Sha        *)0xF002C000U) /**< \brief (SHA       ) Base Address */
#define TRNG       ((Trng       *)0xF0030000U) /**< \brief (TRNG      ) Base Address */
#define AES        ((Aes        *)0xF0034000U) /**< \brief (AES       ) Base Address */
#define TDES       ((Tdes       *)0xF0038000U) /**< \brief (TDES      ) Base Address */
#define CLASSD     ((Classd     *)0xF003C000U) /**< \brief (CLASSD    ) Base Address */
#define CAN0       ((Can        *)0xF8000000U) /**< \brief (CAN0      ) Base Address */
#define CAN1       ((Can        *)0xF8004000U) /**< \brief (CAN1      ) Base Address */
#define TC0        ((Tc         *)0xF8008000U) /**< \brief (TC0       ) Base Address */
#define TC1        ((Tc         *)0xF800C000U) /**< \brief (TC1       ) Base Address */
#define FLEXCOM6   ((Flexcom    *)0xF8010000U) /**< \brief (FLEXCOM6  ) Base Address */
#define FLEXCOM7   ((Flexcom    *)0xF8014000U) /**< \brief (FLEXCOM7  ) Base Address */
#define FLEXCOM8   ((Flexcom    *)0xF8018000U) /**< \brief (FLEXCOM8  ) Base Address */
#define FLEXCOM0   ((Flexcom    *)0xF801C000U) /**< \brief (FLEXCOM0  ) Base Address */
#define FLEXCOM1   ((Flexcom    *)0xF8020000U) /**< \brief (FLEXCOM1  ) Base Address */
#define FLEXCOM2   ((Flexcom    *)0xF8024000U) /**< \brief (FLEXCOM2  ) Base Address */
#define FLEXCOM3   ((Flexcom    *)0xF8028000U) /**< \brief (FLEXCOM3  ) Base Address */
#define EMAC0      ((Emac       *)0xF802C000U) /**< \brief (EMAC0     ) Base Address */
#define EMAC1      ((Emac       *)0xF8030000U) /**< \brief (EMAC1     ) Base Address */
#define PWM        ((Pwm        *)0xF8034000U) /**< \brief (PWM       ) Base Address */
#define LCDC       ((Lcdc       *)0xF8038000U) /**< \brief (LCDC      ) Base Address */
#define UDPHS      ((Udphs      *)0xF803C000U) /**< \brief (UDPHS     ) Base Address */
#define FLEXCOM9   ((Flexcom    *)0xF8040000U) /**< \brief (FLEXCOM9  ) Base Address */
#define FLEXCOM10  ((Flexcom    *)0xF8044000U) /**< \brief (FLEXCOM10 ) Base Address */
#define ISI        ((Isi        *)0xF8048000U) /**< \brief (ISI       ) Base Address */
#define ADC        ((Adc        *)0xF804C000U) /**< \brief (ADC       ) Base Address */
#define SFR        ((Sfr        *)0xF8050000U) /**< \brief (SFR       ) Base Address */
#define MATRIX     ((Matrix     *)0xFFFFDE00U) /**< \brief (MATRIX    ) Base Address */
#define PMECC      ((Pmecc      *)0xFFFFE000U) /**< \brief (PMECC     ) Base Address */
#define PMERRLOC   ((Pmerrloc   *)0xFFFFE600U) /**< \brief (PMERRLOC  ) Base Address */
#define MPDDRC     ((Mpddrc     *)0xFFFFE800U) /**< \brief (MPDDRC    ) Base Address */
#define SMC        ((Smc        *)0xFFFFEA00U) /**< \brief (SMC       ) Base Address */
#define SDRAMC     ((Sdramc     *)0xFFFFEC00U) /**< \brief (SDRAMC    ) Base Address */
#define AIC        ((Aic        *)0xFFFFF100U) /**< \brief (AIC       ) Base Address */
#define DBGU       ((Dbgu       *)0xFFFFF200U) /**< \brief (DBGU      ) Base Address */
#define PIOA       ((Pio        *)0xFFFFF400U) /**< \brief (PIOA      ) Base Address */
#define PIOB       ((Pio        *)0xFFFFF600U) /**< \brief (PIOB      ) Base Address */
#define PIOC       ((Pio        *)0xFFFFF800U) /**< \brief (PIOC      ) Base Address */
#define PIOD       ((Pio        *)0xFFFFFA00U) /**< \brief (PIOD      ) Base Address */
#define PMC        ((Pmc        *)0xFFFFFC00U) /**< \brief (PMC       ) Base Address */
#define RSTC       ((Rstc       *)0xFFFFFE00U) /**< \brief (RSTC      ) Base Address */
#define SHDWC      ((Shdwc      *)0xFFFFFE10U) /**< \brief (SHDWC     ) Base Address */
#define RTT        ((Rtt        *)0xFFFFFE20U) /**< \brief (RTT       ) Base Address */
#define PIT        ((Pit        *)0xFFFFFE40U) /**< \brief (PIT       ) Base Address */
#define SCKC       ((Sckc       *)0xFFFFFE50U) /**< \brief (SCKC      ) Base Address */
#define BSC        ((Bsc        *)0xFFFFFE54U) /**< \brief (BSC       ) Base Address */
#define GPBR       ((Gpbr       *)0xFFFFFE60U) /**< \brief (GPBR      ) Base Address */
#define RTC        ((Rtc        *)0xFFFFFEA8U) /**< \brief (RTC       ) Base Address */
#define SYSCWP     ((Syscwp     *)0xFFFFFEDCU) /**< \brief (SYSCWP    ) Base Address */
#define WDT        ((Wdt        *)0xFFFFFF80U) /**< \brief (WDT       ) Base Address */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */
/** \addtogroup SAM9X60_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/sam9x60.h"
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */


#define EBI_CS0_ADDR   (0x10000000u) /**< EBI Chip Select 0 base address */
#define EBI_CS2_ADDR   (0x30000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR   (0x40000000u) /**< EBI Chip Select 3 base address */
#define EBI_NF_ADDR    (0x40000000u) /**< NAND Flash on EBI Chip Select 3 base address */
#define EBI_CS4_ADDR   (0x50000000u) /**< EBI Chip Select 4 base address */
#define EBI_CS5_ADDR   (0x60000000u) /**< EBI Chip Select 5 base address */
#define QSPIMEM_ADDR   (0x70000000u) /**< QSPI Memory base address */
#define SDMMC0_ADDR    (0x80000000u) /**< SDMMC 0 base address */
#define SDMMC1_ADDR    (0x90000000u) /**< SDMMC 1 base address */
#define ECC_ROM_ADDR   (0x00100000u) /**< ECC ROM base address */
#define IRAM0_ADDR     (0x00300000u) /**< Internal RAM 0 base address */
#define IRAM1_ADDR     (0x00400000u) /**< Internal RAM 1 base address */
#define UDPHS_RAM_ADDR (0x00500000u) /**< USB High Speed Device Port RAM base address */

/* ************************************************************************** */
/*   MISCELLANEOUS DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */

#define CHIP_JTAGID (0x05B4403FUL)
#define CHIP_CIDR   (0x819B81A0UL)
#define CHIP_EXID   (0x00000002UL)

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAM9X60 */
/* ************************************************************************** */

/* %ATMEL_ELECTRICAL% */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAM9X60_ */
