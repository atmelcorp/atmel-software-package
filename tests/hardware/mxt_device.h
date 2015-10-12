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

#ifndef MXT_DEVICE_H
#define MXT_DEVICE_H


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define MXT_MAX_MSG_SIZE       7
#define MXT_TWI_MSG_SIZE_T5    MXT_MAX_MSG_SIZE + 2
#define MXT_RESET_TIME         65

typedef uint16_t mxt_memory_adr;

#define UNUSED(v)          (void)(v)

/*----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

/** \brief Object types */
enum mxt_object_type {

	MXT_GEN_MESSAGEPROCESSOR_T5             = 5,
	MXT_GEN_COMMANDPROCESSOR_T6             = 6,
	MXT_GEN_POWERCONFIG_T7                  = 7,
	MXT_GEN_ACQUISITIONCONFIG_T8            = 8,
	MXT_TOUCH_MULTITOUCHSCREEN_T9           = 9,
	MXT_SPT_COMMSCONFIG_T18                 = 18,
	MXT_SPT_MESSAGECOUNT_T44                = 44,
	MXT_PROCG_TOUCHSUPPRESSION_T48          = 48,
};

/**
 * \name COMMSCONFIG T18 object control register bit positions
 * @{
 */
#define MXT_COMMSCONFIG_T18_CHG_MODE_bp       2
#define MXT_COMMSCONFIG_T18_DISMNTR_bp        7
/** @} */

/** \brief Identification header */
struct mxt_info_object {
	uint8_t family_ID;      /**< Family ID     */
	uint8_t variant_ID;     /**< Variant ID    */
	uint8_t version;        /**< Version       */
	uint8_t build;          /**< Build         */
	uint8_t matrix_x_size;  /**< Matrix x size */
	uint8_t matrix_y_size;  /**< Matrix y size */
	uint8_t obj_count;      /**< Object count  */
};

/** \brief Object table entry */
struct mxt_object {
	uint8_t type;                 /**< Object type                    */
	uint8_t add_lsb;			  /**< Object start address LSB       */
	uint8_t add_msb;			  /**< Object start address MSB       */
	uint8_t size;                 /**< Object size                    */
	uint8_t instances;            /**< Maximum object instances       */
	uint8_t num_report_ids;       /**< Number of report IDs pr object */
};

/** \brief Object message */
struct mxt_conf_messageprocessor_t5 {
	uint8_t reportid;                  /**< Report ID */
	uint8_t message[MXT_MAX_MSG_SIZE]; /**< Message   */
	uint8_t checksum;                  /**< Checksum  */
};

/**
 * \name COMMANDPROCESSOR T6 object register offset
 * @{
 */
#define MXT_GEN_COMMANDPROCESSOR_RESET        0
#define MXT_GEN_COMMANDPROCESSOR_BACKUPNV     1
#define MXT_GEN_COMMANDPROCESSOR_CALIBRATE    2
#define MXT_GEN_COMMANDPROCESSOR_REPORTALL    3
#define MXT_GEN_COMMANDPROCESSOR_DIAGNOSTIC   5
/** @} */

/** \brief Commandprocessor T6 object */
struct mxt_gen_commandprocessor_t6 {
	uint8_t reset;
	uint8_t backupnv;
	uint8_t calibrate;
	uint8_t reportall;
	uint8_t reserved_0x04;
	uint8_t diagnostic;
};

/**
 * \name Touch event types
 * @{
 */
#define MXT_UNGRIP_EVENT   1
#define MXT_SUPPRESS_EVENT 2
#define MXT_AMP_EVENT      4
#define MXT_VECTOR_EVENT   8
#define MXT_MOVE_EVENT     16
#define MXT_RELEASE_EVENT  32
#define MXT_PRESS_EVENT    64
#define MXT_DETECT_EVENT   128
/* @} */

/** \brief Touch event struct */
struct mxt_touch_event {
	uint8_t id;
	uint8_t status;
	uint16_t x;
	uint16_t y;
	uint8_t size;
	int8_t deltax;
	int8_t deltay;
};

/** \brief Map of the report ID vs object type and instance */
struct mxt_report_id_map {
	uint8_t object_type;
	uint8_t instance;
};

/**
 * \brief Forward declaration of the mxt_device struct to avoid warnings
 *         in the mxt_message_handler_t typedef
 */
struct mxt_device;

/**
 * \brief Message handler prototype
 *
 * \param *device Pointer to mxt_device struct
 * \param *message Pointer to mxt_message struct
 */
typedef void (*mxt_message_handler_t)(struct mxt_device *device, struct mxt_conf_messageprocessor_t5 *message);

/**
 * \brief maXTouch device information data container struct
 */

struct mxt_device {
	struct _twi_desc *twid;
	uint8_t chip_id;
	uint8_t firmware_version;

	struct mxt_info_object *info_object;
	struct mxt_object *object_list;
	mxt_message_handler_t handler;
	struct mxt_report_id_map *report_id_map;

	int8_t multitouch_report_offset;

	const struct _pin twi_pin;
	const struct _pin chg_pin;
};


/**
 * Status code that may be returned by shell commands and protocol
 * implementations.
 *
 * \note Any change to these status codes and the corresponding
 * message strings is strictly forbidden. New codes can be added,
 * however, but make sure that any message string tables are updated
 * at the same time.
 */
enum status_code {
	STATUS_OK               =  0, //!< Success
	STATUS_ERR_BUSY         =  0x19,
	STATUS_ERR_DENIED       =  0x1C,
	STATUS_ERR_TIMEOUT      =  0x12,
	ERR_IO_ERROR            =  -1, //!< I/O error
	ERR_FLUSHED             =  -2, //!< Request flushed from queue
	ERR_TIMEOUT             =  -3, //!< Operation timed out
	ERR_BAD_DATA            =  -4, //!< Data integrity check failed
	ERR_PROTOCOL            =  -5, //!< Protocol error
	ERR_UNSUPPORTED_DEV     =  -6, //!< Unsupported device
	ERR_NO_MEMORY           =  -7, //!< Insufficient memory
	ERR_INVALID_ARG         =  -8, //!< Invalid argument
	ERR_BAD_ADDRESS         =  -9, //!< Bad address
	ERR_BUSY                =  -10, //!< Resource is busy
	ERR_BAD_FORMAT          =  -11, //!< Data format not recognized
	ERR_NO_TIMER            =  -12, //!< No timer available
	ERR_TIMER_ALREADY_RUNNING   =  -13, //!< Timer already running
	ERR_TIMER_NOT_RUNNING   =  -14, //!< Timer not running
	ERR_ABORTED             =  -15, //!< Operation aborted by user
	/**
	 * \brief Operation in progress
	 *
	 * This status code is for driver-internal use when an operation
	 * is currently being performed.
	 *
	 * \note Drivers should never return this status code to any
	 * callers. It is strictly for internal use.
	 */
	OPERATION_IN_PROGRESS	= -128,
};

typedef enum status_code status_code_t;


/** Swap 2 bytes of a word */
#define SWAP_LSB_MSB(x)   (((x & 0xff) << 8) | (x >> 8))

/*------------------------------------------------------------------------------
 *         Functions
 *----------------------------------------------------------------------------*/

status_code_t mxt_probe_device(struct mxt_device * device, uint8_t chip_adr);

status_code_t mxt_init_device(struct mxt_device *device);

status_code_t mxt_load_configuration(struct mxt_device *device, void *configuration_data);

uint16_t mxt_get_object_address(struct mxt_device *device, uint8_t object_id, uint8_t instance);

status_code_t mxt_read_config_object(struct mxt_device *device, mxt_memory_adr memory_adr, void *obj_data);

status_code_t mxt_read_config_reg(struct mxt_device *device, mxt_memory_adr memory_adr, uint8_t *value);

status_code_t mxt_write_config_object(struct mxt_device *device, mxt_memory_adr memory_adr, void *obj_data);

status_code_t mxt_write_config_reg(struct mxt_device *device, mxt_memory_adr memory_adr, uint8_t value);

status_code_t mxt_close_device(struct mxt_device *device);

void mxt_set_message_handler(struct mxt_device *device, mxt_message_handler_t handler);

bool mxt_is_message_pending(struct mxt_device *device);

int8_t mxt_get_message_count(struct mxt_device *device);

status_code_t mxt_read_message(struct mxt_device *device, struct mxt_conf_messageprocessor_t5 *message);

status_code_t mxt_read_touch_event(struct mxt_device *device, struct mxt_touch_event *touch_event);

enum mxt_object_type mxt_get_object_type(struct mxt_device *device, struct mxt_conf_messageprocessor_t5 *message);

status_code_t mxt_process_messages(struct mxt_device *device);


#endif /*MXT_DEVICE_H*/
