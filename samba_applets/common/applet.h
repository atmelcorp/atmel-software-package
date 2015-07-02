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

#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/

#define APPLET_CMD_INIT              0x00 /* Applet initialization */
#define APPLET_CMD_FULL_ERASE        0x01 /* Full erase */
#define APPLET_CMD_WRITE             0x02 /* Write */
#define APPLET_CMD_READ              0x03 /* Read */
#define APPLET_CMD_LOCK              0x04 /* Lock */
#define APPLET_CMD_UNLOCK            0x05 /* Unlock */
#define APPLET_CMD_GPNVM             0x06 /* Set/clear GPNVM command code */
#define APPLET_CMD_SECURITY          0x07 /* Set security bit command code */
#define APPLET_CMD_BUFFER_ERASE      0x08 /* Buffer erase command code */
#define APPLET_CMD_BINARY_PAGE       0x09 /* Binary page command code for Dataflash */
#define APPLET_CMD_OTP_READ          0x0A /* Read OTP */
#define APPLET_CMD_OTP_WRITE         0x0B /* Write OPT */
#define APPLET_CMD_LIST_BAD_BLOCKS   0x10 /* List Bad Blocks of a Nandflash */
#define APPLET_CMD_TAG_BLOCK         0x11 /* Tag a Nandflash Block */
#define APPLET_CMD_READ_UNIQUE_ID    0x12 /* Read the Unique ID bits (on SAM3) */
#define APPLET_CMD_ERASE_BLOCKS      0x13 /* Blocks erase command code */
#define APPLET_CMD_BATCH_ERASE       0x14 /* Batch full erase command code */
#define APPLET_CMD_PMECC_HEADER      0x15 /* Set PMECC parameter header code */
#define APPLET_CMD_SENDBOOT          0x16 /* SendBoot file code */
#define APPLET_CMD_SWITCH_ECC        0x17 /* Switch ECC mode code */
#define APPLET_CMD_TRIMFFS           0x18 /* Enable/disable drop jss */

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
	uint32_t command;     /* Applet command */
	uint32_t status;      /* Applet status, updated at the end of the applet execution */
	uint32_t args[];      /* Other command-specific arguments and return values */
};


struct applet_command
{
	uint32_t command;
	uint32_t (*handler)(uint32_t cmd, uint32_t *args);
};

extern const struct applet_command applet_commands[];

extern void applet_set_init_params(uint32_t comm, uint32_t trace);

extern void applet_main(struct applet_mailbox *mailbox);

#endif /* _APPLET_H_ */
