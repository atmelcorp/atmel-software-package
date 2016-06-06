source target/common.gdb

# define 'reset' command
define reset
  jlink_connect
  reset_peripherals
  load_in_sram
end
