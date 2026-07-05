// Filename: ICTE2Part2.ino
// Author: Stephen Ottaway
// Date: 7/5/2026
// Description: This file blinks an LED by setting a GPIO pin directly using registers (both enabling it as an output and setting and clearing it's output register) and a simple timing mechanism (accessed directly through registers).

#include "driver/gpio.h"            // For GPIO driver-level macros
#include "soc/io_mux_reg.h"         // For configuring the MUX (multiplexer)
#include "soc/gpio_reg.h"           // For direct GPIO register access
#include "soc/gpio_periph.h"        // For GPIO pin definitions
#include "soc/timer_group_reg.h"    // For timer register access

// --- Constants --- //
#define GPIO_PIN 5    // GPIO pin connected to the LED
#define GPIO_PIN_5_MASK 0x20 // 0x20 = 0b100000 (e.g. only turning on bit 5, with the LSB corresponding to index 0).
#define LED_TOGGLE_INTERVAL 1000
#define TIMER_INCREMENT_MODE (1 << 30) // Bit 30 needs to be set in the timer config register for the counter to increment up from 0.
#define TIMER_ENABLE (1 << 31) // Bit 31 needs to be set in the timer config register for the timer to be enabled.

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Use MUX macro to set GPIO_PIN function to GPIO
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_MASK; // Enable GPIO_PIN as an output.
  uint32_t timer_config = 0; // Stores 32 bits to be written to the timer config register before the timer is started.
  timer_config |= TIMER_INCREMENT_MODE; // Set increment mode.
  timer_config |= TIMER_ENABLE; // Enable the timer.
  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) = timer_config; // Write the config to the timer config register.
}

void loop() {
  *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (1 << 31); // Trigger a timer update to load settings.
  static uint32_t last_toggle_time = 0; // Track last toggle time.
  uint32_t current_time = *((volatile uint32_t*) TIMG_T0LO_REG(0)); // Read current timer value.
  if ((current_time - last_toggle_time >= LED_TOGGLE_INTERVAL)) { // Check if toggle interval has passed.
    uint32_t gpio_out = *((volatile uint32_t*) GPIO_OUT_REG); // Read current GPIO output state.
    *((volatile uint32_t*) GPIO_OUT_REG) = gpio_out ^ GPIO_PIN_5_MASK; // Toggle GPIO_PIN using XOR.
    last_toggle_time = current_time; // Update last_toggle_time.
  }
}