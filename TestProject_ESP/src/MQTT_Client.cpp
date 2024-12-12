#include <WiFi.h>
#include <PubSubClient.h>

class ESP32MQTTClient {
private:
    // WiFi and MQTT details
    const char* ssid;
    const char* password;
    const char* mqtt_server;
    const int mqtt_port;
    const char* mqtt_topic;

    WiFiClient espClient;
    PubSubClient client;

    void setup_wifi() {
        delay(10);
        Serial.println();
        Serial.print("Connecting to WiFi");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }
        Serial.println();
        Serial.println("WiFi connected");
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Attempting MQTT connection...");
            if (client.connect("ESP32Client")) {
                Serial.println("connected");
            } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" trying again in 5 seconds");
                delay(5000);
            }
        }
    }

public:
    ESP32MQTTClient(const char* ssid, const char* password, const char* mqtt_server, const char* mqtt_topic, int mqtt_port = 1883)
        : ssid(ssid), password(password), mqtt_server(mqtt_server), mqtt_topic(mqtt_topic), mqtt_port(mqtt_port), client(espClient) {}

    void begin() {
        Serial.begin(115200);
        setup_wifi();
        client.setServer(mqtt_server, mqtt_port);
    }

    void run() {
        if (!client.connected()) {
            reconnect();
        }
        client.loop();

        // Publish a message to the MQTT broker
        String payload = "Hello from ESP32";
        client.publish(mqtt_topic, payload.c_str());
        delay(2000); // Publish every 2 seconds
    }
};
