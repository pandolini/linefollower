
#include "MotorController.hpp"

MotorController::MotorController(int16_t baseSpeed, int16_t maxSpeed, int16_t minSpeed): 
baseSpeed_(baseSpeed), maxSpeed_(maxSpeed), minSpeed_(minSpeed),
leftMotor(AIN1, AIN2, PWMA, OFFSET, STBY), rightMotor(BIN1, BIN2, PWMB, OFFSET, STBY) 
{
    previousTime_ = 0;
    motorsEnabled_ = true;
}

void MotorController::setMotors(int16_t input) {
    if (!motorsEnabled_) {
        return;
    }
    int16_t rightMotorSpeed = constrainSpeed(baseSpeed_ + input);
    int16_t leftMotorSpeed = constrainSpeed(baseSpeed_ - input);
    leftMotor.drive(leftMotorSpeed);
    rightMotor.drive(rightMotorSpeed);
}

void MotorController::setBaseSpeed(int16_t baseSpeed) {
    baseSpeed_ = baseSpeed;
}

void MotorController::setMaxSpeed(int16_t maxSpeed) {
    maxSpeed_ = maxSpeed;
}

void MotorController::setMinSpeed(int16_t minSpeed) {
    minSpeed_ = minSpeed;
}

int MotorController::getBaseSpeed() const {
    return baseSpeed_;
}

int MotorController::getMaxSpeed() const {
    return maxSpeed_;
}

int MotorController::getMinSpeed() const {
    return minSpeed_;
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

int16_t MotorController::constrainSpeed(int16_t speed) {
    if (speed > maxSpeed_) {
        return maxSpeed_;
    } else if (speed < minSpeed_) {
        return minSpeed_;
    } else {
        return speed;
    }
}

int16_t MotorController::constrainAcceleration(int16_t speed, bool isRightMotor) {
    int16_t previousSpeed = isRightMotor ? previousRightMotorSpeed_ : previousLeftMotorSpeed_;

    if (abs(speed - previousSpeed) > maxAcceleration_) {
        if (speed > previousSpeed) {
            speed = previousSpeed + maxAcceleration_;
        } else {
            speed = previousSpeed - maxAcceleration_;
        }
    }

    if (isRightMotor) {
        previousRightMotorSpeed_ = speed;
    } else {
        previousLeftMotorSpeed_ = speed;
    }

    return speed;
}

int16_t MotorController::constrainTopSpeed(int16_t speed) {
    unsigned long deltaTime_ = time_ - previousTime_;
    if (abs(speed) < maxSpeed_) {
        return speed;
    }
    if (deltaTime_ > topSpeedDuration_) {
        speed * 0.8;
        previousTime_ = time_;
    }
    return speed;
}