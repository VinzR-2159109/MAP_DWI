#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// Define the OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance for the SSD1306 display with I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize the display
  if (!display.begin(0x3D)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
  }

  // Clear the buffer
  display.clearDisplay();

  // Display some text
  display.setTextSize(1);            // Text size (1 = small, 2 = medium, etc.)
  display.setTextColor(SSD1306_WHITE); // White color text
  display.setCursor(0, 10);          // Position (x=0, y=10)
  display.println("Hello, ESP32!");
  display.display();                 // Render the text on the display

  delay(2000); // Pause for 2 seconds
}

void loop() {
  // Update display content
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Counting:");
  display.println(millis() / 1000); // Display time in seconds since boot
  display.display();
  delay(1000); // Update every second
}
