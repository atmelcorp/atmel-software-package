/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include <assert.h>
#include <string.h>

#include "barriers.h"
#include "board.h"
#include "eefc.h"
#include "errno.h"
#include "flashd.h"
#include "intmath.h"
#include "mm/cache.h"
#include "trace.h"
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define MAX_PAGE_SIZE 512
#define MAX_LOCK_REGIONS 128

static uint32_t page_buffer[MAX_PAGE_SIZE / sizeof(uint32_t)];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

int flashd_initialize(struct _flash* flash, Eefc* eefc)
{
	int i, rc;
	uint32_t planes, plane_size;
	uint32_t lock_size;

	if (!flash)
		return -EINVAL;

	memset(flash, 0, sizeof(*flash));
	flash->eefc = eefc;

	eefc_disable_frdy_it(flash->eefc);

	rc = eefc_perform_command(flash->eefc, EEFC_FCR_FCMD_GETD, 0);
	if (rc < 0)
		return rc;

	/* FL_ID (skip value) */
	eefc_get_result(flash->eefc);

	/* FL_SIZE */
	flash->total_size = eefc_get_result(flash->eefc);

	/* FL_PAGE_SIZE */
	flash->page_size = eefc_get_result(flash->eefc);
	if (flash->page_size > MAX_PAGE_SIZE)
		return -ENOTSUP;

	/* FL_NB_PLANE (check that only 1 plane available) */
	planes = eefc_get_result(flash->eefc);
	if (planes != 1)
		return -ENOTSUP;

	/* FL_PLANE[0] (check that plane covers full flash) */
	plane_size = eefc_get_result(flash->eefc);
	if (plane_size != flash->total_size)
		return -ENOTSUP;

	/* FL_NB_LOCK (number of lock regions) */
	flash->lock_count = eefc_get_result(flash->eefc);
	if (flash->lock_count > MAX_LOCK_REGIONS)
		return -ENOTSUP;

	/* FL_LOCK[i] (size of lock regions, check that is coherent) */
	lock_size = flash->total_size / flash->lock_count;
	for (i = 0; i < flash->lock_count; i++) {
		uint32_t size = eefc_get_result(flash->eefc);
		if (size != lock_size)
			return -ENOTSUP;
	}

	/* FL_NB_GPNVM (number of GPNVM bits) */
	flash->gpnvm_count = eefc_get_result(flash->eefc);

	/* Report erase size (hard-coded for now) */
	/* 16 pages is the only value compatible with all sectors */
	flash->erase_size = 16 * flash->page_size;

	return 0;
}

int flashd_read_unique_id(struct _flash* flash, uint8_t* uid)
{
	int rc;

	board_cfg_mpu_for_flash_write();

	rc = eefc_read_unique_id(flash->eefc, uid);

	board_cfg_mpu_for_flash_read();

	return rc;
}

int flashd_get_gpnvm(struct _flash* flash, uint8_t gpnvm, bool* value)
{
	int rc;

	if (gpnvm >= flash->gpnvm_count)
		return -EINVAL;

	/* Get GPNVMs status */
	rc = eefc_perform_command(flash->eefc, EEFC_FCR_FCMD_GGPB, 0);
	if (rc < 0)
		return rc;

	/* Check if GPNVM is set */
	*value = ((eefc_get_result(flash->eefc) & (1 << gpnvm)) != 0);

	return 0;
}

int flashd_get_gpnvm_bits(struct _flash* flash, uint8_t gpnvm_start, uint8_t gpnvm_end, uint32_t* value)
{
	int rc, i;
	uint32_t val = 0;
	bool bit;

	if (gpnvm_start > gpnvm_end)
		return -EINVAL;
	if (gpnvm_start > flash->gpnvm_count)
		return -EINVAL;
	if (gpnvm_end > flash->gpnvm_count)
		return -EINVAL;

	for (i = gpnvm_end; i >= gpnvm_start; i--) {
		rc = flashd_get_gpnvm(flash, i, &bit);
		if (rc < 0)
			return rc;

		val <<= 1;
		if (bit)
			val |= 1;
	}

	*value = val;

	return 0;
}

int flashd_set_gpnvm(struct _flash* flash, uint8_t gpnvm, bool value)
{
	bool prev_value;
	int rc;

	rc = flashd_get_gpnvm(flash, gpnvm, &prev_value);
	if (rc < 0)
		return rc;

	if (prev_value != value) {
		rc = eefc_perform_command(flash->eefc,
				value ? EEFC_FCR_FCMD_SGPB : EEFC_FCR_FCMD_CGPB, gpnvm);
		if (rc < 0)
			return rc;
	}
	return 0;
}

int flashd_set_gpnvm_bits(struct _flash* flash, uint8_t gpnvm_start, uint8_t gpnvm_end, uint32_t value)
{
	int rc, i;

	if (gpnvm_start > gpnvm_end)
		return -EINVAL;
	if (gpnvm_start > flash->gpnvm_count)
		return -EINVAL;
	if (gpnvm_end > flash->gpnvm_count)
		return -EINVAL;

	for (i = gpnvm_start; i <= gpnvm_end; i++) {
		rc = flashd_set_gpnvm(flash, i, (value & 1) != 0);
		if (rc < 0)
			return rc;

		value >>= 1;
	}

	return 0;
}

int flashd_erase(struct _flash* flash)
{
	cache_invalidate_region((void*)IFLASH_ADDR, flash->total_size);
	return eefc_perform_command(flash->eefc, EEFC_FCR_FCMD_EA, 0);
}

int flashd_erase_block(struct _flash* flash, uint32_t addr, uint32_t length)
{
	uint32_t page, farg;

	if (addr % flash->erase_size != 0)
		return -EINVAL;

	if (length != flash->erase_size)
		return -EINVAL;

	page = addr / flash->page_size;

	/* Get FARG field for EPA command:
	 * The first page to be erased is specified in the FARG[15:2] field of
	 * the MC_FCR register.
	 *
	 * The 2 lowest bits of the FARG field define the number of pages to
	 * be erased (FARG[1:0]).
	 */
	switch (flash->erase_size / flash->page_size) {
	case 32:
		farg = page | 3; /* 32 pages */
		break;
	case 16:
		farg = page | 2; /* 16 pages */
		break;
	case 8:
		farg = page | 1; /* 8 pages */
		break;
	case 4:
		farg = page; /* 4 pages */
		break;
	default:
		return -EINVAL;
	}

	cache_invalidate_region((void*)(IFLASH_ADDR + addr), flash->erase_size);
	return eefc_perform_command(flash->eefc, EEFC_FCR_FCMD_EPA, farg);
}

int flashd_read(struct _flash* flash, uint32_t addr, uint8_t* data, uint32_t length)
{
	if ((addr + length) > flash->total_size)
		return -EINVAL;

	memcpy(data, (uint8_t*)(IFLASH_ADDR + addr), length);

	return 0;
}

int flashd_write(struct _flash* flash, uint32_t addr, const uint8_t* data, uint32_t length)
{
	int i, rc = 0;
	uint32_t offset = 0;

	if ((addr + length) > flash->total_size)
		return -EINVAL;

	board_cfg_mpu_for_flash_write();

	while (offset < length) {
		/* Compute number of bytes to program in page */
		uint32_t page = (addr + offset) / flash->page_size;
		uint32_t page_offset = (addr + offset) - page * flash->page_size;
		uint32_t write_size = min_u32(length - offset, flash->page_size - page_offset);
		volatile uint32_t* flashptr = (uint32_t*)(IFLASH_ADDR + page * flash->page_size);

		/* if data does not cover full page, read existing data from flash */
		if (page_offset > 0 || write_size < flash->page_size)
			for (i = 0; i < flash->page_size / sizeof(uint32_t); i++)
				page_buffer[i] = flashptr[i];

		/* overwrite buffer with new data to flash */
		memcpy(((uint8_t*)page_buffer) + page_offset, data + offset, write_size);

		/* copy from buffer to flash, use barriers to force write order */
		for (i = 0; i < flash->page_size / sizeof(uint32_t); i++) {
			flashptr[i] = page_buffer[i];
			dsb();
		}

		/* Send "erase write page" command */
		rc = eefc_perform_command(flash->eefc, EEFC_FCR_FCMD_WP, page);
		if (rc < 0)
			break;

		offset += write_size;
	}

	board_cfg_mpu_for_flash_read();

	return rc;
}
