USART EXAMPLE
=============

# Objectives
------------
This example aims to perform peripheral data transfer over USART.

# Example Description
---------------------
This example demonstrates how to send/receive data to/from the PC and show it in the terminal. There are plenty of options available for UART to USB convertors and PC serial terminal software. The USART will be configured for asynchronous, dma and polling mode.

# Test
------
## Supported targets
--------------------
* SAM9X60-EK
* SAM9X60-CURIOSITY
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
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal on Microsoft Windows)
	- with these settings:
		- 115200 bauds
		- 8 bits of data
		- No parity
		- 1 stop bit
		- No flow control
	- or handshaking mode with these settings:
		- 115200 bauds
		- 8 bits of data
		- No parity
		- 1 stop bit
		- hardware
* Start the application
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
USART transfer mode: POLLING
Usart example mini-console:

|===========        Commands        ====================|
| r size                                                |
|      Wait to recieve 'size' characters from usart and |
|      print the result string (block call)             |
| w str                                                 |
|      Write 'str' throught usart                       |
| c                                                     |
|      Demo Comparision Function                        |
| p                                                     |
|      receive with DMA (ping/pong buffer used)         |
| m polling                                             |
| m async                                               |
| m dma                                                 |
|      Select transfer mode                             |
| f fifo                                                |
|      Toggle FIFO feature                              |
| f handshaking                                         |
|      Toggle Handshaking and normal mode               |
| l                                                     |
|      Local Loopback test                              |
| h                                                     |
|      Print this menu                                  |
|=======================================================|
```

### sam9x60-ek
--------------------
FLEXUSART4 (40-pin GPIO/RPi connector: RX on pin 23, TX on pin 21, CTS on pin 22, RTS on pin 24)
 - normal mode connection: rx<->tx, tx<->rx
 - handshaking mode connection: rx<->tx, tx<->rx, rts<->cts, cts<->rts

### sam9x60-curiosity
--------------------
FLEXUSART4 (RX: PA11 on MikroBUS J8 pin 5, TX: PA12 on J8 pin 6, CTS: PA14 on J8 pin 3, RTS: PA7 on J9 pin 24)
 - normal mode connection: rx<->tx, tx<->rx
 - handshaking mode connection: rx<->tx, tx<->rx, rts<->cts, cts<->rts

### sama5d2-ptc-ek
--------------------
FLEXUSART4 (RX on J15B:5, TX on J15B:6, CTS on J15:4, RTS on J15A:1)
 - normal mode connection: rx<->tx, tx<->rx
 - handshaking mode connection: rx<->tx, tx<->rx, rts<->cts, cts<->rts

### sama5d2-xplained
--------------------
FLEXUSART0 (RX on J22:4, TX on J22:3, CTS on J25:11, RTS on J25:12))
 - normal mode connection: rx<->tx, tx<->rx
 - handshaking mode connection: rx<->tx, tx<->rx, rts<->cts, cts<->rts

### sama5d27-som1-ek
--------------------
FLEXUSART3 (RX on ISC:28, TX on ISC:29, CTS on ISC:16, RTS on ISC:12)
 - normal mode connection: rx<->tx, tx<->rx
 - handshaking mode connection: rx<->tx, tx<->rx, rts<->cts, cts<->rts

### sama5d4-xplained
--------------------
Connect USART4

### sama5d4-ek
--------------
Connect USART4

### sama5d3-xplained
--------------------
Connect USART3 (pin 1 on J20 and pin 2 on J20)

### same70-xplained
--------------------
Connect USART2 (pin 5 on J505 and pin 6 on J505)

### samv71-xplained
--------------------
Connect USART2 (pin 5 on J505 and pin 6 on J505)

#
Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

|Step | Description | Expected Result | Result
|-----|-------------|-----------------|-------
|Press 'w 11223344' | write string throught usart| receive "11223344" from PC serial terminal  | PASSED
|Press 'r 100'      | Receive 100 characters from from PC serial terminal, on PC serial terminal, send text file  | R:1234567....|PASSED
||||
|Press 'f fifo'     | Toggle FIFO feature |  enabled/disable fifo | PASSED
|Press 'f handshaking' | Toggle Handshaking and normal mode | switch to handshaking mode or normal mode | PASSED
|Press 'm polling'     | switch to polling mode |  | PASSED
|Press 'm async'    | switch to asynchronous mode |  | PASSED
|Press 'm dma'      | switch to dma mode |  | PASSED
||||
|press 'l'          | loopback test | following messaages shown on the console | PASSED
```
Enable Loopback test
Start local loopback test
Mode:ASYNC
FIFO disabled
a
a
ab
ab
abc
abc
abcd
abcd
abcde
abcde
abcdef
abcdef
abcdefg
abcdefg
abcdefgh
abcdefgh
abcdefghi
abcdefghi
abcdefghij
abcdefghij
abcdefghijk
abcdefghijk
abcdefghijkl
abcdefghijkl
abcdefghijklm
abcdefghijklm
abcdefghijklmn
abcdefghijklmn
abcdefghijklmno
abcdefghijklmno
abcdefghijklmnop
abcdefghijklmnop
abcdefghijklmnopq
abcdefghijklmnopq
abcdefghijklmnopqr
abcdefghijklmnopqr
abcdefghijklmnopqrs
abcdefghijklmnopqrs
abcdefghijklmnopqrst
abcdefghijklmnopqrst
abcdefghijklmnopqrstu
abcdefghijklmnopqrstu
abcdefghijklmnopqrstuv
abcdefghijklmnopqrstuv
abcdefghijklmnopqrstuvw
abcdefghijklmnopqrstuvw
abcdefghijklmnopqrstuvwx
abcdefghijklmnopqrstuvwx
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz0
abcdefghijklmnopqrstuvwxyz0
abcdefghijklmnopqrstuvwxyz01
abcdefghijklmnopqrstuvwxyz01
abcdefghijklmnopqrstuvwxyz012
abcdefghijklmnopqrstuvwxyz012
abcdefghijklmnopqrstuvwxyz0123
abcdefghijklmnopqrstuvwxyz0123
abcdefghijklmnopqrstuvwxyz01234
abcdefghijklmnopqrstuvwxyz01234
abcdefghijklmnopqrstuvwxyz012345
abcdefghijklmnopqrstuvwxyz012345
abcdefghijklmnopqrstuvwxyz0123456
abcdefghijklmnopqrstuvwxyz0123456
abcdefghijklmnopqrstuvwxyz01234567
abcdefghijklmnopqrstuvwxyz01234567
abcdefghijklmnopqrstuvwxyz012345678
abcdefghijklmnopqrstuvwxyz012345678
abcdefghijklmnopqrstuvwxyz0123456789
abcdefghijklmnopqrstuvwxyz0123456789
FIFO enabled
a
a
ab
ab
abc
abc
abcd
abcd
abcde
abcde
abcdef
abcdef
abcdefg
abcdefg
abcdefgh
abcdefgh
abcdefghi
abcdefghi
abcdefghij
abcdefghij
abcdefghijk
abcdefghijk
abcdefghijkl
abcdefghijkl
abcdefghijklm
abcdefghijklm
abcdefghijklmn
abcdefghijklmn
abcdefghijklmno
abcdefghijklmno
abcdefghijklmnop
abcdefghijklmnop
abcdefghijklmnopq
abcdefghijklmnopq
abcdefghijklmnopqr
abcdefghijklmnopqr
abcdefghijklmnopqrs
abcdefghijklmnopqrs
abcdefghijklmnopqrst
abcdefghijklmnopqrst
abcdefghijklmnopqrstu
abcdefghijklmnopqrstu
abcdefghijklmnopqrstuv
abcdefghijklmnopqrstuv
abcdefghijklmnopqrstuvw
abcdefghijklmnopqrstuvw
abcdefghijklmnopqrstuvwx
abcdefghijklmnopqrstuvwx
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz0
abcdefghijklmnopqrstuvwxyz0
abcdefghijklmnopqrstuvwxyz01
abcdefghijklmnopqrstuvwxyz01
abcdefghijklmnopqrstuvwxyz012
abcdefghijklmnopqrstuvwxyz012
abcdefghijklmnopqrstuvwxyz0123
abcdefghijklmnopqrstuvwxyz0123
abcdefghijklmnopqrstuvwxyz01234
abcdefghijklmnopqrstuvwxyz01234
abcdefghijklmnopqrstuvwxyz012345
abcdefghijklmnopqrstuvwxyz012345
abcdefghijklmnopqrstuvwxyz0123456
abcdefghijklmnopqrstuvwxyz0123456
abcdefghijklmnopqrstuvwxyz01234567
abcdefghijklmnopqrstuvwxyz01234567
abcdefghijklmnopqrstuvwxyz012345678
abcdefghijklmnopqrstuvwxyz012345678
abcdefghijklmnopqrstuvwxyz0123456789
abcdefghijklmnopqrstuvwxyz0123456789
Mode:DMA
FIFO disabled

a
ab
abc
abcd
abcde
abcdef
abcdefg
abcdefgh
abcdefghi
abcdefghij
abcdefghijk
abcdefghijkl
abcdefghijklm
abcdefghijklmn
abcdefghijklmno
abcdefghijklmnop
abcdefghijklmnopq
abcdefghijklmnopqr
abcdefghijklmnopqrs
abcdefghijklmnopqrst
abcdefghijklmnopqrstu
abcdefghijklmnopqrstuv
abcdefghijklmnopqrstuvw
abcdefghijklmnopqrstuvwx
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz0
abcdefghijklmnopqrstuvwxyz01
abcdefghijklmnopqrstuvwxyz012
abcdefghijklmnopqrstuvwxyz0123
abcdefghijklmnopqrstuvwxyz01234
abcdefghijklmnopqrstuvwxyz012345
abcdefghijklmnopqrstuvwxyz0123456
abcdefghijklmnopqrstuvwxyz01234567
abcdefghijklmnopqrstuvwxyz012345678
abcdefghijklmnopqrstuvwxyz0123456789
```