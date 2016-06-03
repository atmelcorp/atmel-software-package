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

/**
 * \file
 *
 * Interface for Synchronous Serial (SSC) controller.
 *
 */

#ifndef _SSC_
#define _SSC_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Define
 *----------------------------------------------------------------------------*/
/* Send data on Frame changes */
#define I2S_SLAVE_TX_SETTING(nb_bit_by_slot, nb_slot_by_frame)(\
                             (SSC_TCMR_CKS_TK) |\
                             (SSC_TCMR_CKO_NONE) |\
							(SSC_TCMR_START_TF_FALLING) |\
                             (SSC_TCMR_STTDLY(1)) |\
                             (SSC_TCMR_PERIOD(0)))
/* Send 1 data each time */
#define I2S_SLAVE_TX_FRM_SETTING(nb_bit_by_slot, nb_slot_by_frame)( \
                                 (SSC_TFMR_DATLEN(nb_bit_by_slot - 1)) |\
                                 (SSC_TFMR_MSBF) |\
                                 (SSC_TFMR_DATNB(nb_slot_by_frame - 1)) |\
                                 (SSC_TFMR_FSOS_NONE))
/* Read data on Frame changes */
#define I2S_SLAVE_RX_SETTING(nb_bit_by_slot, nb_slot_by_frame)(\
                            (SSC_RCMR_CKS_TK) |\
                            (SSC_RCMR_CKO_NONE) |\
							  (SSC_RCMR_CKI) |\
                            (SSC_RCMR_START_RF_FALLING) |\
                            (SSC_RCMR_STTDLY(1)) |\
                            (SSC_RCMR_PERIOD(0)))
/* Read 1 data each time */
#define I2S_SLAVE_RX_FRM_SETTING(nb_bit_by_slot, nb_slot_by_frame)( \
                                 (SSC_RFMR_DATLEN(nb_bit_by_slot - 1)) |\
                                 (SSC_RFMR_MSBF) |\
                                 (SSC_RFMR_DATNB(nb_slot_by_frame - 1)) |\
                                 (SSC_RFMR_FSOS_NONE))

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/**
 * Configuration setting structure.
 */

struct _ssc_desc {
	Ssc *addr;
	/* Master Clock */
	uint32_t bit_rate;
	/* Sample Frequency (fs) Ratio */
	uint32_t sample_rate;
	/* Number of bits of the slot */
 	uint8_t  slot_length;
	/* Number of slot per frame */
 	uint8_t  slot_num;
	/* tx channel enable */
	bool tx_auto_cfg;
	/* rx channel enable */
	bool rx_auto_cfg;

};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
extern void ssc_configure(struct _ssc_desc* desc);
extern void ssc_configure_transmitter(struct _ssc_desc* desc, uint32_t tcmr,
					uint32_t tfmr);
extern void ssc_configure_receiver(struct _ssc_desc* desc, uint32_t rcmr,
					uint32_t rfmr);
extern void ssc_enable_transmitter(struct _ssc_desc* desc);
extern void ssc_disable_transmitter(struct _ssc_desc* desc);
extern void ssc_enable_receiver(struct _ssc_desc* desc);
extern void ssc_disable_receiver(struct _ssc_desc* desc);
extern void ssc_enable_interrupts(struct _ssc_desc* desc, uint32_t sources);
extern void ssc_disable_interrupts(struct _ssc_desc* desc, uint32_t sources);
extern void ssc_write(struct _ssc_desc* desc, uint32_t frame);
extern uint32_t ssc_read(struct _ssc_desc* desc);
extern uint8_t ssc_is_rx_ready(struct _ssc_desc* desc);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef _SSC_ */
