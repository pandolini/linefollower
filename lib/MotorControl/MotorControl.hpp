#ifndef LINEFOLLOWER_MOTORCONTROL_HPP
#define LINEFOLLOWER_MOTORCONTROL_HPP

#include "Arduino.h"
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

Motor rightMotor(AIN1,AIN2,PWMA, leftOffset, STBY);
Motor leftMotor(BIN1, BIN2, PWMB, rightOffset, STBY);

int16_t velocity = 750;
int16_t bilBredde = 60;
int16_t radius = 11;
float leftWheelSpeed;
float rightWheelSpeed;

void setMotors(int8_t input) {
    float newInput = input / 10.0;
    leftWheelSpeed = ((float)velocity - newInput * (float)bilBredde / 2.0) / (float)radius;
    rightWheelSpeed = ((float)velocity + newInput * (float)bilBredde / 2.0) / (float)radius;
    leftMotor.drive(leftWheelSpeed);
    rightMotor.drive(rightWheelSpeed);
}

#endif