# Connect to the J-Link gdb server
define jlink_connect
  target remote localhost:2331
end

define reset_peripherals
  # Reset the chip to get to a known state
  monitor reset

  # Reset peripherals (using RSTC_CR)
  set *0x400E1800 = 0xA5000004

  # Disable Watchdog (using WDT_MR)
  set *0x400E1850 = 0x00008000
end

# Disable MPDDRC controller
# to avoid corrupted RAM data on soft reset.
define disable_sdram
  set *0x40084104 = (1 << 30)
end

define reset_registers
  # Zero registers
  mon reg r0 = 0
  mon reg r1 = 0
  mon reg r2 = 0
  mon reg r3 = 0
  mon reg r4 = 0
  mon reg r5 = 0
  mon reg r6 = 0
  mon reg r7 = 0
  mon reg r8 = 0
  mon reg r9 = 0
  mon reg r10 = 0
  mon reg r11 = 0
  mon reg r12 = 0
  mon reg sp = 0
  mon reg lr = 0
end

define load_in_sram
  reset_registers

  load

  # Initialize VTOR
  set *0xE000ED08 = 0x20400000

  # Initialize SP and PC
  set $sp = *0x20400000
  set $pc = *0x20400004
end

define init_ddram

  reset_registers

  # Load bootstrap (in SRAM)
  load target/bootstrap.elf

  # Initialize SP and PC
  set $sp = *0x20400000
  set $pc = *0x20400004

  continue
end

define load_in_ddram
  reset_registers

  load

  # Initialize VTOR
  set *0xE000ED08 = 0x70000000

  # Initialize SP and PC
  set $sp = *0x70000000
  set $pc = *0x70000004
end

define load_in_flash
  reset_registers

  # Select flash device
  monitor flash device = ATSAMV71Q21
  # Enable flash download and flash breakpoints
  monitor flash download = 1

  load

  # Initialize SP and PC
  # Workaround: it seems that the first flash access fails
  #     doing it a second times fixes the problem
  set $sp = *0x400000
  set $sp = *0x400000
  set $pc = *0x400004
end
