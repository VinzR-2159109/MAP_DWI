#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

class I2CScanner {
public:
  // Constructor
  I2CScanner(uint8_t sdaPin, uint8_t sclPin) : sdaPin(sdaPin), sclPin(sclPin) {}

  // Initialize pins and Wire library
  void begin() {
    pinMode(sdaPin, INPUT_PULLUP);
    pinMode(sclPin, INPUT_PULLUP);
    Wire.begin();
    Serial.begin(115200);
  }

  // Perform the I2C scan
  void scan() {
    Serial.println("Scanning...");
    uint8_t error, address;
    int devices = 0;

    for (address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
        Serial.print("Device found at 0x");
        if (address < 16) Serial.print("0");
        Serial.println(address, HEX);
        devices++;
      }
    }

    if (devices == 0) {
      Serial.println("No devices found.");
    } else {
      Serial.println("Scan complete.");
    }
  }

private:
  uint8_t sdaPin;
  uint8_t sclPin;
};

// I2CScanner scanner(20, 21);

// void setup() {
//   scanner.begin();
// }

// void loop() {
//   scanner.scan();
//   delay(5000);
// }
