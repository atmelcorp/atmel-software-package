/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#ifndef _SAMV71_
#define _SAMV71_

/** \addtogroup SAMV71_definitions SAMV71 definitions
  This file defines all structures and symbols for SAMV71:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "compiler.h"

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMV71 */
/* ************************************************************************** */

/** \addtogroup SAMV71_api Peripheral Software API */
/*@{*/

#include "component/component_acc.h"
#include "component/component_aes.h"
#include "component/component_afec.h"
#include "component/component_chipid.h"
#include "component/component_dacc.h"
#include "component/component_eefc.h"
#include "component/component_fpu.h"
#include "component/component_gmac.h"
#include "component/component_gpbr.h"
#include "component/component_hsmci.h"
#include "component/component_icm.h"
#include "component/component_isi.h"
#include "component/component_matrix.h"
#include "component/component_mcan.h"
#include "component/component_mlb.h"
#include "component/component_mpddrc.h"
#include "component/component_mpu.h"
#include "component/component_nvic.h"
#include "component/component_pio.h"
#include "component/component_pmc.h"
#include "component/component_pwm.h"
#include "component/component_qspi.h"
#include "component/component_rstc.h"
#include "component/component_rswdt.h"
#include "component/component_rtc.h"
#include "component/component_rtt.h"
#include "component/component_scb.h"
#include "component/component_smc.h"
#include "component/component_spi.h"
#include "component/component_ssc.h"
#include "component/component_supc.h"
#include "component/component_systick.h"
#include "component/component_tc.h"
#include "component/component_trng.h"
#include "component/component_twi.h"
#include "component/component_uart.h"
#include "component/component_usart.h"
#include "component/component_usbhs.h"
#include "component/component_utmi.h"
#include "component/component_wdt.h"
#include "component/component_xdmac.h"

/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMV71 */
/* ************************************************************************** */

/** \addtogroup SAMV71_base Peripheral Base Address Definitions */
/*@{*/

#define HSMCI0  ((Hsmci   *)0x40000000U) /**< \brief (HSMCI0 ) Base Address */
#define SSC0    ((Ssc     *)0x40004000U) /**< \brief (SSC0   ) Base Address */
#define SPI0    ((Spi     *)0x40008000U) /**< \brief (SPI0   ) Base Address */
#define TC0     ((Tc      *)0x4000C000U) /**< \brief (TC0    ) Base Address */
#define TC1     ((Tc      *)0x40010000U) /**< \brief (TC1    ) Base Address */
#define TC2     ((Tc      *)0x40014000U) /**< \brief (TC2    ) Base Address */
#define TWI0    ((Twi     *)0x40018000U) /**< \brief (TWI0   ) Base Address */
#define TWI1    ((Twi     *)0x4001C000U) /**< \brief (TWI1   ) Base Address */
#define PWM0    ((Pwm     *)0x40020000U) /**< \brief (PWM0   ) Base Address */
#define USART0  ((Usart   *)0x40024000U) /**< \brief (USART0 ) Base Address */
#define USART1  ((Usart   *)0x40028000U) /**< \brief (USART1 ) Base Address */
#define USART2  ((Usart   *)0x4002C000U) /**< \brief (USART2 ) Base Address */
#if defined(CONFIG_CHIP_SAME70) || defined(CONFIG_CHIP_SAMV70) || defined(CONFIG_CHIP_SAMV71)
#define MCAN0   ((Mcan    *)0x40030000U) /**< \brief (MCAN0  ) Base Address */
#define MCAN1   ((Mcan    *)0x40034000U) /**< \brief (MCAN1  ) Base Address */
#endif
#define USBHS   ((Usbhs   *)0x40038000U) /**< \brief (USBHS  ) Base Address */
#define AFEC0   ((Afec    *)0x4003C000U) /**< \brief (AFEC0  ) Base Address */
#define DACC    ((Dacc    *)0x40040000U) /**< \brief (DACC   ) Base Address */
#define ACC     ((Acc     *)0x40044000U) /**< \brief (ACC    ) Base Address */
#define ICM     ((Icm     *)0x40048000U) /**< \brief (ICM    ) Base Address */
#define ISI     ((Isi     *)0x4004C000U) /**< \brief (ISI    ) Base Address */
#if defined(CONFIG_CHIP_SAME70) || defined(CONFIG_CHIP_SAMV71)
#define GMAC0   ((Gmac    *)0x40050000U) /**< \brief (GMAC0  ) Base Address */
#endif
#define TC3     ((Tc      *)0x40054000U) /**< \brief (TC3    ) Base Address */
#define SPI1    ((Spi     *)0x40058000U) /**< \brief (SPI1   ) Base Address */
#define PWM1    ((Pwm     *)0x4005C000U) /**< \brief (PWM1   ) Base Address */
#define TWI2    ((Twi     *)0x40060000U) /**< \brief (TWI2   ) Base Address */
#define AFEC1   ((Afec    *)0x40064000U) /**< \brief (AFEC1  ) Base Address */
#if defined(CONFIG_CHIP_SAMV70) || defined(CONFIG_CHIP_SAMV71)
#define MLB     ((Mlb     *)0x40068000U) /**< \brief (MLB    ) Base Address */
#endif
#define AES     ((Aes     *)0x4006C000U) /**< \brief (AES    ) Base Address */
#define TRNG    ((Trng    *)0x40070000U) /**< \brief (TRNG   ) Base Address */
#define XDMAC0  ((Xdmac   *)0x40078000U) /**< \brief (XDMAC0 ) Base Address */
#define QSPI0   ((Qspi    *)0x4007C000U) /**< \brief (QSPI0  ) Base Address */
#define SMC     ((Smc     *)0x40080000U) /**< \brief (SMC    ) Base Address */
#define MPDDRC  ((Mpddrc  *)0x40084000U) /**< \brief (MPDDRC ) Base Address */
#define MATRIX  ((Matrix  *)0x40088000U) /**< \brief (MATRIX ) Base Address */
#define UTMI    ((Utmi    *)0x400E0400U) /**< \brief (UTMI   ) Base Address */
#define PMC     ((Pmc     *)0x400E0600U) /**< \brief (PMC    ) Base Address */
#define UART0   ((Uart    *)0x400E0800U) /**< \brief (UART0  ) Base Address */
#define CHIPID  ((Chipid  *)0x400E0940U) /**< \brief (CHIPID ) Base Address */
#define UART1   ((Uart    *)0x400E0A00U) /**< \brief (UART1  ) Base Address */
#define EEFC    ((Eefc    *)0x400E0C00U) /**< \brief (EEFC   ) Base Address */
#define PIOA    ((Pio     *)0x400E0E00U) /**< \brief (PIOA   ) Base Address */
#define PIOB    ((Pio     *)0x400E1000U) /**< \brief (PIOB   ) Base Address */
#define PIOC    ((Pio     *)0x400E1200U) /**< \brief (PIOC   ) Base Address */
#define PIOD    ((Pio     *)0x400E1400U) /**< \brief (PIOD   ) Base Address */
#define PIOE    ((Pio     *)0x400E1600U) /**< \brief (PIOE   ) Base Address */
#define RSTC    ((Rstc    *)0x400E1800U) /**< \brief (RSTC   ) Base Address */
#define SUPC    ((Supc    *)0x400E1810U) /**< \brief (SUPC   ) Base Address */
#define RTT     ((Rtt     *)0x400E1830U) /**< \brief (RTT    ) Base Address */
#define WDT     ((Wdt     *)0x400E1850U) /**< \brief (WDT    ) Base Address */
#define RTC     ((Rtc     *)0x400E1860U) /**< \brief (RTC    ) Base Address */
#define GPBR    ((Gpbr    *)0x400E1890U) /**< \brief (GPBR   ) Base Address */
#define RSWDT   ((Rswdt   *)0x400E1900U) /**< \brief (RSWDT  ) Base Address */
#define UART2   ((Uart    *)0x400E1A00U) /**< \brief (UART2  ) Base Address */
#define UART3   ((Uart    *)0x400E1C00U) /**< \brief (UART3  ) Base Address */
#define UART4   ((Uart    *)0x400E1E00U) /**< \brief (UART4  ) Base Address */
#define SCNSCB  ((Scnscb  *)0xE000E000U) /**< \brief (SCNSCB ) Base Address */
#define SYSTICK ((Systick *)0xE000E010U) /**< \brief (SYSTICK) Base Address */
#define NVIC    ((Nvic    *)0xE000E100U) /**< \brief (NVIC   ) Base Address */
#define SCB     ((Scb     *)0xE000ED00U) /**< \brief (SCB    ) Base Address */
#define MPU     ((Mpu     *)0xE000ED90U) /**< \brief (MPU    ) Base Address */
#define FPU     ((Fpu     *)0xE000EF30U) /**< \brief (FPU    ) Base Address */

/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMV71 */
/* ************************************************************************** */

/** \addtogroup SAMV71_pio Peripheral Pio Definitions */
/*@{*/

#if defined(CONFIG_PACKAGE_64PIN)
#include "pio/pio_samv71_64pin.h"
#elif defined(CONFIG_PACKAGE_100PIN)
#include "pio/pio_samv71_100pin.h"
#elif defined(CONFIG_PACKAGE_144PIN)
#include "pio/pio_samv71_144pin.h"
#endif

/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMV71 */
/* ************************************************************************** */

#if defined(CONFIG_FLASH_512KB)
#define IFLASH_SIZE             (0x80000u)
#define IRAM_SIZE               (0x40000u)
#elif defined(CONFIG_FLASH_1024KB)
#define IFLASH_SIZE             (0x100000u)
#define IRAM_SIZE               (0x60000u)
#elif defined(CONFIG_FLASH_2048KB)
#define IFLASH_SIZE             (0x200000u)
#define IRAM_SIZE               (0x60000u)
#endif

#define QSPIMEM0_ADDR  (0x80000000u) /**< QSPI Memory 0 base address */
#define AXIMX_ADDR     (0xA0000000u) /**< AXI Bus Matrix base address */
#define ITCM_ADDR      (0x00000000u) /**< Instruction Tightly Coupled Memory base address */
#define IFLASH_ADDR    (0x00400000u) /**< Internal Flash base address */
#define IROM_ADDR      (0x00800000u) /**< Internal ROM base address */
#define DTCM_ADDR      (0x20000000u) /**< Data Tightly Coupled Memory base address */
#define IRAM_ADDR      (0x20400000u) /**< Internal RAM base address */
#define EBI_CS0_ADDR   (0x60000000u) /**< EBI Chip Select 0 base address */
#define EBI_CS1_ADDR   (0x61000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR   (0x62000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR   (0x63000000u) /**< EBI Chip Select 3 base address */
#define DDR_CS_ADDR    (0x70000000u) /**< DDR Chip Select base address */
#define USBHS_RAM_ADDR (0xA0100000u) /**< USB RAM base address */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMV71_ */
