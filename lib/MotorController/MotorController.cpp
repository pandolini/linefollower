
#include "MotorController.hpp"

MotorController::MotorController(): motor1(AIN1, AIN2, PWMA, OFFSET, STBY), motor2(BIN1, BIN2, PWMB, OFFSET, STBY) {}

void MotorController::throttle(int16_t output) {
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed + output);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed - output);
    motor1.drive(rightMotorSpeed);
    motor2.drive(leftMotorSpeed);
}

int16_t MotorController::constrainSpeed(int16_t speed) {
    if (speed > maxSpeed) {
        return maxSpeed;
    } else if (speed < minSpeed) {
        return minSpeed;
    } else {
        return speed;
    }
}