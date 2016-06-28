TWI_EEPROM EXAMPLE
==================

# Objectives
------------
This example aims to test TWI.


# Example Description
---------------------
This example demonstrates how to use the TWI with AT24 driver in order to
access data on a real AT24 device and on an emulated AT24 using a TWI slave
port, it also emulates an EEPROM which size is 1K bits.


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
 -- Twi EEPROM Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
  Twi mode DMA
 twi eeprom example mini-console:
 |===========        Commands        ====================|
 | a serial                                              |
 |      Query device serial number                       |
 | a mac                                                 |
 |      Query device mac addr                            |
 | r addr size                                           |
 |      Read 'size' octets starting from address 'addr'  |
 | w addr str                                            |
 |      Write 'str' to address 'addr'                    |
 | s device (default)                                    |
 |      Select at24 device                               |
 | s emulator                                            |
 |      Select to TWI slave device emulating at24        |
 | m                                                     |
 |      Print this menu                                  |
 |=======================================================|
```

__Pins for SAMA5D2 Xplained Ultra:__
Master SCL | Master SDA | Slave SCL | Slave SDA
------------ | ------------- | ------------- | -------------
EXP_TWCK1_PD5 on J22 pin 8 | EXP_TWD1_PD4 on J22 pin 7 | ISC_D5/EXP/XPRO_PB31 on J25 pin 11 | ISC_D6/EXP/XPRO_PC0 on J25 pin 12

__Pins for SAMA5D4 Xplained Ultra:__
Master SCL | Master SDA | Slave SCL | Slave SDA
------------ | ------------- | ------------- | -------------
EXP_TWCK0_PA31 on J19 pin 8 | EXP_TWD0_PA30 on J19 pin 7 | EXP/XPRO_PE30 on J17 pin 10 | EXP/XPRO_PE29 on J17 pin 9

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'm' | Print the menu on screen | PASSED | PASSED
Press 'a serial' | Print `serial number: ` ... on screen | PASSED | PASSED
Press 'a mac' | Print `MAC addr: ` ... on screen | PASSED | PASSED
Press 'w 0 abcd' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `61 62 63 64` on screen | PASSED | PASSED
Press 'w 0 1234' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `31 32 33 34` on screen | PASSED | PASSED
Press 's device' | Print `Use AT24 device` on screen | PASSED | PASSED
Connect TWI wires to another board running this example | For testing the EEPROM emulated. This board's `master SCL` to another board's `slave SCL`, This board's `master SDA` to another board's `slave SDA` | N/A | N/A
Press 's emulator' | Print `Use AT24 emulator` on screen | PASSED | PASSED
Press 'w 0 abcd' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `61 62 63 64` on screen | PASSED | PASSED
Press 'w 0 1234' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `31 32 33 34` on screen | PASSED | PASSED
