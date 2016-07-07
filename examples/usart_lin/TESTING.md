USART_LIN EXAMPLE
============

# Objectives
------------
This example aims to test the LIN interface.

# Example Description
---------------------
This example demonstrates how to use the LIN peripheral.
The LIN interface is integrated in the FLEXCOM peripheral in SAMA5D2x
micro-controllers.

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
* Start the application (SAMA5D2-XPLAINED)
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- LIN Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Menu :
  ------
   P: [ ] Run Master PUBLISHER to Slave SUBSCRIBER
   S: [ ] Run Master SUBSCRIBER to Slave PUBLISHER
   I: [X] Master and Slave mode IGNORE
   Q: Stop demo and Quit
  ------
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'p' | Print `P: [X] Run Master PUBLISHER to Slave SUBSCRIBER`, `Rx Frame ... Node:1 Handle:0 Count:0001 [ 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x3` ... `Rx Frame ... Node:1 Handle:0 Count:0008 [ 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x3` ... on screen | PASSED | PASSED
Press 'i' | Print ... `I: [X] Master and Slave mode IGNORE` ... on screen | PASSED | PASSED
Press 's' | Print `S: [X] Run Master SUBSCRIBER to Slave PUBLISHER`, `Rx Frame ... Node:0 Handle:1 Count:0001 [ 0x38 0x37 0x36 0x35 0x34 0x33 0x32` ... `Rx Frame ... Node:0 Handle:1 Count:0011 [ 0x38 0x37 0x36 0x35 0x34 0x33 0x32` ... on screen | PASSED | PASSED
Press 'i' | Print ... `I: [X] Master and Slave mode IGNORE` ... on screen | PASSED | PASSED
Press 'q' | Print `End of demo` on screen | PASSED | PASSED

