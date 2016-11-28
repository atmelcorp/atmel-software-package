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

#ifndef CP15_H_
#define CP15_H_

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* SCTLR: I - I-cache enable/disable
 * 0 = I-cache disabled
 * 1 = I-cache enabled
 */
#define CP15_SCTLR_I (1u << 12)

/* SCTLR: C - D-cache enable/disable
 * 0 = D-cache disabled
 * 1 = D-cache enabled
 */
#define CP15_SCTLR_C (1u << 2)

/* SCTLR: A - Alignment fault enable/disable
 * 0 = Data address alignment fault checking disabled
 * 1 = Data address alignment fault checking enabled
 */
#define CP15_SCTLR_A (1u << 1)

/* SCTLR: M - MMU enable/disable
 * 0 = disabled
 * 1 = enabled
 */
#define CP15_SCTLR_M (1u << 0)

/* ACTLR: EXCL - Exclusive L1/L2 cache control.
 * 0 = non-exclusive
 * 1 = exclusive
 */
#define CP15_ACTLR_EXCL (1u << 7)

/* No access: Any access generates a domain fault. */
#define CP15_DACR_NO_ACCESS(x) (0u << (2 * ((x) & 15)))

/* Client: Accesses are checked against the access permission bits in the
 * section or page descriptor. */
#define CP15_DACR_CLIENT_ACCESS(x) (1u << (2 * ((x) & 15)))

/* Manager: Accesses are not checked against the access permission bits so a
 * permission fault cannot be generated. */
#define CP15_DACR_MANAGER_ACCESS(x) (3u << (2 * ((x) & 15)))

/*------------------------------------------------------------------------------ */
/*         Exported functions */
/*------------------------------------------------------------------------------ */

/**
 * \brief Read the System Control Register (SCTLR).
 * \return register contents
 */
static inline uint32_t cp15_read_sctlr(void)
{
	uint32_t sctlr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r"(sctlr));
	return sctlr;
}

/**
 * \brief Modify the System Control Register (SCTLR).
 * \param value new value for SCTLR
 */
static inline void cp15_write_sctlr(uint32_t value)
{
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r"(value));
}

/**
 * \brief Read the Auxiliary Control Register (ACTLR).
 * \return register contents
 */
static inline uint32_t cp15_read_actlr(void)
{
	uint32_t actlr;
	asm("mrc p15, 0, %0, c1, c0, 1" : "=r"(actlr));
	return actlr;
}

/**
 * \brief Modify the Auxiliary Control Register (ACTLR).
 * \param value new value for ACTLR
 */
static inline void cp15_write_actlr(uint32_t value)
{
	asm("mcr p15, 0, %0, c1, c0, 1" :: "r"(value));
}

/**
 * \brief Read the Translation Table Base Register 0 (TTBR0).
 * \return register contents
 */
static inline uint32_t cp15_read_ttbr0(uint32_t value)
{
	uint32_t ttbr0;
	asm("mrc p15, 0, %0, c2, c0, 0" : "=r"(ttbr0));
	return ttbr0;
}

/**
 * \brief Write the Translation Table Base Register 0 (TTBR0).
 * \param value new value for TTBR0
 */
static inline void cp15_write_ttbr0(uint32_t value)
{
	/* write TTBR */
	asm("mcr p15, 0, %0, c2, c0, 0" :: "r"(value));
}

/**
 * \brief Read the Domain Access Control Register (DACR).
 * \return register contents
 */
static inline uint32_t cp15_read_dacr(void)
{
	uint32_t dacr;
	asm("mrc p15, 0, %0, c3, c0, 0" : "=r"(dacr));
	return dacr;
}

/**
 * \brief Modify the Domain Access Control Register (DACR).
 * \param value new value for DACR
 */
static inline void cp15_write_dacr(uint32_t value)
{
	/* write DACR */
	asm("mcr p15, 0, %0, c3, c0, 0" :: "r"(value));
}

/**
 * \brief ICIALLU: Invalidate I-cache
 */
static inline void cp15_icache_invalidate(void)
{
	asm("mcr p15, 0, %0, c7, c5, 0" :: "r"(0));
}

/**
 * \brief DCISW - Invalidate DCache single entry (Set/Way)
 */
static inline void cp15_dcache_invalidate_setway(uint32_t setway)
{
	asm("mcr p15, 0, %0, c7, c6, 2" :: "r"(setway));
}

/**
 * \brief DCCSW: Clean DCache single entry (Set/Way)
 */
static inline void cp15_dcache_clean_setway(uint32_t setway)
{
	asm("mcr p15, 0, %0, c7, c10, 2" :: "r"(setway));
}

/**
 * \brief DCCISW - Clean and invalidate DCache entry (Set/Way)
 */
static inline void cp15_dcache_clean_invalidate_setway(uint32_t setway)
{
	asm("mcr p15, 0, %0, c7, c14, 2" :: "r"(setway));
}

/**
 * \brief DCIMVAC - Invalidate DCache single entry (MVA)
 */
static inline void cp15_dcache_invalidate_mva(uint32_t mva)
{
	asm("mcr p15, 0, %0, c7, c6, 1" :: "r"(mva));
}

/**
 * \brief DCCMVAC - Clean DCache single entry (MVA)
 */
static inline void cp15_dcache_clean_mva(uint32_t mva)
{
	asm("mcr p15, 0, %0, c7, c10, 1" :: "r"(mva));
}

/**
 * \brief DCCIMVAC - Clean and invalidate DCache entry (MVA)
 */
static inline void cp15_dcache_clean_invalidate_mva(uint32_t mva)
{
	asm("mcr p15, 0, %0, c7, c14, 1" :: "r"(mva));
}

#endif /* CP15_H_ */
