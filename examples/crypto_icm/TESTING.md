CRYPTO_ICM EXAMPLE
============

# Objectives
------------
This example aims to shows how to use the Integrity Check Monitor (ICM)
peripheral.

# Example Description
---------------------
The ICM Example integrates two modes of operation. The first one is used to
hash a list of memory regions and save the digests to memory (ICM Hash Area).
The second operation mode is an active monitoring of the memory.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Check Hash result for region 1 | compare the result | MATCH | PASSED
Check Hash result for region 2 | compare the result | MATCH | PASSED
Check Hash result for region 3 | compare the result | MATCH | PASSED
Change context in region 0 | region 0 digest mismatch | MISMATCH | PASSED
Change context in region 1 | region 1 digest mismatch | MISMATCH | PASSED
Change context in region 2 | region 2 digest mismatch | MISMATCH | PASSED
Change context in region 3 | region 3 digest mismatch | MISMATCH | PASSED
