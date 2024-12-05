#include <SoftwareSerial.h>
#include <Arduino.h>

class BluetoothManager {
private:
    SoftwareSerial bluetooth;
    int rxPin;
    int txPin;
    int baudRate;
    int statePin;
    bool isInitialized = false;

public:
    BluetoothManager(int rx, int tx, int state, int baud) : bluetooth(rx, tx), rxPin(rx), txPin(tx), baudRate(baud), statePin(state) {}

    // Initialize Bluetooth module
    void begin() {
        pinMode(statePin, INPUT);
        bluetooth.begin(baudRate);
        Serial.println("Bluetooth module initialized.");
        isInitialized = true;
    }

    // Send a single character to Bluetooth
    void sendToBluetooth(char data) {
        if (!isInitialized) {
            Serial.println("Error: Bluetooth not initialized.");
            return;
        }
        bluetooth.write(data);
    }

    // Send a string to Bluetooth
    void sendStringToBluetooth(const String &data) {
        if (!isInitialized) {
            Serial.println("Error: Bluetooth not initialized.");
            return;
        }
        bluetooth.print(data);
    }

    // Receive a single character from Bluetooth
    char readFromBluetooth() {
        if (!isInitialized || !bluetooth.available()) {
            return '\0'; // No data available
        }
        return bluetooth.read();
    }

    // Receive a string from Bluetooth
    String readStringFromBluetooth() {
        if (!isInitialized) {
            Serial.println("Error: Bluetooth not initialized.");
            return "";
        }
        String result = "";
        while (bluetooth.available()) {
            result += (char)bluetooth.read();
        }
        return result;
    }

    // Check if data is available from Bluetooth
    bool isDataAvailable() {
        return isInitialized && bluetooth.available() > 0;
    }

    bool isConnected() {
        return digitalRead(statePin) == HIGH;
    }

    // Forward data from Bluetooth to Serial Monitor
    void forwardToSerial() {
        if (!isInitialized) {
            Serial.println("Error: Bluetooth not initialized.");
            return;
        }
        while (bluetooth.available()) {
            char data = bluetooth.read();
            Serial.write(data);
        }
    }

    // Forward data from Serial Monitor to Bluetooth
    void forwardToBluetooth() {
        if (!isInitialized) {
            Serial.println("Error: Bluetooth not initialized.");
            return;
        }
        while (Serial.available()) {
            char data = Serial.read();
            bluetooth.write(data);
        }
    }
};
