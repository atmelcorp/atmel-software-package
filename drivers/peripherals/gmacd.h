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

/** \addtogroup gmacd_module
 * @{
 * Implement GMAC data transfer and PHY management functions.
 *
 * \section Usage
 * -# Initialize the instance with gmacd_configure() and gmacd_setup_queue(),
 *    so that GMAC data can be transmitted/received.
 * -# Some management callbacks can be set by gmacd_set_rx_callback()
 *    and ethd_set_tx_wakeup_callback().
 * -# Send ethernet packets using ethd_send(), ethd_get_tx_load() is used
 *    to get the free space in TX queue.
 * -# Check and obtain received ethernet packets via ethd_poll().
 *
 * \sa \ref gmacb_module, \ref gmac_module
 *
 * Related files:\n
 * \ref gmacd.c\n
 * \ref gmacd.h.\n
 *
 *  \defgroup gmacd_defines GMAC Driver Defines
 *  \defgroup gmacd_types GMAC Driver Types
 *  \defgroup gmacd_functions GMAC Driver Functions
 */
/**@}*/

#ifndef _GMACD_H_
#define _GMACD_H_

#ifdef CONFIG_HAVE_GMAC
/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "peripherals/gmac.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/
/** \addtogroup gmacd_defines
    @{*/

/** @}*/

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/
/** \addtogroup gmacd_types
    @{*/

/** @}*/

/*---------------------------------------------------------------------------
 *         GMAC Exported variables
 *---------------------------------------------------------------------------*/

extern const struct _ethd_op _gmac_op;

/** \addtogroup gmacd_functions
    @{*/

/*---------------------------------------------------------------------------
 *         GMAC Exported functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern void gmacd_configure(struct _ethd* gmacd, Gmac *pHw, uint8_t enableCAF, uint8_t enableNBC);

extern uint8_t gmacd_setup_queue(struct _ethd* gmacd, uint8_t queue,
		uint16_t rx_size, uint8_t* rx_buffer, struct _eth_desc* rx_desc,
		uint16_t tx_size, uint8_t* tx_buffer, struct _eth_desc* tx_desc,
		ethd_callback_t *tx_callbacks);

extern void gmacd_start(struct _ethd* gmacd);

extern void gmacd_reset(struct _ethd* gmacd);

extern uint8_t gmacd_send_sg(struct _ethd* gmacd, uint8_t queue,
		const struct _eth_sg_list* sgl, ethd_callback_t callback);

extern uint8_t gmacd_send(struct _ethd* gmacd, uint8_t queue, void *buffer,
		uint32_t size, ethd_callback_t callback);

extern uint32_t gmacd_get_tx_load(struct _ethd* gmacd, uint8_t queue);

extern uint8_t gmacd_poll(struct _ethd* gmacd, uint8_t queue,
		uint8_t* buffer, uint32_t buffer_size, uint32_t* recv_size);

extern void gmacd_set_rx_callback(struct _ethd *gmacd, uint8_t queue,
		ethd_callback_t callback);

/** @}*/

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_GMAC */

#endif /* _GMACD_H_ */
