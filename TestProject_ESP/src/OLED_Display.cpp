#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDDisplay {
private:
    uint8_t screenWidth;
    uint8_t screenHeight;
    Adafruit_SSD1306 display;

public:
    OLEDDisplay(uint8_t width, uint8_t height) : screenWidth(width), screenHeight(height), display(width, height, &Wire, -1) {}
    
    bool begin(uint8_t address = 0x3D) {
        if (!display.begin(SSD1306_SWITCHCAPVCC, address)) {
            Serial.println(F("SSD1306 allocation failed"));
            return false;
        }
        display.clearDisplay();
        return true;
    }

    void displayText(const String& text, uint8_t textSize = 1, uint16_t color = WHITE, int16_t x = 0, int16_t y = 0) {
        display.setTextSize(textSize);
        display.setTextColor(color);
        display.setCursor(x, y);
        display.println(text);
        display.display();
    }

    void clear() {
        display.clearDisplay();
        display.display();
    }
};

