EEFC EXAMPLE
============

# Objectives
------------
This example aims to test embedded flash.


# Example Description
---------------------
This example demonstrates how to program Eebedded Flash with EEFC.


# Test
------

## Supported targets
--------------------

* SAME70-XPLAINED
* SAMV71-XPLAINED

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
Embedded flash example mini-console:
|=============== Embendded Flash Example ===============|
|====================== Commands =======================|
| a uid                                                 |
|      Query embedded flash unique id                   |
| r addr size                                           |
|      Read 'size' bytes starting at address 'addr'     |
| w addr str                                            |
|      Write 'str' to address 'addr'                    |
| d addr                                                |
|      Erase sector from the address 'addr'             |
|      'all' to erase entire flash                      |
| h                                                     |
|      Print this menu                                  |
|=======================================================|
```

## Start the application

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a uid' | Print `Read UID complete: 00 31 34 53 4b 48 4a 48 30 34 30 34 38 30 31 33' on screen | PASSED | PASSED
Press 'd 0' | erase the first sector, print `Erase complete (8192 bytes)` on screen | PASSED | PASSED
Press 'w 0 abcd' | write 4 bytes to the flash, print `Write complete (4 bytes)` on screen | PASSED | PASSED
Press 'r 0 4' | read 4 bytes from flash, print `Read complete (4 bytes): 61 62 63 64` screen | PASSED | PASSED
Press 'd 0' | erase the first sector, print `Erase complete (8192 bytes)` on screen | PASSED | PASSED
Press 'w 0 12345678' | write 8 bytes to the flash, print `Write complete (8 bytes)` on screen | PASSED | PASSED
Press 'r 0 8' | read 8 bytes from flash, print `Read complete (8 bytes): 31 32 33 34 35 36 37 38` on screen | PASSED | PASSED

