TEST-PIO EXAMPLE
================

# Objectives
------------
This example aims to test automatically the pio module.


# Example Description
---------------------
This example does automatic test of the PIO features.

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

The test output follows a JUnit XML format for traces.

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 115200 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application.
* Record the traces


## Start the application
------------------------

__Pins for SAMA5D2 Xplained Ultra:__
Connect CANTX0 (PC10 / pin 8 on J9) to CANRX0 PC11/pin 7 on J9)

__Pins for SAMA5D27_SOM1_EK:__
Connect PD6 (pin 5 on ISC) to PD7 (pin 6 on ISC)

__Pins for SAMA5D3 Xplained Ultra:__
Connect CANTX0 (PD15 / pin 8 on J21) to CANRX0 PD14/pin 7 on J21)

__Pins for SAMA5D4 Xplained Ultra:__
Connect PB15 (pin 8 on J8) to PB14 (pin 7 on J8)

__Pins for SAMA5D4 Evaluation Kit:__
Connect PE26 (pin 59 on EXPJ19) to PE27 (pin 60 on EXPJ19)

__Pins for SAM9X5 Evaluation Kit:__
Connect PD16 (pin 37 on J22) to PD17 (pin 38 on J22)

__Pins for SAME70 Xplained Ultra:__
Connect D7 PA2 (pin 8 on J503) to D6 PC19 (pin 7 on J503)

__Pins for SAMV71 Xplained Ultra:__
Connect D7 PA2 (pin 8 on J503) to D6 PC19 (pin 7 on J503)
