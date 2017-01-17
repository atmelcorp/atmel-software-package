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

#ifndef BUS_H
#define BUS_H

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "io.h"
#include "callback.h"
#include "mutex.h"
#ifdef CONFIG_HAVE_SPI_BUS
#include "spi/spid.h"
#endif
#ifdef CONFIG_HAVE_I2C_BUS
#include "i2c/twid.h"
#endif

/*----------------------------------------------------------------------------
 *         Exported macros
 *----------------------------------------------------------------------------*/

#define BUS_COUNT (SPI_IFACE_COUNT + TWI_IFACE_COUNT)

enum _bus_type {
	BUS_TYPE_NONE,
	BUS_TYPE_I2C,
	BUS_TYPE_SPI,
};

#define BUS(type, index) ((((type) == BUS_TYPE_SPI) ? 0 : \
	(((type) == BUS_TYPE_I2C) ? (SPI_IFACE_COUNT) : \
	(-BUS_COUNT - 1))) + (index))

enum _bus_ioctl {
	BUS_IOCTL_ENABLE = 1,
	BUS_IOCTL_DISABLE = 2,
	BUS_IOCTL_ENABLE_FIFO = 3,
	BUS_IOCTL_DISABLE_FIFO = 4,
	BUS_IOCTL_GET_FIFO_STATUS = 5,
	BUS_IOCTL_SET_TRANSFER_MODE = 6,
	BUS_IOCTL_GET_TRANSFER_MODE = 7,
	BUS_IOCTL_SET_TIMEOUT = 8,
};

/*----------------------------------------------------------------------------
 *         Exported types
 *----------------------------------------------------------------------------*/

enum _bus_buf_attr {
	BUS_BUF_ATTR_RX                = 0x0001,
	BUS_BUF_ATTR_TX                = 0x0002,

#ifdef CONFIG_HAVE_SPI_BUS
	BUS_SPI_BUF_ATTR_RELEASE_CS        = 0x0800,
#endif

#ifdef CONFIG_HAVE_I2C_BUS
	BUS_I2C_BUF_ATTR_START             = 0x1000,
	BUS_I2C_BUF_ATTR_STOP              = 0x2000,
#endif
};

enum _bus_transfer_mode {
	BUS_TRANSFER_MODE_POLLING,
	BUS_TRANSFER_MODE_ASYNC,
	BUS_TRANSFER_MODE_DMA,
};

struct _bus_iface {
	enum _bus_type type;
	union {
		uint32_t dummy;
#ifdef CONFIG_HAVE_SPI_BUS
		struct {
			Spi* hw;
		} spi;
#endif
#ifdef CONFIG_HAVE_I2C_BUS
		struct {
			Twi* hw;
			uint32_t freq;
 		} i2c;
#endif
	};
	enum _bus_transfer_mode transfer_mode;
};

struct _bus_dev_cfg {
	uint8_t bus;
	union {
		uint32_t dummy;
#ifdef CONFIG_HAVE_SPI_BUS
		struct {
			uint8_t chip_select;
			uint32_t bitrate;
			struct {
				uint32_t bs;
				uint32_t bct;
			} delay;
			enum _spid_mode spi_mode;
		} spi_dev;
#endif
	};
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configure an I2C or SPI bus
 *
 * \param bus_id     bus id
 * \param iface      Pointer to the configuration of the interface to plug on
 * \return 0 on success, < 0 on error
 */
int bus_configure(uint8_t bus_id, const struct _bus_iface* iface);

/**
 * \brief Configure a remote device on the bus
 *
 * \param bus_id     bus id
 * \param cfg        Pointer to the configuration to reach a specific remote on the bus
 * \return 0 on success, < 0 on error
 */
int bus_configure_slave(uint8_t bus_id, const struct _bus_dev_cfg* cfg);

/**
 * Control the bus with specific functions
 *
 * \param bus_id  The bus to control
 * \param req     The control to use
 *  - BUS_IOCTL_ENABLE: arg is ignored
 *  - BUS_IOCTL_DISABLE: arg is ignored,
 *  - BUS_IOCTL_ENABLE_FIFO: arg is ignored
 *  - BUS_IOCTL_DISABLE_FIFO: arg is ignored
 *  - BUS_IOCTL_GET_FIFO_STATUS: arg is a bool*
 *  - BUS_IOCTL_SET_TRANSFER_MODE: arg is an enum _bus_transfer_mode*
 *  - BUS_IOCTL_GET_TRANSFER_MODE: arg is an enum _bus_transfer_mode*
 *  - BUS_IOCTL_SET_TIMEOUT: arg is a uint32_t*
 *
 * \param arg     Argument of a control
 * \return 0 on success, < 0 on error
 */
int bus_ioctl(uint8_t bus_id, int req, void* arg);

/**
 * Lock the bus to transfer data.
 * One transaction can lock the bus for multiple data transfer.
 *
 * It is mandatory to lock the bus before trasnferring data
 * \param bus_id     Bus id
 * \return 0 on success, < 0 on error
 */
int bus_start_transaction(uint8_t bus_id);

/**
 * Unlock the bus at the end of a transaction
 * \param bus_id     Bus id
 * \return 0 on success, < 0 on error
 */
int bus_stop_transaction(uint8_t bus_id);

/**
 * \brief Wait until the current transaction is over
 *
 * \param bus_id     bus id
 */
void bus_wait_transaction(uint8_t bus_id);

/**
 * \brief Start a data transfer on bus \bus_id for remote at address \remote
 *
 * \param bus_id     bus id
 * \param remote     Address of the remote device
 * \param buf        List of buffer to transfer
 * \param buffers    Number of buffers to transfer
 * \param cb         Callback to call when transfer is over
 * \return 0 on success, < 0 on error
 */
int bus_transfer(uint8_t bus_id, uint16_t remote, struct _buffer* buf, uint16_t buffers, struct _callback* cb);

/**
 * \brief Verify is the bus is in use
 *
 * \param bus_id     bus id
 * \return true if the bus is in use, else return false
 */
bool bus_is_busy(uint8_t bus_id);

/**
 * \brief Wait until the current transfer is over
 *
 * \param bus_id     bus id
 * \return 0 on succes, errno on error
 */
int bus_wait_transfer(uint8_t bus_id);

/**
 * \brief Suspend the bus if possible
 *
 * \param bus_id     bus id
 * \return 0 on success, < 0 on error
 */
int bus_suspend(uint8_t bus_id);

#endif /* ! BUS_H */
