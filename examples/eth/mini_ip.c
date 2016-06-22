/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
/** \file */
/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "mini_ip.h"
#include <stdbool.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
 *      Local functions
 *---------------------------------------------------------------------------*/

static void _display_ethernet_header(const struct _eth_hdr* eth, uint32_t size)
{
	printf("======= Ethernet %u bytes =======\n\r", (unsigned)size);
	printf(" @MAC dst = %02x:%02x:%02x:%02x:%02x:%02x\n\r",
			eth->et_dest[0], eth->et_dest[1], eth->et_dest[2],
			eth->et_dest[3], eth->et_dest[4], eth->et_dest[5]);
	printf(" @MAC src = %02x:%02x:%02x:%02x:%02x:%02x\n\r",
			eth->et_src[0], eth->et_src[1], eth->et_src[2],
			eth->et_src[3], eth->et_src[4], eth->et_src[5]);
	printf(" Protocol = %04x\n\r", SWAP16(eth->et_protlen));
}

static void _display_arp_header(const struct _arp_hdr* arp)
{
	printf("======= ARP =======\n\r");
	printf(" Hardware type        = %d\n\r", SWAP16(arp->ar_hrd));
	printf(" protocol type        = 0x%04x\n\r", SWAP16(arp->ar_pro));
	printf(" Hardware addr lg     = %d\n\r", arp->ar_hln);
	printf(" Protocol addr lg     = %d\n\r", arp->ar_pln);
	printf(" Operation            = %d\n\r", SWAP16(arp->ar_op));
	printf(" Sender hardware addr = %02x:%02x:%02x:%02x:%02x:%02x\n\r",
			arp->ar_sha[0], arp->ar_sha[1], arp->ar_sha[2],
			arp->ar_sha[3], arp->ar_sha[4], arp->ar_sha[5]);
	printf(" Sender protocol addr = %d.%d.%d.%d\n\r",
			arp->ar_spa[0], arp->ar_spa[1],
			arp->ar_spa[2], arp->ar_spa[3]);
	printf(" Target hardware addr = %02x:%02x:%02x:%02x:%02x:%02x\n\r",
			arp->ar_tha[0], arp->ar_tha[1], arp->ar_tha[2],
			arp->ar_tha[3], arp->ar_tha[4], arp->ar_tha[5]);
	printf(" Target protocol addr = %d.%d.%d.%d\n\r",
			arp->ar_tpa[0], arp->ar_tpa[1],
			arp->ar_tpa[2], arp->ar_tpa[3]);
}

static void _display_ip_header(const struct _ip_hdr* ip)
{
	printf("======= IP =======\n\r");
	printf(" IP Version        = v.%d\n\r", (ip->ip_hl_v & 0xF0) >> 4);
	printf(" Header Length     = %d\n\r", ip->ip_hl_v & 0x0F);
	printf(" Type of service   = 0x%x\n\r", ip->ip_tos);
	printf(" Total IP Length   = 0x%X\n\r",
	       (((ip->ip_len) >> 8) & 0xff) + (((ip->ip_len) << 8) & 0xff00));
	printf(" ID                = 0x%X\n\r",
	       (((ip->ip_id) >> 8) & 0xff) + (((ip->ip_id) << 8) & 0xff00));
	printf(" Header Checksum   = 0x%X\n\r",
	       (((ip->ip_sum) >> 8) & 0xff) + (((ip->ip_sum) << 8) & 0xff00));
	printf(" Protocol          = ");
	switch (ip->ip_p) {
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
		printf("%d (0x%X)\n\r", ip->ip_p, ip->ip_p);
		break;
	}
	printf(" IP Src Address    = %d.%d.%d.%d\n\r",
			ip->ip_src[0], ip->ip_src[1],
			ip->ip_src[2], ip->ip_src[3]);
	printf(" IP Dest Address   = %d.%d.%d.%d\n\r",
			ip->ip_dst[0], ip->ip_dst[1],
			ip->ip_dst[2], ip->ip_dst[3]);
}

static void _display_icmp_header(const struct _icmp_hdr* icmp)
{
	printf("======= ICMP =======\n\r");
	printf(" Type     = %d", icmp->type);
	switch (icmp->type) {
	case ICMP_ECHO_REPLY:
		printf(" (ECHO REPLY)");
		break;
	case ICMP_ECHO_REQUEST:
		printf(" (ECHO REQUEST)");
		break;
	default:
		break;
	}
	printf("\r\n");
	printf(" Code     = %d\n\r", icmp->code);
	printf(" Checksum = 0x%x\n\r", icmp->cksum);
}

static void _display_icmp_echo_header(bool request, const struct _icmp_echo_hdr* icmp_echo)
{
	printf("======= ICMP ECHO %s =======\n\r",
			request ? "REQUEST" : "REPLY");
	printf(" ID  = %d\n\r", SWAP16(icmp_echo->id));
	printf(" Seq = %d\n\r", SWAP16(icmp_echo->seq));
}

/*---------------------------------------------------------------------------
 *      Public functions
 *---------------------------------------------------------------------------*/

uint16_t icmp_chksum(const uint16_t* buffer, uint32_t len)
{
	uint32_t i, t;
	for (i = 0, t = 0; i < len; i++, buffer++) {
		t += SWAP16(*buffer);
	}
	t = (t & 0xffff) + (t >> 16);
	return (uint16_t) (~t);
}

void display_packet_headers(const struct _eth_packet* pkt, uint32_t size)
{
	_display_ethernet_header(&pkt->eth, size);

	uint16_t prot = SWAP16(pkt->eth.et_protlen);
	switch (prot) {
	case ETH_PROT_ARP:
		_display_arp_header(&pkt->arp);
		break;
	case ETH_PROT_IP:
		_display_ip_header(&pkt->ip);
		switch (pkt->ip.ip_p) {
		case IP_PROT_ICMP:
			_display_icmp_header(&pkt->icmp);
			switch (pkt->icmp.type) {
			case ICMP_ECHO_REPLY:
				_display_icmp_echo_header(false, &pkt->icmp_echo);
				break;
			case ICMP_ECHO_REQUEST:
				_display_icmp_echo_header(true, &pkt->icmp_echo);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	printf("----------------------------------------\n\r");
}
