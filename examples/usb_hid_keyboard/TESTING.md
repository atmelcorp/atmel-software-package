USB_HID_KEYBOARD EXAMPLE
========================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Human Interface
Device class (HID).

# Example Description
---------------------
The demonstration program simulates a HID Keyboard. When the board running this
program connected to a host (PC for example), with USB cable, the board appears
as a HID keyboard for the host. Type letter into the console to input it to the
host. It also can emulate the status of NumLock key.

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-XPLAINED
* SAMA5D2-PTC-EK
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

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB Device HID Keyboard Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 -- : DBG key 1 2 used as buttons
 -- : 1st press to push, 2nd press to release
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press any character except '1' and '2' | The character input print in console | PASSED | PASSED
Press '1' and then again| Print `Key 0 pressed uuuuuuuu` then Print `Key 0 released` | PASSED | PASSED
Press '2' and then again| Print ` _ _ _ Key 1 pressed` or ` N _ _ Key 1 pressed` then Print `Key 1 released` | PASSED | PASSED

