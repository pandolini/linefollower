#ifndef LINEFOLLOWER_SENSOR_HPP
#define LINEFOLLOWER_SENSOR_HPP

#include "QTRSensors.h"
#include "Arduino.h"

class Sensor {
private:
    QTRSensors qtr;
    const uint8_t SENSOR_COUNT = 15;
    uint16_t sensorValues[15];
    const uint8_t PINS[15] = {5,14,13,25,16,17,18,19,21,22,23,26,27,32,33};

public:
    void initialize();

    void calibrate();

    uint16_t getPos();
};

#endif