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

/**
 * \file
 *
 *  \unit
 *  \section Purpose
 *
 *  Generic Media type, which provides transparent access to all types of
 *  memories.
 *
 *  \note The physical or HW related media operations (physical device
 *        connection & protection detecting, PIO configurations and interface
 *        driver initialization) are excluded.
 *
 *  \section Usage
 *  -# Do PIO initialization for peripheral interfaces.
 *  -# Initialize peripheral interface driver & device driver.
 *  -# Initialize specific media interface and link to this initialized driver.
 *
 */

#ifndef _MEDIA_
#define _MEDIA_

#include <stdbool.h>
#include <stdint.h>

/*------------------------------------------------------------------------------
 *      Definitions
 *------------------------------------------------------------------------------*/

/**
 *  \brief  Operation result code returned by media methods
 */
#define MEDIA_STATUS_SUCCESS      0x00    /** Operation success */
#define MEDIA_STATUS_ERROR        0x01    /** Operation error */
#define MEDIA_STATUS_BUSY         0x02    /** Failed because media is busy */
#define MEDIA_STATUS_PROTECTED    0x04    /** Write failed because of WP */

/**
 *  \brief Media statuses
 */
#define MEDIA_STATE_NOT_READY     0xFF     /** Media is not connected */
#define MEDIA_STATE_READY         0x00     /** Media is ready for access */
#define MEDIA_STATE_BUSY          0x01     /** Media is busy */

/*------------------------------------------------------------------------------
 *      Types
 *------------------------------------------------------------------------------*/

typedef void (*media_callback_t)(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining);

struct _media;

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

extern uint8_t media_write(struct _media *media, uint32_t address, void *data, uint32_t length, media_callback_t callback, void *callback_arg);
extern uint8_t media_read(struct _media *media, uint32_t address, void *data, uint32_t length, media_callback_t callback, void *callback_arg);
extern uint8_t media_lock(struct _media *media, uint32_t start, uint32_t end, uint32_t *actual_start, uint32_t *actual_end);
extern uint8_t media_unlock(struct _media *media, uint32_t start, uint32_t end, uint32_t *actual_start, uint32_t *actual_end);
extern uint8_t media_flush(struct _media *media);
extern void media_handler(struct _media *media);
extern void media_deinit(struct _media *media);

extern bool media_is_initialized(struct _media *media);
extern bool media_is_busy(struct _media *media);
extern bool media_is_mapped_read_supported(struct _media *media);
extern bool media_is_mapped_write_supported(struct _media *media);
extern bool media_is_write_protected(struct _media *media);

extern uint8_t media_get_state(struct _media *media);
extern uint32_t media_get_block_size(struct _media *media);
extern uint32_t media_get_size(struct _media *media);
extern uint32_t media_get_mapped_address(struct _media *media, uint32_t block);

extern void media_handle_all(struct _media *medias, int num_media);

#endif /* _MEDIA_ */

