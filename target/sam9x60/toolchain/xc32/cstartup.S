/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/


//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

#define AIC         0xFFFFF100
#define AIC_SMR0    0x004
#define AIC_IVR     0x010
#define AIC_EOICR   0x038

#define MODE_MSK         0x1F

#define ARM_MODE_FIQ     0x11
#define ARM_MODE_IRQ     0x12
#define ARM_MODE_SVC     0x13
#define ARM_MODE_ABT     0x17
#define ARM_MODE_UND     0x1B
#define ARM_MODE_SYS     0x1F

#define I_BIT            0x80
#define F_BIT            0x40

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

	.align      4
	.arm

/* Exception vectors
 *******************/
	.section    .vectors, code

resetVector:
/* Reset */
	ldr     pc, =resetHandler
/* Undefined Instruction */
	ldr     pc, =undefined_instruction_irq_handler
/* Software Interrupt */
	ldr     pc, =software_interrupt_irq_handler
/* Prefetch Abort */
	ldr     pc, =prefetch_abort_irq_handler
/* Data Abort */
	ldr     pc, =data_abort_irq_handler
/* Reserved for future use */
	.word   0
/* Interrupt */
	ldr     pc, =irqHandler
/* Fast interrupt */
	ldr     pc, =fiqHandler

	.section    .text, code

//------------------------------------------------------------------------------
/// Handles a fast interrupt request by branching to the address defined in the
/// AIC.
//------------------------------------------------------------------------------
fiqHandler:
	b fiqHandler

//------------------------------------------------------------------------------
/// Handles incoming interrupt requests by branching to the corresponding
/// handler, as defined in the AIC. Supports interrupt nesting.
//------------------------------------------------------------------------------
#ifdef CONFIG_RAMCODE
	.section .ramcode_section
#endif
irqHandler:
	/* Save interrupt context on the stack to allow nesting */

	sub     lr, lr, #4
	stmfd   sp!, {lr}
	mrs     lr, SPSR
	stmfd   sp!, {r0, lr}
#ifdef CONFIG_TIMER
	bl board_get_timer
#endif
#ifdef CONFIG_RAMCODE
	ldr r0, =_ddr_active_needed
	ldr r0, [r0]
	cmp r0, #0x0
	beq 1f
	bl ddram_active
1:
#endif

	/* Write in the IVR to support Protect Mode */

	ldr     lr, =AIC
	ldr     r0, [r14, #AIC_IVR]
	str     lr, [r14, #AIC_IVR]
	/* Dummy read to force AIC_IVR write completion */
	ldr     lr, [r14, #AIC_SMR0]

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
	.section    .textEntry, code
	.global     entry

entry:
	/* Dummy vector table for ROM-code for cases when the real vector table
	 * is relocated (QSPI-XIP) */
	ldr     pc, =resetHandler
	ldr     pc, =resetHandler
	ldr     pc, =resetHandler
	ldr     pc, =resetHandler
	ldr     pc, =resetHandler
	.word   0
	ldr     pc, =resetHandler
	ldr     pc, =resetHandler

resetHandler:

	mov     r0, #0

/* Set up the normal interrupt stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_IRQ
	msr     CPSR_c, r0
	ldr     sp, =_irqstack
	bic     sp, sp, #0x7

/* Set up the abort mode stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_ABT
	msr     CPSR_c, r0
	ldr     sp, =_abtstack
	bic     sp, sp, #0x7

/* Set up the undefined mode stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_UND
	msr     CPSR_c, r0
	ldr     sp, =_undstack
	bic     sp, sp, #0x7

/* Set up the system mode stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_SYS
	msr     CPSR_c, r0
	ldr     sp, =_sysstack
	bic     sp, sp, #0x7

/* Set up the supervisor mode stack pointer */

	bic     r0, r0, #MODE_MSK
	orr     r0, r0, #ARM_MODE_SVC
	msr     CPSR_c, r0
	ldr     sp, =_cstack
	bic     sp, sp, #0x7

/* Relocate */
	ldr     r0, =_etext
	ldr     r1, =_srelocate
	ldr     r2, =_erelocate
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

/* Remap SRAM at 0x00000000 */
	bl      matrix_remap_ram

/* Initialize the C library */

	bl      __libc_init_array

/* Perform board initialization */

	bl      board_init

/* Branch to main() */

	bl      main

/* Loop indefinitely when program is finished */

1:
	b       1b
