PWM EXAMPLE
============

# Objectives
------------
This example aims to test PWM (Pulse Width Modulation Controller).


# Example Description
---------------------
This example demonstrates how to use PWM module.


# Test
------

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
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- PWM Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Menu :
  -------------------------------------------
  a: PWM operations for asynchronous channels
  d: PWM DMA operations with synchronous channels
  f: PWM fault mode initialize
  F: PWM fault mode clear and disable
  m: PWM 2-bit Gray Up/Down Counter for Stepper Motor
  o: PWM output override / dead time settings
  c: Capture waveform from TC capture channel
  h: Display menu
  -------------------------------------------
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Connect for capture | `sama5d2-xplained board:` Connect EXP/XPRO_PB5 (J20 pin 2) and EXP_PB22 (J22 pin 6); `sama5d4-ek board:` Connect EXP_PB28 (J19A pin 19) and USBC_EN5V_PE12 (J19C pin 44); `sama5d4-xplained board:` Connect EXP_PB11 (J15 pin 26) and EXP_PE12 (J15 pin 9) | N/A | N/A
Press 'c' | Print `Start capture, result will be dumped to console when finished.` on screen | PASSED | PASSED
Press 'a' | Print `-- PWM Channel 2 Duty cycle: 0% Signal Period: 20 ms--` ... `-- PWM Channel 2 Duty cycle: 42% Signal Period: 20 ms--` ... `Captured 32 pulses from TC capture channel:` `Captured[0] frequency =` ... `Captured[31] frequency = ` ... on screen | PASSED | PASSED
Press 'h' | Print the menu on screen | PASSED | PASSED
Press 'c' | Print `Start capture, result will be dumped to console when finished.` on screen | PASSED | PASSED
Press 'd' | Print `Captured 32 pulses from TC capture channel:`, `Captured[0] frequency =` ... `Captured[31] frequency = ` ... on screen | PASSED | PASSED
Press 'h' | Print the menu on screen | PASSED | PASSED
Press 'f' | initialize fault mode | PASSED | PASSED
Press 'F' | clear and disable fault mode | PASSED | PASSED
Press 'm' | test 2-bit gray mode | PASSED | PASSED
Press 'o' | Print `Input options:`, `0/1: override to 0/1`, `others: set dead-time` on screen | PASSED | PASSED
Press '0' | test override 0 | PASSED | PASSED
Press 'o' | Print `Input options:`, `0/1: override to 0/1`, `others: set dead-time` on screen | PASSED | PASSED
Press '1' | test override 1 | PASSED | PASSED
Press 'o' | Print `Input options:`, `0/1: override to 0/1`, `others: set dead-time` on screen | PASSED | PASSED
Press 'x' | test dead-time | PASSED | PASSED
Press 'h' | Print the menu on screen | PASSED | PASSED


# Log
------

## Current version
--------
 - v1.3

## History
--------
