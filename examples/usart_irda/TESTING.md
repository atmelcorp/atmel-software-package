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
--------
 Setting of jumpers on Fieldbus shield board:
   - Keep JP24 and JP25 open
   - Short 1&2, 3&4, 5&6 of J11

  For SAM9X60-EK Rev A
    - IRDA TX pin : PA00 (MBUS_TWD_PA00 on SAM9X60-EK MikroBUS pin 11) 
    - IRDA RX pin : PA01 (MBUS_TWCK_PA01 on SAM9X60-EK MikroBUS pin 12) 
    - Connect TX to COM4_TX4 (pin 1 on IRDA Interface J11 of Fieldbus shield board)
    - Connect RX to COM4_RX4 (pin 3 on IRDA Interface J11 of Fieldbus shield board)
  
  For SAM9X60-EK rev. B
    - IRDA TX pin : PA00 (MBUS_TWD on 40-pin GPIO/RPi connector pin 3)
    - IRDA RX pin : PA01 (MBUS_TWCK on 40-pin GPIO/RPi connector pin 5)
    - Connect TX to COM4_TX4 (pin 1 on IRDA Interface J11 of Fieldbus shield board)
    - Connect RX to COM4_RX4 (pin 3 on IRDA Interface J11 of Fieldbus shield board)

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

