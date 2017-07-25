/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
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
/*                                                                              */

#ifndef _CHIP_H_
#define _CHIP_H_

#include <stdint.h>
#include <stdbool.h>

#include "sama5d3.h"
#include "chip_common.h"

/* forward declaration */
struct _console_cfg;

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_id Peripheral Ids Definitions */
/*@{*/

#define ID_FIQ    ( 0) /**< \brief Advanced Interrupt Controller (FIQ) */
#define ID_SYSC   ( 1) /**< \brief System Controller Interrupt (SYSC) */
#define ID_RTC    ( 1) /**< \brief Real Time Clock (RTC) */
#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) */
#define ID_DBGU   ( 2) /**< \brief Debug Unit Interrupt (DBGU) */
#define ID_PIT    ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT    ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_SMC    ( 5) /**< \brief Static Memory Controller (SMC) */
#define ID_PIOA   ( 6) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB   ( 7) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC   ( 8) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_PIOD   ( 9) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_PIOE   (10) /**< \brief Parallel I/O Controller E (PIOE) */
#define ID_SMD    (11) /**< \brief SMD Soft Modem (SMD) */
#define ID_USART0 (12) /**< \brief USART 0 (USART0) */
#define ID_USART1 (13) /**< \brief USART 1 (USART1) */
#define ID_USART2 (14) /**< \brief USART 2 (USART2) */
#define ID_USART3 (15) /**< \brief USART 3 (USART3) */
#define ID_UART0  (16) /**< \brief UART 0 (UART0) */
#define ID_UART1  (17) /**< \brief UART 1 (UART1) */
#define ID_TWI0   (18) /**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1   (19) /**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_TWI2   (20) /**< \brief Two-Wire Interface 2 (TWI2) */
#define ID_HSMCI0 (21) /**< \brief High Speed Multimedia Card Interface 0 (HSMCI0) */
#define ID_HSMCI1 (22) /**< \brief High Speed Multimedia Card Interface 1 (HSMCI1) */
#define ID_HSMCI2 (23) /**< \brief High Speed Multimedia Card Interface 2 (HSMCI2) */
#define ID_SPI0   (24) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1   (25) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_TC0    (26) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1    (27) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_PWM0   (28) /**< \brief Pulse Width Modulation Controller (PWM0) */
#define ID_ADC    (29) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_DMAC0  (30) /**< \brief DMA Controller 0 (DMAC0) */
#define ID_DMAC1  (31) /**< \brief DMA Controller 1 (DMAC1) */
#define ID_UHPHS  (32) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS  (33) /**< \brief USB Device High Speed (UDPHS) */
#define ID_GMAC0  (34) /**< \brief Gigabit Ethernet MAC (GMAC) */
#define ID_EMAC0  (35) /**< \brief Ethernet MAC (EMAC) */
#define ID_LCDC   (36) /**< \brief LCD Controller (LCDC) */
#define ID_ISI    (37) /**< \brief Image Sensor Interface (ISI) */
#define ID_SSC0   (38) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1   (39) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_CAN0   (40) /**< \brief CAN controller 0 (CAN0) */
#define ID_CAN1   (41) /**< \brief CAN controller 1 (CAN1) */
#define ID_SHA    (42) /**< \brief Secure Hash Algorithm (SHA) */
#define ID_AES    (43) /**< \brief Advanced Encryption Standard (AES) */
#define ID_TDES   (44) /**< \brief Triple Data EncryptionStandard (TDES) */
#define ID_TRNG   (45) /**< \brief True Random Number Generator (TRNG) */
#define ID_ARM    (46) /**< \brief Performance Monitor Unit (ARM) */
#define ID_AIC    (47) /**< \brief Advanced Interrupt Controller (IRQ) */
#define ID_FUSE   (48) /**< \brief Fuse Controller (FUSE) */
#define ID_MPDDRC (49) /**< \brief MPDDR controller (MPDDRC) */

#define ID_PERIPH_COUNT (50) /**< \brief Number of peripheral IDs */

/*@}*/

/* ************************************************************************** */
/*   SLAVE MATRIX ID DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_matrix Matrix Ids Definitions */
/*@{*/

#define MX_SLAVE_SRAM0     ( 0) /**< Internal SRAM0 */
#define MX_SLAVE_SRAM1     ( 1) /**< Internal SRAM1 */
#define MX_SLAVE_NFC_SRAM  ( 2) /**< NFC SRAM */
#define MX_SLAVE_ROM       ( 3) /**< Internal ROM */
#define MX_SLAVE_SMD       ( 4) /**< Soft Modem (SMD) */
#define MX_SLAVE_USB       ( 5) /**< USB */
#define MX_SLAVE_EBI       ( 6) /**< External Bus Interface / NFC */
#define MX_SLAVE_DDR_PORT0 ( 7) /**< DDR Port 0 */
#define MX_SLAVE_DDR_PORT1 ( 8) /**< DDR Port 1 */
#define MX_SLAVE_DDR_PORT2 ( 9) /**< DDR Port 2 */
#define MX_SLAVE_DDR_PORT3 (10) /**< DDR Port 3 */
#define MX_SLAVE_APB0      (11) /**< APB0 - User interfaces */
#define MX_SLAVE_APB1      (12) /**< APB1 - User interfaces */

/*@}*/

/* ************************************************************************** */
/*   PMECC DEFINITIONS FOR SAMA5D3x */
/* ************************************************************************** */
/** \addtogroup SAMA5D3x_pmecc PMECC Definitions */
/*@{*/

/** Address of Galois Field Table 512 mapping in ROM. */
#define GALOIS_TABLE_512_ROM_MAPPING (0x110000)

/** Address of Galois Field Table 1024 mapping in ROM. */
#define GALOIS_TABLE_1024_ROM_MAPPING (0x118000)

/*@}*/

/* ************************************************************************** */
/* INCLUDE FOR SAMA5D3x */
/* ************************************************************************** */

#include "chip_pins.h"

/** L1 data cache line size in bytes */
#define L1_CACHE_BYTES (32u)

/** L1 data cache line size in words */
#define L1_CACHE_WORDS (L1_CACHE_BYTES / sizeof(uint32_t))

/** Number of ways of L1 data cache */
#define L1_CACHE_WAYS (4)

/** Number of sets of L1 data cache */
#define L1_CACHE_SETS (256)

/** Build a set/way parameter for cache operations */
#define L1_CACHE_SETWAY(set, way) (((set) << 5) | ((way) << 30))

/** TC channel size (in bits) */
#define TC_CHANNEL_SIZE 32

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

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

/** GMAC Interface max */
#ifndef GMAC_IFACE_COUNT
#define GMAC_IFACE_COUNT (1)
#endif

/** GMAC Queue max */
#ifndef GMAC_QUEUE_COUNT
#define GMAC_QUEUE_COUNT (1)
#endif

/** EMAC Interface max */
#ifndef EMAC_IFACE_COUNT
#define EMAC_IFACE_COUNT (1)
#endif

/** EMAC Queue max */
#ifndef EMAC_QUEUE_COUNT
#define EMAC_QUEUE_COUNT (1)
#endif

/** Ethernet Interface max */
#ifndef ETH_IFACE_COUNT
#define ETH_IFACE_COUNT (EMAC_IFACE_COUNT + GMAC_IFACE_COUNT)
#endif

/** Ethernet Queue max */
#ifndef ETH_QUEUE_COUNT
#define ETH_QUEUE_COUNT (EMAC_QUEUE_COUNT + GMAC_QUEUE_COUNT)
#endif

/** MPDDRC I/O Calibration Delay (in nanoseconds) */
#define MPDDRC_TZQIO_DELAY (20)

/** Endpoints max paxcket size */
#define CHIP_USB_ENDPOINT_MAXPACKETSIZE(ep) \
   ((ep) == 0 ? 64 : 1024)

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINT_BANKS(ep) \
   ((ep) == 0 ? 1 : ((ep) < 3 ? 3 : 2))

/** Endpoints DMA support */
#define CHIP_USB_ENDPOINT_HAS_DMA(ep) \
    ((ep) > 0 && ((ep) < 7))

/** Endpoints High Band Width support */
#define CHIP_USB_ENDPOINT_IS_HBW(ep) \
    ((ep) == 1 || (ep) == 2)

/** NAND EBI Chip Select */
#define NAND_EBI_CS 3

#define GMAC_UR_RMII GMAC_UR_RGMII

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
 * \param xdmac the DMAC controller instance
 * \param transmit a boolean, true for transmit, false for receive
 * \return the DMAC interface number or 0xff if none
 */
extern uint8_t get_peripheral_dma_channel(uint32_t id, Dmac *dmac,
					   bool transmit);

/** \brief Checks if a peripheral is usable with a DMAC controller
 *
 * \param id the Peripheral ID
 * \param xdmac the DMAC controller instance
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
