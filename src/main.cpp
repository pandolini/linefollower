#include <Arduino.h>
#include <QTRSensors.h>
#include "MotorController.hpp"

MotorController motorController;
QTRSensors qtr;
const uint8_t SensorCount = 15;
uint16_t sensorValues[SensorCount];

void calibrationSequence() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){5, 14, 13, 25, 16, 17, 18, 19, 21, 22, 23, 26, 27, 32, 33}, SensorCount);
    delay(500);

    for (uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();
    }
}

void pidControl() {
    uint16_t position = qtr.readLineBlack(sensorValues);
    int16_t error = position - 5500;
    int16_t proportional = 0;
    int16_t integral = 0;
    int16_t derivative = 0;
    int16_t lastError = 0;
    int16_t output = 0;
    const double Kp = 0.01500;
    const double Ki = 0.00000;
    const double Kd = 0.03750;

    while (true) {// PID loop
        proportional = error;
        integral += error;
        derivative = error - lastError;
        output = (proportional * Kp) + (integral * Ki) + (derivative * Kd);
        lastError = error;
        position = qtr.readLineBlack(sensorValues);
        error = position - 5500;
        motorController.throttle(output);
    }
}

void setup() {
    calibrationSequence();
}

void loop() {
    pidControl();
}