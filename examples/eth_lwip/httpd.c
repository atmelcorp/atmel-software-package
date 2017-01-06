/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

/* lwIP Demo */
/* A simple HTTP/1.0 server direcly interfacing the stack. */

#include "board.h"

#include "liblwip.h"
#include "lwip/opt.h"
#include "lwip/tcp.h"

#include "httpd.h"

#include <stdio.h>

#define COUNTER_DISP_INDEX      119

/* This is the data for the actual web page. */
static char indexdata[] =
"HTTP/1.1 200 OK\r\n\
Content-type: text/html\r\n\
\r\n\
<html> \
<head><title>lwIP test page</title></head> \
<body> \
Small test page. \
</body> \
</html>";

/**
 * This is the callback function that is called
 * when a TCP segment has arrived in the connection.
 */
static err_t
httpd_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
	char *rq;
	arg = arg;

	//printf("CB recv %x, %x, %x, %x\n\r", arg, pcb, p, err);
	if (err != ERR_OK) {
		return err;
	}

	/* If we got a NULL pbuf in p, the remote end has closed
	the connection. */
	if(p != NULL) {
		/* The payload pointer in the pbuf contains the data
		in the TCP segment. */
		rq = p->payload;

		/* Check if the request was an HTTP "GET /\r\n".
					    or HTTP "GET / HTTP/1.1\r\n" */
		if(rq[0] == 'G' && rq[1] == 'E' && rq[2] == 'T' &&
				rq[3] == ' ' && rq[4] == '/' &&
				((rq[ 5] == '\r' && rq[ 6] == '\n') ||
				 (rq[14] == '\r' && rq[15] == '\n')) ) {
			/* Send the web page to the remote host. A zero
			 in the last argument means that the data should
			 not be copied into internal buffers. */
			tcp_write(pcb, indexdata, sizeof(indexdata), 0);
		}

		/* Free the pbuf. */
		pbuf_free(p);
	}
	/* send a segment including FIN flag but not data. */
	tcp_close(pcb);
	return ERR_OK;
}

/**
 * This is the callback function that is called when
 * a connection has been accepted.
 */
static err_t httpd_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
	arg = arg;

	if (err != ERR_OK) {
		return err;
	}

	/* Set up the function httpd_recv() to be called when data
	arrives. */
	tcp_recv(pcb, httpd_recv);

	return ERR_OK;
}

/**
 * The initialization function.
 */
err_t httpd_init(void)
{
	struct tcp_pcb *pcb;
	err_t  err;

	/* Create a new TCP PCB. */
	pcb = tcp_new();
	if (pcb == NULL) {
		printf("F: Fail to create PCB\n\r");
		return ERR_BUF;
	}

	/* Bind the PCB to TCP port 80. */
	err = tcp_bind(pcb, NULL, 80);
	if (err != ERR_OK) {
		printf("E: tcp_bind %x\n\r", err);
		return err;
	}

	/* Change TCP state to LISTEN. */
	pcb = tcp_listen(pcb);
	if (pcb == NULL) {
		printf("E: tcp_listen\n\r");
		return ERR_BUF;
	}

	/* Set up httpd_accet() function to be called
	when a new connection arrives. */
	tcp_accept(pcb, httpd_accept);

	return ERR_OK;
}

