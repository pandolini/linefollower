
#include <Sensor.hpp>

Sensor::Sensor() {
    qtr.setTypeRC();
    qtr.setSensorPins(sensorPins, sensorCount);
}

uint16_t Sensor::getLinePosition() {
    return qtr.readLineBlack(sensorValues);
}

void Sensor::calibrate() {
    for (uint16_t i = 0; i < 250; i++) {
        qtr.calibrate();
    }
}