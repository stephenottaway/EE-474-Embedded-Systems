// Filename: Lab2Part3.ino
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file directly interacts with the ESP32's timer registers to control an LED (e.g. turn it ON and then OFF at a specified frequency).

// ============ Includes ============
#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"

// ============= Macros =============
#define GPIO_PIN 1 // GPIO1
#define GPIO_PIN_1_SET_MASK 0x00000002 // 0x00000002 = 0b00000000 00000000 00000000 00000010 as GPIO1 is the second LSB.
//#define PRESCALER 0x50 // 80 in decimal. APB_CLK frequency is 80 MHz, so with prescaler of 80 TB_CLK frequency is 80 MHz / 80 = 1 MHz. 
#define PRESCALER 0x00000001
#define TIMER_COUNT_TOGGLE_THRESHOLD 170

char buff4[256];
uint32_t current_timer_count = 0;
uint32_t current_toggle_threshold = 0;
bool led_state = false;

void setup() {
  //PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
  //*((volatile uint32_t*) GPIO_ENABLE_REG) |= GPIO_PIN_1_SET_MASK; // Enable pin 1 as an output pin while leaving all other pins unchanged.
  pinMode(GPIO_PIN, OUTPUT);
  Serial.begin(9600);

  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) |= (0 << 9); // Set Group 0 Timer 0 configuration register source clock field (bit 9) to 0 to use APB_CLK.
  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) |= (PRESCALER << 13); // Set Group 0 Timer 0 configuration register divider field (bits 13-28) to PRESCALER.
  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) |= (1 << 30); // Set Group 0 Timer 0 configuration register increment/decrement field (bit 30) to 1 to increment.

  delay(5000);
  *((volatile uint32_t*) TIMG_T0LOADLO_REG(0)) |= 0; // Set Group 0 Timer 0 control register reload value for low 32 bits to 0 (e.g. set the starting value for the timer to 0).
  char buff1[128];
  sprintf(buff1, "Low 32 bits of timer register reload value is %x", *((volatile uint32_t*) TIMG_T0LOADLO_REG(0)));
  Serial.println(buff1);
  *((volatile uint32_t*) TIMG_T0LOADHI_REG(0)) |= 0; // Set Group 0 Timer 0 control register reload value for high 22 bits to 0 (e.g. set the starting value for the timer to 0).
  char buff2[128];
  sprintf(buff2, "High 22 bits of timer register reload value is %x", *((volatile uint32_t*) TIMG_T0LOADHI_REG(0)));
  Serial.println(buff2);
  *((volatile uint32_t*) TIMG_T0LOAD_REG(0)) |= 1; // Write any value (1 in this case) to Group 0 Timer 0 control register to trigger a timer 0 time-base counter reload (e.g. loading in the above two reload values to the LO and HI registers).
  *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (0 << 31); // Latch Group 0 Timer 0's current value by writing 0 to bit 31 (the update field).
  char buff3[256];
  sprintf(buff3, "After triggering reload by setting update reg to %x, the low bits should be %x and are actually %x, while the high bits should be %x and are actually %x", *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)), *((volatile uint32_t*) TIMG_T0LOADLO_REG(0)), *((volatile uint32_t*) TIMG_T0LO_REG(0)), *((volatile uint32_t*) TIMG_T0LOADHI_REG(0)), *((volatile uint32_t*) TIMG_T0HI_REG(0)));
  Serial.println(buff3);


  *((volatile uint32_t*) TIMG_T0CONFIG_REG(0)) |= (1 << 31); // Set Group 0 Timer 0 configuration register time-base counter enable field (bit 31) to 1 to enable the counter (e.g. start the timer).
  digitalWrite(GPIO_PIN, led_state);
}


void loop() {
  *((volatile uint32_t*) TIMG_T0UPDATE_REG(0)) |= (0 << 31); // Latch Group 0 Timer 0's current value by writing 0 to bit 31 (the update field).
  current_timer_count = *((volatile uint32_t*) TIMG_T0LO_REG(0));
  if (current_timer_count > current_toggle_threshold) {
    led_state = !led_state;
    Serial.println(led_state);
    digitalWrite(GPIO_PIN, led_state);
    current_toggle_threshold += TIMER_COUNT_TOGGLE_THRESHOLD;
  }
  sprintf(buff4, "timer low bits are currently equal to %u, count threshold is currently equal to %u", current_timer_count, current_toggle_threshold);
  Serial.println(buff4);
}
