POWER_COMSUMPTION_PLL EXAMPLE
============

# Objectives
------------
This example aims to test PMC (Power Management Controller).


# Example Description
---------------------
The demonstration program offers methods to change the settings of Audio PLL,
UPLL and PLLA.

Power consumptions could be measured by ammeters connected between the jumpers
of `VDDCORE` or `VDDBU`.


# Test
------

## Supported targets
--------------------

* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-XPLAINED
* SAMA5D3-EK
* SAMA5D4-XPLAINED
* SAMA5D4-EK
* SAM9XX5-EK

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 38400 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control

## Start the application
------------------------

* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- PLL consumption measurement xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select main clock as MCK
 Select an option :
 ############################
 1 -> Disable AUDIOPLL
 2 -> AUDIOPLL 660 MHz
 3 -> AUDIOPLL 696 MHz
 4 -> AUDIOPLL 720 MHz
 5 -> AUDIOPLL 744 MHz
 ############################
 6 -> Disable UPLL
 7 -> Enable  UPLL
 ############################
 8 -> Disable PLLA
 9 -> PLLA =   408 MHz
 0 -> PLLA =   600 MHz
 a -> PLLA =   792 MHz
 b -> PLLA =   996 MHz
 c -> PLLA =  1200 MHz
 ############################
 =>
```

```
Note:
 * while running out of DDR, changing clock is not permitted.
 * there's no audio clock in SAMA5D4x chips.
 * change PLLA might cause some unreadable code on the console.
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1' | Print `Disable AUDIOPLL` on screen | PASSED | PASSED
Press '2' | Print `f_vco = 660 MHz, f_pmc = f_vco/7` on screen | PASSED | PASSED
Press '3' | Print `f_vco = 696 MHz, f_pmc = f_vco/7` on screen | PASSED | PASSED
Press '4' | Print `f_vco = 720 MHz, f_pmc = f_vco/7` on screen | PASSED | PASSED
Press '5' | Print `f_vco = 744 MHz, f_pmc = f_vco/7` on screen | PASSED | PASSED
Press '6' | Print `Disable UPLL` on screen | PASSED | PASSED
Press '7' | Print `Enable UPLL` on screen | PASSED | PASSED
Press '8' | Print `Disable PLLA` on screen | PASSED | PASSED
Press '9' | Print `PLLA = 408 MHz` on screen | PASSED | PASSED
Press '0' | Print `PLLA = 600 MHz` on screen | PASSED | PASSED
Press 'a' | Print `PLLA = 792 MHz` on screen | PASSED | PASSED
Press 'b' | Print `PLLA = 996 MHz` on screen | PASSED | PASSED
Press 'c' | Print `PLLA = 1200 MHz` on screen | PASSED | PASSED

