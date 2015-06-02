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

#include "resources/compiler_defines.h"

#include "board.h"
#include "chip.h"

#include "core/pio.h"
#include "core/pmc.h"
#include "core/aic.h"

#include "bus/spi.h"

#include "mem/at25dfx.h"

#include "utils/trace.h"

#include <stdio.h>
#include <assert.h>

enum _opcodes {
	READ_ARRAY    = 0x0B,
	READ_ARRAY_LF = 0x03,
	WRITE_ENABLE  = 0x06,
	WRITE_DISABLE = 0x04,
	PROGRAM       = 0x02,
	READ_STATUS   = 0x05,
	WRITE_STATUS  = 0x01,
	DEVICE_INFO   = 0x9F,
	PROT_STATUS   = 0x3C,

	ERASE_4K      = 0x20,
	ERASE_32K     = 0x52,
	ERASE_64K     = 0xD8,
	CHIP_ERASE    = 0x60
};

static void _write_addr(uint32_t addr)
{
	spi_write(AT25DFX_ADDR, 0, (addr & 0x7F0000) >> 16);
	spi_write(AT25DFX_ADDR, 0, (addr & 0x00FF00) >> 8);
	spi_write(AT25DFX_ADDR, 0, (addr & 0x0000FF));
}

static void _write_opcode(enum _opcodes opcode)
{
	spi_write(AT25DFX_ADDR, 0, opcode);
}

static void _write_garbage(void)
{
	spi_write(AT25DFX_ADDR, 0, 0x42);
}

static void _write_data(uint8_t data)
{
	spi_write(AT25DFX_ADDR, 0, data);
}

static uint8_t _read_data(void)
{
	_write_garbage();
	return spi_read(AT25DFX_ADDR) & 0xFF;
}

static void _assert_cs_auto_release(void)
{
	spi_configure_cs_mode(AT25DFX_ADDR, 0, 0);
}

static void _assert_cs(void)
{
	spi_configure_cs_mode(AT25DFX_ADDR, 0, 1);
}

static void _release_cs(void)
{
	spi_release_cs(AT25DFX_ADDR);
}

static uint32_t _at25dfx_enable_write(void)
{
	/* Enable write (chip select MUST be released before doing
	 * anything else) */
	_assert_cs_auto_release();
	_write_opcode(WRITE_ENABLE);

	if (!at25dfx_check_status(AT25DFX_WRITE_ENABLED)) {
		return AT25DFX_WRITE_ERROR;
	}

	return AT25DFX_SUCCESS;
}

void at25dfx_open()
{
	trace_debug("Opening AT25DFx flash device.\r\n");
	static const struct _pin at25dfx_pins[] = PINS_SERIAL_FLASH;
	pio_configure(at25dfx_pins, ARRAY_SIZE(at25dfx_pins));
	uint32_t id = get_spi_id_from_addr(AT25DFX_ADDR);
	pmc_enable_peripheral(id);
	/* Configure in master mode (no fault detection) */
	spi_configure(AT25DFX_ADDR,
		      SPI_MR_MSTR | SPI_MR_MODFDIS | SPI_MR_PCS(0x0));
	spi_configure_cs(AT25DFX_ADDR, 0, AT25DFX_FREQ,
			 AT25DFX_DLYBS, AT25DFX_DLYCT,
			 AT25DFX_SPI_MODE, 1);
	spi_enable(AT25DFX_ADDR);
}

void at25dfx_print_device_info(void)
{
	unsigned int device_info = 0;
	int i = 0;

	spi_configure_cs_mode(AT25DFX_ADDR, 0, 1);

	_write_opcode(DEVICE_INFO);
	for (i = 0; i < 4; ++i) {
		device_info <<= 8;
		device_info |= _read_data();
	}

	spi_release_cs(AT25DFX_ADDR);

	printf("Device info:\r\n");
	printf("\t- Manufacturer ID:\t\t0x%X "
	       "(Should be equal to 0x1F)\r\n", device_info >> 24);
	printf("\t- Device Family Code:\t\t0x%X\r\n",
	       (device_info & 0x00E00000) >> 21);
	printf("\t- Device Density Code:\t\t0x%X\r\n",
	       (device_info & 0x001F0000) >> 16);
	printf("\t- Device Sub Code:\t\t0x%X\r\n",
	       (device_info & 0xE000) >> 13);
	printf("\t- Device Product Version:\t0x%X\r\n",
	       (device_info & 0x1F00) >> 8);
}

uint32_t at25dfx_read_stream(uint32_t start_addr,
			   uint8_t* data, uint32_t length)
{
	uint32_t size_read = length;
	spi_configure_cs_mode(AT25DFX_ADDR, 0, 1);

	trace_debug("Start flash read at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	_write_opcode(READ_ARRAY);
	_write_addr(start_addr);
	/* According to datasheet, a "don't care" octet must be sent */
	_write_garbage();
	while (length--) {
		*data++ = _read_data();
	}

	spi_release_cs(AT25DFX_ADDR);

	size_read -= length;
	return size_read;
}

uint32_t at25dfx_read_stream_low_speed(uint32_t start_addr,
				     uint8_t* data, uint32_t length)
{
	uint32_t size_read = length;
	spi_configure_cs_mode(AT25DFX_ADDR, 0, 1);
	spi_configure_cs(AT25DFX_ADDR, 0, AT25DFX_LOW_FREQ,
			 AT25DFX_DLYBS, AT25DFX_DLYCT,
			 AT25DFX_SPI_MODE, 1);

	trace_debug("Start flash read at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	_write_opcode(READ_ARRAY_LF);
	_write_addr(start_addr);

	while (length--) {
		*data++ = _read_data();
	}

	spi_release_cs(AT25DFX_ADDR);

	spi_configure_cs(AT25DFX_ADDR, 0, AT25DFX_FREQ,
			 AT25DFX_DLYBS, AT25DFX_DLYCT,
			 AT25DFX_SPI_MODE, 1);

	size_read -= length;
	return size_read;
}

uint32_t at25dfx_unlock_sectors()
{
	trace_debug("Unlocking all sectors.\r\n");

	uint32_t status = _at25dfx_enable_write();
	if (status) {
		return status;
	}

	_assert_cs();
	_write_opcode(WRITE_STATUS);
	_write_data(0x0);
	_release_cs();

	return AT25DFX_SUCCESS;
}

uint32_t at25dfx_check_status(uint32_t mask)
{
	uint32_t status = at25dfx_get_status();
	if (status & mask) {
		return status & mask;
	}
	return AT25DFX_SUCCESS;
}

uint32_t at25dfx_write_stream(uint32_t start_addr,
			   const uint8_t* data, uint32_t length)
{
	trace_debug("Start flash write at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	uint32_t status = at25dfx_check_status(AT25DFX_DEVICE_BSY);
	if (status) {
		return status;
	}

	status = _at25dfx_enable_write();
	if (status) {
		return status;
	}

	_assert_cs();
	_write_opcode(PROGRAM);
	_write_addr(start_addr);
	while (length--) {
		_write_data(*data++);
	}
	_release_cs();

	return AT25DFX_SUCCESS;
}

uint32_t at25dfx_erase_block(uint32_t start_addr, uint32_t block_size)
{
	trace_debug("Erasing block at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	uint32_t status = at25dfx_check_status(AT25DFX_DEVICE_BSY);
	if (status) {
		return status;
	}

	enum _opcodes opcode = ERASE_4K;

	switch(block_size) {
	case AT25DFX_BLOCK_4K:
		assert((start_addr & ~0xFFF) == start_addr);
		opcode = ERASE_4K;
		break;
	case AT25DFX_BLOCK_32K:
		assert((start_addr & ~0x7FFF) == start_addr);
		opcode = ERASE_32K;
		break;
	case AT25DFX_BLOCK_64K:
		assert((start_addr & ~0xFFFF) == start_addr);
		opcode = ERASE_64K;
		break;
	default:
		return AT25DFX_WRITE_ERROR;
	}

	status = _at25dfx_enable_write();
	if (status) {
		return status;
	}

	_assert_cs();
	_write_opcode(opcode);
	_write_addr(start_addr);
	_release_cs();

	return AT25DFX_SUCCESS;
}

uint32_t at25dfx_erase_chip()
{
	trace_debug("Erasing all blocks");

	uint32_t status = at25dfx_check_status(AT25DFX_DEVICE_BSY);
	if (status) {
		return status;
	}

	status = _at25dfx_enable_write();
	if (status) {
		return status;
	}

	_assert_cs_auto_release();
	_write_opcode(CHIP_ERASE);

	return AT25DFX_SUCCESS;
}

unsigned char at25dfx_is_protected(uint32_t addr)
{
	_assert_cs();
	_write_opcode(PROT_STATUS);
	uint8_t value = _read_data();
	_release_cs();
	return value;
}

uint32_t at25dfx_get_status(void)
{
	_assert_cs();

	_write_opcode(READ_STATUS);
	uint32_t status = _read_data();
	trace_debug("Status value: %X\r\n",
		    (unsigned int)status);
	_release_cs();

	return status;
}

void at25dfx_close()
{
	spi_disable(AT25DFX_ADDR);
	pmc_disable_peripheral(AT25DFX_ID);
}
