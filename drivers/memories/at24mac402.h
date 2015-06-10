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


//------------------------------------------------------------------------------
//         Global definitions
//------------------------------------------------------------------------------

/** Device address */
#define AT24MAC402_EEP_ADD            0x50
#define AT24MAC402_EXT_MEM_ADD        0x58

/** Internal Register Address Allocation */
#define AT24MAC402_FIRST_MEM_ADD      0x00
#define AT24MAC402_SECOND_MEM_ADD     0x80
#define AT24MAC402_SERIAL_NUMB_ADD    0x80        // 0x80-0x8F
#define AT24MAC402_EUI48_VALUE_ADD    0x9A        // 0x9A-0x9F
#define AT24MAC402_EUI64_VALUE_ADD    0x98        // 0x98-0x9F
#define AT24MAC402_DUMMY_ADD          0x00

#define AT24MAC402_NUM_PAGE           2
#define AT24MAC402_PAGE_SIZE          128
#define AT24MAC402_BLOCK_SIZE         16
#define AT24MAC402_NUM_BLOCK          AT24MAC402_PAGE_SIZE / AT24MAC402_BLOCK_SIZE
#define AT24MAC402_MEM_SIZE           AT24MAC402_PAGE_SIZE * AT24MAC402_NUM_PAGE

#define AT24MAC402_SER_NUM_SIZE       (0x8F-0x80)+1
#define AT24MAC402_EUI48_SIZE         (0x9F-0x9A)+1
#define AT24MAC402_EUI64_SIZE         (0x9F-0x98)+1

#define AT24MAC402_INFO_ADD           AT24MAC402_SECOND_MEM_ADD + ((AT24MAC402_NUM_BLOCK-2)* AT24MAC402_BLOCK_SIZE)
#define AT24MAC402_INFO_SIZE          AT24MAC402_BLOCK_SIZE*2

#define SIZE_SUBC 6
#define SIZE_MANUF_COUNTRY 3
#define SIZE_BOARD_IDENT 12
#define SIZE_HW_REVISION 3

struct _at24mac402_board_info {
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
} ;

static struct _at24mac402_board_info DEFAULT_BOARD_INFO  =
{16*2, "ATMEL ", "RFO", 15, 01, "AAA", 0x00, 0x0000, "SAMA5D2-XULT", 'C', 0x00};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t at24mac402_get_serial_number (uint8_t* pSerNumbr);
extern uint8_t at24mac402_get_mac_address(uint8_t* pMacAddr);
extern uint8_t at24mac402_read_eep (uint8_t add, uint8_t Len, uint8_t* pDataBuf);
extern uint8_t at24mac402_write_eep (uint8_t add, uint8_t Len, uint8_t* pDataBuf);
extern uint8_t at24mac402_write_eep_async (uint8_t add, uint8_t Len, uint8_t* pDataBuf);
extern uint8_t at24mac402_read_eep_async (uint8_t add, uint8_t Len, uint8_t* pDataBuf);
extern uint8_t at24mac402_get_info_board (struct _at24mac402_board_info* pInfo_board);
extern uint8_t at24mac402_set_info_board (struct _at24mac402_board_info* pInfo_board);

extern void at24mac402_display_info_board (struct _at24mac402_board_info* pInfo_board);
extern void at24mac402_display_register (void);

extern uint8_t at24mac402_begin (void);

extern uint8_t at24mac402_test (void);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif //#ifndef AT24MAC402_H
