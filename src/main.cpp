
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"

int16_t baseSpeed = 200;
int16_t maxSpeed = 240;
int16_t minSpeed = maxSpeed *(-1);
float tractionGain = 2.0;
float outputGain = 2.0;

Sensor sensor;
Logic logic(outputGain);
MotorController motorController(baseSpeed, maxSpeed, minSpeed, tractionGain);
uint16_t linePosition;

void setup() {
    sensor.calibrate();
}

void loop() {
    linePosition = sensor.getLinePosition();
    int16_t output = logic.computeCourseCorrection(linePosition);
    int16_t deltaPosition = logic.deltaPosition(linePosition);
    motorController.tractionControl(deltaPosition);
    motorController.setMotors(output);
}