USB_HID_MOUSE EXAMPLE
=====================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Human Interface
Device class (HID).

# Example Description
---------------------
The demonstration program simulates a HID-compliant mouse. When the board
running this program connected to a host (PC for example), with USB cable, the
board appears as a USB mouse for the host. Then the host can play sound through
host software. Press 'I'/'J'/'K'/'L' into the console to control the cursor on
the host.

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

When connecting USB cable to host, the new "HID Mouse Device" appears in the
hardware device list. Once the device is connected and configured, pressing the
'I J K L' key to move the cursor.

 In the terminal window, the following text should appear (values depend on the board and chip used):
```
 -- USB Device HID Mouse Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 -- Press I J K L to move cursor
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'I' | Cursor move up | PASSED | PASSED
Press 'J' | Cursor move to left | PASSED | PASSED
Press 'K' | Cursor move down | PASSED | PASSED
Press 'L' | Cursor move to right | PASSED | PASSED

