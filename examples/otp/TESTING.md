OTP EXAMPLE
============

# Objectives
------------
This example aims to shows how to use OTP.

# Example Description
---------------------
The example demos how to use the OTP, some operations (read, write, update, invalid,
 lock) are shown, and be careful with the operations while the OTP emulation mode
 is disabled. Uncomment the definition of marco "CONFIG_HAVE_OTP_DEBUG" in otpc.c 
 would be helpful for being familiar with the OTP.

# Test
------
## Supported targets
--------------------
* SAM9X60-EK

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

The OTP emulation mode would be enabled if the OTP is not disabled and the OTP
 has not be programmed, first the packets in OTP (empty) are listed bellow:

```
packet type:
        R - REGULAR
        K - KEY
        B - BOOT_CONFIGURATION
        S - SECURE_BOOT_DATA
        H - HARDWARE_CONFIGURATION
        C - CUSTOM
 idx | header addr | check sum |  size | valid | locked | type | payload
-E- invalid packet type!
```

Then if the emulation mode is successfully enabled, some operations (write, update,
 invalid, lock) are done before list the packages again, and now the packages are:

```
packet type:
        R - REGULAR
        K - KEY
        B - BOOT_CONFIGURATION
        S - SECURE_BOOT_DATA
        H - HARDWARE_CONFIGURATION
        C - CUSTOM
 idx | header addr | check sum |  size | valid | locked | type | payload
   0 |  0x00000000 |    0xffff |    4B |    no |    no  |   C  | 00 01 02 ...
   1 |  0x00000002 |    0x0000 |    8B |   yes |    no  |   C  | 0c 0d 0e ...
   2 |  0x00000005 |    0x0000 |   12B |   yes |    no  |   C  | 14 15 16 ...
   3 |  0x00000009 |    0xa5a5 |   16B |   yes |   yes  |   C  | 1c 1d 1e ...
   4 |  0x0000000e |    0x0000 |    8B |   yes |    no  |   C  | 24 25 26 ...
   5 |  0x00000011 |    0x0000 |   16B |   yes |    no  |   C  | 1c 1d 1e ...
```

At last the menu is shown and some operations could be done through it:

```
 =================== OTP Example Menu =====================
|  e: User area Emulation: Enabled[X] Disabled [ ]          |
|  h: Hide packet                                           |
|  i: Invalidate packet                                     |
|  l: Lock packet                                           |
|  s: Show packets                                          |
|  w: write a packet                                        |
|  m: Menu                                                  |
|-----------------------------------------------------------|
```

Tested with IAR and GCC (sram and ddram configuration)
Note: While debugging with GCC the switch of the emulation mode would be effected
       by "reset_peripherals" in the gdb file, mask the reset would make the mode
       switch properly.

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'e' | Disable emulation mode | Emulation mode disabled | PASSED
Press 'e' | Enable emulation mode | Emulation mode enabled | PASSED
Press 'h' '00000000' | Hide packet at 0x0000  | Packet hid | PASSED
Press 's' | Show packets | Payload of the hidden packets are all zero | PASSED
Press 'l' '00000002' | Lock packet at 0x0002 | Packet locked | PASSED
Press 's' | Show packets | the 'locked' cloumn of packet at 0x0002 changes from 'no' to 'yes' | PASSED
Press 'i' '00000005' | Invalid packet at 0x0005 | Packet invalid | PASSED
Press 's' | Show packets | the 'valid' cloumn of packet at 0x0005 changes from 'yes' to 'no' | PASSED
Press 'w' | Write a packet | Packet wrote | PASSED
Press 's' | Show packets | a new packet is shown in the list | PASSED
