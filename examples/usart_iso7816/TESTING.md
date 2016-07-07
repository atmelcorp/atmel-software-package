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

     - 115200 bauds
     - 8 bits of data
     - No parity
     - 1 stop bit
     - No flow control

 - Connect the smart card to the board.
 Smart Card  | Board |  SAMA5D2-XPLAINED | SAMA5D4-XPLAINED |    SAMA5D4-EK   |
 ------|-------------|-------------------|------------------|-----------------|
C1 (Vcc)   | 7816_3V5V|PB29 (J17 pin 13 )|PD16 (J19 pin 4 ) |PD16(J11 pin 13 )|
C2 (Reset) | 7816_RST |PC0  (J17 pin 8)  |PD15 (J15 pin 8 ) |PD15(J11 pin 18 )|
C3 (Clock) | 7816_CLK |PB30 (J17 pin 6)  |PD29 (J15 pin 6 ) |PD29(J11 pin 9 ) |
C5 (GND)   | GND      |------------------|------------------|-----------------|
C7 (I/O)   | 7816_IO  |PB28 (J17 pin 14) |PD17(J19 pin 3 )  |PD17(J11 pin 14 )|
C6 (Vpp)   |
C4 (RFU)   |
C8 (RFU)   |

If necessary, another pin can be connected on the card reader for detecting the
insertion and removal: 7816_IRQ.

## Start the application (SAMA5D2-XPLAINED,SAMA5D4-XPLAINED,SAMA5D4-EK)
--------
ISO7816 driver will be configured and initialized, then the ATR will be gained and decoded.
Tested with IAR and GCC (sram and ddram configuration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press "1" | Non-zero value will be answered | PASSED | PASSED
Press "2" | Non-zero value will be answered | PASSED | PASSED
Press "3" | Non-zero value will be answered | PASSED | PASSED


