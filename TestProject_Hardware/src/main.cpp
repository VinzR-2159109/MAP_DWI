#include "HX711_Scale.cpp"

LoadCell myScale(2, 3);

void setup() {
    Serial.begin(9600);

    if (!myScale.isReady()) {
        Serial.println("Error: HX711 is not ready!");
        while (true);
    }

    // Tare the scale
    myScale.tare();

    // Calibrate (example using a 100g weight)
    Serial.println("Place a 22g weight on the scale.");
    delay(5000); // Wait for the user to place the weight
    myScale.calibrate(22.0f); // Assume 100g weight
}

void loop() {
    // Get the weight
    float weight = myScale.getWeight();
    if (weight >= 0) {
        Serial.print("Weight: ");
        Serial.print(weight, 2); // 2 decimal places
        Serial.println(" g");
    } else {
        Serial.println("Error reading weight.");
    }
    delay(1000); // Read every second
}