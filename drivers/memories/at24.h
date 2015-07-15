/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
 */

#ifndef AT24MAC402_H
#define AT24MAC402_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <stdint.h>

//------------------------------------------------------------------------------
//         Global definitions
//------------------------------------------------------------------------------

/** Device address */
#define AT24_EEP_ADDR                 (0x50 | 0x4)
#define AT24_SN_ADDR                  (0x58 | 0x4)

/** Internal Register Address Allocation */
#define AT24MAC402_FIRST_MEM_ADD      0x00
#define AT24MAC402_SECOND_MEM_ADD     0x80
#define AT24_SN_INT_ADDR              0x80        // 0x80-0x8F
#define AT24_EUI48_VALUE_ADDR         0x9A        // 0x9A-0x9F
#define AT24_EUI64_VALUE_ADDR         0x98        // 0x98-0x9F
#define AT24MAC402_DUMMY_ADDR         0x00

#define AT24MAC402_NUM_PAGE           2
#define AT24MAC402_PAGE_SIZE          128
#define AT24MAC402_BLOCK_SIZE         16
#define AT24MAC402_NUM_BLOCK          AT24MAC402_PAGE_SIZE / AT24MAC402_BLOCK_SIZE
#define AT24MAC402_MEM_SIZE           AT24MAC402_PAGE_SIZE * AT24MAC402_NUM_PAGE

#define AT24_SN_SIZE            (0x8F-0x80)+1
#define AT24_EUI48_SIZE         (0x9F-0x9A)+1
#define AT24_EUI64_SIZE         (0x9F-0x98)+1

#define AT24MAC402_INFO_ADD           AT24MAC402_SECOND_MEM_ADD + ((AT24MAC402_NUM_BLOCK-2)* AT24MAC402_BLOCK_SIZE)
#define AT24MAC402_INFO_SIZE          AT24MAC402_BLOCK_SIZE*2

#define SIZE_SUBC 6
#define SIZE_MANUF_COUNTRY 3
#define SIZE_BOARD_IDENT 12
#define SIZE_HW_REVISION 3

struct _at24
{
	struct _twi_desc* twid;

	uint8_t serial_number[AT24_SN_SIZE];
	uint8_t mac_addr_48[AT24_EUI48_SIZE];
	uint8_t mac_addr_64[AT24_EUI64_SIZE];

	uint8_t page_size;
	uint8_t manufacturer[SIZE_SUBC];
	uint8_t country[SIZE_MANUF_COUNTRY];
	uint8_t manuf_year;
	uint8_t manuf_week;
	uint8_t rev_code[SIZE_HW_REVISION];
	uint8_t crc_sn;
	uint16_t addr_ext_config;
	uint8_t board_ident[SIZE_BOARD_IDENT];
	uint8_t rev_mapping;
	uint8_t crc;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t at24_get_serial_number(struct _at24* at24);
extern uint8_t at24_get_mac_address(struct _at24* at24);
extern uint8_t at24_read_eep(struct _at24* at24, uint8_t addr,
			     uint8_t* data, uint8_t length);
extern uint8_t at24_write_eep(struct _at24* at24, uint8_t addr,
			      const uint8_t* data, uint8_t length);
extern uint8_t at24_configure(struct _at24* at24, struct _twi_desc* twid);
extern void at24_reset(struct _at24* at24);
/* extern uint8_t at24_write_eep_async(uint8_t add, uint8_t Len, uint8_t* pDataBuf); */
/* extern uint8_t at24_read_eep_async(uint8_t add, uint8_t Len, uint8_t* pDataBuf); */
/* extern uint8_t at24_get_info_board(struct _at24* pInfo_board); */
/* extern uint8_t at24_set_info_board(struct _at24* pInfo_board); */

/* extern void at24_display_info_board(struct _at24* at24); */
/* extern void at24_display_register(void); */

/* extern uint8_t at24_begin(void); */

/* extern uint8_t at24_test(void); */

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif //#ifndef AT24MAC402_H
