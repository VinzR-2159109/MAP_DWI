#include <Wire.h>
#include <Adafruit_VCNL4040.h>

class VCNL4040Sensor {
private:
    Adafruit_VCNL4040 vcnl4040;
    uint16_t detectionThreshold;

public:
    VCNL4040Sensor(uint16_t threshold = 3) : detectionThreshold(threshold) {}

    bool begin() {
        if (!vcnl4040.begin()) {
            Serial.println("Couldn't find VCNL4040 chip");
            return false;
        }
        Serial.println("Found VCNL4040 chip");

        vcnl4040.setProximityLEDCurrent(VCNL4040_LED_CURRENT_200MA);
        vcnl4040.setProximityLEDDutyCycle(VCNL4040_LED_DUTY_1_40);
        vcnl4040.setProximityIntegrationTime(VCNL4040_PROXIMITY_INTEGRATION_TIME_8T);

        return true;
    }

    bool isObjectDetected() {
        uint16_t proximity = vcnl4040.getProximity();
        return proximity >= detectionThreshold;
    }

    uint16_t getProximity() {
        return vcnl4040.getProximity();
    }

    void setThreshold(uint16_t threshold) {
        detectionThreshold = threshold;
    }
};


