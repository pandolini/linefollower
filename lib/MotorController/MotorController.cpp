
#include "MotorController.hpp"

MotorController::MotorController(int16_t baseSpeed, int16_t maxSpeed, int16_t minSpeed):
baseSpeed_(baseSpeed), maxSpeed_(maxSpeed), minSpeed_(minSpeed),
leftMotor(AIN1, AIN2, PWMA, OFFSET, STBY), rightMotor(BIN1, BIN2, PWMB, OFFSET, STBY) {}

void MotorController::setMotors(int16_t input) {
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed_ + input);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed_ - input);
    leftMotor.drive(leftMotorSpeed);
    rightMotor.drive(rightMotorSpeed);
}

int16_t MotorController::constrainSpeed(int16_t speed) {
    if (speed > maxSpeed_) {
        return maxSpeed_;
    } else if (speed < minSpeed_) {
        return minSpeed_;
    } else {
        return speed;
    }
}
