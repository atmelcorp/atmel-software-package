ETH EXAMPLE
============

# Objectives
------------
This example uses the Ethernet MAC (EMAC) / Gigabit Ethernet MAC (GMAC) and the on-board Ethernet
transceiver available on the board. It enables the device to respond to a ping
command sent by a host computer.

# Example Description
---------------------
The program will read the MAC address from the AT24MAC EEPROM if it is
available. Then configure the EMAC/GMAC with a default IP address ( / MAC address)
and ask the transceiver to auto-negotiate the best mode of operation. Once this
is done, it will start to monitor incoming packets and process them whenever
appropriate.

The basic will only answer to two kinds of packets:
 - ARP requests with its MAC address
 - ICMP ECHO requests so the device can be PING'ed.

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

The program will auto-negotiate the mode of operation and start receiving
packets, displaying feedback in the terminal.

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Nothing to do | Display ``sama5d* sends out ** ARP request and gets ** reply`` | PASSED | PASSED
