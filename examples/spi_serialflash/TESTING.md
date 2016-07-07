SPI_SERIALFLASH EXAMPLE
============

# Objectives
------------
This example aims to test SPI.


# Example Description
---------------------
This example demonstrates how to use SPI serial Flash.


# Test
------

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 115200 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application.
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- Spi flash Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Spi serial flash example mini-console:
 |===========        Commands        ====================|
 | a status                                              |
 |      Query device status                              |
 | a device                                              |
 |      Query serial flash JEDEC info                    |
 | r addr size                                           |
 |      Read 'size' octets starting from address 'addr'  |
 | w addr str                                            |
 |      Write 'str' to address 'addr'                    |
 | d addr [4k|32k|64k|256k]                              |
 |      Erase block containing the address 'addr'        |
 |      The erase can be 4k, 32k, 64k or 256k            |
 | m                                                     |
 |      Print this menu                                  |
 |=======================================================|
```
## Start the application (SAMA5D2-XPLAINED,SAMA5D3-XPLAINED,SAMA5D3-EK,SAMA5D4-XPLAINED,SAMA5D4-EK)

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a status' | Print `AT25 chip status:` ... `- Raw register value:` ... on screen | PASSED | PASSED
Press 'm' | Print the menu on screen | PASSED | PASSED
Press 'a device' | Print `Device info:` ... `- Block Erase Supported:` ... on screen | PASSED | PASSED
Press 'w 0 abcd' | write the flash | PASSED | PASSED
Press 'r 0 4' | Print `at address: 0x00000000`, `61 62 63 64` on screen | PASSED | PASSED
Press 'd 0 4k' | erase the flash | PASSED | PASSED
Press 'w 0 12345678' | write the flash | PASSED | PASSED
Press 'r 0 8' | Print `at address: 0x00000000`, `31 32 33 34 35 36 37 38` on screen | PASSED | PASSED
Press 'd 0 32k' | erase the flash | PASSED | PASSED
Press 'd 0 64k' | erase the flash | PASSED | PASSED

