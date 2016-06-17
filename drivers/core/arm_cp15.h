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

#ifndef ARM_CP15_H_
#define ARM_CP15_H_

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* Determines if the T bit is set when load instructions change the PC:
 * 0 = loads to PC set the T bit
 * 1 = loads to PC do not set T bit
 */
#define CP15_L4_BIT (1u << 15)

/* RR bit Replacement strategy for I-cache and D-cache:
 * 0 = Random replacement
 * 1 = Round-robin replacement.
 */
#define CP15_RR_BIT (1u << 14)

/* V bit Location of exception vectors:
 * 0 = Normal exception vectors, address range = 0x00000000 to 0x0000001C
 * 1 = High exception vectors, address range = 0xFFFF0000 to 0xFFFF001C
 */
#define CP15_V_BIT  (1u << 13)

/* I bit I-cache enable/disable:
 * 0 = I-cache disabled
 * 1 = I-cache enabled
 */
#define CP15_I_BIT  (1u << 12)

/* R bit ROM protection */
#define CP15_R_BIT  (1u << 9)

/* S bit System protection */
#define CP15_S_BIT  (1u << 8)

/* B bit Endianness:
 * 0 = Little-endian operation
 * 1 = Big-endian operation.
 */
#define CP15_B_BIT  (1u << 7)

/* C bit Dcache enable/disable:
 * 0 = cache disabled
 * 1 = cache enabled
 */
#define CP15_C_BIT  (1u << 2)

/* A bit Alignment fault enable/disable:
 * 0 = Data address alignment fault checking disabled
 * 1 = Data address alignment fault checking enabled
 */
#define CP15_A_BIT  (1u << 1)

/* M bit MMU enable/disable: 0 = disabled 1 = enabled.
 * 0 = disabled
 * 1 = enabled
 */
#define CP15_M_BIT  (1u << 0)

/* No access Any access generates a domain fault. */
#define CP15_DOMAIN_NO_ACCESS      0x00

/* Client Accesses are checked against the access permission bits in the
 * section or page descriptor. */
#define CP15_DOMAIN_CLIENT_ACCESS  0x01

/* Manager Accesses are not checked against the access permission bits so a
 * permission fault cannot be generated. */
#define CP15_DOMAIN_MANAGER_ACCESS 0x03

/*------------------------------------------------------------------------------ */
/*         Exported functions */
/*------------------------------------------------------------------------------ */

/**
 * \brief Read the System Control Register (SCTLR).
 * \return register contents
 */
extern uint32_t cp15_read_control(void);

/**
 * \brief Modify the System Control Register (SCTLR).
 *      This register specifies the configuration used to enable and disable the
 *      caches and MMU.
 *      It is recommended that you access this register using a read-modify-
 *      write sequence.
 * \param value new value for SCTLR
 */
extern void cp15_write_control(uint32_t value);

/**
 * \brief Check is MMU is enabled.
 */
extern bool cp15_mmu_is_enabled(void);

/**
 * \brief Enable MMU.
 */
extern void cp15_mmu_enable(void);

/**
 * \brief Disable MMU.
 * This will also disable the data cache.
 */
extern void cp15_mmu_disable(void);

/**
 * \brief Modify the Domain Access Control Register (DACR).
 * \param value new value for DACR
 */
extern void cp15_write_domain_access_control(uint32_t value);

/**
 * \brief ARMv7A architecture supports two translation tables.
 *      Configure translation table base (TTB) control register 0.
 * \param value address of our page table base
 */
extern void cp15_write_ttb(uint32_t value);

/**
 * \brief Indicate CPU that L2 is in exclusive caching mode.
 */
extern void cp15_cache_set_exclusive(void);

/**
 * \brief Allow data to reside in the L1 and L2 caches at the same time.
 */
extern void cp15_cache_set_non_exclusive(void);

/**
 * \brief Invalidate all instruction cache.
 */
extern void cp15_icache_invalidate(void);

/**
 * \brief Check if instruction cache is enabled.
 */
extern bool cp15_icache_is_enabled(void);

/**
 * \brief Enable instruction cache.
 */ 
extern void cp15_icache_enable(void);

/**
 * \brief Disable instruction cache.
 */
extern void cp15_icache_disable(void);

/**
 * \brief Check if data cache is enabled.
 */
extern bool cp15_dcache_is_enabled(void);

/**
 * \brief Enable data cache.
 */
extern void cp15_dcache_enable(void);

/**
 * \brief Disable the data cache.
 */
extern void cp15_dcache_disable(void);

/**
 * \brief Clean the data cache.
 */
extern void cp15_dcache_clean(void);

/**
 * \brief Invalidate the data cache.
 */
extern void cp15_dcache_invalidate(void);

/**
 * \brief Clean & Invalidate the data cache.
 */
extern void cp15_dcache_clean_invalidate(void);

/**
 * \brief Invalidate the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void cp15_dcache_invalidate_region(uint32_t start, uint32_t end);

/**
 * \brief Clean the data cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void cp15_dcache_clean_region(uint32_t start, uint32_t end);

/**
 * \brief Clean and invalidate the data cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void cp15_dcache_clean_invalidate_region(uint32_t start, uint32_t end);

#endif /* ARM_CP15_H_ */
