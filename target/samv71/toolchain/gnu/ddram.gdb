source target/common.gdb

# define 'reset' command
define reset

  # Connect to the J-Link gdb server
  jlink_connect

  reset_peripherals

  disable_sdram

  init_ddram

  load_in_ddram

end
