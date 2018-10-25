source target/common.gdb

define reset
  jlink_connect
  reset_peripherals
  init_ddr
  load_in_ddr
end
