/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2018, Atmel Corporation                                        */
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

#include "compiler.h"

#if defined(CONFIG_CHIP_SAM9X60)
  #include "sam9x60.h"
#else
  #error Library does not support the specified device.
#endif
#include "chip_common.h"

/* forward declaration */
struct _console_cfg;

/* ************************************************************************** */
/*   CHIPID DEFINITIONS FOR SAM9x60 */
/* ************************************************************************** */
/** \addtogroup SAM9x60_chipid CHIPID Definitions */
/*@{*/

#define CHIPID_CIDR_SAM9X60     (0x819b35a0ul)

/*@}*/

/* ************************************************************************** */
/*   PMECC DEFINITIONS FOR SAM9x60 */
/* ************************************************************************** */
/** \addtogroup SAM9x60_pmecc PMECC Definitions */
/*@{*/

/** Address of Galois Field Table 512 mapping in ROM. */
#define GALOIS_TABLE_512_ROM_MAPPING (0x00100000)

/** Address of Galois Field Table 1024 mapping in ROM. */
#define GALOIS_TABLE_1024_ROM_MAPPING (0x00108000)

/*@}*/

/* Interface ID for DMA trigger with TC compareA or TC compareC */
#define ID_TC1_CPA   43
#define ID_TC4_CPA   44
#define ID_TC1_CPB   45
#define ID_TC4_CPB   46
#define ID_TC1_CPC   47
#define ID_TC4_CPC   48
#define ID_TC1_EXT   49
#define ID_TC4_EXT   50

/* ************************************************************************** */
/* INCLUDE FOR SAM9x60 */
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
#define EMAC_IFACE_COUNT (2)
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

/** FLEXCOM USART FIFO depth */
#define FLEXCOM_USART_FIFO_DEPTH (16u)

/** FLEXCOM SPI FIFO depth */
#define FLEXCOM_SPI_FIFO_DEPTH (16u)

/** CAN Interface max */
#define CAN_IFACE_COUNT (2)

/** SPI FIFO depth */
#define SPI_FIFO_DEPTH (16u)

/** TWI FIFO depth */
#define TWI_FIFO_DEPTH (16u)

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

/** MPDDRC I/O calibration delay, in ns */
#define MPDDRC_TZQIO_DELAY 600

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
    ((ep) > 2)

/** Default ISO IN Endpoint for High Band Width Streaming */
#define ISO_IN_EP   4

/** NAND EBI Chip Select */
#define NAND_EBI_CS 3

#define PLL_ID_PLLA 0
#define PLL_ID_UPLL 1

#define OTPC_EMUL_ADDR IRAM1_ADDR
#define OTPC_EMUL_SIZE (0x00001000u)

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

/** \brief Returns the XDMAC interface number for a given peripheral
 *
 * \param id the Peripheral ID
 * \param xdmac the XDMAC controller instance
 * \param transmit a boolean, true for transmit, false for receive
 * \return the XDMAC interface number or 0xff if none
 */
extern uint8_t get_peripheral_dma_channel(uint32_t id, Xdmac *xdmac, bool transmit);

/** \brief Checks if a peripheral is usable with a XDMAC controller
 *
 * \param id the Peripheral ID
 * \param xdmac the XDMAC controller instance
 * \return true if the peripheral is usable on the given XDMAC controller,
 * false otherwise
 */
extern bool is_peripheral_on_dma_controller(uint32_t id, Xdmac *xdmac);

/** \brief Checks if a peripheral is configurable with divided clk
 *
 * \return true if the peripheral is configurable with a nonzero div
 * false non-configurable
 */
extern bool is_peripheral_configurable(uint32_t id);


/** \brief Retrive peripheral FIFO size from its base address
 *
 * \param addr the Peripheral base addr
 * \return Size in number of data of the peripherals FIFO if
 * available, negative value otherwise.
 */
extern int32_t get_peripheral_fifo_depth(void* addr);
#ifdef __cplusplus
}
#endif

#endif /* _CHIP_H_ */
