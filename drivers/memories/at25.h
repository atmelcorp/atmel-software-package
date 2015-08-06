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

#ifndef _AT25DFX_HEADER_
#define _AT25DFX_HEADER_

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include "peripherals/spid.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Device is protected, operation cannot be carried out. */
#define AT25_ERROR_PROTECTED        1
/** Device is busy executing a command. */
#define AT25_ERROR_BUSY             2
/** There was a problem while trying to program page data. */
#define AT25_ERROR_PROGRAM          3
/** There was an SPI communication error. */
#define AT25_ERROR_SPI              4

/** Device ready/busy status bit. */
#define AT25_STATUS_RDYBSY          (1 << 0)
/** Device is ready. */
#define AT25_STATUS_RDYBSY_READY    (0 << 0)
/** Device is busy with internal operations. */
#define AT25_STATUS_RDYBSY_BUSY     (1 << 0)
/** Write enable latch status bit. */
#define AT25_STATUS_WEL             (1 << 1)
/** Device is not write enabled. */
#define AT25_STATUS_WEL_DISABLED    (0 << 1)
/** Device is write enabled. */
#define AT25_STATUS_WEL_ENABLED     (1 << 1)
/** Software protection status bitfield. */
#define AT25_STATUS_SWP             (3 << 2)
/** All sectors are software protected. */
#define AT25_STATUS_SWP_PROTALL     (3 << 2)
/** Some sectors are software protected. */
#define AT25_STATUS_SWP_PROTSOME    (1 << 2)
/** No sector is software protected. */
#define AT25_STATUS_SWP_PROTNONE    (0 << 2)
/** Write protect pin status bit. */
#define AT25_STATUS_WPP             (1 << 4)
/** Write protect signal is not asserted. */
#define AT25_STATUS_WPP_NOTASSERTED (0 << 4)
/** Write protect signal is asserted. */
#define AT25_STATUS_WPP_ASSERTED    (1 << 4)
/** Erase/program error bit. */
#define AT25_STATUS_EPE             (1 << 5)
/** Erase or program operation was successful. */
#define AT25_STATUS_EPE_SUCCESS     (0 << 5)
/** Erase or program error detected. */
#define AT25_STATUS_EPE_ERROR       (1 << 5)
/** Sector protection registers locked bit. */
#define AT25_STATUS_SPRL            (1 << 7)
/** Sector protection registers are unlocked. */
#define AT25_STATUS_SPRL_UNLOCKED   (0 << 7)
/** Sector protection registers are locked. */
#define AT25_STATUS_SPRL_LOCKED     (1 << 7)

/** Read array command code. */
#define AT25_READ_ARRAY             0x0B
/** Read array (low frequency) command code. */
#define AT25_READ_ARRAY_LF          0x03
/** Block erase command code (4K block). */
#define AT25_BLOCK_ERASE_4K         0x20
/** Block erase command code (32K block). */
#define AT25_BLOCK_ERASE_32K        0x52
/** Block erase command code (64K block). */
#define AT25_BLOCK_ERASE_64K        0xD8
/** Chip erase command code 1. */
#define AT25_CHIP_ERASE_1           0x60
/** Chip erase command code 2. */
#define AT25_CHIP_ERASE_2           0xC7
/** Byte/page program command code. */
#define AT25_BYTE_PAGE_PROGRAM      0x02
/** Sequential program mode command code 1. */
#define AT25_SEQUENTIAL_PROGRAM_1   0xAD
/** Sequential program mode command code 2. */
#define AT25_SEQUENTIAL_PROGRAM_2   0xAF
/** Write enable command code. */
#define AT25_WRITE_ENABLE           0x06
/** Write disable command code. */
#define AT25_WRITE_DISABLE          0x04
/** Protect sector command code. */
#define AT25_PROTECT_SECTOR         0x36
/** Unprotect sector command code. */
#define AT25_UNPROTECT_SECTOR       0x39
/** Read sector protection registers command code. */
#define AT25_READ_SECTOR_PROT       0x3C
/** Read status register command code. */
#define AT25_READ_STATUS            0x05
/** Write status register command code. */
#define AT25_WRITE_STATUS           0x01
/** Read manufacturer and device ID command code. */
#define AT25_READ_JEDEC_ID          0x9F
/** Deep power-down command code. */
#define AT25_DEEP_PDOWN             0xB9
/** Resume from deep power-down command code. */
#define AT25_RES_DEEP_PDOWN         0xAB

/* Enter 4-BYTE ADDRESS mode  */
#define AT25_ENTER_4ADDR_MODE       0xB7
/* Exit 4-BYTE ADDRESS mode  */
#define AT25_EXIT_4ADDR_MODE        0xE9

/** SPI Flash Manufacturer JEDEC ID */
#define AT25_MANUF_ATMEL            0x1F
#define AT25_MANUF_ST               0x20
#define AT25_MANUF_WINBOND          0xEF
#define AT25_MANUF_MACRONIX         0xC2
#define AT25_MANUF_SST              0xBF

#define AT25_ADDRESS_4_BYTES        0x4B
#define AT25_ADDRESS_3_BYTES        0x3B
#define AT25_SUCCESS                0x0
#define AT25_DEVICE_NOT_SUPPORTED   0xF
#define AT25_ADDR_OOB               0xB

enum _at25_erase_cmd {
	AT25_SUPPORT_ERASE_4K = 0x1,
	AT25_SUPPORT_ERASE_32K = 0x2,
	AT25_SUPPORT_ERASE_64K = 0x4
};

/** Describes a serial firmware flash device parameters. */
struct _at25_desc {

	/** Device string name. */
	const char *name;
	/** JEDEC ID of device. */
	uint32_t jedec_id;
	/** Size of device in bytes. */
	uint32_t size;
	/** Size of one page in bytes. */
	uint32_t page_size;
	/** Block erase size in bytes. */
	uint32_t block_size;
	/** Block erase command. */
	enum _at25_erase_cmd block_erase_cmd;
};

struct _at25 {
	struct _spi_desc* spid;
	struct _at25_desc* desc;
	uint32_t addressing;
};

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t at25_check_status(struct _at25* at25, uint32_t mask);
extern void at25_wait(struct _at25* at25);
extern uint32_t at25_configure(struct _at25* at25, struct _spi_desc* spid);
extern const struct _at25_desc* at25_find_device(struct _at25* at25,
					   uint32_t jedec_id);
extern uint32_t at25_read_jedec_id(struct _at25* at25);
extern uint32_t at25_read_status(struct _at25* at25);
extern uint32_t at25_protect(struct _at25* at25);
extern uint32_t at25_unprotect(struct _at25* at25);
extern void at25_print_device_info(struct _at25* at25);
extern uint32_t at25_is_busy(struct _at25* at25);
extern uint32_t at25_read(struct _at25* at25, uint32_t addr,
			  uint8_t* data, uint32_t length);
extern uint32_t at25_erase_chip(struct _at25* at25);
extern uint32_t at25_erase_block(struct _at25* at25, uint32_t addr,
				 uint32_t erase_type);
extern uint32_t at25_write(struct _at25* at25, uint32_t addr,
			   const uint8_t* data, uint32_t length);

/**
 * \brief Exit 4-bytes address mode
 *
 * \param at25  Pointer to an AT25 driver instance.
 */
extern void at25_enter_4addr_mode(struct _at25* at25);

/**
 * \brief Exit 4-bytes address mode
 *
 * \param at25  Pointer to an AT25 driver instance.
 */
extern void at25_exit_4addr_mode(struct _at25* at25);

#ifdef __cplusplus
}
#endif

#endif /* _AT25DFX_HEADER_ */
