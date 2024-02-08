#include <Arduino.h>
#include "Sensor.hpp"
#include "MotorController.hpp"

Sensor sensor;
MotorController motorController;

void pidControl() {
    uint16_t position = sensor.getLinePosition();
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
        position = sensor.getLinePosition();
        error = position - 5500;
        motorController.throttle(output);
    }
}

void setup() {
    sensor.calibrate();
}

void loop() {
    pidControl();
}