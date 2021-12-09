IRDA EXAMPLE
============

# Objectives
------------
This example aims gives an example of how to use USART in IrDA mode.

# Example Description
---------------------
To run this example 2 kits are needed, one acts as a transmitter and the other
acts as a receiver. The infrared modules should keep face to face

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
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
Initializing IrDA interface
IrDA interface initialized.

Menu:
  t - transmit data throught IrDA
  r - receive data from IrDA
```

__Connections before running this example:__
- FIELBUS-SHIELD board can be used in this example, there is an IrDA transceiver (TFDU4101) on it
- Short pin 5 to pin 6 of J11

__Pins to connect to the transceiver:__
|       board           | TFDU4101 TXD on Fieldbus shield J11 pin 2 | TFDU4101 RXD on Fieldbus shield J11 pin 4 |
|-----------------------|-------------------------------------------|-------------------------------------------|
| SAM9X60 EK rev A      | PA00 (MBUS_TWD_PA00 on MikroBUS pin 11)   | PA01 (MBUS_TWCK_PA01 on MikroBUS pin 12)  |
| SAM9X60 EK rev B      | PA00 (MBUS_TWD on J16 pin 3)              | PA01 (MBUS_TWCK on J16 pin 5)             |
| SAM9X60 CURIOSITY     | PA00 (MBUS_TWD_PA0 on MikroBUS pin 11)    | PA01 (MBUS_TWCK_PA1 on MikroBUS pin 12)   |


Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'r' on board 0 | Receive mode on board 0 | Waiting| PASSED
Press 't' on board 1 | transmit data throught IrDA4 | data received on board 0 | PASSED
Press 'r' on board 1 | Receive mode on board 1 | Waiting | PASSED
Press 't' on board 0 | transmit data throught IrDA4 | data received on board 1 | PASSED

