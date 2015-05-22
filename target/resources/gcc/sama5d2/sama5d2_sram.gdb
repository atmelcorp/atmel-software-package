#*************************************************
#
#  Connect to J-Link and debug application in sram.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Load the program
load

# Initialize PC and zero registers
mon reg pc = 0x200000
mon reg r0 = 0x0
mon reg r1 = 0x0
mon reg r2 = 0x0
mon reg r3 = 0x0
mon reg r4 = 0x0
mon reg r5 = 0x0
mon reg r6 = 0x0
mon reg r7 = 0x0

# Disable all interrupts and go to supervisor mode
mon reg cpsr = 0xd3

# Show registers state
mon regs

end
