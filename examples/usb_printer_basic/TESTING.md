USB_PRINTER EXAMPLE
=======================

# Objectives
------------
This example aims to test the USB Device Port(UDP), USB printer Device.

# Example Description
---------------------
This demo uses PC running Windows as a Host. The demo application on top of USB printer function 
driver when connected to the host, enumerates as "USB Printing Support" device under USB controllers 
in Device Manager. This demo allows the user to print the text from Notepad or similar application 
in Windows using built in "Generic/Text Only" print driver. Generic / Text Only driver simply outputs 
the data to the connected USB printer in raw format without performing any translation on the data to 
be printed.

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
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
USB printer driver installation

After the device attached to the host PC enumerates as "USB Printing Support" in Device Manager,
At this point, a new device by the name "Generic Text Printer Demo" should be available under 
Control Panel -> Devices.
Follow the below steps to add "Generic/Text Only" printer and link it to the attached USB printer.
1) Open Devices and Printers from the Control Panel and right click then click "Add a printer".
2) In the Add Printer wizard, click "Add a local printer".
3) In the printer port selection option, choose "Use an existing port" and from the drop-down list,
 select "USB001 (Virtual printer port for USB)".
4) In the printer driver selection, select "Generic" from the Manufacturer list and "Generic / Text Only" 
from the Printers list.
5) Use the default option in driver version select window and click Next.
6) In the printer name window, use the default name "Generic / Text Only" or provide any other name 
and click Next.
7) Click Finish to complete the Add printer wizard.
8) At this point, a new printer icon with the name provided in step #6 should be visible under Devices.

In the terminal window, the following text should appear (values depend on the board and chip used):
```
 -- USB printer basic Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

After successful installation of the "Generic / Text Only" printer,
Print a test page via right click and select "Printer Properties"
Or 
Print a raw text only document using the "Generic / Text Only" printer.
Now the test page data will be printed on the serial terminal application.