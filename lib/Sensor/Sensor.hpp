
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
    const uint8_t sensorPins[sensorCount] = {23, 22, 21, 19, 18, 17, 5, 25, 16, 33, 32, 26, 27, 14, 13};
};

#endif