ADC EXAMPLE
============

# Objectives
------------
The adc12 example demonstrates how to use ADC peripheral with several modes.

# Example Description
---------------------
This application shows how to use the ADC using the several modes:
several types of trigger (Software, ADTRG, Timer, etc.), using sequencer or
not, with/without DMA, power save mode.

Users can select different mode by configuration menu in the terminal.

# Test
------

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 57600 bauds (for sama5d2-xplained)
 - 115200 bauds (for sama5d4-xplained)
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED)
--------
The following menu will be displayed in the terminal window.

``=========================================================
Menu: press a key to change the configuration.``
``---------------------------------------------------------
[X] 0: Set ADC trigger mode: Software.
[ ] 1: Set ADC trigger mode: ADTRG.
[ ] 2: Set ADC trigger mode: Timer TIOA.
[D] S: Enable/Disable sequencer.
[D] D: Enable/Disable to tranfer with DMA.
[D] P: Enable/Disable ADC power save mode.
=========================================================``


Tested with IAR and GCC (sram and ddram configuration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0' | Software trigger is selected, continuous converted value will be printed: ``Count:*  CH03:*mV  CH04:*mV  CH00:*mV  CH01:*mV  CH02:*mV`` | PASSED | PASSED
Press '1' | External trigger on rising edge of the ADTRG pin is selected, the converted value will be updated when triggered| PASSED | PASSED
Press '2' | Timer TIOA trigger is selected, continuous converted value will be printed if triggered  | PASSED | PASSED
Press 'S' | Enable/Disable sequencer, continuous converted value will be printed if triggered | PASSED | PASSED
Press 'D' | Enable/Disable to tranfer with DMA, continuous converted value will be printed if triggered | PASSED | PASSED
Press 'P' | Enable/Disable ADC power save mode, continuous converted value will be printed if triggered | PASSED | PASSED


# Log
------

## Current version
--------
 - v1.3

## History
--------
