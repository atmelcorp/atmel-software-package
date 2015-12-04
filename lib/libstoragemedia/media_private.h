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

#ifndef _MEDIA_PRIVATE_
#define _MEDIA_PRIVATE_

#include <stdbool.h>
#include <stdint.h>

/*------------------------------------------------------------------------------
 *      Types
 *------------------------------------------------------------------------------*/

/**
 *  \brief  Media transfer
 *  \see    media_transfer_t
 */
struct _media_transfer {
	void*            data;         /**< Pointer to the data buffer */
	uint32_t         address;      /**< Address where to read/write the data */
	uint32_t         length;       /**< Size of the data to read/write */
	media_callback_t callback;     /**< Callback to invoke when the transfer done */
	void*            callback_arg; /**< Callback argument */
};

/**
 *  \brief  Media object
 *  \see    _media_transfer
 */
struct _media {
	/** Write method */
	uint8_t (*write)(struct _media* media, uint32_t address, void *data, uint32_t length, media_callback_t callback, void *callback_arg);

	/** Read method */
	uint8_t (*read)(struct _media* media, uint32_t address, void *data, uint32_t length, media_callback_t callback, void *callback_arg);

	/** Cancel pending IO method */
	uint8_t (*cancel_io)(struct _media* media);

	/** Lock method */
	uint8_t (*lock)(struct _media* media, uint32_t start, uint32_t end, uint32_t *actual_start, uint32_t *actual_end);

	/** Unlock method */
	uint8_t (*unlock)(struct _media* media, uint32_t start, uint32_t end, uint32_t *actual_start, uint32_t *actual_end);

	/** IOCTL method */
	uint8_t (*ioctl)(struct _media* media, uint8_t ctrl, void *buffer);

	/** Flush method */
	uint8_t (*flush)(struct _media* media);

	/** Interrupt handler */
	void (*handler)(struct _media* media);

	/** Current transfer operation */
	struct _media_transfer transfer;

	uint32_t block_size;     /**< Block size in bytes (1, 512, 1K, 2K ...) */
	uint32_t base_address;   /**< Base address of media in number of blocks */
	uint32_t size;           /**< Size of media in number of blocks */
	void    *interface;      /**< Pointer to the physical interface used */
	bool     mapped_read;    /**< Mapped to memory space to read */
	bool     mapped_write;   /**< Mapped to memory space to write */
	bool     write_protected; /**< Protected media? */
	bool     removable;      /**< Removable/Fixed media? */
	uint8_t  state;          /**< Status of media */
};

#endif /* _MEDIA_PRIVATE_ */
