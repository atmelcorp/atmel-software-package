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

## Supported targets
--------------------

* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-XPLAINED
* SAMA5D3-EK
* SAMA5D4-XPLAINED
* SAMA5D4-EK
* SAM9XX5-EK
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
* Start the application
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
 | d device                                              |
 |      Select real AT24 device                          |
 | d emulator                                            |
 |      Select emulated AT24 device on TWI slave         |
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

__Pins for SAMA5D2 Xplained Ultra:__
Master SCL                 | Master SDA                | Slave SCL                         | Slave SDA
-------------------------- | ------------------------- | --------------------------------- | ---------------------------------
EXP_TWCK1_PD5 on J22 pin 8 | EXP_TWD1_PD4 on J22 pin 7 | ISC_D6/EXP/XPRO_PC0 on J20 pin 10 | ISC_D5/EXP/XPRO_PB31 on J20 pin 9

__Pins for SAMA5D27 SOM1 EK:__
Master SCL                   | Master SDA                  | Slave SCL                           | Slave SDA
---------------------------- | --------------------------- | ----------------------------------- | -----------------------------------
TWCK_mBUS1 PA23 on J25 pin 5 | TWD_mBUS1 PA24 on J25 pin 6 | Flexcom3_IO1_MISO PC19 on J20 pin 2 | Flexcom3_IO0_MOSI PC20 on J20 pin 4

__Pins for SAMA5D3 EK:__
Master SCL            | Master SDA           | Slave SCL              | Slave SDA
--------------------- | -------------------- | ---------------------- | --------------------
TWCK_ISI on J11 pin 7 | TWD_ISI on J11 pin 8 | ISI_D3 on J11 pin 21   | ISI_D2 on J11 pin 20

__Pins for SAMA5D3 Xplained Ultra:__
Master SCL            | Master SDA           | Slave SCL              | Slave SDA
--------------------- | -------------------- | ---------------------- | --------------------
TWCK_ISI on J20 pin 8 | TWD_ISI on J20 pin 7 | J15_TWCK on J15 pin 10 | J15_TWD on J15 pin 9

__Pins for SAMA5D3 Xplained Ultra:__
Master SCL                  | Master SDA                 | Slave SCL                   | Slave SDA
--------------------------- | -------------------------- | --------------------------- | --------------------------
TWCK1/PC27 on J20 pin 8     | TWD1/PC26 on J20 pin 7     | TWCK0/PA31 on J15 pin 10    | TWD0/PA30 on J15 pin 9

__Pins for SAMA5D4 EK:__
Master SCL                  | Master SDA                 | Slave SCL            | Slave SDA
--------------------------- | -------------------------- | -------------------- | --------------------
ISI_TWCK0_PA31 on J15 pin 7 | ISI_TWD0_PA30 on J15 pin 8 | ISI_D7 on J15 pin 25 | ISI_D6 on J15 pin 24

__Pins for SAMA5D4 Xplained Ultra:__
Master SCL                  | Master SDA                 | Slave SCL                   | Slave SDA
--------------------------- | -------------------------- | --------------------------- | --------------------------
EXP_TWCK0_PA31 on J19 pin 8 | EXP_TWD0_PA30 on J19 pin 7 | EXP/XPRO_PB30 on J8 pin 1 | EXP/XPRO_PB29 on J8 pin 2

__Pins for SAM9xx5 EK:__
Master SCL                  | Master SDA                 | Slave SCL                   | Slave SDA
--------------------------- | -------------------------- | --------------------------- | --------------------------
TWCK0 on J21 pin 7          | TWD0 on J21 pin 8          | TWCK1/PC1 on J2 pin 7       | TWD1/PC0 on J2 pin 5

__Pins for SAME70 Xplained:__
Master SCL                  | Master SDA                 | Slave SCL                   | Slave SDA
--------------------------- | -------------------------- | --------------------------- | --------------------------
A4 TWCK0 on EXT1 pin 12     | PA3 TWD0 on EXT1 pin 11    | PD28 TWCK2 on J400 pin 27   | PD27 TWD2 on J400 pin 26

__Pins for SAMV71 Xplained Ultra:__
Master SCL                  | Master SDA                 | Slave SCL                   | Slave SDA
--------------------------- | -------------------------- | --------------------------- | --------------------------
PA04 TWCK0 on J500 pin 10   | PA03 TWD0 on J500 pin 9    | PD28 TWCK2 on J505 pin 1    | PD27 TWD2 on J505 pin 2

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
Connect wires from TWI master to TWI slave for testing the emulated AT24 EEPROM | | N/A | N/A
Press 'd emulator' | Print `Use AT24 emulator` on screen | PASSED | PASSED
Press 'w 0 abcd' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `61 62 63 64` on screen | PASSED | PASSED
Press 'w 0 1234' | Print `Write done.` on screen | PASSED | PASSED
Press 'r 0 4' | Print `31 32 33 34` on screen | PASSED | PASSED
