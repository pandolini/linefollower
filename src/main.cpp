
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"

int16_t baseSpeed = 200;
int16_t maxSpeed = 255;
float outputGain = 2.0;

Sensor sensor;
Logic logic(outputGain);
MotorController motorController(baseSpeed, maxSpeed);
uint16_t linePosition;

void setup() {
    sensor.calibrate();
}

void loop() {
    linePosition = sensor.getLinePosition();
    int16_t output = logic.computeCourseCorrection(linePosition);
    motorController.setMotors(output);
}