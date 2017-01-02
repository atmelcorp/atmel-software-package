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

/** Internal Register Address Allocation */

/** Chip ID register*/
#define QT1070_CHIP_ID              0

/** Firmware version register*/
#define QT1070_REG_FIRMWARE_VERSION 1

/** Detection status*/
#define QT1070_REG_DETECTION_STATUS 2

/** Key status*/
#define QT1070_REG_KEY_STATUS       3

/** Key signal */
#define QT1070_REG_KEY0_SIGNAL_MSB  4
#define QT1070_REG_KEY0_SIGNAL_LSB  5
#define QT1070_REG_KEY1_SIGNAL_MSB  6
#define QT1070_REG_KEY1_SIGNAL_LSB  7
#define QT1070_REG_KEY2_SIGNAL_MSB  8
#define QT1070_REG_KEY2_SIGNAL_LSB  9
#define QT1070_REG_KEY3_SIGNAL_MSB  10
#define QT1070_REG_KEY3_SIGNAL_LSB  11
#define QT1070_REG_KEY4_SIGNAL_MSB  12
#define QT1070_REG_KEY4_SIGNAL_LSB  13
#define QT1070_REG_KEY5_SIGNAL_MSB  14
#define QT1070_REG_KEY5_SIGNAL_LSB  15
#define QT1070_REG_KEY6_SIGNAL_MSB  16
#define QT1070_REG_KEY6_SIGNAL_LSB  17

/** Reference date */
#define QT1070_REG_REFDATA0_MSB     18
#define QT1070_REG_REFDATA0_LSB     19
#define QT1070_REG_REFDATA1_MSB     20
#define QT1070_REG_REFDATA1_LSB     21
#define QT1070_REG_REFDATA2_MSB     22
#define QT1070_REG_REG_REFDATA2_LSB 23
#define QT1070_REG_REFDATA3_MSB     24
#define QT1070_REG_REG_REFDATA3_LSB 25
#define QT1070_REG_REFDATA4_MSB     26
#define QT1070_REG_REFDATA4_LSB     27
#define QT1070_REG_REFDATA5_MSB     28
#define QT1070_REG_REFDATA5_LSB     29
#define QT1070_REG_REFDATA6_MSB     30
#define QT1070_REG_REFDATA6_LSB     31

/** Negative threshold level */
#define QT1070_REG_NTHR_KEY0        32
#define QT1070_REG_NTHR_KEY1        33
#define QT1070_REG_NTHR_KEY2        34
#define QT1070_REG_NTHR_KEY3        35
#define QT1070_REG_NTHR_KEY4        36
#define QT1070_REG_NTHR_KEY5        37
#define QT1070_REG_NTHR_KEY6        38

/** Adjacent key suppression level */
#define QT1070_REG_AVEAKS_KEY0      39
#define QT1070_REG_AVEAKS_KEY1      40
#define QT1070_REG_AVEAKS_KEY2      41
#define QT1070_REG_AVEAKS_KEY3      42
#define QT1070_REG_AVEAKS_KEY4      43
#define QT1070_REG_AVEAKS_KEY5      44
#define QT1070_REG_AVEAKS_KEY6      45

/** Detection interator conter for key*/
#define QT1070_REG_DI_KEY0          46
#define QT1070_REG_DI_KEY1          47
#define QT1070_REG_DI_KEY2          48
#define QT1070_REG_DI_KEY3          49
#define QT1070_REG_DI_KEY4          50
#define QT1070_REG_DI_KEY5          51
#define QT1070_REG_DI_KEY6          52

/** Low power mode */
#define QT1070_REG_LOWPOWER_MODE    54

/** Maximum on duration */
#define QT1070_REG_MAX_DURATION     55

/** Calibrate */
#define QT1070_REG_CALIRATE         56

/** Reset */
#define QT1070_REG_RESET            57

/** Detection Status. */

/** This bit is set during a calibration sequence.*/
#define QT1070_CALIBRATE_BIT        7

/** This bit is set if the time to acquire all key signals exceeds 8 ms*/
#define QT1070_OVERFLOW_BIT         6

/** This bit is set if Comms mode is enabled. */
#define QT1070_COMMSENABLED_BIT     5

/** This bit is set if any keys are in detect. */
#define QT1070_TOUCH_BIT            0

/*----------------------------------------------------------------------------
 *         Local Definitions
 *----------------------------------------------------------------------------*/

struct _qt1070_desc {
	const char* name;
	uint8_t     size;
	uint8_t     page_size;
};

struct _qt1070 {
	uint8_t bus;
	uint8_t addr;
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
 * \param qt1070 Pointer to the driver structure.
 * \return Chip Id
 */
extern uint8_t qt1070_get_chip_id(struct _qt1070* qt1070);

/**
 * \brief  Get firmware version number.
 *
 * \param qt1070 Pointer to the driver structure.
 * \return Firmware version number.
 */
extern uint8_t qt1070_get_firmware_version(struct _qt1070* qt1070);

/**
 * \brief  Get detection status.
 *
 * \param qt1070 Pointer to the driver structure.
 * \return Dectection status.
 */
extern uint8_t qt1070_get_detection_status(struct _qt1070* qt1070);

/**
 * \brief  Get Key status.
 *
 * \param qt1070 Pointer to the driver structure.
 * \return Key status.
 */
extern uint8_t qt1070_get_key_status(struct _qt1070* qt1070);

/**
 * \brief  Get key signal value in the given Key. These are the key's
 * of 16-bit key signals which are accessed as two 8-bit bytes,stored MSB first
 *
 * \param qt1070 Pointer to the driver structure.
 * \param key     Key index.
 * \return Key signal value.
 */
extern uint16_t qt1070_get_key_signal(struct _qt1070* qt1070, uint8_t key);

/**
 * \brief  Get key reference data in the given Key.
 *
 * \details These are the key's of 16-bit key reference data which are
 * accessed as two 8-bit bytes, stored MSB first.
 *
 * \param qt1070 Pointer to the driver structure.
 * \param key     Key index.
 * \return Key reference data.
 */
extern uint16_t qt1070_get_key_reference(struct _qt1070* qt1070, uint8_t key);

/**
 * \brief  Set the threshold value for the given Key.
 *
 * \param qt1070 Pointer to the driver structure.
 * \param key     Key index.
 * \param threshold Threshold value.
 */
extern void qt1070_set_threshold(struct _qt1070* qt1070, uint8_t key,
				 uint8_t threshold);

/**
 * \brief  Set Averaging factor and adjacent key suppression for the given Key.
 *
 * \param qt1070 Pointer to the driver structure.
 * \param key     Key index.
 * \param ave     Averaging factor.
 * \param aks     AKS group index.
 */
extern void qt1070_set_ave_aks(struct _qt1070* qt1070, uint8_t key, uint8_t ave,
			       uint8_t aks);

/**
 * \brief Set DI level for the given Key.
 *
 * \details This 8-bit value controls the number of consecutive
 * measurement that must be confirmed as having passed the key
 * threshold before that key is registered as being in detect.
 *
 * \param qt1070 Pointer to the driver structure.
 * \param key     Key index.
 * \param di      DI level.
 */
extern void qt1070_set_detection_integrator(struct _qt1070* qt1070, uint8_t key,
					    uint8_t di);

/**
 * \brief Start a calibration cycle, the CALIBTATE flag in the detection status
 * register is set when the calibration begins and clears when the calibration
 * has finished.
 *
 * \param qt1070 Pointer to the driver structure.
 */
extern void qt1070_start_calibrate(struct _qt1070* qt1070);

/**
 * \brief Reset the device.
 *
 * \param qt1070 Pointer to the driver structure.
 */
extern void qt1070_start_reset(struct _qt1070* qt1070);

/**
 * \brief Configure and initialize the device.
 *
 * \param qt1070 Pointer to the driver structure.
 * \param twid Pointer to twi driver structure.
 * \return 0 on success
 */
extern int qt1070_configure(struct _qt1070* qt1070);

#endif /* _QT1070_H_ */
