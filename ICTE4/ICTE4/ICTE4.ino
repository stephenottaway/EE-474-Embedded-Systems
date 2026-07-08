// Filename: ICTE4.ino
// Author: Stephen Ottaway
// Date: 7/8/2026
// Description: This file creates a simple round-robin scheduler that runs three independent tasks on the ESP32s3.
// Specifically, it 1) reads the potentiometer value on the ADC pin and prints out the value, 2) sets the LED 1 frequency based on that ADC reading (variable frequency) 
// and lastly 3) blinks LED 2 at a constant frequency.

// ================= Macros =================
#define LED_PIN_COUNT 2
#define LED_ONE_PIN 1
#define LED_TWO_PIN 2
#define LED_TWO_TOGGLE_TIME_MS 500 // ms, fixed
#define ADC_PIN 3 // Assume the two relevant pins of the analog potentiometer are connected to pin 3 (which contains an ADC as needed) and ground.

// ============ Global Variables ============
int led_pins[LED_PIN_COUNT] = {LED_ONE_PIN, LED_TWO_PIN};
int led_toggle_times_ms[LED_PIN_COUNT] = {0, LED_TWO_TOGGLE_TIME_MS};
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
  pinMode(ADC_PIN, INPUT);
}

void loop() {
  uint32_t analog_pot_value = analogRead(ADC_PIN);
  Serial.println(analog_pot_value);
  led_toggle_times_ms[0] = analog_pot_value;
  blink_leds(led_pins, led_reference_times_ms, led_toggle_times_ms, led_states);
}

