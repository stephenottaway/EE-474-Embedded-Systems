#include "driver/gpio.h"            // For GPIO driver-level macros
#include "soc/io_mux_reg.h"         // For configuring the MUX (multiplexer)
#include "soc/gpio_reg.h"           // For direct GPIO register access
#include "soc/gpio_periph.h"        // For GPIO pin definitions
#include "soc/timer_group_reg.h"

// --- Constants --- //
#define GPIO_PIN 5    // GPIO pin connected to the LED
#define GPIO_PIN_5_MASK 0x20 // 0x20 = 0b100000 (e.g. only turning on bit 5, with the LSB corresponding to index 0).
#define LED_TOGGLE_INTERVAL 1000
#define TIMER_INCREMENT_MODE (1 << 30) // Bit 30 needs to be set in the timer config register for the counter to increment up from 0.
#define TIMER_ENABLE (1 << 31) // Bit 31 needs to be set in the timer config register for the timer to be enabled.

char buff3[256];
char buff4[256];
char buff5[256];

void setup() {
  Serial.begin(9600);
  delay(5000);
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Use MUX macro to set GPIO_PIN function to GPIO
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_MASK; // Enable GPIO_PIN as an output.
  char buff1[128];
  sprintf(buff1, "GPIO_ENABLE_REG value is: %x", *((volatile uint32_t*) GPIO_ENABLE_REG));
  Serial.println(buff1);
  uint32_t timer_config = 0; // Stores 32 bits to be written to the timer config register before the timer is started.
  timer_config |= (0xFFFF << 13);
  timer_config |= TIMER_INCREMENT_MODE; // Set increment mode.
  timer_config |= TIMER_ENABLE; // Enable the timer.
  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) = timer_config; // Write the config to the timer config register.
  char buff2[128];
  sprintf(buff2, "TIMG_T0CONFIG_REG(0) value is: %x", *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)));
  Serial.println(buff2);
  //*((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (1 << 31); // Trigger a timer update to load settings.
}

void loop() {
  *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (1 << 31); // Trigger a timer update to load settings.
  static uint32_t last_toggle_time = 0; // Track last toggle time.
  uint32_t current_time = *((volatile uint32_t*) TIMG_T0LO_REG(0)); // Read current timer value.
  sprintf(buff5, "TIMG_T0LO_REG(0) value is: %x", current_time);
  Serial.println(buff5);
  if ((current_time - last_toggle_time >= LED_TOGGLE_INTERVAL)) { // Check if toggle interval has passed.
    uint32_t gpio_out = *((volatile uint32_t*) GPIO_OUT_REG); // Read current GPIO output state.
    sprintf(buff3, "Initially GPIO_OUT_REG value is: %x", gpio_out);
    Serial.println(buff3);
    *((volatile uint32_t*) GPIO_OUT_REG) = gpio_out ^ GPIO_PIN_5_MASK; // Toggle GPIO_PIN using XOR.
    sprintf(buff4, "After XOR operation GPIO_OUT_REG value is: %x", *((volatile uint32_t*) GPIO_OUT_REG));
    Serial.println(buff4);
    last_toggle_time = current_time; // Update last_toggle_time.
    //*((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (1 << 31); // Refresh timer counter value.
  }
}