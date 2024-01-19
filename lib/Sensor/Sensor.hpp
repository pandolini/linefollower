#ifndef LINEFOLLOWER_SENSOR_HPP
#define LINEFOLLOWER_SENSOR_HPP

#include "QTRSensors.h"
#include "Arduino.h"

class Sensor {
private:
    QTRSensors qtr;
    const uint8_t SENSOR_COUNT = 12;
    uint16_t sensorValues[12];
    const uint8_t PINS[12] = {A0, A1, A2, A3, A4, A5, 2, 3, 4, 5, 6, 7};

public:
    Sensor();

    void calibrate();

    uint16_t getPos();
};

#endif