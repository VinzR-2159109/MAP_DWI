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

    // Calibrate
    Serial.println("Place a 22g weight on the scale and press 'C' to calibrate.");
    while (true) {
        if (Serial.available() > 0) {
            char key = Serial.read();
            if (key == 'c') {
                myScale.calibrate(22.0f);
                break;
            }
        }
    }
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