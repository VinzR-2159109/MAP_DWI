#include "LED_blink.cpp"
#include "LCD_I2C.cpp"
#include <Wire.h>

// Create an LED object for pin 13, with a 1-second blink interval
LED led(13, 1000);

// Create an LCD_I2C object with the I2C address 0x27, and a 16x2 display
LCD_I2C lcd(0x27, 16, 2);

int counter = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Scanning for I2C devices...");

  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      if (i < 16) {
        Serial.print("0");
      }
      Serial.println(i, HEX);
    }
  }
  Serial.println("Scan complete.");

  lcd.begin();  // Initialize the LCD display
  // lcd.printMessage("Welcome to LCD!");  // Display a welcome message
}

void loop() {
  led.update();  // Update the LED blinking
  
  lcd.updateCounter(counter);  // Update the LCD with the counter value
  counter++;                   // Increment the counter
  
  delay(1000);                  // Wait for 1 second before updating again
}