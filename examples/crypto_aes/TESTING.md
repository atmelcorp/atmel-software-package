AES EXAMPLE
============

# Objectives
------------
This example aims to encryption and decryption data with the Advanced
Encryption Standard (AES).

# Example Description
---------------------
This example shows how to configure AES in encryption and decryption mode. In
encryption mode, it encrypts plain text in one of the ECB/CBC/OFB/CFB/CTR/GCM/XTS
modes.
Programmable key mode with processing using with or without DMA support.
In decryption mode, it decrypts cipher data generated from encryption mode,
and compares the result against the initial plain value.

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

    AES Menu: (without GCM/XTS mode)
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
        f: Full test for all AES mode
        h: Display this menu
    
    AES Menu: (with GCM/XTS mode)
    Press [0|1|2|3|4|5|6] to set the Mode of Operation
        0: Electronic5|6] Code Book    [ ]
        1: Cipher Block Chaining   [ ]
        2: Output Feedback         [ ]
        3: Cipher Feedback         [X]
        4: 16-bit internal Counter [ ]
        5: Galois/Counter Mode     [ ]
        6: XEX-Based Tweaked-Code  [ ]
    Press [7|8|9] to select key size
        7: 128 bits[ ]  8: 192 bits[ ]  9: 256 bits[X]
    Press [m|a|d] to set Start Mode
        m: MANUAL_START[ ]  a: AUTO_START[ ]  d: DMA[X]
        p: Begin the encryption/decryption process
        f: Full test for all AES mode
        h: Display this menu
    
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
Press '0','7','m','p' | Electronic Code Book, key128, manual| PASSED | PASSED
Press '1','7','m','p' | Cipher Block Chaining, key128, manual| PASSED | PASSED
Press '2','7','m','p' | Output Feedback, 128bit, manual| PASSED | PASSED
Press '3', '0' '7','m','p' | Cipher Feedback 128bit, key128, manual| PASSED | PASSED
Press '3', '1' '7','m','p' | Cipher Feedback 64bit, key128, manual| PASSED | PASSED
Press '3', '2' '7','m','p' | Cipher Feedback 32bit, key128, manual| PASSED | PASSED
Press '3', '3' '7','m','p' | Cipher Feedback 16bit, key128, manual| PASSED | PASSED
Press '3', '4' '7','m','p' | Cipher Feedback 8bit, key128, manual| PASSED | PASSED
Press '4','7','m','p' | 16-bit internal Counter, key128, manual| PASSED | PASSED
Press '0','8','a','p' | Electronic Code Book, key192, auto| PASSED | PASSED
Press '1','8','a','p' | Cipher Block Chaining, key192, auto| PASSED | PASSED
Press '2','8','a','p' | Output Feedback, key192, auto| PASSED | PASSED
Press '3','0','8','a','p' | Cipher Feedback 128, key192, auto| PASSED | PASSED
Press '3','1','8','a','p' | Cipher Feedback 64, key192, auto| PASSED | PASSED
Press '3','2','8','a','p' | Cipher Feedback 32, key192, auto| PASSED | PASSED
Press '3','3','8','a','p' | Cipher Feedback 16, key192, auto| PASSED | PASSED
Press '3','4','8','a','p' | Cipher Feedback 8, key192, auto| PASSED | PASSED
Press '4','8','a','p' | 16-bit internal Counter, key192, auto| PASSED | PASSED
Press '0','9','d','p' | Electronic Code Book, key256, dma| PASSED | PASSED
Press '1','9','d','p' | Cipher Block Chaining, key256, dma| PASSED | PASSED
Press '2','9','d','p' | Output Feedback, key256, dma| PASSED | PASSED
Press '3','0','9','d','p' | Cipher Feedback 128, key256, dma| PASSED | PASSED
Press '3','1','9','d','p' | Cipher Feedback 64, key256, dma| PASSED | PASSED
Press '3','2','9','d','p' | Cipher Feedback 32, key256, dma| PASSED | PASSED
Press '3','3','9','d','p' | Cipher Feedback 16, key256, dma| PASSED | PASSED
Press '3','4','9','d','p' | Cipher Feedback 8, key256, dma| PASSED | PASSED
Press '4','9','d','p' | 16-bit internal Counter, key256, dma| PASSED | PASSED

AES without GCM/XTS

Press 'f'

    ECB key_size =128 manually passed
    CBC key_size =128 manually passed
    OFB key_size =128 manually passed
    CFBS_128 key_size =128 manually passed
    CFBS_64 key_size =128 manually passed
    CFBS_32 key_size =128 manually passed
    CFBS_16 key_size =128 manually passed
    CFBS_8 key_size =128 manually passed
    CTR key_size =128 manually passed
    ECB key_size =192 manually passed
    CBC key_size =192 manually passed
    OFB key_size =192 manually passed
    CFBS_128 key_size =192 manually passed
    CFBS_64 key_size =192 manually passed
    CFBS_32 key_size =192 manually passed
    CFBS_16 key_size =192 manually passed
    CFBS_8 key_size =192 manually passed
    CTR key_size =192 manually passed
    ECB key_size =256 manually passed
    CBC key_size =256 manually passed
    OFB key_size =256 manually passed
    CFBS_128 key_size =256 manually passed
    CFBS_64 key_size =256 manually passed
    CFBS_32 key_size =256 manually passed
    CFBS_16 key_size =256 manually passed
    CFBS_8 key_size =256 manually passed
    CTR key_size =256 manually passed
    ECB key_size =128 auto start passed
    CBC key_size =128 auto start passed
    OFB key_size =128 auto start passed
    CFBS_128 key_size =128 auto start passed
    CFBS_64 key_size =128 auto start passed
    CFBS_32 key_size =128 auto start passed
    CFBS_16 key_size =128 auto start passed
    CFBS_8 key_size =128 auto start passed
    CTR key_size =128 auto start passed
    ECB key_size =192 auto start passed
    CBC key_size =192 auto start passed
    OFB key_size =192 auto start passed
    CFBS_128 key_size =192 auto start passed
    CFBS_64 key_size =192 auto start passed
    CFBS_32 key_size =192 auto start passed
    CFBS_16 key_size =192 auto start passed
    CFBS_8 key_size =192 auto start passed
    CTR key_size =192 auto start passed
    ECB key_size =256 auto start passed
    CBC key_size =256 auto start passed
    OFB key_size =256 auto start passed
    CFBS_128 key_size =256 auto start passed
    CFBS_64 key_size =256 auto start passed
    CFBS_32 key_size =256 auto start passed
    CFBS_16 key_size =256 auto start passed
    CFBS_8 key_size =256 auto start passed
    CTR key_size =256 auto start passed
    ECB key_size =128 dma passed
    CBC key_size =128 dma passed
    OFB key_size =128 dma passed
    CFBS_128 key_size =128 dma passed
    CFBS_64 key_size =128 dma passed
    CFBS_32 key_size =128 dma passed
    CFBS_16 key_size =128 dma passed
    CFBS_8 key_size =128 dma passed
    CTR key_size =128 dma passed
    ECB key_size =192 dma passed
    CBC key_size =192 dma passed
    OFB key_size =192 dma passed
    CFBS_128 key_size =192 dma passed
    CFBS_64 key_size =192 dma passed
    CFBS_32 key_size =192 dma passed
    CFBS_16 key_size =192 dma passed
    CFBS_8 key_size =192 dma passed
    CTR key_size =192 dma passed
    ECB key_size =256 dma passed
    CBC key_size =256 dma passed
    OFB key_size =256 dma passed
    CFBS_128 key_size =256 dma passed
    CFBS_64 key_size =256 dma passed
    CFBS_32 key_size =256 dma passed
    CFBS_16 key_size =256 dma passed
    CFBS_8 key_size =256 dma passed
    CTR key_size =256 dma passed
    TEST SUCCESS !

TEST AES with GCM/XTS

Press 'f'

    ECB key_size =128 manually passed
    CBC key_size =128 manually passed
    OFB key_size =128 manually passed
    CFBS_128 key_size =128 manually passed
    CFBS_64 key_size =128 manually passed
    CFBS_32 key_size =128 manually passed
    CFBS_16 key_size =128 manually passed
    CFBS_8 key_size =128 manually passed
    CTR key_size =128 manually passed
    GCM iv_size =12 key_size =128 manually passed
    GCM iv_size =16 key_size =128 manually passed
    XTS key_size =128 manually passed
    ECB key_size =192 manually passed
    CBC key_size =192 manually passed
    OFB key_size =192 manually passed
    CFBS_128 key_size =192 manually passed
    CFBS_64 key_size =192 manually passed
    CFBS_32 key_size =192 manually passed
    CFBS_16 key_size =192 manually passed
    CFBS_8 key_size =192 manually passed
    CTR key_size =192 manually passed
    GCM iv_size =12 key_size =192 manually passed
    GCM iv_size =16 key_size =192 manually passed
    XTS key_size =192 manually passed
    ECB key_size =256 manually passed
    CBC key_size =256 manually passed
    OFB key_size =256 manually passed
    CFBS_128 key_size =256 manually passed
    CFBS_64 key_size =256 manually passed
    CFBS_32 key_size =256 manually passed
    CFBS_16 key_size =256 manually passed
    CFBS_8 key_size =256 manually passed
    CTR key_size =256 manually passed
    GCM iv_size =12 key_size =256 manually passed
    GCM iv_size =16 key_size =256 manually passed
    XTS key_size =256 manually passed
    ECB key_size =128 auto start passed
    CBC key_size =128 auto start passed
    OFB key_size =128 auto start passed
    CFBS_128 key_size =128 auto start passed
    CFBS_64 key_size =128 auto start passed
    CFBS_32 key_size =128 auto start passed
    CFBS_16 key_size =128 auto start passed
    CFBS_8 key_size =128 auto start passed
    CTR key_size =128 auto start passed
    GCM iv_size =12 key_size =128 auto start passed
    GCM iv_size =16 key_size =128 auto start passed
    XTS key_size =128 auto start passed
    ECB key_size =192 auto start passed
    CBC key_size =192 auto start passed
    OFB key_size =192 auto start passed
    CFBS_128 key_size =192 auto start passed
    CFBS_64 key_size =192 auto start passed
    CFBS_32 key_size =192 auto start passed
    CFBS_16 key_size =192 auto start passed
    CFBS_8 key_size =192 auto start passed
    CTR key_size =192 auto start passed
    GCM iv_size =12 key_size =192 auto start passed
    GCM iv_size =16 key_size =192 auto start passed
    XTS key_size =192 auto start passed
    ECB key_size =256 auto start passed
    CBC key_size =256 auto start passed
    OFB key_size =256 auto start passed
    CFBS_128 key_size =256 auto start passed
    CFBS_64 key_size =256 auto start passed
    CFBS_32 key_size =256 auto start passed
    CFBS_16 key_size =256 auto start passed
    CFBS_8 key_size =256 auto start passed
    CTR key_size =256 auto start passed
    GCM iv_size =12 key_size =256 auto start passed
    GCM iv_size =16 key_size =256 auto start passed
    XTS key_size =256 auto start passed
    ECB key_size =128 dma passed
    CBC key_size =128 dma passed
    OFB key_size =128 dma passed
    CFBS_128 key_size =128 dma passed
    CFBS_64 key_size =128 dma passed
    CFBS_32 key_size =128 dma passed
    CFBS_16 key_size =128 dma passed
    CFBS_8 key_size =128 dma passed
    CTR key_size =128 dma passed
    GCM iv_size =12 key_size =128 dma passed
    GCM iv_size =16 key_size =128 dma passed
    XTS key_size =128 dma passed
    ECB key_size =192 dma passed
    CBC key_size =192 dma passed
    OFB key_size =192 dma passed
    CFBS_128 key_size =192 dma passed
    CFBS_64 key_size =192 dma passed
    CFBS_32 key_size =192 dma passed
    CFBS_16 key_size =192 dma passed
    CFBS_8 key_size =192 dma passed
    CTR key_size =192 dma passed
    GCM iv_size =12 key_size =192 dma passed
    GCM iv_size =16 key_size =192 dma passed
    XTS key_size =192 dma passed
    ECB key_size =256 dma passed
    CBC key_size =256 dma passed
    OFB key_size =256 dma passed
    CFBS_128 key_size =256 dma passed
    CFBS_64 key_size =256 dma passed
    CFBS_32 key_size =256 dma passed
    CFBS_16 key_size =256 dma passed
    CFBS_8 key_size =256 dma passed
    CTR key_size =256 dma passed
    GCM iv_size =12 key_size =256 dma passed
    GCM iv_size =16 key_size =256 dma passed
    XTS key_size =256 dma passed
    TEST SUCCESS !
