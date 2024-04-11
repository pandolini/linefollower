
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"

Sensor sensor;
Logic logic;
MotorController motorController(100, 200, -100, 1.0, 1.0);
uint16_t linePosition;

void setup() {
    sensor.calibrate();
    logic.initialize();
}

void loop() {
    linePosition = sensor.getLinePosition();
    int16_t output = logic.computeControlOutput(linePosition);
    motorController.setMotors(output);
}