
#ifndef SENSORLOG_H
#define SENSORLOG_H

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

#endif //SENSORLOG_H
