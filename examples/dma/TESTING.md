DMA EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with DMA peripherial.

# Example Description
---------------------
This basic example evaluates the DMA data transfer. The available types of
DMA multiple buffers transfer can be switched by the corresponding options.

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

DMA Menu :
Channel Configuration
| Press [a|b|c|d] to set Date width
|   a: BYTE[ ] b: HALFWORD[X] c: WORD[ ] d: DWORD[ ]
| Press [0|1] to set Source Addressing Mode
|   0: FIXED[ ] 1: INCR[X]
| Press [2|3] to set Destination Addressing Mode
|   2: FIXED[ ] 3: INCR[X]

DMA transfer type
    S: Single Block transfer
    L: Linked List transfer
    h: Display this menu

In order to test this example, the process is the following:

Tested with IAR and GCC (sram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a','0','4','s','t' | BYTE, FIXED_S, FIXED_D,Single block | PASSED | PASSED
Press 'a','1','5','s','t' | BYTE, INC_S, INC_D,Single block | PASSED | PASSED
Press 'b','1','5','s','t' | HALFWORD, INC_S, INC_D,Single block | PASSED | PASSED
Press 'c','1','5','s','t' | WORD, INC_S, INC_D,Single block | PASSED | PASSED

--- For SAMA5 only
Press 'd','1','5','s','t' | DWORD, INC_S, INC_D,Single block | PASSED | PASSED

--- For SAMA5 only
Press 'a','l','t' | BYTE, linker_list| PASSED | PASSED
Press 'b','l','t' | HALFWORD,linker_list| PASSED | PASSED
Press 'c','l','t' | WORD, linker_list| PASSED | PASSED

--- For SAMA5 only
Press 'd','l','t' | DWORD,linker_list| PASSED | PASSED
