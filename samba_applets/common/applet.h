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

#ifndef _APPLET_H_
#define _APPLET_H_

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/

#define APPLET_CMD_INITIALIZE        0x00 /* Initialization */
#define APPLET_CMD_LEGACY_WRITE      0x02 /* Write (legacy) */
#define APPLET_CMD_LEGACY_READ       0x03 /* Read (legacy) */
#define APPLET_CMD_READ_INFO         0x30 /* Read Info */
#define APPLET_CMD_ERASE_PAGES       0x31 /* Erase pages */
#define APPLET_CMD_READ_PAGES        0x32 /* Read pages */
#define APPLET_CMD_WRITE_PAGES       0x33 /* Write pages */
#define APPLET_CMD_READ_BOOTCFG      0x34 /* Read Boot Config */
#define APPLET_CMD_WRITE_BOOTCFG     0x35 /* Write Boot Config */

#define APPLET_SUCCESS               0x00 /* Operation was successful */
#define APPLET_DEV_UNKNOWN           0x01 /* Device unknown */
#define APPLET_WRITE_FAIL            0x02 /* Write operation failed */
#define APPLET_READ_FAIL             0x03 /* Read operation failed */
#define APPLET_PROTECT_FAIL          0x04 /* Protect operation failed */
#define APPLET_UNPROTECT_FAIL        0x05 /* Unprotect operation failed */
#define APPLET_ERASE_FAIL            0x06 /* Erase operation failed */
#define APPLET_NO_DEV                0x07 /* No device defined in board.h */
#define APPLET_ALIGN_ERROR           0x08 /* Read / write address is not aligned */
#define APPLET_BAD_BLOCK             0x09 /* Read / write found bad block */
#define APPLET_PMECC_CONFIG          0x0A /* ECC configure failure */
#define APPLET_FAIL                  0x0F /* Generic/Unknown failure */

/* Communication link identification */
#define COMM_TYPE_USB                0x00
#define COMM_TYPE_DBGU               0x01
#define COMM_TYPE_JTAG               0x02

/**
 * \brief Structure for storing parameters for each command that can be performed by the applet.
 *
 * Structure size must be <= 32 words.
 */
struct applet_mailbox
{
	uint32_t command; /* Applet command */
	uint32_t status;  /* Applet status, updated at the end of the applet execution */
	uint32_t data[];  /* Other command-specific arguments and return values */
};

/** Mailbox content for the 'initialize' command. */
union initialize_mailbox
{
	struct {
		/** Type of communication link used */
		uint32_t comm_type;
		/** Trace level */
		uint32_t trace_level;
		/** Console instance */
		uint32_t console_instance;
		/** Console ioset */
		uint32_t console_ioset;
		/** Initialization parameters */
		uint32_t parameters[4];
	} in;

	struct {
		/** Buffer address */
		uint32_t buf_addr;
		/** Buffer size (in bytes) */
		uint32_t buf_size;
		/** Page size (in bytes) */
		uint32_t page_size;
		/** Memory size (in pages) */
		uint32_t mem_size;
		/** Supported erase size (in pages) */
		uint32_t erase_support;
		/** NAND header (if applicable) */
		uint32_t nand_header;
	} out;
};

/** Mailbox content for the 'read boot config' command. */
union read_bootcfg_mailbox
{
	struct {
		/** Configuration index to read */
		uint32_t index;
	} in;

	struct {
		/** Configuration value */
		uint32_t value;
	} out;
};

/** Mailbox content for the 'write boot config' command. */
union write_bootcfg_mailbox
{
	struct {
		/** Configuration index to read */
		uint32_t index;

		/** Configuration value */
		uint32_t value;
	} in;
};

/** Mailbox content for the 'read/write/erase pages' commands. */
union read_write_erase_pages_mailbox {
	struct {
		/** Read/Write/Erase offset (in pages) */
		uint32_t offset;
		/** Read/Write/Erase length (in pages) */
		uint32_t length;
	} in;

	struct {
		/** Pages read/written/erased */
		uint32_t pages;
	} out;
};

typedef uint32_t (*applet_command_handler_t)(uint32_t cmd, uint32_t *args);

struct applet_command
{
	uint32_t command;
	applet_command_handler_t handler;
};

extern uint8_t *applet_buffer;
extern uint32_t applet_buffer_size;

extern const struct applet_command applet_commands[];

extern bool applet_set_init_params(union initialize_mailbox* mbx);

extern applet_command_handler_t get_applet_command_handler(uint8_t cmd);

extern void applet_main(void);

#endif /* _APPLET_H_ */
