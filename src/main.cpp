
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"

int16_t baseSpeed = 160;
int16_t maxSpeed = 180;
int16_t minSpeed = -230;
float outputGain = 1.0;

Sensor sensor;
Logic logic(outputGain);
MotorController motorController(baseSpeed, maxSpeed, minSpeed);
uint16_t linePosition;

void setup() {
    //logic.initializeFuzzylogic();
    sensor.calibrate();
}

void loop() {
    linePosition = sensor.getLinePosition();
    int16_t output = logic.computeCourseCorrection(linePosition);
    motorController.setMotors(output);
}