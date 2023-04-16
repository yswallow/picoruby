MRuby::CrossBuild.new("nrf-cortex-m4") do |conf|

  ###############################################################
  # You need following tools:
  #   arm-none-eabi       | to make libmruby.a
  ###############################################################

  conf.toolchain

  conf.cc.command = "arm-none-eabi-gcc"
  conf.linker.command = "arm-none-eabi-ld"
  conf.linker.flags << "-static"
  conf.archiver.command = "arm-none-eabi-ar"

  conf.cc.host_command = "gcc"

  conf.cc.flags.flatten!
  conf.cc.flags.delete "-O3"
  conf.cc.flags << "-Og"
  conf.cc.flags << "-mcpu=cortex-m4"
  conf.cc.flags << "-mthumb"
  conf.cc.flags << "-mabi=aapcs"
  conf.cc.flags << "-mfloat-abi=hard"
  conf.cc.flags << "-mfpu=fpv4-sp-d16"
  conf.cc.flags << "-Wall"
  conf.cc.flags << "-Wno-format"
  conf.cc.flags << "-Wno-unused-function"
  conf.cc.flags << "-Wno-maybe-uninitialized"
  conf.cc.flags << "-ffunction-sections"
  conf.cc.flags << "-fdata-sections"

  # These defines should not contradict platform's configuration
  conf.cc.defines << "NDEBUG"
  conf.cc.defines << "MRBC_REQUIRE_32BIT_ALIGNMENT"
  conf.cc.defines << "MRBC_CONVERT_CRLF"
  conf.cc.defines << "MRBC_USE_MATH=0"
  #conf.cc.defines << "MRBC_NO_TIMER"
  conf.cc.defines << "MRBC_TICK_UNIT=1"
  conf.cc.defines << "MRBC_TIMESLICE_TICK_COUNT=10"
  conf.cc.defines << "LEMON_PICORBC"
  #conf.cc.defines << "USE_FAT_FLASH_DISK"
  #conf.cc.defines << "USE_FAT_SD_DISK"

  conf.mrubyc_hal_arm
  conf.picoruby

  #conf.gem core: "picoruby-vim"
  #conf.gem core: "picoruby-shell"

  conf.gembox "nrf"
end

