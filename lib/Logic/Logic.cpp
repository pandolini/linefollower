
#include "Logic.hpp"

Logic::Logic() {
}

void Logic::pidControl(uint16_t sensorPosition) {
    uint16_t position = sensorPosition;
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
        position = sensorPosition;
        error = position - 5500;
        motorController.throttle(output);
    }
}