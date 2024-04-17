
#include "MotorController.hpp"

MotorController::MotorController(int16_t baseSpeed, int16_t maxSpeed, int16_t minSpeed, float tractionGain):
baseSpeed_(baseSpeed), maxSpeed_(maxSpeed), minSpeed_(minSpeed), tractionGain_(tractionGain),
leftMotor(AIN1, AIN2, PWMA, OFFSET, STBY), rightMotor(BIN1, BIN2, PWMB, OFFSET, STBY) 
{
    setSpeed(baseSpeed_);
}

void MotorController::setMotors(int16_t input) {
    int16_t rightMotorSpeed = constrainSpeed(speed_ + input);
    int16_t leftMotorSpeed = constrainSpeed(speed_ - input);
    leftMotor.drive(leftMotorSpeed);
    rightMotor.drive(rightMotorSpeed);
}

int16_t MotorController::constrainSpeed(int16_t speed) {
    if (!tractionMode) {
        upperLimit = maxSpeed_;
        lowerLimit = minSpeed_;
    } else {
        upperLimit = maxSpeed_ / tractionGain_;
        lowerLimit = minSpeed_ / tractionGain_;
    }
    if (speed > upperLimit) {
        return upperLimit;
    } else if (speed < lowerLimit) {
        return lowerLimit;
    } else {
        return speed;
    }
}

void MotorController::tractionControl(int16_t deltaPosition) {
    if (abs(deltaPosition) > tractionThreshold) {
        setSpeed(baseSpeed_ / tractionGain_);
        tractionMode = true;
    } else if (abs(deltaPosition) < tractionThreshold && tractionMode) {
        while (speed_ < baseSpeed_) {
            setSpeed(speed_ + 1);
        }
        tractionMode = false;
    } else {
        setSpeed(baseSpeed_);
    }
}

void MotorController::setSpeed(int16_t speed) {
    speed_ = speed;
}