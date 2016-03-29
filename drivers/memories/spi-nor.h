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

#ifndef _SPINOR_H
#define _SPINOR_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define SPINOR_JEDEC_MANUF(jedec_id)   (((jedec_id) & 0x0000FFu) >> 0)
#define SPINOR_JEDEC_DENSITY(jedec_id) (((jedec_id) & 0x001F00u) >> 8)
#define SPINOR_JEDEC_FAMILY(jedec_id)  (((jedec_id) & 0x00E000u) >> 13)
#define SPINOR_JEDEC_VERSION(jedec_id) (((jedec_id) & 0x1F0000u) >> 16)
#define SPINOR_JEDEC_SUBCODE(jedec_id) (((jedec_id) & 0xE00000u) >> 21)

#define SPINOR_MANUF_SPANSION       (0x01u)
#define SPINOR_MANUF_ATMEL          (0x1fu)
#define SPINOR_MANUF_MICRON         (0x20u)
#define SPINOR_MANUF_SST            (0xbfu)
#define SPINOR_MANUF_MACRONIX       (0xc2u)
#define SPINOR_MANUF_WINBOND        (0xefu)

#define SPINOR_FLAG_ERASE_4K        (0x00000001u)
#define SPINOR_FLAG_ERASE_32K       (0x00000002u)
#define SPINOR_FLAG_ERASE_64K       (0x00000004u)
#define SPINOR_FLAG_ERASE_256K      (0x00000008u)
#define SPINOR_FLAG_QUAD            (0x00000010u)
#define SPINOR_FLAG_QPP             (0x00000020u) /* Quad Page Programming */

/** Describes SPI NOR flash device parameters */
struct _spi_nor_desc {
	const char *name;    /*< Device name */
	uint32_t jedec_id;   /*< JEDEC ID */
	uint32_t page_size;  /*< Page size in bytes */
	uint32_t size;       /*< Total size in bytes */
	uint32_t flags;      /*< Feature flags */
};

#ifdef __cplusplus
extern "C" {
#endif

extern const struct _spi_nor_desc *spi_nor_find(uint32_t jedec_id);

#ifdef __cplusplus
}
#endif

#endif /* _SPINOR_H */
