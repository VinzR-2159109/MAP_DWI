#include <HX711.h>

class LoadCell {
private:
    HX711 scale;
    float calibration_factor;

public:
    LoadCell(int dataPin, int clockPin, float calFactor = 1.0) {
        scale.begin(dataPin, clockPin);
        calibration_factor = calFactor;
    }

    void tare() {
        Serial.println("Taring... Please ensure no weight is on the scale.");
        delay(2000);
        scale.tare(10);
        Serial.println("Tare completed.");
    }

    void calibrate(float knownWeight) {
        Serial.println("Calibrating...");
        float rawReading = scale.get_units(10);
        calibration_factor = rawReading / knownWeight;
        Serial.print("New calibration factor: ");
        Serial.println(calibration_factor);
        Serial.println(rawReading);
        Serial.println(knownWeight);
    }

    void setCalibrationFactor(float factor) {
        calibration_factor = factor;
        Serial.print("Calibration factor set to: ");
        Serial.println(calibration_factor);
    }

    float getCalibrationFactor() {
        return calibration_factor;
    }

    float getWeight(int readings = 5) {
        if (scale.is_ready()) {
            return scale.get_units(readings) / calibration_factor;
        } else {
            Serial.println("HX711 not ready.");
            return -1;
        }
    }

    bool isReady() {
        return scale.is_ready();
    }
};
