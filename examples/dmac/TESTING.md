DMAC EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with DMAC peripherial.

# Example Description
---------------------
This basic example evaluates the DMAC data transfer. The available types of
DMAC multiple buffers transfer can be switched by the corresponding options.

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

## Start the application (SAMA5D3-EK,SAMA5D3-XPLAINED,SAM9XX5-EK)
-------------------------------------------
DMAC Menu :
Channel Configuration
| Press [a|b|c|d] to set Date width
|   a: BYTE[ ] b: HALFWORD[X] c: WORD[ ] d: DWORD[ ]
| Press [0|1] to set Source Addressing Mode
|   0: FIXED[ ] 1: INCR[X]
| Press [2|3] to set Destination Addressing Mode
|   2: FIXED[ ] 3: INCR[X]

DMAC transfer type
    S: Single Block with Single Microblock transfer
    M: Single Block with Multiple Microblock transfer
    L: Linked List Master transfer
    h: Display this menu

In order to test this example, the process is the following:

Tested with IAR and GCC (sram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a','0','1','s','t' | BYTE, FIXED_S, FIXD_D,Single block | PASSED | PASSED
Press 'a','1','3','s','t' | BYTE, INC_S, INC_D,Single block | PASSED | PASSED
Press 'b','1','3','s','t' | HALFWORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'c','1','3','s','t' | WORD, INC_S, INC_D,Single block | PASSED | PASSED
----- For SAMA5D3 ONLY ------
Press 'd','1','3','s','t' | DWORD, INC_S, INC_D,Single block | PASSED | PASSED

Press 'a','m','t' | BYTE, mulit block| PASSED | PASSED
Press 'b','m','t' | HALFWORD,mulit block| PASSED | PASSED
Press 'c','m','t' | WORD, mulit block| PASSED | PASSED

----- For SAMA5D3 ONLY ------
Press 'd','1','3','s','t' | DWORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'd','m','t' | DWORD,mulit block| PASSED | PASSED

Press 'a','l','t' | BYTE, linker_list| PASSED | PASSED
Press 'b','l','t' | HALFWORD,linker_list| PASSED | PASSED
Press 'c','l','t' | WORD, linker_list| PASSED | PASSED

----- For SAMA5D3 ONLY ------
Press 'd','l','t' | DWORD,linker_list| PASSED | PASSED
