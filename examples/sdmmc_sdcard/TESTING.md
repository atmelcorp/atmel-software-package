SDMMC_SDCARD EXAMPLE
============

# Objectives
------------
This example aims to test read and write access to SD cards, MMC cards, and
e.MMC devices.


# Example Description
---------------------
The application first runs the standard initialization sequence with the
device.
At this point, properties of the device can be displayed.
Then the application mounts a FAT file system, if any. The root directory
may be listed (files and folders).

It is then proposed to open a predefined file, named 'test_data.bin', and read
its contents entirely. The contents itself is not displayed, but sent to the
SHA peripheral, which computes the SHA-1 hash of the file.

It is also possible to test writing to the memory device. As of writing, this
particular test is implemented in raw mode, which implies the file system is
bypassed. One may need to reformat the device after having taken the write
test.
A few SD or MMC blocks are first read and displayed on the console, before the
modification occurs. The same blocks are written to, filled with a simple
pattern. Finally the same blocks are read again and their new contents is
dumped on the console.


# Test
------

## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED

## Setup
--------
Build the example in release mode, with extra traces disabled, e.g.:

    cd examples/sdmmc_sdcard/
    export TARGET=sama5d2-xplained
    export RELEASE=1; export -n DEBUG; export TRACE_LEVEL=0
    make clean
    make

Prepare a SD memory card, or a MMC card.

* The card shall have been formatted with a FAT file system, either FAT16 or
FAT32 depending on the size of the partition.
* Select a file of your choice, for the read test. For file size and contents
it's up to you. Large files are supported, though I/O operations may take
longer to complete. Name the file 'test_data.bin' and copy it to the root
directory of the FAT volume on the memory card. On the host compute the SHA-1
of the file, for later reference:

    shasum -a 1 -b test_data.bin
    openssl dgst -sha1 test_data.bin
    FCIV -sha1 test_data.bin

Boot the board and run the example.

Note that if the card is inserted before booting, the bootloader may search
for a bootable file on it, which may prevent running the example.
Expect the example menu to appear on the console.

## Start the application
------------------------

Follow the test steps listed hereafter.

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'i' | Test card detection | "Device not detected." | PASS
Now insert the memory card | N/A | N/A
Press 'i' again | Run the initialization sequence | Card properties are displayed and seem valid. | PASS
Press 'l' | Mount the file system | Files in the root directory are properly listed. | PASS
Press 'r' | Read the predefined file | File size is reported and all right. SHA-1 is printed and matches the hash computed on the host. | PASS
Press 't' | Select the on-board e.MMC device | |
Press 'i' | Run the initialization sequence | Properties of the e.MMC are displayed and seem valid. | PASS

