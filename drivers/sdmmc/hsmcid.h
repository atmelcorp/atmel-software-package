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

/** \addtogroup hsmci_module Working with HSMCI
 *  \ingroup hsmcid_module
 *
 * \section Purpose
 *
 * The HSMCI driver provides an application programming interface that can be
 * used to get benefit of the HSMCI peripheral.
 *
 * \sa \ref mcid_module
 *
 * Related files:\n
 * \ref hsmcid.h\n
 * \ref hsmcid.c\n
 * \ref hsmci.h\n
 * \ref hsmci.c.\n
 */

#ifndef _HSMCID_PERIPH_H_
#define _HSMCID_PERIPH_H_
/** \addtogroup hsmci_module
 * @{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "mutex.h"
#include "gpio/pio.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _dma_channel;
struct _SdmmcCommand;

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

struct _hsmci_set;

struct _hsmci_ops {
	bool (*get_card_detect_status)(uint32_t periph_id);
	bool (*set_card_power)(uint32_t periph_id, bool power);
};

struct _hsmci_cfg {
	uint32_t periph_id;    /* HSMCI peripheral ID (ID_HSMCIx) */
	uint8_t slot;          /* HSMCI slot ID (0..3 for A..D) */
	struct _pin wp_pin;    /* HSMCI write protection pin */
	bool use_polling;      /* Use interrupts if false, otherwise only use polling */
	struct _hsmci_ops ops; /* Function pointers for power control and card detect */
};

/* This structure is private to the HSMCI Driver.
 * Allocate it but ignore its members. */
struct _hsmci_set {
	uint32_t id;                  /* HSMCI peripheral ID (ID_HSMCIx) */
	struct _pin wp_pin;           /* HSMCI write protection pin */
	Hsmci *regs;                  /* set of HSMCI hardware registers */
	struct _hsmci_ops ops;
	struct _dma_channel *dma_tx_channel;
	struct _dma_channel *dma_rx_channel;
	uint32_t nxt_evts;            /* HSMCI IRQs we're still waiting for */
	uint32_t dwXfrNdx;            /* DMA transferred data index (bytes) */
	uint32_t dwXSize;             /* DMA transfer size (bytes) */
	bool use_polling;             /* polling mode */
	uint32_t dev_freq;            /* frequency of clock provided to memory
	                               * device, in Hz */
	uint8_t tim_mode;             /* timing mode aka bus speed mode */
	volatile uint8_t state;
	struct _SdmmcCommand *cmd;    /* pointer to the command being processed */
	uint16_t blk_index;           /* count of data blocks tranferred already,
	                               * in the context of the command and data
	                               * transfer being executed */
	uint8_t resp_len;             /* size of the response, once retrieved,
	                               * in the context of the command being
	                               * executed, expressed in 32-bit words */
	mutex_t dma_unlocks_mutex;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup hsmci_functions HSMCI Functions
 *      @{
 */

/**
 * \brief Initialize the specified driver instance and the associated HSMCI
 * peripheral.
 * \param set Pointer to uninitialized driver instance data.
 * \param config Pointer to driver configuration
 * value.
 */
extern bool hsmci_initialize(struct _hsmci_set* set, const struct _hsmci_cfg* config);

/**     @} */


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* #ifndef _HSMCID_PERIPH_H_ */
