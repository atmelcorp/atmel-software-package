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

#ifndef _MINI_IP_H
#define _MINI_IP_H

/*---------------------------------------------------------------------------
 *         Include
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <chip.h>

/*---------------------------------------------------------------------------
 *         Define
 *---------------------------------------------------------------------------*/

/** Ethernet types */
#define ETH_PROT_IP             0x0800 /**< 2048  (0x0800) IPv4 */
#define ETH_PROT_ARP            0x0806 /**< 2054  (0x0806) ARP */
#define ETH_PROT_APPLETALK      0x8019 /**< 32923 (0x8019) Appletalk */
#define ETH_PROT_IPV6           0x86DD /**< 34525 (0x86DD) IPv6 */

/** ARP OP codes */
#define ARP_REQUEST             0x0001 /**< ARP Request packet */
#define ARP_REPLY               0x0002 /**< ARP Reply packet */

/** IP protocoles code */
/* http://www.iana.org/assignments/protocol-numbers */
#define IP_PROT_ICMP            1
#define IP_PROT_IP              4
#define IP_PROT_TCP             6
#define IP_PROT_UDP             17

/** ICMP types */
/* http://www.iana.org/assignments/icmp-parameters */
#define ICMP_ECHO_REPLY         0x00 /**< Echo reply (used to ping) */
		    /* 1 and 2  Reserved */
#define ICMP_DEST_UNREACHABLE   0x03 /**< Destination Unreachable */
#define ICMP_SOURCE_QUENCH      0x04 /**< Source Quench */
#define ICMP_REDIR_MESSAGE      0x05 /**< Redirect Message */
#define ICMP_ALT_HOST_ADD       0x06 /**< Alternate Host Address */
		    /*  0x07    Reserved */
#define ICMP_ECHO_REQUEST       0x08 /**< Echo Request */
#define ICMP_ROUTER_ADV         0x09 /**< Router Advertisement */
#define ICMP_ROUTER_SOL         0x0A /**< Router Solicitation */
#define ICMP_TIME_EXC           0x0B /**< Time Exceeded */
#define ICMP_PARAM_PB           0x0C /**< Parameter Problem: Bad IP header */
#define ICMP_TIMESTAMP          0x0D /**< Timestamp */
#define ICMP_TIMESTAMP_REP      0x0E /**< Timestamp Reply */
#define ICMP_INFO_REQ           0x0F /**< Information Request */
#define ICMP_INFO_REPLY         0x10 /**< Information Reply */
#define ICMP_ADD_MASK_REQ       0x11 /**< Address Mask Request */
#define ICMP_ADD_MASK_REP       0x12 /**< Address Mask Reply */
		    /*  0x13    Reserved for security */
		    /*  0X14 through 0x1D Reserved for robustness experiment */
#define ICMP_TRACEROUTE         0x1E /**< Traceroute */
#define ICMP_DAT_CONV_ERROR     0x1F /**< Datagram Conversion Error */
#define ICMP_MOB_HOST_RED       0x20 /**< Mobile Host Redirect */
#define ICMP_W_A_Y              0x21 /**< Where-Are-You (originally meant for
                                          IPv6) */
#define ICMP_H_I_A              0x22 /**< Here-I-Am (originally meant for IPv6)
                                      */
#define ICMP_MOB_REG_REQ        0x23 /**< Mobile Registration Request */
#define ICMP_MOB_REG_REP        0x24 /**< Mobile Registration Reply */
#define ICMP_DOM_NAME_REQ       0x25 /**< Domain Name Request */
#define ICMP_DOM_NAME_REP       0x26 /**< Domain Name Reply */
#define ICMP_SKIP_ALGO_PROT     0x27 /**< SKIP Algorithm Discovery Protocol,
                                          Simple Key-Management for
                                          Internet Protocol */
#define ICMP_PHOTURIS           0x28 /**< Photuris, Security failures */
#define ICMP_EXP_MOBIL          0x29 /**< ICMP for experimental mobility
                                          protocols such as Seamoby [RFC4065] */
		     /* 0x2A through 0xFF  Reserved */

/*---------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Swap 2 bytes of a word */
#define SWAP16(x)   (((x & 0xff) << 8) | (x >> 8))

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/


/** Ethernet header structure */
PACKED_STRUCT _eth_hdr {
	uint8_t et_dest[6];   /**< Destination node */
	uint8_t et_src[6];    /**< Source node */
	uint16_t et_protlen;  /**< Protocol or length */
};

/** ARP header structure */
PACKED_STRUCT _arp_hdr {
	uint16_t ar_hrd;      /**< Format of hardware address */
	uint16_t ar_pro;      /**< Format of protocol address */
	uint8_t ar_hln;	      /**< Length of hardware address */
	uint8_t ar_pln;	      /**< Length of protocol address */
	uint16_t ar_op;	      /**< Operation */
	uint8_t ar_sha[6];    /**< Sender hardware address */
	uint8_t ar_spa[4];    /**< Sender protocol address */
	uint8_t ar_tha[6];    /**< Target hardware address */
	uint8_t ar_tpa[4];    /**< Target protocol address */
};

/** IP Header structure */
PACKED_STRUCT _ip_hdr {
	uint8_t ip_hl_v;      /**< header length and version */
	uint8_t ip_tos;	      /**< type of service */
	uint16_t ip_len;      /**< total length */
	uint16_t ip_id;	      /**< identification */
	uint16_t ip_off;      /**< fragment offset field */
	uint8_t ip_ttl;	      /**< time to live */
	uint8_t ip_p;	      /**< protocol */
	uint16_t ip_sum;      /**< checksum */
	uint8_t ip_src[4];    /**< Source IP address */
	uint8_t ip_dst[4];    /**< Destination IP address */
};

/** ICMP header structure */
PACKED_STRUCT _icmp_hdr {
	uint8_t type;	      /**< type of message */
	uint8_t code;	      /**< type subcode */
	uint16_t cksum;	      /**< ones complement cksum of struct */
};

/** ICMP ECHO header structure */
PACKED_STRUCT _icmp_echo_hdr {
	uint16_t id;	      /**< identifier */
	uint16_t seq;	      /**< sequence number */
};

/** UDP Header structure */
PACKED_STRUCT _udp_hdr {
	uint16_t udp_src;     /**< UDP source port */
	uint16_t udp_dst;     /**< UDP destination port */
	uint16_t udp_len;     /**< Length of UDP packet */
	uint16_t udp_xsum;    /**< Checksum */
};

/** Ethernet packet structure */
PACKED_STRUCT _eth_packet {
	struct _eth_hdr eth;
	union {
		struct _arp_hdr arp;
		struct {
			struct _ip_hdr ip;
			union {
				struct {
					struct _icmp_hdr icmp;
					struct _icmp_echo_hdr icmp_echo;
				};
				struct _udp_hdr udp;
			};
		};
	};
};


/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * Process & return the ICMP checksum
 * \param buffer Pointer to the buffer to process
 * \param len The length of the bufferred data
 */
extern uint16_t icmp_chksum(const uint16_t* buffer, uint32_t len);

/**
 * Display packet headers
 */
extern void display_packet_headers(const struct _eth_packet* pkt, uint32_t size);

#endif /* _MINI_IP_H_ */
