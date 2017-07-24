AESB EXAMPLE
============

# Objectives
------------
This example aims to protect electronic data with Advanced Encryption Standard
Bridge (AESB).

# Example Description
---------------------
This example shows how to configure AESB to protect electronic data. The
Automatic Bridge mode, when the AESB block is connected between the system bus
and a DDR port, provides automatic encryption/decryption to/from a DDR port
without any action on the part of the user.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D4-EK
* SAMA5D4-XPLAINED

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
Transfer data to address of AESB IP scope | the data is ciphered on-the-fly | PASSED | PASSED
Read data from address of AESB IP scope | the data is deciphered on-the-fly | PASSED | PASSED
Read data from address outside of AESB IP scope | the data can not be deciphered | FAILED | PASSED

