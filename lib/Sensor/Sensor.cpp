
#include <Sensor.hpp>

Sensor::Sensor() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){5, 14, 13, 25, 16, 17, 18, 19, 21, 22, 23, 26, 27, 32, 33}, SensorCount);
}

uint16_t Sensor::getLinePosition() {
    return qtr.readLineBlack(sensorValues);
}

void Sensor::calibrate() {
    for (uint16_t i = 0; i < 400; i++) {
        qtr.calibrate();
    }
}