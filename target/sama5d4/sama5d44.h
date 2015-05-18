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

#ifndef _SAMA5D44_
#define _SAMA5D44_

/** \addtogroup SAMA5D44_definitions SAMA5D44 definitions
  This file defines all structures and symbols for SAMA5D44:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include "resources/compiler_defines.h"

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#endif

typedef enum IRQn {
	ARM_IRQn = 2,	   /**<  2 SAMA5D44 Performance Monitor Unit (ARM) */
	PIT_IRQn = 3,	   /**<  3 SAMA5D44 Periodic Interval Timer Interrupt (PIT) */
	WDT_IRQn = 4,	   /**<  4 SAMA5D44 Watchdog timer Interrupt (WDT) */
	PIOD_IRQn = 5,	   /**<  5 SAMA5D44 Parallel I/O Controller D (PIOD) */
	USART0_IRQn = 6,   /**<  6 SAMA5D44 USART 0 (USART0) */
	USART1_IRQn = 7,   /**<  7 SAMA5D44 USART 1 (USART1) */
	XDMAC0_IRQn = 8,   /**<  8 SAMA5D44 DMA Controller 0 (XDMAC0) */
	ICM_IRQn = 9,	   /**<  9 SAMA5D44 Integritry Check Monitor (ICM) */
	AES_IRQn = 12,	   /**< 12 SAMA5D44 Advanced Encryption Standard (AES) */
	AESB_IRQn = 13,	   /**< 13 SAMA5D44 AES bridge (AESB) */
	TDES_IRQn = 14,	   /**< 14 SAMA5D44 Triple Data Encryption Standard (TDES) */
	SHA_IRQn = 15,	   /**< 15 SAMA5D44 SHA Signature (SHA) */
	MPDDRC_IRQn = 16,  /**< 16 SAMA5D44 MPDDR controller (MPDDRC) */
	MATRIX1_IRQn = 17, /**< 17 SAMA5D44 H32MX, 32-bit AHB Matrix (MATRIX1) */
	MATRIX0_IRQn = 18, /**< 18 SAMA5D44 H64MX, 64-bit AHB Matrix (MATRIX0) */
	VDEC_IRQn = 19,	   /**< 19 SAMA5D44 Video Decoder (VDEC) */
	HSMC_IRQn = 22,	   /**< 22 SAMA5D44 Multi-bit ECC Interrupt (HSMC) */
	PIOA_IRQn = 23,	   /**< 23 SAMA5D44 Parallel I/O Controller A (PIOA) */
	PIOB_IRQn = 24,	   /**< 24 SAMA5D44 Parallel I/O Controller B (PIOB) */
	PIOC_IRQn = 25,	   /**< 25 SAMA5D44 Parallel I/O Controller C (PIOC) */
	PIOE_IRQn = 26,	   /**< 26 SAMA5D44 Parallel I/O Controller E (PIOE) */
	UART0_IRQn = 27,   /**< 27 SAMA5D44 UART 0 (UART0) */
	UART1_IRQn = 28,   /**< 28 SAMA5D44 UART 1 (UART1) */
	USART2_IRQn = 29,  /**< 29 SAMA5D44 USART 2 (USART2) */
	USART3_IRQn = 30,  /**< 30 SAMA5D44 USART 3 (USART3) */
	USART4_IRQn = 31,  /**< 31 SAMA5D44 USART 4 (USART4) */
	TWI0_IRQn = 32,	   /**< 32 SAMA5D44 Two-Wire Interface 0 (TWI0) */
	TWI1_IRQn = 33,	   /**< 33 SAMA5D44 Two-Wire Interface 1 (TWI1) */
	TWI2_IRQn = 34,	   /**< 34 SAMA5D44 Two-Wire Interface 2 (TWI2) */
	HSMCI0_IRQn = 35,  /**< 35 SAMA5D44 High Speed Multimedia Card Interface 0 (HSMCI0) */
	HSMCI1_IRQn = 36,  /**< 36 SAMA5D44 High Speed Multimedia Card Interface 1 (HSMCI1) */
	SPI0_IRQn = 37,	   /**< 37 SAMA5D44 Serial Peripheral Interface 0 (SPI0) */
	SPI1_IRQn = 38,	   /**< 38 SAMA5D44 Serial Peripheral Interface 1 (SPI1) */
	SPI2_IRQn = 39,	   /**< 39 SAMA5D44 Serial Peripheral Interface 2 (SPI2) */
	TC0_IRQn = 40,	   /**< 40 SAMA5D44 Timer Counter 0 (ch. 0, 1, 2) (TC0) */
	TC1_IRQn = 41,	   /**< 41 SAMA5D44 Timer Counter 1 (ch. 3, 4, 5) (TC1) */
	TC2_IRQn = 42,	   /**< 42 SAMA5D44 Timer Counter 2 (ch. 6, 7, 8) (TC2) */
	PWM_IRQn = 43,	   /**< 43 SAMA5D44 Pulse Width Modulation Controller (PWM) */
	ADC_IRQn = 44,	   /**< 44 SAMA5D44 Touch Screen ADC Controller (ADC) */
	DBGU_IRQn = 45,	   /**< 45 SAMA5D44 Debug Unit Interrupt (DBGU) */
	UHPHS_IRQn = 46,   /**< 46 SAMA5D44 USB Host High Speed (UHPHS) */
	UDPHS_IRQn = 47,   /**< 47 SAMA5D44 USB Device High Speed (UDPHS) */
	SSC0_IRQn = 48,	   /**< 48 SAMA5D44 Synchronous Serial Controller 0 (SSC0) */
	SSC1_IRQn = 49,	   /**< 49 SAMA5D44 Synchronous Serial Controller 1 (SSC1) */
	XDMAC1_IRQn = 50,  /**< 50 SAMA5D44 DMA Controller 1 (XDMAC1) */
	LCDC_IRQn = 51,	   /**< 51 SAMA5D44 LCD Controller (LCDC) */
	ISI_IRQn = 52,	   /**< 52 SAMA5D44 Camera Interface (ISI) */
	TRNG_IRQn = 53,	   /**< 53 SAMA5D44 True Random Number Generator (TRNG) */
	GMAC0_IRQn = 54,   /**< 54 SAMA5D44 Ethernet MAC 0 (GMAC0) */
	GMAC1_IRQn = 55,   /**< 55 SAMA5D44 Ethernet MAC 1 (GMAC1) */
	SFC_IRQn = 57,	   /**< 57 SAMA5D44 Fuse Controller (SFC) */
	SMD_IRQn = 61,	   /**< 61 SAMA5D44 SMD Soft Modem (SMD) */
	TWI3_IRQn = 62,	   /**< 62 SAMA5D44 Two-Wire Interface 3 (TWI3) */
	SFR_IRQn = 64,	   /**< 64 SAMA5D44 Special Function Register  (SFR) */
	AIC_IRQn = 65,	   /**< 65 SAMA5D44 Advanced Interrupt Controller  (AIC) */
	SAIC_IRQn = 66,	   /**< 66 SAMA5D44 Secured Advanced Interrupt Controller  (SAIC) */
	L2CC_IRQn = 67,	   /**< 67 SAMA5D44 L2 Cache Controller  (L2CC) */

	PERIPH_COUNT_IRQn = 68
	/**< Number of peripheral IDs */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_api Peripheral Software API */
/*@{*/

#include "component/component_adc.h"
#include "component/component_aes.h"
#include "component/component_aesb.h"
#include "component/component_aic.h"
#include "component/component_aximx.h"
#include "component/component_dbgu.h"
#include "component/component_gmac.h"
#include "component/component_hsmci.h"
#include "component/component_icm.h"
#include "component/component_isi.h"
#include "component/component_l2cc.h"
#include "component/component_lcdc.h"
#include "component/component_matrix.h"
#include "component/component_mpddrc.h"
#include "component/component_pio.h"
#include "component/component_pit.h"
#include "component/component_pmc.h"
#include "component/component_pwm.h"
#include "component/component_rstc.h"
#include "component/component_rtc.h"
#include "component/component_sckc.h"
#include "component/component_sfc.h"
#include "component/component_sfr.h"
#include "component/component_sha.h"
#include "component/component_shdwc.h"
#include "component/component_smc.h"
#include "component/component_smd.h"
#include "component/component_spi.h"
#include "component/component_ssc.h"
#include "component/component_tc.h"
#include "component/component_tdes.h"
#include "component/component_trng.h"
#include "component/component_twi.h"
#include "component/component_uart.h"
#include "component/component_udphs.h"
#include "component/component_usart.h"
#include "component/component_wdt.h"
#include "component/component_xdmac.h"
/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_reg Registers Access Definitions */
/*@{*/

#include "instance/instance_vdec.h"
#include "instance/instance_aximx.h"
#include "instance/instance_smd.h"
#include "instance/instance_l2cc.h"
#include "instance/instance_lcdc.h"
#include "instance/instance_xdmac1.h"
#include "instance/instance_isi.h"
#include "instance/instance_mpddrc.h"
#include "instance/instance_xdmac0.h"
#include "instance/instance_pmc.h"
#include "instance/instance_matrix0.h"
#include "instance/instance_aesb.h"
#include "instance/instance_hsmci0.h"
#include "instance/instance_uart0.h"
#include "instance/instance_ssc0.h"
#include "instance/instance_pwm.h"
#include "instance/instance_spi0.h"
#include "instance/instance_twi0.h"
#include "instance/instance_twi1.h"
#include "instance/instance_tc0.h"
#include "instance/instance_gmac0.h"
#include "instance/instance_twi2.h"
#include "instance/instance_sfr.h"
#include "instance/instance_usart0.h"
#include "instance/instance_usart1.h"
#include "instance/instance_hsmci1.h"
#include "instance/instance_uart1.h"
#include "instance/instance_usart2.h"
#include "instance/instance_usart3.h"
#include "instance/instance_usart4.h"
#include "instance/instance_ssc1.h"
#include "instance/instance_spi1.h"
#include "instance/instance_spi2.h"
#include "instance/instance_tc1.h"
#include "instance/instance_tc2.h"
#include "instance/instance_gmac1.h"
#include "instance/instance_udphs.h"
#include "instance/instance_trng.h"
#include "instance/instance_adc.h"
#include "instance/instance_twi3.h"
#include "instance/instance_icm.h"
#include "instance/instance_aes.h"
#include "instance/instance_tdes.h"
#include "instance/instance_sha.h"
#include "instance/instance_matrix1.h"
#include "instance/instance_hsmc.h"
#include "instance/instance_sfc.h"
#include "instance/instance_piod.h"
#include "instance/instance_saic.h"
#include "instance/instance_rstc.h"
#include "instance/instance_shdwc.h"
#include "instance/instance_pit.h"
#include "instance/instance_wdt.h"
#include "instance/instance_sckc.h"
#include "instance/instance_rtc.h"
#include "instance/instance_dbgu.h"
#include "instance/instance_pioa.h"
#include "instance/instance_piob.h"
#include "instance/instance_pioc.h"
#include "instance/instance_pioe.h"
#include "instance/instance_aic.h"
/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_id Peripheral Ids Definitions */
/*@{*/

#define ID_PMC     ( 1)	/**< \brief System Controller Interrupt (SYS) */
#define ID_ARM     ( 2)	/**< \brief Performance Monitor Unit (ARM) */
#define ID_PIT     ( 3)	/**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT     ( 4)	/**< \brief Watchdog timer Interrupt (WDT) */
#define ID_PIOD    ( 5)	/**< \brief Parallel I/O Controller D (PIOD) */
#define ID_USART0  ( 6)	/**< \brief USART 0 (USART0) */
#define ID_USART1  ( 7)	/**< \brief USART 1 (USART1) */
#define ID_XDMAC0  ( 8)	/**< \brief DMA Controller 0 (XDMAC0) */
#define ID_ICM     ( 9)	/**< \brief Integritry Check Monitor (ICM) */
#define ID_AES     (12)	/**< \brief Advanced Encryption Standard (AES) */
#define ID_AESB    (13)	/**< \brief AES bridge (AESB) */
#define ID_TDES    (14)	/**< \brief Triple Data Encryption Standard (TDES) */
#define ID_SHA     (15)	/**< \brief SHA Signature (SHA) */
#define ID_MPDDRC  (16)	/**< \brief MPDDR controller (MPDDRC) */
#define ID_MATRIX1 (17)	/**< \brief H32MX, 32-bit AHB Matrix (MATRIX1) */
#define ID_MATRIX0 (18)	/**< \brief H64MX, 64-bit AHB Matrix (MATRIX0) */
#define ID_VDEC    (19)	/**< \brief Video Decoder (VDEC) */
#define ID_MSADCC  (21)	/**< \brief Magnetic Stripe converter Controller (MSADCC) */
#define ID_HSMC    (22)	/**< \brief Multi-bit ECC Interrupt (HSMC) */
#define ID_PIOA    (23)	/**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB    (24)	/**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC    (25)	/**< \brief Parallel I/O Controller C (PIOC) */
#define ID_PIOE    (26)	/**< \brief Parallel I/O Controller E (PIOE) */
#define ID_UART0   (27)	/**< \brief UART 0 (UART0) */
#define ID_UART1   (28)	/**< \brief UART 1 (UART1) */
#define ID_USART2  (29)	/**< \brief USART 2 (USART2) */
#define ID_USART3  (30)	/**< \brief USART 3 (USART3) */
#define ID_USART4  (31)	/**< \brief USART 4 (USART4) */
#define ID_TWI0    (32)	/**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1    (33)	/**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_TWI2    (34)	/**< \brief Two-Wire Interface 2 (TWI2) */
#define ID_HSMCI0  (35)	/**< \brief High Speed Multimedia Card Interface 0 (HSMCI0) */
#define ID_HSMCI1  (36)	/**< \brief High Speed Multimedia Card Interface 1 (HSMCI1) */
#define ID_SPI0    (37)	/**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1    (38)	/**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_SPI2    (39)	/**< \brief Serial Peripheral Interface 2 (SPI2) */
#define ID_TC0     (40)	/**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1     (41)	/**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_TC2     (42)	/**< \brief Timer Counter 2 (ch. 6, 7, 8) (TC2) */
#define ID_PWM     (43)	/**< \brief Pulse Width Modulation Controller (PWM) */
#define ID_ADC     (44)	/**< \brief Touch Screen ADC Controller (ADC) */
#define ID_DBGU    (45)	/**< \brief Debug Unit Interrupt (DBGU) */
#define ID_UHPHS   (46)	/**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS   (47)	/**< \brief USB Device High Speed (UDPHS) */
#define ID_SSC0    (48)	/**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1    (49)	/**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_XDMAC1  (50)	/**< \brief DMA Controller 1 (XDMAC1) */
#define ID_LCDC    (51)	/**< \brief LCD Controller (LCDC) */
#define ID_ISI     (52)	/**< \brief Camera Interface (ISI) */
#define ID_TRNG    (53)	/**< \brief True Random Number Generator (TRNG) */
#define ID_GMAC0   (54)	/**< \brief Ethernet MAC 0 (GMAC0) */
#define ID_GMAC1   (55)	/**< \brief Ethernet MAC 1 (GMAC1) */
#define ID_IRQ     (56)	/**< \brief IRQ Interrupt ID (IRQ) */
#define ID_SFC     (57)	/**< \brief Fuse Controller (SFC) */
#define ID_SMD     (61)	/**< \brief SMD Soft Modem (SMD) */
#define ID_TWI3    (62)	/**< \brief Two-Wire Interface 3 (TWI3) */
#define ID_SFR     (64)	/**< \brief Special Function Register  (SFR) */
#define ID_AIC     (65)	/**< \brief Advanced Interrupt Controller  (AIC) */
#define ID_SAIC    (66)	/**< \brief Secured Advanced Interrupt Controller  (SAIC) */
#define ID_L2CC    (67)	/**< \brief L2 Cache Controller  (L2CC) */

#define ID_PERIPH_COUNT (68) /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_base Peripheral Base Address Definitions */
/*@{*/

#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define VDEC    (0x00300000U) /**< \brief (VDEC   ) Base Address */
#define AXIMX   (0x00700000U) /**< \brief (AXIMX  ) Base Address */
#define SMD     (0x00900000U) /**< \brief (SMD    ) Base Address */
#define L2CC    (0x00A00000U) /**< \brief (L2CC   ) Base Address */
#define LCDC    (0xF0000000U) /**< \brief (LCDC   ) Base Address */
#define XDMAC1  (0xF0004000U) /**< \brief (XDMAC1 ) Base Address */
#define ISI     (0xF0008000U) /**< \brief (ISI    ) Base Address */
#define MPDDRC  (0xF0010000U) /**< \brief (MPDDRC ) Base Address */
#define XDMAC0  (0xF0014000U) /**< \brief (XDMAC0 ) Base Address */
#define PMC     (0xF0018000U) /**< \brief (PMC    ) Base Address */
#define MATRIX0 (0xF001C000U) /**< \brief (MATRIX0) Base Address */
#define AESB    (0xF0020000U) /**< \brief (AESB   ) Base Address */
#define HSMCI0  (0xF8000000U) /**< \brief (HSMCI0 ) Base Address */
#define UART0   (0xF8004000U) /**< \brief (UART0  ) Base Address */
#define SSC0    (0xF8008000U) /**< \brief (SSC0   ) Base Address */
#define PWM     (0xF800C000U) /**< \brief (PWM    ) Base Address */
#define SPI0    (0xF8010000U) /**< \brief (SPI0   ) Base Address */
#define TWI0    (0xF8014000U) /**< \brief (TWI0   ) Base Address */
#define TWI1    (0xF8018000U) /**< \brief (TWI1   ) Base Address */
#define TC0     (0xF801C000U) /**< \brief (TC0    ) Base Address */
#define GMAC0   (0xF8020000U) /**< \brief (GMAC0  ) Base Address */
#define TWI2    (0xF8024000U) /**< \brief (TWI2   ) Base Address */
#define SFR     (0xF8028000U) /**< \brief (SFR    ) Base Address */
#define USART0  (0xF802C000U) /**< \brief (USART0 ) Base Address */
#define USART1  (0xF8030000U) /**< \brief (USART1 ) Base Address */
#define HSMCI1  (0xFC000000U) /**< \brief (HSMCI1 ) Base Address */
#define UART1   (0xFC004000U) /**< \brief (UART1  ) Base Address */
#define USART2  (0xFC008000U) /**< \brief (USART2 ) Base Address */
#define USART3  (0xFC00C000U) /**< \brief (USART3 ) Base Address */
#define USART4  (0xFC010000U) /**< \brief (USART4 ) Base Address */
#define SSC1    (0xFC014000U) /**< \brief (SSC1   ) Base Address */
#define SPI1    (0xFC018000U) /**< \brief (SPI1   ) Base Address */
#define SPI2    (0xFC01C000U) /**< \brief (SPI2   ) Base Address */
#define TC1     (0xFC020000U) /**< \brief (TC1    ) Base Address */
#define TC2     (0xFC024000U) /**< \brief (TC2    ) Base Address */
#define GMAC1   (0xFC028000U) /**< \brief (GMAC1  ) Base Address */
#define UDPHS   (0xFC02C000U) /**< \brief (UDPHS  ) Base Address */
#define TRNG    (0xFC030000U) /**< \brief (TRNG   ) Base Address */
#define ADC     (0xFC034000U) /**< \brief (ADC    ) Base Address */
#define TWI3    (0xFC038000U) /**< \brief (TWI3   ) Base Address */
#define ICM     (0xFC040000U) /**< \brief (ICM    ) Base Address */
#define AES     (0xFC044000U) /**< \brief (AES    ) Base Address */
#define TDES    (0xFC04C000U) /**< \brief (TDES   ) Base Address */
#define SHA     (0xFC050000U) /**< \brief (SHA    ) Base Address */
#define MATRIX1 (0xFC054000U) /**< \brief (MATRIX1) Base Address */
#define HSMC    (0xFC05C000U) /**< \brief (HSMC   ) Base Address */
#define SFC     (0xFC060000U) /**< \brief (SFC    ) Base Address */
#define PIOD    (0xFC068000U) /**< \brief (PIOD   ) Base Address */
#define SAIC    (0xFC068400U) /**< \brief (SAIC   ) Base Address */
#define RSTC    (0xFC068600U) /**< \brief (RSTC   ) Base Address */
#define SHDWC   (0xFC068610U) /**< \brief (SHDWC  ) Base Address */
#define PIT     (0xFC068630U) /**< \brief (PIT    ) Base Address */
#define WDT     (0xFC068640U) /**< \brief (WDT    ) Base Address */
#define SCKC    (0xFC068650U) /**< \brief (SCKC   ) Base Address */
#define RTC     (0xFC0686B0U) /**< \brief (RTC    ) Base Address */
#define DBGU    (0xFC069000U) /**< \brief (DBGU   ) Base Address */
#define PIOA    (0xFC06A000U) /**< \brief (PIOA   ) Base Address */
#define PIOB    (0xFC06B000U) /**< \brief (PIOB   ) Base Address */
#define PIOC    (0xFC06C000U) /**< \brief (PIOC   ) Base Address */
#define PIOE    (0xFC06D000U) /**< \brief (PIOE   ) Base Address */
#define AIC     (0xFC06E000U) /**< \brief (AIC    ) Base Address */
#else
#define VDEC    ((Vdec    *)0x00300000U) /**< \brief (VDEC   ) Base Address */
#define AXIMX   ((Aximx   *)0x00700000U) /**< \brief (AXIMX  ) Base Address */
#define SMD     ((Smd     *)0x00900000U) /**< \brief (SMD    ) Base Address */
#define L2CC    ((L2cc    *)0x00A00000U) /**< \brief (L2CC   ) Base Address */
#define LCDC    ((Lcdc    *)0xF0000000U) /**< \brief (LCDC   ) Base Address */
#define XDMAC1  ((Xdmac   *)0xF0004000U) /**< \brief (XDMAC1 ) Base Address */
#define ISI     ((Isi     *)0xF0008000U) /**< \brief (ISI    ) Base Address */
#define MPDDRC  ((Mpddrc  *)0xF0010000U) /**< \brief (MPDDRC ) Base Address */
#define XDMAC0  ((Xdmac   *)0xF0014000U) /**< \brief (XDMAC0 ) Base Address */
#define PMC     ((Pmc     *)0xF0018000U) /**< \brief (PMC    ) Base Address */
#define MATRIX0 ((Matrix  *)0xF001C000U) /**< \brief (MATRIX0) Base Address */
#define AESB    ((Aesb    *)0xF0020000U) /**< \brief (AESB   ) Base Address */
#define HSMCI0  ((Hsmci   *)0xF8000000U) /**< \brief (HSMCI0 ) Base Address */
#define UART0   ((Uart    *)0xF8004000U) /**< \brief (UART0  ) Base Address */
#define SSC0    ((Ssc     *)0xF8008000U) /**< \brief (SSC0   ) Base Address */
#define PWM     ((Pwm     *)0xF800C000U) /**< \brief (PWM    ) Base Address */
#define SPI0    ((Spi     *)0xF8010000U) /**< \brief (SPI0   ) Base Address */
#define TWI0    ((Twi     *)0xF8014000U) /**< \brief (TWI0   ) Base Address */
#define TWI1    ((Twi     *)0xF8018000U) /**< \brief (TWI1   ) Base Address */
#define TC0     ((Tc      *)0xF801C000U) /**< \brief (TC0    ) Base Address */
#define GMAC0   ((Gmac    *)0xF8020000U) /**< \brief (GMAC0  ) Base Address */
#define TWI2    ((Twi     *)0xF8024000U) /**< \brief (TWI2   ) Base Address */
#define SFR     ((Sfr     *)0xF8028000U) /**< \brief (SFR    ) Base Address */
#define USART0  ((Usart   *)0xF802C000U) /**< \brief (USART0 ) Base Address */
#define USART1  ((Usart   *)0xF8030000U) /**< \brief (USART1 ) Base Address */
#define HSMCI1  ((Hsmci   *)0xFC000000U) /**< \brief (HSMCI1 ) Base Address */
#define UART1   ((Uart    *)0xFC004000U) /**< \brief (UART1  ) Base Address */
#define USART2  ((Usart   *)0xFC008000U) /**< \brief (USART2 ) Base Address */
#define USART3  ((Usart   *)0xFC00C000U) /**< \brief (USART3 ) Base Address */
#define USART4  ((Usart   *)0xFC010000U) /**< \brief (USART4 ) Base Address */
#define SSC1    ((Ssc     *)0xFC014000U) /**< \brief (SSC1   ) Base Address */
#define SPI1    ((Spi     *)0xFC018000U) /**< \brief (SPI1   ) Base Address */
#define SPI2    ((Spi     *)0xFC01C000U) /**< \brief (SPI2   ) Base Address */
#define TC1     ((Tc      *)0xFC020000U) /**< \brief (TC1    ) Base Address */
#define TC2     ((Tc      *)0xFC024000U) /**< \brief (TC2    ) Base Address */
#define GMAC1   ((Gmac    *)0xFC028000U) /**< \brief (GMAC1  ) Base Address */
#define UDPHS   ((Udphs   *)0xFC02C000U) /**< \brief (UDPHS  ) Base Address */
#define TRNG    ((Trng    *)0xFC030000U) /**< \brief (TRNG   ) Base Address */
#define ADC     ((Adc     *)0xFC034000U) /**< \brief (ADC    ) Base Address */
#define TWI3    ((Twi     *)0xFC038000U) /**< \brief (TWI3   ) Base Address */
#define ICM     ((Icm     *)0xFC040000U) /**< \brief (ICM    ) Base Address */
#define AES     ((Aes     *)0xFC044000U) /**< \brief (AES    ) Base Address */
#define TDES    ((Tdes    *)0xFC04C000U) /**< \brief (TDES   ) Base Address */
#define SHA     ((Sha     *)0xFC050000U) /**< \brief (SHA    ) Base Address */
#define MATRIX1 ((Matrix  *)0xFC054000U) /**< \brief (MATRIX1) Base Address */
#define HSMC    ((Smc     *)0xFC05C000U) /**< \brief (HSMC   ) Base Address */
#define SFC     ((Sfc     *)0xFC060000U) /**< \brief (SFC    ) Base Address */
#define PIOD    ((Pio     *)0xFC068000U) /**< \brief (PIOD   ) Base Address */
#define SAIC    ((Aic     *)0xFC068400U) /**< \brief (SAIC   ) Base Address */
#define RSTC    ((Rstc    *)0xFC068600U) /**< \brief (RSTC   ) Base Address */
#define SHDWC   ((Shdwc   *)0xFC068610U) /**< \brief (SHDWC  ) Base Address */
#define PIT     ((Pit     *)0xFC068630U) /**< \brief (PIT    ) Base Address */
#define WDT     ((Wdt     *)0xFC068640U) /**< \brief (WDT    ) Base Address */
#define SCKC    ((Sckc    *)0xFC068650U) /**< \brief (SCKC   ) Base Address */
#define RTC     ((Rtc     *)0xFC0686B0U) /**< \brief (RTC    ) Base Address */
#define DBGU    ((Dbgu    *)0xFC069000U) /**< \brief (DBGU   ) Base Address */
#define PIOA    ((Pio     *)0xFC06A000U) /**< \brief (PIOA   ) Base Address */
#define PIOB    ((Pio     *)0xFC06B000U) /**< \brief (PIOB   ) Base Address */
#define PIOC    ((Pio     *)0xFC06C000U) /**< \brief (PIOC   ) Base Address */
#define PIOE    ((Pio     *)0xFC06D000U) /**< \brief (PIOE   ) Base Address */
#define AIC     ((Aic     *)0xFC06E000U) /**< \brief (AIC    ) Base Address */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/*@}*/

/* ************************************************************************** */
/*   CONFIGURATION ID H64 MATRIX FOR SAMA5D44 */
/* ************************************************************************** */

WEAK const uint8_t _id_h64_matrix[] = {
	ID_ARM,
	ID_XDMAC0,
	ID_AESB,
	ID_MPDDRC,
	ID_VDEC,
	ID_XDMAC1,
	ID_LCDC,
	ID_ISI,
	ID_L2CC
};

#define ID_H64_MATRIX_SIZE	sizeof(_id_h64_matrix)
	
/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/pio_sama5d44.h"
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */

#define IRAM_SIZE (0x20000u)
#define IROM_SIZE (0x20000u)

#define EBI_CS0_ADDR    (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR     (0x20000000u) /**< DDR Chip Select base address */
#define DDR_AES_CS_ADDR (0x40000000u) /**< DDR with AES Chip Select base address */
#define EBI_CS1_ADDR    (0x60000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR    (0x70000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR    (0x80000000u) /**< EBI Chip Select 3 base address */
#define NFC_ADDR        (0x90000000u) /**< NAND Flash Controller Command base address */
#define IROM_ADDR       (0x00000000u) /**< Internal ROM base address */
#define NFC_RAM_ADDR    (0x00100000u) /**< NAND Flash Controller RAM base address */
#define IRAM_ADDR       (0x00200000u) /**< Internal RAM base address */
#define UDPHS_RAM_ADDR  (0x00400000u) /**< USB High Speed Device Port RAM base address */
#define UHP_OHCI_ADDR   (0x00500000u) /**< USB Host Port OHCI base address */
#define UHP_EHCI_ADDR   (0x00600000u) /**< USB Host Port EHCI base address */
#define AXIMX_ADDR      (0x00700000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR        (0x00800000u) /**< Debug Access Port base address */
#define SMD_ADDR        (0x00900000u) /**< Software Modem Device base address */

/* ************************************************************************** */
/*   MISCELLANEOUS DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */

#define CHIP_JTAGID (0x05B3903FUL)
#define CHIP_CIDR   (0x8A5C07CUL)
#define CHIP_EXID   (0x00000004UL)

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAMA5D44 */
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
#endif				/* _SAMA5D44_ */
