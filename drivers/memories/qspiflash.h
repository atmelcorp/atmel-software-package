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

#ifndef _QSPIFLASH_H_
#define _QSPIFLASH_H_

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

struct _qspiflash;

typedef bool (*qspiflash_initialize_t)(struct _qspiflash *flash);
typedef bool (*qspiflash_switch_to_quad)(struct _qspiflash *flash);

/** Describes a QSPI flash device parameters. */
struct _qspiflash_desc {
	const char *name;
	uint32_t jedec_id;
	uint32_t num_blocks;
	uint32_t block_size;
	uint32_t page_size;
	uint8_t num_mode_cycles;
	uint8_t num_dummy_cycles;
	uint8_t normal_read_mode;
	uint8_t continuous_read_mode;
	uint32_t features;
	qspiflash_initialize_t init;
	qspiflash_switch_to_quad switch_to_quad;
};

enum _qspiflash_feature {
	QSPIFLASH_FEAT_ERASE_4K = (1 << 0),
};

struct _qspiflash {
    Qspi *qspi;
    struct _qspiflash_desc desc;
    uint32_t ifr_width;
    bool mode_addr4;
};

/*----------------------------------------------------------------------------
 *        Public Functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern bool qspiflash_configure(struct _qspiflash *flash, Qspi *qspi);
extern bool qspiflash_read_status(const struct _qspiflash *flash, uint8_t *status);
extern bool qspiflash_wait_ready(const struct _qspiflash *flash, uint32_t timeout);
extern bool qspiflash_read_jedec_id(const struct _qspiflash *flash, uint32_t *jedec_id);
extern bool qspiflash_read(const struct _qspiflash *flash, uint32_t addr, void *data, uint32_t length);
extern bool qspiflash_erase_chip(const struct _qspiflash *flash);
extern bool qspiflash_erase_block(const struct _qspiflash *flash, uint32_t addr, bool erase_4k);
extern bool qspiflash_write(const struct _qspiflash *flash, uint32_t addr, const void *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* _QSPIFLASH_H_ */
