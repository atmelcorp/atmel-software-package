# Connect to the J-Link gdb server
define jlink_connect
  target remote localhost:2331
end

define reset_peripherals
  monitor reset

  # Disable Watchdog (using WDT_MR)
  set *0xFFFFFE44 = 0x00008000

  # Disable D-Cache, I-Cache and MMU
  mon cp15 1 0 0 0 = 0x00C50078
end

define reset_registers
  # Zero registers
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
end

define init_ddr
  reset_registers
  load target/bootstrap.elf
  mon reg pc = 0x00300000
  continue
end

define load_in_ddr
  reset_registers
  load
  mon reg pc = 0x20000000
end

define load_in_sram
  reset_registers
  load
  mon reg pc = 0x00300000
end
