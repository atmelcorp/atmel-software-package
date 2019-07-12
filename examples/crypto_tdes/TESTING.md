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

    TDES menu:
    Press [s|t|x] to set tdesd.cfg.algorithm for encryption/decryption
       s: SINGLE[X] t: TRIPLE[ ] x: XTEA[ ]
    Press [k] set key algorithm (three key or two key mode, no need for DES)
       Three key[X] Two key[ ]
    Press [0|1|2|3] to set the Mode of Operation
       0: Electronic Code Book    [X]
       1: Cipher Block Chaining   [ ]
       2: Output Feedback         [ ]
       3: Cipher Feedback         [ ]
    Press [m|a|d] to set Start Mode
       m: MANUAL_START[X] a: AUTO_START[ ] d: DMA[ ]
       p: Begin the encryption/decryption process
       f: Full test of all TDES modes
       h: Display this menu

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

press 'f'
```
ECB single two key auto start passed
CBC single three key auto start passed
OFB single three key auto start passed
CFBS_64 single three key auto start passed
CFBS_32 single three key auto start passed
CFBS_16 single three key auto start passed
CFBS_8 single three key auto start passed
ECB single three key auto start passed
CBC single two key auto start passed
OFB single two key auto start passed
CFBS_64 single two key auto start passed
CFBS_32 single two key auto start passed
CFBS_16 single two key auto start passed
CFBS_8 single two key auto start passed
ECB triple two key auto start passed
CBC triple three key auto start passed
OFB triple three key auto start passed
CFBS_64 triple three key auto start passed
CFBS_32 triple three key auto start passed
CFBS_16 triple three key auto start passed
CFBS_8 triple three key auto start passed
ECB triple three key auto start passed
CBC triple two key auto start passed
OFB triple two key auto start passed
CFBS_64 triple two key auto start passed
CFBS_32 triple two key auto start passed
CFBS_16 triple two key auto start passed
CFBS_8 triple two key auto start passed
ECB xtea two key auto start passed
CBC xtea two key auto start passed
OFB xtea two key auto start passed
CFBS_64 xtea two key auto start passed
CFBS_32 xtea two key auto start passed
CFBS_16 xtea two key auto start passed
CFBS_8 xtea two key auto start passed
ECB single two key dma passed
CBC single three key dma passed
OFB single three key dma passed
CFBS_64 single three key dma passed
CFBS_32 single three key dma passed
CFBS_16 single three key dma passed
CFBS_8 single three key dma passed
ECB single three key dma passed
CBC single two key dma passed
OFB single two key dma passed
CFBS_64 single two key dma passed
CFBS_32 single two key dma passed
CFBS_16 single two key dma passed
CFBS_8 single two key dma passed
ECB triple two key dma passed
CBC triple three key dma passed
OFB triple three key dma passed
CFBS_64 triple three key dma passed
CFBS_32 triple three key dma passed
CFBS_16 triple three key dma passed
CFBS_8 triple three key dma passed
ECB triple three key dma passed
CBC triple two key dma passed
OFB triple two key dma passed
CFBS_64 triple two key dma passed
CFBS_32 triple two key dma passed
CFBS_16 triple two key dma passed
CFBS_8 triple two key dma passed
ECB xtea two key dma passed
CBC xtea two key dma passed
OFB xtea two key dma passed
CFBS_64 xtea two key dma passed
CFBS_32 xtea two key dma passed
CFBS_16 xtea two key dma passed
CFBS_8 xtea two key dma passed
TEST SUCCESS !

```