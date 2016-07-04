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

__Pins for SAMA5D2 Xplained Ultra:__
Connect CANTX0 (PC10 / pin 8 on J9) to CANRX0 PC11/pin 7 on J9)

__Pins for SAMA5D3 Xplained Ultra:__
Connect CANTX0 (PD15 / pin 8 on J21) to CANRX0 PD14/pin 7 on J21)

__Pins for SAMA5D4 Xplained Ultra:__
Connect PB15 (pin 8 on J8) to PB14 (pin 7 on J8)

__Pins for SAMA5D4 Evaluation Kit:__
Connect PE26 (pin 59 on EXPJ19) to PE27 (pin 60 on EXPJ19)
