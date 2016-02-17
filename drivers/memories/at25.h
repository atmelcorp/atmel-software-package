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

#ifndef _AT25_H
#define _AT25_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include "memories/spi-nor.h"
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

#define AT25_ADDRESS_4_BYTES      0x4Bu
#define AT25_ADDRESS_3_BYTES      0x3Bu

#define AT25_SUCCESS              0x0u
#define AT25_DEVICE_NOT_SUPPORTED 0xFu
#define AT25_ADDR_OOB             0xBu

struct _at25 {
	struct _spi_desc* spid;
	const struct _spi_nor_desc* desc;
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
				 uint32_t length);
extern uint32_t at25_write(struct _at25* at25, uint32_t addr,
			   const uint8_t* data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* _AT25_H */
