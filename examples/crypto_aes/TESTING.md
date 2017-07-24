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
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
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

AES Menu:
Press [0|1|2|3|4] to set the Mode of Operation
   0: Electronic Code Book    [ ]
   1: Cipher Block Chaining   [ ]
   2: Output Feedback         [ ]
   3: Cipher Feedback         [X]
   4: 16-bit internal Counter [ ]
Press [5|6|7] to select key size
   5: 128 bits[ ]  6: 192 bits[ ]  7: 256 bits[X]
Press [m|a|d] to set Start Mode
   m: MANUAL_START[ ]  a: AUTO_START[ ]  d: DMA[X]
   p: Begin the encryption/decryption process
   p: Begin the encryption/decryption process

AES Cipher Feedback Menu:
Press [0|1|2|3|4] to set the cipher data size
   0: 128 bits [X]
   1: 64 bits [ ]
   2: 32 bits [ ]
   3: 16 bits [ ]
   4: 8 bits [ ]

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0','5','m','p' | Electronic Code Book, 128bit, manual| PASSED | PASSED
Press '1','5','m','p' |  Cipher Block Chaining, 128bit, manual| PASSED | PASSED
Press '2','5','m','p' | Output Feedback, 128bit, manual| PASSED | PASSED
Press '3', '0' '5','m','p' | Cipher Feedback 128bit, 128bit, manual| PASSED | PASSED
Press '3', '1' '5','m','p' | Cipher Feedback 64bit, 128bit, manual| PASSED | PASSED
Press '3', '2' '5','m','p' | Cipher Feedback 32bit, 128bit, manual| PASSED | PASSED
Press '3', '3' '5','m','p' | Cipher Feedback 16bit, 128bit, manual| PASSED | PASSED
Press '3', '4' '5','m','p' | Cipher Feedback 8bit, 128bit, manual| PASSED | PASSED
Press '4','5','m','p' | 16-bit internal Counter, 128bit, manual| PASSED | PASSED
Press '0','6','a','p' | Electronic Code Book, 192bit, auto| PASSED | PASSED
Press '1','6','a','p' |  Cipher Block Chaining, 192bit, auto| PASSED | PASSED
Press '2','6','a','p' | Output Feedback, 192bit, auto| PASSED | PASSED
Press '3','0','6','a','p' | Cipher Feedback 128, 192bit, auto| PASSED | PASSED
Press '3','1','6','a','p' | Cipher Feedback 64, 192bit, auto| PASSED | PASSED
Press '3','2','6','a','p' | Cipher Feedback 32, 192bit, auto| PASSED | PASSED
Press '3','3','6','a','p' | Cipher Feedback 16, 192bit, auto| PASSED | PASSED
Press '3','4','6','a','p' | Cipher Feedback 8, 192bit, auto| PASSED | PASSED
Press '4','6','a','p' | 16-bit internal Counter, 192bit, auto| PASSED | PASSED
Press '0','7','d','p' | Electronic Code Book, 256bit, dma| PASSED | PASSED
Press '1','7','d','p' |  Cipher Block Chaining, 256bit, dma| PASSED | PASSED
Press '2','7','d','p' | Output Feedback, 256bit, dma| PASSED | PASSED
Press '3','7','d','p' | Cipher Feedback, 256bit, dma| PASSED | PASSED
Press '3','0','7','d','p' | Cipher Feedback 128, 256bit, dma| PASSED | PASSED
Press '3','1','7','d','p' | Cipher Feedback 64, 256bit, dma| PASSED | PASSED
Press '3','2','7','d','p' | Cipher Feedback 32, 256bit, dma| PASSED | PASSED
Press '3','3','7','d','p' | Cipher Feedback 16, 256bit, dma| PASSED | PASSED
Press '3','4','7','d','p' | Cipher Feedback 6, 256bit, dma| PASSED | PASSED
Press '4','7','d','p' | 16-bit internal Counter, 256bit, dma| PASSED | PASSED
