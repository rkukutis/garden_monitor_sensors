#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define WIFI_SSID ""
#define WIFI_PASS ""
#define BACKEND_URI "http://192.168.1.###:5000/sensor_logs"

WiFiClient wifiClient;
HTTPClient httpClient;

void connectToWifi() {
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.printf("Connecting to access point: %s", WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Attempting connection to Wifi");
        delay(1000);
    }
    const IPAddress address = WiFi.localIP();
    Serial.println("Assigned IP: " + address.toString());
}

class SensorLog {
private:
    int value;
    int sensor_id;
public:
    SensorLog(const int value,const int sensor_id)
        : value(value),
          sensor_id(sensor_id) {
    }

    int getValue() const {
        return value;
    }

    int getSensorId() const {
        return sensor_id;
    }

    ~SensorLog() = default;
};

void sendLog(SensorLog log) {
    JsonDocument document;
    document["value"] = log.getValue();
    document["sensor_id"] = log.getSensorId();
    String json;
    serializeJson(document, json);
    Serial.println(json);
    httpClient.begin(wifiClient, BACKEND_URI);
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.POST(json);
}

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    connectToWifi();
}

void loop() {
    const SensorLog log(500, 1);
    JsonDocument document;


}