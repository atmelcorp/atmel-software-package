#
#  Connect to J-Link and debug application in sram.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Disable all interrupts and go to supervisor mode
mon reg cpsr = 0xd3

# Disable Watchdog (using WDT_MR)
set *0xFFFFFE44 = 0x00008000

# Disable D-Cache, I-Cache and MMU
mon cp15 1 0 0 0 = 0x00C50078

# Load the program
load

# Zero registers (cannot reset core because it will disable JTAG)
mon reg r8_fiq = 0
mon reg r9_fiq = 0
mon reg r10_fiq = 0
mon reg r11_fiq = 0
mon reg r12_fiq = 0
mon reg sp_fiq = 0
mon reg lr_fiq = 0
mon reg spsr_fiq = 0
mon reg sp_irq = 0
mon reg lr_irq = 0
mon reg spsr_irq = 0
mon reg sp_abt = 0
mon reg lr_abt = 0
mon reg spsr_abt = 0
mon reg sp_und = 0
mon reg lr_und = 0
mon reg spsr_und = 0
mon reg sp_svc = 0
mon reg lr_svc = 0
mon reg spsr_svc = 0
mon reg r0 = 0
mon reg r1 = 0
mon reg r2 = 0
mon reg r3 = 0
mon reg r4 = 0
mon reg r5 = 0
mon reg r6 = 0
mon reg r7 = 0
mon reg r8_usr = 0
mon reg r9_usr = 0
mon reg r10_usr = 0
mon reg r11_usr = 0
mon reg r12_usr = 0
mon reg sp_usr = 0
mon reg lr_usr = 0

# Initialize SP & PC
mon reg sp = 0x308000
mon reg pc = 0x300000

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
  printf "CMD:    0x%x (%d)\n", *0x300004, *0x300004
  printf "STATUS: 0x%x (%d)\n", *0x300008, *0x300008
  x/32xw 0x30000C
end

define mbxout
  printf "- Mailbox OUT -\n"
  printf "CMD:    0x%x (%d)\n", *0x300004, *0x300004
  printf "STATUS: 0x%x (%d)\n", *0x300008, *0x300008
  x/32xw 0x30000C
end

define runapplet
  set $applet_cmd = $arg0
  set *0x300004=$applet_cmd
  set *0x300008=0
  if $argc >= 2
    set *0x30000C=$arg1
  else
    set *0x30000C=0
  end
  if $argc >= 3
    set *0x300010=$arg2
  else
    set *0x300010=0
  end
  if $argc >= 4
    set *0x300014=$arg3
  else
    set *0x300014=0
  end
  if $argc >= 5
    set *0x300018=$arg4
  else
    set *0x300018=0
  end
  if $argc >= 6
    set *0x30001C=$arg5
  else
    set *0x30001C=0
  end
  if $argc >= 7
    set *0x300020=$arg6
  else
    set *0x300020=0
  end
  if $argc >= 8
    set *0x300024=$arg7
  else
    set *0x300024=0
  end
  set $pc=0x300000
  continue
end
