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

#ifndef _SAMA5D21_
#define _SAMA5D21_

/** \addtogroup SAMA5D21_definitions SAMA5D21 definitions
  This file defines all structures and symbols for SAMA5D21:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

/*------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#endif

typedef enum IRQn
{
  PIT_IRQn             =  3, /**<  3 SAMA5D21 Periodic Interval Timer Interrupt (PIT) */
  WDT_IRQn             =  4, /**<  4 SAMA5D21 Watchdog timer Interrupt (WDT) */
  GMAC_IRQn            =  5, /**<  5 SAMA5D21 Ethernet MAC (GMAC) */
  XDMAC0_IRQn          =  6, /**<  6 SAMA5D21 DMA Controller 0 (XDMAC0) */
  XDMAC1_IRQn          =  7, /**<  7 SAMA5D21 DMA Controller 1 (XDMAC1) */
  ICM_IRQn             =  8, /**<  8 SAMA5D21 Integritry Check Monitor (ICM) */
  AES_IRQn             =  9, /**<  9 SAMA5D21 Advanced Enion Standard (AES) */
  AESB_IRQn            = 10, /**< 10 SAMA5D21 AES bridge (AESB) */
  TDES_IRQn            = 11, /**< 11 SAMA5D21 Triple Data Enion Standard (TDES) */
  SHA_IRQn             = 12, /**< 12 SAMA5D21 SHA Signature (SHA) */
  MPDDRC_IRQn          = 13, /**< 13 SAMA5D21 MPDDR controller (MPDDRC) */
  MATRIX1_IRQn         = 14, /**< 14 SAMA5D21 H32MX, 32-bit AHB Matrix (MATRIX1) */
  MATRIX0_IRQn         = 15, /**< 15 SAMA5D21 H64MX, 64-bit AHB Matrix (MATRIX0) */
  HSMC_IRQn            = 17, /**< 17 SAMA5D21 Multi-bit ECC Interrupt (HSMC) */
  PIOA_IRQn            = 18, /**< 18 SAMA5D21 Parallel I/O Controller (PIOA) */
  FLEXCOM0_IRQn        = 19, /**< 19 SAMA5D21 FLEXCOM 0 (FLEXCOM0) */
  FLEXCOM1_IRQn        = 20, /**< 20 SAMA5D21 FLEXCOM 1 (FLEXCOM1) */
  FLEXCOM3_IRQn        = 22, /**< 22 SAMA5D21 FLEXCOM 3 (FLEXCOM3) */
  FLEXCOM4_IRQn        = 23, /**< 23 SAMA5D21 FLEXCOM 4 (FLEXCOM4) */
  UART0_IRQn           = 24, /**< 24 SAMA5D21 UART 0 (UART0) */
  UART1_IRQn           = 25, /**< 25 SAMA5D21 UART 1 (UART1) */
  UART2_IRQn           = 26, /**< 26 SAMA5D21 UART 2 (UART2) */
  UART3_IRQn           = 27, /**< 27 SAMA5D21 UART 3 (UART3) */
  UART4_IRQn           = 28, /**< 28 SAMA5D21 UART 4 (UART4) */
  TWIHS0_IRQn          = 29, /**< 29 SAMA5D21 Two-Wire Interface 0 (TWIHS0) */
  TWIHS1_IRQn          = 30, /**< 30 SAMA5D21 Two-Wire Interface 1 (TWIHS1) */
  SPI0_IRQn            = 33, /**< 33 SAMA5D21 Serial Peripheral Interface 0 (SPI0) */
  SPI1_IRQn            = 34, /**< 34 SAMA5D21 Serial Peripheral Interface 1 (SPI1) */
  TC0_IRQn             = 35, /**< 35 SAMA5D21 Timer Counter 0 (ch. 0, 1, 2) (TC0) */
  TC1_IRQn             = 36, /**< 36 SAMA5D21 Timer Counter 1 (ch. 3, 4, 5) (TC1) */
  PWM_IRQn             = 38, /**< 38 SAMA5D21 Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
  ADC_IRQn             = 40, /**< 40 SAMA5D21 Touch Screen ADC Controller (ADC) */
  UHPHS_IRQn           = 41, /**< 41 SAMA5D21 USB Host High Speed (UHPHS) */
  UDPHS_IRQn           = 42, /**< 42 SAMA5D21 USB Device High Speed (UDPHS) */
  SSC0_IRQn            = 43, /**< 43 SAMA5D21 Synchronous Serial Controller 0 (SSC0) */
  SSC1_IRQn            = 44, /**< 44 SAMA5D21 Synchronous Serial Controller 1 (SSC1) */
  LCDC_IRQn            = 45, /**< 45 SAMA5D21 LCD Controller (LCDC) */
  ISC_IRQn             = 46, /**< 46 SAMA5D21 Camera Interface (ISC) */
  TRNG_IRQn            = 47, /**< 47 SAMA5D21 True Random Number Generator (TRNG) */
  PDMIC_IRQn           = 48, /**< 48 SAMA5D21 Pulse Density Modulation Interface Controller (PDMIC) */
  SFC_IRQn             = 50, /**< 50 SAMA5D21 Fuse Controller (SFC) */
  QSPI0_IRQn           = 52, /**< 52 SAMA5D21 QSPI 0 (QSPI0) */
  QSPI1_IRQn           = 53, /**< 53 SAMA5D21 QSPI 1 (QSPI1) */
  I2SC0_IRQn           = 54, /**< 54 SAMA5D21 Inter-IC Sound Controller 0 (I2SC0) */
  I2SC1_IRQn           = 55, /**< 55 SAMA5D21 Inter-IC Sound Controller 1 (I2SC1) */
  CLASSD_IRQn          = 59, /**< 59 SAMA5D21 Audio Class D amplifier (CLASSD) */
  SFR_IRQn             = 60, /**< 60 SAMA5D21 Special Function Register  (SFR) */
  SAIC_IRQn            = 61, /**< 61 SAMA5D21 Secured Advanced Interrupt Controller  (SAIC) */
  AIC_IRQn             = 62, /**< 62 SAMA5D21 Advanced Interrupt Controller  (AIC) */
  L2CC_IRQn            = 63, /**< 63 SAMA5D21 L2 Cache Controller (L2CC) */
  PIOB_IRQn            = 68, /**< 68 SAMA5D21  (PIOB) */
  PIOC_IRQn            = 69, /**< 69 SAMA5D21  (PIOC) */
  PIOD_IRQn            = 70, /**< 70 SAMA5D21  (PIOD) */
  ACC_IRQn             = 75, /**< 75 SAMA5D21 Analog Comparator (ACC) */
  RXLP_IRQn            = 76, /**< 76 SAMA5D21 Uart Low Power (RXLP) */
  CHIPID_IRQn          = 78, /**< 78 SAMA5D21 Chip ID (CHIPID) */

  PERIPH_COUNT_IRQn    = 79  /**< Number of peripheral IDs */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMA5D21 */
/* ************************************************************************** */
/** \addtogroup SAMA5D21_api Peripheral Software API */
/*@{*/

#include "component/component_acc.h"
#include "component/component_adc.h"
#include "component/component_aes.h"
#include "component/component_aesb.h"
#include "component/component_aic.h"
#include "component/component_aximx.h"
#include "component/component_chipid.h"
#include "component/component_classd.h"
#include "component/component_flexcom.h"
#include "component/component_gmac.h"
#include "component/component_i2sc.h"
#include "component/component_icm.h"
#include "component/component_isc.h"
#include "component/component_l2cc.h"
#include "component/component_lcdc.h"
#include "component/component_matrix.h"
#include "component/component_mpddrc.h"
#include "component/component_pdmic.h"
#include "component/component_pio.h"
#include "component/component_pit.h"
#include "component/component_pmc.h"
#include "component/component_pwm.h"
#include "component/component_qspi.h"
#include "component/component_rstc.h"
#include "component/component_rtc.h"
#include "component/component_rxlp.h"
#include "component/component_sckc.h"
#include "component/component_sfc.h"
#include "component/component_sha.h"
#include "component/component_shdwc.h"
#include "component/component_smc.h"
//#include "component/component_spi.h"
#include "component/component_ssc.h"
#include "component/component_tc.h"
#include "component/component_tdes.h"
#include "component/component_trng.h"
#include "component/component_twihs.h"
#include "component/component_uart.h"
#include "component/component_udphs.h"
#include "component/component_wdt.h"
#include "component/component_xdmac.h"
/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */
/** \addtogroup SAMA5D21_reg Registers Access Definitions */
/*@{*/

#include "instance/instance_aximx.h"
#include "instance/instance_l2cc.h"
#include "instance/instance_lcdc.h"
#include "instance/instance_xdmac1.h"
#include "instance/instance_isc.h"
#include "instance/instance_mpddrc.h"
#include "instance/instance_xdmac0.h"
#include "instance/instance_pmc.h"
#include "instance/instance_matrix0.h"
#include "instance/instance_aesb.h"
#include "instance/instance_qspi0.h"
#include "instance/instance_qspi1.h"
#include "instance/instance_sha.h"
#include "instance/instance_aes.h"
#include "instance/instance_spi0.h"
#include "instance/instance_ssc0.h"
#include "instance/instance_gmac.h"
#include "instance/instance_tc0.h"
#include "instance/instance_tc1.h"
#include "instance/instance_hsmc.h"
#include "instance/instance_pdmic.h"
#include "instance/instance_uart0.h"
#include "instance/instance_uart1.h"
#include "instance/instance_uart2.h"
#include "instance/instance_twihs0.h"
#include "instance/instance_pwm.h"
#include "instance/instance_sfr.h"
#include "instance/instance_flexcom0.h"
#include "instance/instance_flexcom1.h"
#include "instance/instance_saic.h"
#include "instance/instance_icm.h"
#include "instance/instance_rstc.h"
#include "instance/instance_shdwc.h"
#include "instance/instance_pit.h"
#include "instance/instance_wdt.h"
#include "instance/instance_sckc.h"
#include "instance/instance_rtc.h"
#include "instance/instance_rxlp.h"
#include "instance/instance_acc.h"
#include "instance/instance_sfc.h"
#include "instance/instance_i2sc0.h"
#include "instance/instance_spi1.h"
#include "instance/instance_ssc1.h"
#include "instance/instance_uart3.h"
#include "instance/instance_uart4.h"
#include "instance/instance_flexcom3.h"
#include "instance/instance_flexcom4.h"
#include "instance/instance_trng.h"
#include "instance/instance_aic.h"
#include "instance/instance_twihs1.h"
#include "instance/instance_udphs.h"
#include "instance/instance_adc.h"
#include "instance/instance_pioa.h"
#include "instance/instance_matrix1.h"
#include "instance/instance_tdes.h"
#include "instance/instance_classd.h"
#include "instance/instance_i2sc1.h"
#include "instance/instance_chipid.h"
/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */
/** \addtogroup SAMA5D21_id Peripheral Ids Definitions */
/*@{*/

#define ID_SAIC_FIQ       ( 0) /**< \brief FIQ Interrupt ID (SAIC_FIQ) */
#define ID_PMC            ( 1) /**< \brief System Controller Interrupt (PMC) */
#define ID_ARM_PMU        ( 2) /**< \brief Performance Monitor Unit (PMU) (ARM_PMU) */
#define ID_PIT            ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT            ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_GMAC           ( 5) /**< \brief Ethernet MAC (GMAC) */
#define ID_XDMAC0         ( 6) /**< \brief DMA Controller 0 (XDMAC0) */
#define ID_XDMAC1         ( 7) /**< \brief DMA Controller 1 (XDMAC1) */
#define ID_ICM            ( 8) /**< \brief Integritry Check Monitor (ICM) */
#define ID_AES            ( 9) /**< \brief Advanced Enion Standard (AES) */
// #define ID_AESB           (10) /**< \brief AES bridge (AESB) */
#define ID_TDES           (11) /**< \brief Triple Data Enion Standard (TDES) */
#define ID_SHA            (12) /**< \brief SHA Signature (SHA) */
#define ID_MPDDRC         (13) /**< \brief MPDDR controller (MPDDRC) */
#define ID_MATRIX1        (14) /**< \brief H32MX, 32-bit AHB Matrix (MATRIX1) */
#define ID_MATRIX0        (15) /**< \brief H64MX, 64-bit AHB Matrix (MATRIX0) */
#define ID_HSMC           (17) /**< \brief Multi-bit ECC Interrupt (HSMC) */
#define ID_PIOA           (18) /**< \brief Parallel I/O Controller (PIOA) */

#define ID_FLEXCOM0       (19) /**< \brief FLEXCOM 0 (FLEXCOM0) */
#define ID_USART0         (19) /**< \brief USART (USART0) from FLEXCOM0 */
#define ID_FCOMSPI0       (19) /**< \brief Serial Peripheral Interface (SPI0) from FLEXCOM0 */
#define ID_TWI0           (19) /**< \brief Two-Wire Interface (TWI0) from FLEXCOM0 */
#define ID_FLEXCOM1       (20) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_USART1         (20) /**< \brief USART (USART1) from FLEXCOM1 */
#define ID_FCOMSPI1       (20) /**< \brief Serial Peripheral Interface (SPI1) from FLEXCOM1 */
#define ID_TWI1           (20) /**< \brief Two-Wire Interface (TWI1) from FLEXCOM1 */
#define ID_FLEXCOM2       (21) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_USART2         (21) /**< \brief USART (USART1) from FLEXCOM1 */
#define ID_FCOMSPI2       (21) /**< \brief Serial Peripheral Interface (SPI1) from FLEXCOM1 */
#define ID_TWI2           (21) /**< \brief Two-Wire Interface (TWI1) from FLEXCOM1 */
#define ID_FLEXCOM3       (22) /**< \brief FLEXCOM 3 (FLEXCOM3) */
#define ID_USART3         (22) /**< \brief USART (USART3) from FLEXCOM3 */
#define ID_FCOMSPI3       (22) /**< \brief Serial Peripheral Interface (SPI3) from FLEXCOM3 */
#define ID_TWI3           (22) /**< \brief Two-Wire Interface (TWI3) from FLEXCOM3 */
#define ID_FLEXCOM4       (23) /**< \brief FLEXCOM 4 (FLEXCOM4) */
#define ID_USART4         (23) /**< \brief USART (USART4) from FLEXCOM4 */
#define ID_FCOMSPI4       (23) /**< \brief Serial Peripheral Interface (SPI4) from FLEXCOM4 */
#define ID_TWI4           (23) /**< \brief Two-Wire Interface (TWI4) from FLEXCOM4 */

#define ID_UART0          (24) /**< \brief UART 0 (UART0) */
#define ID_UART1          (25) /**< \brief UART 1 (UART1) */
#define ID_UART2          (26) /**< \brief UART 2 (UART2) */
#define ID_UART3          (27) /**< \brief UART 3 (UART3) */
#define ID_UART4          (28) /**< \brief UART 4 (UART4) */
#define ID_TWIHS0         (29) /**< \brief Two-Wire Interface 0 (TWIHS0) */
#define ID_TWIHS1         (30) /**< \brief Two-Wire Interface 1 (TWIHS1) */

#define ID_SDHC0       (31) /**< \brief Ultra High Speed SD Host Controller 0 (SDHC0) */
// #define ID_SDHC1       (32) /**< \brief Ultra High Speed SD Host Controller 1 (SDHC1) */

#define ID_SPI0           (33) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1           (34) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_TC0            (35) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1            (36) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_PWM            (38) /**< \brief Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
#define ID_ADC            (40) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_UHPHS          (41) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS          (42) /**< \brief USB Device High Speed (UDPHS) */
#define ID_SSC0           (43) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1           (44) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_LCDC           (45) /**< \brief LCD Controller (LCDC) */
#define ID_ISC            (46) /**< \brief Camera Interface (ISC) */
#define ID_TRNG           (47) /**< \brief True Random Number Generator (TRNG) */
#define ID_PDMIC          (48) /**< \brief Pulse Density Modulation Interface Controller (PDMIC) */

#define ID_AIC_IRQ        (49) /**< \brief IRQ Interrupt ID (AIC_IRQ) */

#define ID_SFC            (50) /**< \brief Fuse Controller (SFC) */
#define ID_SECURAM        (51) /**< \brief Secured RAM (SECURAM) */
#define ID_QSPI0          (52) /**< \brief QSPI 0 (QSPI0) */
#define ID_QSPI1          (53) /**< \brief QSPI 1 (QSPI1) */
#define ID_I2SC0          (54) /**< \brief Inter-IC Sound Controller 0 (I2SC0) */
#define ID_I2SC1          (55) /**< \brief Inter-IC Sound Controller 1 (I2SC1) */
#define ID_CLASSD         (59) /**< \brief Audio Class D amplifier (CLASSD) */
#define ID_SFR            (60) /**< \brief Special Function Register  (SFR) */
#define ID_SAIC           (61) /**< \brief Secured Advanced Interrupt Controller  (SAIC) */
#define ID_AIC            (62) /**< \brief Advanced Interrupt Controller  (AIC) */
#define ID_L2CC           (63) /**< \brief L2 Cache Controller (L2CC) */

// #define ID_CAN0_INT1      (64) /**< \brief MCAN 0 Interrupt1 (CAN0_INT1) */
// #define ID_CAN1_INT1      (65) /**< \brief MCAN 1 Interrupt1 (CAN1_INT1) */

#define ID_GMAC_Q1        (66) /**< \brief GMAC Queue 1 Interrupt (GMAC_Q1) */
#define ID_GMAC_Q2        (67) /**< \brief GMAC Queue 2 Interrupt (GMAC_Q2) */

#define ID_PIOB           (68) /**< \brief  (PIOB) */
#define ID_PIOC           (69) /**< \brief  (PIOC) */
#define ID_PIOD           (70) /**< \brief  (PIOD) */
#define ID_SDHC0_TIMER    (71) /**< \brief  (SDHC0_TIMER) */
#define ID_RSTC           (73) /**< \brief System Controller Interrupt (RSTC) */
#define ID_RTC            (74) /**< \brief System Controller Interrupt (RTC) */
#define ID_ACC            (75) /**< \brief Analog Comparator (ACC) */
#define ID_RXLP           (76) /**< \brief Uart Low Power (RXLP) */
#define ID_CHIPID         (78) /**< \brief Chip ID (CHIPID) */

#define ID_PERIPH_COUNT   (79) /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/*   CONFIGURATION ID H64 MATRIX FOR SAMA5D21 */
/* ************************************************************************** */

const uint8_t _id_h64_matrix[] = {
	ID_XDMAC0,
	ID_XDMAC1,
	ID_AES,
	//ID_AESB,
	ID_SHA,
	ID_MPDDRC,
	ID_MATRIX0,
	ID_SDHC0,
	//ID_SDHC1,
	ID_LCDC,
	ID_ISC,
	ID_QSPI0,
	ID_QSPI1,
	ID_L2CC,
} ;

#define ID_H64_MATRIX_SIZE 	sizeof(_id_h64_matrix)


/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */
/** \addtogroup SAMA5D21_base Peripheral Base Address Definitions */
/*@{*/

#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define AXIMX    (0x00600000U) /**< \brief (AXIMX   ) Base Address */
#define L2CC     (0x00A00000U) /**< \brief (L2CC    ) Base Address */
#define LCDC     (0xF0000000U) /**< \brief (LCDC    ) Base Address */
#define XDMAC1   (0xF0004000U) /**< \brief (XDMAC1  ) Base Address */
#define ISC      (0xF0008000U) /**< \brief (ISC     ) Base Address */
#define MPDDRC   (0xF000C000U) /**< \brief (MPDDRC  ) Base Address */
#define XDMAC0   (0xF0010000U) /**< \brief (XDMAC0  ) Base Address */
#define PMC      (0xF0014000U) /**< \brief (PMC     ) Base Address */
#define MATRIX0  (0xF0018000U) /**< \brief (MATRIX0 ) Base Address */
#define AESB     (0xF001C000U) /**< \brief (AESB    ) Base Address */
#define QSPI0    (0xF0020000U) /**< \brief (QSPI0   ) Base Address */
#define QSPI1    (0xF0024000U) /**< \brief (QSPI1   ) Base Address */
#define SHA      (0xF0028000U) /**< \brief (SHA     ) Base Address */
#define AES      (0xF002C000U) /**< \brief (AES     ) Base Address */
#define SPI0     (0xF8000000U) /**< \brief (SPI0    ) Base Address */
#define SSC0     (0xF8004000U) /**< \brief (SSC0    ) Base Address */
#define GMAC     (0xF8008000U) /**< \brief (GMAC    ) Base Address */
#define TC0      (0xF800C000U) /**< \brief (TC0     ) Base Address */
#define TC1      (0xF8010000U) /**< \brief (TC1     ) Base Address */
#define HSMC     (0xF8014000U) /**< \brief (HSMC    ) Base Address */
#define PDMIC    (0xF8018000U) /**< \brief (PDMIC   ) Base Address */
#define UART0    (0xF801C000U) /**< \brief (UART0   ) Base Address */
#define UART1    (0xF8020000U) /**< \brief (UART1   ) Base Address */
#define UART2    (0xF8024000U) /**< \brief (UART2   ) Base Address */
#define TWIHS0   (0xF8028000U) /**< \brief (TWIHS0  ) Base Address */
#define PWM      (0xF802C000U) /**< \brief (PWM     ) Base Address */
#define SFR      (0xF8030000U) /**< \brief (SFR     ) Base Address */
#define FLEXCOM0 (0xF8034000U) /**< \brief (FLEXCOM0) Base Address */
#define USART0   (0xF8034200U) /**< \brief (FLEXCOM0_USART) Base Address */
#define FCOMSPI0 (0xF8034400U) /**< \brief (FLEXCOM0_SPI) Base Address */
#define TWI0     (0xF8034600U) /**< \brief (FLEXCOM0_TWI) Base Address */
#define FLEXCOM1 (0xF8038000U) /**< \brief (FLEXCOM1) Base Address */
#define USART1   (0xF8038200U) /**< \brief (FLEXCOM1_USART) Base Address */
#define FCOMSPI1 (0xF8038400U) /**< \brief (FLEXCOM1_SPI) Base Address */
#define TWI1     (0xF8038600U) /**< \brief (FLEXCOM1_TWI) Base Address */
#define SAIC     (0xF803C000U) /**< \brief (SAIC    ) Base Address */
#define ICM      (0xF8040000U) /**< \brief (ICM     ) Base Address */
#define RSTC     (0xF8048000U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    (0xF8048010U) /**< \brief (SHDWC   ) Base Address */
#define PIT      (0xF8048030U) /**< \brief (PIT     ) Base Address */
#define WDT      (0xF8048040U) /**< \brief (WDT     ) Base Address */
#define SCKC     (0xF8048050U) /**< \brief (SCKC    ) Base Address */
#define RTC      (0xF80480B0U) /**< \brief (RTC     ) Base Address */
#define RXLP     (0xF8049000U) /**< \brief (RXLP    ) Base Address */
#define ACC      (0xF804A000U) /**< \brief (ACC     ) Base Address */
#define SFC      (0xF804C000U) /**< \brief (SFC     ) Base Address */
#define I2SC0    (0xF8050000U) /**< \brief (I2SC0   ) Base Address */
#define SPI1     (0xFC000000U) /**< \brief (SPI1    ) Base Address */
#define SSC1     (0xFC004000U) /**< \brief (SSC1    ) Base Address */
#define UART3    (0xFC008000U) /**< \brief (UART3   ) Base Address */
#define UART4    (0xFC00C000U) /**< \brief (UART4   ) Base Address */
#define FLEXCOM3 (0xFC014000U) /**< \brief (FLEXCOM3) Base Address */
#define USART3   (0xFC014200U) /**< \brief (FLEXCOM3_USART) Base Address */
#define FCOMSPI3 (0xFC014400U) /**< \brief (FLEXCOM3_SPI) Base Address */
#define TWI3     (0xFC014600U) /**< \brief (FLEXCOM3_TWI) Base Address */
#define FLEXCOM4 (0xFC018000U) /**< \brief (FLEXCOM4) Base Address */
#define USART4   (0xFC018200U) /**< \brief (FLEXCOM3_USART) Base Address */
#define FCOMSPI4 (0xFC018400U) /**< \brief (FLEXCOM3_SPI) Base Address */
#define TWI4     (0xFC018600U) /**< \brief (FLEXCOM3_TWI) Base Address */
#define TRNG     (0xFC01C000U) /**< \brief (TRNG    ) Base Address */
#define AIC      (0xFC020000U) /**< \brief (AIC     ) Base Address */
#define TWIHS1   (0xFC028000U) /**< \brief (TWIHS1  ) Base Address */
#define UDPHS    (0xFC02C000U) /**< \brief (UDPHS   ) Base Address */
#define ADC      (0xFC030000U) /**< \brief (ADC     ) Base Address */
#define PIOA     (0xFC038000U) /**< \brief (PIOA    ) Base Address */
#define MATRIX1  (0xFC03C000U) /**< \brief (MATRIX1 ) Base Address */
#define TDES     (0xFC044000U) /**< \brief (TDES    ) Base Address */
#define CLASSD   (0xFC048000U) /**< \brief (CLASSD  ) Base Address */
#define I2SC1    (0xFC04C000U) /**< \brief (I2SC1   ) Base Address */
#define CHIPID   (0xFC069000U) /**< \brief (CHIPID  ) Base Address */
#else
#define AXIMX    ((Aximx    *)0x00600000U) /**< \brief (AXIMX   ) Base Address */
#define L2CC     ((L2cc     *)0x00A00000U) /**< \brief (L2CC    ) Base Address */
#define LCDC     ((Lcdc     *)0xF0000000U) /**< \brief (LCDC    ) Base Address */
#define XDMAC1   ((Xdmac    *)0xF0004000U) /**< \brief (XDMAC1  ) Base Address */
#define ISC      ((Isc      *)0xF0008000U) /**< \brief (ISC     ) Base Address */
#define MPDDRC   ((Mpddrc   *)0xF000C000U) /**< \brief (MPDDRC  ) Base Address */
#define XDMAC0   ((Xdmac    *)0xF0010000U) /**< \brief (XDMAC0  ) Base Address */
#define PMC      ((Pmc      *)0xF0014000U) /**< \brief (PMC     ) Base Address */
#define MATRIX0  ((Matrix   *)0xF0018000U) /**< \brief (MATRIX0 ) Base Address */
#define AESB     ((Aesb     *)0xF001C000U) /**< \brief (AESB    ) Base Address */
#define QSPI0    ((Qspi     *)0xF0020000U) /**< \brief (QSPI0   ) Base Address */
#define QSPI1    ((Qspi     *)0xF0024000U) /**< \brief (QSPI1   ) Base Address */
#define SHA      ((Sha      *)0xF0028000U) /**< \brief (SHA     ) Base Address */
#define AES      ((Aes      *)0xF002C000U) /**< \brief (AES     ) Base Address */
#define SPI0     ((Spi      *)0xF8000000U) /**< \brief (SPI0    ) Base Address */
#define SSC0     ((Ssc      *)0xF8004000U) /**< \brief (SSC0    ) Base Address */
#define GMAC     ((Gmac     *)0xF8008000U) /**< \brief (GMAC    ) Base Address */
#define TC0      ((Tc       *)0xF800C000U) /**< \brief (TC0     ) Base Address */
#define TC1      ((Tc       *)0xF8010000U) /**< \brief (TC1     ) Base Address */
#define HSMC     ((Smc      *)0xF8014000U) /**< \brief (HSMC    ) Base Address */
#define PDMIC    ((Pdmic    *)0xF8018000U) /**< \brief (PDMIC   ) Base Address */
#define UART0    ((Uart     *)0xF801C000U) /**< \brief (UART0   ) Base Address */
#define UART1    ((Uart     *)0xF8020000U) /**< \brief (UART1   ) Base Address */
#define UART2    ((Uart     *)0xF8024000U) /**< \brief (UART2   ) Base Address */
#define TWIHS0   ((Twihs    *)0xF8028000U) /**< \brief (TWIHS0  ) Base Address */
#define PWM      ((Pwm      *)0xF802C000U) /**< \brief (PWM     ) Base Address */
#define SFR      ((Sfr      *)0xF8030000U) /**< \brief (SFR     ) Base Address */
#define FLEXCOM0 ((Flexcom  *)0xF8034000U) /**< \brief (FLEXCOM0) Base Address */
#define USART0   ((Usart    *)0xF8034200U) /**< \brief (FLEXCOM0_USART) Base Address */
#define FCOMSPI0 ((Spi      *)0xF8034400U) /**< \brief (FLEXCOM0_SPI) Base Address */
#define TWI0     ((Twi      *)0xF8034600U) /**< \brief (FLEXCOM0_TWI) Base Address */
#define FLEXCOM1 ((Flexcom  *)0xF8038000U) /**< \brief (FLEXCOM1) Base Address */
#define USART1   ((Usart    *)0xF8038200U) /**< \brief (FLEXCOM1_USART) Base Address */
#define FCOMSPI1 ((Spi      *)0xF8038400U) /**< \brief (FLEXCOM1_SPI) Base Address */
#define TWI1     ((Twi      *)0xF8038600U) /**< \brief (FLEXCOM1_TWI) Base Address */
#define SAIC     ((Aic      *)0xF803C000U) /**< \brief (SAIC    ) Base Address */
#define ICM      ((Icm      *)0xF8040000U) /**< \brief (ICM     ) Base Address */
#define RSTC     ((Rstc     *)0xF8048000U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    ((Shdwc    *)0xF8048010U) /**< \brief (SHDWC   ) Base Address */
#define PIT      ((Pit      *)0xF8048030U) /**< \brief (PIT     ) Base Address */
#define WDT      ((Wdt      *)0xF8048040U) /**< \brief (WDT     ) Base Address */
#define SCKC     ((Sckc     *)0xF8048050U) /**< \brief (SCKC    ) Base Address */
#define RTC      ((Rtc      *)0xF80480B0U) /**< \brief (RTC     ) Base Address */
#define RXLP     ((Rxlp     *)0xF8049000U) /**< \brief (RXLP    ) Base Address */
#define ACC      ((Acc      *)0xF804A000U) /**< \brief (ACC     ) Base Address */
#define SFC      ((Sfc      *)0xF804C000U) /**< \brief (SFC     ) Base Address */
#define I2SC0    ((I2sc     *)0xF8050000U) /**< \brief (I2SC0   ) Base Address */
#define SPI1     ((Spi      *)0xFC000000U) /**< \brief (SPI1    ) Base Address */
#define SSC1     ((Ssc      *)0xFC004000U) /**< \brief (SSC1    ) Base Address */
#define UART3    ((Uart     *)0xFC008000U) /**< \brief (UART3   ) Base Address */
#define UART4    ((Uart     *)0xFC00C000U) /**< \brief (UART4   ) Base Address */
#define FLEXCOM3 ((Flexcom  *)0xFC014000U) /**< \brief (FLEXCOM3) Base Address */
#define USART3   ((Usart    *)0xFC014200U) /**< \brief (FLEXCOM3_USART) Base Address */
#define FCOMSPI3 ((Spi      *)0xFC014400U) /**< \brief (FLEXCOM3_SPI) Base Address */
#define TWI3     ((Twi      *)0xFC014600U) /**< \brief (FLEXCOM3_TWI) Base Address */
#define FLEXCOM4 ((Flexcom  *)0xFC018000U) /**< \brief (FLEXCOM4) Base Address */
#define USART4   ((Usart    *)0xFC018200U) /**< \brief (FLEXCOM3_USART) Base Address */
#define FCOMSPI4 ((Spi      *)0xFC018400U) /**< \brief (FLEXCOM3_SPI) Base Address */
#define TWI4     ((Twi      *)0xFC018600U) /**< \brief (FLEXCOM3_TWI) Base Address */
#define TRNG     ((Trng     *)0xFC01C000U) /**< \brief (TRNG    ) Base Address */
#define AIC      ((Aic      *)0xFC020000U) /**< \brief (AIC     ) Base Address */
#define TWIHS1   ((Twihs    *)0xFC028000U) /**< \brief (TWIHS1  ) Base Address */
#define UDPHS    ((Udphs    *)0xFC02C000U) /**< \brief (UDPHS   ) Base Address */
#define ADC      ((Adc      *)0xFC030000U) /**< \brief (ADC     ) Base Address */
#define PIOA     ((Pio      *)0xFC038000U) /**< \brief (PIOA    ) Base Address */
#define MATRIX1  ((Matrix   *)0xFC03C000U) /**< \brief (MATRIX1 ) Base Address */
#define TDES     ((Tdes     *)0xFC044000U) /**< \brief (TDES    ) Base Address */
#define CLASSD   ((Classd   *)0xFC048000U) /**< \brief (CLASSD  ) Base Address */
#define I2SC1    ((I2sc     *)0xFC04C000U) /**< \brief (I2SC1   ) Base Address */
#define CHIPID   ((Chipid   *)0xFC069000U) /**< \brief (CHIPID  ) Base Address */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/*@}*/

/**
 * \brief retrieve TWI ID from its base address
 * \return TWI ID on success, ID_PERIPH_COUNT otherwise
 */
static inline uint32_t GET_TWI_ID_FROM_ADDR(const void* addr)
{
	if (addr == (void*)TWI0) return ID_FLEXCOM0; /**< \brief FLEXCOM 0 (FLEXCOM0) */
	else if (addr == (void*)TWI1) return ID_FLEXCOM1; /**< \brief FLEXCOM 1 (FLEXCOM1) */
	else if (addr == (void*)TWI3) return ID_FLEXCOM3; /**< \brief FLEXCOM 3 (FLEXCOM3) */
	else if (addr == (void*)TWI4) return ID_FLEXCOM4; /**< \brief FLEXCOM 4 (FLEXCOM4) */
	else return ID_PERIPH_COUNT;
}

/**
 * \brief retrieve TWI base address from its ID
 * \return TWI base address on success, 0 otherwise
 */
static inline void* GET_TWI_ADDR_FROM_ID(const uint32_t id)
{
	if (id == ID_FLEXCOM0) return TWI0; /**< \brief FLEXCOM 0 (FLEXCOM0) */
	else if (id == ID_FLEXCOM1) return TWI1; /**< \brief FLEXCOM 1 (FLEXCOM1) */
	else if (id == ID_FLEXCOM3) return TWI3; /**< \brief FLEXCOM 3 (FLEXCOM3) */
	else if (id == ID_FLEXCOM4) return TWI4; /**< \brief FLEXCOM 4 (FLEXCOM4) */
	else return (void*)0;
}

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */
/** \addtogroup SAMA5D21_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/pio_sama5d21.h"
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */


#define EBI_CS0_ADDR    (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR     (0x20000000u) /**< DDR Chip Select base address */
#define DDR_AES_CS_ADDR (0x40000000u) /**< DDR with AES Chip Select base address */
#define EBI_CS1_ADDR    (0x60000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR    (0x70000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR    (0x80000000u) /**< EBI Chip Select 3 base address */
#define QSPI_AES0_ADDR  (0x90000000u) /**< QPSI Memory crypted with AES 0 base address */
#define QSPI_AES1_ADDR  (0x98000000u) /**< QPSI Memory crypted with AES 1 base address */
#define SDMMC0_ADDR     (0xA0000000u) /**< SDMMC 0 base address */
#define SDMMC1_ADDR     (0xB0000000u) /**< SDMMC 1 base address */
#define NFC_ADDR        (0xC0000000u) /**< NAND Flash Controller Command base address */
#define QSPIMEM0_ADDR   (0xD0000000u) /**< QSPI Memory 0 base address */
#define QSPIMEM1_ADDR   (0xD8000000u) /**< QSPI Memory 1 base address */
#define IROM_ADDR       (0x00000000u) /**< Internal ROM base address */
#define ECC_ROM_ADDR    (0x00040000u) /**< ECC ROM base address */
#define NFC_RAM_ADDR    (0x00100000u) /**< NAND Flash Controller RAM base address */
#define IRAM0_ADDR      (0x00200000u) /**< Internal RAM 0 base address */
#define IRAM1_ADDR      (0x00220000u) /**< Internal RAM 1 base address */
#define UDPHS_RAM_ADDR  (0x00300000u) /**< USB High Speed Device Port RAM base address */
#define UHPHS_OHCI_ADDR (0x00400000u) /**< USB High Speed Device Port RAM base address */
#define UHPHS_EHCI_ADDR (0x00500000u) /**< USB High Speed Device Port RAM base address */
#define AXIMX_ADDR      (0x00600000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR        (0x00700000u) /**< Debug Access Port base address */
#define PTCMEM_ADDR     (0x00800000u) /**< PTC Memory base address */

/* ************************************************************************** */
/*   MISCELLANEOUS DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */

#define CHIP_JTAGID (0x05B3F03FUL)
#define CHIP_CIDR   (0x8A5C08C0UL)
#define CHIP_EXID   (0x00000002UL)

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAMA5D21 */
/* ************************************************************************** */

/* %ATMEL_ELECTRICAL% */

/* Device characteristics */
#define CHIP_FREQ_SLCK_RC_MIN           (20000UL)
#define CHIP_FREQ_SLCK_RC               (32000UL)
#define CHIP_FREQ_SLCK_RC_MAX           (44000UL)
#define CHIP_FREQ_MAINCK_RC_4MHZ        (4000000UL)
#define CHIP_FREQ_MAINCK_RC_8MHZ        (8000000UL)
#define CHIP_FREQ_MAINCK_RC_12MHZ       (12000000UL)
#define CHIP_FREQ_CPU_MAX               (120000000UL)
#define CHIP_FREQ_XTAL_32K              (32768UL)
#define CHIP_FREQ_XTAL_12M              (12000000UL)

/* Embedded Flash Read Wait State (VDDCORE set at 1.20V) */
#define CHIP_FREQ_FWS_0                 (20000000UL)  /**< \brief Maximum operating frequency when FWS is 0 */
#define CHIP_FREQ_FWS_1                 (40000000UL)  /**< \brief Maximum operating frequency when FWS is 1 */
#define CHIP_FREQ_FWS_2                 (60000000UL)  /**< \brief Maximum operating frequency when FWS is 2 */
#define CHIP_FREQ_FWS_3                 (80000000UL)  /**< \brief Maximum operating frequency when FWS is 3 */
#define CHIP_FREQ_FWS_4                 (100000000UL) /**< \brief Maximum operating frequency when FWS is 4 */
#define CHIP_FREQ_FWS_5                 (123000000UL) /**< \brief Maximum operating frequency when FWS is 5 */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMA5D21_ */
