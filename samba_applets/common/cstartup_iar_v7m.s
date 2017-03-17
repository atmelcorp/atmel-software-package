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

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

	MODULE  ?cstartup

	SECTION CSTACK:DATA:NOROOT(3)
	SECTION .cstartup:CODE:NOROOT(2)
	EXTERN  applet_main

	THUMB

	/* Branch to the real entry point */
	b       entry

	/* Mailbox area where PC application stores arguments */
	PUBLIC applet_mailbox
applet_mailbox:
	DS32    32

	/* Address of the entry point */
applet_entry_address:
	DCD     entry

	/* Flag to indicate is the BSS needs to be cleared on the first applet
	 * call */
	PUBLIC applet_first_run
applet_first_run:
	DCD     1

	PUBLIC entry
entry:
	mov     r0, r4
	mov     r4, sp
	ldr     r1, =SFE(CSTACK)
	mov     sp, r1
	push    {r0, lr}

	/* Branch to applet main */
	ldr     r0, =applet_main
	blx     r0

	/* Jump back to romcode */
applet_end:
	mov     r0, r4
	pop     {r4, lr}
	mov     sp, r0
	bx      lr

	END
