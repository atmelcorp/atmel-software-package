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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/flexcom.h"

#include "peripherals/twi.h"
#include "peripherals/twid.h"

#include "mxt_device.h"

#include "trace.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define  MXT_MEM_ADDR               0x00
#define  MXT_ID_BLOCK_SIZE          0x07

#define  OBJECT_TABLE_ELEMENT_SIZE  0x06
#define  OBJECT_TABLE_START_ADDRESS 0x07


#define  MXT_FAMILY_143E            0x81
#define  MXT_VARIANT_143E           0x07

#define  MXT_FAMILY_224            0x82
#define  MXT_VARIANT_224           0x24

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define DEFAULT_REPORT_ID_MAP	64
struct mxt_report_id_map rmb_mxt_report_id_map[DEFAULT_REPORT_ID_MAP] = {0};

#define DEFAULT_OBJECT	32
struct mxt_object rmb_mxt_object[DEFAULT_OBJECT] = {0};

struct mxt_info_object info_obj = {0};

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * \internal
 * \brief Total number of report ids available
 *        in the maXTouch device.
 *
 * \param *device Pointer to mxt_device instance
 * \return Total number of report ids
 */
static uint16_t mxt_get_tot_report_ids(struct mxt_device *device)
{
	uint16_t i;
	uint16_t tot_report_ids = 0;
	/* Figure out how many report id's to allocate memory for */
	for (i = 0; i < device->info_object->obj_count; ++i) {
		tot_report_ids += ((device->object_list[i].instances)+1 * device->object_list[i].num_report_ids);
	}
	return tot_report_ids;
}

/**
 * \internal
 * \brief Read out the id information from the maXTouch device and
 *        put it into the info_object struct in the device instance.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_read_id_block(struct mxt_device *device)
{
	uint8_t status;

	/* set info object pointer */
	device->info_object = &info_obj;

	/* Initializing the TWI packet to send to the slave */
	device->twid->iaddr = SWAP_LSB_MSB(MXT_MEM_ADDR);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = (uint8_t*)device->info_object,
		.size = MXT_ID_BLOCK_SIZE,
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS) return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \internal
 * \brief Read out the object table from the maXTouch device and
 *        put it into the object_list structs in the device instance.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_read_object_table(struct mxt_device *device)
{
	uint8_t status;

	if( device->info_object->obj_count > DEFAULT_OBJECT ) return ERR_IO_ERROR;
	device->object_list = rmb_mxt_object;
	device->twid->iaddr = SWAP_LSB_MSB(OBJECT_TABLE_START_ADDRESS);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = (uint8_t*)device->object_list,
		.size = device->info_object->obj_count * sizeof(struct mxt_object),
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \internal
 * \brief Read info block from device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_read_info_block(struct mxt_device *device)
{
	uint8_t status;

	if ((status = mxt_read_id_block(device)) != STATUS_OK) {
		return (status_code_t)status;
	}
	if(device->info_object->obj_count == 0x00) {
		printf("\n\r -E- Error read id block \n\r ");
		return ERR_BAD_DATA;
	}
	if ((status = mxt_read_object_table(device)) != STATUS_OK) {
		return (status_code_t)status;
	}

	return STATUS_OK;
}

/**
 * \internal
 * \brief Create report ID map from the object list in mxt_device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_create_report_id_map(struct mxt_device *device)
{
	uint8_t k;
	uint16_t i, j;
	uint16_t id_index = 1;
	uint16_t tot_report_ids;

	tot_report_ids = mxt_get_tot_report_ids(device);

	/* rmb DEFAULT_REPORT_ID_MAP mxt_report_id_map struct by default */
	if ( tot_report_ids >= DEFAULT_REPORT_ID_MAP ) return ERR_IO_ERROR;
	device->report_id_map = rmb_mxt_report_id_map;

	/* For every object */
	for (i = 0; i < device->info_object->obj_count; ++i) {
		/* For every instance of an object */
		k = device->object_list[i].instances; /* k=0 indicate at least 1 instance */
		for (j = 0; j <= device->object_list[i].instances; ++j) {
			/* Not all objects report messages */
			if (device->object_list[i].num_report_ids != 0) {
				/* Some object have more than one report_id */
				for (k = 0; k < device->object_list[i].num_report_ids; ++k) {
					device->report_id_map[id_index].object_type = device->object_list[i].type;
					device->report_id_map[id_index].instance = j;
					id_index++;
				} /* each report id */
			} /* if report id */
		} /* every instance */
	} /* every object */

	return STATUS_OK;
}

/**
 * \internal
 * \brief Calculates the next crc value of current crc value
 *        and the following two bytes.
 *
 * \param crc
 * \param byte1
 * \param byte2
 * \return crc
 */
static uint32_t inline mxt_crc_24(uint32_t crc, uint8_t byte1, uint8_t byte2)
{
	static const uint32_t crcpoly = 0x80001B;
	uint32_t result;
	uint16_t data_word;

	data_word = (uint16_t)((uint16_t)(byte2 << 8u) | byte1);
	result = ((crc << 1u) ^ (uint32_t)data_word);
	if (result & 0x1000000) {
		result ^= crcpoly;
	}
	return result;
}

/**
 * \internal
 * \brief Calculates the crc checksum of the data in the info block.
 *
 * \param *device Pointer to mxt_device instance
 * \param *crc    Pointer to the crc variable
 * \return Operation result status code
 */
static status_code_t mxt_calculate_infoblock_crc(struct mxt_device *device,
		uint32_t *crc)
{
	uint32_t crc_tmp = 0;
	uint16_t crc_area_size, i;
	uint8_t *id_pointer = (uint8_t *)device->info_object;
	uint8_t *objects_pointer = (uint8_t *)device->object_list;

	/* Data to calculate crc value for */
	crc_area_size = MXT_ID_BLOCK_SIZE + (device->info_object->obj_count * OBJECT_TABLE_ELEMENT_SIZE);

	for (i = 0; i < MXT_ID_BLOCK_SIZE - 1; i += 2) {
		crc_tmp = mxt_crc_24(crc_tmp, id_pointer[i], id_pointer[i + 1]);
	}

	/* Calculate for the last byte (7th) byte in the info_id_t struct and */
	/* the first in the object table.*/
	crc_tmp = mxt_crc_24(crc_tmp, id_pointer[MXT_ID_BLOCK_SIZE - 1],
			objects_pointer[0]);

	for (i = 1; i < (crc_area_size - MXT_ID_BLOCK_SIZE - 1); i += 2) {
		crc_tmp = mxt_crc_24(crc_tmp, objects_pointer[i], objects_pointer[i + 1]);
	}
	crc_tmp = mxt_crc_24(crc_tmp, objects_pointer[crc_area_size - MXT_ID_BLOCK_SIZE - 1], 0);

	/* Return only 24 bit CRC. */
	*crc = (crc_tmp & 0x00FFFFFF);
	return STATUS_OK;
}

/**
 * \internal
 * \brief Reads out the crc value stored in the mxt-device.
 *
 * \param *device Pointer to mxt_device instance
 * \return crc_value 24-bit value representing the crc.
 */
static uint32_t mxt_get_crc_value(struct mxt_device *device)
{
	uint8_t crc[3];
	uint8_t status;
	uint16_t iaddr = MXT_ID_BLOCK_SIZE + (OBJECT_TABLE_ELEMENT_SIZE * device->info_object->obj_count);

	device->twid->iaddr = SWAP_LSB_MSB(iaddr);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = crc,
		.size = sizeof(crc),
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return ((uint32_t)crc[2] << 16) | ((uint16_t)crc[1] << 8) | crc[0];
}

/**
 * \internal
 * \brief Validates the info block by comparing the calculated Compares the
 *        calculated and stored crc value.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code.
 */
static status_code_t mxt_validate_info_block(struct mxt_device *device)
{
	uint32_t crc_read;
	uint32_t crc_calculated;

	crc_read = mxt_get_crc_value(device);
	if( !crc_read )
		return ERR_BAD_DATA; /* crc null, no programmation on mxt */
	else {
		mxt_calculate_infoblock_crc(device, &crc_calculated);
		if (crc_calculated != crc_read)
			return ERR_BAD_DATA;
		else
			return STATUS_OK;
	}
}

/**
 * \internal
 * \brief Returns the object size by using the object address
 *
 * \param *device Pointer to mxt_device instance
 * \param mem_adr Address of the object
 * \return uint8_t Size of the object
 */
static uint8_t mxt_get_object_size(struct mxt_device *device, mxt_memory_adr mem_adr)
{
	uint8_t i;
	mxt_memory_adr addr;

	for (i = 0; i < device->info_object->obj_count; ++i) {
		addr = device->object_list[i].add_lsb | (device->object_list[i].add_msb<<8);
		if (addr == mem_adr) {
			return (device->object_list[i].size + 1);
		}
	}
	return STATUS_OK;
}

/**
 * \internal
 * \brief Returns the report id offset for a object.
 *
 * \param *device Pointer to mxt_device instance
 * \param object_type ID of the object
 * \return int8_t Report ID offset
 */
static int8_t mxt_get_report_id_offset(struct mxt_device *device, enum mxt_object_type object_type)
{
	uint16_t i;
	uint16_t tot_rpt_id = mxt_get_tot_report_ids(device);
	for (i = 0; i < tot_rpt_id; ++i) {
		if (device->report_id_map[i].object_type == object_type) {
			return i;
		}
	}
	return ERR_IO_ERROR;
}

#if defined(CONF_VALIDATE_MESSAGES) || defined(__DOXYGEN__)
/**
 * \internal
 * \brief Calculates the next crc value of current crc value
 *        and the following byte.
 *
 * \param crc
 * \param data
 * \return crc
 */
static uint8_t mxt_crc_8(uint8_t crc, uint8_t data)
{
	static const uint8_t crcpoly = 0x8c;
	uint8_t index, fb;
	index = 8;

	do {
		fb = (crc ^ data) & 0x01;
		data >>= 1;
		crc >>= 1;
		if (fb) {
			crc ^= crcpoly;
		}
	} while (--index);

	return crc;
}

/**
 * \internal
 * \brief Validates the message received from the maXTouch device.
 *
 * \param packet  Message received from the maXTouch device
 * \return Operation result status code.
 */
static status_code_t mxt_validate_message(twi_package_t *packet)
{
	uint8_t crc = 0;
	uint8_t i;

	for (i = 0; i < (MXT_TWI_MSG_SIZE_T5); ++i) {
		crc = mxt_crc_8(crc, ((uint8_t *)packet->buffer)[i]);
	}

	if (crc != 0) {
		return ERR_BAD_DATA;
	} else {
		return STATUS_OK;
	}
}
#endif

/*------------------------------------------------------------------------------
 *         Display functions
 *----------------------------------------------------------------------------*/

void display_info_object (struct mxt_device *device)
{
	printf("\n\r INFO OBJECT \n\r");
	printf("Family ID: 0x%X \n\r", device->info_object->family_ID);
	printf("Variant ID: 0x%X \n\r", device->info_object->variant_ID);
	printf("Version: 0x%X \n\r", device->info_object->version);
	printf("Build: 0x%X \n\r", device->info_object->build);
	printf("Variant ID: 0x%X \n\r", device->info_object->variant_ID);
	printf("Matrix x-y size : %02d/%02d \n\r",
		   device->info_object->matrix_x_size, device->info_object->matrix_y_size);
	printf("Object count: %02d \n\r", device->info_object->obj_count);
}

void display_object_table (struct mxt_device *device)
{
	uint8_t i;
	mxt_memory_adr addr;


	printf("\n\r INFO TABLE \n\r");
	for (i=0; i<device->info_object->obj_count; i++) {
		printf("** Index: %02d \n\r", i);
		printf("Type: %02d \n\r", device->object_list[i].type);
		addr = (device->object_list[i].add_msb >> 8) | device->object_list[i].add_lsb;
		printf("Mem addr: %04d 0x%04x \n\r", addr, addr);
		printf("Size: %03d \n\r", device->object_list[i].size+1);
		printf("Nb Instances: %02d \n\r", device->object_list[i].instances+1);
		printf("Num report ids: %02d \n\r", device->object_list[i].num_report_ids);
	}
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Probe for a maXTouch connected to a specific TWI line
 *
 * \param interface Pointer to TWI register set
 * \param *chip_adr I2C address to maXTouch device
 * \return Operation result status code
 */
status_code_t mxt_probe_device(struct mxt_device * device, uint8_t chip_adr)
{
	uint8_t status;

	device->twid->iaddr = SWAP_LSB_MSB(MXT_MEM_ADDR);
	device->twid->isize = 2;
	device->twid->slave_addr = chip_adr;
	struct _buffer in = {
		.data = (void*)device->info_object,
		.size = MXT_ID_BLOCK_SIZE,
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS) return (status_code_t)status;
	twid_wait_transfert(device->twid);

	if ((device->info_object->family_ID != MXT_FAMILY_224)
		|| (device->info_object->variant_ID != MXT_VARIANT_224)) {
		return ERR_BAD_ADDRESS;
	}
	return STATUS_OK;
}

/**
 * \brief Initialize maXTouch device connected to TWIx module
 *
 * \param *interface Pointer to TWI register set
 * \param chip_adr I2C address to maXTouch device
 * \return Operation result status code
 */
status_code_t mxt_init_device (struct mxt_device *device)
{
	int8_t status;

	device->handler = NULL;
	device->info_object = &info_obj;

	status = mxt_probe_device(device, device->twid->slave_addr);
	if (status != STATUS_OK)
		return ERR_BAD_ADDRESS;

	status = mxt_read_info_block(device);
	if (status != STATUS_OK)
		return status;

	//display_info_object(device);

	status = mxt_read_object_table(device);
	if (status != STATUS_OK)
		return (status_code_t)status;

	//display_object_table(device);

	/* Validate the data read from the info block */
	status = mxt_validate_info_block(device);
	if (status != STATUS_OK)
		return (status_code_t)status;

	/* Create map of the report ID's and put it into mxt_device struct */
	status = mxt_create_report_id_map(device);
	if (status != STATUS_OK)
		return (status_code_t)status;

	/* Get the report id offset of the multi touch object*/
	status = mxt_get_report_id_offset(device, MXT_TOUCH_MULTITOUCHSCREEN_T9);
	if (status == ERR_IO_ERROR)
		return ERR_BAD_DATA;

	device->multitouch_report_offset = status;
	return STATUS_OK;
}

/**
 * \brief Get memory address to object
 *
 * \param *device Pointer to mxt_device instance
 * \param object_id Object ID
 * \param instance Object instance
 * \return Object memory address on maXTouch device. 0 if object not found
 */
uint16_t mxt_get_object_address(struct mxt_device *device, uint8_t object_id, uint8_t instance)
{
	uint16_t i;
	for (i = 0; i < device->info_object->obj_count; i++) {
		if (object_id == device->object_list[i].type) {
			return (device->object_list[i].add_msb << 8) | device->object_list[i].add_lsb;
			/* return Address LSB/MSB */
		}
	}
	return 0;
}

/**
 * \brief Read object configuration
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to the object (MSB/LBB)
 * \param *obj_data Pointer to a large enough memory buffer
 * \return Operation result status code
 */
status_code_t mxt_read_config_object(struct mxt_device *device, mxt_memory_adr memory_adr, void *obj_data)
{
	uint8_t status;
	device->twid->iaddr = SWAP_LSB_MSB(memory_adr);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = obj_data,
		.size = mxt_get_object_size(device, memory_adr),
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \brief Read object register
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to the register
 * \param *value Pointer to a 1 byte buffer to store the data in
 * \result Operation result status code
 */
status_code_t mxt_read_config_reg(struct mxt_device *device, mxt_memory_adr memory_adr, uint8_t *value)
{
	uint8_t status;
	device->twid->iaddr = SWAP_LSB_MSB(memory_adr);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = value,
		.size = sizeof(uint8_t),
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \brief Write object configuration
 *
 * \param *device Pointer to mxt_device  instance
 * \param memory_adr Memory address to the object
 * \param *obj_data Pointer to memory buffer containing object data
 * \result Operation result status code
 */
status_code_t mxt_write_config_object(struct mxt_device *device, mxt_memory_adr memory_adr, void *obj_data)
{
	uint8_t status;
	device->twid->iaddr = SWAP_LSB_MSB(memory_adr);
	device->twid->isize = 2;
	struct _buffer out = {
		.data = (void*)obj_data,
		.size = mxt_get_object_size(device, memory_adr),
	};
	status = twid_transfert(device->twid, 0, &out, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \brief Write object register
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to register
 * \param value Value to be written to register
 * \result Operation result status code
 */
status_code_t mxt_write_config_reg(struct mxt_device *device, mxt_memory_adr memory_adr, uint8_t value)
{
	uint8_t status;
	device->twid->iaddr = SWAP_LSB_MSB(memory_adr);
	device->twid->isize = 2;
	struct _buffer out = {
		.data = &value,
		.size = sizeof(value),
	};
	status = twid_transfert(device->twid, 0, &out, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return STATUS_OK;
}

/**
 * \brief Closes the twi connection and frees memory.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
status_code_t mxt_close_device(struct mxt_device *device)
{
	return STATUS_OK;
}

/**
 * \brief Set message handler
 *
 * \param *device Pointer to mxt_device instance
 * \param handler Message handler function
 */
void mxt_set_message_handler(struct mxt_device *device, mxt_message_handler_t handler)
{
	device->handler = handler;
}

/**
 * \brief Report if there is any pending messages in the queue
 *
 * \param *device Pointer to mxt_device instance
 * \return Return /CHG pin status
 */
bool mxt_is_message_pending(struct mxt_device *device)
{
	return pio_get(&device->chg_pin) ? true : false;
}

/**
 * \brief Get pending message count
 *
 * \param *device Pointer to mxt_device instance
 * \return Number of pending messages in the queue
 */
int8_t mxt_get_message_count(struct mxt_device *device)
{
	uint8_t count_tmp;
	uint8_t status;
	uint16_t obj_adr = mxt_get_object_address(device, MXT_SPT_MESSAGECOUNT_T44, 0);

	device->twid->iaddr = SWAP_LSB_MSB(obj_adr);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = &count_tmp,
		.size = sizeof(count_tmp),
	};
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	twid_wait_transfert(device->twid);
	return count_tmp;
}

/**
 * \brief Get next message in queue
 *
 * \param *device Pointer to mxt_device instance
 * \param *message Pointer to mxt_message instance
 * \return Operation result status code
 */
status_code_t mxt_read_message(struct mxt_device *device, struct mxt_conf_messageprocessor_t5 *message)
{
	uint8_t status;
	uint16_t obj_adr = mxt_get_object_address(device,
			MXT_GEN_MESSAGEPROCESSOR_T5, 0);

	/* Initializing the TWI packet to send to the slave */

/*
	twi_package_t packet = {
		.addr[0]      = obj_adr,
#ifdef CONF_VALIDATE_MESSAGES
		.addr[1]      = (obj_adr >> 8) | 0x80,
#else
		.addr[1]      = obj_adr >> 8,
#endif
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = message,
		.length       = MXT_TWI_MSG_SIZE_T5
	};
*/

	device->twid->iaddr = SWAP_LSB_MSB(obj_adr);
	device->twid->isize = 2;
	struct _buffer in = {
		.data = (void*)message,
		.size =  MXT_TWI_MSG_SIZE_T5,
	};
	/* Read information from the slave */
	status = twid_transfert(device->twid, &in, 0, twid_finish_transfert_callback, 0);
	if (status != TWID_SUCCESS)
		return ERR_IO_ERROR;
	else {
		twid_wait_transfert(device->twid);
#ifdef CONF_VALIDATE_MESSAGES
		return mxt_validate_message(&packet);
#else
		return STATUS_OK;
#endif
	}
}

/**
 * \brief Read next touch event in queue, skip other events (other events are
 *        lost)
 *
 * \param *device Pointer to mxt_device instance
 * \param *touch_event Pointer to mxt_touch_event instance
 * \return Operation result status code
 */
status_code_t mxt_read_touch_event(struct mxt_device *device, struct mxt_touch_event *touch_event)
{
	uint8_t obj_type, status;
	struct mxt_conf_messageprocessor_t5 message;

	while (!mxt_is_message_pending(device)) {
		if((status = mxt_read_message(device, &message)) != STATUS_OK) {
			return (status_code_t)status;
		}
		obj_type = mxt_get_object_type(device, &message);
		if (obj_type == MXT_TOUCH_MULTITOUCHSCREEN_T9) {
			touch_event->id = (message.reportid - device->multitouch_report_offset);
			touch_event->status = message.message[0];
			touch_event->x = (message.message[1] << 4) | ((message.message[3] & 0xf0) >> 4);
			touch_event->y = (message.message[2] << 4) | (message.message[3] & 0x0f);
			touch_event->size = message.message[4];
			return STATUS_OK;
		}
	}
	return ERR_BAD_DATA;
}

/**
 * \brief Get object type from message
 *
 * \param *device Pointer to mxt_device instance
 * \param *message Message buffer
 * \return Operation
 */
enum mxt_object_type mxt_get_object_type(struct mxt_device *device, struct mxt_conf_messageprocessor_t5 *message)
{
	return (enum mxt_object_type)(device->report_id_map[message->reportid].object_type);
}

/**
 * \brief Process message queue on maXTouch device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
status_code_t mxt_process_messages(struct mxt_device *device)
{
	struct mxt_conf_messageprocessor_t5 message;
	uint8_t status;

	mxt_message_handler_t mxt_message_handler;
	mxt_message_handler = (mxt_message_handler_t)device->handler;

	if (device->handler == NULL) {
		return ERR_BAD_ADDRESS;
	}

	while (mxt_is_message_pending(device)) {
		if ((status = mxt_read_message(device, &message)) != STATUS_OK) {
			return (status_code_t)status;
		} else {
			mxt_message_handler(device, &message);
		}
	}
	return STATUS_OK;
}

