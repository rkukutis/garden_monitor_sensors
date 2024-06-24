#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include  "./Sensors/Sensor.h"
#include "./secrets.h"

#define BACKEND_URI "http://192.168.1.100:3000/sensor_logs"
#define SOIL_MOISTURE_PIN 34

WiFiClient wifi_client;
HTTPClient http_client;
Sensor moisture_sensor(1, SOIL_MOISTURE_PIN);
unsigned long long uS_TO_H_FACTOR = 3600000000;

int sleep_hours = 1;

void connectToWifi() {
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    Serial.println("Assigned IP: " + WiFi.localIP().toString());
}

void send_sensor_log(SensorLog log) {
    JsonDocument document;
    document["value"] = log.getValue();
    document["sensor_id"] = log.getSensorId();
    String json;
    serializeJson(document, json);
    http_client.begin(wifi_client, BACKEND_URI);
    http_client.addHeader("Content-Type", "application/json");
    http_client.POST(json);
}

void enterDeepSleep() {
    esp_sleep_enable_timer_wakeup(sleep_hours * uS_TO_H_FACTOR);
    esp_deep_sleep_start();
}

void setup() {
    Serial.begin(115200);
    connectToWifi();
    send_sensor_log(moisture_sensor.get_moisture_reading());
    enterDeepSleep();
}

void loop() {
}