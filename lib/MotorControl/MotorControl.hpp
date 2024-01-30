#ifndef LINEFOLLOWER_MOTORCONTROL_HPP
#define LINEFOLLOWER_MOTORCONTROL_HPP

#include "Arduino.h"
#include "SparkFun_TB6612.h"

int8_t AIN1 = 2;
int8_t BIN1 = 7;
int8_t AIN2 = 4;
int8_t BIN2 = 8;
int8_t PWMA = 5;
int8_t PWMB = 6;
int8_t STBY = 9;

int8_t leftOffset = 1;
int8_t rightOffset = 1;

Motor leftMotor(AIN1,AIN2,PWMA, leftOffset, STBY);
Motor rightMotor(BIN1, BIN2, PWMB, rightOffset, STBY);

int16_t velocity = 2000;
int16_t bilBredde = 60;
int16_t radius = 11;
int16_t leftWheelSpeed;
int16_t rightWheelSpeed;

void setMotors(int8_t input) {
    leftWheelSpeed = (velocity - input * bilBredde / 20) / radius;
    rightWheelSpeed = (velocity + input * bilBredde / 20) / radius;
    
    leftMotor.drive(leftWheelSpeed);
    rightMotor.drive(rightWheelSpeed);
}

#endif