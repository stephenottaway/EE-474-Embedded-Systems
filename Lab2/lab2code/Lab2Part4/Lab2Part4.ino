// Filename: Lab2Part4.ino
// Author: Stephen Ottaway
// Date: 7/6/2026
// Description: This file uses the intensity of ambient light detected in the room by a photoresistor to control the brightness of an LED; the less ambient light detected, the brighter the LED is driven (and vice-versa).

// ============= Macros =============
#define PWM_PIN 5
#define ANALOG_READ_PIN 4
#define PWM_FREQ 1000 // Hz
#define PWM_RES 12 // bits
#define MAX_DUTY_CYCLE 4095 // 2^12 - 1

// ======== Global Variables ========
uint32_t duty = 0;

// ====== Function Prototypes =======
uint32_t update_led_duty(uint8_t analog_read_pin);

// Name: update_led_duty
// Description: Converts the ADC reading of the voltage divider to an updated duty cycle to drive the LED at. At max detected light intensity the LED should be dim and at minimum detected light intensity the LED should be bright.
uint32_t update_led_duty(uint8_t analog_read_pin) {
  return MAX_DUTY_CYCLE - analogRead(analog_read_pin);
}

void setup() {
  pinMode(ANALOG_READ_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RES);
}

void loop() {
  duty = update_led_duty(ANALOG_READ_PIN);
  ledcWrite(PWM_PIN, duty);
}
