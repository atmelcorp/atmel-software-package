CRYPTO_TDES EXAMPLE
============

# Objectives
------------
This example aims to configure TDES in encryption and decryption modes. the
Triple Data Encryption Algorithm (TDES) peripheral  encrypts and decrypts a
test buffer in Electronic Code Book (ECB), Cipher Block Chaining (CBC), Output
Feedback (OFB), and Cipher Feedback (CFB) modes, and checks the decrypted data
against the expected result.

# Example Description
---------------------
This example shows how to configure TDES in encryption and decryption modes. In
encryption mode, it encrypts plain text in one of the ECB/CBC/OFB/CFB modes.
Programmable key mode with Single DES, Triple DES or XTEA encryption, with or
without DMA support.
In decryption mode, it decrypts cipher data generated at encryption step, and
prints the result, which should match the initial plain value.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
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
Press '0','s','m','p' | Electronic Code Book, single, manual | PASSED | PASSED
Press '1','s','m','p' | Cipher Block Chaining, single, manual | PASSED | PASSED
Press '2','s','m','p' | Output Feedback, single, manual | PASSED | PASSED
Press '3','0, 's','m','p' | Cipher Feedback, 64bit, single, manual | PASSED | PASSED
Press '3','1, 's','m','p' | Cipher Feedback, 32bit, single, manual | PASSED | PASSED
Press '3','2, 's','m','p' | Cipher Feedback, 16bit, single, manual | PASSED | PASSED
Press '3','3, 's','m','p' | Cipher Feedback, 8bit, single, manual | PASSED | PASSED
Press '0','t','a','p' | Electronic Code Book, TRIPLE, auto | PASSED | PASSED
Press '1','t','a','p' | Cipher Block Chaining, TRIPLE, auto | PASSED | PASSED
Press '2','t','a','p' | Output Feedback, TRIPLE, auto | PASSED | PASSED
Press '3','0','t','a','p' | Cipher Feedback, 64bit, TRIPLE, auto | PASSED | PASSED
Press '3','1','t','a','p' | Cipher Feedback, 32bit, TRIPLE, auto | PASSED | PASSED
Press '3','2','t','a','p' | Cipher Feedback, 16bit, TRIPLE, auto | PASSED | PASSED
Press '3','3','t','a','p' | Cipher Feedback, 8bit, TRIPLE, auto | PASSED | PASSED
Press '0','x','d','p' | Electronic Code Book, XTEA, dma | PASSED | PASSED
Press '1','x','d','p' | Cipher Block Chaining, XTEA, dma | PASSED | PASSED
Press '2','x','d','p' | Output Feedback, XTEA, dma | PASSED | PASSED
Press '3','0','x','a','p' | Cipher Feedback, 64bit, XTEA, dma | PASSED | PASSED
Press '3','1','x','a','p' | Cipher Feedback, 32bit, XTEA, dma | PASSED | PASSED
Press '3','2','x','a','p' | Cipher Feedback, 16bit, XTEA, dma | PASSED | PASSED
Press '3','3','x','a','p' | Cipher Feedback, 8bit, XTEA, dma | PASSED | PASSED
