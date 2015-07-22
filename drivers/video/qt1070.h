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
  * Implementation QT1070 driver.
  *
  */

#ifndef _QT1070_H_
#define _QT1070_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _qt1070_desc {
	const char* name;
	uint8_t     size;
	uint8_t     page_size;
};

struct _qt1070 {
	struct _twi_desc* twid;
	struct _qt1070_desc desc;

	uint8_t chip_id;
	uint8_t firmware_version;
};


/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Get chip ID.
 *
 * \param twid   Pointer to twi driver structure.
 * \return Chip Id
 */
extern uint8_t qt1070_get_chip_id(struct _qt1070* qt1070);

/**
 * \brief  Get firmware version number.
 *
 * \param twid   Pointer to twi driver structure.
 * \return Firmware version number.
 */
extern uint8_t qt1070_get_firmware_version(struct _qt1070* qt1070);

/**
* \brief  Get detection status.
*
* \param twid   Pointer to twi driver structure.
* \return Dectection status.
*/
extern uint8_t qt1070_get_detection_status(struct _qt1070* qt1070);

/**
 * \brief  Get Key status.
 *
 * \param twid   Pointer to twi driver structure.
 * \return Key status.
 */
extern uint8_t qt1070_get_key_status(struct _qt1070* qt1070);

/**
 * \brief  Get key signal value in the given Key. These are the key's
 * of 16-bit key signals which are accessed as two 8-bit bytes,stored MSB first
 *
 * \param twid   Pointer to twi driver structure.
 * \param key     Key index.
 * \return Key signal value.
 */
extern uint16_t qt1070_get_key_signal(struct _qt1070* qt1070, uint8_t key);

/**
 * \brief  Get key reference data in the given Key. These are the key's
 * of 16-bit key reference data which are accessed as two 8-bit bytes, stored MSB first
 *
 * \param twid   Pointer to twi driver structure.
 * \param key     Key index.
 * \return Key reference data.
 */
extern uint16_t qt1070_get_key_reference(struct _qt1070* qt1070, uint8_t key);

/**
 * \brief  Set the threshold value for the given Key.
 *
 * \param twid   Pointer to twi driver structure.
 * \param key     Key index.
 * \param threshold Threshold value.
 */
extern void qt1070_set_threshold(struct _qt1070* qt1070, uint8_t key, uint8_t threshold);

/**
 * \brief  Set Averaging factor and adjacent key suppression for the given Key.
 *
 * \param twid   Pointer to twi driver structure.
 * \param key     Key index.
 * \param ave     Averaging factor.
 * \param aks     AKS group index.
 */
extern void qt1070_set_ave_aks(struct _qt1070* qt1070, uint8_t key, uint8_t ave, uint8_t aks);

/**
 * \brief Set DI level for the given Key. This 8-bit value controls the number
 * of consecutive measurement that must be confirmed as having passed the key threshold
 * before that key is registered as being in detect.
 *
 * \param twid   Pointer to twi driver structure.
 * \param key     Key index.
 * \param di      DI level.
 */
extern void qt1070_set_detection_integrator(struct _qt1070* qt1070, uint8_t key, uint8_t di);

/**
 * \brief Start a calibration cycle, the CALIBTATE flag in the detection status
 * register is set when the calibration begins and clears when the calibration
 * has finished.
 *
 * \param twid   Pointer to twi driver structure.
 */
extern void qt1070_start_calibrate(struct _qt1070* qt1070);

/**
 * \brief Reset the device.
 *
 * \param twid   Pointer to twi driver structure.
 */
extern void qt1070_start_reset(struct _qt1070* qt1070);

#endif /* _QT1070_H_ */
