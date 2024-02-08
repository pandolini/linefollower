
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QTRSensors.h>

class Sensor {
public:
    Sensor();
    uint16_t getLinePosition();
    void calibrate();

private:
    QTRSensors qtr;
    static const uint8_t SensorCount = 15;
    uint16_t sensorValues[SensorCount];
};

#endif