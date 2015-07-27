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

/** \file */

/*----------------------------------------------------------------------------
 *        Functions to access CP15 coprocessor register
 *----------------------------------------------------------------------------*/

/**
 * \brief Register c0 accesses the ID Register, Cache Type Register, and TCM Status Registers.
 *  Reading from this register returns the device ID, the cache type, or the TCM status
 *   depending on the value of Opcode_2 used.
 */
	.section .text.cp15_read_id
	.global   cp15_read_id
cp15_read_id:
	mov     r0, #0
	mrc     p15, 0, r0, c0, c0, 0
	bx      lr

/**
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
	.section .text.cp15_isb
	.global   cp15_isb
cp15_isb:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4
	nop
	bx      lr

/**
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
	.section .text.cp15_dsb
	.global   cp15_dsb
cp15_dsb:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4
	nop
	bx      lr

/**
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
	.section .text.cp15_dmb
	.global   cp15_dmb
cp15_dmb:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 5
	nop
	bx      lr

/**
 * \brief  Invalidate TLB
 */
	.section .text.cp15_invalidate_tlb
	.global  cp15_invalidate_tlb
cp15_invalidate_tlb:
	mov     r0, #0
	mcr     p15, 0, r0, c8, c7, 0
	dsb
	bx      lr

/**
 * \brief Register c1 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
	.section .text.cp15_exclusive_cache
	.global   cp15_exclusive_cache
cp15_exclusive_cache:
	mov     r0, #0
	mrc     p15, 0, r0, c1, c0, 1 // Read ACTLR
	orr     r0, r0, #0x00000080
	mcr     p15, 0, r0, c1, c0, 1 // Write ACTLR
	nop
	bx      lr

/**
 * \brief Register c1 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
	.section .text.cp15_non_exclusive_cache
	.global   cp15_non_exclusive_cache
cp15_non_exclusive_cache:
	mov     r0, #0
	mrc     p15, 0, r0, c1, c0, 1 // Read ACTLR
	bic     r0, r0, #0x00000080
	mcr     p15, 0, r0, c1, c0, 1 // Write ACTLR
	nop
	bx      lr

/**
 * \brief Register c1 accesses the CSSELR Register, to select ICache
 */
	.section .text.cp15_select_icache
	.global   cp15_select_icache
cp15_select_icache:
	mrc     p15, 2, r0, c0, c0, 0           // Read CSSELR
	orr     r0,  r0, #0x1                   // Change 0th bit to ICache
	mcr     p15, 2, r0, c0, c0, 0           // Write CSSELR
	nop
	bx      lr

/**
 * \brief Register c1 accesses the CSSELR Register, to select DCache
 */
	.section .text.cp15_select_dcache
	.global   cp15_select_dcache
cp15_select_dcache:
	mrc     p15, 2, r0, c0, c0, 0           // Read CSSELR
	and     r0,  r0, #0xFFFFFFFE            // Change 0th bit to DCache
	mcr     p15, 2, r0, c0, c0, 0           // Write CSSELR
	nop
	bx      lr

/**
 * \brief Register c1 is the Control Register for the ARM926EJ-S processor.
 * This register specifies the configuration used to enable and disable the
 * caches and MMU. It is recommended that you access this register using a
 * read-modify-write sequence
 */
	.section .text.cp15_read_control
	.global   cp15_read_control
cp15_read_control:
	mov     r0, #0
	mrc     p15, 0, r0, c1, c0, 0
	bx      lr

	.section .text.cp15_write_control
	.global   cp15_write_control
cp15_write_control:
	mcr     p15, 0, r0, c1, c0, 0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bx      lr

	.section .text.cp15_write_domain_access_control
	.global   cp15_write_domain_access_control
cp15_write_domain_access_control:
	mcr     p15, 0, r0, c3, c0, 0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bx      lr

/**
 * \brief  ARMv7A architecture supports two translation tables
 * Configure translation table base (TTB) control register cp15,c2
 * to a value of all zeros, indicates we are using TTB register 0.
 * write the address of our page table base to TTB register 0.
 */
	.section .text.cp15_write_ttb
	.global   cp15_write_ttb
cp15_write_ttb:
	mcr     p15, 0, r0, c2, c0, 0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	bx     lr

/**
 * \brief Invalidate I cache predictor array inner Sharable
 */
	.section .text.cp15_invalid_icache_inner_sharable
	.global   cp15_invalid_icache_inner_sharable
cp15_invalid_icache_inner_sharable:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c1, 0
	bx      lr

/**
 * \brief Invalidate entire branch predictor array inner Sharable
 */
	.section .text.cp15_invalid_btb_inner_sharable
	.global   cp15_invalid_btb_inner_sharable
cp15_invalid_btb_inner_sharable:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c1, 6
	bx      lr

/**
 * \brief Invalidate all instruction caches to PoU, also flushes branch target cache
 */
	.section .text.cp15_invalid_icache
	.global   cp15_invalid_icache
cp15_invalid_icache:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 0
	bx      lr

/**
 * \brief Invalidate instruction caches by VA to PoU
 */
	.section .text.cp15_invalid_icache_by_mva
	.global   cp15_invalid_icache_by_mva
cp15_invalid_icache_by_mva:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 1
	bx      lr

/**
 * \brief Invalidate entire branch predictor array
 */
	.section .text.cp15_invalid_btb
	.global   cp15_invalid_btb
cp15_invalid_btb:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 6
	bx      lr

/**
 * \brief Invalidate branch predictor array entry by MVA
 */
	.section .text.cp15_invalid_btb_by_mva
	.global   cp15_invalid_btb_by_mva
cp15_invalid_btb_by_mva:
	mcr     p15, 0, r0, c7, c5, 7
	bx      lr

/***********************************************************
 *        Data Cache related maintenance functions
 ***********************************************************/

/**
 * \brief Invalidate entire data cache by set/way
 */
	.section .text.cp15_invalid_dcache_by_set_way
	.global   cp15_invalid_dcache_by_set_way
cp15_invalid_dcache_by_set_way:
	push    {r1-r4}
	mrc     p15, 1, r0, c0, c0, 0
	mov     r1, r0, lsr #3          // Num of ways
	and     r1, r1, #3              // 3 is specific to CortexA5 with 32 KB
	mov     r2, r0, lsr #13         // Num of sets
	and     r2, r2, #0xFF           // 8bit is specific to CortexA5 with 32 KB
	mov     r0, #0                  // 0:SHL:5
1:
	lsl     r4, r1, #30
	mov     r3, r2
2:
	orr     r0, r4, r3, lsl #5
	mcr     p15, 0, r0, c7, c6, 2
	subs    r3, r3, #1              // 1:SHL:30
	bpl     2b
	subs    r1, r1, #1
	bpl     1b
	dsb
	pop     {r1-r4}
	bx      lr

/**
 * \brief Clean entire data cache by set/way
 */
	.section .text.cp15_clean_dcache_by_set_way
	.global   cp15_clean_dcache_by_set_way
cp15_clean_dcache_by_set_way:
	push    {r1-r4}
	mrc     p15, 1, r0, c0, c0, 0
	mov     r1, r0, lsr #3          // Num of ways
	and     r1, r1, #3              // 3 is specific to CortexA5 with 32 KB
	mov     r2, r0, lsr #13         // Num of sets
	and     r2, r2, #0xFF           // 8bit is specific to CortexA5 with 32 KB
	mov     r0, #0                  // 0:SHL:5
1:
	lsl     r4, r1, #30
	mov     r3, r2
2:
	orr     r0, r4, r3, lsl #5
	mcr     p15, 0, r0, c7, c10, 2
	subs    r3, r3, #1              // 1:SHL:30
	bpl     2b
	subs    r1, r1, #1
	bpl     1b
	dsb
	pop     {r1-r4}
	bx      lr

/**
 * \brief Clean and Invalidate entire data cache by set/way
 */
	.section .text.cp15_clean_invalid_dcache_by_set_way
	.global   cp15_clean_invalid_dcache_by_set_way
cp15_clean_invalid_dcache_by_set_way:
	push    {r1-r4}
	mrc     p15, 1, r0, c0, c0, 0
	mov     r1, r0, lsr #3          // Num of ways
	and     r1, r1, #3              // 3 is specific to CortexA5 with 32 KB
	mov     r2, r0, lsr #13         // Num of sets
	and     r2, r2, #0xFF           // 8bit is specific to CortexA5 with 32 KB
	mov     r0, #0                  // 0:SHL:5
1:
	lsl     r4, r1, #30
	mov     r3, r2
2:
	orr     r0, r4, r3, lsl #5
	mcr     p15, 0, r0, c7, c14, 2
	subs    r3, r3, #1              // 1:SHL:30
	bpl     2b
	subs    r1, r1, #1
	bpl     1b
	dsb
	pop     {r1-r4}
	bx      lr

/**
 * \brief Invalidate data cache by VA to Poc
 */
	.section .text.cp15_invalid_dcache_by_mva
	.global   cp15_invalid_dcache_by_mva
cp15_invalid_dcache_by_mva:
	mov     r2, #0x20                          // Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
	mov     r3, r0
inv_loop:
	mcr     p15, 0, r0, c7, c6, 1
	add     r3, r3, r2
	cmp     r3, r1
	bls     inv_loop
	bx      lr

/**
 * \brief Clean data cache by MVA
 */
	.section .text.cp15_clean_dcache_by_mva
	.global   cp15_clean_dcache_by_mva
cp15_clean_dcache_by_mva:
	mov     r2, #0x20                          // Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
	mov     r3, r0
clean_loop:
	mcr     p15, 0, r0, c7, c10, 1
	add     r3, r3, r2
	cmp     r3, r1
	bls     clean_loop
	bx      lr

/**
 * \brief Clean unified cache by MVA
 */
	.section .text.cp15_clean_dcache_umva
	.global   cp15_clean_dcache_umva
cp15_clean_dcache_umva:
	mov     r0, #0
	mcr     p15, 0, r0, c7, c11, 1
	bx      lr

/**
 * \brief Clean and invalidate data cache by VA to PoC
 */
	.section .text.cp15_clean_invalid_dcache_by_mva
	.global   cp15_clean_invalid_dcache_by_mva
cp15_clean_invalid_dcache_by_mva:
	mov     r2, #0x20                          // Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
	mov     r3, r0
clinv_loop:
	mcr     p15, 0, r0, c7, c14, 1
	add     r3, r3, r2
	cmp     r3, r1
	bls     clinv_loop
	bx      lr

/**
 * \brief Ensure that the I and D caches are coherent within specified
 *      region.  This is typically used when code has been written to
 *      a memory region, and will be executed.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
	.section .text.cp15_coherent_dcache_for_dma
	.global   cp15_coherent_dcache_for_dma
cp15_coherent_dcache_for_dma:
	push    {r2-r4}
	mrc     p15, 0, r3, c0, c0, 1
	lsr     r3, r3, #16
	and     r3, r3, #0xf
	mov     r2, #4
	mov     r2, r2, lsl r3

	sub     r3, r2, #1
	bic     r4, r0, r3
1:
	mcr     p15, 0, r4, c7, c11, 1
	add     r4, r4, r2
	cmp     r4, r1
	blo     1b
	dsb

	bic     r4, r0, r3
2:
	mcr     p15, 0, r4, c7, c5, 1
	add     r4, r4, r2
	cmp     r4, r1
	blo     2b
	mov     r0, #0
	mcr     p15, 0, r0, c7, c1, 6
	mcr     p15, 0, r0, c7, c5, 6
	dsb
	isb
	pop     {r2-r4}
	bx      lr

/**
 * \brief Invalidate the data cache within the specified region; we will
 *      be performing a DMA operation in this region and we want to
 *      purge old data in the cache.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
	.section .text.cp15_invalidate_dcache_for_dma
	.global   cp15_invalidate_dcache_for_dma
cp15_invalidate_dcache_for_dma:
	push    {r2-r3}
	mrc     p15, 0, r3, c0, c0, 1
	lsr     r3, r3, #16
	and     r3, r3, #0xf
	mov     r2, #4
	mov     r2, r2, lsl r3

	sub     r3, r2, #1
	bic     r0, r0, r3
3:
	mcr     p15, 0, r0, c7, c6, 1
	add     r0, r0, r2
	cmp     r0, r1
	blo     3b
	dsb
	pop     {r2-r3}
	bx      lr

/**
 * \brief Clean the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
	.section .text.cp15_clean_dcache_for_dma
	.global   cp15_clean_dcache_for_dma
cp15_clean_dcache_for_dma:
	mrc     p15, 0, r3, c0, c0, 1
	lsr     r3, r3, #16
	and     r3, r3, #0xf
	mov     r2, #4
	mov     r2, r2, lsl r3

	sub     r3, r2, #1
	bic     r0, r0, r3
4:
	mcr     p15, 0, r0, c7, c10, 1
	add     r0, r0, r2
	cmp     r0, r1
	blo     4b
	dsb
	bx      lr

/**
 * \brief Flush the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
	.section .text.cp15_flush_dcache_for_dma
	.global   cp15_flush_dcache_for_dma
cp15_flush_dcache_for_dma:
	mrc     p15, 0, r3, c0, c0, 1
	lsr     r3, r3, #16
	and     r3, r3, #0xf
	mov     r2, #4
	mov     r2, r2, lsl r3

	sub     r3, r2, #1
	bic     r0, r0, r3
5:
	mcr     p15, 0, r0, c7, c14, 1
	add     r0, r0, r2
	cmp     r0, r1
	blo     5b
	dsb
	bx      lr

/**
 * \brief cp15_flush_kern_dcache_for_dma
 * Ensure that the data held in the page kaddr is written back to the page in question.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
	.section .text.cp15_flush_kern_dcache_for_dma
	.global   cp15_flush_kern_dcache_for_dma
cp15_flush_kern_dcache_for_dma:
	mrc     p15, 0, r3, c0, c0, 1
	lsr     r3, r3, #16
	and     r3, r3, #0xf
	mov     r2, #4
	mov     r2, r2, lsl r3

	add     r1, r0, r1
	sub     r3, r2, #1
	bic     r0, r0, r3

	mcr     p15, 0, r0, c7, c14, 1
	add     r0, r0, r2
	cmp     r0, r1
	blo     1b
	dsb
	bx      lr
