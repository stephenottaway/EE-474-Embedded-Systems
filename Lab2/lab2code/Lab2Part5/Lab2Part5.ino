// Filename: Lab2Part5.ino
// Author: Stephen Ottaway
// Date: 7/7/2026
// Description: This file uses timer logic to produce a one-time LED blinking sequence at a low, medium, and high frequency for a certain duration once the ambient light drops below a certain threshold.

// ============ Includes ============
#include "driver/ledc.h"

// ============= Macros =============
#define PWM_PIN 5
#define ANALOG_READ_PIN 4
#define PWM_RES 14 // bits
#define PWM_DUTY 2048 // Roughly ((2^12)-1)/2 to give a 50% duty cycle.
#define ADC_LOW_THRESHOLD 1024 // 2^10, reading this value or below means there is relatively little ambient light.
#define TOTAL_BLINKING_TIME 15000 // ms
#define BLINKING_TIME_ONE_FREQUENCY TOTAL_BLINKING_TIME/3 // ms

// ======== Global Variables ========
bool adc_low_threshold_met = false;
uint32_t low_freq = 4; // Hz
uint32_t mid_freq = 8; // Hz
uint32_t high_freq = 16; // Hz

// ====== Function Prototypes =======
bool light_below_threshold(uint8_t analog_read_pin);
void drive_led_low();
void drive_led_at_freq_for_time_interval(uint32_t freq);
void run_led_sequence(uint32_t low_freq, uint32_t mid_freq, uint32_t high_freq);

// Name: light_below_threshold
// Description: Checks if the ADC reading (proportional to the intensity of light incident on the photoresistor) is below the threshold required to trigger the LED blinking sequence to commence.
bool light_below_threshold(uint8_t analog_read_pin) {
  return (analogRead(analog_read_pin) <= ADC_LOW_THRESHOLD);
} 

// Name: drive_led_low
// Description: Using the ledc library functions drive the LED low (e.g. with a 0% duty cycle) when the ambient light detected is above the threshold required for the one-time light sequence to be triggered.
void drive_led_low() {
  ledcAttach(PWM_PIN, 0, PWM_RES);
  ledcWrite(PWM_PIN, 0);
}

// Name: drive_led_at_freq_for_time_interval
// Description: Blink LED at specified frequency for a third of the total time interval comprising the one-time light sequence. Either the low, mid, or high frequency can be passed into the function accordingly.
void drive_led_at_freq_for_time_interval(uint32_t freq) {
  ledcAttach(PWM_PIN, freq, PWM_RES);
  long reference_time = millis();
  while ((millis() - reference_time) <= BLINKING_TIME_ONE_FREQUENCY) {
    ledcWrite(PWM_PIN, PWM_DUTY);
  }
  ledcDetach(PWM_PIN);
}

// Name: run_led_sequence
// Description: Runs the one-time LED sequence with the LED blinking at 1) slow, 2) medium, and lastly 3) high blinking frequencies for a certain time interval (a third of the total time for the one-time sequence in each case).
void run_led_sequence(uint32_t low_freq, uint32_t mid_freq, uint32_t high_freq) {
  drive_led_at_freq_for_time_interval(low_freq);
  drive_led_at_freq_for_time_interval(mid_freq);
  drive_led_at_freq_for_time_interval(high_freq);
}

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_READ_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  Serial.println(analogRead(ANALOG_READ_PIN));
  adc_low_threshold_met = light_below_threshold(ANALOG_READ_PIN);
  Serial.println(adc_low_threshold_met);
  delay(500);
  if (adc_low_threshold_met) {
    run_led_sequence(low_freq, mid_freq, high_freq);
    adc_low_threshold_met = false; // Reset this flag so that the led sequence only runs once per threshold detection occurrence.
  }
  else {
    drive_led_low();
  }
}
