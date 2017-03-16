/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
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
/*                                                                              */

#ifndef _CHIP_H_
#define _CHIP_H_

#include <stdint.h>
#include <stdbool.h>

#if defined(CONFIG_CHIP_SAM9G15)
  #include "sam9g15.h"
#elif defined(CONFIG_CHIP_SAM9G25)
  #include "sam9g25.h"
#elif defined(CONFIG_CHIP_SAM9G35)
  #include "sam9g35.h"
#elif defined(CONFIG_CHIP_SAM9X25)
  #include "sam9x25.h"
#elif defined(CONFIG_CHIP_SAM9X35)
  #include "sam9x35.h"
#else
  #error Library does not support the specified device.
#endif
#include "chip_common.h"

/* forward declaration */
struct _console_cfg;

/* ************************************************************************** */
/*   CHIPID DEFINITIONS FOR SAM9xx5 */
/* ************************************************************************** */
/** \addtogroup SAM9xx5_chipid CHIPID Definitions */
/*@{*/

#define CHIPID_CIDR_SAM9XX5     (0x819a05a0ul)

#define CHIPID_EXID_SAM9G15     (0x00000000ul)
#define CHIPID_EXID_SAM9G25     (0x00000003ul)
#define CHIPID_EXID_SAM9G35     (0x00000001ul)
#define CHIPID_EXID_SAM9X35     (0x00000002ul)
#define CHIPID_EXID_SAM9X25     (0x00000004ul)

/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAM9xx5 */
/* ************************************************************************** */
/** \addtogroup SAM9xx5_id Peripheral Ids Definitions */
/*@{*/

#define ID_FIQ    ( 0) /**< \brief Advanced Interrupt Controller (FIQ) */
#define ID_SYSC   ( 1) /**< \brief System Controller (SYS) */
#define ID_PIT    ( 1) /**< \brief Periodic Interval Timer (PIT) */
#define ID_RTC    ( 1) /**< \brief Real Time Clock (RTC) */
#define ID_DBGU   ( 1) /**< \brief Debug Unit (DBGU) */
#define ID_WDT    ( 1) /**< \brief Watchdog timer (WDT) */
#define ID_PIOA   ( 2) /**< \brief Parallel I/O Controller A and B (PIOA) */
#define ID_PIOB   ( 2) /**< \brief Parallel I/O Controller A and B (PIOB) */
#define ID_PIOC   ( 3) /**< \brief Parallel I/O Controller C and D (PIOC) */
#define ID_PIOD   ( 3) /**< \brief Parallel I/O Controller C and D (PIOD) */
#define ID_SMD    ( 4) /**< \brief SMD Soft Modem (SMD) */
#define ID_USART0 ( 5) /**< \brief USART 0 (USART0) */
#define ID_USART1 ( 6) /**< \brief USART 1 (USART1) */
#define ID_USART2 ( 7) /**< \brief USART 2 (USART2) */
#define ID_USART3 ( 8) /**< \brief USART 3 (USART3) */
#define ID_TWI0   ( 9) /**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1   (10) /**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_TWI2   (11) /**< \brief Two-Wire Interface 2 (TWI2) */
#define ID_HSMCI0 (12) /**< \brief High Speed Multimedia Card Interface 0 (HSMCI0) */
#define ID_SPI0   (13) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1   (14) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_UART0  (15) /**< \brief UART 0 (UART0) */
#define ID_UART1  (16) /**< \brief UART 1 (UART1) */
#define ID_TC0    (17) /**< \brief Timer Counter 0 (TC0) */
#define ID_TC1    (17) /**< \brief 1 (TC1) */
#define ID_PWM0   (18) /**< \brief Pulse Width Modulation Controller (PWM0) */
#define ID_ADC    (19) /**< \brief ADC Controller (ADC) */
#define ID_DMAC0  (20) /**< \brief DMA Controller 0 (DMAC0) */
#define ID_DMAC1  (21) /**< \brief DMA Controller 1 (DMAC1) */
#define ID_UHPHS  (22) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS  (23) /**< \brief USB Device High Speed (UDPHS) */
#define ID_EMAC0  (24) /**< \brief Ethernet MAC (EMAC0) */
#define ID_ISI    (25) /**< \brief Image Sensor Interface (ISI) */
#define ID_LCDC   (25) /**< \brief LCD Controller (LCDC) */
#define ID_HSMCI1 (26) /**< \brief High Speed Multimedia Card Interface 1 (HSMCI1) */
#define ID_EMAC1  (27) /**< \brief Ethernet MAC 1 (EMAC1) */
#define ID_SSC0   (28) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_CAN0   (29) /**< \brief CAN controller 0 (CAN0) */
#define ID_CAN1   (30) /**< \brief CAN controller 1 (CAN1) */
#define ID_IRQ    (31) /**< \brief Advanced Interrupt Controller (IRQ) */

#define ID_PERIPH_COUNT (32) /**< \brief Number of peripheral IDs */

/*@}*/

/* ************************************************************************** */
/*   SLAVE MATRIX ID DEFINITIONS FOR SAM9xx5 */
/* ************************************************************************** */
/** \addtogroup SAM9xx5_matrix Matrix Ids Definitions */
/*@{*/

#define MX_SLAVE_SRAM            0    /**< Internal SRAM */
#define MX_SLAVE_ROM             1    /**< Internal ROM */
#define MX_SLAVE_SMD             2    /**< Soft Modem (SMD) */
#define MX_SLAVE_USB             3    /**< USB */
#define MX_SLAVE_EBI             4    /**< External Bus Interface */
#define MX_SLAVE_DDR_PORT1       5    /**< DDR Port 1 */
#define MX_SLAVE_DDR_PORT2       6    /**< DDR Port 2 */
#define MX_SLAVE_DDR_PORT3       7    /**< DDR Port 3 */
#define MX_SLAVE_APB0            8    /**< Peripheral Bridge 0*/
#define MX_SLAVE_APB1            9    /**< Peripheral Bridge 1*/

/*@}*/

/* ************************************************************************** */
/*   PMECC DEFINITIONS FOR SAM9xx5 */
/* ************************************************************************** */
/** \addtogroup SAM9xx5_pmecc PMECC Definitions */
/*@{*/

/** Address of Galois Field Table 512 mapping in ROM. */
#define GALOIS_TABLE_512_ROM_MAPPING (0x108000)

/** Address of Galois Field Table 1024 mapping in ROM. */
#define GALOIS_TABLE_1024_ROM_MAPPING (0x110000)

/*@}*/

/* ************************************************************************** */
/* INCLUDE FOR SAM9xx5 */
/* ************************************************************************** */

#include "chip_pins.h"

/** L1 data cache line size in bytes */
#define L1_CACHE_BYTES (32u)

/** L1 data cache line size in words */
#define L1_CACHE_WORDS (L1_CACHE_BYTES / sizeof(uint32_t))

/** Number of ways of L1 data cache */
#define L1_CACHE_WAYS (4)

/** Number of sets of L1 data cache */
#define L1_CACHE_SETS (128)

/** Build a set/way parameter for cache operations */
#define L1_CACHE_SETWAY(set, way) (((set) << 5) | ((way) << 30))

/** TC channel size (in bits) */
#define TC_CHANNEL_SIZE 32

/** CAN Interface max */
#define CAN_IFACE_COUNT (2)

/** TWI Interface max */
#ifndef TWI_IFACE_COUNT
#define TWI_IFACE_COUNT (3)
#endif

/** SPI Interface max */
#ifndef SPI_IFACE_COUNT
#define SPI_IFACE_COUNT (2)
#endif

/** USART Interface max */
#ifndef USART_IFACE_COUNT
#define USART_IFACE_COUNT (4)
#endif

/** EMAC Interface max */
#ifndef EMAC_IFACE_COUNT
#if defined(EMAC1)
#define EMAC_IFACE_COUNT (2)
#else
#define EMAC_IFACE_COUNT (1)
#endif
#endif

/** EMAC Queue max */
#ifndef EMAC_QUEUE_COUNT
#define EMAC_QUEUE_COUNT (1)
#endif

/** Ethernet Interface max */
#ifndef ETH_IFACE_COUNT
#define ETH_IFACE_COUNT (EMAC_IFACE_COUNT)
#endif

/** Ethernet Queue max */
#ifndef ETH_QUEUE_COUNT
#define ETH_QUEUE_COUNT (EMAC_QUEUE_COUNT)
#endif

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

/** Endpoints max paxcket size */
#define CHIP_USB_ENDPOINT_MAXPACKETSIZE(ep) \
   ((ep) == 0 ? 64 : 1024)

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINT_BANKS(ep) \
   ((ep) == 0 ? 1 : ((ep) < 3 ? 2 : 3))

/** Endpoints DMA support */
#define CHIP_USB_ENDPOINT_HAS_DMA(ep) \
    ((ep) > 0)

/** Endpoints High Band Width support */
#define CHIP_USB_ENDPOINT_IS_HBW(ep) \
    ((ep) != 0 || (ep) != 3 || (ep) != 4)

/** NAND EBI Chip Select */
#define NAND_EBI_CS 3

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Identify the chip model and return it as a string
 * \return a constant string containing the chip name
 */
extern const char* get_chip_name(void);

/**
 * \brief Return the default parameters used by the ROM-code for its console.
 * \param config a structure into which the function will write the serial
 * peripheral, the baudrate and the TX/RX pins. It will be all zeros if the
 * ROM-code console is disabled.
 */
extern void get_romcode_console(struct _console_cfg* config);

/** \brief Returns the matrix clock divider for the given peripheral
 *
 * \param id the Peripheral ID
 * \return the clock divider for the peripheral
 */
extern uint32_t get_peripheral_clock_matrix_div(uint32_t id);

/** \brief Returns the max clock frequency for the given peripheral
 *
 * \param id the Peripheral ID
 * \return the max clock frequency for the peripheral
 */
extern uint32_t get_peripheral_clock_max_freq(uint32_t id);

/** \brief Checks if the peripheral can be configured with a divided clock
 *
 * \param id the Peripheral ID
 * \return true if the peripheral can be configured with a divided clock, false
 * otherwise
 */
extern bool peripheral_has_clock_div(uint32_t id);

/** \brief Returns the DMAC interface number for a given peripheral
 *
 * \param id the Peripheral ID
 * \param dmac the DMAC controller instance
 * \param transmit a boolean, true for transmit, false for receive
 * \return the DMAC interface number or 0xff if none
 */
extern uint8_t get_peripheral_dma_channel(uint32_t id, Dmac *dmac,
					   bool transmit);

/** \brief Checks if a peripheral is usable with a DMAC controller
 *
 * \param id the Peripheral ID
 * \param dmac the DMAC controller instance
 * \return true if the peripheral is usable on the given DMAC controller,
 * false otherwise
 */
extern bool is_peripheral_on_dma_controller(uint32_t id, Dmac *dmac);

/** \brief Checks if a peripheral is configurable with divided clk
 *
 * \return true if the peripheral is configurable with a nonzero div
 * false non-configurable
 */
extern bool is_peripheral_configurable(uint32_t id);

#ifdef __cplusplus
}
#endif

#endif /* _CHIP_H_ */
