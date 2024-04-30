
#include "MotorController.hpp"

MotorController::MotorController(short baseSpeed, short maxSpeed, short minSpeed): 
baseSpeed_(baseSpeed), maxSpeed_(maxSpeed), minSpeed_(minSpeed),
leftMotor(AIN1, AIN2, PWMA, OFFSET, STBY), rightMotor(BIN1, BIN2, PWMB, OFFSET, STBY) 
{
    motorsEnabled_ = true;
}

void MotorController::setMotors(short input) {
    if (!motorsEnabled_) {
        return;
    }
    short rightMotorSpeed = constrainSpeed(baseSpeed_ + input);
    short leftMotorSpeed = constrainSpeed(baseSpeed_ - input);
    leftMotor.drive(leftMotorSpeed);
    rightMotor.drive(rightMotorSpeed);
}

void MotorController::enableMotors() {
    motorsEnabled_ = true;
}

void MotorController::disableMotors() {
    motorsEnabled_ = false;
    delay(100);
    leftMotor.brake();
    rightMotor.brake();
}

short MotorController::constrainSpeed(short speed) {
    if (speed > maxSpeed_) {
        return maxSpeed_;
    } else if (speed < minSpeed_) {
        return minSpeed_;
    } else {
        return speed;
    }
}