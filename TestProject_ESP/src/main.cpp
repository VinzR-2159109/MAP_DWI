#include <Arduino.h>
#include "VCNL4040.cpp"

VCNL4040Sensor proximitySensor;

void setup() {
    Serial.begin(115200);

    while (!Serial) { delay(1); }

    Serial.println("Initializing VCNL4040...");

    if (!proximitySensor.begin()) {
        Serial.println("Failed to initialize VCNL4040. Check wiring.");
        while (1);
    }
    Serial.println("VCNL4040 initialized successfully.");
}

void loop() {
    if (proximitySensor.isObjectDetected()) {
        Serial.println("Object detected!");
    } else {
        Serial.println("No object detected.");
    }

    Serial.print("Proximity value: ");
    Serial.println(proximitySensor.getProximity());
    
    delay(500);
}