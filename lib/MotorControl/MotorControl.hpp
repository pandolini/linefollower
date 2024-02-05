
#ifndef LINEFOLLOWER_MOTORCONTROL_HPP
#define LINEFOLLOWER_MOTORCONTROL_HPP

#include "SparkFun_TB6612.h"

int8_t AIN1 = 97;
int8_t BIN1 = 98;
int8_t AIN2 = 99;
int8_t BIN2 = 100;
int8_t PWMA = 0;
int8_t PWMB = 2;
int8_t STBY = 101;

int8_t leftOffset = 1;
int8_t rightOffset = 1;

Motor rightMotor(AIN1, AIN2, PWMA, leftOffset, STBY);
Motor leftMotor(BIN1, BIN2, PWMB, rightOffset, STBY);

int16_t baseSpeed = 125;
float scaleFactor = 0.5;
float leftWheelSpeed;
float rightWheelSpeed;

void setMotors(int8_t input) {
    leftWheelSpeed = baseSpeed - input;
    rightWheelSpeed = baseSpeed + input;
    leftMotor.drive(leftWheelSpeed * scaleFactor);
    rightMotor.drive(rightWheelSpeed * scaleFactor);
}

#endif