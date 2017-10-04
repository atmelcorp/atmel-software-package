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
On the board:
 - SAMA5D2-XPLAINED: Connect PB9 (pin 1 on J21) to PD31 (ADTRG) (pin 33 on J17)
 - SAMA5D4-XPLAINED: Connect PE23 (pin 1 on J18) to PE31 (ADTRG) (pin 34 on J15)
 - SAMA5D4-EK: Connect to PE23 to PE31 (ADTRG)
 - SAMA5D3-XPLAINED: Connect PD15 (pin 8 on J21) to PD19 (ADTRG) (pin 6 on J21)
 - SAMA5D3-EK: Connect to PD15 (pin 32 on J3) to PD19 (ADTRG) (pin 34 on J3)
 - SAM9XX5-EK: Connect to PA8 (pin 21 on J1) to PB18 (ADTRG) (pin 10 on J3)

On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED,SAMA5D3-XPLAINED,SAMA5D3-EK,SAMA5D4-XPLAINED,SAMA5D4-EK)
--------
The following menu will be displayed in the terminal window.

``=========================================================
Menu: press a key to change the configuration.``
``---------------------------------------------------------
[X] 0: Set ADC trigger mode: Software.
[ ] 1: Set ADC trigger mode: ADTRG.
[ ] 2: Set ADC trigger mode: Timer TIOA.
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
Press 'D' | Enable/Disable to tranfer with DMA, continuous converted value will be printed if triggered | PASSED | PASSED
Press 'P' | Enable/Disable ADC power save mode, continuous converted value will be printed if triggered | PASSED | PASSED

