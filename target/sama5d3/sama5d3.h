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


#ifndef _SAMA5D3x_
#define _SAMA5D3x_

/** \addtogroup SAMA5D3x_definitions SAMA5D3x definitions
  This file defines all structures and symbols for SAMA5D3x:
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
/*   CHIPID DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_chipid CHIPID Definitions */
/*@{*/

#define CHIPID_CIDR_SAMA5D3  (0x8a5c07c0ul)

#define CHIPID_EXID_SAMA5D31 (0x00444300ul)
#define CHIPID_EXID_SAMA5D33 (0x00414300ul)
#define CHIPID_EXID_SAMA5D34 (0x00414301ul)
#define CHIPID_EXID_SAMA5D35 (0x00584300ul)
#define CHIPID_EXID_SAMA5D36 (0x00004301ul)

/*@}*/

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_api Peripheral Software API */
/*@{*/

#include "component/component_adc.h"
#include "component/component_aic.h"
#include "component/component_aximx.h"
#include "component/component_bsc.h"
#ifdef CONFIG_HAVE_CAN
#include "component/component_can.h"
#endif
#include "component/component_dbgu.h"
#include "component/component_dmac.h"
#ifdef CONFIG_HAVE_EMAC
#include "component/component_emac.h"
#endif
#ifdef CONFIG_HAVE_GMAC
#include "component/component_gmac.h"
#endif
#include "component/component_fuse.h"
#include "component/component_gpbr.h"
#include "component/component_hsmci.h"
#include "component/component_isi.h"
#ifdef CONFIG_HAVE_LCDC
#include "component/component_lcdc.h"
#endif
#include "component/component_matrix.h"
#include "component/component_mpddrc.h"
#include "component/component_nfc.h"
#include "component/component_pio.h"
#include "component/component_pit.h"
#include "component/component_pmc.h"
#include "component/component_pmecc.h"
#include "component/component_pmerrloc.h"
#include "component/component_pwm.h"
#include "component/component_rstc.h"
#include "component/component_rtc.h"
#include "component/component_sckc.h"
#include "component/component_sfr.h"
#include "component/component_shdwc.h"
#include "component/component_smc.h"
#include "component/component_spi.h"
#include "component/component_ssc.h"
#include "component/component_tc.h"
#include "component/component_trng.h"
#include "component/component_twi.h"
#ifdef CONFIG_HAVE_UART
#include "component/component_uart.h"
#endif
#include "component/component_udphs.h"
#include "component/component_usart.h"
#include "component/component_wdt.h"
#include "component/component_aes.h"
#include "component/component_sha.h"
#include "component/component_tdes.h"

/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_base Peripheral Base Address Definitions */
/*@{*/

#define SMD      ((Smd      *)0x00400000U) /**< \brief (SMD     ) Base Address */
#define AXIMX    ((Aximx    *)0x00800000U) /**< \brief (AXIMX   ) Base Address */
#define HSMCI0   ((Hsmci    *)0xF0000000U) /**< \brief (HSMCI0  ) Base Address */
#define SPI0     ((Spi      *)0xF0004000U) /**< \brief (SPI0    ) Base Address */
#define SSC0     ((Ssc      *)0xF0008000U) /**< \brief (SSC0    ) Base Address */
#ifdef CONFIG_HAVE_CAN
#define CAN0     ((Can      *)0xF000C000U) /**< \brief (CAN0    ) Base Address */
#endif
#define TC0      ((Tc       *)0xF0010000U) /**< \brief (TC0     ) Base Address */
#define TWI0     ((Twi      *)0xF0014000U) /**< \brief (TWI0    ) Base Address */
#define TWI1     ((Twi      *)0xF0018000U) /**< \brief (TWI1    ) Base Address */
#define USART0   ((Usart    *)0xF001C000U) /**< \brief (USART0  ) Base Address */
#define USART1   ((Usart    *)0xF0020000U) /**< \brief (USART1  ) Base Address */
#ifdef CONFIG_HAVE_UART
#define UART0    ((Uart     *)0xF0024000U) /**< \brief (UART0   ) Base Address */
#endif
#ifdef CONFIG_HAVE_GMAC
#define GMAC0    ((Gmac     *)0xF0028000U) /**< \brief (GMAC0   ) Base Address */
#endif
#define PWM0     ((Pwm      *)0xF002C000U) /**< \brief (PWM0    ) Base Address */
#ifdef CONFIG_HAVE_LCDC
#define LCDC     ((Lcdc     *)0xF0030000U) /**< \brief (LCDC    ) Base Address */
#endif
#define ISI      ((Isi      *)0xF0034000U) /**< \brief (ISI     ) Base Address */
#define SFR      ((Sfr      *)0xF0038000U) /**< \brief (SFR     ) Base Address */
#define HSMCI1   ((Hsmci    *)0xF8000000U) /**< \brief (HSMCI1  ) Base Address */
#if defined(CONFIG_CHIP_SAMA5D31) ||\
    defined(CONFIG_CHIP_SAMA5D34) ||\
    defined(CONFIG_CHIP_SAMA5D35) ||\
    defined(CONFIG_CHIP_SAMA5D36)
#define HSMCI2   ((Hsmci    *)0xF8004000U) /**< \brief (HSMCI2  ) Base Address */
#endif
#define SPI1     ((Spi      *)0xF8008000U) /**< \brief (SPI1    ) Base Address */
#define SSC1     ((Ssc      *)0xF800C000U) /**< \brief (SSC1    ) Base Address */
#ifdef CONFIG_HAVE_CAN
#define CAN1     ((Can      *)0xF8010000U) /**< \brief (CAN1    ) Base Address */
#endif
#if defined(CONFIG_CHIP_SAMA5D35) ||\
    defined(CONFIG_CHIP_SAMA5D36)
#define TC1      ((Tc       *)0xF8014000U) /**< \brief (TC1     ) Base Address */
#endif
#define ADC      ((Adc      *)0xF8018000U) /**< \brief (ADC     ) Base Address */
#define TWI2     ((Twi      *)0xF801C000U) /**< \brief (TWI2    ) Base Address */
#define USART2   ((Usart    *)0xF8020000U) /**< \brief (USART2  ) Base Address */
#define USART3   ((Usart    *)0xF8024000U) /**< \brief (USART3  ) Base Address */
#ifdef CONFIG_HAVE_UART
#define UART1    ((Uart     *)0xF8028000U) /**< \brief (UART1   ) Base Address */
#endif
#ifdef CONFIG_HAVE_EMAC
#define EMAC0    ((Emac     *)0xF802C000U) /**< \brief (EMAC0   ) Base Address */
#endif
#define UDPHS    ((Udphs    *)0xF8030000U) /**< \brief (UDPHS   ) Base Address */
#define SHA      ((Sha      *)0xF8034000U) /**< \brief (SHA     ) Base Address */
#define AES      ((Aes      *)0xF8038000U) /**< \brief (AES     ) Base Address */
#define TDES     ((Tdes     *)0xF803C000U) /**< \brief (TDES    ) Base Address */
#define TRNG     ((Trng     *)0xF8040000U) /**< \brief (TRNG    ) Base Address */
#define NFC      ((Nfc      *)0xFFFFC000U) /**< \brief (NFC     ) Base Address */
#define PMECC    ((Pmecc    *)0xFFFFC070U) /**< \brief (PMECC   ) Base Address */
#define PMERRLOC ((Pmerrloc *)0xFFFFC500U) /**< \brief (PMERRLOC) Base Address */
#define SMC      ((Smc      *)0xFFFFC600U) /**< \brief (SMC     ) Base Address */
#define FUSE     ((Fuse     *)0xFFFFE400U) /**< \brief (FUSE    ) Base Address */
#define DMAC0    ((Dmac     *)0xFFFFE600U) /**< \brief (DMAC0   ) Base Address */
#define DMAC1    ((Dmac     *)0xFFFFE800U) /**< \brief (DMAC1   ) Base Address */
#define MPDDRC   ((Mpddrc   *)0xFFFFEA00U) /**< \brief (MPDDRC  ) Base Address */
#define MATRIX   ((Matrix   *)0xFFFFEC00U) /**< \brief (MATRIX  ) Base Address */
#define DBGU     ((Dbgu     *)0xFFFFEE00U) /**< \brief (DBGU    ) Base Address */
#define AIC      ((Aic      *)0xFFFFF000U) /**< \brief (AIC     ) Base Address */
#define PIOA     ((Pio      *)0xFFFFF200U) /**< \brief (PIOA    ) Base Address */
#define PIOB     ((Pio      *)0xFFFFF400U) /**< \brief (PIOB    ) Base Address */
#define PIOC     ((Pio      *)0xFFFFF600U) /**< \brief (PIOC    ) Base Address */
#define PIOD     ((Pio      *)0xFFFFF800U) /**< \brief (PIOD    ) Base Address */
#define PIOE     ((Pio      *)0xFFFFFA00U) /**< \brief (PIOE    ) Base Address */
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
/*   PIO DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/pio_sama5d3.h"

/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */

#define IRAM0_SIZE (0x10000u)
#define IRAM1_SIZE (0x10000u)
#define IROM_SIZE  (0x20000u)
#define IRAM_SIZE  (IRAM0_SIZE+IRAM1_SIZE)

#define EBI_CS0_ADDR   (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR    (0x20000000u) /**< DDR Chip Select base address */
#define EBI_CS1_ADDR   (0x40000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR   (0x50000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR   (0x60000000u) /**< EBI Chip Select 3 base address */
#define EBI_NF_ADDR    (0x60000000u) /**< NAND Flash on EBI Chip Select 3 base address */
#define NFC_CMD_ADDR   (0x70000000u) /**< NAND Flash Controller Command base address */
#define IROM_ADDR      (0x00100000u) /**< Internal ROM base address */
#define NFC_RAM_ADDR   (0x00200000u) /**< NAND Flash Controller RAM base address */
#define IRAM0_ADDR     (0x00300000u) /**< Internal RAM 0 base address */
#define IRAM_ADDR      IRAM0_ADDR
#define IRAM1_ADDR     (IRAM0_ADDR+IRAM0_SIZE) /**< Internal RAM 1 base address */
#define SMD_ADDR       (0x00400000u) /**< Software Modem Device base address */
#define UDPHS_RAM_ADDR (0x00500000u) /**< USB High Speed Device Port RAM base address */
#define UHP_OHCI_ADDR  (0x00600000u) /**< USB Host Port OHCI base address */
#define UHP_EHCI_ADDR  (0x00700000u) /**< USB Host Port EHCI base address */
#define AXIMX_ADDR     (0x00800000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR       (0x00900000u) /**< Debug Access Port base address */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMA5D3x_ */

