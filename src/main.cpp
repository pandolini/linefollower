
#include <Arduino.h>
#include "Logic.hpp"

Sensor sensor;
Logic logic;
void setup() {
    sensor.calibrate();
}

void loop() {
    logic.pidControl(sensor.getLinePosition());
}