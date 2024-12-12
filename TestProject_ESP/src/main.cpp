#include "MQTT_Client.cpp"

ESP32MQTTClient esp32MqttClient("Hotspot van Vinz", "Vinz1512.", "192.168.1.10", "test/topic");

void setup() {
    esp32MqttClient.begin();
}

void loop() {
    esp32MqttClient.run();
}
