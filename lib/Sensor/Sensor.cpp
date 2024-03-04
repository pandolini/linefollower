
#include "Sensor.hpp"

Sensor::Sensor() {
    qtr.setTypeRC();
    qtr.setSensorPins(sensorPins, sensorCount);
}

void Sensor::calibrate() {
    for (uint16_t i = 0; i < 300; i++) {
        qtr.calibrate();
    }
}

uint16_t Sensor::getLinePosition() {
    return qtr.readLineBlack(sensorValues) / 100;
}
