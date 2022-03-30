USART RS485 EXAMPLE
===================

# Objectives
------------
This example aims to perform peripheral data transfer over USART rs485 mode.

# Example Description
---------------------
The example handles the transfer between two USART peripherals,
transfer/receive data to/from USART rs485 mode.

# Test
------
## Supported targets
--------------------
* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED
* SAM9X60-EK
* SAM9X60-CURIOSITY

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
Menu :
------
 - t: Transmit pattern to RS485
 - r: Receive data from RS485
 - m: Display menu
```

### sama5dx\same70\samv71\sam9x60 board
--------------------
 *  This package can be used with SAMA5Dx/SAME70/SAMV71/SAM9X60 board.
 *  Before running, make sure to connect two boards with RS485 lines. (Use rs485 adapt board(ADM3485ARZ) for this purpose.
 *  Match each paired pins of two boards respectively with A to A, B to B and FGND to FGND(the central pin of J3).
 *  Connect boards to ADM3485ARZ:

	|  Board  |  ADM3485ARZ |
	|---------|-------------|
	|   TXD   |   DI        |
	|   RXD   |   RO        |
	|   RTS   |   DE        |
	|   3.3v  |   3.3v      |
	|   GND   |   GND       |
	|   TXD   |   DI        |
 *  2 ways to connect !RE(ADM3485ARZ)
	-  1. RTS( board) <-> RE(ADM3485ARZ)
	-  2. RE(ADM3485ARZ) <-> GND

__Pins to connect to ADM3485ARZ:__
|       board       | TXD                        | RXD                        | RTS                            |
|-------------------|--------------------------- | -------------------------- | ------------------------------ |
| SAM9X60 EK rev A  | PA00 (MikroBUS J15 pin 11) | PA01 (MikroBUS J15 pin 12) | PA02 (40-pin GPIO, J17 pin 11) |
| SAM9X60 EK rev B  | PA00 (RPI J16 pin 3)       | PA01 (RPI J16 pin 5)       | PA02 (40-pin GPIO, J17 pin 11) |
| SAM9X60 CURIOSITY | PA12 (MikroBUS J8 pin 7)   | PA11 (J8 pin 6)            | PA00 (J8 pin 11)               |

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'r' on board 0 | Receive mode on board 0 | Waiting| PASSED
Press 't' on board 1 | transmit data throught usart | data received on board 0 | PASSED
Press 'r' on board 1 | Receive mode on board 1 | Waiting | PASSED
Press 't' on board 0 | transmit data throught usart | data received on board 1 | PASSED
Press 'm'| Display the menu | Display the help menu on console | PASSED

