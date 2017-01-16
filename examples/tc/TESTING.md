TC_CAPTURE_WAVEFORM EXAMPLE
===========================

# Objectives
------------
This example aims to test the TC capture peripheral.

# Example Description
---------------------
This example shows how to configure TC in waveform and capture mode.
In capture mode, pulse signal is set as an input, RA and RB will be loaded when
programmed event occurs. When TC interrupt happens, we could read RA and RB
value for calculating pulse frequency and pulse number be increased. The current
pulse frequency and total pulse number is output on DBGU.

The code can be roughly broken down as follows:
 - Select pre-defined waveform frequency and duty cycle to be generated.
 - Configure TC channel 1 as waveform output.
 - Configure TC channel 2 as capture input.
 - Configure capture Register A be loaded when rising edge of TIOA occurs.
 - Configure capture Register B be loaded when failing edge of TIOA occurs.
 - Configure an interrupt for TC and enable the RB load interrupt.
 - 'c' start capture.
 - 's' will stop capture,and dump the informations what have been captured.

# Test
------
## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

### SAMA5D2-XPLAINED
--------------------
Connect EXP_PA19 (J21 pin 2) and EXP_PB22 (J22 pin 6) on the board.

### SAMA5D4-EK
--------------
Connect USBC_EN5V_PE12 (J19 pin 44) and MCI1_PWR_PE15 (J19 pin 47) on the board.

### SAMA5D4-XPLAINED
--------------------
Connect EXP_PE12 (J15 pin 9) and EXP_PE15 (J18 pin 6) on the board.

### SAMA5D3-EK
--------------
Connect PE27 (J22 pin 11) and PC12 (J2 pin 29) on the board.

### SAMA9XX5-EK
---------------
Connect PA22 (J1 pin 18) and PA23 (J1 pin 20) on the board.

### SAME70-XPLAINED
-------------------
Connect PA0 (J401/EXT_1 pin 7) and PD21 (J401/EXT_1 pin 16) on the board.

### SAMV71-XPLAINED
-------------------
Connect PA0 (J401/EXT_1 pin 7) and PD21 (J401/EXT_1 pin 16) on the board.

## Start the application
------------------------
In the terminal window, the following text should appear (values depend on the
board and chip used):
```
-- TC Capture Waveform Example  xxx --
-- SAMxxxxx-xx
-- Compiled: xxx xx xxxx xx:xx:xx --
```

```
Menu :
  -----
  Output waveform property:
  0: Set Frequency =  80 Hz, Duty Cycle = 30%
  1: Set Frequency =  180 Hz, Duty Cycle = 50%
  2: Set Frequency =  400 Hz, Duty Cycle = 75%
  3: Set Frequency =  500 Hz, Duty Cycle = 80%
  4: Set Frequency = 2000 Hz, Duty Cycle = 55%
  -------------------------------------------
  c: Capture waveform from TC capture channel
  s: Stop capture and display informations what have been captured
  h: Display menu
  ------
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0' 'c' | Capture waveform | Captured wave frequency = 80 Hz, Duty cycle = 30% | PASSED
Press '1' 'c' | Capture waveform | Captured wave frequency = 180 Hz, Duty cycle = 50% | PASSED
Press '2' 'c' | Capture waveform | Captured wave frequency = 400 Hz, Duty cycle = 75% | PASSED
Press '3' 'c' | Capture waveform | Captured wave frequency = 500 Hz, Duty cycle = 80% | PASSED
Press '4' 'c' | Capture waveform | Captured wave frequency = 2000 Hz, Duty cycle = 55% | PASSED

--------------------------------------------------------------------------------------------------
# For SAMA5D2-XLUT and SAMV71-XLUT
Press '0' 'c' 'd'| Capture waveform with DMA| Captured wave frequency = 80 Hz, Duty cycle = 30% | PASSED
Press '1' 'c' 'd'| Capture waveform with DMA| Captured wave frequency = 180 Hz, Duty cycle = 50% | PASSED
Press '2' 'c' 'd'| Capture waveform with DMA| Captured wave frequency = 400 Hz, Duty cycle = 75% | PASSED
Press '3' 'c' 'd'| Capture waveform with DMA| Captured wave frequency = 500 Hz, Duty cycle = 80% | PASSED
Press '4' 'c' 'd'| Capture waveform with DMA| Captured wave frequency = 2000 Hz, Duty cycle = 55% | PASSED

Press 'h' | Print the menu | Display the menu | PASSED

