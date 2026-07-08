// Filename: Lab2Part1Step1.ino
// Author: Stephen Ottaway
// Date: 7/8/2026
// Description: This file blinks an external LED by directly manipulating hardware GPIO registers and using bitwise operations. 

// ============ Includes ============
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"

// ============= Macros =============
#define GPIO_PIN 5 // GPIO5
#define GPIO_PIN_5_SET_MASK (1 << 5) // GPIO 5 is 5th LSB
#define TOGGLE_INTERVAL 1000 // ms

// ======== Global Variables ========
bool toggle_high = true;
long reference_time = 0;
bool update_reference_time = false;

// ====== Function Prototypes =======
void blink_led(long reference_time, uint32_t toggle_interval, bool toggle_high);

// Name: blink_led
// Description: Toggles the LED between the ON and OFF state every time the toggle_interval has elapsed by directly setting and clearing the gpio pins output register bit.
void blink_led(long reference_time, uint32_t toggle_interval, bool toggle_high) {
  if ((millis() - reference_time) >= toggle_interval) {
    if (toggle_high) {
      *((volatile uint32_t*) GPIO_OUT_REG) |= GPIO_PIN_5_SET_MASK; // Set pin 5 to output 1 (HIGH voltage) while leaving all other pins unchanged.
    }
    else {
      *((volatile uint32_t*) GPIO_OUT_REG) &= ~GPIO_PIN_5_SET_MASK; // Set pin 5 to output 0 (LOW voltage) while leaving all other pins unchanged.
    }
    update_reference_time = true; // Update the reference time to reset the toggle interval.
  }
  else {
    update_reference_time = false; // Wait for the toggle interval to elapse before updating the reference time.
  }
}

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Select pin 5 to be a GPIO pin using the pin multiplex macro.
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_SET_MASK; // Enable pin 5 as an output pin while leaving all other pins unchanged.
}

void loop() {
  if (update_reference_time) {
    reference_time = millis();
    toggle_high = !toggle_high;
  }
  blink_led(reference_time, TOGGLE_INTERVAL, toggle_high);
}
