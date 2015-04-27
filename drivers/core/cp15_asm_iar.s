/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
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
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES// LOSS OF USE, DATA,
 * OR PROFITS// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */
 

/** \file */

        MODULE  ?cp15

        //// Forward declaration of sections.
        SECTION IRQ_STACK:DATA:NOROOT(2)
        SECTION CSTACK:DATA:NOROOT(3)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#define __ASSEMBLY__


/*----------------------------------------------------------------------------
 *        Functions to access CP15 coprocessor register
 *----------------------------------------------------------------------------*/
        PUBLIC  cp15_read_id
        PUBLIC  cp15_exclusive_cache
        PUBLIC  cp15_non_exclusive_cache
        PUBLIC  cp15_isb
        PUBLIC  cp15_dsb
        PUBLIC  cp15_dmb        
        PUBLIC  cp15_select_icache
        PUBLIC  cp15_select_dcache
        PUBLIC  cp15_read_control
        PUBLIC  cp15_write_control
        PUBLIC  cp15_write_domain_access_control
        PUBLIC  cp15_write_ttb
        PUBLIC  cp15_invalid_icache_inner_sharable
        PUBLIC  cp15_invalid_btb_inner_sharable
        PUBLIC  cp15_invalid_icache
        PUBLIC  cp15_invalid_icache_by_mva
        PUBLIC  cp15_invalid_btb
        PUBLIC  cp15_invalid_btb_by_mva
        
        PUBLIC  cp15_invalid_dcache_by_set_way
        PUBLIC  cp15_clean_dcache_by_set_way
        PUBLIC  cp15_clean_invalid_dcache_by_set_way
        
        PUBLIC  cp15_invalid_dcache_by_mva        
        PUBLIC  cp15_clean_dcache_by_mva             
        PUBLIC  cp15_clean_dcache_umva
        PUBLIC  cp15_clean_invalid_dcache_by_mva
        PUBLIC  cp15_invalid_translation_table
        
        PUBLIC  cp15_coherent_dcache_for_dma
        PUBLIC  cp15_invalidate_dcache_for_dma
        PUBLIC  cp15_clean_dcache_for_dma
        PUBLIC  cp15_flush_dcache_for_dma
        PUBLIC  cp15_flush_kern_dcache_for_dma

/** 
 * \brief Register c0 accesses the ID Register, Cache Type Register, and TCM Status Registers.
 *  Reading from this register returns the device ID, the cache type, or the TCM status
 *   depending on the value of Opcode_2 used. 
 */
        SECTION .cp15_read_id:DATA:NOROOT(2)
        PUBLIC   cp15_read_id
cp15_read_id:
        mov     r0, #0
        mrc     p15, 0, r0, c0, c0, 0
        bx      lr
     

/** 
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
        SECTION .cp15_isb:DATA:NOROOT(2)
        PUBLIC   cp15_isb
cp15_isb:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c5, 4
        nop
        bx      lr
        
/** 
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
        SECTION .cp15_dsb:DATA:NOROOT(2)
        PUBLIC   cp15_dsb
cp15_dsb:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c10, 4
        nop
        bx      lr

/** 
 * \brief Register c7 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
        SECTION .cp15_dmb:DATA:NOROOT(2)
        PUBLIC   cp15_dmb
cp15_dmb:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c10, 5
        nop
        bx      lr

/** 
 * \brief Register c1 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
        SECTION .cp15_exclusive_cache:DATA:NOROOT(2)
        PUBLIC   cp15_exclusive_cache
cp15_exclusive_cache:
        mov     r0, #0
        mrc     p15, 0, r0, c1, c0, 1 ; Read ACTLR
        orr     r0, r0, #0x00000080
        mcr     p15, 0, r0, c1, c0, 1 ; Write ACTLR
        nop
        bx      lr
       
       
/** 
 * \brief Register c1 accesses the ACTLR Register, to indicate cpu that L2 is in exclusive mode
 */
        SECTION .cp15_non_exclusive_cache:DATA:NOROOT(2)
        PUBLIC   cp15_non_exclusive_cache
cp15_non_exclusive_cache:
        mov     r0, #0
        mrc     p15, 0, r0, c1, c0, 1 ; Read ACTLR
        bic     r0, r0, #0x00000080
        mcr     p15, 0, r0, c1, c0, 1 ; Write ACTLR
        nop
        bx      lr       
        
/** 
 * \brief Register c1 accesses the CSSELR Register, to select ICache 
 */
        SECTION .cp15_select_icache:DATA:NOROOT(2)
        PUBLIC   cp15_select_icache
cp15_select_icache:
        mrc     p15, 2, r0, c0, c0, 0           ; Read CSSELR
        orr     r0,  r0, #0x1                   ; Change 0th bit to ICache
        mcr     p15, 2, r0, c0, c0, 0           ; Write CSSELR
        nop
        bx      lr
        
/** 
 * \brief Register c1 accesses the CSSELR Register, to select DCache
 */
        SECTION .cp15_select_dcache:DATA:NOROOT(2)
        PUBLIC   cp15_select_dcache
cp15_select_dcache:
        mrc     p15, 2, r0, c0, c0, 0           ; Read CSSELR
        and     r0,  r0, #0xFFFFFFFE            ; Change 0th bit to ICache
        mcr     p15, 2, r0, c0, c0, 0           ; Write CSSELR
        nop
        bx      lr
        


/** 
 * \brief Register c1 is the Control Register for the ARM926EJ-S processor.
 * This register specifies the configuration used to enable and disable the
 * caches and MMU. It is recommended that you access this register using a
 * read-modify-write sequence
 */
        SECTION .cp15_read_control:CODE:NOROOT(2)
        PUBLIC   cp15_read_control
cp15_read_control:
        mov     r0, #0
        mrc     p15, 0, r0, c1, c0, 0   
        bx      lr

        SECTION .cp15_write_control:CODE:NOROOT(2)
        PUBLIC   cp15_write_control
cp15_write_control:
        mcr     p15, 0, r0, c1, c0, 0
        dsb
        isb
        bx      lr

       SECTION .cp15_write_domain_access_control:CODE:NOROOT(2)
       PUBLIC   cp15_write_domain_access_control
cp15_write_domain_access_control:
        mcr     p15, 0, r0, c3, c0, 0
        dsb
        isb
        bx      lr
 
/** 
 * \brief  ARMv7A architecture supports two translation tables
 * Configure translation table base (TTB) control register cp15,c2
 * to a value of all zeros, indicates we are using TTB register 0.
 * write the address of our page table base to TTB register 0.
 */
        SECTION .cp15_write_ttb:CODE:NOROOT(2)
        PUBLIC   cp15_write_ttb
cp15_write_ttb:
       mcr     p15, 0, r0, c2, c0, 0
       dsb
       isb
       bx     lr

/**
 * \brief Invalidate I cache predictor array inner Sharable
 */
        SECTION .cp15_invalid_icache_inner_sharable:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_icache_inner_sharable
cp15_invalid_icache_inner_sharable:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c1, 0
        bx      lr

/**
 * \brief Invalidate entire branch predictor array inner Sharable
 */
        SECTION .cp15_invalid_btb_inner_sharable:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_btb_inner_sharable
cp15_invalid_btb_inner_sharable:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c1, 6
        bx      lr

/**
 * \brief Invalidate all instruction caches to PoU, also flushes branch target cache
 */
        SECTION .cp15_invalid_icache:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_icache
cp15_invalid_icache:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c5, 0
        isb
        bx      lr

/**
 * \brief Invalidate instruction caches by VA to PoU
 */
        SECTION .cp15_invalid_icache_by_mva:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_icache_by_mva
cp15_invalid_icache_by_mva:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c5, 1
        bx      lr

/**
 * \brief Invalidate entire branch predictor array
 */
        SECTION .cp15_invalid_btb:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_btb
cp15_invalid_btb:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c5, 6
        dsb
        isb
        bx      lr

/**
 * \brief Invalidate branch predictor array entry by MVA
 */
        SECTION .cp15_invalid_btb_by_mva:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_btb_by_mva
cp15_invalid_btb_by_mva:
        mcr     p15, 0, r0, c7, c5, 7
        bx      lr

/***********************************************************
*
*       ===Data Cache related maintenance functions===
*
**************************************************************/


//      ===Data Cache maintenance by SetWay  === 

/**
 * \brief Invalidate entire data cache by set/way
 */
        SECTION .cp15_invalid_dcache_by_set_way:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_dcache_by_set_way
cp15_invalid_dcache_by_set_way:
        mrc     p15, 1, r0, c0, c0, 0
        mov     r1, r0, lsr #3          ; Num of ways
        and     r1, r1, #3              ; 3 is specific to CortexA5 with 32 KB
        mov     r2, r0, lsr #13         ; Num of stes
        and     r2, r2, #0xFF           ; 8bit is specific to CortexA5 with 32 KB        
        mov     r0, #0                  ; 0:SHL:5
inv_way_loop
        lsl     r4, r1, #30
        sub     r1, r1, #1              ; 
        mov     r3, r2
inv_line_loop
        orr     r0, r4, r3, lsl #5
        mcr     p15, 0, r0, c7, c6, 2
        sub     r3, r3, #1              ; 1:SHL:30
        cmp     r3, #0
        bpl     inv_line_loop
        cmp     r1, #-1
        bne     inv_way_loop
        nop
        bx      lr        
        
        
/**
 * \brief Clean entire data cache by set/way
 */
        SECTION .cp15_clean_dcache_by_set_way:CODE:NOROOT(2)
        PUBLIC   cp15_clean_dcache_by_set_way
cp15_clean_dcache_by_set_way:
        mrc     p15, 1, r0, c0, c0, 0
        mov     r1, r0, lsr #3          ; Num of ways
        and     r1, r1, #3              ; 3 is specific to CortexA5 with 32 KB
        mov     r2, r0, lsr #13         ; Num of stes
        and     r2, r2, #0xFF           ; 8bit is specific to CortexA5 with 32 KB        
        mov     r0, #0                  ; 0:SHL:5
clean_way_loop
        lsl     r4, r1, #30
        sub     r1, r1, #1              ; 
        mov     r3, r2
clean_line_loop
        orr     r0, r4, r3, lsl #5
        mcr     p15, 0, r0, c7, c10, 2
        sub     r3, r3, #1              ; 1:SHL:30
        cmp     r3, #0
        bpl     clean_line_loop
        cmp     r1, #-1
        bne     clean_way_loop
        nop
        bx      lr 
        
/**
 * \brief Clean and Invalidate entire data cache by set/way
 */
        SECTION .cp15_clean_invalid_dcache_by_set_way:CODE:NOROOT(2)
        PUBLIC   cp15_clean_invalid_dcache_by_set_way
cp15_clean_invalid_dcache_by_set_way:
        mrc     p15, 1, r0, c0, c0, 0
        mov     r1, r0, lsr #3          ; Num of ways
        and     r1, r1, #3              ; 3 is specific to CortexA5 with 32 KB
        mov     r2, r0, lsr #13         ; Num of stes
        and     r2, r2, #0xFF           ; 8bit is specific to CortexA5 with 32 KB        
        mov     r0, #0                  ; 0:SHL:5
clinv_way_loop
        lsl     r4, r1, #30
        sub     r1, r1, #1              ; 
        mov     r3, r2
clinv_line_loop
        orr     r0, r4, r3, lsl #5
        mcr     p15, 0, r0, c7, c10, 2
        sub     r3, r3, #1              ; 1:SHL:30
        cmp     r3, #0
        bpl     clinv_line_loop
        cmp     r1, #-1
        bne     clinv_way_loop
        dsb
        isb
        bx      lr    
        
        
        
//      ===Data Cache maintenance by VA  === 


/**
 * \brief Invalidate data cache by VA to Poc
 */
        SECTION .cp15_invalid_dcache_by_mva:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_dcache_by_mva
cp15_invalid_dcache_by_mva: 
        mov     r2, #0x20                          ;Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
        mov     r3, r0
inv_loop
        mcr     p15, 0, r0, c7, c6, 1
        add     r3, r3, r2
        cmp     r3, r1        
        bls     inv_loop        
        bx      lr


/**
 * \brief Clean data cache by MVA
 */
        SECTION .cp15_clean_dcache_by_mva:CODE:NOROOT(2)
        PUBLIC   cp15_clean_dcache_by_mva
cp15_clean_dcache_by_mva:   
        mov     r2, #0x20                          ;Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
        mov     r3, r0
clean_loop
        mcr     p15, 0, r0, c7, c10, 1
        add     r3, r3, r2
        cmp     r3, r1        
        bls     clean_loop        
        bx      lr
       
/**
 * \brief Clean unified cache by MVA 
 */
        SECTION .cp15_clean_dcache_umva:CODE:NOROOT(2)
        PUBLIC   cp15_clean_dcache_umva
cp15_clean_dcache_umva:
        mov     r0, #0
        mcr     p15, 0, r0, c7, c11, 1
        bx      lr

/**
 * \brief Clean and invalidate data cache by VA to PoC
 */
        SECTION .cp15_clean_invalid_dcache_by_mva:CODE:NOROOT(2)
        PUBLIC   cp15_clean_invalid_dcache_by_mva
cp15_clean_invalid_dcache_by_mva:
        mov     r2, #0x20                          ;Eight words per line, Cortex-A5 L1 Line Size 32 Bytes
        mov     r3, r0
clinv_loop
        mcr     p15, 0, r0, c7, c14, 1
        add     r3, r3, r2
        cmp     r3, r1        
        bls     clinv_loop        
        bx      lr
        
        
/**
 * \brief Invalidate translation table
 */
        SECTION .cp15_invalid_translation_table:CODE:NOROOT(2)
        PUBLIC   cp15_invalid_translation_table
cp15_invalid_translation_table:
        mcr      p15, 0, r0, c8, c3,  0
        dsb
        isb
        mcr      p15, 0, r0, c8, c7,  0
        dsb
        isb   
        bx      lr        
        
/**
 * \brief flush translation table
 */
        SECTION .CP15_FlushTranslationTable:CODE:NOROOT(2)
        PUBLIC   CP15_FlushTranslationTable
CP15_FlushTranslationTable:
        mcr      p15, 0, r0, c8, c3,  0
        dsb
        isb    
        bx      lr          


/**
 * \brief Ensure that the I and D caches are coherent within specified
 *      region.  This is typically used when code has been written to
 *      a memory region, and will be executed.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
        SECTION .cp15_coherent_dcache_for_dma:CODE:NOROOT(2)
        PUBLIC   cp15_coherent_dcache_for_dma
cp15_coherent_dcache_for_dma:
//      dcache_line_size r2, r3
 
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        lsr     r3, r3, #16
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size

        sub     r3, r2, #1
        bic     r12, r0, r3
loop1:
        mcr     p15, 0, r12, c7, c11, 1       // clean D line to the point of unification
        add     r12, r12, r2
        cmp     r12, r1
        blo     loop1
        dsb

// .macro  icache_line_size, reg, tmp
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size

        sub     r3, r2, #1
        bic     r12, r0, r3
loop2:
        mcr     p15, 0, r12, c7, c5, 1        // invalidate I line
        add     r12, r12, r2
        cmp     r12, r1
        blo     loop2
        mov     r0, #0
        mcr     p15, 0, r0, c7, c1, 6         //invalidate BTB Inner Shareable
        mcr      p15, 0, r0, c7, c5, 6        // invalidate BTB
        dsb
        isb
        bx      lr


/**
 * \brief Invalidate the data cache within the specified region; we will
 *      be performing a DMA operation in this region and we want to
 *      purge old data in the cache.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
        SECTION .cp15_invalidate_dcache_for_dma:CODE:NOROOT(2)
        PUBLIC   cp15_invalidate_dcache_for_dma
cp15_invalidate_dcache_for_dma:

//      dcache_line_size r2, r3
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        lsr     r3, r3, #16
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size

        sub     r3, r2, #1
        tst     r0, r3
        bic     r0, r0, r3

        mcrne   p15, 0, r0, c7, c14, 1         // clean & invalidate D / U line

        tst     r1, r3
        bic     r1, r1, r3
        mcrne   p15, 0, r1, c7, c14, 1         // clean & invalidate D / U line
loop3:
        mcr     p15, 0, r0, c7, c6, 1          // invalidate D / U line
        add     r0, r0, r2
        cmp     r0, r1
        blo     loop3
        dsb
        bx      lr


/**
 * \brief Clean the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
        SECTION .cp15_clean_dcache_for_dma:CODE:NOROOT(2)
        PUBLIC   cp15_clean_dcache_for_dma
cp15_clean_dcache_for_dma:
//      dcache_line_size r2, r3
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        lsr     r3, r3, #16
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size

        sub     r3, r2, #1
        bic     r0, r0, r3
loop4:
        mcr     p15, 0, r0, c7, c10, 1        // clean D / U line
        add     r0, r0, r2
        cmp     r0, r1
        blo     loop4
        dsb
        bx      lr


/**
 * \brief Flush the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
        SECTION .cp15_flush_dcache_for_dma:CODE:NOROOT(2)
        PUBLIC   cp15_flush_dcache_for_dma
cp15_flush_dcache_for_dma:
//        dcache_line_size r2, r3
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        lsr     r3, r3, #16
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size
        sub     r3, r2, #1
        bic     r0, r0, r3
loop5:
        mcr     p15, 0, r0, c7, c14, 1         // clean & invalidate D / U line
        add     r0, r0, r2
        cmp     r0, r1
        blo     loop5
        dsb
        bx      lr


/**
 * \brief cp15_flush_kern_dcache_for_dma
 * Ensure that the data held in the page kaddr is written back to the page in question.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
        SECTION .cp15_flush_kern_dcache_for_dma:CODE:NOROOT(2)
        PUBLIC   cp15_flush_kern_dcache_for_dma
cp15_flush_kern_dcache_for_dma:
//       dcache_line_size r2, r3
        mrc     p15, 0, r3, c0, c0, 1         // read ctr
        lsr     r3, r3, #16
        and     r3, r3, #0xf                  // cache line size encoding
        mov     r2, #4                        // bytes per word
        mov     r2, r2, lsl r3                // actual cache line size

        add     r1, r0, r1
        sub     r3, r2, #1
        bic     r0, r0, r3

        mcr     p15, 0, r0, c7, c14, 1        // clean & invalidate D line / unified line
        add     r0, r0, r2
        cmp     r0, r1
        blo     1b
        dsb
        bx      lr
        END

