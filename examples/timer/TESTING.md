GETTING_STARTED EXAMPLE
============

# Objectives
------------
This example aims to shows basic use of timer.

# Example Description
---------------------
The program demostrates how to use the time_sleep() function.
The timer is configured to 1Mhz,1 interrupt per 1000 ticks.
It allows the user to wait in different granularity.

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
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'a 12'   | Print `12s elapsed!` on screen | PASSED | PASSED
Press 'b 12'   | Print `12ms elapsed!` on screen | PASSED | PASSED
Press 'c 12'   | Print `12us elapsed!` on screen | PASSED | PASSED
Press 'h'      | Print the munu on screen | PASSED | PASSED

