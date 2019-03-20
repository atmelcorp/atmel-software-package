CRYPTO_SHA EXAMPLE
============

# Objectives
------------
This example aims to encryption and decryption data with the Secure Hash
Algorithm (SHA) peripheral.

# Example Description
---------------------
This example shows how to configure SHA1/SHA224/SHA256/SHA384/SHA512 mode and
transfer message with one block, multi-blocks and long message with or without
DMA.

# Test
------
## Supported targets
--------------------
* SAM9X60-EK
* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
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

Tested with IAR<sup>®</sup> and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0','o','p','s' | SHA1, single block, polling | Digest successfully verified | PASSED
Press '1','o','p','s' | SHA224, single block, polling | Digest successfully verified | PASSED
Press '2','o','p','s' | SHA256, single block, polling | Digest successfully verified | PASSED
Press '3','o','p','s' | SHA384, single block, polling | Digest successfully verified | PASSED
Press '4','o','p','s' | SHA512, single block, polling | Digest successfully verified | PASSED
Press '0','t','d','s' | SHA1, multi block, dma | Digest successfully verified | PASSED
Press '1','t','d','s' | SHA224, multi block, dma | Digest successfully verified | PASSED
Press '2','t','d','s' | SHA256, multi block, dma | Digest successfully verified | PASSED
Press '3','t','d','s' | SHA384, multi block, dma | Digest successfully verified | PASSED
Press '4','t','d','s' | SHA512, multi block, dma | Digest successfully verified | PASSED
Press '0','l','d','s' | SHA1, long-msg, dma | Digest successfully verified | PASSED
Press '1','l','d','s' | SHA224, long-msg, dma | Digest successfully verified | PASSED
Press '2','l','d','s' | SHA256, long-msg, dma | Digest successfully verified | PASSED
Press '3','l','d','s' | SHA384, long-msg, dma | Digest successfully verified | PASSED
Press '4','l','d','s' | SHA512, long-msg, dma | Digest successfully verified | PASSED

Press 'f'

```
SHA1 one-block message polling passed
SHA1 multi-block message polling passed
SHA1 long message polling passed
SHA224 one-block message polling passed
SHA224 multi-block message polling passed
SHA224 long message polling passed
SHA256 one-block message polling passed
SHA256 multi-block message polling passed
SHA256 long message polling passed
SHA384 one-block message polling passed
SHA384 multi-block message polling passed
SHA384 long message polling passed
SHA512 one-block message polling passed
SHA512 multi-block message polling passed
SHA512 long message polling passed
SHA1 one-block message dma passed
SHA1 multi-block message dma passed
SHA1 long message dma passed
SHA224 one-block message dma passed
SHA224 multi-block message dma passed
SHA224 long message dma passed
SHA256 one-block message dma passed
SHA256 multi-block message dma passed
SHA256 long message dma passed
SHA384 one-block message dma passed
SHA384 multi-block message dma passed
SHA384 long message dma passed
SHA512 one-block message dma passed
SHA512 multi-block message dma passed
SHA512 long message dma passed
TEST SUCCESS 
```