# Connect to the J-Link gdb server
define jlink_connect
  target remote localhost:2331
end

define reset_peripherals
  # Disable all interrupts and go to supervisor mode
  mon reg cpsr = 0xd3

  # Remap AHB & AXI Matrixes
  set *0xFFFFED00 = 0x1
  mon sleep 2
  set *0x00800000 = 0x1
  mon sleep 50

  # Disable Watchdog (using WDT_MR)
  set *0xFFFFFE44 = 0x00008000

  # Disable D-Cache, I-Cache and MMU
  mon cp15 1 0 0 0 = 0x00C50078
end

# Disable DDR clock and MPDDRC controller
# to avoid corrupted RAM data on soft reset.
define disable_ddr
  set *0xFFFFFC04 = 0x4
  set *0xFFFFFC14 = (1 << 16)
end

define reset_registers
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
end

define init_ddr  

  reset_registers
  
  load target/bootstrap.elf
  
  # Initialize PC
  mon reg pc = 0x00300000

  continue
end

define load_in_ddr

  reset_registers

  load
  
  # Initialize PC
  mon reg pc = 0x20000000
end

define load_in_sram
  reset_registers

  load

  # Initialize PC
  mon reg pc = 0x00300000
end
