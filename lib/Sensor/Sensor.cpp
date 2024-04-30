
#include "Sensor.hpp"

Sensor::Sensor() {
    qtr.setTypeRC();
    qtr.setSensorPins(sensorPins, sensorCount);
}

void Sensor::calibrate() {
    for (unsigned short i = 0; i < 300; i++) {
        qtr.calibrate();
    }
}

unsigned short Sensor::getLinePosition() {
    return qtr.readLineBlack(sensorValues) / 100;
}
