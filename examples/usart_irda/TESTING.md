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

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED)
--------
 Setting of jumpers on Fieldbus shield board:
   - Keep JP24 and JP25 open
   - Short 1&2, 3&4, 5&6 of J11

Menu:
t: transmit data throught IrDA
r: receive data from IrDA

Tested with IAR and GCC (sram ddram configration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'r' on board 0 | Receive mode on board 0 | Waiting| PASSED
Press 't' on board 1 | transmit data throught IrDA4 | data received on board 0 | PASSED
Press 'r' on board 1 | Receive mode on board 1 | Waiting | PASSED
Press 't' on board 0 | transmit data throught IrDA4 | data received on board 1 | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
