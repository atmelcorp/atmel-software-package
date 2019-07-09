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
 */

/*----------------------------------------------------------------------------
 *        HEADERS
 *----------------------------------------------------------------------------*/

#include <errno.h>

#include "board.h"
#include "nvm/spi-nor/spi-nor.h"
#include "peripherals/pmc.h"
#include "string.h"
#include "spi/qspi.h"
#include "spi/spid.h"
#include "timer.h"
#include "trace.h"
#ifdef CONFIG_HAVE_QSPI_DMA
#include "barriers.h"
#include "dma/dma.h"
#include "mm/cache.h"
#endif

/*----------------------------------------------------------------------------
 *        CONSTANTS
 *----------------------------------------------------------------------------*/

//#define QSPI_VERBOSE_DEBUG

/*----------------------------------------------------------------------------
 *        LOCAL FUNCTIONS
 *----------------------------------------------------------------------------*/

static void * qspi_memcpy(union spi_flash_priv* priv, uint8_t *dst, const uint8_t *src, int count, bool use_dma)
{
#ifdef CONFIG_HAVE_QSPI_DMA
	if (use_dma) {
		uint32_t rc;
		struct _dma_transfer_cfg cfg = {
			.daddr = (void *)dst,
			.saddr = (void *)src,
			.len = count,
		};
		static struct _dma_cfg dma_cfg = {
			.incr_saddr = true,
			.incr_daddr = true,
			.data_width = DMA_DATA_WIDTH_BYTE,
			.chunk_size = DMA_CHUNK_SIZE_1,
			.loop = false,
		};
		dma_configure_transfer(priv->qspi.dma_ch, &dma_cfg, &cfg, 1);
		rc = dma_start_transfer(priv->qspi.dma_ch);
		if (rc != 0)
			trace_fatal("Couldn't start xDMA transfer\n\r");
		while (!dma_is_transfer_done(priv->qspi.dma_ch))
			dma_poll();
		dma_reset_channel(priv->qspi.dma_ch);
		dsb();

		return dst;
	}
#endif
	while (count--) {
		*dst++ = *src;
		src++;
	}
	return 0;
}

static int qspi_set_freq(union spi_flash_priv* priv, uint32_t clock)
{
	Qspi* qspi = priv->qspi.addr;
	uint32_t scbr;
	uint32_t reg;

	if (clock == 0) {
		scbr = 0;
	} else {
		uint32_t mck = pmc_get_peripheral_clock(get_qspi_id_from_addr(qspi));
		scbr = (mck + clock - 1) / (clock);
		if (scbr >= 1)
			scbr--;
	}

	reg = qspi->QSPI_SCR;
	reg = (reg & ~QSPI_SCR_SCBR_Msk) | QSPI_SCR_SCBR(scbr);
	qspi->QSPI_SCR = reg;

	return 0;
}

static int qspi_set_mode(union spi_flash_priv* priv, uint8_t mode)
{
	Qspi* qspi = priv->qspi.addr;
	uint32_t reg, val, msk;

	reg = qspi->QSPI_SCR;

	msk = (QSPI_SCR_CPHA | QSPI_SCR_CPOL);
	switch (mode) {
	case SPID_MODE_0:
		val = 0;
		break;

	case SPID_MODE_1:
		val = QSPI_SCR_CPHA;
		break;

	case SPID_MODE_2:
		val = QSPI_SCR_CPOL;
		break;

	case SPID_MODE_3:
		val = (QSPI_SCR_CPOL | QSPI_SCR_CPHA);
		break;

	default:
		return -1;
	}

	if ((reg & msk) != val) {
		reg = (reg & ~msk) | val;
		qspi->QSPI_SCR = reg;
	}

	return 0;
}

static int qspi_init(union spi_flash_priv* priv)
{
	Qspi* qspi = priv->qspi.addr;

	if (pmc_has_system_clock(PMC_SYSTEM_CLOCK_QSPI))
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_QSPI);
	pmc_configure_peripheral(get_qspi_id_from_addr(qspi), NULL, true);

	/* Disable write protection */
	qspi->QSPI_WPMR = QSPI_WPMR_WPKEY_PASSWD;

	qspi->QSPI_CR = QSPI_CR_QSPIDIS;
	qspi->QSPI_CR = QSPI_CR_SWRST;

	qspi->QSPI_MR = QSPI_MR_SMM_MEMORY;
	qspi->QSPI_SCR = 0;

	qspi->QSPI_CR = QSPI_CR_QSPIEN;

#ifdef CONFIG_HAVE_QSPI_DMA
	priv->qspi.dma_ch = dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
	if (!priv->qspi.dma_ch)
		trace_fatal("Couldn't allocate XDMA channel\n\r");
#endif

	return 0;
}

static int qspi_cleanup(union spi_flash_priv* priv)
{
	Qspi* qspi = priv->qspi.addr;

	qspi->QSPI_CR = QSPI_CR_QSPIDIS;
	qspi->QSPI_CR = QSPI_CR_SWRST;

	return 0;
}

static int qspi_init_ifr(const struct spi_flash_command *cmd, uint32_t *ifr)
{
	*ifr = 0;

#ifdef QSPI_IFR_TFRTYP_TRSFR_REGISTER
	switch (cmd->flags & SFLASH_TYPE_MASK) {
	case SFLASH_TYPE_READ_REG:
		*ifr |= QSPI_IFR_APBTFRTYP_READ | QSPI_IFR_TFRTYP_TRSFR_REGISTER;
		break;
	case SFLASH_TYPE_READ:
		*ifr |= QSPI_IFR_APBTFRTYP_READ | QSPI_IFR_TFRTYP_TRSFR_MEMORY;
		break;
	case SFLASH_TYPE_WRITE_REG:
	case SFLASH_TYPE_ERASE:
		*ifr |= QSPI_IFR_APBTFRTYP_WRITE | QSPI_IFR_TFRTYP_TRSFR_REGISTER;
		break;
	case SFLASH_TYPE_WRITE:
		*ifr |= QSPI_IFR_APBTFRTYP_WRITE | QSPI_IFR_TFRTYP_TRSFR_MEMORY;
		break;
	default:
		return -1;
	}
#else
	switch (cmd->flags & SFLASH_TYPE_MASK) {
	case SFLASH_TYPE_READ:
		*ifr |= QSPI_IFR_TFRTYP_TRSFR_READ_MEMORY;
		break;

	case SFLASH_TYPE_WRITE:
		*ifr |= QSPI_IFR_TFRTYP_TRSFR_WRITE_MEMORY;
		break;

	case SFLASH_TYPE_READ_REG:
		*ifr |= QSPI_IFR_TFRTYP_TRSFR_READ;
		break;

	case SFLASH_TYPE_WRITE_REG:
	case SFLASH_TYPE_ERASE:
		*ifr |= QSPI_IFR_TFRTYP_TRSFR_WRITE;
		break;

	default:
		return -1;
	}
#endif

	switch (cmd->proto) {
	case SFLASH_PROTO_1_1_1:
		*ifr |= QSPI_IFR_WIDTH_SINGLE_BIT_SPI;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 1-1-1 ");
#endif
		break;

	case SFLASH_PROTO_1_1_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_OUTPUT;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 1-1-2 ");
#endif
		break;

	case SFLASH_PROTO_1_2_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_IO;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 1-2-2 ");
#endif
		break;

	case SFLASH_PROTO_2_2_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_CMD;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 2-2-2 ");
#endif
		break;

	case SFLASH_PROTO_1_1_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_OUTPUT;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 1-1-4 ");
#endif
		break;

	case SFLASH_PROTO_1_4_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_IO;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 1-4-4 ");
#endif
		break;

	case SFLASH_PROTO_4_4_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_CMD;
#ifdef QSPI_VERBOSE_DEBUG
		printf("SPI 4-4-4 ");
#endif
		break;

	default:
		return -1;
	}

	return 0;
}

static int qspi_exec(union spi_flash_priv* priv, const struct spi_flash_command *cmd)
{
	Qspi* qspi = priv->qspi.addr;
	uint32_t iar, icr, ifr;
	uint32_t offset;
	uint8_t *ptr;
	bool use_dma = false;
	bool enable_data =
		(((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ ) ||
		 ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE ) ||
		 ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ_REG ) ||
		 (((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE_REG ) &&
		  (cmd->data_len != 0))) ? true : false;
#ifdef QSPI_RICR_RDINST
	bool icr_write = false;
#endif

	iar = 0;
	icr = 0;

	/* Init ifr. */
	if (qspi_init_ifr(cmd, &ifr))
		return -1;

	/* Compute instruction parameters. */
#ifdef QSPI_RICR_RDINST
	if ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_ERASE
	    || (cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE_REG
	    || (cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE) {
		icr_write = true;
		icr |= QSPI_WICR_WRINST(cmd->inst);
	} else {
		icr |= QSPI_RICR_RDINST(cmd->inst);
	}
#else
	icr |= QSPI_ICR_INST(cmd->inst);
#endif
	ifr |= QSPI_IFR_INSTEN;

	/* Compute address parameters. */
	switch (cmd->addr_len) {
	case 4:
		ifr |= QSPI_IFR_ADDRL_32_BIT;
		/* fall through the 24bit (3 byte) address case */
	case 3:
		iar = cmd->data_len ? 0 : QSPI_IAR_ADDR(cmd->addr);
		ifr |= QSPI_IFR_ADDREN;
		offset = cmd->addr;
		break;
	case 0:
		offset = 0;
		break;
	default:
		return -1;
	}

	/* Compute option parameters. */
	if (cmd->num_mode_cycles) {
		uint32_t mode_cycle_bits, mode_bits;

#ifdef QSPI_RICR_RDINST
		if (icr_write)
			icr |= QSPI_WICR_WROPT(cmd->mode);
		else
			icr |= QSPI_RICR_RDOPT(cmd->mode);
#else
		icr |= QSPI_ICR_OPT(cmd->mode);
#endif
		ifr |= QSPI_IFR_OPTEN;

		switch (ifr & QSPI_IFR_WIDTH_Msk) {
		case QSPI_IFR_WIDTH_SINGLE_BIT_SPI:
		case QSPI_IFR_WIDTH_DUAL_OUTPUT:
		case QSPI_IFR_WIDTH_QUAD_OUTPUT:
			mode_cycle_bits = 1;
			break;
		case QSPI_IFR_WIDTH_DUAL_IO:
		case QSPI_IFR_WIDTH_DUAL_CMD:
			mode_cycle_bits = 2;
			break;
		case QSPI_IFR_WIDTH_QUAD_IO:
		case QSPI_IFR_WIDTH_QUAD_CMD:
			mode_cycle_bits = 4;
			break;
		default:
			return -1;
		}

		mode_bits = cmd->num_mode_cycles * mode_cycle_bits;
		switch (mode_bits) {
		case 1:
			ifr |= QSPI_IFR_OPTL_OPTION_1BIT;
			break;

		case 2:
			ifr |= QSPI_IFR_OPTL_OPTION_2BIT;
			break;

		case 4:
			ifr |= QSPI_IFR_OPTL_OPTION_4BIT;
			break;

		case 8:
			ifr |= QSPI_IFR_OPTL_OPTION_8BIT;
			break;

		default:
			return -1;
		}
	}

	/* Set the number of dummy cycles. */
	if (cmd->num_wait_states)
		ifr |= QSPI_IFR_NBDUM(cmd->num_wait_states);

	/* Set data enable. */
	if (enable_data) {
		ifr |= QSPI_IFR_DATAEN;

		/* Special case for Continuous Read Mode. */
		if (!cmd->tx_data && !cmd->rx_data)
			ifr |= QSPI_IFR_CRM;
	}

	/* Clear pending interrupts. */
	(void)qspi->QSPI_SR;

#ifdef QSPI_VERBOSE_DEBUG
	{
		int len;

		if (cmd->inst)
			printf("opcode=%02Xh ", cmd->inst);

		if (cmd->addr_len)
			printf("address=0x%08X (%d-bytes) ", (unsigned int)cmd->addr, cmd->addr_len);

		if (cmd->num_mode_cycles)
			printf("mode=%u (%02Xh) ", cmd->num_mode_cycles, cmd->mode);

		if (cmd->num_wait_states)
			printf("dummy=%u ", cmd->num_wait_states);

		len = cmd->data_len;
		if (len > 4)
			len = 4;
		if (len) {
			if (cmd->rx_data)
				goto next;

			if (cmd->tx_data) {
				int i;
				printf("TX (%u bytes): ", (unsigned int)cmd->data_len);
				for (i = 0; i < len; i++)
					printf("0x%02X ", ((uint8_t *)cmd->tx_data)[i]);
			}

			if (len != cmd->data_len)
				printf("... ");
		}

		printf("\r\n");
	}
next:
#endif /* QSPI_VERBOSE_DEBUG */


	/* Set QSPI Instruction Frame registers. */
	qspi->QSPI_IAR = iar;
#ifdef QSPI_RICR_RDINST
	if (icr_write)
		qspi->QSPI_WICR = icr;
	else
		qspi->QSPI_RICR = icr;
#else
	qspi->QSPI_ICR = icr;
#endif
	qspi->QSPI_IFR = ifr;

	/* Skip to the final steps if there is no data. */
	if (!enable_data)
		goto no_data;

	/* Dummy read of QSPI_IFR to synchronize APB and AHB accesses. */
	(void)qspi->QSPI_IFR;

#ifdef CONFIG_HAVE_QSPI_DMA
	if ((((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE) &&
	     IS_CACHE_ALIGNED(cmd->tx_data) &&
	     IS_CACHE_ALIGNED(cmd->data_len)) ||
	    (((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ) &&
	     IS_CACHE_ALIGNED(cmd->rx_data) &&
	     IS_CACHE_ALIGNED(cmd->data_len)))
		use_dma = true;
#endif

	/* Stop here for Continuous Read. */
	if (cmd->tx_data) {
		/* Write data */
#ifdef CONFIG_HAVE_AESB
		if (cmd->use_aesb)
			ptr = priv->qspi.mem_aesb;
		else
#endif
			ptr = priv->qspi.mem;

#ifdef CONFIG_HAVE_QSPI_DMA
		if (use_dma)
			cache_clean_region(cmd->tx_data, cmd->data_len);
#endif
		qspi_memcpy(priv, ptr + offset, cmd->tx_data, cmd->data_len, use_dma);
	} else if (cmd->rx_data) {
		/* Read data */
#ifdef CONFIG_HAVE_AESB
		if (cmd->use_aesb)
			ptr = priv->qspi.mem_aesb;
		else
#endif
			ptr = priv->qspi.mem;

		qspi_memcpy(priv, cmd->rx_data, ptr + offset, cmd->data_len, use_dma);
#ifdef CONFIG_HAVE_QSPI_DMA
		if (use_dma)
			cache_invalidate_region(cmd->rx_data, cmd->data_len);
#endif
	} else {
		/* Stop here for continuous read */
		return 0;
	}

	/* Release the chip-select. */
	qspi->QSPI_CR = QSPI_CR_LASTXFER;

no_data:
	{
		/* Wait for INSTRuction End */
		struct _timeout timeout;
		timer_start_timeout(&timeout, cmd->timeout);
		while (!(qspi->QSPI_SR & QSPI_SR_INSTRE)) {
			if (timer_timeout_reached(&timeout)) {
				trace_debug("qspi_exec timeout reached\r\n");
				return -ETIMEDOUT;
			}
		}
	}

#ifdef QSPI_VERBOSE_DEBUG
	{
		uint32_t i, len;

		len = cmd->data_len;
		if (len > 4)
			len = 4;
		if (len && cmd->rx_data) {
			printf("RX (%u bytes): ", (unsigned int)cmd->data_len);
			for (i = 0; i < len; i++)
				printf("0x%02X ", ((uint8_t *)cmd->rx_data)[i]);

			if (len != cmd->data_len)
				printf("... ");

			printf("\r\n");
		}
	}
#endif /* QSPI_VERBOSE_DEBUG */

	return 0;
}

static const struct spi_ops qspi_ops = {
	.init		= qspi_init,
	.cleanup	= qspi_cleanup,
	.set_freq	= qspi_set_freq,
	.set_mode	= qspi_set_mode,
	.exec		= qspi_exec,
};

/*----------------------------------------------------------------------------
 *        EXPORTED FUNCTIONS
 *----------------------------------------------------------------------------*/

void qspi_configure(struct spi_flash *flash, const struct spi_flash_cfg *cfg)
{
	flash->priv.qspi.addr = cfg->qspi.addr;
	flash->priv.qspi.mem = get_qspi_mem_from_addr(cfg->qspi.addr);
#ifdef CONFIG_HAVE_AESB
	flash->priv.qspi.mem_aesb = get_qspi_aesb_mem_from_addr(cfg->qspi.addr);
#endif

	flash->hwcaps.mask = (SFLASH_HWCAPS_READ_MASK | SFLASH_HWCAPS_PP_MASK);

	flash->ops = &qspi_ops;
}

int qspi_xip(struct spi_flash *flash, void **mem)
{
	int ret;

	if (flash->enable_0_4_4) {
		ret = flash->enable_0_4_4(flash, true);
		if (ret)
			return ret;
	}

	*mem = flash->priv.qspi.mem;
	return spi_flash_read(flash, 0, NULL, 0);
}
