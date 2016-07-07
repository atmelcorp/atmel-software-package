SECUMOD EXAMPLE
============

# Objectives
------------
This example aims to test Security Module (SECUMOD).


# Example Description
---------------------
This example demonstrates how to use the `Security Module`.


# Test
------

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 115200 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application.
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- SECUMOD Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 ============== SECUMOD (Security Module) Menu =================

 |-----------------------------------------------------------|
 |                 Protection Configuration                  |
 |                                                           |
 | Press [0|3|7|j] to Enable/Disable Protection Monitoring   |
 |                                                           |
 |  0: PIOBU0 and 1 (Dynamic)  [Disabled]                    |
 |  3: PIOBU3 (Static)         [Enabled ]                    |
 |  2: PIOBU4 and 5 (Dynamic)  [Disabled]                    |
 |  7: PIOBU7 (Static)         [Enabled ]                    |
 |  j: JTAG Pins               [Disabled]                    |
 |  O: TST Pins                [Disabled]                    |
 |-----------------------------------------------------------|
 |  q: Tamper Interrupt        [Enabled ]                    |
 |  y: SECURAM Auto Erase      [Enabled ]                    |
 |-----------------------------------------------------------|
 |              SECURAM Access Rights Settings               |
 |                                                           |
 | Press [a|b|c] to change access rights for regions below   |
 |                                                           |
 |  a: Lower area       [ ] None   [ ] W   [ ] R   [X] RW    |
 |  b: Higher area      [ ] None   [ ] W   [ ] R   [X] RW    |
 |  c: Reg. Bank area   [ ] None   [ ] W   [ ] R   [X] RW    |
 |                                                           |
 |-----------------------------------------------------------|
 |-----------------------------------------------------------|
 |                         Commands                          |
 |                                                           |
 |  w: Write pattern into SECURAM                            |
 |  r: Read pattern from SECURAM                             |
 |  p: Launch software protection (SECURAM erasing process)  |
 |  s: Change Scrambling Key                                 |
 |                                                           |
 |  m: Switch to Backup Mode                                 |
 |                                                           |
 |  i: Display the tamper/SECURAM events                     |
 |  h: Display this menu                                     |
 |                                                           |
 |-----------------------------------------------------------|
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'h' | Print the menu on screen | PASSED | PASSED
Press 'i' | Print `-I- no SECURAM events happened.`, `-I- no access violations happened.` ... on screen | PASSED | PASSED
Press '0' | Print `SECUMOD (Security Module) Menu` ... `0: PIOBU0 and 1 (Dynamic)  [Enabled ]` ... on screen | PASSED | PASSED
Press 'i' | Print `SECURAM erased X times` ... `SECURAM: lower and register bank areas have been erased.` ... `SECUMOD interrupt occurs X times` ... `Tamper source:    PIOBU1 Intrusion Detector` ... `SECURAM erased X times` on screen | PASSED | PASSED
Press 'i' | Print `SECURAM erased X times` ... `SECURAM: lower and register bank areas have been erased.` ... `SECUMOD interrupt occurs X times` ... `Tamper source:    PIOBU1 Intrusion Detector` ... `SECRAM erased X times` on screen | PASSED | PASSED
Press '0' | Print `SECUMOD (Security Module) Menu` ... `0: PIOBU0 and 1 (Dynamic)  [Disabled]` ... on screen | PASSED | PASSED
Press 'h' | Print the menu on screen | PASSED | PASSED
PIOBU3/PIOBU7 tamper | test tamper static mode | PASSED | PASSED
JTAG tamper | test JTAG tamper | PASSED | PASSED
TST tamper | test TST tamper | PASSED | PASSED
Press 'q' | Print ... `q: Tamper Interrupt        [Disabled]` ... on screen | PASSED | PASSED
Press 'q' | Print ... `q: Tamper Interrupt        [Enabled ]` ... on screen | PASSED | PASSED
Press 'y' | Print ... `y: SECURAM Auto Erase      [Disabled]` ... on screen | PASSED | PASSED
Press 'y' | Print ... `y: SECURAM Auto Erase      [Enabled ]` ... on screen | PASSED | PASSED
Press 'w' | Print `-I- Fill SECURAM:`, `-I- -- Lower area with 0x04 (size 4096 bytes)`, `-I- -- Higher area with 0x01 (size 1024)`, `-I- -- Register Bank area with 0xff (size 256 bits)` on screen | PASSED | PASSED
Press 'r' | Print `-I- SECURAM dump:` ... on screen | PASSED | PASSED
Press 'a' | Print ... `a: Lower area      [X] None   [ ] W   [ ] R   [ ] RW` ... on screen | PASSED | PASSED
Press 'b' | Print ... `b: Higher area     [X] None   [ ] W   [ ] R   [ ] RW` ... on screen | PASSED | PASSED
Press 'c' | Print ... `c: Reg. Bank area  [X] None   [ ] W   [ ] R   [ ] RW` ... on screen | PASSED | PASSED
Press 'w' | Print `-I- Fill SECURAM:`, `-I- -- Lower area with 0x04 (size 4096 bytes)`, `-I- -- Higher area with 0x01 (size 1024 bytes)`, `-I- -- Register Bank area with 0xff (size 256 bits)` on screen | PASSED | PASSED
Press 'i' | Print `SECURAM Region [5 kbytes - 6 kbytes] write access violation occurred.` ... on screen | PASSED | PASSED
Press 'r' | Print `-I- SECURAM dump:` ... on screen | PASSED | PASSED
Press 'i' | Print `SECURAM Region [5 kbytes - 6 kbytes] read access violation occurred.` ... on screen | PASSED | PASSED
Press 'c' | Print ... `c: Reg. Bank area  [ ] None   [X] W   [ ] R   [ ] RW` ... on screen | PASSED | PASSED
Press 'w' | Print `-I- Fill SECURAM:`, `-I- -- Lower area with 0x04 (size 4096 bytes)`, `-I- -- Higher area with 0x01 (size 1024)`, `-I- -- Register Bank area with 0xff (size 256 bits)` on screen | PASSED | PASSED
Press 'i' | Print `SECURAM Region [4 kbytes - 5 kbytes] write access violation occurred.` ... on screen | PASSED | PASSED
Press 'p' | Print `-I- SECURAM erased.` on screen | PASSED | PASSED
Press 's' | Print `-I- Current Scrambling Key is:` ... on screen then test functions with the new scrambling key | PASSED | PASSED
Press 'm' | Print ... `Enter in Backup Mode` ... on screen then test functions in the backup mode | PASSED | PASSED

