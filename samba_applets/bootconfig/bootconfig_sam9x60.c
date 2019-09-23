/* ----------------------------------------------------------------------------
 *         MICROCHIP Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Microchip
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <errno.h>
#include <string.h>

#include "applet.h"
#include "bootconfig.h"
#include "chip.h"
#include "nvm/otp/otpc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

enum bootcfg_index {
	BOOTCFG_BSCR,
	BOOTCFG_BCP_EMUL,
	BOOTCFG_BCP_OTP,
	BOOTCFG_UHCP_EMUL,
	BOOTCFG_UHCP_OTP,
	BOOTCFG_SBCP_EMUL,
	BOOTCFG_SBCP_OTP,
};

enum intf_type {
	TYPE_DISABLED,
	TYPE_QSPI,
	TYPE_SPI,
	TYPE_SDMMC,
	TYPE_NFC,
};

struct boot_intf {
	union {
		struct {
			uint32_t	ioset:4;
			uint32_t	instance:4;
			uint32_t	type:4;
			uint32_t	reserved:20;
		};
		uint32_t		word;
	}		mem_cfg;
	uint32_t	extra;
};

#define MAX_BOOTABLE_INTERF   7

struct bootcfg_packet {
	uint32_t	monitor_disabled;
	uint32_t	pll_disabled;
	uint32_t	reserved[2];
	uint32_t	console_ioset;

	struct boot_intf interface[MAX_BOOTABLE_INTERF];
};

struct sdmmc_extra {
	uint32_t	pin:5;
	uint32_t	pid:2;
	uint32_t	enabled:1;
	uint32_t	magic:8;
	uint32_t	reserved:16;
};

struct user_hwcfg_packet {
	union {
		struct {
			uint32_t	jtagdis:8;
			uint32_t	reserved:24;
		};
		uint32_t		word;
	}	uhc0r;
	union {
		struct {
			uint32_t	urddis:1;
			uint32_t	upgdis:1;
			uint32_t	uhcinvdis:1;
			uint32_t	uhclkdis:1;
			uint32_t	uhcpgdis:1;
			uint32_t	bcinvdis:1;
			uint32_t	bclkdis:1;
			uint32_t	bcpgdis:1;
			uint32_t	sbcinvdis:1;
			uint32_t	sbclkdis:1;
			uint32_t	sbcpgdis:1;
			uint32_t	reserved0:3;
			uint32_t	cinvdis:1;
			uint32_t	clkdis:1;
			uint32_t	cpgdis:1;
			uint32_t	urfdis:1;
			uint32_t	reserved1:14;
		};
		uint32_t		word;
	}	uhc1r;
};

enum otp_key_type {
	OTPKEY_AES_CIPHER = 0,
	OTPKEY_AES_CMAC,

	OTPKEY_MAX_KEYS
};

struct seccfg_packet {
	uint32_t	secure_boot_enabled;
	uint32_t	auth_mode;
	uint32_t	pairing_mode_enabled;
	uint32_t	key_written;

	uint32_t	iv;
	uint32_t	rsa_hash;
	uint32_t	keys[OTPKEY_MAX_KEYS];
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static int prologue(bool is_emulation_enabled, bool *toggle)
{
	if (is_emulation_enabled ^ otp_is_emulation_enabled()) {
		if (otp_emulation_mode(is_emulation_enabled)) {
			trace_error("Cannot %sable EMULATION mode.\r\n",
				    is_emulation_enabled ? "en" : "dis");
			return -EIO;
		}

		*toggle = true;
	} else {
		*toggle = false;
	}

	return 0;
}

static int epilogue(bool is_emulation_enabled, bool toggle, int rc)
{
	/*
	 * Cannot switch back to emulation mode, once the OTP matrix has been
	 * written.
	 */
	if (toggle &&
	    (rc || is_emulation_enabled) &&
	    otp_emulation_mode(!is_emulation_enabled)) {
		trace_error("Cannot %sable EMULATION mode.\r\n",
			    is_emulation_enabled ? "dis" : "en");
		return -EIO;
	}

	return rc;
}

static void print_bscr(uint32_t bsc_cr)
{
	trace_warning_wp("BSCR: 0x%08x -> ", (unsigned)bsc_cr);

	if (bsc_cr)
		trace_warning_wp("EMULATION_ENABLED\r\n");
	else
		trace_warning_wp("EMULATION_DISABLED\r\n");
}

static void print_bcp(bool is_emulation_enabled,
		      const struct bootcfg_packet *bcp)
{
	const char *sep = "";

	trace_warning_wp("BCP (%s): ",
			 is_emulation_enabled ? "EMUL" : "OTP");

	if (bcp->monitor_disabled) {
		trace_warning_wp("%sMONITOR_DISABLED", sep);
		sep = ",";
	}

	if (bcp->pll_disabled) {
		trace_warning_wp("%sPLL_DISABLED", sep);
		sep = ",";
	}

	if (bcp->console_ioset >= 1 && bcp->console_ioset <= 13) {
		trace_warning_wp("%sFLEXCOM%u_USART_IOSET1",
				 sep, (unsigned)(bcp->console_ioset - 1));
		sep = ",";
	} else if (bcp->console_ioset == 0) {
		trace_warning_wp("%sDBGU", sep);
		sep = ",";
	}

	for (int i = 0; i < MAX_BOOTABLE_INTERF; i++) {
		const struct boot_intf *intf = &bcp->interface[i];
		unsigned instance = intf->mem_cfg.instance;
		unsigned ioset = intf->mem_cfg.ioset + 1;

		switch (intf->mem_cfg.type) {
		case TYPE_QSPI:
			trace_warning_wp("%sQSPI%u_IOSET%u",
					 sep, instance, ioset);
			sep = ",";
			if (intf->extra)
				trace_warning_wp("_XIP");
			break;

		case TYPE_SPI:
			trace_warning_wp("%sFLEXCOM%u_SPI_IOSET%u",
					 sep, instance, ioset);
			sep = ",";
			break;

		case TYPE_SDMMC:
			trace_warning_wp("%sSDMMC%u_IOSET%u",
					 sep, instance, ioset);
			sep = ",";
			if (intf->extra) {
				const struct sdmmc_extra *extra = (const struct sdmmc_extra *)&intf->extra;

				if (extra->enabled && extra->magic == 0x96)
					trace_warning_wp("_P%c%u", 'A' + extra->pid, extra->pin);
			}
			break;

		case TYPE_NFC:
			trace_warning_wp("%sNFC_IOSET%u", sep, ioset);
			sep = ",";
			break;

		default:
			continue;
		}
	}

	trace_warning_wp("\r\n");
}

static int read_bcp(bool is_emulation_enabled,
		    struct bootcfg_packet *bcp)
{
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_BCADDR_Msk) >> OTPC_BAR_BCADDR_Pos;

	if (otp_read_packet(hdr_addr, (uint32_t *)bcp, sizeof(*bcp), &packet_len) ||
	    packet_len != sizeof(*bcp)) {
		trace_error("Cannot read Boot Config Packet.\r\n");
		rc = -EIO;
	} else {
		rc = 0;
	}

	return epilogue(is_emulation_enabled, toggle, rc);
}

static int write_bcp(bool is_emulation_enabled,
		     const struct bootcfg_packet *bcp)
{
	struct bootcfg_packet cur_bcp;
	struct otp_new_packet pckt;
	uint16_t hdr_addr;
	bool toggle;
	uint16_t packet_len = 0;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_BCADDR_Msk) >> OTPC_BAR_BCADDR_Pos;

	rc = -EIO;
	if (!otp_read_packet(hdr_addr, (uint32_t *)&cur_bcp, sizeof(cur_bcp), &packet_len) &&
	    packet_len == sizeof(cur_bcp)) {
		if (!memcmp(&cur_bcp, bcp, sizeof(*bcp))) {
			trace_info("Boot Config Packet is already up to date.\r\n");
			rc = 0;
			goto exit;
		}

		if (!otp_can_update_payload(&cur_bcp, bcp, sizeof(cur_bcp)) ||
		    otp_update_payload(hdr_addr, (const uint32_t *)bcp)) {
			trace_error("Cannot update existing Boot Config Packet.\r\n");
			goto exit;
		}
	} else {
		memset(&pckt, 0, sizeof(pckt));
		pckt.type = OTP_PCKT_BOOT_CONFIGURATION;
		pckt.size = sizeof(*bcp);
		if (otp_write_packet(&pckt, (const uint32_t *)bcp, &hdr_addr, &packet_len) ||
		    packet_len != sizeof(*bcp)) {
			trace_error("Cannot write new Boot Config Packet.\r\n");
			goto exit;
		}
	}

	if (otp_read_packet(hdr_addr, (uint32_t *)&cur_bcp, sizeof(cur_bcp), &packet_len) ||
	    packet_len != sizeof(cur_bcp) ||
	    memcmp(bcp, &cur_bcp, sizeof(cur_bcp))) {
		trace_error("Cannot read-back Boot Config Packet.\r\n");
		goto exit;
	}

	rc = 0;
exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int invalidate_bcp(bool is_emulation_enabled)
{
	struct bootcfg_packet bcp;
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_BCADDR_Msk) >> OTPC_BAR_BCADDR_Pos;

	rc = -EIO;
	if (otp_read_packet(hdr_addr, (uint32_t *)&bcp, sizeof(bcp), &packet_len) ||
	    packet_len != sizeof(bcp)) {
		trace_error("Cannot read Boot Config Packet.\r\n");
		goto exit;
	}

	if (otp_invalidate_packet(hdr_addr))
		trace_error("Cannot invalidate Boot Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int lock_bcp(bool is_emulation_enabled)
{
	struct bootcfg_packet bcp;
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_BCADDR_Msk) >> OTPC_BAR_BCADDR_Pos;

	rc = -EIO;
	if (otp_read_packet(hdr_addr, (uint32_t *)&bcp, sizeof(bcp), &packet_len) ||
	    packet_len != sizeof(bcp)) {
		trace_error("Cannot read Boot Config Packet.\r\n");
		goto exit;
	}

	if (otp_lock_packet(hdr_addr))
		trace_error("Cannot lock Boot Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static void print_uhcp(bool is_emulation_enabled,
		       const struct user_hwcfg_packet *uhcp)
{
	trace_warning_wp("UHCP (%s): [0x%08x, 0x%08x]\r\n",
			 is_emulation_enabled ? "EMUL" : "OTP",
			 (unsigned)uhcp->uhc0r.word, (unsigned)uhcp->uhc1r.word);
}

static int read_uhcp(bool is_emulation_enabled,
		     struct user_hwcfg_packet *uhcp)
{
	uhcp->uhc0r.word = OTPC->OTPC_UHC0R;
	uhcp->uhc1r.word = OTPC->OTPC_UHC1R;
	return 0;
}

static bool get_uhcp(uint16_t *hdr_addr)
{
	struct otp_packet_header match, hdr;
	uint32_t filters;

	filters = OTP_FILTER_TYPE | OTP_FILTER_SIZE | OTP_FILTER_INVALID;
	memset(&match, 0, sizeof(match));
	match.type = OTP_PCKT_HARDWARE_CONFIGURATION;
	match.size = sizeof(struct user_hwcfg_packet);
	match.is_invalid = false;

	*hdr_addr = 0;
	return !otp_get_latest_matching_packet(filters, &match, &hdr, hdr_addr);
}

static int write_uhcp(bool is_emulation_enabled,
		      const struct user_hwcfg_packet *uhcp)
{
	struct user_hwcfg_packet cur_uhcp;
	struct otp_new_packet pckt;
	uint16_t hdr_addr;
	bool toggle;
	uint16_t packet_len = 0;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	rc = -EIO;
	if (get_uhcp(&hdr_addr) &&
	    !otp_read_packet(hdr_addr, (uint32_t *)&cur_uhcp, sizeof(cur_uhcp), &packet_len) &&
	    packet_len == sizeof(cur_uhcp)) {
		if (!memcmp(&cur_uhcp, uhcp, sizeof(*uhcp))) {
			trace_info("User Hardware Config Packet is already up to date.\r\n");
			rc = 0;
			goto exit;
		}

		if (!otp_can_update_payload(&cur_uhcp, uhcp, sizeof(cur_uhcp)) ||
		    otp_update_payload(hdr_addr, (const uint32_t *)uhcp)) {
			trace_error("Cannot update existing User Hardware Config Packet.\r\n");
			goto exit;
		}
	} else {
		memset(&pckt, 0, sizeof(pckt));
		pckt.type = OTP_PCKT_HARDWARE_CONFIGURATION;
		pckt.size = sizeof(*uhcp);
		if (otp_write_packet(&pckt, (const uint32_t *)uhcp, &hdr_addr, &packet_len) ||
		    packet_len != sizeof(*uhcp)) {
			trace_error("Cannot write new User Hardware Config Packet.\r\n");
			goto exit;
		}
	}

	if (otp_read_packet(hdr_addr, (uint32_t *)&cur_uhcp, sizeof(cur_uhcp), &packet_len) ||
	    packet_len != sizeof(cur_uhcp) ||
	    memcmp(uhcp, &cur_uhcp, sizeof(cur_uhcp))) {
		trace_error("Cannot read-back User Hardware Config Packet.\r\n");
		goto exit;
	}

	rc = 0;
exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int invalidate_uhcp(bool is_emulation_enabled)
{
	uint16_t hdr_addr;
	struct user_hwcfg_packet uhcp;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	rc = -EIO;
	if (!get_uhcp(&hdr_addr) ||
	    otp_read_packet(hdr_addr, (uint32_t *)&uhcp, sizeof(uhcp), &packet_len) ||
	    packet_len != sizeof(uhcp)) {
		trace_error("Cannot read User Hardware Config Packet.\r\n");
		goto exit;
	}

	if (otp_invalidate_packet(hdr_addr))
		trace_error("Cannot invalidate User Hardware Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int lock_uhcp(bool is_emulation_enabled)
{
	uint16_t hdr_addr;
	struct user_hwcfg_packet uhcp;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	rc = -EIO;
	if (!get_uhcp(&hdr_addr) ||
	    otp_read_packet(hdr_addr, (uint32_t *)&uhcp, sizeof(uhcp), &packet_len) ||
	    packet_len != sizeof(uhcp)) {
		trace_error("Cannot read User Hardware Config Packet.\r\n");
		goto exit;
	}

	if (otp_lock_packet(hdr_addr))
		trace_error("Cannot lock User Hardware Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static void print_sbcp(bool is_emulation_enabled,
		       const struct seccfg_packet *sbcp)
{
	const char *sep = "";

	trace_warning_wp("SBCP (%s): ",
			 is_emulation_enabled ? "EMUL" : "OTP");

	if (sbcp->secure_boot_enabled) {
		trace_warning_wp("%sSECURE_BOOT_ENABLED", sep);
		sep = ",";
	}

	if (sbcp->auth_mode) {
		trace_warning_wp("%sRSA_SIGNATURE", sep);
		sep = ",";
	}

	if (sbcp->pairing_mode_enabled) {
		trace_warning_wp("%sPAIRING_MODE_ENABLED", sep);
		sep = ",";
	}

	if (sbcp->key_written) {
		trace_warning_wp("%sCUSTOMER_KEY_WRITTEN", sep);
		sep = ",";
	}

	trace_warning_wp("\r\n");
}

static int read_sbcp(bool is_emulation_enabled,
		     struct seccfg_packet *sbcp)
{
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_SBCADDR_Msk) >> OTPC_BAR_SBCADDR_Pos;

	if (otp_read_packet(hdr_addr, (uint32_t *)sbcp, sizeof(*sbcp), &packet_len) ||
	    packet_len != sizeof(*sbcp)) {
		trace_error("Cannot read Secure Boot Config Packet.\r\n");
		rc = -EIO;
	} else {
		rc = 0;
	}

	return epilogue(is_emulation_enabled, toggle, rc);
}

static int create_sbcp(bool is_emulation_enabled)
{
	struct seccfg_packet old_sec, sec;
	struct otp_new_packet pckt;
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_SBCADDR_Msk) >> OTPC_BAR_SBCADDR_Pos;

	memset(&sec, 0, sizeof(sec));
	sec.secure_boot_enabled = 1;

	if (!otp_read_packet(hdr_addr, (uint32_t *)&old_sec, sizeof(old_sec), &packet_len) &&
	    packet_len == sizeof(sec)) {
		if (memcmp(&old_sec, &sec, sizeof(sec))) {
			trace_error("A non-empty Secure Boot Config Packet is already existing.\r\n");
			rc = -EIO;
			goto exit;
		}

		trace_info("An empty Secure Boot Config Packet has already been created.\r\n");
		rc = 0;
		goto exit;
	}

	memset(&pckt, 0, sizeof(pckt));
	pckt.type = OTP_PCKT_SECURE_BOOT_CONFIGURATION;
	pckt.size = sizeof(sec);
	if (otp_write_packet(&pckt, (const uint32_t *)&sec, &hdr_addr, &packet_len) ||
	    packet_len != sizeof(sec)) {
		trace_error("Cannot create new Secure Boot Config Packet.\r\n");
		rc = -EIO;
		goto exit;
	}

	if (otp_read_packet(hdr_addr, (uint32_t *)&old_sec, sizeof(old_sec), &packet_len) ||
	    packet_len != sizeof(old_sec) ||
	    memcmp(&sec, &old_sec, sizeof(old_sec))) {
		trace_error("Cannot read-back Secure Boot Config Packet.\r\n");
		rc = -EIO;
		goto exit;
	}

	rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int invalidate_sbcp(bool is_emulation_enabled)
{
	struct seccfg_packet sec;
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_SBCADDR_Msk) >> OTPC_BAR_SBCADDR_Pos;

	rc = -EIO;
	if (otp_read_packet(hdr_addr, (uint32_t *)&sec, sizeof(sec), &packet_len) ||
	    packet_len != sizeof(sec)) {
		trace_error("Cannot read Secure Boot Config Packet.\r\n");
		goto exit;
	}

	if (otp_invalidate_packet(hdr_addr))
		trace_error("Cannot invalidate Secure Boot Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

static int lock_sbcp(bool is_emulation_enabled)
{
	struct seccfg_packet sec;
	uint16_t hdr_addr;
	uint16_t packet_len = 0;
	bool toggle;
	int rc;

	if ((rc = prologue(is_emulation_enabled, &toggle)) < 0)
		return rc;

	hdr_addr = (OTPC->OTPC_BAR & OTPC_BAR_SBCADDR_Msk) >> OTPC_BAR_SBCADDR_Pos;

	rc = -EIO;
	if (otp_read_packet(hdr_addr, (uint32_t *)&sec, sizeof(sec), &packet_len) ||
	    packet_len != sizeof(sec)) {
		trace_error("Cannot read Secure Boot Config Packet.\r\n");
		goto exit;
	}

	if (!sec.key_written) {
		trace_error("The Customer Key has not been written yet.\r\n");
		rc = -EINVAL;
		goto exit;
	}

	if (otp_lock_packet(hdr_addr))
		trace_error("Cannot lock Secure Boot Config Packet.\r\n");
	else
		rc = 0;

exit:
	return epilogue(is_emulation_enabled, toggle, rc);
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

int bootcfg_initialize(void)
{
	return otp_init();
}

int bootcfg_print(uint32_t index, uint32_t value)
{
	switch (index) {
	case BOOTCFG_BSCR:
		print_bscr(value);
		break;
	case BOOTCFG_BCP_EMUL:
	case BOOTCFG_BCP_OTP:
		print_bcp(index == BOOTCFG_BCP_EMUL,
			  (const struct bootcfg_packet *)applet_buffer);
		break;
	case BOOTCFG_UHCP_EMUL:
	case BOOTCFG_UHCP_OTP:
		print_uhcp(index == BOOTCFG_UHCP_EMUL,
			   (const struct user_hwcfg_packet *)applet_buffer);
		break;
	case BOOTCFG_SBCP_EMUL:
	case BOOTCFG_SBCP_OTP:
		print_sbcp(index == BOOTCFG_SBCP_EMUL,
			   (const struct seccfg_packet *)applet_buffer);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_read(uint32_t index, uint32_t *value)
{
	switch (index) {
	case BOOTCFG_BSCR:
		*value = BSC->BSC_CR;
		break;
	case BOOTCFG_BCP_EMUL:
	case BOOTCFG_BCP_OTP:
		*value = 0;
		return read_bcp(index == BOOTCFG_BCP_EMUL,
				(struct bootcfg_packet *)applet_buffer);
	case BOOTCFG_UHCP_EMUL:
	case BOOTCFG_UHCP_OTP:
		*value = 0;
		return read_uhcp(index == BOOTCFG_UHCP_EMUL,
				 (struct user_hwcfg_packet *)applet_buffer);
	case BOOTCFG_SBCP_EMUL:
	case BOOTCFG_SBCP_OTP:
		*value = 0;
		return read_sbcp(index == BOOTCFG_SBCP_EMUL,
				 (struct seccfg_packet *)applet_buffer);
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_write(uint32_t index, uint32_t value)
{
	switch (index) {
	case BOOTCFG_BSCR:
		BSC->BSC_CR = ((!!value) & ~BSC_CR_WPKEY_Msk) | BSC_CR_WPKEY_PASSWD;
		break;
	case BOOTCFG_BCP_EMUL:
	case BOOTCFG_BCP_OTP:
		return write_bcp(index == BOOTCFG_BCP_EMUL,
				 (const struct bootcfg_packet *)applet_buffer);
	case BOOTCFG_UHCP_EMUL:
	case BOOTCFG_UHCP_OTP:
		return write_uhcp(index == BOOTCFG_UHCP_EMUL,
				  (const struct user_hwcfg_packet *)applet_buffer);
	case BOOTCFG_SBCP_EMUL:
	case BOOTCFG_SBCP_OTP:
		return create_sbcp(index == BOOTCFG_SBCP_EMUL);
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_invalidate(uint32_t index)
{
	switch (index) {
	case BOOTCFG_BCP_EMUL:
	case BOOTCFG_BCP_OTP:
		return invalidate_bcp(index == BOOTCFG_BCP_EMUL);
	case BOOTCFG_UHCP_EMUL:
	case BOOTCFG_UHCP_OTP:
		return invalidate_uhcp(index == BOOTCFG_UHCP_EMUL);
	case BOOTCFG_SBCP_EMUL:
	case BOOTCFG_SBCP_OTP:
		return invalidate_sbcp(index == BOOTCFG_SBCP_EMUL);
	default:
		break;
	}

	return -EINVAL;
}

int bootcfg_lock(uint32_t index)
{
	switch (index) {
	case BOOTCFG_BCP_EMUL:
	case BOOTCFG_BCP_OTP:
		return lock_bcp(index == BOOTCFG_BCP_EMUL);
	case BOOTCFG_UHCP_EMUL:
	case BOOTCFG_UHCP_OTP:
		return lock_uhcp(index == BOOTCFG_UHCP_EMUL);
	case BOOTCFG_SBCP_EMUL:
	case BOOTCFG_SBCP_OTP:
		return lock_sbcp(index == BOOTCFG_SBCP_EMUL);
	default:
		break;
	}

	return -EINVAL;
}

int bootcfg_refresh(uint32_t index)
{
	bool is_emulation_enabled = (index != 0);
	uint8_t rc;

	rc = otp_emulation_mode(is_emulation_enabled);
	if (rc) {
		switch (rc) {
		case OTPC_CANNOT_REFRESH:
			trace_error("Cannot refresh.\r\n");
			break;
		case OTPC_ERROR_CANNOT_ACTIVATE_EMULATION:
			trace_error("Cannot %sable EMULATION mode.\r\n",
				    is_emulation_enabled ? "en" : "dis");
			break;
		default:
			trace_error("Unknown error.\r\n");
			break;
		}
		return -EIO;
	}

	return 0;
}
