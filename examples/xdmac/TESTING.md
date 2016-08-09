XDMA EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with XDMA peripherial.

# Example Description
---------------------
This basic example evaluates the XDMA data transfer. The available types of
XDMA multiple buffers transfer can be switched by the corresponding options.

# Test
------

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED,SAMA5D4-XPLAINED,SAMA5D4-EK))
-------------------------------------------

xDMA Menu :
Channel Configuration
| Press [a|b|c|d] to set Date width
|   a: BYTE[ ] b: HALFWORD[X] c: WORD[ ] d: DWORD[ ]
| Press [0|1|2|3] to set Source Addressing Mode
|   0: FIXED[ ] 1: INCR[X] 2: AM[ ] 3: DS_AM[ ]
| Press [4|5|6|7] to set Destination Addressing Mode
|   4: FIXED[ ] 5: INCR[X] 6: AM[ ] 7: DS_AM[ ]
| Press [8|9| to set MEMSET Mode
|   8: NORMAL Mode[X] 9: HW_MODE[ ]

xDMA transfer type
    S: Single Block with Single Microblock transfer
    M: Single Block with Multiple Microblock transfer
    L: Linked List Master transfer
    h: Display this menu

In order to test this example, the process is the following:

Tested with IAR and GCC (sram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a','0','4','s','t' | BYTE, FIXED_S, FIXD_D,Single block | PASSED | PASSED
Press 'a','1','5','s','t' | BYTE, INC_S, INC_D,Single block | PASSED | PASSED
Press 'b','1','5','s','t' | HALFWORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'c','1','5','s','t' | WORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'd','1','5','s','t' | DWORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'a','m','t' | BYTE, mulit block| PASSED | PASSED
Press 'b','m','t' | HALFWORD,mulit block| PASSED | PASSED
Press 'c','m','t' | WORD, mulit block| PASSED | PASSED
Press 'd','m','t' | DWORD,mulit block| PASSED | PASSED
Press 'a','l','t' | BYTE, linker_list| PASSED | PASSED
Press 'b','l','t' | HALFWORD,linker_list| PASSED | PASSED
Press 'c','l','t' | WORD, linker_list| PASSED | PASSED
Press 'd','l','t' | DWORD,linker_list| PASSED | PASSED
