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
mon reg r0 = 0x0
mon reg r1 = 0x0
mon reg r2 = 0x0
mon reg r3 = 0x0
mon reg r4 = 0x0
mon reg r5 = 0x0
mon reg r6 = 0x0
mon reg r7 = 0x0
# Disable all interrupt and pass to supervisor mode
mon reg cpsr = 0xd3
info reg

# end of 'reset' command
end
