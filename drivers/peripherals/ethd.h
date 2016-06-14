/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/** \file */

/** \addtogroup eth_module
 * @{
 * Provides the interface to configure and use the ETH interface.
 *
 *
 * \sa \ref eth_module
 *
 * Related files:\n
 * eth.c\n
 * eth.h.\n
 *
 *   \defgroup ethd_defines ETH Defines
 *   \defgroup ethd_structs ETH Data Structs
 *   \defgroup ethd_functions ETH Functions
 */
/**@}*/

#ifndef _ETH_H_
#define _ETH_H_

#ifdef CONFIG_HAVE_ETH

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/
/** \addtogroup ethd_defines
	@{*/

enum _eth_duplex {
	ETH_DUPLEX_HALF = 0,
	ETH_DUPLEX_FULL = 1,
};

enum _eth_speed {
	ETH_SPEED_10M   = 0,
	ETH_SPEED_100M  = 1,
};

#define ETH_NUM_QUEUES 3

/** The MAC can support frame lengths up to 1536 bytes. */
#define ETH_MAX_FRAME_LENGTH 1536

/* Bits contained in struct _eth_desc addr when used for RX*/
#define ETH_RX_ADDR_OWN  (1u << 0)
#define ETH_RX_ADDR_WRAP (1u << 1)
#define ETH_RX_ADDR_MASK 0xfffffffcu

/* Bits contained in struct _eth_desc status when used for RX */
#define ETH_RX_STATUS_LENGTH_MASK 0x3fffu
#define ETH_RX_STATUS_SOF         (1u << 14)
#define ETH_RX_STATUS_EOF         (1u << 15)

/* Bits contained in struct _eth_desc status when used for TX */
#define ETH_TX_STATUS_LASTBUF (1u << 15)
#define ETH_TX_STATUS_WRAP    (1u << 30)
#define ETH_TX_STATUS_USED    (1u << 31)

/**@}*/

/** \addtogroup eth_buf_size ETH(EMACD/GMACD) Default Buffer Size
        @{*/
#define ETH_RX_UNITSIZE            128  /**< RX buffer size, must be 128 */
#define ETH_TX_UNITSIZE            1536 /**< TX buffer size, must be multiple
					   of 32 (cache line) */
/**     @}*/

/** \addtogroup eth_rc ETH(EMACD/GMACD) Return Codes
        @{*/
#define ETH_OK                0   /**< Operation OK */
#define ETH_TX_BUSY           1   /**< TX in progress */
#define ETH_RX_NULL           1   /**< No data received */
/** Buffer size not enough */
#define ETH_SIZE_TOO_SMALL    2
/** Parameter error, TX packet invalid or RX size too small */
#define ETH_PARAM             3
/** Transter is not initialized */
#define ETH_NOT_INITIALIZED   4

enum _eth_type {
	ETH_TYPE_EMAC,
	ETH_TYPE_GMAC,
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup ethd_structs
    @{*/

/** Transmit/Receive buffer descriptor struct */
struct _eth_desc {
	uint32_t addr;
	uint32_t status;
};

/** ETH scatter-gather entry */
struct _eth_sg {
	uint32_t        size;
	void           *buffer;
	struct _eth_sg *next;
};

/** ETH scatter-gather list */
struct _eth_sg_list {
	uint32_t        size;
	struct _eth_sg *entries;
};

/** @}*/

/** \addtogroup ethd_types
    @{*/

/** RX/TX callback */
typedef void (*ethd_callback_t)(uint8_t queue, uint32_t status);

/** TX Wakeup callback */
typedef void (*ethd_wakeup_cb_t)(uint8_t queue);

typedef void (*_ethd_configure)(void* ethd, Gmac *pHw, uint8_t enable_caf, uint8_t enable_nbc);

typedef uint8_t (*_ethd_setup_queue)(void* ethd, uint8_t queue,
		uint16_t rx_size, uint8_t* rx_buffer, struct _eth_desc* rx_desc,
		uint16_t tx_size, uint8_t* tx_buffer, struct _eth_desc* tx_desc,
		ethd_callback_t *tx_callbacks);

typedef void (*_ethd_start)(void* ethd);

typedef void (*_ethd_reset)(void* ethd);

typedef void (*_eth_set_mac_addr)(void* eth, uint8_t sa_idx, uint8_t* mac);

typedef void (*_eth_set_mac_addr32)(void* eth, uint8_t sa_idx, uint32_t mac_top, uint32_t mac_bottom);

typedef void (*_eth_set_mac_addr64)(void* eth, uint8_t sa_idx, uint64_t mac);

typedef void (*_eth_start_transmission)(void * eth);

typedef uint8_t (*_ethd_send_sg)(void* ethd, uint8_t queue, const struct _eth_sg_list* sgl, ethd_callback_t callback);

typedef uint8_t (*_ethd_send)(void* ethd, uint8_t queue, void *buffer, uint32_t size, ethd_callback_t callback);

typedef uint32_t (*_ethd_get_tx_load)(void* ethd, uint8_t queue);

typedef uint8_t (*_ethd_poll)(void* ethd, uint8_t queue, uint8_t* buffer, uint32_t buffer_size, uint32_t* recv_size);

typedef void (*_ethd_set_rx_callback)(void *ethd, uint8_t queue, ethd_callback_t callback);

typedef uint8_t (*_ethd_set_tx_wakeup_callback)(void *ethd, uint8_t queue, ethd_wakeup_cb_t wakeup_callback, uint16_t threshold);

/** @}*/

/** \addtogroup ethd_structs
	@{*/

struct _ethd_op {
	_ethd_configure configure;
	_ethd_setup_queue setup_queue;
	_ethd_start start;
	_ethd_reset reset;
	_eth_set_mac_addr set_mac_addr;
	_eth_set_mac_addr32 set_mac_addr32;
	_eth_set_mac_addr64 set_mac_addr64;
	_eth_start_transmission start_transmission;
	_ethd_send_sg send_sg;
	_ethd_send send;
	_ethd_poll poll;
	_ethd_set_rx_callback set_rx_callback;
	_ethd_set_tx_wakeup_callback set_tx_wakeup_callback;
};

struct _ethd_queue {
	uint8_t          *rx_buffer;
	struct _eth_desc *rx_desc;
	uint16_t          rx_size;
	uint16_t          rx_head;
	ethd_callback_t   rx_callback;

	uint8_t          *tx_buffer;
	struct _eth_desc *tx_desc;
	uint16_t          tx_size;
	uint16_t          tx_head;
	uint16_t          tx_tail;
	ethd_callback_t  *tx_callbacks;

	ethd_wakeup_cb_t tx_wakeup_callback;
	uint16_t         tx_wakeup_threshold;
};

/**
 * ETH driver struct.
 */
struct _ethd {
	union {
		void *addr;       /**< ETH instance (GMAC/EMAC) */
#if defined(CONFIG_HAVE_EMAC)
		Emac *emac;       /**< EMAC instance */
#endif
#if defined(CONFIG_HAVE_GMAC)
		Gmac *gmac;       /**< GMAC instance */
#endif
	};
	struct _ethd_queue queues[ETH_NUM_QUEUES];
	const struct _ethd_op *op;
};

/** @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup ethd_functions
	@{*/

extern void ethd_set_mac_addr(struct _ethd * ethd, uint8_t sa_idx, uint8_t* mac);

extern bool ethd_configure(struct _ethd * ethd, enum _eth_type eth_type, void * addr, uint8_t enable_caf, uint8_t enable_nbc);

extern uint8_t ethd_setup_queue(struct _ethd* ethd, uint8_t queue,
								uint16_t rx_size, uint8_t* rx_buffer, struct _eth_desc* rx_desc,
								uint16_t tx_size, uint8_t* tx_buffer, struct _eth_desc* tx_desc,
								ethd_callback_t *tx_callbacks);

/**
 * \brief Send a frame splitted into buffers. If the frame size is larger than transfer buffer size
 * error returned. If frame transfer status is monitored, specify callback for each frame.
 *  \param ethd Pointer to ETH Driver instance.
 *  \param sgl Pointer to a scatter-gather list describing the buffers of the ethernet frame.
 *  \param callback Pointer to callback function.
 */
extern uint8_t ethd_send_sg(struct _ethd* ethd, uint8_t queue, const struct _eth_sg_list* sgl, ethd_callback_t callback);

extern void ethd_start(struct _ethd* ethd);

/**
 * \brief Send a packet with ETH. If the packet size is larger than transfer buffer size
 * error returned. If packet transfer status is monitored, specify callback for each packet.
 *  \param ethd Pointer to ETH Driver instance.
 *  \param buffer   The buffer to be send
 *  \param size     The size of buffer to be send
 *  \param callback Threshold Wakeup callback
 *  \return         OK, Busy or invalid packet
 */
extern uint8_t ethd_send(struct _ethd* ethd, uint8_t queue, void *buffer, uint32_t size, ethd_callback_t callback);

extern uint32_t ethd_get_tx_load(struct _ethd* ethd, uint8_t queue);

/**
 * \brief Receive a packet with ETH.
 * If not enough buffer for the packet, the remaining data is lost but right
 * frame length is returned.
 *  \param ethd Pointer to ETH Driver instance.
 *  \param buffer           Buffer to store the frame
 *  \param buffer_size      Size of the frame
 *  \param recv_size        Received size
 *  \return                 OK, no data, or frame too small
 */
extern uint8_t ethd_poll(struct _ethd* ethd, uint8_t queue, uint8_t* buffer, uint32_t buffer_size, uint32_t* recv_size);

extern void ethd_set_rx_callback(struct _ethd *ethd, uint8_t queue, ethd_callback_t callback);

/**
 * Register/Clear TX wakeup callback.
 *
 * When ethd_send() returns ETH_TX_BUSY (all TD busy) the application
 * task calls ethd_set_tx_wakeup_callback() to register fWakeup() callback and
 * enters suspend state. The callback is in charge to resume the task once
 * several TD have been released. The next time ethd_send() will be called,
 * it shall be successful.
 *
 * This function is usually invoked with NULL callback from the TX wakeup
 * callback itself, to unregister. Once the callback has resumed the
 * application task, there is no need to invoke the callback again.
 *
 * \param ethd   Pointer to ETH Driver instance.
 * \param callback  Wakeup callback.
 * \param threshold Number of free TD before wakeup callback invoked.
 * \return ETH_OK, ETH_PARAM on parameter error.
 */
extern uint8_t ethd_set_tx_wakeup_callback(struct _ethd* ethd, uint8_t queue, ethd_wakeup_cb_t callback, uint16_t threshold);

/** @}*/

#ifdef __cplusplus
}
#endif

#endif

#endif /* #ifndef _ETH_H_ */
