FREERTOS_START EXAMPLE
============

# Objectives
------------
This example aims to shows basic use of FreeRTOS, create a LDE blink task.

# Example Description
---------------------
The demonstration program makes one LED on the board blink at a fixed rate.
This rate is generated by using vTaskDelay API of FreeRTOS.


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
* SAM9X60-EK
* SAM9X60-CURIOSITY

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

One LEDs should start blinking on the board. In the terminal window, "0 0 0 0 ..."

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Start the program | LED blinking | PASSED | PASSED


