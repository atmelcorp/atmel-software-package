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

#ifndef MPU_ARMV7M_H_
#define MPU_ARMV7M_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "mm/mpu.h"

/*----------------------------------------------------------------------------
 *        Exported definitions
 *----------------------------------------------------------------------------*/

/* Region Address and Index */
#define MPU_REGION(region, addr) (((addr) & MPU_RBAR_ADDR_Msk) |\
                                  MPU_RBAR_REGION(region) | MPU_RBAR_VALID)

/* Region Sizes: region size is 2^(value+1)*/
#define MPU_REGION_SIZE(value) (MPU_RASR_SIZE(value))

/* Bitfield to disable some subregions
 * (1 bit for each 1/8 of region, region must be bigger than 128 bytes) */
#define MPU_SUBREGION_DISABLE(value) (MPU_RASR_SRD(value))

/* --- Access Privilege constants --- */

/* Access Privilege: no access for all */
#define MPU_AP_NOACCESS                (MPU_RASR_AP(0))

/* Access Privilege: no access for unprivileged, readonly for privileged */
#define MPU_AP_NOACCESS_PRIV_READONLY  (MPU_RASR_AP(5))

/* Access Privilege: no access for unprivileged, read/write for privileged */
#define MPU_AP_NOACCESS_PRIV_READWRITE (MPU_RASR_AP(1))

/* Access Privilege: readonly for all */
#define MPU_AP_READONLY                (MPU_RASR_AP(7))

/* Access Privilege: readonly for unprivileged, read/write for privileged */
#define MPU_AP_READONLY_PRIV_READWRITE (MPU_RASR_AP(2))

/* Access Privilege: read/write for all */
#define MPU_AP_READWRITE               (MPU_RASR_AP(3))

/* --- Memory Types Attributes --- */

/* Strongly-Ordered Shareable */
#define MPU_ATTR_STRONGLY_ORDERED (MPU_RASR_TEX(0))

/* Device Shareable */
#define MPU_ATTR_DEVICE           (MPU_RASR_TEX(0) | MPU_RASR_B)

/* Normal, Write-Through Read Allocate */
#define MPU_ATTR_NORMAL_WT        (MPU_RASR_TEX(0) | MPU_RASR_C)

/* Normal, Write-Back Read Allocate */
#define MPU_ATTR_NORMAL_WB        (MPU_RASR_TEX(0) | MPU_RASR_C | MPU_RASR_B)

/* Normal, Write-Back Read/Write Allocate */
#define MPU_ATTR_NORMAL_WB_WA     (MPU_RASR_TEX(1) | MPU_RASR_C | MPU_RASR_B)

/* Normal, Non-cacheable */
#define MPU_ATTR_NORMAL           (MPU_RASR_TEX(1))

/* Other Attributes */
#define MPU_ATTR_SHAREABLE     (MPU_RASR_S)
#define MPU_ATTR_EXECUTE_NEVER (MPU_RASR_XN)
#define MPU_ATTR_ENABLE        (MPU_RASR_ENABLE)

#endif  /* MPU_ARMV7M_H_ */
