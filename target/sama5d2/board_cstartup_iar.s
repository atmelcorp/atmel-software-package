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

/*
     IAR startup file for SAMA5D2X microcontrollers.
 */

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION IRQ_STACK:DATA:NOROOT(2)
        SECTION FIQ_STACK:DATA:NOROOT(2)
		SECTION UND_STACK:DATA:NOROOT(2)
        SECTION ABT_STACK:DATA:NOROOT(2)
        SECTION CSTACK:DATA:NOROOT(3)

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#define __ASSEMBLY__

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

AT91C_BASE_AIC	DEFINE	0xFC020000
AIC_IVR     	DEFINE	0x10
AIC_EOICR   	DEFINE	0x38

#define L2CC_CR     0x00A00100

#define REG_SFR_AICREDIR        0xF8028054
#define REG_SFR_UID             0xF8028050
#define AICREDIR_KEY            0x5F67B102

MODE_MSK DEFINE 0x1F            ; Bit mask for mode bits in CPSR

#define ARM_MODE_ABT     0x17
#define ARM_MODE_FIQ     0x11
#define ARM_MODE_IRQ     0x12
#define ARM_MODE_SVC     0x13
#define ARM_MODE_SYS     0x1F
#define ARM_MODE_UND     0x1B

I_BIT		DEFINE	0x80
F_BIT		DEFINE	0x40

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

;
; The module in this file are included in the libraries, and may be
; replaced by any user-defined modules that define the PUBLIC symbol
; _reset_handler or a user defined start symbol.
;
; To override the cstartup defined in the library, simply add your
; modified version to the workbench project.

        SECTION .vectors:CODE:NOROOT(2)

        PUBLIC  _reset_vector
        PUBLIC  __iar_program_start
		PUBLIC  IRQ_handler
        PUBLIC  FIQ_handler

        EXTERN  undefined_c_Handler
        EXTERN  prefetch_c_handler
        EXTERN  abort_c_handler
        EXTERN  SWI_Handler



        DATA

__iar_init$$done:               ; The vector table is not needed
                                ; until after copy initialization is done

_reset_vector:                  ; Make this a DATA label, so that stack usage
                                ; analysis doesn't consider it an uncalled fun

        ARM

        ; All default exception handlers (except reset) are
        ; defined as weak symbol definitions.
        ; If a handler is defined by the application it will take precedence.
        LDR     PC,reset_addr           ; 0x0 Reset
        LDR     PC,undefined_addr       ; 0x4 Undefined instructions
        LDR     PC,SWI_Addr             ; 0x8 Software interrupt (SWI/SVC)
        LDR     PC,prefetch_addr        ; 0xc Prefetch abort
        LDR     PC,abort_addr           ; 0x10 Data abort
        DCD     0                       ; 0x14 RESERVED
        LDR     PC,IRQ_Addr             ; 0x18 IRQ
        LDR     PC,FIQ_Addr             ; 0x1c FIQ

        DATA

reset_addr:     DCD   __iar_program_start
undefined_addr: DCD   undefined_c_Handler
SWI_Addr:       DCD   SWI_Handler
prefetch_addr:  DCD   prefetch_c_handler
abort_addr:     DCD   abort_c_handler
IRQ_Addr:       DCD   IRQ_handler
FIQ_Addr:       DCD   FIQ_handler


; --------------------------------------------------
; ?cstartup -- low-level system initialization code.
;
; After a reset execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
;

        SECTION .text:CODE:NOROOT(2)
		PUBLIC	__iar_program_start
        EXTERN  ?main
		EXTERN 	low_level_init
        REQUIRE _reset_vector

       	EXTERN  cp15_invalid_btb
        EXTERN  cp15_invalid_translation_table
        EXTERN  cp15_invalid_icache
        EXTERN  cp15_invalid_dcache_by_set_way

        ARM

__iar_program_start:
?cstartup:

;
; Add initialization needed before setup of stackpointers here.
;

        ldr     r4, =SFE(CSTACK)     ; End of SVC stack
        bic     r4,r4,#0x7           ; Make sure SP is 8 aligned
        mov     sp, r4

        ;; Set up the normal interrupt stack pointer.

        msr   CPSR_c, #(ARM_MODE_IRQ | F_BIT | I_BIT)
        ldr   sp, =SFE(IRQ_STACK)     ; End of IRQ_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Set up the fast interrupt stack pointer.

        msr     CPSR_c, #(ARM_MODE_FIQ | F_BIT | I_BIT)
        ldr     sp, =SFE(FIQ_STACK)     ; End of FIQ_STACK
        bic   sp,sp,#0x7              ; Make sure SP is 8 aligned

        msr     CPSR_c, #(ARM_MODE_ABT | F_BIT | I_BIT)
        ldr     sp, =SFE(ABT_STACK)     ; End of ABT_STACK
        bic     sp,sp,#0x7              ; Make sure SP is 8 aligned

        msr     CPSR_c, #(ARM_MODE_UND | F_BIT | I_BIT)
        ldr     sp, =SFE(UND_STACK)     ; End of UND_STACK
        bic     sp,sp,#0x7              ; Make sure SP is 8 aligned

        msr     CPSR_c, #(ARM_MODE_SYS | F_BIT | I_BIT)
        ldr     sp, =SFE(CSTACK-0x3000) ; 0x1000 bytes of SYS stack
        bic     sp,sp,#0x7              ; Make sure SP is 8 aligned


        msr     CPSR_c, #(ARM_MODE_SVC | F_BIT | I_BIT)
        cpsie	a

        /* Enable VFP */
        /* - Enable access to CP10 and CP11 in CP15.CACR */
        mrc   p15, 0, r0, c1, c0, 2
        orr   r0, r0, #0xf00000
        mcr   p15, 0, r0, c1, c0, 2
        /* - Enable access to CP10 and CP11 in CP15.NSACR */
        /* - Set FPEXC.EN (B30) */
#ifdef __ARMVFP__
        mov   r3, #0x40000000
        vmsr  FPEXC, r3
#endif

         // Redirect FIQ to IRQ
        ldr r0,  =AICREDIR_KEY
        ldr  r1, = REG_SFR_UID
        ldr  r2, = REG_SFR_AICREDIR
        ldr  r3,[r1]
        eors r0, r0, r3
        orrs r0, r0, #0x01
        str  r0, [r2]

         /* Perform low-level initialization of the chip using LowLevelInit() */
        ldr     r0, =low_level_init
        blx     r0


        mrc     p15, 0, r0, c1, c0, 0       ; Read CP15 Control Regsiter into r0
        tst     r0, #0x1                    ; Is the MMU enabled?
        bicne   r0, r0, #0x1                ; Clear bit 0
        tst     r0, #0x4                    ; Is the Dcache enabled?
        bicne   r0, r0, #0x4                ; Clear bit 2
        mcrne   p15, 0, r0, c1, c0, 0       ; Write value back

        // Disbale L2 cache
        ldr r1,=L2CC_CR
        mov r2,#0
        str r2, [r1]

        DMB
        bl      cp15_invalid_translation_table
        bl      cp15_invalid_btb
        bl      cp15_invalid_icache
        bl      cp15_invalid_dcache_by_set_way
        DMB
        ISB

        	FUNCALL _reset_handler, ?main
        ldr     r0, =?main
        blx     r0

       ;; Loop indefinitely when program is finished
loop4:  b       loop4

;------------------------------------------------------------------------------
;- Function             : IRQ_Handler
;- Treatments           : IRQ Controller Interrupt Handler.
;- Called Functions     : AIC_IVR[interrupt]
;------------------------------------------------------------------------------

        SECTION .text:CODE:NOROOT(2)
        ARM
IRQ_handler:

;- Manage Exception Entry
;- Adjust and save LR_irq in IRQ stack
		sub         lr, lr, #4
        stmfd       sp!, {lr}
;- Save and r0 in IRQ stack
        stmfd       sp!, {r0}

;- Write in the IVR to support Protect Mode
;- No effect in Normal Mode
;- De-assert the NIRQ and clear the source in Protect Mode
        ldr         r14, =AT91C_BASE_AIC
	    ldr         r0 , [r14, #AIC_IVR]
	   	str         r14, [r14, #AIC_IVR]

;- Enable Interrupt and Switch in Supervisor Mode
        msr         CPSR_c, #ARM_MODE_SVC

;- Save scratch/used registers and LR in User Stack
        stmfd       sp!, { r1-r3, r12, r14}

;- Branch to the routine pointed by the AIC_IVR
        mov         r14, pc
        bx          r0

;- Restore scratch/used registers and LR from User Stack
        ldmia       sp!, { r1-r3, r12, r14}

;- Disable Interrupt and switch back in IRQ mode
        msr         CPSR_c, #I_BIT | ARM_MODE_IRQ

;- Mark the End of Interrupt on the AIC
        ldr         r14, =AT91C_BASE_AIC
        str         r14, [r14, #AIC_EOICR]

;- Restore SPSR_irq and r0 from IRQ stack
        ldmia       sp!, {r0}

;- Restore adjusted  LR_irq from IRQ stack directly in the PC
		ldmia       sp!, {pc}^


;------------------------------------------------------------------------------
;- Function             : FIQ_Handler
;- Treatments           : FIQ Controller Interrupt Handler.
;- Called Functions     : AIC_IVR[interrupt]
;------------------------------------------------------------------------------

AT91C_BASE_SAIC   DEFINE   0xF803C000
AIC_FVR           DEFINE   0x14


        SECTION .text:CODE:NOROOT(2)
        ARM
FIQ_handler:

;- Manage Exception Entry
;- Adjust and save LR_irq in IRQ stack
        sub         lr, lr, #4
        stmfd       sp!, {lr}
;- Save and r0 in IRQ stack
        stmfd       sp!, {r0}

;- Write in the IVR to support Protect Mode
;- No effect in Normal Mode
;- De-assert the NIRQ and clear the source in Protect Mode
        ldr         r14, =AT91C_BASE_SAIC
	    ldr         r0 , [r14, #AIC_IVR]
	    str         r14, [r14, #AIC_IVR]

;- Enable Interrupt and Switch in Supervisor Mode
        msr         CPSR_c, #ARM_MODE_SVC

;- Save scratch/used registers and LR in User Stack
        stmfd       sp!, { r1-r3, r12, r14}

;- Branch to the routine pointed by the AIC_IVR
        mov         r14, pc
        bx          r0

;- Restore scratch/used registers and LR from User Stack
        ldmia       sp!, { r1-r3, r12, r14}

;- Disable Interrupt and switch back in IRQ mode
        msr         CPSR_c, #ARM_MODE_FIQ

;- Mark the End of Interrupt on the AIC
        ldr         r14, =AT91C_BASE_SAIC
        str         r14, [r14, #AIC_EOICR]

;- Restore SPSR_irq and r0 from IRQ stack
        ldmia       sp!, {r0}

;- Restore adjusted  LR_irq from IRQ stack directly in the PC
        ldmia       sp!, {pc}^

;------------------------------------------------------------------------------
;------------------------------------------------------------------------------


        END
