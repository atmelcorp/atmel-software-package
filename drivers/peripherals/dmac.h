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

/** \addtogroup dmac_module Working with DMAC
 *
 * \section Usage
 * <ul>
 * <li> Enable or disable DMAC channel with DMAC_EnableChannel() and DMAC_EnableChannels() or DMAC_DisableChannel() and DMAC_DisableChannels().</li>
 * <li> Enable or disable %DMA interrupt using DMAC_EnableGIt() and DMAC_EnableChannelIt() or DMAC_DisableGIt() and DMAC_DisableChannelIt().</li>
 * <li> Get %DMA interrupt status by DMAC_GetChannelIsr() and DMAC_GetMaskChannelIsr().</li>
 * <li> Enable or disable specified %DMA channel with DMAC_EnableChannel() or DMAC_DisableChannel().</li>
 * <li> Suspend or resume specified %DMA channel with DMAC_SuspendReadChannel(), DMAC_SuspendWriteChannel() and DMAC_SuspendReadWriteChannel() or DMAC_ResumeReadWriteChannel().</li>
 * <li> Get %DMA channel status by DMAC_GetGlobalChStatus().</li>
 * <li> Configure source and/or destination start address with DMAC_SetSourceAddr() and/or DMAC_SetDestinationAddr().</li>
 * <li> Set %DMA descriptor address using DMAC_SetDescriptorAddr().</li>
 * <li> Configure source and destination memory pattern with DMAC_SetDataStride_MemPattern().</li>
 * <li> Configure source or destination Microblock stride with DMAC_SetSourceMicroBlockStride() or DMAC_SetDestinationMicroBlockStride().</li>
 * </ul>
 *
 * For more accurate information, please look at the DMAC section of the
 * Datasheet.
 *
 * \sa \ref dmad_module
 *
 * Related files :\n
 * \ref dmac.c\n
 * \ref dmac.h\n
 *
 */

#ifndef _DMAC_H_
#define _DMAC_H_

#ifdef CONFIG_HAVE_DMAC

/**@{*/

/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup dmac_defines DMAC Definitions
 *      @{
 */

/** Number of DMA channels */
#define DMAC_CONTROLLERS 2

/** Number of DMA channels */
#define DMAC_CHANNELS (DMACCH_NUM_NUMBER)

/** Max DMA single transfer size */
#define DMAC_MAX_BT_SIZE 0xFFFF

/**     @}*/

/*----------------------------------------------------------------------------
 *         Macro
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

/** \addtogroup dmac_functions DMAC Functions
 *      @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get the DMAC peripheral instance with given index
 *
 * \param index Index of DMAC instance.
 */
extern Dmac *dmac_get_instance(uint32_t index);

/**
 * \brief Get the DMAC peripheral ID for a given DMAC instance
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_periph_id(Dmac *dmac);

/**
 * \brief Enable DMA controller for a given DMAC instance
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern void dmac_enable(Dmac *dmac);

/**
 * \brief Disable DMA controller for a given DMAC instance
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern void dmac_disable(Dmac *dmac);

/**
 * \brief Get DMAC global configuration.
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_config(Dmac *dmac);

/**
 * \brief Enables DMAC global Error, buffer transfer and chained buffer
 *  transfer interrupt.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param int_mask IT to be enabled.
 */
extern void dmac_enable_global_it(Dmac *dmac, uint32_t int_mask);

/**
 * \brief Disables DMAC global Error, buffer transfer and chained buffer
 *  transfer interrupt.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param int_mask IT to be enabled
 */
extern void dmac_disable_global_it(Dmac *dmac, uint32_t int_mask);

/**
 * \brief Get DMAC global Error, buffer transfer and chained buffer
 *  transfer mask register.
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_global_it_mask(Dmac *dmac);

/**
 * \brief Get DMAC global Error, buffer transfer and chained buffer
 *  transfer status register.
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_global_isr(Dmac *dmac);

/**
 * \brief Get DMAC masked Error, buffer transfer and chained buffer
 *  transfer interrupt status.
 *
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_masked_global_isr(Dmac *dmac);

/**
 * \brief enables the relevant channel of given DMAC.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 */
extern void dmac_enable_channel(Dmac *dmac, uint8_t channel);

/**
 * \brief enables the relevant channels of given DMAC.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
extern void dmac_enable_channels(Dmac *dmac, uint8_t channel_mask);

/**
 * \brief Disables the relevant channel of given DMAC.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 */
extern void dmac_disable_channel(Dmac *dmac, uint8_t channel);

/**
 * \brief Disables the relevant channels of given DMAC.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
extern void dmac_disable_channels(Dmac *dmac, uint8_t channel_mask);

/**
 * \brief Get Global channel status of given DMAC.
 * \param dmac Pointer to the DMAC instance.
 */
extern uint32_t dmac_get_channel_status(Dmac *dmac);

/**
 * \brief Clear auto bit of the relevant channel of given DMAC.
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
 
/**
 * \brief Clear automatic bit of the relevant channel of given DMAC.
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
extern void dmac_auto_clear(Dmac *dmac, uint8_t channel);

/**
 * \brief Check if automatic multiple buffer transfer is set of
 * of the relevant channel of given DMAC.
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
extern bool is_dmac_auto_transfer(Dmac *dmac, uint8_t channel);

/**
 * \brief Resumes the relevant channel of given DMAC.
 * \param dmac Pointer to the DMAC instance.
 * \param channel_mask Channels bitmap.
 */
extern void dmac_resume_channel(Dmac *dmac, uint8_t channel);
/**
 * \brief software single request the relevant channel.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 */
extern void dmac_software_single_request(Dmac *dmac, uint8_t channel);

/**
 * \brief software chunk transfer request the relevant channel.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 */
extern void dmac_software_chunk_transfer_request(Dmac *dmac, uint8_t channel);

/**
 * \brief Set source address for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param addr Source address.
 */
extern void dmac_set_src_addr(Dmac *dmac, uint8_t channel, void *addr);

/**
 * \brief Set destination address for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param addr Destination address.
 */
extern void dmac_set_dest_addr(Dmac *dmac, uint8_t channel, void *addr);

/**
 * \brief Get source address for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \return source address
 */
extern uint32_t dmac_get_channel_src_addr(Dmac *dmac, uint8_t channel);

/**
 * \brief Get destination address for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \return destination address
 */
extern uint32_t dmac_get_channel_dest_addr(Dmac *dmac, uint8_t channel);

/**
 * \brief Set next descriptor's address & interface for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param addr Address of next descriptor.
 * \param nda Next Descriptor Interface.
 */
extern void dmac_set_descriptor_addr(Dmac *dmac, uint8_t channel, void *addr, uint32_t ndaif);


/**
 * \brief Set control A register for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param config Channel configuration.
 */
extern void dmac_set_control_a(Dmac *dmac, uint8_t channel, uint32_t config);

/**
 * \brief Set control B register for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param config Channel configuration.
 */
extern void dmac_set_control_b(Dmac *dmac, uint8_t channel, uint32_t config);

/**
 * \brief Set configuration for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param config Channel configuration.
 */
extern void dmac_set_channel_config(Dmac *dmac, uint8_t channel, uint32_t config);

/**
 * \brief Get the relevant channel's configuration of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 */
extern uint32_t dmac_get_channel_config(Dmac *dmac, uint8_t channel);

/**
 * \brief Set source Picture-in-Picture configuration for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param pip source pip config.
 */
extern void dmac_set_src_pip(Dmac *dmac, uint8_t channel,
			       uint32_t pip);

/**
 * \brief Set destination Picture-in-Picture configuration for the relevant channel of given DMA.
 *
 * \param dmac Pointer to the DMAC instance.
 * \param channel Particular channel number.
 * \param pip destination pip config.
 */ 
extern void dmac_set_des_pip(Dmac *dmac, uint8_t channel,
			       uint32_t pip);


#ifdef __cplusplus
}
#endif

/**     @}*//**@}*/

#endif /* CONFIG_HAVE_DMAC */

#endif /* _DMAC_H_ */
