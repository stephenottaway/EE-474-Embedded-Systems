// Filename: Lab1Part2.ino
// Author: Stephen Ottaway
// Date: 06/25/2026
// Description: This file turns on an external LED when a button is pressed and held, otherwise the LED stays off.
// GPIO pin 4 is configured as a pull-down pin with a 10k ohm pull-down resistor and GPIO pin 5 drives the LED with a 220 ohm current-limiting resistor.

// ============ Macros ============
#define PULL_DOWN_PIN 4
#define LED_PIN 5

void setup() {
  pinMode(PULL_DOWN_PIN, INPUT); // pull-down GPIO pin
  pinMode(LED_PIN, OUTPUT); // LED GPIO pin
}

void loop() {
  if (digitalRead(PULL_DOWN_PIN) == HIGH) { // Button is pressed.
    digitalWrite(LED_PIN, HIGH); // Turn the LED on.
  } 
  else {
    digitalWrite(LED_PIN, LOW); // Keep the LED off.
  }
}
