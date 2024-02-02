#ifndef LINEFOLLOWER_SENSOR_HPP
#define LINEFOLLOWER_SENSOR_HPP

#include "QTRSensors.h"
#include "Arduino.h"

class Sensor {
private:
    QTRSensors qtr;
    const uint8_t SENSOR_COUNT = 17;
    uint16_t sensorValues[17];
    const uint8_t PINS[17] = {4,5,12,14,13,16,17,18,19,21,22,23,25,26,27,32,33};

public:
    void initialize();

    void calibrate();

    uint16_t getPos();
};

#endif