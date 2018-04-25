FREERTOS_QUEUE EXAMPLE
============

# Objectives
------------
This example aims to shows basic use of I/O, FreeRTOS initialization and queues.

# Example Description
---------------------
The demonstration program makes one LED on the board blink at a fixed rate.
This program create two task: one send data, another receive. Data is shared by
these two tasks through queue, which control the led blink rate.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

Two/three LEDs should start blinking on the board. In the terminal window, "S R S R S R ..."

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Start the program | LED blinking, print "S R S R S R ..." | PASSED | PASSED

