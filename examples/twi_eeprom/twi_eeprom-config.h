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
#ifndef TWI_EEPROM_CONFIG
#define TWI_EEPROM_CONFIG

#include "peripherals/twid.h"
#include "memories/at24.h"


/** Slave address of the device on TWI bus. */
#define TWI_SLAVE_EEP_ADDR 0x53
/** TWI slave serial memory pages (example AT24C02)*/
#define TWI_SLAVE_EEP_PAGES 16
/** TWI slave serial memory page size (example AT24C02)*/
#define TWI_SLAVE_EEP_PAGE_SIZE 16

extern struct _at24 at24_drv;
extern struct _twi_desc at24_twid;

/* =================== TWI slave device definition ============== */
/* twi_slave examples mimics a serial memory with TWI interface. */
#if   defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI0_IOS1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWIHS0)

#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWI1)

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWI1)

#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
/* twi_slave examples mimics a serial memory with TWI interface. */
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWI1)

#elif defined(CONFIG_BOARD_SAMA5D3_EK)
/* twi_slave examples mimics a serial memory with TWI interface. */
/** TWI slave pins definition **/
#define TWI_SLAVE_PINS PINS_TWI1
/** TWI slave address definition */
#define TWI_SLAVE_ADDR ((Twi*)TWI1)

#else
#error Unsupported board...
#endif

#endif /* ! TWI_EEPROM_CONFIG_H */

