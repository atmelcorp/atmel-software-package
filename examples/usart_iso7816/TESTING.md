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
* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAM9X60-EK

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

Smart Card        | C1 (Vcc)          | C2 (Reset)        | C3 (Clock)        | C5 (GND) | C7 (I/O)          | C6 (Vpp) | C4 (RFU) | C8 (RFU) |
------------------|-------------------|-------------------|-------------------|----------|-------------------|----------|----------|----------|
Board             | 7816_3V5V         | 7816_RST          | 7816_CLK          | GND      | 7816_IO           |
SAMA5D2-PTC-EK    | PD22 (J15B pin 5) | PD25 (J15A pin 1) | PD23 (J15B pin 3) | GND      | PD21 (J15B pin 6) |
SAMA5D2-XPLAINED  | PB29 (J17 pin 13) | PC0  (J17 pin 8)  | PB30 (J17 pin 6)  | GND      | PB28 (J17 pin 14) |
SAMA5D27-SOM1-EK  | PC19 (ISC pin 28) | PC22 (ISC pin 12) | PC18 (ISC pin 27) | GND      | PC20 (ISC pin 29) |
SAMA5D3-XPLAINED  | PE25(J19 pin 27)  | PD24(J19 pin 26)  | PE20(J19 pin 22)  | GND      | PE26(J19 pin 28)  |
SAMA5D3-EK        | PB28 (J3 pin 31)  | PB27 (J3 pin 29)  | PB25 (J3 pin 25)  | GND      | PB29 (J3 pin 33)  |
SAMA5D4-XPLAINED  | PD16 (J19 pin 4)  | PD15 (J15 pin 8)  | PD29 (J15 pin 6)  | GND      | PD17 (J19 pin 3)  |
SAMA5D4-EK        | PD16 (J11 pin 13) | PD15 (J11 pin 18) | PD29 (J11 pin 9)  | GND      | PD17 (J11 pin 14) |
SAM9XX5-EK        | PA1A (J1 pin 7)   | PA2A (J1 pin 9)   | PA4A (J1 pin 13)  | GND      | PA0A (J1 pin 5)   |
SAMV71-XPLAINED   | PB0 (EXT1 pin 13) | PB3 (EXT1 pin 5)  | PB13(ADCH pin 5)  | GND      | PB1 (EXT1 pin 14) |
SAM9X60-EK Rev A  | PA11 (J15 pin 5)  | PA0 (J15 pin 11)  | PA13 (J15 pin 4)  | GND      | PA12 (J15 pin 6)  |
SAM9X60-EK rev. B | PA11 (J14 pin 5)  | PA0 (J16 pin 3)   | PA13 (J14 pin 4)  | GND      | PA12 (J14 pin 6)  |

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

