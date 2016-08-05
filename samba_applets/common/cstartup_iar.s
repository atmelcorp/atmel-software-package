/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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

	MODULE  ?cstartup

	;; Forward declaration of sections.
	SECTION CSTACK:DATA:NOROOT(3)

	SECTION .cstartup:CODE:NOROOT(2)
	PUBLIC  entry
	PUBLIC  __iar_program_start
	EXTERN  __iar_data_init3
	EXTERN  applet_main

	ARM

/* Main Application entry*/
entry:
__iar_program_start:
?cstartup:
	/* Branch to the init after the arguments */
	b       init

	/* Mailbox area where PC application stores arguments */
mailbox:
	DS32  32

is_initialized:
	DCD   0

init:
	stmdb   sp!, {r0-r4,lr}
	mov     r4, sp
	ldr     sp, =SFE(CSTACK)

	/* Clear the zero segment only the first time the applet is loaded */

	/* Check the is_initialized flag  */

	mov     r0, #0
	ldr     r1, is_initialized
	cmp     r0, r1
	bne     run_main

	/* Clear the zero segment */

	FUNCALL __iar_program_start, __iar_data_init3
	bl      __iar_data_init3

	/* Update the is_initialized flag */

	mov     r1, #1
	str     r1, is_initialized

	/* Branch to main */
run_main:
	ADR     r0, mailbox
	ldr     r3, =applet_main
	push    {r4}
	blx     r3
	pop     {r4}

	/* Jump back to romcode */
applet_end:
	mov     sp, r4
	ldmfd   sp!, {r0-r4,lr}
	bx      lr

	END
