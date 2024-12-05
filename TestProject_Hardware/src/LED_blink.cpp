#include <Arduino.h>

// LED class definition
class LED {
private:
  int pin;        // Pin number for the LED
  unsigned long interval; // Blink interval (milliseconds)
  unsigned long previousMillis; // Store last time LED was updated

public:
  // Constructor to initialize the LED
  LED(int pin, unsigned long interval) {
    this->pin = pin;
    this->interval = interval;
    this->previousMillis = 0;  // Initialize time to 0
    pinMode(pin, OUTPUT);      // Set the LED pin as an output
  }

  // Method to update the LED state
  void update() {
    unsigned long currentMillis = millis(); // Get the current time

    if (currentMillis - previousMillis >= interval) {
      // Save the last time LED was updated
      previousMillis = currentMillis;

      // Toggle the LED
      digitalWrite(pin, !digitalRead(pin));
    }
  }
};

