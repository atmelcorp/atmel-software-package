/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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
 */

#ifndef _SPI_FLASH_H
#define _SPI_FLASH_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "intmath.h"
#include "peripherals/bus.h"
#ifdef CONFIG_HAVE_QSPI
#include "spi/qspi.h"
#endif
#include "spi/spid.h"

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define SFLASH_MAX_ID_LEN      6
#define SFLASH_DEFAULT_TIMEOUT 500000 /* 500 ms */

/**
 * Manufacturer IDs.
 */
#define SFLASH_MFR_ATMEL     0x1F
#define SFLASH_MFR_MACRONIX  0xC2
#define SFLASH_MFR_MICRON    0x20
#define SFLASH_MFR_SPANSION  0x01
#define SFLASH_MFR_SST	     0xBF
#define SFLASH_MFR_WINBOND   0xEF

/**
 * Read instructions.
 */
#define SFLASH_INST_READ            0x03
#define SFLASH_INST_FAST_READ	    0x0B
#define SFLASH_INST_FAST_READ_1_1_2 0x3B
#define SFLASH_INST_FAST_READ_1_2_2 0xBB
#define SFLASH_INST_FAST_READ_1_1_4 0x6B
#define SFLASH_INST_FAST_READ_1_4_4 0xEB
#define SFLASH_INST_READ_SR         0x05
#define SFLASH_INST_READ_CR         0x35
#define SFLASH_INST_READ_SR2        0x3F
#define SFLASH_INST_READ_FSR        0x70
#define SFLASH_INST_READ_VCR        0x85
#define SFLASH_INST_READ_ID         0x9F
#define SFLASH_INST_READ_SFDP       0x5A

/**
 * Write instructions.
 */
#define SFLASH_INST_WRITE_SR           0x01
#define SFLASH_INST_PAGE_PROGRAM       0x02
#define SFLASH_INST_WRITE_DISABLE      0x04
#define SFLASH_INST_WRITE_ENABLE       0x06
#define SFLASH_INST_PAGE_PROGRAM_1_1_4 0x32
#define SFLASH_INST_PAGE_PROGRAM_1_4_4 0x38
#define SFLASH_INST_WRITE_SR2          0x3E
#define SFLASH_INST_WRITE_VCR          0x81
#define SFLASH_INST_ULBPR              0x98
#define SFLASH_INST_RESET_ENABLE       0x66
#define SFLASH_INST_RESET              0x99

/**
 * Erase instructions.
 */
#define SFLASH_INST_ERASE_4K  0x20
#define SFLASH_INST_ERASE_32K 0x52
#define SFLASH_INST_ERASE_64K 0xD8

/**
 * 4-byte address instruction set.
 */
#define SFLASH_INST_READ_4B               0x13
#define SFLASH_INST_FAST_READ_4B          0x0C
#define SFLASH_INST_FAST_READ_1_1_2_4B    0x3C
#define SFLASH_INST_FAST_READ_1_2_2_4B    0xBC
#define SFLASH_INST_FAST_READ_1_1_4_4B    0x6C
#define SFLASH_INST_FAST_READ_1_4_4_4B    0xEC
#define SFLASH_INST_PAGE_PROGRAM_4B       0x12
#define SFLASH_INST_PAGE_PROGRAM_1_1_4_4B 0x34
#define SFLASH_INST_PAGE_PROGRAM_1_4_4_4B 0x3E
#define SFLASH_INST_ERASE_4K_4B	          0x21
#define SFLASH_INST_ERASE_32K_4B          0x5C
#define SFLASH_INST_ERASE_64K_4B          0xDC

/**
 * Status Register
 */
#define SR_WIP                  (0x1UL << 0)
#define SR_SWP                  (0x3UL << 2)
#define SR_SWP_PROTECT_NONE     (0x0UL << 2)
#define SR_SWP_PROTECT_SOME     (0x1UL << 2)
#define SR_SWP_PROTECT_ALL      (0x3UL << 2)
#define SR_QE_MX                (0x1UL << 6)
#define SR_SPRL                 (0x1UL << 7)
#define SR_SPRL_UNLOCKED        (0x0UL << 7)
#define SR_SPRL_LOCKED          (0x1UL << 7)

/**
 * Configuration Register
 */
#define CR_QE_SPAN (0x1UL << 1)

/**
 * Flag Status Register
 */
#define FSR_READY (0x1UL << 7)

/**
 * Status Register 2
 */
#define SR2_QE_BIT7 (0x1UL << 7)

/**
 * Volatile Configuration Register (Micron)
 */
#define VCR_XIP (0x1UL << 3)

/**
 * enum spi_flash_protocol - SPI flash command protocol
 */
#define SFLASH_PROTO_INST_SHIFT	16
#define SFLASH_PROTO_INST_MASK	(0xFFUL << 16)
#define SFLASH_PROTO_INST(nbits)					\
	((((unsigned long)(nbits)) << SFLASH_PROTO_INST_SHIFT) &	\
	 SFLASH_PROTO_INST_MASK)

#define SFLASH_PROTO_ADDR_SHIFT	8
#define SFLASH_PROTO_ADDR_MASK	(0xFFUL << 8)
#define SFLASH_PROTO_ADDR(nbits)					\
	((((unsigned long)(nbits)) << SFLASH_PROTO_ADDR_SHIFT) &	\
	 SFLASH_PROTO_ADDR_MASK)

#define SFLASH_PROTO_DATA_SHIFT	0
#define SFLASH_PROTO_DATA_MASK	(0xFFUL << 0)
#define SFLASH_PROTO_DATA(nbits)					\
	((((unsigned long)(nbits)) << SFLASH_PROTO_DATA_SHIFT) &	\
	 SFLASH_PROTO_DATA_MASK)

#define SFLASH_PROTO(inst_nbits, addr_nbits, data_nbits)	\
	(SFLASH_PROTO_INST(inst_nbits) |			\
	 SFLASH_PROTO_ADDR(addr_nbits) |			\
	 SFLASH_PROTO_DATA(data_nbits))

#define SFLASH_CMD_ERASE_MAX	4
#define SFLASH_CMD_ERASE_MASK	0xFULL
#define SFLASH_CMD_ERASE_OFFSET(_cmd_mask, _offset)		\
	((((uint64_t)(_offset)) & ~SFLASH_CMD_ERASE_MASK) |	\
	 (((uint64_t)(_cmd_mask)) & SFLASH_CMD_ERASE_MASK))

/*
 *(Fast) Read capabilities.
 * MUST be ordered by priority: the higher bit position, the higher priority.
 * As a matter of performances, it is relevant to use Octo SPI protocols first,
 * then Quad SPI protocols before Dual SPI protocols, Fast Read and lastly
 * (Slow) Read.
 */
#define SFLASH_HWCAPS_READ_MASK	 (0xFFUL << 0)
#define SFLASH_HWCAPS_READ       (0x1UL << 0)
#define SFLASH_HWCAPS_READ_FAST	 (0x1UL << 1)

#define SFLASH_HWCAPS_READ_DUAL	 (0x7UL << 2)
#define SFLASH_HWCAPS_READ_1_1_2 (0x1UL << 2)
#define SFLASH_HWCAPS_READ_1_2_2 (0x1UL << 3)
#define SFLASH_HWCAPS_READ_2_2_2 (0x1UL << 4)

#define SFLASH_HWCAPS_READ_QUAD	 (0x7UL << 5)
#define SFLASH_HWCAPS_READ_1_1_4 (0x1UL << 5)
#define SFLASH_HWCAPS_READ_1_4_4 (0x1UL << 6)
#define SFLASH_HWCAPS_READ_4_4_4 (0x1UL << 7)

enum spi_flash_protocol {
	SFLASH_PROTO_1_1_1 = SFLASH_PROTO(1, 1, 1),
	SFLASH_PROTO_1_1_2 = SFLASH_PROTO(1, 1, 2),
	SFLASH_PROTO_1_1_4 = SFLASH_PROTO(1, 1, 4),
	SFLASH_PROTO_1_2_2 = SFLASH_PROTO(1, 2, 2),
	SFLASH_PROTO_1_4_4 = SFLASH_PROTO(1, 4, 4),
	SFLASH_PROTO_2_2_2 = SFLASH_PROTO(2, 2, 2),
	SFLASH_PROTO_4_4_4 = SFLASH_PROTO(4, 4, 4),
};

/*
 * Page Program capabilities.
 * MUST be ordered by priority: the higher bit position, the higher priority.
 * Like (Fast) Read capabilities, Octo/Quad SPI protocols are preferred to the
 * legacy SPI 1-1-1 protocol.
 * Note that Dual Page Programs are not supported because there is no existing
 * JEDEC/SFDP standard to define them. Also at this moment no SPI flash memory
 * implements such commands.
 */
#define SFLASH_HWCAPS_PP_MASK	(0xFUL << 16)
#define SFLASH_HWCAPS_PP	(0x1UL << 16)

#define SFLASH_HWCAPS_PP_QUAD	(0x7UL << 17)
#define SFLASH_HWCAPS_PP_1_1_4	(0x1UL << 17)
#define SFLASH_HWCAPS_PP_1_4_4	(0x1UL << 18)
#define SFLASH_HWCAPS_PP_4_4_4	(0x1UL << 19)

#define SFLASH_TYPE_MASK	(0x7UL << 0)
#define SFLASH_TYPE_READ	(0x0UL << 0)
#define SFLASH_TYPE_WRITE	(0x1UL << 0)
#define SFLASH_TYPE_ERASE	(0x2UL << 0)
#define SFLASH_TYPE_READ_REG	(0x3UL << 0)
#define SFLASH_TYPE_WRITE_REG	(0x4UL << 0)

#define SFLASH_FLG_HAS_FSR (0x1UL << 0)

/*----------------------------------------------------------------------------
 *        Exported Typedefs
 *----------------------------------------------------------------------------*/

/**
 * struct spi_flash_command - SPI flash command structure
 *
 * @proto:		The SPI x-y-z protocol.
 * @flags:		The command type and other options/flags.
 * @inst:		Opcode sent to the SPI slave during instr clock cycles.
 * @mode:		Value sent to the SPI slave during mode clock cycles.
 * @num_mode_cycles:	Number of mode clock cycles.
 * @num_wait_states:	Number of wait-state clock cycles.
 * @addr_len:		Number of bytes sent during address clock cycles:
 *			should be 0, 3, or 4.
 * @addr:		Value sent to the SPI slave during address clock cycles.
 * @data_len:		Number of bytes to be sent during data clock cycles.
 * @tx_data:		Data sent to the SPI slave during data clock cycles.
 * @rx_data:		Data read from the SPI slave during data clock cycles.
 */
struct spi_flash_command {
	enum spi_flash_protocol proto;
	uint32_t flags;
	uint8_t inst;
	uint8_t mode;
	uint8_t num_mode_cycles;
	uint8_t num_wait_states;
	uint8_t addr_len;
	size_t addr;
	size_t data_len;
	const void *tx_data;
	void *rx_data;
	uint32_t timeout;
#ifdef CONFIG_HAVE_AESB
	bool use_aesb;
#endif
};

/**
 * struct spi_flash_erase_command - Structure to describe a SPI FLASH erase command
 * @size:		the size of the sector/block erased by the command.
 * @size_shift:		the size shift: if @size is a power of 2 then the shift
 *			is stored in @size_shift, otherwise @size_shift is zero.
 * @size_mask:		the size mask based on @size_shift.
 * @inst:		the SPI command op code to erase the sector/block.
 */
struct spi_flash_erase_command {
	uint32_t size;
	uint32_t size_shift;
	uint32_t size_mask;
	uint8_t	inst;
};

/**
 * struct spi_flash_erase_region - Structure to describe a SPI FLASH erase region
 * @offset:             the offset in the data array of erase region start.
 *                      LSB bits are used as a
 * @cmd_mask            bitmask encoding the erase
 *                      commands supported inside this erase region.
 * @size:               the size of the region in bytes.
 */
struct spi_flash_erase_region {
	uint32_t cmd_mask;
	uint32_t offset;
	uint64_t size;
};

/**
 * struct spi_flash_erase_map - Structure to describe the SPI FLASH erase map
 * @commands:		an array of erase commands shared by all the regions.
 * @uniform_region:	a pre-allocated erase region for SPI FLASH with a uniform
 *			sector size (legacy implementation).
 * @regions:		point to an array describing the boundaries of the erase
 *			regions.
 * @num_regions:	the number of elements in the @regions array.
 */
struct spi_flash_erase_map {
	struct spi_flash_erase_command commands[SFLASH_CMD_ERASE_MAX];
	struct spi_flash_erase_region uniform_region;
	struct spi_flash_erase_region *regions;
	uint32_t num_regions;
};

struct spi_flash;
union spi_flash_priv;
struct spi_flash_parameters;

/**
 * struct spi_ops - Structure to abstract the SPI controller interface.
 * @init:	Initialize the SPI controller.
 * @cleanup:	Uninitialize the SPI controller.
 * @set_freq:	Set the SPI clock frequency.
 * @set_mode:	Set the SPI mode, ie CPHA (clock phase) / CPOL (clock polarity).
 * @exec:	Execute a given SPI flash command.
 */
struct spi_ops {
	int (*init)(union spi_flash_priv* priv);
	int (*cleanup)(union spi_flash_priv* priv);
	int (*set_freq)(union spi_flash_priv* priv, uint32_t freq);
	int (*set_mode)(union spi_flash_priv* priv, uint8_t mode);
	int (*exec)(union spi_flash_priv* priv, const struct spi_flash_command *cmd);
};

union spi_flash_priv {
#ifdef CONFIG_HAVE_QSPI
	struct qspi_priv qspi;
#endif
	struct _bus_dev_cfg spi;
};

/**
 * struct spi_flash_hwcaps - Structure for describing the hardware capabilities
 * supported by the SPI controller (bus master).
 * @mask:		the bitmask listing all the supported hw capabilities
 */
struct spi_flash_hwcaps {
	uint32_t mask;
};

/**
 * struct spi_flash - Structure to describe some SPI flash memory
 * @priv:		The private data.
 * @flags		Runtime flags & options for the current SPI flash.
 * @read_proto:		The SPI protocol for read operations.
 * @write_proto:	The SPI protocol for write operations.
 * @reg_proto:		The SPI protocol for read_reg/write_reg/erase operations.
 * @addr_len:		Number of address bytes.
 * @read_inst:		The (Fast) Read instruction opcode.
 * @write_inst:		The Page Program instruction opcode.
 * @mode:		The value to send during mode clock cycles.
 * @num_mode_cycles:	The number of mode clock cycles.
 * @num_wait_states:	The number of wait state clock cycles.
 * @size:		The total SPI flash size (in bytes).
 * @page_size:		The page size (in bytes).
 * @erase_map:		The erase map of the SPI flash.
 * @ops:		[DRIVER-SPECIFIC] The SPI controller interface.
 * @read:		[FLASH-SPECIFIC] Read data from the SPI flash.
 * @write:		[FLASH-SPECIFIC] Write data into the SPI flash.
 * @erase:		[FLASH-SPECIFIC] Erase data inside the SPI flash.
 */
struct spi_flash {
	union spi_flash_priv priv;
	struct spi_flash_hwcaps hwcaps;

	uint32_t flags;

	enum spi_flash_protocol	read_proto;
	enum spi_flash_protocol	write_proto;
	enum spi_flash_protocol reg_proto;

	uint8_t addr_len;
	uint8_t read_inst;
	uint8_t write_inst;
	uint8_t normal_mode;
	uint8_t xip_mode;
	uint8_t num_mode_cycles;
	uint8_t num_wait_states;
	uint8_t id[SFLASH_MAX_ID_LEN];
	const char *name;

	size_t size;
	size_t page_size;
	struct spi_flash_erase_map erase_map;

	const struct spi_ops *ops;

#ifdef CONFIG_HAVE_AESB
	bool use_aesb;
#endif

	int (*read)(struct spi_flash *, size_t, uint8_t *, size_t);
	int (*write)(struct spi_flash *, size_t, const uint8_t *, size_t);
	int (*erase)(struct spi_flash *, size_t, size_t);
	int (*enable_0_4_4)(struct spi_flash *, bool);
	int (*set_protection)(struct spi_flash *flash, bool protect);
};

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

/**
 * Initialize a 'struct spi_flash_command'.
 *
 * @cmd:		Pointer to the 'struct spi_flash_command' to initialize.
 * @inst:		Instruction opcode.
 * @addr_len:		Number of address bytes.
 * @flags:		The SPI flash command type and other flags.
 */
extern void spi_flash_command_init(struct spi_flash_command *cmd, uint8_t inst, uint8_t addr_len, uint8_t flags);

extern void spi_flash_init_uniform_erase_map(struct spi_flash_erase_map *map, uint32_t cmd_mask, uint64_t flash_size);

extern uint8_t spi_flash_get_mfr(const struct spi_flash *flash);

extern int spi_flash_init(struct spi_flash *flash);

extern int spi_flash_cleanup(struct spi_flash *flash);

extern int spi_flash_set_mode(struct spi_flash *flash, uint8_t mode);

extern int spi_flash_set_freq(struct spi_flash *flash, uint32_t freq);

extern int spi_flash_exec(struct spi_flash *flash, const struct spi_flash_command *cmd);

extern int spi_flash_read(struct spi_flash *flash, size_t from, void *buf, size_t len);

extern int spi_flash_write(struct spi_flash *flash, size_t to, const void *buf, size_t len);

extern int spi_flash_erase(struct spi_flash *flash, size_t offset, size_t len);

extern bool spi_flash_has_uniform_erase(const struct spi_flash *flash);

extern uint32_t spi_flash_get_uniform_erase_map(const struct spi_flash *flash);

extern uint8_t spi_flash_protocol_get_inst_nbits(enum spi_flash_protocol proto);

extern uint8_t spi_flash_protocol_get_addr_nbits(enum spi_flash_protocol proto);

extern uint8_t spi_flash_protocol_get_data_nbits(enum spi_flash_protocol proto);

extern int spi_flash_hwcaps2cmd(uint32_t hwcaps);
extern int spi_flash_read_reg(struct spi_flash *flash, uint8_t inst, uint8_t *buf, size_t len);
extern int spi_flash_write_reg(struct spi_flash *flash, uint8_t inst, const uint8_t *buf, size_t len);
extern int spi_flash_wait_till_ready_timeout(struct spi_flash *flash, unsigned long timeout);

extern int spi_flash_setup(struct spi_flash *flash, const struct spi_flash_parameters *params);

extern int spi_flash_read_sr(struct spi_flash *flash, uint8_t *sr);

extern int spi_flash_write_enable(struct spi_flash *flash);

extern int spi_flash_write_disable(struct spi_flash *flash);

extern int spi_flash_reset(struct spi_flash *flash);

extern int spi_flash_wait_till_ready(struct spi_flash *flash);

#ifdef CONFIG_HAVE_AESB
extern void spi_flash_use_aesb(struct spi_flash* flash, bool enable);
#endif

extern void spi_flash_set_erase_command(struct spi_flash_erase_command *cmd, size_t size, uint8_t inst);

extern uint32_t spi_flash_div_by_erase_size(const struct spi_flash_erase_command *cmd, uint32_t dividend, uint32_t *remainder);

extern int spi_flash_set_protection(struct spi_flash *flash, bool protect);

#endif /* _SPI_FLASH_H */
