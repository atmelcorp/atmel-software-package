USB_CDC_SERIAL EXAMPLE
======================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Communication Device
class (CDC).

# Example Description
---------------------
The demonstration program simulates a serial COM port for host. When the board
running this program connected to a host (PC for example), after driver
installation with the offered 6119.inf. Then the host can send or receive data
through the port with host software. The data stream from the host is then sent
to the board, and forward to USART port of board.

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------
On the computer, open and configure a terminal application (e.g. HyperTerminal
on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

When connecting USB cable to host, the host reports a new USB device
attachment, then new "AT91 USB to Serial Converter (COMx)" appears in the
hardware device list. Run host serial communication software to send data to
the port, and it also can be seen at another serial communication software
which connects to the USART port of the board.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB Device CDC Serial Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --

 -- ESC to Enable/Disable ECHO on cdc serial --
 -- Press 't' to test trasfer --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Write any character except 't' in console | Print 'Alive' in serial and USART | PASSED | PASSED
Write 't' in console |  Print test string '0,1,2...' in serial and USART | PASSED | PASSED
Write any character in serial | Print same character in USART | PASSED | PASSED
Write any character in USART | Print same character in serial | PASSED | PASSED
Print ESC button in console | Open or close cdc eco function | PASSED | PASSED

