
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorControl.hpp"
#include "Sensor.hpp"

Sensor sensor;
Logic logic;
uint16_t linePosition;

void setup() {
    sensor.calibrate();
    logic.initialize();
}

void loop() {
    linePosition = sensor.getLinePosition();
    int8_t output = logic.getOutput(linePosition);
    setMotors(output);
}