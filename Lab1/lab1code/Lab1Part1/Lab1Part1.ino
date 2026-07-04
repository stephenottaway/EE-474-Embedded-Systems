// Filename: Lab1Part1.ino
// Author: Stephen Ottaway
// Date: 06/25/2026
// Description: This file blinks two external LEDs on an ESP32 simultaneously at two frequencies set by the user.

// ================= Macros =================
#define LED_PIN_COUNT 2
#define LED_ONE_PIN 1
#define LED_TWO_PIN 2
#define LED_ONE_TOGGLE_TIME_MS 1 // ms
#define LED_TWO_TOGGLE_TIME_MS 500 // ms

// ============ Global Variables ============
int led_pins[LED_PIN_COUNT] = {LED_ONE_PIN, LED_TWO_PIN};
int led_toggle_times_ms[LED_PIN_COUNT] = {LED_ONE_TOGGLE_TIME_MS, LED_TWO_TOGGLE_TIME_MS};
bool led_states[LED_PIN_COUNT] = {true, true};
int led_reference_times_ms[LED_PIN_COUNT] = {int(millis()), int(millis())};

// =========== Function Prototypes ===========
void toggle_led_state(int led_pin, int led_reference_time_ms, int led_toggle_time_ms, bool led_state);
void blink_leds(int led_pins[], int led_reference_times_ms[], int led_toggle_times_ms[], bool led_states[]);

// Name: toggle_led_state
// Description: This function toggles the state of an LED (HIGH -> LOW or LOW -> HIGH) after led_toggle_time_ms has elapsed, then updates the reference time used for comparison.
void toggle_led_state(int led_pin, int led_reference_time_ms, int led_toggle_time_ms, bool led_state) {
  if (int(millis()) - led_reference_time_ms >= led_toggle_time_ms) {
    led_states[led_pin-1] = !led_state;
    digitalWrite(led_pin, int(led_states[led_pin-1]));
    led_reference_times_ms[led_pin-1] = (millis());
  }
}

// Name: blink_leds
// Description: This function calls the toggle_led_state function for all of the LED pins to be blinked (in this case two different LEDs).
void blink_leds(int led_pins[], int led_reference_times_ms[], int led_toggle_times_ms[], bool led_states[]) {
  for (int i = 0; i < LED_PIN_COUNT; i++) {
    toggle_led_state(led_pins[i], led_reference_times_ms[i], led_toggle_times_ms[i], led_states[i]);
  }
}

void setup() {
  for (int i = 0; i < LED_PIN_COUNT; i++) {
      pinMode(led_pins[i], OUTPUT);
      digitalWrite(led_pins[i], HIGH);
  }
}

void loop() {
  blink_leds(led_pins, led_reference_times_ms, led_toggle_times_ms, led_states);
}

