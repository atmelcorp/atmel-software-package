QSPI_XIP EXAMPLE
================

# Objectives
------------
This examples demonstrates how to setup the QSPI Flash in XIP mode to execute
code from QSPI flash.

# Example Description
---------------------
This example writes the getting-started example into flash via SPI and enables quad
mode spi to read code and to execute from it.

# Test
------
## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 57600 bauds (for sama5d2-xplained)
 - 115200 bauds (for sama5d4-xplained)
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

This package can be used with SAMA5D2-XULT with QSPI memory onboard.

## Start the application (SAMA5D2-XPLAINED)
-------------------------------------------
In the terminal window, the following text should appear (values depend on the
board and chip used):
```
-- QSPI XIP Example  xxx --
-- SAMxxxxx-xx
-- Compiled: xxx xx xxxx xx:xx:xx --
-D- ../../drivers/peripherals/twi.c:123 twi_configure_master(400000)
-D- ../../drivers/peripherals/twi.c:153 twi: CKDIV=0 CLDIV=CHDIV=100 -> TWI Clock 408867Hz
-D- ../../drivers/peripherals/twi.c:158 twi: HOLD=22 -> Holding Time 301ns
-D- ../../drivers/power/act8945a.c:458 Charge Level: 450mA
-D- ../../examples/qspi_xip/main.c:198 Initializing QSPI drivers...
-D- ../../examples/qspi_xip/main.c:200 QSPI drivers initialized.
-D- ../../examples/qspi_xip/main.c:203 QSPI baudrate set to 41500000Hz
-D- ../../examples/qspi_xip/main.c:205 Configuring QSPI Flash...
-D- ../../drivers/memories/qspiflash.c:614 Trying protocol 0 opcode 0x9f
-D- ../../drivers/memories/qspiflash.c:629 Found memory with JEDEC ID 0x001a20c2.
-D- ../../drivers/memories/qspiflash.c:649 Found supported memory with JEDEC ID 0x001a20c2 (MX25L51245G).
-D- ../../drivers/memories/qspiflash.c:331 QSPI Flash: Macronix Quad mode already enabled
-D- ../../examples/qspi_xip/main.c:209 QSPI Flash configured.
-I- Data at the beginning of QSPI: e59ff018 e59ff018 e59ff018 e59ff018
-I- Valid application already in QSPI, will run it using QSPI XIP
-I- Starting continuous read mode to enter in XIP mode
-- Getting Started Example 1.2
[...]
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Nothing to do | LED Blinks | PASSED | PASSED
'0' or '1' or '2' or '3' | Enable/disable LED color | PASSED | PASSED
's' | Disable TC | Output only '0' | PASSED
'b' | Enable TC | Output numbers betwen 0 and 2 | PASSED


# Log
-----
## Current version
------------------
 - v1.3

## History
----------
