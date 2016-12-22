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

#include <stdint.h>
#include "compiler.h"

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
#include "component/component_secumod.h"
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
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D44 */
/* ************************************************************************** */
/** \addtogroup SAMA5D44_base Peripheral Base Address Definitions */
/*@{*/

#define VDEC     ((Vdec     *)0x00300000U) /**< \brief (VDEC    ) Base Address */
#define AXIMX    ((Aximx    *)0x00700000U) /**< \brief (AXIMX   ) Base Address */
#define SMD      ((Smd      *)0x00900000U) /**< \brief (SMD     ) Base Address */
#define L2CC     ((L2cc     *)0x00A00000U) /**< \brief (L2CC    ) Base Address */
#define LCDC     ((Lcdc     *)0xF0000000U) /**< \brief (LCDC    ) Base Address */
#define XDMAC1   ((Xdmac    *)0xF0004000U) /**< \brief (XDMAC1  ) Base Address */
#define ISI      ((Isi      *)0xF0008000U) /**< \brief (ISI     ) Base Address */
#define MPDDRC   ((Mpddrc   *)0xF0010000U) /**< \brief (MPDDRC  ) Base Address */
#define XDMAC0   ((Xdmac    *)0xF0014000U) /**< \brief (XDMAC0  ) Base Address */
#define PMC      ((Pmc      *)0xF0018000U) /**< \brief (PMC     ) Base Address */
#define MATRIX0  ((Matrix   *)0xF001C000U) /**< \brief (MATRIX0 ) Base Address */
#define AESB     ((Aesb     *)0xF0020000U) /**< \brief (AESB    ) Base Address */
#define HSMCI0   ((Hsmci    *)0xF8000000U) /**< \brief (HSMCI0  ) Base Address */
#define UART0    ((Uart     *)0xF8004000U) /**< \brief (UART0   ) Base Address */
#define SSC0     ((Ssc      *)0xF8008000U) /**< \brief (SSC0    ) Base Address */
#define PWM0     ((Pwm      *)0xF800C000U) /**< \brief (PWM0    ) Base Address */
#define SPI0     ((Spi      *)0xF8010000U) /**< \brief (SPI0    ) Base Address */
#define TWI0     ((Twi      *)0xF8014000U) /**< \brief (TWI0    ) Base Address */
#define TWI1     ((Twi      *)0xF8018000U) /**< \brief (TWI1    ) Base Address */
#define TC0      ((Tc       *)0xF801C000U) /**< \brief (TC0     ) Base Address */
#define GMAC0    ((Gmac     *)0xF8020000U) /**< \brief (GMAC0   ) Base Address */
#define TWI2     ((Twi      *)0xF8024000U) /**< \brief (TWI2    ) Base Address */
#define SFR      ((Sfr      *)0xF8028000U) /**< \brief (SFR     ) Base Address */
#define USART0   ((Usart    *)0xF802C000U) /**< \brief (USART0  ) Base Address */
#define USART1   ((Usart    *)0xF8030000U) /**< \brief (USART1  ) Base Address */
#define HSMCI1   ((Hsmci    *)0xFC000000U) /**< \brief (HSMCI1  ) Base Address */
#define UART1    ((Uart     *)0xFC004000U) /**< \brief (UART1   ) Base Address */
#define USART2   ((Usart    *)0xFC008000U) /**< \brief (USART2  ) Base Address */
#define USART3   ((Usart    *)0xFC00C000U) /**< \brief (USART3  ) Base Address */
#define USART4   ((Usart    *)0xFC010000U) /**< \brief (USART4  ) Base Address */
#define SSC1     ((Ssc      *)0xFC014000U) /**< \brief (SSC1    ) Base Address */
#define SPI1     ((Spi      *)0xFC018000U) /**< \brief (SPI1    ) Base Address */
#define SPI2     ((Spi      *)0xFC01C000U) /**< \brief (SPI2    ) Base Address */
#define TC1      ((Tc       *)0xFC020000U) /**< \brief (TC1     ) Base Address */
#define TC2      ((Tc       *)0xFC024000U) /**< \brief (TC2     ) Base Address */
#define GMAC1    ((Gmac     *)0xFC028000U) /**< \brief (GMAC1   ) Base Address */
#define UDPHS    ((Udphs    *)0xFC02C000U) /**< \brief (UDPHS   ) Base Address */
#define TRNG     ((Trng     *)0xFC030000U) /**< \brief (TRNG    ) Base Address */
#define ADC      ((Adc      *)0xFC034000U) /**< \brief (ADC     ) Base Address */
#define TWI3     ((Twi      *)0xFC038000U) /**< \brief (TWI3    ) Base Address */
#define ICM      ((Icm      *)0xFC040000U) /**< \brief (ICM     ) Base Address */
#define AES      ((Aes      *)0xFC044000U) /**< \brief (AES     ) Base Address */
#define TDES     ((Tdes     *)0xFC04C000U) /**< \brief (TDES    ) Base Address */
#define SHA      ((Sha      *)0xFC050000U) /**< \brief (SHA     ) Base Address */
#define MATRIX1  ((Matrix   *)0xFC054000U) /**< \brief (MATRIX1 ) Base Address */
#define SECURAM  ((Securam  *)0xFC058000U) /**< \brief (SECURAM ) Base Address */
#define NFC      ((Nfc      *)0xFC05C000U) /**< \brief (NFC     ) Base Address */
#define PMECC    ((Pmecc    *)0xFC05C070U) /**< \brief (PMECC   ) Base Address */
#define PMERRLOC ((Pmerrloc *)0xFC05C500U) /**< \brief (PMERRLOC) Base Address */
#define SMC      ((Smc      *)0xFC05C600U) /**< \brief (SMC     ) Base Address */
#define SFC      ((Sfc      *)0xFC060000U) /**< \brief (SFC     ) Base Address */
#define PIOD     ((Pio      *)0xFC068000U) /**< \brief (PIOD    ) Base Address */
#define SECUMOD  ((Secumod  *)0xFC068200U) /**< \brief (SECUMOD ) Base Address */
#define SAIC     ((Aic      *)0xFC068400U) /**< \brief (SAIC    ) Base Address */
#define RSTC     ((Rstc     *)0xFC068600U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    ((Shdwc    *)0xFC068610U) /**< \brief (SHDWC   ) Base Address */
#define PIT      ((Pit      *)0xFC068630U) /**< \brief (PIT     ) Base Address */
#define WDT      ((Wdt      *)0xFC068640U) /**< \brief (WDT     ) Base Address */
#define SCKC     ((Sckc     *)0xFC068650U) /**< \brief (SCKC    ) Base Address */
#define RTC      ((Rtc      *)0xFC0686B0U) /**< \brief (RTC     ) Base Address */
#define DBGU     ((Dbgu     *)0xFC069000U) /**< \brief (DBGU    ) Base Address */
#define PIOA     ((Pio      *)0xFC06A000U) /**< \brief (PIOA    ) Base Address */
#define PIOB     ((Pio      *)0xFC06B000U) /**< \brief (PIOB    ) Base Address */
#define PIOC     ((Pio      *)0xFC06C000U) /**< \brief (PIOC    ) Base Address */
#define PIOE     ((Pio      *)0xFC06D000U) /**< \brief (PIOE    ) Base Address */
#define AIC      ((Aic      *)0xFC06E000U) /**< \brief (AIC     ) Base Address */

/*@}*/

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
#define NFC_CMD_ADDR    (0x90000000u) /**< NAND Flash Controller Command base address */
#define IROM_ADDR       (0x00000000u) /**< Internal ROM base address */
#define NFC_RAM_ADDR    (0x00100000u) /**< NAND Flash Controller RAM base address */
#define IRAM_ADDR       (0x00200000u) /**< Internal RAM base address */
#define UDPHS_RAM_ADDR  (0x00400000u) /**< USB High Speed Device Port RAM base address */
#define UHP_OHCI_ADDR   (0x00500000u) /**< USB Host Port OHCI base address */
#define UHP_EHCI_ADDR   (0x00600000u) /**< USB Host Port EHCI base address */
#define AXIMX_ADDR      (0x00700000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR        (0x00800000u) /**< Debug Access Port base address */
#define SMD_ADDR        (0x00900000u) /**< Software Modem Device base address */
#define SECURAM_ADDR    (0xFC058000u) /**< Security Module Internal Memory base address */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMA5D44_ */
