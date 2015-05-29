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

#include "core/pio.h"
#include "core/pmc.h"
#include "core/aic.h"

#include "bus/spi.h"

#include "mem/at25df321.h"

#include "utils/trace.h"

#include <stdio.h>

#define AT25DF321_ID ID_SPI0
#define AT25DF321_ADDR SPI0

#define AT25DF321_FREQ 65
#define AT25DF321_LOW_FREQ 25

#define AT25DF321_SPI_MODE SPI_CSR_NCPHA

enum _opcodes {
	READ_ARRAY    = 0x0B,
	READ_ARRAY_LF = 0x03,
	WRITE_ENABLE  = 0x06,
	WRITE_DISABLE = 0x04,
	PROGRAM       = 0x02,
	READ_STATUS   = 0x05,
	WRITE_STATUS  = 0x01,
	DEVICE_INFO   = 0x9F,
	PROT_STATUS   = 0x3C
};

static void _write_addr(uint32_t addr)
{
	spi_write(AT25DF321_ADDR, 0, (addr & 0x7F0000) >> 16);
	spi_write(AT25DF321_ADDR, 0, (addr & 0x00FF00) >> 8);
	spi_write(AT25DF321_ADDR, 0, (addr & 0x0000FF));
}

static inline void _write_opcode(enum _opcodes opcode)
{
	spi_write(AT25DF321_ADDR, 0, opcode);
}

static inline void _write_garbage(void)
{
	spi_write(AT25DF321_ADDR, 0, 0x42);
}

static inline void _write_data(uint8_t data)
{
	spi_write(AT25DF321_ADDR, 0, data);
}

static uint8_t _read_data(void)
{
	_write_garbage();
	return spi_read(AT25DF321_ADDR) & 0xFF;
}

static inline void _assert_cs_auto_release(void)
{
	spi_configure_cs_mode(AT25DF321_ADDR, 0, 0);
}

static inline void _assert_cs(void)
{
	spi_configure_cs_mode(AT25DF321_ADDR, 0, 1);
}

static inline void _release_cs(void)
{
	spi_release_cs(AT25DF321_ADDR);
}

void at25df321_open()
{
	trace_debug("Opening At25DF321 flash device.\r\n");
	static const struct _pin at25df321_pins[] = PINS_SERIAL_FLASH;
	pio_configure(at25df321_pins, ARRAY_SIZE(at25df321_pins));
	pmc_enable_peripheral(AT25DF321_ID);
	/* Configure in master mode (no fault detection) */
	spi_configure(AT25DF321_ADDR,
		      SPI_MR_MSTR | SPI_MR_MODFDIS | SPI_MR_PCS(0x0));
	spi_configure_cs(AT25DF321_ADDR, 0, AT25DF321_FREQ,
			 0, 0, AT25DF321_SPI_MODE, 1);
	spi_enable(AT25DF321_ADDR);
}

void at25df321_print_device_info(void)
{
	unsigned int device_info = 0;
	int i = 0;

	spi_configure_cs_mode(AT25DF321_ADDR, 0, 1);

	_write_opcode(DEVICE_INFO);
	for (i = 0; i < 4; ++i) {
		device_info <<= 8;
		device_info |= _read_data();
	}

	spi_release_cs(AT25DF321_ADDR);

	printf("AT25DF321:\r\n");
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

void at25df321_read_stream(uint32_t start_addr,
			   uint8_t* data, uint32_t length)
{
	spi_configure_cs_mode(AT25DF321_ADDR, 0, 1);

	trace_debug("Start flash read at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	_write_opcode(READ_ARRAY);
	_write_addr(start_addr);
	/* According to datasheet, a "don't care" octet must be sent */
	_write_garbage();
	while (length--) {
		*data++ = _read_data();
	}

	spi_release_cs(AT25DF321_ADDR);
}

void at25df321_read_stream_low_speed(uint32_t start_addr,
				     uint8_t* data, uint32_t length)
{
	spi_configure_cs_mode(AT25DF321_ADDR, 0, 1);
	spi_configure_cs(AT25DF321_ADDR, 0, AT25DF321_LOW_FREQ,
			 0, 0, AT25DF321_SPI_MODE, 1);

	trace_debug("Start flash read at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	_write_opcode(READ_ARRAY_LF);
	_write_addr(start_addr);

	while (length--) {
		*data++ = _read_data();
	}

	spi_release_cs(AT25DF321_ADDR);

	spi_configure_cs(AT25DF321_ADDR, 0, AT25DF321_FREQ,
			 0, 0, AT25DF321_SPI_MODE, 1);
}

void at25df321_unlock_sectors()
{
	/* Enable wright (chip select MUST be released before doing
	 * anything else */
	_assert_cs_auto_release();
	_write_opcode(WRITE_ENABLE);

	_assert_cs();
	_write_opcode(WRITE_STATUS);
	_write_data(0x0);
	_release_cs();
}

void at25df321_write_stream(uint32_t start_addr,
			    const uint8_t* data, uint32_t length)
{
	trace_debug("Start flash write at address: %X\r\n",
		    (unsigned int)(start_addr & 0x7FFFFF));

	/* Enable wright (chip select MUST be released before doing
	 * anything else */
	_assert_cs_auto_release();
	_write_opcode(WRITE_ENABLE);

	uint32_t current_status = at25df321_get_status();

	if (!(current_status & AT25DF321_WRITE_ENABLED)) {
		trace_error("Cannot write to flash device. "
			    "Write is not enabled");
		return;
	}

	_assert_cs();
	_write_opcode(PROGRAM);

	while (length--) {
		_write_data(*data++);
	}

	_release_cs();

	/* Wait for the write to be applied */
	current_status = at25df321_get_status();
	while (current_status & AT25DF321_DEVICE_BSY) {
		current_status = at25df321_get_status();
	}
	if (current_status & AT25DF321_ERASE_PRG_ERROR) {
		trace_error(__FILE__":%i:Write operation failed", __LINE__);
	}
}

unsigned char at25df321_is_protected(uint32_t addr)
{
	_assert_cs();
	_write_opcode(PROT_STATUS);
	uint8_t value = _read_data();
	_release_cs();
	return value;
}

uint32_t at25df321_get_status(void)
{
	_assert_cs();

	_write_opcode(READ_STATUS);
	unsigned int status = _read_data();
	trace_debug("Status value: %X\r\n", status);

	spi_release_cs(AT25DF321_ADDR);

	return status;
}

void at25df321_close()
{
	/* TODO: cleanly close device */
	spi_disable(AT25DF321_ADDR);
	pmc_disable_peripheral(AT25DF321_ID);
}
