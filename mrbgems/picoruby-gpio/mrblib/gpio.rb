class GPIO
  # This is a mimic of pico_error_codes
  # from pico-sdk/src/common/pico_base/include/pico/error.h
  ERROR_NONE = 0
  ERROR_TIMEOUT = -1
  ERROR_GENERIC = -2
  ERROR_NO_DATA = -3
  ERROR_NOT_PERMITTED = -4
  ERROR_INVALID_ARG = -5
  ERROR_IO = -6

  def self.handle_error(code, name = "unknown peripheral")
    case code
    when ERROR_NONE
      return 0
    when ERROR_TIMEOUT
      raise(RuntimeError.new "Timeout error in #{name}")
    when ERROR_GENERIC
      raise(RuntimeError.new "Generic error in #{name}")
    when ERROR_NO_DATA
      raise(RuntimeError.new "No data error in #{name}")
    when ERROR_NOT_PERMITTED
      raise(RuntimeError.new "Not permitted error in #{name}")
    when ERROR_INVALID_ARG
      raise(RuntimeError.new "Invalid arg error in #{name}")
    when ERROR_IO
      raise(RuntimeError.new "IO error in #{name}")
    else
      raise(RuntimeError.new "Unknown error in #{name}. code: #{code}")
    end
  end

  def initialize(pin, flags)
    @pin = pin
    GPIO._init(pin)
    setmode(flags)
    unless @dir
      raise ArgumentError.new("You must specify one of IN, OUT and HIGH_Z")
    end
  end

  def setmode(flags)
    set_dir(flags)
    set_pull(flags)
    open_drain(flags)
  end

  # private

  def set_dir(flags)
    dir = (flags & (IN|OUT|HIGH_Z))
    return 0 if dir == 0 && !on_initialize?
    mode_dir = ((flags & IN) + ((flags & OUT)>>1) + ((flags & HIGH_Z)>>2))
    @dir = case mode_dir
    when 0
      nil
    when 1
      GPIO.set_dir_at(@pin, dir)
      dir
    else
      raise ArgumentError.new("IN, OUT and HIGH_Z are exclusive")
    end
    0
  end

  def set_pull(flags)
    pull = (flags & (PULL_UP|PULL_DOWN))
    return 0 if 0 == pull && !on_initialize?
    @pull = case pull
    when 0
      nil
    when PULL_UP
      GPIO.pull_up_at(@pin)
      PULL_UP
    when PULL_DOWN
      GPIO.pull_down_at(@pin)
      PULL_DOWN
    else
      raise ArgumentError.new("PULL_UP and PULL_DOWN are exclusive")
    end
    0
  end

  def open_drain(flags)
    @open_drain = (0 < (flags & OPEN_DRAIN))
    if on_initialize? || @open_drain
      GPIO.open_drain_at(@pin) if @open_drain
    end
    0
  end

  def on_initialize?
    @dir.nil?
  end
end

