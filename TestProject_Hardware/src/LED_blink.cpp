#include <Arduino.h>

class LED {
private:
  int pin;
  unsigned long interval;
  unsigned long previousMillis;

public:
  LED(int pin, unsigned long interval) {
    this->pin = pin;
    this->interval = interval;
    this->previousMillis = 0;
    pinMode(pin, OUTPUT);
  }

  void update() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(pin, !digitalRead(pin));
    }
  }
};
