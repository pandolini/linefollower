
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"
#include "Webserver.hpp"

float baseSpeed = 200;
float maxSpeed = 255;
float minSpeed = -110;

double Kp = 10.00;
double Kd = 60.00;
double Ki = 0;
float outputGain = 1.0;

Sensor sensor;
Logic logic(Kp, Kd, Ki, outputGain);
MotorController motorController(baseSpeed, maxSpeed, minSpeed);
Webserver webserver("iPhone", "Qwefgh123");
uint16_t linePosition;

void setup() {
    sensor.calibrate();
    webserver.connectWiFi();
    webserver.setupServer(logic, motorController);
    webserver.setupOTA();
}

void loop() {
    webserver.handleOTA();
    linePosition = sensor.getLinePosition();
    int16_t output = logic.computeCourseCorrection(linePosition);
    motorController.setMotors(output);
}