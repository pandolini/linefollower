#include "Sensor.hpp"

Sensor::Sensor() {
    for (auto &&pin : PINS)
    {
        pinMode(pin, INPUT);
    }

    qtr.setTypeRC();
    qtr.setSensorPins(PINS, SENSOR_COUNT);

    calibrate();
}

void Sensor::calibrate() {
    for (uint16_t i = 0; i < 400; i++) // Calibration loop (400 iterations)
    {
        qtr.calibrate();
    }
}

uint16_t Sensor::getPos() {
        return qtr.readLineBlack(sensorValues);
    }
