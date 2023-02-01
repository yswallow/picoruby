#include <stdbool.h>
#include <mrubyc.h>
#include "../include/gpio.h"

#define GETIV(str)       mrbc_instance_getiv(&v[0], mrbc_str_to_symid(#str))
#define READ(pin)        GPIO_read(pin_num(vm, pin))
#define WRITE(pin, val)  GPIO_write(pin_num(vm, pin), val)

static int
pin_num(mrbc_vm *vm, mrbc_value pin)
{
  switch (mrbc_type(pin)) {
    case MRBC_TT_INTEGER: {
      return pin.i;
    }
    case MRBC_TT_STRING: {
      return GPIO_pin_num_from_char(pin.string->data);
    }
    default:
      mrbc_raise(vm, MRBC_CLASS(ArgumentError), "Wrong GPIO pin value");
      return -1;
  }
}

/*
 * GPIO._init(pin)
 */
static void
c__init(mrbc_vm *vm, mrbc_value *v, int argc)
{
  int pin_number = pin_num(vm, v[1]);
  if (-1 < pin_number) GPIO_init(pin_number);
  SET_INT_RETURN(0);
}

/*
 * GPIO._set_dir(pin, dir)
 */
static void
c__set_dir(mrbc_vm *vm, mrbc_value *v, int argc)
{
  GPIO_set_dir(pin_num(vm, v[1]), GET_INT_ARG(2));
  SET_INT_RETURN(0);
}

/*
 * GPIO._set_open_drain(pin)
 */
static void
c__set_open_drain(mrbc_vm *vm, mrbc_value *v, int argc)
{
  GPIO_set_open_drain(pin_num(vm, v[1]));
  SET_INT_RETURN(0);
}

/*
 * GPIO._set_pull(pin, pull)
 */
static void
c__set_pull(mrbc_vm *vm, mrbc_value *v, int argc)
{
  GPIO_set_pull(pin_num(vm, v[1]), GET_INT_ARG(2));
  SET_INT_RETURN(0);
}

/*
 * GPIO.high_at?(pin)
 */
static void
c_high_at_q(mrbc_vm *vm, mrbc_value *v, int argc)
{
  if (READ(v[1]) == 0) {
    SET_FALSE_RETURN();
  } else {
    SET_TRUE_RETURN();
  }
}

/*
 * GPIO.high?(pin)
 */
static void
c_high_q(mrbc_vm *vm, mrbc_value *v, int argc)
{
  if (READ(GETIV(pin)) == 0) {
    SET_FALSE_RETURN();
  } else {
    SET_TRUE_RETURN();
  }
}

/*
 * GPIO.low_at?(pin)
 */
static void
c_low_at_q(mrbc_vm *vm, mrbc_value *v, int argc)
{
  if (READ(v[1]) == 0) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

/*
 * GPIO.low?(pin)
 */
static void
c_low_q(mrbc_vm *vm, mrbc_value *v, int argc)
{
  if (READ(GETIV(pin)) == 0) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

/*
 * GPIO.read_at(pin)
 */
static void
c_read_at(mrbc_vm *vm, mrbc_value *v, int argc)
{
  SET_INT_RETURN(READ(v[1]));
}

/*
 * GPIO.read(pin)
 */
static void
c_read(mrbc_vm *vm, mrbc_value *v, int argc)
{
  SET_INT_RETURN(READ(GETIV(pin)));
}

/*
 * GPIO.write_at(pin, val)
 */
static void
c_write_at(mrbc_vm *vm, mrbc_value *v, int argc)
{
  WRITE(v[1], GET_INT_ARG(2));
  SET_INT_RETURN(0);
}

/*
 * GPIO#write(val)
 */
static void
c_write(mrbc_vm *vm, mrbc_value *v, int argc)
{
  WRITE(GETIV(pin), GET_INT_ARG(1));
  SET_INT_RETURN(0);
}

void
mrbc_gpio_init(void)
{
  mrbc_class *mrbc_class_GPIO = mrbc_define_class(0, "GPIO", mrbc_class_object);

  mrbc_set_const(mrbc_str_to_symid("IN"), &mrbc_integer_value(IN));
  mrbc_set_const(mrbc_str_to_symid("OUT"), &mrbc_integer_value(OUT));
  mrbc_set_const(mrbc_str_to_symid("HIGH_Z"), &mrbc_integer_value(HIGH_Z));
  mrbc_set_const(mrbc_str_to_symid("PULL_UP"), &mrbc_integer_value(PULL_UP));
  mrbc_set_const(mrbc_str_to_symid("PULL_DOWN"), &mrbc_integer_value(PULL_DOWN));
  mrbc_set_const(mrbc_str_to_symid("OPEN_DRAIN"), &mrbc_integer_value(OPEN_DRAIN));

  mrbc_define_method(0, mrbc_class_GPIO, "_init", c__init);
  mrbc_define_method(0, mrbc_class_GPIO, "_set_dir", c__set_dir);
  mrbc_define_method(0, mrbc_class_GPIO, "_set_pull", c__set_pull);
  mrbc_define_method(0, mrbc_class_GPIO, "_set_open_drain", c__set_open_drain);
  mrbc_define_method(0, mrbc_class_GPIO, "high_at?", c_high_at_q);
  mrbc_define_method(0, mrbc_class_GPIO, "high?", c_high_q);
  mrbc_define_method(0, mrbc_class_GPIO, "low_at?", c_low_at_q);
  mrbc_define_method(0, mrbc_class_GPIO, "low?", c_low_q);
  mrbc_define_method(0, mrbc_class_GPIO, "read_at", c_read_at);
  mrbc_define_method(0, mrbc_class_GPIO, "read", c_read);
  mrbc_define_method(0, mrbc_class_GPIO, "write_at", c_write_at);
  mrbc_define_method(0, mrbc_class_GPIO, "write", c_write);
}

