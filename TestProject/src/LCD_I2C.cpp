#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCD_I2C {
private:
  LiquidCrystal_I2C lcd;  // LCD object for I2C display
  int width;
  int height;

public:
  // Constructor to initialize the LCD with address, width, and height
  LCD_I2C(int address, int width, int height) : lcd(address, width, height) {
    this->width = width;
    this->height = height;
  }

  // Method to initialize the LCD
  void begin() {
    lcd.begin(width, height);    // Initialize the LCD with given dimensions
    lcd.backlight();              // Turn on the backlight
  }

  // Method to print a message on the LCD
  void printMessage(const char* message) {
    lcd.setCursor(0, 0);          // Set the cursor to the first line
    lcd.print(message);           // Print the message
  }

  // Method to update the counter on the LCD
  void updateCounter(int counter) {
    lcd.setCursor(0, 1);          // Move the cursor to the second line
    lcd.print("Count: ");         // Display the label
    lcd.print(counter);           // Display the counter value
  }
};