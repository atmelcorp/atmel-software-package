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

#ifndef _MCAND_H_
#define _MCAND_H_
/**@{*/
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "can/mcan.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _cand_ram_item {
	struct _buffer *buf;
	struct _callback cb;
	uint8_t state;
};

enum _mcan_ram {
	MCAN_RAM_STD_FILTER = 0,   /* 11-bit Message ID Rx Filters */
	MCAN_RAM_EXT_FILTER = 4,   /* 29-bit Message ID Rx Filters */
	MCAN_RAM_RX_FIFO0   = 6,   /* Rx Buffers in Rx FIFO 0 */
	MCAN_RAM_RX_FIFO1   = 8,   /* Rx Buffers in Rx FIFO 1 */
	MCAN_RAM_RX_BUFFER  = 10,  /* dedicated Rx Buffers */
	MCAN_RAM_TX_EVENT   = 12,  /* Tx Event Elements in the Tx Event FIFO */
	MCAN_RAM_TX_BUFFER  = 13,  /* dedicated Tx Buffers */
	MCAN_RAM_TX_FIFO    = 14,  /* Tx Buffers in the Tx FIFO or Tx Queue */
	MCAN_RAM_TOTAL      = 15,
};

struct mcan_config
{
	uint32_t *msg_ram[2];           /* base address of the Message RAM to be
					 * assigned to this MCAN instance */
	uint32_t ram_size[2];
	uint8_t item_count[MCAN_RAM_TOTAL];
	uint32_t ram_status[MCAN_RAM_TOTAL];
	uint32_t ram_index[MCAN_RAM_TOTAL];

	uint8_t buf_size_rx_fifo0;      /* size of the data field in each Rx
					 * Buffer of Rx FIFO 0, in bytes */
	uint8_t buf_size_rx_fifo1;      /* size of the data field in each Rx
					 * Buffer of Rx FIFO 1, in bytes */
	uint8_t buf_size_rx;            /* size of the data field in each
					 * dedicated Rx Buffer, in bytes */
	uint8_t buf_size_tx;            /* size of the data field in each Tx
					 * Buffer, in bytes. Applies to all Tx
					 * Buffers, dedicated and in Tx FIFO /
					 * Queue. */
};

/* This structure is private to the MCAN Driver.
 * Allocate it but ignore its members. */
struct mcan_set
{
	struct mcan_config cfg;
	uint32_t *ram_filt_std;
	uint32_t *ram_filt_ext;
	uint32_t *ram_fifo_rx0;
	uint32_t *ram_fifo_rx1;
	uint32_t *ram_array_rx;
	uint32_t *ram_fifo_tx_evt;
	uint32_t *ram_array_tx;
};

struct _mcan_desc {
	Mcan* addr;            /**< Pointer to HW register base */
	uint32_t freq;         /**< Current working baudrate */
	uint32_t freq_fd;

	uint32_t identifier;
	uint32_t mask;

	uint8_t bState;             /**< CAN states */

	struct _cand_ram_item * ram_item;
	struct mcan_set set;
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern struct _mcan_desc* mcand_get_desc(Mcan * mcan_if);
extern int mcand_configure(struct _mcan_desc* desc);

/**
 * Configure the CAN Mailbox for message transfer.
 * \param desc Pointer to CAN Driver descriptor instance.
 * \param buf  Pointer to buffer to transfer.
 * \param cb   Pointer to call back structure.
 */
extern int mcand_transfer(struct _mcan_desc* desc, struct _buffer *buf,
			  struct _callback* cb);
/**@}*/
#endif /* #ifndef _MCAN_H_ */
