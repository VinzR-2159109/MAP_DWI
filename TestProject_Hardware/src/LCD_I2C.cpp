#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCD_I2C {
private:
  LiquidCrystal_I2C lcd; 
  int width;
  int height;

public:
  LCD_I2C(int address, int width, int height) : lcd(address, width, height) {
    this->width = width;
    this->height = height;
  }

  void begin() {
    lcd.begin(width, height);
    lcd.backlight();
  }

  void printMessage(const char* message) {
    lcd.setCursor(0, 0);
    lcd.print(message);
  }

  void updateCounter(int counter) {
    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(counter);
  }
};