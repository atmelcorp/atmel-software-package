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

#ifndef _AT25_HEADER_
#define _AT25_HEADER_

#include <stdint.h>

#define AT25_SUCCESS                  (0u)
#define AT25_DEVICE_BSY               (0x1 << 0)
#define AT25_WRITE_ENABLED            (0x1 << 1)
#define AT25_WRITE_PROT_PIN_STATUS    (0x1 << 4)
#define AT25_ERASE_PRG_ERROR          (0x1 << 5)
#define AT25_SECTOR_PROT_LOCKED       (0x1 << 7)
#define AT25_SOFT_PROT_STATUS_MSK     (0x3 << 2)
#define AT25_SOFT_ALL_PROTECTED       (AT25_SOFT_PROT_STATUS_MSK)
#define AT25_SOFT_SOME_PROTECTED      (AT25_SOFT_PROT_STATUS_MSK & (0x01))
#define AT25_WRITE_ERROR              ~AT25_WRITE_ENABLED

#define AT25DFX_BLOCK_4K  (1)
#define AT25DFX_BLOCK_32K (2)
#define AT25DFX_BLOCK_64K (3)

#ifdef __cplusplus
extern "C" {
#endif

extern void at25_open(void);
extern void at25_print_device_info(void);
extern uint32_t at25_get_status(void);
extern uint32_t at25_read_stream(uint32_t start_addr,
				  uint8_t* data, uint32_t length);
extern uint32_t at25_read_stream_low_speed(uint32_t start_addr,
					    uint8_t* data, uint32_t length);
extern uint32_t at25_unlock_sectors(void);
extern uint32_t at25_write_stream(uint32_t start_addr,
				  const uint8_t* data, uint32_t length);
extern uint32_t at25_erase_block(uint32_t start_addr, uint32_t end_addr);
extern uint32_t at25_erase_chip(void);
extern unsigned char at25_is_protected(uint32_t addr);
extern uint32_t at25_check_status(uint32_t mask);
extern void at25_close(void);

#ifdef __cplusplus
}
#endif

#endif /* _AT25_HEADER_ */
