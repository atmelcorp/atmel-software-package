RTT EXAMPLE
============

# Objectives
------------
This example aims to test RTT (Real-time Timer).


# Example Description
---------------------
This example demonstrates how to use the Real-Time Timer (RTT) peripheral.

The RTT enables timer and allows the user to set alarm.

# Test
------
## Supported targets
--------------------
* SAM9X60-EK

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

## Start the application
------------------------

* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- RTT Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Menu :
    Time: xx
Menu:
 r - Reset timer
 s - Set alarm
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'r' | reset timer | PASSED | PASSED
Press 's' | Print `Enter alarm time (recommend > current timer):` on screen then set the alarm | PASSED | PASSED
Press alarm time | Print 'xx' on screen to set the alarm time | PASSED | PASSED
Waiting | until '!!! ALARM !!!' on screen| PASSED | PASSED
Press 'c' | Print `Clear alarm notification` on screen | PASSED | PASSED


