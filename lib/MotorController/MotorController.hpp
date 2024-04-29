
#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP

#include <SparkFun_TB6612.h>

class MotorController {
    
public:
    MotorController(int16_t baseSpeed, int16_t maxSpeed, int16_t minSpeed);

    void setMotors(int16_t input);
    void enableMotors();
    void disableMotors();

    void setBaseSpeed(int16_t baseSpeed) { baseSpeed_ = baseSpeed; }
    void setMaxSpeed(int16_t maxSpeed) { maxSpeed_ = maxSpeed; }
    void setMinSpeed(int16_t minSpeed) { minSpeed_ = minSpeed; }
    int getBaseSpeed() const { return baseSpeed_; }
    int getMaxSpeed() const { return maxSpeed_; }
    int getMinSpeed() const { return minSpeed_; }

private:
    Motor leftMotor;
    Motor rightMotor;
    int16_t constrainSpeed(int16_t speed);

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
    };

#endif