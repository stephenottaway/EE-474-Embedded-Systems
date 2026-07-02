// Filename: Lab1Part3.ino
// Author: Stephen Ottaway
// Date: 06/25/2026
// Description: This file allows two initially blinking LEDs to be individually turned off by tactile switches. 
// If a switch is pressed (not held), the LED turns off and stays off until the switch is pressed again, resulting in the blinking resuming.

// ============ Macros ============
#define LED_PIN_COUNT 2
#define LED_ONE_PIN 1
#define LED_TWO_PIN 2
#define LED_ONE_TOGGLE_TIME_MS 1000 // ms
#define LED_TWO_TOGGLE_TIME_MS 500 // ms
#define PULL_DOWN_ONE_PIN 6
#define PULL_DOWN_TWO_PIN 7
#define PULL_DOWN_PIN_ARRAY_OFFSET 6

// ============ Global Variables ============
int pull_down_pins[LED_PIN_COUNT] = {PULL_DOWN_ONE_PIN, PULL_DOWN_TWO_PIN};
int led_pins[LED_PIN_COUNT] = {LED_ONE_PIN, LED_TWO_PIN};
int led_toggle_times_ms[LED_PIN_COUNT] = {LED_ONE_TOGGLE_TIME_MS, LED_TWO_TOGGLE_TIME_MS};
bool buttons_pressed[LED_PIN_COUNT] = {false, false};
bool buttons_released[LED_PIN_COUNT] = {false, false};
bool led_blinking[LED_PIN_COUNT] = {true, true}; 
bool led_states[LED_PIN_COUNT] = {true, true};
int led_reference_times_ms[LED_PIN_COUNT] = {int(millis()), int(millis())};

// =========== Function Prototypes ===========
void check_if_button_pressed(int pull_down_pin);
void check_if_button_released(int pull_down_pin);
bool button_pressed_and_released(int pull_down_pin);
void drive_led_state(int pull_down_pin, int led_pin, int led_reference_time_ms, int led_toggle_time_ms, bool led_state);
void drive_leds(int pull_down_pins[], int led_pins[], int led_reference_times_ms[], int led_toggle_times_ms[], bool led_states[]);

// Name: check_if_button_pressed
// Description: This function checks if a button has been pressed and updates the buttons_pressed states array if so.
void check_if_button_pressed(int pull_down_pin) {
  if (digitalRead(pull_down_pins[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET]) == HIGH) {
    buttons_pressed[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] = true;
  }
}

// Name: check_if_button_released
// Description: This function checks if a button has been released after it was pressed and updates the buttons_released states array if so.
void check_if_button_released(int pull_down_pin) {
  if (digitalRead(pull_down_pins[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET]) == LOW && buttons_pressed[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] == true) {
    buttons_released[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] = true;
  }
}

// Name: button_pressed_and_released
// Description: This function checks if a button has been pressed and subsequently released (the condition required to go from blinking -> off or vice-versa for a LED).
bool button_pressed_and_released(int pull_down_pin) {
  return buttons_pressed[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] && buttons_released[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET];
}

// Name: drive_led_state
// Description: This function drives the state of an LED, either toggling (HIGH -> LOW or LOW -> HIGH) it's state or driving it LOW always based on a button press event.
void drive_led_state(int pull_down_pin, int led_pin, int led_reference_time_ms, int led_toggle_time_ms, bool led_state) {
  if (int(millis()) - led_reference_time_ms >= led_toggle_time_ms) {
    if (button_pressed_and_released(pull_down_pin)) {
      buttons_pressed[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] = false;
      buttons_released[pull_down_pin-PULL_DOWN_PIN_ARRAY_OFFSET] = false;
      led_blinking[led_pin-1] = !led_blinking[led_pin-1];
    }
    if (led_blinking[led_pin-1]) {
      led_states[led_pin-1] = !led_states[led_pin-1];
    }
    else {
      led_states[led_pin-1] = false;
    }
    digitalWrite(led_pin, int(led_states[led_pin-1]));
    led_reference_times_ms[led_pin-1] = int(millis());
  }
}

// Name: blink_leds
// Description: This function calls the drive_led_state function for the two different LED and uses the button state (press and release) to set the LED state.
void drive_leds(int pull_down_pins[], int led_pins[], int led_reference_times_ms[], int led_toggle_times_ms[], bool led_states[]) {
  for (int i = 0; i < LED_PIN_COUNT; i++) {
    check_if_button_pressed(pull_down_pins[i]);
    check_if_button_released(pull_down_pins[i]);
    drive_led_state(pull_down_pins[i], led_pins[i], led_reference_times_ms[i], led_toggle_times_ms[i], led_states[i]);
  }
}

void setup() {
  for (int i = 0; i < LED_PIN_COUNT; i++) {
      pinMode(pull_down_pins[i], INPUT);
      pinMode(led_pins[i], OUTPUT);
      digitalWrite(led_pins[i], HIGH);
  }
}

void loop() {
  drive_leds(pull_down_pins, led_pins, led_reference_times_ms, led_toggle_times_ms, led_states);
}





