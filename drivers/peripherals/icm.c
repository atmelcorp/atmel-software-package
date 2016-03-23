/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
 * DISCLAIMED. IN NO EVENT ICMLL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
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
 * Implementation of Integrity Check Monitor (ICM)
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/icm.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enable ICM, the ICM controller is activated
 */
void icm_enable(void)
{
	ICM->ICM_CTRL = ICM_CTRL_ENABLE;
}

/**
 * \brief Disable ICM, if a region is active, this region is terminated
 */
void icm_disable(void)
{
	ICM->ICM_CTRL = ICM_CTRL_DISABLE;
}

/**
 * \brief Resets the ICM controller.
 */
void icm_swrst(void)
{
	ICM->ICM_CTRL = ICM_CTRL_SWRST;
}

/**
 * \brief Enable region monitoring for given region
 * \param region When bit RMEN[region] is set to one, the monitoring of Region is activated.
 */
void icm_enable_monitor(uint8_t region)
{
	ICM->ICM_CTRL = ICM_CTRL_RMEN(region);
}

/**
 * \brief Disable region monitoring for given region
 * \param region When bit RMDIS[region] is set to one, the monitoring of Region is disabled.
 */
void
icm_disable_monitor(uint8_t region)
{
	ICM->ICM_CTRL = ICM_CTRL_RMDIS(region);
}

/**
 * \brief Recompute Internal hash.
 * \param region When REHASH[region] is set to one, the region digest is re-computed.
 * \note This bit is only available when Region monitoring is disabled.
 */
void
icm_re_compute_hash(uint8_t region)
{
	/* This bit is only available when region monitoring is disabled. */
	if ((ICM->ICM_SR & ICM_SR_RMDIS(region)) == ICM_SR_RMDIS(region))
		ICM->ICM_CTRL = ICM_CTRL_REHASH(region);
}

/**
 * \brief Configures an ICM peripheral with the specified parameters.
 *  \param mode  Desired value for the ICM mode register (see the datasheet).
 */
void icm_configure(uint32_t mode)
{
	ICM->ICM_CFG = mode;
}

/**
 * \brief Enables the selected interrupts sources on a ICM peripheral.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void
icm_enable_it(uint32_t sources)
{
	ICM->ICM_IER = sources;
}

/**
 * \brief Disables the selected interrupts sources on a ICM peripheral.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void
icm_disable_it(uint32_t sources)
{
	ICM->ICM_IDR = sources;
}

/**
 * \brief Get the current interrupt status register of the given ICM peripheral.
 * \return  ICM status register.
 */
uint32_t icm_get_int_status(void)
{
	return ICM->ICM_ISR;
}

/**
 * \brief Get the current interrupt mask register of the given ICM peripheral.
 * \return  ICM interrupt mask register.
 */
uint32_t icm_get_int_mask(void)
{
	return ICM->ICM_IMR;
}


/**
 * \brief Get the current status register of the given ICM peripheral.
 * \return  ICM status register.
 */
uint32_t icm_get_status(void)
{
	return ICM->ICM_SR;
}

/**
 * \brief Get the undefined access status register of the given ICM peripheral.
 * \return  ICM status register.
 */
uint32_t icm_get_access_status(void)
{
	return ICM->ICM_UASR;
}

/**
 * \brief Set descriptor area start address register.
 * \param addr start address
 * \note The start address is a multiple of the total size of the data structure (64 bytes).
 */
void icm_set_desc_address(uint32_t addr)
{
	ICM->ICM_DSCR = addr;
}

/**
 * \brief Set hash area start address register.
 * \param addr start address
 * \note This field points at the Hash memory location. The address must be a multiple of 128 bytes.
 */
void icm_set_hash_address(uint32_t addr)
{
	ICM->ICM_HASH = addr;
}

/**
 * \brief Set ICM user initial Hash value register.
 * \param field
 * \param val Initial Hash Value
 */
void icm_set_init_hash(uint8_t field, uint32_t val)
{
	ICM->ICM_UIHVAL[field] = ICM_UIHVAL_VAL(val);
}
