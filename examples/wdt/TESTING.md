WDT EXAMPLE
============

# Objectives
------------
This example aims to show how to configure different mode/interrupt of watchdog
timer.

This basic application can be configure to reset WDT at every fix period to
restart it or it can be configured to interrupt before allowed window to
generate error interrupt.

# Example Description
---------------------
The demonstration program reset WDT at regular interval without provoking any
error underflow interrupt.

User can choose to generate interrupt(underflow/error) and choose if WDT
generates interrupt or resets the system.

By default WDT is Counter value is set to 10 sec and Delta counter value is set
to 6 sec and fault interrupt is enable and WDT reset disable. WDT values can
not be changed or it can not be put to reset within first 4 sec (forbidden
window) after it starts. Doing so will generate fault interrupt and it restart.
Resetting WDT before it reaches zero and after 4 seconds has past will reset it
properly without generating any fault or interrupt.

If it does not get re-serviced before 10 seconds it will generate underflow
error and depending on whether reset is enabled or not it will reset the
system.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
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

 - Press 1 to generate WatchDog Underflow error
 - Press 2 to reset WatchDog and enable Watchdog Reset
 - Press 3 to generate WatchDog error
 - Press 4 to Enable WatchDog reset interrupt

In order to test this example, the process is the following:

Tested with IAR and GCC (sram ddram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1' | WDT will be reset every 16 seconds | PASSED | PASSED
Press '2' | WDT has been Reset after 5s| PASSED | PASSED
Press '3' | WDT will be reset every 2 seconds | PASSED | PASSED
Press '4' | System will be restarted by WDT after 16 seconds| PASSED | PASSED

