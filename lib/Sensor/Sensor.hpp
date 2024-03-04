
#ifndef LINEFOLLOWER_SENSOR_HPP
#define LINEFOLLOWER_SENSOR_HPP

#include <QTRSensors.h>

class Sensor {
public:
    Sensor();
    uint16_t getLinePosition();
    void calibrate();

private:
    QTRSensors qtr;
    static const uint8_t sensorCount = 15;
    uint16_t sensorValues[sensorCount];
    const uint8_t sensorPins[sensorCount] = {5, 14, 13, 25, 16, 17, 18, 19, 21, 22, 23, 26, 27, 32, 33};
};

#endif