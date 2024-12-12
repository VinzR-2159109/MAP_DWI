#include <WiFi.h>
#include <HTTPClient.h>

class WiFiHttpClient {
private:
    const char* ssid;
    const char* password;
    const char* serverUrl;

public:
    // Constructor
    WiFiHttpClient(const char* wifiSsid, const char* wifiPassword, const char* url)
        : ssid(wifiSsid), password(wifiPassword), serverUrl(url) {}

    // Method to connect to Wi-Fi
    void connectWiFi() {
        Serial.begin(115200);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to Wi-Fi...");
        }
        Serial.println("Connected to Wi-Fi");
    }

    // Method to send GET request
    void sendGetRequest() {
        HTTPClient http;
        http.begin(serverUrl);

        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("Response from server: " + payload);
        } else {
            Serial.println("Failed to connect to server");
        }
        http.end();
    }

    // Method to send POST request
    void sendPostRequest(const String& jsonData) {
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        int postHttpCode = http.POST(jsonData);
        if (postHttpCode > 0) {
            String response = http.getString();
            Serial.println("Response from server (POST): " + response);
        } else {
            Serial.println("Failed to send POST request");
        }
        http.end();
    }
};

// // Replace with your Wi-Fi credentials
// const char* ssid = "Hotspot van Vinz";
// const char* password = "Vinz1512.";

// // Replace with your server's IP and port
// const char* serverUrl = "http://192.168.1.10:5000/esp-data";

// WiFiHttpClient client(ssid, password, serverUrl);

// void setup() {
//     client.connectWiFi();
// }

// void loop() {
//     client.sendGetRequest();

//     String jsonData = "{\"sensor\": \"temperature\", \"value\": 25.5}";
//     client.sendPostRequest(jsonData);

//     delay(10000);  // Wait 10 seconds before next request
// }
