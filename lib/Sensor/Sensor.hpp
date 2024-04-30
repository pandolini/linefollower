
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QTRSensors.h>

class Sensor {
public:
    Sensor();
    unsigned short getLinePosition();
    void calibrate();

private:
    QTRSensors qtr;
    static const unsigned char sensorCount = 15;
    unsigned short sensorValues[sensorCount];
    const unsigned char sensorPins[sensorCount] = {23, 22, 21, 19, 18, 17, 5, 25, 16, 33, 32, 26, 27, 14, 13};
};

#endif