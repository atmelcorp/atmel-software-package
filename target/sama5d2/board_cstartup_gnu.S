/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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


//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------


#define AIC         0xFC020000
#define AIC_IVR     0x10
#define AIC_EOICR   0x38
#define SAIC        0xF803C000

#define MODE_MSK         0x1F
#define ARM_MODE_FIQ     0x11
#define ARM_MODE_IRQ     0x12
#define ARM_MODE_SVC     0x13
#define ARM_MODE_SYS     0x1F

#define I_BIT            0x80
#define F_BIT            0x40

#define REG_SFR_AICREDIR        0xF8030054
#define REG_SFR_UID             0xF8030050
#define AICREDIR_KEY            0x5F67B102

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

	.align      4
	.arm

/* Exception vectors
 *******************/
	.section    .vectors, "a", %progbits

resetVector:
	ldr     pc, =resetHandler             /* Reset */
	ldr     pc, =UndefInstr_IrqHandler    /* Undefined Instruction */
1:
	b       1b                            /* Software Interrupt */
	ldr     pc, =PrefetchAbort_IrqHandler /* Prefetch Abort */
	ldr     pc, =DataAbort_IrqHandler     /* Data Abort */
1:
	b       1b                            /* Reserved for future use */
	b       irqHandler                    /* Interrupt */
	b       fiqHandler                    /* Fast interrupt */

//------------------------------------------------------------------------------
/// Handles a fast interrupt request by branching to the address defined in the
/// AIC.
//------------------------------------------------------------------------------
fiqHandler:
	sub     lr, lr, #4
	stmfd   sp!, {lr}
	//mrs     lr, SPSR
	stmfd   sp!, {r0}

	/* Write in the IVR to support Protect Mode */

	ldr     lr, =SAIC
	ldr     r0, [r14, #AIC_IVR]
	str     lr, [r14, #AIC_IVR]

	/* Branch to interrupt handler in Supervisor mode */

	msr     CPSR_c, #ARM_MODE_SVC
	stmfd   sp!, {r1-r3, r4, r12, lr}

	mov     r14, pc
	bx      r0

	ldmia   sp!, {r1-r3, r4, r12, lr}
	msr     CPSR_c, #ARM_MODE_FIQ | I_BIT | F_BIT

	/* Acknowledge interrupt */

	ldr     lr, =SAIC
	str     lr, [r14, #AIC_EOICR]

	/* Restore interrupt context and branch back to calling code */

	ldmia   sp!, {r0}
	//msr     SPSR_cxsf, lr
	ldmia   sp!, {pc}^

//------------------------------------------------------------------------------
/// Handles incoming interrupt requests by branching to the corresponding
/// handler, as defined in the AIC. Supports interrupt nesting.
//------------------------------------------------------------------------------
irqHandler:
	/* Save interrupt context on the stack to allow nesting */

	sub     lr, lr, #4
	stmfd   sp!, {lr}
	mrs     lr, SPSR
	stmfd   sp!, {r0, lr}

	/* Write in the IVR to support Protect Mode */

	ldr     lr, =AIC
	ldr     r0, [r14, #AIC_IVR]
	str     lr, [r14, #AIC_IVR]

	/* Branch to interrupt handler in Supervisor mode */

	msr     CPSR_c, #ARM_MODE_SVC
	stmfd   sp!, {r1-r3, r4, r12, lr}

	/* Check for 8-byte alignment and save lr plus a */
	/* word to indicate the stack adjustment used (0 or 4) */

	and     r1, sp, #4
	sub     sp, sp, r1
	stmfd   sp!, {r1, lr}

	blx     r0

	ldmia   sp!, {r1, lr}
	add     sp, sp, r1

	ldmia   sp!, {r1-r3, r4, r12, lr}
	msr     CPSR_c, #ARM_MODE_IRQ | I_BIT | F_BIT

	/* Acknowledge interrupt */

	ldr     lr, =AIC
	str     lr, [r14, #AIC_EOICR]

	/* Restore interrupt context and branch back to calling code */

	ldmia   sp!, {r0, lr}
	msr     SPSR_cxsf, lr
	ldmia   sp!, {pc}^


//------------------------------------------------------------------------------
/// Initializes the chip and branches to the main() function.
//------------------------------------------------------------------------------
	.section    .textEntry
	.global     entry

entry:
resetHandler:

	cpsie   a

/* Enable VFP */

	/* - Enable access to CP10 and CP11 in CP15.CACR */
	//mrc     p15, 0, r0, c1, c0, 2
	//orr     r0, r0, #0xf00000
	//mcr     p15, 0, r0, c1, c0, 2
	/* - Enable access to CP10 and CP11 in CP15.NSACR */
	/* - Set FPEXC.EN (B30) */
	//fmrx    r0, fpexc
	//orr     r0, r0, #0x40000000
	//fmxr    fpexc, r0

/* Useless instruction for referencing the .vectors section */

	ldr     r0, =resetVector

/* Set pc to actual code location (i.e. not in remap zone) */

	ldr     pc, =1f

/* Initialize the prerelocate segment */

1:
	ldr     r0, =_efixed
	ldr     r1, =_sprerelocate
	ldr     r2, =_eprerelocate
1:
	cmp     r1, r2
	ldrcc   r3, [r0], #4
	strcc   r3, [r1], #4
	bcc     1b

/* Initialize the postrelocate segment */

	//ldmfd   sp!, {r0}
	ldr     r1, =_spostrelocate
	ldr     r2, =_epostrelocate
1:
	cmp     r1, r2
	ldrcc   r3, [r0], #4
	strcc   r3, [r1], #4
	bcc     1b

/* Clear the zero segment */
	ldr     r0, =_szero
	ldr     r1, =_ezero
	mov     r2, #0
1:
	cmp     r0, r1
	strcc   r2, [r0], #4
	bcc     1b

/* Perform low-level initialization of the chip using low_level_init() */

	//ldr     sp, =_cstack
	//stmfd   sp!, {r0}
	ldr     r0, =low_level_init
	blx     r0

	mrs     r0, CPSR

/* Set up the fast interrupt stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_FIQ
	msr     CPSR_c, r0
	ldr     sp, =_fiqstack
	bic     sp, sp, #0x7

/* Set up the normal interrupt stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_IRQ
	msr     CPSR_c, r0
	ldr     sp, =_irqstack
	bic     sp, sp, #0x7

/* Set up the stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_SYS
	msr     CPSR_c, r0
	ldr     sp, =_sysstack
	bic     sp, sp, #0x7

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_SVC
	msr     CPSR_c, r0
	ldr     sp, =_cstack
	bic     sp, sp, #0x7

/* Redirect FIQ to IRQ */

	ldr     r0, =AICREDIR_KEY
	ldr     r1, =REG_SFR_UID
	ldr     r2, =REG_SFR_AICREDIR
	ldr     r3, [r1]
	eors    r0, r0, r3
	orrs    r0, r0, #0x01
	str     r0, [r2]

/* Initialize the C library */

	ldr     r3, =__libc_init_array
	mov     lr, pc
	bx      r3

/* Branch to main() */

	ldr     r0, =main
	blx     r0

/* Loop indefinitely when program is finished */

1:
	b       1b
