
#include <Arduino.h>
#include "Sensor.hpp"
#include "Logic.hpp"


Sensor sensor;
Logic logic(0.015, 0.000, 0.0375);
void setup() {
    sensor.calibrate();
}

void loop() {
    logic.pidControl(sensor.getLinePosition());
}