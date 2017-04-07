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
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED

## Setup
--------
 - On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:

     - 115200 bauds
     - 8 bits of data
     - No parity
     - 1 stop bit
     - No flow control

 - Connect the smart card to the board.
Smart Card | Board     | SAMA5D2-XPLAINED  | SAMA5D27-SOM1-EK  | SAMA5D3-XPLAINED | SAMA5D3-EK       | SAMA5D4-XPLAINED | SAMA5D4-EK        | SAM9XX5-EK       |
-----------|-----------|-------------------|-------------------|------------------|------------------|------------------|-------------------|------------------|
C1 (Vcc)   | 7816_3V5V | PB29 (J17 pin 13) | PC19 (ISC pin 28) | PE25(J19 pin 27) | PB28 (J3 pin 31) | PD16 (J19 pin 4) | PD16 (J11 pin 13) | PA1A (J1 pin 7)  |
C2 (Reset) | 7816_RST  | PC0  (J17 pin 8)  | PC22 (ISC pin 12) | PD24(J19 pin 26) | PB27 (J3 pin 29) | PD15 (J15 pin 8) | PD15 (J11 pin 18) | PA2A (J1 pin 9)  |
C3 (Clock) | 7816_CLK  | PB30 (J17 pin 6)  | PC18 (ISC pin 27) | PE20(J19 pin 22) | PB25 (J3 pin 25) | PD29 (J15 pin 6) | PD29 (J11 pin 9)  | PA4A (J1 pin 13) |
C5 (GND)   | GND       | GND               | GND               | GND              | GND              | GND              | GND               | GND              |
C7 (I/O)   | 7816_IO   | PB28 (J17 pin 14) | PC20 (ISC pin 29) | PE26(J19 pin 28) | PB29 (J3 pin 33) | PD17 (J19 pin 3) | PD17 (J11 pin 14) | PA0A (J1 pin 5)  |
C6 (Vpp)   |
C4 (RFU)   |
C8 (RFU)   |

 - Connect the smart card to the board (Cont.)
Smart Card | Board     | SAMV71-XPLAINED  |
-----------|-----------|------------------|
C1 (Vcc)   | 7816_3V5V | PB0 (EXT1 pin 13)|
C2 (Reset) | 7816_RST  | PB3 (EXT1 pin 5) |
C3 (Clock) | 7816_CLK  | PB13(ADCH pin 5) |
C5 (GND)   | GND       | GND              |
C7 (I/O)   | 7816_IO   | PB1 (EXT1 pin 14)|
C6 (Vpp)   |
C4 (RFU)   |
C8 (RFU)   |

If necessary, another pin can be connected on the card reader for detecting the
insertion and removal: 7816_IRQ.

## Start the application
------------------------

ISO7816 driver will be configured and initialized, then the ATR will be gained and decoded.
Tested with IAR and GCC (sram and ddram configuration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press "1" | Non-zero value will be answered | PASSED | PASSED
Press "2" | Non-zero value will be answered | PASSED | PASSED
Press "3" | Non-zero value will be answered | PASSED | PASSED

