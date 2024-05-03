
#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <SparkFun_TB6612.h>

class MotorController {
    
public:
    MotorController(short baseSpeed, short maxSpeed, short minSpeed);

    void setMotors(short input);
    void enableMotors();
    void disableMotors();

    void setBaseSpeed(short baseSpeed) { baseSpeed_ = baseSpeed; }
    void setMaxSpeed(short maxSpeed) { maxSpeed_ = maxSpeed; }
    void setMinSpeed(short minSpeed) { minSpeed_ = minSpeed; }
    short getBaseSpeed() const { return baseSpeed_; }
    short getMaxSpeed() const { return maxSpeed_; }
    short getMinSpeed() const { return minSpeed_; }

private:
    short constrainSpeed(short speed);
    bool motorsEnabled_;
    short baseSpeed_;
    short maxSpeed_;
    short minSpeed_;

    Motor leftMotor;
    Motor rightMotor;
    static const char AIN1 = 1;
    static const char BIN1 = 4;
    static const char AIN2 = 12;
    static const char BIN2 = 15;
    static const char PWMA = 0;
    static const char PWMB = 2;
    static const char STBY = 101; //Not in use
    static const char OFFSET = -1;
    };

#endif