#include "driver/gpio.h"            // For GPIO driver-level macros
#include "soc/io_mux_reg.h"         // For configuring the MUX (multiplexer)
#include "soc/gpio_reg.h"           // For direct GPIO register access
#include "soc/gpio_periph.h"        // For GPIO pin definitions

// --- Constants --- //
#define GPIO_PIN 5    // GPIO pin connected to the LED
#define GPIO_PIN_5_MASK 0x20 // 0x20 = 0b100000 (e.g. only turning on bit 5, with the LSB corresponding to index 0).

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_MASK;
}

void loop() {
  *((volatile uint32_t*) GPIO_OUT_REG) |= GPIO_PIN_5_MASK;
  // Wait for 1 second
  delay(1000);
  *((volatile uint32_t*) GPIO_OUT_REG) &= ~GPIO_PIN_5_MASK;
  // Wait again
  delay(1000);
}