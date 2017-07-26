CAN EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with the CAN (Controller Area
 Network) / MCAN peripheral.

# Example Description
---------------------
The demonstration program transmits several different CAN/MCAN messages. The
 messages transmitted on port 0/1 could be looped back on port 1/0 when the two
 ports are connected together. For the MCAN peripheral, the messages could be
 reflected back on the same port when working under loopback mode, both standard
 CAN and CAN FD operation can be tested too.

# Test
------

## Supported targets
--------------------

* SAM9X25-EK
* SAM9X35-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------
Step needed to set up the example.
* For the EK boards: Connect CAN0 and CAN1 together using a cable
* For the EXPLAINED boards: Mount a FIELDBUS-SHEELD-XULT board and connect CAN0
 and CAN1 together
* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
  - 115200 bauds
  - 8 bits of data
  - No parity
  - 1 stop bit
  - No flow control
* Start the application.
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
CAN menu:
Press [c|f|s] to set CAN or CAN FD mode
   c: [X] ISO 11898-1 CAN
   f: [ ] ISO 11898-7 CAN FD, 64-byte data
   s: [ ] ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit rate
Press [l] to toggle the integrated MCAN loop-back on/off
   l: [ ] Integrated CANTX->CANRX loop-back
   p: Send sample messages
   r: Receive a specified message
   t: Send out a specified message
   h: Display this menu
```

## Start the application

Tested with IAR and GCC
 - SAM9: sram configration
 - SAMA5D2: ddram configration
 - SAMA5D3: sram ddram configration
 - SAME70: sram ddram configration
 - SAMV71: sram ddram configration

To test transfer between two boards, the can cables should be connected correctly before doing the tests.

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'c'.'p' | ISO 11898-1 CAN,| PASSED | PASSED
Press 'f'.'p' | ISO 11898-7 CAN FD, 64-byte data| PASSED | PASSED
Press 's'.'p' | ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit| PASSED | PASSED
Press 'l'.'p' | toggle the integrated MCAN loop-back off| PASSED | PASSED
Press 'r' on one board | prepare to receive the specified message | PASSED | PASSED
Press 't' on the other board | send out the specified message| PASSED | PASSED
Press 'l' | toggle the integrated MCAN loop-back on| PASSED | PASSED

