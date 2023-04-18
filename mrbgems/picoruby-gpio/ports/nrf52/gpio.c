#include <stdint.h>
#include <stdbool.h>
#include "nrf_gpio.h"

#include "../../include/gpio.h"

int
GPIO_pin_num_from_char(const uint8_t *str)
{
  /* Not supported */
  return -1;
}

void
GPIO_init(uint8_t pin)
{
  // not needed
}

void
GPIO_set_dir(uint8_t pin, uint8_t dir)
{
  switch (dir) {
    case (IN):
      nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);
      break;
    case (OUT):
      nrf_gpio_cfg_output(pin);
      break;
    case (HIGH_Z):
      /* HIGH_Z is not supported */
      break;
  }
}

void
GPIO_open_drain(uint8_t pin)
{
  /* Not supported */
}

void
GPIO_pull_up(uint8_t pin)
{
  nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLUP);
}

void
GPIO_pull_down(uint8_t pin)
{
  nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLDOWN);
}

int
GPIO_read(uint8_t pin)
{
  return nrf_gpio_pin_read(pin);
}

void
GPIO_write(uint8_t pin, uint8_t val)
{
  if(val) {
    nrf_gpio_pin_set(pin);
  } else {
    nrf_gpio_pin_clear(pin);
  }
  
}
