ETH_UIP_HELLOWORLD EXAMPLE
============

# Objectives
------------
This project implements a telnet hello-world example of the UIP stack.
It makes the device to respond to telnet connections on port 1000.

# Example Description
---------------------
The program will read the MAC address from the AT24MAC EEPROM if it is
available. Then configure the /EMACGMAC with a default IP address ( / MAC address)
and ask the transceiver to auto-negotiate the best mode of operation. Once this
is done, it will initialize uIP modules.
Please refer to the uIP documentation for more information about the TCP/IP
stack, the hello-world example.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------

 - On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:

     - 115200 bauds
     - 8 bits of data
     - No parity
     - 1 stop bit
     - No flow control

 - Connect an Ethernet cable between the board and the network.

     - The board may be connected directly to a computer; in this case,make sure to use a cross/twisted wired cable such as the one provided with the board.
     - Make sure the IP adress of the computer is in the same network as the device (192.168.1.0/24, the board is at 192.168.1.3).

## Start the application
------------------------

Tested with IAR and GCC (sram and ddram configuration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Connect to the device IP address using telnet on port 1000: ``telnet 192.168.1.3 1000`` | A greeting message will appear: ``Hello. What is your name?`` | PASSED | PASSED
