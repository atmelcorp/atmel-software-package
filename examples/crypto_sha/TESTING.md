CRYPTO_SHA EXAMPLE
============

# Objectives
------------
This example aims to encryption and decryption data with the he Secure Hash
Algorithm (SHA) peripheral.

# Example Description
---------------------
This example shows how to configure SHA1/SH256/SHA384/SHA512/SHA224 mode and
transfer message with one block, multi-blocks and long message with or without
DMA.

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
Press '0','o','m','p' | SHA1, single block, manual | PASSED | PASSED
Press '1','o','m','p' | SHA256, single block, manual | PASSED | PASSED
Press '2','o','m','p' | SHA384, single block, manual | PASSED | PASSED
Press '3','o','m','p' | SHA512, single block, manual | PASSED | PASSED
Press '4','o','m','p' | SHA224, single block, manual | PASSED | PASSED
Press '0','t','a','p' | SHA1, multi block, auto | PASSED | PASSED
Press '1','t','a','p' | SHA256, multi block, auto | PASSED | PASSED
Press '2','t','a','p' | SHA384, multi block, auto | PASSED | PASSED
Press '3','t','a','p' | SHA512, multi block, auto | PASSED | PASSED
Press '4','t','a','p' | SHA224, multi block, auto | PASSED | PASSED
Press '0','l','d','p' | SHA1, long-msg, dma | PASSED | PASSED
Press '1','l','d','p' | SHA256, long-msg, dma | PASSED | PASSED
Press '2','l','d','p' | SHA384, long-msg, dma | PASSED | PASSED
Press '3','l','d','p' | SHA512, long-msg, dma | PASSED | PASSED
Press '4','l','d','p' | SHA224, long-msg, dma | PASSED | PASSED
