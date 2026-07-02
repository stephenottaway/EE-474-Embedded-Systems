// Filename: Lab2Part1.ino
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file blinks an external LED by directly manipulating hardware GPIO registers and using bitwise operations. 

// ============ Includes ============
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"

// ============= Macros =============
#define GPIO_PIN 1 // GPIO1
#define GPIO_PIN_1_SET_MASK 0x00000002 // 0x00000002 = 0b00000000 00000000 00000000 00000010 as GPIO1 is the second LSB.

void setup() {
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
  *((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_1_SET_MASK; // Enable pin 1 as an output pin while leaving all other pins unchanged.
}

void loop() {
  *((volatile uint32_t*) GPIO_OUT_REG) |= GPIO_PIN_1_SET_MASK; // Set pin 1 to output 1 (HIGH voltage) while leaving all other pins unchanged. 
  delay(1000);
  *((volatile uint32_t*) GPIO_OUT_REG) &= ~GPIO_PIN_1_SET_MASK; // Set pin 1 to output 0 (LOW voltage) while leaving all other pins unchanged.
  delay(1000);
}
