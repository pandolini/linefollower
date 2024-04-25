
#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <SparkFun_TB6612.h>

class MotorController {
public:
    MotorController(int16_t baseSpeed, int16_t maxSpeed, int16_t minSpeed);

    void setMotors(int16_t input);
    void setBaseSpeed(int16_t baseSpeed);
    void setMaxSpeed(int16_t maxSpeed);
    void setMinSpeed(int16_t minSpeed);
    void enableMotors();
    void disableMotors();
    
private:
    Motor leftMotor;
    Motor rightMotor;
    int16_t constrainSpeed(int16_t speed);
    int16_t constrainAcceleration(int16_t speed, bool isRightMotor);
    int16_t constrainTopSpeed(int16_t speed);

    static const int8_t AIN1 = 1;
    static const int8_t BIN1 = 4;
    static const int8_t AIN2 = 12;
    static const int8_t BIN2 = 15;
    static const int8_t PWMA = 0;
    static const int8_t PWMB = 2;
    static const int8_t STBY = 101; //Not in use
    static const int8_t OFFSET = -1;

    bool motorsEnabled_;
    int16_t baseSpeed_;
    int16_t maxSpeed_;
    int16_t minSpeed_;
    int16_t previousRightMotorSpeed_;
    int16_t previousLeftMotorSpeed_;
    unsigned long time_ = millis();
    unsigned long previousTime_;
    int16_t maxAcceleration_ = 10;
    int topSpeedDuration_ = 5000;
    };

#endif