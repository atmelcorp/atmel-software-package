#
#  Connect to J-Link and debug application in sram.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Reset peripherals (using RSTC_CR)
set *0x400E1800 = 0xA5000004

# Disable Watchdog (using WDT_MR)
set *0x400E1850 = 0x00008000

# Load the program
load

# Zero registers
set $r0 = 0
set $r1 = 0
set $r2 = 0
set $r3 = 0
set $r4 = 0
set $r5 = 0
set $r6 = 0
set $r7 = 0
set $r8 = 0
set $r9 = 0
set $r10 = 0
set $r11 = 0
set $r12 = 0
set $sp = 0
set $lr = 0

# Initialize SP & PC
set $sp=0x20401000
set $pc=0x20401000

# Set breakpoint at end of applet execution
b applet_end
commands 1
mbxout
end

# Show registers state
mon regs

end

define mbxin
  printf "- Mailbox IN -\n"
  printf "CMD:    0x%x (%d)\n", *0x20401004, *0x20401004
  printf "STATUS: 0x%x (%d)\n", *0x20401008, *0x20401008
  x/32xw 0x2040100C
end

define mbxout
  printf "- Mailbox OUT -\n"
  printf "CMD:    0x%x (%d)\n", *0x20401004, *0x20401004
  printf "STATUS: 0x%x (%d)\n", *0x20401008, *0x20401008
  x/32xw 0x2040100C
end

define runapplet
  set $applet_cmd = $arg0
  set *0x20401004=$applet_cmd
  set *0x20401008=0
  if $argc >= 2
    set *0x2040100C=$arg1
  else
    set *0x2040100C=0
  end
  if $argc >= 3
    set *0x20401010=$arg2
  else
    set *0x20401010=0
  end
  if $argc >= 4
    set *0x20401014=$arg3
  else
    set *0x20401014=0
  end
  if $argc >= 5
    set *0x20401018=$arg4
  else
    set *0x20401018=0
  end
  if $argc >= 6
    set *0x2040101C=$arg5
  else
    set *0x2040101C=0
  end
  if $argc >= 7
    set *0x20401020=$arg6
  else
    set *0x20401020=0
  end
  if $argc >= 8
    set *0x20401024=$arg7
  else
    set *0x20401024=0
  end
  set $sp=0x20401000
  set $pc=0x20401000
  continue
end
