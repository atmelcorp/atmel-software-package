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

#include "applet.h"
#include "trace.h"
#include "misc/console.h"

static uint32_t _comm_type;

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

void applet_set_init_params(uint32_t comm, uint32_t trace)
{
	_comm_type = comm;
	trace_level = trace;
}

/**
 * \brief  Applet main entry. This function decodes received command and executes it.
 * \param mailbox  Applet mailbox
 */
void applet_main(struct applet_mailbox *mailbox)
{
	int i;

	// set default status
	mailbox->status = APPLET_FAIL;

	// look for handler and call it
	for (i = 0; applet_commands[i].handler; i++) {
		if (applet_commands[i].command == mailbox->command)
		{
			mailbox->status = applet_commands[i].handler(mailbox->command, mailbox->args);
			break;
		}
	}

	/* notify the host application of the end of the command processing */
	mailbox->command = ~(mailbox->command);

	/* send ACK character if comm type is DBGU */
	if (_comm_type == COMM_TYPE_DBGU)
		console_put_char(0x06);
}
