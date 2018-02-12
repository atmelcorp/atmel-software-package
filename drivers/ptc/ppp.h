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

#ifndef _PPP_H
#define _PPP_H

/*----------------------------------------------------------------------------
 *         Includes
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "mutex.h"

/*----------------------------------------------------------------------------
 *         Constants
 *----------------------------------------------------------------------------*/

/* Description */
#define PPP_SRAM_ADDR     (PPP_ADDR)
#define PPP_SRAM_LEN      (0x00004000)
#define PPP_MAILBOX_ADDR  (PPP_SRAM_ADDR + PPP_SRAM_LEN)
#define PPP_MAILBOX_LEN   (0x1000)

/*----------------------------------------------------------------------------
 *	   Types
 *----------------------------------------------------------------------------*/

struct _ppp_irq_handler {
	struct _callback on_irq0;
	struct _callback on_irq1;
	struct _callback on_irq2;
	struct _callback on_irq3;
};

struct _ppp {
	Ppp* addr;
	struct {
		struct {
			uint8_t* addr; /* Address of code/mailbox sram */
			uint16_t len;  /* Size of code/mailbox sram */
		} code, mailbox;
	} sram;

	struct {
		struct {
			uint8_t* code;
			uint16_t size;
		} firmware;
	} cfg;

	uint32_t imr;
	struct _ppp_irq_handler irq_handler;

	mutex_t mutex;
};


//
/*----------------------------------------------------------------------------
 *	  Public method prototypes
 *----------------------------------------------------------------------------*/
/**
 * \brief Initialization of PTC subsystem
 * \param ppp       Pointer to a ppp instance
 * \return 0 on success
 */
extern int ppp_configure(struct _ppp* ppp);

/**
 * \brief Registr IRQ handlers
 * \param ppp         Pointer to a ppp instance
 * \param irq         Interruption flag
 * \param handler     IRQ handler
 * \param user_arg    User argument of the handler
 */
extern void ppp_register_irq_handler(struct _ppp* ppp, uint32_t irq, callback_method_t handler, void* user_arg);

/**
 * \brief Get the start of the mailbox
 * \param ppp         Pointer to a ppp instance
 */
extern uint8_t * ppp_get_mailbox_addr(struct _ppp* ppp);

/**
 * \brief Load the pPP firmware
 */
extern void ppp_load(struct _ppp* ppp, uint8_t* firmware, uint16_t size);


/**
 * \brief Start pPP
 * \param ppp          Pointer to a ppp instance
 */
extern void ppp_start(struct _ppp* ppp);

/**
 * \brief Stop pPP
 * \param ppp          Pointer to a ppp instance
 */
extern void ppp_stop(struct _ppp* ppp);

/**
 * \brief Restart pPP
 * \param ppp          Pointer to a ppp instance
 */
extern void ppp_restart(struct _ppp* ppp);

/**
 * \brief Abort
 * \param ppp          Pointer to a ppp instance
 */
extern void ppp_abort(struct _ppp* ppp);

/**
 * \brief Reset pPP
 * \param ppp          Pointer to a ppp instance
 */
extern void ppp_reset(struct _ppp* ppp);

/**
 * \brief Enable IRQ on host
 * \param ppp          Pointer to a ppp instance
 * \param mask         IRQ mask
 */
extern void ppp_enable_it(struct _ppp* ppp, uint32_t mask);

/**
 * \brief Clear HOST pending interrupts
 * \param ppp          Pointer to a ppp instance
 * \param mask         IRQ mask
 */
extern void ppp_clear_pending_it(struct _ppp* ppp, uint32_t mask);

/**
 * \brief Notify PPP that a command is available in mailbox
 * \param ppp          Pointer to a ppp instance
 * \param mask         IRQ mask
 */
extern void ppp_notify(struct _ppp* ppp, uint32_t mask);

/**
 * \brief Disable IRQ on host
 * \param ppp          Pointer to a ppp instance
 * \param mask         IRQ mask
 */
extern void ppp_disable_it(struct _ppp* ppp, uint32_t mask);

/**
 * \brief Implement a memcpy function to avoid volatile errors
 * \param dst  Destination address
 * \param src  Source address
 * \param len  Length of the source
 */
extern void ppp_memcpy(uint8_t* dst, uint8_t* src, uint16_t len);

/**
 * \brief Send a command to pPP and wait IRQ_0 to rise
 * \param ppp       Pointer to a ppp instance
 */
extern void ppp_exec(struct _ppp* ppp);

#endif /* ! _PPP_H */
