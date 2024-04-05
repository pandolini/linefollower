
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

int16_t baseSpeed = 125;
float baseScaleFactor = 0.6;
float inputScaleFactor = 1.0;
float leftWheelSpeed;
float rightWheelSpeed;

void setMotors(int8_t input) {
    leftWheelSpeed = (int)(baseSpeed - inputScaleFactor*input)*baseScaleFactor;
    rightWheelSpeed = (int)(baseSpeed + inputScaleFactor*input)*baseScaleFactor;
    if (leftWheelSpeed < 0) {
        leftWheelSpeed = 0;
    }
    if (rightWheelSpeed < 0) {
        rightWheelSpeed = 0;
    }
    leftMotor.drive(leftWheelSpeed);
    rightMotor.drive(rightWheelSpeed);
}

#endif