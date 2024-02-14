
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorControl.hpp"
#include "Sensor.hpp"

Sensor sensor;
Logic logic;
uint16_t linePosition;

void setup() {
    sensor.initialize();
    logic.initialize();
}

void loop() {
    linePosition = sensor.getPos();
    setMotors(logic.getOutput(linePosition));
}