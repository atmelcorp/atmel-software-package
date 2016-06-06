/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

	.align      4
	.arm

/* Main Application entry*/
	.section    .textEntry
	.global     entry
entry:
	/* Branch to the init after the arguments */
	b       init

	/* Mailbox area where PC application stores arguments */
mailbox:
	.space  4 * 32

is_initialized:
	.word   0

init:
	stmdb   sp!, {r0-r4,lr}
	mov     r4, sp
	ldr     sp, =_cstack

	/* Clear the zero segment only the first time the applet is loaded */

	/* Check the is_initialized flag  */

	ldr     r0, [pc, #-(8+.-is_initialized)]
	mov     r1, #0
	cmp     r0, r1
	bne     2f

	/* Clear the zero segment */

	ldr     r0, =_szero
	ldr     r1, =_ezero
	mov     r2, #0
1:
	cmp     r0, r1
	strcc   r2, [r0], #4
	bcc     1b

	/* Initialize the C library */

	ldr     r0, =__libc_init_array
	blx     r0

	/* Update the is_initialized flag */

	mov     r1, #1
	mov     r2, #-(12+.-is_initialized)
	str     r1, [pc,r2]

	/* Branch to main */
2:
	add     r0, pc, #-(8+.-mailbox)
	ldr     r3, =applet_main
	push    {r4}
	blx     r3
	pop     {r4}

	/* Jump back to SAM-BA */
applet_end:
	mov     sp, r4
	ldmfd   sp!, {r0-r4,lr}
	bx      lr
