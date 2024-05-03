
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"
#include "Webserver.hpp"

short baseSpeed = 210;
short maxSpeed = 255;
short minSpeed = -115;

float Kp = 10.0;
float Kd = 62.0;
float Ki = 0;
float outputGain = 1.0;

Sensor sensor;
Logic logic(Kp, Kd, Ki, outputGain);
MotorController motorController(baseSpeed, maxSpeed, minSpeed);
Webserver webserver("iPhone", "Qwefgh123");
unsigned short linePosition;

void setup() {
    sensor.calibrate();
    webserver.connectWiFi();
    webserver.setupServer(logic, motorController);
    // webserver.setupOTA();
}

void loop() {
    // webserver.handleOTA();
    linePosition = sensor.getLinePosition();
    short output = logic.computeCourseCorrection(linePosition);
    motorController.setMotors(output);
}