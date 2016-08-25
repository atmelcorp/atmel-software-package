TWI_EEPROM EXAMPLE
==================

# Objectives
------------
This example aims to test TWI.


# Example Description
---------------------
This example demonstrates how to use the TWI with AT24 driver in order to
access data on a AT24 device.


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
* Start the application (SAMA5D2-XPLAINED,SAMA5D4-XPLAINED, SAM9xx5-EK)
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- Twi EEPROM Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 |================= TWI EEPROM Example ==================|
 | I2C Address: 0x54                                     |
 | Device: AT24MAC402                                    |
 | Mode: DMA                                             |
 | FIFO: disabled                                        |
 |====================== Commands =======================|
 | m polling                                             |
 | m async                                               |
 | m dma                                                 |
 |      Select mode                                      |
 | f fifo                                                |
 |      Toggle feature                                   |
 | r addr size                                           |
 |      Read 'size' bytes starting at address 'addr'     |
 | w addr str                                            |
 |      Write 'str' to address 'addr'                    |
 | a serial                                              |
 |      Query device serial number                       |
 | a mac                                                 |
 |      Query device EUI48                               |
 | h                                                     |
 |      Print this menu                                  |
 |=======================================================|
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'm' | Print the menu on screen | PASSED | PASSED
Press 'd device' | Print `Use AT24 device` on screen | PASSED | PASSED
Press 'a serial' | Print `serial number: ` ... on screen | PASSED | PASSED
Press 'a mac' | Print `MAC addr: ` ... on screen | PASSED | PASSED
Press 'w 0 abcd' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `61 62 63 64` on screen | PASSED | PASSED
Press 'w 0 1234' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `31 32 33 34` on screen | PASSED | PASSED
