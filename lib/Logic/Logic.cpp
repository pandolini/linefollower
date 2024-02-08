
#include "Logic.hpp"

Logic::Logic(double Kp, double Ki, double Kd) : Kp_(Kp), Ki_(Ki), Kd_(Kd), motorController(0, 2) {
}

void Logic::pidControl(uint16_t sensorPosition) {
    while (true) {
        position = sensorPosition;
        error = position - 7500;
        proportional = error;
        integral += error;
        derivative = error - lastError;
        output = (proportional * Kp_) + (integral * Ki_) + (derivative * Kd_);
        motorController.throttle(output);
        lastError = error;
    }
}