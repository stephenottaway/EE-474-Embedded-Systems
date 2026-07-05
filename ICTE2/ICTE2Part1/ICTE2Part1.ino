// Filename: ICTE2Part1.ino
// Author: Stephen Ottaway
// Date: 7/5/2026
// Description: This file blinks an LED by setting a GPIO pin directly using registers (both enabling it as an output and setting and clearing it's output register) and using the Arduino delay() macro.

#include "driver/gpio.h"            // For GPIO driver-level macros
#include "soc/io_mux_reg.h"         // For configuring the MUX (multiplexer)
#include "soc/gpio_reg.h"           // For direct GPIO register access
#include "soc/gpio_periph.h"        // For GPIO pin definitions

// --- Constants --- //
#define GPIO_PIN 5    // GPIO pin connected to the LED
#define GPIO_PIN_5_MASK 0x20 // 0x20 = 0b100000 (e.g. only turning on bit 5, with the LSB corresponding to index 0).

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Set the pin function to GPIO.
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_MASK; // Enable the GPIO pin as an output.
}

void loop() {
  *((volatile uint32_t*) GPIO_OUT_REG) |= GPIO_PIN_5_MASK; // Set the GPIO pins output register bit.
  // Wait for 1 second
  delay(1000);
  *((volatile uint32_t*) GPIO_OUT_REG) &= ~GPIO_PIN_5_MASK; // Clear the GPIO pins output register bit.
  // Wait again
  delay(1000);
}