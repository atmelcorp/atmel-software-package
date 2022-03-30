USART_LIN EXAMPLE
============

# Objectives
------------
This example aims to test the LIN interface.

# Example Description
---------------------
This example demonstrates how to use the LIN peripheral.
The LIN interface is integrated in the FLEXCOM peripheral in SAMA5D2x and SAM9X60 MPUs.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
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
 -- LIN Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Menu :
  ------
   P: [ ] Run Master PUBLISHER to Slave SUBSCRIBER
   S: [ ] Run Master SUBSCRIBER to Slave PUBLISHER
   I: [X] Master and Slave mode IGNORE
   Q: Stop demo and Quit
  ------
```

__Connections before running this example:__
- FIELBUS-SHIELD board can be used in this example, there are 2 LIN transceivers (NCV7321D10G) on it.
- Mount the FIELBUS-SHIELD to the XPLAINED board or connect USART signals through wires.
- Connect the LIN and VBB(with power supply) pins of the two transceivers.

__Pins to connect to NCV7321D10G 1:__
|       board           | TXD                        | RXD                        | EN (Enable input)              |
|-----------------------|--------------------------- | -------------------------- | ------------------------------ |
| fieldbus_shield LIN 1 | LIN_1_TXD   JP22 pin 6     | LIN_1_RXD   JP19 pin 6     | LIN_1_RTS   JP26 pin 6         |
| SAM9X60 EK rev A      | PA00 (MikroBUS J15 pin 11) | PA01 (MikroBUS J15 pin 12) | PA02 (40-pin GPIO, J17 pin 11) |
| SAM9X60 EK rev B      | PA00 (RPI J16 pin 3)       | PA01 (RPI J16 pin 5)       | PA02 (40-pin GPIO, J17 pin 11) |
| SAM9X60 CURIOSITY     | PA12 (MikroBUS J8 pin 7)   | PA11 (J8 pin 6)            | PA00 (J8 pin 11)               |

__Pins to connect to NCV7321D10G 2:__
|       board           | TXD                        | RXD                        | EN (Enable input)              |
|-----------------------|--------------------------- | -------------------------- | ------------------------------ |
| fieldbus_shield LIN 2 | LIN_2_TXD   JP23 pin 6     | LIN_2_RXD   JP20 pin 6     | LIN_2_RTS   JP27 pin 6         |
| SAM9X60 EK rev A      | PA07 (J17 pin 24)          | PA08 (J17 pin 26)          | PA03 (J17 pin 13)              |
| SAM9X60 EK rev B      | PA07 (RPI J16 pin 24)      | PA08 (RPI J16 pin 26)      | PA03 (RPI J16 pin 15)          |
| SAM9X60 CURIOSITY     | PA22 (RPI J9 pin 19)       | PA21 (RPI J9 pin 21)       | PA07 (RPI J9 pin 24)           |

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'p' | Print `P: [X] Run Master PUBLISHER to Slave SUBSCRIBER`, `Rx Frame ... Node:1 Handle:0 Count:0001 [ 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x3` ... `Rx Frame ... Node:1 Handle:0 Count:0008 [ 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x3` ... on screen | PASSED | PASSED
Press 'i' | Print ... `I: [X] Master and Slave mode IGNORE` ... on screen | PASSED | PASSED
Press 's' | Print `S: [X] Run Master SUBSCRIBER to Slave PUBLISHER`, `Rx Frame ... Node:0 Handle:1 Count:0001 [ 0x38 0x37 0x36 0x35 0x34 0x33 0x32` ... `Rx Frame ... Node:0 Handle:1 Count:0011 [ 0x38 0x37 0x36 0x35 0x34 0x33 0x32` ... on screen | PASSED | PASSED
Press 'i' | Print ... `I: [X] Master and Slave mode IGNORE` ... on screen | PASSED | PASSED
Press 'q' | Print `End of demo` on screen | PASSED | PASSED

