
#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include "./Logs/SensorLog.h"
#include <Arduino.h>
#include <WString.h>

class Sensor {
public:
    static constexpr int min_value = 0;
    static constexpr int max_value = 4096;

    explicit Sensor(int sensor_id, int pin)
        : sensorId(sensor_id), pin(pin) {}

    ~Sensor() = default;

    int sensor_id() const {
        return sensorId;
    }

    SensorLog get_moisture_reading() const {
        const int sensor_value = analogRead(pin);
        const SensorLog log(sensor_value, sensor_id());
        return log;
    }

private:
    int sensorId;
    int pin;
    String name;
};

#endif //MOISTURESENSOR_H
