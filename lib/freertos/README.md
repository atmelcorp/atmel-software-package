FreeRTOS Support
============

FreeRTOS is a market leading RTOS, has become the de facto standard RTOS
for microcontrollers by removing common objections to using free software,
and in so doing, providing a truly compelling free software model.

For more details:

http://www.freertos.org/FreeRTOS-quick-start-guide.html  
http://www.freertos.org/FAQHelp.html

FreeRTOS Porting
---------------

The Software Package references to FreeRTOS code, which is available from one of the following reference links:

AWS FreeRTOS: https://github.com/aws/amazon-freertos  
FreeRTOS SVN clone: https://github.com/cjlano/freertos

The porting layer code is available under lib/freertos/portable,
Some examples using task, queue, lwIP, uIP with FreeRTOS are located under examples/freertos_xxxx.

Directories
---------

We need to check out the Software Package and FreeRTOS in the same location, like this:

+ softpack
+ FreeRTOS
+ FreeRTOS-Plus

The FreeRTOS/Source directory contains the FreeRTOS source code and contains its own readme file.

The FreeRTOS-Plus/Source directory contains source code for some of the FreeRTOS+ components.
These subdirectories contain further readme files and links to documentation.

Environment variable FREERTOS_SOURCE_TOP define the path of FreeRTOS source code. The default path
is defined in scripts/Makefile.freertos, override by an environment variable FREERTOS_SOURCE_TOP.
