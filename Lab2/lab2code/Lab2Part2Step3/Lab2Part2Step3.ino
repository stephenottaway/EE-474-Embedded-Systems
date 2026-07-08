// Filename: Lab2Part2Step3.ino
// Author: Stephen Ottaway
// Date: 7/8/2026
// Description: This file directly interacts with the ESP32's timer registers to control an LED (e.g. turn it ON and then OFF at a specified frequency).

// ============ Includes ============
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"

// ============= Macros =============
#define GPIO_PIN 5 // GPIO1
#define GPIO_PIN_5_SET_MASK (1 << 5) // GPIO5 is the fifth LSB.
#define LED_TOGGLE_INTERVAL 250
#define TIMER_INCREMENT_MODE (1 << 30) // Bit 30 needs to be set in the timer config register for the counter to increment up from 0.
#define TIMER_ENABLE (1 << 31) // Bit 31 needs to be set in the timer config register for the timer to be enabled.

// ====== Function Prototypes =======
void config_timer_reg();
void blink_led_with_timer_reg();

// Name: config_timer_reg
// Description: Sets the enable and increment mode bits in a config variable before writing that variable to the TIMG_T0CONFIG register to start the timer.
void config_timer_reg() {
  uint32_t timer_config = 0; // Stores 32 bits to be written to timer config register before the timer is started (enabled).
  timer_config |= TIMER_INCREMENT_MODE; // Set increment mode.
  timer_config |= TIMER_ENABLE; // Enable the timer.
  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) = timer_config; // Write the config to the timer config register.
}

// Name: blink_led_with_timer_reg
// Description: Latches the current timer value by writing to the TIMG_T0UPDATE register, reads that value, and if the toggle interval has elapsed, flips the GPIO 5 output register bit (turning on/off the LED) and
// updates the last toggle time.
void blink_led_with_timer_reg() {
  *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (1 << 31); // Trigger a timer update to load settings.
  static uint32_t last_toggle_time = 0; // Track last toggle time.
  uint32_t current_time = *((volatile uint32_t*) TIMG_T0LO_REG(0)); // Read current timer value.
  if ((current_time - last_toggle_time >= LED_TOGGLE_INTERVAL)) { // Check if toggle interval has passed.
    uint32_t gpio_out = *((volatile uint32_t*) GPIO_OUT_REG); // Read current GPIO output state.
    *((volatile uint32_t*) GPIO_OUT_REG) = gpio_out ^ GPIO_PIN_5_SET_MASK; // Toggle GPIO_PIN using XOR.
    last_toggle_time = current_time; // Update last_toggle_time.
  }
}

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Use MUX macro to set GPIO_PIN function to GPIO.
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_SET_MASK; // Enable pin 5 as an output pin while leaving all other pins unchanged.
  config_timer_reg();
}

void loop() {
  blink_led_with_timer_reg();
}
