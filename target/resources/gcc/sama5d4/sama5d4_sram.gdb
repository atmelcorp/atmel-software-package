#*************************************************
#
#  Connect to J-Link and debug application in sram.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Reset the chip to get to a known state
#monitor reset

# Load the program
load

# Initializing PC and stack pointer
mon reg pc = 0x200000
mon reg pc = 0x200000
info reg

# end of 'reset' command
end
