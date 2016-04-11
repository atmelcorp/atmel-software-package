AES EXAMPLE
============

# Objectives
------------
This example aims to encryption and decryption data with the Advanced
Encryption Standard (AES).

# Example Description
---------------------
This example shows how to configure AES in encryption and decryption mode. In
encryption mode, it encrypts plain text in one of the ECB/CBC/OFB/CFB/CTR
modes.
Programmable key mode with processing using with or without DMA support.
In decryption mode, it decrypts cipher data generated from encryption mode,
and compares the result against the initial plain value.

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

## Start the application (SAMA5D2-XPLAINED)
--------

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0','5','m','p' | Electronic Code Book, 128bit, manual| PASSED | PASSED
Press '1','5','m','p' |  Cipher Block Chaining, 128bit, manual| PASSED | PASSED
Press '2','5','m','p' | Output Feedback, 128bit, manual| PASSED | PASSED
Press '3','5','m','p' | Cipher Feedback, 128bit, manual| PASSED | PASSED
Press '4','5','m','p' | 16-bit internal Counter, 128bit, manual| PASSED | PASSED
Press '0','6','a','p' | Electronic Code Book, 192bit, auto| PASSED | PASSED
Press '1','6','a','p' |  Cipher Block Chaining, 192bit, auto| PASSED | PASSED
Press '2','6','a','p' | Output Feedback, 192bit, auto| PASSED | PASSED
Press '3','6','a','p' | Cipher Feedback, 192bit, auto| PASSED | PASSED
Press '4','6','a','p' | 16-bit internal Counter, 192bit, auto| PASSED | PASSED
Press '0','7','d','p' | Electronic Code Book, 256bit, dma| PASSED | PASSED
Press '1','7','d','p' |  Cipher Block Chaining, 256bit, dma| PASSED | PASSED
Press '2','7','d','p' | Output Feedback, 256bit, dma| PASSED | PASSED
Press '3','7','d','p' | Cipher Feedback, 256bit, dma| PASSED | PASSED
Press '4','7','d','p' | 16-bit internal Counter, 256bit, dma| PASSED | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
