
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
    static const uint8_t sensorCount = 17;
    uint16_t sensorValues[sensorCount];
    const uint8_t sensorPins[sensorCount] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 23, 25, 26, 27, 32, 33};
};

#endif