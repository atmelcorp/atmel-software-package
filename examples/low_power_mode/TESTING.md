LOW_POWER_MODE EXAMPLE
============

# Objectives
------------
This example aims to test Low-power modes.


# Example Description
---------------------
The demonstration program offers methods to make the device enter low power
mode, users can also change the settings of clock and DDR.

Power consumptions could be measured by ammeters connected between the jumpers
of `VDDCORE` or `VDDBU`.


# Test
------
## Supported targets

* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAM9X60-EK
* SAM9X35-EK
* SAM9X25-EK
* SAM9G35-EK
* SAM9G25-EK
* SAM9G15-EK

## Setup

On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control
 
### VARIANTs

This program support both SRAM and DRAM variants. 

In DRAM variant, we run the code in SRAM while keep DRAM in self-refresh mode. 
In this way, we can reach a much lower power consumption. 
(Be careful, we need to disable DRAM access from all peripherals).

## Start the application

### VARIANT = DRAM
In the terminal window, the following text should appear (values depend on the
 board and chip used): 
 
```
 -- Low Power mode --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 0 -> Enter BackUp mode
 1 -> Enter Low Power mode
```

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
Press '0' | Enter Backup mode | PASSED | PASSED
Press WAKE_UP |	RomBOOT | PASSED | PASSED
Press '1' | Enter Low Power mode | PASSED | PASSED
Press '0' or '1'... | Select low power mode | PASSED | PASSED
Press 'a' or 'b'... | Set wake-up event | PASSED | PASSED
Press 't' | Waiting for event to exit the low power mode ... Leave low power mode | PASSED | PASSED
Press 'u' | Auto run all setting items with the selected event ... Leave low power mode | PASSED | PASSED

### VARIANT = SRAM

In the terminal window, the following text should appear (values depend on the
 board and chip used): 

```
 -- Low Power mode --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 0 -> Enter BackUp mode
 1 -> Enter Low Power mode
 A -> Init DDR
 B -> Write data in DDR
 C -> Check data in DDR
 D -> Set DDR self-refresh mode and isolate Pads
 E -> Reset DDR to normal mode and reconnect Pads
```

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
Press '0' | Enter Backup mode | PASSED | PASSED
Press WAKE_UP |	RomBOOT | PASSED | PASSED
Press '1' | Enter Low Power mode | PASSED | PASSED
Press '0' or '1'... | Select low power mode | PASSED | PASSED
Press 'a' or 'b'... | Set wake-up event | PASSED | PASSED
Press 't' | Waiting for event to exit the low power mode ... Leave low power mode | PASSED | PASSED
Press 'u' | Auto run all setting items with the selected event ... Leave low power mode | PASSED | PASSED
Press 'A' | Init DDR ... | PASSED | PASSED
Press 'B' | Write data into DDR ... end of init | PASSED | PASSED
Press 'C' | Verify data in DDR` ... `data OK | PASSED | PASSED
Press 'D' | Set DDR into self-refresh | PASSED | PASSED
Press 'E' | Out of DDR Self refresh state | PASSED | PASSED
Press 'D' | Set DDR into self-refresh | PASSED | PASSED
Press '1' | Enter Low Power mode | PASSED | PASSED
Press '8' | Select low power mode | PASSED | PASSED
Press 'a' | Set wake-up event | PASSED | PASSED
Press 't' | Waiting for event to exit the low power mode ... Leave low power mode | PASSED | PASSED
Press 'C' | Verify data in DDR` ... `data OK | PASSED | PASSED


# Note:
-------
 * Some DDR related operations are omitted while running out of DDR.
 * The battery should be mounted and 'Force Power UP' jumper should be opened to support the BackUp mode correctly.
 * There are two ULP modes for SAMA5D2 while only one ULP mode for SAMA5D4.
 * The JTAG connection is lost with ULP1 or BackUp mode.
 * The JTAG/SWD speed should be set to adaptive on sam9x60 sram project, because of the processor run with slow clock when switch mck to slck.
 * The GDB adaptive command: JLinkGDBServer -select USB -device arm9 -if JTAG -speed adaptive.
 * Waking up from ulp0_512Hz mode with PB_USER button may take 15 seconds and even much longer for sama5d2-xplained.
 * Need 37ms power down 3V3 after setting SHDN pin low on sama5d3-ek/sam9xx5-ek boards, the processor will go on to print "enter backup failed", it not really means the backup failed. If D2 LED power-off, means successful backup.
 * SAM9XX5-EK only support variant ddram, because of 32-Kbyte of sram is too small to load the sram binary.