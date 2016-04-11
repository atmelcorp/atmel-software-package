USB_AUDIO_LOOPREC EXAMPLE
=========================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Audio Device class.

# Example Description
---------------------
The demonstration program simulates an USB Desktop Speaker with Microphone
which actually does not "speak out" but loop back the sound as microphone
input.

# Test
------

## Setup
--------
On the computer, open and configure a terminal application (e.g. HyperTerminal
on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED)
-------------------------------------------
When the board running this program connected to a host with USB cable
connected, the board appears as a desktop speaker for the host. Then the host
side plays sound through host software. The audio stream from the host is then
sent to the board. At the same time, the audio stream received is also sent
back to host from board for recording.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB Device Audio LoopREC Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Host side play sound then record | Sound is recorded | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
