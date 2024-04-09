
#ifndef LINEFOLLOWER_MOTORCONTROL_HPP
#define LINEFOLLOWER_MOTORCONTROL_HPP

#include "SparkFun_TB6612.h"

int8_t AIN1 = 1;
int8_t BIN1 = 4;
int8_t AIN2 = 12;
int8_t BIN2 = 15;
int8_t PWMA = 0;
int8_t PWMB = 2;
int8_t STBY = 101; //Not in use

int8_t leftOffset = -1;
int8_t rightOffset = -1;

Motor leftMotor(AIN1, AIN2, PWMA, leftOffset, STBY);
Motor rightMotor(BIN1, BIN2, PWMB, rightOffset, STBY);

int16_t baseSpeed = 100;
float baseScaleFactor = 1;
float inputScaleFactor = 1.0;
float leftWheelSpeed;
float rightWheelSpeed;

void setMotors(int16_t input) {
    leftWheelSpeed = (int)(baseSpeed - inputScaleFactor*input)*baseScaleFactor;
    rightWheelSpeed = (int)(baseSpeed + inputScaleFactor*input)*baseScaleFactor;
    if (leftWheelSpeed < -100) {
        leftWheelSpeed = -100;
    }
    if (rightWheelSpeed < -100) {
        rightWheelSpeed = -100;
    }
    if (leftWheelSpeed > 200) {
        leftWheelSpeed = 200;
    }
    if (rightWheelSpeed > 200) {
        rightWheelSpeed = 200;
    }
    leftMotor.drive(leftWheelSpeed);
    rightMotor.drive(rightWheelSpeed);
}

#endif