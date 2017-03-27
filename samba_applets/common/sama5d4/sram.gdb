#
#  Connect to J-Link and debug application in sram.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Reset peripherals (using RSTC_CR)
set *0xFC068600 = 0xA5000004

# Disable Watchdog (using WDT_MR)
set *0xFC068644 = 0x00008000

# Disable D-Cache, I-Cache and MMU
mon cp15 1 0 0 0 = 0x00C50078

# Load the program
load

# Disable all interrupts and go to supervisor mode
mon reg cpsr = 0xd3

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
mon reg sp = 0x220000
mon reg pc = 0x200000

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
  printf "CMD:    0x%x (%d)\n", *0x200004, *0x200004
  printf "STATUS: 0x%x (%d)\n", *0x200008, *0x200008
  x/32xw 0x20000C
end

define mbxout
  printf "- Mailbox OUT -\n"
  printf "CMD:    0x%x (%d)\n", *0x200004, *0x200004
  printf "STATUS: 0x%x (%d)\n", *0x200008, *0x200008
  x/32xw 0x20000C
end

define runapplet
  set $applet_cmd = $arg0
  set *0x200004=$applet_cmd
  set *0x200008=0
  if $argc >= 2
    set *0x20000C=$arg1
  else
    set *0x20000C=0
  end
  if $argc >= 3
    set *0x200010=$arg2
  else
    set *0x200010=0
  end
  if $argc >= 4
    set *0x200014=$arg3
  else
    set *0x200014=0
  end
  if $argc >= 5
    set *0x200018=$arg4
  else
    set *0x200018=0
  end
  if $argc >= 6
    set *0x20001C=$arg5
  else
    set *0x20001C=0
  end
  if $argc >= 7
    set *0x200020=$arg6
  else
    set *0x200020=0
  end
  if $argc >= 8
    set *0x200024=$arg7
  else
    set *0x200024=0
  end
  set $pc=0x200000
  continue
end
