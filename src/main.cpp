
#include "Arduino.h"
#include "Logic.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"
#include "Webserver.hpp"

int16_t baseSpeed = 150;
int16_t maxSpeed = 170;
int16_t minSpeed = -230;

double Kp = 5;
double Kd = 11;
double Ki = 0;
float outputGain = 1.0;

Sensor sensor;
Logic logic(Kp, Kd, Ki, outputGain);
MotorController motorController(baseSpeed, maxSpeed, minSpeed);
Webserver webserver("iPhone", "Qwefgh123");
uint16_t linePosition;

void setup() {
    //logic.initializeFuzzylogic();
    sensor.calibrate();
    webserver.connectWiFi();
    webserver.setupServer(logic, motorController);
    webserver.setupOTA();
}

void loop() {
    webserver.handleOTA();
    linePosition = sensor.getLinePosition();
//    logic.updateFuzzyParameters(linePosition);
    int16_t output = logic.computeCourseCorrection(linePosition);
    motorController.setMotors(output);
}