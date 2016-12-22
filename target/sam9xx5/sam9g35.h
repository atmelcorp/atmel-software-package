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

#ifndef _SAM9G35_
#define _SAM9G35_

/** \addtogroup SAM9G35_definitions SAM9G35 definitions
  This file defines all structures and symbols for SAM9G35:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#include "compiler.h"

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAM9G35 */
/* ************************************************************************** */
/** \addtogroup SAM9G35_api Peripheral Software API */
/*@{*/

#include "component/component_adc.h"
#include "component/component_aic.h"
#include "component/component_bsc.h"
#include "component/component_dbgu.h"
#include "component/component_dmac.h"
#include "component/component_emac.h"
#include "component/component_gpbr.h"
#include "component/component_hsmci.h"
#include "component/component_lcdc.h"
#include "component/component_matrix.h"
#include "component/component_mpddrc.h"
#include "component/component_pio.h"
#include "component/component_pit.h"
#include "component/component_pmc.h"
#include "component/component_pmecc.h"
#include "component/component_pmerrloc.h"
#include "component/component_pwm.h"
#include "component/component_rstc.h"
#include "component/component_rtc.h"
#include "component/component_sckc.h"
#include "component/component_shdwc.h"
#include "component/component_smc.h"
#include "component/component_spi.h"
#include "component/component_ssc.h"
#include "component/component_tc.h"
#include "component/component_twi.h"
#include "component/component_uart.h"
#include "component/component_udphs.h"
#include "component/component_usart.h"
#include "component/component_wdt.h"

/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAM9G35 */
/* ************************************************************************** */
/** \addtogroup SAM9G35_base Peripheral Base Address Definitions */
/*@{*/

#define SMD      ((Smd      *)0x00400000U) /**< \brief (SMD     ) Base Address */
#define SPI0     ((Spi      *)0xF0000000U) /**< \brief (SPI0    ) Base Address */
#define SPI1     ((Spi      *)0xF0004000U) /**< \brief (SPI1    ) Base Address */
#define HSMCI0   ((Hsmci    *)0xF0008000U) /**< \brief (HSMCI0  ) Base Address */
#define HSMCI1   ((Hsmci    *)0xF000C000U) /**< \brief (HSMCI1  ) Base Address */
#define SSC0     ((Ssc      *)0xF0010000U) /**< \brief (SSC0    ) Base Address */
#define TC0      ((Tc       *)0xF8008000U) /**< \brief (TC0     ) Base Address */
#define TC1      ((Tc       *)0xF800C000U) /**< \brief (TC1     ) Base Address */
#define TWI0     ((Twi      *)0xF8010000U) /**< \brief (TWI0    ) Base Address */
#define TWI1     ((Twi      *)0xF8014000U) /**< \brief (TWI1    ) Base Address */
#define TWI2     ((Twi      *)0xF8018000U) /**< \brief (TWI2    ) Base Address */
#define USART0   ((Usart    *)0xF801C000U) /**< \brief (USART0  ) Base Address */
#define USART1   ((Usart    *)0xF8020000U) /**< \brief (USART1  ) Base Address */
#define USART2   ((Usart    *)0xF8024000U) /**< \brief (USART2  ) Base Address */
#define EMAC0    ((Emac     *)0xF802C000U) /**< \brief (EMAC0   ) Base Address */
#define PWM0     ((Pwm      *)0xF8034000U) /**< \brief (PWM0    ) Base Address */
#define LCDC     ((Lcdc     *)0xF8038000U) /**< \brief (LCDC    ) Base Address */
#define UDPHS    ((Udphs    *)0xF803C000U) /**< \brief (UDPHS   ) Base Address */
#define UART0    ((Uart     *)0xF8040000U) /**< \brief (UART0   ) Base Address */
#define UART1    ((Uart     *)0xF8044000U) /**< \brief (UART1   ) Base Address */
#define ADC      ((Adc      *)0xF804C000U) /**< \brief (ADC     ) Base Address */
#define MATRIX   ((Matrix   *)0xFFFFDE00U) /**< \brief (MATRIX  ) Base Address */
#define PMECC    ((Pmecc    *)0xFFFFE000U) /**< \brief (PMECC   ) Base Address */
#define PMERRLOC ((Pmerrloc *)0xFFFFE600U) /**< \brief (PMERRLOC) Base Address */
#define MPDDRC   ((Mpddrc   *)0xFFFFE800U) /**< \brief (MPDDRC  ) Base Address */
#define SMC      ((Smc      *)0xFFFFEA00U) /**< \brief (SMC     ) Base Address */
#define DMAC0    ((Dmac     *)0xFFFFEC00U) /**< \brief (DMAC0   ) Base Address */
#define DMAC1    ((Dmac     *)0xFFFFEE00U) /**< \brief (DMAC1   ) Base Address */
#define AIC      ((Aic      *)0xFFFFF000U) /**< \brief (AIC     ) Base Address */
#define DBGU     ((Dbgu     *)0xFFFFF200U) /**< \brief (DBGU    ) Base Address */
#define PIOA     ((Pio      *)0xFFFFF400U) /**< \brief (PIOA    ) Base Address */
#define PIOB     ((Pio      *)0xFFFFF600U) /**< \brief (PIOB    ) Base Address */
#define PIOC     ((Pio      *)0xFFFFF800U) /**< \brief (PIOC    ) Base Address */
#define PIOD     ((Pio      *)0xFFFFFA00U) /**< \brief (PIOD    ) Base Address */
#define PMC      ((Pmc      *)0xFFFFFC00U) /**< \brief (PMC     ) Base Address */
#define RSTC     ((Rstc     *)0xFFFFFE00U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    ((Shdwc    *)0xFFFFFE10U) /**< \brief (SHDWC   ) Base Address */
#define PIT      ((Pit      *)0xFFFFFE30U) /**< \brief (PIT     ) Base Address */
#define WDT      ((Wdt      *)0xFFFFFE40U) /**< \brief (WDT     ) Base Address */
#define SCKC     ((Sckc     *)0xFFFFFE50U) /**< \brief (SCKC    ) Base Address */
#define BSC      ((Bsc      *)0xFFFFFE54U) /**< \brief (BSC     ) Base Address */
#define GPBR     ((Gpbr     *)0xFFFFFE60U) /**< \brief (GPBR    ) Base Address */
#define RTC      ((Rtc      *)0xFFFFFEB0U) /**< \brief (RTC     ) Base Address */

/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAM9G35 */
/* ************************************************************************** */
/** \addtogroup SAM9G35_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/pio_sam9g35.h"

/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAM9G35 */
/* ************************************************************************** */

#define IRAM_SIZE (0x8000u)

#define EBI_CS0_ADDR     (0x10000000u) /**< EBI Chip Select 0 base address */
#define EBI_CS1_ADDR     (0x20000000u) /**< EBI Chip Select 1 base address */
#define DDR_CS_ADDR      (0x20000000u) /**< DDR SDRAM Controller on EBI Chip Select 1 base address */
#define EBI_CS2_ADDR     (0x30000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR     (0x40000000u) /**< EBI Chip Select 3 base address */
#define EBI_NF_ADDR      (0x40000000u) /**< NAND Flash on EBI Chip Select 3 base address */
#define EBI_CS4_ADDR     (0x50000000u) /**< EBI Chip Select 4 base address */
#define EBI_CS5_ADDR     (0x60000000u) /**< EBI Chip Select 5 base address */
#define IROM_ADDR        (0x00100000u) /**< Internal ROM base address */
#define IRAM_ADDR        (0x00300000u) /**< Internal RAM base address */
#define SMD_ADDR         (0x00400000u) /**< Software Modem Device base address */
#define UDPHS_RAM_ADDR   (0x00500000u) /**< USB High Speed Device Port RAM base address */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAM9G35_ */
