/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 *  \page gmac GMAC Example
 *
 *  \section Purpose
 *
 *  This example uses the Gigabit Ethernet MAC (GMAC) and the on-board Ethernet
 *  transceiver available on Atmel SAMA5D4-EK or SAMA5D4-XULT. It enables the device to
 *  respond to a ping command sent by a host computer.
 *
 *  \section Requirements
 *
 *  - SAMA5D4x microcontrollers with GMAC feature.
 *  - On-board ethernet interface.
 *
 *  \section Description
 *
 *  Upon startup, the program will configure the GMAC with a default IP and
 *  MAC address and then ask the transceiver to auto-negotiate the best mode
 *  of operation. Once this is done, it will start to monitor incoming packets
 *  and processing them whenever appropriate.
 *
 *  The basic will only answer to two kinds of packets:
 *
 *  - It will reply to ARP requests with its MAC address,
 *  - and to ICMP ECHO request so the device can be PING'ed.
 *
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Connect an Ethernet cable between the evaluation board and the network.
 *      The board may be connected directly to a computer; in this case,
 *      make sure to use a cross/twisted wired cable such as the one provided
 *      with the board.
 *  -# Start the application. It will display the following message on the DBGU:
 *     \code
 *      -- GMAC Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      MAC 3a 1f 34 08 54 54
 *      IP  192, 168, 1, 3
 *     \endcode
 *  -# The program will then auto-negotiate the mode of operation and start
 *     receiving packets, displaying feedback on the DBGU. To display additional
 *     information, press any key in the terminal application.
 *  \note
 *  Make sure the IP adress of the device(the board) and the computer are in the same network.
 *
 *  \section References
 *  - gmac/main.c
 *  - gmacb.h
 *  - gmacd.h
 *  - gmac.h
 */

/** \file
 *
 *  This file contains all the specific code for the gmac example.
 *
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include <board.h>
#include <string.h>

#include "core/pio.h"
#include "core/wdt.h"
#include "core/aic.h"
#include "core/pmc.h"

#include "net/gmacd.h"
#include "net/gmacb.h"

#include "mini_ip.h"

#include <stdio.h>

/*---------------------------------------------------------------------------
 *         Local Define
 *---------------------------------------------------------------------------*/

/** Number of buffer for RX */
#define RX_BUFFERS  16
/** Number of buffer for TX */
#define TX_BUFFERS  32

/** GMAC packet processing offset */
#define GMAC_RCV_OFFSET     0

#define GMAC_CAF_DISABLE  0
#define GMAC_CAF_ENABLE   1
#define GMAC_NBC_DISABLE  0
#define GMAC_NBC_ENABLE   1

/** SAMA5D4-EK or SAMA5D4-XULT board sends out MAX_ARP_REQUEST ARP request and wants to get at least MIN_ARP_REPLY reply */
#define GMAX_ARP_REQUEST    100
#define GMIN_ARP_REPLY      90

/** Try to get link */
#define GMAX_TRY_LINK   500

/*---------------------------------------------------------------------------
 *         Local variables
 *---------------------------------------------------------------------------*/

/** The PINs for GMAC */
static const struct _pin gmacPins[] = { BOARD_GMAC_RUN_PINS0 };

/** The MAC address used for demo */
static uint8_t GMacAddress[6] = { 0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54 };

/** The IP address used for demo (ping ...) */
static uint8_t GIpAddress[4] = { 192, 168, 1, 3 };
static uint8_t GDesIpAddress[4] = { 192, 168, 1, 2 };

/** The GMAC driver instance */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
//#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
//__attribute__((__section__(".region_dma_nocache")))
#endif
static sGmacd gGmacd;

/** The MACB driver instance */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
//#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
//__attribute__((__section__(".region_dma_nocache")))
#endif
static GMacb gGmacb;

/** TX descriptors list */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8), __section__(".region_dma_nocache")))
#endif
static sGmacTxDescriptor gTxDs[TX_BUFFERS];

/** TX callbacks list */
static fGmacdTransferCallback gTxCbs[TX_BUFFERS];

/** RX descriptors list */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8), __section__(".region_dma_nocache")))
#endif
static sGmacRxDescriptor gRxDs[RX_BUFFERS];

/** Send Buffer */
/* Section 3.6 of AMBA 2.0 spec states that burst should not cross 1K Boundaries.
   Receive buffer manager writes are burst of 2 words => 3 lsb bits of the address
   shall be set to 0 */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8), __section__(".region_dma_nocache")))
#endif
static uint8_t pTxBuffer[TX_BUFFERS * GMAC_TX_UNITSIZE];

/** Receive Buffer */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8), __section__(".region_dma_nocache")))
#endif
static uint8_t pRxBuffer[RX_BUFFERS * GMAC_RX_UNITSIZE];

/** Buffer for Ethernet packets */
static uint8_t GEthBuffer[GMAC_FRAME_LENTGH_MAX];

static uint8_t gbIsIpAddrInit = 1;
static uint8_t gtotal_request;
static uint8_t gtotal_reply;

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

/**
 * Gmac interrupt handler
 */
void
GMAC0_IrqHandler(void)
{
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	printf("\r");
	GMACD_Handler(&gGmacd);
}

/**
 * Display the protocol header
 */
static void
GDisplayEthernetHeader(PEthHeader pEth, uint32_t size)
{
	printf("======= Ethernet %4u bytes, HEADER ==========\n\r",
	       (unsigned int) size);
	printf(" @Mac dst = %02x.%02x.%02x.%02x.%02x.%02x\n\r",
	       pEth->et_dest[0], pEth->et_dest[1], pEth->et_dest[2],
	       pEth->et_dest[3], pEth->et_dest[4], pEth->et_dest[5]);
	printf(" @Mac src = %02x.%02x.%02x.%02x.%02x.%02x\n\r", pEth->et_src[0],
	       pEth->et_src[1], pEth->et_src[2], pEth->et_src[3],
	       pEth->et_src[4], pEth->et_src[5]);
	printf(" Protocol = %d\n\r", pEth->et_protlen);
}

static void
GDisplayArpHeader(PArpHeader pArp, uint32_t size)
{
	printf("======= ARP %4u bytes, HEADER ==========\n\r",
	       (unsigned int) size);
	printf(" Hardware type        = %d\n\r", SWAP16(pArp->ar_hrd));
	printf(" protocol type        = 0x%04x\n\r", SWAP16(pArp->ar_pro));
	printf(" Hardware addr lg     = %d\n\r", pArp->ar_hln);
	printf(" Protocol addr lg     = %d\n\r", pArp->ar_pln);
	printf(" Operation            = %d\n\r", SWAP16(pArp->ar_op));
	printf(" Sender hardware addr = %02x.%02x.%02x.%02x.%02x.%02x\n\r",
	       pArp->ar_sha[0], pArp->ar_sha[1], pArp->ar_sha[2],
	       pArp->ar_sha[3], pArp->ar_sha[4], pArp->ar_sha[5]);
	printf(" Sender protocol addr = %d.%d.%d.%d\n\r", pArp->ar_spa[0],
	       pArp->ar_spa[1], pArp->ar_spa[2], pArp->ar_spa[3]);
	printf(" Target hardware addr = %02x.%02x.%02x.%02x.%02x.%02x\n\r",
	       pArp->ar_tha[0], pArp->ar_tha[1], pArp->ar_tha[2],
	       pArp->ar_tha[3], pArp->ar_tha[4], pArp->ar_tha[5]);
	printf(" Target protocol addr = %d.%d.%d.%d\n\r", pArp->ar_tpa[0],
	       pArp->ar_tpa[1], pArp->ar_tpa[2], pArp->ar_tpa[3]);
}

static void
GDisplayIpHeader(PIpHeader pIpHeader, uint32_t size)
{
	printf("======= IP %4u bytes, HEADER ==========\n\r",
	       (unsigned int) size);
	printf(" IP Version        = v.%d\n\r",
	       (pIpHeader->ip_hl_v & 0xF0) >> 4);
	printf(" Header Length     = %d\n\r", pIpHeader->ip_hl_v & 0x0F);
	printf(" Type of service   = 0x%x\n\r", pIpHeader->ip_tos);
	printf(" Total IP Length   = 0x%X\n\r",
	       (((pIpHeader->ip_len) >> 8) & 0xff) +
	       (((pIpHeader->ip_len) << 8) & 0xff00));
	printf(" ID                = 0x%X\n\r",
	       (((pIpHeader->ip_id) >> 8) & 0xff) +
	       (((pIpHeader->ip_id) << 8) & 0xff00));
	printf(" Header Checksum   = 0x%X\n\r",
	       (((pIpHeader->ip_sum) >> 8) & 0xff) +
	       (((pIpHeader->ip_sum) << 8) & 0xff00));
	printf(" Protocol          = ");

	switch (pIpHeader->ip_p) {

	case IP_PROT_ICMP:
		printf("ICMP\n\r");
		break;

	case IP_PROT_IP:
		printf("IP\n\r");
		break;

	case IP_PROT_TCP:
		printf("TCP\n\r");
		break;

	case IP_PROT_UDP:
		printf("UDP\n\r");
		break;

	default:
		printf("%d (0x%X)\n\r", pIpHeader->ip_p, pIpHeader->ip_p);
		break;
	}

	printf(" IP Src Address    = %d:%d:%d:%d\n\r",
	       pIpHeader->ip_src[0],
	       pIpHeader->ip_src[1],
	       pIpHeader->ip_src[2], pIpHeader->ip_src[3]);

	printf(" IP Dest Address   = %d:%d:%d:%d\n\r",
	       pIpHeader->ip_dst[0],
	       pIpHeader->ip_dst[1],
	       pIpHeader->ip_dst[2], pIpHeader->ip_dst[3]);
	printf("----------------------------------------\n\r");

}

/**
 * initialize the Ip address of the board if not yet initialized
 */
static void
garp_init_ip_addr(uint8_t * pData)
{
	uint32_t i;
	PArpHeader pArp = (PArpHeader) (pData + 14 + GMAC_RCV_OFFSET);

	if (SWAP16(pArp->ar_op) == ARP_REQUEST) {

		if (gbIsIpAddrInit == 0) {

			printf
			    ("first arp request, Check @ip. src=%d.%d.%d.%d dst=%d.%d.%d.%d ",
			     pArp->ar_spa[0], pArp->ar_spa[1], pArp->ar_spa[2],
			     pArp->ar_spa[3], pArp->ar_tpa[0], pArp->ar_tpa[1],
			     pArp->ar_tpa[2], pArp->ar_tpa[3]);

			if ((pArp->ar_tpa[0] == pArp->ar_spa[0]) &&
			    (pArp->ar_tpa[1] == pArp->ar_spa[1]) &&
			    (pArp->ar_tpa[2] == pArp->ar_spa[2]) &&
			    (pArp->ar_tpa[3] >= 250) &&
			    (pArp->ar_tpa[3] <= 254)) {
				for (i = 0; i < 4; i++) {
					GIpAddress[i] = pArp->ar_tpa[i];
				}

				printf("=> OK\n\r");
				gbIsIpAddrInit = 1;

			} else {
				printf("=> KO!\n\r");
			}
		}
	}
}

static void
garp_request(uint8_t * pData)
{
	uint32_t i;
	uint8_t gmac_rc = GMACD_OK;

	PEthHeader pEth = (PEthHeader) (pData + GMAC_RCV_OFFSET);
	PArpHeader pArp = (PArpHeader) (pData + 14 + GMAC_RCV_OFFSET);

	pEth->et_protlen = SWAP16(ETH_PROT_ARP);
	// ARP REPLY operation
	pArp->ar_hrd = SWAP16(0x0001);
	pArp->ar_pro = SWAP16(ETH_PROT_IP);
	pArp->ar_hln = 6;
	pArp->ar_pln = 4;
	pArp->ar_op = SWAP16(ARP_REQUEST);

	/* Fill the dest address and src address */
	for (i = 0; i < 6; i++) {
		// swap ethernet dest address and ethernet src address
		pEth->et_dest[i] = 0xff;
		pEth->et_src[i] = GMacAddress[i];
		pArp->ar_tha[i] = 0x00;
		pArp->ar_sha[i] = GMacAddress[i];
	}
	/* swap sender IP address and target IP address */
	for (i = 0; i < 4; i++) {
		pArp->ar_tpa[i] = GDesIpAddress[i];
		pArp->ar_spa[i] = GIpAddress[i];
	}
	gmac_rc = GMACD_Send(&gGmacd, (pData + GMAC_RCV_OFFSET), 42, NULL);
	if (gmac_rc != GMACD_OK) {
		printf("-E- ARP_REQUEST Send - 0x%x\n\r", gmac_rc);
	}
}

/**
 * Process the received ARP packet
 */
static void
garp_process_packet(uint8_t * pData, uint32_t size)
{
	uint32_t i, j;
	uint8_t gmac_rc = GMACD_OK;

	PEthHeader pEth = (PEthHeader) pData;
	PArpHeader pArp = (PArpHeader) (pData + 14 + GMAC_RCV_OFFSET);

	if (SWAP16(pArp->ar_op) == ARP_REQUEST) {

		/* ARP REPLY operation */
		pArp->ar_op = SWAP16(ARP_REPLY);

		/* Fill the dest address and src address */
		for (i = 0; i < 6; i++) {
			/* swap ethernet dest address and ethernet src address */
			pEth->et_dest[i] = pEth->et_src[i];
			pEth->et_src[i] = GMacAddress[i];
			pArp->ar_tha[i] = pArp->ar_sha[i];
			pArp->ar_sha[i] = GMacAddress[i];
		}
		/* swap sender IP address and target IP address */
		for (i = 0; i < 4; i++) {
			pArp->ar_tpa[i] = pArp->ar_spa[i];
			pArp->ar_spa[i] = GIpAddress[i];
		}
		gmac_rc = GMACD_Send(&gGmacd,
				     (pData + GMAC_RCV_OFFSET), size, NULL);
		if (gmac_rc != GMACD_OK) {
			printf("-E- ARP Send - 0x%x\n\r", gmac_rc);
		}
	}

	if (SWAP16(pArp->ar_op) == ARP_REPLY) {
		/* check sender IP address and target IP address */
		for (i = 0, j = 0; i < 4; i++) {
			if (pArp->ar_tpa[i] != GIpAddress[i]) {
				j++;
				break;
			}
			if (pArp->ar_spa[i] != GDesIpAddress[i]) {
				j++;
				break;
			}
		}
		if (!j) {
			gtotal_reply++;
		}
	}
}

/**
 * Process the received IP packet
 */
static void
gip_process_packet(uint8_t * pData)
{
	uint32_t i;
	uint32_t icmp_len;
	uint32_t gmac_rc = GMACD_OK;

	PEthHeader pEth = (PEthHeader) pData;
	PIpHeader pIpHeader = (PIpHeader) (pData + 14 + GMAC_RCV_OFFSET);

	PIcmpEchoHeader pIcmpEcho = (PIcmpEchoHeader) ((char *) pIpHeader + 20);

	switch (pIpHeader->ip_p) {

	case IP_PROT_ICMP:

		/* if ICMP_ECHO_REQUEST ==> resp = ICMP_ECHO_REPLY */
		if (pIcmpEcho->type == ICMP_ECHO_REQUEST) {
			pIcmpEcho->type = ICMP_ECHO_REPLY;
			pIcmpEcho->code = 0;
			pIcmpEcho->cksum = 0;

			/* Checksum of the ICMP Message */
			icmp_len = (SWAP16(pIpHeader->ip_len) - 20);
			if (icmp_len % 2) {
				*((uint8_t *) pIcmpEcho + icmp_len) = 0;
				icmp_len++;
			}
			icmp_len = icmp_len / sizeof (unsigned short);

			pIcmpEcho->cksum =
			    SWAP16(IcmpChksum
				   ((unsigned short *) pIcmpEcho, icmp_len));
			/* Swap IP Dest address and IP Source address */
			for (i = 0; i < 4; i++) {
				GIpAddress[i] = pIpHeader->ip_dst[i];
				pIpHeader->ip_dst[i] = pIpHeader->ip_src[i];
				pIpHeader->ip_src[i] = GIpAddress[i];
			}
			/* Swap Eth Dest address and Eth Source address */
			for (i = 0; i < 6; i++) {

				/* swap ethernet dest address and ethernet src addr */
				pEth->et_dest[i] = pEth->et_src[i];
				pEth->et_src[i] = GMacAddress[i];
			}
			/* send the echo_reply */
			gmac_rc = GMACD_Send(&gGmacd,
					     (pData + GMAC_RCV_OFFSET),
					     SWAP16(pIpHeader->ip_len) + 14 +
					     GMAC_RCV_OFFSET, NULL);
			if (gmac_rc != GMACD_OK) {
				printf("-E- ICMP Send - 0x%x\n\r",
				       (unsigned int) gmac_rc);
			}
		}
		break;

	default:
		break;
	}
}

/**
 * Process the received GMAC packet
 */
static void
geth_process_packet(uint8_t * pData, uint32_t size)
{
	uint16_t pkt_format;

	PEthHeader pEth = (PEthHeader) (pData + GMAC_RCV_OFFSET);
	PIpHeader pIpHeader = (PIpHeader) (pData + 14 + GMAC_RCV_OFFSET);
	IpHeader ipHeader;

	pkt_format = SWAP16(pEth->et_protlen);
	switch (pkt_format) {

		/* ARP Packet format */
	case ETH_PROT_ARP:

		/* Dump the ARP header */
		GDisplayEthernetHeader(pEth, size);
		GDisplayArpHeader((PArpHeader) (pData + 14 + GMAC_RCV_OFFSET),
				  size);

		/* initialize the ip address if not yet initialized */
		garp_init_ip_addr(pData);

		/* Process the ARP packet */
		if (gbIsIpAddrInit == 0)
			return;
		garp_process_packet(pData, size);

		/* Dump for ARP packet */
		break;
		/* IP protocol frame */
	case ETH_PROT_IP:

		if (gbIsIpAddrInit == 0)
			return;

		/* Backup the header */
		memcpy(&ipHeader, pIpHeader, sizeof (IpHeader));

		/* Process the IP packet */
		gip_process_packet(pData);

		/* Dump the IP header */
		GDisplayIpHeader(&ipHeader, size);
		break;
	default:
		break;
	}
}

/*---------------------------------------------------------------------------
 *         Global functions
 *---------------------------------------------------------------------------*/

/**
 * Default main() function. Initializes the DBGU and writes a string on the
 * DBGU.
 */
int
main(void)
{
	sGmacd *pGmacd = &gGmacd;
	GMacb *pGmacb = &gGmacb;
	uint32_t frmSize;
	uint32_t delay;

	/* Disable watchdog */
	WDT_Disable(WDT);
#if defined (ddram)
	mmu_initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_icache();
	cp15_enable_dcache();
#endif
	printf("-- GMAC Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Display MAC & IP settings */
	printf("-- MAC %x:%x:%x:%x:%x:%x\n\r",
	       GMacAddress[0], GMacAddress[1], GMacAddress[2],
	       GMacAddress[3], GMacAddress[4], GMacAddress[5]);
	printf("-- %s`s IP  %d.%d.%d.%d\n\r",
	       BOARD_NAME, GIpAddress[0], GIpAddress[1], GIpAddress[2],
	       GIpAddress[3]);
	printf("-- PC`s IP  %d.%d.%d.%d\n\r", GDesIpAddress[0],
	       GDesIpAddress[1], GDesIpAddress[2], GDesIpAddress[3]);

	printf("Connect the board to a host PC via an ethernet cable\n\r");

	/* Init GMAC driver structure */
	GMACD_Init(pGmacd, GMAC0, ID_GMAC0, GMAC_CAF_ENABLE, GMAC_NBC_DISABLE);
	GMACD_InitTransfer(pGmacd,
			   pRxBuffer,
			   gRxDs,
			   RX_BUFFERS, pTxBuffer, gTxDs, gTxCbs, TX_BUFFERS);
	GMAC_SetAddress(gGmacd.pHw, 0, GMacAddress);

	/* Setup interrupts */
	aic_enable(ID_GMAC0);
	GMACB_Init(pGmacb, pGmacd, BOARD_GMAC_PHY_ADDR);
	GMACB_ResetPhy(pGmacb);
	/* PHY initialize */
	if (!GMACB_InitPhy
	    (pGmacb, pmc_get_master_clock(), 0, 0, gmacPins, PIO_LISTSIZE(gmacPins))) {
		printf("PHY Initialize ERROR!\n\r");
		return 0;
	}
	printf("GMACB_AutoNegotiate\n\r");
	if (!GMACB_AutoNegotiate(pGmacb)) {
		printf("Auto Negotiate ERROR!\n\r");
		return 0;
	}

	for (delay = 0; delay < (pmc_get_master_clock() / 5); delay++)
		asm("nop");
	delay = 0;
	gtotal_request = 0;
	gtotal_reply = 0;
	while (1) {

		if (gtotal_request >= GMAX_ARP_REQUEST)
			break;

		if ((delay++) >= (pmc_get_master_clock() / 1000000)) {
			delay = 0;
			gtotal_request++;
			printf("arp... \n\r");
			garp_request(GEthBuffer);
		} else
			asm("nop");

		/* Process packets */
		if (GMACD_OK !=
		    GMACD_Poll(pGmacd, GEthBuffer, sizeof (GEthBuffer),
			       &frmSize)) {
			continue;
		}

		if (frmSize > 0) {
			/* Handle input frame */
			printf("Process_packet ...\n\r");
			geth_process_packet(GEthBuffer, frmSize);
		}
	}

	printf("%s sends out %d ARP request and gets %d reply\n\r", BOARD_NAME,
	       gtotal_request, gtotal_reply);
	return 1;
}
