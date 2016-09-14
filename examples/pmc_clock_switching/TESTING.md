PMC_CLOCK_SWITCHING EXAMPLE
============

# Objectives
------------
This example aims to test Low-power modes.


# Example Description
---------------------
This examples shows how to switch from a clock to another (PLLA, PLLUTMI, SLCK,
MCK) or change divider, also shows how to change SLCK (32K OSC or internal RC).

# Test
------

## Supported targets
--------------------

* SAMA5D2-XPLAINED
* SAMA5D3-XPLAINED
* SAMA5D3-EK
* SAMA5D4-XPLAINED
* SAMA5D4-EK
* SAM9XX5-EK

## Setup
--------


* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 38400 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- Clock switching Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 MCK = 166 Mhz
 PLLA = 498 Mhz
 Processor clock = 498 Mhz
 Select an option :
 ###############################
 1 -> Switch to PLLA
 2 -> Switch to UPLL
 3 -> Switch to main clock
 4 -> Switch to slow clock
 -------------------------------
```
`Note: while running out of DDR, changing clock is not permitted.`

Tested with IAR and GCC (sram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1' | Print `Switch to PLLA`, `MCK = 166 Mhz`, `PLLA = 498 Mhz`, `Processor clock = 498 Mhz` on screen | PASSED | PASSED
Press '2' | Print `MCK = 160 Mhz`, `PLLA = 0 Mhz`, `Processor clock = 480 Mhz` on screen | PASSED | PASSED
Press '3' | Print `Switch to main clock`, `MCK = 12 Mhz`, `PLLA = 0 Mhz`, `Processor clock = 12 Mhz` on screen | PASSED | PASSED
Press '4' | Print `Switch to slow clock`, `It is too slow to output info on serial port`, `So stay at this speed for a moment only`, `Back to PLLA`, `MCK = 166 Mhz`, `PLLA = 498 Mhz`, `Processor clock = 498 Mhz` on screen | PASSED | PASSED

