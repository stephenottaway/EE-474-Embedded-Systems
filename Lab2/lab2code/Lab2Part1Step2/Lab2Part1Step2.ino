// Filename: Lab2Part2.ino
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file measures and compares the time it takes to change the output voltage on a pin from HIGH to LOW using a) Arduino library functions (digitalWrite()) and b) direct register access.

// ============ Includes ============
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"

// ============= Macros =============
#define GPIO_PIN 5 // GPIO5
#define GPIO_PIN_5_SET_MASK (1 << 5) // GPIO5 is the fifth LSB.
#define REPETITIONS 1000

// ====== Function Prototypes =======
unsigned long measure_arduino_time(uint8_t gpio_pin, uint32_t repetitions);
unsigned long measure_register_time(uint8_t gpio_pin, uint32_t repetitions); 
void compare_measured_times(uint8_t gpio_pin, uint32_t repetitions);

// Name: measure_arduino_time
// Description: Returns the total time (in microseconds) for the specified pin to be turned ON and then OFF the number of times specified by the repetitions parameter using the Arduino library digitalWrite() function. 
unsigned long measure_arduino_time(uint8_t gpio_pin, uint32_t repetitions) {
  unsigned long measured_time = 0;
  unsigned long reference_time = 0;
  for (int i = 0; i < repetitions; i++) {
    reference_time = micros();
    digitalWrite(GPIO_PIN, HIGH);
    digitalWrite(GPIO_PIN, LOW);
    measured_time += (micros() - reference_time);
  }
  return measured_time;
}

// Name: measure_register_time
// Description: Returns the total time (in microseconds) for the specified pin to be turned ON and then OFF the number of times specified by the repetitions parameter using direct register access.
unsigned long measure_register_time(uint8_t gpio_pin, uint32_t repetitions) {
  unsigned long measured_time = 0;
  unsigned long reference_time = 0;
  for (int i = 0; i < repetitions; i++) {
    reference_time = micros();
    *((volatile uint32_t*) GPIO_OUT_REG) |= GPIO_PIN_5_SET_MASK; // Set pin 5 to output 1 (HIGH voltage) while leaving all other pins unchanged.
    *((volatile uint32_t*) GPIO_OUT_REG) &= ~GPIO_PIN_5_SET_MASK; // Set pin 5 to output 0 (LOW voltage) while leaving all other pins unchanged.
    measured_time += (micros() - reference_time);
  }
  return measured_time;
}

// Name: compare_measured_times
// Description: Calls the measure_arduino_time() and measure_register_time() functions and prints a buffer to the Serial monitor comparing the two elapsed times for the specified number of repetitions.
void compare_measured_times(uint8_t gpio_pin, uint32_t repetitions) {
  unsigned long measured_arduino_time = measure_arduino_time(gpio_pin, repetitions);
  unsigned long measured_register_time = measure_register_time(gpio_pin, repetitions);
  char buffer[256];
  sprintf(buffer, "For %d repetitions turning pin %d ON and then immediately turning it OFF, the digitalWrite() implementation took %d microseconds while the register implementation took %d microseconds.", (int) repetitions, (int) gpio_pin, (int) measured_arduino_time, (int) measured_register_time);
  Serial.println(buffer);
}

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO); // Select pin 5 to be a GPIO pin using the pin multiplex macro.
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_5_SET_MASK; // Enable pin 5 as an output pin while leaving all other pins unchanged.
  Serial.begin(9600);
  delay(5000); // Wait for five seconds before running measurements and comparing them.
  compare_measured_times((uint8_t) GPIO_PIN, (uint32_t) REPETITIONS);
}

void loop() {
  // Nothing needed here since we only care about doing one comparison, therefore that code is in the setup() function.
}
