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

/** \file
 * \addtogroup usbd_msd
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "usb/device/msd/msd_io_fifo.h"

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief  Initializes a MSDIOFifo instance.
 * \param  p_fifo        Pointer to the MSDIOFifo instance to initialize
 * \param  buffer      Pointer to a buffer used for read/write operation and
 *                      which must be blockSize bytes aligned.
 * \param  buffer_size   Total size of the buffer in bytes
 */
void msd_io_fifo_init(MSDIOFifo *p_fifo,
					void * buffer, unsigned int buffer_size)
{
	p_fifo->pBuffer = buffer;
	p_fifo->bufferSize = buffer_size;

	p_fifo->inputNdx = 0;
	p_fifo->outputNdx = 0;
	p_fifo->inputTotal = 0;
	p_fifo->outputTotal = 0;

	p_fifo->inputState = MSDIO_IDLE;
	p_fifo->outputState = MSDIO_IDLE;

	p_fifo->fullCnt = 0;
	p_fifo->nullCnt = 0;
}

/**@}*/
