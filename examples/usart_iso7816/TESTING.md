USART_ISO7816 EXAMPLE
============

# Objectives
------------
This example sends ISO 7816 commands to a smartcard connected to the board.

# Example Description
---------------------
The iso7816 software provide in this examples is use to transform APDU commands
to TPDU commands for the smart card.

Limitations:
- support is provided here only for T=0 protocol.
- polling is used to send and receive characters.
- driver is compliant with case 1, 2, 3 of the ISO7816-4 specification.

The pins used are defined in ISO7816_Init, users must check/change these
definitions according to the hardware used.

# Test
------

## Setup
--------
 - On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:

     - 57600 bauds (for sama5d2-xplained)
     - 115200 bauds (for sama5d4-xplained)
     - 8 bits of data
     - No parity
     - 1 stop bit
     - No flow control

 - Connect the smart card to the board.
 Smart Card  | Board |
 ------|-------------|
C1 (Vcc)   | 7816_3V5V
C2 (Reset) | 7816_RST
C3 (Clock) | 7816_CLK
C5 (GND)   | GND
C7 (I/O)   | 7816_IO
C6 (Vpp)   |
C4 (RFU)   |
C8 (RFU)   |

If necessary, another pin can be connected on the card reader for detecting the
insertion and removal: 7816_IRQ.

## Start the application (SAMA5D2-XPLAINED)
--------
ISO7816 driver will be configured and initialized, then the ATR will be gained and decoded.
Tested with IAR and GCC (sram and ddram configuration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press "1" | Non-zero value will be answered | PASSED | PASSED
Press "2" | Non-zero value will be answered | PASSED | PASSED
Press "3" | Non-zero value will be answered | PASSED | PASSED


# Log
------

## Current version
--------
 - v1.3

## History
--------
